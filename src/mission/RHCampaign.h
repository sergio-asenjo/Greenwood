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

// SIZE 0x0c
class RHMission
{
public:
    void *m_profile; // 0x00
    unsigned short m_4; // 0x04
    unsigned short m_6; // 0x06
    int m_8; // 0x08
    RHMission();
    RHMission(const RHMission &value);
    bool Serialize(SBFile &file);
};

class RHUnk00452030
{
public:
    char m_pad0[0x108];
    void **m_108;
    void **m_10c;
    int Get(int index);
    int FUN_00453d60(const void *value);
};

extern RHUnk00452030 *g_unk0x6c07fc;

// SIZE 0x1c4
class RHCampaign
{
public:
    undefined m_pad0[0x104]; // 0x00
    std::vector<RHPCDescription *> m_104; // 0x104
    std::vector<RHPCDescription *> m_114; // 0x114
    std::vector<RHPCDescription *> m_124; // 0x124
    std::vector<std::wstring> m_134; // 0x134
    std::vector<RHMission> m_144; // 0x144
    std::vector<RHMission *> m_154; // 0x154
    std::vector<RHMission *> m_164; // 0x164
    RHMission *m_174; // 0x174
    RHMission *m_178; // 0x178
    RHMission *m_17c; // 0x17c
    undefined m_pad180[0x30]; // 0x180
    std::vector<RHPCDescription *> m_1b0; // 0x1b0
    bool m_1c0; // 0x1c0

    void CreateGang();
    void SelectMissions(bool forced);
    void SelectMissionsByLocation(std::vector<RHMission *> &missions);
    void SelectMissionsByObligation(std::vector<RHMission *> &missions);
    bool Serialize(SBFile &file);
    bool SerializeAllCharacters(SBFile &file);
    void CreatePlayableCharacterSet(SBArray<RHElement *> &elements, std::vector<RHbeamMe> &beamMes);
    void FUN_004526f0(std::vector<RHMission *> &missions);
    void FUN_00452810(std::vector<RHMission *> &missions);
    void FUN_00452a50(std::vector<RHMission *> &missions);
    void FUN_00452c90(std::vector<RHMission *> &missions);
    void FUN_00455f00(std::vector<RHMission *> &missions);
    void FUN_004564e0(std::vector<RHMission *> &missions);
    void FUN_00456e60();
    bool FUN_00454c00(RHbeamMe beamMe, unsigned short character);
    void FUN_004552f0(SBArray<RHElement *> &elements, RHbeamMe beamMe, unsigned short character);
    void FUN_004559f0();
    unsigned short GetNumberOfPeasantsToConvertToBlazons() const;
    bool LoadFromSaveGame(const RHSaveGame *saveGame);
    bool CreateBackup();
    bool CopyBackupTo(SBFile &file) const;
    void Emit(std::vector<RHMission *> &missions);
};

struct RHGameMission;

// SIZE 0x184
class RHGameCampaignView
{
public:
    undefined m_00[0x178]; // 0x00
    RHGameMission *m_178; // 0x178
    RHGameMission *m_17c; // 0x17c
    RHGameMission *m_180; // 0x180
    void FUN_00456540(bool flag, RHGameMission *mission);
};

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

class RHScriptFXArray
{
public:
    int grow;
    void **first;
    void **last;
    void **end;
    void **Unk004fe420(void **first, void **last, void **destination);
    void Unk004fe450(void **destination, unsigned count, void *const &value);
    void Unk005008e0(void **first, void **last);
};

class RHFastFindGateArray : public RHScriptFXArray
{
public:
    unsigned FUN_0059fbc0()
    {
        typedef unsigned (std::vector<unsigned long>::*Size)() const;
        Size size = &std::vector<unsigned long>::size;
        return (((const std::vector<unsigned long> *)this)->*size)();
    }
};

template<class T>
class RHCampaignPointerArray
{
public:
    char m_allocator[4];
    T *m_first;
    T *m_last;
    T *m_end;
    T *begin() { return m_first; }
    T *end() { return m_last; }
    unsigned size() { return m_first == 0 ? 0 : m_last - m_first; }
    T *erase(T *first, T *last)
    {
        T *next = copy(last, end(), first);
        Destroy(next, end());
        m_last = next;
        return first;
    }
    void Destroy(T *first, T *last)
    {
        for (; first != last; ++first)
            ;
    }
    static T *copy(T *source, T *last, T *destination)
    {
        while (source != last)
        {
            *destination = *source;
            ++destination;
            ++source;
        }
        return destination;
    }
    void insert(T *position, unsigned count, const T &value)
    {
        RHScriptFXArray *array = (RHScriptFXArray *)this;
        RHFastFindGateArray *sizes = (RHFastFindGateArray *)this;
        if ((unsigned)(m_end - m_last) < count)
        {
            unsigned grow = count < size() ? size() : count;
            int capacity = sizes->FUN_0059fbc0() + grow;
            T *storage = std::_Allocate(capacity, (T *)0);
            T *destination = (T *)array->Unk004fe420((void **)m_first, (void **)position, (void **)storage);
            array->Unk004fe450((void **)destination, count, reinterpret_cast<void *const &>(value));
            array->Unk004fe420((void **)position, (void **)m_last, (void **)(destination + count));
            array->Unk005008e0((void **)m_first, (void **)m_last);
            operator delete(m_first);
            m_end = storage + capacity;
            m_last = storage + sizes->FUN_0059fbc0() + count;
            m_first = storage;
        }
        else if ((unsigned)(m_last - position) < count)
        {
            array->Unk004fe420((void **)position, (void **)m_last, (void **)(position + count));
            array->Unk004fe450((void **)m_last, count - (m_last - position), reinterpret_cast<void *const &>(value));
            T *last = m_last;
            for (T *destination = position; destination != last; ++destination)
                *destination = value;
            m_last += count;
        }
        else if (count > 0)
        {
            array->Unk004fe420((void **)(m_last - count), (void **)m_last, (void **)m_last);
            T *source = m_last - count;
            T *destination = m_last;
            while (position != source)
                *--destination = *--source;
            for (destination = position; destination != position + count; ++destination)
                *destination = value;
            m_last += count;
        }
    }
};

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
