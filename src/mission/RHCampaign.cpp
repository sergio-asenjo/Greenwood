#include "SBNullstr.h"

namespace std {
template<> inline basic_string<unsigned short, char_traits<unsigned short>, allocator<unsigned short> >::basic_string(const basic_string &value)
    : allocator(value.allocator)
{
    _Tidy();
    assign(value, 0, static_cast<size_type>(-1));
}
}

#include "RHCampaign.h"
#include <algorithm>
#include <windows.h>
#include <cstdlib>
#include "RHPCStatusCore.h"

namespace std {
template<> void _Sort(RHMission **first, RHMission **last, bool (*compare)(RHMission *, RHMission *), RHMission **);
}

class RHScriptBatchCalls
{
public:
    void Unk00455400(void *description);
    void Unk004555f0(void *description);
    void FUN_00456d20();
};

DECOMP_SIZE_ASSERT(RHMission, 0x0c)
DECOMP_SIZE_ASSERT(RHCampaign, 0x1c4)
DECOMP_SIZE_ASSERT(RHGameCampaignView, 0x184)
DECOMP_SIZE_ASSERT(RHCampaignMissionCandidates, 0x10)
DECOMP_SIZE_ASSERT(RHCampaignBeamText, 0x10)
DECOMP_SIZE_ASSERT(RHbeamMe, 0x30)
DECOMP_SIZE_ASSERT(RHUnk0048f280, 0x60c)
DECOMP_SIZE_ASSERT(RHPCDescription, 0x48)
DECOMP_SIZE_ASSERT(RHCampaignPCBase, 0x04)
DECOMP_SIZE_ASSERT(SBGeoVector2D, 0x08)
DECOMP_SIZE_ASSERT(SBGeoBoundingBox2D, 0x14)
DECOMP_SIZE_ASSERT(RHCampaignCharacterData, 0x9c)
DECOMP_SIZE_ASSERT(RHSaveGame::Header, 0x0c)

#include "RHElementActorPC.h"

class RHMessenger;
RHMessenger *RHUnk00546050();

// LIBRARY: GAME 0x0044e940
// ?_Construct@std@@YAXPAGABG@Z

// FUNCTION: GAME 0x00436500
RHProfileManager *RHUnk00436500GetProfileManager()
{
    if (!g_unk0x6c0e84)
        g_unk0x6c0e84 = new RHCampaignProfiles;
    return (RHProfileManager *)g_unk0x6c0e84;
}

// FUNCTION: GAME 0x0044ea70
void RHCampaignArrayOps::FUN_0044ea70()
{
    ((std::vector<void *> *)this)->erase(((std::vector<void *> *)this)->begin(),
                                       ((std::vector<void *> *)this)->end());
}

struct RHCampaignWidgetEvent
{
    int type;
    void *widget;
    unsigned value;
    void *next;
};

#include "SBUIKeyboardCalls.h"

struct RHCampaignWidgetInput
{
    undefined m_00[0x0a];
    unsigned short flags;
    RHGameWidgetInputCalls *shortcuts;
};

class RHGameWidgetRendererCalls
{
public:
    bool FUN_0060d890(const SBGeoPoint2D &point);
};

struct RHCampaignWidgetView
{
    undefined m_00[4];
    char m_04;
    undefined m_05[0x4c - 5];
    RHCampaignWidgetEvent m_event;
    undefined m_5c[0x7c - 0x5c];
    int m_7c;
};

class RHUnk0044fd00 : public RHCampaignWidgetView
{
public:
    void FUN_0044fd00(int value);
    int FUN_0044fd10();
    void FUN_0044fd20();
    RHCampaignWidgetEvent *FUN_0044fd40(const RHCampaignWidgetInput &input);
};

class RHUnk0044fd20Dispatch
{
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual void v8();
    virtual unsigned V24();
};

class SBUIUnk0060da20
{
public:
    bool FUN_0060da20(unsigned id);
};

// FUNCTION: GAME 0x0044fd00
void RHUnk0044fd00::FUN_0044fd00(int value)
{
    *(int *)((char *)this + 0xcc) = value;
}

// FUNCTION: GAME 0x0044fd10
int RHUnk0044fd00::FUN_0044fd10()
{
    return *(int *)((char *)this + 0xcc);
}

// FUNCTION: GAME 0x0044fd20
void RHUnk0044fd00::FUN_0044fd20()
{
    ((SBUIUnk0060da20 *)((char *)this + 0x80))->FUN_0060da20(((RHUnk0044fd20Dispatch *)this)->V24());
}

// FUNCTION: GAME 0x0044fd40
RHCampaignWidgetEvent *RHUnk0044fd00::FUN_0044fd40(const RHCampaignWidgetInput &input)
{
    if (m_04)
    {
        SBGeoBoundingBox2D &box = *(SBGeoBoundingBox2D *)((char *)this + 0x30);
        if (box.FUN_006083b0(*(SBGeoPoint2D *)&input) == 1 &&
            ((RHGameWidgetRendererCalls *)((char *)this + 0x80))->FUN_0060d890(
                ((SBGeoPoint2D *)&input)->Unk005fc110(*(SBGeoPoint2D *)&box)) == 1)
        {
            if (!(input.flags & 1))
            {
                RHCampaignWidgetEvent *event = &m_event;
                m_event.next = 0;
                m_event.value = 0;
                m_event.widget = this;
                event->type = 0;
                return event;
            }
        }
        else if (!*(unsigned short *)((char *)this + 0x0a) ||
            input.shortcuts->FUN_0060e240(*(unsigned short *)((char *)this + 0x0a)) != 2)
        {
            m_7c = 0;
            return 0;
        }
        RHCampaignWidgetEvent *event = &m_event;
        if (m_event.type != 2 && m_event.type != 7)
        {
            m_event.next = 0;
            m_event.value = 0;
            m_event.widget = this;
            event->type = 2;
            return event;
        }
        m_event.next = 0;
        m_event.value = 0;
        m_event.widget = this;
        event->type = 7;
        return event;
    }
    return 0;
}

class RHUnk0044fe70
{
public:
    int FUN_0044fe70();
};

// FUNCTION: GAME 0x0044fe70
int RHUnk0044fe70::FUN_0044fe70()
{
    if (!*(char *)((char *)this + 4))
        return 0xff;
    return *(int *)((char *)this + 0xcc);
}

void EmitRHUnk0044fd00(RHUnk0044fd00 *a, RHUnk0044fe70 *b)
{
    a->FUN_0044fd00(0);
    a->FUN_0044fd10();
    b->FUN_0044fe70();
}

// FUNCTION: GAME 0x00450c10
void RHCampaign::FUN_00450c10(SBArray<RHElement *> &elements, std::vector<RHbeamMe> &beamMes)
{
    for (RHPCDescription **it = m_114.begin(); it != m_114.end(); ++it)
        (*it)->m_44 = false;
    CreatePlayableCharacterSet(elements, beamMes);
}

