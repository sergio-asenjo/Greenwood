#include "SBNullstr.h"
#include "RHElementActorNPC_calls.h"
#include "RHMalignityActorCalls.h"
#include "RHMalignityOwnerCalls.h"
#include "RHElementActorHumanCore.h"

#define RHNPC_ACCESS(buffer, size, line) \
    if (file.Access(buffer, size) < 0) \
    { \
        SBString *error = file.GetError(); \
        SBAssert(0, "P:\\Robin Hood\\RHelementactornpc.cpp", line, "Serialize failed reason is %s", error->m_chars ? error->m_chars : ""); \
        return false; \
    }

#define RHNPC_CHECK(expression, line) \
    if (!(expression)) \
    { \
        SBAssert(1, "P:\\Robin Hood\\RHelementactornpc.cpp", line, "Serialization failed"); \
        return false; \
    }

// FUNCTION: GAME 0x00486260
bool RHDetectable::Serialize(SBFile &file)
{
    RHSerializeName(file,
                    // STRING: GAME 0x006ae5bc
                    "RHDetectable");
    RHNPC_ACCESS(&m_04, 4, 144);
    RHNPC_ACCESS(&m_08, 1, 145);
    RHNPC_ACCESS(&m_0a, 1, 146);
    RHNPC_ACCESS(&m_0c, 1, 147);
    RHNPC_ACCESS(&m_09, 1, 148);
    RHNPC_ACCESS(&m_10, 4, 149);
    if (!FUN_00416b30(m_00, file))
    {
        SBAssert(1,
                 // STRING: GAME 0x006ae598
                 "P:\\Robin Hood\\RHelementactornpc.cpp", 150, "Serialization failed");
        return false;
    }
    return true;
}

#define RHNPC_FIELD(type, offset) (*(type *)((char *)this + (offset)))

struct RHNPCCachedCursor
{
    RHScriptNode *node;
    RHNPCCachedCursor(RHScriptNode *value) : node(value) {}
    RHNPCCachedCursor &operator=(const RHNPCCachedCursor &other)
    {
        node = other.node;
        return *this;
    }
};

struct RHNPCCachedList
{
    int allocator;
    RHScriptNode *head;
    int size;
    RHNPCCachedCursor current;
    bool valid;
    int index;
    RHNPCCachedCursor Begin()
    {
        return RHNPCCachedCursor(*(RHScriptNode *volatile *)&head->next);
    }
    RHNPCCachedCursor End()
    {
        return RHNPCCachedCursor(*(RHScriptNode *volatile *)&head);
    }
    RHDetectable &Get(int wanted)
    {
        int count = size;
        if (valid)
        {
            if (wanted <= (count + 1) / 2)
            {
                current = Begin();
                std::bidirectional_iterator_tag category;
                FUN_005c9010((RHUnk005c9010Iterator &)current, wanted, category);
            }
            else
            {
                current = End();
                std::bidirectional_iterator_tag category;
                FUN_005c9010((RHUnk005c9010Iterator &)current, wanted - count, category);
            }
            valid = false;
            index = wanted;
        }
        else
        {
            int previous = index;
            if (wanted != previous)
            {
                if (wanted < previous)
                {
                    if (wanted < (previous + 1) / 2)
                    {
                        current = RHNPCCachedCursor(((RHUnk0046eb30 *)this)->FUN_0046eb80().node);
                        std::bidirectional_iterator_tag category;
                        FUN_005c9010((RHUnk005c9010Iterator &)current, wanted, category);
                    }
                    else
                    {
                        std::bidirectional_iterator_tag category;
                        FUN_005c9010((RHUnk005c9010Iterator &)current, wanted - previous, category);
                    }
                }
                else if (wanted < (previous + count) / 2)
                {
                    std::bidirectional_iterator_tag category;
                    FUN_005c9010((RHUnk005c9010Iterator &)current, wanted - previous, category);
                }
                else
                {
                    current = End();
                    std::bidirectional_iterator_tag category;
                    FUN_005c9010((RHUnk005c9010Iterator &)current, wanted - count, category);
                }
                index = wanted;
            }
        }
        return *(RHDetectable *)&current.node->data;
    }
};

extern unsigned *g_unk0x006c08a4;

// FUNCTION: GAME 0x00486790
int RHElementActorNPC::FUN_00486790()
{
    return 0;
}

// FUNCTION: GAME 0x004867d0
RHNPCUnk004867d0::~RHNPCUnk004867d0()
{
}

