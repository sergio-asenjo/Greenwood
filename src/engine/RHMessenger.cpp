// RHMessenger.cpp — translation unit with __FILE__ evidence at 0x005472d0
// ("P:\Robin Hood\RHMessenger.cpp", symbols/functions-by-file.tsv).
//
// BINDING (0x005472d0 -> RHMessenger::Serialize(SBFile&)):
//   - TU:        rhmessenger.cpp (embedded __FILE__ string 0x006b118c).
//   - Class:     RHMessenger (symbols/oracle-correlation.tsv:
//                rhmessenger -> class RHMessenger, 25 methods).
//   - Signature: RHMessenger::Serialize(SBFile&) (symbols/mac-RH.txt:3082).
//   - Signals:
//       * the first act writes the tag "RHMessenger" (string 0x006b11ac) via
//         0x005e1b70 — the name matches the TU's class;
//       * a run of SBFile::Access checks at +0x1a/1 (line 873), +0x28/1 (876),
//         +0x2a/2 (877), +0xa2/2 (880), each with the "Serialize failed reason
//         is %s" idiom;
//       * a `file.m_version >= 0x11` gate: the read path Accesses +0x17/1 at
//         line 884, the below-version path stores 0 into the +0x17 byte;
//       * the file.m_bLoading gate (mov al,[esi+4]; test; je) then calls
//         0x00547560 on `this` in BOTH paths; on the loading path a
//         `file.m_version >= 0x2a` gate guards a final Access of a 1-byte
//         stack local at line 900;
//       * no loop and no `new`.
//
// BINDING (0x00547460 -> RHMessenger::SerializeLockUser(SBFile&)):
//   - TU:        rhmessenger.cpp (same embedded __FILE__ string 0x006b118c).
//   - Class:     RHMessenger; the Mac map's rhmessenger.cpp lists exactly two
//                methods, Serialize and SerializeLockUser
//                (symbols/mac-functions-by-file.tsv:128-129); Serialize is
//                already bound above, so the remaining __FILE__ function is
//                SerializeLockUser.
//   - Signals:   the body serialises the "lock user" flag at this+0x23; on the
//                loading path a fetched byte that differs from +0x23 dispatches
//                a lock/unlock action carrying the 0x1c/0x1d constant selected
//                by `byte == 0`; on the saving path it writes +0x23 directly.
//                Both Access failures use the "Serialize failed reason is %s"
//                idiom at lines 924 / 935.
//
// The `// STRING:` markers pin the literals to their original Game.exe
// addresses: the original is a fixed-base EXE, so its absolute string pointers
// carry no relocation records and reccmp cannot discover them by scanning.
// ("" 0x006773d0 and the format 0x006a7390 are annotated once, in
// src/RHSword.cpp; references here resolve to the same pooled entities.)

#include "SBNullstr.h"
#include "RHMessenger.h"
#include <algorithm>
#include <vector>
#include <math.h>

DECOMP_SIZE_ASSERT(RHMessenger, 0xac)
DECOMP_SIZE_ASSERT(RHMessengerTrailStorage, 0x24)

// TEMPLATE: GAME 0x0044e8b0 FOLDED
// ?erase@?$list@MV?$allocator@M@std@@@std@@QAE?AViterator@12@V312@0@Z

// TEMPLATE: GAME 0x0046eb30 FOLDED
// ?erase@?$list@MV?$allocator@M@std@@@std@@QAE?AViterator@12@V312@@Z

// TEMPLATE: GAME 0x004e52a0 FOLDED
// ??1?$SBListCursorStorage@V?$list@MV?$allocator@M@std@@@std@@@@QAE@XZ

// TEMPLATE: GAME 0x0057c9c0 FOLDED
// ??Eiterator@?$list@MV?$allocator@M@std@@@std@@QAE?AV012@H@Z

// TEMPLATE: GAME 0x005c9010 FOLDED
// ?_Advance@std@@YAXAAViterator@?$list@MV?$allocator@M@std@@@1@HUbidirectional_iterator_tag@1@@Z

template<class T> T &RHMessengerField(void *object, unsigned offset)
{
    return *(T *)((char *)object + offset);
}


// GLOBAL: GAME 0x006c0c4c
RHMessenger *g_unk0x006c0c4c = 0;

#include "SBDrawViewport.h"
#include "SBDrawManagerCore.h"
#include "SBResourceManager.h"

DECOMP_SIZE_ASSERT(std::vector<RHReceiverInterface *>, 0x10)
DECOMP_SIZE_ASSERT(SBGeoPolyLine2DList, 0x28)
DECOMP_SIZE_ASSERT(SBGeoPoint2D, 0x08)
DECOMP_SIZE_ASSERT(SBDrawViewport, 0x18)

extern RHUnk005ef320 *g_unk0x6c11d0;
class RHMapResources;
extern RHMapResources *g_unk0x006c1840;

inline unsigned short RHMessengerPalette(unsigned short intensity, int level, int redShift, int greenShift, int redMask, int greenMask)
{
    unsigned short strength = (unsigned short)((intensity * level) >> 5);
    unsigned short red = (unsigned short)((strength * 31 << redShift) & redMask);
    unsigned short green = (unsigned short)((strength * 9 << greenShift) & greenMask);
    return red | green;
}

