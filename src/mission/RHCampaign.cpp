#include "RHCampaign.h"
#include <algorithm>
#include <windows.h>
#include <cstdlib>

// Parked: 49.95%.
// STUB: GAME 0x00450ec0
void RHCampaign::CreateGang()
{
    for (RHPCDescription **it = m_114.begin(); it != m_114.end(); ++it)
        if (*it != 0)
            (*it)->FUN_00459dd0(1);
    ((RHMissionArrayStorage *)&m_114)->FUN_004609a0(m_114.begin(), m_114.end());
    ((RHMissionArrayStorage *)&m_104)->FUN_004609a0(m_104.begin(), m_104.end());
    bool defaultGang = g_unk0x6c05cc.FUN_0045a010(RHCampaignText(g_unk0x6c0560)) == 0;
    if (defaultGang)
    {
        if (g_unk0x6c0e84 == 0)
            g_unk0x6c0e84 = new RHCampaignProfiles;
        RHPCDescription *value = new RHPCDescription(g_unk0x6c0e84->m_characters.begin()[1], true);
        ((RHMissionArrayStorage *)&m_114)->FUN_004e5820(m_114.end(), (const unsigned long &)value);
        ((RHMissionArrayStorage *)&m_104)->FUN_004e5820(m_104.end(), (const unsigned long &)m_114.back());
    }
    else
    {
        if (g_unk0x6c0e84 == 0)
            g_unk0x6c0e84 = new RHCampaignProfiles;
        RHCampaignProfiles *profiles = g_unk0x6c0e84;
        unsigned count = g_unk0x6c05cc.m_length;
        for (unsigned i = 0; i < count; ++i)
        {
            switch (toupper(g_unk0x6c05cc[i]))
            {
            case 'R':
                {
                    ((RHCampaignPCArray *)&m_114)->Push(new RHPCDescription(profiles->FUN_0056d5d0(RHCampaignText("Robin des bois"), true), true));
                    ((RHMissionArrayStorage *)&m_104)->FUN_004e5820(m_104.end(), (const unsigned long &)m_114.back());
                }
                break;
            case 'J':
                {
                    ((RHCampaignPCArray *)&m_114)->Push(new RHPCDescription(profiles->FUN_0056d5d0(RHCampaignText("Petit Jean"), true), true));
                    ((RHMissionArrayStorage *)&m_104)->FUN_004e5820(m_104.end(), (const unsigned long &)m_114.back());
                }
                break;
            case 'T':
                {
                    ((RHCampaignPCArray *)&m_114)->Push(new RHPCDescription(profiles->FUN_0056d5d0(RHCampaignText("Frere Tuck"), true), true));
                    ((RHMissionArrayStorage *)&m_104)->FUN_004e5820(m_104.end(), (const unsigned long &)m_114.back());
                }
                break;
            case 'S':
                {
                    ((RHCampaignPCArray *)&m_114)->PushCounted(new RHPCDescription(profiles->FUN_0056d5d0(RHCampaignText("Stutely"), true), true));
                    ((SBArray<RHSaveGame *> *)&m_104)->Insert((RHSaveGame **)m_104.end(), 1, (RHSaveGame *const &)m_114.back());
                }
                break;
            case 'W':
                {
                    ((RHCampaignPCArray *)&m_114)->PushCounted(new RHPCDescription(profiles->FUN_0056d5d0(RHProfileText("Will Ecarlate"), true), true));
                    ((SBArray<RHSaveGame *> *)&m_104)->Insert((RHSaveGame **)m_104.end(), 1, (RHSaveGame *const &)m_114.back());
                }
                break;
            case 'M':
                {
                    ((RHCampaignPCArray *)&m_114)->PushCounted(new RHPCDescription(profiles->FUN_0056d5d0(RHProfileText("Lady Marianne"), true), true));
                    ((SBArray<RHSaveGame *> *)&m_104)->Insert((RHSaveGame **)m_104.end(), 1, (RHSaveGame *const &)m_114.back());
                }
                break;
            case 'A':
                {
                    ((RHCampaignPCArray *)&m_114)->PushCounted(new RHPCDescription(profiles->FUN_0056d5d0(RHProfileText(
                        // STRING: GAME 0x006ab954
                        "Paysan A"), true), true));
                    ((SBArray<RHSaveGame *> *)&m_104)->Insert((RHSaveGame **)m_104.end(), 1, (RHSaveGame *const &)m_114.back());
                }
                break;
            case 'B':
                {
                    ((RHCampaignPCArray *)&m_114)->PushCounted(new RHPCDescription(profiles->FUN_0056d5d0(RHProfileText(
                        // STRING: GAME 0x006ab948
                        "Paysan B"), true), true));
                    ((SBArray<RHSaveGame *> *)&m_104)->Insert((RHSaveGame **)m_104.end(), 1, (RHSaveGame *const &)m_114.back());
                }
                break;
            case 'C':
                {
                    ((RHCampaignPCArray *)&m_114)->PushCounted(new RHPCDescription(profiles->FUN_0056d5d0(RHProfileText(
                        // STRING: GAME 0x006ab93c
                        "Paysan C"), true), true));
                    ((SBArray<RHSaveGame *> *)&m_104)->Insert((RHSaveGame **)m_104.end(), 1, (RHSaveGame *const &)m_114.back());
                }
                break;
            default:
                SBAssert(1, "P:\\Robin Hood\\RHCampaign.cpp", 298,
                    // STRING: GAME 0x006ab8f8
                    "JETZT GEHT'S LOS : Unknow character specified on the command line !");
                break;
            }
        }
    }
}

