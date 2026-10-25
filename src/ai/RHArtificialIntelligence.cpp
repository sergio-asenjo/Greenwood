#include "SBNullstr.h"
#include "RHArtificialIntelligence.h"

// GLOBAL: GAME 0x006c078a
unsigned short g_unk0x006c078a;
// GLOBAL: GAME 0x006c06c2
unsigned short g_unk0x006c06c2;
// GLOBAL: GAME 0x006c0738
bool g_unk0x006c0738;
// GLOBAL: GAME 0x006c06c0
bool g_unk0x006c06c0;

struct RHAIConsiderationThreshold
{
    unsigned short weight;
    short value;
};

// GLOBAL: GAME 0x006c07b4
RHAIConsiderationThreshold g_unk0x006c07b4;

template <class T> inline T &RHAIField(void *object, unsigned offset)
{
    return *(T *)((char *)object + offset);
}

#include <list>

class RHArtificialIntelligenceSeekList : public std::list<RHArtificialIntelligenceElement *>
{
public:
    iterator Begin()
    {
        _Nodeptr sentinel = _Head;
        _Nodeptr first = *(_Nodeptr volatile *)&sentinel->_Next;
        return iterator(first);
    }
    iterator End()
    {
        _Nodeptr sentinel = *(_Nodeptr volatile *)&_Head;
        return iterator(sentinel);
    }
    struct Cursor : std::list<RHArtificialIntelligenceElement *>::iterator
    {
        Cursor &Assign(_Nodeptr value)
        {
            *(_Nodeptr volatile *)this = value;
            return *this;
        }
    };
    void Seek(int wanted)
    {
        int size = _Size;
        if (m_dirty)
        {
            if (wanted <= (size + 1) / 2)
            {
                m_cursor = Begin();
                std::bidirectional_iterator_tag category;
                FUN_005c9010((RHUnk005c9010Iterator &)m_cursor, wanted, category);
            }
            else
            {
                m_cursor = End();
                std::bidirectional_iterator_tag category;
                FUN_005c9010((RHUnk005c9010Iterator &)m_cursor, wanted - size, category);
            }
            m_dirty = false;
            m_index = wanted;
        }
        else
        {
            int previous = m_index;
            if (wanted != previous)
            {
                if (wanted < previous)
                {
                    if (wanted < (previous + 1) / 2)
                    {
                        std::bidirectional_iterator_tag category;
                        FUN_005c9010((RHUnk005c9010Iterator &)((Cursor &)m_cursor).Assign(*(_Nodeptr volatile *)&_Head->_Next), wanted, category);
                    }
                    else
                    {
                        int distance = wanted - previous;
                        std::bidirectional_iterator_tag category;
                        FUN_005c9010((RHUnk005c9010Iterator &)m_cursor, distance, category);
                    }
                }
                else if (wanted < (size + previous) / 2)
                    std::advance(m_cursor, wanted - previous);
                else
                {
                    m_cursor = End();
                    std::advance(m_cursor, wanted - size);
                }
                m_index = wanted;
            }
        }
    }
    iterator m_cursor;
    bool m_dirty;
    int m_index;
};

// FUNCTION: GAME 0x00423c20
RHArtificialIntelligenceElement *&RHArtificialIntelligenceList::FUN_00423c20(int wanted)
{
    RHArtificialIntelligenceSeekList *self = (RHArtificialIntelligenceSeekList *)this;
    self->Seek(wanted);
    return *self->m_cursor;
}

#include "RHMalignityPosition.h"

SBGeoVector2D FUN_0040ec20(const RHMalignityPosition &first, RHMalignityPosition second);

class RHSeekPoint
{
public:
    bool SerializeStatus(SBFile &file);
};
class RHFastFindTacticalArray;
extern RHFastFindTacticalArray g_unk0x006c06f0;

struct RHArtificialIntelligenceStaticArray
{
    int m_grow;
    void **m_first;
    void **m_last;
    unsigned size() { return m_first == 0 ? 0 : m_last - m_first; }
    void *operator[](unsigned index) { return m_first[index]; }
};

class RHArtificialIntelligenceStaticObject
{
public:
    virtual void V00() = 0;
    virtual void V04() = 0;
    virtual void V08() = 0;
    virtual bool V0c(SBFile &file) = 0;
};

struct RHUnk00423fa0Node
{
    RHUnk00423fa0Node *next;
    RHUnk00423fa0Node *previous;
    void *payload;
};

class RHUnk00423fa0List
{
public:
    int allocator;
    RHUnk00423fa0Node *head;
    int count;
    void Clear();
};

// Parked: the target's iterator-helper and per-node cleanup calls are not yet attributed.
// STUB: GAME 0x00423fa0
void RHUnk00423fa0List::Clear()
{
    RHUnk00423fa0Node *sentinel = head;
    RHUnk00423fa0Node *node = sentinel->next;
    while (node != sentinel)
    {
        RHUnk00423fa0Node *next = node->next;
        node->previous->next = node->next;
        node->next->previous = node->previous;
        typedef void (__cdecl *NodeCleanup)(int);
        ((NodeCleanup)0x0040eab0)(0);
        operator delete(node);
        --count;
        node = next;
    }
    operator delete(sentinel);
    head = 0;
    count = 0;
}

struct RHUnk00424060Node
{
    RHUnk00424060Node *next;
    RHUnk00424060Node *previous;
    void *payload;
};

class RHUnk00424060List
{
public:
    int allocator;
    RHUnk00424060Node *head;
    int count;
    RHUnk00424060Node *cursor;
    void Clear();
};

// Parked: target iterator-helper passes after payload release remain unresolved.
// STUB: GAME 0x00424060
void RHUnk00424060List::Clear()
{
    RHUnk00424060Node *sentinel = head;
    cursor = sentinel->next;
    while (cursor != sentinel)
    {
        void *storage = cursor->payload;
        if (storage)
            operator delete(storage);
        cursor = cursor->next;
    }
    RHUnk00424060Node *node = sentinel->next;
    while (node != sentinel)
    {
        RHUnk00424060Node *next = node->next;
        node->previous->next = next;
        next->previous = node->previous;
        operator delete(node);
        --count;
        node = next;
    }
    operator delete(sentinel);
    head = 0;
    count = 0;
}

// GLOBAL: GAME 0x006c06ca
unsigned char g_unk0x006c06ca;
// GLOBAL: GAME 0x006c06d0
RHArtificialIntelligenceStaticArray g_unk0x006c06d0;
// GLOBAL: GAME 0x006c07de
char g_unk0x006c07de;
// GLOBAL: GAME 0x006c07e2
unsigned short g_unk0x006c07e2;
// GLOBAL: GAME 0x006c07e4
unsigned short g_unk0x006c07e4;
// GLOBAL: GAME 0x006c07e6
unsigned short g_unk0x006c07e6;
// GLOBAL: GAME 0x006c078c
unsigned g_unk0x006c078c;
// GLOBAL: GAME 0x006c0780
unsigned g_unk0x006c0780;
// GLOBAL: GAME 0x006c0784
long g_unk0x006c0784;
// GLOBAL: GAME 0x006c07b8
RHArtificialIntelligenceList g_unk0x006c07b8;
// GLOBAL: GAME 0x006c0758
RHArtificialIntelligenceList g_unk0x006c0758;

extern "C" long __cdecl time(long *value);
extern "C" void __cdecl srand(unsigned seed);
void operator delete(void *pointer) throw();

class RHAIObjectDeletingView
{
public:
    virtual void Delete(unsigned flags) = 0;
};

class RHUnk00423d90
{
public:
    int allocator;
    void **first;
    void **last;
    void **end;
    void FUN_00423d90();
};

class RHUnk00423e40
{
public:
    int allocator;
    void **first;
    void **last;
    void **end;
    void FUN_00423e40();
};

class RHUnk00423ef0
{
public:
    int allocator;
    void **first;
    void **last;
    void **end;
    void FUN_00423ef0();
};

// Parked: 59.46%; provisional vector-clear; exact owner and register schedule unresolved.
// STUB: GAME 0x00423d90
void RHUnk00423d90::FUN_00423d90()
{
    int count = first == 0 ? 0 : last - first;
    int index = 0;
    if (count > 0)
    {
        do
        {
            RHAIObjectDeletingView *object = (RHAIObjectDeletingView *)first[index];
            if (object)
                object->Delete(1);
            ++index;
        } while (index < count);
    }
    last = first;
    last = first;
    operator delete(first);
    first = 0;
    last = 0;
    end = 0;
}

// Parked: 59.46%; provisional vector-clear sibling; no direct TU attribution.
// STUB: GAME 0x00423e40
void RHUnk00423e40::FUN_00423e40()
{
    int count = first == 0 ? 0 : last - first;
    int index = 0;
    if (count > 0)
    {
        do
        {
            RHAIObjectDeletingView *object = (RHAIObjectDeletingView *)first[index];
            if (object)
                object->Delete(1);
            ++index;
        } while (index < count);
    }
    last = first;
    last = first;
    operator delete(first);
    first = 0;
    last = 0;
    end = 0;
}

// Parked: 59.46%; provisional vector-clear sibling; no direct TU attribution.
// STUB: GAME 0x00423ef0
void RHUnk00423ef0::FUN_00423ef0()
{
    int count = first == 0 ? 0 : last - first;
    int index = 0;
    if (count > 0)
    {
        do
        {
            RHAIObjectDeletingView *object = (RHAIObjectDeletingView *)first[index];
            if (object)
                object->Delete(1);
            ++index;
        } while (index < count);
    }
    last = first;
    last = first;
    operator delete(first);
    first = 0;
    last = 0;
    end = 0;
}

class RHArtificialIntelligenceForbiddenRemark
{
public:
    ~RHArtificialIntelligenceForbiddenRemark() {}
    int remark;
    unsigned short flags;
    void *voice;
    unsigned short actorID;
    bool soldier;
    unsigned deadline;
};

// GLOBAL: GAME 0x006a73c8
extern const char g_unk0x006a73c8[] = "P:\\Robin Hood\\RHartificialintelligence.cpp";

#define RHAI_STIMULUS_ACCESS(offset, size, line) \
    if (file.Access((char *)this + offset, size) < 0) \
    { \
        SBString *err = file.GetError(); \
        const char *reason = err->m_chars ? err->m_chars : ""; \
        SBAssert(0, g_unk0x006a73c8, line, "Serialize failed reason is %s", reason); \
        return false; \
    }

#define RHAI_STIMULUS_POINTER(offset, line) \
    if (!FUN_00416b30(*(void **)((char *)this + offset), file)) \
    { \
        SBAssert(1, "P:\\Robin Hood\\RHartificialintelligence.cpp", line, "Serialization failed"); \
        return false; \
    }

// FUNCTION: GAME 0x0040f090
bool RHStimulus::Serialize(SBFile &file)
{
    // STRING: GAME 0x006a7424
    RHSerializeName(file, "RHStimulus");
    if (file.m_version >= 10)
    {
        RHAI_STIMULUS_ACCESS(0x28, 1, 171);
    }
    RHAI_STIMULUS_ACCESS(0x20, 4, 174);
    if (file.Access(&m_type, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, g_unk0x006a73c8, 175, "Serialize failed reason is %s", reason);
        return false;
    }
    if (!((RHReconnaissanceEngine *)g_pEngine)->Unk004c3cb0(file, m_24))
    {
        SBAssert(1, "P:\\Robin Hood\\RHartificialintelligence.cpp", 176, "Serialization failed");
        return false;
    }
    switch (m_type)
    {
    case 0:
        break;
    case 1:
        RHAI_STIMULUS_ACCESS(0, 16, 184);
        ((RHUnkPathGeometry *)g_unk0x6c0a9c)->Unk004fbec0(file, *(void **)((char *)this + 8));
        if (file.m_version >= 22)
        {
            RHAI_STIMULUS_ACCESS(0, 4, 189);
            RHAI_STIMULUS_ACCESS(4, 4, 190);
            RHAI_STIMULUS_ACCESS(12, 2, 191);
            ((RHUnkPathGeometry *)g_unk0x6c0a9c)->Unk004fbec0(file, *(void **)((char *)this + 8));
        }
        RHAI_STIMULUS_ACCESS(16, 4, 195);
        RHAI_STIMULUS_ACCESS(20, 2, 196);
        RHAI_STIMULUS_ACCESS(22, 2, 197);
        break;
    case 2:
        RHAI_STIMULUS_ACCESS(0, 4, 202);
        RHAI_STIMULUS_ACCESS(4, 4, 203);
        ((RHUnkPathGeometry *)g_unk0x6c0a9c)->Unk004fbec0(file, *(void **)((char *)this + 8));
        RHAI_STIMULUS_ACCESS(12, 2, 205);
        break;
    case 3:
        RHAI_STIMULUS_POINTER(0, 209);
        break;
    case 4:
        RHAI_STIMULUS_ACCESS(0, 4, 213);
        RHAI_STIMULUS_ACCESS(4, 4, 214);
        ((RHUnkPathGeometry *)g_unk0x6c0a9c)->Unk004fbec0(file, *(void **)((char *)this + 8));
        RHAI_STIMULUS_ACCESS(12, 2, 216);
        RHAI_STIMULUS_POINTER(20, 217);
        RHAI_STIMULUS_ACCESS(16, 2, 218);
        break;
    case 5:
        RHAI_STIMULUS_POINTER(0, 222);
        break;
    case 6:
        RHAI_STIMULUS_POINTER(0, 226);
        RHAI_STIMULUS_POINTER(4, 227);
    case 7:
        RHAI_STIMULUS_ACCESS(4, 4, 230);
        RHAI_STIMULUS_ACCESS(8, 4, 231);
        ((RHUnkPathGeometry *)g_unk0x6c0a9c)->Unk004fbec0(file, *(void **)((char *)this + 12));
        RHAI_STIMULUS_ACCESS(16, 2, 233);
        RHAI_STIMULUS_POINTER(0, 234);
        break;
    case 8:
        RHAI_STIMULUS_ACCESS(0, 2, 238);
        RHAI_STIMULUS_ACCESS(20, 2, 239);
        RHAI_STIMULUS_ACCESS(4, 4, 240);
        RHAI_STIMULUS_ACCESS(8, 4, 241);
        ((RHUnkPathGeometry *)g_unk0x6c0a9c)->Unk004fbec0(file, *(void **)((char *)this + 12));
        RHAI_STIMULUS_ACCESS(16, 2, 243);
        RHAI_STIMULUS_POINTER(24, 244);
        break;
    case 9:
        RHAI_STIMULUS_ACCESS(0, 2, 248);
        break;
    default:
        return false;
    }
    return true;
}

#undef RHAI_STIMULUS_ACCESS
#undef RHAI_STIMULUS_POINTER

class RHUnk0040fd10
{
public:
    bool FUN_0040fd10(int value);
};

class RHUnk00410000
{
public:
    void FUN_00410000(int value);
};

// FUNCTION: GAME 0x0040fd10
bool RHUnk0040fd10::FUN_0040fd10(int value)
{
    return true;
}

