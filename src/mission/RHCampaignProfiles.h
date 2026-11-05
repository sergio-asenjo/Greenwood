#ifndef RHCAMPAIGNPROFILES_H
#define RHCAMPAIGNPROFILES_H

#include "RHCampaignPointerArray.h"

class RHProfileText;

class RHCampaignProfiles
{
public:
    char m_0[0x10];
    RHCampaignPointerArray<void *> m_characters;
    char m_20[0x50];
    RHCampaignProfiles();
    ~RHCampaignProfiles();
    void *FUN_0056d5d0(const RHProfileText &name);
};

#endif
