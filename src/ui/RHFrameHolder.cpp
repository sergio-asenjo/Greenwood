#include "RHFrameHolder.h"

DECOMP_SIZE_ASSERT(RHFrameHolderRecord, 0x14)
DECOMP_SIZE_ASSERT(SBGeoPoint2D, 0x08)
DECOMP_SIZE_ASSERT(SBGeoVector2D, 0x08)
DECOMP_SIZE_ASSERT(RHFrameHolderRowMap, 0x10)
DECOMP_SIZE_ASSERT(RHUnk005f4fc0, 0x58)
DECOMP_SIZE_ASSERT(RHUnk00506e00, 0x10)
DECOMP_SIZE_ASSERT(RHUnk005074d0, 0x10)
DECOMP_SIZE_ASSERT(RHUnk005068e0, 0x14)
DECOMP_SIZE_ASSERT(RHUnk005051a0Array, 0x10)
DECOMP_SIZE_ASSERT(RHFrameHolderFrameArray, 0x10)
DECOMP_SIZE_ASSERT(RHFrameHolder, 0xec)
DECOMP_SIZE_ASSERT(RHUnk00641782, 0x01)
DECOMP_SIZE_ASSERT(RHUnk00507500, 0x10)
DECOMP_SIZE_ASSERT(RHUnk00507500::Node, 0x14)
DECOMP_SIZE_ASSERT(RHFrameHolderRowMap::Node, 0x18)
DECOMP_SIZE_ASSERT(RHUnk00613e90, 0x18)
DECOMP_SIZE_ASSERT(RHUnkFXDraw, 0x10e)

// GLOBAL: GAME 0x006c0b2c
RHFrameHolderRowMap::Node *g_unk0x006c0b2c = 0;

// GLOBAL: GAME 0x006c0b30
RHUnk00507500::Node *g_unk0x006c0b30 = 0;
// GLOBAL: GAME 0x006c0b34
unsigned int g_unk0x006c0b34 = 0;

// FUNCTION: GAME 0x004d2340
unsigned int RHEngine::FUN_004d2340(int type)
{
    switch (type)
    {
    case 11: return m_4790 != 0;
    case 12: return m_4791 != 0;
    case 14: return m_4aa4;
    case 15: return m_4aa6;
    default: return 0;
    }
}

// STRING: GAME 0x006b0008
#define g_frameHolderFile "P:\\Robin Hood\\RHframeholder.cpp"
// STRING: GAME 0x006b0028
#define g_frameHolderIndexError "Unable to open the sprite index file"
// STRING: GAME 0x006b0050
#define g_frameHolderIndex "Data\\RobinHood.dic"
// STRING: GAME 0x006b0064
#define g_frameHolderBankError "No Sprite Bank Found !!"
// STRING: GAME 0x006b007c
#define g_frameHolderBank "Data\\RobinHood.bks"
// STRING: GAME 0x006b0090
#define g_frameHolderSurfaceError "Unable to retrieve surface from resource"

// Parked: dictionary local slots and success-path destructor inlining differ.
// STUB: GAME 0x00504040
bool RHFrameHolder::InitializeSpriteBank()
{
    RHUnk00507500 dictionaries;
    if (!FUN_005f6400(g_frameHolderBank))
        SBAssert(1, g_frameHolderFile, 86, g_frameHolderBankError);
    int opened = m_bank.FUN_005f5d60(g_frameHolderBank, 1);
    if (opened == 0)
    {
        m_e8 = true;
        m_bank.FUN_005f5090(g_frameHolderBank, 1);
    }
    else
        m_e8 = false;
    RHUnk005f4fc0 index;
    if (index.FUN_005f5090(g_frameHolderIndex, 1) != 0)
    {
        SBAssert(1, g_frameHolderFile, 107, g_frameHolderIndexError);
        return false;
    }
    index.Access(&m_b4, 4);
    unsigned short count;
    index.Access(&count, 2);
    for (unsigned short i = 0; i < count; ++i)
    {
        unsigned short id;
        index.Access(&id, 2);
        unsigned short slot = FUN_005051a0(id, index);
        dictionaries[i] = slot;
    }
    dictionaries[0xffff] = 0xffff;
    unsigned long frames;
    index.Access(&frames, 4);
    m_frames.Resize(frames);
    for (unsigned long frame = 0; frame < frames; ++frame)
    {
        unsigned char bytes[14];
        index.Access(bytes, 14);
        RHFrameHolderRecord record;
        record.m_size = *(unsigned long *)(bytes + 8);
        record.m_data = opened + ((*(unsigned long *)(bytes + 4) >> 1) * 2);
        record.m_10 = true;
        record.m_0c = 0;
        record.m_12 = dictionaries[*(unsigned short *)(bytes + 12)];
        record.m_width = *(unsigned short *)bytes;
        record.m_height = *(unsigned short *)(bytes + 2);
        m_frames.m_first[frame] = record;
    }
    return true;
}

// FUNCTION: GAME 0x00504590
void RHUnk00507500::FUN_00504590()
{
    Iterator first;
    first.m_node = m_head->m_left;
    Iterator last;
    last.m_node = m_head;
    FUN_00507500(first, last);
    operator delete(m_head);
    m_head = 0;
    m_size = 0;
    {
        RHUnk00641782 lock;
        if (--g_unk0x006c0b34 == 0)
        {
            operator delete(g_unk0x006c0b30);
            g_unk0x006c0b30 = 0;
        }
    }
}