// FUNCTION: GAME 0x00410000
void RHUnk00410000::FUN_00410000(int value)
{
    *(int *)((char *)this + 4) = value;
}

void EmitRHUnk0040fd10(RHUnk0040fd10 *a, RHUnk00410000 *b)
{
    a->FUN_0040fd10(0);
    b->FUN_00410000(0);
}

// GLOBAL: GAME 0x006c07e8
char g_unk0x006c07e8;

// Parked: 59.63%; switch/register scheduling and recursive ILT operands.
// STUB: GAME 0x00410010
void RHArtificialIntelligence::Unk00410010(bool mode)
{
    RHArtificialIntelligenceActor *actor;
    RHArtificialIntelligencePathCursor *cursor;
    for (;;)
    {
        if (RHAIField<int>(this, 0x0c) == 1)
            V10(1, 15);
        actor = m_actor;
        RHAIField<unsigned short>(this, 0xa8) = 0;
        void *interfaceObject = RHAIField<void *>(actor, 0x49c);
        cursor = (RHArtificialIntelligencePathCursor *)((char *)actor + 0x4cc + RHAIField<int>(interfaceObject, 4));
        if (RHAIField<short>(this, 0x7c) <= 0)
            break;
        unsigned char *commands = RHAIField<unsigned char *>(this, 0x78);
        --RHAIField<short>(this, 0x7c);
        unsigned char command = *commands++;
        RHAIField<unsigned char *>(this, 0x78) = commands;
        RHAIField<char>(this, 0x7e) = 1;
        switch (command)
        {
        case 0:
            RHAIField<char>(cursor, 2) ^= 1;
            mode = false;
            continue;
        case 1:
            cursor->Unk005505c0();
            RHAIField<short>(this, 0x7c) = 0;
            mode = false;
            continue;
        case 2:
        {
            unsigned short waypoint = *(unsigned short *)commands;
            if (waypoint == RHAIField<unsigned char>(cursor, 0) && !g_unk0x006c07e8)
                SBAssert(1, "P:\\Robin Hood\\RHartificialintelligence.cpp", 582,
                         // STRING: GAME 0x006a769c
                         "It's a crusade of the Good against the Evil ! : NPC going from a waypoint to the same waypoint !");
            cursor->Unk005505b0(waypoint);
            RHAIField<short>(this, 0x7c) = 0;
            mode = true;
            continue;
        }
        case 3:
            V10(1, 16);
            Unk00412f70(RHAIField<unsigned short>(RHAIField<void *>(this, 0x78), 0), 0);
            RHAIField<char *>(this, 0x78) += 2;
            RHAIField<short>(this, 0x7c) -= 2;
            return;
        case 4:
            ((RHArtificialIntelligenceActorCalls *)m_actor)->Unk0048b450(*(unsigned short *)commands, 1);
            RHAIField<char>(this, 0x7f) = 0;
            RHAIField<char *>(this, 0x78) += 2;
            RHAIField<short>(this, 0x7c) -= 2;
            return;
        case 5:
        {
            unsigned short first = *(unsigned short *)commands;
            unsigned short second = *(unsigned short *)(commands + 2);
            RHAIField<short>(this, 0x7c) -= 4;
            RHAIField<unsigned char *>(this, 0x78) = commands + 4;
            if ((RHAIField<unsigned>(m_actor, 4) & 31) != 20)
                SBAssert(1, "P:\\Robin Hood\\RHartificialintelligence.cpp", 611,
                         // STRING: GAME 0x006a75b8
                         "Waypoint command 'CheckFor' is illegal for civilists");
            if (!m_actor->V130())
                SBAssert(1, "P:\\Robin Hood\\RHartificialintelligence.cpp", 616,
                         // STRING: GAME 0x006a7578
                         "Waypoint command 'CheckFor' is illegal for friendly soldiers");
            V40(first, second, 0xffff);
            RHAIField<char>(this, 0x7f) = 0;
            return;
        }
        case 6:
        {
            unsigned short first = *(unsigned short *)commands;
            unsigned short second = *(unsigned short *)(commands + 2);
            unsigned short third = *(unsigned short *)(commands + 4);
            RHAIField<unsigned char *>(this, 0x78) = commands + 6;
            RHAIField<short>(this, 0x7c) -= 6;
            if ((RHAIField<unsigned>(m_actor, 4) & 31) != 20)
                SBAssert(1, "P:\\Robin Hood\\RHartificialintelligence.cpp", 633,
                         // STRING: GAME 0x006a753c
                         "Waypoint command 'CheckForSync' is illegal for civilists");
            if (!m_actor->V130())
                SBAssert(1, "P:\\Robin Hood\\RHartificialintelligence.cpp", 638,
                         // STRING: GAME 0x006a74f8
                         "Waypoint command 'CheckForSync' is illegal for friendly soldiers");
            V40(first, second, third);
            RHAIField<char>(this, 0x7f) = 0;
            return;
        }
        case 7:
            Unk00418600(0xffff);
            return;
        case 8:
            Unk00418600(*(unsigned short *)commands);
            Unk00410600();
            V00(0);
            return;
        case 9:
            RHAIField<unsigned char>(this, 0x22c) |= 1;
            Unk00410010(false);
            if ((RHAIField<unsigned>(m_actor, 4) & 31) == 4 && (RHAIField<unsigned short>(this, 0x22c) & 0xd802))
                RHAIField<unsigned short>(this, 0x22c) &= 0x27fd;
            return;
        case 10:
            RHAIField<unsigned short>(this, 0x22c) &= 0xfffe;
            Unk00410010(false);
            if ((RHAIField<unsigned>(m_actor, 4) & 31) == 4 && (RHAIField<unsigned short>(this, 0x22c) & 0xd802))
                RHAIField<unsigned short>(this, 0x22c) &= 0x27fd;
            return;
        case 11:
            if ((RHAIField<unsigned>(m_actor, 4) & 31) != 20)
                SBAssert(1, "P:\\Robin Hood\\RHartificialintelligence.cpp", 689,
                         // STRING: GAME 0x006a749c
                         "Waypoint command 'LookLeft' is illegal for civilists, even if they are called Guisbourne!");
            V04(0);
            V10(1, 16);
            RHAIField<char>(this, 0x7f) = 0;
            return;
        case 12:
            if ((RHAIField<unsigned>(m_actor, 4) & 31) != 20)
                SBAssert(1, "P:\\Robin Hood\\RHartificialintelligence.cpp", 700,
                         // STRING: GAME 0x006a7464
                         "Waypoint command 'LookRight' is illegal for civilists");
            V04(1);
            V10(1, 16);
            RHAIField<char>(this, 0x7f) = 0;
            return;
        case 13:
            if ((RHAIField<unsigned>(m_actor, 4) & 31) != 20)
                SBAssert(1, "P:\\Robin Hood\\RHartificialintelligence.cpp", 710,
                         // STRING: GAME 0x006a7430
                         "Waypoint command 'Bend' is illegal for civilists");
            V04(4);
            ((RHArtificialIntelligenceActorCalls *)m_actor)->Unk0048b450(RHAIField<unsigned short>(RHAIField<void *>(this, 0x78), 0), 1);
            RHAIField<char>(this, 0x7f) = 0;
            RHAIField<char *>(this, 0x78) += 2;
            RHAIField<short>(this, 0x7c) -= 2;
            return;
        case 14:
            if ((RHAIField<unsigned>(actor, 4) & 31) != 20)
                SBAssert(1, "P:\\Robin Hood\\RHartificialintelligence.cpp", 722,
                         // STRING: GAME 0x006a7664
                         "Waypoint command 'PatrolStop' is illegal for civilists");
            RHAIField<char>(this, 0x344) = 1;
            if ((RHAIField<unsigned>(m_actor, 4) & 31) == 20 && RHAIField<int>(RHAIField<void *>(m_actor, 0xa1c), 0x58) == 1)
                Unk00418c40(59, 0);
            mode = false;
            continue;
        case 15:
            if ((RHAIField<unsigned>(actor, 4) & 31) != 20)
                SBAssert(1, "P:\\Robin Hood\\RHartificialintelligence.cpp", 735,
                         // STRING: GAME 0x006a7628
                         "Waypoint command 'PatrolDirection' is illegal for civilists");
            Unk0041a960(RHAIField<unsigned short>(RHAIField<void *>(this, 0x78), 0));
            RHAIField<short>(this, 0x7c) -= 2;
            RHAIField<char *>(this, 0x78) += 2;
            mode = false;
            continue;
        case 16:
            if ((RHAIField<unsigned>(actor, 4) & 31) != 20)
                SBAssert(1, "P:\\Robin Hood\\RHartificialintelligence.cpp", 746,
                         // STRING: GAME 0x006a75f0
                         "Waypoint command 'PatrolStart' is illegal for civilists");
            RHAIField<char>(this, 0x344) = 0;
            if ((RHAIField<unsigned>(m_actor, 4) & 31) == 20 && RHAIField<int>(RHAIField<void *>(m_actor, 0xa1c), 0x58) == 1)
                Unk00418c40(60, 0);
            ((RHScriptBatchCalls *)this)->Unk0041ac50();
            mode = false;
            continue;
        default:
            RHAIField<short>(this, 0x7c) = 0;
            mode = false;
            continue;
        }
    }
    if (V28())
    {
        Unk00410600();
        return;
    }
    void *path = RHAIField<void *>(cursor, 4);
    if (path && RHAIField<void **>(path, 4) && (unsigned short)(RHAIField<void **>(path, 8) - RHAIField<void **>(path, 4)) == 1)
    {
        if (RHAIField<char>(this, 0x7f))
        {
            V10(1, 15);
            RHAIField<char>(this, 0x7f) = 0;
            ((RHArtificialIntelligenceActorCalls *)m_actor)->Unk0048b450(100, 1);
        }
        else
        {
            RHAIField<char>(this, 0x7e) = 0;
            ((RHArtificialIntelligenceActorCalls *)m_actor)->Unk0048b4e0(1);
            V10(1, 13);
            ((RHScriptBatchCalls *)this)->Unk0040d980(3);
        }
        return;
    }
    if (!mode)
        cursor->Unk005505c0();
    V10(1, 13);
    if (Unk00419cc0())
        Unk00412c80(RHAIField<void **>(RHAIField<void *>(cursor, 4), 4)[RHAIField<unsigned char>(cursor, 0)], RHAIField<unsigned short>(this, 0x22c));
    else
        Unk00412c80(RHAIField<void **>(RHAIField<void *>(cursor, 4), 4)[RHAIField<unsigned char>(cursor, 0)], RHAIField<unsigned short>(this, 0x22c) | 0x400);
    RHAIField<char>(this, 0x7e) = 0;
    ((RHArtificialIntelligenceActorCalls *)m_actor)->Unk0048b4e0(1);
}

// FUNCTION: GAME 0x00410600
void RHArtificialIntelligence::Unk00410600()
{
    RHArtificialIntelligenceActorCalls *actor = (RHArtificialIntelligenceActorCalls *)m_actor;
    RHAIField<char>(this, 0x7e) = 0;
    actor->Unk0048b4e0(1);
    FUN_0041a300(0);
}

struct RHAIPathArray
{
    int m_grow;
    void **m_first;
    void **m_last;
    unsigned size() { return m_first ? m_last - m_first : 0; }
};

// FUNCTION: GAME 0x004121a0
void RHArtificialIntelligence::FUN_004121a0()
{
    RHArtificialIntelligencePathCursor *cursor = (RHArtificialIntelligencePathCursor *)((char *)m_actor + RHAIField<int>(RHAIField<void *>(m_actor, 0x49c), 4) + 0x4cc);
    V10(1, 13);
    RHAIPathArray *path = cursor->m_path;
    if (path && (unsigned short)path->size() == 1)
    {
        RHAIField<char>(this, 0x16d) = 1;
        return;
    }
    cursor->Unk005505c0();
    if (Unk00419cc0())
    {
        unsigned short flags = RHAIField<unsigned short>(this, 0x22c) | 4;
        void *waypoint = RHAIField<void **>(RHAIField<void *>(cursor, 4), 4)[cursor->m_current];
        Unk00412c80(waypoint, flags);
        return;
    }
    unsigned short flags = RHAIField<unsigned short>(this, 0x22c) | 0x404;
    void *waypoint = RHAIField<void **>(RHAIField<void *>(cursor, 4), 4)[cursor->m_current];
    Unk00412c80(waypoint, flags);
}

// FUNCTION: GAME 0x00412c80
bool RHArtificialIntelligence::Unk00412c80(void *waypoint, unsigned short flags)
{
    RHUnk00571160Position position;
    position.x = RHAIField<short>(waypoint, 0x64);
    position.y = RHAIField<short>(waypoint, 0x66);
    position.area = RHAIField<void *>(waypoint, 0x68);
    position.layer = RHAIField<short>(waypoint, 0x6c);
    RHUnk00571160Position destination = position;
    return Unk00412240(destination, flags, 1.0f);
}

// FUNCTION: GAME 0x00412e90
void RHArtificialIntelligence::FUN_00412e90(SBGeoPoint2D point, int mode)
{
    Unk00412f40((RHUnk005fc3b0 *)&FUN_0040ec20(*(const RHMalignityPosition *)&point, FUN_004165e0(m_actor, true)), mode);
}

// FUNCTION: GAME 0x00412f40
bool RHArtificialIntelligence::Unk00412f40(RHUnk005fc3b0 *direction, int mode)
{
    return Unk00412f70((unsigned short)direction->FUN_005fcc50(0.57357645f), mode);
}

class RHUnk00582220
{
public:
    RHUnk00582220();
    ~RHUnk00582220();
    char m_data[0x3c];
};

class RHUnk005866a0
{
public:
    RHUnk005866a0(unsigned short level, int command, void *actor);
    ~RHUnk005866a0();
    void Unk00586e90(int property, unsigned short value);
    char m_data[0x74];
};

#include "RHSequenceAppendCalls.h"

class RHUnk0058a3d0
{
public:
    void *Unk(void *context, int value, void *sequence);
};

class RHUnk6c1040;
extern RHUnk6c1040 *g_unk0x6c1040;

// FUNCTION: GAME 0x00412f70
bool RHArtificialIntelligence::Unk00412f70(unsigned short direction, int mode)
{
    SBGeoPoint2D point;
    RHArtificialIntelligenceActor *actor = m_actor;
    if ((unsigned)direction == (int)RHAIField<short>(actor->m_data, 0xd8) &&
        RHAIField<int>(actor, 0x144) >= 0 && RHAIField<int>(actor, 0x144) <= 1)
    {
        RHAIField<char>(this, 0x16e) = 1;
        return true;
    }
    ((RHArtificialIntelligenceActorCalls *)actor)->Unk0048d020();
    RHUnk00582220 *sequence = new RHUnk00582220;
    RHUnk005866a0 *command = new RHUnk005866a0(1, (unsigned char)mode ? 28 : 26, m_actor);
    command->Unk00586e90(0, direction);
    ((RHUnk00585500 *)command)->Unk(sequence);
    ((RHUnk0058a3d0 *)g_unk0x6c1040)->Unk("", 0, sequence);
    return true;
}

