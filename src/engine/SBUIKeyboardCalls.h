#ifndef SBUIKEYBOARDCALLS_H
#define SBUIKEYBOARDCALLS_H

class SBInputKeyboardState;

class SBUIUnk0060e1b0
{
public:
    void *FUN_0060e210(unsigned flags);
    SBUIUnk0060e1b0(int capacity);
    ~SBUIUnk0060e1b0();
    void FUN_0060e460();
    int FUN_0060e240(unsigned short shortcut);
    bool FUN_0060e260() const;
    bool FUN_0060e2a0(const SBInputKeyboardState &input);
    bool EmitRefresh(const SBInputKeyboardState &input);
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

class RHPortraitKeyboardCalls
{
public:
    char FUN_0060e270(unsigned short key);
};

#endif
