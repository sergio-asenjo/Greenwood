#include "SBNullstr.h"
#include "RHTitbits.h"
#include "RHEngine.h"
#include "SBGeoPoint2D.h"
#include "SBGeoBoundingBox2DCore.h"
#include "RHUnk005fc3b0.h"
#include "RHSpriteCore.h"
#include "RHMobileVectorArray.h"
#include "RHFrameHolder.h"
#include "RHCivilianSpriteView.h"
#include "RHMalignityActorCalls.h"
#include "RHPlayerProfileAccess.h"
#include "RHSoundCore.h"
#include <list>
#include <iterator>
#include <string.h>

class RHArtificialIntelligenceSoundCalls;
extern RHArtificialIntelligenceSoundCalls *g_unk0x006c1070;
#include "RHPlayerProfileManagerStorage.h"
extern float g_unk0x006774cc;

struct RHUnk005c9010Iterator;
void FUN_005c9010(RHUnk005c9010Iterator &, int, std::bidirectional_iterator_tag);

struct RHTitbitCursor : std::iterator<std::bidirectional_iterator_tag, RHTitbit>
{
    RHTitbitNode *node;
    RHTitbitCursor(RHTitbitNode *value = 0) : node(value) {}
    RHTitbitCursor &operator=(const RHTitbitCursor &other)
    {
        node = other.node;
        return *this;
    }
    RHTitbitCursor &AssignNode(RHTitbitNode *value)
    {
        *(RHTitbitNode *volatile *)&node = value;
        return *this;
    }
    RHTitbitCursor &operator++() { node = node->m_next; return *this; }
    RHTitbitCursor &operator--() { node = node->m_prev; return *this; }
    RHTitbit &operator*() { return node->m_data; }
};

template<bool rewind, bool outlined> class RHTitbitAccessMode
{
public:
    RHTitbitCursor Begin()
    {
        RHTitbitNode *head = ((RHTitbitList *)this)->m_head;
        RHTitbitNode *first = *(RHTitbitNode *volatile *)&head->m_next;
        return RHTitbitCursor(first);
    }
    RHTitbitCursor End()
    {
        RHTitbitNode *head = *(RHTitbitNode *volatile *)&((RHTitbitList *)this)->m_head;
        return RHTitbitCursor(head);
    }
    RHTitbit &Get(int index, bool removing = false)
    {
        int count = m_list.size();
        if (m_dirty)
        {
            if (index <= (count + 1) / 2)
            {
                std::bidirectional_iterator_tag category;
                if (rewind)
                    FUN_005c9010((RHUnk005c9010Iterator &)m_current.AssignNode(
                        *(RHTitbitNode *volatile *)&((RHTitbitList *)this)->m_head->m_next), index, category);
                else
                {
                    m_current = Begin();
                    FUN_005c9010((RHUnk005c9010Iterator &)m_current, index, category);
                }
            }
            else
            {
                m_current = End();
                std::bidirectional_iterator_tag category;
                FUN_005c9010((RHUnk005c9010Iterator &)m_current, index - count, category);
            }
            m_dirty = false;
            m_index = index;
        }
        else
        {
            int previous = m_index;
            if (index != previous)
            {
                if (index < previous)
                {
                    if (index < (previous + 1) / 2)
                    {
                        std::bidirectional_iterator_tag category;
                        if (removing)
                        {
                            m_current.node = (RHTitbitNode *)((RHUnk0046eb30 *)this)->FUN_0046eb80().node;
                            FUN_005c9010((RHUnk005c9010Iterator &)m_current, index, category);
                        }
                        else
                            FUN_005c9010((RHUnk005c9010Iterator &)m_current.AssignNode(
                                *(RHTitbitNode *volatile *)&((RHTitbitList *)this)->m_head->m_next), index, category);
                    }
                    else
                    {
                        std::bidirectional_iterator_tag category;
                        FUN_005c9010((RHUnk005c9010Iterator &)m_current, index - previous, category);
                    }
                }
                else if (index < (previous + count) / 2)
                {
                    if (removing || outlined)
                    {
                        std::bidirectional_iterator_tag category;
                        FUN_005c9010((RHUnk005c9010Iterator &)m_current, index - previous, category);
                    }
                    else
                        std::advance(m_current, index - previous);
                }
                else
                {
                    m_current = End();
                    if (removing)
                    {
                        std::bidirectional_iterator_tag category;
                        FUN_005c9010((RHUnk005c9010Iterator &)m_current, index - count, category);
                    }
                    else
                        std::advance(m_current, index - count);
                }
                m_index = index;
            }
        }
        return *m_current;
    }
    std::list<RHTitbit> m_list;
    RHTitbitCursor m_current;
    bool m_dirty;
    int m_index;
};

typedef RHTitbitAccessMode<false, false> RHTitbitAccess;

class RHMapResources;
extern RHMapResources *g_unk0x006c1840;
SBGeoVector2D FUN_005fc580(const SBGeoVector2D &, float);

DECOMP_SIZE_ASSERT(RHTitbits, 0xb0)
DECOMP_STATIC_ASSERT(offsetof(RHTitbits, m_sprite) == 4)
DECOMP_STATIC_ASSERT(offsetof(RHTitbits, m_counts) == 0x10)
DECOMP_STATIC_ASSERT(offsetof(RHTitbits, m_draw) == 0x70)
DECOMP_STATIC_ASSERT(offsetof(RHTitbits, m_bank) == 0x74)
DECOMP_STATIC_ASSERT(offsetof(RHTitbits, m_a0) == 0xa0)

