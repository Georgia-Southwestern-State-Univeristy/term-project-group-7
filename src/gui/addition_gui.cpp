#include "gui/addition_gui.h"
#include "gui/main_menu_gui.h"
#include "gui/question_bank.h"

#include <cctype>
#include <commctrl.h>
#include <cstring>
#include <ctime>
#include <richedit.h>
#include <sstream>
#include <string>
#include <vector>

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#define SUBMIT_BUTTON_ID 201
#define HOME_BUTTON_ID 202
#define HINT_BUTTON_ID 203
#define THEME_BUTTON_ID 204

struct QuizWindowState {
  std::vector<Question> questionList;
  std::vector<AnsweredQuestion> answeredQuestions;
  int currentQuestionIndex;
  int correctAnswerForCurrentQuestion;
  int gradeLevel;
  std::string topic;
  std::string sessionId;
  bool waitingForNextClick;
  bool darkModeEnabled;
  bool showError;

  HWND progressLabel;
  HWND questionLabel;
  HWND answerLabel;
  HWND answerInputBox;
  HWND submitButton;
  HWND homeButton;
  HWND hintButton;
  HWND themeButton;
  HWND resultLabel;
  HWND explanationBox;

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

static COLORREF GetSubmitButtonColor(bool darkModeEnabled) {
  return darkModeEnabled ? RGB(85, 130, 85) : RGB(198, 234, 198);
}

static COLORREF GetHintButtonColor(bool darkModeEnabled) {
  return darkModeEnabled ? RGB(135, 120, 70) : RGB(247, 236, 181);
}

static std::string GetPathToDatabase() {
  char pathToExecutable[MAX_PATH] = {};
  GetModuleFileNameA(NULL, pathToExecutable, MAX_PATH);
  std::string fullPath(pathToExecutable);
  auto lastSlash = fullPath.find_last_of("\\/");
  return (lastSlash != std::string::npos ? fullPath.substr(0, lastSlash + 1) : "") + "questions.db";
}

static std::string BuildUniqueSessionId(const std::string &topic) {
  return std::to_string(static_cast<long long>(time(nullptr))) + "_" + topic;
}

static void RefreshQuizBrushes(QuizWindowState *quizState) {
  if (!quizState)
    return;

  if (quizState->backgroundBrush)
    DeleteObject(quizState->backgroundBrush);
  if (quizState->panelBrush)
    DeleteObject(quizState->panelBrush);
  if (quizState->editBrush)
    DeleteObject(quizState->editBrush);

  quizState->backgroundBrush = CreateSolidBrush(GetBackgroundColor(quizState->darkModeEnabled));
  quizState->panelBrush = CreateSolidBrush(GetPanelColor(quizState->darkModeEnabled));
  quizState->editBrush = CreateSolidBrush(GetEditColor(quizState->darkModeEnabled));
}

static std::wstring ToWide(const std::string &text) {
  if (text.empty())
    return L"";

  int wideLength = MultiByteToWideChar(CP_UTF8, 0, text.c_str(), -1, NULL, 0);

  if (wideLength <= 0) {
    wideLength = MultiByteToWideChar(CP_ACP, 0, text.c_str(), -1, NULL, 0);
    if (wideLength <= 0)
      return L"";
    std::wstring output(wideLength - 1, L'\0');
    MultiByteToWideChar(CP_ACP, 0, text.c_str(), -1, &output[0], wideLength);
    return output;
  }

  std::wstring output(wideLength - 1, L'\0');
  MultiByteToWideChar(CP_UTF8, 0, text.c_str(), -1, &output[0], wideLength);
  return output;
}

static bool ParseSimpleBinaryQuestion(const std::string &questionText, int &leftValue,
                                      std::string &operation, int &rightValue) {
  std::istringstream input(questionText);
  if (!(input >> leftValue))
    return false;
  if (!(input >> operation))
    return false;
  if (!(input >> rightValue))
    return false;
  return true;
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

    Ellipse(deviceContext, centerX - sunRadius, centerY - sunRadius, centerX + sunRadius,
            centerY + sunRadius);

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

    Ellipse(deviceContext, centerX - moonRadius, centerY - moonRadius, centerX + moonRadius,
            centerY + moonRadius);

    SelectObject(deviceContext, backgroundBrush);
    SelectObject(deviceContext, GetStockObject(NULL_PEN));

    int cutOffsetX = moonRadius / 2;
    int cutOffsetY = moonRadius / 5;

    Ellipse(deviceContext, centerX - moonRadius + cutOffsetX, centerY - moonRadius - cutOffsetY,
            centerX + moonRadius + cutOffsetX, centerY + moonRadius - cutOffsetY);
  }