// FUNCTION: GAME 0x00413240
void RHArtificialIntelligence::FUN_00413240(SBGeoPoint2D point, int first, int second)
{
    SBGeoPoint2D origin = RHAIField<SBGeoPoint2D>(RHAIField<void *>(m_actor, 0x50), 0x24);
    RHAIField<SBGeoPoint2D>(this, 0xf4) = point;
    FUN_004132d0(first, 1, second);
}

// Parked: switch tail merging and register scheduling.
// STUB: GAME 0x00414550
bool RHArtificialIntelligence::InitState()
{
    SBGeoPoint2D point;
    m_16f = false;
    m_170 = false;
    m_173 = false;
    RHArtificialIntelligenceInitialEntry *entry = m_actor->m_data->m_entry;
    bool done = true;
    if (entry->Flag13() & 1)
    {
        m_173 = done;
        V10(1, 17);
        RHElementActor *value = (RHElementActor *)entry;
        if (((RHSectorActorList *)&g_unk0x006c0758)->Unk004b8f80(value, true) == -1)
            g_unk0x006c0758.InsertLast((void *const &)value);
    }
    else
    {
        switch (m_initialAction)
        {
        case 0:
        case 1:
        case 3:
            V10(1, 11);
            Unk00416710(Unk0041a420());
            return done;
        case 45:
            V10(0, 1);
            m_actor->Vc4(0);
            ((RHScriptBatchCalls *)m_actor)->Unk0046bcf0(13, 0);
            ((RHScriptBatchCalls *)m_actor)->Unk00464630();
            *((char *)m_actor + 0x490) = done;
            break;
        case 47:
            V10(0, 1);
            m_actor->Vc4(0);
            ((RHScriptBatchCalls *)m_actor)->Unk0046bcf0(12, 0);
            ((RHScriptBatchCalls *)m_actor)->Unk00464630();
            *((char *)m_actor + 0x490) = done;
            break;
        case 48:
            V10(0, 2);
            m_actor->Vdc(300, 0, 0);
            ((RHScriptBatchCalls *)m_actor)->Unk0046bcf0(3, 0);
            ((RHScriptBatchCalls *)m_actor)->Unk00464630();
            break;
        case 270:
            V10(1, 11);
            ((RHScriptBatchCalls *)m_actor)->Unk0046bcf0(24, 0);
            ((RHScriptBatchCalls *)m_actor)->Unk00464630();
            m_170 = done;
            break;
        case 162:
            V10(0, 3);
            ((RHArtificialIntelligence *)m_actor)->Unk00486f60();
            ((RHScriptBatchCalls *)m_actor)->Unk0046bcf0(1, 16);
            ((RHScriptBatchCalls *)m_actor)->Unk00464630();
            ((RHScriptBatchCalls *)this)->Unk00419fb0(4);
            break;
        case 159:
            V10(1, 11);
            Unk00416710(Unk0041a420());
            ((RHScriptBatchCalls *)m_actor)->Unk0046bcf0(8, 0);
            ((RHScriptBatchCalls *)m_actor)->Unk00464630();
            m_16f = done;
            break;
        default:
            V10(1, 11);
            Unk00416710(Unk0041a420());
            SBAssert(0, "P:\\Robin Hood\\RHartificialintelligence.cpp", 3734,
                     // STRING: GAME 0x006a7700
                     "Actor at (%f, %f): Initial action %u not supported by AI.",
                     m_actor->m_data->m_x, m_actor->m_data->m_y, (unsigned short)m_initialAction);
            return done;
        }
    }
    return false;
}

// Parked: delete omits the ecx-to-eax transfer and reloads the sentinel before the cursor.
// STUB: GAME 0x004148b0
bool RHArtificialIntelligence::SerializeAllAI(SBFile &file)
{
    // STRING: GAME 0x006a773c
    RHSerializeName(file, "RHArtificialIntelligence");
    if (file.Access(&g_unk0x006c07de, 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, g_unk0x006a73c8,
                 3764, "Serialize failed reason is %s", reason);
        return false;
    }
    RHArtificialIntelligenceStaticArray &points = (RHArtificialIntelligenceStaticArray &)g_unk0x006c06f0;
    unsigned count = points.size();
    for (unsigned i = 0; i < count; ++i)
    {
        if (!((RHSeekPoint *)points[i])->SerializeStatus(file))
        {
            SBAssert(1, "P:\\Robin Hood\\RHartificialintelligence.cpp", 3772, "Serialization failed");
            return false;
        }
    }
    count = g_unk0x006c06d0.size();
    for (i = 0; i < count; ++i)
    {
        if (!((RHArtificialIntelligenceStaticObject *)g_unk0x006c06d0[i])->V0c(file))
        {
            SBAssert(1, "P:\\Robin Hood\\RHartificialintelligence.cpp", 3779, "Serialization failed");
            return false;
        }
    }
    if (file.Access(&g_unk0x006c07e2, 2) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, g_unk0x006a73c8,
                 3782, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&g_unk0x006c07e4, 2) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, g_unk0x006a73c8,
                 3783, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&g_unk0x006c07e6, 2) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, g_unk0x006a73c8,
                 3784, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&g_unk0x006c078c, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, g_unk0x006a73c8,
                 3786, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&g_unk0x006c0780, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, g_unk0x006a73c8,
                 3787, "Serialize failed reason is %s", reason);
        return false;
    }
    if (!file.m_bLoading)
    {
        g_unk0x006c0784 = time(0);
        if (file.Access(&g_unk0x006c0784, 4) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, g_unk0x006a73c8,
                      3800, "Serialize failed reason is %s", reason);
            return false;
        }
        srand(g_unk0x006c0784);
    }
    else
    {
        if (file.Access(&g_unk0x006c0784, 4) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, g_unk0x006a73c8,
                      3812, "Serialize failed reason is %s", reason);
            return false;
        }
        srand(g_unk0x006c0784);
    }
    if (file.m_bLoading)
    {
        g_unk0x006c07b8.m_current = g_unk0x006c07b8.begin();
        while (g_unk0x006c07b8.m_current.m_node != g_unk0x006c07b8.m_head)
        {
            delete (RHArtificialIntelligenceForbiddenRemark *)g_unk0x006c07b8.m_current.m_node->m_data;
            ++g_unk0x006c07b8.m_current;
        }
        RHArtificialIntelligenceNode *head = g_unk0x006c07b8.m_head;
        RHArtificialIntelligenceNode *node = head->m_next;
        while (node != head)
        {
            RHArtificialIntelligenceNode *old = node;
            node = node->m_next;
            old->m_prev->m_next = old->m_next;
            old->m_next->m_prev = old->m_prev;
            ::operator delete(old);
            --g_unk0x006c07b8.m_count;
        }
        g_unk0x006c07b8.m_dirty = true;
    }
    return true;
}

template <class T> struct RHArtificialIntelligenceValueNode
{
    RHArtificialIntelligenceValueNode *m_next;
    RHArtificialIntelligenceValueNode *m_previous;
    T m_value;
};

template <class T> struct RHArtificialIntelligenceValueList
{
    int m_allocator;
    RHArtificialIntelligenceValueNode<T> *m_head;
    unsigned m_count;
    RHArtificialIntelligenceValueNode<T> *m_current;
    bool m_dirty;
    char m_11[3];
    int m_index;
    void clear()
    {
        typedef RHScriptIter (RHTitbitList::*Erase)(RHScriptIter, RHScriptIter);
        (((RHTitbitList *)this)->*(Erase)&RHTitbitList::Clear)(((RHUnk0046eb30 *)this)->FUN_0046eb80(), RHScriptIter((RHScriptNode *)m_head));
        m_dirty = true;
    }
    T &operator[](unsigned index)
    {
        ((RHTitbitList *)this)->At(index);
        return m_current->m_value;
    }
};

#define RHAI_LOCAL_ACCESS(address, size, line) \
    if (file.Access(address, size) < 0) \
    { \
        SBString *error = file.GetError(); \
        const char *reason = error->m_chars ? error->m_chars : ""; \
        SBAssert(0, "P:\\Robin Hood\\RHartificialintelligence.cpp", line, "Serialize failed reason is %s", reason); \
        return false; \
    }

#define RHAI_LOCAL_FIELD(offset, size, line) RHAI_LOCAL_ACCESS((char *)this + offset, size, line)

#define RHAI_LOCAL_CHECK(expression, line) \
    if (!(expression)) \
    { \
        SBAssert(1, "P:\\Robin Hood\\RHartificialintelligence.cpp", line, "Serialization failed"); \
        return false; \
    }

