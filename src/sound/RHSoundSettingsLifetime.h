#ifndef RHSOUNDSETTINGSLIFETIME_H
#define RHSOUNDSETTINGSLIFETIME_H

#include "RHSoundSettings.h"

inline RHSoundSettings::~RHSoundSettings()
{
    ((SBGeoPoint2D *)m_04)->~SBGeoPoint2D();
}

#endif
