#include "rhuirenderer_005cb220.h"

DECOMP_SIZE_ASSERT(SBGeoBoundingBox2D, 0x14)
DECOMP_SIZE_ASSERT(SBUIUnk0060da20, 0x4c)
DECOMP_SIZE_ASSERT(RHPictureRenderer0060d9f0, 0x4c)
DECOMP_SIZE_ASSERT(RHGameRenderer005cb220, 0x50)

// FUNCTION: GAME 0x005cb220
RHGameRenderer005cb220::RHGameRenderer005cb220()
{
    m_alternate = -1;
    m_vptr = 0x00679e8c;
}

// FUNCTION: GAME 0x005cb240
void *RHGameRenderer005cb220::FUN_005cb240(unsigned flags)
{
    this->~RHGameRenderer005cb220();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x005cb270
bool RHGameRenderer005cb220::FUN_005cb270(unsigned id)
{
    if (m_alternate == -1)
        return ((SBUIUnk0060da20 *)this)->FUN_0060da20(id);
    return m_draw->FUN_005e6440(m_alternate, 0, m_target, &m_box, 0);
}

// FUNCTION: GAME 0x005cb2a0
void RHGameRenderer005cb220::FUN_005cb2a0()
{
    m_alternate = -1;
    m_40 = -1;
    m_44 = -1;
}

// FUNCTION: GAME 0x005cb2b0
void RHGameRenderer005cb220::FUN_005cb2b0(int value)
{
    RHUnk005fc3b0 size;
    m_alternate = value;
    if (value != -1)
        m_draw->FUN_005e57e0(value, (SBGeoVector2D &)size);
    else
        m_resource->FUN_006006f0(m_resourceId, size);
    m_box.SetMax(m_box.m_first.Unk005fc190(size));
    m_40 = -1;
    m_44 = -1;
}
