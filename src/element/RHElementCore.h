#ifndef RHELEMENTCORE_H
#define RHELEMENTCORE_H

#include "SB.h"
#include "Decomp.h"

#ifndef SBGEO_POINT2D_VIEW
#include "SBGeoPoint2D.h"
#endif

class RHUnk005b5ed0;
class RHElevationLine;
class SBGeoVector2D;

class RHUnk005df510
{
public:
    int m_0;
    int m_4;
    int m_8;
    bool Serialize(SBFile &file);
};

class RHElement
{
public:
    virtual bool Serialize(SBFile &file);
    int FUN_00462190() const;
    SBGeoVector2D FUN_004621a0() const;
    void FUN_004621d0(RHUnk005df510 &point) const;
    void FUN_004621f0();
    char FUN_00462200() const;
    char FUN_00462210(void *value);
    void *FUN_004622d0() const;
    void CrossElevationLine(RHElevationLine *line);
    void Emit(SBFile &file);

    undefined m_04[4];
    char m_08;
    undefined m_09[3];
    int m_0c;
    short m_10;
    char m_12;
    undefined m_13[0x3d];
    RHUnk005b5ed0 *m_50;
    undefined m_54[0x1c];
    char m_70;
    char m_71;
    undefined m_72[2];
    RHUnk005df510 m_74;
    SBGeoPoint2D m_80;
    char m_88;
    undefined m_89;
    short m_8a;
    short m_8c;
    undefined m_8e[6];
    undefined m_94[10];
    undefined m_9e[2];
    int m_a0;
    short m_a4;
    char m_a6;
    undefined m_a7;
};

void RHSerializeName(SBFile &file, const char *name);

#endif
