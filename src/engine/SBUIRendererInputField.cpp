#include "SBNullstr.h"
#include "SBUIRendererInputField.h"
#include "SBUIRenderer.h"
#include "SBFont.h"
#include "SBUIRendererListbox.h"

DECOMP_SIZE_ASSERT(SBUIInputFieldNode, 0x10)
DECOMP_SIZE_ASSERT(SBUIInputFieldTextUnk, 0x20)
DECOMP_SIZE_ASSERT(SBUIInputFieldUnkObject, 0x04)
DECOMP_SIZE_ASSERT(SBUIInputFieldUnkResource, 0x1c)
DECOMP_SIZE_ASSERT(SBUIInputFieldUnk00621440, 0x90)
DECOMP_SIZE_ASSERT(SBGeoPoint2D, 0x08)
DECOMP_SIZE_ASSERT(SBGeoVector2D, 0x08)
DECOMP_SIZE_ASSERT(SBGeoBoundingBox2D, 0x14)
DECOMP_SIZE_ASSERT(RHMapBox, 0x14)
DECOMP_SIZE_ASSERT(RHMobileUnk006100e0, 0x10)
DECOMP_SIZE_ASSERT(RHMobileUnk00607da0, 0x14)
DECOMP_SIZE_ASSERT(SBUIInputFieldDrawUnk, 0x30)
DECOMP_SIZE_ASSERT(RHMapWideText, 0x10)

void SBAssert(int, const char *, int, const char *, ...);
namespace std { void _Xlen(); }
extern float g_unk0x006775d8;
void FUN_0048be30();

class RHUnkFXDraw
{
public:
    unsigned short FUN_005e56c0(unsigned long);
    unsigned short FUN_005e5750(unsigned long);
};

class SBDrawManager
{
public:
    void BlitAlphaKeying(unsigned long, unsigned long, unsigned long,
        SBGeoBoundingBox2D *, unsigned short, unsigned short, unsigned long);
};

class RHUnk00600820
{
public:
    bool ResolveSurface(void *, unsigned int, float *);
};

// SIZE 0x04
class SBUIInputFieldFontHeight
{
public:
    virtual void v0() = 0; // vtable+0x00
    virtual void v1() = 0; // vtable+0x04
    virtual void v2(unsigned int) = 0; // vtable+0x08
    virtual void v3() = 0; // vtable+0x0c
    virtual void v4() = 0; // vtable+0x10
    virtual void v5() = 0; // vtable+0x14
    virtual void v6() = 0; // vtable+0x18
    virtual unsigned int v7() = 0; // vtable+0x1c
};

DECOMP_SIZE_ASSERT(SBUIInputFieldFontHeight, 0x04)

// GLOBAL: GAME 0x006775dc
// ?_C@?1??_Nullstr@?$basic_string@GU?$char_traits@G@std@@V?$allocator@G@2@@std@@CAPBGXZ@4GB

// FUNCTION: GAME 0x0061df50
unsigned int SBUIInputFieldTextUnk::FUN_0061df50()
{
    return m_0c - 1;
}

// Parked: the linked-list copy is captured, but the compiler emits a larger temporary string frame and different allocator/copy operations; three shapes scored 34.75%, 36.24%, and 45.85%.
// STUB: GAME 0x0061df60
RHMapWideText SBUIInputFieldUnk00621440::FUN_0061df60()
{
    std::wstring temporary;
    SBUIInputFieldNode *head = *(SBUIInputFieldNode **)((char *)this + 8);
    for (SBUIInputFieldNode *node = head->m_00; node != head; node = node->m_00)
        temporary.append(1, (wchar_t)node->m_08);
    RHMapWideText result;
    result.FUN_004580c0(temporary, 0, std::wstring::npos);
    return result;
}

// SYNTHETIC: GAME 0x004d7770
// ??1SBUIInputFieldDrawUnk@@QAE@XZ

// LIBRARY: GAME 0x005cf1e0
// ??0?$basic_string@GU?$char_traits@G@std@@V?$allocator@G@2@@std@@QAE@ABV01@@Z

// FUNCTION: GAME 0x005d0880
std::wstring FUN_005d0880(const std::wstring &left, const std::wstring &right)
{
    std::wstring result(left);
    result.append(right);
    return result;
}

