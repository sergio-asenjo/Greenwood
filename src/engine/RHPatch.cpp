#include "SBGeoPoint2D.h"
#include "SBNullstr.h"
#include "RHPatch.h"

DECOMP_SIZE_ASSERT(RHPatch, 0x1a0)
DECOMP_STATIC_ASSERT(offsetof(RHPatch, m_3) == 0x03)
DECOMP_STATIC_ASSERT(offsetof(RHPatch, m_6) == 0x06)
DECOMP_STATIC_ASSERT(offsetof(RHPatch, m_8) == 0x08)
DECOMP_STATIC_ASSERT(offsetof(RHPatch, m_9) == 0x09)
DECOMP_STATIC_ASSERT(offsetof(RHPatch, m_a) == 0x0a)
DECOMP_STATIC_ASSERT(offsetof(RHPatch, m_b) == 0x0b)
DECOMP_STATIC_ASSERT(offsetof(RHPatch, m_d) == 0x0d)
DECOMP_STATIC_ASSERT(offsetof(RHPatch, m_10) == 0x10)
DECOMP_STATIC_ASSERT(offsetof(RHPatch, m_14) == 0x14)
DECOMP_STATIC_ASSERT(offsetof(RHPatch, m_16) == 0x16)
DECOMP_STATIC_ASSERT(offsetof(RHPatch, m_18) == 0x18)
DECOMP_STATIC_ASSERT(offsetof(RHPatch, m_1c) == 0x1c)
DECOMP_STATIC_ASSERT(offsetof(RHPatch, m_40) == 0x40)
DECOMP_STATIC_ASSERT(offsetof(RHPatch, m_64) == 0x64)
DECOMP_STATIC_ASSERT(offsetof(RHPatch, m_88) == 0x88)
DECOMP_STATIC_ASSERT(offsetof(RHPatch, m_ac) == 0xac)
DECOMP_STATIC_ASSERT(offsetof(RHPatch, m_d0) == 0xd0)
DECOMP_STATIC_ASSERT(offsetof(RHPatch, m_f4) == 0xf4)
DECOMP_STATIC_ASSERT(offsetof(RHPatch, m_118) == 0x118)
DECOMP_STATIC_ASSERT(offsetof(RHPatch, m_13c) == 0x13c)
DECOMP_STATIC_ASSERT(offsetof(RHPatch, m_140) == 0x140)
DECOMP_STATIC_ASSERT(offsetof(RHPatch, m_148) == 0x148)
DECOMP_STATIC_ASSERT(offsetof(RHPatch, m_154) == 0x154)
DECOMP_STATIC_ASSERT(offsetof(RHPatch, m_158) == 0x158)
DECOMP_STATIC_ASSERT(offsetof(RHPatch, m_178) == 0x178)
DECOMP_STATIC_ASSERT(offsetof(RHPatch, m_19c) == 0x19c)
DECOMP_SIZE_ASSERT(RHMotionAreaList<void *>, 0x24)
DECOMP_STATIC_ASSERT(offsetof(RHMotionAreaList<void *>, m_cursor) == 0x0c)
DECOMP_SIZE_ASSERT(SBResourceSurfaceArray, 0x20)
DECOMP_SIZE_ASSERT(RHPatchActorList, 0x24)
DECOMP_STATIC_ASSERT(offsetof(RHPatchActorList, list) == 0)
DECOMP_STATIC_ASSERT(offsetof(RHPatchActorList, valid) == 0x10)

// STUB: GAME 0x0054ec40
RHPatch::~RHPatch()
{
}

