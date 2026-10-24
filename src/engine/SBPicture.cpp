#include "SBNullstr.h"
#include "SBPicture.h"
#include "RHLoadingScreen.h"
#include <new>
#include <vector>
#include <algorithm>

// LIBRARY: GAME 0x006136a0
// ?_Sort@std@@YAXPAG0P6A_NGG@Z0@Z

// LIBRARY: GAME 0x006137d0
// ?_Insertion_sort_1@std@@YAXPAG0P6A_NGG@Z0@Z

// SIZE 0x18
class SBPictureUnkView
{
public:
    SBPictureUnkView();
    ~SBPictureUnkView();
    char m_00[4];
    unsigned short m_width;
    unsigned short m_height;
    unsigned long m_pitch;
    unsigned short m_depth;
    char m_0e[2];
    unsigned short *m_data;
    char m_14[4];
};

class SBPictureUnkDrawManager
{
public:
    bool Unk005e5a00(unsigned long, SBPictureUnkView &, unsigned long);
    void Unk005e5ea0(SBPictureUnkView &);
    char m_00[0x10c];
    unsigned short m_depth;
    unsigned short Depth() const { return m_depth; }
};

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

// FUNCTION: GAME 0x00611c80
bool SBPicture::FUN_00611c80(SBPictureUnkDrawManager *draw, unsigned long surface)
{
    SBPictureUnkView view;
    if (!((RHUnkFXDraw *)draw)->Unk005e5a00(surface, (RHUnk00613e90 &)view, 0))
        return false;
    if (m_1c != 0) {
        unsigned char *old = m_14;
        m_1c = 0;
        operator delete(old);
    }
    if (m_04 == 1) {
        void *old = m_18;
        operator delete(old);
    }
    m_04 = draw->Depth() == 16 ? 3 : 2;
    m_20 = view.m_width;
    m_22 = view.m_height;
    m_24 = view.m_width;
    m_1c = view.m_height * view.m_width * 2;
    unsigned short *picture = new unsigned short[m_1c / 2];
    m_14 = (unsigned char *)picture;
    unsigned long pitch = view.m_pitch >> 1;
    unsigned short *source = view.m_data;
    unsigned long sourceOffset = 0;
    unsigned long destinationOffset = 0;
    for (unsigned short y = 0; y < view.m_height; ++y) {
        for (unsigned short x = 0; x < view.m_width; ++x)
            picture[x + destinationOffset] = source[x + sourceOffset];
        sourceOffset += pitch;
        destinationOffset += view.m_width;
    }
    ((RHUnkFXDraw *)draw)->Unk005e5ea0((RHUnk00613e90 &)view);
    return true;
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

// FUNCTION: GAME 0x00611ea0
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
    for (unsigned int i = 0; i < m_1c / 3; ++i)
    {
        unsigned short value = source[i * 3] & 0xf8;
        value = (value << 5) | (unsigned short)(source[i * 3 + 1] & 0xfc);
        value = (value << 3) | (unsigned short)(source[i * 3 + 2] >> 3);
        picture[i] = value;
    }
    m_04 = 3;
    operator delete(m_14);
    m_14 = (unsigned char *)picture;
    m_24 = m_20 * 2;
    return true;
}

// FUNCTION: GAME 0x00611f70
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
    for (unsigned int i = 0; i < m_1c / 3; ++i)
    {
        unsigned short value = source[i * 3] & 0xf8;
        value = (value << 5) | (unsigned short)(source[i * 3 + 1] & 0xf8);
        value = (value << 2) | (unsigned short)(source[i * 3 + 2] >> 3);
        picture[i] = value;
    }
    m_04 = 2;
    operator delete(m_14);
    m_14 = (unsigned char *)picture;
    m_24 = m_20 * 2;
    return true;
}

// FUNCTION: GAME 0x00612040
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
    for (unsigned int i = 0; i < m_1c / 2; ++i) {
        int green = ((source[i] >> 5) & 63) * 256 / 64;
        int blue = (source[i] & 31) * 256 / 32;
        int red = (source[i] >> 11) * 256 / 32;
        picture[i * 3] = red;
        picture[i * 3 + 1] = green;
        picture[i * 3 + 2] = blue;
    }
    m_04 = 4;
    operator delete(m_14);
    m_14 = picture;
    m_24 = m_20 * 3;
    return true;
}