// FUNCTION: GAME 0x005c2570
unsigned long RHTitbits::LoadFromResource()
{
    RHMobileVectorArray offsets;
    RHUnk005fc3b0 size;
    unsigned short count;
    SBResourceManager *resources = (SBResourceManager *)g_unk0x006c1840;
    m_sprite->FUN_005b73f0(0x26);
    unsigned long first = ((RHFrameHolder *)m_bank)->AddRowFromResource(resources, 0xd, count, (SBArray<SBGeoVector2D> &)offsets);
    m_sprite->FUN_005bb180(0, first, count, 2, 0, &offsets);
    first = ((RHFrameHolder *)m_bank)->AddRowFromResource(resources, 0xd, count, (SBArray<SBGeoVector2D> &)offsets);
    m_sprite->FUN_005bb180(1, first, count, 2, 0, &offsets);
    first = ((RHFrameHolder *)m_bank)->AddRowFromResource(resources, 0xc, count, (SBArray<SBGeoVector2D> &)offsets);
    m_sprite->FUN_005bb180(2, first, count, 2, 0, &offsets);
    first = ((RHFrameHolder *)m_bank)->AddRowFromResource(resources, 0xb, count, (SBArray<SBGeoVector2D> &)offsets);
    m_sprite->FUN_005bb180(3, first, count, 2, 0, &offsets);
    first = ((RHFrameHolder *)m_bank)->AddRowFromResource(resources, 0xa, count, (SBArray<SBGeoVector2D> &)offsets);
    m_sprite->FUN_005bb180(4, first, count, 2, 0, &offsets);
    first = ((RHFrameHolder *)m_bank)->AddRowFromResource(resources, 9, count, (SBArray<SBGeoVector2D> &)offsets);
    m_sprite->FUN_005bb180(5, first, count, 2, 0, &offsets);
    first = ((RHFrameHolder *)m_bank)->AddRowFromResource(resources, 0x10, count, (SBArray<SBGeoVector2D> &)offsets);
    m_sprite->FUN_005bb180(6, first, count, 2, 0, &offsets);
    first = ((RHFrameHolder *)m_bank)->AddRowFromResource(resources, 0xd, count, (SBArray<SBGeoVector2D> &)offsets);
    m_sprite->FUN_005bb180(7, first, count, 2, 0, &offsets);
    m_counts[0] = count;
    first = ((RHFrameHolder *)m_bank)->AddRowFromResource(resources, 0x20, count, (SBArray<SBGeoVector2D> &)offsets);
    m_sprite->FUN_005bb180(8, first, count, 2, 0, &offsets);
    m_counts[1] = count;
    first = ((RHFrameHolder *)m_bank)->AddRowFromResource(resources, 0x21, count, (SBArray<SBGeoVector2D> &)offsets);
    m_sprite->FUN_005bb180(9, first, count, 2, 0, &offsets);
    m_counts[2] = count;
    first = ((RHFrameHolder *)m_bank)->AddRowFromResource(resources, 0x21, count, (SBArray<SBGeoVector2D> &)offsets);
    m_sprite->FUN_005bb180(10, first, count, 2, 0, &offsets);
    m_counts[3] = count;
    first = ((RHFrameHolder *)m_bank)->AddRowFromResource(resources, 0x36, count, (SBArray<SBGeoVector2D> &)offsets);
    m_sprite->FUN_005bb180(11, first, count, 2, 0, &offsets);
    m_counts[4] = count;
    first = ((RHFrameHolder *)m_bank)->AddRowFromResource(resources, 0x37, count, (SBArray<SBGeoVector2D> &)offsets);
    m_sprite->FUN_005bb180(12, first, count, 2, 0, &offsets);
    first = ((RHFrameHolder *)m_bank)->AddRowFromResource(resources, 0x38, count, (SBArray<SBGeoVector2D> &)offsets);
    m_sprite->FUN_005bb180(13, first, count, 2, 0, &offsets);
    m_counts[5] = count;
    first = ((RHFrameHolder *)m_bank)->AddRowFromResource(resources, 0x39, count, (SBArray<SBGeoVector2D> &)offsets);
    m_sprite->FUN_005bb180(14, first, count, 2, 0, &offsets);
    m_counts[6] = count;
    first = ((RHFrameHolder *)m_bank)->AddRowFromResource(resources, 0x77, count, (SBArray<SBGeoVector2D> &)offsets);
    m_sprite->FUN_005bb180(15, first, count, 2, 0, &offsets);
    first = ((RHFrameHolder *)m_bank)->AddRowFromResource(resources, 0x78, count, (SBArray<SBGeoVector2D> &)offsets);
    m_sprite->FUN_005bb180(16, first, count, 2, 0, &offsets);
    first = ((RHFrameHolder *)m_bank)->AddRowFromResource(resources, 0x79, count, (SBArray<SBGeoVector2D> &)offsets);
    m_sprite->FUN_005bb180(17, first, count, 2, 0, &offsets);
    first = ((RHFrameHolder *)m_bank)->AddRowFromResource(resources, 0x7a, count, (SBArray<SBGeoVector2D> &)offsets);
    m_sprite->FUN_005bb180(18, first, count, 2, 0, &offsets);
    first = ((RHFrameHolder *)m_bank)->AddRowFromResource(resources, 0x76, count, (SBArray<SBGeoVector2D> &)offsets);
    m_sprite->FUN_005bb180(19, first, count, 2, 0, &offsets);
    first = ((RHFrameHolder *)m_bank)->AddRowFromResource(resources, 0xc8, count, (SBArray<SBGeoVector2D> &)offsets);
    m_sprite->FUN_005bb180(20, first, count, 2, 0, &offsets);
    m_counts[7] = count;
    first = ((RHFrameHolder *)m_bank)->AddRowFromResource(resources, 0xd0, count, (SBArray<SBGeoVector2D> &)offsets);
    m_sprite->FUN_005bb180(21, first, count, 2, 0, &offsets);
    first = ((RHFrameHolder *)m_bank)->AddRowFromResource(resources, 0xdc, count, (SBArray<SBGeoVector2D> &)offsets);
    m_sprite->FUN_005bb180(22, first, count, 2, 0, &offsets);
    first = ((RHFrameHolder *)m_bank)->AddRowFromResource(resources, 0xdd, count, (SBArray<SBGeoVector2D> &)offsets);
    m_sprite->FUN_005bb180(23, first, count, 2, 0, &offsets);
    first = ((RHFrameHolder *)m_bank)->AddRowFromResource(resources, 0xf9, count, (SBArray<SBGeoVector2D> &)offsets);
    m_sprite->FUN_005bb180(24, first, count, 2, 0, &offsets);
    first = ((RHFrameHolder *)m_bank)->AddRowFromResource(resources, 0xfa, count, (SBArray<SBGeoVector2D> &)offsets);
    m_sprite->FUN_005bb180(25, first, count, 2, 0, &offsets);
    first = ((RHFrameHolder *)m_bank)->AddRowFromResource(resources, 0x11c, count, (SBArray<SBGeoVector2D> &)offsets);
    m_sprite->FUN_005bb180(26, first, count, 2, 0, &offsets);
    first = ((RHFrameHolder *)m_bank)->AddRowFromResource(resources, 0x11d, count, (SBArray<SBGeoVector2D> &)offsets);
    m_sprite->FUN_005bb180(27, first, count, 2, 0, &offsets);
    first = ((RHFrameHolder *)m_bank)->AddRowFromResource(resources, 0x11e, count, (SBArray<SBGeoVector2D> &)offsets);
    m_sprite->FUN_005bb180(28, first, count, 2, 0, &offsets);
    first = ((RHFrameHolder *)m_bank)->AddRowFromResource(resources, 0x11f, count, (SBArray<SBGeoVector2D> &)offsets);
    m_sprite->FUN_005bb180(29, first, count, 2, 0, &offsets);
    first = ((RHFrameHolder *)m_bank)->AddRowFromResource(resources, 0x120, count, (SBArray<SBGeoVector2D> &)offsets);
    m_sprite->FUN_005bb180(30, first, count, 2, 0, &offsets);
    first = ((RHFrameHolder *)m_bank)->AddRowFromResource(resources, 0x121, count, (SBArray<SBGeoVector2D> &)offsets);
    m_sprite->FUN_005bb180(31, first, count, 2, 0, &offsets);
    first = ((RHFrameHolder *)m_bank)->AddRowFromResource(resources, 0x122, count, (SBArray<SBGeoVector2D> &)offsets);
    m_sprite->FUN_005bb180(32, first, count, 2, 0, &offsets);
    first = ((RHFrameHolder *)m_bank)->AddRowFromResource(resources, 0x123, count, (SBArray<SBGeoVector2D> &)offsets);
    m_sprite->FUN_005bb180(33, first, count, 2, 0, &offsets);
    first = ((RHFrameHolder *)m_bank)->AddRowFromResource(resources, 0x124, count, (SBArray<SBGeoVector2D> &)offsets);
    m_sprite->FUN_005bb180(34, first, count, 2, 0, &offsets);
    first = ((RHFrameHolder *)m_bank)->AddRowFromResource(resources, 0x125, count, (SBArray<SBGeoVector2D> &)offsets);
    m_sprite->FUN_005bb180(35, first, count, 2, 0, &offsets);
    first = ((RHFrameHolder *)m_bank)->AddRowFromResource(resources, 0x126, count, (SBArray<SBGeoVector2D> &)offsets);
    m_sprite->FUN_005bb180(36, first, count, 2, 0, &offsets);
    first = ((RHFrameHolder *)m_bank)->AddRowFromResource(resources, 0x127, count, (SBArray<SBGeoVector2D> &)offsets);
    m_sprite->FUN_005bb180(37, first, count, 2, 0, &offsets);
    typedef unsigned long (RHUnkFXDraw::*CreateSurface)(unsigned short, unsigned short, int, bool);
    m_surface = (((RHUnkFXDraw *)m_draw)->*reinterpret_cast<CreateSurface>(&RHUnkFXDraw::Unk005e4ed0))(
        ((RHCivilianSpriteView *)m_sprite)->FUN_005bdef0(), ((RHCivilianSpriteView *)m_sprite)->FUN_005bdf20(), 0, false);
    m_mask = (((RHUnkFXDraw *)m_draw)->*reinterpret_cast<CreateSurface>(&RHUnkFXDraw::Unk005e4ed0))(
        ((RHCivilianSpriteView *)m_sprite)->FUN_005bdef0(), ((RHCivilianSpriteView *)m_sprite)->FUN_005bdf20(), 0, false);
    size.FUN_005fc430(FUN_005fc580(SBGeoVector2D((float)((RHCivilianSpriteView *)m_sprite)->FUN_005bdef0(),
        (float)((RHCivilianSpriteView *)m_sprite)->FUN_005bdf20()), 0.5f));
    m_sprite->AssignBox(SBGeoBoundingBox2D(-size, size));
    m_sprite->AssignOffset(size);
    m_a0 = g_pEngine->FUN_004d2340(15);
    return 0;
}

