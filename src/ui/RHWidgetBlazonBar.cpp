#include "RHGameBlazonWidget.h"
#include "RHPortraitRootLifetime.h"
#include "RHMission.h"
#include "RHMenuShortMissionBlazons.h"
#include <new>

class RHUnk0048a970;
class RHUnk00452030;
extern RHUnk0048a970 *g_unk0x6c0b3c;
extern RHUnk00452030 *g_unk0x6c07fc;

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
