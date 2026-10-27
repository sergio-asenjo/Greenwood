// RHMenuWindow.cpp — the menu window base TU (code 0x00543e70..0x00544bcb).
// See RHMenuWindow.h for the binding evidence.

#include "SBNullstr.h"
#include "RHMenuWindow.h"

void RHMenuWindow_Emit(RHMenuWindow *window)
{
    window->FUN_00544300();
    std::vector<void *> widgets;
    window->FUN_00544380(widgets, 0);
    window->FUN_00544600(widgets, 0);
    window->FUN_00544800(widgets, 0);
}

// FUNCTION: GAME 0x00543e70
RHMenuWindow::RHMenuWindow(RHMenuWindow *parent, RHMenuWindowScreen *screen, bool saveBackground)
    : m_draw((RHUnkFXDraw *)g_unk0x6c11d0), m_screen(screen), m_parent(parent), m_resourceHeld(false)
{
    if (saveBackground)
    {
        typedef unsigned long (RHUnkFXDraw::*CreateSurface)(unsigned short, unsigned short, unsigned long, bool);
        m_saveSurface = (m_draw->*reinterpret_cast<CreateSurface>(&RHUnkFXDraw::Unk005e4ed0))(
            m_draw->FUN_005e56c0(0), m_draw->FUN_005e5750(0), 0, false);
        RHMenuWindowUI *ui = m_screen->FUN_0053bf30();
        m_draw->FUN_005e6440(ui->m_17ec, 0, m_saveSurface, 0, 0);
        unsigned long background = m_screen->FUN_0053bf30()->m_17ec;
        m_draw->FUN_005e6440(0, 0, background, 0, 0);
    }
    else
    {
        m_saveSurface = (unsigned long)-1;
    }
}

