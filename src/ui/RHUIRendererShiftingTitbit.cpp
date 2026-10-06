#include "RHUIRendererShiftingTitbit.h"

// deferred: unannotated pending reccmp #534; 99.56% annotated, sole difference is the call to 0x005cbe60.
bool RHUIRendererShiftingTitbit::Render(unsigned id)
{
    if (RHUIRendererShifting::Render(id) && m_54 != unsigned(-1) && m_58)
    {
        SBGeoBoundingBox2D box;
        SBGeoVector2D bankSize;
        box = TitbitBox + SBGeoVector2D((float)TitbitWord50, 0.0f);
        box += SBGeoVector2D(4.0f, 4.0f);
        TitbitResource->FUN_006006f0(0x10, bankSize);
        unsigned surface;
        if (TitbitResource->GetSurfaceForResource(0x10, m_54, surface) != 1)
        {
            SBAssert(0,
                     // STRING: GAME 0x006b8d90
                     "P:\\Robin Hood\\RHUIRendererShiftingTitbit.cpp", 0x25,
                     "Unable to retrieve a resource for the bitmap renderer");
            return false;
        }
        SBGeoVector2D surfaceSize;
        RHUnk005ef320 *draw = g_unk0x6c11d0;
        draw->FUN_005e57e0(surface, surfaceSize);
        box += 0.5f * (bankSize + -surfaceSize);
        box.UnkSecondPoint(box.m_p0 + surfaceSize);
        ((SBDrawManager *)draw)->BlitAlphaKeying(surface, 0, TitbitBlitArg, &box, TitbitWord4c, TitbitWord4e, 1);
        if (m_59)
        {
            box += SBGeoVector2D(3.0f, 0.0f);
            ((SBDrawManager *)draw)->BlitAlphaKeying(surface, 0, TitbitBlitArg, &box, TitbitWord4c, TitbitWord4e, 1);
        }
    }
    return true;
}

void RHUIRendererShiftingTitbit::Emit()
{
    Render(0);
}