// STUB: GAME 0x00545bd0
RHMessenger::RHMessenger()
    : m_flag14(false), m_flag15(false), m_flag16(false), m_flag17(false),
      m_flag18(false), m_flag19(false), m_flag1a(false), m_flag1b(false),
      m_flag22(false), m_flag23(false), m_flag24(false)
{
    SBDrawViewport viewport;
    m_flagAA = false;
    m_action = 0;
    m_savedAction = 0;
    m_valueA8 = 0;
    m_position.Set(0.0f, 0.0f);
    m_previous.Set(0.0f, 0.0f);
    m_savedPosition.Set(0.0f, 0.0f);
    m_flag20 = false;
    m_flag21 = false;
    m_flag28 = false;
    m_flag1c = false;
    m_flag1d = false;
    m_flag1f = false;
    m_stationaryCount = 0;
    unsigned long surface;
    ((SBResourceManager *)g_unk0x006c1840)->FUN_00600920(0x46, 0, surface);
    ((SBDrawManager *)g_unk0x6c11d0)->FUN_005e5a00(surface, viewport, 0);
    m_patternHeight = viewport.m_height;
    m_pattern = new unsigned short[m_patternHeight * 32];
    m_mask = new unsigned short[m_patternHeight];
    for (unsigned short i = 0; i < m_patternHeight; ++i)
        m_mask[i] = 31 - (viewport.GetPixel(0, i) & 31);
    if (((SBDrawManager *)g_unk0x6c11d0)->m_10c == 16)
    {
        int level = 1;
        int remaining = 32;
        do
        {
            for (unsigned short row = 0; row < m_patternHeight; ++row)
            {
                m_pattern[(level - 1) * m_patternHeight + row] = RHMessengerPalette(m_mask[row], level, 6, 2, 0xf800, 0x7e0);
            }
            ++level;
        } while (--remaining);
    }
    else
    {
        int level = 1;
        int remaining = 32;
        do
        {
            for (unsigned short row = 0; row < m_patternHeight; ++row)
            {
                m_pattern[(level - 1) * m_patternHeight + row] = RHMessengerPalette(m_mask[row], level, 5, 1, 0x7c00, 0x3e0);
            }
            ++level;
        } while (--remaining);
    }
    ((SBDrawManager *)g_unk0x6c11d0)->FUN_005e5ea0(viewport);
}

// FUNCTION: GAME 0x00545ef0
RHMessenger::~RHMessenger()
{
    g_unk0x006c0c4c = 0;
    delete[] m_pattern;
    delete[] m_mask;
}