// FUNCTION: GAME 0x0054f870
bool RHUnk0054f870::Unk0054f870(SBFile &file)
{
    RHPatch *patch = (RHPatch *)this;
    // STRING: GAME 0x006b13c0
    RHSerializeName(file, "RHPatch");
    if (file.Access(&patch->m_2, 1) < 0)
    {
        SBString *error = file.GetError();
        SBAssert(0,
            // STRING: GAME 0x006b13a4
            "P:\\Robin Hood\\RHpatch.cpp", 339, "Serialize failed reason is %s", error->m_chars ? error->m_chars : "");
        return false;
    }
    ((RHProfileFile *)&file)->FUN_005f5370(4, 1);
    if (file.m_version >= 19)
    {
        if (file.Access(&patch->m_c, 1) < 0)
        {
            SBString *error = file.GetError();
            SBAssert(0, "P:\\Robin Hood\\RHpatch.cpp", 350, "Serialize failed reason is %s", error->m_chars ? error->m_chars : "");
            return false;
        }
    }
    int count;
    RHElementActor *actor;
    if (!file.m_bLoading)
    {
        count = patch->m_178.list.size();
        if (file.Access(&count, 2) < 0)
        {
            SBString *error = file.GetError();
            SBAssert(0, "P:\\Robin Hood\\RHpatch.cpp", 356, "Serialize failed reason is %s", error->m_chars ? error->m_chars : "");
            return false;
        }
        for (unsigned short i = 0; i < (unsigned short)count; ++i)
        {
            RHSectorActorList &actors = (RHSectorActorList &)patch->m_178;
            actors.Unk005c8e40(i);
            actor = actors.m_cur.m_p->m_data;
            if (!g_pEngine->FUN_004c3af0(file, (void *&)actor))
                return false;
        }
    }
    else
    {
        RHSectorActorList &actors = (RHSectorActorList &)patch->m_178;
        typedef std::list<RHElementActor *>::iterator Iterator;
        typedef Iterator (RHTitbitList::*Clear)(Iterator, Iterator);
        (((RHTitbitList *)&actors)->*(Clear)&RHTitbitList::Clear)(patch->m_178.list.begin(), patch->m_178.list.end());
        actors.m_valid = 1;
        if (file.Access(&count, 2) < 0)
        {
            SBString *error = file.GetError();
            SBAssert(0, "P:\\Robin Hood\\RHpatch.cpp", 371, "Serialize failed reason is %s", error->m_chars ? error->m_chars : "");
            return false;
        }
        for (unsigned short i = 0; i < (unsigned short)count; ++i)
        {
            if (!g_pEngine->FUN_004c3af0(file, (void *&)actor))
                return false;
            RHSectorActorNode *node = actors.m_head;
            node->m_prev = (RHSectorActorNode *)((RHUnk0046eb30 *)&actors)->Unk0059f720((RHScriptNode *)node, (RHScriptNode *)node->m_prev);
            RHSectorActorNode *created = node->m_prev;
            created->m_prev->m_next = created;
            RHSeqList::CopyData((RHSequenceElement **)&created->m_data, (RHSequenceElement *const *)&actor);
            ++actors.m_count;
            actors.m_valid = 1;
        }
    }
    if (file.m_bLoading)
    {
        char first;
        char second;
        char third;
        if (file.Access(&first, 1) < 0)
        {
            SBString *error = file.GetError();
            SBAssert(0, "P:\\Robin Hood\\RHpatch.cpp", 389, "Serialize failed reason is %s", error->m_chars ? error->m_chars : "");
            return false;
        }
        if (file.Access(&second, 1) < 0)
        {
            SBString *error = file.GetError();
            SBAssert(0, "P:\\Robin Hood\\RHpatch.cpp", 390, "Serialize failed reason is %s", error->m_chars ? error->m_chars : "");
            return false;
        }
        if (file.Access(&third, 1) < 0)
        {
            SBString *error = file.GetError();
            SBAssert(0, "P:\\Robin Hood\\RHpatch.cpp", 391, "Serialize failed reason is %s", error->m_chars ? error->m_chars : "");
            return false;
        }
        patch->m_2 = 1;
        patch->m_b = 0;
        patch->m_0 = 0;
        if (second)
            patch->FUN_00550070(true);
        if (third)
            patch->FUN_00550150();
        if (patch->m_18)
            patch->m_18->Slot16(file);
    }
    else
    {
        if (file.Access(&patch->m_2, 1) < 0)
        {
            SBString *error = file.GetError();
            SBAssert(0, "P:\\Robin Hood\\RHpatch.cpp", 422, "Serialize failed reason is %s", error->m_chars ? error->m_chars : "");
            return false;
        }
        if (file.Access(&patch->m_0, 1) < 0)
        {
            SBString *error = file.GetError();
            SBAssert(0, "P:\\Robin Hood\\RHpatch.cpp", 423, "Serialize failed reason is %s", error->m_chars ? error->m_chars : "");
            return false;
        }
        if (file.Access(&patch->m_b, 1) < 0)
        {
            SBString *error = file.GetError();
            SBAssert(0, "P:\\Robin Hood\\RHpatch.cpp", 424, "Serialize failed reason is %s", error->m_chars ? error->m_chars : "");
            return false;
        }
        if (patch->m_18)
            patch->m_18->Slot16(file);
    }
    if (file.Access(&patch->m_19c, 1) < 0)
    {
        SBString *error = file.GetError();
        SBAssert(0, "P:\\Robin Hood\\RHpatch.cpp", 467, "Serialize failed reason is %s", error->m_chars ? error->m_chars : "");
        return false;
    }
    return true;
}

#include "RHSpriteCore.h"
#include "RHSpriteLastFrameCalls.h"
#include "RHElementFX.h"
#include "RHCivilianSpriteView.h"
#include "RHEngineWidenedCalls.h"

