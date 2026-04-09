#include "gui/addition_gui.h"
#include "gui/question_bank.h"

#include <ctime>
#include <string>
#include <vector>
#include <windows.h>

#define SUBMIT_BUTTON_ID 201
#define BACK_BUTTON_ID 202

struct QuizWindowState {
  std::vector<Question> questionList;
  std::vector<AnsweredQuestion> answeredQuestions;
  int currentQuestionIndex;
  int correctAnswerForCurrentQuestion;
  int gradeLevel;
  std::string topic;
  bool waitingForUserToAcknowledgeWrongAnswer;

  HWND progressLabel;
  HWND questionLabel;
  HWND answerInputBox;
  HWND submitButton;
  HWND resultLabel;
  HWND explanationBox;
};

static std::string GetPathToDatabase() {
  char pathToExecutable[MAX_PATH] = {};
  GetModuleFileNameA(NULL, pathToExecutable, MAX_PATH);
  std::string fullPath(pathToExecutable);
  auto lastSlash = fullPath.find_last_of("\\/");
  return (lastSlash != std::string::npos ? fullPath.substr(0, lastSlash + 1) : "") + "questions.db";
}

static std::string BuildUniqueSessionId(const std::string &topic) {
  return std::to_string((long long)time(nullptr)) + "_" + topic;
}

static void DisplayCurrentQuestion(QuizWindowState *quizState) {
  if (!quizState || quizState->questionList.empty())
    return;
  if (quizState->currentQuestionIndex >= (int)quizState->questionList.size())
    return;

  const Question &currentQuestion = quizState->questionList[quizState->currentQuestionIndex];
  quizState->correctAnswerForCurrentQuestion = currentQuestion.correctAnswer;
  quizState->waitingForUserToAcknowledgeWrongAnswer = false;

  std::string progressText = "Question " + std::to_string(quizState->currentQuestionIndex + 1) +
                             " of " + std::to_string((int)quizState->questionList.size());

  SetWindowText(quizState->progressLabel, progressText.c_str());
  SetWindowText(quizState->questionLabel, currentQuestion.questionText.c_str());
  SetWindowText(quizState->answerInputBox, "");
  SetWindowText(quizState->resultLabel, "");
  SetWindowText(quizState->explanationBox, "");

  SetFocus(quizState->answerInputBox);
}

static void SaveAndShowFinalScore(QuizWindowState *quizState) {
  int totalAnswered = (int)quizState->answeredQuestions.size();
  int totalCorrect = 0;

  for (const auto &answeredQuestion : quizState->answeredQuestions)
    if (answeredQuestion.wasCorrect)
      totalCorrect++;

  try {
    QuestionBank questionBank(GetPathToDatabase());
    questionBank.saveSessionResults(BuildUniqueSessionId(quizState->topic), quizState->gradeLevel,
                                    quizState->topic, quizState->answeredQuestions);
  } catch (...) {
  }

  int scorePercent = totalAnswered > 0 ? (totalCorrect * 100 / totalAnswered) : 0;
  std::string finalScoreText = "All done!  You scored " + std::to_string(totalCorrect) +
                               " out of " + std::to_string(totalAnswered) + " (" +
                               std::to_string(scorePercent) + "%)";

  SetWindowText(quizState->questionLabel, finalScoreText.c_str());
  SetWindowText(quizState->progressLabel, "");
  SetWindowText(quizState->answerInputBox, "");
  SetWindowText(quizState->resultLabel, "");
  SetWindowText(quizState->explanationBox, "Press Back to return to the menu.");
  EnableWindow(quizState->submitButton, FALSE);
}

