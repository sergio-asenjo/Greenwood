#ifndef SBUI_H
#define SBUI_H

#include "Decomp.h"

class RHUnk005ef320;
extern RHUnk005ef320 *g_unk0x6c11d0;

class RHUnkFXDraw
{
public:
    void FUN_005e5260();
    void FUN_005e6440(unsigned long surface, int first, int second, unsigned long third, unsigned long flags);
};

class SBThreadedInput
{
public:
    void FUN_005f1700();
    void PopMouseBackground(bool wait);
};

extern SBThreadedInput *g_unk0x6c1340;

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
};

class SBUI
{
public:
    void FUN_00618910(unsigned long surface);
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
    undefined m_39[0x171f];
    SBUIWindowTooltip *m_tooltip;
    undefined m_175c[8];
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
