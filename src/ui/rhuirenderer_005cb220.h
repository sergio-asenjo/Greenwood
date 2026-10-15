#ifndef RHUIRENDERER_005CB220_H
#define RHUIRENDERER_005CB220_H

#include "Decomp.h"
#include "RHGameRenderer005cb220.h"
#include "SBUIRenderer.h"

class RHUnk005fc3b0 : public SBGeoPoint2D
{
public:
    RHUnk005fc3b0();
};

class RHUnk005ef320
{
public:
    void FUN_005e57e0(unsigned surface, SBGeoVector2D &size);
    bool FUN_005e6440(unsigned long surface, int source, unsigned long target, SBGeoBoundingBox2D *box, int flags);
};

#endif
