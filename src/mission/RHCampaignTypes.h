#ifndef RHCAMPAIGNTYPES_H
#define RHCAMPAIGNTYPES_H

#include "RHMissionProfile.h"
#include "RHCampaignCommandLine.h"
#include "RHMission.h"
#include <list>

class RHSectorProduction;

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

// SIZE 0x48
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
    void FUN_00459fd0();
    bool FUN_0055bb30(SBFile &file);
};

#include "RHCampaignArrayOps.h"

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
    RHMission *FUN_00507960(RHMission *first, RHMission *last);
    void FUN_00457e80(RHMission *position, const RHMission &value);
};

bool FUN_00453930(SBFile &file, RHMission &mission);
bool FUN_00453940(SBFile &file, RHMission *&mission);
char FUN_0054cc10(RHMission *mission);

typedef RHMission RHCampaignMissionCalls;

extern char g_unk0x006c13c0[16];
void SBSimpleUnk005f9510(void *, const char *, ...);
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
        typedef RHMission *(std::vector<RHMission>::*Erase)(RHMission *, RHMission *);
        Erase erase = &std::vector<RHMission>::erase;
        (((std::vector<RHMission> *)&list)->*erase)(list.begin(), list.end());
        unsigned count;
        if (!RHCampaignAccess(file, &count, 4, 60))
            return false;
        while (count > 0)
        {
            RHMission value;
            if (!FUN_00453930(file, value))
                return false;
            typedef RHMission *(std::vector<RHMission>::*Insert)(RHMission *, const RHMission &);
            Insert insert = &std::vector<RHMission>::insert;
            (((std::vector<RHMission> *)&list)->*insert)(list.end(), value);
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
            typedef unsigned long *(std::vector<unsigned long>::*Insert)(unsigned long *, const unsigned long &);
            Insert insert = &std::vector<unsigned long>::insert;
            (((std::vector<unsigned long> *)&list)->*insert)((unsigned long *)list.end(), (const unsigned long &)value);
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
    void FUN_0045a440(const RHMission *const &value);
    void FUN_005c8e40(unsigned index);
};

void **FUN_004598e0(void **first, void **last, void **destination);

// SIZE 0x10
class RHCampaignMissionCandidates
{
public:
    std::allocator<RHMission *> m_allocator; // 0x00
    RHMission **m_first; // 0x04
    RHMission **m_last; // 0x08
    RHMission **m_end; // 0x0c
    RHCampaignMissionCandidates(const std::allocator<RHMission *> &allocator = std::allocator<RHMission *>())
        : m_allocator(allocator), m_first(0), m_last(0), m_end(0) {}
    RHCampaignMissionCandidates(const std::vector<RHMission *> &value)
    {
        *(char *)&m_allocator = *(const char *)&value;
        m_first = std::_Allocate((int)value.size(), (RHMission **)0);
        m_last = (RHMission **)((RHScriptFXArray *)this)->Unk004fe420(
            (void **)value.begin(), (void **)value.end(), (void **)m_first);
        m_end = m_last;
    }
    ~RHCampaignMissionCandidates() { ((RHCampaignArrayOps *)this)->FUN_00570330(); }
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
    void *FUN_0056d5d0(const RHProfileText &name);
};

// SIZE 0x04
class RHCampaignPCBase
{
public:
    virtual bool FUN_0055bce0(SBFile &file); // vtable+0x00
};

class RHProfileManager
{
public:
    bool SerializeProfilePointer(SBFile &file, const RHCharacterProfile *&profile) const;
};

RHProfileManager *RHUnk00436500GetProfileManager();

extern RHCampaignCommandLine g_unk0x6c05cc;
extern RHCampaignProfiles *g_unk0x6c0e84;

// SIZE 0x10
class RHCampaignBeamText : public std::string
{
public:
    typedef std::string Base;
    RHCampaignBeamText() {}
    RHCampaignBeamText(const RHCampaignBeamText &value) : Base(value) {}
    void FUN_00401ce0(const std::string &value, unsigned first, unsigned count)
    {
        ((RHProfileText *)this)->FUN_00401ce0(value, first, count);
    }
};

// SIZE 0x30
struct RHbeamMe
{
    SBGeoPoint2D m_point; // 0x00
    unsigned short m_8; // 0x08
    unsigned short m_a; // 0x0a
    unsigned short m_c; // 0x0c
    char m_e; // 0x0e
    undefined m_f; // 0x0f
    unsigned short m_10; // 0x10
    unsigned short m_12; // 0x12
    unsigned short m_14; // 0x14
    undefined m_16[2]; // 0x16
    int m_required; // 0x18
    int m_1c; // 0x1c
    RHCampaignBeamText m_text; // 0x20
    RHbeamMe() {}
    ~RHbeamMe();
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
    char m_allocator[4];
    RHbeamMe *m_first;
    RHbeamMe &FUN_00457bc0(unsigned beamMe);
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
            std::_Construct((unsigned short *)&node->data, value);
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

// SIZE 0x08
class SBGeoVector2D : public SBGeoPoint2D
{
public:
    SBGeoVector2D(const SBGeoPoint2D &point);
    ~SBGeoVector2D() {}
    SBGeoVector2D(const SBGeoVector2D &other);
    SBGeoVector2D &operator=(const SBGeoVector2D &other);
};

// SIZE 0x14
class SBGeoBoundingBox2D
{
public:
    SBGeoBoundingBox2D(const SBGeoBoundingBox2D &value);
    SBGeoBoundingBox2D FUN_006090d0(const SBGeoVector2D &value) const;
    bool FUN_006083b0(const SBGeoPoint2D &point) const;
    SBGeoPoint2D m_0; // 0x00
    SBGeoPoint2D m_8; // 0x08
    undefined m_10; // 0x10
};

// SIZE 0x9c
struct RHCampaignCharacterData
{
    undefined4 m_00; // 0x00
    RHProfileString m_04; // 0x04
    RHProfileString m_14; // 0x14
    RHProfileString m_24; // 0x24
    undefined m_34; // 0x34
    undefined m_35; // 0x35
    undefined2 m_36; // 0x36
    undefined2 m_38; // 0x38
    undefined2 m_3a; // 0x3a
    undefined4 m_3c; // 0x3c
    undefined4 m_40; // 0x40
    undefined4 m_44; // 0x44
    int m_48[3]; // 0x48
    undefined4 m_54; // 0x54
    undefined2 m_58; // 0x58
    int m_5c[4]; // 0x5c
    undefined m_6c; // 0x6c
    SBGeoBoundingBox2D m_70; // 0x70
    SBGeoPoint2D m_84; // 0x84
    undefined2 m_8c[4]; // 0x8c
    undefined4 m_94; // 0x94
    undefined4 m_98; // 0x98
};

class RHMobileUnk006091b0
{
public:
    RHMobileUnk006091b0 &FUN_006091b0(const SBGeoPoint2D &value);
};

class RHMobileUnk00607da0
{
public:
    RHMobileUnk00607da0 &FUN_00607da0(const RHMobileUnk00607da0 &value);
};

class RHUnkPathActorInfoBase
{
public:
    void *Unk0055fa10(int index);
};

class RHBonusInfoBase
{
public:
    void FUN_0055f290();
};

class RHPathObstacleGrid
{
public:
    bool FUN_004f5750(SBGeoBoundingBox2D &box, unsigned short layer);
    bool FUN_004f9260(const SBGeoPoint2D &first, const SBGeoPoint2D &last, unsigned short layer);
};

template<class T>
T &RHCampaignField(void *object, unsigned offset)
{
    return *(T *)((char *)object + offset);
}


#endif
