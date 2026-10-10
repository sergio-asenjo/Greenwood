#include "SBNullstr.h"
#include "SBFont.h"
#include "RHSaveGame.h"
#include "RHCampaign.h"
#include <string.h>

DECOMP_SIZE_ASSERT(SBFontTextView, 0x0c)
DECOMP_SIZE_ASSERT(SBFontUnk0061e840, 0x44)
DECOMP_SIZE_ASSERT(SBFontNode0061fcb0, 0x14)
DECOMP_SIZE_ASSERT(SBFontIterator0061fe10, 0x04)
DECOMP_SIZE_ASSERT(SBFontPair0061f2b0, 0x08)
DECOMP_SIZE_ASSERT(SBFontTree0061fcb0, 0x10)
DECOMP_SIZE_ASSERT(SBFontValue0061f120, 0x20)
DECOMP_SIZE_ASSERT(SBFontNode0061f3e0, 0x30)
DECOMP_SIZE_ASSERT(SBFontTree0061f3e0, 0x10)
DECOMP_SIZE_ASSERT(SBFontIterator0061f3e0, 0x04)
DECOMP_SIZE_ASSERT(SBFontPair0061f3e0, 0x08)
DECOMP_SIZE_ASSERT(SBFontLock, 0x01)

// GLOBAL: GAME 0x006c191c
SBFontNode0061fcb0 *g_unk0x006c191c = 0;
// GLOBAL: GAME 0x006c1920
unsigned g_unk0x006c1920 = 0;
// GLOBAL: GAME 0x006c1914
SBFontNode0061f3e0 *g_unk0x006c1914 = 0;
// GLOBAL: GAME 0x006c1900
SBFontTree0061f3e0 g_unk0x006c1900;

// STRING: GAME 0x006bb87c
static const char g_sbFontFile[] = "P:\\Robin Hood\\SBLibNG\\SBFont.cpp";
// STRING: GAME 0x006bb8a0
static const char g_sbFontMissing[] = "Warning ! Character 0x%02x is missing in the font '%s'";

// FUNCTION: GAME 0x0061e810
void SBFontUnk0061e840::FUN_0061e810(int value, int)
{
    if (m_04) {
        v6();
    }
    m_04 = value;
}

// FUNCTION: GAME 0x0061e840
void SBFontUnk0061e840::FUN_0061e840()
{
    m_04 = 0;
}

// FUNCTION: GAME 0x0061e850
int SBFontUnk0061e840::FUN_0061e850(unsigned short value)
{
    int first;
    int second;
    int result = v3(value, first, second);
    return first + second + result;
}

// FUNCTION: GAME 0x0061e880
int SBFontUnk0061e840::FUN_0061e880()
{
    return m_14;
}

// FUNCTION: GAME 0x0061e8a0
std::string SBFontUnk0061e840::FUN_0061e8a0()
{
    return std::string(m_18);
}

// FUNCTION: GAME 0x0061e970
int SBFontUnk0061e840::FUN_0061e970()
{
    return m_3c;
}

// Unannotated: coupled text-width helper, register scheduling remains unmatched.
int SBFontUnk0061e840::FUN_0061e980(void *value, int &first, int &second)
{
    SBFontTextView &text = *(SBFontTextView *)value;
    first = 0;
    second = 0;
    int width = 0;
    for (unsigned short *it = text.m_04, *next = it + 1;
         it != text.end(); ++it, ++next) {
        int left;
        int right;
        int result = v3(*it, left, right);
        width += v8();
        width += result;
        if (it == text.m_04) {
            first = left;
        } else {
            width += left;
        }
        if (next == text.end()) {
            second = right;
        } else {
            width += right;
        }
    }
    return width;
}

// FUNCTION: GAME 0x0061ea50
int SBFontUnk0061e840::FUN_0061ea50(void *value)
{
    int first;
    int second;
    int result = FUN_0061e980(value, first, second);
    return first + second + result;
}

// FUNCTION: GAME 0x0061ea80
bool SBFontUnk0061e840::FUN_0061ea80(const std::string &name)
{
    RHUnk005f4fc0 file;
    bool result = false;
    if (file.FUN_005f5090(name, 1) == 0) {
        result = v9(file);
    }
    m_08[0] = result;
    return result;
}

// FUNCTION: GAME 0x0061eb00
bool SBFontUnk0061e840::FUN_0061eb00(SBFile &file)
{
    char tag[6];
    file.Access(m_08 + 4, 6);
    if (file.Access(&m_14, 4)) {
        return false;
    }
    v1(tag);
    if (memcmp(m_08 + 4, tag, 6)) {
        return false;
    }
    if (file.Access(m_18, 0x2c)) {
        return false;
    }
    return true;
}

// FUNCTION: GAME 0x0061eb80
int SBFontUnk0061e840::FUN_0061eb80(SBFontTextView *text, void *a, const void *b, bool c)
{
    int count = 0;
    for (unsigned short *it = text->m_04; it != text->end(); ++count, ++it) {
        v4(*it, a, b, c);
    }
    return count;
}

// Parked: font-name return ABI and pair-copy materialization remain unmatched.
// STUB: GAME 0x0061ebd0
void SBFontUnk0061e840::FUN_0061ebd0(unsigned short value)
{
    std::string name = FUN_0061e8a0();
    undefined compare;
    undefined allocator;
    SBFontPair0061f3e0 result = g_unk0x006c1900.FUN_0061f3e0(
        SBFontValue0061f120(name, SBFontTree0061fcb0(compare, false, allocator)));
    SBFontTree0061fcb0 &characters = result.m_00.m_00->m_0c.m_10;
    SBFontIterator0061fe10 it = characters.FUN_0061fe10(value);
    if (it.m_00 == characters.m_04 || value < it.m_00->m_0c) {
        it = characters.end();
    }
    if (it.m_00 == characters.m_04) {
        characters.FUN_0061f2b0(value);
        FUN_005f8030(0, g_sbFontFile, 0x17d, g_sbFontMissing, (unsigned)value, name.c_str());
    }
}