// Parked: carried index/pixel registers and conditional esi save differ.
// STUB: GAME 0x00504b10
void RHFrameHolder::FUN_00504b10(unsigned long data, unsigned long size, unsigned short replacement)
{
    unsigned int index = 0;
    size >>= 1;
    unsigned short *words = (unsigned short *)data;
    while (index < size)
    {
        unsigned short first = words[index++];
        unsigned short last = words[index++];
        if (last != 0xffff && first <= last)
        {
            unsigned int count = last - first + 1;
            unsigned short *pixel = words + index;
            index += count;
            do
            {
                if (*pixel == replacement)
                    ++*pixel;
                if (*pixel == 31)
                    *pixel = replacement;
                ++pixel;
            } while (--count);
        }
    }
}

// Parked: source array and stride argument lowering differ.
// STUB: GAME 0x00504bd0
void RHFrameHolder::FUN_00504bd0(unsigned long data, unsigned short width, unsigned short height,
    unsigned long pitch, unsigned short key)
{
    unsigned short *row = (unsigned short *)data;
    for (unsigned int y = 0; y < height; ++y, row += pitch >> 1)
        for (unsigned int x = 0; x < width; ++x)
            if (row[x] != key)
                row[x] = (row[x] & 0x001f) | ((row[x] >> 1) & 0x7fe0);
}

// Parked: source array and stride argument lowering differ.
// STUB: GAME 0x00504c50
void RHFrameHolder::FUN_00504c50(unsigned long data, unsigned short width, unsigned short height,
    unsigned long pitch, unsigned short key)
{
    unsigned short *row = (unsigned short *)data;
    for (unsigned int y = 0; y < height; ++y, row += pitch >> 1)
        for (unsigned int x = 0; x < width; ++x)
            if (row[x] != key)
                row[x] = (row[x] & 0x001f) | ((row[x] & 0xfff0) << 1);
}

// Parked: target scheduling differs for selector and row-stride operands.
// STUB: GAME 0x005050a0
void RHFrameHolder::FUN_005050a0(unsigned short *pixels, unsigned long *output,
    unsigned short outputPitch, unsigned short width, unsigned short height, unsigned int tableIndex, int selector)
{
    unsigned long table;
    if (selector == 0)
        table = *(unsigned long *)((char *)this + 0x1c) + (tableIndex & 0xffff) * 0x14;
    else if (selector == 1)
        table = *(unsigned long *)((char *)this + 0x2c) + (tableIndex & 0xffff) * 0x14;
    else if (selector == 2)
        table = *(unsigned long *)((char *)this + 0x3c) + (tableIndex & 0xffff) * 0x14;
    else
        table = tableIndex;

    unsigned int outputPadding = outputPitch >> 1;
    for (unsigned int row = 0; row < height; ++row)
    {
        for (unsigned int column = 0; column < (width + 3) / 4; ++column)
        {
            unsigned short color = *pixels++;
            unsigned long lookup = *(unsigned long *)(table + 4) + color * 8;
            *output++ = *(unsigned long *)lookup;
            *output++ = *(unsigned long *)(lookup + 4);
        }
        output = (unsigned long *)((char *)output + outputPadding * 2);
    }
}

// Parked: function return and sentinel merge differ.
// STUB: GAME 0x00505170
RHUnk005068e0 *RHFrameHolder::FUN_00505170(unsigned short id)
{
    unsigned short index = FUN_00504680(id);
    RHUnk005068e0 *result = 0;
    if (index != 0xffff)
        result = m_dictionaries.m_first + index;
    return result;
}

// Parked: effective-only; signed size division sign fix uses ecx instead of eax.
// STUB: GAME 0x005051a0
unsigned short RHFrameHolder::FUN_005051a0(unsigned short id, SBFile &file)
{
    RHUnk005068e0 value;
    unsigned int index = 0;
    if (id == 0)
        return 0xffff;
    value.FUN_005069d0(id, file);
    RHUnk005068e0 *cursor = *(RHUnk005068e0 **)((char *)this + 0x1c);
    RHUnk005068e0 *end = *(RHUnk005068e0 **)((char *)this + 0x20);
    for (; cursor != end; ++cursor, ++index)
        if (cursor->m_08 == value.m_08)
            return index;
    RHUnk005051a0Array &array = *(RHUnk005051a0Array *)((char *)this + 0x18);
    array.FUN_00508090(array.m_last, 1, value);
    return array.Size() - 1;
}

