#include "RHMenuCampaignMap.h"
#include <windows.h>

// Parked: 99.19%, two this-register scheduling differences.
// STUB: GAME 0x00527d20
bool RHMenuCampaignMap::Create()
{
    bool created;
    {
        // STRING: GAME 0x006b09fc
        RHMapTitleText title(L"Campaign Map");
        created = FUN_00544b40(title, RHMapBox(0.0f, 0.0f, 629.0f, 480.0f), 0);
    }
    if (created)
    {
        RHMapCampaign *campaign = (RHMapCampaign *)g_unk0x6c07fc;
        RHMapWidget *arrow = (RHMapWidget *)((char *)this + 0x1a74);
        for (unsigned count = 10; count != 0; --count, ++arrow)
            V30(arrow);
        RHMapLocation *locations = (RHMapLocation *)((char *)this + 0x19c);
        for (unsigned i = 0; i < 10; ++i)
        {
            if (i != 8 && i != 0)
            {
                RHMapWidget *flag = &locations[i].m_e0;
                V30((char *)flag - 0xe0);
                V30(&locations[i].m_1ac);
                if (i != 1 && i != 2 && i != 3)
                    V30(flag);
                V38(&locations[i].m_1ac);
                locations[i].m_1ac.m_04[0] = 0;
            }
        }
        FUN_005284b0();
        FUN_00527c00(campaign->FUN_00528050());
        FUN_00527a70(campaign->UnkState());
        FUN_00527ae0(campaign->UnkState());
        if (campaign->FUN_00528050().size() == 0)
        {
            {
                // STRING: GAME 0x006b09f4
                std::wstring ok(L"OK");
                ((RHMapWidget *)((char *)this + 0xcc))->V30(ok, RHMapBox(574.0f, 5.0f, 595.0f, 26.0f), 0, 0x7c);
            }
            V30((char *)this + 0xcc);
            SBAssert(0,
                     // STRING: GAME 0x006b099c
                     "P:\\Robin Hood\\RHMenuCampaignMap.cpp", 0x1a6,
                     // STRING: GAME 0x006b09c0
                     "Campaign map : warning no missions are accessible.");
        }
        V30((char *)this + 0x25ec);
        FUN_00528810();
        DisplayPseudoMissionDebriefing();
        return true;
    }
    return false;
}

// deferred: unannotated pending reccmp #534; proven 100.00% when annotated.
void RHMenuCampaignMap::DisplayPseudoMissionDebriefing()
{
    RHMapCampaign *campaign = (RHMapCampaign *)g_unk0x6c07fc;
    if (campaign->FUN_004577a0() != 0)
    {
        if (m_2700 != unsigned(-1))
        {
            RHMapWideText message;
            *((char *)this + 0x5d) = 1;
            (*(RHMapWindow **)((char *)this + 0xb4))->FUN_0053bb30(m_2700);
            m_2700 = unsigned(-1);
            bool won = campaign->FUN_004577a0() == 1;
            RHMapDescription description;
            char directory[0x104];
            GetCurrentDirectoryA(0x104, directory);
            const char *directoryChars = ((SBString *)&g_unk0x006c0660)->m_chars;
            SetCurrentDirectoryA(directoryChars ? directoryChars : "");
            unsigned mission = campaign->m_1ac;
            if (!description.FUN_0063cda0(mission))
                SBAssert(0,
                         // STRING: GAME 0x006b0948
                         "P:\\Robin Hood\\RHMenuCampaignMap.cpp", 0x1ec,
                         // STRING: GAME 0x006afa88
                         "Warning: unable to load the resource description for the mission '%s'\n", &mission);
            SetCurrentDirectoryA(directory);
            RHMapDescription::Entry *entry = description.FUN_0063c9e0(mission);
            unsigned resource = won ? entry->m_30 : entry->m_38;
            RHMapResources *resources = g_unk0x006c1840;
            if (!resources->FUN_00600fc0(resource) || !resources->FUN_006009e0(resource, 0, message))
            {
                if (won)
                    (std::wstring &)message = FUN_005e23d0(0x104);
                else
                    (std::wstring &)message = FUN_005e23d0(0x103);
            }
            FUN_00529e60(*(RHMapWindow **)((char *)this + 0xb4), message, won, 0);
            (*(RHMapWindow **)((char *)this + 0xb4))->FUN_0053c7e0();
            campaign->FUN_004577b0();
            if (campaign->m_100.value == 0)
                (*(RHMapWindow **)((char *)this + 0xb4))->FUN_0053bbe0();
        }
        else
        {
            *((char *)this + 0x5d) = 0;
            m_2700 = (*(RHMapWindow **)((char *)this + 0xb4))->FUN_0053baa0(0x1f4);
        }
    }
}

void RHMenuCampaignMap::Emit()
{
    Create();
    DisplayPseudoMissionDebriefing();
}