// Parked: geometry temporaries and counted helper operands differ.
// STUB: GAME 0x006084a0
bool SBGeoBoundingBox2D::FUN_006084a0(const SBGeoBoundingBox2D &other)
{
    RHMobileUnk006100e0 span;
    SBGeoPoint2D first(0, 0);
    SBGeoPoint2D second(0, 0);
    ((RHMobileUnk0060a820 *)&span)->FUN_0060a820(first, second);
    if (!other.m_10)
        return false;
    RHMobileUnk006100e0 candidate;
    ((RHMobileUnk0060a820 *)&candidate)->FUN_0060a820(other.m_00, other.m_08);
    ((SBUIInputFieldBoxCalls *)&span)->FUN_0060a860(candidate);
    return ((SBUIInputFieldBoxCalls *)this)->FUN_00608450(*(SBGeoBoundingBox2D *)&span);
}

// FUNCTION: GAME 0x006138e0
SBUIInputFieldDrawUnk::SBUIInputFieldDrawUnk()
    : m_10(0), m_14(0), m_18(2), m_1c(0, 0, 0, 0)
{
}

// Parked: one counted branch displacement still differs after two loop shapes.
// STUB: GAME 0x00613c50
int FUN_00613c50(const unsigned short *left, const unsigned short *right, unsigned int count)
{
    if (count > 0)
    {
        do
        {
            if (*left != *right)
                return *left < *right ? -1 : 1;
            ++left;
            ++right;
        } while (--count);
    }
    return 0;
}

// FUNCTION: GAME 0x00613e40
bool FUN_00613e40(unsigned char flag, unsigned int count, const void *first, const void *last)
{
    return count >= 2 && (const char *)first + 0x10 != last && flag == 0;
}

// FUNCTION: GAME 0x00613e70
RHMapBox *SBUIInputFieldDrawUnk::FUN_00613e70()
{
    return &m_1c;
}

// FUNCTION: GAME 0x00613e80
unsigned int SBUIInputFieldDrawUnk::FUN_00613e80()
{
    return m_10;
}

// Parked: font parameter order and floating-point compare lowering differ.
// STUB: GAME 0x006141e0
bool FUN_006141e0(float threshold, const std::wstring &text, void *font)
{
    const unsigned short *character = (const unsigned short *)text.c_str();
    for (unsigned int i = 0; i < text.size(); ++i, ++character)
        if (((SBFontUnk0061e840 *)font)->FUN_0061ea50((void *)character) <= threshold)
            return true;
    return false;
}

inline void SetSBUIInputFieldBoxX(SBGeoBoundingBox2D &box, float first, float last)
{
    box.m_00.m_x = first;
    box.m_08.m_x = last;
    box.m_10 = true;
}

inline void SetSBUIInputFieldBoxY(SBGeoBoundingBox2D &box, float first, float last)
{
    box.m_00.m_y = first;
    box.m_08.m_y = last;
    box.m_10 = true;
}

// Parked: x87 operand order, alignment flags and result-slot scheduling differ.
// STUB: GAME 0x00614bf0
bool SBUIInputFieldDrawUnk::FUN_00614bf0(void *font, std::wstring *text, const SBGeoPoint2D &point, unsigned int flags)
{
    SBGeoBoundingBox2D box;
    int width = ((SBFontUnk0061e840 *)font)->FUN_0061ea50(text);
    int height = ((SBUIListboxUnk0061e890 *)font)->FUN_0061e890();
    SetSBUIInputFieldBoxY(box, point.m_y, point.m_y + height);
    if (flags & 1)
    {
        SetSBUIInputFieldBoxX(box, point.m_x, point.m_x + ((float)(m_18 * 2) + width));
    }
    else if (!(flags & 6))
    {
        if (flags & 8)
        {
            SetSBUIInputFieldBoxX(box, point.m_x - width - (int)(m_18 * 2), point.m_x);
        }
    }
    else
    {
        float padding = (float)m_18;
        float first = point.m_x - width / 2 - padding;
        SetSBUIInputFieldBoxX(box, first, first + (width + padding));
        flags = (flags & ~6) | 1;
    }
    return FUN_00614230(font, text, box, flags, 0, 0) != 0;
}

#include <vector>

std::wstring *FUN_00606780(const std::wstring *, const std::wstring *, std::wstring *);

class RHCampaignWideString;
class RHCampaignWideStrings
{
public:
    void FUN_00459620(RHCampaignWideString *, unsigned, const RHCampaignWideString &);
};

