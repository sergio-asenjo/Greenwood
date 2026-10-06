#include "RHElementActorNPC_calls.h"

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
    engine->SerializeNestedA(file, (char *)this + 0x6bc);
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

void RHElementActorNPC::Emit(SBFile &file)
{
    Serialize(file);
    RHDetectable value;
    value.Serialize(file);
}
