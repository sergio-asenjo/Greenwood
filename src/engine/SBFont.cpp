#include "SBFont.h"
#include "RHSaveGame.h"
#include <string.h>

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
}