// FUNCTION: GAME 0x0061ed70
bool SBFontUnk0061e840::FUN_0061ed70(SBFile &file)
{
    v1(m_08 + 4);
    m_14 = v0();
    file.Access(m_08 + 4, 6);
    if (file.Access(&m_14, 4)) {
        return false;
    }
    if (file.Access(m_18, 0x2c)) {
        return false;
    }
    return true;
}

// FUNCTION: GAME 0x0061eea0
void SBFontTree0061fcb0::FUN_0061eea0()
{
    FUN_0061fce0(begin(), end());
    operator delete(m_04);
    m_04 = 0;
    m_0c = 0;
    {
        SBFontLock lock;
        if (--g_unk0x006c1920 == 0) {
            operator delete(g_unk0x006c191c);
            g_unk0x006c191c = 0;
        }
    }
}

// FUNCTION: GAME 0x0061ef10
SBFontValue0061f120::~SBFontValue0061f120()
{
}

// FUNCTION: GAME 0x0061f120
SBFontValue0061f120::SBFontValue0061f120(const std::string &name, const SBFontTree0061fcb0 &tree)
    : m_00(name), m_10(tree)
{
}

// FUNCTION: GAME 0x0061f2b0
SBFontPair0061f2b0 SBFontTree0061fcb0::FUN_0061f2b0(const unsigned short &value)
{
    SBFontNode0061fcb0 *node = m_04->m_04;
    SBFontNode0061fcb0 *parent = m_04;
    bool left = true;
    {
        SBFontLock lock;
        while (node != g_unk0x006c191c) {
            parent = node;
            left = value < node->m_0c;
            node = left ? node->m_00 : node->m_08;
        }
    }
    if (m_08) {
        SBFontPair0061f2b0 result(FUN_0061fe30(node, parent, value), true);
        return result;
    }
    SBFontIterator0061fe10 it;
    it.m_00 = parent;
    if (left) {
        if (it.m_00 == m_04->m_00) {
            SBFontPair0061f2b0 result(FUN_0061fe30(node, parent, value), true);
            return result;
        }
        it.FUN_00620ca0();
    }
    if (it.m_00->m_0c < value) {
        SBFontPair0061f2b0 result(FUN_0061fe30(node, parent, value), true);
        return result;
    }
    SBFontPair0061f2b0 result(it, false);
    return result;
}

// Parked: pair-construction calls and frame slots differ from the target.
// STUB: GAME 0x0061f3e0
SBFontPair0061f3e0 SBFontTree0061f3e0::FUN_0061f3e0(const SBFontValue0061f120 &value)
{
    SBFontNode0061f3e0 *node = m_04->m_04;
    SBFontNode0061f3e0 *parent = m_04;
    bool left = true;
    {
        SBFontLock lock;
        while (node != g_unk0x006c1914) {
            parent = node;
            const RHProfileText &key = *(const RHProfileText *)&value.m_00;
            const RHProfileText &other = *(const RHProfileText *)&node->m_0c.m_00;
            left = key.FUN_00460900(0, key.m_size, other.c_str(), other.m_size) < 0;
            node = left ? node->m_00 : node->m_08;
        }
    }
    if (m_08) {
        SBFontPair0061f3e0 result(FUN_00620130(node, parent, value), true);
        return result;
    }
    SBFontIterator0061f3e0 it;
    it.m_00 = parent;
    if (left) {
        if (it.m_00 == m_04->m_00) {
            SBFontPair0061f3e0 result(FUN_00620130(node, parent, value), true);
            return result;
        }
        it.FUN_00620e30();
    }
    if (((RHCampaignCommandLine *)&it.m_00->m_0c.m_00)->FUN_0045a010(*(const RHProfileText *)&value.m_00) < 0) {
        SBFontPair0061f3e0 result(FUN_00620130(node, parent, value), true);
        return result;
    }
    SBFontPair0061f3e0 result(it, false);
    return result;
}

// FUNCTION: GAME 0x0061fcb0
SBFontTree0061fcb0::SBFontTree0061fcb0(const undefined &compare, bool multi, const undefined &allocator)
    : m_00(allocator), m_01(compare), m_08(multi)
{
    FUN_00620b70();
}

// FUNCTION: GAME 0x0061fe10
SBFontIterator0061fe10 SBFontTree0061fcb0::FUN_0061fe10(const unsigned short &value)
{
    SBFontIterator0061fe10 result;
    result.m_00 = FUN_00620c20(value);
    return result;
}

void SBFontEmit(SBFontUnk0061e840 *font, unsigned short value)
{
    font->FUN_0061e810(value, 0);
    font->FUN_0061e840();
    font->FUN_0061e850(value);
    font->FUN_0061e880();
    font->FUN_0061e8a0();
    font->FUN_0061e970();
    font->FUN_0061ea50(0);
    font->FUN_0061ea80(std::string());
    font->FUN_0061eb80(0, 0, 0, 0);
    font->FUN_0061eb00(*(SBFile *)0);
    font->FUN_0061ed70(*(SBFile *)0);
    font->FUN_0061ebd0(value);
    undefined byte;
    SBFontTree0061fcb0 tree(byte, false, byte);
    tree.FUN_0061fe10(value);
    tree.FUN_0061eea0();
    tree.FUN_0061f2b0(value);
    SBFontValue0061f120 pair(std::string(), tree);
    g_unk0x006c1900.FUN_0061f3e0(pair);
}
