#ifndef RHCAMPAIGNMISSIONLIST_H
#define RHCAMPAIGNMISSIONLIST_H

#include "RHScriptListCore.h"
#include "RHMission.h"
#include "RHSectorActorList.h"

class RHCampaignMissionList : public std::list<RHMission *>
{
public:
    typedef _Node Node;
    RHCampaignMissionList() : valid(true) {}
    ~RHCampaignMissionList() { clear(); }
    Node *Head() { return _Head; }
    Node *cursor;
    bool valid;
    char padding[3];
    int index;
    void FUN_0045a440(const RHMission *const &value);
    __forceinline void FUN_005c8e40(unsigned index) { ((RHSectorActorList *)this)->Unk005c8e40(index); }
    void Clear()
    {
        typedef iterator (std::list<RHMission *>::*Erase)(iterator);
        Erase eraseOne = &std::list<RHMission *>::erase;
        iterator last = end();
        iterator current = begin();
        while (current != last)
        {
            iterator removed = (this->*eraseOne)(current++);
        }
        valid = true;
    }
};

#endif