static void HandleSubmitButtonPressed(QuizWindowState *quizState) {
  if (!quizState || quizState->questionList.empty())
    return;

  if (quizState->waitingForUserToAcknowledgeWrongAnswer) {
    quizState->waitingForUserToAcknowledgeWrongAnswer = false;
    if (quizState->currentQuestionIndex >= (int)quizState->questionList.size()) {
      SaveAndShowFinalScore(quizState);
    } else {
      DisplayCurrentQuestion(quizState);
    }
    return;
  }

  char userTypedAnswer[64] = {};
  GetWindowText(quizState->answerInputBox, userTypedAnswer, 64);

  if (userTypedAnswer[0] == '\0') {
    SetWindowText(quizState->resultLabel, "Please type an answer first.");
    return;
  }

  int userAnswer = atoi(userTypedAnswer);
  bool answeredCorrectly = (userAnswer == quizState->correctAnswerForCurrentQuestion);

  const Question &currentQuestion = quizState->questionList[quizState->currentQuestionIndex];

  AnsweredQuestion answeredQuestion;
  answeredQuestion.questionId = currentQuestion.questionId;
  answeredQuestion.topic = currentQuestion.topic;
  answeredQuestion.gradeLevel = currentQuestion.gradeLevel;
  answeredQuestion.wasCorrect = answeredCorrectly;
  quizState->answeredQuestions.push_back(answeredQuestion);

  std::string feedbackExplanation =
      currentQuestion.explanation.empty()
          ? "The correct answer is " + std::to_string(quizState->correctAnswerForCurrentQuestion) +
                "."
          : currentQuestion.explanation;

  quizState->currentQuestionIndex++;

  if (answeredCorrectly) {
    SetWindowText(quizState->resultLabel, "Correct!");
    SetWindowText(quizState->explanationBox, "");

    if (quizState->currentQuestionIndex >= (int)quizState->questionList.size()) {
      SaveAndShowFinalScore(quizState);
    } else {
      DisplayCurrentQuestion(quizState);
    }
  } else {
    SetWindowText(quizState->resultLabel, "Incorrect.");
    SetWindowText(quizState->explanationBox, feedbackExplanation.c_str());
    SetWindowText(quizState->progressLabel, "Press Submit to continue.");
    quizState->waitingForUserToAcknowledgeWrongAnswer = true;
  }
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

    HFONT normalFont =
        CreateFont(22, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
                   CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));

    quizState->progressLabel = CreateWindow("STATIC", "", WS_VISIBLE | WS_CHILD, 20, 14, 580, 26,
                                            windowHandle, NULL, NULL, NULL);

    quizState->questionLabel = CreateWindow("STATIC", "", WS_VISIBLE | WS_CHILD | SS_LEFT, 20, 55,
                                            580, 80, windowHandle, NULL, NULL, NULL);

    CreateWindow("STATIC", "Your answer:", WS_VISIBLE | WS_CHILD, 20, 152, 130, 26, windowHandle,
                 NULL, NULL, NULL);

    quizState->answerInputBox =
        CreateWindow("EDIT", "", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_NUMBER, 160, 150, 140, 30,
                     windowHandle, NULL, NULL, NULL);

    quizState->submitButton =
        CreateWindow("BUTTON", "Submit", WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 20, 200, 120, 38,
                     windowHandle, (HMENU)(UINT_PTR)SUBMIT_BUTTON_ID, GetModuleHandle(NULL), NULL);

    CreateWindow("BUTTON", "Back", WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 160, 200, 120, 38,
                 windowHandle, (HMENU)(UINT_PTR)BACK_BUTTON_ID, GetModuleHandle(NULL), NULL);

    quizState->resultLabel = CreateWindow("STATIC", "", WS_VISIBLE | WS_CHILD, 20, 254, 580, 26,
                                          windowHandle, NULL, NULL, NULL);

    quizState->explanationBox = CreateWindow("EDIT", "",
                                             WS_VISIBLE | WS_CHILD | WS_BORDER | WS_VSCROLL |
                                                 ES_MULTILINE | ES_READONLY | ES_AUTOVSCROLL,
                                             20, 290, 580, 170, windowHandle, NULL, NULL, NULL);

    HWND allControls[] = {quizState->progressLabel, quizState->questionLabel,
                          quizState->answerInputBox, quizState->resultLabel,
                          quizState->explanationBox};
    for (HWND control : allControls)
      SendMessage(control, WM_SETFONT, (WPARAM)normalFont, TRUE);

    DisplayCurrentQuestion(quizState);
    break;
  }

  case WM_COMMAND: {
    if (LOWORD(wParam) == SUBMIT_BUTTON_ID)
      HandleSubmitButtonPressed(quizState);
    if (LOWORD(wParam) == BACK_BUTTON_ID)
      DestroyWindow(windowHandle);
    break;
  }

  case WM_DESTROY:
    delete quizState;
    return 0;
  }

  return DefWindowProc(windowHandle, message, wParam, lParam);
}

void OpenQuizWindow(HWND parentWindow, int gradeLevel, const char *topic) {
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
        ".\n\n"
        "Please make sure the database has been seeded with questions for this subject and grade.";
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
  quizState->waitingForUserToAcknowledgeWrongAnswer = false;

  static bool quizWindowClassRegistered = false;
  if (!quizWindowClassRegistered) {
    WNDCLASS quizWindowClass = {};
    quizWindowClass.lpfnWndProc = QuizWindowMessageHandler;
    quizWindowClass.hInstance = GetModuleHandle(NULL);
    quizWindowClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    quizWindowClass.lpszClassName = "QuizWindowClass";
    RegisterClass(&quizWindowClass);
    quizWindowClassRegistered = true;
  }

  HWND quizWindowHandle = CreateWindowEx(
      0, "QuizWindowClass", windowTitle.c_str(),
      WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT, 640,
      520, parentWindow, NULL, GetModuleHandle(NULL), reinterpret_cast<LPVOID>(quizState));

  if (!quizWindowHandle) {
    delete quizState;
    return;
  }

  ShowWindow(quizWindowHandle, SW_SHOW);
  UpdateWindow(quizWindowHandle);
}