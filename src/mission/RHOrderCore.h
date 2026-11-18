#ifndef RHORDERCORE_H
#define RHORDERCORE_H

#include "SB.h"
#include "Decomp.h"
#ifndef SBGEO_POINT2D_VIEW
#include "SBGeoPoint2D.h"
#endif
#ifndef SBGEO_VECTOR2D_VIEW
#include "SBGeoVector2D.h"
#endif
#include "RHUnk00613e90.h"

class SBFile;
class RHElement;
class RHSequenceElement;

// VTABLE: GAME 0x00679bc8
// SIZE 0x3c
class RHOrder
{
public:
    RHOrder();
    RHOrder(RHOrder &);
    virtual ~RHOrder();
    bool Serialize(SBFile &file, RHSequenceElement *element);
    static bool SerializeStaticStuff(SBFile &file);
    void Emit(SBFile &file);
    void FUN_0054e730();
    union
    {
        undefined4 m_4;
        float m_float04;
    };
    RHUnk00613e90 m_08;
    SBGeoPoint2D m_14;
    SBGeoVector2D m_1c;
    int m_24;
    undefined m_28;
    undefined m_29;
    undefined m_2a;
    undefined m_2b;
    undefined m_2c;
    undefined m_2d;
    char m_2e;
    char m_2f;
    RHElement *m_30;
    int m_34;
    RHSequenceElement *m_38;
};

#endif