class SBUIInputFieldSplitStrings : public std::vector<std::wstring>
{
public:
    void Clear()
    {
        std::wstring *last = FUN_00606780(end(), end(), begin());
        typedef void (SBUIInputFieldSplitStrings::*Destroy)(std::wstring *, std::wstring *);
        Destroy destroy = &SBUIInputFieldSplitStrings::_Destroy;
        (this->*destroy)(last, end());
        _Last = last;
    }
    void Append(const std::wstring &value)
    {
        ((RHCampaignWideStrings *)this)->FUN_00459620(
            (RHCampaignWideString *)end(), 1, (const RHCampaignWideString &)value);
    }
};

class SBUIInputFieldSplitUnk
{
public:
    ~SBUIInputFieldSplitUnk();
    void *FUN_00614e40(unsigned flags);
    void FUN_00614e60(const std::wstring &text, const std::wstring &separators);
    unsigned m_vptr;
    std::vector<std::wstring> m_tokens;
    std::vector<std::wstring> m_separators;
};

// FUNCTION: GAME 0x00614d80
SBUIInputFieldSplitUnk::~SBUIInputFieldSplitUnk()
{
    m_vptr = 0x0067a8f8;
}

// FUNCTION: GAME 0x00614e40
void *SBUIInputFieldSplitUnk::FUN_00614e40(unsigned flags)
{
    this->~SBUIInputFieldSplitUnk();
    if (flags & 1)
        operator delete(this);
    return this;
}

// Parked: iterator storage, append npos load and temporary assign inline depth differ.
// STUB: GAME 0x00614e60
void SBUIInputFieldSplitUnk::FUN_00614e60(const std::wstring &text, const std::wstring &separators)
{
    std::wstring token;
    SBUIInputFieldSplitStrings &tokens = (SBUIInputFieldSplitStrings &)m_tokens;
    SBUIInputFieldSplitStrings &separatorTokens = (SBUIInputFieldSplitStrings &)m_separators;
    tokens.Clear();
    typedef std::wstring *(std::vector<std::wstring>::*Erase)(std::wstring *, std::wstring *);
    Erase erase = &std::vector<std::wstring>::erase;
    (m_separators.*erase)(m_separators.begin(), m_separators.end());
    typedef unsigned (std::wstring::*Find)(const unsigned short *, unsigned, unsigned) const;
    Find find = &std::wstring::find;
    for (std::wstring::const_iterator character = text.begin(); character != text.end(); ++character)
    {
        unsigned short value = *character;
        if ((separators.*find)(&value, 0, 1) == (unsigned)-1)
            token.append(character, 1);
        else
        {
            tokens.Append(token);
            token.erase(0, (unsigned)-1);
            separatorTokens.Append(std::wstring(character, 1));
        }
    }
    tokens.Append(token);
}

void EmitSBUIInputFieldSplit(SBUIInputFieldSplitUnk *split, const std::wstring &text)
{
    split->FUN_00614e40(0);
    split->FUN_00614e60(text, text);
}

// FUNCTION: GAME 0x0061dd00
unsigned int SBUIInputFieldTextUnk::FUN_0061dd00()
{
    SBUIInputFieldNode *head = m_08;
    unsigned int total = 0;
    for (SBUIInputFieldNode *node = head->m_00; node != head; node = node->m_00)
    {
        unsigned int width = node->m_0c;
        total += width;
        if (node == m_10)
            break;
    }
    return total;
}

// Parked: scalar-slot scheduling and counted font/copy operands differ.
// STUB: GAME 0x0061dd50
RHMapWideText SBUIInputFieldTextUnk::FUN_0061dd50(unsigned int direction, unsigned int width)
{
    RHMapWideText result;
    unsigned int total = 0;
    SBUIInputFieldNode *node = m_10;
    if (direction == 1 && node != m_08)
        node = node->m_00;
    while (node != m_08 && node != m_08->m_00)
    {
        unsigned short character = node->m_08;
        SBFontUnk0061e840 *font = (SBFontUnk0061e840 *)m_14;
        unsigned int advance = font->FUN_0061e850(character);
        total += advance + font->v8();
        if (total > width)
            break;
        if (direction == 0)
        {
            if (std::wstring::npos - result.m_size <= 1)
                std::_Xlen();
            unsigned int size = result.m_size + 1;
            if (result.Grow(size, false))
            {
                wmemmove(result.m_chars + 1, result.m_chars, result.m_size);
                wmemcpy(result.m_chars, &character, 1);
                result.m_chars[result.m_size = size] = 0;
            }
            node = node->m_04;
        }
        else if (direction == 1)
        {
            unsigned int offset = result.m_size;
            if (std::wstring::npos - result.m_size <= 1)
                std::_Xlen();
            unsigned int size = result.m_size + 1;
            if (result.Grow(size, false))
            {
                wmemmove(result.m_chars + offset + 1, result.m_chars + offset, result.m_size - offset);
                wmemcpy(result.m_chars + offset, &character, 1);
                result.m_chars[result.m_size = size] = 0;
            }
            node = node->m_00;
        }
    }
    return result;
}
// FUNCTION: GAME 0x0061e230
char SBUIInputFieldTextUnk::FUN_0061e230()
{
    return m_1c;
}

