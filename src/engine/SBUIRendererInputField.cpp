#include "SBNullstr.h"
#include "SBUIRendererInputField.h"
#include "SBUIRenderer.h"
#include "SBFont.h"
#include "SBUIRendererListbox.h"
#include "RHPortraitRenderer006212d0.h"
#include "RHPopupRenderer0060dbc0.h"
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

#include "SBDrawManagerCore.h"

#include "RHUnk00600820.h"

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
    if (!other.m_flag)
        return false;
    ((SBUIInputFieldBoxCalls *)&span)->FUN_0060a860(
        SBGeoSegment2D(other.m_p0, other.m_p1).Line());
    return ((SBUIInputFieldBoxCalls *)this)->FUN_00608450(span);
}

// FUNCTION: GAME 0x0060dda0
int RHPopupRenderer0060dbc0::FUN_0060dda0(SBFontUnk0061e840 *font, bool silent)
{
    int result;
    SBUIInputFieldDrawUnk renderer;
    renderer.FUN_00614d70(silent);
    if (m_position.m_p1.m_x - m_position.m_p0.m_x > 0.0f)
    {
        result = renderer.FUN_00614230(font, m_name, m_position, m_60, m_64, true);
        m_68 = renderer.FUN_00613e90();
    }
    else
    {
        SBGeoPoint2D position;
        switch (m_60)
        {
        case 8:
            position = m_position.m_p0.FUN_005fc200(
                SBGeoVector2D((float)font->FUN_0061ea50(m_name), 0.0f));
            break;
        case 2:
            position = m_position.m_p0.FUN_005fc200(
                SBGeoVector2D((float)(font->FUN_0061ea50(m_name) / 2), 0.0f));
            break;
        case 1:
            position = m_position.m_p0;
            break;
        }
        renderer.FUN_00614bf0(font, &m_name, position, 1);
        result = 1;
        m_68.assign(renderer.FUN_00613e90());
    }
    return result;
}

// FUNCTION: GAME 0x006138e0
SBUIInputFieldDrawUnk::SBUIInputFieldDrawUnk()
    : m_10(0), m_14(0), m_18(2), m_1c(0, 0, 0, 0)
{
}

