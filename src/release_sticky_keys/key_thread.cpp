#include "key_thread.h"
#include "interception.h"
#include "key_define.h"
#include "utils.h"
#include "timer.h"

// 全局变量，用于线程同步
HANDLE g_ThreadHandle = NULL;
HANDLE g_ThreadHandle_Alt = NULL;
HANDLE g_ThreadHandle_Shift = NULL;
HANDLE g_ThreadHandle_Ctrl = NULL;

// 该函数会持续检查物理键盘键的状态
DWORD WINAPI CheckPhyKeyState(LPVOID lpParam)
{
    InterceptionContext context; // Type: void *
    InterceptionDevice device;   // Type: int
    InterceptionStroke stroke;   // Type: char[20]

    raise_process_priority();

    context = interception_create_context();                                                 // 创建一个上下文
    interception_set_filter(context, interception_is_keyboard, INTERCEPTION_FILTER_KEY_ALL); // 设置键盘过滤器

    while (interception_receive(context, device = interception_wait(context), &stroke, 1) > 0)
    {
        if (interception_is_keyboard(device))
        {
            InterceptionKeyStroke &keystroke = *(InterceptionKeyStroke *)&stroke;

            DBGprint("key: %d\n", keystroke.code);

            if (keystroke.code == SCANCODE_LALT || keystroke.code == SCANCODE_RALT)
            {
                phy_Alt_pressed = (bool)keystroke.state;
                DBGprint("ALT: %d %d\n", keystroke.code, keystroke.state);

                // 启动定时器
                if (g_TimerId_Alt != 0)
                {
                    KillTimer(NULL, g_TimerId_Alt);
                }
                g_TimerId_Alt = SetTimer(NULL, 0, 500, TimerCallback_Alt);
            }
            if (keystroke.code == SCANCODE_LSHIFT || keystroke.code == SCANCODE_RSHIFT)
            {
                phy_Shift_pressed = (bool)keystroke.state;
                DBGprint("SHIFT: %d %d\n", keystroke.code, keystroke.state);

                if (g_TimerId_Shift != 0)
                {
                    KillTimer(NULL, g_TimerId_Shift);
                }
                g_TimerId_Shift = SetTimer(NULL, 0, 500, TimerCallback_Shift);
            }
            if (keystroke.code == SCANCODE_LCTRL || keystroke.code == SCANCODE_RCTRL)
            {
                phy_Ctrl_pressed = (bool)keystroke.state;
                DBGprint("CTRL: %d %d\n", keystroke.code, keystroke.state);

                if (g_TimerId_Ctrl != 0)
                {
                    KillTimer(NULL, g_TimerId_Ctrl);
                }
                g_TimerId_Ctrl = SetTimer(NULL, 0, 500, TimerCallback_Ctrl);
            }
        }

        interception_send(context, device, &stroke, 1);
    }

    interception_destroy_context(context);
    return 0;
}

DWORD WINAPI releaseCtrlKeyState(LPVOID lpParam)
{
    (void)lpParam;

    volatile short count_ctrl = 0;
    while (1)
    {
        if (phy_Ctrl_pressed == PHY_KEY_DOWN)
        {
            // printf("phy_ctrl is down\n");
            Sleep(50);
            continue;
        }
        // 这里使用 count_ctrl 做次数控制, 是因为如果使用纯软件做按键模拟,
        // 那么物理按键一定是 PHY_KEY_UP 状态 程序就要执行到这里 如果立即释放,
        // 那么软件模拟的按键可能会失效, 比如软件模拟 ctrl+w 因为立即释放了 ctrl
        // 所以实际输出就只是 w
        while (KEY_DOWN(VK_LCONTROL) || KEY_DOWN(VK_RCONTROL))
        {
            count_ctrl++;
            Sleep(2);
            if (count_ctrl == 10)
            {
                break;
            }
        }
        if (count_ctrl == 10)
        {
            DBGprint("ctrl will releaseL\n");
            keybd_event(VK_LCONTROL, 0, KEYEVENTF_KEYUP, 0);
            keybd_event(VK_RCONTROL, 0, KEYEVENTF_KEYUP, 0);
        }
        count_ctrl = 0;
        Sleep(50);
    }
}

DWORD WINAPI releaseShiftKeyState(LPVOID lpParam)
{
    (void)lpParam;

    volatile short count_shift = 0;
    while (1)
    {
        if (phy_Shift_pressed == PHY_KEY_DOWN)
        {
            // printf("phy_lshift is down\n");
            Sleep(50);
            continue;
        }

        // 这里使用 count_shift 做次数控制, 是因为如果使用纯软件做按键模拟,
        // 那么物理按键一定是 PHY_KEY_UP 状态 程序就要执行到这里 如果立即释放,
        // 那么软件模拟的按键可能会失效, 比如软件模拟 shift+f4 因为立即释放了 shift
        // 所以实际输出就只是 f4
        while (KEY_DOWN(VK_LSHIFT) || KEY_DOWN(VK_RSHIFT))
        {
            count_shift++;
            Sleep(2);
            if (count_shift == 10)
            {
                break;
            }
        }
        if (count_shift == 10)
        {
            keybd_event(VK_LSHIFT, 0, KEYEVENTF_KEYUP, 0);
            keybd_event(VK_RSHIFT, 0, KEYEVENTF_KEYUP, 0);
        }
        count_shift = 0;
        Sleep(50);
    }
}

DWORD WINAPI releaseAltKeyState(LPVOID lpParam)
{
    (void)lpParam;

    volatile short count_alt = 0;
    while (1)
    {
        if (phy_Alt_pressed == PHY_KEY_DOWN)
        {
            // printf("phy_alt is down\n");
            Sleep(50);
            continue;
        }

        // 这里使用 count_alt 做次数控制, 是因为如果使用纯软件做按键模拟,
        // 那么物理按键一定是 PHY_KEY_UP 状态 程序就要执行到这里 如果立即释放,
        // 那么软件模拟的按键可能会失效, 比如软件模拟 alt+f4 因为立即释放了 alt
        // 所以实际输出就只是 f4
        while (KEY_DOWN(VK_LMENU) || KEY_DOWN(VK_RMENU))
        {
            count_alt++;
            Sleep(2);
            if (count_alt == 10)
            {
                break;
            }
        }
        if (count_alt == 10)
        {
            DBGprint("alt will releaseL\n");
            keybd_event(VK_LMENU, 0, KEYEVENTF_KEYUP, 0);
            keybd_event(VK_RMENU, 0, KEYEVENTF_KEYUP, 0);
        }
        count_alt = 0;
        Sleep(50);
    }
}