// FUNCTION: GAME 0x00612150
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
    for (unsigned int i = 0; i < m_1c / 2; ++i) {
        int green = ((source[i] >> 5) & 31) * 256 / 32;
        int blue = (source[i] & 31) * 256 / 32;
        int red = ((source[i] >> 10) & 31) * 256 / 32;
        picture[i * 3] = red;
        picture[i * 3 + 1] = green;
        picture[i * 3 + 2] = blue;
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
bool SBPicture::FUN_00612300(const SBGeoVector2D &size, int mode)
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

// FUNCTION: GAME 0x00612350
bool SBPicture::FUN_00612350(const SBGeoVector2D &size)
{
    float allocationWidth = size.m_x;
    unsigned short *picture = (unsigned short *)operator new((int)(allocationWidth * size.GetY()) * 2);
    unsigned short *source = (unsigned short *)m_14;
    if (!picture) {
        SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBPicture.cpp", 0x253,
            // STRING: GAME 0x006bb72c
            "Unable to allocate a new picture to resize the old one");
        return false;
    }
    unsigned short width = (int)size.GetX();
    float x = 0.0f;
    float y = 0.0f;
    float stepX = size.GetX() / m_20;
    float stepY = size.GetY() / m_22;
    for (unsigned short row = 0; row < m_22; ++row) {
        for (unsigned short column = 0; column < m_20; ++column) {
            picture[(unsigned short)(int)y * width + (unsigned short)(int)x] = source[row * m_24 + column];
            x += stepX;
        }
        y += stepY;
    }
    operator delete(m_14);
    m_14 = (unsigned char *)picture;
    m_24 = width;
    m_20 = (int)size.GetX();
    m_22 = (int)size.GetY();
    return true;
}

// FUNCTION: GAME 0x006124f0
unsigned short SBPicture::FUN_006124f0(unsigned short *pixels, unsigned short stride,
    unsigned short width, unsigned short height)
{
    unsigned short red = 0;
    unsigned short green = 0;
    unsigned short blue = 0;
    for (unsigned short y = 0; y < height; ++y) {
        unsigned short *row = pixels;
        for (unsigned short x = 0; x < width; ++x) {
            unsigned short value = *row++;
            red += value >> 11;
            green += (value >> 5) & 62;
            blue += value & 31;
        }
        pixels += stride;
    }
    return (((red / (width * height)) << 6) | ((green / (width * height)) & 63)) << 5
        | ((blue / (width * height)) & 31);
}

// FUNCTION: GAME 0x006125c0
unsigned short SBPicture::FUN_006125c0(unsigned short *pixels, unsigned short stride,
    unsigned short width, unsigned short height)
{
    unsigned short red = 0;
    unsigned short green = 0;
    unsigned short blue = 0;
    for (unsigned short y = 0; y < height; ++y) {
        unsigned short *row = pixels;
        for (unsigned short x = 0; x < width; ++x) {
            unsigned short value = *row++;
            red += (value >> 10) & 31;
            green += (value >> 5) & 31;
            blue += value & 31;
        }
        pixels += stride;
    }
    return ((((red / (width * height)) & 31) << 5) | ((green / (width * height)) & 31)) << 5
        | ((blue / (width * height)) & 31);
}

// FUNCTION: GAME 0x00612690
bool SBPicture::FUN_00612690(const SBGeoVector2D &size)
{
    float allocationWidth = size.GetX();
    double allocationHeight = size.GetY();
    unsigned short *picture = (unsigned short *)operator new((int)(allocationWidth * (float)allocationHeight) * 2);
    unsigned short *source = (unsigned short *)m_14;
    if (!picture) {
        SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBPicture.cpp", 0x305,
            "Unable to allocate a new picture to resize the old one");
        return false;
    }
    unsigned short width = (int)size.GetX();
    float stepX = m_20 / size.GetX();
    float stepY = m_22 / size.GetY();
    float y = 0.0f;
    for (unsigned short row = 0; row < size.GetY(); ++row) {
        float x = 0.0f;
        double columnValue;
        for (unsigned short column = 0; (columnValue = column, (float)columnValue < size.GetX()); ++column) {
            int blockHeight = (int)stepY;
            int blockWidth = (int)stepX;
            picture[column + row * width] = FUN_006124f0(source + m_24 * (int)y + (int)x, m_24,
                blockWidth < 1 ? 1 : blockWidth, blockHeight < 1 ? 1 : blockHeight);
            x += stepX;
        }
        y += stepY;
    }
    operator delete(m_14);
    m_14 = (unsigned char *)picture;
    m_24 = width;
    m_20 = (int)size.GetX();
    m_22 = (int)size.GetY();
    m_1c = (int)(size.GetX() * size.GetY() * 2);
    return true;
}

// FUNCTION: GAME 0x006128b0
bool SBPicture::FUN_006128b0(const SBGeoVector2D &size)
{
    float allocationWidth = size.GetX();
    double allocationHeight = size.GetY();
    unsigned short *picture = (unsigned short *)operator new((int)(allocationWidth * (float)allocationHeight) * 2);
    unsigned short *source = (unsigned short *)m_14;
    if (!picture) {
        SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBPicture.cpp", 0x34c,
            "Unable to allocate a new picture to resize the old one");
        return false;
    }
    unsigned short width = (int)size.GetX();
    float stepX = m_20 / size.GetX();
    float stepY = m_22 / size.GetY();
    float y = 0.0f;
    for (unsigned short row = 0; row < size.GetY(); ++row) {
        float x = 0.0f;
        double columnValue;
        for (unsigned short column = 0; (columnValue = column, (float)columnValue < size.GetX()); ++column) {
            int blockHeight = (int)stepY;
            int blockWidth = (int)stepX;
            picture[row * width + column] = FUN_006125c0(source + m_24 * (int)y + (int)x, m_24,
                blockWidth < 1 ? 1 : blockWidth, blockHeight < 1 ? 1 : blockHeight);
            x += stepX;
        }
        y += stepY;
    }
    operator delete(m_14);
    m_14 = (unsigned char *)picture;
    m_24 = width;
    m_20 = (int)size.GetX();
    m_22 = (int)size.GetY();
    m_1c = (int)(size.GetX() * size.GetY() * 2);
    return true;
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
bool FUN_00612dc0(unsigned short first, unsigned short second)
{
    unsigned short secondIntensity = (((second >> 7) & 15) + (second >> 11) + (second & 31)) / 3;
    unsigned short firstIntensity = (((first >> 7) & 15) + (first >> 11) + (first & 31)) / 3;
    return firstIntensity < secondIntensity;
}

