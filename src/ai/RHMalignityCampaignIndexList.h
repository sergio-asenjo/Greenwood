#ifndef RHMALIGNITYCAMPAIGNINDEXLIST_H
#define RHMALIGNITYCAMPAIGNINDEXLIST_H

#include "Decomp.h"

struct RHScriptNode;
struct RHScriptIter;

template <bool InlineHead>
class RHCampaignIndexList
{
public:
    undefined4 m_allocator;
    RHScriptNode *m_head;
    int m_count;
    RHScriptIter FUN_004fe2e0(RHScriptIter position, const unsigned short &value);
};

#endif