// FUNCTION: GAME 0x005c2ec0
unsigned long RHTitbits::AddTitbit(const RHUnk00613e90 &position, unsigned short layer, RHtitbitKind kind,
    RHElement *element, unsigned short subtype, RHElementActorPC *pc, bool shadow, unsigned long id)
{
    RHTitbit titbit;
    if (!((RHUnk0055dbb0 *)g_unk0x006c0e48)->FUN_0055dbb0()[0x53] && (kind == 5 || kind == 6 || kind == 7))
        return -1;
    titbit.m_10 = (int)pc;
    titbit.m_0c = (int)element;
    titbit.m_sub = position;
    titbit.m_08 = 0;
    titbit.m_06 = 0;
    titbit.m_04 = subtype;
    titbit.m_0a = 0;
    titbit.m_00 = kind;
    titbit.m_28 = 0;
    titbit.m_2c = id != -1 ? id : m_ac++;
    if (kind == 4 && subtype == 0)
        return -1;
    if (element)
    {
        char *sprite = *(char **)((char *)element + 0x50);
        titbit.m_u14.m_14s = *(unsigned short *)(sprite + 0xde);
    }
    else
    {
        titbit.m_u14.m_14s = layer;
        if (layer == 0xffff)
            titbit.m_u14.m_14s = 0;
    }
    if (element && kind == 1)
        RemoveUnconsciousStarsIf((RHElementActor *)element);
    else if (kind == 15)
    {
        if (((RHMalignityActorCalls *)element)->V168())
            titbit.m_04 = 0;
        else
        {
            char *type = *(char **)((char *)element + 0x5fc);
            if (strcmp(((std::string *)(type + 4))->c_str(), "LittleJohn") == 0)
                titbit.m_04 = 1;
            else if (strcmp(((std::string *)(type + 4))->c_str(), "WillScarlet") == 0)
                titbit.m_04 = 2;
            else if (strcmp(((std::string *)(type + 4))->c_str(), "Friar Tuck") == 0)
                titbit.m_04 = 3;
            else if (strcmp(((std::string *)(type + 4))->c_str(), "Stuteley") == 0)
                titbit.m_04 = 4;
            else if (strcmp(((std::string *)(type + 4))->c_str(), "LadyMarian") == 0)
                titbit.m_04 = 5;
            else if (strcmp(((std::string *)(type + 4))->c_str(), "MerryManA") == 0)
                titbit.m_04 = 6;
            else if (strcmp(((std::string *)(type + 4))->c_str(), "MerryManB") == 0)
                titbit.m_04 = 7;
            else if (strcmp(((std::string *)(type + 4))->c_str(), "MerryManC") == 0)
                titbit.m_04 = 8;
        }
    }
    float &depth = *(float *)&titbit.m_24;
    switch (kind)
    {
    case 0:
        titbit.m_sub.z += 0.1f;
    case 5:
    case 6:
    case 7:
    case 11:
        depth = position.y + 0.01f;
        break;
    case 1:
    case 2:
    case 8:
    case 9:
    case 10:
    case 13:
    case 14:
    case 15:
    case 16:
        depth = (titbit.m_0c ? *(float *)(*(char **)((char *)titbit.m_0c + 0x50) + 0x1c4) : position.y) + 0.01f;
        break;
    case 4:
        if (titbit.m_0c)
            depth = *(float *)(*(char **)((char *)titbit.m_0c + 0x50) + 0x1c4) + 1000.1f;
        else
            depth = position.y + 1000.1f;
        break;
    case 3:
        if (titbit.m_0c)
            depth = *(float *)(*(char **)((char *)titbit.m_0c + 0x50) + 0x1c4) + 0.01f;
        else
            depth = position.y + 0.01f;
        break;
    case 12:
        break;
    }
    RHTitbitAccess &list = *(RHTitbitAccess *)&m_list;
    list.m_list.push_back(titbit);
    list.m_dirty = true;
    if (shadow)
    {
        depth -= g_unk0x006774cc;
        titbit.m_00 = 17;
        list.m_list.push_back(titbit);
        list.m_dirty = true;
    }
    if (kind == 0)
        ((RHSound *)g_unk0x006c1070)->FUN_005a8070(0x5c4, SBGeoPoint2D(position.x, position.y - position.z), 9);
    return titbit.m_2c;
}

// Parked: second cached traversal is outlined and leaves the frame four bytes short.
// STUB: GAME 0x005c3440
bool RHTitbits::RemoveQuickActionTitbitsFor(RHElementActorPC *actor, unsigned short action)
{
    unsigned long id = *(unsigned long *)((char *)actor + 0x538 + action * 4);
    if (id == -1)
        return false;
    bool removed = false;
    unsigned short count = m_list.m_count;
    for (int index = count - 1; count != 0; --count, --index)
    {
        RHTitbitAccess &list = *(RHTitbitAccess *)&m_list;
        if (list.Get(index, true).m_2c == id)
        {
            removed = true;
            list.Get(index, true);
            ((RHUnk0046eb30 *)&list)->erase(RHScriptIter((RHScriptNode *)list.m_current.node));
            list.m_dirty = true;
        }
    }
    return removed;
}

// Parked: duplicate traversal outlining and dirty-path cursor scheduling differ.
// STUB: GAME 0x005c3680
bool RHTitbits::FUN_005c3680()
{
    bool removed = false;
    for (short index = ((std::list<RHTitbit> *)&m_list)->size() - 1; index != -1; --index)
    {
        RHTitbit entry;
        entry = ((RHTitbitAccess *)&m_list)->Get(index, true);
        if (entry.m_00 == 8)
        {
            removed = true;
            RHTitbitAccess &list = *(RHTitbitAccess *)&m_list;
            ((RHTitbitAccessMode<true, false> *)&list)->Get(index, true);
            ((RHUnk0046eb30 *)&list)->erase(*(RHScriptIter *)&list.m_current);
            list.m_dirty = true;
        }
    }
    return removed;
}

// FUNCTION: GAME 0x005c38b0
bool RHTitbits::RemoveUnconsciousStarsIf(RHElementActor *actor)
{
    bool removed = false;
    for (unsigned short i = ((std::list<RHTitbit> *)&m_list)->size(); i != 0; --i)
    {
        int index = i - 1;
        RHTitbit entry;
        entry = m_list.Item(index);
        if (entry.m_00 == 1 && entry.m_0c == (int)actor && !*(bool *)((char *)actor + 0x1ce))
        {
            removed = true;
            RHTitbitAccess &list = *(RHTitbitAccess *)&m_list;
            ((RHTitbitAccessMode<false, true> *)&list)->Get(index, false);
            RHTitbitNode *node = list.m_current.node;
            node->m_prev->m_next = node->m_next;
            node->m_next->m_prev = node->m_prev;
            ::operator delete(node);
            int remaining = ((RHTitbitList *)&list)->m_count - 1;
            list.m_dirty = true;
            ((RHTitbitList *)&list)->m_count = remaining;
        }
    }
    return removed;
}

