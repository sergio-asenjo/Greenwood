#ifndef RHCAMPAIGNPROFILES_H
#define RHCAMPAIGNPROFILES_H

#include "RHCampaignPointerArray.h"
#include <string>
#include <string.h>

class RHCharacterProfile;

class RHCampaignCharacterName : public std::string
{
public:
    explicit RHCampaignCharacterName(const char *text)
    {
        std::string &(std::string::*assign)(const char *, unsigned) = &std::string::assign;
        (this->*assign)(text, strlen(text));
    }
};

class RHCampaignProfiles
{
public:
    char m_0[0x10];
    RHCampaignPointerArray<RHCharacterProfile *> m_characters;
    char m_20[0x50];
    RHCampaignProfiles();
    ~RHCampaignProfiles();
    RHCharacterProfile *FUN_0056d5d0(const std::string &name);
};

extern RHCampaignProfiles *g_unk0x6c0e84;

#endif