// GLOBAL: GAME 0x006c087c
unsigned char g_unk0x006c087c = 0;
// GLOBAL: GAME 0x006c087d
unsigned char g_unk0x006c087d = 0;
// GLOBAL: GAME 0x006c0880
unsigned char g_unk0x006c0880 = 0;
// GLOBAL: GAME 0x006c0881
unsigned char g_unk0x006c0881 = 0;
// GLOBAL: GAME 0x006c08a8
unsigned char g_unk0x006c08a8 = 0;
// GLOBAL: GAME 0x006c08a9
unsigned char g_unk0x006c08a9 = 0;
// GLOBAL: GAME 0x006c08ac
unsigned char g_unk0x006c08ac[32] = {0};
// GLOBAL: GAME 0x006c08cc
unsigned char g_unk0x006c08cc[32] = {0};
// GLOBAL: GAME 0x006c0884
unsigned char g_unk0x006c0884[32] = {0};
// GLOBAL: GAME 0x00677d7c
float g_unk0x00677d7c = 1.0f / 36.0f;
extern float g_unk0x0067749c;

inline void RHNPCColorChannels(unsigned long color, unsigned char &red, unsigned char &green, unsigned char &blue)
{
    red = color;
    green = color >> 8;
    blue = color >> 16;
}

// Parked: byte-local storage, channel conversion order and x87 lifetimes differ.
// STUB: GAME 0x00486940
void RHElementActorNPC::FUN_00486940(unsigned long first, unsigned long second, unsigned long third)
{
    unsigned char red = first;
    unsigned char green = first >> 8;
    unsigned char blue = first >> 16;
    RHNPCColorChannels(second, g_unk0x006c0881, g_unk0x006c087d, g_unk0x006c08a8);
    RHNPCColorChannels(third, g_unk0x006c0880, g_unk0x006c087c, g_unk0x006c08a9);
    float redStart = red;
    float redEnd = g_unk0x006c0881;
    float greenStart = green;
    float greenEnd = g_unk0x006c087d;
    float blueStart = blue;
    float blueEnd = g_unk0x006c08a8;
    int i = 0;
    int count = 32;
    do {
        g_unk0x006c08ac[i] = redStart * (g_unk0x0067749c - i * g_unk0x00677d7c) + redEnd * (i * g_unk0x00677d7c);
        g_unk0x006c08cc[i] = greenStart * (g_unk0x0067749c - i * g_unk0x00677d7c) + greenEnd * (i * g_unk0x00677d7c);
        g_unk0x006c0884[i] = blueStart * (g_unk0x0067749c - i * g_unk0x00677d7c) + blueEnd * (i * g_unk0x00677d7c);
        ++i;
    } while (--count);
}

// FUNCTION: GAME 0x00486f30
void RHElementActorNPC::FUN_00486f30(unsigned char status)
{
    RHNPC_FIELD(unsigned char, 0x65d) = RHNPC_FIELD(unsigned char, 0x65c) != status;
    RHNPC_FIELD(unsigned char, 0x65c) = status;
}

// FUNCTION: GAME 0x00486f70
void RHElementActorNPC::FUN_00486f70()
{
    RHNPC_FIELD(unsigned char, 0x65d) = 1;
    RHNPC_FIELD(unsigned short, 0x6c2) = 5;
    RHNPC_FIELD(unsigned short, 0x6c0) = *(unsigned short *)((char *)g_pEngine + 0x4cc0);
    RHNPC_FIELD(unsigned char, 0x65c) = 8;
}

// FUNCTION: GAME 0x00487aa0
void RHElementActorNPC::FUN_00487aa0(void *target)
{
    if (target)
    {
        RHNPC_FIELD(void *, 0x6bc) = target;
        RHNPC_FIELD(unsigned char, 0x65c) = 6;
        RHNPC_FIELD(float, 0x660) = 1.3f;
    }
    else
        FUN_00487b70();
}

RHUnk00613e90 FUN_00414360(const RHMalignityPosition &position, bool mode);

struct RHNPCProjectionCopy
{
    RHNPCProjectionCopy(const RHUnk00613e90 &value)
        : x(value.m_0), y(value.m_4), z(value.m_8) {}
    float x;
    float y;
    float z;
};

// Parked: projection return-buffer and scalar-copy stack slots differ.
// STUB: GAME 0x00487ad0
void RHElementActorNPC::FUN_00487ad0(const RHMalignityPosition &position)
{
    RHNPCProjectionCopy projected(FUN_00414360(position, false));
    SBGeoPoint2D point(projected.x, projected.y);
    RHNPC_FIELD(SBGeoPoint2D, 0x6b4) = point;
    RHNPC_FIELD(unsigned char, 0x65c) = 7;
    RHNPC_FIELD(float, 0x660) = 1.3f;
}

