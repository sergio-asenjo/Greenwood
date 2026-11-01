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
    typedef unsigned long (RHUnkFXDraw::*CreateSurface)(unsigned short, unsigned short, int, bool);
    m_10 = (((RHUnkFXDraw *)m_8)->*
        reinterpret_cast<CreateSurface>(&RHUnkFXDraw::Unk005e4ed0))(
        m_4->FUN_005bdd50(), m_4->FUN_005bdd70(), 0, false);
    size.FUN_005fc430(FUN_005fc580(SBGeoVector2D((float)m_4->FUN_005bdd50(),
        (float)m_4->FUN_005bdd70()), 0.5f));
    m_4->AssignBox(SBGeoBoundingBox2D(-size, size));
    m_4->AssignOffset(size);
    return 0;
}
