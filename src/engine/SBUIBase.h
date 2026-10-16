#ifndef SBUIBASE_H
#define SBUIBASE_H

#include "Decomp.h"

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

class SBUIWindowTooltip
{
public:
    void FUN_00627ee0(unsigned long display);
    void FUN_00628500();
};

class SBInputKeyboardState;

class SBUIUnk0060e1b0
{
public:
    SBUIUnk0060e1b0(int capacity);
    ~SBUIUnk0060e1b0();
    void FUN_0060e460();
    bool FUN_0060e260() const;
    bool FUN_0060e2a0(const SBInputKeyboardState &input);
    bool EmitRefresh(const SBInputKeyboardState &input);
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
    unsigned m_allocator;
    SBUIWindowView **m_first;
    SBUIWindowView **m_last;
    SBUIWindowView **m_end;
    SBUIWindowView **m_cursor;
    bool m_dirty;
    bool m_cursorValid;
    undefined m_1a[2];
    int m_index;
    SBUIWindowView *m_current;
    unsigned m_byteAllocator;
    unsigned char *m_flags;
    unsigned char *m_flagsLast;
    unsigned char *m_flagsEnd;
    unsigned char *m_flagsCursor;
    bool m_flagsDirty;
    undefined m_39[0xb];
    SBUIUnk0060e1b0 m_input;
    undefined m_45[0x1713];
    SBUIWindowTooltip *m_tooltip;
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
        SBUIWindowView **first = *(SBUIWindowView **volatile *)&m_first;
        return first == 0 ? 0 : m_last - first;
    }
    int Find(SBUIWindowView *window)
    {
        m_dirty = false;
        m_current = window;
        int count = m_first == 0 ? 0 : m_last - m_first;
        m_cursor = m_first;
        m_cursorValid = true;
        int index = 0;
        for (; index < count; ++index, ++m_cursor)
            if (*m_cursor == window)
                break;
        return index < count ? index : -1;
    }
};

#endif