// FUNCTION: GAME 0x00487b70
void RHElementActorNPC::FUN_00487b70()
{
    RHNPC_FIELD(unsigned char, 0x65c) = 1;
    RHNPC_FIELD(float, 0x660) = 0.8f;
}

// FUNCTION: GAME 0x00487ce0
void RHElementActorNPC::FUN_00487ce0()
{
    RHNPC_FIELD(RHUnk005b5ed0 *, 0x50)->FUN_005bd8b0();
    RHNPC_FIELD(unsigned char, 0x08) = 0;
}

// Parked: VC6 lays out and cross-jumps the two state-range switch bodies differently.
// STUB: GAME 0x004887a0
bool RHElementActorNPC::FUN_004887a0(int kind)
{
    int state;
    if (((RHNPCActorCalls *)this)->V130() == 1)
    {
        switch (kind)
        {
        case 0:
        case 1:
            state = *(int *)((char *)this + 0x4a8 + (*(int **)((char *)this + 0x49c))[1]);
            if (state >= 0 && state <= 2)
                return false;
            return true;
        case 2:
            state = *(int *)((char *)this + 0x4a8 + (*(int **)((char *)this + 0x49c))[1]);
            if (state >= 0 && state <= 1)
                return false;
            return true;
        case 3:
        case 4:
        case 5:
            return true;
        }
    }
    else
    {
        switch (kind)
        {
        case 0:
            return true;
        case 1:
            state = *(int *)((char *)this + 0x4a8 + (*(int **)((char *)this + 0x49c))[1]);
            if (state >= 0 && state <= 2)
                return false;
            return true;
        case 2:
            state = *(int *)((char *)this + 0x4a8 + (*(int **)((char *)this + 0x49c))[1]);
            if (state >= 0 && state <= 1)
                return false;
            return true;
        case 3:
        case 4:
        case 5:
            return true;
        }
    }
    return false;
}

// FUNCTION: GAME 0x0048b440
void RHElementActorNPC::SetUniversalFrameCounter(unsigned long &counter)
{
    g_unk0x006c08a4 = (unsigned *)&counter;
}

#include "RHSoldierNPCCalls.h"

class RHUnk00413640
{
public:
    void Unk(int state, bool flag);
};

class RHNPCAIStateCalls
{
public:
    virtual void V00() = 0;
    virtual void V04() = 0;
    virtual void V08() = 0;
    virtual void V0c() = 0;
    virtual void V10(int state, bool flag) = 0;
};

#define RHNPC_AI(type) ((type *)((char *)this + 0x49c + (*(int **)((char *)this + 0x49c))[1]))

// FUNCTION: GAME 0x0048b510
void RHSoldierNPCCalls::FUN_0048b510(void *element)
{
    RHNPC_AI(RHUnk00413640)->Unk(0, true);
    RHNPC_AI(RHNPCAIStateCalls)->V10(0, true);
    if (*((char *)this + 0x65c))
        ((RHElementActorNPC *)this)->FUN_00486f30(5);
    *((bool *)this + 0x4ee) = element && (*(unsigned *)((char *)element + 4) & 0xf) == 0xc;
    *((char *)RHNPC_AI(char) + 0x2ac) = 0;
    RHNPC_AI(RHScriptBatchCalls)->Unk00419fb0(0);
    RHElementActorNPC::FUN_0048c6a0(this, 3);
    RHElementActorNPC::FUN_0048c6a0(this, 4);
    ((RHElementActorHuman *)this)->FUN_0047f4f0(element);
}

// STRING: GAME 0x006ae570
static const char *g_rhelementactornpcFile = "P:\\Robin Hood\\RHelementactornpc.cpp";

