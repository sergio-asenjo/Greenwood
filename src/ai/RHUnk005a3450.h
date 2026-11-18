#ifndef RHUNK005A3450_H
#define RHUNK005A3450_H

#include "sb3dstuff.h"
#include "RHUnkSectorPoints.h"
#include "RHFastFindSightStorage.h"

class RHFastFindPointerArray;

class RHUnk005a3450
{
public:
    RHUnk005a3450();
    RHUnk005a3450(int type);
    ~RHUnk005a3450();
    int Unk005a3810(SBFile &file, RHFastFindPointerArray &materials);
    void *Unk005a5780();
    unsigned short ProjectionFlag() { return m_flags >> 2; }
    RHUnk005df860 &FirstPlane() { return m_firstPlane; }
    RHUnk005df860 &SecondPlane() { return m_secondPlane; }
    SBGeoBoundingBox2D &Bounds() { return m_bounds; }
    SBGeoBoundingBox2D &OtherBounds() { return m_otherBounds; }
    void SetLayer(unsigned short layer) { m_layer = layer; }
    void SetSector(unsigned short sector) { m_sector = sector; }
    unsigned long m_flags;
    unsigned long m_id;
    bool m_enabled;
    char m_09[3];
    RHUnk005dfd00 m_box;
    SBGeoBoundingBox2D m_bounds;
    SBGeoBoundingBox2D m_otherBounds;
    RHFastFindSightList<RHFastFindSightVertex> m_vertices;
    RHUnkSectorPoints m_polygon;
    RHUnk005df860 m_firstPlane;
    RHUnk005df860 m_secondPlane;
    char m_158[2];
    unsigned short m_layer;
    unsigned short m_sector;
    char m_15e[2];
    float m_160;
    float m_164;
    char m_168[8];
    RHFastFindSightList<void *> m_materials;
    void *m_motionArea;
    char m_198[0xe];
    bool m_active;
    char m_1a7;
};

#endif
