#ifndef RHUNKWAYPOINTREF_H
#define RHUNKWAYPOINTREF_H

class RHWaypoint;
class RHElementMobile;

// SIZE 0x04
class RHUnkWaypointRef
{
public:
    RHWaypoint *m_0; // +0x00
    int Unk00408660();
    int Unk00408750(RHElementMobile *mobile);
};

#endif
