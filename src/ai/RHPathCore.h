#ifndef RHPATHCORE_H
#define RHPATHCORE_H

#include "RHMotionAreaList.h"
#include "RHTitbitsCore.h"

class SBFile;
class RHElementActor;
class RHWaypoint;

struct RHPathArray
{
    int m_grow;
    RHWaypoint **m_first;
    RHWaypoint **m_last;
    RHWaypoint **m_end;
    unsigned size() { return m_first == 0 ? 0 : m_last - m_first; }
    RHWaypoint **begin() { return m_first; }
    RHWaypoint *&operator[](unsigned index) { return *(begin() + index); }
};

struct RHPathHistory
{
    float m_0;
    float m_4;
    void *m_8;
    unsigned short m_c;
    char m_pade[2];
    char m_10;
    char m_pad11;
    unsigned short m_12;
};

struct RHPathHistoryNode
{
    RHPathHistoryNode *m_next;
    RHPathHistoryNode *m_prev;
    RHPathHistory m_data;
};

class RHPathHistoryIter
{
public:
    RHPathHistoryNode *m_p;
    RHPathHistoryIter() {}
    RHPathHistoryIter(RHPathHistoryNode *p) : m_p(p) {}
};

void RHPathUnk0048f180(RHPathHistory *dst, const RHPathHistory *src);

class RHPathHistoryList : public RHMotionAreaListStorage<RHPathHistory>
{
public:
    RHPathHistoryNode *m_cur;
    char m_valid;
    char m_pad11[3];
    int m_index;
    RHPathHistoryNode *Unk00551de0(RHPathHistoryNode *next, RHPathHistoryNode *prev);
    RHPathHistoryNode *Head() { return (RHPathHistoryNode *)_Head; }
    RHPathHistoryIter begin() { return RHPathHistoryIter(Head()->m_next); }
    RHPathHistoryIter end() { return RHPathHistoryIter(Head()); }
    RHPathHistoryIter insert(RHPathHistoryIter pos, const RHPathHistory &value)
    {
        RHPathHistoryNode *node = pos.m_p;
        node->m_prev = Unk00551de0(node, node->m_prev);
        node = node->m_prev;
        node->m_prev->m_next = node;
        RHPathUnk0048f180(&node->m_data, &value);
        ++_Size;
        return RHPathHistoryIter(node);
    }
    RHPathHistoryIter erase(RHPathHistoryIter first, RHPathHistoryIter last)
    {
        RHPathHistoryIter result;
        ((RHTitbitList *)this)->Clear(&result, (RHTitbitNode *)first.m_p, (RHTitbitNode *)last.m_p);
        return result;
    }
    void clear()
    {
        erase(begin(), end());
        m_valid = 1;
    }
    RHPathHistory &operator[](int index)
    {
        ((RHTitbitList *)this)->At(index);
        return m_cur->m_data;
    }
};

class RHPath
{
public:
    ~RHPath();
    bool TestIfPathIsFine(RHElementActor *actor);
    bool SerializeStatus(SBFile &file);
    RHWaypoint *LookupNextWaypoint() const;
    void ResetHistory();
    void InitializeHistoryEntriesOnPath();
    unsigned short GetWaypointCount() const
    {
        if (m_4 == 0)
            return 0;
        return m_4->size();
    }
    void Emit(SBFile &file, RHElementActor *actor);
    char m_0;
    char m_1;
    char m_2;
    char m_pad3;
    RHPathArray *m_4;
    unsigned short m_8;
    char m_pada[2];
    RHPathHistoryList m_c;
};

#endif
