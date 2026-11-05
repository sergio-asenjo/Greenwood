#ifndef RHWAYPOINT_H
#define RHWAYPOINT_H

#include "SB.h"
#include "Decomp.h"
#include "RHUnkWaypointRef.h"
#include "RHUnk00571160Position.h"

class RHWaypoint
{
public:
    unsigned int LoadDataFromFile(SBFile &file);
    void Emit(SBFile &file);
    RHUnk00571160Position Position() const
    {
        RHUnk00571160Position position = {(float)m_64, (float)m_66, m_68, (short)m_6c};
        return position;
    }

    undefined m_pad0[0x60];
    RHUnkWaypointRef m_60;
    short m_64;
    short m_66;
    void *m_68;
    unsigned short m_6c;
    char m_6e;
    char m_pad6f;
    unsigned short m_70;
    char m_pad72[2];
    void *m_74;
    char *m_78;
};

#endif