// Parked: RLE scan/copy scheduling and live-local register allocation differ.
// STUB: GAME 0x00505980
unsigned long RHFrameHolder::FUN_00505980(unsigned long surface, unsigned long &size, unsigned short &width, unsigned short &height, long &x, long &y)
{
    RHUnk00613e90 pixels;
    unsigned int used = 0;
    if (!Draw()->Unk005e5a00(surface, pixels, 0))
        return 0;
    if (Draw()->m_depth != 16)
        FUN_00504c50((unsigned long)pixels.m_data, pixels.m_width, pixels.m_height, pixels.m_pitch, 31);
    unsigned int pitch = pixels.m_pitch >> 1;
    unsigned short *row = pixels.m_data;
    width = pixels.m_width;
    height = pixels.m_height;
    unsigned int left = ~0u;
    unsigned int top = ~0u;
    unsigned int right = 0;
    unsigned int bottom = 0;
    for (unsigned int outputRow = 0; outputRow < height; ++outputRow)
    {
        unsigned short *pixel = row;
        for (unsigned int i = 0; i < width; ++i)
        {
            if (*pixel != 0x7c0)
            {
                if (left > i) left = i;
                if (right < i) right = i;
                if (top > outputRow) top = outputRow;
                if (bottom < outputRow) bottom = outputRow;
            }
            ++pixel;
        }
        row += pitch;
    }
    x = left;
    y = top;
    width = right - left + 1;
    height = bottom - top + 1;
    row = pixels.m_data + top * pitch + left;
    unsigned short *temporary = (unsigned short *)operator new(width * height * 4);
    unsigned short *source = row;
    unsigned int rowOffset = 0;
    for (unsigned int j = 0; j < height; ++j)
    {
        unsigned int first = ~0u;
        unsigned int last = ~0u;
        for (unsigned int column = 0; column < width; ++column)
            if (source[column] != 0x7c0 && first == ~0u)
                first = column;
        if (first == ~0u)
            temporary[used++] = 0xffff;
        else
            temporary[used++] = first;
        for (unsigned int reverse = width - 1; reverse > 0; --reverse)
            if (row[rowOffset + reverse] != 0x7c0 && last == ~0u)
                last = reverse;
        if (last == ~0u)
            temporary[used++] = 0xffff;
        else
        {
            temporary[used++] = last;
            if (first <= last)
            {
                unsigned int count = last - first + 1;
                unsigned short *destination = temporary + used;
                unsigned short *pixel = row + rowOffset + first;
                used += count;
                do
                {
                    *destination++ = *pixel++;
                } while (--count);
            }
        }
        source += pitch;
        rowOffset += pitch;
    }
    size = used * 2;
    unsigned short *result = (unsigned short *)operator new(size * 2);
    memcpy(result, temporary, size);
    operator delete(temporary);
    if (Draw()->m_depth != 16)
        FUN_00504bd0((unsigned long)pixels.m_data, pixels.m_width, pixels.m_height, pixels.m_pitch, 31);
    Draw()->Unk005e5ea0(pixels);
    return (unsigned long)result;
}

#include <vector>

class RHFrameHolderVectors : public std::vector<SBGeoVector2D>
{
public:
    void RemoveAll()
    {
        iterator (std::vector<SBGeoVector2D>::*eraseRange)(iterator, iterator) = &std::vector<SBGeoVector2D>::erase;
        (this->*eraseRange)(begin(), end());
        m_dirty = true;
    }
    void InsertLast(const SBGeoVector2D &value)
    {
        void (std::vector<SBGeoVector2D>::*insertCount)(iterator, size_type, const SBGeoVector2D &) = &std::vector<SBGeoVector2D>::insert;
        (this->*insertCount)(end(), 1, value);
        m_dirty = true;
    }
    unsigned int m_10; // 0x10
    bool m_dirty; // 0x14
};

DECOMP_SIZE_ASSERT(RHFrameHolderVectors, 0x18)

// Parked: vector temporary/EH slots and frame-record receiver scheduling differ.
// STUB: GAME 0x00505cd0
unsigned long RHFrameHolder::AddRowFromResource(SBResourceManager *resources, unsigned long row, unsigned short &count, SBArray<SBGeoVector2D> &vectors)
{
    RHFrameHolderVectors &output = (RHFrameHolderVectors &)vectors;
    output.RemoveAll();
    unsigned long first;
    unsigned long surface;
    long x;
    long y;
    if (m_rows.Find(row) != m_rows.End())
    {
        count = resources->FUN_00600550(row);
        first = m_rows.Insert(RHFrameHolderRowMap::Value(row, 0)).first.m_node->m_value;
        for (unsigned long i = first; i < first + count; ++i)
        {
            if (!resources->FUN_00600920(row, i - first, surface))
                SBAssert(1, g_frameHolderFile, 1208, g_frameHolderSurfaceError);
            unsigned long data = FUN_00505980(surface, m_frames[i].m_size, m_frames[i].m_width, m_frames[i].m_height, x, y);
            operator delete((void *)data);
            output.InsertLast(SBGeoVector2D((float)x, (float)y));
        }
    }
    else
    {
        first = m_frames.Size();
        count = resources->FUN_00600550(row);
        m_frames.Resize(first + count);
        for (long i = first; i < first + count; ++i)
        {
            if (!resources->FUN_00600920(row, i - first, surface))
                SBAssert(1, g_frameHolderFile, 1236, g_frameHolderSurfaceError);
            m_frames[i].m_10 = false;
            m_frames[i].m_data = FUN_00505980(surface, m_frames[i].m_size, m_frames[i].m_width, m_frames[i].m_height, x, y);
            m_frames[i].m_12 = 0xffff;
            FUN_00504b10(m_frames[i].m_data, m_frames[i].m_size, g_pEngine->FUN_004d2340(15));
            output.InsertLast(SBGeoVector2D((float)x, (float)y));
        }
        m_rows[row] = first;
    }
    return first;
}

#include <stdio.h>
#include <string.h>
#include <math.h>