  SelectObject(deviceContext, oldBrush);
  SelectObject(deviceContext, oldPen);

  DeleteObject(iconBrush);
  DeleteObject(backgroundBrush);
  DeleteObject(pen);
}

static void DrawHomeIcon(HDC deviceContext, RECT rect, bool darkModeEnabled) {
  COLORREF iconColor = darkModeEnabled ? RGB(250, 250, 250) : RGB(20, 20, 20);
  COLORREF cutColor = GetPanelColor(darkModeEnabled);

  const int centerX = (rect.left + rect.right) / 2;
  const int centerY = (rect.top + rect.bottom) / 2;

  const int iconWidth = 26;
  const int iconHeight = 22;

  const int left = centerX - iconWidth / 2;
  const int right = centerX + iconWidth / 2;
  const int top = centerY - iconHeight / 2;
  const int bottom = centerY + iconHeight / 2;

  const int roofPeakY = top;
  const int roofBaseY = top + 9;

  const int bodyLeftX = centerX - 9;
  const int bodyRightX = centerX + 9;
  const int bodyTopY = roofBaseY - 1;
  const int bodyBottomY = bottom;

  const int doorLeftX = centerX - 3;
  const int doorRightX = centerX + 3;
  const int doorTopY = bottom - 8;

  HBRUSH iconBrush = CreateSolidBrush(iconColor);
  HBRUSH cutBrush = CreateSolidBrush(cutColor);
  HPEN iconPen = CreatePen(PS_SOLID, 1, iconColor);

  HGDIOBJ oldBrush = SelectObject(deviceContext, iconBrush);
  HGDIOBJ oldPen = SelectObject(deviceContext, iconPen);

  POINT roof[3];
  roof[0] = {centerX, roofPeakY};
  roof[1] = {left, roofBaseY};
  roof[2] = {right, roofBaseY};
  Polygon(deviceContext, roof, 3);

  Rectangle(deviceContext, bodyLeftX, bodyTopY, bodyRightX, bodyBottomY);

  SelectObject(deviceContext, cutBrush);
  SelectObject(deviceContext, GetStockObject(NULL_PEN));
  Rectangle(deviceContext, doorLeftX, doorTopY, doorRightX, bodyBottomY);

  SelectObject(deviceContext, oldBrush);
  SelectObject(deviceContext, oldPen);

  DeleteObject(iconBrush);
  DeleteObject(cutBrush);
  DeleteObject(iconPen);
}

static std::string BuildHintText(const Question &question) {
  int leftValue = 0;
  int rightValue = 0;
  std::string operation;

  if (!ParseSimpleBinaryQuestion(question.questionText, leftValue, operation, rightValue)) {
    return "Break the problem into smaller steps and focus on one part at a time.";
  }

  std::ostringstream hint;

  if (operation == "+") {
    hint << "Start at the ones place for " << leftValue << " + " << rightValue << ".\r\n";
    hint << "Add each column from right to left and carry if a column is 10 or more.";
    return hint.str();
  }

  if (operation == "-") {
    hint << "Start at the ones place for " << leftValue << " - " << rightValue << ".\r\n";
    hint << "Subtract right to left and borrow from the next place if needed.";
    return hint.str();
  }

  if (operation == "*" || operation == "x" || operation == "X") {
    hint << "For " << leftValue << " x " << rightValue
         << ", think about equal groups or break one number into easier parts.";
    return hint.str();
  }

  if (operation == "/" || operation == "÷") {
    hint << "Use the related multiplication fact.\r\n";
    hint << "Ask: what number multiplied by " << rightValue << " gives " << leftValue << "?";
    return hint.str();
  }

  return "Solve it one step at a time and check your place values carefully.";
}