// Parked: 81.23%.
// STUB: GAME 0x00451b70
void RHCampaign::SelectMissions(bool forced)
{
    unsigned attempts = 10;
    RHCampaignMissionCandidates candidates;
    do
    {
        if (forced)
        {
            if (m_164.size() == 0)
                return;
            candidates.Assign(m_164);
        }
        else
            candidates.Assign(m_154);
        if (candidates.size() > 1)
            FUN_004526f0(candidates);
        if (candidates.size() > 1)
            SelectMissionsByObligation(candidates);
        if (!forced)
        {
            if (candidates.size() > 1)
                FUN_00452810(candidates);
            FUN_00455f00(candidates);
        }
        if (candidates.size() > 1)
            FUN_00452c90(candidates);
        if (candidates.size() > 1)
            FUN_00452a50(candidates);
        if (candidates.size() > 1)
            SelectMissionsByLocation(candidates);
        if (candidates.size() >= 1)
            break;
        --attempts;
    } while (attempts != 0);
    if (attempts == 0)
    {
        SBAssert(0, "P:\\Robin Hood\\RHCampaign.cpp", 440,
            // STRING: GAME 0x006ab9f0
            "RHCampaign: unable to determine accessible mission (see following report) !");
        FUN_00456e60();
        SBAssert(0, "P:\\Robin Hood\\RHCampaign.cpp", 442,
            // STRING: GAME 0x006ab9b0
            "RHCampaign: forcing mission !");
        if (forced)
            ((RHCampaignArrayOps *)&candidates)->FUN_00457a30((const RHCampaignArrayOps &)m_164);
        else
        {
            ((RHCampaignArrayOps *)&candidates)->FUN_00457a30((const RHCampaignArrayOps &)m_154);
            FUN_00455f00(candidates);
        }
        if (candidates.size() > 1)
        {
            unsigned index = rand() % candidates.size();
            std::vector<RHMission *> &missions = forced ? m_164 : m_154;
            if (forced)
                ((RHMissionArrayStorage *)&missions)->FUN_004609a0(missions.begin(), missions.end());
            else
            {
                for (RHMission **it = missions.begin(); it != missions.end(); ++it)
                    if (*it != candidates[index])
                        (*it)->m_4 = 0;
                ((RHCampaignArrayOps *)&missions)->FUN_0044ea70();
            }
            ((RHMissionArrayStorage *)&missions)->FUN_004e5820(missions.end(), (const unsigned long &)candidates[index]);
            return;
        }
    }
    if (forced)
        ((RHCampaignArrayOps *)&m_164)->FUN_00457a30((const RHCampaignArrayOps &)candidates);
    else
        ((RHCampaignArrayOps *)&m_154)->FUN_00457a30((const RHCampaignArrayOps &)candidates);
}

