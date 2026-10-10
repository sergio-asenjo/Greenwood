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

// parked (69.61%): STL pair construction and dictionary cleanup differ.
// STUB: GAME 0x00504040
bool RHFrameHolder::InitializeSpriteBank()
{
    std::map<unsigned short, unsigned short> dictionaries;
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
        record.m_width = *(unsigned short *)bytes;
        record.m_height = *(unsigned short *)(bytes + 2);
        record.m_size = *(unsigned long *)(bytes + 8);
        record.m_data = opened + ((*(unsigned long *)(bytes + 4) >> 1) * 2);
        record.m_0c = 0;
        record.m_10 = true;
        record.m_12 = dictionaries[*(unsigned short *)(bytes + 12)];
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

// STUB: GAME 0x00505980
unsigned long RHFrameHolder::FUN_00505980(unsigned long surface, unsigned long &size, unsigned short &width, unsigned short &height, long &x, long &y)
{
    RHUnk00613e90 pixels;
    unsigned int used = 0;
    RHUnkFXDraw *draw = *(RHUnkFXDraw **)((char *)this + 4);
    if (!draw->Unk005e5a00(surface, pixels, 0))
        return 0;
    if (draw->m_depth != 16)
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
        for (unsigned int i = 0; i < width; ++i, ++pixel)
        {
            if (*pixel != 0x7c0)
            {
                if (left > i) left = i;
                if (right < i) right = i;
                if (top > outputRow) top = outputRow;
                if (bottom < outputRow) bottom = outputRow;
            }
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
        temporary[used++] = first;
        for (unsigned int reverse = width - 1; reverse > 0; --reverse)
            if (row[rowOffset + reverse] != 0x7c0 && last == ~0u)
                last = reverse;
        temporary[used++] = last;
        if (last != ~0u && first <= last)
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
        source += pitch;
        rowOffset += pitch;
    }
    size = used * 2;
    unsigned short *result = (unsigned short *)operator new(size * 2);
    memcpy(result, temporary, size);
    operator delete(temporary);
    draw = *(RHUnkFXDraw **)((char *)this + 4);
    if (draw->m_depth != 16)
        FUN_00504bd0((unsigned long)pixels.m_data, pixels.m_width, pixels.m_height, pixels.m_pitch, 31);
    draw->Unk005e5ea0(pixels);
    return (unsigned long)result;
}

// parked (46.79%): container/frame scheduling remains unmatched.
// STUB: GAME 0x00505cd0
unsigned long RHFrameHolder::AddRowFromResource(SBResourceManager *resources, unsigned long row, unsigned short &count, SBArray<SBGeoVector2D> &vectors)
{
    vectors.RemoveAll();
    unsigned long first;
    unsigned long surface;
    long y;
    if (m_rows.Find(row) != m_rows.End())
    {
        count = resources->FUN_00600550(row);
        first = m_rows.Insert(RHFrameHolderRowMap::Value(row, 0)).first.m_node->m_value;
        for (unsigned long i = first; i < first + count; ++i)
        {
            long x;
            if (!resources->FUN_00600920(row, i - first, surface))
                SBAssert(1, g_frameHolderFile, 1208, g_frameHolderSurfaceError);
            unsigned long data = FUN_00505980(surface, m_frames[i].m_size, m_frames[i].m_width, m_frames[i].m_height, x, y);
            operator delete((void *)data);
            vectors.InsertLast(SBGeoVector2D((float)x, (float)y));
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
            m_frames[i].m_data = FUN_00505980(surface, m_frames[i].m_size, m_frames[i].m_width, m_frames[i].m_height, i, y);
            m_frames[i].m_12 = 0xffff;
            FUN_00504b10(m_frames[i].m_data, m_frames[i].m_size, g_pEngine->FUN_004d2340(15));
            vectors.InsertLast(SBGeoVector2D((float)i, (float)y));
        }
        m_rows[row] = first;
    }
    return first;
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

// Parked: EH-state store and return-slot load scheduled before the root reset.
// STUB: GAME 0x00507500
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
        m_head->m_parent = g_unk0x006c0b30;
        m_size = 0;
        m_head->m_left = m_head;
        m_head->m_right = m_head;
        return begin();
    }
    while (first.m_node != last.m_node)
    {
        Iterator previous = first;
        first.FUN_00509a80();
        FUN_00508a80(previous);
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

// Parked: VC6 inlines the std::_Construct value copy; the target calls it out of line.
// STUB: GAME 0x005094a0
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
        if (x->m_parent == x->m_parent->m_parent->m_left)
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
            y = x->m_parent->m_parent->m_left;
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

// Parked: target shrink-wraps push esi into the _Max branch; VC6 pushes it in the prologue.
// STUB: GAME 0x005097a0
void RHFrameHolderRowMap::Iterator::FUN_005097a0()
{
    RHUnk00641782 lock;
    if (m_node->m_color == 0 && m_node->m_parent->m_parent == m_node)
        m_node = m_node->m_right;
    else if (m_node->m_left != g_unk0x006c0b2c)
        m_node = FrameHolderRowMax(m_node->m_left);
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

// Parked: target shrink-wraps push esi into the _Max branch; VC6 pushes it in the prologue.
// STUB: GAME 0x005099c0
void RHUnk005074d0::Iterator::FUN_005099c0()
{
    RHUnk00641782 lock;
    if (m_node->m_color == 0 && m_node->m_parent->m_parent == m_node)
        m_node = m_node->m_right;
    else if (m_node->m_left != (Node *)g_unk0x006c0b30)
        m_node = FrameHolderShortMax(m_node->m_left);
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