static std::string BuildStepByStepSolution(const Question &question) {
  int leftValue = 0;
  int rightValue = 0;
  std::string operation;

  std::ostringstream steps;
  steps << "Correct answer: " << question.correctAnswer << "\r\n\r\n";

  if (!ParseSimpleBinaryQuestion(question.questionText, leftValue, operation, rightValue)) {
    if (!question.explanation.empty()) {
      steps << "Steps:\r\n" << question.explanation;
    } else {
      steps
          << "Steps:\r\nSolve the problem one step at a time and compare with the correct answer.";
    }
    return steps.str();
  }

  if (operation == "+") {
    steps << "Steps:\r\n";
    steps << "1. Write " << leftValue << " and " << rightValue
          << " in vertical columns by place value.\r\n";
    steps << "2. Add from the ones column and move left.\r\n";
    steps << "3. Carry to the next column if a sum is 10 or more.\r\n";
    steps << "4. Final answer: " << leftValue << " + " << rightValue << " = "
          << question.correctAnswer << ".\r\n";
  } else if (operation == "-") {
    steps << "Steps:\r\n";
    steps << "1. Write " << leftValue << " and " << rightValue
          << " in vertical columns by place value.\r\n";
    steps << "2. Subtract from right to left.\r\n";
    steps << "3. Borrow from the next column when the top digit is too small.\r\n";
    steps << "4. Final answer: " << leftValue << " - " << rightValue << " = "
          << question.correctAnswer << ".\r\n";
  } else if (operation == "*" || operation == "x" || operation == "X") {
    steps << "Steps:\r\n";
    steps << "1. Multiply " << leftValue << " by " << rightValue << ".\r\n";
    steps << "2. Break the numbers into smaller multiplication facts if that helps.\r\n";
    steps << "3. Add partial products if needed.\r\n";
    steps << "4. Final answer: " << leftValue << " x " << rightValue << " = "
          << question.correctAnswer << ".\r\n";
  } else if (operation == "/" || operation == "÷") {
    steps << "Steps:\r\n";
    steps << "1. Think of the related multiplication fact.\r\n";
    steps << "2. Ask: what number times " << rightValue << " equals " << leftValue << "?\r\n";
    steps << "3. The answer is " << question.correctAnswer << " because " << question.correctAnswer
          << " x " << rightValue << " = " << leftValue << ".\r\n";
    steps << "4. Final answer: " << leftValue << " / " << rightValue << " = "
          << question.correctAnswer << ".\r\n";
  }

  if (!question.explanation.empty()) {
    steps << "\r\nTeacher note / explanation:\r\n" << question.explanation;
  }

  return steps.str();
}

static void SaveLiveProgress(QuizWindowState *quizState) {
  if (!quizState || quizState->answeredQuestions.empty())
    return;

  try {
    QuestionBank questionBank(GetPathToDatabase());
    questionBank.saveSessionResults(quizState->sessionId, quizState->gradeLevel, quizState->topic,
                                    quizState->answeredQuestions);
  } catch (...) {
  }
}

static void SetButtonToSubmitMode(QuizWindowState *quizState) {
  if (!quizState)
    return;
  SetWindowText(quizState->submitButton, "Submit");
}

static void SetButtonToNextMode(QuizWindowState *quizState) {
  if (!quizState)
    return;
  SetWindowText(quizState->submitButton, "Next");
}

static void ClearRichText(HWND richEditHandle) { SetWindowTextW(richEditHandle, L""); }

static void AppendRichText(HWND richEditHandle, const std::wstring &text, COLORREF color,
                           bool bold) {
  CHARRANGE selectionRange;
  selectionRange.cpMin = -1;
  selectionRange.cpMax = -1;
  SendMessage(richEditHandle, EM_EXSETSEL, 0, (LPARAM)&selectionRange);

  CHARFORMAT2W format = {};
  format.cbSize = sizeof(format);
  format.dwMask = CFM_COLOR | CFM_BOLD;
  format.crTextColor = color;
  format.dwEffects = bold ? CFE_BOLD : 0;

  SendMessage(richEditHandle, EM_SETCHARFORMAT, SCF_SELECTION, (LPARAM)&format);
  SendMessageW(richEditHandle, EM_REPLACESEL, FALSE, (LPARAM)text.c_str());
}

static void ApplyQuizTheme(HWND windowHandle, QuizWindowState *quizState) {
  if (!quizState)
    return;

  quizState->darkModeEnabled = IsDarkModeEnabled();
  RefreshQuizBrushes(quizState);

  SendMessage(quizState->explanationBox, EM_SETBKGNDCOLOR, 0,
              (LPARAM)GetEditColor(quizState->darkModeEnabled));

  InvalidateRect(windowHandle, NULL, TRUE);
  UpdateWindow(windowHandle);
}

static void ShowExplanationDefault(QuizWindowState *quizState) {
  ClearRichText(quizState->explanationBox);
  AppendRichText(quizState->explanationBox,
                 L"Click Hint for guidance before answering. If your answer is incorrect, the full "
                 L"steps will appear here.",
                 GetTextColor(quizState->darkModeEnabled), false);
}

static void ShowHintText(QuizWindowState *quizState, const Question &currentQuestion) {
  COLORREF hintColor = quizState->darkModeEnabled ? RGB(255, 230, 90) : RGB(160, 120, 0);

  ClearRichText(quizState->explanationBox);
  AppendRichText(quizState->explanationBox, L"HINT:\r\n", hintColor, true);
  AppendRichText(quizState->explanationBox, ToWide(BuildHintText(currentQuestion)), hintColor,
                 false);
}

