#ifndef RHJUMPSECTOR_H
#define RHJUMPSECTOR_H

#include "RHFastFindPointerArray.h"

class SBFile;
class SBGeoPoint2D;
class RHElementActor;
class RHUnk0051e1e0;

class RHUnk0051e5e0
{
public:
    RHUnk0051e5e0();
    ~RHUnk0051e5e0();
    void *FUN_0051e630(unsigned flags);
    int Unk0051e700(SBFile &file);
    RHUnk0051e1e0 *FUN_0051e790(RHElementActor *actor, const SBGeoPoint2D &first,
        const SBGeoPoint2D &second, bool mode);
    bool FUN_0051e7b0(unsigned int index, RHElementActor *actor, bool mode);
    void Unk0051e800();
    float FUN_0051e890(RHUnk0051e1e0 *line);
    RHUnk0051e1e0 *FUN_0051e8e0(RHElementActor *actor, const SBGeoPoint2D &first,
        const SBGeoPoint2D &second, bool mode);
    char m_00[0x36];
    unsigned short m_layer;
    char m_38[0x20];
    RHFastFindPointerArray m_lines;
    char m_78[0x28];
};

#endif