// Parked: 87.95%; four-byte frame gap, container scheduling and rule 28.
// STUB: GAME 0x00414be0
bool RHArtificialIntelligence::Unk00414be0(SBFile &file)
{
    RHStimulus stimulus;
    // STRING: GAME 0x006a77ac
    RHSerializeName(file, "RHArtificialIntelligenceLocalAI");
    unsigned count;
    unsigned i;
    if (file.m_version > 37)
    {
        SerializePosition(RHAIField<RHArtificialIntelligencePosition>(this, 0x378), file);
        RHAI_LOCAL_FIELD(0x388, 2, 0xf1b)
        RHAI_LOCAL_FIELD(0x38a, 2, 0xf1c)
    }
    else
        RHAIField<void *>(this, 0x380) = 0;
    if (file.m_version > 32)
    {
        RHArtificialIntelligenceValueList<int> &list = RHAIField<RHArtificialIntelligenceValueList<int> >(this, 0x230);
        int value;
        if (file.m_bLoading)
        {
            RHAI_LOCAL_ACCESS(&count, 4, 0xf2b)
            list.clear();
            for (i = 0; i < count; ++i)
            {
                RHAI_LOCAL_ACCESS(&value, 4, 0xf31)
                ((RHUnkList *)&list)->insert(RHUnkIter(list.m_head), (RHOrder *const &)value);
                list.m_dirty = true;
            }
        }
        else
        {
            count = list.m_count;
            RHAI_LOCAL_ACCESS(&count, 4, 0xf39)
            for (i = 0; i < count; ++i)
            {
                value = list[i];
                RHAI_LOCAL_ACCESS(&value, 4, 0xf3f)
            }
        }
    }
    if (file.m_version >= 14)
    {
        RHAI_LOCAL_FIELD(0x25c, 2, 0xf46)
    }
    if (file.m_version >= 12)
    {
        RHArtificialIntelligenceValueList<RHArtificialIntelligenceTriple> &list = RHAIField<RHArtificialIntelligenceValueList<RHArtificialIntelligenceTriple> >(this, 0x34c);
        RHArtificialIntelligenceTriple value;
        if (file.m_bLoading)
        {
            RHAI_LOCAL_ACCESS(&count, 4, 0xf4e)
            list.clear();
            for (i = 0; i < count; ++i)
            {
                RHAI_LOCAL_ACCESS(&value, 12, 0xf54)
                ((RHArtificialIntelligenceTripleList *)&list)->insert(RHArtificialIntelligenceIterator((RHArtificialIntelligenceNode *)list.m_head), value);
                list.m_dirty = true;
            }
        }
        else
        {
            count = list.m_count;
            RHAI_LOCAL_ACCESS(&count, 4, 0xf5c)
            for (i = 0; i < count; ++i)
            {
                RHAI_LOCAL_ACCESS(&list[i], 12, 0xf61)
            }
        }
    }
    RHAI_LOCAL_CHECK(FUN_00416b30((void *&)m_actor, file), 0xf67)
    RHAI_LOCAL_FIELD(0x0c, 4, 0xf6a)
    RHAI_LOCAL_FIELD(0x10, 4, 0xf6b)
    RHAI_LOCAL_FIELD(0x14, 4, 0xf6c)
    RHAI_LOCAL_FIELD(0x18, 4, 0xf6d)
    RHAI_LOCAL_FIELD(0x1c, 4, 0xf6e)
    RHAI_LOCAL_FIELD(0x20, 4, 0xf6f)
    RHAI_LOCAL_FIELD(0x24, 1, 0xf70)
    RHAI_LOCAL_FIELD(0x28, 4, 0xf71)
    RHAI_LOCAL_FIELD(0x2c, 1, 0xf73)
    RHAI_LOCAL_FIELD(0x71, 1, 0xf75)
    RHAI_LOCAL_FIELD(0x72, 1, 0xf78)
    RHAI_LOCAL_FIELD(0x73, 1, 0xf79)
    RHAI_LOCAL_FIELD(0x74, 2, 0xf7a)
    RHArtificialIntelligencePathCursor *cursor = (RHArtificialIntelligencePathCursor *)((char *)this + 0x30);
    RHAI_LOCAL_CHECK(((RHPath *)cursor)->SerializeStatus(file), 0xf7e)
    RHAI_LOCAL_FIELD(0x70, 1, 0xf7f)
    if (RHAIField<char>(this, 0x70))
    {
        unsigned short offset;
        if (file.m_bLoading)
        {
            RHAI_LOCAL_ACCESS(&offset, 2, 0xf87)
            void *waypoint = RHAIField<void **>(RHAIField<void *>(cursor, 4), 4)[RHAIField<unsigned char>(cursor, 0)];
            RHAIField<char *>(this, 0x78) = RHAIField<char *>(waypoint, 0x74) + offset;
        }
        else
        {
            void *waypoint = RHAIField<void **>(RHAIField<void *>(cursor, 4), 4)[RHAIField<unsigned char>(cursor, 0)];
            offset = (unsigned short)(RHAIField<char *>(this, 0x78) - RHAIField<char *>(waypoint, 0x74));
            RHAI_LOCAL_ACCESS(&offset, 2, 0xf8d)
        }
    }
    RHAI_LOCAL_FIELD(0x7c, 2, 0xf90)
    RHAI_LOCAL_FIELD(0x7e, 1, 0xf91)
    RHAI_LOCAL_CHECK(FUN_00416b30(RHAIField<void *>(this, 0x80), file), 0xf94)
    RHAI_LOCAL_CHECK(FUN_00416b30(RHAIField<void *>(this, 0x84), file), 0xf95)
    RHAI_LOCAL_CHECK(FUN_00416b30(RHAIField<void *>(this, 0x88), file), 0xf96)
    RHAI_LOCAL_CHECK(FUN_00416b30(RHAIField<void *>(this, 0x8c), file), 0xf97)
    RHAI_LOCAL_CHECK(FUN_00416b30(RHAIField<void *>(this, 0x90), file), 0xf9a)
    RHAI_LOCAL_CHECK(FUN_00416b30(RHAIField<void *>(this, 0x94), file), 0xf9b)
    RHAI_LOCAL_FIELD(0x98, 1, 0xf9e)
    RHAI_LOCAL_FIELD(0x9c, 4, 0xf9f)
    RHAI_LOCAL_FIELD(0xa0, 1, 0xfa0)
    RHAI_LOCAL_FIELD(0xa4, 4, 0xfa1)
    RHAI_LOCAL_FIELD(0xa8, 2, 0xfa4)
    RHAI_LOCAL_FIELD(0xaa, 2, 0xfa7)
    RHAI_LOCAL_FIELD(0xac, 4, 0xfaa)
    RHAI_LOCAL_FIELD(0xb0, 4, 0xfab)
    RHAI_LOCAL_FIELD(0xb4, 4, 0xfac)
    RHAI_LOCAL_FIELD(0xb8, 4, 0xfad)
    RHAI_LOCAL_FIELD(0xbc, 4, 0xfae)
    RHAI_LOCAL_FIELD(0xc0, 2, 0xfaf)
    RHAI_LOCAL_FIELD(0xc2, 2, 0xfb0)
    RHAI_LOCAL_FIELD(0xc4, 2, 0xfb1)
    RHAI_LOCAL_FIELD(0xc6, 2, 0xfb2)
    RHAI_LOCAL_FIELD(0xc8, 2, 0xfb3)
    RHAI_LOCAL_FIELD(0xca, 1, 0xfb6)
    RHAI_LOCAL_CHECK(FUN_00416b30(RHAIField<void *>(this, 0xcc), file), 0xfb7)
    SerializePosition(RHAIField<RHArtificialIntelligencePosition>(this, 0xd0), file);
    SerializePosition(RHAIField<RHArtificialIntelligencePosition>(this, 0xe0), file);
    RHAI_LOCAL_FIELD(0xf0, 1, 0xfbe)
    RHAI_LOCAL_FIELD(0xf4, 4, 0xfc1)
    RHAI_LOCAL_FIELD(0xf8, 4, 0xfc2)
    RHAI_LOCAL_FIELD(0xfc, 1, 0xfc3)
    RHAI_LOCAL_FIELD(0xfd, 1, 0xfc4)
    RHAI_LOCAL_CHECK(SerializeListOfPointersToHumans(RHAIField<RHArtificialIntelligenceList>(this, 0x100), file), 0xfc8)
    RHAI_LOCAL_CHECK(SerializeListOfPointersToActorsNPC(RHAIField<RHArtificialIntelligenceList>(this, 0x124), file), 0xfc9)
    RHAI_LOCAL_CHECK(SerializeListOfPointersToActorsNPC(RHAIField<RHArtificialIntelligenceList>(this, 0x148), file), 0xfca)
    RHAI_LOCAL_FIELD(0x16c, 1, 0xfcd)
    RHAI_LOCAL_FIELD(0x16d, 1, 0xfce)
    RHAI_LOCAL_FIELD(0x16e, 1, 0xfcf)
    RHAI_LOCAL_FIELD(0x16f, 1, 0xfd2)
    RHAI_LOCAL_FIELD(0x170, 1, 0xfd3)
    RHAI_LOCAL_FIELD(0x171, 1, 0xfd7)
    RHAI_LOCAL_FIELD(0x172, 1, 0xfda)
    RHAI_LOCAL_FIELD(0x173, 1, 0xfdd)
    RHAI_LOCAL_FIELD(0x174, 1, 0xfe1)
    RHAI_LOCAL_FIELD(0x175, 1, 0xfe2)
    RHArtificialIntelligenceValueList<RHStimulus> &stimuli = RHAIField<RHArtificialIntelligenceValueList<RHStimulus> >(this, 0x178);
    if (file.m_bLoading)
    {
        RHAI_LOCAL_ACCESS(&count, 4, 0xfe6)
        RHScriptIter first((RHScriptNode *)stimuli.m_head->m_next);
        RHScriptNode *last = (RHScriptNode *)stimuli.m_head;
        while (first.node != last)
        {
            typedef RHProfilePointerList::iterator Native;
            typedef Native (Native::*Increment)(int);
            typedef RHScriptIter (RHSectorActorIter::*Forward)(int);
            Increment increment = &Native::operator++;
            ((RHUnk0046eb30 *)&stimuli)->erase((((RHSectorActorIter *)&first)->*(Forward)increment)(0));
        }
        stimuli.m_dirty = true;
        for (i = 0; i < count; ++i)
        {
            RHAI_LOCAL_CHECK(stimulus.Serialize(file), 0xfec)
            RHArtificialIntelligenceStimulusNode *head = (RHArtificialIntelligenceStimulusNode *)stimuli.m_head;
            head->m_previous = ((RHArtificialIntelligenceStimulusList *)&stimuli)->Unk00424340(head, head->m_previous);
            RHArtificialIntelligenceStimulusNode *node = head->m_previous;
            node->m_previous->m_next = node;
            FUN_00424470((RHStimulus *)(node + 1), &stimulus);
            ++stimuli.m_count;
            stimuli.m_dirty = true;
        }
    }
    else
    {
        count = stimuli.m_count;
        RHAI_LOCAL_ACCESS(&count, 4, 0xff4)
        for (i = 0; i < count; ++i)
        {
            RHAI_LOCAL_CHECK(stimuli[i].Serialize(file), 0xff9)
        }
    }
    RHAI_LOCAL_FIELD(0x1c4, 1, 0xffc)
    RHAI_LOCAL_FIELD(0x1c5, 1, 0xffd)
    RHAI_LOCAL_FIELD(0x1c6, 2, 0x1000)
    RHAI_LOCAL_FIELD(0x1c8, 4, 0x1003)
    RHAI_LOCAL_FIELD(0x1cc, 4, 0x1004)
    RHAI_LOCAL_CHECK(((RHUnkPathGeometry *)g_unk0x6c0a9c)->Unk004fc030(file, RHAIField<void *>(this, 0x1d0)), 0x1006)
    RHAI_LOCAL_CHECK(SerializeListOfPointersToObjects(RHAIField<RHArtificialIntelligenceList>(this, 0x1d4), file), 0x1008)
    RHAI_LOCAL_CHECK(((RHReconnaissanceEngine *)g_pEngine)->Unk004c4110(file, RHAIField<void *>(this, 0x1f8)), 0x1009)
    RHAI_LOCAL_CHECK(((RHReconnaissanceEngine *)g_pEngine)->Unk004c3cb0(file, RHAIField<void *>(this, 0x1fc)), 0x100a)
    RHAI_LOCAL_CHECK(((RHReconnaissanceEngine *)g_pEngine)->Unk004c3cb0(file, RHAIField<void *>(this, 0x200)), 0x100b)
    RHAI_LOCAL_FIELD(0x204, 1, 0x100c)
    RHAI_LOCAL_FIELD(0x7f, 1, 0x100e)
    SerializeListOfPointersToActorsNPC(RHAIField<RHArtificialIntelligenceList>(this, 0x208), file);
    unsigned short &walkingFlags = RHAIField<unsigned short>(this, 0x22c);
    if (file.m_bLoading)
    {
        RHAI_LOCAL_ACCESS(&walkingFlags, 2, 0x1013)
        if ((RHAIField<unsigned>(m_actor, 4) & 31) == 4 && (walkingFlags & 0xd802))
        {
            SBAssert(0, "P:\\Robin Hood\\RHartificialintelligence.cpp", 0x1017,
                     // STRING: GAME 0x006a7784
                     "Bad walking flags for civilians read!");
            walkingFlags &= 0x27fd;
        }
    }
    else
    {
        if ((RHAIField<unsigned>(m_actor, 4) & 31) == 4 && (walkingFlags & 0xd802))
        {
            SBAssert(0, "P:\\Robin Hood\\RHartificialintelligence.cpp", 0x1020,
                     // STRING: GAME 0x006a7758
                     "Bad walking flags for civilians written!");
            walkingFlags &= 0x27fd;
        }
        RHAI_LOCAL_ACCESS(&walkingFlags, 2, 0x1023)
    }
    RHAI_LOCAL_FIELD(0x22e, 1, 0x1025)
    RHAI_LOCAL_FIELD(0x258, 4, 0x1027)
    if (file.m_bLoading && RHAIField<int>(this, 0x258) != 121)
    {
        unsigned short flags = RHAIField<unsigned short>(this, 0x25c);
        RHAIField<int>(this, 0x258) = 121;
        RHAIField<unsigned short>(this, 0x25c) = 0;
        Unk004195f0(flags);
    }
    RHAI_LOCAL_FIELD(0x25e, 2, 0x1031)
    RHAI_LOCAL_FIELD(0x25f, 1, 0x1032)
    RHAI_LOCAL_FIELD(0x260, 4, 0x1034)
    RHAI_LOCAL_FIELD(0x264, 4, 0x1035)
    RHAI_LOCAL_FIELD(0x268, 1, 0x1036)
    RHAI_LOCAL_CHECK(((RHReconnaissanceReport *)((char *)this + 0x26c))->Serialize(file), 0x1038)
    RHAI_LOCAL_FIELD(0x2ac, 1, 0x103a)
    RHAI_LOCAL_FIELD(0x348, 1, 0x103b)
    RHAI_LOCAL_CHECK(((RHReconnaissanceEngine *)g_pEngine)->Unk004c3cb0(file, RHAIField<void *>(this, 0x2b0)), 0x103d)
    SerializeListOfPointersToActorsNPC(RHAIField<RHArtificialIntelligenceList>(this, 0x2b4), file);
    SerializeListOfPointersToActorsNPC(RHAIField<RHArtificialIntelligenceList>(this, 0x2d8), file);
    SerializeListOfPointersToActorsNPC(RHAIField<RHArtificialIntelligenceList>(this, 0x2fc), file);
    RHAI_LOCAL_FIELD(0x344, 1, 0x1041)
    RHAI_LOCAL_FIELD(0x346, 2, 0x1042)
    return V08(file);
}

#undef RHAI_LOCAL_ACCESS
#undef RHAI_LOCAL_FIELD
#undef RHAI_LOCAL_CHECK

// FUNCTION: GAME 0x00416710
void RHArtificialIntelligence::Unk00416710(unsigned value)
{
    Unk00422b70(7, value);
    if (value == 0)
        value = 1;
    ((RHArtificialIntelligenceActorCalls *)m_actor)->Unk0048b450(value, 0);
}

// FUNCTION: GAME 0x00416740
short FUN_00416740()
{
    const unsigned short &weight = g_unk0x006c078a;
    const unsigned short &value = g_unk0x006c06c2;
    short result;
    if (weight > 0)
        result = (int)(unsigned short)value / (int)(unsigned short)weight;
    else if (g_unk0x006c0738 == g_unk0x006c06c0)
        result = 50;
    else
        result = g_unk0x006c0738 ? 0 : 100;
    if (g_unk0x006c07b4.weight > 0)
    {
        short weighted = *(unsigned long *)&g_unk0x006c07b4 * result;
        weighted += g_unk0x006c07b4.value;
        weighted += value;
        result = weighted / (g_unk0x006c07b4.weight + (int)(unsigned short)weight);
    }
    if (result < 0)
        result = 0;
    else if (result > 100)
        result = 100;
    g_unk0x006c078a = 0;
    g_unk0x006c06c2 = 0;
    g_unk0x006c07b4.weight = 0;
    g_unk0x006c07b4.value = 0;
    g_unk0x006c0738 = false;
    g_unk0x006c06c0 = false;
    return result;
}

short EmitRHAIConsiderations()
{
    return FUN_00416740();
}

// FUNCTION: GAME 0x00416b30
bool FUN_00416b30(void *&value, SBFile &file)
{
    unsigned short index;
    RHArtificialIntelligenceEngineView *engine;
    if (file.m_bLoading)
    {
        if (file.Access(&index, 2) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0,
                     g_unk0x006a73c8,
                     4772, "Serialize failed reason is %s", reason);
            return false;
        }
        if (index == 0xd431)
        {
            value = 0;
            return true;
        }
        engine = (RHArtificialIntelligenceEngineView *)g_pEngine;
        if (index >= engine->m_elements.size())
            return false;
        value = engine->m_elements[index];
        return true;
    }
    {
        if (value)
        {
            engine = (RHArtificialIntelligenceEngineView *)g_pEngine;
            engine->m_elements.Find(value, index);
        }
        else
            index = 0xd431;
        if (file.Access(&index, 2) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, g_unk0x006a73c8,
                     4820, "Serialize failed reason is %s", reason);
            return false;
        }
        return true;
    }
}

// New probe: marker flip leaves dirty-end/cursor scheduling at 92.39% and creates an effective row.
// STUB: GAME 0x00416c80
bool RHArtificialIntelligence::SerializeListOfPointersToActorsNPC(RHArtificialIntelligenceList &list, SBFile &file)
{
    // STRING: GAME 0x006a77cc
    RHSerializeName(file, "ListOfPointerToActorsNPC");
    unsigned count;
    RHArtificialIntelligenceElement *element;
    if (file.m_bLoading)
    {
        list.clear();
        if (file.Access(&count, 4) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, g_unk0x006a73c8,
                     4980, "Serialize failed reason is %s", reason);
            return false;
        }
        for (unsigned i = 0; i < count; ++i)
        {
            if (!FUN_00416b30((void *&)element, file))
            {
                SBAssert(1, "P:\\Robin Hood\\RHartificialintelligence.cpp", 4985, "Serialization failed");
                return false;
            }
            if (element)
            {
                unsigned type = element->m_flags & 0xf;
                if (type != 4)
                    return false;
                list.InsertLast((void *)element);
            }
        }
    }
    else
    {
        count = list.m_count;
        if (file.Access(&count, 4) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, g_unk0x006a73c8,
                     5013, "Serialize failed reason is %s", reason);
            return false;
        }
        for (unsigned i = 0; i < count; ++i)
        {
            element = list[i];
            if (!FUN_00416b30((void *&)element, file))
            {
                SBAssert(1, "P:\\Robin Hood\\RHartificialintelligence.cpp", 5019, "Serialization failed");
                return false;
            }
        }
    }
    return true;
}

// New probe: marker flip leaves dirty-end/cursor scheduling at 91.84% and creates an effective row.
// STUB: GAME 0x00416f40
bool RHArtificialIntelligence::SerializeListOfPointersToHumans(RHArtificialIntelligenceList &list, SBFile &file)
{
    // STRING: GAME 0x006a77e8
    RHSerializeName(file, "ListOfPointerToHumans");
    unsigned count;
    RHArtificialIntelligenceElement *element;
    if (file.m_bLoading)
    {
        list.clear();
        if (file.Access(&count, 4) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, g_unk0x006a73c8,
                     5053, "Serialize failed reason is %s", reason);
            return false;
        }
        for (unsigned i = 0; i < count; ++i)
        {
            if (!FUN_00416b30((void *&)element, file))
            {
                SBAssert(1,
                         // STRING: GAME 0x006a73f8
                         "P:\\Robin Hood\\RHartificialintelligence.cpp",
                         5058, "Serialization failed");
                return false;
            }
            list.InsertLast((void *)element);
        }
    }
    else
    {
        count = list.m_count;
        if (file.Access(&count, 4) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, g_unk0x006a73c8,
                     5068, "Serialize failed reason is %s", reason);
            return false;
        }
        for (unsigned i = 0; i < count; ++i)
        {
            element = list[i];
            if (!FUN_00416b30((void *&)element, file))
            {
                SBAssert(1, "P:\\Robin Hood\\RHartificialintelligence.cpp",
                         5075, "Serialization failed");
                return false;
            }
        }
    }
    return true;
}

