#include "RHMenuShortMissionBlazons.h"
#include "RHBriefingWindowCalls.h"
#include "RHGameWidgetLifetime.h"

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

// GLOBAL: GAME 0x006775cc
float g_blazonCompactWidth = 0.0714285746216774f;

// GLOBAL: GAME 0x006775d0
float g_blazonMinimumHeight = 42.0f;

// GLOBAL: GAME 0x006775d4
float g_blazonNormalWidth = 0.0270270276814699f;

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
    unsigned long count = (long)((box[2] - box[0]) * g_blazonNormalWidth);
    normal = true;
    if (count <= m_count || box[3] - box[1] < g_blazonMinimumHeight) {
        count = (long)((box[2] - box[0]) * g_blazonCompactWidth);
        normal = false;
    }
    return count;
}
