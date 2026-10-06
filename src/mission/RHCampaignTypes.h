#ifndef RHCAMPAIGNTYPES_H
#define RHCAMPAIGNTYPES_H

#include "RHMissionProfile.h"
#include <list>

template<class T>
class SBArray
{
public:
    int m_grow;
    T *m_first;
    T *m_last;
    T *m_end;
    void Insert(T *position, unsigned count, const T &value);
};

class RHPCDescription
{
public:
    char m_0[0x3c];
    short m_3c;
    char m_3e[2];
    void *m_profile;
    bool m_44;
    char m_45[3];
    RHPCDescription();
    RHPCDescription(void *profile, bool playable);
    ~RHPCDescription();
    void *FUN_00459dd0(unsigned flags);
    bool FUN_0055bb30(SBFile &file);
};

class RHCampaignArrayOps
{
public:
    void FUN_0044ea70();
    unsigned FUN_004580a0();
    void FUN_00457a30(const RHCampaignArrayOps &value);
    void FUN_00570330();
};

class RHCampaignMissionValues
{
public:
    char m_allocator[4];
    RHMission *m_first;
    RHMission *m_last;
    RHMission *m_end;
    RHMission *begin() { return m_first; }
    RHMission *end() { return m_last; }
    unsigned size() { return m_first == 0 ? 0 : m_last - m_first; }
    void FUN_00507960(RHMission *first, RHMission *last);
    void FUN_00457e80(RHMission *position, const RHMission &value);
};

bool FUN_00453930(SBFile &file, RHMission &mission);
bool FUN_00453940(SBFile &file, RHMission *&mission);
bool FUN_00456a30(SBFile &file, RHSectorProduction &sector);
bool FUN_00456aa0(SBFile &file, unsigned long &value);
void RHSerializeName(SBFile &file, const char *name);

__forceinline bool RHCampaignAccess(SBFile &file, void *value, unsigned size, int line)
{
    if (file.Access(value, size) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHCampaign.cpp", line, "Serialize failed reason is %s", reason);
        return false;
    }
    return true;
}

__forceinline bool RHCampaignSerializeMissions(SBFile &file, RHCampaignMissionValues &values)
{
    if (!file.m_bLoading)
    {
        unsigned count = values.size();
        if (!RHCampaignAccess(file, &count, 4, 39))
            return false;
        for (RHMission *it = values.begin(); it != values.end(); ++it)
            if (!FUN_00453930(file, *it))
                return false;
    }
    else
    {
        RHCampaignMissionValues &list = values;
        list.FUN_00507960(list.begin(), list.end());
        unsigned count;
        if (!RHCampaignAccess(file, &count, 4, 60))
            return false;
        while (count > 0)
        {
            RHMission value;
            if (!FUN_00453930(file, value))
                return false;
            list.FUN_00457e80(list.end(), value);
            --count;
        }
    }
    return true;
}

template<class T>
__forceinline bool RHCampaignSerializePointers(SBFile &file, std::vector<T *> &values,
                                         bool (*serialize)(SBFile &, T *&), bool externalSize)
{
    if (!file.m_bLoading)
    {
        unsigned count = externalSize ? ((RHFastFindGateArray *)&values)->FUN_0059fbc0() : values.size();
        if (!RHCampaignAccess(file, &count, 4, 39))
            return false;
        for (T **it = values.begin(); it != values.end(); ++it)
            if (!serialize(file, *it))
                return false;
    }
    else
    {
        std::vector<T *> &list = values;
        ((RHCampaignArrayOps *)&list)->FUN_0044ea70();
        unsigned count;
        if (!RHCampaignAccess(file, &count, 4, 60))
            return false;
        while (count > 0)
        {
            T *value;
            if (!serialize(file, value))
                return false;
            ((RHMissionArrayStorage *)&list)->FUN_004e5820(list.end(), (const unsigned long &)value);
            --count;
        }
    }
    return true;
}

class RHCampaignMissionList
{
public:
    struct Node
    {
        Node *next;
        Node *previous;
        RHMission *value;
    };
    char m_allocator[4];
    Node *m_head;
    unsigned m_count;
    Node *m_cursor;
    bool m_dirty;
    void FUN_004e6c10();
    void FUN_0045a440(const RHMission *const &value);
    void FUN_005c8e40(unsigned index);
};

void **FUN_004598e0(void **first, void **last, void **destination);

