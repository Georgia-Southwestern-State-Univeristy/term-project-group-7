#include "gui/main_menu_gui.h"
#include "gui/addition_gui.h"

#define WIN32_LEAN_AND_MEAN
#include <cmath>
#include <windows.h>

#define ADDITION_BUTTON_ID 101
#define SUBTRACTION_BUTTON_ID 102
#define GRADE_DROPDOWN_ID 103
#define ANALYTICS_BUTTON_ID 104
#define MULTIPLICATION_BUTTON_ID 105
#define DIVISION_BUTTON_ID 106
#define THEME_BUTTON_ID 107

void ShowAnalyticsWindow(HWND parentWindow);

static bool g_darkModeEnabled = false;

bool IsDarkModeEnabled() { return g_darkModeEnabled; }

void SetDarkModeEnabled(bool enabled) { g_darkModeEnabled = enabled; }

static BOOL CALLBACK BroadcastThemeChangedCallback(HWND windowHandle, LPARAM) {
  PostMessage(windowHandle, WM_APP_THEME_CHANGED, 0, 0);
  return TRUE;
}

void BroadcastThemeChanged() {
  EnumThreadWindows(GetCurrentThreadId(), BroadcastThemeChangedCallback, 0);
}

void ToggleDarkModeEnabled() {
  g_darkModeEnabled = !g_darkModeEnabled;
  BroadcastThemeChanged();
}

static COLORREF GetBackgroundColor(bool darkModeEnabled) {
  return darkModeEnabled ? RGB(30, 30, 30) : RGB(245, 245, 245);
}

static COLORREF GetPanelColor(bool darkModeEnabled) {
  return darkModeEnabled ? RGB(55, 55, 58) : RGB(235, 235, 235);
}

static COLORREF GetTextColor(bool darkModeEnabled) {
  return darkModeEnabled ? RGB(235, 235, 235) : RGB(20, 20, 20);
}

struct MainMenuWindowState {
  bool darkModeEnabled;
  HBRUSH backgroundBrush;
  HBRUSH panelBrush;
  HFONT titleFont;
  HFONT normalFont;

  HWND titleLabel;
  HWND gradeLabel;
  HWND gradeDropdown;
  HWND additionButton;
  HWND subtractionButton;
  HWND multiplicationButton;
  HWND divisionButton;
  HWND analyticsButton;
  HWND themeButton;
};