// STUB: GAME 0x00613940
unsigned long SBUIInputFieldDrawUnk::FUN_00613940(const SBFontUnk0061e840 *font,
    const std::vector<std::wstring>::const_iterator &endA,
    const std::vector<std::wstring>::const_iterator &endB,
    std::vector<std::wstring>::const_iterator &currentA,
    std::vector<std::wstring>::const_iterator &currentB, bool &stopped,
    unsigned long maxWidth, unsigned long spacingWidth) const
{
    std::vector<std::wstring>::const_iterator initialB = currentB;
    unsigned long total = 0;
    unsigned long count = 0;
    stopped = false;
    while (currentB != endB)
    {
        long width = font->FUN_0061ea50(*currentA);
        if ((unsigned long)width > maxWidth && count == 0)
        {
            total = width;
            ++currentA;
            ++currentB;
            count = 1;
            break;
        }
        if (total + width > maxWidth)
        {
            if (currentB != initialB && (unsigned long)width <= maxWidth)
            {
                --currentA;
                --currentB;
                total -= spacingWidth;
            }
            break;
        }
        total += width < 0 ? 0 : width;
        if (*currentB == L"\n")
        {
            stopped = true;
            break;
        }
        ++currentA;
        ++currentB;
        total += spacingWidth;
        ++count;
    }
    if (currentB != endB)
    {
        std::vector<std::wstring>::const_iterator nextA = currentA + 1;
        if (*currentB != L"\n" && nextA->size() <= 5
            && (nextA + 1 == endA || *(currentB + 1) == L"\n")
            && currentB != initialB)
        {
            total -= font->FUN_0061ea50(*currentA);
            --currentA;
            --currentB;
        }
        return total;
    }
    else
    {
        long width = font->FUN_0061ea50(*currentA);
        if ((unsigned long)width > maxWidth && count == 0)
            total = width;
        else if (total + width > maxWidth)
        {
            if (currentB != initialB)
            {
                if (currentA->size() <= 5 && count > 1)
                {
                    --currentA;
                    --currentB;
                    long previousWidth = font->FUN_0061ea50(*currentA);
                    total -= previousWidth < 0 ? 0 : previousWidth;
                }
                --currentA;
                --currentB;
                total -= spacingWidth;
            }
        }
        else
            total += width < 0 ? 0 : width;
    }
    return total;
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

// FUNCTION: GAME 0x00613c90
void SBUIInputFieldDrawUnk::FUN_00613c90(std::vector<std::wstring>::const_iterator beginA,
    std::vector<std::wstring>::const_iterator beginB, std::vector<std::wstring>::const_iterator endA,
    std::vector<std::wstring>::const_iterator endB)
{
    std::vector<std::wstring>::const_iterator currentA = beginA;
    m_00.erase();
    for (std::vector<std::wstring>::const_iterator currentB = beginB;
         currentA != endA; ++currentA, ++currentB)
    {
        m_00.append(*currentA);
        if (currentB != endB)
            m_00.append(*currentB);
    }
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

// STUB: GAME 0x00613ea0
unsigned short SBUIInputFieldDrawUnk::FUN_00613ea0(SBFontUnk0061e840 *font, const std::wstring *text,
    const SBGeoBoundingBox2D &bounds, unsigned int flags, unsigned int spacing)
{
    SBGeoPoint2D position(bounds.Min());
    std::wstring remaining;
    const unsigned short *character = text->begin();
    for (; character != text->end(); ++character) {
        SBGeoVector2D extent((float)(unsigned int)font->FUN_0061e850(*character),
            (float)((unsigned int)font->GetHeight() - (unsigned short)spacing));
        bool inside = bounds.FUN_00608400(position) && bounds.FUN_00608400(position.Unk005fc190(extent));
        float bottom = bounds.ValueC();
        float currentY = position.m_y;
        bool nextLine = currentY + (unsigned int)font->GetHeight() < bottom;
        if (inside || nextLine) {
            if (!font->Render(*character, position, bounds, m_14))
                break;
        } else {
            break;
        }
    }
    m_00.erase();
    for (; character != text->end(); ++character)
        m_00.append(1, *character);
    return (unsigned short)((position.m_y - bounds.Value4()) /
        (float)((unsigned int)font->GetHeight() - (unsigned short)spacing) + 1.0f);
}

void EmitSBUIInputFieldSingleWord(SBUIInputFieldDrawUnk *renderer, SBFontUnk0061e840 *font,
    std::wstring *text, const SBGeoBoundingBox2D &bounds)
{
    renderer->FUN_00613ea0(font, text, bounds, 0, 0);
}

// FUNCTION: GAME 0x006141e0
bool SBUIInputFieldDrawUnk::OneWordBiggerThanALine(const SBFontUnk0061e840 *font,
    float threshold, const std::vector<std::wstring> *words)
{
    for (std::vector<std::wstring>::const_iterator word = words->begin(); word != words->end(); ++word)
        if (font->FUN_0061ea50(*word) > threshold)
            return true;
    return false;
}

inline void SetSBUIInputFieldBoxX(SBGeoBoundingBox2D &box, float first, float last)
{
    box.m_p0.m_x = first;
    box.m_p1.m_x = last;
    box.m_flag = true;
}

inline void SetSBUIInputFieldBoxY(SBGeoBoundingBox2D &box, float first, float last)
{
    box.m_p0.m_y = first;
    box.m_p1.m_y = last;
    box.m_flag = true;
}

// Parked: x87 operand order, alignment flags and result-slot scheduling differ.
static inline float SBUIInputFieldPadding(const float &padding)
{
    return padding;
}

static inline void SBUIInputFieldCenter(SBGeoBoundingBox2D &box, float x, long width, unsigned int paddingValue, unsigned int &flags)
{
    float padding = (float)paddingValue;
    float first = x - width / 2 - SBUIInputFieldPadding(padding);
    box.SetValue0(first);
    box.SetValue8(box.Value0() + (width + SBUIInputFieldPadding(padding)));
    flags = (flags & ~6) | 1;
}

// STUB: GAME 0x00614bf0
bool SBUIInputFieldDrawUnk::FUN_00614bf0(SBFontUnk0061e840 *font, std::wstring *text, const SBGeoPoint2D &point, unsigned int flags)
{
    SBGeoBoundingBox2D box;
    long width = font->FUN_0061ea50(*text);
    int height = font->GetHeight();
    float y = point.m_y;
    box.SetValue4(y);
    box.SetValueC(y + height);
    if (flags & 1)
    {
        box.m_p0.m_x = point.m_x;
        float x = point.GetX();
        box.SetValue8(x + ((float)(m_18 * 2) + width));
    }
    else if (!(flags & 6))
    {
        if (flags & 8)
        {
            float first = point.GetX();
            first -= width;
            first -= (int)(m_18 * 2);
            box.SetValue0(first);
            box.SetValue8(point.GetX());
        }
    }
    else
    {
        SBUIInputFieldCenter(box, point.GetX(), width, m_18, flags);
    }
    bool rendered = FUN_00614230(font, *text, box, flags, 0, 0) != 0;
    return rendered;
}

// FUNCTION: GAME 0x00614d70
void SBUIInputFieldDrawUnk::FUN_00614d70(bool value)
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
    SBUIInputFieldSplitUnk(const std::wstring &text, const std::wstring &separators)
    {
        m_vptr = 0x0067a8f8;
        FUN_00614e60(text, separators);
    }
    ~SBUIInputFieldSplitUnk();
    void *FUN_00614e40(unsigned flags);
    void FUN_00614e60(const std::wstring &text, const std::wstring &separators);
    unsigned m_vptr;
    std::vector<std::wstring> m_tokens;
    std::vector<std::wstring> m_separators;
};

DECOMP_SIZE_ASSERT(SBUIInputFieldSplitUnk, 0x24)
DECOMP_STATIC_ASSERT(offsetof(SBUIInputFieldSplitUnk, m_tokens) == 4)
DECOMP_STATIC_ASSERT(offsetof(SBUIInputFieldSplitUnk, m_separators) == 0x14)

// TEMPLATE: GAME 0x00614d80
// ??1SBUIInputFieldSplitUnk@@QAE@XZ
inline SBUIInputFieldSplitUnk::~SBUIInputFieldSplitUnk()
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

// STUB: GAME 0x00614230
unsigned short SBUIInputFieldDrawUnk::FUN_00614230(SBFontUnk0061e840 *font, const std::wstring &text,
    const SBGeoBoundingBox2D &bounds, unsigned int flags, unsigned short spacing, bool breakWords)
{
    SBUIInputFieldSplitUnk split(text, std::wstring(
        // STRING: GAME 0x006bb79c
        L" \n\r\t"));
    SBGeoPoint2D position;
    SBGeoBoundingBox2D lineBounds;
    m_00.erase();
    m_10 = 0;
    m_1c = SBGeoBoundingBox2D(bounds.Min(), bounds.Min());
    lineBounds = bounds;
    if (lineBounds.Width() > (float)(m_18 * 2)) {
        SetSBUIInputFieldBoxX(lineBounds,
            lineBounds.Value0() + m_18, lineBounds.Value8() - m_18);
    }
    if (split.m_tokens.empty())
        return 0;
    if (breakWords && OneWordBiggerThanALine(font, lineBounds.Width(), &split.m_tokens))
        return FUN_00613ea0(font, &text, bounds, flags, spacing);
    if (split.m_separators.size() > split.m_tokens.size() - 1)
        split.m_separators.erase(split.m_separators.begin() + split.m_tokens.size() - 1,
            split.m_separators.end());
    unsigned long maxWidth = (unsigned long)lineBounds.Width();
    position = lineBounds.Min();
    std::vector<std::wstring>::const_iterator word = split.m_tokens.begin();
    std::vector<std::wstring>::const_iterator separator = split.m_separators.begin();
    unsigned long lines = 0;
    unsigned long spaceWidth = font->FUN_0061ea50(std::wstring(L" "));
    while (word != split.m_tokens.end()) {
        bool stopped = false;
        bool justified = false;
        unsigned long lineSpaceWidth = spaceWidth;
        unsigned long extraSpaces = 0;
        if ((flags & 0x10) == 0x10) {
            float height = lineBounds.ValueC() - lineBounds.Value4();
            if ((unsigned int)font->GetHeight() < height)
                position.m_y += (height - font->GetBaseLine()) * 0.5f;
            maxWidth = font->FUN_0061ea50(text);
        }
        std::vector<std::wstring>::const_iterator endWord = split.m_tokens.end();
        std::vector<std::wstring>::const_iterator endSeparator = split.m_separators.end();
        std::vector<std::wstring>::const_iterator first = word;
        unsigned long width = FUN_00613940(font, endWord, endSeparator, word, separator,
            stopped, maxWidth, spaceWidth);
        unsigned long count = word - first + 1;
        if (flags & 0x10)
            maxWidth = (unsigned long)lineBounds.Width();
        if (flags & 2)
            position.m_x = lineBounds.Value0() + (int)(maxWidth - width) / 2;
        else if (flags & 8)
            position.m_x = lineBounds.Value0() + (maxWidth - width);
        else if ((flags & 4) && FUN_00613e40(stopped, count, word, endWord)) {
            justified = true;
            lineSpaceWidth = spaceWidth + (maxWidth - width) / count;
            extraSpaces = (maxWidth - width) % count;
        }
        for (; first != word; ++first) {
            m_10 += font->FUN_0061eb80(first, &position, &bounds, m_14);
            if (extraSpaces) {
                position.m_x += lineSpaceWidth + 1;
                --extraSpaces;
            } else {
                position.m_x += lineSpaceWidth;
            }
        }
        if (justified)
            position.m_x = lineBounds.Value8() - font->FUN_0061ea50(*first);
        m_10 += font->FUN_0061eb80(first, &position, &bounds, m_14);
        if (position.m_x + m_18 > m_1c.Value8())
            m_1c.SetValue8(m_1c.Value0() + m_18 + position.m_x);
        m_1c.SetValueC(m_1c.ValueC() +
            (unsigned int)font->GetHeight() - (float)spacing);
        position.m_x = lineBounds.Value0();
        position.m_y += (unsigned int)font->GetHeight() - (float)spacing;
        ++lines;
        ++word;
        ++separator;
        if ((unsigned int)font->GetHeight() >
            lineBounds.ValueC() - position.m_y) {
            FUN_00613c90(word, separator, split.m_tokens.end(), split.m_separators.end());
            break;
        }
    }
    return (unsigned short)lines;
}

void EmitSBUIInputFieldSplit(SBUIInputFieldSplitUnk *split, const std::wstring &text)
{
    split->FUN_00614e40(0);
    split->FUN_00614e60(text, text);
}

#include "SBUIInputFieldCharacters.h"

// TEMPLATE: GAME 0x00509ba0 FOLDED
// ?_Construct@std@@YAXPAUSBUIInputFieldCharacter@@ABU2@@Z

// TEMPLATE: GAME 0x0059fcc0 FOLDED
// ?_Buynode@?$list@USBUIInputFieldCharacter@@V?$allocator@USBUIInputFieldCharacter@@@std@@@std@@IAEPAU_Node@12@PAU312@0@Z

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
        total += advance + font->GetExtraSpacing();
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
        + ((SBFontUnk0061e840 *)text.m_font)->GetExtraSpacing();
    text.m_cursor = text.m_characters.insert(position, value);
    return true;
}