class RHSpriteFrameCalls
{
public:
    void FUN_00505940(unsigned);
};

struct RHConsoleBlockMap
{
    char m_00[0x58];
    int m_counts[17];
};

class RHConsoleBlockAllocator
{
public:
    bool FUN_00506070(RHConsoleBlockMap *);
    int FUN_00506620();
};

// FUNCTION: GAME 0x00506120
void RHFrameHolder::FUN_00506120()
{
    unsigned int count = m_frames.Size();
    for (unsigned int i = 0; i < count; ++i)
        ((RHSpriteFrameCalls *)this)->FUN_00505940(i);
}

// FUNCTION: GAME 0x00506160
bool RHFrameHolder::FUN_00506160(SBFile &file)
{
    char text[80];
    RHConsoleBlockMap information;
    ((RHConsoleBlockAllocator *)this)->FUN_00506070(&information);
    sprintf(text,
        // STRING: GAME 0x006b00bc
        "%d;%d;%d;%d\n",
        *(int *)(information.m_00 + 4),
        *(int *)(information.m_00 + 12),
        *(int *)(information.m_00 + 8),
        *(int *)(information.m_00 + 16));
    file.Access(text, strlen(text));
    return true;
}

struct RHFramePoolBlock
{
    void *address;
    unsigned long size;
    unsigned long page;
};

struct RHFramePoolNode
{
    RHFramePoolNode *next;
    RHFramePoolNode *previous;
    RHFramePoolBlock value;
};

#include <list>
#include "RHShortBriefings.h"

class RHFramePoolListLifetime
{
public:
    void FUN_005062b0();
    std::allocator<RHFramePoolBlock> m_allocator;
    RHFramePoolNode *m_head;
    unsigned long m_count;
};

// FUNCTION: GAME 0x005062b0
void RHFramePoolListLifetime::FUN_005062b0()
{
    std::allocator<RHFramePoolBlock> allocator;
    memcpy(&m_allocator, &allocator, sizeof(allocator));
    RHFramePoolNode *node = (RHFramePoolNode *)operator new(sizeof(RHFramePoolNode));
    node->next = node;
    node->previous = node;
    m_head = node;
    m_count = 0;
}

void RHFramePoolListEmit(RHFramePoolListLifetime *list)
{
    list->FUN_005062b0();
}

struct RHFramePoolList
{
    char allocator;
    RHFramePoolNode *head;
    unsigned long count;

    void Insert(RHFramePoolNode *position, const RHFramePoolBlock &value)
    {
        RHFramePoolNode *previous = position->previous;
        RHFramePoolNode *node = (RHFramePoolNode *)operator new(sizeof(RHFramePoolNode));
        node->next = position ? position : node;
        node->previous = previous ? previous : node;
        position->previous = node;
        node->previous->next = node;
        if (&node->value)
            new (&node->value) RHFramePoolBlock(value);
        ++count;
    }
};

struct RHFramePoolPage
{
    void *address;
    unsigned long index;
};

class RHFrameMemoryPool
{
public:
    void FUN_005062e0();
    unsigned long FUN_00506460(unsigned long size);
    void FUN_005064b0(RHFramePoolList *list, const RHFramePoolBlock &value);
    bool FUN_00506560(RHFramePoolList *list, const RHFramePoolBlock &value);
    unsigned long FUN_005065b0() const;
    unsigned long FUN_005065d0() const;
    static int FUN_00506600(const RHFramePoolBlock *first, const RHFramePoolBlock *second);
    unsigned long Size() const { if (!m_first) return 0; return m_last - m_first; }

    RHFramePoolList *m_free;
    RHFramePoolList *m_used;
    unsigned long m_allocator;
    RHFramePoolPage *m_first;
    RHFramePoolPage *m_last;
    RHFramePoolPage *m_end;
};

extern double g_unk0x00677670;
double FUN_006433ab(double) throw();

DECOMP_SIZE_ASSERT(RHFramePoolBlock, 0x0c)
DECOMP_SIZE_ASSERT(RHFramePoolNode, 0x14)
DECOMP_SIZE_ASSERT(RHFramePoolList, 0x0c)
DECOMP_SIZE_ASSERT(RHFramePoolListLifetime, 0x0c)
DECOMP_SIZE_ASSERT(RHFramePoolPage, 0x08)
DECOMP_SIZE_ASSERT(RHFrameMemoryPool, 0x18)

// FUNCTION: GAME 0x005062e0
void RHFrameMemoryPool::FUN_005062e0()
{
    RHFramePoolPage page;
    page.address = operator new(0x200000);
    *(unsigned short *)&page.index = 0;
    typedef RHShortBriefings::ShortBriefing Value;
    typedef std::vector<Value> Vector;
    Vector &pages = *(Vector *)((char *)this + 8);
    void (Vector::*insert)(Value *, unsigned, const Value &) = &Vector::insert;
    (pages.*insert)(pages.end(), 1, *(const Value *)&page);
    RHFramePoolBlock block;
    block.address = page.address;
    block.size = 0x200000;
    *(unsigned short *)&block.page = (unsigned short)(pages.size() - 1);
    RHFramePoolList &list = m_free[16];
    list.Insert(list.head, block);
}