class RHCampaignMissionCandidates
{
public:
    std::allocator<RHMission *> m_allocator;
    RHMission **m_first;
    RHMission **m_last;
    RHMission **m_end;
    RHCampaignMissionCandidates(const std::allocator<RHMission *> &allocator = std::allocator<RHMission *>())
        : m_allocator(allocator), m_first(0), m_last(0), m_end(0) {}
    ~RHCampaignMissionCandidates()
    {
        ((RHScriptFXArray *)this)->Unk005008e0((void **)begin(), (void **)end());
        operator delete(begin());
        m_first = 0, m_last = 0, m_end = 0;
    }
    operator std::vector<RHMission *> &() { return *(std::vector<RHMission *> *)this; }
    RHMission **begin() { return m_first; }
    RHMission **end() { return m_last; }
    unsigned size() { return m_first == 0 ? 0 : m_last - m_first; }
    RHMission *&operator[](unsigned index) { return m_first[index]; }
    __forceinline void Assign(const std::vector<RHMission *> &value)
    {
        if ((const void *)this != &value)
        {
            RHFastFindGateArray *source = (RHFastFindGateArray *)&value;
            RHFastFindGateArray *sizes = (RHFastFindGateArray *)this;
            RHCampaignPointerArray<RHMission *> *storage = (RHCampaignPointerArray<RHMission *> *)this;
            RHScriptFXArray *array = (RHScriptFXArray *)this;
            if (source->FUN_0059fbc0() <= sizes->FUN_0059fbc0())
            {
                RHMission **last = (RHMission **)FUN_004598e0((void **)value.begin(), (void **)value.end(), (void **)begin());
                array->Unk005008e0((void **)last, (void **)end());
                unsigned nextSize = source->FUN_0059fbc0();
                storage->m_last = begin() + nextSize;
            }
            else
            {
                unsigned sourceSize = source->FUN_0059fbc0();
                if (sourceSize <= ((RHCampaignArrayOps *)this)->FUN_004580a0())
                {
                    RHMission *const *middle = value.begin() + sizes->FUN_0059fbc0();
                    FUN_004598e0((void **)value.begin(), (void **)middle, (void **)begin());
                    array->Unk004fe420((void **)middle, (void **)value.end(), (void **)end());
                    unsigned nextSize = source->FUN_0059fbc0();
                    storage->m_last = begin() + nextSize;
                }
                else
                {
                    array->Unk005008e0((void **)begin(), (void **)end());
                    operator delete(begin());
                    storage->m_first = std::_Allocate((int)source->FUN_0059fbc0(), (RHMission **)0);
                    storage->m_last = (RHMission **)array->Unk004fe420((void **)value.begin(), (void **)value.end(), (void **)begin());
                    storage->m_end = end();
                }
            }
        }
    }
};

class RHCampaignText
{
public:
    char m_allocator;
    char *m_chars;
    unsigned m_length;
    unsigned m_capacity;
    RHCampaignText(const char *value, const std::allocator<char> &allocator = std::allocator<char>())
    {
        m_allocator = *(const char *)&allocator;
        ((RHProfileText *)this)->FUN_00401ee0(false);
        FUN_004021c0(value, strlen(value));
    }
    ~RHCampaignText() { ((RHProfileText *)this)->FUN_00401ee0(true); }
    operator const RHProfileText &() const { return *(const RHProfileText *)this; }
    void FUN_004021c0(const char *value, unsigned length);
};

class RHCampaignPCArray
{
public:
    char m_allocator[4];
    RHPCDescription **m_first;
    RHPCDescription **m_last;
    RHPCDescription **m_end;
    void Push(const RHPCDescription *const &value)
    {
        ((RHMissionArrayStorage *)this)->FUN_004e5820(m_last, (const unsigned long &)value);
    }
    void PushCounted(const RHPCDescription *const &value)
    {
        ((SBArray<RHSaveGame *> *)this)->Insert((RHSaveGame **)m_last, 1, (RHSaveGame *const &)value);
    }
};

class RHCampaignProfiles
{
public:
    char m_0[0x10];
    RHCampaignPointerArray<void *> m_characters;
    char m_20[0x50];
    RHCampaignProfiles();
    ~RHCampaignProfiles();
    void *FUN_0056d5d0(const RHProfileText &name, bool required);
};

class RHCampaignCommandLine
{
public:
    char m_allocator[4];
    char *m_chars;
    unsigned m_length;
    unsigned m_capacity;
    int FUN_0045a010(const RHProfileText &value);
    void FUN_00457be0();
    char operator[](unsigned index)
    {
        if (m_length >= index && m_chars != 0)
        {
            FUN_00457be0();
            return m_chars[index];
        }
        return *"";
    }
};