// parked: 0x0048b5d0, 84.82%; unannotated to preserve coupled callers.
bool RHElementActorNPC::Serialize(SBFile &file)
{
    unsigned count;
    unsigned char type;
    RHDetectable value;
    RHEngine *engine = g_pEngine;
    RHSerializeName(file,
                    // STRING: GAME 0x006ae5cc
                    "RHElementActorNPC");
    RHNPC_ACCESS((char *)this + 0x4c8, 2, 3973);
    RHNPC_ACCESS((char *)this + 0x4ca, 2, 3974);
    RHNPC_ACCESS((char *)this + 0x4d0, 2, 3975);
    RHNPC_ACCESS((char *)this + 0x4ec, 2, 3976);
    if (file.m_version >= 3)
        engine->FUN_004c4490(file, *(void **)((char *)this + 0x500));
    else
    {
        int oldValue;
        RHNPC_ACCESS(&oldValue, 4, 3984);
        if (file.m_bLoading)
            *(void **)((char *)this + 0x500) = 0;
    }
    RHNPC_ACCESS((char *)this + 0x4ee, 1, 3991);
    RHNPC_ACCESS((char *)this + 0x4f0, 4, 3994);
    RHNPC_ACCESS((char *)this + 0x4f4, 1, 3995);
    RHNPC_ACCESS((char *)this + 0x4f6, 2, 3997);
    RHNPC_ACCESS((char *)this + 0x654, 0x90, 4000);
    engine->SerializeElementPointer(file, *(RHElement **)((char *)this + 0x6bc));
    RHNPC_ACCESS((char *)this + 0x4dc, 0x10, 4003);
    RHNPC_CHECK(((RHUnkPathGeometry *)g_unk0x6c0a9c)->Unk004fbec0(file, *(void **)((char *)this + 0x4e4)), 4004);
    ((SBGeoPoint2D *)((char *)this + 0x4d4))->Serialize(file);
    RHNPC_ACCESS((char *)this + 0x6e4, 1, 4009);
    char *ai = (char *)this + 0x49c;
    RHNPC_CHECK(((RHArtificialIntelligence *)(ai + (*(int **)ai)[1]))->Unk00414be0(file), 4012);
    RHNPC_ACCESS((char *)this + 0x4fa, 2, 4014);
    RHNPC_ACCESS((char *)this + 0x4fc, 4, 4015);
    for (type = 0; type < 6; ++type)
    {
        if (file.m_bLoading)
        {
            RHNPC_ACCESS(&count, 4, 4022);
            RHNPCDetectableList &list = ((RHNPCDetectableList *)((char *)this + 0x504))[type];
            RHSectorActorIter current((RHSectorActorNode *)list.m_head->m_next);
            RHSectorActorNode *end = (RHSectorActorNode *)list.m_head;
            while (current.m_p != end)
                ((RHUnk0046eb30 *)&list)->erase(RHScriptIter((RHScriptNode *)(current++).m_p));
            list.m_valid = 1;
            for (unsigned index = 0; index < count; ++index)
            {
                RHNPC_CHECK(value.Serialize(file), 4028);
                list.insert(list.end(), value);
            }
        }
        else
        {
            RHNPCDetectableList &list = ((RHNPCDetectableList *)((char *)this + 0x504))[type];
            count = list.m_count;
            RHNPC_ACCESS(&count, 4, 4036);
            for (unsigned index = 0; index < count; ++index)
            {
                ((RHTitbitList *)&list)->At(index);
                RHNPC_CHECK(((RHDetectable *)&list.m_cur->m_data)->Serialize(file), 4041);
            }
        }
        RHNPC_ACCESS((char *)this + 0x63c + type * 2, 2, 4046);
    }
    RHNPC_ACCESS((char *)this + 0x648, 2, 4049);
    RHNPC_ACCESS((char *)this + 0x64c, 4, 4050);
    RHNPC_ACCESS((char *)this + 0x4a0, 0x28, 4051);
    RHNPC_ACCESS((char *)this + 0x652, 1, 4054);
    if (file.m_bLoading)
    {
        *(short *)((char *)this + 0x4f8) = 0;
        *((char *)this + 0x6e5) = 0;
    }
    return ((RHNPCBaseCalls *)this)->FUN_004799e0(file);
}

#define SBGEO_BOUNDINGBOX2D_VIEW
#include "RHActorSequenceStorage.h"

// FUNCTION: GAME 0x0048c380
void *RHElementActorNPC::FUN_0048c380(RHElementActorHuman *target)
{
    if (!((RHNPCActorCalls *)this)->V48() && !RHNPC_FIELD(char, 0x1ce) && RHNPC_FIELD(void *, 0x500))
    {
        RHUnk0045aaf0 *sequence = (RHUnk0045aaf0 *)((char *)this + 0x14);
        sequence->FUN_0045abc0(0xf8, 0, 0);
        RHNPC_FIELD(char, 0x92) = 1;
        RHNPC_FIELD(int, 0xa0) = 0;
        RHNPC_FIELD(unsigned short, 0xa4) = 2;
        return sequence;
    }
    if (((RHNPCActorCalls *)this)->V48() || RHNPC_FIELD(char, 0x1ce))
    {
        if (RHNPC_FIELD(int, 0x4f0) && ((RHScriptBatchCalls *)target)->Unk0049d560(0x17))
        {
            RHUnk0045aaf0 *sequence = (RHUnk0045aaf0 *)((char *)this + 0x14);
            sequence->FUN_0045abc0(0x70, 0, 0);
            RHNPC_FIELD(char, 0x92) = 1;
            RHNPC_FIELD(int, 0xa0) = 0;
            RHNPC_FIELD(unsigned short, 0xa4) = 2;
            return sequence;
        }
        if (RHNPC_FIELD(char, 0x1ce) && ((RHScriptBatchCalls *)target)->Unk0049d560(0x1d) &&
            *(int *)(RHNPC_FIELD(char *, 0x50) + 0x8c) == 3)
        {
            RHUnk0045aaf0 *sequence = (RHUnk0045aaf0 *)((char *)this + 0x14);
            sequence->FUN_0045abc0(0x41, 0, 0);
            RHNPC_FIELD(char, 0x92) = 1;
            RHNPC_FIELD(int, 0xa0) = 0;
            RHNPC_FIELD(unsigned short, 0xa4) = 2;
            return sequence;
        }
        if (RHNPC_FIELD(char, 0x1ce) && ((RHScriptBatchCalls *)target)->Unk0049d560(0x1b))
        {
            RHUnk0045aaf0 *sequence = (RHUnk0045aaf0 *)((char *)this + 0x14);
            sequence->FUN_0045abc0(0x66, 0, 0);
            RHNPC_FIELD(char, 0x92) = 1;
            RHNPC_FIELD(int, 0xa0) = 0;
            RHNPC_FIELD(unsigned short, 0xa4) = 2;
            return sequence;
        }
    }
    return ((RHElementActorHuman *)this)->FUN_004837f0(target);
}

