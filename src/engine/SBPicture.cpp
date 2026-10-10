#include "SBNullstr.h"
#include "SBPicture.h"
#include "RHLoadingScreen.h"
#include <new>

// FUNCTION: GAME 0x00611bd0
void *SBPicture::FUN_00611bd0(int)
{
    return m_pad08;
}

// FUNCTION: GAME 0x00611c50
void SBPicture::FUN_00611c50()
{
    if (m_1c != 0) {
        operator delete(m_14);
        m_14 = 0;
        m_1c = 0;
    }
}

// FUNCTION: GAME 0x00611e10
bool RHUnk006114c0::Unk00611e10(unsigned long format, unsigned long mode)
{
    SBPicture *picture = (SBPicture *)this;
    switch (picture->m_04) {
    case 2:
        switch (format) {
        case 3: return picture->FUN_00612260(mode);
        case 4: return picture->FUN_00612150(mode);
        }
        break;
    case 3:
        switch (format) {
        case 2: return picture->FUN_006122b0(mode);
        case 4: return picture->FUN_00612040(mode);
        }
        break;
    case 4:
        switch (format) {
        case 2: return picture->FUN_00611f70(mode);
        case 3: return picture->FUN_00611ea0(mode);
        }
        break;
    }
    return false;
}

// STUB: GAME 0x00611ea0
bool SBPicture::FUN_00611ea0(int)
{
    unsigned short *picture = (unsigned short *)operator new(m_22 * m_20 * 2);
    unsigned char *source = m_14;
    if (!picture)
    {
        SBAssert(0,
            // STRING: GAME 0x006bb624
            "P:\\Robin Hood\\SBLibNG\\SBPicture.cpp", 0x11f,
            // STRING: GAME 0x006bb648
            "Unable to allocate new picture when trying to convert from 24 to 16 bits");
        return false;
    }
    unsigned short *destination = picture;
    for (unsigned int i = 0; i < m_1c / 3; ++i)
    {
        unsigned short value = source[0] & 0xf8;
        value = (value << 5) | (unsigned short)(source[1] & 0xfc);
        value = (value << 3) | (unsigned short)(source[2] >> 3);
        *destination++ = value;
        source += 3;
    }
    m_04 = 3;
    operator delete(m_14);
    m_14 = (unsigned char *)picture;
    m_24 = m_20 * 2;
    return true;
}

// STUB: GAME 0x00611f70
bool SBPicture::FUN_00611f70(int)
{
    unsigned short *picture = (unsigned short *)operator new(m_22 * m_20 * 2);
    unsigned char *source = m_14;
    if (!picture)
    {
        SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBPicture.cpp", 0x151,
            "Unable to allocate new picture when trying to convert from 24 to 16 bits");
        return false;
    }
    unsigned short *destination = picture;
    for (unsigned int i = 0; i < m_1c / 3; ++i)
    {
        unsigned short value = source[0] & 0xf8;
        value = (value << 5) | (unsigned short)(source[1] & 0xf8);
        value = (value << 2) | (unsigned short)(source[2] >> 3);
        *destination++ = value;
        source += 3;
    }
    m_04 = 2;
    operator delete(m_14);
    m_14 = (unsigned char *)picture;
    m_24 = m_20 * 2;
    return true;
}

// STUB: GAME 0x00612040
bool SBPicture::FUN_00612040(int)
{
    unsigned char *picture = (unsigned char *)operator new(m_22 * m_20 * 3);
    unsigned short *source = (unsigned short *)m_14;
    if (!picture) {
        SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBPicture.cpp", 0x181,
            // STRING: GAME 0x006bb694
            "Unable to allocate new picture when trying to convert from 16 to 24 bits");
        return false;
    }
    unsigned char *destination = picture;
    for (unsigned int i = 0; i < m_1c / 2; ++i) {
        unsigned short value = *source++;
        int green = (((value >> 5) & 63) << 8) / 64;
        int blue = ((value & 31) << 8) / 32;
        int red = ((value >> 11) << 8) / 32;
        *destination++ = red;
        *destination++ = green;
        *destination++ = blue;
    }
    m_04 = 4;
    operator delete(m_14);
    m_14 = picture;
    m_24 = m_20 * 3;
    return true;
}

// STUB: GAME 0x00612150
bool SBPicture::FUN_00612150(int)
{
    unsigned char *picture = (unsigned char *)operator new(m_22 * m_20 * 3);
    unsigned short *source = (unsigned short *)m_14;
    if (!picture) {
        SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBPicture.cpp", 0x1b6,
            // STRING: GAME 0x006bb6e0
            "Unable to allocate new picture when trying to convert from 15 to 24 bits");
        return false;
    }
    unsigned char *destination = picture;
    for (unsigned int i = 0; i < m_1c / 2; ++i) {
        unsigned short value = *source++;
        int green = (((value >> 5) & 31) << 8) / 32;
        int blue = ((value & 31) << 8) / 32;
        int red = (((value >> 10) & 31) << 8) / 32;
        *destination++ = red;
        *destination++ = green;
        *destination++ = blue;
    }
    operator delete(m_14);
    m_14 = picture;
    m_04 = 4;
    m_24 = m_20 * 3;
    return true;
}

