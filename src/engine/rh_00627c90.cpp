#include "RHElementMobile.h"

class RHUnk00627c90
{
public:
    bool FUN_00627c90(const SBGeoPoint2D &first, const SBGeoPoint2D &second);
    char m_0[0x88];
};

// FUNCTION: GAME 0x00627c90
bool RHUnk00627c90::FUN_00627c90(const SBGeoPoint2D &first, const SBGeoPoint2D &second)
{
    *(SBGeoPoint2D *)((char *)this + 0x80) = first;
    ((RHUnk005fc3b0 *)((char *)this + 0x88))->FUN_005fc430(second);
    return true;
}
