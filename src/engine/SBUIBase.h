#ifndef SBUIBASE_H
#define SBUIBASE_H

#include "Decomp.h"
#include <vector>

class RHUnk005ef320;

class SBUIWindowView
{
public:
    virtual void V00() = 0;
    virtual void V04() = 0;
    virtual void AttachToDisplay(unsigned long display) = 0;
    virtual void V0c() = 0;
    virtual void V10() = 0;
    virtual void V14() = 0;
    virtual void V18(unsigned long surface) = 0;
    virtual void V1c() = 0;
};

class SBUIFontView
{
public:
    virtual void V00() = 0;
    virtual void V04() = 0;
    virtual void V08() = 0;
    virtual void V0c() = 0;
    virtual void V10() = 0;
    virtual void V14(void *renderer, bool alternate) = 0;
};

class SBUIWindowTooltipPart
{
public:
    SBUIWindowTooltipPart()
    {
        m_0 = 0;
        m_4 = 0;
        m_8 = 0;
    }

    int m_0;
    int m_4;
    short m_8;
};

class RHUnk006279d0;

class SBInputKeyboardState;

class SBUIUnk0060e1b0
{
public:
    void *FUN_0060e210(unsigned flags);
    SBUIUnk0060e1b0(int capacity);
    ~SBUIUnk0060e1b0();
    void FUN_0060e460();
    bool FUN_0060e260() const;
    bool FUN_0060e2a0(const SBInputKeyboardState &input);
    bool EmitRefresh(const SBInputKeyboardState &input);
};

struct SBUIWindowArray : public std::vector<SBUIWindowView *>
{
    friend class SBUI;
    friend class RHMapWindowPart;
    SBUIWindowView **cursor;
    bool dirty;
    bool cursorValid;
    undefined m_16[2];
    int index;
    SBUIWindowView *current;

    inline void Clear();
    void Remove(long position)
    {
        erase(&at(position));
        dirty = true;
    }
    int Size() const { return _First == 0 ? 0 : _Last - _First; }
    int Find(SBUIWindowView *window)
    {
        dirty = false;
        current = window;
        int count = _First == 0 ? 0 : _Last - _First;
        cursor = _First;
        cursorValid = true;
        int position = 0;
        for (; position < count; ++position, ++cursor)
            if (*cursor == window)
                break;
        return position < count ? position : -1;
    }
};

class SBUIFlagArray : public std::vector<char>
{
public:
    friend class SBUI;
    char *cursor;
    bool dirty;
    bool cursorValid;
    undefined m_16[2];
    int index;
    char current;
    void FUN_00619d00();
    inline void Clear();
    void Remove(long position)
    {
        erase(&at(position));
        dirty = true;
    }
    inline void Insert(char *position, unsigned count, const char &value);
};

class SBUI
{
public:
    ~SBUI();
    void *FUN_006186d0(unsigned flags);
    void FUN_00618910(unsigned long surface);
    void FUN_006189e0(unsigned long frame);
    bool FUN_00619800(SBUIWindowView *window);
    void FUN_00619a00(SBUIWindowView *window);
    bool FUN_00619c20(unsigned long display);
    void FUN_00619c80(SBUIFontView *font, SBUIFontView *alternate);

    unsigned m_vptr;
    SBUIWindowArray m_windows;
    SBUIFlagArray m_flags;
    SBUIUnk0060e1b0 m_input;
    undefined m_45[0x1713];
    RHUnk006279d0 *m_tooltip;
    unsigned short m_175c;
    unsigned short m_175e;
    unsigned short m_1760;
    unsigned short m_1762;
    RHUnk005ef320 *m_draw;
    unsigned long m_display;
    undefined m_176c[8];
    SBUIFontView *m_font;
    SBUIFontView *m_alternate;
    undefined m_177c[0x50];
    undefined m_renderer[0x20];
    unsigned long m_surface;
    undefined m_17f0[8];

    int Size() const
    {
        SBUIWindowView **first = *(SBUIWindowView **volatile *)&m_windows._First;
        return first == 0 ? 0 : m_windows._Last - first;
    }
    int Find(SBUIWindowView *window)
    {
        return m_windows.Find(window);
    }
};

#endif