static void RefreshMainMenuBrushes(MainMenuWindowState *windowState) {
  if (!windowState)
    return;

  if (windowState->backgroundBrush)
    DeleteObject(windowState->backgroundBrush);
  if (windowState->panelBrush)
    DeleteObject(windowState->panelBrush);

  windowState->backgroundBrush = CreateSolidBrush(GetBackgroundColor(windowState->darkModeEnabled));
  windowState->panelBrush = CreateSolidBrush(GetPanelColor(windowState->darkModeEnabled));
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

static void LayoutMainMenuControls(HWND windowHandle, MainMenuWindowState *windowState) {
  if (!windowState)
    return;

  RECT clientRect;
  GetClientRect(windowHandle, &clientRect);

  int clientWidth = clientRect.right - clientRect.left;
  int clientHeight = clientRect.bottom - clientRect.top;

  const int groupWidth = 560;
  const int topY = 35;

  int leftX = (clientWidth - groupWidth) / 2;
  if (leftX < 20)
    leftX = 20;

  int centerX = clientWidth / 2;

  MoveWindow(windowState->titleLabel, centerX - 175, topY, 350, 35, TRUE);
  MoveWindow(windowState->gradeLabel, centerX - 140, topY + 45, 280, 24, TRUE);
  MoveWindow(windowState->gradeDropdown, centerX - 100, topY + 78, 200, 150, TRUE);

  MoveWindow(windowState->additionButton, leftX, topY + 145, 170, 50, TRUE);
  MoveWindow(windowState->subtractionButton, leftX + 390, topY + 145, 170, 50, TRUE);

  MoveWindow(windowState->multiplicationButton, leftX, topY + 235, 170, 50, TRUE);
  MoveWindow(windowState->divisionButton, leftX + 390, topY + 235, 170, 50, TRUE);

  MoveWindow(windowState->analyticsButton, centerX - 110, topY + 345, 220, 45, TRUE);

  MoveWindow(windowState->themeButton, clientWidth - 80, 20, 52, 40, TRUE);
}

static void ApplyMainMenuTheme(HWND windowHandle, MainMenuWindowState *windowState) {
  if (!windowState)
    return;

  windowState->darkModeEnabled = IsDarkModeEnabled();
  RefreshMainMenuBrushes(windowState);

  InvalidateRect(windowHandle, NULL, TRUE);
  UpdateWindow(windowHandle);
}

static void DrawMenuButton(const DRAWITEMSTRUCT *drawItem, bool darkModeEnabled) {
  bool isThemeButton = (drawItem->CtlID == THEME_BUTTON_ID);

  COLORREF fillColor = darkModeEnabled ? RGB(60, 60, 65) : RGB(230, 230, 230);
  COLORREF borderColor = darkModeEnabled ? RGB(120, 120, 120) : RGB(150, 150, 150);

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

  if (isThemeButton) {
    DrawThemeToggleIcon(drawItem->hDC, drawItem->rcItem, darkModeEnabled);
    return;
  }

  SetBkMode(drawItem->hDC, TRANSPARENT);
  SetTextColor(drawItem->hDC, GetTextColor(darkModeEnabled));

  wchar_t buttonText[64] = {};
  GetWindowTextW(drawItem->hwndItem, buttonText, 64);
  DrawTextW(drawItem->hDC, buttonText, -1, const_cast<RECT *>(&drawItem->rcItem),
            DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

LRESULT CALLBACK MainMenuMessageHandler(HWND windowHandle, UINT message, WPARAM wParam,
                                        LPARAM lParam) {
  MainMenuWindowState *windowState =
      reinterpret_cast<MainMenuWindowState *>(GetWindowLongPtr(windowHandle, GWLP_USERDATA));

  switch (message) {

  case WM_CREATE: {
    windowState = new MainMenuWindowState();
    windowState->darkModeEnabled = IsDarkModeEnabled();
    windowState->backgroundBrush = NULL;
    windowState->panelBrush = NULL;
    windowState->titleFont =
        CreateFont(24, 0, 0, 0, FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
                   CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));
    windowState->normalFont =
        CreateFont(19, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
                   CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, VARIABLE_PITCH, TEXT("Arial"));

    SetWindowLongPtr(windowHandle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(windowState));
    RefreshMainMenuBrushes(windowState);

    windowState->titleLabel =
        CreateWindow("STATIC", "Math Trainer", WS_VISIBLE | WS_CHILD | SS_CENTER, 0, 0, 350, 35,
                     windowHandle, NULL, NULL, NULL);

    windowState->gradeLabel =
        CreateWindow("STATIC", "Select Grade Level:", WS_VISIBLE | WS_CHILD | SS_CENTER, 0, 0, 280,
                     24, windowHandle, NULL, NULL, NULL);

    windowState->gradeDropdown =
        CreateWindow("COMBOBOX", NULL, WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST | WS_VSCROLL, 0, 0,
                     200, 150, windowHandle, (HMENU)(UINT_PTR)GRADE_DROPDOWN_ID, NULL, NULL);

    const char *gradeChoices[] = {"Grade 6", "Grade 7", "Grade 8"};
    for (int i = 0; i < 3; i++) {
      SendMessage(windowState->gradeDropdown, CB_ADDSTRING, 0, (LPARAM)gradeChoices[i]);
    }
    SendMessage(windowState->gradeDropdown, CB_SETCURSEL, 0, 0);

    windowState->additionButton =
        CreateWindow("BUTTON", "Addition", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_OWNERDRAW, 0, 0,
                     170, 50, windowHandle, (HMENU)(UINT_PTR)ADDITION_BUTTON_ID, NULL, NULL);

    windowState->subtractionButton =
        CreateWindow("BUTTON", "Subtraction", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_OWNERDRAW, 0,
                     0, 170, 50, windowHandle, (HMENU)(UINT_PTR)SUBTRACTION_BUTTON_ID, NULL, NULL);

    windowState->multiplicationButton = CreateWindow(
        "BUTTON", "Multiplication", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_OWNERDRAW, 0, 0, 170,
        50, windowHandle, (HMENU)(UINT_PTR)MULTIPLICATION_BUTTON_ID, NULL, NULL);

    windowState->divisionButton =
        CreateWindow("BUTTON", "Division", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_OWNERDRAW, 0, 0,
                     170, 50, windowHandle, (HMENU)(UINT_PTR)DIVISION_BUTTON_ID, NULL, NULL);

    windowState->analyticsButton =
        CreateWindow("BUTTON", "View Analytics", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_OWNERDRAW,
                     0, 0, 220, 45, windowHandle, (HMENU)(UINT_PTR)ANALYTICS_BUTTON_ID, NULL, NULL);

    windowState->themeButton =
        CreateWindowW(L"BUTTON", L"", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_OWNERDRAW, 0, 0, 52,
                      40, windowHandle, (HMENU)(UINT_PTR)THEME_BUTTON_ID, NULL, NULL);

    SendMessage(windowState->titleLabel, WM_SETFONT, (WPARAM)windowState->titleFont, TRUE);
    SendMessage(windowState->gradeLabel, WM_SETFONT, (WPARAM)windowState->normalFont, TRUE);
    SendMessage(windowState->gradeDropdown, WM_SETFONT, (WPARAM)windowState->normalFont, TRUE);

    LayoutMainMenuControls(windowHandle, windowState);
    break;
  }

  case WM_SIZE:
    if (windowState) {
      LayoutMainMenuControls(windowHandle, windowState);
    }
    return 0;

  case WM_COMMAND: {
    int buttonPressed = LOWORD(wParam);

    if (buttonPressed == THEME_BUTTON_ID) {
      ToggleDarkModeEnabled();
      break;
    }

    if (buttonPressed == ADDITION_BUTTON_ID || buttonPressed == SUBTRACTION_BUTTON_ID ||
        buttonPressed == MULTIPLICATION_BUTTON_ID || buttonPressed == DIVISION_BUTTON_ID) {
      int selectedIndex = (int)SendMessage(windowState->gradeDropdown, CB_GETCURSEL, 0, 0);
      int selectedGrade = (selectedIndex == CB_ERR) ? 6 : selectedIndex + 6;

      const char *topicName = "addition";
      if (buttonPressed == ADDITION_BUTTON_ID) {
        topicName = "addition";
      } else if (buttonPressed == SUBTRACTION_BUTTON_ID) {
        topicName = "subtraction";
      } else if (buttonPressed == MULTIPLICATION_BUTTON_ID) {
        topicName = "multiplication";
      } else if (buttonPressed == DIVISION_BUTTON_ID) {
        topicName = "division";
      }

      OpenQuizWindow(windowHandle, selectedGrade, topicName);
    }

    if (buttonPressed == ANALYTICS_BUTTON_ID) {
      ShowAnalyticsWindow(windowHandle);
    }
    break;
  }

  case WM_DRAWITEM: {
    if (!windowState)
      break;

    const DRAWITEMSTRUCT *drawItem = reinterpret_cast<DRAWITEMSTRUCT *>(lParam);
    DrawMenuButton(drawItem, windowState->darkModeEnabled);
    return TRUE;
  }

  case WM_CTLCOLORSTATIC: {
    if (!windowState)
      break;

    HDC deviceContext = reinterpret_cast<HDC>(wParam);
    SetTextColor(deviceContext, GetTextColor(windowState->darkModeEnabled));
    SetBkColor(deviceContext, GetBackgroundColor(windowState->darkModeEnabled));
    return reinterpret_cast<INT_PTR>(windowState->backgroundBrush);
  }

  case WM_CTLCOLOREDIT: {
    HDC deviceContext = reinterpret_cast<HDC>(wParam);
    SetTextColor(deviceContext, RGB(0, 0, 0));
    SetBkColor(deviceContext, RGB(255, 255, 255));
    return reinterpret_cast<INT_PTR>(GetStockObject(WHITE_BRUSH));
  }

  case WM_CTLCOLORLISTBOX: {
    HDC deviceContext = reinterpret_cast<HDC>(wParam);
    SetTextColor(deviceContext, RGB(0, 0, 0));
    SetBkColor(deviceContext, RGB(255, 255, 255));
    return reinterpret_cast<INT_PTR>(GetStockObject(WHITE_BRUSH));
  }

  case WM_ERASEBKGND: {
    if (!windowState)
      break;

    RECT clientArea;
    GetClientRect(windowHandle, &clientArea);
    FillRect(reinterpret_cast<HDC>(wParam), &clientArea, windowState->backgroundBrush);
    return 1;
  }

  case WM_APP_THEME_CHANGED:
    if (windowState) {
      ApplyMainMenuTheme(windowHandle, windowState);
    }
    return 0;

  case WM_DESTROY:
    if (windowState) {
      if (windowState->backgroundBrush)
        DeleteObject(windowState->backgroundBrush);
      if (windowState->panelBrush)
        DeleteObject(windowState->panelBrush);
      if (windowState->titleFont)
        DeleteObject(windowState->titleFont);
      if (windowState->normalFont)
        DeleteObject(windowState->normalFont);
      delete windowState;
    }
    PostQuitMessage(0);
    return 0;
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
      CreateWindowEx(0, "MainMenuWindowClass", "Math Trainer", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
                     CW_USEDEFAULT, 1000, 600, NULL, NULL, applicationInstance, NULL);

  ShowWindow(mainMenuWindow, SW_SHOW);
  UpdateWindow(mainMenuWindow);

  MSG windowMessage = {};
  while (GetMessage(&windowMessage, NULL, 0, 0)) {
    TranslateMessage(&windowMessage);
    DispatchMessage(&windowMessage);
  }
}