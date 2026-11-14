#ifndef RHUNKMASKOBSTACLETABLE_H
#define RHUNKMASKOBSTACLETABLE_H

#include "RHFastFindPointerArray.h"

class RHUnkMaskObstacleTable
{
public:
    void InsertObstacle(void *const &area)
    {
        m_obstacles.InsertSingleLast(area);
    }
    char m_00[0x40];
    RHFastFindPointerArray m_sectors;
    RHFastFindPointerArray m_obstacles;
    char m_80[0x40];
};

#endif
