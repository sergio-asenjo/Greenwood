#ifndef SBUIBASE_H
#define SBUIBASE_H

#include "Decomp.h"
#include <vector>
#include <string>
#include "SBUIUnkSurface.h"
#include "SBUIKeyboardCalls.h"
#ifndef SBGEO_BOUNDINGBOX2D_VIEW
#include "SBGeoBoundingBox2DCore.h"
#endif

class SBDrawManager;
struct RHPortraitWidgetInput;
struct RHPortraitWidgetEvent;
class SBFrameWidgetView;
struct SBInputMouseState;
struct SBFrameEvent;

class RHPortraitRootLifetime;
typedef RHPortraitRootLifetime SBUIWindowView;

class SBFontUnk0061e840;

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
    RHPortraitWidgetEvent *InputLoop(SBInputMouseState &mouse, SBInputKeyboardState &keyboard, bool skip);
    bool FUN_00619800(SBUIWindowView *window);
    void FUN_00619a00(SBUIWindowView *window);
    bool FUN_00619c20(unsigned long display);
    void FUN_00619c80(SBFontUnk0061e840 *font, SBFontUnk0061e840 *alternate);

    unsigned m_vptr;
    SBUIWindowArray m_windows;
    SBUIFlagArray m_flags;
    SBUIUnk0060e1b0 m_input;
    bool m_1754;
    bool m_1755;
    undefined m_1756[2];
    RHUnk006279d0 *m_tooltip;
    unsigned short m_175c;
    unsigned short m_175e;
    unsigned short m_1760;
    unsigned short m_1762;
    SBDrawManager *m_draw;
    unsigned long m_display;
    undefined m_176c[8];
    SBFontUnk0061e840 *m_font;
    SBFontUnk0061e840 *m_alternate;
    void *m_177c;
    unsigned long m_1780;
    unsigned long m_1784;
    bool m_1788;
    std::wstring m_178c;
    SBGeoBoundingBox2D m_179c[2];
    bool m_17c4[2];
    unsigned long m_17c8;
    SBUIUnkSurface m_renderer;
    unsigned long m_surface;
    SBFrameWidgetView *m_17f0;
    SBUIWindowView *m_17f4;

    int Size() const
    {
        SBUIWindowView **first = *(SBUIWindowView **volatile *)&m_windows._First;
        return first == 0 ? 0 : m_windows._Last - first;
    }
    int Find(SBUIWindowView *window)
    {
        return m_windows.Find(window);
    }
    SBUI &ReleaseInput()
    {
        m_17f0 = 0;
        m_17f4 = 0;
        return *this;
    }
};

#endif