// New probe: marker flip leaves dirty-end/cursor scheduling at 92.76% and creates an effective row.
// STUB: GAME 0x004171f0
bool RHArtificialIntelligence::SerializeListOfPointersToObjects(RHArtificialIntelligenceList &list, SBFile &file)
{
    // STRING: GAME 0x006a7800
    RHSerializeName(file, "ListOfPointerToObjects");
    unsigned count;
    RHArtificialIntelligenceElement *element;
    if (file.m_bLoading)
    {
        list.clear();
        if (file.Access(&count, 4) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, g_unk0x006a73c8,
                     5110, "Serialize failed reason is %s", reason);
            return false;
        }
        for (unsigned i = 0; i < count; ++i)
        {
            if (!FUN_00416b30((void *&)element, file))
            {
                SBAssert(1, "P:\\Robin Hood\\RHartificialintelligence.cpp", 5115, "Serialization failed");
                return false;
            }
            if (element)
            {
                unsigned type = element->m_flags & 3;
                if (type == 3)
                    list.InsertLast((void *)element);
            }
        }
    }
    else
    {
        count = list.m_count;
        if (file.Access(&count, 4) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, g_unk0x006a73c8,
                     5134, "Serialize failed reason is %s", reason);
            return false;
        }
        for (unsigned i = 0; i < count; ++i)
        {
            element = list[i];
            if (!FUN_00416b30((void *&)element, file))
            {
                SBAssert(1, "P:\\Robin Hood\\RHartificialintelligence.cpp", 5140, "Serialization failed");
                return false;
            }
        }
    }
    return true;
}

// FUNCTION: GAME 0x004174b0
bool RHArtificialIntelligence::SerializePosition(RHArtificialIntelligencePosition &position, SBFile &file)
{
    // STRING: GAME 0x006a7818
    RHSerializeName(file, "RHArtificialIntelligencePosition");
    if (file.Access(&position.m_00, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, g_unk0x006a73c8,
                 5166, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&position.m_04, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, g_unk0x006a73c8,
                 5167, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&position.m_0c, 2) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, g_unk0x006a73c8,
                 5168, "Serialize failed reason is %s", reason);
        return false;
    }
    ((RHUnkPathGeometry *)g_unk0x6c0a9c)->Unk004fbec0(file, position.m_08);
    return true;
}

class RHDrawManager : public SBGeoBoundingBox2D
{
public:
    static RHDrawManager *mpDrawManager;
    float m_scale;
    unsigned m_18;
    SBDrawManager *m_drawManager;
};

class RHMobileUnk00607da0
{
public:
    RHMobileUnk00607da0 &FUN_00607da0(const RHMobileUnk00607da0 &other);
};

extern float g_unk0x006774cc;
extern float g_unk0x006774a0;

void FUN_00417ab0(const SBGeoBoundingBox2D &box, unsigned char red, unsigned char green, unsigned char blue,
                 SBDrawManager *draw, bool shade);
void FUN_00417ca0(const SBGeoBoundingBox2D &box, unsigned char red, unsigned char green, unsigned char blue,
                 SBDrawManager *draw, unsigned char thickness, bool shade);

// Parked: 94.29%; clipped-box vector temporaries use different stack slots and argument registers.
// STUB: GAME 0x00417580
void RHArtificialIntelligence::FUN_00417580()
{
    SBGeoPoint2D center;
    SBGeoBoundingBox2D outline;
    SBGeoBoundingBox2D fill;
    RHDrawManager *draw = RHDrawManager::mpDrawManager;
    SBGeoBoundingBox2D clip = draw->FUN_00417a20();
    float scale = draw->m_scale;
    center = RHAIField<SBGeoPoint2D>(RHAIField<void *>(m_actor, 0x50), 0x24).Unk005fc190(SBGeoVector2D(0.0f, -55.0f));
    void *interfaceObject = RHAIField<void *>(m_actor, 0x49c);
    unsigned short first = RHAIField<unsigned short>(m_actor, 0x648);
    unsigned short second = RHAIField<unsigned short>(m_actor, 0x546 + RHAIField<int>(interfaceObject, 4));
    unsigned short maximum = first > second ? first : second;
    unsigned value;
    if (maximum > 1000)
        value = 1000;
    else
        value = (unsigned short)(first > second ? first : second);
    fill.FUN_00609050(center.FUN_005fc200(SBGeoVector2D(20.0f, 2.0f)),
        center.Unk005fc190(SBGeoVector2D(((unsigned short)value * g_unk0x006774cc) * 40.0f - g_unk0x006774a0, 0.0f)));
    ((RHMobileUnk00607da0 *)&fill)->FUN_00607da0((const RHMobileUnk00607da0 &)clip.FUN_006092c0(fill));
    if (fill.Unk00608f30())
    {
        fill -= (SBGeoVector2D)clip.first;
        fill.FUN_006091d0(scale);
        FUN_00417ab0(fill, 255, 0, 0, draw->m_drawManager, false);
    }
    outline.FUN_00609050(center.FUN_005fc200(SBGeoVector2D(20.0f, 2.0f)),
        center.Unk005fc190(SBGeoVector2D(20.0f, 2.0f)));
    ((RHMobileUnk00607da0 *)&outline)->FUN_00607da0((const RHMobileUnk00607da0 &)clip.FUN_006092c0(outline));
    if (outline.Unk00608f30())
    {
        outline -= (SBGeoVector2D)clip.first;
        outline.FUN_006091d0(scale);
        FUN_00417ca0(outline, 255, 255, 255, draw->m_drawManager, 0, false);
    }
}

// FUNCTION: GAME 0x00417a20
SBGeoBoundingBox2D SBGeoBoundingBox2D::FUN_00417a20()
{
    return *this;
}

// FUNCTION: GAME 0x00417a40
unsigned short FUN_00417a40(unsigned char red, unsigned char green, unsigned char blue, unsigned short depth)
{
    switch ((unsigned char)depth)
    {
    case 15:
        return (((red & 0xf8) << 5) | (green & 0xf8)) << 2 | (blue >> 3);
    case 16:
        return (((red & 0xf8) << 5) | (green & 0xfc)) << 3 | (blue >> 3);
    }
    return 0;
}


// Parked: 82.07%; dark-color x87 operand order and shaded-edge register scheduling differ.
// STUB: GAME 0x00417ab0
void FUN_00417ab0(const SBGeoBoundingBox2D &box, unsigned char red, unsigned char green, unsigned char blue,
                 SBDrawManager *draw, bool shade)
{
    SBGeoPoint2D lowerLeft;
    SBGeoPoint2D upperRight;
    unsigned short depth = *(unsigned short *)((char *)draw + 0x10c);
    unsigned short color = FUN_00417a40(red, green, blue, depth);
    double r;
    unsigned short brightRed = (unsigned short)((r = red) * 1.5);
    if (brightRed > 255)
        brightRed = 255;
    double g;
    unsigned short brightGreen = (unsigned short)((g = green) * 1.5);
    if (brightGreen > 255)
        brightGreen = 255;
    double b;
    unsigned short brightBlue = (unsigned short)((b = blue) * 1.5);
    if (brightBlue > 255)
        brightBlue = 255;
    unsigned short bright = FUN_00417a40((unsigned char)brightRed, (unsigned char)brightGreen, (unsigned char)brightBlue,
        *(unsigned short *)((char *)draw + 0x10c));
    unsigned short dark = FUN_00417a40((unsigned char)(0.7 * r), (unsigned char)(0.7 * g),
        (unsigned char)(0.7 * b), *(unsigned short *)((char *)draw + 0x10c));
    draw->FUN_005e61e0(0, &box, color, 0);
    if (shade)
    {
        upperRight.m_x = box.last.m_x;
        float top = box.first.m_y;
        upperRight.m_y = top;
        lowerLeft.m_x = box.first.m_x;
        float bottom = box.last.m_y;
        lowerLeft.m_y = bottom;
        draw->FUN_005ecbd0(0, lowerLeft, box.last, dark);
        draw->FUN_005ecbd0(0, box.last, upperRight, dark);
        draw->FUN_005ecbd0(0, lowerLeft, box.first, bright);
        draw->FUN_005ecbd0(0, box.first, upperRight, bright);
    }
}

// Parked: 73.96%; expanded-corner x87 temporaries and call argument scheduling differ.
// STUB: GAME 0x00417ca0
void FUN_00417ca0(const SBGeoBoundingBox2D &box, unsigned char red, unsigned char green, unsigned char blue,
                 SBDrawManager *draw, unsigned char thickness, bool shade)
{
    SBGeoBoundingBox2D expanded;
    SBGeoPoint2D first;
    SBGeoPoint2D last;
    unsigned short color = FUN_00417a40(red, green, blue, *(unsigned short *)((char *)draw + 0x10c));
    unsigned short dark = FUN_00417a40((unsigned char)(red * 0.7), (unsigned char)(green * 0.7),
        (unsigned char)(blue * 0.7), *(unsigned short *)((char *)draw + 0x10c));
    float size = thickness;
    first.m_y = box.first.m_y - size - 1.0f;
    first.m_x = box.first.m_x - size - 1.0f;
    last.m_x = box.last.m_x + size;
    last.m_y = box.last.m_y + size;
    expanded.FUN_00609050(first, last);
    if (shade)
        draw->FUN_005ecdc0(0, expanded.FUN_006090d0(SBGeoVector2D(1.0f, 1.0f)), dark, 0);
    draw->FUN_005ecdc0(0, expanded, color, 0);
}

void EmitArtificialIntelligenceDebug(SBGeoBoundingBox2D &box)
{
    box.FUN_00417a20();
    FUN_00417a40(0, 0, 0, 0);
    FUN_00417ab0(box, 0, 0, 0, (SBDrawManager *)&box, false);
    FUN_00417ca0(box, 0, 0, 0, (SBDrawManager *)&box, 0, false);
}

class RHArtificialIntelligenceDoorCalls
{
public:
    virtual bool V00(int mode, void *actor, int first, int second, int third) = 0;
};

// Parked: 26.76%; nearest-door stack layout, temporary lifetimes and iterator register allocation differ.
// STUB: GAME 0x00417ed0
void *RHArtificialIntelligence::FUN_00417ed0(SBGeoPoint2D *position, bool active)
{
    RHUnk005fc3b0 direction;
    SBGeoPoint2D own;
    unsigned short best = 0xffff;
    void *result = 0;
    own = RHAIField<SBGeoPoint2D>(RHAIField<void *>(m_actor, 0x50), 0x24);
    RHArtificialIntelligenceStaticArray &doors = RHAIField<RHArtificialIntelligenceStaticArray>(g_unk0x6c0a9c, 0x4080);
    unsigned short count = doors.size();
    for (unsigned short index = 0; index < count; ++index)
    {
        void *door = doors[index];
        if (RHAIField<int>(door, 4) != 1)
            continue;
        direction.FUN_005fc430(RHAIField<SBGeoPoint2D>(door, 0x18).Unk005fc110(own));
        if (RHAIField<int>(door, 0x88) != 1)
            continue;
        void *area = RHAIField<void *>(RHAIField<void *>(m_actor, 0x50), 0xe0);
        if (!((RHAIField<unsigned>(area, 0x30) >> 13) & 1))
            area = 0;
        if (RHAIField<void *>(door, 0x10) == area ||
            !((RHArtificialIntelligenceDoorCalls *)door)->V00(1, m_actor, 0, 0, 0))
            continue;
        if (position)
        {
            SBGeoPoint2D offset = FUN_0040ec20(*(RHMalignityPosition *)position,
                FUN_004165e0(m_actor, true));
            if (((SBGeoVector2D &)direction).FUN_005fc660(offset) >= 0.0f)
                continue;
        }
        if (active && !RHAIField<bool>(RHAIField<void *>(door, 0x10), 0x118))
            continue;
        RHMalignityPosition destination;
        destination.x = RHAIField<float>(door, 0x18);
        destination.y = RHAIField<float>(door, 0x1c);
        destination.area = RHAIField<void *>(door, 0x0c);
        destination.layer = RHAIField<unsigned short>(door, 0x14);
        SBGeoPoint2D offset = FUN_0040ec20(destination, FUN_004165e0(m_actor, true));
        direction.FUN_005fc430(offset);
        int distance = (int)direction.FUN_005fc700(1.0f);
        void *profile = RHAIField<void *>(m_actor, 0x50);
        if (destination.area != RHAIField<void *>(profile, 0xe0))
            distance += 500;
        if (destination.layer != RHAIField<unsigned short>(profile, 0xde))
            distance += 300;
        unsigned short candidate = (unsigned short)distance;
        if (candidate >= best)
            continue;
        bool blocked = false;
        if (m_actor->V130() == 1)
        {
            RHArtificialIntelligenceList &occupants = RHAIField<RHArtificialIntelligenceList>(RHAIField<void *>(door, 0x10), 0xf4);
            unsigned short size = occupants.m_count;
            for (unsigned short occupant = 0; occupant < size; ++occupant)
            {
                occupants.GoTo(occupant);
                if ((occupants.m_current.m_node->m_data->m_flags & 15) == 12)
                {
                    blocked = true;
                    break;
                }
            }
        }
        if (!blocked)
        {
            best = candidate;
            result = door;
        }
    }
    return result;
}

class RHArtificialIntelligenceDispatchView
{
public:
    virtual void V00() = 0;
    virtual void V04() = 0;
    virtual void V08() = 0;
    virtual void V0c() = 0;
    virtual void V10() = 0;
    virtual void V14() = 0;
    virtual void V18() = 0;
    virtual void V1c() = 0;
    virtual void V20() = 0;
    virtual void V24(RHStimulus *stimulus) = 0;
};

struct RHUnkPathRegistry;
extern RHUnkPathRegistry *g_unk0x6c0b9c;

