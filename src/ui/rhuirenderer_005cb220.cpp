#include "rhuirenderer_005cb220.h"
#include "SBDrawManagerCore.h"

DECOMP_SIZE_ASSERT(SBGeoBoundingBox2D, 0x14)
DECOMP_SIZE_ASSERT(SBUIUnk0060da20, 0x4c)
DECOMP_SIZE_ASSERT(RHGameRenderer0060da10, 0x4c)
DECOMP_SIZE_ASSERT(RHGameRenderer005cb220, 0x50)

// FUNCTION: GAME 0x005cb220
RHGameRenderer005cb220::RHGameRenderer005cb220()
{
    m_alternate = -1;
    *(unsigned *)this = 0x00679e8c;
}

// FUNCTION: GAME 0x005cb240
void *RHGameRenderer005cb220::FUN_005cb240(unsigned flags)
{
    this->RHGameRenderer005cb220::~RHGameRenderer005cb220();
    if (flags & 1)
        operator delete(this);
    return this;
}

// SYNTHETIC: GAME 0x005cb260
// ??1RHGameRenderer005cb220@@UAE@XZ

// FUNCTION: GAME 0x005cb270
bool RHGameRenderer005cb220::FUN_005cb270(unsigned id)
{
    if (m_alternate == -1)
        return ((SBUIUnk0060da20 *)this)->FUN_0060da20(id);
    return ((SBDrawManager *)m_drawManager)->FUN_005e6440(m_alternate, 0, m_hardware, &m_position, 0);
}

// FUNCTION: GAME 0x005cb2a0
void RHGameRenderer005cb220::FUN_005cb2a0()
{
    m_alternate = -1;
    m_surfaces.values[0] = -1;
    m_surfaces.values[1] = -1;
}

// FUNCTION: GAME 0x005cb2b0
void RHGameRenderer005cb220::FUN_005cb2b0(int value)
{
    RHUnk005fc3b0 size;
    m_alternate = value;
    if (value != -1)
        m_drawManager->FUN_005e57e0(value, (SBGeoVector2D &)size);
    else
        m_resources->FUN_006006f0(m_widgetResource, size);
    m_position.SetMax(m_position.m_first.Unk005fc190(size));
    m_surfaces.values[0] = -1;
    m_surfaces.values[1] = -1;
}