// Parked: subtraction emits add eax,-4 instead of sub eax,4.
// STUB: GAME 0x00506460
unsigned long RHFrameMemoryPool::FUN_00506460(unsigned long size)
{
    unsigned long index = (unsigned long)FUN_006433ab(log10((double)size) / log10(g_unk0x00677670));
    return index >= 4 ? index - 4 : 0;
}

// FUNCTION: GAME 0x005064b0
void RHFrameMemoryPool::FUN_005064b0(RHFramePoolList *list, const RHFramePoolBlock &value)
{
    RHFramePoolNode *head = list->head;
    RHFramePoolNode *position = head->next;
    for (; position != head; position = position->next)
        if (position->value.size > value.size)
        {
            list->Insert(position, value);
            return;
        }
    list->Insert(head, value);
}

// FUNCTION: GAME 0x00506560
bool RHFrameMemoryPool::FUN_00506560(RHFramePoolList *list, const RHFramePoolBlock &value)
{
    bool found = false;
    RHFramePoolNode *head = list->head;
    for (RHFramePoolNode *node = head->next; node != head; node = node->next)
        if (node->value.address == value.address)
        {
            node->previous->next = node->next;
            node->next->previous = node->previous;
            operator delete(node);
            --list->count;
            found = true;
            break;
        }
    return found;
}

// FUNCTION: GAME 0x005065b0
unsigned long RHFrameMemoryPool::FUN_005065b0() const
{
    return Size() * 0x200000;
}

// FUNCTION: GAME 0x005065d0
unsigned long RHFrameMemoryPool::FUN_005065d0() const
{
    unsigned long size = 0;
    for (unsigned int i = 0; i < 17; ++i)
    {
        RHFramePoolNode *head = m_used[i].head;
        for (RHFramePoolNode *node = head->next; node != head; node = node->next)
            size += node->value.size;
    }
    return size;
}

// FUNCTION: GAME 0x00506600
int RHFrameMemoryPool::FUN_00506600(const RHFramePoolBlock *first, const RHFramePoolBlock *second)
{
    return first->address < second->address;
}

void RHFramePoolEmit(RHFrameMemoryPool *pool, RHFramePoolList *list, const RHFramePoolBlock &value)
{
    pool->FUN_005062e0();
    pool->FUN_005064b0(list, value);
    pool->FUN_00506460(value.size);
    pool->FUN_00506560(list, value);
    pool->FUN_005065b0();
    pool->FUN_005065d0();
    RHFrameMemoryPool::FUN_00506600(&value, &value);
}

// FUNCTION: GAME 0x005068e0
RHUnk005068e0::RHUnk005068e0()
{
    m_00 = 0;
    m_04 = 0;
    m_0c = 31;
    m_0e[0] = 0;
    m_0e[1] = 0;
    m_0e[2] = 0;
    m_0e[3] = 0;
}

RHUnk005068e0::RHUnk005068e0(const RHUnk005068e0 &value)
{
    m_00 = 0;
    m_04 = 0;
    m_0e[0] = 0;
    m_0e[1] = 0;
    m_0e[2] = 0;
    m_0e[3] = 0;
    m_0c = 31;
    FUN_00506a70(value);
}

RHUnk005068e0 &RHUnk005068e0::FUN_005069b0(const RHUnk005068e0 &value)
{
    FUN_00506a70(value);
    return *this;
}

struct RHFrameDictionaryEntry
{
    unsigned long first;
    unsigned long second;
};

class RHUnk005ef320;
extern RHUnk005ef320 *g_unk0x6c11d0;
unsigned long FUN_006183c0(unsigned long, const char *, unsigned long);

// FUNCTION: GAME 0x005069d0
void RHUnk005068e0::FUN_005069d0(unsigned short count, SBFile &file)
{
    m_00 = count;
    if (m_04)
        operator delete((void *)m_04);
    unsigned long size = count * 8;
    m_04 = (unsigned long)operator new(size);
    file.Access((void *)m_04, size);
    m_08 = FUN_006183c0(0, (const char *)m_04, size);
    unsigned short *pixels = (unsigned short *)m_04;
    for (unsigned short i = 0; i < m_00 * 4; ++i)
        if (pixels[i] == 0x7e0)
            pixels[i] = 0x7c0;
    if (((RHUnkFXDraw *)g_unk0x6c11d0)->m_depth == 15)
        FUN_00506b40();
}

// FUNCTION: GAME 0x00506a70
void RHUnk005068e0::FUN_00506a70(const RHUnk005068e0 &value)
{
    if (m_04)
        operator delete((void *)m_04);
    m_00 = value.m_00;
    if (!value.m_04)
        m_04 = 0;
    else
    {
        m_04 = (unsigned long)operator new(m_00 * sizeof(RHFrameDictionaryEntry));
        for (unsigned short i = 0; i < m_00; ++i)
            ((RHFrameDictionaryEntry *)m_04)[i] = ((RHFrameDictionaryEntry *)value.m_04)[i];
    }
    m_0e[3] = value.m_0e[3];
    m_0e[0] = value.m_0e[0];
    m_0e[1] = value.m_0e[1];
    m_0e[2] = value.m_0e[2];
    m_0c = value.m_0c;
}

void RHFrameDictionaryEmit(RHUnk005068e0 *destination, const RHUnk005068e0 &value)
{
    new (destination) RHUnk005068e0;
    new (destination) RHUnk005068e0(value);
    destination->FUN_005069b0(value);
    destination->FUN_00506a70(value);
}

