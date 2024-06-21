#include "key_thread.h"
#include <windows.h>

int main()
{
    // 隐藏命令窗口
    HWND hWnd = GetConsoleWindow();
    ShowWindow(hWnd, SW_HIDE);
    
    // 创建线程
    g_ThreadHandle = CreateThread(NULL, 0, CheckPhyKeyState, NULL, 0, NULL);
    g_ThreadHandle_Alt = CreateThread(NULL, 0, releaseAltKeyState, NULL, 0, NULL);
    g_ThreadHandle_Ctrl = CreateThread(NULL, 0, releaseCtrlKeyState, NULL, 0, NULL);
    g_ThreadHandle_Shift = CreateThread(NULL, 0, releaseShiftKeyState, NULL, 0, NULL);

    // 等待线程退出
    WaitForSingleObject(g_ThreadHandle, INFINITE);
    WaitForSingleObject(g_ThreadHandle_Alt, INFINITE);
    WaitForSingleObject(g_ThreadHandle_Ctrl, INFINITE);
    WaitForSingleObject(g_ThreadHandle_Shift, INFINITE);

    // 关闭线程句柄
    CloseHandle(g_ThreadHandle);
    CloseHandle(g_ThreadHandle_Alt);
    CloseHandle(g_ThreadHandle_Ctrl);
    CloseHandle(g_ThreadHandle_Shift);
}
