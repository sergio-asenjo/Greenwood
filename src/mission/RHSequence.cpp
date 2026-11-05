// RHSequence.cpp — translation unit with __FILE__ evidence at 0x00584980
// ("P:\Robin Hood\RHsequence.cpp", symbols/functions-by-file.tsv).
//
// BINDING (0x005843c0 -> RHSequence::Serialize(SBFile&, bool)):
//   - TU:        rhsequence.cpp (embedded __FILE__ string 0x006b7460).
//   - Class:     RHSequence (symbols/oracle-correlation.tsv: rhsequence -> class
//                RHSequence, 21 methods).
//   - Signature: RHSequence::Serialize(SBFile&, bool)
//                (symbols/mac-RH.txt; the only other serializer in the Mac TU,
//                symbols/mac-functions-by-file.tsv: 0x001a88b0 Serialize).
//   - Signals:
//       * the first act writes the type-name tag "RHSequence" (string 0x006b7484)
//         via the 0x005e1b70 helper;
//       * an EH frame (new below), `sub esp,0x10`, this=esi, file=edi, the bool
//         as the second stack arg;
//       * an `Access` chain on +0x34/+0x2e/+0x30/+0x2c/+0x04 and the
//         "Serialize failed reason is %s" assert idiom;
//       * a dual-path element loop over the SBList at this+0x08: on write it
//         walks with SBList::GoTo (0x005c8e40) and serialises each element; on
//         load it reads a type byte, allocates one of five element types via
//         operator new (0x006428b5) + their ctors, serialises and links it with
//         the inlined SBList insert (0x0059fb00 payload copy);
//       * a trailing reorder pass that re-walks the list and chains each
//         element's +0x4c to the next.
//
// STATUS (0x005843c0): PARKED as STUB — the binding is solid and the logic is
// reproduced, but the target cannot be made byte-exact at this compiler tier.
// The residual is a 4-byte stack-frame / EH-layout difference of the same family
// as RHGroundMark/RHTitbits/RHScript::GetScrollStatus:
//   * target: `sub esp,0x10` with exactly four frame slots at [esp+0x10]
//     (count), [esp+0x14] (type), [esp+0x18] (i), [esp+0x1c] (elem); the five
//     `new` EH trylevels are packed into the pushed-EH-state dword at [esp+0x28].
//   * ours:   `sub esp,0x14` — VC6 reserves a fifth 4-byte slot when the load
//     path contains the five-way `switch` of `new` expressions. Every [esp+N]
//     *and* the register allocation shift with it (e.g. the phase-1 list lands
//     in ebp instead of ebx), so reccmp scores 56.54%.
// * isolate-probe evidence (/O2 /GX): a single `new`
//     the same source shape gives the target's `sub esp,0x10`; removing the
//     switch gives `sub esp,0xc`; every probed five-way form
//     (switch/if-chain, with/without `default`, `elem` hoisted/initialised,
//     `int`/`unsigned char` type, serialize inside/after the cases,
//     virtual/non-virtual element dtor) gives `sub esp,0x14`.
//   * the load path genuinely emits five `operator new` calls (sizes
//     0x64/0x7c/0x74/0x68/0x9c) with five distinct EH states, so the extra slot
//     is VC6's bookkeeping for that switch, not a source-shape artefact we can
//     fold away. Kept as STUB so reccmp does not count it; the reconstruction
//     below is for reference.
//
// BINDING (0x00584980 -> RHSequence::SerializeStaticStuff(SBFile&)):
//   - Signals:
//       * the function writes the type-name tag "RHSequence::SerializeStaticStuff"
//         (string 0x006b7490) as its first act via the 0x005e1b70 helper;
//       * a single SBFile::Access check on the 4-byte global 0x006b7480, then
//         the "Serialize failed reason is %s" assert idiom — a serializer with
//         no loop, no `new`, no base call;
//       * the body never uses ecx as `this` (arg is `[esp+8]`), so Windows
//         emits it as a static member — declared `static` here.
//
// The `// STRING:` markers pin the literals to their original Game.exe
// addresses: the original is a fixed-base EXE, so its absolute string pointers
// carry no relocation records and reccmp cannot discover them by scanning.

#include "SBNullstr.h"
#include "RHSequence.h"
#include "RHSequenceGenericCalls.h"
#include "RHEngineSequenceStateCalls.h"
#include "RHScriptListCore.h"
#include "RHFastFindGridCore.h"
#include "RHActorGridCalls.h"
#include "RHScriptEngineCalls.h"
#include "RHMalignityQueryList.h"
#include "RHSequenceAppendCalls.h"
#include "RHUnk005fc3b0.h"

