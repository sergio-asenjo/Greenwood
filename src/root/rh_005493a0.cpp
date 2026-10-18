#include "SBGeoPoint2D.h"

class SBGeoVector2D : public SBGeoPoint2D
{
public:
    SBGeoVector2D(float, float);
    ~SBGeoVector2D() {}
};

// GLOBAL: GAME 0x006c0c58
float g_unk0x006c0c58[2];

// FUNCTION: GAME 0x005493a0
void FUN_005493a0()
{
    ((SBGeoVector2D *)g_unk0x006c0c58)->SBGeoVector2D::SBGeoVector2D(14.0f, 24.0f);
}