// FUNCTION: GAME 0x00452d20
void RHCampaign::SelectMissionsByLocation(std::vector<RHMission *> &missions)
{
    unsigned location = 0;
    unsigned short priority = 0xffff;
    RHMission **first = missions.begin();
    RHMission **last = missions.end();
    if (last - first <= 16)
        FUN_004e7210(first, last, (bool (*)(RHMission *, RHMission *))0x0054c780, 0);
    else
    {
        FUN_0045a940(first, last, (bool (*)(RHMission *, RHMission *))0x0054c780, 0);
        FUN_004e7210(first, first + 16, (bool (*)(RHMission *, RHMission *))0x0054c780, 0);
        for (RHMission **it = first + 16; it != last; ++it)
        {
            RHMission *value = *it;
            RHMission **destination = it;
            RHMission **previous = it - 1;
            while (FUN_0054c780(value, *previous))
            {
                *destination = *previous;
                destination = previous;
                --previous;
            }
            *destination = value;
        }
    }
    for (RHMission **it = missions.begin(); it != missions.end(); ++it)
    {
        RHMission *mission = *it;
        void *profile = mission->m_profile;
        unsigned nextLocation = *(unsigned *)((char *)profile + 0x3c);
        if (location == nextLocation)
        {
            unsigned short nextPriority = *(unsigned short *)((char *)profile + 0x50);
            if (nextPriority == priority)
            {
                SBAssert(1, "P:\\Robin Hood\\RHCampaign.cpp", 999,
                         // STRING: GAME 0x006aba3c
                         "RHCampaign: two candidate missions have the same location and the same priority. Ach !\n");
            }
            else if (nextPriority > priority)
            {
                mission->m_4 = 0;
                missions.erase(it);
                --it;
            }
        }
        else
        {
            location = nextLocation;
            priority = *(unsigned short *)((char *)profile + 0x50);
        }
    }
}

// FUNCTION: GAME 0x00452e70
void RHCampaign::SelectMissionsByObligation(std::vector<RHMission *> &missions)
{
    FUN_0045a4f0(missions.begin(), missions.end(),
                 (bool (*)(RHMission *, RHMission *))0x0054c760, 0);
    if (missions.size() >= 2 && *((char *)missions[0]->m_profile + 0x5f))
    {
        if (*((char *)missions[1]->m_profile + 0x5f))
        {
            // STRING: GAME 0x006ab9d0
            SBAssert(1, "P:\\Robin Hood\\RHCampaign.cpp", 1048,
                     // STRING: GAME 0x006aba94
                     "RHCampaign: when building the accessible mission list, more than one obligatory missions have been encountered !\n");
            return;
        }
        for (RHMission **it = missions.begin() + 1; it != missions.end(); ++it)
            (*it)->m_4 = 0;
        missions.erase(missions.begin() + 1, missions.end());
    }
}

// deferred: unannotated pending reccmp #534
// 0x00452f20: 100.00%.
bool RHCampaign::Serialize(SBFile &file)
{
    RHSerializeName(file,
        // STRING: GAME 0x006abb08
        "RHCampaign");
    if (file.m_version >= 28 && !RHCampaignAccess(file, &m_1c0, 1, 1084))
        return false;
    if (!RHCampaignAccess(file, (char *)this + 0x94, 108, 1088))
        return false;
    if (!RHCampaignAccess(file, (char *)this + 0x100, 1, 1089))
        return false;
    if (!RHCampaignSerializeMissions(file, (RHCampaignMissionValues &)m_144))
        return false;
    if (!RHCampaignSerializePointers<RHMission>(file, m_154, FUN_00453940, false))
        return false;
    if (!RHCampaignSerializePointers<RHMission>(file, m_164, FUN_00453940, false))
        return false;
    if (!SerializeAllCharacters(file))
        return false;
    if (!RHCampaignSerializePointers<RHPCDescription>(file, m_114,
            (bool (*)(SBFile &, RHPCDescription *&))FUN_00453da0, true))
        return false;
    if (!RHCampaignSerializePointers<RHPCDescription>(file, m_124,
            (bool (*)(SBFile &, RHPCDescription *&))FUN_00453da0, true))
        return false;
    if (!FUN_00458be0(file, m_1b0, (bool (*)(SBFile &, RHPCDescription *&))0x00453da0))
        return false;
    if (!FUN_00458e70(file, *(RHCampaignProductionSectors *)((char *)this + 0x74),
            (bool (*)(SBFile &, RHSectorProduction &))0x00456a30))
        return false;
    if (!FUN_00459160(file, *(std::vector<unsigned long> *)((char *)this + 0x84),
            (bool (*)(SBFile &, unsigned long &))0x00456aa0))
        return false;
    if (!RHUnk004593f0SerializeList(file, (RHUnk0054e250List &)m_134, (void *)0x005e0ea0))
        return false;
    FUN_00453940(file, m_174);
    FUN_00453940(file, m_178);
    FUN_00453940(file, m_17c);
    FUN_00453940(file, *(RHMission **)((char *)this + 0x180));
    if (file.m_version >= 30)
    {
        RHMission *value;
        unsigned count;
        if (file.m_bLoading)
        {
            RHCampaignMissionList &missions = *(RHCampaignMissionList *)((char *)this + 0x184);
            missions.FUN_004e6c10();
            missions.m_dirty = true;
            if (!RHCampaignAccess(file, &count, 4, 1121))
                return false;
            for (unsigned i = 0; i < count; ++i)
            {
                FUN_00453940(file, value);
                missions.FUN_0045a440((const RHMission *const &)value);
                missions.m_dirty = true;
            }
        }
        else
        {
            count = *(unsigned *)((char *)this + 0x18c);
            if (!RHCampaignAccess(file, &count, 4, 1132))
                return false;
            for (unsigned i = 0; i < count; ++i)
            {
                RHCampaignMissionList &missions = *(RHCampaignMissionList *)((char *)this + 0x184);
                missions.FUN_005c8e40(i);
                value = missions.m_cursor->value;
                FUN_00453940(file, value);
            }
        }
    }
    if (file.m_version >= 41)
    {
        if (!RHCampaignAccess(file, (char *)this + 0x1a8, 4, 1145))
            return false;
        if (file.m_version >= 48 && !RHCampaignAccess(file, (char *)this + 0x1ac, 4, 1149))
            return false;
    }
    else
        *(unsigned *)((char *)this + 0x1a8) = 0;
    return true;
}

