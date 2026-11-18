#ifndef SB_DRAW_MANAGER_H
#define SB_DRAW_MANAGER_H

#include <utility>
#include <string>
#include "SBDrawManagerCore.h"

class SBGeoVector2D;
class RHUnk00613e90;
class RHMobileUnk00607da0;

class SBDrawUnk005e8450
{
public:
    bool FUN_005e7710(unsigned short *, unsigned short *, unsigned short *, unsigned,
        unsigned, unsigned, unsigned, unsigned);
    bool FUN_005e8110(unsigned short *, unsigned short *, unsigned short *, unsigned,
        unsigned, unsigned, unsigned, unsigned, unsigned short);
    bool FUN_005e7880(void *, void *, void *, int, int, int, int, int, unsigned short);
    bool FUN_005e78c0(unsigned short *, unsigned short *, unsigned short *, unsigned, unsigned, unsigned, unsigned, unsigned);
    bool FUN_005e7a30(unsigned short *, unsigned short *, unsigned short *, unsigned, unsigned, unsigned, unsigned, unsigned, unsigned short);
    bool FUN_005e7bc0(unsigned short *, unsigned short *, unsigned short *, unsigned, unsigned, unsigned, unsigned, unsigned);
    bool FUN_005e7de0(unsigned short *, unsigned short *, unsigned short *, unsigned, unsigned, unsigned, unsigned, unsigned);
    bool FUN_005e7fa0(unsigned short *, unsigned short *, unsigned short *, unsigned, unsigned, unsigned, unsigned, unsigned);
    bool FUN_005e82a0(unsigned short *, unsigned short *, unsigned short *, unsigned, unsigned, unsigned, unsigned, unsigned);
    bool FUN_005e7d30(void *, void *, void *, int, int, int, int, int, unsigned short);
    bool FUN_005e7d70(void *, void *, void *, int, int, int, int, int, unsigned short);
    bool FUN_005e7da0(void *, void *, void *, int, int, int, int, int, unsigned short);
    bool FUN_005e7f60(void *, void *, void *, int, int, int, int, int, unsigned short);
    bool FUN_005e8410(void *, void *, void *, int, int, int, int, int, unsigned short);
    bool FUN_005e8450(void *source, void *destination, void *alpha, int width,
        int height, int sourceStride, int destinationStride, int arg8, unsigned short arg9);
    bool FUN_005e84a0(void *, void *, void *, int, int, int, int, int, unsigned short);
    bool FUN_005e84e0(void *source, void *destination, void *alpha, unsigned short arg4,
        int width, int height, int sourceStride, int destinationStride,
        float stretchX, float stretchY);
    bool FUN_005e85b0(void *source, void *destination, void *alpha, unsigned short arg4,
        int width, int height, int sourceStride, int destinationStride,
        float stretchX, float stretchY);
    bool FUN_005e8670(void *source, void *destination, void *alpha, unsigned short arg4,
        int width, int height, int sourceStride, int destinationStride,
        float stretchX, float stretchY);
    bool FUN_005e8740(unsigned short *, unsigned short *, unsigned short *, unsigned,
        unsigned, unsigned, unsigned, float, float);
    bool FUN_005e8b10(unsigned short *, unsigned short *, unsigned short *, unsigned short,
        unsigned, unsigned, unsigned, unsigned, float, float);
    bool FUN_005e8f20(unsigned short *, unsigned short *, unsigned short *, unsigned,
        unsigned, unsigned, unsigned, float, float);
    bool FUN_005e93c0(unsigned short *, unsigned short *, unsigned short *, unsigned,
        unsigned, unsigned, unsigned, float, float);
    bool FUN_005e99f0(unsigned short *, unsigned short *, unsigned short *, unsigned,
        unsigned, unsigned, unsigned, float, float);
    bool FUN_005e9dc0(unsigned short *, unsigned short *, unsigned short *, unsigned short,
        unsigned, unsigned, unsigned, unsigned, float, float);
    bool FUN_005ea1d0(unsigned short *, unsigned short *, unsigned short *, unsigned,
        unsigned, unsigned, unsigned, float, float);
    bool FUN_005ea670(unsigned short *, unsigned short *, unsigned short *, unsigned,
        unsigned, unsigned, unsigned, float, float);
    bool FUN_005eb450(unsigned short *, unsigned short *, unsigned short, unsigned,
        unsigned, unsigned, unsigned, float, float);
    bool FUN_005eb800(unsigned short *, unsigned short *, unsigned short, unsigned,
        unsigned, unsigned, unsigned, float, float);
    bool FUN_005e92f0(void *source, void *destination, void *alpha, unsigned short arg4,
        int width, int height, int sourceStride, int destinationStride,
        float stretchX, float stretchY);
    bool FUN_005e9790(void *source, void *destination, void *alpha, unsigned short arg4,
        int width, int height, int sourceStride, int destinationStride,
        float stretchX, float stretchY);
    bool FUN_005e9860(void *source, void *destination, void *alpha, unsigned short arg4,
        int width, int height, int sourceStride, int destinationStride,
        float stretchX, float stretchY);
    bool FUN_005e9920(void *source, void *destination, void *alpha, unsigned short arg4,
        int width, int height, int sourceStride, int destinationStride,
        float stretchX, float stretchY);
    bool FUN_005ea5a0(void *source, void *destination, void *alpha, unsigned short arg4,
        int width, int height, int sourceStride, int destinationStride,
        float stretchX, float stretchY);
    bool FUN_005ec230(void *, void *, int, int, int, int, float, float, unsigned short, unsigned short);
    bool FUN_005ec320(void *, void *, int, int, int, int, float, float, unsigned short, unsigned short);
    bool FUN_005ec410(void *, void *, int, int, int, int, float, float, unsigned short, unsigned short);
    bool FUN_005ec500(void *, void *, int, int, int, int, float, float, unsigned short, unsigned short);
};