static void ShowCorrectText(QuizWindowState *quizState, const Question &currentQuestion) {
  COLORREF correctColor = RGB(80, 180, 80);

  ClearRichText(quizState->explanationBox);
  AppendRichText(quizState->explanationBox, L"CORRECT:\r\n", correctColor, true);
  AppendRichText(quizState->explanationBox, ToWide(BuildHintText(currentQuestion)), correctColor,
                 false);
}

static void ShowWrongAnswerSteps(QuizWindowState *quizState, const Question &currentQuestion) {
  ClearRichText(quizState->explanationBox);

  std::wstring correctAnswerLine =
      L"Correct answer: " + std::to_wstring(currentQuestion.correctAnswer) + L"\r\n\r\n";
  AppendRichText(quizState->explanationBox, correctAnswerLine, RGB(255, 80, 80), true);

  std::string fullText = BuildStepByStepSolution(currentQuestion);
  std::string prefix =
      "Correct answer: " + std::to_string(currentQuestion.correctAnswer) + "\r\n\r\n";
  if (fullText.rfind(prefix, 0) == 0) {
    fullText = fullText.substr(prefix.size());
  }

  AppendRichText(quizState->explanationBox, ToWide(fullText),
                 GetTextColor(quizState->darkModeEnabled), false);
}

static void ShowSavedMessage(QuizWindowState *quizState) {
  ClearRichText(quizState->explanationBox);
  AppendRichText(quizState->explanationBox,
                 L"Your results were saved. Press the Home icon to return to the menu.",
                 RGB(80, 180, 80), true);
}

static void LayoutQuizControls(HWND windowHandle, QuizWindowState *quizState) {
  if (!quizState)
    return;

  RECT clientRect;
  GetClientRect(windowHandle, &clientRect);

  int clientWidth = clientRect.right - clientRect.left;
  int clientHeight = clientRect.bottom - clientRect.top;

  if (clientWidth < 900)
    clientWidth = 900;
  if (clientHeight < 700)
    clientHeight = 700;

  const int buttonW = 65;
  const int buttonH = 38;
  const int outerMargin = 24;

  MoveWindow(quizState->homeButton, outerMargin, 18, buttonW, buttonH, TRUE);
  MoveWindow(quizState->themeButton, clientRect.right - outerMargin - buttonW, 18, buttonW, buttonH,
             TRUE);

  const int contentWidth = 760;
  int leftX = (clientWidth - contentWidth) / 2;
  if (leftX < 60)
    leftX = 60;

  const int progressY = 96;
  const int questionY = 138;
  const int answerY = 195;
  const int buttonY = 245;
  const int resultY = 288;
  const int explanationY = 315;
  int explanationHeight = clientHeight - explanationY - 20;
  if (explanationHeight < 260)
    explanationHeight = 260;

  MoveWindow(quizState->progressLabel, leftX, progressY, 520, 28, TRUE);
  MoveWindow(quizState->questionLabel, leftX, questionY, contentWidth, 48, TRUE);

  MoveWindow(quizState->answerLabel, leftX, answerY, 120, 24, TRUE);
  MoveWindow(quizState->answerInputBox, leftX + 125, answerY - 4, 130, 30, TRUE);

  MoveWindow(quizState->submitButton, leftX + (contentWidth / 2) - 60, buttonY, 120, 40, TRUE);
  MoveWindow(quizState->hintButton, leftX + contentWidth - 120, buttonY, 120, 40, TRUE);

  MoveWindow(quizState->resultLabel, leftX, resultY, contentWidth, 24, TRUE);
  MoveWindow(quizState->explanationBox, leftX, explanationY, contentWidth, explanationHeight, TRUE);
}

static void DisplayCurrentQuestion(QuizWindowState *quizState) {
  if (!quizState || quizState->questionList.empty())
    return;
  if (quizState->currentQuestionIndex >= static_cast<int>(quizState->questionList.size()))
    return;

  const Question &currentQuestion = quizState->questionList[quizState->currentQuestionIndex];
  quizState->correctAnswerForCurrentQuestion = currentQuestion.correctAnswer;
  quizState->waitingForNextClick = false;

  std::string progressText = "Question " + std::to_string(quizState->currentQuestionIndex + 1) +
                             " of " +
                             std::to_string(static_cast<int>(quizState->questionList.size()));

  SetWindowText(quizState->progressLabel, progressText.c_str());
  SetWindowText(quizState->questionLabel, currentQuestion.questionText.c_str());
  SetWindowText(quizState->answerInputBox, "");
  SetWindowText(quizState->resultLabel, "");
  quizState->showError = false;
  ShowExplanationDefault(quizState);
  SetButtonToSubmitMode(quizState);
  SetFocus(quizState->answerInputBox);
}