// FUNCTION: GAME 0x00453630
bool RHCampaign::SerializeAllCharacters(SBFile &file)
{
    unsigned count;
    if (!file.m_bLoading)
    {
        count = m_104.size();
        if (file.Access(&count, 4) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHCampaign.cpp", 1171, "Serialize failed reason is %s", reason);
            return false;
        }
        for (unsigned i = 0; i < count; ++i)
            m_104[i]->FUN_0055bb30(file);
    }
    else
    {
        RHCampaignPointerArray<RHPCDescription *> &list = (RHCampaignPointerArray<RHPCDescription *> &)m_104;
        list.erase(list.begin(), list.end());
        if (file.Access(&count, 4) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHCampaign.cpp", 1184, "Serialize failed reason is %s", reason);
            return false;
        }
        for (unsigned i = 0; i < count; ++i)
        {
            RHPCDescription *value = new RHPCDescription;
            value->FUN_0055bb30(file);
            list.insert(list.end(), 1, value);
        }
    }
    return true;
}

// deferred: unannotated pending reccmp #534
// 0x00453da0: 100.00% when temporarily annotated.
bool FUN_00453da0(SBFile &file, void *&value)
{
    int index;
    if (file.m_bLoading)
    {
        if (file.Access(&index, 4) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            // STRING: GAME 0x006ab8d8
            SBAssert(0, "P:\\Robin Hood\\RHCampaign.cpp", 1507, "Serialize failed reason is %s", reason);
            return false;
        }
        value = g_unk0x6c07fc->m_108[index];
    }
    else
    {
        index = g_unk0x6c07fc->FUN_00453d60(value);
        if (file.Access(&index, 4) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHCampaign.cpp", 1517, "Serialize failed reason is %s", reason);
            return false;
        }
    }
    return true;
}

