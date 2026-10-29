#include "SBNullstr.h"
#include "SBUIRendererInputField.h"
#include "SBUIRenderer.h"
#include "SBFont.h"
#include "SBUIRendererListbox.h"
#include "RHPortraitRenderer006212d0.h"
#include <stddef.h>

DECOMP_SIZE_ASSERT(SBUIInputFieldNode, 0x10)
DECOMP_SIZE_ASSERT(SBUIInputFieldTextUnk, 0x20)
DECOMP_SIZE_ASSERT(SBUIInputFieldUnkObject, 0x04)
DECOMP_SIZE_ASSERT(SBUIInputFieldUnkResource, 0x1c)
DECOMP_SIZE_ASSERT(SBUIInputFieldUnk00621440, 0x90)
DECOMP_SIZE_ASSERT(RHPortraitRenderer006212d0, 0x90)
DECOMP_STATIC_ASSERT(offsetof(RHPortraitRenderer006212d0, m_prompt) == 0x50)
DECOMP_STATIC_ASSERT(offsetof(RHPortraitRenderer006212d0, m_bounds) == 0x70)
DECOMP_STATIC_ASSERT(offsetof(RHPortraitRenderer006212d0, m_offset) == 0x88)
DECOMP_SIZE_ASSERT(SBGeoPoint2D, 0x08)
DECOMP_SIZE_ASSERT(SBGeoVector2D, 0x08)
DECOMP_SIZE_ASSERT(SBGeoBoundingBox2D, 0x14)
DECOMP_SIZE_ASSERT(RHMapBox, 0x14)
DECOMP_SIZE_ASSERT(RHMobileUnk006100e0, 0x10)
DECOMP_SIZE_ASSERT(RHMobileUnk00607da0, 0x14)
DECOMP_SIZE_ASSERT(SBUIInputFieldDrawUnk, 0x30)

void SBAssert(int, const char *, int, const char *, ...);
namespace std { void _Xlen(); }
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

// TEMPLATE: GAME 0x0046eb30 FOLDED
// ?erase@?$list@USBUIInputFieldCharacter@@V?$allocator@USBUIInputFieldCharacter@@@std@@@std@@QAE?AViterator@12@V312@@Z

// FUNCTION: GAME 0x0061df50
unsigned int SBUIInputFieldTextUnk::FUN_0061df50()
{
    return m_0c - 1;
}

// Parked: string construction and return-copy inline boundaries differ.
// STUB: GAME 0x0061df60
std::wstring SBUIInputFieldUnk00621440::FUN_0061df60()
{
    std::wstring temporary;
    for (SBUIInputFieldNode *node = (*(SBUIInputFieldNode **)((char *)this + 8))->m_00->m_00;
         node != *(SBUIInputFieldNode **)((char *)this + 8); node = node->m_00)
        temporary.append(&node->m_08, 1);
    return temporary;
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

// FUNCTION: GAME 0x006084a0
bool SBGeoBoundingBox2D::FUN_006084a0(const SBGeoBoundingBox2D &other)
{
    SBGeoSegment2D span(SBGeoPoint2D(0, 0), SBGeoPoint2D(0, 0));
    if (!other.m_10)
        return false;
    ((SBUIInputFieldBoxCalls *)&span)->FUN_0060a860(
        SBGeoSegment2D(other.m_00, other.m_08).Line());
    return ((SBUIInputFieldBoxCalls *)this)->FUN_00608450(*(SBGeoBoundingBox2D *)&span);
}

// FUNCTION: GAME 0x006138e0
SBUIInputFieldDrawUnk::SBUIInputFieldDrawUnk()
    : m_10(0), m_14(0), m_18(2), m_1c(0, 0, 0, 0)
{
}

// FUNCTION: GAME 0x00613c50
int FUN_00613c50(const unsigned short *left, const unsigned short *right, unsigned int count)
{
    while (count > 0)
    {
        if (*left != *right)
            return *left < *right ? -1 : 1;
        ++left;
        ++right;
        --count;
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
    bool rendered = FUN_00614230(font, text, box, flags, 0, 0) != 0;
    return rendered;
}

// FUNCTION: GAME 0x00614d70
void SBUIInputFieldDrawUnk::FUN_00614d70(char value)
{
    m_14 = value;
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
            std::wstring separator;
            typedef std::wstring &(std::wstring::*Assign)(const unsigned short *, unsigned int);
            Assign assign = &std::wstring::assign;
            (separator.*assign)(character, 1);
            separatorTokens.Append(separator);
        }
    }
    tokens.Append(token);
}