// STUB: GAME 0x0054fc40
void RHPatch::FUN_0054fc40(bool open)
{
    if (m_7)
    {
        SBGeoBoundingBox2D bounds;
        SBGeoBoundingBox2D first;
        SBGeoBoundingBox2D second;
        if (!open)
        {
            ((RHElementFX *)m_18)->RestoreBackground();
            *((char *)g_pEngine + 0x48d1) = 0;
        }
        else
        {
            unsigned short x = (*(RHSprite **)((char *)m_18 + 0x50))->m_184;
            unsigned short y = (*(RHSprite **)((char *)m_18 + 0x50))->m_186;
            (*(RHSprite **)((char *)m_18 + 0x50))->FUN_005b76e0(0x95, 0);
            (*(RHUnk005bd5b0 **)((char *)m_18 + 0x50))->Unk(true);
            ((RHElementFX *)m_18)->FUN_004a9990();
            unsigned short height = (*(RHCivilianSpriteView **)((char *)m_18 + 0x50))->FUN_005bdf20();
            unsigned short width = (*(RHCivilianSpriteView **)((char *)m_18 + 0x50))->FUN_005bdef0();
            bounds.FUN_00609050(*(SBGeoPoint2D *)(*(char **)((char *)m_18 + 0x50) + 0x1c),
                                (*(SBGeoPoint2D *)(*(char **)((char *)m_18 + 0x50) + 0x1c)).Unk005fc190(SBGeoVector2D((float)width, (float)height)));
            RHSprite *sprite = *(RHSprite **)((char *)m_18 + 0x50);
            sprite->FUN_005bd450();
            sprite->m_184 = x;
            sprite->m_186 = y;
        }
    }
}

// FUNCTION: GAME 0x0054fe10
void RHPatch::FUN_0054fe10()
{
    RHPatchDoorCalls **first = *(RHPatchDoorCalls ***)((char *)this + 0x15c);
    unsigned count = first == 0 ? 0 : *(RHPatchDoorCalls ***)((char *)this + 0x160) - first;
    for (unsigned i = 0; i < count; ++i)
        (*(RHPatchDoorCalls ***)((char *)this + 0x15c))[i]->FUN_0051b660();
}

// FUNCTION: GAME 0x0054fe50
void RHPatch::FUN_0054fe50(bool open, bool mode)
{
    unsigned short count;
    unsigned short i;
    count = m_1c.size();
    for (i = 0; i < count; ++i)
        *(char *)m_1c.At(i) = !open;
    count = m_40.size();
    for (i = 0; i < count; ++i)
        *(char *)m_40.At(i) = open;
    count = m_64.size();
    for (i = 0; i < count; ++i)
        *((char *)m_64.At(i) + 8) = !open;
    count = m_88.size();
    for (i = 0; i < count; ++i)
        *((char *)m_88.At(i) + 8) = open;
    count = m_ac.size();
    for (i = 0; i < count; ++i)
        *((char *)m_ac.At(i) + 0x34) = !open;
    count = m_d0.size();
    for (i = 0; i < count; ++i)
        *((char *)m_d0.At(i) + 0x34) = open;
    count = m_f4.size();
    for (i = 0; i < count; ++i)
        *((char *)m_f4.At(i) + 0x18) = !open;
    count = m_118.size();
    for (i = 0; i < count; ++i)
        *((char *)m_118.At(i) + 0x18) = open;
    if (m_d)
        g_pEngine->PerformPathFinderStateChange(m_14, m_16, m_10, !mode);
}

// FUNCTION: GAME 0x00550070
void RHPatch::FUN_00550070(bool mode)
{
    if (m_1)
        m_2 = 0;
    FUN_0054fe10();
    if (m_0)
    {
        if (!m_1)
        {
            m_0 = 0;
            if (m_8)
            {
                *((char *)m_18 + 0x12) = 1;
                (*(RHSprite **)((char *)m_18 + 0x50))->FUN_005b76e0(0x94, 0);
                (*(RHUnk005bd5b0 **)((char *)m_18 + 0x50))->Unk(false);
            }
            else if (m_18)
                *((char *)m_18 + 0x12) = 0;
            FUN_0054fe50(false, mode);
        }
    }
    else
    {
        m_0 = 1;
        FUN_0054fc40(true);
        FUN_0054fe50(true, mode);
        if (m_a)
        {
            *((char *)m_18 + 0x12) = 1;
            (*(RHSprite **)((char *)m_18 + 0x50))->FUN_005b76e0(0x96, 0);
            (*(RHUnk005bd5b0 **)((char *)m_18 + 0x50))->Unk(false);
        }
        else if (m_18)
            *((char *)m_18 + 0x12) = 0;
    }
}

