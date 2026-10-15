#ifndef RHSEQUENCEELEMENTSERIALIZATION_H
#define RHSEQUENCEELEMENTSERIALIZATION_H

#include "SB.h"
#include "RHEngine.h"

class RHSequenceElement
{
public:
    RHSequenceElement();
    ~RHSequenceElement();
    virtual void Dummy1();
    virtual void Dummy2();
    virtual bool Serialize(SBFile &file, bool pointers);
    bool FUN_00584ef0(SBFile &file, bool pointers);
    char m_04[0x60];
};

class RHSword
{
public:
    static bool SerializePointer(SBFile &file, RHSword *&value);
};

class SBGeoPoint2D
{
public:
    SBGeoPoint2D();
    ~SBGeoPoint2D();
    SBGeoPoint2D &operator=(const SBGeoPoint2D &other);
    bool Serialize(SBFile &file);
    float m_x;
    float m_y;
};

class RHUnkPathGeometry
{
public:
    bool Unk004fbec0(SBFile &file, void *&value);
    bool Unk004fc030(SBFile &file, void *&value);
};

class RHFastFindGrid
{
public:
    bool SerializeLinePointer(SBFile &file, void *&value);
};

#endif
