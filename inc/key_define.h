#ifndef _KEY_DEFINE_H_
#define _KEY_DEFINE_H_
    
#include <stdio.h>

enum ScanCode
{
    SCANCODE_LWIN = 0x5B,
    SCANCODE_LALT = 0x38,
    SCANCODE_RALT = 0x38,
    SCANCODE_LSHIFT = 0x2A,
    SCANCODE_RSHIFT = 0x36,
    SCANCODE_LCTRL = 0x1D,
    SCANCODE_RCTRL = 0x1D
};

enum VirtCode
{
    VIRTCODE_LWIN = 91,
    VIRTCODE_LALT = 18,
    VIRTCODE_RALT = 165,
    VIRTCODE_LSHIFT = 16,
    VIRTCODE_RSHIFT = 161,
    VIRTCODE_LCTRL = 17,
    VIRTCODE_RCTRL = 163
};

enum PhyKeyState
{
    PHY_KEY_DOWN = false,
    PHY_KEY_UP = true
};

#define KEY_DOWN(vKey) ((GetAsyncKeyState(vKey) & 0x8000) ? 1 : 0)

// #define DEBUG
#ifdef DEBUG
    #define DBGprint(...) printf(__VA_ARGS__)
#else
    #define DBGprint(...)
#endif

extern bool phy_Alt_pressed;
extern bool phy_Ctrl_pressed;
extern bool phy_Shift_pressed;

#endif
