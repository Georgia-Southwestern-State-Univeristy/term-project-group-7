#include "gui/addition_gui.h"

#include <iomanip>
#include <sstream>
#include <string>
#include <windows.h>

#include "../../database/sqlite/sqlite3.h"

static std::string GetPathToDatabase() {
  char pathToExecutable[MAX_PATH] = {};
  GetModuleFileNameA(NULL, pathToExecutable, MAX_PATH);
  std::string fullPath(pathToExecutable);
  auto lastSlash = fullPath.find_last_of("\\/");
  return (lastSlash != std::string::npos ? fullPath.substr(0, lastSlash + 1) : "") + "questions.db";
}

static std::string BuildAnalyticsReportText(sqlite3 *database) {
  if (!database)
    return "Could not open the database.";

  std::ostringstream report;
  report << std::fixed << std::setprecision(1);

  {
    const char *lifetimeTotalsSQL =
        "SELECT "
        "    SUM(correct_answers)                       AS totalCorrect, "
        "    SUM(total_questions - correct_answers)     AS totalIncorrect, "
        "    SUM(total_questions)                       AS totalAnswered "
        "FROM sessions;";

    sqlite3_stmt *preparedStatement = nullptr;
    sqlite3_prepare_v2(database, lifetimeTotalsSQL, -1, &preparedStatement, nullptr);

    report << "       LIFETIME TOTALS \r\n";

    if (sqlite3_step(preparedStatement) == SQLITE_ROW &&
        sqlite3_column_type(preparedStatement, 2) != SQLITE_NULL) {

      int totalCorrect = sqlite3_column_int(preparedStatement, 0);
      int totalIncorrect = sqlite3_column_int(preparedStatement, 1);
      int totalAnswered = sqlite3_column_int(preparedStatement, 2);
      double overallScore = totalAnswered > 0 ? totalCorrect * 100.0 / totalAnswered : 0.0;

      report << "Total answered  : " << totalAnswered   << "\r\n";
      report << "Correct         : " << totalCorrect    << "\r\n";
      report << "Incorrect       : " << totalIncorrect  << "\r\n";
      report << "Overall score   : " << overallScore    << "%\r\n";
    } else {
      report << "No sessions have been recorded yet.\r\n";
    }

    sqlite3_finalize(preparedStatement);
  }

  report << "\r\n";

  {
    const char *breakdownBySubjectSQL = "SELECT "
                                        "    topic, "
                                        "    SUM(correct_answers)                   AS correct, "
                                        "    SUM(total_questions - correct_answers) AS incorrect, "
                                        "    SUM(total_questions)                   AS total "
                                        "FROM sessions "
                                        "GROUP BY LOWER(topic) "
                                        "ORDER BY LOWER(topic);";

    sqlite3_stmt *preparedStatement = nullptr;
    sqlite3_prepare_v2(database, breakdownBySubjectSQL, -1, &preparedStatement, nullptr);

    report << "      BREAKDOWN BY SUBJECT \r\n";

    bool anyRowsFound = false;
    while (sqlite3_step(preparedStatement) == SQLITE_ROW) {
      anyRowsFound = true;

      const char *rawTopicName =
          reinterpret_cast<const char *>(sqlite3_column_text(preparedStatement, 0));
      std::string topicName = rawTopicName ? rawTopicName : "unknown";
      topicName[0] = (char)toupper((unsigned char)topicName[0]);

      int correct = sqlite3_column_int(preparedStatement, 1);
      int incorrect = sqlite3_column_int(preparedStatement, 2);
      int total = sqlite3_column_int(preparedStatement, 3);
      double score = total > 0 ? correct * 100.0 / total : 0.0;

      report << "\r\n" << topicName             << "\r\n";
      report << "  Answered  : " << total       << "\r\n";
      report << "  Correct   : " << correct     << "\r\n";
      report << "  Incorrect : " << incorrect   << "\r\n";
      report << "  Score     : " << score       << "%\r\n";
    }

    if (!anyRowsFound)
      report << "No subject data yet.\r\n";
    sqlite3_finalize(preparedStatement);
  }

  report << "\r\n";

  {
    const char *breakdownByGradeSQL = "SELECT "
                                      "    grade_level, "
                                      "    SUM(correct_answers)                   AS correct, "
                                      "    SUM(total_questions - correct_answers) AS incorrect, "
                                      "    SUM(total_questions)                   AS total "
                                      "FROM sessions "
                                      "GROUP BY grade_level "
                                      "ORDER BY grade_level;";

    sqlite3_stmt *preparedStatement = nullptr;
    sqlite3_prepare_v2(database, breakdownByGradeSQL, -1, &preparedStatement, nullptr);

    report << "      BREAKDOWN BY GRADE  \r\n";

    bool anyRowsFound = false;
    while (sqlite3_step(preparedStatement) == SQLITE_ROW) {
      anyRowsFound = true;

      int gradeLevel = sqlite3_column_int(preparedStatement, 0);
      int correct = sqlite3_column_int(preparedStatement, 1);
      int incorrect = sqlite3_column_int(preparedStatement, 2);
      int total = sqlite3_column_int(preparedStatement, 3);
      double score = total > 0 ? correct * 100.0 / total : 0.0;

      report << "\r\nGrade "     << gradeLevel  << "\r\n";
      report << "  Answered  : " << total       << "\r\n";
      report << "  Correct   : " << correct     << "\r\n";
      report << "  Incorrect : " << incorrect   << "\r\n";
      report << "  Score     : " << score       << "%\r\n";
    }

    if (!anyRowsFound)
      report << "No grade data yet.\r\n";
    sqlite3_finalize(preparedStatement);
  }

  report << "\r\n";

  {
    const char *recentSessionsSQL =
        "SELECT started_at, topic, grade_level, correct_answers, total_questions, score_percentage "
        "FROM sessions "
        "ORDER BY started_at DESC "
        "LIMIT 10;";

    sqlite3_stmt *preparedStatement = nullptr;
    sqlite3_prepare_v2(database, recentSessionsSQL, -1, &preparedStatement, nullptr);

    report << "      RECENT SESSIONS (last 10)  \r\n";

    bool anyRowsFound = false;
    while (sqlite3_step(preparedStatement) == SQLITE_ROW) {
      anyRowsFound = true;

      long long sessionTimestamp = sqlite3_column_int64(preparedStatement, 0);
      const char *rawTopicName =
          reinterpret_cast<const char *>(sqlite3_column_text(preparedStatement, 1));
      std::string topicName = rawTopicName ? rawTopicName : "unknown";
      topicName[0] = (char)toupper((unsigned char)topicName[0]);

      int gradeLevel = sqlite3_column_int(preparedStatement, 2);
      int correctCount = sqlite3_column_int(preparedStatement, 3);
      int totalCount = sqlite3_column_int(preparedStatement, 4);
      double scorePercent = sqlite3_column_double(preparedStatement, 5);

      time_t timeValue = (time_t)sessionTimestamp;
      struct tm *timeInfo = localtime(&timeValue);
      char formattedDate[32] = {};
      strftime(formattedDate, sizeof(formattedDate), "%m/%d/%Y %H:%M", timeInfo);

      report << "\r\n"
             << formattedDate   << "  " << topicName  << " Grade " << gradeLevel   << "  "
             << correctCount    << "/"  << totalCount << " ("      << scorePercent << "%)\r\n";
    }

    if (!anyRowsFound)
      report << "No sessions recorded yet.\r\n";
    sqlite3_finalize(preparedStatement);
  }

  return report.str();
}

