#pragma once

#include <winsock2.h>
#include <ws2tcpip.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

void OpenQuizWindow(HWND parentWindow, int gradeLevel, const char *topic);