// FUNCTION: GAME 0x00612260
bool SBPicture::FUN_00612260(int)
{
    unsigned short *pixels = (unsigned short *)m_14;
    for (unsigned int i = 0; i < m_1c / 2; ++i) {
        unsigned short value = *pixels++;
        pixels[-1] = ((value & 0xffe0) << 1) | (value & 0x1f);
    }
    m_04 = 3;
    return true;
}

// FUNCTION: GAME 0x006122b0
bool SBPicture::FUN_006122b0(int)
{
    unsigned short *pixels = (unsigned short *)m_14;
    for (unsigned int i = 0; i < m_1c / 2; ++i) {
        unsigned short value = *pixels++;
        pixels[-1] = ((value >> 1) & 0x7fe0) | (value & 0x1f);
    }
    m_04 = 2;
    return true;
}

// FUNCTION: GAME 0x00612300
bool SBPicture::FUN_00612300(void *size, int mode)
{
    switch (m_04) {
    case 2:
        switch (mode) {
        case 0: return FUN_00612350(size);
        case 1: return FUN_006128b0(size);
        }
        break;
    case 3:
        switch (mode) {
        case 0: return FUN_00612350(size);
        case 1: return FUN_00612690(size);
        }
        break;
    }
    return false;
}

// STUB: GAME 0x006124f0
unsigned short SBPicture::FUN_006124f0(unsigned short *pixels, unsigned short stride,
    unsigned short width, unsigned short height)
{
    unsigned short red = 0;
    unsigned short green = 0;
    unsigned short blue = 0;
    for (unsigned int y = 0; y < height; ++y) {
        unsigned short *row = pixels;
        for (unsigned int x = 0; x < width; ++x) {
            unsigned short value = *row++;
            red += value >> 11;
            green += (value >> 5) & 62;
            blue += value & 31;
        }
        pixels += stride;
    }
    int count = width * height;
    return (((red / count) << 6) | ((green / count) & 63)) << 5 | ((blue / count) & 31);
}

// STUB: GAME 0x006125c0
unsigned short SBPicture::FUN_006125c0(unsigned short *pixels, unsigned short stride,
    unsigned short width, unsigned short height)
{
    unsigned short red = 0;
    unsigned short green = 0;
    unsigned short blue = 0;
    for (unsigned int y = 0; y < height; ++y) {
        unsigned short *row = pixels;
        for (unsigned int x = 0; x < width; ++x) {
            unsigned short value = *row++;
            red += (value >> 10) & 31;
            green += (value >> 5) & 31;
            blue += value & 31;
        }
        pixels += stride;
    }
    int count = width * height;
    return ((((red / count) & 31) << 5) | ((green / count) & 31)) << 5 | ((blue / count) & 31);
}

// FUNCTION: GAME 0x00612d80
bool SBPicture::FUN_00612d80(unsigned short width, unsigned short height)
{
    switch (m_04) {
    case 2: return FUN_006131a0(width, height);
    case 3: return FUN_00612e30(width, height);
    }
    return false;
}

// FUNCTION: GAME 0x00612dc0
int FUN_00612dc0(unsigned short first, unsigned short second)
{
    unsigned short secondIntensity = (((second >> 7) & 15) + (second >> 11) + (second & 31)) / 3;
    unsigned short firstIntensity = (((first >> 7) & 15) + (first >> 11) + (first & 31)) / 3;
    return firstIntensity < secondIntensity;
}

// FUNCTION: GAME 0x00613130
int FUN_00613130(unsigned short first, unsigned short second)
{
    unsigned short secondIntensity = (((second >> 5) & 30) + ((second >> 11) & 15) + (second & 31)) / 3;
    unsigned short firstIntensity = (((first >> 5) & 30) + ((first >> 11) & 15) + (first & 31)) / 3;
    return firstIntensity < secondIntensity;
}

void EmitSBPicture(SBPicture *picture)
{
    picture->FUN_00611bd0(0);
    picture->FUN_00611c50();
    ((RHUnk006114c0 *)picture)->Unk00611e10(0, 0);
    picture->FUN_00611ea0(0);
    picture->FUN_00611f70(0);
    picture->FUN_00612040(0);
    picture->FUN_00612150(0);
    picture->FUN_00612260(0);
    picture->FUN_006122b0(0);
    picture->FUN_00612300(0, 0);
    picture->FUN_006124f0(0, 0, 0, 0);
    picture->FUN_006125c0(0, 0, 0, 0);
    picture->FUN_00612d80(0, 0);
}
