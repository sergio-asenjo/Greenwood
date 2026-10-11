#include "SBNullstr.h"
#include "RHCampaign.h"
#include <algorithm>

namespace std {
template<> void _Sort(RHMission **first, RHMission **last, bool (*compare)(RHMission *, RHMission *), RHMission **)
{
    while (_SORT_MAX < last - first)
    {
        RHMission **middle = _Unguarded_partition(first, last,
            _Median(*first, *(first + (last - first) / 2), *(last - 1), compare), compare);
        if (last - middle <= middle - first)
        {
            _Sort(middle, last, compare, (RHMission **)0);
            last = middle;
        }
        else
        {
            _Sort(first, middle, compare, (RHMission **)0);
            first = middle;
        }
    }
}
}

// FUNCTION: GAME 0x0054c6a0
RHMission::RHMission(const RHMission &value)
    : m_profile(value.m_profile), m_4(value.m_4), m_6(value.m_6), m_8(value.m_8)
{
}

extern "C" int __cdecl rand() { return 0; }


void RHCampaignWideString::Tidy(bool) {}
void RHCampaignWideStrings::Destroy(RHCampaignWideString *, RHCampaignWideString *) {}
void RHCampaignWideStrings::Insert(RHCampaignWideString *, unsigned, const RHCampaignWideString &) {}

void RHCampaignUnk00457950::Value::FUN_0051c0c0() {}

void RHPCDescription::FUN_0055bc30() {}
void RHPCDescription::FUN_0055bc90(void *, bool) {}
RHPCDescription::~RHPCDescription() {}
void RHPCDescription::FUN_00459fd0() {}
bool FUN_00456a30(SBFile &, RHSectorProduction &) { return false; }
bool FUN_00452040(RHMission *) { return false; }
bool FUN_00452090(RHMission *) { return false; }
void RHCampaign::FUN_004564e0(std::vector<RHMission *> &) {}
bool FUN_0054cc10(RHMission *) { return false; }
bool RHCampaignMissionCalls::FUN_0054cc20() { return false; }
bool RHCampaignMissionCalls::FUN_0054cbf0() { return false; }
bool RHCampaignMissionCalls::FUN_0054c8a0(std::string &) { return false; }
void RHCampaignMissionList::FUN_005c8e40(unsigned) {}
void RHCampaignText::FUN_004021c0(const char *, unsigned) {}
RHCampaignProfiles::~RHCampaignProfiles() {}

// GLOBAL: GAME 0x006c05cc
RHCampaignCommandLine g_unk0x6c05cc;
// GLOBAL: GAME 0x006c0e84
RHCampaignProfiles *g_unk0x6c0e84;

void RHCampaignLoadingProgress::FUN_00523300() {}
bool RHPathObstacleGrid::FUN_004f9260(const SBGeoPoint2D &, const SBGeoPoint2D &, unsigned short) { return false; }

// GLOBAL: GAME 0x00677438
float g_unk0x00677438 = 10.0f;
// GLOBAL: GAME 0x006c0a50
RHCampaignLoadingProgress g_unk0x6c0a50;