// FUNCTION: GAME 0x0061e240
void RHPortraitText0061db10::FUN_0061e240(unsigned int direction)
{
    SBUIInputFieldNode *&cursor = *(SBUIInputFieldNode **)&m_cursor;
    switch (direction)
    {
    case 1:
    {
        if (m_cursor != m_characters.rend().base())
            --m_cursor;
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
                --m_cursor;
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

// FUNCTION: GAME 0x0061e060
void RHPortraitText0061db10::FUN_0061e060(const std::wstring &text)
{
    typedef SBUIInputFieldCharacters::iterator (SBUIInputFieldCharacters::*Erase)(SBUIInputFieldCharacters::iterator);
    Erase erase = &SBUIInputFieldCharacters::erase;
    {
        SBUIInputFieldCharacters::iterator last = m_characters.end();
        for (SBUIInputFieldCharacters::iterator current = m_characters.begin(); current != last;)
            (m_characters.*erase)(current++);
    }
    SBUIInputFieldCharacters &characters = m_characters;
    SBUIInputFieldCharacter value;
    value.width = 0;
    value.character = 0;
    characters.push_back(value);
    std::wstring::const_iterator first = *(std::wstring::const_iterator volatile *)((char *)&text + 4);
    for (std::wstring::const_iterator character = first; character != text.end(); ++character)
    {
        value.character = *character;
        SBFontUnk0061e840 *font = (SBFontUnk0061e840 *)m_font;
        value.width = font->FUN_0061e850(*character) + font->GetExtraSpacing();
        characters.insert(characters.end(), value);
    }
    m_cursor = m_characters.begin();
}

// FUNCTION: GAME 0x0061e340
void SBUIInputFieldUnk00621440::FUN_0061e340()
{
    *(std::wstring *)((char *)this + 0x38) = (const std::wstring &)FUN_0061df60();
}

// FUNCTION: GAME 0x0061e4b0
void SBUIInputFieldUnk00621440::FUN_0061e4b0()
{
    ((RHPortraitText0061db10 *)this)->FUN_0061e060(*(const std::wstring *)((char *)this + 0x38));
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
        delete m_64;
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
    SBFontUnk0061e840 *font = m_84 == 1 ? m_64 : m_68;
    SBGeoBoundingBox2D &box = m_70;
    float height = box.m_p1.m_y - box.m_p0.m_y;
    offset.m_x = 0;
    offset.m_y = (height - (unsigned long)font->GetBaseLine()) * 0.5f;
    if (!((SBUIUnk0060dae0 *)this)->FUN_0060dae0(id))
        return false;
    if (!m_84)
        return false;
    unsigned int width = ((SBUIInputFieldTextUnk *)m_6c)->FUN_0061dd00();
    int shift = box.m_p1.m_x - box.m_p0.m_x <= width
        ? (int)(box.m_p1.m_x - box.m_p0.m_x - width) : 0;
    unsigned int cursor = width + shift;
    typedef std::wstring &(std::wstring::*Assign)(const std::wstring &, unsigned, unsigned);
    Assign assign = &std::wstring::assign;
    (before.*assign)(((SBUIInputFieldTextUnk *)m_6c)->FUN_0061dd50(0, cursor), 0, std::wstring::npos);
    (after.*assign)(((SBUIInputFieldTextUnk *)m_6c)->FUN_0061dd50(1,
        (unsigned int)(box.m_p1.m_x - box.m_p0.m_x - width - shift)), 0, std::wstring::npos);
    unsigned int surface;
    if (m_00[0x60] == 1 && !((SBUIInputFieldTextUnk *)m_6c)->FUN_0061e230())
    {
        draw.FUN_00614bf0(font,
            SBUIInputFieldTextAddress(FUN_005d0880(*(std::wstring *)&before, *(std::wstring *)&after)),
            m_70.m_p0.Unk005fc190(offset), 1);
        std::wstring *value = (std::wstring *)(m_00 + 0x50);
        long textWidth = font->FUN_0061ea50(*value);
        draw.FUN_00614bf0(font, value,
            SBGeoPoint2D(m_70.m_p1.m_x - textWidth, m_70.m_p0.m_y).Unk005fc190(offset), 1);
    }
    else
    {
        draw.FUN_00614bf0(font,
            SBUIInputFieldTextAddress(FUN_005d0880(*(std::wstring *)&before, *(std::wstring *)&after)),
            m_70.m_p0.Unk005fc190(offset), 1);
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
        position = box.m_p0.Unk005fc190(SBGeoVector2D((const SBGeoVector2D &)SBGeoPoint2D((float)cursor, 0)));
        SBDrawManager *manager = *(SBDrawManager **)(m_00 + 0x1c);
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
    RHUnk005fc400 displacement(*(SBGeoPoint2D *)((SBUIUnk0060d530 *)this)->FUN_0060d690(), m_bounds.m_p0);
    RHPortraitRenderer0060d470::FUN_0060d6a0(box);
    {
        const SBGeoVector2D &origin = SBGeoVector2D(*(SBGeoVector2D *)&m_bounds.m_p0);
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
    draw.FUN_00614bf0(0, 0, renderer->m_70.m_p0, 0);
    FUN_005d0880(draw.m_00, draw.m_00);
    ((RHPortraitRenderer006212d0 *)renderer)->RHPortraitRenderer006212d0::FUN_0060d530(0);
    renderer->FUN_00621440(0);
    renderer->FUN_00621470(0);
    ((RHPortraitRenderer006212d0 *)renderer)->RHPortraitRenderer006212d0::FUN_0060d6a0(renderer->m_70);
    renderer->FUN_00621c30(renderer->m_70);
}

void SBUIInputFieldEmitAssigned(SBUIInputFieldDrawUnk *draw, const unsigned short *left,
    const unsigned short *right, unsigned char flag, const void *first, unsigned int count,
    const void *last, void *font, const std::vector<std::wstring> *words)
{
    FUN_00613c50(left, right, count);
    FUN_00613e40(flag, count, first, last);
    draw->FUN_00613e70();
    draw->FUN_00613e80();
    draw->OneWordBiggerThanALine((const SBFontUnk0061e840 *)font, 0.0f, words);
}

void SBUIInputFieldEmitTextAlgorithms(SBUIInputFieldDrawUnk *draw,
    const SBFontUnk0061e840 *font, std::vector<std::wstring>::const_iterator endA,
    std::vector<std::wstring>::const_iterator endB, std::vector<std::wstring>::const_iterator currentA,
    std::vector<std::wstring>::const_iterator currentB, bool &stopped,
    unsigned long maxWidth, unsigned long spacingWidth)
{
    draw->FUN_00613940(font, endA, endB, currentA, currentB, stopped, maxWidth, spacingWidth);
    draw->FUN_00613c90(currentA, currentB, endA, endB);
}
