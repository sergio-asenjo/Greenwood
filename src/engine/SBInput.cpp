#include "SBNullstr.h"
#include "SBInput.h"

void SBAssert(int, const char *, int, const char *, ...);

static __forceinline const char *SBInputStringData(const std::string &value)
{
    const char *buffer = *(const char *const *)((const char *)&value + 4);
    return buffer ? buffer : "";
}

// LIBRARY: GAME 0x005f78f0
// ?fill@std@@YAXPAV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@1@0ABV21@@Z

class SBGeoPoint2D
{
public:
    float m_x;
    float m_y;
};

class SBDrawViewport
{
public:
    unsigned short *operator[](const SBGeoPoint2D &point) const;
    unsigned short GetPixel(unsigned short x, unsigned short y) const;
    unsigned char m_00[4];
    unsigned short m_width;
    unsigned short m_height;
    unsigned long m_pitch;
    unsigned char m_0c[4];
    unsigned short *m_pixels;
};

// FUNCTION: GAME 0x005f99f0
unsigned short *SBDrawViewport::operator[](const SBGeoPoint2D &point) const
{
    unsigned long row = (m_pitch >> 1) * (int)point.m_y;
    row += (int)point.m_x;
    return m_pixels + row;
}

// FUNCTION: GAME 0x005f9a20
unsigned short SBDrawViewport::GetPixel(unsigned short x, unsigned short y) const
{
    return m_pixels[(m_pitch >> 1) * y + x];
}

// FUNCTION: GAME 0x005fae50
int __stdcall FUN_005fae50(void *value, SBInputUnk005fb730 *input)
{
    input->FUN_005fae70(value);
    return 1;
}

// FUNCTION: GAME 0x005fb730
bool SBInputUnk005fb730::FUN_005fb730(unsigned char index)
{
    if (index < 16) {
        SBInputUnkDevice *&device = m_144[index];
        if (device) {
            device->m_table->m_20(device);
            device->m_table->m_08(device);
            device = 0;
            return true;
        }
    }
    return false;
}

// FUNCTION: GAME 0x005fb770
bool SBInputUnk005fb730::FUN_005fb770(unsigned char index, void *data, int)
{
    if (index < 16) {
        SBInputUnkDevice *&device = m_144[index];
        if (device) {
            device->m_table->m_64(device);
            long result = device->m_table->m_24(device, 0x50, data);
            if (result == 0) return true;
            if (result == (long)0x8007001e) {
                result = device->m_table->m_1c(device);
                if (result != 0) {
                    m_2aa = 0x11;
                    m_2ac = FUN_005f81d0(result);
                } else {
                    device->m_table->m_64(device);
                    result = device->m_table->m_24(device, 0x50, data);
                    if (result != 0) {
                        m_2aa = 0x0b;
                        m_2ac = FUN_005f81d0(result);
                        return false;
                    }
                    return true;
                }
            }
        }
    }
    return false;
}

// FUNCTION: GAME 0x005fb980
bool SBInputUnk005fb730::FUN_005fb980(void *event)
{
    if (!m_2a7) return false;
    long result = m_0c->m_table->m_30(m_0c, event);
    if (result != 0) {
        SBAssert(0,
            // STRING: GAME 0x006bb19c
            "P:\\Robin Hood\\SBLibNG\\SBInput.cpp", 0x474,
            // STRING: GAME 0x006bb314
            "Unable to set event notification DxERR=%s", SBInputStringData(FUN_005f81d0(result)));
        return false;
    }
    return true;
}

// FUNCTION: GAME 0x005fba70
bool SBInputUnk005fb730::FUN_005fba70(void *event)
{
    if (!m_2a5) return false;
    m_08->m_table->m_20(m_08);
    long result = m_08->m_table->m_30(m_08, event);
    if (result != 0) {
        SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBInput.cpp", 0x494,
            "Unable to set event notification DxERR=%s", SBInputStringData(FUN_005f81d0(result)));
        return false;
    }
    m_08->m_table->m_1c(m_08);
    return true;
}

// FUNCTION: GAME 0x005fbfc0
bool SBInputUnk005fb730::FUN_005fbfc0()
{
    if (m_2a5 == 1) {
        long result;
        do {
            result = m_08->m_table->m_1c(m_08);
        } while (result != 0 && result != 1);
    }
    if (m_2a7 == 1) {
        long result;
        do {
            result = m_0c->m_table->m_1c(m_0c);
        } while (result != 0 && result != 1);
    }
    return true;
}

void SBInputEmit(SBInputUnk005fb730 *input, unsigned char index)
{
    SBDrawViewport *viewport = (SBDrawViewport *)input;
    viewport->operator[](*(SBGeoPoint2D *)input);
    viewport->GetPixel(index, index);
    input->FUN_005fb730(index);
    input->FUN_005fb770(index, 0, 0);
    input->FUN_005fb980(0);
    input->FUN_005fba70(0);
    input->FUN_005fbfc0();
}
