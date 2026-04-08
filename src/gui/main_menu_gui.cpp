#include "gui/main_menu_gui.h"
#include "gui/addition_gui.h"

#include <winsock2.h>
#include <ws2tcpip.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#define ADDITION_BUTTON_ID      101
#define SUBTRACTION_BUTTON_ID   102
#define GRADE_DROPDOWN_ID       103
#define ANALYTICS_BUTTON_ID     104

void ShowAnalyticsWindow(HWND parentWindow);

LRESULT CALLBACK MainMenuMessageHandler(HWND windowHandle, UINT message, WPARAM wParam,
                                        LPARAM lParam) {
  switch (message) {

  case WM_CREATE: {
    CreateWindow("STATIC", "Select Grade Level:", WS_VISIBLE | WS_CHILD, 300, 80, 200, 20,
                 windowHandle, NULL, NULL, NULL);

    HWND gradeDropdown =
        CreateWindow("COMBOBOX", NULL, WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST | WS_VSCROLL, 300,
                     130, 200, 150, windowHandle, (HMENU)(UINT_PTR)GRADE_DROPDOWN_ID, NULL, NULL);

    const char *gradeChoices[] = {"Grade 6", "Grade 7", "Grade 8"};
    for (int i = 0; i < 3; i++)
      SendMessage(gradeDropdown, CB_ADDSTRING, 0, (LPARAM)gradeChoices[i]);
    SendMessage(gradeDropdown, CB_SETCURSEL, 0, 0);

    CreateWindow("BUTTON", "Addition", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 200, 260,
                 130, 45, windowHandle, (HMENU)(UINT_PTR)ADDITION_BUTTON_ID, NULL, NULL);

    CreateWindow("BUTTON", "Subtraction", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 540,
                 260, 130, 45, windowHandle, (HMENU)(UINT_PTR)SUBTRACTION_BUTTON_ID, NULL, NULL);

    CreateWindow("BUTTON", "View Analytics", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON,
                 300, 390, 200, 40, windowHandle, (HMENU)(UINT_PTR)ANALYTICS_BUTTON_ID, NULL, NULL);
    break;
  }

  case WM_COMMAND: {
    int buttonPressed = LOWORD(wParam);

    if (buttonPressed == ADDITION_BUTTON_ID || buttonPressed == SUBTRACTION_BUTTON_ID) {
      HWND gradeDropdown = GetDlgItem(windowHandle, GRADE_DROPDOWN_ID);
      int selectedIndex = (int)SendMessage(gradeDropdown, CB_GETCURSEL, 0, 0);
      int selectedGrade = (selectedIndex == CB_ERR) ? 6 : selectedIndex + 6;
      const char *topicName = (buttonPressed == ADDITION_BUTTON_ID) ? "addition" : "subtraction";
      OpenQuizWindow(windowHandle, selectedGrade, topicName);
    }

    if (buttonPressed == ANALYTICS_BUTTON_ID) {
      ShowAnalyticsWindow(windowHandle);
    }
    break;
  }

  case WM_DESTROY:
    PostQuitMessage(0);
    break;
  }

  return DefWindowProc(windowHandle, message, wParam, lParam);
}

void OpenMainMenuWindow() {
  HINSTANCE applicationInstance = GetModuleHandle(NULL);

  WNDCLASS mainMenuWindowClass = {};
  mainMenuWindowClass.lpfnWndProc = MainMenuMessageHandler;
  mainMenuWindowClass.hInstance = applicationInstance;
  mainMenuWindowClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
  mainMenuWindowClass.lpszClassName = "MainMenuWindowClass";
  RegisterClass(&mainMenuWindowClass);

  HWND mainMenuWindow =
      CreateWindowEx(0, "MainMenuWindowClass", "Math Trainer",
                     WS_OVERLAPPEDWINDOW & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX, CW_USEDEFAULT,
                     CW_USEDEFAULT, 1000, 600, NULL, NULL, applicationInstance, NULL);

  ShowWindow(mainMenuWindow, SW_SHOW);
  UpdateWindow(mainMenuWindow);

  MSG windowMessage = {};
  while (GetMessage(&windowMessage, NULL, 0, 0)) {
    TranslateMessage(&windowMessage);
    DispatchMessage(&windowMessage);
  }
}