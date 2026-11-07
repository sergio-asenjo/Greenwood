#include "SBGeoPoint2D.h"

class SBGeoVector2D : public SBGeoPoint2D
{
public:
    SBGeoVector2D(float, float);
    ~SBGeoVector2D();
    SBGeoVector2D(const SBGeoVector2D &other);
    SBGeoVector2D &operator=(const SBGeoVector2D &other);
};

#include "RHGeoStaticStorage.h"

// GLOBAL: GAME 0x006c0aa8
SBGeoVector2D RHFastFindGridStaticStorage::mvGridsetDiagonal(64.0f, 64.0f);

// SYNTHETIC: GAME 0x004e7450
// $E3

// SYNTHETIC: GAME 0x004e7480
// $E4