// Parked: list/file register allocation and cursor scheduling remain different.
// STUB: GAME 0x005c3a60
bool RHTitbits::Serialize(SBFile &file)
{
    unsigned int count;
    unsigned int i;
    RHTitbit elem;

    // STRING: GAME 0x6b8bfc
    RHSerializeName(file, "RHTitbits");

    if (file.Access(&m_ac, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0,
                 // STRING: GAME 0x6b8bd8
                 "P:\\Robin Hood\\RHtitbit.cpp",
                 621,
                 "Serialize failed reason is %s",
                 reason);
        return false;
    }

    if (!file.m_bLoading)
    {
        count = m_list.m_count;
        if (file.Access(&count, 4) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHtitbit.cpp", 626, "Serialize failed reason is %s", reason);
            return false;
        }
    }
    else
    {
        RHTitbitList &list = m_list;
        typedef RHTitbitIterator (RHTitbitList::*Erase)(RHTitbitIterator, RHTitbitIterator);
        (list.*(Erase)&RHTitbitList::Clear)(RHTitbitIterator(list.m_head->m_next), RHTitbitIterator(list.m_head));
        list.m_valid = 1;
        if (file.Access(&count, 4) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHtitbit.cpp", 631, "Serialize failed reason is %s", reason);
            return false;
        }
        list.Resize(count);
        m_a4 = 0xf;
        m_a8 = 10.0f;
    }

    RHTitbitNode *node;
    for (i = 0; i < count; i++)
    {
        if (!file.m_bLoading)
        {
            RHTitbitList &list = m_list;
            list.At(i);
            node = list.m_cur;
            elem = node->m_data;
        }

        if (file.Access(&elem.m_00, 4) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHtitbit.cpp", 647, "Serialize failed reason is %s", reason);
            return false;
        }
        if (file.Access(&elem.m_0a, 2) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHtitbit.cpp", 648, "Serialize failed reason is %s", reason);
            return false;
        }
        if (file.Access(&elem.m_08, 2) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHtitbit.cpp", 649, "Serialize failed reason is %s", reason);
            return false;
        }
        if (file.Access(&elem.m_06, 2) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHtitbit.cpp", 650, "Serialize failed reason is %s", reason);
            return false;
        }
        if (file.Access(&elem.m_04, 2) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHtitbit.cpp", 651, "Serialize failed reason is %s", reason);
            return false;
        }
        if (file.Access(&elem.m_24, 4) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHtitbit.cpp", 652, "Serialize failed reason is %s", reason);
            return false;
        }
        if (file.Access(&elem.m_24, 4) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHtitbit.cpp", 653, "Serialize failed reason is %s", reason);
            return false;
        }
        if (file.Access(&elem.m_u14.m_14s, 2) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHtitbit.cpp", 654, "Serialize failed reason is %s", reason);
            return false;
        }
        if (file.Access(&elem.m_28, 1) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHtitbit.cpp", 655, "Serialize failed reason is %s", reason);
            return false;
        }
        if (file.Access(&elem.m_2c, 4) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHtitbit.cpp", 656, "Serialize failed reason is %s", reason);
            return false;
        }

        g_pEngine->SerializeElementPointer(file, *(RHElement **)(&elem.m_0c));
        g_pEngine->SerializeNestedB(file, &elem.m_10);
        ((RHUnk005df510 *)((char *)&elem + 0x1c))->Serialize(file);

        if (file.m_bLoading)
        {
            m_list.Seek(i);
            m_list.m_cur->m_data = elem;
        }
    }

    return true;
}

// FUNCTION: GAME 0x005c72a0
void RHTitbits::FUN_005c72a0()
{
    if (m_a4 <= 0)
        m_a4 = 15;
    else
        --m_a4;
    m_a8 += 1.0f;
    if (m_a8 > 10.0f)
        m_a8 -= 10.0f;
    m_00 = 0;
    for (short index = ((std::list<RHTitbit> *)&m_list)->size() - 1; index >= 0; --index)
    {
        RHTitbit &entry = m_list.Item(index);
        float &depth = *(float *)&entry.m_24;
        switch (entry.m_00)
        {
        case 8:
            depth = *(float *)(*(char **)((char *)entry.m_0c + 0x50) + 0x1c4) - 0.01f;
            break;
        case 15:
            depth = *(float *)(*(char **)((char *)entry.m_0c + 0x50) + 0x1c4) + 0.01f;
            break;
        case 1: case 2: case 13: case 14:
            if (entry.m_0c)
                depth = *(float *)(*(char **)((char *)entry.m_0c + 0x50) + 0x1c4) + 0.01f;
            break;
        case 9: case 16:
            depth = *(float *)(*(char **)((char *)entry.m_0c + 0x50) + 0x1c4) + 0.01f;
            break;
        case 3: case 17:
            if (entry.m_0c)
                depth = *(float *)(*(char **)((char *)entry.m_0c + 0x50) + 0x1c4) - 0.01f;
            break;
        }
    }
    m_list.Sort();
}

// FUNCTION: GAME 0x005c77f0
void RHTitbits::SetBlinking(RHElementActorPC *actor, unsigned short action, bool blinking)
{
    unsigned long id = *(unsigned long *)((char *)actor + 0x538 + action * 4);
    if (id == -1)
        return;
    unsigned count = m_list.m_count;
    for (int index = 0; (unsigned)index < count; ++index)
    {
        RHTitbit &entry = ((RHTitbitAccessMode<true, false> *)&m_list)->Get(index, false);
        if (entry.m_2c == id)
            *(bool *)&entry.m_28 = blinking;
    }
}

// FUNCTION: GAME 0x005c7970
void RHTitbits::ResetBlinking()
{
    unsigned count = m_list.m_count;
    for (int index = 0; (unsigned)index < count; ++index)
        *(bool *)&((RHTitbitAccess *)&m_list)->Get(index).m_28 = false;
}

// FUNCTION: GAME 0x005c7fb0
short RHTitbits::FUN_005c7fb0(unsigned long id)
{
    RHTitbit value;
    unsigned count = m_list.m_count;
    for (int index = 0; (unsigned)index < count; ++index)
    {
        RHTitbit &entry = ((RHTitbitAccess *)&m_list)->Get(index);
        if (entry.m_2c == id)
            return entry.m_04;
    }
    return -1;
}

// Parked: VC6 outlines the second cached traversal, changing frame and branch layout.
// STUB: GAME 0x005c8120
void RHTitbits::FUN_005c8120(int kind, RHElement *element)
{
    for (int index = 0; (unsigned)index < (unsigned)m_list.m_count; ++index)
    {
        RHTitbitAccess &list = *(RHTitbitAccess *)&m_list;
        RHTitbit &entry = list.Get(index, true);
        if (entry.m_00 == kind && entry.m_0c == (int)element)
        {
            list.Get(index, true);
            ((RHUnk0046eb30 *)&list)->erase(RHScriptIter((RHScriptNode *)list.m_current.node));
            list.m_dirty = true;
            --index;
        }
    }
}

// FUNCTION: GAME 0x005c8340
bool RHTitbits::FUN_005c8340(int kind, RHElement *element)
{
    for (int index = 0; (unsigned)index < (unsigned)m_list.m_count; ++index)
    {
        RHTitbit &entry = ((RHTitbitAccess *)&m_list)->Get(index);
        if (entry.m_00 == kind && entry.m_0c == (int)element)
            return true;
    }
    return false;
}

#include "RHMapBox.h"

class SBUIInputFieldDrawUnk
{
public:
    SBUIInputFieldDrawUnk();
    bool FUN_00614bf0(void *, std::wstring *, const SBGeoPoint2D &, unsigned);
    unsigned short FUN_00614230(void *, std::wstring *, const SBGeoBoundingBox2D &, unsigned, unsigned, unsigned);
    std::wstring m_00;
    unsigned m_10;
    char m_14;
    unsigned m_18;
    RHMapBox m_1c;
};