// Parked: 27.40%.
// STUB: GAME 0x00453e60
void RHCampaign::CreatePlayableCharacterSet(SBArray<RHElement *> &elements, std::vector<RHbeamMe> &beamMes)
{
    RHCampaignIndexList<false> available;
    unsigned short remaining = beamMes.size();
    bool allowAmbiguous = false;
    RHCampaignByteArray assigned(remaining, 0);
    for (unsigned i = 0; i < (unsigned short)beamMes.size(); ++i)
    {
        RHPCDescription **it = m_1b0.end();
        const char *required = 0;
        switch (beamMes[i].m_required)
        {
        case 1: required = "Frere Tuck"; break;
        case 2: required = "Lady Marianne"; break;
        case 3: required = "Petit Jean"; break;
        case 4: required = "Robin des bois"; break;
        case 5: required = "Stutely"; break;
        case 6: required = "Will Ecarlate"; break;
        }
        assigned[i] = 0;
        if (required != 0)
        {
            unsigned character = 0;
            for (it = m_1b0.begin(); it != m_1b0.end(); ++it, ++character)
            {
                const char *name = ((RHProfileText *)((char *)(*it)->m_profile + 0x14))->c_str();
                if (_stricmp(name, required) == 0 ||
                    (beamMes[i].m_required == 4 && _stricmp(name, "Robin des villes") == 0))
                {
                    FUN_004552f0(elements, ((RHCampaignBeamArray *)&beamMes)->FUN_00457bc0(i, character), character);
                    assigned[i] = 1;
                    --remaining;
                    break;
                }
            }
        }
        if (beamMes[i].m_required != 0 && it == m_1b0.end())
            SBAssert(0, "P:\\Robin Hood\\RHCampaign.cpp", 1668,
                // STRING: GAME 0x006abb14
                "WARNUNG ! Beam-me with required PC could not be filled (required PC is not in mission team) Check required PCs in mission profile.");
    }
    if (*(int *)((char *)m_178->m_profile + 0x3c) == 8)
    {
        unsigned character = 0;
        for (RHPCDescription **it = m_1b0.begin(); it != m_1b0.end(); ++it, ++character)
        {
            short beamMe = (*it)->m_3c;
            if (beamMe != -1)
            {
                assigned[beamMe] = 1;
                FUN_004552f0(elements, ((RHCampaignBeamArray *)&beamMes)->FUN_00457bc0(beamMe, character), character);
                --remaining;
                g_pEngine->FUN_004e3770(elements.m_last[-1]);
            }
        }
        unsigned count = beamMes.size();
        RHbeamMe value;
        for (unsigned attempts = 100; attempts != 0; --attempts)
        {
            unsigned first = rand() % count;
            unsigned second = rand() % count;
            if (first != second)
            {
                char flag = assigned[first];
                assigned[first] = assigned[second];
                assigned[second] = flag;
                value = beamMes[first];
                beamMes[first] = beamMes[second];
                beamMes[second] = value;
            }
        }
    }
    unsigned short characters = m_1b0.size();
    for (unsigned short characterIndex = 0; characterIndex < characters; ++characterIndex)
        if (!m_1b0[characterIndex]->m_44)
            available.Push(characterIndex);
    if (*(int *)((char *)m_178->m_profile + 0x3c) != 8 && available.m_count >= 5)
    {
        while (available.m_count > 5)
            ((RHUnk0046eb30 *)&available)->erase(RHScriptIter(available.m_head->prev));
    }
    while (remaining > 0 && available.m_count > 0)
    {
        bool progress = false;
        unsigned short index = 0;
        for (RHbeamMe *it = beamMes.begin(); it != beamMes.end() && available.m_count != 0; ++it, ++index)
        {
            if (assigned[index])
                continue;
            RHCampaignIndexList<true> candidates;
            for (RHScriptNode *node = available.m_head->next; node != available.m_head; node = node->next)
            {
                unsigned short character = *(unsigned short *)&node->data;
                if (FUN_00454c00(*it, character))
                    candidates.Push(character);
            }
            if (candidates.m_count == 1 || (candidates.m_count > 1 && allowAmbiguous))
            {
                assigned[index] = 1;
                unsigned short character = candidates.Front();
                FUN_004552f0(elements, *it, character);
                for (RHScriptNode *node = available.m_head->next; node != available.m_head;)
                {
                    RHScriptNode *position = node;
                    node = node->next;
                    if (*(unsigned short *)&position->data == character)
                        ((RHUnk0046eb30 *)&available)->erase(RHScriptIter(position));
                }
                g_unk0x6c0a50.m_progress += g_unk0x00677438 / (int)characters;
                g_unk0x6c0a50.FUN_00523300();
                allowAmbiguous = false;
                --remaining;
                progress = true;
            }
        }
        if (remaining == 0)
            break;
        if (!progress && available.m_count > 0)
        {
            if (!allowAmbiguous)
                allowAmbiguous = true;
            else
            {
                unsigned short index = 0;
                for (RHbeamMe *it = beamMes.begin(); it != beamMes.end(); ++it, ++index)
                {
                    if (assigned[index])
                        continue;
                    FUN_004552f0(elements, *it, available.Front());
                    available.Remove(available.m_head->next);
                    --remaining;
                    g_unk0x6c0a50.m_progress += g_unk0x00677438 / (int)characters;
                    g_unk0x6c0a50.FUN_00523300();
                    if (available.m_count == 0)
                        break;
                }
            }
        }
    }
    if (m_144.begin() == m_178)
        FUN_004559f0();
}