void EmitSBUIInputFieldSplit(SBUIInputFieldSplitUnk *split, const std::wstring &text)
{
    split->FUN_00614e40(0);
    split->FUN_00614e60(text, text);
}

#include "SBUIInputFieldCharacters.h"

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

// Parked: string insert/copy inline boundaries and scalar-slot scheduling differ.
// STUB: GAME 0x0061dd50
std::wstring SBUIInputFieldTextUnk::FUN_0061dd50(unsigned int direction, unsigned int width)
{
    unsigned int total = 0;
    std::wstring result;
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
            result.insert(0, &character, 1);
            node = node->m_04;
        }
        else if (direction == 1)
        {
            result.insert(result.size(), &character, 1);
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

// FUNCTION: GAME 0x0061e2b0
void SBUIInputFieldTextUnk::FUN_0061e2b0(unsigned int index)
{
    SBUIInputFieldCharacters &characters = *(SBUIInputFieldCharacters *)((char *)this + 4);
    SBUIInputFieldCharacters::iterator current;
    if (index != 0xffffffff)
    {
        if (index >= m_0c - 1)
            return;
        current = characters.begin();
        std::advance(current, index + 1);
    }
    else
    {
        current = *(SBUIInputFieldCharacters::iterator *)&m_10;
    }
    if (current != characters.end() && current != characters.begin())
    {
        if (current == *(SBUIInputFieldCharacters::iterator *)&m_10)
            --*(SBUIInputFieldCharacters::iterator *)&m_10;
        characters.erase(current);
    }
}

#include "SBUIInputFieldText.h"

// Parked: node and font registers are interchanged across list insertion.
// STUB: GAME 0x0061e180
bool RHPortraitText0061db10::Insert(unsigned short character)
{
    RHPortraitText0061db10 &text = *this;
    if (text.m_maximum != 0xffffffff && text.m_maximum <= text.m_characters.size())
        return false;
    if (character == 0)
        return false;
    SBUIInputFieldCharacters::iterator position = text.m_cursor;
    if (position != text.m_characters.end())
        ++position;
    SBUIInputFieldCharacter value;
    value.character = character;
    value.width = ((SBFontUnk0061e840 *)text.m_font)->FUN_0061e850(character)
        + ((SBFontUnk0061e840 *)text.m_font)->v8();
    text.m_cursor = text.m_characters.insert(position, value);
    return true;
}

// Parked: the switch dispatch still differs in branch-table and register setup.
// STUB: GAME 0x0061e240
void RHPortraitText0061db10::FUN_0061e240(unsigned int direction)
{
    SBUIInputFieldNode *&cursor = *(SBUIInputFieldNode **)&m_cursor;
    switch (direction)
    {
    case 1:
    {
        SBUIInputFieldNode *first = (*(SBUIInputFieldNode *volatile *)((char *)this + 8))->m_00;
        SBUIInputFieldNode *node = cursor;
        if (node != first)
            cursor = node->m_04;
        return;
    }
    case 0:
    {
        SBUIInputFieldNode *head = (SBUIInputFieldNode *)m_characters.end()._Mynode();
        SBUIInputFieldNode *node = cursor;
        if (node != head)
        {
            cursor = node->m_00;
            if (cursor == head)
            {
                SBUIInputFieldNode *last = cursor;
                cursor = last->m_04;
            }
        }
        return;
    }
    case 2:
    {
        SBUIInputFieldNode *head = (SBUIInputFieldNode *)m_characters.end()._Mynode();
        cursor = head->m_00;
        return;
    }
    case 3:
        cursor = (SBUIInputFieldNode *)m_characters.end()._Mynode();
        cursor = cursor->m_04;
        return;
    }
}

// FUNCTION: GAME 0x0061e320
void SBUIInputFieldTextUnk::FUN_0061e320(unsigned char value)
{
    m_1c = value;
    ((RHPortraitText0061db10 *)this)->FUN_0061e240(3);
}

// Parked: the list reset and text-node insertion semantics are identified, but the temporary list node/container helper setup does not match the target.
// STUB: GAME 0x0061e060
void SBUIInputFieldUnk00621440::FUN_0061e060(const std::wstring &text)
{
    SBUIInputFieldCharacters &characters = *(SBUIInputFieldCharacters *)((char *)this + 4);
    typedef SBUIInputFieldCharacters::iterator (SBUIInputFieldCharacters::*Erase)(SBUIInputFieldCharacters::iterator);
    Erase erase = &SBUIInputFieldCharacters::erase;
    for (SBUIInputFieldCharacters::iterator current = characters.begin(); current != characters.end();)
        (characters.*erase)(current++);
    SBUIInputFieldCharacter value;
    value.character = 0;
    value.width = 0;
    characters.insert(characters.end(), value);
    for (std::wstring::const_iterator character = text.begin(); character != text.end(); ++character)
    {
        value.character = *character;
        SBFontUnk0061e840 *font = *(SBFontUnk0061e840 **)((char *)this + 0x14);
        value.width = font->FUN_0061e850(*character) + font->v8();
        characters.insert(characters.end(), value);
    }
    SBUIInputFieldCharacters::iterator first = characters.begin();
    *(SBUIInputFieldNode **)((char *)this + 0x10) = *(SBUIInputFieldNode **)&first;
}

// FUNCTION: GAME 0x0061e340
void SBUIInputFieldUnk00621440::FUN_0061e340()
{
    *(std::wstring *)((char *)this + 0x38) = (const std::wstring &)FUN_0061df60();
}

// FUNCTION: GAME 0x0061e4b0
void SBUIInputFieldUnk00621440::FUN_0061e4b0()
{
    FUN_0061e060(*(const std::wstring *)((char *)this + 0x38));
}

// Parked: global-bit branch and fixed-address tail target differ.
// LIBRARY: GAME 0x0061e4c0
void FUN_0061e4c0()
{
    *(unsigned char *)0x006c223c |= 1;
    FUN_0048be30();
}

// FUNCTION: GAME 0x00621430
void RHPortraitRenderer006212d0::FUN_0060d530(unsigned int value)
{
    RHPortraitRenderer0060d470::FUN_0060d530(value);
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

inline std::wstring *SBUIInputFieldTextAddress(const std::wstring &text)
{
    return const_cast<std::wstring *>(&text);
}

// Parked: renderer temporary/EH layout and counted helper operands differ.
// STUB: GAME 0x00621470
bool SBUIInputFieldUnk00621440::FUN_00621470(unsigned int id)
{
    std::wstring before;
    std::wstring after;
    SBGeoVector2D offset;
    SBUIInputFieldDrawUnk draw;
    void *font = m_84 == 1 ? (void *)m_64 : m_68;
    SBGeoBoundingBox2D &box = m_70;
    float height = box.m_08.m_y - box.m_00.m_y;
    offset.m_x = 0;
    offset.m_y = (height - ((SBUIInputFieldFontHeight *)font)->v7()) * 0.5f;
    if (!((SBUIUnk0060dae0 *)this)->FUN_0060dae0(id))
        return false;
    if (!m_84)
        return false;
    unsigned int width = ((SBUIInputFieldTextUnk *)m_6c)->FUN_0061dd00();
    int shift = box.m_08.m_x - box.m_00.m_x <= width
        ? (int)(box.m_08.m_x - box.m_00.m_x - width) : 0;
    unsigned int cursor = width + shift;
    typedef std::wstring &(std::wstring::*Assign)(const std::wstring &, unsigned, unsigned);
    Assign assign = &std::wstring::assign;
    (before.*assign)(((SBUIInputFieldTextUnk *)m_6c)->FUN_0061dd50(0, cursor), 0, std::wstring::npos);
    (after.*assign)(((SBUIInputFieldTextUnk *)m_6c)->FUN_0061dd50(1,
        (unsigned int)(box.m_08.m_x - box.m_00.m_x - width - shift)), 0, std::wstring::npos);
    unsigned int surface;
    if (m_00[0x60] == 1 && !((SBUIInputFieldTextUnk *)m_6c)->FUN_0061e230())
    {
        draw.FUN_00614bf0(font,
            SBUIInputFieldTextAddress(FUN_005d0880(*(std::wstring *)&before, *(std::wstring *)&after)),
            m_70.m_00.Unk005fc190(offset), 1);
        std::wstring *value = (std::wstring *)(m_00 + 0x50);
        int textWidth = ((SBFontUnk0061e840 *)font)->FUN_0061ea50(value);
        draw.FUN_00614bf0(font, value,
            SBGeoPoint2D(m_70.m_08.m_x - textWidth, m_70.m_00.m_y).Unk005fc190(offset), 1);
    }
    else
    {
        draw.FUN_00614bf0(font,
            SBUIInputFieldTextAddress(FUN_005d0880(*(std::wstring *)&before, *(std::wstring *)&after)),
            m_70.m_00.Unk005fc190(offset), 1);
    }
    if (((SBUIInputFieldTextUnk *)m_6c)->FUN_0061e230())
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
        position = box.m_00.Unk005fc190(SBGeoVector2D((const SBGeoVector2D &)SBGeoPoint2D((float)cursor, 0)));
        RHUnkFXDraw *manager = *(RHUnkFXDraw **)(m_00 + 0x1c);
        RHMapBox bounds(position.m_x, position.m_y,
            position.m_x + manager->FUN_005e56c0(surface),
            position.m_y + manager->FUN_005e5750(surface));
        SBGeoBoundingBox2D clipped = ((SBGeoBoundingBox2D *)&bounds)->FUN_006090d0(m_88);
        ((SBDrawManager *)manager)->BlitAlphaKeying(surface, 0,
            *(unsigned int *)(m_00 + 0x20), &clipped, 0x1f, 0x41, 1);
    }
    return true;
}

#include "RHUnk005fc400.h"

class RHMobileUnk006091b0
{
public:
    RHMobileUnk006091b0 &FUN_006091b0(const SBGeoPoint2D &);
    SBGeoPoint2D m_0;
    SBGeoPoint2D m_8;
};

// FUNCTION: GAME 0x00621b80
void RHPortraitRenderer006212d0::FUN_0060d6a0(const SBGeoBoundingBox2D &box)
{
    RHUnk005fc400 displacement(*(SBGeoPoint2D *)((SBUIUnk0060d530 *)this)->FUN_0060d690(), m_bounds.m_00);
    RHPortraitRenderer0060d470::FUN_0060d6a0(box);
    {
        const SBGeoVector2D &origin = SBGeoVector2D(*(SBGeoVector2D *)&m_bounds.m_00);
        m_bounds -= origin;
    }
    ((RHMobileUnk006091b0 *)&m_bounds)->FUN_006091b0(displacement);
    ((SBUIInputFieldUnk00621440 *)this)->FUN_00621c30(m_bounds);
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
    ((RHPortraitRenderer006212d0 *)renderer)->RHPortraitRenderer006212d0::FUN_0060d530(0);
    renderer->FUN_00621440(0);
    renderer->FUN_00621470(0);
    ((RHPortraitRenderer006212d0 *)renderer)->RHPortraitRenderer006212d0::FUN_0060d6a0(renderer->m_70);
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
