#include "SBNullstr.h"
#include "RHElementActorNPC_calls.h"
#include "RHMalignityActorCalls.h"

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

inline unsigned short RHNPCActorCount()
{
    RHMalignityActorCalls **first = *(RHMalignityActorCalls ***)((char *)g_pEngine + 0x495c);
    if (!first)
        return 0;
    return (unsigned short)(*(RHMalignityActorCalls ***)((char *)g_pEngine + 0x4960) - first);
}

// FUNCTION: GAME 0x0048c6a0
void RHElementActorNPC::FUN_0048c6a0(void *actor, unsigned mode)
{
    unsigned short count = RHNPCActorCount();
    for (unsigned short i = 0; i < count; ++i)
        (*(RHMalignityActorCalls ***)((char *)g_pEngine + 0x495c))[i]->FUN_0048ca20(actor, mode);
}

void RHElementActorNPC::Emit(SBFile &file)
{
    FUN_00487ce0();
    FUN_0048c6a0(this, 0);
    Serialize(file);
    RHDetectable value;
    value.Serialize(file);
}
