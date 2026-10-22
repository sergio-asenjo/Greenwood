#ifndef RHACTORSEQUENCESTORAGE_H
#define RHACTORSEQUENCESTORAGE_H

#include "Decomp.h"

#ifndef SBGEO_BOUNDINGBOX2D_VIEW
#include "SBGeoBoundingBox2DCore.h"
#endif

class RHUnk0045aaf0
{
public:
    RHUnk0045aaf0();
    ~RHUnk0045aaf0();
    bool FUN_0045abc0(unsigned short value, int first, int second);
    bool FUN_0045abf0(unsigned short value, const SBGeoPoint2D &point, int third, int fourth);
    undefined4 m_0;
    undefined4 m_4;
    undefined m_8[8];
    SBGeoBoundingBox2D m_10;
    unsigned char m_24;
    undefined m_25[7];
    unsigned short m_2c;
    undefined m_2e[2];
    int m_30;
    SBGeoPoint2D m_34;
};

#endif
