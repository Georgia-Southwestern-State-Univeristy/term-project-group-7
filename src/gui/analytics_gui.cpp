#include "gui/main_menu_gui.h"

#include <ctime>
#include <iomanip>
#include <sstream>
#include <string>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <cmath>

#include "../../database/sqlite/sqlite3.h"

#define ANALYTICS_THEME_BUTTON_ID 301
#define ANALYTICS_REFRESH_BUTTON_ID 302

struct AnalyticsWindowState {
  bool darkModeEnabled;
  HWND reportTextBox;
  HWND themeButton;
  HWND refreshButton;
  HBRUSH backgroundBrush;
  HBRUSH panelBrush;
  HBRUSH editBrush;
};

static COLORREF GetBackgroundColor(bool darkModeEnabled) {
  return darkModeEnabled ? RGB(30, 30, 30) : RGB(245, 245, 245);
}

static COLORREF GetPanelColor(bool darkModeEnabled) {
  return darkModeEnabled ? RGB(55, 55, 58) : RGB(235, 235, 235);
}

static COLORREF GetEditColor(bool darkModeEnabled) {
  return darkModeEnabled ? RGB(37, 37, 38) : RGB(255, 255, 255);
}

static COLORREF GetTextColor(bool darkModeEnabled) {
  return darkModeEnabled ? RGB(235, 235, 235) : RGB(20, 20, 20);
}

static void RefreshAnalyticsBrushes(AnalyticsWindowState *windowState) {
  if (!windowState)
    return;

  if (windowState->backgroundBrush)
    DeleteObject(windowState->backgroundBrush);
  if (windowState->panelBrush)
    DeleteObject(windowState->panelBrush);
  if (windowState->editBrush)
    DeleteObject(windowState->editBrush);

  windowState->backgroundBrush =
      CreateSolidBrush(GetBackgroundColor(windowState->darkModeEnabled));
  windowState->panelBrush =
      CreateSolidBrush(GetPanelColor(windowState->darkModeEnabled));
  windowState->editBrush =
      CreateSolidBrush(GetEditColor(windowState->darkModeEnabled));
}

static void DrawThemeToggleIcon(HDC deviceContext, RECT rect, bool darkModeEnabled) {
  COLORREF iconColor = darkModeEnabled ? RGB(250, 250, 250) : RGB(30, 30, 30);

  int width = rect.right - rect.left;
  int height = rect.bottom - rect.top;
  int centerX = rect.left + width / 2;
  int centerY = rect.top + height / 2;

  HBRUSH iconBrush = CreateSolidBrush(iconColor);
  HBRUSH backgroundBrush = CreateSolidBrush(GetPanelColor(darkModeEnabled));
  HPEN pen = CreatePen(PS_SOLID, 1, iconColor);

  HGDIOBJ oldBrush = SelectObject(deviceContext, iconBrush);
  HGDIOBJ oldPen = SelectObject(deviceContext, pen);

  if (!darkModeEnabled) {
    int sunRadius = min(width, height) / 6;

    Ellipse(deviceContext, centerX - sunRadius, centerY - sunRadius,
            centerX + sunRadius, centerY + sunRadius);

    const int rayLength = sunRadius + 8;
    const int rayInner = sunRadius + 3;

    for (int i = 0; i < 8; i++) {
      double angle = (3.14159265358979323846 / 4.0) * i;
      int x1 = centerX + (int)(cos(angle) * rayInner);
      int y1 = centerY + (int)(sin(angle) * rayInner);
      int x2 = centerX + (int)(cos(angle) * rayLength);
      int y2 = centerY + (int)(sin(angle) * rayLength);

      MoveToEx(deviceContext, x1, y1, NULL);
      LineTo(deviceContext, x2, y2);
    }
  } else {
    int moonRadius = min(width, height) / 4;

    Ellipse(deviceContext, centerX - moonRadius, centerY - moonRadius,
            centerX + moonRadius, centerY + moonRadius);

    SelectObject(deviceContext, backgroundBrush);
    SelectObject(deviceContext, GetStockObject(NULL_PEN));

    int cutOffsetX = moonRadius / 2;
    int cutOffsetY = moonRadius / 5;

    Ellipse(deviceContext,
            centerX - moonRadius + cutOffsetX,
            centerY - moonRadius - cutOffsetY,
            centerX + moonRadius + cutOffsetX,
            centerY + moonRadius - cutOffsetY);
  }

  SelectObject(deviceContext, oldBrush);
  SelectObject(deviceContext, oldPen);

  DeleteObject(iconBrush);
  DeleteObject(backgroundBrush);
  DeleteObject(pen);
}