void RHFrameCacheEmit(RHFrameHolder *holder, SBFile &file)
{
    holder->FUN_00506120();
    holder->FUN_00506160(file);
}

// FUNCTION: GAME 0x00506e00
unsigned int RHUnk00506e00::FUN_00506e00() const
{
    return m_first == 0 ? 0 : m_last - m_first;
}

// FUNCTION: GAME 0x00506e70
RHFrameHolderRowMap::Pair RHFrameHolderRowMap::Insert(const Value &value)
{
    TreePair result;
    result = InsertTree(value);
    Pair pair(result.first, result.second);
    return pair;
}

// FUNCTION: GAME 0x00506fd0
RHFrameHolderRowMap::Iterator RHFrameHolderRowMap::Find(const unsigned long &key)
{
    Iterator result;
    result.m_node = FUN_005093e0(key);
    return result == End() || key < result.m_node->m_key ? End() : result;
}

// FUNCTION: GAME 0x00507020
void RHUnk00506e00::FUN_00507020(RHFrameHolderRecord *position, unsigned int count, const RHFrameHolderRecord &value)
{
    if (m_end - m_last < count)
    {
        unsigned int capacity = Size() + (count < Size() ? Size() : count);
        RHFrameHolderRecord *storage = m_allocator.allocate(capacity, 0);
        RHFrameHolderRecord *middle = Copy(m_first, position, storage);
        Fill(middle, count, value);
        Copy(position, m_last, middle + count);
        Destroy(m_first, m_last);
        m_allocator.deallocate(m_first, m_end - m_first);
        m_end = storage + capacity;
        m_last = storage + Size() + count;
        m_first = storage;
    }
    else if (m_last - position < count)
    {
        Copy(position, m_last, position + count);
        Fill(m_last, count - (m_last - position), value);
        std::fill(position, m_last, value);
        m_last += count;
    }
    else if (count > 0)
    {
        Copy(m_last - count, m_last, m_last);
        std::copy_backward(position, m_last - count, m_last);
        std::fill(position, position + count, value);
        m_last += count;
    }
}

// FUNCTION: GAME 0x00507320
RHFrameHolderRecord *RHUnk00506e00::FUN_00507320(RHFrameHolderRecord *first, RHFrameHolderRecord *last)
{
    RHFrameHolderRecord *next = std::copy(last, m_last, first);
    last = m_last;
    m_last = next;
    while (next != last)
        ++next;
    return first;
}

// TEMPLATE: GAME 0x00507360
// ?_Destroy@?$vector@VRHUnk005069a0@@V?$allocator@VRHUnk005069a0@@@std@@@std@@IAEXPAVRHUnk005069a0@@0@Z

// FUNCTION: GAME 0x005074d0
RHUnk005074d0::Pair RHUnk005074d0::FUN_005074d0(const Value &value)
{
    TreePair result;
    result = FUN_00508950(value);
    Pair pair(result.first, result.second);
    return pair;
}

// FUNCTION: GAME 0x00507500
RHUnk00507500::Iterator RHUnk00507500::FUN_00507500(Iterator first, Iterator last)
{
    if (m_size != 0 && first.m_node == m_head->m_left && last.m_node == m_head)
    {
        RHUnk00641782 lock;
        Node *node = m_head->m_parent;
        {
            RHUnk00641782 inner;
            for (Node *next = node; next != g_unk0x006c0b30; node = next)
            {
                FUN_00508fa0(next->m_right);
                next = next->m_left;
                operator delete(node);
            }
        }
        Root() = g_unk0x006c0b30;
        m_size = 0;
        Leftmost() = m_head;
        Rightmost() = m_head;
        return begin();
    }
    while (first.m_node != last.m_node)
    {
        FUN_00508a80(first++);
    }
    return first;
}

// FUNCTION: GAME 0x005079b0
RHFrameHolderRowMap::TreePair RHFrameHolderRowMap::InsertTree(const Value &value)
{
    Node *parent = m_head;
    Node *node = parent->m_parent;
    bool left = true;
    {
        RHUnk00641782 lock;
        while (node != g_unk0x006c0b2c)
        {
            parent = node;
            left = value.first < node->m_key;
            node = left ? node->m_left : node->m_right;
        }
    }
    if (m_comparator[0])
    {
        TreePair result(FUN_005090e0(node, parent, value), true);
        return result;
    }
    Iterator previous;
    previous.m_node = parent;
    if (left)
    {
        if (previous.m_node == m_head->m_left)
        {
            TreePair result(FUN_005090e0(node, parent, value), true);
            return result;
        }
        previous.FUN_005097a0();
    }
    if (previous.m_node->m_key < value.first)
    {
        TreePair result(FUN_005090e0(node, parent, value), true);
        return result;
    }
    TreePair result(previous, false);
    return result;
}

// FUNCTION: GAME 0x00508000
void RHFrameHolderRowMap::FUN_00508000(Node *node)
{
    RHUnk00641782 lock;
    for (Node *next = node; next != g_unk0x006c0b2c; node = next)
    {
        FUN_00508000(next->m_right);
        next = next->m_left;
        operator delete(node);
    }
}

