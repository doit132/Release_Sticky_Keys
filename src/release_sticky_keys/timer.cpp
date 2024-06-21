#include "timer.h"
#include "key_define.h"

// 全局变量，定时器ID
UINT_PTR g_TimerId_Alt = 0;
UINT_PTR g_TimerId_Shift = 0;
UINT_PTR g_TimerId_Ctrl = 0;
UINT_PTR g_TimerId_LWin = 0;

// ### 定时器回调函数 begin
VOID CALLBACK TimerCallback_Ctrl(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
	(void)dwTime;
	(void)idEvent;
	(void)hwnd;
	(void)uMsg;
	// 停止定时器
	KillTimer(NULL, g_TimerId_Ctrl);
	g_TimerId_Ctrl = 0;
	phy_Ctrl_pressed = PHY_KEY_DOWN;
}

VOID CALLBACK TimerCallback_Shift(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
	(void)dwTime;
	(void)idEvent;
	(void)hwnd;
	(void)uMsg;
	// 停止定时器
	KillTimer(NULL, g_TimerId_Shift);
	g_TimerId_Shift = 0;
	phy_Shift_pressed = PHY_KEY_DOWN;
}

VOID CALLBACK TimerCallback_Alt(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
	(void)dwTime;
	(void)idEvent;
	(void)hwnd;
	(void)uMsg;
	// 停止定时器
	KillTimer(NULL, g_TimerId_Alt);
	g_TimerId_Alt = 0;
	phy_Alt_pressed = PHY_KEY_DOWN;
}

VOID CALLBACK TimerCallback_LWin(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
	(void)dwTime;
	(void)idEvent;
	(void)hwnd;
	(void)uMsg;
	// 停止定时器
	KillTimer(NULL, g_TimerId_LWin);
	g_TimerId_LWin = 0;
	phy_Alt_pressed = PHY_KEY_DOWN;
}
// ### 定时器回调函数 end