// FUNCTION: GAME 0x00550150
void RHPatch::FUN_00550150()
{
    if (m_6 && m_b)
    {
        *((char *)m_18 + 0x12) = 0;
        FUN_00550070(false);
    }
    if (m_0)
    {
        if (m_1)
            return;
        FUN_0054fc40(false);
        if (m_9)
        {
            *((char *)m_18 + 0x12) = 1;
            (*(RHSprite **)((char *)m_18 + 0x50))->FUN_005b76e0(0x95, 0);
            (*(RHUnk005bd5b0 **)((char *)m_18 + 0x50))->Unk(true);
            m_b = 1;
        }
        else
        {
            if (m_18)
                *((char *)m_18 + 0x12) = 0;
            FUN_00550070(false);
        }
    }
    else if (m_9)
    {
        *((char *)m_18 + 0x12) = 1;
        (*(RHSprite **)((char *)m_18 + 0x50))->FUN_005b76e0(0x95, 0);
        (*(RHUnk005bd5b0 **)((char *)m_18 + 0x50))->Unk(false);
        m_b = 1;
    }
    else
    {
        if (m_18)
            *((char *)m_18 + 0x12) = 0;
        FUN_00550070(false);
    }
}

// FUNCTION: GAME 0x00550220
void RHPatch::FUN_00550220()
{
    if (m_0)
    {
        FUN_0054fc40(false);
        if (!m_b)
            FUN_0054fe10();
    }
    m_0 = 0;
    m_2 = m_3;
    if (m_6)
    {
        if (m_8)
        {
            ((RHElementFX *)m_18)->RestoreBackground();
            *((char *)m_18 + 0x12) = 1;
            (*(RHSprite **)((char *)m_18 + 0x50))->FUN_005b76e0(0x94, 0);
            (*(RHUnk005bd5b0 **)((char *)m_18 + 0x50))->Unk(false);
            m_b = 0;
            FUN_0054fe50(false, true);
            return;
        }
        if (m_18)
        {
            ((RHElementFX *)m_18)->RestoreBackground();
            *((char *)m_18 + 0x12) = 0;
        }
        m_b = 0;
    }
    FUN_0054fe50(false, true);
}

// FUNCTION: GAME 0x005502c0
void RHPatch::Enter(RHElementActor *actor)
{
    RHElementActor *value = actor;
    RHSectorActorList &actors = (RHSectorActorList &)m_178;
    if (actors.Unk004b8f80(value, true) != -1)
    {
        SBAssert(0, "P:\\Robin Hood\\RHpatch.cpp", 815,
            // STRING: GAME 0x006b13c8
            "VERBOTEN : Actor entering a patch sector twice !");
    }
    else
    {
        RHSectorActorNode *node = actors.m_head->m_next;
        node->m_prev = (RHSectorActorNode *)((RHUnk0046eb30 *)&actors)->Unk0059f720((RHScriptNode *)node, (RHScriptNode *)node->m_prev);
        RHSectorActorNode *created = node->m_prev;
        created->m_prev->m_next = created;
        RHSeqList::CopyData((RHSequenceElement **)&created->m_data, (RHSequenceElement *const *)&actor);
        ++actors.m_count;
        actors.m_valid = 1;
    }
    if (actor->UnkType() == RHUnkSectorType12 && actor->m_5cc != 0)
        Enter(actor->m_5cc);
}

// FUNCTION: GAME 0x00550360
void RHPatch::Leave(RHElementActor *actor)
{
    RHPatchActorList &actors = m_178;
    int found = actors.Find(actor);
    if ((unsigned short)found == 0xffff)
    {
        SBAssert(0, "P:\\Robin Hood\\RHpatch.cpp", 849,
            // STRING: GAME 0x006b13fc
            "VERBOTEN : Actor leaving a script sector he hadn't entered !");
    }
    else
    {
        ((RHSectorActorList *)&actors)->Unk005c8e40((unsigned short)found);
        typedef std::list<RHElementActor *>::iterator (RHUnk0046eb30::*Erase)(std::list<RHElementActor *>::iterator);
        (((RHUnk0046eb30 *)&actors)->*(Erase)&RHUnk0046eb30::erase)(actors.current);
        actors.valid = 1;
    }
    if (actor->UnkType() == RHUnkSectorType12 && actor->m_5cc != 0)
        Leave(actor->m_5cc);
}

void RHPatch::Emit(SBFile &file, RHElementActor *actor)
{
    Serialize(file);
    Enter(actor);
    Leave(actor);
}