// Parked: 49.95%.
// STUB: GAME 0x00450ec0
void RHCampaign::CreateGang()
{
    for (RHPCDescription **it = m_114.begin(); it != m_114.end(); ++it)
        if (*it != 0)
            (*it)->FUN_00459dd0(1);
    ((RHMissionArrayStorage *)&m_114)->FUN_004609a0(m_114.begin(), m_114.end());
    ((RHMissionArrayStorage *)&m_104)->FUN_004609a0(m_104.begin(), m_104.end());
    bool defaultGang = g_unk0x6c05cc.FUN_0045a010(RHCampaignText("")) == 0;
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
                    ((RHCampaignPCArray *)&m_114)->Push(new RHPCDescription(profiles->FUN_0056d5d0(RHCampaignText("Robin des bois")), true));
                    ((RHMissionArrayStorage *)&m_104)->FUN_004e5820(m_104.end(), (const unsigned long &)m_114.back());
                }
                break;
            case 'J':
                {
                    ((RHCampaignPCArray *)&m_114)->Push(new RHPCDescription(profiles->FUN_0056d5d0(RHCampaignText("Petit Jean")), true));
                    ((RHMissionArrayStorage *)&m_104)->FUN_004e5820(m_104.end(), (const unsigned long &)m_114.back());
                }
                break;
            case 'T':
                {
                    ((RHCampaignPCArray *)&m_114)->Push(new RHPCDescription(profiles->FUN_0056d5d0(RHCampaignText("Frere Tuck")), true));
                    ((RHMissionArrayStorage *)&m_104)->FUN_004e5820(m_104.end(), (const unsigned long &)m_114.back());
                }
                break;
            case 'S':
                {
                    ((RHCampaignPCArray *)&m_114)->PushCounted(new RHPCDescription(profiles->FUN_0056d5d0(RHCampaignText("Stutely")), true));
                    ((SBArray<RHSaveGame *> *)&m_104)->Insert((RHSaveGame **)m_104.end(), 1, (RHSaveGame *const &)m_114.back());
                }
                break;
            case 'W':
                {
                    ((RHCampaignPCArray *)&m_114)->PushCounted(new RHPCDescription(profiles->FUN_0056d5d0(RHProfileText("Will Ecarlate")), true));
                    ((SBArray<RHSaveGame *> *)&m_104)->Insert((RHSaveGame **)m_104.end(), 1, (RHSaveGame *const &)m_114.back());
                }
                break;
            case 'M':
                {
                    ((RHCampaignPCArray *)&m_114)->PushCounted(new RHPCDescription(profiles->FUN_0056d5d0(RHProfileText("Lady Marianne")), true));
                    ((SBArray<RHSaveGame *> *)&m_104)->Insert((RHSaveGame **)m_104.end(), 1, (RHSaveGame *const &)m_114.back());
                }
                break;
            case 'A':
                {
                    ((RHCampaignPCArray *)&m_114)->PushCounted(new RHPCDescription(profiles->FUN_0056d5d0(RHProfileText(
                        // STRING: GAME 0x006ab954
                        "Paysan A")), true));
                    ((SBArray<RHSaveGame *> *)&m_104)->Insert((RHSaveGame **)m_104.end(), 1, (RHSaveGame *const &)m_114.back());
                }
                break;
            case 'B':
                {
                    ((RHCampaignPCArray *)&m_114)->PushCounted(new RHPCDescription(profiles->FUN_0056d5d0(RHProfileText(
                        // STRING: GAME 0x006ab948
                        "Paysan B")), true));
                    ((SBArray<RHSaveGame *> *)&m_104)->Insert((RHSaveGame **)m_104.end(), 1, (RHSaveGame *const &)m_114.back());
                }
                break;
            case 'C':
                {
                    ((RHCampaignPCArray *)&m_114)->PushCounted(new RHPCDescription(profiles->FUN_0056d5d0(RHProfileText(
                        // STRING: GAME 0x006ab93c
                        "Paysan C")), true));
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

// Parked: receiver scheduling and early-exit vector cleanup differ.
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

// Parked: register allocation and a counted callee operand.
// STUB: GAME 0x004526f0
void RHCampaign::FUN_004526f0(std::vector<RHMission *> &missions)
{
    for (RHMission **it = missions.begin(); it != missions.end();)
    {
        RHMission *mission = *it;
        void *profile = mission->m_profile;
        if (*(int *)((char *)profile + 0x34) == 0 &&
            (unsigned short)mission->m_4 == *(unsigned short *)((char *)profile + 0x4c) - 1)
        {
            for (RHMission **other = missions.begin(); other != missions.end(); ++other)
                if (*other != mission)
                    (*other)->m_4 = 0;
            RHCampaignPointerArray<RHMission *> &values = (RHCampaignPointerArray<RHMission *> &)missions;
            RHMission **last = values.copy(values.end(), values.end(), values.begin());
            ((RHScriptFXArray *)&values)->Unk005008e0((void **)last, (void **)values.end());
            values.m_last = last;
            ((SBArray<RHSaveGame *> *)&values)->Insert((RHSaveGame **)last, 1, (RHSaveGame *const &)mission);
            break;
        }
        if ((unsigned short)mission->m_4 == *(unsigned short *)((char *)profile + 0x4c))
        {
            mission->m_4 = 0;
            it = missions.erase(it);
            if (mission->m_8 == 0 &&
                (*(int *)((char *)mission->m_profile + 0x34) == 5 ||
                 *(int *)((char *)mission->m_profile + 0x34) == 1))
                ((RHGameCampaignView *)this)->FUN_00456540(false, (RHGameMission *)mission);
        }
        else
            ++it;
    }
}

// Parked: container scheduling and counted helper operands.
// STUB: GAME 0x00452810
void RHCampaign::FUN_00452810(std::vector<RHMission *> &missions)
{
    RHCampaignMissionCandidates previous(missions);
    missions.erase(std::remove_if(missions.begin(), missions.end(), FUN_00452040), missions.end());
    if (missions.empty())
        ((RHCampaignMissionCandidates *)&missions)->Assign(previous);
}

// Parked: container scheduling and counted helper operands.
// STUB: GAME 0x00452a50
void RHCampaign::FUN_00452a50(std::vector<RHMission *> &missions)
{
    RHCampaignMissionCandidates previous(missions);
    missions.erase(std::remove_if(missions.begin(), missions.end(), FUN_00452090), missions.end());
    if (missions.empty())
        ((RHCampaignMissionCandidates *)&missions)->Assign(previous);
}

// FUNCTION: GAME 0x00452c90
void RHCampaign::FUN_00452c90(std::vector<RHMission *> &missions)
{
    for (int i = *(unsigned *)((char *)this + 0x18c) - 1; i >= 0; --i)
    {
        RHCampaignMissionList &previous = *(RHCampaignMissionList *)((char *)this + 0x184);
        previous.FUN_005c8e40(i);
        RHMission *value = previous.m_cursor->value;
        for (RHMission **position = missions.begin(); position != missions.end(); ++position)
        {
            if (*position == value)
            {
                (*position)->m_4 = 0;
                missions.erase(position);
                break;
            }
        }
        if (missions.size() <= 1)
            break;
    }
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
        std::_Sort(first, last, (bool (*)(RHMission *, RHMission *))0x0054c780, (RHMission **)0);
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

// FUNCTION: GAME 0x00452f20
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
            typedef void (RHProfilePointerList::*Clear)();
            Clear clear = &RHProfilePointerList::clear;
            (((RHProfilePointerList *)&missions)->*clear)();
            missions.m_dirty = true;
            if (!RHCampaignAccess(file, &count, 4, 1121))
                return false;
            for (unsigned i = 0; i < count; ++i)
            {
                FUN_00453940(file, value);
                typedef void (std::list<RHMission *>::*Push)(RHMission *const &);
                Push push = &std::list<RHMission *>::push_back;
                (((std::list<RHMission *> *)&missions)->*push)(value);
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

// FUNCTION: GAME 0x00453930
bool FUN_00453930(SBFile &file, RHMission &mission)
{
    return mission.Serialize(file);
}

// FUNCTION: GAME 0x00453940
bool FUN_00453940(SBFile &file, RHMission *&mission)
{
    unsigned index;
    if (!file.m_bLoading)
    {
        index = 0xffff;
        if (mission != 0)
        {
            unsigned id = *(unsigned *)mission->m_profile;
            unsigned i = 0;
            std::vector<RHMission> &missions = ((RHCampaign *)g_unk0x6c07fc)->m_144;
            for (RHMission *it = missions.begin(); it != missions.end(); ++it, ++i)
                if (*(unsigned *)it->m_profile == id)
                {
                    index = i;
                    break;
                }
        }
        file.Access(&index, 2);
        return true;
    }
    else
    {
        file.Access(&index, 2);
        if ((unsigned short)index == 0xffff)
        {
            mission = 0;
            return true;
        }
        mission = ((RHCampaign *)g_unk0x6c07fc)->m_144.begin() + (unsigned short)index;
    }
    return true;
}

class RHUnk0054cda0;
void FUN_0054cda0(RHUnk0054cda0 *value);

class RHSequenceElement;
class RHSeqList
{
public:
    static void CopyData(RHSequenceElement **destination, RHSequenceElement *const *source);
};

inline void RHCampaignPushMission(RHCampaignMissionList &missions, RHMission *const &value)
{
    RHCampaignMissionList::Node *head = missions.m_head;
    RHCampaignMissionList::Node *last = head->previous;
    RHCampaignMissionList::Node *node = (RHCampaignMissionList::Node *)operator new(0xc);
    node->next = head != 0 ? head : node;
    node->previous = last != 0 ? last : node;
    head->previous = node;
    node->previous->next = node;
    RHSeqList::CopyData((RHSequenceElement **)&node->value, (RHSequenceElement *const *)&value);
    ++missions.m_count;
    missions.m_dirty = true;
}

// Parked: effective only; the incremented list count lands in edx where the target uses ecx.
// STUB: GAME 0x004539f0
RHMission *RHCampaign::FUN_004539f0()
{
    if (m_17c)
    {
        m_174 = m_178;
        m_178 = m_17c;
        m_17c = 0;
    }
    else
    {
        ((RHGameCampaignView *)this)->FUN_00451a90();
        std::for_each((RHUnk0054cda0 **)m_154.begin(), (RHUnk0054cda0 **)m_154.end(), FUN_0054cda0);
        if (m_154.size() == 1 && !*((char *)m_154[0]->m_profile + 0x38))
        {
            FUN_00455650();
            m_174 = m_178;
            m_178 = m_154[0];
        }
        else
        {
            FUN_00455650();
            m_174 = m_178;
            m_178 = m_144.begin();
        }
    }
    if (m_178 != m_144.begin())
        ((RHGameCampaignView *)this)->FUN_00453b70((RHGameMission *)m_178);
    if (m_178 != m_144.begin())
    {
        RHCampaignMissionList &previous = *(RHCampaignMissionList *)((char *)this + 0x184);
        RHCampaignPushMission(previous, m_178);
        if ((int)previous.m_count > 3)
        {
            ((std::list<RHMission *> *)&previous)->pop_front();
            previous.m_dirty = true;
        }
    }
    return m_178;
}

__forceinline void RHCampaignInsertMission(std::vector<RHMission> &missions, const RHMission &value)
{
    typedef std::vector<RHMission> Missions;
    void (Missions::*insert)(RHMission *, unsigned int, const RHMission &) = &Missions::insert;
    (missions.*insert)(missions.end(), 1, value);
}

// FUNCTION: GAME 0x00453bd0
void RHCampaign::ForceNextMission(const std::string &first, const std::string &second, bool create)
{
    for (RHMission *mission = m_144.begin(); mission != m_144.end(); ++mission)
    {
        if (!_stricmp(mission->m_profile->m_04.c_str(), second.c_str()) &&
            !_stricmp(mission->m_profile->m_14.c_str(), first.c_str()))
        {
            m_17c = mission;
            FUN_00455650();
            return;
        }
    }
    if (create)
    {
        RHCampaignInsertMission(m_144, RHMission(RHUnk00436500GetProfileManager()->AddForcedMission(second, first, first)));
        m_17c = m_144.end() - 1;
    }
    FUN_00455650();
}

class RHCampaignUnk00457480
{
public:
    bool FUN_00457480(int value, void *container);
    bool FUN_004574b0(int action, void *container);
};

// FUNCTION: GAME 0x00453cd0
bool RHCampaign::FUN_00453cd0()
{
    RHMissionProfile *profile = m_17c->m_profile;
    unsigned int count = profile->m_74.GetSize();
    for (unsigned int i = 0; i < count; ++i)
    {
        if (!((RHCampaignUnk00457480 *)this)->FUN_00457480((int)profile->m_74.begin()[i], &m_1b0))
            return false;
    }
    for (unsigned long *action = profile->m_84.begin(); action != profile->m_84.end(); ++action)
    {
        if (!((RHCampaignUnk00457480 *)this)->FUN_004574b0(*action, &m_1b0))
            return false;
    }
    return true;
}

// FUNCTION: GAME 0x00453d60
int RHUnk00452030::FUN_00453d60(const void *value)
{
    void **first = *(void **volatile *)&m_108;
    unsigned count = first == 0 ? 0 : m_10c - first;
    for (unsigned i = 0; i < count; ++i)
        if (m_108[i] == value)
            return i;
    return -1;
}

// FUNCTION: GAME 0x00453da0
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
                    FUN_004552f0(elements, ((RHCampaignBeamArray *)&beamMes)->FUN_00457bc0(i), character);
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
                FUN_004552f0(elements, ((RHCampaignBeamArray *)&beamMes)->FUN_00457bc0(beamMe), character);
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
                g_unk0x6c0a50.m_progress += 10.0f / (int)characters;
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
                    g_unk0x6c0a50.m_progress += 10.0f / (int)characters;
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

// FUNCTION: GAME 0x00454a10
RHbeamMe::RHbeamMe(const RHbeamMe &value)
    : m_point(value.m_point), m_8(value.m_8), m_a(value.m_a), m_c(value.m_c),
      m_e(value.m_e), m_10(value.m_10), m_12(value.m_12), m_14(value.m_14),
      m_required(value.m_required), m_1c(value.m_1c), m_text(value.m_text)
{
}

// FUNCTION: GAME 0x00454bb0
RHbeamMe::~RHbeamMe() {}

// Parked: four-byte EH frame excess and annotated helper operands.
// STUB: GAME 0x00454c00
bool RHCampaign::FUN_00454c00(RHbeamMe beamMe, unsigned short character)
{
    RHCampaignCharacterData profile(*(RHCampaignCharacterData *)m_114[character]->m_profile);
    bool available0 = false;
    bool available1 = false;
    bool available2 = false;
    bool available3 = false;
    bool available4 = false;
    bool available5 = false;
    bool available6 = false;
    bool available7 = false;
    bool available8 = false;
    bool available9 = false;
    for (unsigned first = 0; first < 3; ++first)
    {
        switch (profile.m_48[first])
        {
        case 1: available3 = true; break;
        case 2:
        case 3: available6 = true; break;
        case 9: available7 = true; break;
        case 13:
        case 14: available8 = true; break;
        case 28: available2 = true; break;
        }
    }
    for (unsigned second = 0; second < 4; ++second)
    {
        switch (profile.m_5c[second])
        {
        case 9: available7 = true; break;
        case 21: available0 = true; break;
        case 22: available1 = true; break;
        case 23: available9 = true; break;
        case 25:
        case 26: available4 = true; break;
        case 27: available5 = true; break;
        case 28: available2 = true; break;
        }
    }
    unsigned requirements = beamMe.m_required;
    if ((requirements & 8) && !available3) return false;
    if ((requirements & 16) && !available4) return false;
    if ((requirements & 1) && !available0) return false;
    if ((requirements & 2) && !available1) return false;
    if ((requirements & 128) && !available7) return false;
    if ((requirements & 4) && !available2) return false;
    if ((requirements & 64) && !available6) return false;
    if ((requirements & 32) && !available5) return false;
    if ((requirements & 256) && !available8) return false;
    if ((requirements & 512) && !available9) return false;
    return true;
}

// SYNTHETIC: GAME 0x00455200
// ??1RHCampaignCharacterData@@QAE@XZ

// STUB: GAME 0x004552f0
void RHCampaign::FUN_004552f0(SBArray<RHElement *> &elements, RHbeamMe beamMe, unsigned short character)
{
    RHPCDescription *description = m_1b0[character];
    description->m_44 = true;
    if (*(int *)((char *)m_178->m_profile + 0x3c) == 8)
        description->m_3c = beamMe.m_12;
    else
        description->m_3c = -1;
    RHUnk0048f280 *actor = new RHUnk0048f280(description);
    ((RHEngineReinforcementCalls *)actor)->FUN_00491fd0(beamMe);
    RHElement *element = (RHElement *)actor;
    ((SBArray<RHSaveGame *> *)&elements)->Insert((RHSaveGame **)elements.m_last, 1,
                                                (RHSaveGame *const &)element);
    *(bool *)((char *)&elements + 0x14) = true;
}

// FUNCTION: GAME 0x004553f0
std::vector<RHPCDescription *> *RHCampaign::FUN_004553f0()
{
    return &m_1b0;
}

// Parked: vector growth and exception cleanup remain approximate.
// STUB: GAME 0x00455400
void RHScriptBatchCalls::Unk00455400(void *description)
{
    RHCampaign *campaign = (RHCampaign *)this;
    RHCampaignPointerArray<void *> &available =
        (RHCampaignPointerArray<void *> &)campaign->m_1b0;
    if (description == 0)
    {
        available.erase(available.begin(), available.end());
        description = campaign->m_114.front();
    }
    for (void **it = available.begin(); it != available.end(); ++it)
        if (*it == description)
            return;
    available.insert(available.end(), 1, description);
}

// FUNCTION: GAME 0x004555f0
void RHScriptBatchCalls::Unk004555f0(void *description)
{
    RHCampaign *campaign = (RHCampaign *)this;
    std::vector<RHPCDescription *>::iterator match = std::find(
        campaign->m_1b0.begin(), campaign->m_1b0.end(), (RHPCDescription *)description);
    if (match != campaign->m_1b0.end())
        campaign->m_1b0.erase(match);
}

// Parked: real vector insertion and EH cleanup still differ from the target.
// STUB: GAME 0x00455650
void RHCampaign::FUN_00455650()
{
    FUN_004559f0();
    RHCampaignPointerArray<RHPCDescription *> &available =
        (RHCampaignPointerArray<RHPCDescription *> &)m_1b0;
    for (RHPCDescription **it = m_114.begin(); it != m_114.end(); ++it)
    {
        if (*((char *)(*it)->m_profile + 0x35))
            available.insert(available.m_last, 1, *it);
    }
}

// FUNCTION: GAME 0x00455810
void RHCampaign::FUN_00455810()
{
    FUN_004559f0();
    for (std::vector<RHPCDescription *>::iterator first = m_114.begin(); first != m_114.end(); ++first)
    {
        if (*((char *)(*first)->m_profile + 0x35))
            m_1b0.push_back(*first);
    }
}

// FUNCTION: GAME 0x004559f0
void RHCampaign::FUN_004559f0()
{
    m_1b0.erase(m_1b0.begin(), m_1b0.end());
}

// FUNCTION: GAME 0x00455a40
bool RHCampaign::FUN_00455a40(RHPCDescription *character)
{
    if (std::find(m_1b0.begin(), m_1b0.end(), character) == m_1b0.end())
        return false;
    return true;
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

// FUNCTION: GAME 0x00455af0
unsigned short RHCampaign::FUN_00455af0()
{
    RHMission *selected = *(RHMission **)((char *)this + 0x180);
    if (selected != m_178 && selected)
    {
        void *profile = selected->m_profile;
        return *(unsigned short *)((char *)profile + 0x68) -
               *(unsigned short *)((char *)profile + 0x6a);
    }
    return *(unsigned short *)((char *)m_178->m_profile + 0x68);
}

// FUNCTION: GAME 0x00455b20
void RHCampaign::FUN_00455b20(RHPCDescription *character)
{
    std::vector<RHPCDescription *>::iterator first = m_114.begin();
    std::vector<RHPCDescription *>::iterator last = m_114.end();
    for (; first != last; ++first)
    {
        if (*first == character)
        {
            m_114.erase(first);
            return;
        }
    }
}

// FUNCTION: GAME 0x00455b80
void RHCampaign::FUN_00455b80(RHPCDescription *character)
{
    std::vector<RHPCDescription *>::iterator first = m_114.begin();
    std::vector<RHPCDescription *>::iterator last = m_114.end();
    for (; first != last; ++first)
    {
        if (*first == character)
        {
            SBArray<RHSaveGame *> &reservists = *(SBArray<RHSaveGame *> *)&m_124;
            reservists.Insert(reservists.m_last, 1, *(RHSaveGame **)first);
            m_114.erase(first);
            return;
        }
    }
}

// FUNCTION: GAME 0x00455bf0
void RHCampaign::FUN_00455bf0(RHPCDescription *character)
{
    std::vector<RHPCDescription *>::iterator first = m_124.begin();
    std::vector<RHPCDescription *>::iterator last = m_124.end();
    for (; first != last; ++first)
    {
        RHPCDescription *reservist = *first;
        if (reservist == character)
        {
            ((RHPCStatus *)reservist)->FUN_0051d550(0, 1.5f);
            ((RHPCStatus *)reservist)->FUN_0051d550(1, 1.5f);
            *(short *)((char *)reservist + 0x14) = (short)(*(short *)((char *)reservist + 0x14) * 1.5f);
            if (*(short *)((char *)reservist + 0x14) > 100)
                *(short *)((char *)reservist + 0x14) = 100;
            ((RHPCStatus *)reservist)->FUN_0055c390();
            reservist->m_3c = -1;
            SBArray<RHSaveGame *> &gang = *(SBArray<RHSaveGame *> *)&m_114;
            gang.Insert(gang.m_last, 1, *(RHSaveGame **)&reservist);
            m_124.erase(first);
            return;
        }
    }
}

// FUNCTION: GAME 0x00455d10
bool RHCampaign::FUN_00455d10(RHPCDescription *character)
{
    std::vector<RHPCDescription *>::iterator first = m_104.begin();
    std::vector<RHPCDescription *>::iterator last = m_104.end();
    for (; first != last; ++first)
    {
        if (*first == character)
            return true;
    }
    return false;
}

// FUNCTION: GAME 0x00455f00
void RHCampaign::FUN_00455f00(std::vector<RHMission *> &missions)
{
    RHMission *&selected = *(RHMission **)((char *)this + 0x180);
    if (missions.size() > 1)
    {
        FUN_004564e0(m_164);
        RHMission **found = std::find_if(missions.begin(), missions.end(), FUN_0054cc10);
        selected = found != missions.end() ? *found : 0;
        for (RHMission **it = missions.begin(); it != missions.end();)
        {
            RHMission *mission = *it;
            if (mission != selected && FUN_0054cc10(mission))
            {
                mission->m_4 = 0;
                it = missions.erase(it);
            }
            else if ((char)((RHCampaignMissionCalls *)mission)->FUN_0054cc20())
            {
                if (selected == 0)
                {
                    mission->m_4 = 0;
                    it = missions.erase(it);
                }
                else if (selected != mission)
                {
                    it = missions.erase(it);
                    SBArray<RHSaveGame *> &saved = *(SBArray<RHSaveGame *> *)&m_164;
                    saved.Insert(saved.m_last, 1, (RHSaveGame *const &)mission);
                }
                else
                    ++it;
            }
            else
                ++it;
        }
    }
    else if (missions.size() == 1 && (char)((RHCampaignMissionCalls *)missions.front())->FUN_0054cbf0())
        selected = missions.front();
    else
        selected = 0;
}

// FUNCTION: GAME 0x004560d0
void RHCampaign::FUN_004560d0(RHMission *mission)
{
    if (mission == 0)
        mission = m_17c;
    std::vector<RHMission *>::iterator it = m_154.begin();
    while (it != m_154.end())
    {
        RHMission *current = *it;
        if (current != mission)
        {
            if (*(unsigned short *)((char *)current->m_profile + 0x4c) < 1000 || current->m_4 == 0)
                ++current->m_4;
            if ((unsigned short)mission->m_4 > *(unsigned short *)((char *)mission->m_profile + 0x4c))
                ((RHGameCampaignView *)this)->FUN_00456e40(*(char *)((char *)mission->m_profile + 0x62));
            ++it;
        }
        else
        {
            m_17c = current;
            current->m_4 = 0;
            it = m_154.erase(it);
        }
    }
}

// FUNCTION: GAME 0x00456270
unsigned short RHGameCampaignView::FUN_00456270()
{
    RHPCDescription **first = *(RHPCDescription ***)((char *)this + 0x118);
    RHPCDescription **last = *(RHPCDescription ***)((char *)this + 0x11c);
    unsigned count = 0;
    for (; first != last; ++first)
    {
        if (*(char *)((char *)(*first)->m_profile + 0x35) == 0)
            ++count;
    }
    return count;
}

// FUNCTION: GAME 0x004562a0
void RHCampaign::FUN_004562a0()
{
    m_154.insert(m_154.end(), m_164.begin(), m_164.end());
    FUN_004564e0(m_164);
}

// FUNCTION: GAME 0x004564e0
void RHCampaign::FUN_004564e0(std::vector<RHMission *> &missions)
{
    for (RHMission **it = missions.begin(); it != missions.end(); ++it)
        (*it)->m_4 = 0;
    missions.erase(missions.begin(), missions.end());
}

// Parked: erase inlines the sector destructor with out-of-line 0x457990/0x457950 member vector dtors; ours inlines differently.
// STUB: GAME 0x00456820
void RHCampaign::CreateProductionSectors()
{
    std::vector<RHSectorProduction> &sectors = *(std::vector<RHSectorProduction> *)((char *)this + 0x74);
    sectors.erase(sectors.begin(), sectors.end());
    for (int type = 0; type < 13; ++type)
        ((RHCampaignProductionSectors &)sectors).Insert(sectors.end(), 1, RHSectorProduction(type));
}

// FUNCTION: GAME 0x00456a10
RHSectorProduction *RHCampaign::FUN_00456a10(unsigned long index)
{
    RHSectorProduction *first = ((RHCampaignProductionSectors *)((char *)this + 0x74))->begin();
    return first + index;
}

// FUNCTION: GAME 0x00456a30
bool FUN_00456a30(SBFile &file, RHSectorProduction &sector)
{
    return sector.Serialize(file);
}

// FUNCTION: GAME 0x00456a40
void RHCampaign::FUN_00456a40()
{
    RHCampaignProductionSectors &sectors = *(RHCampaignProductionSectors *)((char *)this + 0x74);
    for (RHSectorProduction *it = sectors.begin(); it != sectors.end(); ++it)
        it->FUN_00580d20(m_174);
}

// FUNCTION: GAME 0x00456a70
void RHCampaign::FUN_00456a70()
{
    RHCampaignProductionSectors &sectors = *(RHCampaignProductionSectors *)((char *)this + 0x74);
    for (RHSectorProduction *it = sectors.begin(); it != sectors.end(); ++it)
    {
        it->FUN_005804e0();
        it->FUN_005803c0();
    }
}

// FUNCTION: GAME 0x00456aa0
bool FUN_00456aa0(SBFile &file, unsigned long &value)
{
    if (file.Access(&value, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHCampaign.cpp", 2857, "Serialize failed reason is %s", reason);
        return false;
    }
    return true;
}

// Parked: vector construction helpers inline differently and enlarge the frame.
// STUB: GAME 0x00456af0
void RHCampaign::FUN_00456af0(const void *object)
{
    std::vector<unsigned long> &relics = *(std::vector<unsigned long> *)((char *)this + 0x84);
    unsigned long type = *(const unsigned long *)((const char *)object + 0xb0);
    relics.insert(relics.end(), 1, type);
}

// FUNCTION: GAME 0x00456d20
void RHScriptBatchCalls::FUN_00456d20()
{
    RHUnk00546050();
    unsigned index = 0;
    for (;; ++index)
    {
        RHEngine *engine = g_pEngine;
        RHElementActorPC **first = *(RHElementActorPC **volatile *)((char *)engine + 0x493c);
        if (index == (unsigned char)(first == 0 ? 0 : *(RHElementActorPC ***)((char *)engine + 0x4940) - first))
            break;
        RHElementActorPC *actor = (*(RHElementActorPC ***)((char *)g_pEngine + 0x493c))[(unsigned char)index];
        int action = actor->FUN_0049d590(4);
        if (action != -1)
        {
            if (*(unsigned short *)((char *)*(void **)((char *)actor + 0x600) + 0x28) != 0 &&
                *(int *)((char *)this + 0x98) >= 50)
                actor->FUN_0049d960(action);
            else
                actor->FUN_0049d890(action);
        }
    }
}

// FUNCTION: GAME 0x00456db0
unsigned RHCampaign::FUN_00456db0() const
{
    const RHMission *first = m_144.begin();
    const RHMission *last = m_144.end();
    bool finalWon;
    unsigned won = 0;
    unsigned total = 0;
    bool previousWon;
    finalWon = previousWon = false;
    for (; first != last; ++first)
    {
        const RHMissionProfile *profile = (const RHMissionProfile *)first->m_profile;
        if (profile->m_34 != 3 && profile->m_34 != 6)
        {
            ++total;
            if (first->m_8 == 1)
            {
                ++won;
                switch (profile->m_00)
                {
                case 0x4444:
                    previousWon = true;
                    break;
                case 0x4948:
                    finalWon = true;
                    break;
                }
            }
        }
    }
    if (finalWon == true)
        return 100;
    if (previousWon == true)
        return 95;
    return 100 * won / total;
}

// FUNCTION: GAME 0x00456e40
void RHGameCampaignView::FUN_00456e40(char value)
{
    if (value != -1)
        *((char *)this + 0x100) = value;
}

// STUB: GAME 0x00456e60
void RHCampaign::FUN_00456e60()
{
    std::string status;
    std::string accessible;
    std::string reason;
    SBSimpleUnk005f9510(g_unk0x006c13c0, "\n");
    SBSimpleUnk005f9510(g_unk0x006c13c0, "\n");
    SBSimpleUnk005f9510(g_unk0x006c13c0, " ---------- \n");
    SBSimpleUnk005f9510(g_unk0x006c13c0, "| Campaign |\n");
    SBSimpleUnk005f9510(g_unk0x006c13c0, " ---------- \n");
    SBSimpleUnk005f9510(g_unk0x006c13c0, " - Ransom : %d\n", ((RHUnk00452030 *)this)->Get(1));
    SBSimpleUnk005f9510(g_unk0x006c13c0, " - Gang size : %d\n", m_114.size());
    SBSimpleUnk005f9510(g_unk0x006c13c0, " - ARES : %d\n", *(signed char *)((char *)this + 0x100));
    SBSimpleUnk005f9510(g_unk0x006c13c0, "\n");
    SBSimpleUnk005f9510(g_unk0x006c13c0, "\n");
    SBSimpleUnk005f9510(g_unk0x006c13c0, " ---------- \n");
    SBSimpleUnk005f9510(g_unk0x006c13c0, "| Missions |\n");
    SBSimpleUnk005f9510(g_unk0x006c13c0, " ---------- \n");
    unsigned count = m_144.size();
    for (unsigned index = 0; index < count; ++index)
    {
        RHMission &mission = m_144[index];
        switch (mission.m_8)
        {
        case 0: status = "AVAILABLE"; break;
        case 1: status.assign("WON", 3); break;
        case 2: status = "LOST"; break;
        }
        if (((RHCampaignMissionCalls *)&mission)->FUN_0054c8a0(reason))
            accessible = "ACCESSIBLE";
        else
            accessible = "NOT ACCESSIBLE";
        RHMissionProfile *profile = (RHMissionProfile *)mission.m_profile;
        SBSimpleUnk005f9510(g_unk0x006c13c0, " - Mission[ %d ] \"%s\" (%s,%s) : %s - %s (%s)\n",
            index, profile->m_24.c_str(), profile->m_14.c_str(), profile->m_04.c_str(),
            status.c_str(), accessible.c_str(), reason.c_str());
    }
    SBSimpleUnk005f9510(g_unk0x006c13c0, "\n");
    SBSimpleUnk005f9510(g_unk0x006c13c0, "\n");
    SBSimpleUnk005f9510(g_unk0x006c13c0, " -------------- \n");
    SBSimpleUnk005f9510(g_unk0x006c13c0, "| Robin's gang |\n");
    SBSimpleUnk005f9510(g_unk0x006c13c0, " -------------- \n");
    count = m_114.size();
    for (unsigned character = 0; character < count; ++character)
    {
        RHPCDescription *description = m_114[character];
        const char *name = ((RHProfileText *)((char *)description->m_profile + 0x14))->c_str();
        unsigned short *displayName = *(unsigned short **)((char *)description + 0x30);
        SBSimpleUnk005f9510(g_unk0x006c13c0, " - Gang member[ %d ] \"%S\" (%s)\n",
            character, displayName ? displayName : (const unsigned short *)L"", name);
    }
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

// FUNCTION: GAME 0x00457480
bool RHCampaignUnk00457480::FUN_00457480(int value, void *container)
{
    int *first = *(int **)((char *)container + 4);
    int *last = *(int **)((char *)container + 8);
    while (first != last)
    {
        if (*(int *)((char *)*first + 0x40) == value)
            return true;
        ++first;
    }
    return false;
}

// FUNCTION: GAME 0x004574b0
bool RHCampaignUnk00457480::FUN_004574b0(int action, void *container)
{
    int *first = *(int **)((char *)container + 4);
    int *last = *(int **)((char *)container + 8);
    for (; first != last; ++first)
    {
        char *profile = *(char **)((char *)*first + 0x40);
        int *primary = (int *)(profile + 0x48);
        unsigned int i;
        for (i = 0; i < 3; ++i)
        {
            if (primary[i] == action)
                return true;
        }
        if (action == 2)
        {
            for (i = 0; i < 3; ++i)
            {
                if (primary[i] == 3)
                    return true;
            }
        }
        else if (action == 13)
        {
            for (i = 0; i < 3; ++i)
            {
                if (primary[i] == 14)
                    return true;
            }
        }
        int *secondary = (int *)(profile + 0x5c);
        for (i = 0; i < 4; ++i)
        {
            if (secondary[i] == action)
                return true;
        }
        if (action == 25)
        {
            for (i = 0; i < 4; ++i)
            {
                if (secondary[i] == 26)
                    return true;
            }
        }
    }
    return false;
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

// LIBRARY: GAME 0x004578e0
// ??1?$vector@V?$basic_string@GU?$char_traits@G@std@@V?$allocator@G@2@@std@@V?$allocator@V?$basic_string@GU?$char_traits@G@std@@V?$allocator@G@2@@std@@@2@@std@@QAE@XZ

// TEMPLATE: GAME 0x00457950
// ??1?$vector@UPoint@RHSectorProduction@@V?$allocator@UPoint@RHSectorProduction@@@std@@@std@@QAE@XZ

void RHCampaignUnk00457950::FUN_00457950()
{
    Value *last = m_last;
    for (Value *it = m_first; it != last; ++it)
        it->FUN_0051c0c0();
    operator delete(m_first);
    m_first = 0;
    m_last = 0;
    m_end = 0;
}

// ??1?$vector@VRHSectorProduction@@V?$allocator@VRHSectorProduction@@@std@@@std@@QAE@XZ
// FUNCTION: GAME 0x004579d0
void RHCampaignUnk004579d0::FUN_004579d0()
{
    RHSectorProduction *last = m_last;
    for (RHSectorProduction *it = m_first; it != last; ++it)
        it->~RHSectorProduction();
    operator delete(m_first);
    m_first = 0;
    m_last = 0;
    m_end = 0;
}

// TEMPLATE: GAME 0x00457a10
// ?size@?$vector@VRHMission@@V?$allocator@VRHMission@@@std@@@std@@QBEIXZ

// LIBRARY: GAME 0x00457a30
// ??4?$vector@HV?$allocator@H@std@@@std@@QAEAAV01@ABV01@@Z

// FUNCTION: GAME 0x00457bc0
RHbeamMe &RHCampaignBeamArray::FUN_00457bc0(unsigned beamMe)
{
    return m_first[beamMe];
}

// LIBRARY: GAME 0x00457be0
// ?_Freeze@?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AAEXXZ

// LIBRARY: GAME 0x00457cb0
// ?insert@?$vector@DV?$allocator@D@std@@@std@@QAEXPADIABD@Z

void RHCampaignByteArray::FUN_00457cb0(char *position, unsigned count, const char &value)
{
    ((std::vector<char> *)this)->insert(position, count, value);
}

// TEMPLATE: GAME 0x00457e80
// ?insert@?$vector@VRHMission@@V?$allocator@VRHMission@@@std@@@std@@QAEPAVRHMission@@PAV3@ABV3@@Z

void RHCampaignMissionValues::FUN_00457e80(RHMission *position, const RHMission &value)
{
    ((std::vector<RHMission> *)this)->insert(position, value);
}

// LIBRARY: GAME 0x004580a0
// ?capacity@?$vector@HV?$allocator@H@std@@@std@@QBEIXZ

// Parked: real sector vector insertion calls assignment where the target inlines it.
// STUB: GAME 0x004584e0
void RHCampaignProductionSectors::Insert(RHSectorProduction *position, unsigned count,
                                         const RHSectorProduction &value)
{
    ((std::vector<RHSectorProduction> *)this)->insert(position, count, value);
}

// TEMPLATE: GAME 0x00458800
// ?insert@?$vector@VRHMission@@V?$allocator@VRHMission@@@std@@@std@@QAEXPAVRHMission@@IABV3@@Z

// LIBRARY: GAME 0x00458af0
// ?_Ucopy@?$vector@V?$basic_string@GU?$char_traits@G@std@@V?$allocator@G@2@@std@@V?$allocator@V?$basic_string@GU?$char_traits@G@std@@V?$allocator@G@2@@std@@@2@@std@@IAEPAV?$basic_string@GU?$char_traits@G@std@@V?$allocator@G@2@@2@PBV32@0PAV32@@Z

// LIBRARY: GAME 0x00458b30
// ?_Ufill@?$vector@V?$basic_string@GU?$char_traits@G@std@@V?$allocator@G@2@@std@@V?$allocator@V?$basic_string@GU?$char_traits@G@std@@V?$allocator@G@2@@std@@@2@@std@@IAEXPAV?$basic_string@GU?$char_traits@G@std@@V?$allocator@G@2@@2@IABV32@@Z

// TEMPLATE: GAME 0x00458b60
// ?_Ucopy@?$vector@VRHMission@@V?$allocator@VRHMission@@@std@@@std@@IAEPAVRHMission@@PBV3@0PAV3@@Z

// TEMPLATE: GAME 0x00458ba0
// ?_Ufill@?$vector@VRHMission@@V?$allocator@VRHMission@@@std@@@std@@IAEXPAVRHMission@@IABV3@@Z

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

// Parked: cleanup needs a distinct _Destroy entity and an out-of-line Point-vector destructor.
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

// FUNCTION: GAME 0x00459130
void RHCampaignProductionSectors::Destroy(RHSectorProduction *first, RHSectorProduction *last)
{
    for (; first != last; ++first)
        first->~RHSectorProduction();
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

class RHCampaignWideVectorCalls : public std::vector<std::wstring>
{
public:
    typedef void (std::vector<std::wstring>::*Destroy)(std::wstring *, std::wstring *);
    static Destroy GetDestroy() { return &RHCampaignWideVectorCalls::_Destroy; }
};

// FUNCTION: GAME 0x004593f0
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
        RHCampaignWideString *destination = RHCampaignWideStrings::copy(list.end(), list.end(), list.begin());
        RHCampaignWideVectorCalls::Destroy destroy = RHCampaignWideVectorCalls::GetDestroy();
        (((std::vector<std::wstring> *)&list)->*destroy)((std::wstring *)destination, (std::wstring *)list.end());
        list.m_last = destination;
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
                list.FUN_00459620(list.end(), 1, value);
            }
            --count;
        }
    }
    return true;
}

// Parked: real wide vector insertion has register-allocation and scheduling differences.
// LIBRARY: GAME 0x00459620
void RHCampaignWideStrings::FUN_00459620(RHCampaignWideString *position, unsigned count,
                                        const RHCampaignWideString &value)
{
    ((std::vector<std::wstring> *)this)->insert((std::wstring *)position, count, (const std::wstring &)value);
}

// LIBRARY: GAME 0x00459910
// ?fill@std@@YAXPAV?$basic_string@GU?$char_traits@G@std@@V?$allocator@G@2@@1@0ABV21@@Z

// LIBRARY: GAME 0x00459a60
// ?copy_backward@std@@YAPAV?$basic_string@GU?$char_traits@G@std@@V?$allocator@G@2@@1@PAV21@00@Z

// TEMPLATE: GAME 0x00459d30
// ?_Construct@std@@YAXPAVRHSectorProduction@@ABV2@@Z

// TEMPLATE: GAME 0x00459d80
// ?_Construct@std@@YAXPAVRHMission@@ABV2@@Z

// FUNCTION: GAME 0x00459dd0
void *RHPCDescription::FUN_00459dd0(unsigned flags)
{
    FUN_00459fd0();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x00459df0
RHSectorProduction &RHSectorProduction::operator=(const RHSectorProduction &value)
{
    m_0 = value.m_0;
    m_4 = value.m_4;
    m_8 = value.m_8;
    m_points = value.m_points;
    m_occupants = value.m_occupants;
    m_2c = value.m_2c;
    m_2e = value.m_2e;
    m_30 = value.m_30;
    return *this;
}

// TEMPLATE: GAME 0x00459fa0
// ?_Destroy@?$vector@UPoint@RHSectorProduction@@V?$allocator@UPoint@RHSectorProduction@@@std@@@std@@IAEXPAUPoint@RHSectorProduction@@0@Z

// FUNCTION: GAME 0x0045a010
int RHCampaignCommandLine::FUN_0045a010(const RHProfileText &value)
{
    unsigned length = value.m_size;
    const char *chars = value.c_str();
    const std::string &text = *(const std::string *)this;
    return text.compare(0, text.size(), chars, length);
}

class RHUnk00457990
{
public:
    void FUN_00457990();
    char m_0[4];
    RHSectorProduction::Occupant *m_4;
    RHSectorProduction::Occupant *m_8;
    RHSectorProduction::Occupant *m_c;
};

// FUNCTION: GAME 0x00457990
void RHUnk00457990::FUN_00457990()
{
    typedef RHSectorProduction::Occupant Occupant;
    Occupant *last = m_8;
    Occupant *first = m_4;
    while (first != last)
    {
        first->~Occupant();
        ++first;
    }
    operator delete(m_4);
    m_4 = 0;
    m_8 = 0;
    m_c = 0;
}

// TEMPLATE: GAME 0x0045a060
// ??4?$vector@UPoint@RHSectorProduction@@V?$allocator@UPoint@RHSectorProduction@@@std@@@std@@QAEAAV01@ABV01@@Z
// TEMPLATE: GAME 0x0045a240
// ??4?$vector@UOccupant@RHSectorProduction@@V?$allocator@UOccupant@RHSectorProduction@@@std@@@std@@QAEAAV01@ABV01@@Z

// SYNTHETIC: GAME 0x0045a420
// RHSectorProduction::Occupant::`scalar deleting destructor'

// TEMPLATE: GAME 0x0045a440
// ?push_back@?$list@PAVRHMission@@V?$allocator@PAVRHMission@@@std@@@std@@QAEXABQAVRHMission@@@Z

void RHCampaignMissionList::FUN_0045a440(const RHMission *const &value)
{
    Node *next = m_head;
    Node *previous = next->previous;
    Node *node = (Node *)operator new(sizeof(Node));
    node->next = next ? next : node;
    node->previous = previous ? previous : node;
    next->previous = node;
    node->previous->next = node;
    RHMission **destination = &node->value;
    if (destination)
        *destination = (RHMission *)value;
    ++m_count;
}

// TEMPLATE: GAME 0x0045a490
// ?size@?$vector@UPoint@RHSectorProduction@@V?$allocator@UPoint@RHSectorProduction@@@std@@@std@@QBEIXZ

// TEMPLATE: GAME 0x0045a4b0
// ?_Ucopy@?$vector@UPoint@RHSectorProduction@@V?$allocator@UPoint@RHSectorProduction@@@std@@@std@@IAEPAUPoint@RHSectorProduction@@PBU34@0PAU34@@Z

// FUNCTION: GAME 0x0045a4f0
void FUN_0045a4f0(RHMission **first, RHMission **last,
                  bool (*compare)(RHMission *, RHMission *), int)
{
    if (last - first <= std::_SORT_MAX)
        std::_Insertion_sort(first, last, compare);
    else
    {
        RHMission **rangeLast = last;
        RHMission **rangeFirst = first;
        while (std::_SORT_MAX < rangeLast - rangeFirst)
        {
            RHMission **middle = std::_Unguarded_partition(rangeFirst, rangeLast,
                std::_Median(*rangeFirst, *(rangeFirst + (rangeLast - rangeFirst) / 2), *(rangeLast - 1), compare), compare);
            if (rangeLast - middle <= middle - rangeFirst)
            {
                std::_Sort(middle, rangeLast, compare, (RHMission **)0);
                rangeLast = middle;
            }
            else
            {
                std::_Sort(rangeFirst, middle, compare, (RHMission **)0);
                rangeFirst = middle;
            }
        }
        std::_Insertion_sort(first, first + std::_SORT_MAX, compare);
        for (first += std::_SORT_MAX; first != last; ++first)
            std::_Unguarded_insert(first, (RHMission *)*first, compare);
    }
}

// TEMPLATE: GAME 0x0045a790
// ?copy@std@@YAPAUPoint@RHSectorProduction@@PBU23@0PAU23@@Z

// TEMPLATE: GAME 0x0045a7e0
// ?_Construct@std@@YAXPAUPoint@RHSectorProduction@@ABU23@@Z

// TEMPLATE: GAME 0x0045a850
// ?_Construct@std@@YAXPAUOccupant@RHSectorProduction@@ABU23@@Z

// SYNTHETIC: GAME 0x0045a8e0
// ??4Point@RHSectorProduction@@QAEAAU01@ABU01@@Z

// TEMPLATE: GAME 0x0045a940
// ?_Sort@std@@YAXPAPAVRHMission@@0P6A_NPAV2@1@Z0@Z

void FUN_0045a940(RHMission **first, RHMission **last,
                  bool (*compare)(RHMission *, RHMission *), int)
{
    while (std::_SORT_MAX < last - first)
    {
        RHMission **middle = std::_Unguarded_partition(first, last,
            std::_Median(*first, *(first + (last - first) / 2), *(last - 1), compare), compare);
        if (last - middle <= middle - first)
        {
            FUN_0045a940(middle, last, compare, 0);
            last = middle;
        }
        else
        {
            FUN_0045a940(first, middle, compare, 0);
            first = middle;
        }
    }
}

// LIBRARY: GAME 0x004609a0
// ?erase@?$vector@HV?$allocator@H@std@@@std@@QAEPAHPAH0@Z

// STUB: GAME 0x004e3770
void RHEngine::FUN_004e3770(RHElement *element)
{
    char *info = RHCampaignField<char *>(element, 0x50);
    SBGeoPoint2D point(RHCampaignField<SBGeoPoint2D>(info, 0x24));
    point.m_x += rand() * 0.00003051850944757461548f * 10.0f - 5.0f;
    point.m_y += rand() * 0.00003051850944757461548f * 10.0f - 5.0f;
    char *position = RHCampaignField<char *>(element, 0x50) + 4;
    SBGeoBoundingBox2D box(*(SBGeoBoundingBox2D *)((RHUnkPathActorInfoBase *)position)->Unk0055fa10(
        RHCampaignField<int>(position, 0x88)));
    ((RHMobileUnk006091b0 *)((char *)&box + 4))->FUN_006091b0(SBGeoVector2D(point));
    RHPathObstacleGrid *grid = (RHPathObstacleGrid *)((char *)this + 0x11c);
    info = RHCampaignField<char *>(element, 0x50);
    if (grid->FUN_004f5750(box, RHCampaignField<unsigned short>(info, 0xde)) &&
        grid->FUN_004f9260(RHCampaignField<SBGeoPoint2D>(info, 0x24), point,
                          RHCampaignField<unsigned short>(info, 0xde)))
    {
        position = RHCampaignField<char *>(element, 0x50) + 4;
        for (unsigned offset = 0; offset < 12; offset += 4)
            RHCampaignField<undefined4>(position, 0x28 + offset) = RHCampaignField<undefined4>(position, 0x0c + offset);
        RHCampaignField<SBGeoPoint2D>(position, 0x3c) = RHCampaignField<SBGeoPoint2D>(position, 0x20);
        position = RHCampaignField<char *>(element, 0x50) + 4;
        RHCampaignField<SBGeoPoint2D>(position, 0x20) = point;
        SBGeoBoundingBox2D shifted = ((SBGeoBoundingBox2D *)((RHUnkPathActorInfoBase *)position)->Unk0055fa10(
            RHCampaignField<int>(position, 0x88)))->FUN_006090d0(SBGeoVector2D(point));
        ((RHMobileUnk00607da0 *)(position + 0xc0))->FUN_00607da0(*(RHMobileUnk00607da0 *)&shifted);
        RHCampaignField<int>(position, 4) = 2;
        ((RHBonusInfoBase *)(RHCampaignField<char *>(element, 0x50) + 4))->FUN_0055f290();
    }
    unsigned short direction = (rand() % 16) & 15;
    position = RHCampaignField<char *>(element, 0x50) + 4;
    RHCampaignField<unsigned short>(position, 0xd4) = direction;
    RHCampaignField<unsigned short>(position, 0xd6) = direction;
}

// LIBRARY: GAME 0x004e5820
// ?insert@?$vector@KV?$allocator@K@std@@@std@@QAEPAKPAKABK@Z

// TEMPLATE: GAME 0x004e6ba0
// ?_Destroy@?$vector@UOccupant@RHSectorProduction@@V?$allocator@UOccupant@RHSectorProduction@@@std@@@std@@IAEXPAUOccupant@RHSectorProduction@@0@Z

// TEMPLATE: GAME 0x004e6c10
// ?clear@?$list@PAVRHPlayerProfile@@V?$allocator@PAVRHPlayerProfile@@@std@@@std@@QAEXXZ

// FUNCTION: GAME 0x004e7210
void FUN_004e7210(RHMission **first, RHMission **last,
                  bool (*compare)(RHMission *, RHMission *), int)
{
    std::_Insertion_sort(first, last, compare);
}

// TEMPLATE: GAME 0x00507960
// ?erase@?$vector@VRHMission@@V?$allocator@VRHMission@@@std@@@std@@QAEPAVRHMission@@PAV3@0@Z

RHMission *RHCampaignMissionValues::FUN_00507960(RHMission *first, RHMission *last)
{
    return ((std::vector<RHMission> *)this)->erase(first, last);
}

// FUNCTION: GAME 0x0054c680
RHMission::RHMission()
{
    m_profile = 0;
    m_4 = 0;
    m_6 = 0;
    m_8 = 0;
}

// FUNCTION: GAME 0x0054c780
bool FUN_0054c780(RHMission *left, RHMission *right)
{
    RHMissionProfile *rightProfile = (RHMissionProfile *)right->m_profile;
    const char *rightName = ((const std::string *)&rightProfile->m_04)->c_str();
    RHMissionProfile *leftProfile = (RHMissionProfile *)left->m_profile;
    int order = strcmp(leftProfile->m_04.c_str(), rightName);
    if (order < 0)
        return true;
    if (order == 0)
        return *(unsigned short *)((char *)leftProfile + 0x50) < *(unsigned short *)((char *)rightProfile + 0x50) ? 1 : 0;
    return false;
}

// FUNCTION: GAME 0x0055bab0
RHPCDescription::RHPCDescription()
{
    ((RHPCStatus *)this)->RHPCStatus::RHPCStatus();
    m_profile = 0;
    m_44 = false;
}

// FUNCTION: GAME 0x0055bad0
RHPCDescription::RHPCDescription(void *profile, bool playable)
{
    ((RHPCStatus *)this)->RHPCStatus::RHPCStatus(*(const RHCharacterProfile *)profile, playable);
    m_profile = profile;
    m_44 = false;
}

// FUNCTION: GAME 0x0055bb30
bool RHPCDescription::FUN_0055bb30(SBFile &file)
{
    if (!((RHCampaignPCBase *)this)->FUN_0055bce0(file))
        return false;
    if (!RHUnk00436500GetProfileManager()->SerializeProfilePointer(file, *(const RHCharacterProfile **)&m_profile))
        return false;
    file.Access(&m_44, 1);
    return true;
}

// FUNCTION: GAME 0x0056d5d0
void *RHCampaignProfiles::FUN_0056d5d0(const RHProfileText &name)
{
    void **first = m_characters.begin();
    void **last = m_characters.end();
    for (void **it = first; it != last; ++it)
    {
        const std::string &text = *(const std::string *)((char *)*it + 0x14);
        if (text.compare(0, text.size(), name.c_str(), name.m_size) == 0)
            return *it;
    }
    return *first;
}

// FUNCTION: GAME 0x0056e210
RHSaveGame::Header::Header()
{
    m_00 = 0x52485347;
    m_04 = 0x30;
    m_08 = 0xbad;
}

// LIBRARY: GAME 0x00570330 FOLDED
// ??1?$vector@HV?$allocator@H@std@@@std@@QAE@XZ

// LIBRARY: GAME 0x00570330 FOLDED
// ??1?$vector@GV?$allocator@G@std@@@std@@QAE@XZ

void RHCampaignArrayOps::FUN_00570330()
{
    typedef std::vector<void *> Values;
    ((Values *)this)->~Values();
}

// FUNCTION: GAME 0x00580090
RHSectorProduction::RHSectorProduction(const RHSectorProduction &value)
    : m_0(value.m_0), m_4(value.m_4), m_8(value.m_8), m_points(value.m_points),
      m_occupants(value.m_occupants), m_2c(value.m_2c), m_2e(value.m_2e), m_30(value.m_30)
{
}

class RHUnk00580330
{
public:
    void FUN_00580330(int first, unsigned short second);
};

// FUNCTION: GAME 0x00580330
void RHUnk00580330::FUN_00580330(int first, unsigned short second)
{
    *(int *)((char *)this + 8) = first;
    *(unsigned short *)((char *)this + 4) = second;
    *(int *)((char *)first + 0xf4) = *(int *)this;
}

void EmitRHUnk00580330(RHUnk00580330 *a)
{
    a->FUN_00580330(0, 0);
}

// FUNCTION: GAME 0x00580050
RHSectorProduction::RHSectorProduction(int type)
    : m_0(type), m_4(0), m_8(0), m_2c(0), m_2e(0), m_30(0)
{
}

void RHCampaign::Emit(std::vector<RHMission *> &missions)
{
    FUN_00456db0();
    SelectMissions(false);
    CreateGang();
    SelectMissionsByLocation(missions);
    SelectMissionsByObligation(missions);
    GetNumberOfPeasantsToConvertToBlazons();
    FUN_00455a40(0);
    FUN_00455af0();
    FUN_00455b20(0);
    FUN_00455b80(0);
    FUN_004560d0(0);
    FUN_00455d10(0);
    FUN_00456a10(0);
    FUN_00456a40();
    FUN_00456a70();
    FUN_00456af0(0);
    RHUnk005f4fc0 file;
    SerializeAllCharacters(file);
    SBArray<RHElement *> elements;
    std::vector<RHbeamMe> beamMes;
    CreatePlayableCharacterSet(elements, beamMes);
    ((RHCampaignArrayOps *)&missions)->FUN_004580a0();
    ((RHCampaignArrayOps *)&missions)->FUN_00570330();
    RHCampaignUnk00457950 values;
    values.FUN_00457950();
    RHCampaignWideStrings strings;
    strings.FUN_00459620(0, 0, *(const RHCampaignWideString *)0);
    typedef std::vector<RHMission> Missions;
    unsigned (Missions::*volatile size)() const = &Missions::size;
    RHMission *(Missions::*volatile insertMission)(RHMission *, const RHMission &) = &Missions::insert;
    void (Missions::*volatile insertMissionCount)(RHMission *, unsigned, const RHMission &) = &Missions::insert;
    RHMission *(Missions::*volatile eraseMissions)(RHMission *, RHMission *) = &Missions::erase;
    typedef std::list<RHMission *> MissionList;
    void (RHProfilePointerList::*volatile clearMissions)() = &RHProfilePointerList::clear;
    void (MissionList::*volatile pushMission)(RHMission *const &) = &MissionList::push_back;
    typedef std::vector<unsigned long> Indices;
    unsigned long *(Indices::*volatile insertIndex)(unsigned long *, const unsigned long &) = &Indices::insert;
    typedef std::vector<char> Bytes;
    void (Bytes::*volatile insertByte)(char *, unsigned, const char &) = &Bytes::insert;
    typedef std::vector<std::wstring> WideStrings;
    void (WideStrings::*volatile insertWide)(std::wstring *, unsigned, const std::wstring &) = &WideStrings::insert;
    WideStrings wideStrings;
    WideStrings &(WideStrings::*volatile assignWide)(const WideStrings &) = &WideStrings::operator=;
    (wideStrings.*assignWide)(wideStrings);
    typedef RHSectorProduction::Point Point;
    Point &(Point::*volatile assign)(const Point &) = &Point::operator=;
    typedef std::vector<Point> Points;
    Points &(Points::*volatile assignPoints)(const Points &) = &Points::operator=;
}
