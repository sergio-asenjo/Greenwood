#ifndef RHSOUNDACTORCALLS_H
#define RHSOUNDACTORCALLS_H

class RHArtificialIntelligenceActor;
class SBGeoPoint2D;

class RHArtificialIntelligenceSoundCalls
{
public:
    bool Unk005a8d10(RHArtificialIntelligenceActor *actor);
    void Unk005a8b70(int category, void *profile, unsigned short remark, long variant, SBGeoPoint2D *position, RHArtificialIntelligenceActor *actor);
};

#endif
