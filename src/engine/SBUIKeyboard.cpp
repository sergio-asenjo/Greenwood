#include <windows.h>
#include <string.h>
#include "SBUI.h"

struct SBUIKeyboardFields
{
    unsigned int vptr;
    unsigned short first;
    unsigned short second;
    bool initialized;
    bool changed;
    unsigned short keys[256];
    unsigned short padding;
    int state[256];
    int previous[256];
    int repeat[256];
    unsigned long released[256];
    unsigned long pressed[256];
    unsigned long delay;
    unsigned char keyboard[256];
};

typedef char SBUIKeyboardSizeCheck[sizeof(SBUIKeyboardFields) == 0x1710 ? 1 : -1];

// FUNCTION: GAME 0x0060e2a0
bool SBUIUnk0060e1b0::FUN_0060e2a0(const SBInputKeyboardState &input)
{
    SBUIKeyboardFields &self = *(SBUIKeyboardFields *)this;
    const unsigned char *keyboard = (const unsigned char *)&input;
    if (!self.initialized)
    {
        memcpy(self.keyboard, keyboard, 256);
        self.initialized = true;
        return false;
    }
    memcpy(self.previous, self.state, sizeof(self.state));
    self.changed = false;
    unsigned int i = 0;
    for (unsigned int remaining = 256; remaining != 0; --remaining, ++i)
    {
        if (keyboard[i] != self.keyboard[i])
        {
            unsigned long time = GetTickCount();
            self.changed = true;
            if (keyboard[i] > 0)
            {
                self.state[i] = 1;
                self.pressed[i] = time;
                self.repeat[i] = 0;
            }
            else
            {
                self.keys[i] = 0;
                switch (self.state[i])
                {
                case 1:
                    if (time - self.released[i] <= self.delay)
                        self.state[i] = 3;
                    else
                    {
                        self.state[i] = 2;
                        self.released[i] = time;
                    }
                    break;
                }
            }
        }
        else
        {
            if (keyboard[i] > 0)
            {
                switch (self.repeat[i])
                {
                case 0:
                    self.repeat[i] = 1;
                    break;
                case 1:
                    if (GetTickCount() - self.pressed[i] > 400)
                    {
                        self.repeat[i] = 2;
                        self.pressed[i] = GetTickCount();
                    }
                    break;
                case 2:
                    self.repeat[i] = 3;
                    break;
                case 3:
                    if (GetTickCount() - self.pressed[i] > 50)
                    {
                        self.repeat[i] = 2;
                        self.pressed[i] = GetTickCount();
                    }
                    break;
                }
            }
            else
                self.repeat[i] = 0;
            if (self.state[i] >= 2 && self.state[i] <= 3)
            {
                self.changed = true;
                self.state[i] = 0;
            }
        }
    }
    memcpy(self.keyboard, keyboard, 256);
    return true;
}

bool SBUIUnk0060e1b0::EmitRefresh(const SBInputKeyboardState &input)
{
    return FUN_0060e2a0(input);
}
