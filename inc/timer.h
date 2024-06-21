#ifndef _TIMER_H_
#define _TIMER_H_

#include <windows.h>

extern UINT_PTR g_TimerId_Alt;
extern UINT_PTR g_TimerId_Shift;
extern UINT_PTR g_TimerId_Ctrl;
extern UINT_PTR g_TimerId_LWin;

VOID CALLBACK TimerCallback_Ctrl(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);
VOID CALLBACK TimerCallback_Shift(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);
VOID CALLBACK TimerCallback_Alt(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);
#endif
