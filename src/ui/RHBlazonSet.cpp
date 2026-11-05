#include "SBNullstr.h"
#include "SBGeoBoundingBox2DCore.h"
#include "SBGeoVector2D.h"
#include "RHMenuShortMissionBlazons.h"
#include "RHBriefingWindowCalls.h"
#include "RHGameWidgetLifetime.h"
#include "RHMapWidget.h"
#include "RHFocusManager.h"
#include "RHMobileUnk00607da0.h"
#include "RHCampaignValueCalls.h"
#include <stddef.h>

extern RHUnk00452030 *g_unk0x6c07fc;
std::wstring FUN_005e23d0(unsigned long);

DECOMP_SIZE_ASSERT(RHMenuShortMissionBlazons, 0x1c)
DECOMP_SIZE_ASSERT(RHGameLifetime0044fe90, 0xd0)
DECOMP_STATIC_ASSERT(offsetof(RHMenuShortMissionBlazons, m_widgets) == 0x08)
DECOMP_STATIC_ASSERT(offsetof(RHMenuShortMissionBlazons, m_count) == 0x0c)
DECOMP_STATIC_ASSERT(offsetof(RHGameWidgetLifetimeBase, m_08) == 0x08)
DECOMP_STATIC_ASSERT(offsetof(RHGameWidgetLifetimeBase, m_20) == 0x20)

// FUNCTION: GAME 0x0044edb0
RHMenuShortMissionBlazons::RHMenuShortMissionBlazons(void *mission, void *parent)
{
    m_mission = mission;
    m_parent = parent;
    m_count = *(unsigned short *)((char *)*(void **)mission + 0x68);
    m_10 = 0;
    m_14 = false;
    m_18 = 0;
    if (m_count)
        m_widgets = new RHGameLifetime0044fe90[m_count];
    else
        m_widgets = 0;
}

void EmitRHBlazonSetConstructor(void *mission, void *parent)
{
    RHMenuShortMissionBlazons value(mission, parent);
}

// SYNTHETIC: GAME 0x0044ee50
// ??_ERHGameLifetime0044fe90@@QAEPAXI@Z

// LIBRARY: GAME 0x00642cba
// ??_M@YGXPAXIHP6EX0@Z@Z




class RHBlazonWidgetDeletionCalls
{
public:
    virtual void Delete(unsigned flags) = 0;
};

// FUNCTION: GAME 0x0044eeb0
RHMenuShortMissionBlazons::~RHMenuShortMissionBlazons()
{
    if (m_widgets) {
        for (unsigned long index = 0; index < m_count; ++index)
            ((RHBriefingWindowCalls *)m_parent)->V34((char *)m_widgets + index * 0xd0);
        if (m_widgets)
            ((RHBlazonWidgetDeletionCalls *)m_widgets)->Delete(3);
    }
}

// FUNCTION: GAME 0x0044ef00
unsigned long RHMenuShortMissionBlazons::ComputeNumberOfBlazonsPerRow(const SBGeoBoundingBox2D &bounds, bool &normal) const
{
    const float *box = (const float *)&bounds;
    unsigned long count = (long)((box[2] - box[0]) * 0.0270270276814699f);
    normal = true;
    if (count <= m_count || box[3] - box[1] < 42.0f) {
        count = (long)((box[2] - box[0]) * 0.0714285746216774f);
        normal = false;
    }
    return count;
}