// FUNCTION: GAME 0x00543f80
void *RHMenuWindow::FUN_00543f80(unsigned flags)
{
    this->~RHMenuWindow();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x005442b0
RHMenuWindow::~RHMenuWindow()
{
    FUN_00544300();
}

// FUNCTION: GAME 0x00544300
void RHMenuWindow::FUN_00544300()
{
    if (m_resourceHeld)
    {
        m_resourceOwner->FUN_005fd4a0(m_resource);
        m_resourceHeld = false;
    }
    if (m_saveSurface != (unsigned long)-1)
    {
        RHMenuWindowUI *ui = m_screen->FUN_0053bf30();
        m_draw->FUN_005e6440(m_saveSurface, 0, ui->m_17ec, 0, 0);
        m_draw->Unk005e5160(m_saveSurface);
        m_saveSurface = (unsigned long)-1;
    }
}

#include "RHMapWidget.h"

// FUNCTION: GAME 0x00544380
void RHMenuWindow::FUN_00544380(const std::vector<void *> &widgets, unsigned spacing)
{
    unsigned height = 0;
    unsigned width = 0;
    SBGeoPoint2D position;
    std::vector<void *>::const_iterator it = widgets.begin();
    for (; it != widgets.end(); ++it)
    {
        SBGeoBoundingBox2D box(*(SBGeoBoundingBox2D *)((char *)*it + 0x30));
        height += box.Height();
        if (box.Width() > width)
            width = box.Width();
    }
    height += (widgets.size() - 1) * spacing;
    position = ((RHMapWidget *)this)->V24().Max().FUN_005fc200(SBGeoVector2D(width, height));
    for (it = widgets.begin(); it != widgets.end(); ++it)
    {
        SBGeoPoint2D current(position);
        SBGeoBoundingBox2D box(*(SBGeoBoundingBox2D *)((char *)*it + 0x30));
        current.FUN_005fc1e0(SBGeoVector2D(0.0f, (box.Width() - width) * 0.5f));
        ((RHUnk005d92c0Sub *)*it)->v08(current);
        position.FUN_005fc1e0(SBGeoVector2D(0.0f, box.Height() + spacing));
    }
}

// FUNCTION: GAME 0x00544600
void RHMenuWindow::FUN_00544600(const std::vector<void *> &widgets, unsigned spacing)
{
    unsigned width = 0;
    SBGeoPoint2D position;
    std::vector<void *>::const_iterator it = widgets.begin();
    for (; it != widgets.end(); ++it)
    {
        SBGeoBoundingBox2D box(*(SBGeoBoundingBox2D *)((char *)*it + 0x30));
        if (box.Width() > width)
            width = box.Width();
    }
    float right = ((RHMapWidget *)this)->V24().m_second.m_x;
    position.m_x = right - width;
    position.m_y = ((RHMapWidget *)this)->V24().m_first.m_y;
    for (it = widgets.begin(); it != widgets.end(); ++it)
    {
        SBGeoPoint2D current(position);
        SBGeoBoundingBox2D box(*(SBGeoBoundingBox2D *)((char *)*it + 0x30));
        current.FUN_005fc1e0(SBGeoVector2D(0.0f, (box.Width() - width) * 0.5f));
        ((RHUnk005d92c0Sub *)*it)->v08(current);
        position.FUN_005fc1e0(SBGeoVector2D(0.0f, box.Height() + spacing));
    }
}

// FUNCTION: GAME 0x00544800
unsigned RHMenuWindow::FUN_00544800(const std::vector<void *> &widgets, unsigned spacing)
{
    SBGeoPoint2D position;
    unsigned height = 0;
    unsigned width;
    if (widgets.size() >= 1)
    {
        position = ((SBGeoBoundingBox2D *)((char *)widgets.front() + 0x30))->m_first;
        width = ((SBGeoBoundingBox2D *)((char *)widgets.front() + 0x30))->Width();
    }
    else
        width = spacing;
    for (std::vector<void *>::const_iterator it = widgets.begin(); it != widgets.end(); ++it)
    {
        SBGeoPoint2D current(position);
        SBGeoBoundingBox2D box(*(SBGeoBoundingBox2D *)((char *)*it + 0x30));
        current.FUN_005fc1e0(SBGeoVector2D((width - box.Width()) * 0.5f, 0.0f));
        ((RHUnk005d92c0Sub *)*it)->v08(current);
        position.FUN_005fc1e0(SBGeoVector2D(0.0f, box.Height() + spacing));
        height += box.Height();
    }
    if (!widgets.empty())
        height += (widgets.size() - 1) * spacing;
    return height;
}

// FUNCTION: GAME 0x005449e0
void RHMenuWindow::FUN_005449e0(const std::vector<void *> &widgets, unsigned spacing)
{
    unsigned width = 0;
    SBGeoPoint2D position;
    std::vector<void *>::const_iterator it = widgets.begin();
    std::vector<void *>::const_iterator end = widgets.end();
    for (; it != end; ++it)
        width += ((SBGeoBoundingBox2D *)((char *)*it + 0x30))->Width();
    width += (widgets.size() - 1) * spacing;
    position.m_x = (((RHMapWidget *)this)->V24().Width() - width) * 0.5f;
    it = widgets.begin();
    position.m_y = ((SBGeoBoundingBox2D *)((char *)*it + 0x30))->m_first.m_y;
    for (; it != widgets.end(); ++it)
    {
        ((RHUnk005d92c0Sub *)*it)->v08(position);
        position.FUN_005fc1e0(SBGeoVector2D(((SBGeoBoundingBox2D *)((char *)*it + 0x30))->Width() + spacing, 0.0f));
    }
}

// FUNCTION: GAME 0x00544b40
bool RHMenuWindow::FUN_00544b40(const std::wstring &title, const RHMapBox &box, unsigned flags)
{
    return RHPortraitRootLifetime::FUN_0061a1e0(*(const RHMapTitleText *)&title, box, flags);
}

class RHBriefingNarrowText;

class RHBriefingParentCalls
{
public:
    void *FUN_00544b60(const RHBriefingNarrowText &name);
};

// FUNCTION: GAME 0x00544b60
void *RHBriefingParentCalls::FUN_00544b60(const RHBriefingNarrowText &name)
{
    return (*(RHPortraitTextResourceCalls **)((char *)this + 0xb4))->FUN_0053be80(*(const std::string *)&name);
}

// FUNCTION: GAME 0x00544b80
void RHMenuWindow::FUN_00544b80(bool display, bool modal)
{
    m_screen->FUN_0053bb80(this, display, modal);
}