// Parked: list traversal and node relinking are present, but VC6 emits a different cursor branch and link-store order; five shapes scored 57.78%, 58.43%, 58.14%, 58.14%, and 67.44%.
// STUB: GAME 0x0061e2b0
void SBUIInputFieldTextUnk::FUN_0061e2b0(unsigned int index)
{
    SBUIInputFieldNode *node;
    if (index == 0xffffffff)
    {
        node = m_10;
    }
    else
    {
        if (m_0c - 1 <= index)
            return;
        node = m_08->m_00;
        for (unsigned int count = index + 1; count != 0; --count)
            node = node->m_00;
    }
    if (node != m_08 && node != m_08->m_00)
    {
        if (node == m_10)
            m_10 = m_10->m_04;
        node->m_04->m_00 = node->m_00;
        node->m_00->m_04 = node->m_04;
        operator delete(node);
        --m_0c;
    }
}

class SBUIInputFieldUnk0061e180
{
public:
    char m_00[8];
    SBUIInputFieldNode *m_08;
    unsigned int m_0c;
    SBUIInputFieldNode *m_10;
    SBFontUnk0061e840 *m_14;
    char m_18[8];
    unsigned int m_20;
    bool Insert(unsigned short character);
};

// Parked: insertion semantics are identified, but VC6 register allocation and local character storage differ; five shapes scored 20.56%, 20.56%, 5.36%, 37.40%, and 15.65%.
// STUB: GAME 0x0061e180
bool SBUIInputFieldUnk0061e180::Insert(unsigned short character)
{
    unsigned int characterValue = character;
    if (m_20 != 0xffffffff && m_20 <= m_0c)
        return false;
    if (character == 0)
        return false;
    SBUIInputFieldNode *position = m_10;
    if (position != m_08)
        position = position->m_00;
    int width = m_14->FUN_0061e850((unsigned short)characterValue) + m_14->v8();
    SBUIInputFieldNode *node = (SBUIInputFieldNode *)operator new(0x10);
    SBUIInputFieldNode *previous = position->m_04;
    node->m_00 = position;
    node->m_04 = previous;
    previous->m_00 = node;
    position->m_04 = node;
    node->m_08 = (unsigned short)characterValue;
    node->m_0c = width;
    ++m_0c;
    m_10 = node;
    return true;
}

// Parked: the switch dispatch still differs in branch-table and register setup.
// STUB: GAME 0x0061e240
void SBUIInputFieldTextUnk::FUN_0061e240(unsigned int direction)
{
    SBUIInputFieldNode *head = m_08;
    SBUIInputFieldNode *node = m_10;
    switch (direction)
    {
    case 0:
        if (node != head->m_00)
            m_10 = node->m_04;
        return;
    case 1:
        if (node != head)
        {
            node = node->m_00;
            m_10 = node;
            if (node == head)
                m_10 = node->m_04;
        }
        return;
    case 2:
        m_10 = head->m_00;
        return;
    case 3:
        m_10 = head->m_04;
        return;
    }
}

// FUNCTION: GAME 0x0061e320
void SBUIInputFieldTextUnk::FUN_0061e320(unsigned char value)
{
    m_1c = value;
    FUN_0061e240(3);
}