// FUNCTION: GAME 0x005c84a0
bool RHTitbits::RenderText(const std::wstring &text, const SBGeoBoundingBox2D &box, unsigned long flags) const
{
    SBUIInputFieldDrawUnk draw;
    draw.FUN_00614230(*(void *const *)((const char *)this + 0x78), (std::wstring *)&text, box, flags, 0, 1);
    return true;
}

// FUNCTION: GAME 0x005c8570
bool RHTitbits::RenderText(const std::wstring &text, const SBGeoPoint2D &point) const
{
    SBUIInputFieldDrawUnk draw;
    SBGeoPoint2D offset;
    void *outline = *(void *const *)((const char *)this + 0x7c);
    if (outline)
    {
        offset = point;
        offset.FUN_005fc1e0(SBGeoVector2D(-1.0f, -1.0f));
        draw.FUN_00614bf0(*(void *const *)((const char *)this + 0x7c), (std::wstring *)&text, offset, 1);
        offset = point;
        offset.FUN_005fc1e0(SBGeoVector2D(-1.0f, 1.0f));
        draw.FUN_00614bf0(*(void *const *)((const char *)this + 0x7c), (std::wstring *)&text, offset, 1);
        offset = point;
        offset.FUN_005fc1e0(SBGeoVector2D(1.0f, -1.0f));
        draw.FUN_00614bf0(*(void *const *)((const char *)this + 0x7c), (std::wstring *)&text, offset, 1);
        offset = point;
        offset.FUN_005fc1e0(SBGeoVector2D(1.0f, 1.0f));
        draw.FUN_00614bf0(*(void *const *)((const char *)this + 0x7c), (std::wstring *)&text, offset, 1);
    }
    draw.FUN_00614bf0(*(void *const *)((const char *)this + 0x78), (std::wstring *)&text, point, 1);
    return true;
}

// Parked: The second cached traversal is outlined instead of duplicated inline.
// STUB: GAME 0x005c8780
bool RHTitbits::IsRunningForQA(unsigned long id)
{
    unsigned count = m_list.m_count;
    for (int index = 0; (unsigned)index < count; ++index)
    {
        RHTitbitAccess &list = *(RHTitbitAccess *)&m_list;
        if (list.Get(index, true).m_2c == id && list.Get(index, true).m_00 == 17)
            return true;
    }
    return false;
}

inline bool operator<(const RHTitbit &first, const RHTitbit &second)
{
    return *(const float *)&first.m_24 < *(const float *)&second.m_24;
}

// Parked: Sort locals and shared destructor entities differ from the native instantiation.
// STUB: GAME 0x005c8980
void RHTitbitList::FUN_005c8980()
{
    std::list<RHTitbit> &list = *(std::list<RHTitbit> *)this;
    if (list.size() >= 2)
    {
        std::list<RHTitbit> carry(list.get_allocator());
        std::list<RHTitbit> bins[16];
        unsigned used = 0;
        while (!list.empty())
        {
            carry.splice(carry.begin(), list, list.begin());
            unsigned index;
            for (index = 0; index < used && !bins[index].empty(); ++index)
            {
                bins[index].merge(carry);
                bins[index].swap(carry);
            }
            if (index == 15)
                bins[index].merge(carry);
            else
            {
                bins[index].swap(carry);
                if (index == used)
                    ++used;
            }
        }
        while (used > 0)
            list.merge(bins[--used]);
    }
}

// SYNTHETIC: GAME 0x005c8bc0
// ??_F?$list@URHTitbit@@V?$allocator@URHTitbit@@@std@@@std@@QAEXXZ

// TEMPLATE: GAME 0x005c8bf0
// ?merge@?$list@URHTitbit@@V?$allocator@URHTitbit@@@std@@@std@@QAEXAAV12@@Z

void RHTitbitList::FUN_005c8bf0(RHTitbitList &other)
{
    typedef std::list<RHTitbit> List;
    typedef void (List::*Merge)(List &);
    Merge merge = &List::merge;
    (((List *)this)->*merge)(*(List *)&other);
}

// TEMPLATE: GAME 0x005c8cc0
// ?_Buynode@?$list@URHTitbit@@V?$allocator@URHTitbit@@@std@@@std@@IAEPAU_Node@12@PAU312@0@Z

// TEMPLATE: GAME 0x005c8cf0
// ?_Splice@?$list@URHTitbit@@V?$allocator@URHTitbit@@@std@@@std@@IAEXViterator@12@AAV12@00@Z

// Parked: initial size/count registers are exchanged despite matching insertion and erase loops.
// STUB: GAME 0x005c8d30
void RHTitbitList::Resize(long count)
{
    RHTitbit *value = new RHTitbit;
    std::list<RHTitbit> &list = *(std::list<RHTitbit> *)this;
    if (count <= m_count)
    {
        for (long remaining = m_count - count; remaining > 0; --remaining)
            list.pop_back();
    }
    else
    {
        for (long remaining = count - m_count; remaining > 0; --remaining)
            list.insert(list.end(), *value);
    }
    delete value;
    m_valid = 1;
}

#include "RHGameWidgetLifetime.h"

typedef std::map<SBResourceWidgetID, RHUIRendererBlinking::BlinkingItem> RHBlinkingMap;
typedef std::_Tree<SBResourceWidgetID,
    std::pair<const SBResourceWidgetID, RHUIRendererBlinking::BlinkingItem>,
    std::map<SBResourceWidgetID, RHUIRendererBlinking::BlinkingItem>::_Kfn,
    std::less<SBResourceWidgetID>,
    std::allocator<RHUIRendererBlinking::BlinkingItem> > RHBlinkingTree;

template<> inline void RHBlinkingTree::_Init()
{
    std::_Lockit lock;
    if (_Nil == 0)
    {
        _Nil = _Buynode(0, _Black);
        _Left(_Nil) = 0, _Right(_Nil) = 0;
    }
    ++_Nilrefs;
    _Head = _Buynode(_Nil, _Red), _Size = 0;
    _Lmost() = _Head, _Rmost() = _Head;
}

template<> inline RHBlinkingTree::~_Tree()
{
    erase(begin(), end());
    _Freenode(_Head);
    _Head = 0, _Size = 0;
    {
        std::_Lockit lock;
        if (--_Nilrefs == 0)
        {
            _Freenode(_Nil);
            _Nil = 0;
        }
    }
}

typedef int RHBlinkingWidgetIDSize[(sizeof(SBResourceWidgetID) == 0x04) ? 1 : -1];
typedef int RHBlinkingItemSize[(sizeof(RHUIRendererBlinking::BlinkingItem) == 0x0c) ? 1 : -1];
typedef int RHBlinkingMapSize[(sizeof(RHBlinkingMap) == 0x10) ? 1 : -1];
typedef int RHBlinkingRendererViewSize[(sizeof(RHUIRendererBlinking) == 0x74) ? 1 : -1];

template<> RHBlinkingTree::_Nodeptr RHBlinkingTree::_Min(_Nodeptr node)
{
    std::_Lockit lock;
    while (_Left(node) != _Nil)
        node = _Left(node);
    return node;
}

template<> RHBlinkingTree::_Nodeptr RHBlinkingTree::_Max(_Nodeptr node)
{
    std::_Lockit lock;
    while (_Right(node) != _Nil)
        node = _Right(node);
    return node;
}

