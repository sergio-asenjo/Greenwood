#include "SBNullstr.h"
#include "RHPatch.h"

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

// FUNCTION: GAME 0x0054fe10
void RHPatch::FUN_0054fe10()
{
    RHPatchDoorCalls **first = *(RHPatchDoorCalls ***)((char *)this + 0x15c);
    unsigned count = first == 0 ? 0 : *(RHPatchDoorCalls ***)((char *)this + 0x160) - first;
    for (unsigned i = 0; i < count; ++i)
        (*(RHPatchDoorCalls ***)((char *)this + 0x15c))[i]->FUN_0051b660();
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