// Parked: the list reset and text-node insertion semantics are identified, but the temporary list node/container helper setup does not match the target.
// STUB: GAME 0x0061e060
void SBUIInputFieldUnk00621440::FUN_0061e060(RHMapWideText *text)
{
    SBUIInputFieldNode *head = *(SBUIInputFieldNode **)((char *)this + 8);
    SBUIInputFieldNode *node = head->m_00;
    while (node != head)
    {
        SBUIInputFieldNode *next = node->m_00;
        node->m_04->m_00 = next;
        next->m_04 = node->m_04;
        operator delete(node);
        node = next;
    }
    *(unsigned int *)((char *)this + 0x0c) = 0;
    SBUIInputFieldNode *empty = (SBUIInputFieldNode *)operator new(0x10);
    empty->m_00 = head;
    empty->m_04 = head->m_04;
    head->m_04->m_00 = empty;
    head->m_04 = empty;
    empty->m_08 = 0;
    empty->m_0c = 0;
    ++*(unsigned int *)((char *)this + 0x0c);
    SBFontUnk0061e840 *font = *(SBFontUnk0061e840 **)((char *)this + 0x14);
    for (unsigned int i = 0; i != text->m_size; ++i)
    {
        unsigned short character = text->m_chars[i];
        SBUIInputFieldNode *inserted = (SBUIInputFieldNode *)operator new(0x10);
        SBUIInputFieldNode *previous = head->m_04;
        inserted->m_00 = head;
        inserted->m_04 = previous;
        previous->m_00 = inserted;
        head->m_04 = inserted;
        inserted->m_08 = character;
        inserted->m_0c = font->FUN_0061e850(character) + font->v8();
        ++*(unsigned int *)((char *)this + 0x0c);
    }
    *(SBUIInputFieldNode **)((char *)this + 0x10) = head->m_00;
}

// Parked: copy-on-write assignment is modeled, but the generated return-temporary layout and inlined string-copy branches still differ; three shapes scored 26.67%, 26.67%, and 80.15%.
// STUB: GAME 0x0061e340
void SBUIInputFieldUnk00621440::FUN_0061e340()
{
    RHMapWideText text = FUN_0061df60();
    *(std::wstring *)((char *)this + 0x38) = (const std::wstring &)text;
}

// FUNCTION: GAME 0x0061e4b0
void SBUIInputFieldUnk00621440::FUN_0061e4b0()
{
    FUN_0061e060((RHMapWideText *)((char *)this + 0x38));
}

// Parked: global-bit branch and fixed-address tail target differ.
// LIBRARY: GAME 0x0061e4c0
void FUN_0061e4c0()
{
    *(unsigned char *)0x006c223c |= 1;
    FUN_0048be30();
}

// FUNCTION: GAME 0x00621430
void SBUIInputFieldUnk00621440::FUN_00621430(unsigned int value)
{
    ((SBUIUnk0060d530 *)this)->FUN_0060d530(value);
}

// FUNCTION: GAME 0x00621440
void SBUIInputFieldUnk00621440::FUN_00621440(SBUIInputFieldUnkResource *resource)
{
    m_6c = resource;
    if (m_64)
        m_64->v2(1);
    m_64 = m_6c->m_14;
    m_68 = m_6c->m_18;
}

