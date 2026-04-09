#pragma once

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

constexpr UINT WM_APP_THEME_CHANGED = WM_APP + 101;

void OpenMainMenuWindow();

bool IsDarkModeEnabled();
void SetDarkModeEnabled(bool enabled);
void ToggleDarkModeEnabled();
void BroadcastThemeChanged();