// FUNCTION: GAME 0x00508950
RHUnk005074d0::TreePair RHUnk005074d0::FUN_00508950(const Value &value)
{
    Node *parent = m_head;
    Node *node = parent->m_parent;
    bool left = true;
    {
        RHUnk00641782 lock;
        while (node != (Node *)g_unk0x006c0b30)
        {
            parent = node;
            left = value.m_key < node->m_key;
            node = left ? node->m_left : node->m_right;
        }
    }
    if (m_multi)
    {
        TreePair result(FUN_005094a0(node, parent, value), true);
        return result;
    }
    Iterator previous;
    previous.m_node = parent;
    if (left)
    {
        if (previous.m_node == m_head->m_left)
        {
            TreePair result(FUN_005094a0(node, parent, value), true);
            return result;
        }
        previous.FUN_005099c0();
    }
    if (previous.m_node->m_key < value.m_key)
    {
        TreePair result(FUN_005094a0(node, parent, value), true);
        return result;
    }
    TreePair result(RHFrameHolderRowMap::Iterator((RHFrameHolderRowMap::Node *)previous.m_node), false);
    return result;
}

// FUNCTION: GAME 0x00508fa0
void RHUnk00507500::FUN_00508fa0(Node *node)
{
    RHUnk00641782 lock;
    for (Node *next = node; next != g_unk0x006c0b30; node = next)
    {
        FUN_00508fa0(next->m_right);
        next = next->m_left;
        operator delete(node);
    }
}

// FUNCTION: GAME 0x00509030
void RHUnk00507500::FUN_00509030()
{
    RHUnk00641782 lock;
    if (g_unk0x006c0b30 == 0)
    {
        Node *node = (Node *)operator new(sizeof(Node));
        node->m_parent = 0;
        node->m_color = 1;
        g_unk0x006c0b30 = node;
        g_unk0x006c0b30->m_left = 0;
        g_unk0x006c0b30->m_right = 0;
    }
    ++g_unk0x006c0b34;
    Node *sentinel = g_unk0x006c0b30;
    Node *head = (Node *)operator new(sizeof(Node));
    head->m_parent = sentinel;
    head->m_color = 0;
    m_head = head;
    m_size = 0;
    m_head->m_left = m_head;
    m_head->m_right = m_head;
}

inline void RHUnk005074d0::Lrotate(Node *x)
{
    RHUnk00641782 lock;
    Node *y = x->m_right;
    x->m_right = y->m_left;
    if (y->m_left != (Node *)g_unk0x006c0b30)
        y->m_left->m_parent = x;
    y->m_parent = x->m_parent;
    if (x == m_head->m_parent)
        m_head->m_parent = y;
    else if (x == x->m_parent->m_left)
        x->m_parent->m_left = y;
    else
        x->m_parent->m_right = y;
    y->m_left = x;
    x->m_parent = y;
}

inline void RHUnk005074d0::Rrotate(Node *x)
{
    RHUnk00641782 lock;
    Node *y = x->m_left;
    x->m_left = y->m_right;
    if (y->m_right != (Node *)g_unk0x006c0b30)
        y->m_right->m_parent = x;
    y->m_parent = x->m_parent;
    if (x == m_head->m_parent)
        m_head->m_parent = y;
    else if (x == x->m_parent->m_right)
        x->m_parent->m_right = y;
    else
        x->m_parent->m_left = y;
    y->m_right = x;
    x->m_parent = y;
}

// FUNCTION: GAME 0x005094a0
RHFrameHolderRowMap::Iterator RHUnk005074d0::FUN_005094a0(Node *x, Node *y, const Value &value)
{
    RHUnk00641782 lock;
    Node *z = (Node *)operator new(sizeof(Node));
    z->m_parent = y;
    z->m_color = 0;
    z->m_left = (Node *)g_unk0x006c0b30;
    z->m_right = (Node *)g_unk0x006c0b30;
    std::_Construct((Value *)&z->m_key, value);
    ++m_size;
    if (y == m_head || x != (Node *)g_unk0x006c0b30 || value.m_key < y->m_key)
    {
        y->m_left = z;
        if (y == m_head)
        {
            m_head->m_parent = z;
            m_head->m_right = z;
        }
        else if (y == m_head->m_left)
            m_head->m_left = z;
    }
    else
    {
        y->m_right = z;
        if (y == m_head->m_right)
            m_head->m_right = z;
    }
    for (x = z; x != m_head->m_parent && x->m_parent->m_color == 0; )
        if (x->m_parent == Left(x->m_parent->m_parent))
        {
            y = x->m_parent->m_parent->m_right;
            if (y->m_color == 0)
            {
                x->m_parent->m_color = 1;
                y->m_color = 1;
                x->m_parent->m_parent->m_color = 0;
                x = x->m_parent->m_parent;
            }
            else
            {
                if (x == x->m_parent->m_right)
                {
                    x = x->m_parent;
                    Lrotate(x);
                }
                x->m_parent->m_color = 1;
                x->m_parent->m_parent->m_color = 0;
                Rrotate(x->m_parent->m_parent);
            }
        }
        else
        {
            y = Left(x->m_parent->m_parent);
            if (y->m_color == 0)
            {
                x->m_parent->m_color = 1;
                y->m_color = 1;
                x->m_parent->m_parent->m_color = 0;
                x = x->m_parent->m_parent;
            }
            else
            {
                if (x == x->m_parent->m_left)
                {
                    x = x->m_parent;
                    Rrotate(x);
                }
                x->m_parent->m_color = 1;
                x->m_parent->m_parent->m_color = 0;
                Lrotate(x->m_parent->m_parent);
            }
        }
    m_head->m_parent->m_color = 1;
    return RHFrameHolderRowMap::Iterator((RHFrameHolderRowMap::Node *)z);
}