inline unsigned short RHNPCActorCount()
{
    RHMalignityActorCalls **first = *(RHMalignityActorCalls ***)((char *)g_pEngine + 0x495c);
    if (!first)
        return 0;
    return (unsigned short)(*(RHMalignityActorCalls ***)((char *)g_pEngine + 0x4960) - first);
}

#include <vector>

// FUNCTION: GAME 0x0048c620
void RHElementActorNPC::FUN_0048c620(void *actor)
{
    RHEngine *engine = g_pEngine;
    typedef std::vector<RHMalignityActorCalls *> Actors;
    unsigned short count = ((Actors *)((char *)engine + 0x4d28))->size();
    for (unsigned short index = 0; index < count; ++index)
    {
        RHMalignityActorCalls *npc = (*(Actors *)((char *)engine + 0x4d28))[index];
        if (((RHMalignityOwnerCalls *)((char *)npc + 0x6e8))->FUN_00438600() >= 30)
        {
            int state = *(int *)((char *)npc + (*(int **)((char *)npc + 0x49c))[1] + 0x4b0);
            if (state >= 73 && state <= 81)
                npc->FUN_0048c700(actor, 5);
        }
    }
}

// FUNCTION: GAME 0x0048c6a0
void RHElementActorNPC::FUN_0048c6a0(void *actor, unsigned mode)
{
    unsigned short count = RHNPCActorCount();
    for (unsigned short i = 0; i < count; ++i)
        (*(RHMalignityActorCalls ***)((char *)g_pEngine + 0x495c))[i]->FUN_0048ca20(actor, mode);
}

#include "RHActorPriorityCalls.h"
#include "RHSoldierNPCCalls.h"

struct RHUnk00571160Position;

// FUNCTION: GAME 0x0048ce80
void RHUnk0048ce80(int noise, RHUnk00571160Position *position)
{
    RHElementActorNPC::Noise(noise, *(RHAnimalNoisePosition *)position,
        FUN_00414360(*(RHMalignityPosition *)position, true).m_8, 0);
}

// FUNCTION: GAME 0x0048d100
int RHSoldierNPCCalls::FUN_0048d100(RHSoldierSequenceElement *element)
{
    int kind = element->m_5c;
    if (kind == 0xb)
    {
        switch (element->m_10)
        {
        case 0x7b:
            return 3;
        case 0x48: case 0x77: case 0x78: case 0x79: case 0x7a:
        case 0x7c: case 0x7d: case 0x86: case 0x87: case 0x88:
        case 0x8f: case 0x90:
            return 8;
        case 0x83: case 0x84: case 0x85:
            return 1;
        }
        return ((RHHumanPriorityCalls *)this)->FUN_00471f20(element);
    }
    return kind;
}

// FUNCTION: GAME 0x0048d390
void RHElementActorNPC::GetTransitionFlags(RHSequenceElement *element, unsigned long &first, unsigned long &second, unsigned long &third)
{
    switch (*(int *)((char *)element + 0x10))
    {
    case 0x77:
        first = 0x81; second = 1; break;
    case 0x7a:
        first = 1; second = 1; break;
    case 0x8f:
        first = 1; second = 1; break;
    case 0x90:
        first = 1; second = 0x20001; break;
    default:
        ((RHElementActorHuman *)this)->GetTransitionFlags(element, first, second, third);
    }
}