static std::string GetPathToDatabase() {
  char pathToExecutable[MAX_PATH] = {};
  GetModuleFileNameA(NULL, pathToExecutable, MAX_PATH);
  std::string fullPath(pathToExecutable);
  auto lastSlash = fullPath.find_last_of("\\/");
  return (lastSlash != std::string::npos ? fullPath.substr(0, lastSlash + 1) : "") +
         "questions.db";
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

      report << "Total answered  : " << totalAnswered << "\r\n";
      report << "Correct         : " << totalCorrect << "\r\n";
      report << "Incorrect       : " << totalIncorrect << "\r\n";
      report << "Overall score   : " << overallScore << "%\r\n";
    } else {
      report << "No sessions have been recorded yet.\r\n";
    }

    sqlite3_finalize(preparedStatement);
  }

  report << "\r\n";

  {
    const char *breakdownBySubjectSQL =
        "SELECT "
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

      report << "\r\n" << topicName << "\r\n";
      report << "  Answered  : " << total << "\r\n";
      report << "  Correct   : " << correct << "\r\n";
      report << "  Incorrect : " << incorrect << "\r\n";
      report << "  Score     : " << score << "%\r\n";
    }

    if (!anyRowsFound)
      report << "No subject data yet.\r\n";
    sqlite3_finalize(preparedStatement);
  }

  report << "\r\n";

  {
    const char *breakdownByGradeSQL =
        "SELECT "
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

      report << "\r\nGrade " << gradeLevel << "\r\n";
      report << "  Answered  : " << total << "\r\n";
      report << "  Correct   : " << correct << "\r\n";
      report << "  Incorrect : " << incorrect << "\r\n";
      report << "  Score     : " << score << "%\r\n";
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
             << formattedDate << "  " << topicName << " Grade " << gradeLevel << "  "
             << correctCount << "/" << totalCount << " (" << scorePercent << "%)\r\n";
    }

    if (!anyRowsFound)
      report << "No sessions recorded yet.\r\n";
    sqlite3_finalize(preparedStatement);
  }

  return report.str();
}

static void RefreshAnalyticsReport(AnalyticsWindowState *windowState) {
  if (!windowState || !windowState->reportTextBox)
    return;

  int firstVisibleLine = (int)SendMessage(windowState->reportTextBox, EM_GETFIRSTVISIBLELINE, 0, 0);

  sqlite3 *database = nullptr;
  sqlite3_open(GetPathToDatabase().c_str(), &database);
  std::string reportText = BuildAnalyticsReportText(database);
  if (database)
    sqlite3_close(database);

  SetWindowText(windowState->reportTextBox, reportText.c_str());
  SendMessage(windowState->reportTextBox, EM_LINESCROLL, 0, firstVisibleLine);
}

static void ApplyAnalyticsTheme(HWND windowHandle, AnalyticsWindowState *windowState) {
  if (!windowState)
    return;

  windowState->darkModeEnabled = IsDarkModeEnabled();
  RefreshAnalyticsBrushes(windowState);

  InvalidateRect(windowHandle, NULL, TRUE);
  UpdateWindow(windowHandle);
}