#include "SBDrawUnk005e5ec0.h"

void FUN_006220ec(void *, void *, int, int, int, int, unsigned, unsigned);
void FUN_00622028(void *, void *, int, int, int, int, unsigned, unsigned);
void FUN_006222bc(void *, void *, int, int, int, int, unsigned, unsigned);
void FUN_00622550(void *, void *, int, int, int, int, unsigned, unsigned);
void FUN_00623598(void *, void *, int, int, int, int, unsigned, unsigned);
void FUN_006221e4(void *, void *, int, int, int, int, unsigned, unsigned);
void FUN_00622380(void *, void *, int, int, int, int, unsigned, unsigned);
void FUN_00622478(void *, void *, int, int, int, int, unsigned, unsigned);
void FUN_0062261c(void *, void *, int, int, int, int, unsigned, unsigned);
void FUN_00622720(void *, void *, int, int, int, int, unsigned, unsigned);
void FUN_00623668(void *, void *, int, int, int, int, unsigned, unsigned);
void FUN_0062376c(void *, void *, int, int, int, int, unsigned, unsigned);

void FUN_00622800(void *, void *, void *, int, int, int, int, int);
void FUN_00622924(void *, void *, void *, int, int, int, int, int);
void FUN_00622a7c(void *, void *, void *, int, int, int, int, int);
void FUN_00622bc0(void *, void *, void *, int, int, int, int, int);
void FUN_00622ca0(void *, void *, void *, int, int, int, int, int);
void FUN_00622db4(void *, void *, void *, int, int, int, int, int);
void FUN_00622eb4(void *, void *, void *, int, int, int, int, int);
void FUN_00622fd4(void *, void *, void *, int, int, int, int, int);
void FUN_00623128(void *, void *, void *, int, int, int, int, int);
void FUN_00623268(void *, void *, int, int, int, int);
void FUN_00623360(void *, void *, int, int, int, int);
void FUN_0062348c(void *, void *, int, int, int, int);
void FUN_00623850(void *, void *, void *, int, int, int, int, int);
void FUN_00623978(void *, void *, void *, int, int, int, int, int);
void FUN_00623ad4(void *, void *, void *, int, int, int, int, int);
void FUN_00623c1c(void *, void *, void *, int, int, int, int, int);
void FUN_00623cfc(void *, void *, void *, int, int, int, int, int);
void FUN_00623e10(void *, void *, void *, int, int, int, int, int);
void FUN_00623f10(void *, void *, void *, int, int, int, int, int);
void FUN_00624030(void *, void *, void *, int, int, int, int, int);
void FUN_00624184(void *, void *, void *, int, int, int, int, int);
void FUN_006242c4(void *, void *, int, int, int, int);
void FUN_006243c0(void *, void *, int, int, int, int);
void FUN_006244ec(void *, void *, int, int, int, int);

#endif