// STUB: GAME 0x0044ef60
bool RHMenuShortMissionBlazons::FUN_0044ef60(const RHMapBox &bounds, RHFocusManager *focus)
{
    bool normal;
    unsigned long perRow = ComputeNumberOfBlazonsPerRow(bounds, normal);
    SBGeoBoundingBox2D size;
    unsigned long rows = m_count / perRow + (m_count % perRow != 0);
    unsigned long resource;
    unsigned long vertical;
    unsigned long horizontal;
    if (normal) {
        perRow = m_count;
        ((RHMobileUnk00607da0 *)&size)->FUN_00607da0((const RHMobileUnk00607da0 &)SBGeoBoundingBox2D(0.0f, 0.0f, 32.0f, 42.0f));
        resource = 134;
        vertical = 47;
        horizontal = 37;
    } else {
        ((RHMobileUnk00607da0 *)&size)->FUN_00607da0((const RHMobileUnk00607da0 &)SBGeoBoundingBox2D(0.0f, 0.0f, 9.0f, 14.0f));
        resource = 135;
        vertical = 19;
        horizontal = 14;
    }
    for (unsigned long row = 0; row < rows; ++row) {
        SBGeoPoint2D position;
        unsigned long count = (row + 1) * perRow <= m_count ? perRow : m_count - row * perRow;
        unsigned long width = count * horizontal - 5;
        position = bounds.Min();
        position.FUN_005fc1e0(SBGeoVector2D((bounds.Width() - width) * 0.5f, (float)(row * vertical)));
        for (unsigned long column = 0; column < count; ++column) {
            RHGameLifetime0044fe90 &widget = m_widgets[row * perRow + column];
            bool created;
            {
                SBGeoVector2D offset((const SBGeoVector2D &)position);
                created = ((RHMapWidget *)&widget)->V30(
                    // STRING: GAME 0x006ab8b0
                    L"Blazon", size.FUN_006090d0(offset), 0, resource);
            }
            if (!created)
                return false;
            ((RHBriefingWindowCalls *)m_parent)->V30(&widget);
            ((RHMapWidget *)&widget)->V10();
            if (focus)
                focus->FUN_004ffd20(&widget);
            position.FUN_005fc1e0(SBGeoVector2D((float)horizontal, 0.0f));
        }
    }
    FUN_0044f960(0);
    return true;
}

inline void RHBlazonSetText(RHGameLifetime0044fe90 &widget, const std::wstring &text)
{
    widget.m_08 = true;
    widget.m_20 = text;
}

// FUNCTION: GAME 0x0044f400
void RHMenuShortMissionBlazons::FUN_0044f400(RHGameLifetime0044fe90 &widget)
{
    ((RHMapWidget *)&widget)->V38(2);
    RHBlazonSetText(widget, FUN_005e23d0(0x141));
}

// FUNCTION: GAME 0x0044f5d0
void RHMenuShortMissionBlazons::FUN_0044f5d0(RHGameLifetime0044fe90 &widget)
{
    ((RHMapWidget *)&widget)->V38(0);
    RHBlazonSetText(widget, FUN_005e23d0(0x140));
}

// FUNCTION: GAME 0x0044f750
void RHMenuShortMissionBlazons::FUN_0044f750(RHGameLifetime0044fe90 &widget)
{
    ((RHMapWidget *)&widget)->V38(1);
    RHBlazonSetText(widget, FUN_005e23d0(0x142));
}

// FUNCTION: GAME 0x0044f960
void RHMenuShortMissionBlazons::FUN_0044f960(int value)
{
    unsigned long level = g_unk0x6c07fc->Get(3) + value;
    unsigned long visible = *(unsigned short *)((char *)*(void **)m_mission + 0x6a);
    if (level > m_count)
        level = m_count;
    RHGameLifetime0044fe90 *last = m_widgets + level;
    for (RHGameLifetime0044fe90 *widget = m_widgets; widget != last; ++widget)
        FUN_0044f750(*widget);
    if (level + visible < m_count) {
        RHGameLifetime0044fe90 *emptyEnd = m_widgets + (m_count - visible);
        for (RHGameLifetime0044fe90 *widget = m_widgets + level; widget != emptyEnd; ++widget)
            FUN_0044f5d0(*widget);
        RHGameLifetime0044fe90 *end = m_widgets + m_count;
        for (RHGameLifetime0044fe90 *castle = m_widgets + (m_count - visible); castle != end; ++castle)
            FUN_0044f400(*castle);
    } else {
        RHGameLifetime0044fe90 *end = m_widgets + m_count;
        for (RHGameLifetime0044fe90 *widget = m_widgets + level; widget != end; ++widget)
            FUN_0044f400(*widget);
    }
}