class RHElementActor
{
public:
    bool FUN_0046d710();
};

class RHNPCAIReactionCalls
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
    virtual void V24() = 0;
    virtual void V28() = 0;
    virtual void V2c() = 0;
    virtual void V30() = 0;
    virtual void V34() = 0;
    virtual void V38() = 0;
    virtual void V3c(int reaction) = 0;
};

// FUNCTION: GAME 0x0048d790
void RHSoldierNPCCalls::FUN_0048d790(RHSoldierSequenceElement *element)
{
    ((RHElementActorHuman *)this)->FUN_00479970((RHSequenceElement *)element);
    if (!FUN_0048da40((RHUnk0048da10 *)element) || *((char *)RHNPC_AI(char) + 0x204))
        return;
    switch (element->m_10)
    {
    case 0x13: case 0x14: case 0x16: case 0x7a:
        if (element->m_58 != 0)
        {
            if (element->m_58 == 5)
            {
                if (!*((char *)RHNPC_AI(char) + 0x175) && ((RHElementActor *)this)->FUN_0046d710())
                {
                    RHNPC_AI(RHNPCAIReactionCalls)->V3c(2);
                    *((char *)RHNPC_AI(char) + 0x175) = 1;
                }
                RHNPC_AI(RHScriptBatchCalls)->Unk0040d980(4);
            }
        }
        else
            RHNPC_AI(RHScriptBatchCalls)->Unk0040d980(3);
        break;
    case 0x19: case 0x1a: case 0x1b: case 0x1c: case 0x1d: case 0x1e: case 0x1f: case 0x22:
    case 0x23: case 0x27: case 0x2a: case 0x2e: case 0x2f: case 0x30: case 0x32: case 0x36:
    case 0x3b: case 0x3c: case 0x3d: case 0x3e: case 0x3f: case 0x40: case 0x41: case 0x42:
    case 0x43: case 0x44: case 0x45: case 0x47: case 0x48: case 0x4b: case 0x54: case 0x55:
    case 0x56: case 0x6b: case 0x77: case 0x78: case 0x7b: case 0x7c: case 0x87: case 0x88:
    case 0x8a: case 0x8d:
        if (element->m_58 == 0 || element->m_58 == 6)
            RHNPC_AI(RHScriptBatchCalls)->Unk0040d980(5);
        else
            RHNPC_AI(RHScriptBatchCalls)->Unk0040d980(6);
        break;
    case 0x37: case 0x38: case 0x39: case 0x3a:
        if (element->m_58 == 0 || element->m_58 == 6)
            RHNPC_AI(RHScriptBatchCalls)->Unk0040d980(5);
        break;
    case 0xa1:
        if (element->m_58 == 0)
            RHNPC_AI(RHScriptBatchCalls)->Unk0040d980(5);
        break;
    case 0x89:
        if (element->m_58 == 0 || (element->m_58 > 4 && element->m_58 <= 6))
            RHNPC_AI(RHScriptBatchCalls)->Unk0040d980(0x1b);
        break;
    }
}

// FUNCTION: GAME 0x0048d990
void RHElementActorNPC::FUN_0048d990(unsigned short amount, void *source, bool force)
{
    char previous = RHNPC_FIELD(char, 0x1ce);
    ((RHElementActorHuman *)this)->FUN_00471c00(amount, source, force);
    if (previous)
    {
        if (!RHNPC_FIELD(char, 0x1ce) && *(int *)((char *)RHNPC_AI(char) + 0x14) == 2)
            RHNPC_AI(RHScriptBatchCalls)->Unk0040d980(13);
    }
    else if (RHNPC_FIELD(char, 0x1ce))
    {
        ((RHMalignityActorCalls *)this)->FUN_0048e580();
        RHNPC_AI(RHScriptBatchCalls)->Unk0040d980(15);
        RHNPC_FIELD(bool, 0x4ee) = source && (*(unsigned *)((char *)source + 4) & 15) == 12;
    }
}

#include "RHHumanSequenceElement.h"
#include "RHActorTranslationSequenceCalls.h"

class RHUnk00418b80
{
public:
    void Unk(bool value);
};