static void SaveAndShowFinalScore(QuizWindowState *quizState) {
  int totalAnswered = static_cast<int>(quizState->answeredQuestions.size());
  int totalCorrect = 0;

  for (const auto &answeredQuestion : quizState->answeredQuestions) {
    if (answeredQuestion.wasCorrect) {
      totalCorrect++;
    }
  }

  SaveLiveProgress(quizState);

  int scorePercent = totalAnswered > 0 ? (totalCorrect * 100 / totalAnswered) : 0;
  std::string finalScoreText = "All done! You scored " + std::to_string(totalCorrect) + " out of " +
                               std::to_string(totalAnswered) + " (" + std::to_string(scorePercent) +
                               "%)";

  SetWindowText(quizState->questionLabel, finalScoreText.c_str());
  SetWindowText(quizState->progressLabel, "");
  SetWindowText(quizState->answerInputBox, "");
  SetWindowText(quizState->resultLabel, "");
  quizState->showError = false;
  ShowSavedMessage(quizState);
  EnableWindow(quizState->submitButton, FALSE);
  EnableWindow(quizState->hintButton, FALSE);
}

static void HandleHintButtonPressed(QuizWindowState *quizState) {
  if (!quizState || quizState->questionList.empty())
    return;
  if (quizState->currentQuestionIndex >= static_cast<int>(quizState->questionList.size()))
    return;
  if (quizState->waitingForNextClick)
    return;

  const Question &currentQuestion = quizState->questionList[quizState->currentQuestionIndex];
  ShowHintText(quizState, currentQuestion);
}

static void HandleSubmitButtonPressed(QuizWindowState *quizState) {
  if (!quizState || quizState->questionList.empty())
    return;

  if (quizState->waitingForNextClick) {
    quizState->waitingForNextClick = false;

    if (quizState->currentQuestionIndex >= static_cast<int>(quizState->questionList.size())) {
      SaveAndShowFinalScore(quizState);
    } else {
      DisplayCurrentQuestion(quizState);
    }
    return;
  }

  char userTypedAnswer[64] = {};
  GetWindowText(quizState->answerInputBox, userTypedAnswer, 64);

  if (userTypedAnswer[0] == '\0') {
    quizState->showError = true;
    SetWindowText(quizState->resultLabel, "Input an answer before submitting");
    return;
  }

  quizState->showError = false;

  int userAnswer = atoi(userTypedAnswer);
  const Question &currentQuestion = quizState->questionList[quizState->currentQuestionIndex];
  bool answeredCorrectly = (userAnswer == currentQuestion.correctAnswer);

  AnsweredQuestion answeredQuestion;
  answeredQuestion.questionId = currentQuestion.questionId;
  answeredQuestion.topic = currentQuestion.topic;
  answeredQuestion.gradeLevel = currentQuestion.gradeLevel;
  answeredQuestion.wasCorrect = answeredCorrectly;
  quizState->answeredQuestions.push_back(answeredQuestion);

  SaveLiveProgress(quizState);
  quizState->currentQuestionIndex++;
  quizState->waitingForNextClick = true;
  SetButtonToNextMode(quizState);

  if (answeredCorrectly) {
    SetWindowText(quizState->resultLabel, "Correct! Click Next to continue.");
    ShowCorrectText(quizState, currentQuestion);
  } else {
    SetWindowText(quizState->resultLabel, "Incorrect. Click Next to continue.");
    ShowWrongAnswerSteps(quizState, currentQuestion);
  }

  if (quizState->currentQuestionIndex >= static_cast<int>(quizState->questionList.size())) {
    SetWindowText(quizState->progressLabel, "Quiz complete. Click Next to finish.");
  } else {
    SetWindowText(quizState->progressLabel, "Answer recorded. Click Next for the next question.");
  }
}

static LRESULT CALLBACK AnswerEditSubclassProc(HWND editHandle, UINT message, WPARAM wParam,
                                               LPARAM lParam, UINT_PTR, DWORD_PTR) {
  if (message == WM_KEYDOWN && wParam == VK_RETURN) {
    HWND parentWindow = GetParent(editHandle);
    if (parentWindow) {
      SendMessage(parentWindow, WM_COMMAND, MAKEWPARAM(SUBMIT_BUTTON_ID, BN_CLICKED), 0);
    }
    return 0;
  }

  return DefSubclassProc(editHandle, message, wParam, lParam);
}

