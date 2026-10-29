#include "sbgeo_0060ff30.h"
#include "RHUnk0060bd40.h"
#include "RHGameInputTranslator.h"

// FUNCTION: GAME 0x0060fdb0
void RHUnk0060fbf0::FUN_0060fdb0()
{
    FUN_0060fce0();
    m_0 = 0;
}

// FUNCTION: GAME 0x0060fce0
void RHUnk0060fbf0::FUN_0060fce0()
{
    switch (m_0)
    {
    case 1:
        delete (SBGeoPoint2D *)m_8;
        break;
    case 4:
        {
            RHGameInputSegment *value = (RHGameInputSegment *)m_8;
            if (value)
            {
                value->FUN_004611c0();
                operator delete(value);
            }
        }
        break;
    case 3:
        delete (RHMobileUnk0060a820 *)m_8;
        break;
    case 2:
        delete (RHMobileUnk006100e0 *)m_8;
        break;
    case 5:
        delete (SBGeoPolyLine2DList *)m_8;
        break;
    case 6:
        delete (RHUnk0060bd40 *)m_8;
        break;
    }
}