template<> RHBlinkingTree::_Nodeptr RHBlinkingTree::_Lbound(const SBResourceWidgetID &id) const;
template<> RHBlinkingTree::_Nodeptr RHBlinkingTree::_Ubound(const SBResourceWidgetID &id) const;
template<> void RHBlinkingTree::_Erase(_Nodeptr node);
template<> void RHBlinkingTree::const_iterator::_Dec();
template<> void RHBlinkingTree::const_iterator::_Inc();
template<> RHBlinkingTree::_Pairib RHBlinkingTree::insert(const value_type &value);
template<> RHBlinkingTree::iterator RHBlinkingTree::erase(iterator first, iterator last);
template<> RHBlinkingTree::iterator RHBlinkingTree::erase(iterator position);
template<> RHBlinkingTree::iterator RHBlinkingTree::_Insert(_Nodeptr node, _Nodeptr parent, const value_type &value);

template<> void RHBlinkingTree::_Lrotate(_Nodeptr node)
{
    std::_Lockit lock;
    _Nodeptr right = _Right(node);
    _Right(node) = _Left(right);
    if (_Left(right) != _Nil)
        _Parent(_Left(right)) = node;
    _Parent(right) = _Parent(node);
    if (node == _Root())
        _Root() = right;
    else if (node == _Left(_Parent(node)))
        _Left(_Parent(node)) = right;
    else
        _Right(_Parent(node)) = right;
    _Left(right) = node;
    _Parent(node) = right;
}

template<> void RHBlinkingTree::_Rrotate(_Nodeptr node)
{
    std::_Lockit lock;
    _Nodeptr left = _Left(node);
    _Left(node) = _Right(left);
    if (_Right(left) != _Nil)
        _Parent(_Right(left)) = node;
    _Parent(left) = _Parent(node);
    if (node == _Root())
        _Root() = left;
    else if (node == _Right(_Parent(node)))
        _Right(_Parent(node)) = left;
    else
        _Left(_Parent(node)) = left;
    _Right(left) = node;
    _Parent(node) = left;
}

struct RHUnk00571160Position;
class RHScriptPositionList
{
public:
    static void Unk00588190(RHUnk00571160Position *, const RHUnk00571160Position *);
};

template<> RHBlinkingMap::_Pairib RHBlinkingMap::insert(const value_type &value)
{
    typedef RHBlinkingTree::_Pairib (RHBlinkingTree::*Insert)(const RHBlinkingTree::value_type &);
    Insert insert = &RHBlinkingTree::insert;
    _Imp::_Pairib result = (_Tr.*insert)(value);
    return _Pairib(result.first, result.second);
}

// FUNCTION: GAME 0x005c9170
RHUIRendererBlinking::RHUIRendererBlinking() : m_currentId(0), m_frame(0), m_active(false)
{
    m_vptr = 0x679e5c;
}

// FUNCTION: GAME 0x005c9250
void *RHUIRendererBlinking::FUN_005c9250(unsigned flags)
{
    this->~RHUIRendererBlinking();
    if (flags & 1)
        operator delete(this);
    return this;
}

// Parked: the inlined tree teardown sets its EH state before the end/begin loads.
// STUB: GAME 0x005c9270
RHUIRendererBlinking::~RHUIRendererBlinking()
{
    m_vptr = 0x679e5c;
}

#include "SBUIRenderer.h"
#include "RHGameWidgetRendererCalls.h"

// FUNCTION: GAME 0x005c9320
bool RHGameWidgetRendererCalls::FUN_005c9320(unsigned id)
{
    RHUIRendererBlinking *blinking = (RHUIRendererBlinking *)this;
    if (blinking->m_active && id == blinking->m_currentId) {
        if ((++blinking->m_frame / blinking->m_current.m_period) & 1)
            ((SBUIUnk0060da20 *)this)->FUN_0060da20(blinking->m_current.m_second);
        else
            ((SBUIUnk0060da20 *)this)->FUN_0060da20(blinking->m_current.m_first);
        return true;
    }
    const SBResourceWidgetID &key = *(SBResourceWidgetID *)&id;
    if (blinking->m_items.find(key) != blinking->m_items.end()) {
        blinking->m_currentId = id;
        blinking->m_active = true;
        blinking->m_current = blinking->m_items[key];
        blinking->m_frame = 0;
        ((SBUIUnk0060da20 *)this)->FUN_0060da20(blinking->m_current.m_first);
        return true;
    }
    ((SBUIUnk0060da20 *)this)->FUN_0060da20(id);
    return true;
}

// FUNCTION: GAME 0x005c9430
void RHUIRendererBlinking::SetBlinking(SBResourceWidgetID id, SBResourceWidgetID first,
    SBResourceWidgetID second, unsigned long period)
{
    BlinkingItem value;
    value.m_first = first;
    value.m_second = second;
    value.m_period = period;
    m_items[id] = value;
    if (*(bool *)((char *)this + 0x60) && id == *(int *)((char *)this + 0x58))
    {
        *(BlinkingItem *)((char *)this + 0x4c) = value;
    }
}

// FUNCTION: GAME 0x005c94c0
void RHUIRendererBlinking::RemoveBlinking(SBResourceWidgetID id)
{
    RHBlinkingTree &tree = *(RHBlinkingTree *)&m_items;
    RHBlinkingTree::iterator last = tree.upper_bound(id);
    RHBlinkingTree::iterator first = tree.lower_bound(id);
    RHBlinkingTree::iterator current = first;
    for (; current != last; ++current) {}
    typedef RHBlinkingTree::iterator (RHBlinkingTree::*Erase)(RHBlinkingTree::iterator, RHBlinkingTree::iterator);
    Erase erase = &RHBlinkingTree::erase;
    (tree.*erase)(first, last);
}

// TEMPLATE: GAME 0x005c9520
// ?erase@?$_Tree@W4SBResourceWidgetID@@U?$pair@$$CBW4SBResourceWidgetID@@UBlinkingItem@RHUIRendererBlinking@@@std@@U_Kfn@?$map@W4SBResourceWidgetID@@UBlinkingItem@RHUIRendererBlinking@@U?$less@W4SBResourceWidgetID@@@std@@V?$allocator@UBlinkingItem@R682db932
template<> RHBlinkingTree::iterator RHBlinkingTree::erase(iterator first, iterator last)
{
    if (size() == 0 || first != begin() || last != end())
    {
        while (first != last)
            erase(first++);
        return first;
    }
    else
    {
        std::_Lockit lock;
        _Erase(_Root());
        _Root() = _Nil;
        _Size = 0;
        _Lmost() = _Head;
        _Rmost() = _Head;
        return begin();
    }
}

// TEMPLATE: GAME 0x005c9650
// ?insert@?$_Tree@W4SBResourceWidgetID@@U?$pair@$$CBW4SBResourceWidgetID@@UBlinkingItem@RHUIRendererBlinking@@@std@@U_Kfn@?$map@W4SBResourceWidgetID@@UBlinkingItem@RHUIRendererBlinking@@U?$less@W4SBResourceWidgetID@@@std@@V?$allocator@UBlinkingItem@67f73113
template<> RHBlinkingTree::_Pairib RHBlinkingTree::insert(const value_type &value)
{
    typedef iterator (RHBlinkingTree::*Insert)(_Nodeptr, _Nodeptr, const value_type &);
    Insert insert = &RHBlinkingTree::_Insert;
    _Nodeptr parent = _Head;
    _Nodeptr node = _Root();
    bool left = true;
    {
        std::_Lockit lock;
        while (node != _Nil)
        {
            parent = node;
            left = key_compare(_Kfn()(value), _Key(node));
            node = left ? _Left(node) : _Right(node);
        }
    }
    if (_Multi)
    {
        _Pairib result((this->*insert)(node, parent, value), true);
        return result;
    }
    iterator position(parent);
    if (!left) {}
    else if (position == begin())
    {
        _Pairib result((this->*insert)(node, parent, value), true);
        return result;
    }
    else
    {
        void (const_iterator::*decrement)() = &const_iterator::_Dec;
        (position.*decrement)();
    }
    if (key_compare(_Key(position._Mynode()), _Kfn()(value)))
    {
        _Pairib result((this->*insert)(node, parent, value), true);
        return result;
    }
    _Pairib result(position, false);
    return result;
}