extern "C" int __cdecl rand();
struct RHUnkSectorGlobal;
extern RHUnkSectorGlobal *g_unk0x6c0a9c;

template<class T> inline T &RHSequenceField(void *object, unsigned offset)
{
    return *(T *)((char *)object + offset);
}

// STUB: GAME 0x00582640
bool RHUnk00582220::FUN_00582640(unsigned short &level, void *actor, int style, const SBGeoPoint2D &start, void *startArea, unsigned short startLayer, const SBGeoPoint2D &end, void *endArea, unsigned short endLayer, void *element, float distance, unsigned long flags, float scale)
{
    RHMalignityQueryList route;
    SBGeoPoint2D origin(start);
    SBGeoPoint2D destination(end);
    void *sprite = RHSequenceField<void *>(actor, 0x50);
    void *gate = RHSequenceField<void *>(sprite, 0xf4);
    if (gate)
    {
        if (RHSequenceField<bool>(sprite, 0xf8))
        {
            origin = RHSequenceField<SBGeoPoint2D>(gate, 0x20);
            startArea = RHSequenceField<void *>(gate, 0x10);
            startLayer = RHSequenceField<unsigned short>(gate, 0x16);
        }
        else
        {
            origin = RHSequenceField<SBGeoPoint2D>(gate, 0x18);
            startArea = RHSequenceField<void *>(gate, 0xc);
            startLayer = RHSequenceField<unsigned short>(gate, 0x14);
        }
    }
    if (endArea != startArea)
    {
        RHUnk00588530 *movement = new RHUnk00588530(level++, 2, actor, startArea, SBGeoPoint2D(), actor, 0.0f, 0);
        movement->m_98 = scale;
        ((RHUnk00585500 *)movement)->Unk(this);
    }
    unsigned short firstLevel = level;
    if (endArea == startArea)
    {
        RHUnk00588530 *movement = new RHUnk00588530(level++, 20, actor, style, destination, element, distance, flags);
        movement->m_98 = scale;
        ((RHUnk00585500 *)movement)->Unk(this);
        return true;
    }
    bool finalMove;
    bool found;
    if (RHSequenceField<unsigned long>(endArea, 0x30) & 0x1000)
    {
        finalMove = false;
        found = ((RHFastFindGrid *)g_unk0x6c0a9c)->FUN_004fa080((RHFastFindUniqueList &)route, (RHElementActor *)actor,
            origin, startArea, startLayer, RHSequenceField<RHFastFindPathGate *>(endArea, 0x58), (flags >> 1) & 1);
    }
    else
    {
        finalMove = true;
        found = ((RHActorGridCalls *)g_unk0x6c0a9c)->FUN_004f9a80(&route, (RHElementActor *)actor,
            origin, startArea, startLayer, destination, endArea, endLayer, 0);
    }
    if (!found)
    {
        if ((RHSequenceField<unsigned>(actor, 4) & 0xf) == 12)
            ((void (__fastcall *)(void *, void *, int, int, int))(*(void ***)actor)[0x104 / 4])(actor, 0, 14, 0, 255);
        route.clear();
        return false;
    }
    unsigned short count = route.Count();
    unsigned short firstSpecial = 0xffff;
    for (unsigned short index = 0; index < count; ++index)
    {
        route.GoTo(index);
        gate = *(void **)((char *)route.cursor + 8);
        if (RHSequenceField<int>(gate, 4) == 2)
        {
            firstSpecial = index;
            break;
        }
    }
    unsigned long currentFlags = flags;
    void *nextArea = endArea;
    for (unsigned short step = 0; step < count; ++step)
    {
        route.GoTo(step);
        gate = *(void **)((char *)route.cursor + 8);
        currentFlags = firstSpecial != 0xffff && step <= firstSpecial ? flags | 0x800 : flags;
        bool reverse = RHSequenceField<bool>(gate, 0x81);
        nextArea = RHSequenceField<void *>(gate, reverse ? 0x10 : 0xc);
        if (RHSequenceField<unsigned long>(startArea, 0x30) & 0x2000)
        {
            if (level != firstLevel)
            {
                RHUnk005866a0 *wait = new RHUnk005866a0(level++, 160, actor);
                wait->Unk00586ed0(2, 50);
                ((RHUnk00585500 *)wait)->Unk(this);
            }
            RHUnk005866a0 *wait = new RHUnk005866a0(level++, 160, actor);
            int first = rand() & 15;
            int second = rand() & 15;
            wait->Unk00586ed0(2, first + second);
            ((RHUnk00585500 *)wait)->Unk(this);
            RHUnk00588530 *movement;
            if (reverse)
                movement = new RHUnk00588530(level++, 25, actor, RHSequenceField<SBGeoPoint2D>(gate, 0x18), startArea,
                    (unsigned char)((const RHUnk005fc3b0 &)RHSequenceField<SBGeoPoint2D>(gate, 0x20).Unk005fc110(RHSequenceField<SBGeoPoint2D>(gate, 0x18))).FUN_005fcc50(1.0f), currentFlags);
            else
                movement = new RHUnk00588530(level++, 25, actor, RHSequenceField<SBGeoPoint2D>(gate, 0x20), startArea,
                    (unsigned char)((const RHUnk005fc3b0 &)RHSequenceField<SBGeoPoint2D>(gate, 0x18).Unk005fc110(RHSequenceField<SBGeoPoint2D>(gate, 0x20))).FUN_005fcc50(1.0f), currentFlags);
            movement->m_98 = scale;
            ((RHUnk00585500 *)movement)->Unk(this);
        }
        else
        {
            RHUnk00588530 *movement = new RHUnk00588530(level++, 20, actor, style,
                RHSequenceField<SBGeoPoint2D>(gate, reverse ? 0x18 : 0x20), 0, 0.0f, currentFlags);
            movement->m_98 = scale;
            ((RHUnk00585500 *)movement)->Unk(this);
            movement = new RHUnk00588530(level++, 2, actor, (void *)0,
                RHSequenceField<SBGeoPoint2D>(gate, reverse ? 0x18 : 0x20), actor, 10.0f, 0);
            movement->m_98 = scale;
            ((RHUnk00585500 *)movement)->Unk(this);
        }
        if (RHSequenceField<int>(gate, 4) == 1)
        {
            if ((RHSequenceField<unsigned>(actor, 4) & 0xf) == 12 && RHSequenceField<bool>(gate, 0x8c) &&
                ((RHScriptBatchCalls *)actor)->Unk0049d560(28))
            {
                RHUnk005866a0 *turn = new RHUnk005866a0(level++, 26, actor);
                turn->Unk00587010(8, RHSequenceField<SBGeoPoint2D>(gate, reverse ? 0x20 : 0x18));
                ((RHUnk00585500 *)turn)->Unk(this);
                RHUnk005866a0 *command = new RHUnk005866a0(level++, 10, actor);
                command->Unk00586ed0(36, (int)gate);
                ((RHUnk00585500 *)command)->Unk(this);
                return true;
            }
            if ((RHSequenceField<unsigned long>(nextArea, 0x30) & 0x200) && RHSequenceField<int>(nextArea, 0xf0) == 2)
            {
                RHUnk00588530 *movement = new RHUnk00588530(level++, 169, actor, nextArea, SBGeoPoint2D(), (void *)0, 0.0f, 0);
                movement->m_98 = scale;
                movement->m_7c = gate;
                ((RHUnk00585500 *)movement)->Unk(this);
            }
            RHUnk00588530 *movement = new RHUnk00588530(level++, 19, actor, style, 0);
            movement->m_7c = gate;
            movement->m_98 = scale;
            ((RHUnk00585500 *)movement)->Unk(this);
            movement = new RHUnk00588530(level++, 2, actor, (void *)0,
                RHSequenceField<SBGeoPoint2D>(gate, reverse ? 0x20 : 0x18), actor, 10.0f, 0);
            movement->m_98 = scale;
            ((RHUnk00585500 *)movement)->Unk(this);
        }
        else
        {
            RHUnk005866a0 *command = new RHUnk005866a0(level++, 83, actor);
            if (reverse)
            {
                command->Unk00586ed0(23, RHSequenceField<int>(gate, 0x8c));
                command->Unk00586ed0(24, RHSequenceField<int>(gate, 0x88));
            }
            else
            {
                command->Unk00586ed0(23, RHSequenceField<int>(gate, 0x88));
                command->Unk00586ed0(24, RHSequenceField<int>(gate, 0x8c));
            }
            ((RHUnk00585500 *)command)->Unk(this);
        }
        startArea = nextArea;
    }
    if (finalMove && !(RHSequenceField<unsigned long>(nextArea, 0x30) & 0x2000))
    {
        RHUnk00588530 *movement = new RHUnk00588530(level++, 20, actor, style, destination, element, distance, currentFlags);
        movement->m_98 = scale;
        ((RHUnk00585500 *)movement)->Unk(this);
    }
    if ((currentFlags & 4) && (RHSequenceField<unsigned long>(nextArea, 0x30) & 0x2000))
    {
        RHUnk00588530 *movement = new RHUnk00588530(level++, 20, actor, style, RHSequenceField<SBGeoPoint2D>(gate, 0x20), element, distance, currentFlags);
        movement->m_98 = scale;
        ((RHUnk00585500 *)movement)->Unk(this);
    }
    return true;
}