// FUNCTION: GAME 0x00455a70
unsigned short RHCampaign::GetNumberOfPeasantsToConvertToBlazons() const
{
    void *profile = m_17c->m_profile;
    unsigned short quotation = *(unsigned short *)((char *)profile + 0x70);
    if (quotation == 0)
    {
        SBAssert(1, "P:\\Robin Hood\\RHCampaign.cpp", 2200,
                 // STRING: GAME 0x006abbac
                 "ABSOLUT VERBOTEN : The peasant to blazon quotation is zero, this would lead to a division by zero !");
        return 0;
    }
    unsigned peasants = m_1b0.size() / quotation;
    int won = ((RHUnk00452030 *)this)->Get(3);
    unsigned short blazons = *(unsigned short *)((char *)profile + 0x68) -
                              *(unsigned short *)((char *)profile + 0x6a) - won;
    if ((unsigned short)peasants < blazons)
        return peasants * *(unsigned short *)((char *)profile + 0x70);
    return blazons * *(unsigned short *)((char *)profile + 0x70);
}

// STUB: GAME 0x00457330
bool RHCampaign::LoadFromSaveGame(const RHSaveGame *saveGame)
{
    RHUnk005f4fc0 file;
    bool result = false;
    if (file.FUN_005f5090(saveGame->FUN_0056e5d0(), 1))
    {
        SBAssert(0, "P:\\Robin Hood\\RHCampaign.cpp", 3144,
                 // STRING: GAME 0x006abd24
                 "Unable to open the savegame '%s'.", RHCampaignStringChars(saveGame->FUN_0056e5d0()));
    }
    else
    {
        RHSaveGame::Header header;
        RHSaveGame::SerializeHeader(file, header);
        result = Serialize(file);
        file.FUN_005f5290();
    }
    return result;
}

// FUNCTION: GAME 0x00457560
bool RHCampaign::CreateBackup()
{
    RHUnk005f4fc0 file;
    bool failed = file.FUN_005f5090((const std::string &)RHCampaignNarrowString("Campaign.bck"), 8) != 0;
    if (failed)
    {
        SBAssert(0, "P:\\Robin Hood\\RHCampaign.cpp", 3376,
                 // STRING: GAME 0x006abd48
                 "Unable to create the campaign backup file !");
        return false;
    }
    file.m_version = 48;
    file.Access(&file.m_version, 4);
    Serialize(file);
    file.FUN_005f5290();
    return true;
}

// FUNCTION: GAME 0x004576f0
bool RHCampaign::CopyBackupTo(SBFile &file) const
{
    // STRING: GAME 0x006abd74
    HANDLE backup = CreateFileA("Campaign.bck", GENERIC_READ, 0, 0, OPEN_EXISTING, 0, 0);
    if (backup == INVALID_HANDLE_VALUE)
    {
        SBAssert(0, "P:\\Robin Hood\\RHCampaign.cpp", 3408,
                 // STRING: GAME 0x006abd84
                 "Unable to open the campaign backup file !");
        return false;
    }
    DWORD transferred;
    unsigned version;
    char buffer[512];
    ReadFile(backup, &version, 4, &transferred, 0);
    do
    {
        ReadFile(backup, buffer, 512, &transferred, 0);
        file.Access(buffer, transferred);
    } while (transferred != 0);
    CloseHandle(backup);
    return true;
}

// FUNCTION: GAME 0x00458be0
bool FUN_00458be0(SBFile &file, std::vector<RHPCDescription *> &values,
                  bool (*serialize)(SBFile &, RHPCDescription *&))
{
    RHCampaignPointerArray<RHPCDescription *> &pointers = (RHCampaignPointerArray<RHPCDescription *> &)values;
    if (!file.m_bLoading)
    {
        unsigned count = pointers.size();
        if (file.Access(&count, 4) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHCampaign.cpp", 39, "Serialize failed reason is %s", reason);
            return false;
        }
        for (RHPCDescription **it = pointers.begin(); it != pointers.end(); ++it)
            if (!serialize(file, *it))
                return false;
    }
    else
    {
        RHCampaignPointerArray<RHPCDescription *> &list = pointers;
        list.erase(list.begin(), list.end());
        unsigned count;
        if (file.Access(&count, 4) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHCampaign.cpp", 60, "Serialize failed reason is %s", reason);
            return false;
        }
        while (count > 0)
        {
            RHPCDescription *value;
            if (!serialize(file, value))
                return false;
            list.insert(list.end(), 1, value);
            --count;
        }
    }
    return true;
}

