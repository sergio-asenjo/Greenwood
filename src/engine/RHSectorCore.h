#ifndef RHSECTORCORE_H
#define RHSECTORCORE_H

#include "Decomp.h"
#include "RHUnk0060c2c0.h"
#ifndef SBGEO_BOUNDINGBOX2D_VIEW
#include "SBGeoBoundingBox2DCore.h"
#endif

class SBFile;

// VTABLE: GAME 0x00679bf4
// SIZE 0x58
class RHSector : public RHUnk0060c2c0
{
public:
    RHSector();
    RHSector(int type);
    virtual ~RHSector();
    virtual int Unk0057cd60(SBFile &file, bool mode);
    virtual void FUN_0057d390(void *draw, unsigned long surface, const SBGeoBoundingBox2D &box, float scale, unsigned short layer);
    virtual bool Serialize(SBFile &file);
    void DisplayAlpha(unsigned long color, unsigned long alpha, bool mode);
    int m_30;
    bool m_34;
    unsigned short m_36;
    unsigned short m_38;
    SBGeoBoundingBox2D m_3c;
    undefined m_50[8];
};

#endif
