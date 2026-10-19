#include "SBGeoPoint2D.h"

class SBGeoVector2D : public SBGeoPoint2D
{
public:
    SBGeoVector2D(float, float);
    ~SBGeoVector2D() {}
    SBGeoVector2D(const SBGeoVector2D &other);
    SBGeoVector2D &operator=(const SBGeoVector2D &other);
};

extern float g_unk0x006c0aa8[2];

// FUNCTION: GAME 0x004e7450
void FUN_004e7450()
{
    ((SBGeoVector2D *)g_unk0x006c0aa8)->SBGeoVector2D::SBGeoVector2D(64.0f, 64.0f);
}