extern char g_unk0x6c0560[4];
extern RHCampaignCommandLine g_unk0x6c05cc;
extern RHCampaignProfiles *g_unk0x6c0e84;

struct RHbeamMe
{
    SBGeoPoint2D m_point;
    unsigned short m_8;
    unsigned short m_a;
    unsigned short m_c;
    char m_e;
    char m_f;
    unsigned short m_10;
    unsigned short m_12;
    unsigned short m_14;
    char m_16[2];
    int m_required;
    int m_1c;
    RHProfileText m_text;
    RHbeamMe() {}
    RHbeamMe(const RHbeamMe &value);
    RHbeamMe &operator=(const RHbeamMe &value)
    {
        m_point = value.m_point;
        m_8 = value.m_8;
        m_a = value.m_a;
        m_c = value.m_c;
        m_e = value.m_e;
        m_10 = value.m_10;
        m_12 = value.m_12;
        m_14 = value.m_14;
        m_required = value.m_required;
        m_1c = value.m_1c;
        m_text.FUN_00401ce0((const std::string &)value.m_text, 0, std::string::npos);
        return *this;
    }
};

class RHCampaignBeamArray
{
public:
    RHbeamMe &FUN_00457bc0(unsigned beamMe, unsigned character);
};

struct RHScriptNode
{
    RHScriptNode *next;
    RHScriptNode *prev;
    void *data;
};

struct RHScriptIter
{
    RHScriptNode *node;
    RHScriptIter(RHScriptNode *value) : node(value) {}
};

class RHUnk0046eb30
{
public:
    RHScriptIter erase(RHScriptIter position);
    RHScriptNode *Unk0059f720(RHScriptNode *next, RHScriptNode *previous);
};

void FUN_0044e940(unsigned short *destination, const unsigned short *value);

template<bool InlineHead>
class RHCampaignIndexList
{
public:
    std::allocator<unsigned short> m_allocator;
    RHScriptNode *m_head;
    unsigned m_count;
    RHCampaignIndexList(const std::allocator<unsigned short> &allocator = std::allocator<unsigned short>())
        : m_allocator(allocator)
    {
        if (InlineHead)
        {
            m_head = (RHScriptNode *)operator new(12);
            m_head->next = m_head;
            m_head->prev = m_head;
        }
        else
            m_head = ((RHUnk0046eb30 *)this)->Unk0059f720(0, 0);
        m_count = 0;
    }
    ~RHCampaignIndexList()
    {
        RHScriptNode *it = m_head->next;
        while (it != m_head)
        {
            RHScriptNode *node = it;
            it = it->next;
            if (InlineHead)
                ((RHUnk0046eb30 *)this)->erase(RHScriptIter(node));
            else
                Remove(node);
        }
        operator delete(m_head);
    }
    void Remove(RHScriptNode *node)
    {
        node->prev->next = node->next;
        node->next->prev = node->prev;
        operator delete(node);
        --m_count;
    }
    unsigned short Front() { return *(unsigned short *)&m_head->next->data; }
    RHScriptIter FUN_004fe2e0(RHScriptIter position, const unsigned short &value);
    void Push(const unsigned short &value)
    {
        if (InlineHead)
        {
            RHScriptNode *node = ((RHUnk0046eb30 *)this)->Unk0059f720(m_head, m_head->prev);
            m_head->prev = node;
            node->prev->next = node;
            FUN_0044e940((unsigned short *)&node->data, &value);
            ++m_count;
        }
        else
            FUN_004fe2e0(RHScriptIter(m_head), value);
    }
};

class RHCampaignByteArray
{
public:
    std::allocator<char> m_allocator;
    char *m_first;
    char *m_last;
    char *m_end;
    RHCampaignByteArray(unsigned count, char value,
                         const std::allocator<char> &allocator = std::allocator<char>())
        : m_allocator(allocator), m_first(0), m_last(0), m_end(0)
    {
        if (count > 0)
            FUN_00457cb0(0, count, value);
    }
    ~RHCampaignByteArray()
    {
        operator delete(m_first);
        m_first = 0, m_last = 0, m_end = 0;
    }
    void FUN_00457cb0(char *position, unsigned count, const char &value);
    char &operator[](unsigned index) { return m_first[index]; }
};

class RHCampaignLoadingProgress
{
public:
    char m_0[8];
    float m_progress;
    void FUN_00523300();
};

class RHEngine
{
public:
    void FUN_004e3770(RHElement *element);
};

extern RHEngine *g_pEngine;
extern RHCampaignLoadingProgress g_unk0x6c0a50;
extern float g_unk0x00677438;

#endif
