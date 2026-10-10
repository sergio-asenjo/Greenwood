#ifndef RHSOUNDSOURCE_H
#define RHSOUNDSOURCE_H

#include "RHSoundSourceManager.h"

class RHUnk005b4700
{
public:
    void FUN_005b4700(int count);
    SBGeoPoint2D &operator[](unsigned short index)
    {
        SBGeoPoint2D *first = m_first;
        return first[index];
    }
    int m_00;
    SBGeoPoint2D *m_first;
    SBGeoPoint2D *m_last;
    SBGeoPoint2D *m_end;
};

void RHSerializeName(SBFile &file, const char *name);

#endif
