#pragma once

#include <windows.h>

// 全局变量，用于线程同步
extern HANDLE g_ThreadHandle;
extern HANDLE g_ThreadHandle_Alt;
extern HANDLE g_ThreadHandle_Shift;
extern HANDLE g_ThreadHandle_Ctrl;

DWORD WINAPI CheckPhyKeyState(LPVOID lpParam);
DWORD WINAPI releaseCtrlKeyState(LPVOID lpParam);
DWORD WINAPI releaseShiftKeyState(LPVOID lpParam);
DWORD WINAPI releaseAltKeyState(LPVOID lpParam);
