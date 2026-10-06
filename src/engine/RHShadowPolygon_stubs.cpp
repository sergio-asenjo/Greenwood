#include "RHShadowPolygon.h"

void RHEngine::FUN_004c9d20(void *) {}
void RHShadowPolygon::FUN_0058d990() {}
void RHShadowPolygon::FUN_0058ec60() {}
void RHShadowPolygon::FUN_0058ffa0(RHUnk00597a70 *) {}
void RHShadowPolygon::FUN_00590c90(RHUnk00597a70 *) {}
void RHShadowPolygon::FUN_00592080(RHUnk00597a70 *) {}
void RHShadowPolygon::FUN_005934b0(RHUnk00597a70 *) {}
void RHShadowPolygon::FUN_00594bf0(const SBGeoBoundingBox2D &, float, RHElementActor *, SBGeoPoint3D &, RHviewParameters &) {}
void RHShadowPolygon::FUN_00595020() {}
void RHShadowPolygon::FUN_005959e0() {}
void RHShadowPolygon::FUN_005971f0() {}
void RHShadowPolygon::FUN_005973f0() {}
void RHShadowPolygon::FUN_00597910() {}
bool RHShadowPolygon::FUN_00597a70(RHUnk00597a70 *) { return false; }

void FUN_005c9010(RHUnk005c9010Iterator &current, int distance, std::bidirectional_iterator_tag)
{
    for (; 0 < distance; --distance)
        ++current;
    for (; distance < 0; ++distance)
        --current;
}