// TEMPLATE: GAME 0x005c9780
// ?erase@?$_Tree@W4SBResourceWidgetID@@U?$pair@$$CBW4SBResourceWidgetID@@UBlinkingItem@RHUIRendererBlinking@@@std@@U_Kfn@?$map@W4SBResourceWidgetID@@UBlinkingItem@RHUIRendererBlinking@@U?$less@W4SBResourceWidgetID@@@std@@V?$allocator@UBlinkingItem@R22574a04
template<> RHBlinkingTree::iterator RHBlinkingTree::erase(iterator position)
{
    _Nodeptr node;
    _Nodeptr removed = position._Mynode();
    void (const_iterator::*increment)() = &const_iterator::_Inc;
    (position.*increment)();
    _Nodeptr replacement = removed;
    std::_Lockit lock;
    if (_Left(replacement) == _Nil)
        node = _Right(replacement);
    else if (_Right(replacement) == _Nil)
        node = _Left(replacement);
    else
    {
        replacement = _Min(_Right(replacement));
        node = _Right(replacement);
    }
    if (replacement != removed)
    {
        _Parent(_Left(removed)) = replacement;
        _Left(replacement) = _Left(removed);
        if (replacement == _Right(removed))
            _Parent(node) = replacement;
        else
        {
            _Parent(node) = _Parent(replacement);
            _Left(_Parent(replacement)) = node;
            _Right(replacement) = _Right(removed);
            _Parent(_Right(removed)) = replacement;
        }
        if (_Root() == removed)
            _Root() = replacement;
        else if (_Left(_Parent(removed)) == removed)
            _Left(_Parent(removed)) = replacement;
        else
            _Right(_Parent(removed)) = replacement;
        _Parent(replacement) = _Parent(removed);
        std::swap(_Color(replacement), _Color(removed));
        replacement = removed;
    }
    else
    {
        _Parent(node) = _Parent(replacement);
        if (_Root() == removed)
            _Root() = node;
        else if (_Left(_Parent(removed)) == removed)
            _Left(_Parent(removed)) = node;
        else
            _Right(_Parent(removed)) = node;
        if (_Lmost() != removed) {}
        else if (_Right(removed) == _Nil)
            _Lmost() = _Parent(removed);
        else
            _Lmost() = _Min(node);
        if (_Rmost() != removed) {}
        else if (_Left(removed) == _Nil)
            _Rmost() = _Parent(removed);
        else
            _Rmost() = _Max(node);
    }
    if (_Color(replacement) == _Black)
    {
        while (node != _Root() && _Color(node) == _Black)
        {
            if (node == _Left(_Parent(node)))
            {
                _Nodeptr sibling = _Right(_Parent(node));
                if (_Color(sibling) == _Red)
                {
                    _Color(sibling) = _Black;
                    _Color(_Parent(node)) = _Red;
                    _Lrotate(_Parent(node));
                    sibling = _Right(_Parent(node));
                }
                if (_Color(_Left(sibling)) == _Black && _Color(_Right(sibling)) == _Black)
                {
                    _Color(sibling) = _Red;
                    node = _Parent(node);
                }
                else
                {
                    if (_Color(_Right(sibling)) == _Black)
                    {
                        _Color(_Left(sibling)) = _Black;
                        _Color(sibling) = _Red;
                        _Rrotate(sibling);
                        sibling = _Right(_Parent(node));
                    }
                    _Color(sibling) = _Color(_Parent(node));
                    _Color(_Parent(node)) = _Black;
                    _Color(_Right(sibling)) = _Black;
                    _Lrotate(_Parent(node));
                    break;
                }
            }
            else
            {
                _Nodeptr sibling = _Left(_Parent(node));
                if (_Color(sibling) == _Red)
                {
                    _Color(sibling) = _Black;
                    _Color(_Parent(node)) = _Red;
                    _Rrotate(_Parent(node));
                    sibling = _Left(_Parent(node));
                }
                if (_Color(_Right(sibling)) == _Black && _Color(_Left(sibling)) == _Black)
                {
                    _Color(sibling) = _Red;
                    node = _Parent(node);
                }
                else
                {
                    if (_Color(_Left(sibling)) == _Black)
                    {
                        _Color(_Right(sibling)) = _Black;
                        _Color(sibling) = _Red;
                        _Lrotate(sibling);
                        sibling = _Left(_Parent(node));
                    }
                    _Color(sibling) = _Color(_Parent(node));
                    _Color(_Parent(node)) = _Black;
                    _Color(_Left(sibling)) = _Black;
                    _Rrotate(_Parent(node));
                    break;
                }
            }
        }
        _Color(node) = _Black;
    }
    _Destval(&_Value(replacement));
    _Freenode(replacement);
    --_Size;
    return position;
}

// TEMPLATE: GAME 0x005c9ca0
// std::_Tree<SBResourceWidgetID,std::pair<SBResourceWidgetID const,RHUIRendererBlinking::BlinkingItem>,std::map<SBResourceWidgetID,RHUIRendererBlinking::BlinkingItem,std::less<SBResourceWidgetID>,std::allocator<RHUIRendererBlinking::BlinkingItem> >:c34947a4
template<> void RHBlinkingTree::_Erase(_Nodeptr node)
{
    std::_Lockit lock;
    for (_Nodeptr current = node; current != _Nil; node = current)
    {
        _Erase(_Right(current));
        current = _Left(current);
        _Destval(&_Value(node));
        _Freenode(node);
    }
}

// TEMPLATE: GAME 0x005c9d30
// std::_Tree<SBResourceWidgetID,std::pair<SBResourceWidgetID const,RHUIRendererBlinking::BlinkingItem>,std::map<SBResourceWidgetID,RHUIRendererBlinking::BlinkingItem,std::less<SBResourceWidgetID>,std::allocator<RHUIRendererBlinking::BlinkingItem> >:b3fae52b
template<> RHBlinkingTree::iterator RHBlinkingTree::_Insert(_Nodeptr node, _Nodeptr parent, const value_type &value)
{
    std::_Lockit lock;
    _Nodeptr inserted = _Buynode(parent, _Red);
    _Left(inserted) = _Nil;
    _Right(inserted) = _Nil;
    RHScriptPositionList::Unk00588190((RHUnk00571160Position *)&_Value(inserted),
        (const RHUnk00571160Position *)&value);
    ++_Size;
    if (parent == _Head || node != _Nil || key_compare(_Kfn()(value), _Key(parent)))
    {
        _Left(parent) = inserted;
        if (parent == _Head)
        {
            _Root() = inserted;
            _Rmost() = inserted;
        }
        else if (parent == _Lmost())
            _Lmost() = inserted;
    }
    else
    {
        _Right(parent) = inserted;
        if (parent == _Rmost())
            _Rmost() = inserted;
    }
    for (node = inserted; node != _Root() && _Color(_Parent(node)) == _Red; )
    {
        if (_Parent(node) == _Left(_Parent(_Parent(node))))
        {
            parent = _Right(_Parent(_Parent(node)));
            if (_Color(parent) == _Red)
            {
                _Color(_Parent(node)) = _Black;
                _Color(parent) = _Black;
                _Color(_Parent(_Parent(node))) = _Red;
                node = _Parent(_Parent(node));
            }
            else
            {
                if (node == _Right(_Parent(node)))
                {
                    node = _Parent(node);
                    _Lrotate(node);
                }
                _Color(_Parent(node)) = _Black;
                _Color(_Parent(_Parent(node))) = _Red;
                _Rrotate(_Parent(_Parent(node)));
            }
        }
        else
        {
            parent = _Left(_Parent(_Parent(node)));
            if (_Color(parent) == _Red)
            {
                _Color(_Parent(node)) = _Black;
                _Color(parent) = _Black;
                _Color(_Parent(_Parent(node))) = _Red;
                node = _Parent(_Parent(node));
            }
            else
            {
                if (node == _Left(_Parent(node)))
                {
                    node = _Parent(node);
                    _Rrotate(node);
                }
                _Color(_Parent(node)) = _Black;
                _Color(_Parent(_Parent(node))) = _Red;
                _Lrotate(_Parent(_Parent(node)));
            }
        }
    }
    _Color(_Root()) = _Black;
    return iterator(inserted);
}

