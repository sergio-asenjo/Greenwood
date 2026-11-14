#ifndef RHELEMENTCORE_H
#define RHELEMENTCORE_H

#include "SB.h"
#include "Decomp.h"

#ifndef SBGEO_POINT2D_VIEW
#include "SBGeoPoint2D.h"
#endif

class RHElevationLine;
class SBGeoVector2D;
class SBGeoBoundingBox2D;

#include "RHUnk005df510.h"
#include "RHUnk00613e90.h"
#include "RHActorSequenceStorage.h"

class RHSprite;
class RHUnk005069a0;

// VTABLE: GAME 0x006776a0
// SIZE 0xa8
class RHElement
{
public:
    RHElement(int type, char flag);
    virtual ~RHElement();
    virtual char v1() const { return 0; }
    virtual char v2() const { return 0; }
    virtual char v3() const { return 0; }
    virtual int FUN_00462190() const;
    virtual SBGeoVector2D FUN_004621a0() const;
    virtual bool FUN_004b23c0(void *first, void *second, void *third) = 0;
    virtual void *FUN_004b29c0(void *value) = 0;
    virtual bool FUN_004b26a0(int first, int second, int third) = 0;
    virtual void *Refresh(unsigned long surface, float value, const SBGeoBoundingBox2D &box, unsigned long flags) = 0;
    virtual char v10() = 0;
    virtual float FUN_004621c0() const;
    virtual void FUN_004621d0(RHUnk005df510 &point) const;
    virtual void FUN_004621f0();
    virtual void v14(SBFile &file) = 0;
    virtual void v15(unsigned value) = 0;
    virtual bool Serialize(SBFile &file);
    virtual void FUN_00462940(int action);
    virtual char FUN_00462200() const;
    virtual void v19(unsigned value) {}
    virtual char FUN_00462210(void *value);
    virtual void v21(unsigned value) {}
    virtual char v22(void *value) { return 0; }
    virtual void v23(unsigned value) {}
    virtual char v24() const { return 0; }
    virtual void v25(unsigned first, unsigned second, unsigned third) {}
    void *FUN_004622d0() const;
    int FUN_004671b0() const;
    RHUnk005069a0 *FUN_004a1af0();
    void CrossElevationLine(RHElevationLine *line);
    void Emit(SBFile &file);

    int m_04;
    char m_08;
    undefined m_09[3];
    int m_0c;
    short m_10;
    char m_12;
    undefined m_13;
    RHUnk0045aaf0 m_14;
    RHSprite *m_50;
    int m_54;
    int m_58;
    void *m_5c;
    void *m_60;
    void *m_64;
    void *m_68;
    undefined m_6c[4];
    char m_70;
    char m_71;
    undefined m_72[2];
    RHUnk00613e90 m_74;
    SBGeoPoint2D m_80;
    char m_88;
    undefined m_89;
    unsigned short m_8a;
    short m_8c;
    char m_8e;
    undefined m_8f;
    short m_90;
    char m_92;
    undefined m_93;
    union
    {
        undefined m_94[10];
        struct
        {
            unsigned short m_94w;
            unsigned short m_96;
            unsigned short m_98;
            unsigned short m_9a;
            unsigned short m_9c;
        };
    };
    undefined m_9e[2];
    int m_a0;
    short m_a4;
    char m_a6;
    undefined m_a7;
};

void RHSerializeName(SBFile &file, const char *name);

#endif