// FUNCTION: GAME 0x005823f0
bool RHEngineSequenceStateCalls::FUN_005823f0()
{
    int count = *(int *)((char *)this + 0x10);
    if (count)
    {
        if (*(unsigned short *)((char *)this + 0x32) > 0)
            return false;
        for (int index = count - 1; (short)index >= 0; --index)
        {
            switch (*(int *)((char *)((RHUnk0046eb30 *)((char *)this + 8))->Get((short)index) + 0x58))
            {
            case 2:
                return false;
            case 3:
            case 4:
                return false;
            }
        }
    }
    return true;
}

// The 4-byte global read/written by SerializeStaticStuff (original 0x006b7480).
// GLOBAL: GAME 0x006b7480
int g_unk0x6b7480;

inline void ClearRHSequenceElementRange(std::list<RHSequenceElement *> *list)
{
    typedef std::list<RHSequenceElement *>::iterator Iterator;
    typedef Iterator (RHUnk0046eb30::*Begin)();
    Iterator (std::list<RHSequenceElement *>::*eraseRange)(Iterator, Iterator) = &std::list<RHSequenceElement *>::erase;
    (list->*eraseRange)((((RHUnk0046eb30 *)list)->*(Begin)&RHUnk0046eb30::FUN_0046eb80)(), list->end());
}

