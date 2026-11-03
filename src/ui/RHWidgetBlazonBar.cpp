#include "SBNullstr.h"
#include "RHGameBlazonWidget.h"
#include "RHPortraitRootLifetime.h"
#include "RHMission.h"
#include "RHMenuShortMissionBlazons.h"
#include "SBGeoBoundingBox2DCore.h"
#include "SBGeoVector2D.h"
#include <new>

class RHUnk0048a970;
class RHUnk00452030;
extern RHUnk0048a970 *g_unk0x6c0b3c;
extern RHUnk00452030 *g_unk0x6c07fc;

// FUNCTION: GAME 0x005cc5d0
RHGameBlazonWidget::RHGameBlazonWidget() : m_b0(0)
{
}

// FUNCTION: GAME 0x005cc610
void *RHGameBlazonWidget::FUN_005cc610(unsigned flags)
{
    this->~RHGameBlazonWidget();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x005cc630
RHGameBlazonWidget::~RHGameBlazonWidget()
{
    FUN_005cc840();
}

// FUNCTION: GAME 0x005cc680
bool RHGameBlazonWidget::FUN_005cc680(const SBGeoBoundingBox2D &bounds)
{
    bool initialized;
    {
        std::wstring title(
            // STRING: GAME 0x006b8dc0
            L"BlazonBar");
        initialized = RHPortraitRootLifetime::FUN_0061a1e0((const RHMapTitleText &)title, bounds, 0) == true;
    }
    if (initialized) {
        SBGeoVector2D origin((const SBGeoVector2D &)bounds.Min());
        FUN_005cc7b0(bounds - origin);
        return true;
    }
    return false;
}

// FUNCTION: GAME 0x005cc7b0
void RHGameBlazonWidget::FUN_005cc7b0(const SBGeoBoundingBox2D &bounds)
{
    RHMission *mission = FUN_005cc870();
    FUN_005cc840();
    if (mission) {
        m_b0 = (RHGameBlazonValue *)new RHMenuShortMissionBlazons(mission, this);
        ((RHMenuShortMissionBlazons *)m_b0)->FUN_0044ef60(bounds, false);
    }
}

// FUNCTION: GAME 0x005cc840
void RHGameBlazonWidget::FUN_005cc840()
{
    if (m_b0) {
        delete (RHMenuShortMissionBlazons *)m_b0;
        m_b0 = 0;
    }
}

// Parked: mission-pointer live ranges select different registers and conditional saves.
// STUB: GAME 0x005cc870
RHMission *RHGameBlazonWidget::FUN_005cc870()
{
    RHMission *mission = *(RHMission **)((char *)g_unk0x6c07fc + 0x180);
    if (*(bool *)((char *)g_unk0x6c0b3c + 0x57)) {
        if (mission == 0)
            return *(RHMission **)((char *)g_unk0x6c07fc + 0x17c);
    } else if (mission == 0) {
        mission = *(RHMission **)((char *)g_unk0x6c07fc + 0x178);
        if (!(char)mission->FUN_0054cc20())
            return 0;
    }
    return mission;
}

// FUNCTION: GAME 0x005cc8c0
SBFrameInputEvent *RHGameBlazonWidget::FUN_005cc8c0(const void *input)
{
    SBFrameInputEvent *events = (SBFrameInputEvent *)((RHPortraitRootLifetime *)this)->FUN_0061a6e0(input);
    SBFrameInputEvent **link = &events;
    while (*link) {
        SBFrameInputEvent *event = *link;
        if (event->widget == this)
            *link = event->next;
        link = &event->next;
    }
    return events;
}

// FUNCTION: GAME 0x005cc900
void RHGameBlazonWidget::FUN_005cc900(int value)
{
    if (m_b0)
        m_b0->FUN_0044f960(value);
}

// FUNCTION: GAME 0x005cc920
void RHGameBlazonWidget::FUN_005cc920(int value)
{
    if (m_b0)
        m_b0->FUN_0044f8d0(value);
}

// FUNCTION: GAME 0x005cc940
void RHGameBlazonWidget::FUN_005cc940(const SBGeoBoundingBox2D &bounds)
{
    SBGeoVector2D origin((const SBGeoVector2D &)bounds.Min());
    FUN_005cc7b0(bounds - origin);
}
