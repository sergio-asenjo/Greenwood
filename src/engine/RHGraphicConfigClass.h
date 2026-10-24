#ifndef RHGRAPHICCONFIGCLASS_H
#define RHGRAPHICCONFIGCLASS_H

#if !defined(SBGEO_VECTOR2D_VIEW) && !defined(SBGEOVECTOR2D_H)
#include "SBGeoVector2D.h"
#endif

class SBFile;

class RHGraphicConfig
{
public:
    RHGraphicConfig();
    RHGraphicConfig(const RHGraphicConfig &other);
    bool Serialize(SBFile &file);

    void Emit(SBFile &file);

    char m_0;             // [0x0]
    char m_1;             // [0x1]
    char m_2;             // [0x2]
    char m_3;             // [0x3]
    SBGeoVector2D m_point; // [0x4]
};

#endif
