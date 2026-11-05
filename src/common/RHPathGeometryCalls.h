#ifndef RHPATHGEOMETRYCALLS_H
#define RHPATHGEOMETRYCALLS_H

class SBFile;
class SBGeoPoint2D;

class RHUnkPathGeometry
{
public:
    bool Unk004f9170(const SBGeoPoint2D &a, const SBGeoPoint2D &b, unsigned short layer, void *radius);
    bool Unk004fbec0(SBFile &file, void *&value);
    bool Unk004fc030(SBFile &file, void *&value);
    bool Unk004fc180(SBFile &file, void *&value);
    bool Unk004fc2d0(SBFile &file, void *&value);
};

#endif