static inline RHFrameHolderRowMap::Node *FrameHolderRowMax(RHFrameHolderRowMap::Node *node)
{
    RHUnk00641782 lock;
    while (node->m_right != g_unk0x006c0b2c)
        node = node->m_right;
    return node;
}

// FUNCTION: GAME 0x005097a0
void RHFrameHolderRowMap::Iterator::FUN_005097a0()
{
    RHUnk00641782 lock;
    if (m_node->m_color == 0 && m_node->m_parent->m_parent == m_node)
        m_node = m_node->m_right;
    else if (Left(m_node) != g_unk0x006c0b2c)
        m_node = FrameHolderRowMax(Left(m_node));
    else
    {
        Node *parent;
        while (m_node == (parent = m_node->m_parent)->m_left)
            m_node = parent;
        m_node = parent;
    }
}

static inline RHFrameHolderRowMap::Node *FrameHolderRowMin(RHFrameHolderRowMap::Node *node)
{
    RHUnk00641782 lock;
    while (node->m_left != g_unk0x006c0b2c)
        node = node->m_left;
    return node;
}

// FUNCTION: GAME 0x00509860
void RHFrameHolderRowMap::Iterator::FUN_00509860()
{
    RHUnk00641782 lock;
    if (m_node->m_right != g_unk0x006c0b2c)
        m_node = FrameHolderRowMin(m_node->m_right);
    else
    {
        Node *parent;
        while (m_node == (parent = m_node->m_parent)->m_right)
            m_node = parent;
        if (m_node->m_right != parent)
            m_node = parent;
    }
}

static inline RHUnk005074d0::Node *FrameHolderShortMax(RHUnk005074d0::Node *node)
{
    RHUnk00641782 lock;
    while (node->m_right != (RHUnk005074d0::Node *)g_unk0x006c0b30)
        node = node->m_right;
    return node;
}

// FUNCTION: GAME 0x005099c0
void RHUnk005074d0::Iterator::FUN_005099c0()
{
    RHUnk00641782 lock;
    if (m_node->m_color == 0 && m_node->m_parent->m_parent == m_node)
        m_node = m_node->m_right;
    else if (Left(m_node) != (Node *)g_unk0x006c0b30)
        m_node = FrameHolderShortMax(Left(m_node));
    else
    {
        Node *parent;
        while (m_node == (parent = m_node->m_parent)->m_left)
            m_node = parent;
        m_node = parent;
    }
}

static inline RHUnk00507500::Node *FrameHolderShortMin(RHUnk00507500::Node *node)
{
    RHUnk00641782 lock;
    while (node->m_left != g_unk0x006c0b30)
        node = node->m_left;
    return node;
}

// FUNCTION: GAME 0x00509a80
void RHUnk00507500::Iterator::FUN_00509a80()
{
    RHUnk00641782 lock;
    if (m_node->m_right != g_unk0x006c0b30)
        m_node = FrameHolderShortMin(m_node->m_right);
    else
    {
        Node *parent;
        while (m_node == (parent = m_node->m_parent)->m_right)
            m_node = parent;
        if (m_node->m_right != parent)
            m_node = parent;
    }
}

void RHFrameHolder::Emit(SBResourceManager *resources, SBArray<SBGeoVector2D> &vectors)
{
    unsigned short count;
    InitializeSpriteBank();
    AddRowFromResource(resources, 0, count, vectors);
}

void EmitFrameHolderWidened(RHEngine *engine, RHUnk00506e00 *array, unsigned int count, const RHFrameHolderRecord &value)
{
    engine->FUN_004d2340(15);
    RHFrameHolder *holder = 0;
    holder->FUN_00504b10(0, 0, 0);
    array->FUN_00506e00();
    array->FUN_00507320(0, 0);
    array->FUN_00507020(0, count, value);
}

void EmitFrameHolderMaps(RHFrameHolderRowMap *rows, RHUnk005074d0 *strings, RHUnk005074d0::Value &value)
{
    unsigned long key = 0;
    rows->Insert(RHFrameHolderRowMap::Value(0, 0));
    rows->Find(key);
    RHFrameHolderRowMap::Iterator it = rows->End();
    it.FUN_00509860();
    rows->FUN_00508000(it.m_node);
    strings->FUN_005074d0(value);
}

void EmitFrameHolderTree(RHUnk00507500 *tree, RHFrameHolder *holder, SBFile &file)
{
    tree->FUN_00509030();
    tree->FUN_00504590();
    holder->FUN_005051a0(0, file);
}


void EmitFrameHolderAssigned(RHFrameHolder *holder, void *mapping, unsigned short *pixels,
    unsigned short width, unsigned short height, unsigned long pitch, unsigned short key)
{
    holder->FUN_00505170(key);
    holder->FUN_00504bd0((unsigned long)pixels, width, height, pitch, key);
    holder->FUN_00504c50((unsigned long)pixels, width, height, pitch, key);
}