// FUNCTION: GAME 0x0048da80
void RHElementActorNPC::FUN_0048da80(RHSequenceElement *element)
{
    switch (element->m_10)
    {
    case 0x7f:
        RHNPC_AI(RHUnk00418b80)->Unk(false);
        ((RHActorTranslationSequenceCalls *)element)->V0c(0, true);
        return;
    case 0x80:
        RHNPC_AI(RHScriptBatchCalls)->Unk00418bc0();
        ((RHActorTranslationSequenceCalls *)element)->V0c(0, true);
        return;
    case 0x81:
        if (RHNPC_FIELD(char, 8))
            ((RHNPCActorCalls *)this)->V34();
        ((RHActorTranslationSequenceCalls *)element)->V0c(0, true);
        return;
    case 0x92:
        ((RHNPCActorCalls *)this)->V100(element->Unk00587160(15), element->Unk00587160(16));
        ((RHActorTranslationSequenceCalls *)element)->V0c(0, true);
        return;
    default:
        ((RHElementActorHuman *)this)->FUN_0047a880(element);
    }
}

// FUNCTION: GAME 0x0048e580
void RHMalignityActorCalls::FUN_0048e580()
{
    struct Position
    {
        float x;
        float y;
        void *area;
        unsigned short layer;
    };
    Position &position = RHNPC_FIELD(Position, 0x63c);
    position.x = 0.0f;
    position.y = 0.0f;
    position.area = 0;
    position.layer = 0;
    RHNPC_FIELD(unsigned, 0x64c) = 7;
}

// FUNCTION: GAME 0x0048e5b0
void RHMalignityActorCalls::FUN_0048e5b0(unsigned operation, unsigned short value, unsigned)
{
    switch (operation)
    {
    case 1:
        unsigned short current = RHNPC_FIELD(unsigned short, 0x4ca);
        RHNPC_FIELD(unsigned short, 0x4ca) = value >= current ? 0 : current - value;
    }
}

// FUNCTION: GAME 0x0048e5f0
unsigned short RHMalignityActorCalls::FUN_0048e5f0(unsigned operation)
{
    switch (operation)
    {
    default:
        return 0xffff;
    case 1:
        return RHNPC_FIELD(unsigned short, 0x4ca);
    }
}

#include "RHActorTranslationSequenceCalls.h"

// FUNCTION: GAME 0x0048d460
bool RHElementActorNPC::FUN_0048d460(unsigned flags, RHActorTranslationSequenceCalls *sequence)
{
    if (*(int *)((char *)RHNPC_FIELD(void *, 0x50) + 0x8c) != 8)
        return ((RHElementActorHuman *)this)->FUN_00475750(flags, sequence);
    if (flags & 1)
    {
        RHOrder *order = new RHOrder;
        order->m_24 = 0xa0;
        order->m_2a = 0;
        sequence->FUN_00585970(order);
        *(int *)((char *)sequence + 0x3c) = 1;
    }
    return true;
}

#include "RHElementActorCivilianCore.h"
#include "RHPositionProvider.h"
#include "RHSoundActorCalls.h"
#include "RHMalignityPosition.h"

extern RHArtificialIntelligenceSoundCalls *g_unk0x006c1070;

inline float RHNPCNoiseHeight(void *sprite)
{
    return *(float *)((char *)sprite + 0x18);
}

// FUNCTION: GAME 0x0048ec70
void RHElementActorNPC::FUN_0048ec70()
{
    int state = *(int *)((char *)RHNPC_AI(char) + 0x14);
    if (state >= 41 && state <= 52)
        return;
    if (RHNPC_FIELD(char, 0x1ce))
    {
        if (*(int *)((char *)RHNPC_AI(char) + 0x258) != 121)
        {
            g_unk0x006c1070->Unk005a8d10((RHArtificialIntelligenceActor *)this);
            *(int *)((char *)RHNPC_AI(char) + 0x258) = 121;
        }
        return;
    }
    RHMalignityPosition position;
    ((RHUnk00560420 *)((char *)RHNPC_FIELD(void *, 0x50) + 4))->Unk((RHUnk00571160Position *)&position);
    if ((RHNPC_FIELD(unsigned, 4) & 31) == 4)
    {
        if (((RHElementActorCivilian *)this)->FUN_00470ce0())
            RHNPC_AI(RHArtificialIntelligence)->Unk00418c40(((RHNPCActorCalls *)this)->V48() ? 110 : 109, 2);
        else
            RHNPC_AI(RHArtificialIntelligence)->Unk00418c40(((RHNPCActorCalls *)this)->V48() ? 85 : 84, 2);
    }
    else
    {
        if (((RHNPCActorCalls *)this)->Vf8())
            RHNPC_AI(RHArtificialIntelligence)->Unk00418c40(((RHNPCActorCalls *)this)->V48() ? 110 : 109, 2);
        else
            RHNPC_AI(RHArtificialIntelligence)->Unk00418c40(((RHNPCActorCalls *)this)->V48() ? 30 : 29, 2);
    }
    Noise(7, (RHAnimalNoisePosition &)position, RHNPCNoiseHeight(RHNPC_FIELD(void *, 0x50)), this);
}

