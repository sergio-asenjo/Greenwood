#ifndef RHCAMPAIGN_H
#define RHCAMPAIGN_H

#include "RHSaveGame.h"
#include "RHCivilianProfile.h"
#include "RHSectorProduction.h"
#include "Decomp.h"
#include <vector>
#include <string>

class RHPCDescription;
class RHElement;
struct RHbeamMe;
class RHEngine;
template<class T> class SBArray;

inline const char *RHCampaignStringChars(const std::string &value)
{
    const char *chars = ((const SBString *)&value)->m_chars;
    return chars ? chars : "";
}

#include "RHMission.h"

#include "RHCampaignValueCalls.h"

extern RHUnk00452030 *g_unk0x6c07fc;

#include "RHCampaignCore.h"

#include "RHGameCampaignView.h"

bool FUN_00452040(RHMission *mission);
bool FUN_00452090(RHMission *mission);

bool FUN_00453da0(SBFile &file, void *&value);
void FUN_0045a4f0(RHMission **first, RHMission **last,
                  bool (*compare)(RHMission *, RHMission *), int depth);
bool FUN_0054c780(RHMission *left, RHMission *right);
void FUN_0045a940(RHMission **first, RHMission **last, bool (*compare)(RHMission *, RHMission *), int depth);
void FUN_004e7210(RHMission **first, RHMission **last, bool (*compare)(RHMission *, RHMission *), int depth);
bool FUN_00458be0(SBFile &file, std::vector<RHPCDescription *> &values,
                  bool (*serialize)(SBFile &, RHPCDescription *&));
bool FUN_00459160(SBFile &file, std::vector<unsigned long> &values,
                  bool (*serialize)(SBFile &, unsigned long &));

class RHUnk0054e250List;
bool RHUnk004593f0SerializeList(SBFile &file, RHUnk0054e250List &values, void *serialize);

#include "RHCampaignPointerArray.h"

class RHCampaignWideString
{
public:
    std::allocator<unsigned short> m_allocator;
    unsigned short *m_chars;
    unsigned m_length;
    unsigned m_capacity;
    RHCampaignWideString(const std::allocator<unsigned short> &allocator = std::allocator<unsigned short>())
        : m_allocator(allocator) { Tidy(false); }
    void Tidy(bool built);
    RHCampaignWideString &operator=(const RHCampaignWideString &value)
    {
        typedef std::wstring &(std::wstring::*AssignCall)(const std::wstring &, unsigned, unsigned);
        AssignCall assign = &std::wstring::assign;
        (((std::wstring *)this)->*assign)((const std::wstring &)value, 0, std::wstring::npos);
        return *this;
    }
    ~RHCampaignWideString()
    {
        if (m_chars == 0)
            ;
        else if (*((unsigned char *)m_chars - 1) == 0 || *((unsigned char *)m_chars - 1) == 255)
            m_allocator.deallocate(m_chars - 1, m_capacity + 2);
        else
            --*((unsigned char *)m_chars - 1);
        m_chars = 0, m_length = 0, m_capacity = 0;
    }
};

class RHCampaignWideStrings
{
public:
    char m_allocator[4];
    RHCampaignWideString *m_first;
    RHCampaignWideString *m_last;
    RHCampaignWideString *m_end;
    RHCampaignWideString *begin() { return m_first; }
    RHCampaignWideString *end() { return m_last; }
    unsigned size() { return m_first == 0 ? 0 : m_last - m_first; }
    void Destroy(RHCampaignWideString *first, RHCampaignWideString *last);
    void Insert(RHCampaignWideString *position, unsigned count, const RHCampaignWideString &value);
    void FUN_00459620(RHCampaignWideString *position, unsigned count, const RHCampaignWideString &value);
    void erase(RHCampaignWideString *first, RHCampaignWideString *last)
    {
        RHCampaignWideString *destination = copy(last, end(), first);
        Destroy(destination, end());
        m_last = destination;
    }
    static RHCampaignWideString *copy(RHCampaignWideString *source, RHCampaignWideString *last,
                                       RHCampaignWideString *destination)
    {
        while (source != last)
        {
            *destination = *source;
            ++destination;
            ++source;
        }
        return destination;
    }
};

// SIZE 0x60c
class RHUnk0048f280
{
public:
    RHUnk0048f280(void *description);
    undefined m_data[0x60c]; // 0x00
};

class RHEngineReinforcementCalls
{
public:
    void FUN_00491fd0(const RHbeamMe &beamMe);
};

class RHCampaignProductionSectors
{
public:
    char m_allocator[4];
    RHSectorProduction *m_first;
    RHSectorProduction *m_last;
    RHSectorProduction *m_end;
    RHSectorProduction *begin() { return m_first; }
    RHSectorProduction *end() { return m_last; }
    unsigned size() { return m_first == 0 ? 0 : m_last - m_first; }
    void Destroy(RHSectorProduction *first, RHSectorProduction *last);
    void Insert(RHSectorProduction *position, unsigned count, const RHSectorProduction &value);
    void erase(RHSectorProduction *first, RHSectorProduction *last)
    {
        RHSectorProduction *next = copy(last, end(), first);
        Destroy(next, end());
        m_last = next;
    }
    static RHSectorProduction *copy(RHSectorProduction *source, RHSectorProduction *last,
                                     RHSectorProduction *destination)
    {
        while (source != last)
        {
            *destination = *source;
            ++destination;
            ++source;
        }
        return destination;
    }
};

class RHCampaignUnk00457950
{
public:
    struct Value
    {
        char m_data[16];
        void FUN_0051c0c0();
    };
    char m_allocator[4];
    Value *m_first;
    Value *m_last;
    Value *m_end;
    void FUN_00457950();
};

class RHCampaignUnk004579d0
{
public:
    char m_allocator[4];
    RHSectorProduction *m_first;
    RHSectorProduction *m_last;
    RHSectorProduction *m_end;
    void FUN_004579d0();
};

bool FUN_00458e70(SBFile &file, RHCampaignProductionSectors &values,
                  bool (*serialize)(SBFile &, RHSectorProduction &));

class RHCampaignNarrowString
{
public:
    char m_allocator;
    char *m_chars;
    unsigned m_size;
    unsigned m_capacity;
    RHCampaignNarrowString(const char *value,
                           const std::allocator<char> &allocator = std::allocator<char>())
    {
        m_allocator = *(const char *)&allocator;
        m_chars = 0, m_size = 0, m_capacity = 0;
        unsigned size = strlen(value);
        if (((RHProfileText *)this)->FUN_00402280(size, true))
        {
            memcpy(m_chars, value, size);
            ((RHProfileText *)this)->FUN_00402260(size);
        }
    }
    ~RHCampaignNarrowString()
    {
        if (m_chars == 0)
            ;
        else if (*((unsigned char *)m_chars - 1) == 0 || *((unsigned char *)m_chars - 1) == 255)
            operator delete(m_chars - 1);
        else
            --*((unsigned char *)m_chars - 1);
        m_chars = 0, m_size = 0, m_capacity = 0;
    }
};

#include "RHCampaignTypes.h"

#endif
