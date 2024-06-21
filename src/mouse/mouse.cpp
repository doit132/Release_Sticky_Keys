#include <stdio.h>
#include <interception.h>

#define CAPSLOCK_KEY 58 // Caps Lock 的键码
#define CTRL_KEY 29     // Ctrl 的键码
#define ESC_KEY 1       // Esc 的键码

int main()
{
    InterceptionContext context;
    InterceptionDevice device;
    InterceptionStroke stroke;

    int capsLockPressed = 0; // 标志变量，用于记录 Caps Lock 是否被按下
    int otherKeyPressed = 0; // 标志变量，用于记录是否有其他按键被按下

    context = interception_create_context();

    interception_set_filter(
        context, interception_is_keyboard, INTERCEPTION_FILTER_KEY_DOWN | INTERCEPTION_FILTER_KEY_UP);
    interception_set_filter(context, interception_is_mouse, INTERCEPTION_FILTER_MOUSE_ALL);

    while (interception_receive(context, device = interception_wait(context), &stroke, 1) > 0)
    {
        if (interception_is_keyboard(device))
        {
            InterceptionKeyStroke &keystroke = *(InterceptionKeyStroke *)&stroke;

            if (keystroke.code == CAPSLOCK_KEY && keystroke.state == INTERCEPTION_KEY_DOWN)
            {
                capsLockPressed = 1;
                otherKeyPressed = 0; // 重置其他按键标志
            }
            else if (keystroke.code == CAPSLOCK_KEY && keystroke.state == INTERCEPTION_KEY_UP)
            {
                if (!otherKeyPressed)
                {
                    // 映射成 ESC 键
                    keystroke.code = ESC_KEY;
                    interception_send(context, device, &stroke, 1);
                }
                capsLockPressed = 0;
                continue; // 避免再次发送原按键
            }
            else
            {
                otherKeyPressed = 1; // 记录有其他按键被按下
                if (capsLockPressed)
                {
                    // 映射成 CTRL 键
                    keystroke.code = CTRL_KEY;
                }
            }
        }
        else if (interception_is_mouse(device) && capsLockPressed)
        {
            // 当鼠标事件发生且 Caps Lock 被按下时，将 Caps Lock 映射成 CTRL
            InterceptionKeyStroke ctrlStroke = {CTRL_KEY, INTERCEPTION_KEY_DOWN};
            interception_send(context, device, (InterceptionStroke *)&ctrlStroke, 1);
            ctrlStroke.state = INTERCEPTION_KEY_UP;
            interception_send(context, device, (InterceptionStroke *)&ctrlStroke, 1);
            continue; // 避免发送原鼠标事件
        }

        interception_send(context, device, &stroke, 1);
    }

    interception_destroy_context(context);

    return 0;
}
