#include "SBGeoPoint2D.h"
#include "SBGeoBoundingBox2DCore.h"
#include "RHUnk005fc3b0.h"
#include "RHSelectionMark.h"
#include "RHSpriteCore.h"
#include "RHMobileVectorArray.h"
#include "RHFrameHolder.h"

class RHMapResources;
extern RHMapResources *g_unk0x006c1840;
SBGeoVector2D FUN_005fc580(const SBGeoVector2D &, float);

DECOMP_SIZE_ASSERT(RHUnk00581c40, 0x1c)
DECOMP_STATIC_ASSERT(offsetof(RHUnk00581c40, m_4) == 4)
DECOMP_STATIC_ASSERT(offsetof(RHUnk00581c40, m_c) == 0xc)
DECOMP_STATIC_ASSERT(offsetof(RHUnk00581c40, m_10) == 0x10)

// FUNCTION: GAME 0x00581c70
unsigned long RHUnk00581c40::LoadFromResource()
{
    RHMobileVectorArray offsets;
    RHUnk005fc3b0 size;
    unsigned short count;
    SBResourceManager *resources = (SBResourceManager *)g_unk0x006c1840;
    m_4->FUN_005b73f0(2);
    unsigned long first = ((RHFrameHolder *)m_c)->AddRowFromResource(
        resources, 6, count, (SBArray<SBGeoVector2D> &)offsets);
    m_4->FUN_005bb180(0, first, 9, 2, 0, &offsets);
    first = ((RHFrameHolder *)m_c)->AddRowFromResource(
        resources, 0x45, count, (SBArray<SBGeoVector2D> &)offsets);
    m_4->FUN_005bb180(1, first, 9, 2, 0, &offsets);
    m_10 = m_8->Unk005e4ed0(
        m_4->FUN_005bdd50(), m_4->FUN_005bdd70(), 0, false);
    size.FUN_005fc430(FUN_005fc580(SBGeoVector2D((float)m_4->FUN_005bdd50(),
        (float)m_4->FUN_005bdd70()), 0.5f));
    m_4->AssignBox(SBGeoBoundingBox2D(-size, size));
    m_4->AssignOffset(size);
    return 0;
}

#include "RHPositionInterface.h"
#include "RHEngineWidenedCalls.h"
#include "RHspriteRenderingInfoCore.h"
#include "SBDrawManagerCore.h"

class RHEngine;
extern RHEngine *g_pEngine;

// STUB: GAME 0x00581ee0
bool RHUnk00581c40::FUN_00581ee0(unsigned long surface, float scale, const SBGeoBoundingBox2D &view,
    const SBGeoPoint2D &point, unsigned short layer, bool, bool selected)
{
    RHspriteRenderingInfo info;
    SBGeoBoundingBox2D source;
    SBGeoBoundingBox2D destination;
    unsigned long flags = (selected ? 0x100 : 0x200) | 1;
    if (m_14 != *(unsigned *)((char *)g_pEngine + 0x4a94) / 3)
    {
        m_14 = *(unsigned *)((char *)g_pEngine + 0x4a94) / 3;
        if (m_18)
        {
            if (++m_1a == 9)
            {
                m_1a = 8;
                m_18 = 0;
            }
        }
        else if (m_1a == 0)
            m_18 = 1;
        else
            --m_1a;
    }
    RHPositionInterface *position = (RHPositionInterface *)((char *)m_4 + 4);
    position->m_20 = point;
    ((RHMobileUnk00607da0 *)&position->m_c0)->FUN_00607da0(
        (const RHMobileUnk00607da0 &)position->Box().FUN_006090d0(SBGeoVector2D(point)));
    position->m_4 = 2;
    m_4->ComputePositionSprite();
    m_4->m_da = layer;
    if (m_4->FUN_005b9b60(view, scale))
    {
        info.m_masks = 1;
        static_cast<RHPositionInterface &>(*m_4).ComputePositionMap();
        unsigned short frame = m_1a;
        RHSprite *sprite = m_4;
        info.m_surface = m_10;
        sprite->FUN_005bd450();
        sprite->m_184 = selected != 0;
        sprite->m_186 = frame;
        m_4->CreateTargetSprite(info);
        if (m_4->FUN_005ba130(view, scale, source, destination))
            ((SBDrawManager *)m_8)->BlitAlpha(m_10, &source, surface, &destination, m_10, flags);
    }
    return false;
}

void EmitRHSelectionMarkDrawAt(RHUnk00581c40 *mark, const SBGeoBoundingBox2D &view, const SBGeoPoint2D &point)
{
    mark->FUN_00581ee0(0, 0.0f, view, point, 0, false, false);
}
