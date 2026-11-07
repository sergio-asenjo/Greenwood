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

// GLOBAL: GAME 0x006c0bb0
SBGeoVector2D RHInfoPopupStaticStorage::vPositionOffset(25.0f, 10.0f);

// SYNTHETIC: GAME 0x0051d740
// $E3

// SYNTHETIC: GAME 0x0051d770
// $E4