static void DrawAnalyticsButton(const DRAWITEMSTRUCT *drawItem, bool darkModeEnabled, bool themeButton) {
  COLORREF fillColor = darkModeEnabled ? RGB(55, 55, 58) : RGB(235, 235, 235);
  COLORREF borderColor = darkModeEnabled ? RGB(140, 140, 140) : RGB(150, 150, 150);
  COLORREF textColor = GetTextColor(darkModeEnabled);

  HBRUSH fillBrush = CreateSolidBrush(fillColor);
  FillRect(drawItem->hDC, &drawItem->rcItem, fillBrush);
  DeleteObject(fillBrush);

  HPEN borderPen = CreatePen(PS_SOLID, 1, borderColor);
  HGDIOBJ oldPen = SelectObject(drawItem->hDC, borderPen);
  HGDIOBJ oldBrush = SelectObject(drawItem->hDC, GetStockObject(NULL_BRUSH));
  Rectangle(drawItem->hDC, drawItem->rcItem.left, drawItem->rcItem.top,
            drawItem->rcItem.right, drawItem->rcItem.bottom);
  SelectObject(drawItem->hDC, oldBrush);
  SelectObject(drawItem->hDC, oldPen);
  DeleteObject(borderPen);

  if (themeButton) {
    DrawThemeToggleIcon(drawItem->hDC, drawItem->rcItem, darkModeEnabled);
    return;
  }

  SetBkMode(drawItem->hDC, TRANSPARENT);
  SetTextColor(drawItem->hDC, textColor);

  wchar_t buttonText[64] = {};
  GetWindowTextW(drawItem->hwndItem, buttonText, 64);
  DrawTextW(drawItem->hDC, buttonText, -1,
            const_cast<RECT *>(&drawItem->rcItem),
            DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

LRESULT CALLBACK AnalyticsWindowMessageHandler(HWND windowHandle, UINT message, WPARAM wParam,
                                               LPARAM lParam) {
  AnalyticsWindowState *windowState =
      reinterpret_cast<AnalyticsWindowState *>(
          GetWindowLongPtr(windowHandle, GWLP_USERDATA));

  switch (message) {

  case WM_CREATE: {
    windowState = new AnalyticsWindowState();
    windowState->darkModeEnabled = IsDarkModeEnabled();
    windowState->reportTextBox = NULL;
    windowState->themeButton = NULL;
    windowState->refreshButton = NULL;
    windowState->backgroundBrush = NULL;
    windowState->panelBrush = NULL;
    windowState->editBrush = NULL;

    SetWindowLongPtr(windowHandle, GWLP_USERDATA,
                     reinterpret_cast<LONG_PTR>(windowState));
    RefreshAnalyticsBrushes(windowState);

    HFONT monospaceFont =
        CreateFont(20, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
                   OUT_OUTLINE_PRECIS, CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY,
                   FIXED_PITCH, TEXT("Courier New"));

    windowState->refreshButton =
        CreateWindow("BUTTON", "Refresh",
                     WS_VISIBLE | WS_CHILD | BS_OWNERDRAW,
                     620, 10, 75, 36, windowHandle,
                     (HMENU)(UINT_PTR)ANALYTICS_REFRESH_BUTTON_ID, NULL, NULL);

    windowState->themeButton =
        CreateWindowW(L"BUTTON", L"",
                      WS_VISIBLE | WS_CHILD | BS_OWNERDRAW,
                      700, 10, 50, 36, windowHandle,
                      (HMENU)(UINT_PTR)ANALYTICS_THEME_BUTTON_ID, NULL, NULL);

    windowState->reportTextBox =
        CreateWindow("EDIT", "",
                     WS_VISIBLE | WS_CHILD | WS_BORDER | WS_VSCROLL | WS_HSCROLL |
                         ES_MULTILINE | ES_READONLY | ES_AUTOVSCROLL,
                     10, 55, 740, 475, windowHandle, NULL, NULL, NULL);

    SendMessage(windowState->themeButton, WM_SETFONT, (WPARAM)monospaceFont, TRUE);
    SendMessage(windowState->refreshButton, WM_SETFONT, (WPARAM)monospaceFont, TRUE);
    SendMessage(windowState->reportTextBox, WM_SETFONT, (WPARAM)monospaceFont, TRUE);

    RefreshAnalyticsReport(windowState);
    break;
  }

  case WM_SIZE:
    if (windowState) {
      int clientWidth = LOWORD(lParam);
      int clientHeight = HIWORD(lParam);

      MoveWindow(windowState->refreshButton, clientWidth - 160, 10, 75, 36, TRUE);
      MoveWindow(windowState->themeButton, clientWidth - 80, 10, 50, 36, TRUE);
      MoveWindow(windowState->reportTextBox, 10, 55, clientWidth - 20, clientHeight - 65, TRUE);
    }
    return 0;

  case WM_COMMAND:
    if (windowState && LOWORD(wParam) == ANALYTICS_THEME_BUTTON_ID) {
      ToggleDarkModeEnabled();
    }
    if (windowState && LOWORD(wParam) == ANALYTICS_REFRESH_BUTTON_ID) {
      RefreshAnalyticsReport(windowState);
    }
    return 0;

  case WM_DRAWITEM:
    if (windowState) {
      const DRAWITEMSTRUCT *drawItem =
          reinterpret_cast<DRAWITEMSTRUCT *>(lParam);
      bool isThemeButton = (drawItem->CtlID == ANALYTICS_THEME_BUTTON_ID);
      DrawAnalyticsButton(drawItem, windowState->darkModeEnabled, isThemeButton);
      return TRUE;
    }
    break;

  case WM_CTLCOLORSTATIC:
    if (windowState) {
      HDC deviceContext = reinterpret_cast<HDC>(wParam);
      SetTextColor(deviceContext, GetTextColor(windowState->darkModeEnabled));
      SetBkColor(deviceContext, GetBackgroundColor(windowState->darkModeEnabled));
      return reinterpret_cast<INT_PTR>(windowState->backgroundBrush);
    }
    break;

  case WM_CTLCOLOREDIT:
    if (windowState) {
      HDC deviceContext = reinterpret_cast<HDC>(wParam);
      SetTextColor(deviceContext, GetTextColor(windowState->darkModeEnabled));
      SetBkColor(deviceContext, GetEditColor(windowState->darkModeEnabled));
      return reinterpret_cast<INT_PTR>(windowState->editBrush);
    }
    break;

  case WM_ERASEBKGND:
    if (windowState) {
      RECT clientArea;
      GetClientRect(windowHandle, &clientArea);
      FillRect(reinterpret_cast<HDC>(wParam), &clientArea, windowState->backgroundBrush);
      return 1;
    }
    break;

  case WM_APP_THEME_CHANGED:
    if (windowState) {
      ApplyAnalyticsTheme(windowHandle, windowState);
    }
    return 0;

  case WM_DESTROY:
    if (windowState) {
      if (windowState->backgroundBrush)
        DeleteObject(windowState->backgroundBrush);
      if (windowState->panelBrush)
        DeleteObject(windowState->panelBrush);
      if (windowState->editBrush)
        DeleteObject(windowState->editBrush);
      delete windowState;
    }
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
                     WS_OVERLAPPEDWINDOW,
                     CW_USEDEFAULT, CW_USEDEFAULT, 780, 600, parentWindow, NULL,
                     GetModuleHandle(NULL), NULL);

  if (!analyticsWindow)
    return;

  ShowWindow(analyticsWindow, SW_SHOW);
  UpdateWindow(analyticsWindow);
}