// Parked: 82.38%; argument/register scheduling and dispatch tail merging.
// STUB: GAME 0x00418600
bool RHArtificialIntelligence::Unk00418600(unsigned short path)
{
    RHUnk005fc3b0 direction;
    Unk00410600();
    if (path == 0xffff)
    {
        RHAIField<char>(this, 0x70) = 0;
        ((RHArtificialIntelligencePathCursor *)((char *)this + 0x30))->Unk00550f60(0xffff);
        RHUnk00571160Position position;
        ((RHUnk00560420 *)((char *)m_actor->m_data + 4))->Unk(&position);
        RHAIField<RHUnk00571160Position>(m_actor, 0x4dc) = position;
        direction.Unk005fcd40(RHAIField<unsigned short>(m_actor->m_data, 0xd8), 0.57357645f);
        RHAIField<SBGeoPoint2D>(m_actor, 0x4d4) = direction;
        char disabled = RHAIField<char>(this, 0x1c4);
        m_16f = 0;
        m_170 = 0;
        m_173 = 0;
        if (!disabled)
        switch (RHAIField<int>(this, 0x0c))
        {
        case 1:
        {
            RHStimulus stimulus;
            stimulus.Unk004188d0(0x15);
            ((RHArtificialIntelligenceDispatchView *)this)->V24(&stimulus);
            break;
        }
        }
    }
    else if (path == 0xfffe)
    {
        RHAIField<char>(this, 0x70) = 0;
        ((RHArtificialIntelligencePathCursor *)((char *)this + 0x30))->Unk00550f60(0xffff);
        RHUnk00571160Position position;
        ((RHUnk00560420 *)((char *)m_actor->m_data + 4))->Unk(&position);
        RHAIField<RHUnk00571160Position>(m_actor, 0x4dc) = position;
        direction.Unk005fcd40(RHAIField<unsigned short>(m_actor->m_data, 0xd8), 0.57357645f);
        RHAIField<SBGeoPoint2D>(m_actor, 0x4d4) = direction;
        char disabled = RHAIField<char>(this, 0x1c4);
        m_16f = 1;
        m_170 = 0;
        m_173 = 0;
        if (!disabled)
        switch (RHAIField<int>(this, 0x0c))
        {
        case 1:
        {
            RHStimulus stimulus;
            stimulus.m_20 = 0x15;
            *(unsigned short *)stimulus.m_00 = 0;
            stimulus.m_type = 0;
            ((RHArtificialIntelligenceDispatchView *)this)->V24(&stimulus);
            break;
        }
        }
    }
    else
    {
        RHAIField<char>(this, 0x70) = 1;
        void **first = RHAIField<void **>(g_unk0x6c0b9c, 8);
        unsigned count = first == 0 ? 0 : RHAIField<void **>(g_unk0x6c0b9c, 0x0c) - first;
        if (path > (unsigned short)count)
        {
            SBAssert(1, "P:\\Robin Hood\\RHartificialintelligence.cpp", 5598,
                     // STRING: GAME 0x006a783c
                     "Assigned illegal path on point (%f,%f) !", m_actor->m_data->m_x, m_actor->m_data->m_y);
            return false;
        }
        ((RHArtificialIntelligencePathCursor *)((char *)this + 0x30))->Unk00550f60(path);
        char disabled = RHAIField<char>(this, 0x1c4);
        m_16f = 0;
        m_170 = 0;
        if (!disabled)
        switch (RHAIField<int>(this, 0x0c))
        {
        case 1:
        {
            RHStimulus stimulus;
            stimulus.m_20 = 0x15;
            *(unsigned short *)stimulus.m_00 = 0;
            stimulus.m_type = 0;
            ((RHArtificialIntelligenceDispatchView *)this)->V24(&stimulus);
            break;
        }
        }
    }
    return true;
}

// FUNCTION: GAME 0x004188d0
void RHStimulus::Unk004188d0(int value)
{
    *(unsigned short *)m_00 = 0;
    m_20 = value;
    m_type = 0;
}

struct RHArtificialIntelligenceRemarkEntry
{
    unsigned short m_command;
    unsigned short m_02;
    std::string m_name;
    int m_remark;
    RHArtificialIntelligenceRemarkEntry(unsigned flags)
    {
        *(unsigned char *)&m_name = (unsigned char)flags;
    }
};

struct RHArtificialIntelligenceRemarkNode
{
    RHArtificialIntelligenceRemarkNode *m_next;
    RHArtificialIntelligenceRemarkNode *m_previous;
    RHArtificialIntelligenceRemarkEntry *m_entry;
};

// GLOBAL: GAME 0x006c0794
RHArtificialIntelligenceRemarkNode *g_unk0x006c0794;
// GLOBAL: GAME 0x006c0798
unsigned g_unk0x006c0798;
// GLOBAL: GAME 0x006c07a0
char g_unk0x006c07a0;
// GLOBAL: GAME 0x006c07e0
unsigned short g_unk0x006c07e0;
// GLOBAL: GAME 0x006c1070
RHArtificialIntelligenceSoundCalls *g_unk0x006c1070;

#define RHAI_REMARK_ERROR(message, line) \
    { \
        std::string name = FUN_00420d40(remark); \
        const char *text = name.c_str(); \
        RHArtificialIntelligenceInitialData *data = m_actor->m_data; \
        SBAssert(0, "P:\\Robin Hood\\RHartificialintelligence.cpp", line, message, text, \
                 (unsigned short)data->m_x, (unsigned short)data->m_y); \
    }

// Parked: 61.78%; string cleanup, search/register scheduling and switch layout.
// STUB: GAME 0x00418c40
void RHArtificialIntelligence::Unk00418c40(int remark, unsigned flags)
{
    SBGeoPoint2D position;
    unsigned variant = 0xffff;
    Unk00422b70(4, remark);
    if (RHAIField<char>(m_actor, 8))
    {
        Unk00422b70(5, 0);
        Unk004195f0(flags);
        return;
    }
    RHArtificialIntelligenceList &forbidden = RHAIField<RHArtificialIntelligenceList>(this, 0x230);
    RHAIField<int>(this, 0x250) = remark;
    RHAIField<char>(this, 0x248) = 1;
    forbidden.m_current.m_node = forbidden.m_head->m_next;
    int count = forbidden.m_count;
    int i = 0;
    while (i < count)
    {
        if ((int)forbidden.m_current.m_node->m_data == RHAIField<int>(this, 0x250))
            break;
        ++i;
        ((RHSectorActorIter *)&forbidden.m_current)->operator++(0);
    }
    if (i < count)
    {
        RHAIField<int>(this, 0x24c) = i;
        forbidden.m_dirty = false;
        forbidden.m_index = i;
    }
    else
    {
        forbidden.m_dirty = true;
        RHAIField<int>(this, 0x24c) = -1;
    }
    if (RHAIField<int>(this, 0x24c) != -1)
    {
        Unk00422b70(5, 1);
        Unk004195f0(flags);
        return;
    }
    if (!(flags & 8) && Unk00419b20(remark))
    {
        Unk00422b70(5, 2);
        Unk004195f0(flags);
        return;
    }
    if (!(flags & 1) && ((RHArtificialIntelligenceActorCalls *)m_actor)->Unk00485e60())
    {
        Unk00422b70(5, 3);
        Unk004195f0(flags);
        return;
    }
    if (flags & 0x800)
    {
        variant = ((int)g_unk0x006c07e0 + 1) % 3;
        g_unk0x006c07e0 = variant;
    }
    if (RHAIField<int>(this, 0x258) != 121)
    {
        if (!(flags & 2))
        {
            Unk00422b70(5, 4);
            Unk004195f0(flags);
            return;
        }
        g_unk0x006c1070->Unk005a8d10(m_actor);
    }
    position = RHAIField<SBGeoPoint2D>(m_actor->m_data, 0x24);
    RHAIField<int>(this, 0x258) = remark;
    RHAIField<unsigned short>(this, 0x25c) = (unsigned short)flags;
    void *profile = m_actor->V178();
    if (profile)
    {
        if (remark >= 106)
        {
            if ((unsigned char)(RHAIField<unsigned>(m_actor, 4) & 31) == 20 && !m_actor->Vf8())
            {
                if (!(flags & 4))
                    // STRING: GAME 0x006a7a78
                    RHAI_REMARK_ERROR("AI error: Trying to play VIP remark [%s] for non-VIP soldier at (%u,%u)", 5885)
                else
                    // STRING: GAME 0x006a7a2c
                    RHAI_REMARK_ERROR("Script error: Trying to play VIP remark [%s] for non-VIP soldier at (%u,%u)", 5889)
                Unk00422b70(5, 5);
                Unk004195f0(flags);
                RHAIField<int>(this, 0x258) = 121;
                RHAIField<unsigned short>(this, 0x25c) = 0;
                return;
            }
            if ((unsigned char)(RHAIField<unsigned>(m_actor, 4) & 31) == 4 && !((RHArtificialIntelligenceActorCalls *)m_actor)->Unk00470ce0())
            {
                if (!(flags & 4))
                    // STRING: GAME 0x006a79e0
                    RHAI_REMARK_ERROR("AI error: Trying to play VIP remark [%s] for non-VIP civilian at (%u,%u)", 5901)
                else
                    // STRING: GAME 0x006a7990
                    RHAI_REMARK_ERROR("Script error: Trying to play VIP remark [%s] for non-VIP civilian at (%u,%u)", 5905)
                Unk00422b70(5, 6);
                Unk004195f0(flags);
                RHAIField<int>(this, 0x258) = 121;
                RHAIField<unsigned short>(this, 0x25c) = 0;
                return;
            }
            g_unk0x006c1070->Unk005a8b70(3, profile, remark - 106, variant, &position, m_actor);
        }
        else if (remark >= 78)
        {
            if ((unsigned char)(RHAIField<unsigned>(m_actor, 4) & 31) == 20)
            {
                if (!(flags & 4))
                    // STRING: GAME 0x006a7948
                    RHAI_REMARK_ERROR("AI error: Trying to play civilian remark [%s] for soldier at (%u,%u)", 5924)
                else
                    // STRING: GAME 0x006a78fc
                    RHAI_REMARK_ERROR("Script error: Trying to play civilian remark [%s] for soldier at (%u,%u)", 5928)
                Unk00422b70(5, 7);
                Unk004195f0(flags);
                RHAIField<int>(this, 0x258) = 121;
                RHAIField<unsigned short>(this, 0x25c) = 0;
                return;
            }
            if (((RHArtificialIntelligenceActorCalls *)m_actor)->Unk00470ce0())
            {
                Unk004195f0(flags);
                Unk00422b70(5, 8);
                RHAIField<int>(this, 0x258) = 121;
                RHAIField<unsigned short>(this, 0x25c) = 0;
                return;
            }
            g_unk0x006c1070->Unk005a8b70(2, profile, remark - 78, variant, &position, m_actor);
        }
        else
        {
            if ((unsigned char)(RHAIField<unsigned>(m_actor, 4) & 31) != 20)
            {
                if (!(flags & 4))
                    // STRING: GAME 0x006a78b4
                    RHAI_REMARK_ERROR("AI error: Trying to play soldier remark [%s] for civilian at (%u,%u)", 5956)
                else
                    // STRING: GAME 0x006a7868
                    RHAI_REMARK_ERROR("Script error: Trying to play soldier remark [%s] for civilian at (%u,%u)", 5960)
                Unk004195f0(flags);
                Unk00422b70(5, 9);
                RHAIField<int>(this, 0x258) = 121;
                RHAIField<unsigned short>(this, 0x25c) = 0;
                return;
            }
            if (m_actor->Vf8())
            {
                Unk00422b70(5, 10);
                Unk004195f0(flags);
                RHAIField<int>(this, 0x258) = 121;
                RHAIField<unsigned short>(this, 0x25c) = 0;
                return;
            }
            g_unk0x006c1070->Unk005a8b70(2, profile, remark, variant, &position, m_actor);
        }
    }
    RHArtificialIntelligenceRemarkEntry *entry = new RHArtificialIntelligenceRemarkEntry(flags);
    entry->m_command = 100;
    entry->m_remark = remark;
    const char *name = RHAIField<char *>(m_actor->m_data, 0x168);
    entry->m_name = name ? name : "";
    RHArtificialIntelligenceRemarkNode *head = g_unk0x006c0794;
    RHArtificialIntelligenceRemarkNode *previous = head->m_previous;
    RHArtificialIntelligenceRemarkNode *node = (RHArtificialIntelligenceRemarkNode *)::operator new(12);
    node->m_next = head ? head : node;
    node->m_previous = previous ? previous : node;
    head->m_previous = node;
    node->m_previous->m_next = node;
    node->m_entry = entry;
    ++g_unk0x006c0798;
    g_unk0x006c07a0 = 1;
    switch (remark)
    {
    case 29:
        Unk00419970(29, 10, 1);
        break;
    case 36:
        Unk00419970(36, 200, 1);
        Unk00419970(36, 1000, 8);
        break;
    case 78:
    case 79:
        Unk00419970(remark, 200, 6);
        break;
    case 12: case 13: case 14: case 15: case 16: case 17: case 18: case 19:
    case 20: case 21: case 22: case 23: case 24: case 30: case 31: case 54:
    case 61: case 62: case 63: case 64: case 66: case 67: case 68: case 69:
    case 70: case 71: case 72: case 73: case 74: case 75: case 77: case 84:
    case 85: case 102: case 103: case 104: case 105: case 106: case 113: case 114:
        break;
    default:
        if ((unsigned)remark <= 119)
            Unk00419970(remark, 200, 1);
        break;
    }
}

// FUNCTION: GAME 0x004195f0
void RHArtificialIntelligence::Unk004195f0(unsigned short flags)
{
    if ((flags & 0x100) > 0)
        ((RHScriptBatchCalls *)this)->Unk0040d980(59);
    else if ((flags & 0x200) > 0)
        ((RHScriptBatchCalls *)this)->Unk0040d980(60);
    else if ((flags & 0x400) > 0)
        ((RHScriptBatchCalls *)this)->Unk0040d980(61);
    else if ((flags & 0x1000) > 0)
        ((RHScriptBatchCalls *)this)->Unk0040d980(68);
}

extern unsigned *g_unk0x006c08a4;

static inline unsigned char RHAIActorKind(void *actor)
{
    return RHAIField<unsigned>(actor, 4) & 0x1f;
}

// Parked: narrowed actor loads and speech-field store scheduling differ.
// STUB: GAME 0x00419970
void RHArtificialIntelligence::Unk00419970(int remark, int time, int flags)
{
    if (flags & 0x1000)
        flags |= (unsigned char)(RHAIField<unsigned>(m_actor, 4) & 0x1f) == 0x14 ? 4 : 2;
    RHArtificialIntelligenceForbiddenRemark *speech = (RHArtificialIntelligenceForbiddenRemark *)operator new(sizeof(RHArtificialIntelligenceForbiddenRemark));
    speech->remark = remark;
    speech->soldier = (unsigned char)(RHAIField<unsigned>(m_actor, 4) & 0x1f) == 0x14;
    speech->flags = flags;
    speech->deadline = *g_unk0x006c08a4 + (unsigned short)time;
    speech->voice = m_actor->V178();
    speech->actorID = RHAIField<unsigned>(m_actor, 0x0c);
    RHArtificialIntelligenceNode *head = g_unk0x006c07b8.m_head;
    RHArtificialIntelligenceNode *previous = head->m_prev;
    RHArtificialIntelligenceNode *node = (RHArtificialIntelligenceNode *)operator new(sizeof(RHArtificialIntelligenceNode));
    node->m_next = head ? head : node;
    node->m_prev = previous ? previous : node;
    head->m_prev = node;
    node->m_prev->m_next = node;
    RHArtificialIntelligenceElement **destination = &node->m_data;
    if (destination)
        *destination = (RHArtificialIntelligenceElement *)speech;
    ++g_unk0x006c07b8.m_count;
    g_unk0x006c07b8.m_dirty = true;
}

