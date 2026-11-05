#ifndef RHSEQUENCEGENERICCONSTRUCTION_H
#define RHSEQUENCEGENERICCONSTRUCTION_H

#include "RHSequenceGenericCalls.h"
#include "RHGenericMap.h"

class SBGeoPoint2D;

// VTABLE: GAME 0x00679d5c
class RHUnk005866a0 : public RHUnk00584d60
{
public:
    RHUnk005866a0();
    RHUnk005866a0(unsigned short level, int command, void *actor);
    ~RHUnk005866a0();
    virtual void *FUN_00584d40(unsigned int flags);
    void Unk00586ed0(int property, int value);
    void Unk00586fd0(int property, float value);
    void Unk00587010(int property, const SBGeoPoint2D &value);
    void Unk00586e00(int property, bool value);
    void Unk00586e90(int property, unsigned short value);
    RHGenericMap m_64;
};

#endif
