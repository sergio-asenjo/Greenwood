#include "SBGeoPoint2D.h"

class SBGeoVector2D : public SBGeoPoint2D
{
public:
    SBGeoVector2D(float, float);
    ~SBGeoVector2D() {}
};

// GLOBAL: GAME 0x006c0bb0
float g_unk0x006c0bb0[2];

// FUNCTION: GAME 0x0051d740
void FUN_0051d740()
{
    ((SBGeoVector2D *)g_unk0x006c0bb0)->SBGeoVector2D::SBGeoVector2D(25.0f, 10.0f);
}