// STUB: GAME 0x00419b20
bool RHArtificialIntelligence::Unk00419b20(int remark)
{
    unsigned short count = (unsigned short)g_unk0x006c07b8.m_count;
    for (unsigned short index = 0; index < count; ++index)
    {
        ((RHSeqList *)&g_unk0x006c07b8)->GoTo(index);
        RHArtificialIntelligenceForbiddenRemark *speech = (RHArtificialIntelligenceForbiddenRemark *)g_unk0x006c07b8.m_current.m_node->m_data;
        if (speech->deadline < *g_unk0x006c08a4)
        {
            ((RHSeqList *)&g_unk0x006c07b8)->GoTo(index);
            delete (RHArtificialIntelligenceForbiddenRemark *)g_unk0x006c07b8.m_current.m_node->m_data;
            RHArtificialIntelligenceNode *node = g_unk0x006c07b8.m_current.m_node;
            node->m_prev->m_next = node->m_next;
            node->m_next->m_prev = node->m_prev;
            operator delete(node);
            --g_unk0x006c07b8.m_count;
            g_unk0x006c07b8.m_dirty = true;
            --index;
            --count;
        }
        else if (speech->remark == remark)
        {
            RHArtificialIntelligence *self = this;
            if ((unsigned)(speech->flags & 1) > 0 &&
                (unsigned char)speech->soldier == (unsigned char)((unsigned char)RHAIActorKind(self->m_actor) == 0x14) &&
                speech->voice == self->m_actor->V178())
                return true;
            if ((unsigned)(speech->flags & 8) > 0 && speech->actorID == RHAIField<unsigned>(self->m_actor, 0xc))
                return true;
            if ((unsigned char)RHAIActorKind(self->m_actor) == 0x14)
            {
                if ((unsigned)(speech->flags & 4) > 0)
                    return true;
            }
            else if ((unsigned)(speech->flags & 2) > 0)
                return true;
        }
    }
    return false;
}

struct RHAIActorSelectionList : RHArtificialIntelligenceList
{
    bool searched;
    int found;
    RHArtificialIntelligenceElement *value;
};

#include "RHUnk00419a40.h"

// Parked: cached-search dispatch retains a constant register and an extra spill.
// STUB: GAME 0x00419a40
void RHUnk00419a40::Unk(int remark, bool enabled)
{
    RHAIActorSelectionList &list = RHAIField<RHAIActorSelectionList>(this, 0x230);
    list.value = (RHArtificialIntelligenceElement *)remark;
    list.searched = true;
    list.m_current.m_node = list.m_head->m_next;
    int index = 0;
    int count = list.m_count;
    for (; index < count; ++index, ++list.m_current)
        if (list.m_current.m_node->m_data == list.value)
            break;
    if (index < count)
    {
        list.found = index;
        list.m_dirty = false;
        list.m_index = index;
    }
    else
    {
        list.m_dirty = true;
        list.found = -1;
    }
    if (enabled)
    {
        if (list.found == -1)
            list.InsertLast((void *)remark);
    }
    else if (list.found != -1)
    {
        ((RHSeqList *)&list)->GoTo(list.found);
        RHArtificialIntelligenceNode *node = list.m_current.m_node;
        node->m_prev->m_next = node->m_next;
        node->m_next->m_prev = node->m_prev;
        operator delete(node);
        --list.m_count;
        list.m_dirty = true;
    }
}

class RHAIUnk00550660
{
public:
    int Unk00550660(int value);
};

// Parked: command-decoder frame and register scheduling.
// STUB: GAME 0x00419cc0
bool RHArtificialIntelligence::Unk00419cc0()
{
    char *actor = (char *)m_actor;
    RHArtificialIntelligencePathCursor *cursor = (RHArtificialIntelligencePathCursor *)(actor + RHAIField<int>(RHAIField<void *>(actor, 0x49c), 4) + 0x4cc);
    void *path = RHAIField<void *>(cursor, 4);
    if (!path || !RHAIField<void **>(path, 4) || (unsigned short)(RHAIField<void **>(path, 8) - RHAIField<void **>(path, 4)) == 0)
        return true;
    void *waypoint = RHAIField<void **>(path, 4)[RHAIField<unsigned char>(cursor, 0)];
    if (RHAIField<unsigned short>(waypoint, 0x70) == 0)
        return false;
    if (RHAIField<char>(waypoint, 0x6e))
        return true;
    unsigned char *base = RHAIField<unsigned char *>(waypoint, 0x74);
    unsigned char *stream = base;
    unsigned short alternatives = *(unsigned short *)stream;
    stream += 2;
    int condition = *stream++;
    unsigned offset;
    if (((RHAIUnk00550660 *)cursor)->Unk00550660(condition))
        offset = *(unsigned short *)stream;
    else
    {
        stream += 2;
        if (alternatives != 2 || !((RHAIUnk00550660 *)cursor)->Unk00550660(*stream))
            return false;
        offset = *(unsigned short *)(stream + 1);
    }
    stream = base + offset;
    unsigned short count = *(unsigned short *)stream;
    stream += 2;
    unsigned char choice = Unk00419c80();
    unsigned short index = 0;
    while (choice > *stream)
    {
        choice -= *stream;
        stream += 3;
        if (++index == count)
            return false;
    }
    stream = base + *(unsigned short *)(stream + 1);
    count = *(unsigned short *)stream;
    stream += 2;
    while (count > 0)
    {
        switch (*stream)
        {
        case 3: case 4: case 5: case 6: case 7: case 11: case 12: case 13:
            return true;
        case 9: case 10: case 14: case 16:
            --count;
            ++stream;
            break;
        case 15:
            count -= 3;
            stream += 3;
            break;
        case 0: case 1: case 2: case 8:
        default:
            return false;
        }
    }
    return false;
}

// FUNCTION: GAME 0x00419fb0
void RHScriptBatchCalls::Unk00419fb0(int value)
{
    RHAIField<char>(this, 0x268) = 0;
    RHAIField<int>(this, 0x260) = value;
}

extern "C" int __cdecl rand();

// Parked: inlined profile-test shape and register scheduling.
// STUB: GAME 0x0041a420
unsigned short RHArtificialIntelligence::Unk0041a420()
{
    unsigned type = RHAIField<unsigned>(m_actor, 4) & 31;
    if (type == 20 && RHAIField<int>(RHAIField<void *>(m_actor, 0xa1c), 0x58) == 1)
        return rand() % 600 + 200;
    if (type == 20 && RHAIField<unsigned short>(RHAIField<void *>(m_actor, 0xa1c), 0x38) > 0)
        return rand() % 800 + 400;
    return rand() % 70 + 70;
}

#include "RHMalignityActorCalls.h"

#include "RHAIStateCalls.h"

// Parked: complete panic procedure; temporary layout and EH scheduling remain unmatched.
// STUB: GAME 0x004132d0
void RHArtificialIntelligence::FUN_004132d0(int first, int mode, int second)
{
    RHAIField<unsigned char>(this, 0xfd) = (unsigned char)mode;
    bool start = RHAIField<int>(this, 0x14) != 0xe0 && RHAIField<int>(this, 0x14) != 0xdd;
    void *destination;
    if ((unsigned char)mode)
    {
        destination = FUN_00417ed0(&RHAIField<SBGeoPoint2D>(this, 0xf4), false);
        if (!destination)
        {
            destination = FUN_00417ed0(0, false);
            RHAIField<unsigned char>(this, 0xfd) = 0;
        }
    }
    else
        destination = FUN_00417ed0(0, false);
    Unk00410600();
    ((RHScriptBatchCalls *)this)->Unk00419fb0(3);
    if (destination)
    {
        if ((RHAIField<unsigned>(m_actor, 4) & 0x1f) == 4)
            Unk00418c40(0x53, 0);
        V10(6, 0xdd);
        ((RHUnk00413640 *)this)->Unk(second, 0);
        RHAIField<unsigned char>(this, 0xfc) = 0;
        {
            RHUnk00571160Position position;
            position.x = RHAIField<float>(destination, 0x20);
            position.y = RHAIField<float>(destination, 0x24);
            position.area = RHAIField<void *>(destination, 0x10);
            position.layer = RHAIField<unsigned short>(destination, 0x16);
            RHUnk00571160Position next = position;
            Unk00412240(next, 1, 1.0f);
        }
        if (RHAIField<unsigned char>(this, 0x16c) != 1)
            return;
        RHAIField<unsigned char>(this, 0x16c) = 0;
        if (RHAIField<unsigned char>(this, 0xfd))
        {
            destination = FUN_00417ed0(0, false);
            RHAIField<unsigned char>(this, 0xfd) = 0;
            RHUnk00571160Position position;
            position.x = RHAIField<float>(destination, 0x20);
            position.y = RHAIField<float>(destination, 0x24);
            position.area = RHAIField<void *>(destination, 0x10);
            position.layer = RHAIField<unsigned short>(destination, 0x16);
            RHUnk00571160Position next = position;
            Unk00412240(next, 1, 1.0f);
            if (RHAIField<unsigned char>(this, 0x16c) != 1)
                return;
            RHAIField<unsigned char>(this, 0x16c) = 0;
        }
    }
    RHMalignityPosition own = FUN_004165e0(m_actor, true);
    if ((unsigned char)mode)
        start |= ((RHMalignityActorCalls *)m_actor)->FUN_004135b0().FUN_005fc660(
            FUN_0040ec20(RHAIField<RHMalignityPosition>(this, 0xf4), own)) > 0.0f;
    if (start)
    {
        V10(6, 0xe0);
        Unk00418c40((RHAIField<unsigned>(m_actor, 4) & 0x1f) == 4 ? 0x53 : 0x2e, 0);
        ((RHUnk00413640 *)this)->Unk(second, 0);
        RHAIField<unsigned char>(this, 0xfc) = (unsigned char)((unsigned char)first + 1);
        RHStimulus stimulus;
        stimulus.Unk004188d0(3);
        ((RHArtificialIntelligenceDispatchView *)this)->V24(&stimulus);
    }
    else if (RHAIField<unsigned char>(this, 0xfc) < (unsigned char)first)
        RHAIField<unsigned char>(this, 0xfc) = (unsigned char)first;
}

// Parked: receiver and scan-index registers are exchanged throughout the body.
// STUB: GAME 0x00418bc0
void RHScriptBatchCalls::Unk00418bc0()
{
    RHArtificialIntelligence *ai = (RHArtificialIntelligence *)this;
    ((RHMalignityActorCalls *)ai->m_actor)->FUN_0048e420(0);
    unsigned index = 0;
    unsigned count = RHAIField<unsigned>(this, 0x180);
    bool found = false;
    if ((unsigned short)count > 0)
    {
        RHArtificialIntelligenceValueList<RHStimulus> &stimuli = RHAIField<RHArtificialIntelligenceValueList<RHStimulus> >(this, 0x178);
        for (; (unsigned short)index < (unsigned short)count; ++index)
        {
            if (stimuli[(unsigned short)index].m_20 == 20)
            {
                found = true;
                break;
            }
        }
    }
    void *pending = RHAIField<void *>(this, 0xc);
    RHAIField<char>(this, 0x1c4) = 0;
    if (pending && !found && !RHAIField<char>(ai->m_actor, 0x1ce))
        Unk0040d980(21);
}

// Parked: null-count tail merging and the bonus-flag boolean materialization differ.
// STUB: GAME 0x0041a490
void RHArtificialIntelligence::FUN_0041a490()
{
    unsigned short count = (unsigned short)RHAIField<RHArtificialIntelligenceStaticArray>(g_pEngine, 0x48d8).size();
    if (count > 0)
    {
        int offset = 0;
        unsigned remaining = (unsigned short)count;
        do
        {
            void *object = RHAIField<void *>(RHAIField<void *>(g_pEngine, 0x48dc), offset);
            if ((RHAIField<unsigned>(object, 4) & 3) == 3 && RHAIField<char>(object, 0x12) &&
                (RHAIField<int>(object, 0xb0) == 3 ||
                 RHAIField<int>(object, 0xb0) == 8 && !RHAIField<bool>(this, 0x2ac)))
            {
                if (!((RHMalignityActorCalls *)m_actor)->FUN_0048c8e0(object, 2))
                    ((RHMalignityActorCalls *)m_actor)->FUN_0048c700(object, 2);
            }
            offset += 4;
        } while (--remaining);
    }
}

void EmitRHAIFresh603(RHArtificialIntelligence *value)
{
    value->FUN_004121a0();
    ((RHScriptBatchCalls *)value)->Unk00418bc0();
    value->FUN_0041a490();
}

struct RHUnk0041a930Value
{
    int m_00;
    int m_04;
    int m_08;
    int m_0c;
};

class RHUnk0041a930
{
public:
    int m_00;
    int m_04;
    int m_08;
    int m_0c;
    char m_10[0xc];
    int m_1c;
    int m_20;
    RHUnk0041a930 *FUN_0041a930(int first, const RHUnk0041a930Value *second);
};

// Parked: register colouring seam; VC6 keeps `this` in eax (return) where the target keeps arg1 in eax.
// STUB: GAME 0x0041a930
RHUnk0041a930 *RHUnk0041a930::FUN_0041a930(int first, const RHUnk0041a930Value *second)
{
    m_20 = first;
    *(RHUnk0041a930Value *)((char *)this) = *second;
    m_1c = 2;
    return this;
}

void EmitRHUnk0041a930(RHUnk0041a930 *a)
{
    RHUnk0041a930Value value = {0, 0, 0, 0};
    a->FUN_0041a930(0, &value);
}

// Parked: cached-list cursor and loop-counter scheduling.
// STUB: GAME 0x0041a960
void RHArtificialIntelligence::Unk0041a960(unsigned short direction)
{
    RHArtificialIntelligenceList &list = RHAIField<RHArtificialIntelligenceList>(this, 0x2b4);
    unsigned short size = (unsigned short)list.m_count;
    if (size > 0)
    {
        unsigned count = size;
        int index = 0;
        do
        {
            list.GoTo(index);
            char *actor = (char *)list.m_current.m_node->m_data;
            RHArtificialIntelligence *ai = (RHArtificialIntelligence *)(actor + RHAIField<int>(RHAIField<void *>(actor, 0x49c), 4) + 0x49c);
            ai->Unk0041ab10(direction);
            ++index;
        } while (--count);
    }
}

class RHUnk00613e90;
void FUN_0059fb20(RHUnk00613e90 *, const RHUnk00613e90 &);

struct RHArtificialIntelligenceHistoryEntry
{
    int m_property;
    unsigned short m_value;
    unsigned m_time;
};

struct RHArtificialIntelligenceHistoryNode
{
    RHArtificialIntelligenceHistoryNode *m_next;
    RHArtificialIntelligenceHistoryNode *m_prev;
    RHArtificialIntelligenceHistoryEntry m_data;
};

struct RHArtificialIntelligenceHistory
{
    int m_allocator;
    RHArtificialIntelligenceHistoryNode *m_head;
    int m_count;
    RHArtificialIntelligenceHistoryNode *m_current;
    bool m_dirty;