static void DrawColoredButton(const DRAWITEMSTRUCT *drawItem, COLORREF fillColor,
                              COLORREF borderColor, COLORREF textColor, bool drawThemeIcon,
                              bool drawHomeButton, bool darkModeEnabled) {
  HBRUSH fillBrush = CreateSolidBrush(fillColor);
  FillRect(drawItem->hDC, &drawItem->rcItem, fillBrush);
  DeleteObject(fillBrush);

  HPEN borderPen = CreatePen(PS_SOLID, 1, borderColor);
  HGDIOBJ oldPen = SelectObject(drawItem->hDC, borderPen);
  HGDIOBJ oldBrush = SelectObject(drawItem->hDC, GetStockObject(NULL_BRUSH));
  Rectangle(drawItem->hDC, drawItem->rcItem.left, drawItem->rcItem.top, drawItem->rcItem.right,
            drawItem->rcItem.bottom);
  SelectObject(drawItem->hDC, oldBrush);
  SelectObject(drawItem->hDC, oldPen);
  DeleteObject(borderPen);

  if (drawThemeIcon) {
    DrawThemeToggleIcon(drawItem->hDC, drawItem->rcItem, darkModeEnabled);
    return;
  }

  if (drawHomeButton) {
    DrawHomeIcon(drawItem->hDC, drawItem->rcItem, darkModeEnabled);
    return;
  }

  SetBkMode(drawItem->hDC, TRANSPARENT);
  SetTextColor(drawItem->hDC, textColor);

  wchar_t buttonText[64] = {};
  GetWindowTextW(drawItem->hwndItem, buttonText, 64);
  DrawTextW(drawItem->hDC, buttonText, -1, const_cast<RECT *>(&drawItem->rcItem),
            DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

LRESULT CALLBACK QuizWindowMessageHandler(HWND windowHandle, UINT message, WPARAM wParam,
                                          LPARAM lParam) {
  QuizWindowState *quizState =
      reinterpret_cast<QuizWindowState *>(GetWindowLongPtr(windowHandle, GWLP_USERDATA));

  switch (message) {

  case WM_CREATE: {
    CREATESTRUCT *createInfo = reinterpret_cast<CREATESTRUCT *>(lParam);
    quizState = reinterpret_cast<QuizWindowState *>(createInfo->lpCreateParams);
    SetWindowLongPtr(windowHandle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(quizState));

    quizState->darkModeEnabled = IsDarkModeEnabled();
    quizState->backgroundBrush = NULL;
    quizState->panelBrush = NULL;
    quizState->editBrush = NULL;
    RefreshQuizBrushes(quizState);

    HFONT titleFont =
        CreateFont(22, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
                   CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));

    HFONT normalFont =
        CreateFont(19, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
                   CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));

    quizState->progressLabel = CreateWindow("STATIC", "", WS_VISIBLE | WS_CHILD | SS_LEFT, 0, 0,
                                            520, 28, windowHandle, NULL, NULL, NULL);

    quizState->homeButton =
        CreateWindowW(L"BUTTON", L"", WS_VISIBLE | WS_CHILD | BS_OWNERDRAW, 0, 0, 65, 38,
                      windowHandle, (HMENU)(UINT_PTR)HOME_BUTTON_ID, GetModuleHandle(NULL), NULL);

    quizState->themeButton =
        CreateWindowW(L"BUTTON", L"", WS_VISIBLE | WS_CHILD | BS_OWNERDRAW, 0, 0, 65, 38,
                      windowHandle, (HMENU)(UINT_PTR)THEME_BUTTON_ID, GetModuleHandle(NULL), NULL);

    quizState->questionLabel = CreateWindow("STATIC", "", WS_VISIBLE | WS_CHILD | SS_LEFT, 0, 0,
                                            700, 58, windowHandle, NULL, NULL, NULL);

    quizState->answerLabel = CreateWindow("STATIC", "Your answer:", WS_VISIBLE | WS_CHILD | SS_LEFT,
                                          0, 0, 120, 24, windowHandle, NULL, NULL, NULL);

    quizState->answerInputBox =
        CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER, 0, 0, 130, 30,
                     windowHandle, NULL, NULL, NULL);

    SetWindowSubclass(quizState->answerInputBox, AnswerEditSubclassProc, 1, 0);

    quizState->submitButton =
        CreateWindow("BUTTON", "Submit", WS_VISIBLE | WS_CHILD | BS_OWNERDRAW, 0, 0, 120, 40,
                     windowHandle, (HMENU)(UINT_PTR)SUBMIT_BUTTON_ID, GetModuleHandle(NULL), NULL);

    quizState->hintButton =
        CreateWindow("BUTTON", "Hint", WS_VISIBLE | WS_CHILD | BS_OWNERDRAW, 0, 0, 120, 40,
                     windowHandle, (HMENU)(UINT_PTR)HINT_BUTTON_ID, GetModuleHandle(NULL), NULL);

    quizState->resultLabel = CreateWindow("STATIC", "", WS_VISIBLE | WS_CHILD | SS_LEFT, 0, 0, 700,
                                          24, windowHandle, NULL, NULL, NULL);

    quizState->explanationBox = CreateWindowExW(WS_EX_CLIENTEDGE, MSFTEDIT_CLASS, L"",
                                                WS_VISIBLE | WS_CHILD | WS_VSCROLL | ES_MULTILINE |
                                                    ES_READONLY | ES_AUTOVSCROLL,
                                                0, 0, 700, 210, windowHandle, NULL, NULL, NULL);

    SendMessage(quizState->explanationBox, EM_SETBKGNDCOLOR, 0,
                (LPARAM)GetEditColor(quizState->darkModeEnabled));

    SendMessage(quizState->progressLabel, WM_SETFONT, (WPARAM)titleFont, TRUE);

    HWND normalControls[] = {quizState->homeButton,     quizState->themeButton,
                             quizState->questionLabel,  quizState->answerLabel,
                             quizState->answerInputBox, quizState->submitButton,
                             quizState->hintButton,     quizState->resultLabel};

    for (HWND control : normalControls) {
      SendMessage(control, WM_SETFONT, (WPARAM)normalFont, TRUE);
    }

    SendMessage(quizState->explanationBox, WM_SETFONT, (WPARAM)normalFont, TRUE);

    LayoutQuizControls(windowHandle, quizState);
    DisplayCurrentQuestion(quizState);
    break;
  }

  case WM_SIZE:
    if (quizState) {
      LayoutQuizControls(windowHandle, quizState);
    }
    return 0;

  case WM_COMMAND: {
    if (!quizState)
      break;

    if (LOWORD(wParam) == SUBMIT_BUTTON_ID) {
      char buffer[64] = {};
      GetWindowText(quizState->answerInputBox, buffer, sizeof(buffer));

      if (!quizState->waitingForNextClick && std::strlen(buffer) == 0) {
        quizState->showError = true;
        SetWindowText(quizState->resultLabel, "Input an answer before submitting");
        InvalidateRect(windowHandle, NULL, TRUE);
        UpdateWindow(windowHandle);
        return 0;
      }

      quizState->showError = false;
      HandleSubmitButtonPressed(quizState);
      InvalidateRect(windowHandle, NULL, TRUE);
      UpdateWindow(windowHandle);
    }

    if (LOWORD(wParam) == HOME_BUTTON_ID) {
      DestroyWindow(windowHandle);
    }

    if (LOWORD(wParam) == HINT_BUTTON_ID) {
      HandleHintButtonPressed(quizState);
    }

    if (LOWORD(wParam) == THEME_BUTTON_ID) {
      ToggleDarkModeEnabled();
    }

    break;
  }

  case WM_DRAWITEM: {
    if (!quizState)
      break;

    const DRAWITEMSTRUCT *drawItem = reinterpret_cast<DRAWITEMSTRUCT *>(lParam);

    COLORREF textColor = GetTextColor(quizState->darkModeEnabled);
    COLORREF borderColor = quizState->darkModeEnabled ? RGB(140, 140, 140) : RGB(150, 150, 150);

    if (drawItem->CtlID == HOME_BUTTON_ID) {
      DrawColoredButton(drawItem, GetPanelColor(quizState->darkModeEnabled), borderColor, textColor,
                        false, true, quizState->darkModeEnabled);
      return TRUE;
    }

    if (drawItem->CtlID == SUBMIT_BUTTON_ID) {
      DrawColoredButton(drawItem, GetSubmitButtonColor(quizState->darkModeEnabled), borderColor,
                        textColor, false, false, quizState->darkModeEnabled);
      return TRUE;
    }

    if (drawItem->CtlID == HINT_BUTTON_ID) {
      DrawColoredButton(drawItem, GetHintButtonColor(quizState->darkModeEnabled), borderColor,
                        textColor, false, false, quizState->darkModeEnabled);
      return TRUE;
    }

    if (drawItem->CtlID == THEME_BUTTON_ID) {
      DrawColoredButton(drawItem, GetPanelColor(quizState->darkModeEnabled), borderColor, textColor,
                        true, false, quizState->darkModeEnabled);
      return TRUE;
    }

    break;
  }

  case WM_CTLCOLORSTATIC: {
    if (!quizState)
      break;

    HDC deviceContext = reinterpret_cast<HDC>(wParam);

    if ((HWND)lParam == quizState->resultLabel && quizState->showError) {
      SetTextColor(deviceContext, RGB(255, 80, 80));
      SetBkColor(deviceContext, GetBackgroundColor(quizState->darkModeEnabled));
      return reinterpret_cast<INT_PTR>(quizState->backgroundBrush);
    }

    SetTextColor(deviceContext, GetTextColor(quizState->darkModeEnabled));
    SetBkColor(deviceContext, GetBackgroundColor(quizState->darkModeEnabled));
    return reinterpret_cast<INT_PTR>(quizState->backgroundBrush);
  }

  case WM_CTLCOLOREDIT: {
    if (!quizState)
      break;

    HDC deviceContext = reinterpret_cast<HDC>(wParam);
    SetTextColor(deviceContext, GetTextColor(quizState->darkModeEnabled));
    SetBkColor(deviceContext, GetEditColor(quizState->darkModeEnabled));
    return reinterpret_cast<INT_PTR>(quizState->editBrush);
  }

  case WM_ERASEBKGND: {
    if (!quizState)
      break;

    RECT clientArea;
    GetClientRect(windowHandle, &clientArea);
    FillRect(reinterpret_cast<HDC>(wParam), &clientArea, quizState->backgroundBrush);
    return 1;
  }

  case WM_APP_THEME_CHANGED:
    if (quizState) {
      ApplyQuizTheme(windowHandle, quizState);
    }
    return 0;

  case WM_DESTROY:
    if (quizState) {
      if (quizState->backgroundBrush)
        DeleteObject(quizState->backgroundBrush);
      if (quizState->panelBrush)
        DeleteObject(quizState->panelBrush);
      if (quizState->editBrush)
        DeleteObject(quizState->editBrush);
      delete quizState;
    }
    return 0;
  }

  return DefWindowProc(windowHandle, message, wParam, lParam);
}