// FUNCTION: GAME 0x00545ed0
void *RHMessenger::FUN_00545ed0(unsigned flags)
{
    this->~RHMessenger();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x00546050
RHMessenger *RHUnk00546050()
{
    if (!g_unk0x006c0c4c)
        g_unk0x006c0c4c = new RHMessenger;
    return g_unk0x006c0c4c;
}

#include "RHEngine.h"
#include "RHElementActorPC.h"
#include "RHSectorActorList.h"
#include "RHWidgetPortraitClass.h"
#include "SBGeoPolyLine2DList.h"
#include "SBThreadedInput.h"
#include "RHMouseMessage.h"
#include "RHActorMessage.h"
#include "RHUnk0053bf20.h"
#include <list>

typedef std::list<float> RHMessengerTrail;

inline RHSectorActorList &RHMessengerSelection(RHEngine *engine)
{
    return RHMessengerField<RHSectorActorList>(engine, 0x49f8);
}

inline unsigned RHMessengerSelectionCount(RHEngine *engine)
{
    return RHMessengerField<unsigned>(engine, 0x4a00);
}

inline bool RHMessengerIsSelected(RHEngine *engine, RHElementActor *actor)
{
    if (actor)
        return RHMessengerSelection(engine).Unk004b8f80(actor, true) != -1;
    return RHMessengerSelectionCount(engine) != 0;
}

inline bool RHMessengerActionLocked(RHElementActorPC *actor, unsigned short slot)
{
    char *flags = (char *)actor + slot;
    return flags[0x508] || flags[0x50b];
}

// STUB: GAME 0x005460c0
void RHMessenger::RHUnk005460c0(RHUnk5490f0 &message)
{
    int type = message.m_type;
    int value = message.m_value;
    if (m_unk23)
    {
        switch (type)
        {
        case 1:
            switch (message.m_unk0c)
            {
            case 1:
            case 3:
                return;
            }
        }
    }

    int command;
    switch (type)
    {
    case 2:
        command = message.m_unk0c;
        switch (command)
        {
        case 5:
            RHMessengerField<bool>(this, 0x20) = true;
            RHMessengerField<unsigned short>(this, 0x26) = (unsigned short)value;
            RHMessengerField<unsigned short>(this, 0xa8) = RHMessengerField<unsigned short>(this, 0xa2);
            break;
        case 6:
            if (!RHMessengerField<bool>(this, 0x20))
                return;
            RHMessengerField<bool>(this, 0x20) = false;
            break;
        case 9:
            RHMessengerField<bool>(this, 0x20) = true;
            RHMessengerField<unsigned short>(this, 0x26) = (unsigned short)value;
            break;
        case 0x15:
        {
            RHEngine *engine = g_pEngine;
            if (RHMessengerSelectionCount(engine) != 1)
                return;
            RHSectorActorList &selection = RHMessengerSelection(engine);
            selection.Unk005c8e40(0);
            RHElementActorPC *actor = (RHElementActorPC *)selection.CurrentValue();
            int action = RHMessengerField<int>(actor->m_5fc, 0x48 + message.m_value * 4);
            if (!action)
                return;
            if (RHMessengerField<RHWidgetPortrait *>(actor, 0x4ec)->FUN_005d9a20(message.m_value) != true)
                return;
            RHUnk005460c0((RHUnk5490f0 &)RHUnk00549250(0x16, actor, action));
            return;
        }
        case 0x16:
        case 0x19:
        {
            RHEngine *engine = g_pEngine;
            RHElementActorPC *actor = (RHElementActorPC *)((RHUnk00549250 &)message).m_10;
            if (!actor)
            {
                unsigned count = RHMessengerSelectionCount(engine);
                for (unsigned i = 0; i < count; ++i)
                {
                    RHSectorActorList &selection = RHMessengerSelection(engine);
                    selection.Unk005c8e40((unsigned short)i);
                    RHElementActorPC *selected = (RHElementActorPC *)selection.CurrentValue();
                    if (value && RHMessengerActionLocked(selected, (unsigned short)selected->FUN_0049d590(value)))
                        continue;
                    if (!RHMessengerIsSelected(engine, (RHElementActor *)selected))
                        selected->FUN_0049d680(value);
                    else
                        RHMessengerField<unsigned short>(this, 0xa2) = (unsigned short)value;
                }
            }
            else
            {
                if (value && RHMessengerActionLocked(actor, (unsigned short)actor->FUN_0049d590(value)))
                    break;
                if (!RHMessengerIsSelected(engine, (RHElementActor *)actor))
                {
                    actor->FUN_0049d680(value);
                    break;
                }
                if (value && RHMessengerSelectionCount(engine) > 1)
                {
                    RHUnk005460c0((RHUnk5490f0 &)RHUnk00549250(0x12, 0));
                    RHUnk005460c0((RHUnk5490f0 &)RHUnk00549250(0xd, actor));
                }
                RHMessengerField<unsigned short>(this, 0xa2) = (unsigned short)value;
                if (RHMessengerField<unsigned short>(this, 0xa2))
                    RHMessengerField<bool>(this, 0x16) = false;
            }
            break;
        }
        case 0x17:
            if (!RHMessengerField<unsigned short>(this, 0xa2) || RHMessengerField<unsigned short>(this, 0xa2) != value)
                return;
            if (!value)
                message.m_value = RHMessengerField<unsigned short>(this, 0xa2);
            RHMessengerField<unsigned short>(this, 0xa2) = 0;
            break;
        case 0x1e:
            if (RHMessengerField<unsigned short>(this, 0xa2))
                RHMessengerField<bool>(this, 0x16) = true;
            break;
        case 0x1f:
            if (RHMessengerField<unsigned short>(this, 0xa2))
                RHMessengerField<bool>(this, 0x16) = false;
            break;
        case 0x1a:
        {
            RHElementActorPC *actor = (RHElementActorPC *)((RHUnk00549250 &)message).m_10;
            if (RHMessengerField<unsigned short>(this, 0xa2) == actor->FUN_0049d5c0(value) &&
                RHMessengerIsSelected(g_pEngine, (RHElementActor *)actor) && RHMessengerActionLocked(actor, (unsigned short)value))
                RHUnk005460c0((RHUnk5490f0 &)RHUnk00549250(0x19, 0, 0));
            break;
        }
        case 0xd:
        case 0xe:
        {
            RHEngine *engine = g_pEngine;
            RHElementActorPC *actor = (RHElementActorPC *)((RHUnk00549250 &)message).m_10;
            if (actor)
            {
                if (!engine->FUN_004c7f50(actor))
                    return;
                RHMessengerField<bool>(this, 0x16) = false;
                RHMessengerField<unsigned short>(this, 0xa4) = 0;
                RHMessengerField<unsigned short>(this, 0xa6) = 0;
                if (RHMessengerField<bool>(this, 0x14))
                {
                    if (command == 0xd)
                    {
                        RHUnk005460c0((RHUnk5490f0 &)RHUnk00549250(0xf, actor));
                        return;
                    }
                    RHUnk005460c0((RHUnk5490f0 &)RHUnk00549250(0x10, actor));
                    return;
                }
                if (RHMessengerIsSelected(engine, (RHElementActor *)actor))
                {
                    RHUnk005460c0((RHUnk5490f0 &)RHUnk00549250(0x13, actor));
                    RHMessengerField<bool>(actor, 0x604) = false;
                    RHMessengerField<bool>(actor, 0x48a) = true;
                }
                break;
            }
            unsigned count = (unsigned char)engine->PCCount();
            for (unsigned i = 0; i < count; ++i)
                RHUnk005460c0((RHUnk5490f0 &)RHUnk00549250(0xf, g_pEngine->m_pcs.First()[(unsigned char)i]));
            return;
        }
        case 0xf:
        case 0x10:
            if (!g_pEngine->FUN_004c7f50(((RHUnk00549250 &)message).m_10))
                return;
            RHMessengerField<bool>(this, 0x16) = false;
            break;
        case 0x12:
        {
            RHElementActorPC *actor = (RHElementActorPC *)((RHUnk00549250 &)message).m_10;
            if (!RHMessengerIsSelected(g_pEngine, (RHElementActor *)actor))
                return;
            RHMessengerField<bool>(this, 0x16) = false;
            if (!actor || RHMessengerSelectionCount(g_pEngine) == 1)
                RHMessengerField<unsigned short>(this, 0xa2) = 0;
            break;
        }
        case 0xc:
        {
            RHElementActor *actor = (RHElementActor *)((RHUnk00549250 &)message).m_10;
            RHEngine *engine = g_pEngine;
            if (RHMessengerSelectionCount(engine) == 1 &&
                (actor ? RHMessengerSelection(engine).Find(actor) != -1 : RHMessengerSelectionCount(engine) != 0))
                RHUnk005460c0((RHUnk5490f0 &)RHUnk00549250(0x16, 0, 0));
            break;
        }
        }
        break;
    case 1:
        switch (message.m_unk0c)
        {
        case 3:
            switch (value & 0x49)
            {
            case 0x40:
                if (!RHMessengerField<bool>(this, 0x1f))
                {
                    RHMessengerField<SBGeoPolyLine2DList>(this, 0x5c).FUN_00610ac0();
                    RHMessengerTrail &intensities = RHMessengerField<RHMessengerTrail>(this, 0x2c);
                    RHMessengerTrail::iterator (RHMessengerTrail::*erase)(RHMessengerTrail::iterator, RHMessengerTrail::iterator) =
                        &RHMessengerTrail::erase;
                    (intensities.*erase)(intensities.begin(), intensities.end());
                    RHMessengerField<bool>(this, 0x3c) = true;
                }
                RHMessengerField<bool>(this, 0x1f) = true;
                break;
            case 8:
            {
                RHEngine *engine = g_pEngine;
                unsigned count = RHMessengerSelectionCount(engine);
                if (RHMessengerField<unsigned short>(this, 0xa4) && !count)
                    return;
                for (unsigned i = 0; i < count; ++i)
                {
                    RHSectorActorList &selection = RHMessengerSelection(engine);
                    selection.Unk005c8e40((unsigned short)i);
                    RHElementActorPC *selected = (RHElementActorPC *)selection.CurrentValue();
                    if (RHMessengerField<unsigned short>(this, 0xa4))
                    {
                        unsigned short slot = (unsigned short)selected->FUN_0049d590(RHMessengerField<unsigned short>(this, 0xa4));
                        if (slot == 0xffff || RHMessengerActionLocked(selected, slot))
                            return;
                    }
                }
                RHMessengerField<unsigned short>(this, 0xa2) = RHMessengerField<unsigned short>(this, 0xa4);
                RHMessengerField<bool>(this, 0x20) = RHMessengerField<bool>(this, 0x21);
                RHMessengerField<SBGeoPoint2D>(this, 0x84) = RHMessengerField<SBGeoPoint2D>(this, 0x94);
                RHMessengerField<bool>(this, 0x1f) = false;
                break;
            }
            case 1:
                RHMessengerField<bool>(this, 0x1f) = false;
                if (RHMessengerField<bool>(this, 0xaa))
                    RHMessengerField<bool>(this, 0xaa) = false;
                else
                {
                    RHMessengerField<unsigned short>(this, 0xa4) = RHMessengerField<unsigned short>(this, 0xa2);
                    RHMessengerField<bool>(this, 0x21) = RHMessengerField<bool>(this, 0x20);
                    RHMessengerField<SBGeoPoint2D>(this, 0x94) = RHMessengerField<SBGeoPoint2D>(this, 0x84);
                }
                break;
            }
            switch (value & 0x92)
            {
            case 2:
            case 0x10:
                RHMessengerField<unsigned short>(this, 0xa4) = 0;
                break;
            }
            break;
        case 2:
            if (value != 2)
            {
                if (value == 1)
                {
                    if (RHMessengerField<unsigned short>(this, 0x2a) < 6)
                        ++RHMessengerField<unsigned short>(this, 0x2a);
                }
                else if (RHMessengerField<unsigned short>(this, 0x2a) > 0)
                    --RHMessengerField<unsigned short>(this, 0x2a);
            }
            return;
        case 1:
            if (RHMessengerField<bool>(this, 0x1f) && !RHMessengerField<bool>(this, 0x15) &&
                !RHMessengerField<unsigned short>(this, 0xa2) && g_pEngine->FUN_004e1890())
            {
                SBGeoPolyLine2DList &trail = RHMessengerField<SBGeoPolyLine2DList>(this, 0x5c);
                trail.FUN_00610a60(RHMessengerField<SBGeoPoint2D>(this, 0x84));
                RHMessengerTrail &intensities = RHMessengerField<RHMessengerTrail>(this, 0x2c);
                RHMessengerTrail::iterator (RHMessengerTrail::*insert)(RHMessengerTrail::iterator, const float &) =
                    &RHMessengerTrail::insert;
                (intensities.*insert)(intensities.end(), 112.5f);
                RHMessengerField<bool>(this, 0x3c) = true;
                if ((unsigned)((RHUnk0053bf20 *)&trail)->FUN_0053bf20() > 350)
                {
                    trail.FUN_00610b10();
                    RHMessengerTrail::iterator (RHMessengerTrail::*erase)(RHMessengerTrail::iterator) = &RHMessengerTrail::erase;
                    (intensities.*erase)(intensities.begin());
                    RHMessengerField<bool>(this, 0x3c) = true;
                }
            }
            RHMessengerField<SBGeoPoint2D>(this, 0x8c) = RHMessengerField<SBGeoPoint2D>(this, 0x84);
            RHMessengerField<SBGeoPoint2D>(this, 0x84) = ((RHUnk00549120 &)message).m_10;
            break;
        }
        break;
    case 0:
        command = message.m_unk0c;
        switch (command)
        {
        case 0xf:
            RHMessengerField<bool>(this, 0x16) = true;
            RHMessengerField<unsigned short>(this, 0xa6) = RHMessengerField<unsigned short>(this, 0xa2);
            break;
        case 0x12:
            if (!RHMessengerField<bool>(this, 0x16))
                return;
            RHMessengerField<bool>(this, 0x16) = false;
            break;
        case 0xd:
            RHMessengerField<bool>(this, 0x14) = true;
            break;
        case 0x10:
            RHMessengerField<bool>(this, 0x14) = false;
            break;
        case 0x1a:
            RHMessengerField<bool>(this, 0x19) = true;
            break;
        case 0xe:
            RHMessengerField<bool>(this, 0x15) = true;
            break;
        case 0x1b:
            RHMessengerField<bool>(this, 0x19) = false;
            break;
        case 0x11:
            RHMessengerField<bool>(this, 0x15) = false;
            break;
        case 0x15:
            RHMessengerField<bool>(this, 0x18) = !RHMessengerField<bool>(this, 0x18);
            break;
        case 0x27:
            RHMessengerField<bool>(this, 0x17) = !RHMessengerField<bool>(this, 0x17);
            message.m_value = RHMessengerField<bool>(this, 0x17);
            break;
        case 0x2e:
            Reset();
            break;
        case 0x1c:
            m_unk23 = true;
            break;
        case 0x1d:
            m_unk23 = false;
            break;
        case 0x1e:
            RHMessengerField<bool>(this, 0x28) = true;
            RHMessengerField<unsigned short>(this, 0x2a) = 0;
            g_inputAlternate = true;
            break;
        case 0x1f:
            RHMessengerField<bool>(this, 0x28) = false;
            g_inputAlternate = false;
            break;
        case 0x18:
            RHMessengerField<bool>(this, 0x24) = true;
            break;
        case 9:
            RHMessengerField<unsigned short>(this, 0x26) = (unsigned short)value;
            break;
        case 0xc:
            RHUnk005460c0((RHUnk5490f0 &)RHUnk00549250(6, 0, 1));
            break;
        case 0x13:
            RHMessengerField<bool>(this, 0x1c) = !RHMessengerField<bool>(this, 0x1c);
            break;
        case 0x17:
            RHMessengerField<bool>(this, 0x22) = !RHMessengerField<bool>(this, 0x22);
            break;
        }
        break;
    }

    std::vector<RHReceiverInterface *> &receivers = RHMessengerField<std::vector<RHReceiverInterface *> >(this, 4);
    for (std::vector<RHReceiverInterface *>::iterator it = receivers.begin(); it != receivers.end(); ++it)
        (*it)->v00(message);

    switch (type)
    {
    case 2:
        command = message.m_unk0c;
        switch (command)
        {
        case 0xd:
        case 0xe:
            RHUnk005460c0(RHUnk5490f0(0x21));
            RHUnk005460c0((RHUnk5490f0 &)RHUnk00549250(7, 0));
            RHMessengerField<unsigned short>(this, 0xa8) = 0;
            break;
        case 0xf:
        case 0x10:
            RHUnk005460c0(RHUnk5490f0(0x21));
            RHUnk005460c0((RHUnk5490f0 &)RHUnk00549250(7, 0));
            RHMessengerField<unsigned short>(this, 0xa8) = 0;
            break;
        case 0x12:
            RHUnk005460c0(RHUnk5490f0(0x21));
            RHUnk005460c0((RHUnk5490f0 &)RHUnk00549250(7, 0));
            RHMessengerField<unsigned short>(this, 0xa8) = 0;
            break;
        case 6:
            RHUnk005460c0((RHUnk5490f0 &)RHUnk00549250(0x16, 0, RHMessengerField<unsigned short>(this, 0xa8)));
            break;
        }
        break;
    case 0:
        command = message.m_unk0c;
        switch (command)
        {
        case 0xf:
            RHUnk005460c0((RHUnk5490f0 &)RHUnk00549250(0x16, 0, 0));
            break;
        case 0x12:
            RHUnk005460c0((RHUnk5490f0 &)RHUnk00549250(0x16, 0, RHMessengerField<unsigned short>(this, 0xa6)));
            break;
        case 0x22:
            RHUnk005460c0(RHUnk5490f0(0x21));
            break;
        case 0x25:
        case 0x28:
            RHUnk005460c0(RHUnk5490f0(0x2e));
            break;
        }
        break;
    }
}

// FUNCTION: GAME 0x00547080
void RHMessenger::Subscribe(RHReceiverInterface *receiver)
{
    std::vector<RHReceiverInterface *> &receivers = RHMessengerField<std::vector<RHReceiverInterface *> >(this, 4);
    receivers.push_back(receiver);
}

// FUNCTION: GAME 0x00547230
void RHMessenger::Unsubscribe(RHReceiverInterface *receiver)
{
    std::vector<RHReceiverInterface *> &receivers = RHMessengerField<std::vector<RHReceiverInterface *> >(this, 4);
    std::vector<RHReceiverInterface *>::iterator position = receivers.begin();
    RHReceiverInterface **last;
    memcpy(&last, (char *)this + 0x0c, sizeof(last));
    for (; position != last; ++position)
    {
        if (*position == receiver)
        {
            receivers.erase(position);
            return;
        }
    }
}

// FUNCTION: GAME 0x00547280
void RHMessenger::FUN_00547280()
{
    SBGeoPoint2D &previous = RHMessengerField<SBGeoPoint2D>(this, 0x8c);
    SBGeoPoint2D &position = RHMessengerField<SBGeoPoint2D>(this, 0x84);
    if (position == previous)
    {
        int count = RHMessengerField<int>(this, 0x9c);
        RHMessengerField<bool>(this, 0x24) = false;
        RHMessengerField<int>(this, 0x9c) = count + 1;
    }
    else
    {
        RHMessengerField<int>(this, 0x9c) = 0;
        previous = position;
        RHMessengerField<bool>(this, 0x24) = false;
    }
}

// FUNCTION: GAME 0x005472d0
bool RHMessenger::Serialize(SBFile &file)
{
    // STRING: GAME 0x6b11ac
    RHSerializeName(file, "RHMessenger");

    if (file.Access(&m_unk1a, 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0,
                 // STRING: GAME 0x6b118c
                 "P:\\Robin Hood\\RHMessenger.cpp",
                 873,
                 "Serialize failed reason is %s",
                 reason);
        return false;
    }

    if (file.Access(&m_unk28, 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHMessenger.cpp", 876, "Serialize failed reason is %s", reason);
        return false;
    }

    if (file.Access(&m_unk2a, 2) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHMessenger.cpp", 877, "Serialize failed reason is %s", reason);
        return false;
    }

    if (file.Access(&m_unka2, 2) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHMessenger.cpp", 880, "Serialize failed reason is %s", reason);
        return false;
    }

    if (file.m_version >= 0x11)
    {
        if (file.Access(&m_unk17, 1) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHMessenger.cpp", 884, "Serialize failed reason is %s", reason);
            return false;
        }
    }
    else
    {
        m_unk17 = 0;
    }

    if (file.m_bLoading)
    {
        Reset();

        if (file.m_version < 0x2a)
        {
            char scratch;
            if (file.Access(&scratch, 1) < 0)
            {
                SBString *err = file.GetError();
                const char *reason = err->m_chars ? err->m_chars : "";
                SBAssert(0, "P:\\Robin Hood\\RHMessenger.cpp", 900, "Serialize failed reason is %s", reason);
                return false;
            }
        }
    }
    else
    {
        Reset();
    }

    return true;
}

// FUNCTION: GAME 0x00547460
bool RHMessenger::SerializeLockUser(SBFile &file)
{
    if (file.m_bLoading)
    {
        char loaded;
        if (file.Access(&loaded, 1) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0,
                     // The __FILE__ literal 0x006b118c is annotated once, in
                     // RHMessenger::Serialize above; this reference resolves to
                     // the same pooled entity. ("" 0x006773d0 and the format
                     // 0x006a7390 are owned by src/RHSword.cpp.)
                     "P:\\Robin Hood\\RHMessenger.cpp",
                     924,
                     "Serialize failed reason is %s",
                     reason);
            return false;
        }

        if (loaded != m_unk23)
        {
            RHUnk005460c0(RHUnk5490f0(loaded == 0 ? 0x1d : 0x1c));
        }
    }
    else
    {
        if (file.Access(&m_unk23, 1) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHMessenger.cpp", 935, "Serialize failed reason is %s", reason);
            return false;
        }
    }

    return true;
}

struct RHScriptNode
{
    RHScriptNode *next;
    RHScriptNode *prev;
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
};

#include "SBGeoPolyLine2DList.h"

struct RHMessengerFlags
{
    char m_00[0x14]; // 0x00
    bool m_14;       // 0x14
    bool m_15;       // 0x15
    bool m_16;       // 0x16
    char m_17[2];    // 0x17
    bool m_19;       // 0x19
    char m_1a;       // 0x1a
    bool m_1b;       // 0x1b
    bool m_1c;       // 0x1c
    bool m_1d;       // 0x1d
    char m_1e;       // 0x1e
    bool m_1f;       // 0x1f
    char m_20[4];    // 0x20
    bool m_24;       // 0x24
};

// FUNCTION: GAME 0x00547560
void RHMessenger::Reset()
{
    RHMessengerFlags &flags = *(RHMessengerFlags *)this;
    flags.m_14 = false;
    flags.m_15 = false;
    flags.m_16 = false;
    flags.m_19 = false;
    flags.m_1b = false;
    flags.m_1c = flags.m_1d;
    flags.m_1d = false;
    flags.m_1f = false;
    flags.m_24 = false;
    RHMessengerField<SBGeoPolyLine2DList>(this, 0x5c).FUN_00610ac0();
    RHScriptNode *head = RHMessengerField<RHScriptNode *>(this, 0x30);
    RHScriptNode *node = head->next;
    while (node != head)
    {
        RHScriptNode *current = node;
        node = node->next;
        ((RHUnk0046eb30 *)((char *)this + 0x2c))->erase(RHScriptIter(current));
    }
    RHMessengerField<bool>(this, 0x3c) = true;
    RHMessengerField<SBGeoPoint2D>(this, 0x84) = *(const SBGeoPoint2D *)&SBThreadedInput::mpointPosition;
    RHMessengerField<SBGeoPoint2D>(this, 0x8c) = *(const SBGeoPoint2D *)&SBThreadedInput::mpointPosition;
    RHMessengerField<int>(this, 0x94) = 0;
    RHMessengerField<int>(this, 0x98) = 0;
    RHMessengerField<int>(this, 0x9c) = 0;
    RHMessengerField<bool>(this, 0xa0) = false;
    RHMessengerField<bool>(this, 0xaa) = false;
}

#include "SBGeoVector2D.h"
#include "RHUnk005fc3b0.h"

#include "SBGeoBoundingBox2DCore.h"

SBGeoVector2D FUN_005fc580(const SBGeoVector2D &point, float factor);

// STUB: GAME 0x00547600
int RHMessenger::EvaluateMouseWay(const SBGeoPoint2D &point, const SBGeoVector2D &direction)
{
    unsigned long count = (unsigned long)((RHUnk0053bf20 *)&m_way)->FUN_0053bf20();
    if (count <= 1)
        return 0;
    SBGeoPoint2D first(m_way.FUN_00610cb0(0));
    SBGeoPoint2D last(m_way.FUN_00610cb0(count - 1));
    SBGeoVector2D middle = FUN_005fc580(SBGeoVector2D(first.Unk005fc190(SBGeoVector2D(last))), 0.5f);
    SBGeoBoundingBox2D bounds;
    SBGeoPoint2D center;
    SBGeoPoint2D current;
    SBGeoVector2D normal = ((RHUnk005fc3b0 &)last.Unk005fc110(first)).FUN_005fc8f0(true, 1.0f).GetNormalized(1.0f);
    if (count > 2)
    {
        float minSum = 1000000000.0f;
        float maxSum = -1000000000.0f;
        float maxDifference = -1000000000.0f;
        float minDifference = 1000000000.0f;
        float negativeDistance = 0.0f;
        float positiveDistance = 0.0f;
        unsigned long minSumIndex;
        unsigned long maxSumIndex;
        unsigned long maxDifferenceIndex;
        unsigned long minDifferenceIndex;
        for (unsigned long i = 0; i < count; ++i)
        {
            current = m_way.FUN_00610cb0(i);
            float sum = current.m_x + current.m_y;
            float difference = current.m_x - current.m_y;
            float distance = current.Unk005fc110(first).FUN_005fc660(normal);
            if (distance > positiveDistance)
                positiveDistance = distance;
            else if (distance < -negativeDistance)
                negativeDistance = -distance;
            if (sum < minSum)
            {
                minSumIndex = i;
                minSum = sum;
            }
            if (sum > maxSum)
            {
                maxSumIndex = i;
                maxSum = sum;
            }
            if (difference > maxDifference)
            {
                maxDifferenceIndex = i;
                maxDifference = difference;
            }
            if (difference < minDifference)
            {
                minDifferenceIndex = i;
                minDifference = difference;
            }
        }
        bool closed = m_way.FUN_006107e0();
        bounds.FUN_00607e50(&m_way);
        center = bounds.FUN_00608f40();
        int result;
        if (!closed)
        {
            result = CheckThrustHI(point, first, last, center, minSumIndex, maxSumIndex, maxDifferenceIndex, minDifferenceIndex);
            if (result)
                return result;
            result = CheckThrustFG(point, first, last, negativeDistance, positiveDistance);
            if (result)
                return result;
            result = CheckThrustAB(point, direction, first, last);
            if (result)
                return result;
            result = CheckThrustDE(point, direction, first, last);
            if (result)
                return result;
        }
        else
        {
            result = CheckThrustC(minSumIndex, maxSumIndex, maxDifferenceIndex, minDifferenceIndex);
            if (result)
                return result;
            result = CheckThrustHI(point, first, last, center, minSumIndex, maxSumIndex, maxDifferenceIndex, minDifferenceIndex);
            if (result)
                return result;
        }
    }
    {
        SBGeoBoundingBox2D size;
        size.FUN_00607e50(&m_way);
        if (size.m_p1.m_x - size.m_p0.m_x < 10.0f && size.m_p1.m_y - size.m_p0.m_y < 10.0f)
            return 0;
    }
    return 1;
}

inline float RHMessengerLength(const SBGeoPoint2D &vector)
{
    return ((RHUnk005fc3b0 *)&vector)->Unk005fc6a0(1.0f);
}



// FUNCTION: GAME 0x00547f00
int RHMessenger::CheckThrustHI(const SBGeoPoint2D &a, const SBGeoPoint2D &b, const SBGeoPoint2D &c,
    const SBGeoPoint2D &d, unsigned long e, unsigned long f, unsigned long g, unsigned long h)
{
    SBGeoVector2D first = d.Unk005fc110(b);
    SBGeoVector2D second = d.Unk005fc110(c);
    if (fabs(first.FUN_005fca90(second, 1.0f)) < 1.5707963705062866)
    {
        if ((e <= g && g <= f && f <= h) || (g <= f && f <= h && h <= e) || (f <= h && h <= e && e <= g)
            || (h <= e && e <= g && g <= f))
            return 9;
        return 10;
    }
    return 0;
}

// FUNCTION: GAME 0x00548050
int RHMessenger::CheckThrustFG(const SBGeoPoint2D &a, const SBGeoPoint2D &b, const SBGeoPoint2D &c, float x, float y)
{
    float length = RHMessengerLength(c.Unk005fc110(b));
    if (x / length > 0.3f)
    {
        if (y / length <= 0.3f)
            return 7;
    }
    else if (y / length > 0.3f)
        return 8;
    return 0;
}







// FUNCTION: GAME 0x00548120
int RHMessenger::CheckThrustDE(const SBGeoPoint2D &a, const SBGeoVector2D &b, const SBGeoPoint2D &c,
    const SBGeoPoint2D &d)
{
    SBGeoVector2D first = d.Unk005fc110(c);
    RHUnk005fc3b0 direction;
    direction.FUN_005fc430(-b);
    float angle = direction.FUN_005fca90(first, 1.0f);
    if (angle > 0.785398185f && angle < 2.35619450f)
        return 6;
    if (angle < (-0.785398185f) && angle > (-2.35619450f))
        return 5;
    return 0;
}

// FUNCTION: GAME 0x00548280
int RHMessenger::CheckThrustAB(const SBGeoPoint2D &a, const SBGeoVector2D &b, const SBGeoPoint2D &c,
    const SBGeoPoint2D &d)
{
    SBGeoVector2D first = c.Unk005fc110(d);
    RHUnk005fc3b0 direction;
    direction.FUN_005fc430(-b);
    double angle = fabs(direction.FUN_005fca90(first, 1.0f));
    if (angle < 0.7853981852531433)
        return 3;
    if (angle > 2.35619455575943)
        return 2;
    return 0;
}

// FUNCTION: GAME 0x005483b0
int RHMessenger::CheckThrustC(unsigned long a, unsigned long b, unsigned long c, unsigned long d)
{
    unsigned long values[4];
    unsigned short index = 0;
    unsigned long minimum = 0xffffffff;
    unsigned long maximum = 0;
    bool ascending = a < b;
    values[0] = a;
    values[1] = b;
    values[2] = c;
    values[3] = d;
    for (unsigned short i = 0; i < 4; ++i)
    {
        if (ascending)
        {
            if (values[i] < minimum)
            {
                index = i;
                minimum = values[i];
            }
        }
        else if (values[i] > maximum)
        {
            index = i;
            maximum = values[i];
        }
    }
    for (unsigned short j = index; j < index + 3; ++j)
    {
        unsigned long current = values[j % 4];
        unsigned long next = values[(j + 1) % 4];
        if (current > next && ascending)
            return 0;
        if (current < next && !ascending)
            return 0;
    }
    return 4;
}

#include "RHPlayerProfileAccess.h"
#include "SBDrawViewport.h"

#include "RHPlayerProfileManagerStorage.h"
class RHUnk005ef320;
extern RHUnk005ef320 *g_unk0x6c11d0;

inline float RHMessengerHeight(char *config)
{
    return *(float *)(config + 8);
}

inline unsigned short RHMessengerBlend(unsigned short source, unsigned short destination, unsigned short strength,
    int redMask, int greenMask)
{
    unsigned short red = source & redMask;
    unsigned short green = source & greenMask;
    unsigned short blue = source & 0x1f;
    unsigned short targetRed = (((destination & redMask) * strength) >> 5) & redMask;
    unsigned short targetGreen = (((destination & greenMask) * strength) >> 5) & greenMask;
    unsigned short targetBlue = (((destination & 0x1f) * strength) >> 5) & 0x1f;
    unsigned long resultRed = targetRed + (unsigned long)red;
    if (resultRed >= (unsigned long)redMask)
        resultRed = redMask;
    unsigned long resultGreen = targetGreen + (unsigned long)green;
    if (resultGreen >= (unsigned long)greenMask)
        resultGreen = greenMask;
    unsigned long resultBlue = targetBlue + (unsigned long)blue;
    if (resultBlue >= 0x1f)
        resultBlue = 0x1f;
    return (unsigned short)(resultBlue | resultGreen | resultRed);
}

// STUB: GAME 0x00548480
void RHMessenger::DrawMouseTrailPattern(const SBGeoPoint2D &point, unsigned short strength, SBDrawViewport &viewport)
{
    char *config = ((RHUnk0055dbb0 *)g_unk0x006c0e48)->FUN_0055dbb0() + 0x50;
    short count = (short)(RHMessengerField<unsigned short>(this, 0x58) <
        RHMessengerHeight(config) - (unsigned short)point.m_y ?
        RHMessengerField<unsigned short>(this, 0x58) :
        RHMessengerHeight(((RHUnk0055dbb0 *)g_unk0x006c0e48)->FUN_0055dbb0() + 0x50) - (unsigned short)point.m_y);
    unsigned short level = strength * 32 / 100;
    if (!level)
        return;
    if (level > 32)
        level = 32;
    unsigned short *pattern = RHMessengerField<unsigned short *>(this, 0x50) +
        (level - 1) * RHMessengerField<unsigned short>(this, 0x58);
    unsigned long pitch = viewport.m_pitch >> 1;
    unsigned short *pixel = viewport.m_pixels + (unsigned short)point.m_y * pitch + (unsigned short)point.m_x;
    if (RHMessengerField<unsigned short>(g_unk0x6c11d0, 0x10c) == 16)
    {
        if (count <= 0)
            return;
        int remaining = count;
        int i = 0;
        do
        {
            unsigned short source = pattern[i];
            int blend = (32 - (unsigned short)((RHMessengerField<unsigned short *>(this, 0x54)[i] * level) >> 5)) * 2;
            if (blend > 32)
                blend = 32;
            *pixel = RHMessengerBlend(source, *pixel, (unsigned short)blend, 0xf800, 0x7e0);
            pixel += pitch;
            ++i;
        } while (--remaining);
    }
    else
    {
        if (count <= 0)
            return;
        int remaining = count;
        int i = 0;
        do
        {
            unsigned short source = pattern[i];
            int blend = (32 - (unsigned short)((RHMessengerField<unsigned short *>(this, 0x54)[i] * level) >> 5)) * 2;
            if (blend > 32)
                blend = 32;
            *pixel = RHMessengerBlend(source, *pixel, (unsigned short)blend, 0x7c00, 0x3e0);
            pixel += pitch;
            ++i;
        } while (--remaining);
    }
}

// Force emission: a non-inline member function defined here is emitted into the
// object; this out-of-line call keeps RHMessenger::Serialize and
// RHMessenger::SerializeLockUser in the build.
extern double g_unk0x00677d90;

// FUNCTION: GAME 0x00548800
void RHMessenger::DisplayMouseWay(unsigned short value)
{
    SBDrawViewport viewport;
    SBDrawManager *draw = (SBDrawManager *)g_unk0x6c11d0;
    unsigned short count = (unsigned short)(unsigned long)((RHUnk0053bf20 *)&m_way)->FUN_0053bf20();
    draw->FUN_005e5a00(0, viewport, 0);
    for (unsigned short i = 0; i < count; ++i)
    {
        SBGeoPoint2D current(m_way.FUN_00610cb0(i));
        float strength = m_trail.Value(i);
        if (i != count - 1 && (fabs(m_way.FUN_00610cb0(i + 1).m_x - current.m_x) > g_unk0x00677d90 ||
            fabs(m_way.FUN_00610cb0(i + 1).m_y - current.m_y) > 16.0))
        {
            float nextX = m_way.FUN_00610cb0(i + 1).m_x;
            float nextY = m_way.FUN_00610cb0(i + 1).m_y;
            if (fabs(nextX - current.m_x) * 16.0 > fabs(nextY - current.m_y))
            {
                float x1 = current.m_x;
                const float nextX = m_way.FUN_00610cb0(i + 1).GetX();
                float x2 = nextX;
                float y1 = current.m_y;
                const float nextY = m_way.FUN_00610cb0(i + 1).GetY();
                float y2 = nextY;
                float strength1 = strength;
                float strength2 = m_trail.Value(i + 1);
                SBGeoPoint2D sample;
                if (x1 > nextX)
                {
                    std::swap(x1, x2);
                    std::swap(y1, y2);
                    std::swap(strength1, strength2);
                    x1 += 1.0f;
                    x2 += 1.0f;
                }
                float yStep = (y2 - y1) / (x2 - x1);
                float strengthStep = (strength2 - strength1) / (x2 - x1);
                float sampleStrength = strength1;
                sample.Set(x1, y1);
                for (unsigned short x = (unsigned short)x1; x != (unsigned short)x2; ++x)
                {
                    sample.m_x = x;
                    DrawMouseTrailPattern(sample, (unsigned short)sampleStrength, viewport);
                    sample.m_y += yStep;
                    sampleStrength += strengthStep;
                }
            }
            else
            {
                float x1 = current.m_x;
                const float nextX = m_way.FUN_00610cb0(i + 1).GetX();
                float x2 = nextX;
                float y1 = current.m_y;
                const float nextY = m_way.FUN_00610cb0(i + 1).GetY();
                float y2 = nextY;
                float strength1 = strength;
                float strength2 = m_trail.Value(i + 1);
                SBGeoPoint2D sample;
                if (y1 > nextY)
                {
                    std::swap(x1, x2);
                    std::swap(y1, y2);
                    std::swap(strength1, strength2);
                    y1 += 1.0f;
                    y2 += 1.0f;
                }
                float xStep = (x2 - x1) * 16.0f / (y2 - y1);
                float strengthStep = (strength2 - strength1) * 16.0f / (y2 - y1);
                float sampleStrength = strength1;
                sample.Set(x1, y1);
                unsigned short y = (unsigned short)y1;
                for (; y < (unsigned short)y2; y += 16)
                {
                    sample.m_y = y;
                    DrawMouseTrailPattern(sample, (unsigned short)sampleStrength, viewport);
                    sample.m_x += xStep;
                    sampleStrength += strengthStep;
                }
                if (y > (unsigned short)y2)
                {
                    sample.m_y = y;
                    DrawMouseTrailPattern(sample, (unsigned short)sampleStrength, viewport);
                }
            }
        }
        else
            DrawMouseTrailPattern(m_way.FUN_00610cb0(i), (unsigned short)strength, viewport);
        if (strength > 100.0f)
            m_trail.MutableValue(i) = strength - 1.0f;
        else
        {
            float faded = strength - 1.0f / (1.0f > strength ? 1.0f : strength) * 300.0f;
            float remaining = faded > 0.0f ? faded : 0.0f;
            m_trail.MutableValue(i) = remaining;
        }
    }
    draw->FUN_005e5ea0(viewport);
}

void RHMessenger::Emit(SBFile &file)
{
    Subscribe(0);
    Unsubscribe(0);
    FUN_00547280();
    Serialize(file);
    SerializeLockUser(file);
}

#include "RHMouseMessage.h"

#include "RHActorMessage.h"


// FUNCTION: GAME 0x00549030
RHMessage::RHMessage(int type, int value) : m_type(type), m_value(value)
{
}

// FUNCTION: GAME 0x00549050
void *RHMessage::FUN_00549050(unsigned flags)
{
    this->~RHMessage();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x00549070
RHMessage::RHMessage(int type) : m_type(type), m_value(0)
{
}

// FUNCTION: GAME 0x00549090
RHMessage::~RHMessage()
{
}

// FUNCTION: GAME 0x005490a0
RHUnk5490f0::RHUnk5490f0(int command, int value) : RHMessage(0, value)
{
    m_unk0c = command;
}

// FUNCTION: GAME 0x005490d0
void *RHUnk5490f0::FUN_005490d0(unsigned flags)
{
    this->~RHUnk5490f0();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x005490f0
RHUnk5490f0::RHUnk5490f0(int value) : RHMessage(0)
{
    m_unk0c = value;
}

// FUNCTION: GAME 0x00549120
RHUnk00549120::RHUnk00549120(int value, const SBGeoPoint2D &point) : RHMessage(1), m_0c(value), m_10(point)
{
}

// FUNCTION: GAME 0x00549180
void *RHUnk00549120::FUN_00549180(unsigned flags)
{
    this->~RHUnk00549120();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x005491a0
RHUnk00549120::RHUnk00549120(int value, const SBGeoPoint2D &point, int extra)
    : RHMessage(1, extra), m_0c(value), m_10(point)
{
}

// FUNCTION: GAME 0x00549200
RHUnk00549120::~RHUnk00549120()
{
}

// FUNCTION: GAME 0x00549250
RHUnk00549250::RHUnk00549250(int command, void *actor) : RHMessage(2), m_0c(command), m_10(actor)
{
}

// FUNCTION: GAME 0x00549280
void *RHUnk00549250::FUN_00549280(unsigned flags)
{
    this->~RHUnk00549250();
    if (flags & 1)
        operator delete(this);
    return this;
}