    void InsertLast(const RHArtificialIntelligenceHistoryEntry &value)
    {
        RHArtificialIntelligenceHistoryNode *head = m_head;
        RHArtificialIntelligenceHistoryNode *previous = head->m_prev;
        RHArtificialIntelligenceHistoryNode *node = (RHArtificialIntelligenceHistoryNode *)::operator new(0x14);
        node->m_next = head ? head : node;
        node->m_prev = previous ? previous : node;
        head->m_prev = node;
        node->m_prev->m_next = node;
        FUN_0059fb20((RHUnk00613e90 *)&node->m_data, (const RHUnk00613e90 &)value);
        ++m_count;
        m_dirty = true;
    }
    void RemoveFirst()
    {
        RHArtificialIntelligenceHistoryNode *first = m_head->m_next;
        first->m_prev->m_next = first->m_next;
        first->m_next->m_prev = first->m_prev;
        ::operator delete(first);
        --m_count;
        m_dirty = true;
    }
};

// Parked: effective; incremented count lands in EDX instead of ECX.
// STUB: GAME 0x00422b70
void RHArtificialIntelligence::Unk00422b70(int property, int value)
{
    RHArtificialIntelligenceHistory &history = RHAIField<RHArtificialIntelligenceHistory>(this, 0x34c);
    RHArtificialIntelligenceHistoryEntry entry;
    entry.m_property = property;
    RHArtificialIntelligenceHistoryNode *head = history.m_head;
    entry.m_value = (unsigned short)value;
    entry.m_time = *(unsigned *)((char *)g_pEngine + 0x4a94);
    RHArtificialIntelligenceHistoryNode *previous = head->m_prev;
    RHArtificialIntelligenceHistoryNode *node = (RHArtificialIntelligenceHistoryNode *)::operator new(0x14);
    node->m_next = head ? head : node;
    node->m_prev = previous ? previous : node;
    head->m_prev = node;
    node->m_prev->m_next = node;
    FUN_0059fb20((RHUnk00613e90 *)&node->m_data, (const RHUnk00613e90 &)entry);
    ++history.m_count;
    history.m_dirty = true;
    if (history.m_count > 26)
        history.RemoveFirst();
}

// FUNCTION: GAME 0x00424340
RHArtificialIntelligenceStimulusNode *RHArtificialIntelligenceStimulusList::Unk00424340(RHArtificialIntelligenceStimulusNode *next, RHArtificialIntelligenceStimulusNode *previous)
{
    RHArtificialIntelligenceStimulusNode *node = (RHArtificialIntelligenceStimulusNode *)::operator new(0x34);
    node->m_next = next ? next : node;
    node->m_previous = previous ? previous : node;
    return node;
}

// FUNCTION: GAME 0x00424370
RHArtificialIntelligenceIterator RHArtificialIntelligenceTripleList::insert(RHArtificialIntelligenceIterator position, const RHArtificialIntelligenceTriple &value)
{
    RHArtificialIntelligenceNode *head = position.m_node;
    RHArtificialIntelligenceNode *previous = head->m_prev;
    RHArtificialIntelligenceNode *node = (RHArtificialIntelligenceNode *)::operator new(20);
    node->m_next = head ? head : node;
    node->m_prev = previous ? previous : node;
    head->m_prev = node;
    node->m_prev->m_next = node;
    RHArtificialIntelligenceTriple *destination = (RHArtificialIntelligenceTriple *)((char *)node + 8);
    if (destination)
        *destination = value;
    ++RHAIField<unsigned>(this, 8);
    return RHArtificialIntelligenceIterator(node);
}

// FUNCTION: GAME 0x00424470
void FUN_00424470(RHStimulus *destination, const RHStimulus *source)
{
    if (destination)
        *destination = *source;
}

// deferred: unannotated pending reccmp #534
class RHUnk0044e640
{
public:
    void FUN_0044e640();
    char m_00[4];
    RHArtificialIntelligenceNode *m_head;
    int m_count;
    char m_0c[4];
    bool m_dirty;
};

// Parked: payload load uses ECX/EAX instead of EAX/ECX after two shapes.
// STUB: GAME 0x0044e640
void RHUnk0044e640::FUN_0044e640()
{
    void *value = m_head->m_next->m_data;
    if (value)
        operator delete(value);
    RHArtificialIntelligenceNode *node = m_head->m_next;
    node->m_prev->m_next = node->m_next;
    node->m_next->m_prev = node->m_prev;
    operator delete(node);
    --m_count;
    m_dirty = true;
}

// Parked (rule-28 deferral): the body matches the shared original 0x44e8b0, but
// binding it as one canonical view regresses every caller that binds a different
// view class (RHTitbitList::Clear, RHAIUnk0044e8b0 with another iterator type,
// RHUnk004b1520List::FUN_0044e8b0, RHShadowUnk0044e8b0...).
RHArtificialIntelligenceIterator RHAIUnk0044e8b0::FUN_0044e8b0(RHArtificialIntelligenceIterator first, RHArtificialIntelligenceIterator last)
{
    while (first.m_node != last.m_node)
    {
        RHArtificialIntelligenceNode *node = first.m_node;
        first.m_node = first.m_node->m_next;
        node->m_prev->m_next = node->m_next;
        node->m_next->m_prev = node->m_prev;
        ::operator delete(node);
        --m_count;
    }
    return first;
}

struct RHUnk0042c750Value
{
    int m_00;
    int m_04;
    int m_08;
    int m_0c;
};

class RHUnk0042c730
{
public:
    unsigned short FUN_0042c730();
};

class RHUnk0042c750
{
public:
    void FUN_0042c750(int level, const RHUnk0042c750Value *value);
};

struct RHUnk0042c730Vector
{
    int m_0;
    int *m_first;
    int *m_last;

    unsigned size() const { return m_first == 0 ? 0 : m_last - m_first; }
};

// FUNCTION: GAME 0x0042c730
unsigned short RHUnk0042c730::FUN_0042c730()
{
    RHUnk0042c730Vector *outer = *(RHUnk0042c730Vector **)((char *)this + 4);
    if (!outer)
        return 0;
    return outer->size();
}

// FUNCTION: GAME 0x0042c750
void RHUnk0042c750::FUN_0042c750(int level, const RHUnk0042c750Value *value)
{
    if (*(int *)((char *)this + 0x10) <= level)
    {
        *(int *)((char *)this + 0x10) = level;
        *(RHUnk0042c750Value *)((char *)this) = *value;
    }
}

class RHUnk0042c780
{
public:
    RHUnk0042c780 *FUN_0042c780();
    void FUN_0042c790(int first, int second);
    void FUN_0042c7b0(int first, int *second);
};

class RHUnk0042c960
{
public:
    int FUN_0042c960();
};

// FUNCTION: GAME 0x0042c780
RHUnk0042c780 *RHUnk0042c780::FUN_0042c780()
{
    int zero = 0;
    *(int *)((char *)this + 0x1c) = zero;
    *(int *)((char *)this + 0x24) = zero;
    *(char *)((char *)this + 0x28) = (char)zero;
    return this;
}

// FUNCTION: GAME 0x0042c790
void RHUnk0042c780::FUN_0042c790(int first, int second)
{
    *(int *)((char *)this + 0x20) = first;
    *(int *)this = second;
    *(int *)((char *)this + 0x1c) = 3;
}

// FUNCTION: GAME 0x0042c7b0
void RHUnk0042c780::FUN_0042c7b0(int first, int *second)
{
    *(int *)((char *)this + 0x20) = first;
    *(int *)this = second[0];
    *(int *)((char *)this + 4) = second[1];
    *(int *)((char *)this + 0x1c) = 6;
}

// FUNCTION: GAME 0x0042c960
int RHUnk0042c960::FUN_0042c960()
{
    void *value = *(void **)((char *)this + 0x134);
    if (!value)
        return 0x11b;
    return *(int *)((char *)value + 0x24);
}

void EmitRHUnk0042c780(RHUnk0042c780 *a, RHUnk0042c960 *b)
{
    a->FUN_0042c780();
    a->FUN_0042c790(0, 0);
    a->FUN_0042c7b0(0, 0);
    b->FUN_0042c960();
}

// FUNCTION: GAME 0x00486f60
void RHArtificialIntelligence::Unk00486f60()
{
    RHAIField<char>(this, 0x65d) = 0;
    RHAIField<char>(this, 0x65c) = 0;
}

extern unsigned *g_unk0x006c08a4;

struct RHAIActorTimerView
{
    char m_00[0x4b0];
    unsigned m_4b0;
    char m_4b4[4];
    unsigned m_4b8;
    unsigned Field4b0() { return m_4b0; }
    void Field4b8(unsigned value) { m_4b8 = value; }
};

inline RHAIActorTimerView &RHArtificialIntelligenceActorCalls::TimerView()
{
    return *(RHAIActorTimerView *)((char *)this + RHAIField<int>(RHAIField<void *>(this, 0x49c), 4));
}

// FUNCTION: GAME 0x0048b450
void RHArtificialIntelligenceActorCalls::Unk0048b450(unsigned value, int mode)
{
    if ((unsigned char)mode)
    {
        unsigned time = *g_unk0x006c08a4 + value;
        RHAIField<unsigned>((char *)this + RHAIField<int>(RHAIField<void *>(this, 0x49c), 4), 0x540) = time;
        RHAIField<char>((char *)this + RHAIField<int>(RHAIField<void *>(this, 0x49c), 4), 0x53c) = 1;
    }
    else
    {
        TimerView().Field4b8(TimerView().Field4b0());
        unsigned time = *g_unk0x006c08a4 + value;
        RHAIField<unsigned>((char *)this + RHAIField<int>(RHAIField<void *>(this, 0x49c), 4), 0x538) = time;
        RHAIField<char>((char *)this + RHAIField<int>(RHAIField<void *>(this, 0x49c), 4), 0x534) = 1;
    }
}

// FUNCTION: GAME 0x0048b4e0
void RHArtificialIntelligenceActorCalls::Unk0048b4e0(int mode)
{
    if ((unsigned char)mode)
        RHAIField<char>((char *)this + RHAIField<int>(RHAIField<void *>(this, 0x49c), 4), 0x53c) = 0;
    else
        RHAIField<char>((char *)this + RHAIField<int>(RHAIField<void *>(this, 0x49c), 4), 0x534) = 0;
}

// FUNCTION: GAME 0x005505b0
void RHArtificialIntelligencePathCursor::Unk005505b0(unsigned short waypoint)
{
    RHAIField<unsigned char>(this, 1) = RHAIField<unsigned char>(this, 0);
    RHAIField<unsigned char>(this, 0) = (unsigned char)waypoint;
}

// Parked: repeated array-size tests and register scheduling.
// STUB: GAME 0x005505c0
RHArtificialIntelligencePathCursor &RHArtificialIntelligencePathCursor::Unk005505c0()
{
    RHAIPathArray *path = m_path;
    m_previous = m_current;
    if (path && path->m_first && (unsigned short)(path->m_last - path->m_first) > 1)
    {
        if (m_forward)
        {
            if (m_current < (unsigned short)path->size() - 1)
                ++m_current;
            else
            {
                --m_current;
                m_forward = 0;
            }
        }
        else if (m_current > 0)
            --m_current;
        else
        {
            m_forward = 1;
            ++m_current;
        }
    }
    return *this;
}

// FUNCTION: GAME 0x00550640
RHArtificialIntelligencePathCursor &RHArtificialIntelligencePathCursor::Unk00550640()
{
    m_forward = m_forward ^ 1;
    Unk005505c0();
    m_forward = m_forward ^ 1;
    return *this;
}

// FUNCTION: GAME 0x00550f60
void RHArtificialIntelligencePathCursor::Unk00550f60(unsigned short path)
{
    RHAIField<unsigned short>(this, 8) = path;
    if (path == 0xffff)
        RHAIField<void *>(this, 4) = 0;
    else
    {
        RHAIField<unsigned char>(this, 0) = 0;
        RHAIField<unsigned char>(this, 2) = 1;
        RHAIField<void *>(this, 4) = RHAIField<void **>(g_unk0x6c0b9c, 8)[path];
    }
}

struct RHScriptNode
{
    RHScriptNode *next;
    RHScriptNode *previous;
    void *value;
};

// FUNCTION: GAME 0x0059f720
RHScriptNode *RHUnk0046eb30::Unk0059f720(RHScriptNode *next, RHScriptNode *previous)
{
    RHScriptNode *node = (RHScriptNode *)::operator new(12);
    node->next = next ? next : node;
    node->previous = previous ? previous : node;
    return node;
}

// deferred: unannotated pending reccmp #534
void RHSeqList::CopyData(RHSequenceElement **destination, RHSequenceElement *const *source)
{
    if (destination)
        *destination = *source;
}

// GLOBAL: GAME 0x0067a7a0
const unsigned g_unk0x0067a7a0[16] = {
    0x00000000, 0x3ec3ef15, 0x3f3504f3, 0x3f6c835e,
    0x3f800000, 0x3f6c835e, 0x3f3504f3, 0x3ec3ef15,
    0x00000000, 0xbec3ef15, 0xbf3504f3, 0xbf6c835e,
    0xbf800000, 0xbf6c835e, 0xbf3504f3, 0xbec3ef15
};

// GLOBAL: GAME 0x0067a7e0
const unsigned g_unk0x0067a7e0[16] = {
    0xbf800000, 0xbf6c835e, 0xbf3504f3, 0xbec3ef15,
    0x00000000, 0x3ec3ef15, 0x3f3504f3, 0x3f6c835e,
    0x3f800000, 0x3f6c835e, 0x3f3504f3, 0x3ec3ef15,
    0x00000000, 0xbec3ef15, 0xbf3504f3, 0xbf6c835e
};

// FUNCTION: GAME 0x005fcd40
RHUnk005fc3b0 &RHUnk005fc3b0::Unk005fcd40(unsigned char direction, float length)
{
    unsigned offset = (direction & 15) * 4;
    m_x = *(const float *)((const char *)g_unk0x0067a7a0 + offset);
    m_y = length * *(const float *)((const char *)g_unk0x0067a7e0 + offset);
    return *this;
}

void RHArtificialIntelligence::Emit(SBFile &file, RHArtificialIntelligencePosition &position)
{
    ((RHUnk00419a40 *)this)->Unk(0, false);
    FUN_00417ed0(0, false);
    FUN_00417580();
    SerializePosition(position, file);
    ((RHStimulus *)this)->Serialize(file);
    InitState();
    SerializeAllAI(file);
    RHArtificialIntelligenceList list;
    SerializeListOfPointersToHumans(list, file);
    SerializeListOfPointersToActorsNPC(list, file);
    SerializeListOfPointersToObjects(list, file);
    Unk00418600(0);
    Unk00410010(false);
    Unk00418c40(0, 0);
    Unk00414be0(file);
    Unk00486f60();
    ((RHAIUnk0044e8b0 *)this)->FUN_0044e8b0(RHArtificialIntelligenceIterator(0), RHArtificialIntelligenceIterator(0));
}