void OpenQuizWindow(HWND parentWindow, int gradeLevel, const char *topic) {
  LoadLibraryW(L"Msftedit.dll");

  std::vector<Question> questionsFromDatabase;
  try {
    QuestionBank questionBank(GetPathToDatabase());
    questionsFromDatabase = questionBank.getRandomQuestions(10, gradeLevel, topic);
  } catch (const std::exception &error) {
    MessageBox(parentWindow, error.what(), "Database Error", MB_OK | MB_ICONERROR);
    return;
  }

  if (questionsFromDatabase.empty()) {
    std::string noQuestionsMessage =
        "No " + std::string(topic) + " questions were found for Grade " +
        std::to_string(gradeLevel) +
        ".\n\nPlease make sure the database has been seeded with questions for this subject and "
        "grade.";
    MessageBox(parentWindow, noQuestionsMessage.c_str(), "No Questions Available",
               MB_OK | MB_ICONINFORMATION);
    return;
  }

  std::string windowTitle = std::string(topic);
  windowTitle[0] = (char)toupper((unsigned char)windowTitle[0]);
  windowTitle += " - Grade " + std::to_string(gradeLevel);

  QuizWindowState *quizState = new QuizWindowState();
  quizState->questionList = std::move(questionsFromDatabase);
  quizState->answeredQuestions = {};
  quizState->currentQuestionIndex = 0;
  quizState->gradeLevel = gradeLevel;
  quizState->topic = topic;
  quizState->sessionId = BuildUniqueSessionId(topic);
  quizState->waitingForNextClick = false;
  quizState->darkModeEnabled = IsDarkModeEnabled();
  quizState->showError = false;
  quizState->correctAnswerForCurrentQuestion = 0;
  quizState->progressLabel = NULL;
  quizState->questionLabel = NULL;
  quizState->answerLabel = NULL;
  quizState->answerInputBox = NULL;
  quizState->submitButton = NULL;
  quizState->homeButton = NULL;
  quizState->hintButton = NULL;
  quizState->themeButton = NULL;
  quizState->resultLabel = NULL;
  quizState->explanationBox = NULL;
  quizState->backgroundBrush = NULL;
  quizState->panelBrush = NULL;
  quizState->editBrush = NULL;

  WNDCLASS quizWindowClass = {};
  quizWindowClass.lpfnWndProc = QuizWindowMessageHandler;
  quizWindowClass.hInstance = GetModuleHandle(NULL);
  quizWindowClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
  quizWindowClass.lpszClassName = "QuizWindowClass";
  RegisterClass(&quizWindowClass);

  HWND quizWindow =
      CreateWindow("QuizWindowClass", windowTitle.c_str(), WS_OVERLAPPEDWINDOW, 120, 95, 900, 760,
                   parentWindow, NULL, GetModuleHandle(NULL), quizState);

  ShowWindow(quizWindow, SW_SHOW);
  UpdateWindow(quizWindow);
}