// TEMPLATE: GAME 0x005ca030
// std::_Tree<SBResourceWidgetID,std::pair<SBResourceWidgetID const,RHUIRendererBlinking::BlinkingItem>,std::map<SBResourceWidgetID,RHUIRendererBlinking::BlinkingItem,std::less<SBResourceWidgetID>,std::allocator<RHUIRendererBlinking::BlinkingItem> >:dbee9ff7
template<> RHBlinkingTree::_Nodeptr RHBlinkingTree::_Lbound(const SBResourceWidgetID &id) const
{
    std::_Lockit lock;
    _Nodeptr node = _Root();
    _Nodeptr result = _Head;
    while (node != _Nil)
    {
        if (key_compare(_Key(node), id))
            node = _Right(node);
        else
        {
            result = node;
            node = _Left(node);
        }
    }
    return result;
}

// TEMPLATE: GAME 0x005ca080
// std::_Tree<SBResourceWidgetID,std::pair<SBResourceWidgetID const,RHUIRendererBlinking::BlinkingItem>,std::map<SBResourceWidgetID,RHUIRendererBlinking::BlinkingItem,std::less<SBResourceWidgetID>,std::allocator<RHUIRendererBlinking::BlinkingItem> >:ff37cca4
template<> RHBlinkingTree::_Nodeptr RHBlinkingTree::_Ubound(const SBResourceWidgetID &id) const
{
    std::_Lockit lock;
    _Nodeptr node = _Root();
    _Nodeptr result = _Head;
    while (node != _Nil)
    {
        if (key_compare(id, _Key(node)))
        {
            result = node;
            node = _Left(node);
        }
        else
            node = _Right(node);
    }
    return result;
}

// TEMPLATE: GAME 0x005ca0d0
// std::_Tree<SBResourceWidgetID,std::pair<SBResourceWidgetID const,RHUIRendererBlinking::BlinkingItem>,std::map<SBResourceWidgetID,RHUIRendererBlinking::BlinkingItem,std::less<SBResourceWidgetID>,std::allocator<RHUIRendererBlinking::BlinkingItem> >:1eace2aa
template<> void RHBlinkingTree::const_iterator::_Dec()
{
    std::_Lockit lock;
    if (_Color(_Ptr) == _Red && _Parent(_Parent(_Ptr)) == _Ptr)
        _Ptr = _Right(_Ptr);
    else if (_Left(_Ptr) != _Nil)
        _Ptr = _Max(_Left(_Ptr));
    else
    {
        _Nodeptr parent;
        while (_Ptr == _Left(parent = _Parent(_Ptr)))
            _Ptr = parent;
        _Ptr = parent;
    }
}

// TEMPLATE: GAME 0x005ca190
// std::_Tree<SBResourceWidgetID,std::pair<SBResourceWidgetID const,RHUIRendererBlinking::BlinkingItem>,std::map<SBResourceWidgetID,RHUIRendererBlinking::BlinkingItem,std::less<SBResourceWidgetID>,std::allocator<RHUIRendererBlinking::BlinkingItem> >:f580a832
template<> void RHBlinkingTree::const_iterator::_Inc()
{
    std::_Lockit lock;
    if (_Right(_Ptr) != _Nil)
        _Ptr = _Min(_Right(_Ptr));
    else
    {
        _Nodeptr parent;
        while (_Ptr == _Right(parent = _Parent(_Ptr)))
            _Ptr = parent;
        if (_Right(_Ptr) != parent)
            _Ptr = parent;
    }
}

// GLOBAL: GAME 0x006c10fc
// std::_Tree<SBResourceWidgetID,std::pair<SBResourceWidgetID const,RHUIRendererBlinking::BlinkingItem>,std::map<SBResourceWidgetID,RHUIRendererBlinking::BlinkingItem,std::less<SBResourceWidgetID>,std::allocator<RHUIRendererBlinking::BlinkingItem> >:cd8bb598

class RHBlinkingNativeAccess : public RHBlinkingTree
{
public:
    void Emit(const SBResourceWidgetID &id, const value_type &value, iterator position)
    {
        typedef _Nodeptr (RHBlinkingTree::*Bound)(const SBResourceWidgetID &) const;
        Bound lower = &RHBlinkingNativeAccess::_Lbound;
        Bound upper = &RHBlinkingNativeAccess::_Ubound;
        (this->*lower)(id);
        (this->*upper)(id);
        typedef void (RHBlinkingTree::*Erase)(_Nodeptr);
        Erase erase = &RHBlinkingNativeAccess::_Erase;
        (this->*erase)(position._Mynode());
        typedef iterator (RHBlinkingTree::*Insert)(_Nodeptr, _Nodeptr, const value_type &);
        Insert insert = &RHBlinkingNativeAccess::_Insert;
        (this->*insert)(position._Mynode(), position._Mynode(), value);
        typedef _Pairib (RHBlinkingTree::*InsertValue)(const value_type &);
        InsertValue insertValue = &RHBlinkingTree::insert;
        (this->*insertValue)(value);
        typedef iterator (RHBlinkingTree::*EraseRange)(iterator, iterator);
        EraseRange eraseRange = &RHBlinkingTree::erase;
        (this->*eraseRange)(position, position);
        typedef iterator (RHBlinkingTree::*EraseOne)(iterator);
        EraseOne eraseOne = &RHBlinkingTree::erase;
        (this->*eraseOne)(position);
        void (const_iterator::*decrement)() = &const_iterator::_Dec;
        void (const_iterator::*increment)() = &const_iterator::_Inc;
        (position.*decrement)();
        (position.*increment)();
    }
};

void EmitRHBlinkingHelpers(RHBlinkingNativeAccess *tree, RHUIRendererBlinking *renderer)
{
    SBResourceWidgetID id;
    RHBlinkingTree::value_type value;
    tree->Emit(id, value, tree->begin());
    renderer->SetBlinking(id, id, id, 0);
    renderer->RemoveBlinking(id);
    renderer->FUN_005c9250(0);
}

void RHTitbits::Emit(SBFile &file)
{
    Serialize(file);
    FUN_005c7fb0(0);
    FUN_005c8120(0, 0);
    FUN_005c8340(0, 0);
    RenderText(*(std::wstring *)0, *(SBGeoPoint2D *)0);
    RenderText(*(std::wstring *)0, *(SBGeoBoundingBox2D *)0, 0);
    IsRunningForQA(0);
    FUN_005c72a0();
    SetBlinking(0, 0, false);
    m_list.FUN_005c8980();
    m_list.FUN_005c8bf0(m_list);
    m_list.Resize(0);
    m_list.At(0);
}

void (std::list<RHTitbit>::*g_rhtitbitMerge)(std::list<RHTitbit> &) = &std::list<RHTitbit>::merge;

class RHTitbitNativeAccess : public std::list<RHTitbit>
{
public:
    void EmitBuynode()
    {
        typedef _Nodeptr (std::list<RHTitbit>::*Buy)(_Nodeptr, _Nodeptr);
        Buy buy = &RHTitbitNativeAccess::_Buynode;
        (this->*buy)(0, 0);
    }
};

void EmitRHTitbitNativeHelpers(RHTitbitNativeAccess *list)
{
    list->EmitBuynode();
}