// STUB: GAME 0x00458e70
bool FUN_00458e70(SBFile &file, RHCampaignProductionSectors &values,
                  bool (*serialize)(SBFile &, RHSectorProduction &))
{
    if (!file.m_bLoading)
    {
        unsigned count = values.size();
        if (file.Access(&count, 4) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHCampaign.cpp", 39, "Serialize failed reason is %s", reason);
            return false;
        }
        for (RHSectorProduction *it = values.begin(); it != values.end(); ++it)
            if (!serialize(file, *it))
                return false;
    }
    else
    {
        RHCampaignProductionSectors &list = values;
        list.erase(list.begin(), list.end());
        unsigned count;
        if (file.Access(&count, 4) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHCampaign.cpp", 60, "Serialize failed reason is %s", reason);
            return false;
        }
        while (count > 0)
        {
            {
                RHSectorProduction value(14);
                if (!serialize(file, value))
                    return false;
                list.Insert(list.end(), 1, value);
            }
            --count;
        }
    }
    return true;
}

// FUNCTION: GAME 0x00459160
bool FUN_00459160(SBFile &file, std::vector<unsigned long> &values,
                  bool (*serialize)(SBFile &, unsigned long &))
{
    RHCampaignPointerArray<unsigned long> &pointers = (RHCampaignPointerArray<unsigned long> &)values;
    if (!file.m_bLoading)
    {
        unsigned count = pointers.size();
        if (file.Access(&count, 4) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHCampaign.cpp", 39, "Serialize failed reason is %s", reason);
            return false;
        }
        for (unsigned long *it = pointers.begin(); it != pointers.end(); ++it)
            if (!serialize(file, *it))
                return false;
    }
    else
    {
        RHCampaignPointerArray<unsigned long> &list = pointers;
        list.erase(list.begin(), list.end());
        unsigned count;
        if (file.Access(&count, 4) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHCampaign.cpp", 60, "Serialize failed reason is %s", reason);
            return false;
        }
        while (count > 0)
        {
            unsigned long value;
            if (!serialize(file, value))
                return false;
            list.insert(list.end(), 1, value);
            --count;
        }
    }
    return true;
}

// deferred: unannotated pending reccmp #534
// 0x004593f0: 100.00% when temporarily annotated.
bool RHUnk004593f0SerializeList(SBFile &file, RHUnk0054e250List &values, void *serialize)
{
    RHCampaignWideStrings &strings = (RHCampaignWideStrings &)values;
    bool (*callback)(SBFile &, RHCampaignWideString &) = (bool (*)(SBFile &, RHCampaignWideString &))serialize;
    if (!file.m_bLoading)
    {
        unsigned count = strings.size();
        if (file.Access(&count, 4) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHCampaign.cpp", 39, "Serialize failed reason is %s", reason);
            return false;
        }
        for (RHCampaignWideString *it = strings.begin(); it != strings.end(); ++it)
            if (!callback(file, *it))
                return false;
    }
    else
    {
        RHCampaignWideStrings &list = strings;
        list.erase(list.begin(), list.end());
        unsigned count;
        if (file.Access(&count, 4) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHCampaign.cpp", 60, "Serialize failed reason is %s", reason);
            return false;
        }
        while (count > 0)
        {
            {
                RHCampaignWideString value;
                if (!callback(file, value))
                    return false;
                list.Insert(list.end(), 1, value);
            }
            --count;
        }
    }
    return true;
}

void RHCampaign::Emit(std::vector<RHMission *> &missions)
{
    SelectMissions(false);
    CreateGang();
    SelectMissionsByLocation(missions);
    SelectMissionsByObligation(missions);
    GetNumberOfPeasantsToConvertToBlazons();
    RHUnk005f4fc0 file;
    SerializeAllCharacters(file);
    SBArray<RHElement *> elements;
    std::vector<RHbeamMe> beamMes;
    CreatePlayableCharacterSet(elements, beamMes);
}