inline void RHSequenceElementList::clear()
{
    iterator position = begin();
    iterator last = end();
    iterator (std::list<RHSequenceElement *>::*eraseOne)(iterator) = &std::list<RHSequenceElement *>::erase;
    while (position != last)
        (this->*eraseOne)(position++);
    m_dirty = true;
}

inline void RHSequenceElementList::DeleteAll()
{
    for (m_cursor = begin(); m_cursor != end(); ++m_cursor)
        delete (RHUnkSequenceOrder *)*m_cursor;
    clear();
}

// STUB: GAME 0x00584b40
inline RHSequenceElementList::~RHSequenceElementList()
{
    for (m_cursor = begin(); m_cursor != end(); ++m_cursor)
        delete (RHUnkSequenceOrder *)*m_cursor;
    ClearRHSequenceElementRange(this);
}

inline RHSequenceElementListStorage::~RHSequenceElementListStorage()
{
    ClearRHSequenceElementRange(this);
}

// TEMPLATE: GAME 0x0044e8b0 FOLDED
// ?erase@?$list@PAVRHSequenceElement@@V?$allocator@PAVRHSequenceElement@@@std@@@std@@QAE?AViterator@12@V312@0@Z

// TEMPLATE: GAME 0x0046eb30 FOLDED
// ?erase@?$list@PAVRHSequenceElement@@V?$allocator@PAVRHSequenceElement@@@std@@@std@@QAE?AViterator@12@V312@@Z

// TEMPLATE: GAME 0x0046eb30 FOLDED
// ?erase@?$list@PAVRHUnkSequenceOrder@@V?$allocator@PAVRHUnkSequenceOrder@@@std@@@std@@QAE?AViterator@12@V312@@Z

// FUNCTION: GAME 0x00582220
RHUnk00582220::RHUnk00582220()
{
    m_04 = g_unk0x6b7480++;
    m_2c = 0;
    m_2e = 0;
    m_30 = 0;
    m_32 = 0;
    m_34 = 0;
}

// FUNCTION: GAME 0x00582280
void *RHUnk00582220::FUN_00582280(unsigned int flags)
{
    this->~RHUnk00582220();
    if (flags & 1)
        operator delete(this);
    return this;
}

// Parked: list teardown inline depth and range-erase scheduling differ.
// STUB: GAME 0x005822a0
RHUnk00582220::~RHUnk00582220()
{
    m_elements.DeleteAll();
}