// Parked: renderer temporary/EH layout and counted helper operands differ.
// STUB: GAME 0x00621470
bool SBUIInputFieldUnk00621440::FUN_00621470(unsigned int id)
{
    RHMapWideText before;
    RHMapWideText after;
    SBGeoPoint2D offset;
    SBUIInputFieldDrawUnk draw;
    void *font = m_84 == 1 ? (void *)m_64 : m_68;
    float height = m_70.m_08.m_y - m_70.m_00.m_y;
    offset.m_x = 0;
    offset.m_y = (height - ((SBUIInputFieldFontHeight *)font)->v7()) * g_unk0x006775d8;
    if (!((SBUIUnk0060dae0 *)this)->FUN_0060dae0(id))
        return false;
    if (!m_84)
        return false;
    SBUIInputFieldTextUnk *text = (SBUIInputFieldTextUnk *)m_6c;
    unsigned int width = text->FUN_0061dd00();
    float available = m_70.m_08.m_x - m_70.m_00.m_x;
    int shift = available <= width ? (int)(available - width) : 0;
    unsigned int cursor = width + shift;
    typedef std::wstring &(std::wstring::*Assign)(const std::wstring &, unsigned, unsigned);
    Assign assign = &std::wstring::assign;
    (((std::wstring *)&before)->*assign)((const std::wstring &)text->FUN_0061dd50(0, cursor), 0, std::wstring::npos);
    (((std::wstring *)&after)->*assign)((const std::wstring &)text->FUN_0061dd50(1, (unsigned int)(available - width - shift)), 0, std::wstring::npos);
    unsigned int surface = 0;
    if (m_00[0x60] == 1 && !text->FUN_0061e230())
    {
        SBGeoPoint2D position = m_70.m_00.Unk005fc190(offset);
        std::wstring joined = FUN_005d0880(*(std::wstring *)&before, *(std::wstring *)&after);
        draw.FUN_00614bf0(font, &joined, position, 1);
        std::wstring *value = (std::wstring *)(m_00 + 0x50);
        int textWidth = ((SBFontUnk0061e840 *)font)->FUN_0061ea50(value);
        SBGeoPoint2D left(m_70.m_00.m_y, m_70.m_08.m_x - textWidth);
        SBGeoPoint2D location = left.Unk005fc190(offset);
        draw.FUN_00614bf0(font, value, location, 1);
    }
    else
    {
        SBGeoPoint2D position = m_70.m_00.Unk005fc190(offset);
        std::wstring joined = FUN_005d0880(*(std::wstring *)&before, *(std::wstring *)&after);
        draw.FUN_00614bf0(font, &joined, position, 1);
    }
    if (text->FUN_0061e230())
    {
        SBGeoPoint2D position;
        RHUnk00600820 *resources = *(RHUnk00600820 **)(m_00 + 4);
        if (!resources->ResolveSurface(*(void **)(m_00 + 0x38), 5, (float *)&surface))
        {
            SBAssert(0,
                // STRING: GAME 0x006bb8d8
                "P:\\Robin Hood\\SBLibNG\\SBUIRendererInputField.cpp", 0xbd,
                // STRING: GAME 0x006bb90c
                "Unable to retrieve a resource for the input field renderer");
            return false;
        }
        SBGeoVector2D displacement(SBGeoPoint2D((float)cursor, 0));
        position = m_70.m_00.Unk005fc190(displacement);
        RHUnkFXDraw *manager = *(RHUnkFXDraw **)(m_00 + 0x1c);
        SBGeoPoint2D upper(position.m_x, position.m_y);
        SBGeoPoint2D lower(position.m_x + manager->FUN_005e56c0(surface),
            position.m_y + manager->FUN_005e5750(surface));
        RHMapBox bounds(upper.m_x, upper.m_y, lower.m_x, lower.m_y);
        SBGeoBoundingBox2D clipped = ((SBGeoBoundingBox2D *)&bounds)->FUN_006090d0(m_88);
        ((SBDrawManager *)manager)->BlitAlphaKeying(surface, 0,
            *(unsigned int *)(m_00 + 0x20), &clipped, 0x1f, 0x41, 1);
    }
    return true;
}

// FUNCTION: GAME 0x00621c30
bool SBUIInputFieldUnk00621440::FUN_00621c30(const SBGeoBoundingBox2D &box)
{
    SBGeoPoint2D *origin = (SBGeoPoint2D *)(m_00 + 8);
    bool inside;
    {
        SBGeoVector2D displacement(*(SBGeoVector2D *)origin);
        inside = ((SBGeoBoundingBox2D *)origin)->FUN_006084a0(box.FUN_006090d0(displacement));
    }
    if (inside)
    {
        SBGeoVector2D displacement(*(SBGeoVector2D *)origin);
        ((RHMobileUnk00607da0 *)&m_70)->FUN_00607da0(*(RHMobileUnk00607da0 *)&box.FUN_006090d0(displacement));
        return true;
    }
    SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBUIRendererInputField.cpp", 0x14d,
        // STRING: GAME 0x006bb948
        "Unable to set the new text field box : the relative given box is not inside the widget bounding box");
    return false;
}

void SBUIInputFieldEmit(SBUIInputFieldUnk00621440 *renderer)
{
    SBUIInputFieldTextUnk *text = (SBUIInputFieldTextUnk *)renderer;
    text->FUN_0061dd00();
    text->FUN_0061e230();
    text->FUN_0061dd50(0, 0);
    ((SBGeoBoundingBox2D *)renderer)->FUN_006084a0(renderer->m_70);
    SBUIInputFieldDrawUnk draw;
    draw.FUN_00614bf0(0, 0, renderer->m_70.m_00, 0);
    FUN_005d0880(draw.m_00, draw.m_00);
    renderer->FUN_00621430(0);
    renderer->FUN_00621440(0);
    renderer->FUN_00621470(0);
    renderer->FUN_00621c30(renderer->m_70);
}

void SBUIInputFieldEmitAssigned(SBUIInputFieldDrawUnk *draw, const unsigned short *left,
    const unsigned short *right, unsigned char flag, const void *first, unsigned int count,
    const void *last, void *font, const std::wstring &text)
{
    FUN_00613c50(left, right, count);
    FUN_00613e40(flag, count, first, last);
    draw->FUN_00613e70();
    draw->FUN_00613e80();
    FUN_006141e0(0.0f, text, font);
}
