#ifndef RHELEMENTFXCORE_H
#define RHELEMENTFXCORE_H

#include "Decomp.h"
#include "SBGeoBoundingBox2DCore.h"
#include "SBFile.h"
#include "RHElementCore.h"
#include "sbgeo_00610600.h"

// VTABLE: GAME 0x006784a0
// SIZE 0xfc
class RHElementFX : public RHElement
{
public:
    RHElementFX(int type);
    virtual ~RHElementFX();
    virtual bool FUN_004b23c0(const void *first, void *second, int third);
    virtual void *FUN_004b29c0(void *value);
    virtual bool FUN_004b26a0(const SBGeoPoint2D *first, unsigned short second, RHElementActorPC *selectedPC);
    virtual void *Refresh(unsigned long surface, float value, const SBGeoBoundingBox2D &box, unsigned long flags);
    virtual char FUN_004b9f40();
    virtual void v14(SBFile &file);
    virtual void InitializeFromMissionStream(SBFile &file);
    virtual bool Serialize(SBFile &file);
    void FUN_004a9990();
    void RestoreBackground();
    void InitializeBackgroundRestoration();
    bool IsElementBehind(RHElement *element);
    bool FUN_004aa420(SBGeoBoundingBox2D *clip, float scale, SBGeoBoundingBox2D *first,
                      SBGeoBoundingBox2D *second);
    int FUN_004aa930();
    void Emit(SBFile &file);
    int m_a8;
    void *m_ac;
    int m_b0;
    SBGeoBoundingBox2D m_b4;
    char m_c8;
    unsigned long m_cc;
    char m_d0;
    RHMobileUnk00611360 m_d4;
    float m_f8;
};

#endif