// FUNCTION: GAME 0x0048ed90
void RHElementActorNPC::FUN_0048ed90(unsigned short state)
{
    unsigned short current;
    RHNPCActorCalls *actor = *(RHNPCActorCalls **)((char *)RHNPC_AI(char) + 4);
    if ((*(unsigned *)((char *)actor + 4) & 31) == 20)
    {
        if (actor->Vf8())
            current = *(unsigned short *)((char *)RHNPC_AI(char) + 0x258) - 106;
        else
            current = *(unsigned short *)((char *)RHNPC_AI(char) + 0x258);
    }
    else if (((RHElementActorCivilian *)actor)->FUN_00470ce0())
        current = *(unsigned short *)((char *)RHNPC_AI(char) + 0x258) - 106;
    else
        current = *(unsigned short *)((char *)RHNPC_AI(char) + 0x258) - 78;
    if (current == state)
    {
        unsigned short flags = *(unsigned short *)((char *)RHNPC_AI(char) + 0x25c);
        *(int *)((char *)RHNPC_AI(char) + 0x258) = 121;
        *(unsigned short *)((char *)RHNPC_AI(char) + 0x25c) = 0;
        RHNPC_AI(RHArtificialIntelligence)->Unk00422b70(6, 0);
        RHNPC_AI(RHArtificialIntelligence)->Unk004195f0(flags);
    }
}

// FUNCTION: GAME 0x0048ee90
void *RHMalignityActorCalls::FUN_0048ee90(unsigned short index)
{
    return ((RHNPCCachedList *)((char *)this + 0x504))->Get(index).m_00;
}

// FUNCTION: GAME 0x0048efa0
int RHElementActorNPC::FUN_0048efa0()
{
    if (((RHNPCActorCalls *)this)->V130() == 0 &&
        *(char *)((char *)g_pEngine + 0x4aa8) &&
        !((RHNPCActorCalls *)this)->Vf4())
        return 1;
    return 0;
}

// FUNCTION: GAME 0x0048efe0
RHNPCDetectableList::RHNPCDetectableList()
{
    char value;
    *(char *)&m_0 = value;
    RHPathHistoryNode *list = new RHPathHistoryNode;
    list->m_next = list;
    list->m_prev = list;
    m_head = list;
    m_valid = 1;
    m_count = 0;
    *(char *)((char *)this + 0x2a) = 0;
    *(char *)((char *)this + 0x28) = 0;
    *(char *)((char *)this + 0x29) = 0;
    *(char *)((char *)this + 0x2c) = 0;
    *(int *)((char *)this + 0x30) = 0;
    *(int *)((char *)this + 0x24) = 7;
}

void RHElementActorNPC::Emit(SBFile &file)
{
    FUN_00487ad0(*(RHMalignityPosition *)this);
    FUN_0048d460(0, 0);
    FUN_0048c380(0);
    FUN_00487ce0();
    FUN_0048c620(this);
    FUN_0048c6a0(this, 0);
    Serialize(file);
    RHDetectable value;
    value.Serialize(file);
    FUN_0048efa0();
    RHNPCDetectableList detectables;
}

#include "RHArtificialMalignityCore.h"

// GLOBAL: GAME 0x006775c8
float g_unk0x006775c8 = 700.0f;

// Parked at 0.6974: actor/receiver registers and tag comparison width differ.
// STUB: GAME 0x0048c4d0
void RHElementActorNPC::FUN_0048c4d0()
{
    *(unsigned short *)((char *)this + 0x4f6) = 0;
    unsigned short count = RHNPCActorCount();
    for (unsigned short index = 0; index < count; ++index)
    {
        RHMalignityActorCalls *actor = (*(RHMalignityActorCalls ***)((char *)g_pEngine + 0x495c))[index];
        if (actor != (RHMalignityActorCalls *)this)
        {
            char *ai = (char *)this + 0x49c;
            if (!*(char *)(ai + (*(int **)ai)[1] + 0x2ac) ||
                (*(RHUnk00613e90 *)(*(char **)((char *)this + 0x50) + 0x10)).FUN_005df550(
                    *(RHUnk00613e90 *)(*(char **)((char *)actor + 0x50) + 0x10)).FUN_005df680() > g_unk0x006775c8)
            {
                if (!actor->FUN_0048c8e0(this, 1))
                    actor->FUN_0048c700(this, 1);
            }
            unsigned type = *(unsigned *)((char *)this + 4) & 0x1f;
            if (type == 0x14 && (*(unsigned *)((char *)actor + 4) & 0x1f) == type)
                ((RHArtificialMalignity *)((char *)actor + 0x6e8))->FUN_00446eb0(this);
        }
    }
}
