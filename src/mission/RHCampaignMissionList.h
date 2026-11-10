#ifndef RHCAMPAIGNMISSIONLIST_H
#define RHCAMPAIGNMISSIONLIST_H

#include "RHScriptListCore.h"
#include "RHMission.h"
#include "RHSectorActorList.h"

class RHCampaignMissionList : public RHUnk0046eb30
{
public:
    typedef RHScriptNode Node;
    void FUN_0045a440(const RHMission *const &value);
    __forceinline void FUN_005c8e40(unsigned index) { ((RHSectorActorList *)this)->Unk005c8e40(index); }
    void Clear()
    {
        RHScriptNode *last = head;
        RHScriptIter current(last->next);
        while (current.node != last)
        {
            RHScriptIter removed = erase(current++);
        }
        valid = true;
    }
};

#endif