LRESULT CALLBACK AnalyticsWindowMessageHandler(HWND windowHandle, UINT message, WPARAM wParam,
                                               LPARAM lParam) {
  switch (message) {

  case WM_CREATE: {
    HFONT monospaceFont =
        CreateFont(20, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
                   CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, FIXED_PITCH, TEXT("Courier New"));

    HWND reportTextBox = CreateWindow("EDIT", "",
                                      WS_VISIBLE | WS_CHILD | WS_BORDER | WS_VSCROLL | WS_HSCROLL |
                                          ES_MULTILINE | ES_READONLY | ES_AUTOVSCROLL,
                                      10, 10, 740, 520, windowHandle, NULL, NULL, NULL);

    SendMessage(reportTextBox, WM_SETFONT, (WPARAM)monospaceFont, TRUE);

    sqlite3 *database = nullptr;
    sqlite3_open(GetPathToDatabase().c_str(), &database);
    std::string reportText = BuildAnalyticsReportText(database);
    if (database)
      sqlite3_close(database);

    SetWindowText(reportTextBox, reportText.c_str());
    break;
  }

  case WM_DESTROY:
    return 0;
  }

  return DefWindowProc(windowHandle, message, wParam, lParam);
}

void ShowAnalyticsWindow(HWND parentWindow) {
  static bool analyticsWindowClassRegistered = false;
  if (!analyticsWindowClassRegistered) {
    WNDCLASS analyticsWindowClass = {};
    analyticsWindowClass.lpfnWndProc = AnalyticsWindowMessageHandler;
    analyticsWindowClass.hInstance = GetModuleHandle(NULL);
    analyticsWindowClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    analyticsWindowClass.lpszClassName = "AnalyticsWindowClass";
    RegisterClass(&analyticsWindowClass);
    analyticsWindowClassRegistered = true;
  }

  HWND analyticsWindow =
      CreateWindowEx(0, "AnalyticsWindowClass", "Analytics",
                     WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX, CW_USEDEFAULT,
                     CW_USEDEFAULT, 780, 600, parentWindow, NULL, GetModuleHandle(NULL), NULL);

  if (!analyticsWindow)
    return;
  ShowWindow(analyticsWindow, SW_SHOW);
  UpdateWindow(analyticsWindow);
}