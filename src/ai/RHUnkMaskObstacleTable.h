#ifndef RHUNKMASKOBSTACLETABLE_H
#define RHUNKMASKOBSTACLETABLE_H

#include "RHFastFindPointerArray.h"
#include <vector>

class RHFastFindRecordStorage : public RHFastFindPointerArray
{
public:
    ~RHFastFindRecordStorage();
};

class RHFastFindClearedPointerRecord : public RHFastFindRecordStorage
{
public:
    ~RHFastFindClearedPointerRecord();
};

class RHFastFindLayerLines : public std::vector<int>
{
public:
    ~RHFastFindLayerLines()
    {
        typedef std::vector<int> Values;
        int *(Values::*eraseRange)(int *, int *) = &Values::erase;
        (this->*eraseRange)(begin(), end());
    }
    char m_10[0x10];
};

class RHUnk004fd7f0
{
public:
    ~RHUnk004fd7f0();
    RHUnk004fd7f0 &operator=(const RHUnk004fd7f0 &other);
    void InsertObstacle(void *const &area)
    {
        m_obstacles.InsertSingleLast(area);
    }
    RHFastFindClearedPointerRecord m_points;
    RHFastFindLayerLines m_lines;
    RHFastFindClearedPointerRecord m_sectors;
    RHFastFindClearedPointerRecord m_obstacles;
    RHFastFindClearedPointerRecord m_masks;
    RHFastFindClearedPointerRecord m_paths;
};

#endif
