#ifndef RHVIEWPARAMETERS_H
#define RHVIEWPARAMETERS_H

#ifndef SBGEO_POINT2D_VIEW
#include "SBGeoPoint2D.h"
#endif
#include "SBGeoVector2D.h"

class RHviewParameters
{
public:
    char m_00;
    char m_01[7];
    char m_viewStatus;
    char m_09;
    unsigned short m_0a;
    char m_0c[0x14];
    float m_20;
    float m_24;
    char m_28[0x20];
    SBGeoVector2D m_48;
    SBGeoVector2D m_50;
    SBGeoVector2D m_58;
    SBGeoPoint2D m_60;
    char m_68[0x10];
    unsigned short m_78;
    char m_7a[0x16];
};

DECOMP_SIZE_ASSERT(RHviewParameters, 0x90)

#endif