// <vector>/<algorithm> are included at the top (see the include block): moving them
// after these resize functions flips FUN_00612350's loop-exit reload order.

// FUNCTION: GAME 0x00612e30
bool SBPicture::FUN_00612e30(unsigned short width, unsigned short height)
{
    std::vector<unsigned short> window;
    --width;
    --height;
    int count;
    window.resize(count = (width + 1) * (height + 1));
    unsigned short *first = window.begin();
    unsigned short *last = window.end();
    unsigned short *picture = (unsigned short *)operator new(m_22 * m_20 * 2);
    for (unsigned short y = 0; y < m_22; ++y) {
        for (unsigned short x = 0; x < m_20; ++x) {
            unsigned short index = 0;
            for (short row = y - (height >> 1); row <= (height >> 1) + y; ++row) {
                for (short column = x - (width >> 1); column <= (width >> 1) + x; ++column) {
                    if (column >= 0 && column < m_20 && row >= 0 && row < m_22)
                        window[index] = ((unsigned short *)m_14)[row * m_20 + column];
                    else
                        window[index] = 0;
                    ++index;
                }
            }
            std::sort(first, last, FUN_00612dc0);
            picture[y * m_20 + x] = window[count >> 1];
        }
    }
    operator delete(m_14);
    m_14 = (unsigned char *)picture;
    return true;
}

// FUNCTION: GAME 0x00613130
bool FUN_00613130(unsigned short first, unsigned short second)
{
    unsigned short secondIntensity = (((second >> 5) & 30) + ((second >> 11) & 15) + (second & 31)) / 3;
    unsigned short firstIntensity = (((first >> 5) & 30) + ((first >> 11) & 15) + (first & 31)) / 3;
    return firstIntensity < secondIntensity;
}

// FUNCTION: GAME 0x006131a0
bool SBPicture::FUN_006131a0(unsigned short width, unsigned short height)
{
    std::vector<unsigned short> window;
    --width;
    --height;
    int count;
    window.resize(count = (width + 1) * (height + 1));
    unsigned short *first = window.begin();
    unsigned short *last = window.end();
    unsigned short *picture = (unsigned short *)operator new(m_22 * m_20 * 2);
    for (unsigned short y = 0; y < m_22; ++y) {
        for (unsigned short x = 0; x < m_20; ++x) {
            unsigned short index = 0;
            for (short row = y - (height >> 1); row <= (height >> 1) + y; ++row) {
                for (short column = x - (width >> 1); column <= (width >> 1) + x; ++column) {
                    if (column >= 0 && column < m_20 && row >= 0 && row < m_22)
                        window[index] = ((unsigned short *)m_14)[row * m_20 + column];
                    else
                        window[index] = 0;
                    ++index;
                }
            }
            std::sort(first, last, FUN_00613130);
            picture[y * m_20 + x] = window[count >> 1];
        }
    }
    operator delete(m_14);
    m_14 = (unsigned char *)picture;
    return true;
}

void EmitSBPicture(SBPicture *picture, const SBGeoVector2D &size)
{
    picture->FUN_00611bd0(0);
    picture->FUN_00611c50();
    picture->FUN_00611c80(0, 0);
    ((RHUnk006114c0 *)picture)->Unk00611e10(0, 0);
    picture->FUN_00611ea0(0);
    picture->FUN_00611f70(0);
    picture->FUN_00612040(0);
    picture->FUN_00612150(0);
    picture->FUN_00612260(0);
    picture->FUN_006122b0(0);
    picture->FUN_00612300(size, 0);
    picture->FUN_006124f0(0, 0, 0, 0);
    picture->FUN_006125c0(0, 0, 0, 0);
    picture->FUN_00612d80(0, 0);
    picture->FUN_00612e30(0, 0);
    picture->FUN_006131a0(0, 0);
}

// FUNCTION: GAME 0x00611be0
void *SBPicture::FUN_00611be0(unsigned flags)
{
    this->~SBPicture();
    if (flags & 1)
        operator delete(this);
    return this;
}

// Parked: member destruction is explicit here, so VC6 omits the target's EH cleanup frame.
SBPicture::~SBPicture()
{
    *(unsigned *)this = 0x67a8bc;
    FUN_00611c50();
    ((SBGeoPoint2D *)((char *)this + 0x28))->~SBGeoPoint2D();
}