// STUB: GAME 0x005843c0
bool RHSequence::Serialize(SBFile &file, bool bArg)
{
    // STRING: GAME 0x6b7484
    RHSerializeName(file, "RHSequence");

    if (file.m_bLoading)
    {
        RHUnkListSeq &list = RHSequenceGlobalList();
        list.insert(list.end(), this);
        list.m_flag10 = 1;
    }

    if (file.Access(&m_34, 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHsequence.cpp", 1234, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_2e, 2) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHsequence.cpp", 1235, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_30, 2) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHsequence.cpp", 1236, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_2c, 2) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHsequence.cpp", 1237, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_04, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHsequence.cpp", 1238, "Serialize failed reason is %s", reason);
        return false;
    }

    unsigned int count;
    unsigned char type;
    RHSequenceElement *elem;
    if (!file.m_bLoading)
    {
        count = m_list.m_count;
        if (file.Access(&count, 4) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHsequence.cpp", 1244, "Serialize failed reason is %s", reason);
            return false;
        }
    }
    else
    {
        if (file.Access(&count, 4) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHsequence.cpp", 1248, "Serialize failed reason is %s", reason);
            return false;
        }
    }

    for (unsigned int i = 0; i < count; i++)
    {
        if (!file.m_bLoading)
        {
            m_list.GoTo(i);
            elem = m_list.m_cur->m_data;
            type = *((unsigned char *)elem + 4);
            if (file.Access(&type, 1) < 0)
            {
                SBString *err = file.GetError();
                const char *reason = err->m_chars ? err->m_chars : "";
                SBAssert(0, "P:\\Robin Hood\\RHsequence.cpp", 1261, "Serialize failed reason is %s", reason);
                return false;
            }
            elem->Serialize(file, bArg);
        }
        else
        {
            if (file.Access(&type, 1) < 0)
            {
                SBString *err = file.GetError();
                const char *reason = err->m_chars ? err->m_chars : "";
                SBAssert(0, "P:\\Robin Hood\\RHsequence.cpp", 1274, "Serialize failed reason is %s", reason);
                return false;
            }

            switch (type & 0xff)
            {
            case 0:
                elem = (RHSequenceElement *)new RHUnk00584d60();
                break;
            case 1:
                elem = new RHUnk586050();
                break;
            case 2:
                elem = (RHSequenceElement *)new RHUnk005866a0();
                break;
            case 3:
                elem = new RHUnk585e70();
                break;
            case 4:
                elem = (RHSequenceElement *)new RHUnk00588530();
                break;
            default:
                elem = 0;
                break;
            }

            elem->Serialize(file, bArg);

            m_list.insert(m_list.end(), elem);
            m_list.m_count++;
            m_list.m_valid = 1;
            *(RHSequence **)((char *)elem + 0x54) = this;
        }
    }

    if (file.Access(&m_32, 2) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHsequence.cpp", 1317, "Serialize failed reason is %s", reason);
        return false;
    }

    if (bArg)
        return true;
    if (!file.m_bLoading)
        return true;
    if (count == 0)
        return true;
    if (count <= 1)
        return true;

    RHSequenceElement *prev = m_list.m_head->m_next->m_data;
    for (unsigned int j = 1; j < count; j++)
    {
        m_list.GoTo(j);
        RHSequenceElement *cur = m_list.m_cur->m_data;
        *(RHSequenceElement **)((char *)prev + 0x4c) = cur;
        prev = cur;
    }

    return true;
}

// FUNCTION: GAME 0x00584980
bool RHSequence::SerializeStaticStuff(SBFile &file)
{
    // STRING: GAME 0x6b7490
    RHSerializeName(file, "RHSequence::SerializeStaticStuff");

    if (file.Access(&g_unk0x6b7480, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0,
                 // STRING: GAME 0x6b7460
                 "P:\\Robin Hood\\RHsequence.cpp",
                 1353,
                 "Serialize failed reason is %s",
                 reason);
        return false;
    }
    return true;
}

// FUNCTION: GAME 0x005849e0
void RHSequence::Unk005849e0(RHSequenceElement *first, RHSequenceElement *second)
{
    for (unsigned short index = m_2c - 1; ; --index)
    {
        ((RHUnk0046eb30 *)&m_list)->GoToInline(index);
        if (m_list.m_cur->m_data == first)
        {
            ++m_30;
            break;
        }
        if (index == 0)
            break;
    }
}

// Force emission: a non-inline member function defined here is emitted into the
// object; this out-of-line call keeps the serialisers in the build.
void RHSequence::Emit(SBFile &file)
{
    Serialize(file, false);
    SerializeStaticStuff(file);
}
