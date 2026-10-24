#ifndef RHACTORGRIDCALLS_H
#define RHACTORGRIDCALLS_H

class SBGeoPoint2D;
class RHElementActor;

class RHActorGridCalls
{
public:
    short FUN_004e8fc0(const SBGeoPoint2D &point, const SBGeoPoint2D &origin, short layer, void *&area);
    unsigned short FUN_004e9800(const SBGeoPoint2D &point, void *&area, int &layer);
    bool FUN_004f5e50(SBGeoPoint2D &point, const SBGeoPoint2D &other, int layer);
    bool FUN_004f9a80(void *sectors, RHElementActor *actor, const SBGeoPoint2D &start, void *startArea,
        unsigned short startLayer, const SBGeoPoint2D &end, void *endArea, unsigned endLayer, int mode);
};

#endif
