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
unsigned short *FUN_00419940(unsigned short *, const unsigned short *, unsigned int);
unsigned short *FUN_0044f580(unsigned short *, const unsigned short *, unsigned int);
namespace std { void _Xlen(); }
extern float g_unk0x006775d8;

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

// Parked: pooled STL null-string operand is unresolved.
// STUB: GAME 0x005d0880
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

// Parked: call to counted box constructor resolves asymmetrically.
// STUB: GAME 0x006138e0
SBUIInputFieldDrawUnk::SBUIInputFieldDrawUnk()
    : m_10(0), m_14(0), m_18(2), m_1c(0, 0, 0, 0)
{
}

// Parked: x87/register scheduling and counted font operand differ.
// STUB: GAME 0x00614bf0
bool SBUIInputFieldDrawUnk::FUN_00614bf0(void *font, std::wstring *text, const SBGeoPoint2D &point, unsigned int flags)
{
    SBGeoBoundingBox2D box;
    int width = ((SBFontUnk0061e840 *)font)->FUN_0061ea50(text);
    int height = ((SBUIListboxUnk0061e890 *)font)->FUN_0061e890();
    float y = point.m_y;
    box.m_00.m_y = y;
    box.m_08.m_y = y + height;
    box.m_10 = true;
    if (flags & 1)
    {
        box.m_00.m_x = point.m_x;
        box.m_08.m_x = point.m_x + ((float)(m_18 * 2) + width);
        box.m_10 = true;
    }
    else if (!(flags & 6))
    {
        if (flags & 8)
        {
            box.m_00.m_x = point.m_x - width - (int)(m_18 * 2);
            box.m_08.m_x = point.m_x;
            box.m_10 = true;
        }
    }
    else
    {
        float padding = (float)m_18;
        box.m_00.m_x = point.m_x - width / 2 - padding;
        box.m_08.m_x = box.m_00.m_x + (width + padding);
        box.m_10 = true;
        flags = (flags & ~6) | 1;
    }
    return FUN_00614230(font, text, box, flags, 0, 0) != 0;
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
                FUN_0044f580(result.m_chars + 1, result.m_chars, result.m_size);
                FUN_00419940(result.m_chars, &character, 1);
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
                FUN_0044f580(result.m_chars + offset + 1, result.m_chars + offset, result.m_size - offset);
                FUN_00419940(result.m_chars + offset, &character, 1);
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

// STUB: GAME 0x00621430
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
    before.FUN_004580c0(*(std::wstring *)&text->FUN_0061dd50(0, cursor), 0, std::wstring::npos);
    after.FUN_004580c0(*(std::wstring *)&text->FUN_0061dd50(1, (unsigned int)(available - width - shift)), 0, std::wstring::npos);
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

// Parked: annotated containment helper resolves asymmetrically.
// STUB: GAME 0x00621c30
bool SBUIInputFieldUnk00621440::FUN_00621c30(const SBGeoBoundingBox2D &box)
{
    SBGeoPoint2D *origin = (SBGeoPoint2D *)(m_00 + 8);
    bool inside;
    {
        SBGeoVector2D displacement(*origin);
        inside = ((SBGeoBoundingBox2D *)origin)->FUN_006084a0(box.FUN_006090d0(displacement));
    }
    if (inside)
    {
        SBGeoVector2D displacement(*origin);
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
