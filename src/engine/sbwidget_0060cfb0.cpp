#include "SBGeoBoundingBox2DCore.h"
#include "RHGameWidgetLifetime.h"
#include "RHMobileUnk00607da0.h"
#include <string.h>

// FUNCTION: GAME 0x0060cfb0
RHGameWidgetLifetimeBase::RHGameWidgetLifetimeBase()
    : m_04(true), m_05(true), m_06(true), m_07(false), m_08(false), m_0a(0), m_state(0)
{
    memset(m_4c, 0, sizeof(m_4c));
}

// FUNCTION: GAME 0x0060d050
RHGameWidgetLifetimeBase::~RHGameWidgetLifetimeBase()
{
}

// FUNCTION: GAME 0x0060d130
bool RHGameWidgetLifetimeBase::Create(const std::wstring &name, const SBGeoBoundingBox2D &box, unsigned long flags)
{
    m_10 = name;
    m_0c = flags;
    ((RHMobileUnk00607da0 *)&m_30)->FUN_00607da0(*(const RHMobileUnk00607da0 *)&box);
    m_07 = true;
    return true;
}
