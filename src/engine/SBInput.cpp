#include "SBNullstr.h"
#include "SBInput.h"
#include <list>

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

#include "SBDrawViewport.h"

// GLOBAL: GAME 0x006c1838
SBInputUnk005fb730 *SBInputUnk005fb730::mpInput = 0;

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

// FUNCTION: GAME 0x005f9d00
SBInputUnk005fb730::~SBInputUnk005fb730()
{
    for (int index = 0; index < 16; ++index)
    {
        SBInputUnkDevice *&device = m_144[index];
        if (device)
        {
            if (m_2a9 == 1)
                device->m_table->m_20(device);
            device->m_table->m_08(device);
        }
    }
    if (m_2a5 == 1)
    {
        if (m_2a9 == 1)
            m_08->m_table->m_20(m_08);
        m_08->m_table->m_08(m_08);
    }
    if (m_2a7 == 1)
    {
        if (m_2a9 == 1)
            m_0c->m_table->m_20(m_0c);
        m_0c->m_table->m_08(m_0c);
    }
    if (m_2a4 == 1)
        m_04->m_table->m_08(m_04);
}

// FUNCTION: GAME 0x005f9ea0
bool SBInputUnk005fb730::FUN_005f9ea0(unsigned char active)
{
    if (active == 1 && m_2a9 == 0)
    {
        if (m_2a5 == 1)
        {
            long result = m_08->m_table->m_1c(m_08);
            if (result != 0 && result != 1)
            {
                m_2aa = 2;
                typedef std::string &(std::string::*Assign)(const std::string &, unsigned, unsigned);
                Assign assign = &std::string::assign;
                (m_2ac.*assign)(FUN_005f81d0(result), 0, std::string::npos);
                return false;
            }
            m_2aa = 0;
            m_2a9 = 1;
        }
        if (m_2a7 == 1)
        {
            long result = m_0c->m_table->m_1c(m_0c);
            if (result != 0 && result != 1)
            {
                m_2aa = 2;
                typedef std::string &(std::string::*Assign)(const std::string &, unsigned, unsigned);
                Assign assign = &std::string::assign;
                (m_2ac.*assign)(FUN_005f81d0(result), 0, std::string::npos);
                return false;
            }
            m_2aa = 0;
            m_2a9 = 1;
        }
        for (unsigned char index = 0; index < 16; ++index)
        {
            SBInputUnkDevice *device = m_144[index];
            if (device)
            {
                long result = device->m_table->m_1c(device);
                if (result != 0 && result != 1)
                {
                    m_2aa = 2;
                    m_2ac = FUN_005f81d0(result);
                    return false;
                }
                m_2aa = 0;
                m_2a9 = 1;
            }
        }
        return true;
    }
    m_08->m_table->m_1c(m_08);
    m_0c->m_table->m_1c(m_0c);
    if (active || m_2a9 != 1)
        return true;
    m_2a9 = 0;
    if (m_2a5 == 1)
    {
        m_08->m_table->m_20(m_08);
        m_2aa = 0;
    }
    if (m_2a7 == 1)
    {
        m_0c->m_table->m_20(m_0c);
        m_2aa = 0;
    }
    for (int index = 0; index < 16; ++index)
    {
        SBInputUnkDevice *device = m_144[index];
        if (device)
        {
            device->m_table->m_20(device);
            m_2aa = 0;
        }
    }
    return true;
}

#include "SBInputSystemData.h"

// GLOBAL: GAME 0x0067a6d8
const SBInputDeviceGuid g_inputPovGuid = {{0xa36d02f2, 0x11cfc9f3, 0x4544c7bf, 0x00005453}};
// GLOBAL: GAME 0x0067a6f8
const SBInputDeviceGuid g_inputSliderGuid = {{0xa36d02e4, 0x11cfc9f3, 0x4544c7bf, 0x00005453}};
// GLOBAL: GAME 0x0067a708
const SBInputDeviceGuid g_inputRzAxisGuid = {{0xa36d02e3, 0x11cfc9f3, 0x4544c7bf, 0x00005453}};
// GLOBAL: GAME 0x0067a718
const SBInputDeviceGuid g_inputRyAxisGuid = {{0xa36d02f5, 0x11cfc9f3, 0x4544c7bf, 0x00005453}};
// GLOBAL: GAME 0x0067a728
const SBInputDeviceGuid g_inputRxAxisGuid = {{0xa36d02f4, 0x11cfc9f3, 0x4544c7bf, 0x00005453}};
// GLOBAL: GAME 0x0067a738
const SBInputDeviceGuid g_inputZAxisGuid = {{0xa36d02e2, 0x11cfc9f3, 0x4544c7bf, 0x00005453}};
// GLOBAL: GAME 0x0067a748
const SBInputDeviceGuid g_inputYAxisGuid = {{0xa36d02e1, 0x11cfc9f3, 0x4544c7bf, 0x00005453}};
// GLOBAL: GAME 0x0067a758
const SBInputDeviceGuid g_inputXAxisGuid = {{0xa36d02e0, 0x11cfc9f3, 0x4544c7bf, 0x00005453}};

// GLOBAL: GAME 0x00650d80
const SBInputObjectFormat g_inputJoystickObjects[44] = {
    {&g_inputXAxisGuid, 0, 0x80ffff03, 0x100},
    {&g_inputYAxisGuid, 4, 0x80ffff03, 0x100},
    {&g_inputZAxisGuid, 8, 0x80ffff03, 0x100},
    {&g_inputRxAxisGuid, 12, 0x80ffff03, 0x100},
    {&g_inputRyAxisGuid, 16, 0x80ffff03, 0x100},
    {&g_inputRzAxisGuid, 20, 0x80ffff03, 0x100},
    {&g_inputSliderGuid, 24, 0x80ffff03, 0x100},
    {&g_inputSliderGuid, 28, 0x80ffff03, 0x100},
    {&g_inputPovGuid, 32, 0x80ffff10, 0},
    {&g_inputPovGuid, 36, 0x80ffff10, 0},
    {&g_inputPovGuid, 40, 0x80ffff10, 0},
    {&g_inputPovGuid, 44, 0x80ffff10, 0},
    {0, 48, 0x80ffff0c, 0},
    {0, 49, 0x80ffff0c, 0},
    {0, 50, 0x80ffff0c, 0},
    {0, 51, 0x80ffff0c, 0},
    {0, 52, 0x80ffff0c, 0},
    {0, 53, 0x80ffff0c, 0},
    {0, 54, 0x80ffff0c, 0},
    {0, 55, 0x80ffff0c, 0},
    {0, 56, 0x80ffff0c, 0},
    {0, 57, 0x80ffff0c, 0},
    {0, 58, 0x80ffff0c, 0},
    {0, 59, 0x80ffff0c, 0},
    {0, 60, 0x80ffff0c, 0},
    {0, 61, 0x80ffff0c, 0},
    {0, 62, 0x80ffff0c, 0},
    {0, 63, 0x80ffff0c, 0},
    {0, 64, 0x80ffff0c, 0},
    {0, 65, 0x80ffff0c, 0},
    {0, 66, 0x80ffff0c, 0},
    {0, 67, 0x80ffff0c, 0},
    {0, 68, 0x80ffff0c, 0},
    {0, 69, 0x80ffff0c, 0},
    {0, 70, 0x80ffff0c, 0},
    {0, 71, 0x80ffff0c, 0},
    {0, 72, 0x80ffff0c, 0},
    {0, 73, 0x80ffff0c, 0},
    {0, 74, 0x80ffff0c, 0},
    {0, 75, 0x80ffff0c, 0},
    {0, 76, 0x80ffff0c, 0},
    {0, 77, 0x80ffff0c, 0},
    {0, 78, 0x80ffff0c, 0},
    {0, 79, 0x80ffff0c, 0}
};

// GLOBAL: GAME 0x0067c5d8
const SBInputDataFormat g_inputJoystickFormat = {24, 16, 1, 80, 44, g_inputJoystickObjects};

// GLOBAL: GAME 0x0067a6b8
const SBInputDeviceGuid g_inputKeyboardGuid = {{0x6f1d2b61, 0x11cfd5a0, 0x4544c7bf, 0x00005453}};
// GLOBAL: GAME 0x0067a6c8
const SBInputDeviceGuid g_inputMouseGuid = {{0x6f1d2b60, 0x11cfd5a0, 0x4544c7bf, 0x00005453}};
// GLOBAL: GAME 0x0067a6e8
const SBInputDeviceGuid g_inputKeyGuid = {{0x55728220, 0x11cfd33c, 0x4544c7bf, 0x00005453}};
// GLOBAL: GAME 0x0067a768
const SBInputDeviceGuid g_inputDeviceInterfaceGuid = {{0x57d7c6bc, 0x11d32356, 0xc0009d8e, 0xae44684f}};

// GLOBAL: GAME 0x0064fc60
const SBInputObjectFormat g_inputMouseObjects[7] = {
    {&g_inputXAxisGuid, 0, 0x00ffff03, 0},
    {&g_inputYAxisGuid, 4, 0x00ffff03, 0},
    {&g_inputZAxisGuid, 8, 0x80ffff03, 0},
    {0, 12, 0x00ffff0c, 0}, {0, 13, 0x00ffff0c, 0},
    {0, 14, 0x80ffff0c, 0}, {0, 15, 0x80ffff0c, 0}
};

// GLOBAL: GAME 0x0064fcd0
const SBInputObjectFormat g_inputBufferedMouseObjects[11] = {
    {&g_inputXAxisGuid, 0, 0x00ffff03, 0},
    {&g_inputYAxisGuid, 4, 0x00ffff03, 0},
    {&g_inputZAxisGuid, 8, 0x80ffff03, 0},
    {0, 12, 0x00ffff0c, 0}, {0, 13, 0x00ffff0c, 0},
    {0, 14, 0x80ffff0c, 0}, {0, 15, 0x80ffff0c, 0},
    {0, 16, 0x80ffff0c, 0}, {0, 17, 0x80ffff0c, 0},
    {0, 18, 0x80ffff0c, 0}, {0, 19, 0x80ffff0c, 0}
};

// GLOBAL: GAME 0x0064fd80
const SBInputObjectFormat g_inputKeyboardObjects[256] = {
    {&g_inputKeyGuid, 0x00, 0x8000000c, 0},
    {&g_inputKeyGuid, 0x01, 0x8000010c, 0},
    {&g_inputKeyGuid, 0x02, 0x8000020c, 0},
    {&g_inputKeyGuid, 0x03, 0x8000030c, 0},
    {&g_inputKeyGuid, 0x04, 0x8000040c, 0},
    {&g_inputKeyGuid, 0x05, 0x8000050c, 0},
    {&g_inputKeyGuid, 0x06, 0x8000060c, 0},
    {&g_inputKeyGuid, 0x07, 0x8000070c, 0},
    {&g_inputKeyGuid, 0x08, 0x8000080c, 0},
    {&g_inputKeyGuid, 0x09, 0x8000090c, 0},
    {&g_inputKeyGuid, 0x0a, 0x80000a0c, 0},
    {&g_inputKeyGuid, 0x0b, 0x80000b0c, 0},
    {&g_inputKeyGuid, 0x0c, 0x80000c0c, 0},
    {&g_inputKeyGuid, 0x0d, 0x80000d0c, 0},
    {&g_inputKeyGuid, 0x0e, 0x80000e0c, 0},
    {&g_inputKeyGuid, 0x0f, 0x80000f0c, 0},
    {&g_inputKeyGuid, 0x10, 0x8000100c, 0},
    {&g_inputKeyGuid, 0x11, 0x8000110c, 0},
    {&g_inputKeyGuid, 0x12, 0x8000120c, 0},
    {&g_inputKeyGuid, 0x13, 0x8000130c, 0},
    {&g_inputKeyGuid, 0x14, 0x8000140c, 0},
    {&g_inputKeyGuid, 0x15, 0x8000150c, 0},
    {&g_inputKeyGuid, 0x16, 0x8000160c, 0},
    {&g_inputKeyGuid, 0x17, 0x8000170c, 0},
    {&g_inputKeyGuid, 0x18, 0x8000180c, 0},
    {&g_inputKeyGuid, 0x19, 0x8000190c, 0},
    {&g_inputKeyGuid, 0x1a, 0x80001a0c, 0},
    {&g_inputKeyGuid, 0x1b, 0x80001b0c, 0},
    {&g_inputKeyGuid, 0x1c, 0x80001c0c, 0},
    {&g_inputKeyGuid, 0x1d, 0x80001d0c, 0},
    {&g_inputKeyGuid, 0x1e, 0x80001e0c, 0},
    {&g_inputKeyGuid, 0x1f, 0x80001f0c, 0},
    {&g_inputKeyGuid, 0x20, 0x8000200c, 0},
    {&g_inputKeyGuid, 0x21, 0x8000210c, 0},
    {&g_inputKeyGuid, 0x22, 0x8000220c, 0},
    {&g_inputKeyGuid, 0x23, 0x8000230c, 0},
    {&g_inputKeyGuid, 0x24, 0x8000240c, 0},
    {&g_inputKeyGuid, 0x25, 0x8000250c, 0},
    {&g_inputKeyGuid, 0x26, 0x8000260c, 0},
    {&g_inputKeyGuid, 0x27, 0x8000270c, 0},
    {&g_inputKeyGuid, 0x28, 0x8000280c, 0},
    {&g_inputKeyGuid, 0x29, 0x8000290c, 0},
    {&g_inputKeyGuid, 0x2a, 0x80002a0c, 0},
    {&g_inputKeyGuid, 0x2b, 0x80002b0c, 0},
    {&g_inputKeyGuid, 0x2c, 0x80002c0c, 0},
    {&g_inputKeyGuid, 0x2d, 0x80002d0c, 0},
    {&g_inputKeyGuid, 0x2e, 0x80002e0c, 0},
    {&g_inputKeyGuid, 0x2f, 0x80002f0c, 0},
    {&g_inputKeyGuid, 0x30, 0x8000300c, 0},
    {&g_inputKeyGuid, 0x31, 0x8000310c, 0},
    {&g_inputKeyGuid, 0x32, 0x8000320c, 0},
    {&g_inputKeyGuid, 0x33, 0x8000330c, 0},
    {&g_inputKeyGuid, 0x34, 0x8000340c, 0},
    {&g_inputKeyGuid, 0x35, 0x8000350c, 0},
    {&g_inputKeyGuid, 0x36, 0x8000360c, 0},
    {&g_inputKeyGuid, 0x37, 0x8000370c, 0},
    {&g_inputKeyGuid, 0x38, 0x8000380c, 0},
    {&g_inputKeyGuid, 0x39, 0x8000390c, 0},
    {&g_inputKeyGuid, 0x3a, 0x80003a0c, 0},
    {&g_inputKeyGuid, 0x3b, 0x80003b0c, 0},
    {&g_inputKeyGuid, 0x3c, 0x80003c0c, 0},
    {&g_inputKeyGuid, 0x3d, 0x80003d0c, 0},
    {&g_inputKeyGuid, 0x3e, 0x80003e0c, 0},
    {&g_inputKeyGuid, 0x3f, 0x80003f0c, 0},
    {&g_inputKeyGuid, 0x40, 0x8000400c, 0},
    {&g_inputKeyGuid, 0x41, 0x8000410c, 0},
    {&g_inputKeyGuid, 0x42, 0x8000420c, 0},
    {&g_inputKeyGuid, 0x43, 0x8000430c, 0},
    {&g_inputKeyGuid, 0x44, 0x8000440c, 0},
    {&g_inputKeyGuid, 0x45, 0x8000450c, 0},
    {&g_inputKeyGuid, 0x46, 0x8000460c, 0},
    {&g_inputKeyGuid, 0x47, 0x8000470c, 0},
    {&g_inputKeyGuid, 0x48, 0x8000480c, 0},
    {&g_inputKeyGuid, 0x49, 0x8000490c, 0},
    {&g_inputKeyGuid, 0x4a, 0x80004a0c, 0},
    {&g_inputKeyGuid, 0x4b, 0x80004b0c, 0},
    {&g_inputKeyGuid, 0x4c, 0x80004c0c, 0},
    {&g_inputKeyGuid, 0x4d, 0x80004d0c, 0},
    {&g_inputKeyGuid, 0x4e, 0x80004e0c, 0},
    {&g_inputKeyGuid, 0x4f, 0x80004f0c, 0},
    {&g_inputKeyGuid, 0x50, 0x8000500c, 0},
    {&g_inputKeyGuid, 0x51, 0x8000510c, 0},
    {&g_inputKeyGuid, 0x52, 0x8000520c, 0},
    {&g_inputKeyGuid, 0x53, 0x8000530c, 0},
    {&g_inputKeyGuid, 0x54, 0x8000540c, 0},
    {&g_inputKeyGuid, 0x55, 0x8000550c, 0},
    {&g_inputKeyGuid, 0x56, 0x8000560c, 0},
    {&g_inputKeyGuid, 0x57, 0x8000570c, 0},
    {&g_inputKeyGuid, 0x58, 0x8000580c, 0},
    {&g_inputKeyGuid, 0x59, 0x8000590c, 0},
    {&g_inputKeyGuid, 0x5a, 0x80005a0c, 0},
    {&g_inputKeyGuid, 0x5b, 0x80005b0c, 0},
    {&g_inputKeyGuid, 0x5c, 0x80005c0c, 0},
    {&g_inputKeyGuid, 0x5d, 0x80005d0c, 0},
    {&g_inputKeyGuid, 0x5e, 0x80005e0c, 0},
    {&g_inputKeyGuid, 0x5f, 0x80005f0c, 0},
    {&g_inputKeyGuid, 0x60, 0x8000600c, 0},
    {&g_inputKeyGuid, 0x61, 0x8000610c, 0},
    {&g_inputKeyGuid, 0x62, 0x8000620c, 0},
    {&g_inputKeyGuid, 0x63, 0x8000630c, 0},
    {&g_inputKeyGuid, 0x64, 0x8000640c, 0},
    {&g_inputKeyGuid, 0x65, 0x8000650c, 0},
    {&g_inputKeyGuid, 0x66, 0x8000660c, 0},
    {&g_inputKeyGuid, 0x67, 0x8000670c, 0},
    {&g_inputKeyGuid, 0x68, 0x8000680c, 0},
    {&g_inputKeyGuid, 0x69, 0x8000690c, 0},
    {&g_inputKeyGuid, 0x6a, 0x80006a0c, 0},
    {&g_inputKeyGuid, 0x6b, 0x80006b0c, 0},
    {&g_inputKeyGuid, 0x6c, 0x80006c0c, 0},
    {&g_inputKeyGuid, 0x6d, 0x80006d0c, 0},
    {&g_inputKeyGuid, 0x6e, 0x80006e0c, 0},
    {&g_inputKeyGuid, 0x6f, 0x80006f0c, 0},
    {&g_inputKeyGuid, 0x70, 0x8000700c, 0},
    {&g_inputKeyGuid, 0x71, 0x8000710c, 0},
    {&g_inputKeyGuid, 0x72, 0x8000720c, 0},
    {&g_inputKeyGuid, 0x73, 0x8000730c, 0},
    {&g_inputKeyGuid, 0x74, 0x8000740c, 0},
    {&g_inputKeyGuid, 0x75, 0x8000750c, 0},
    {&g_inputKeyGuid, 0x76, 0x8000760c, 0},
    {&g_inputKeyGuid, 0x77, 0x8000770c, 0},
    {&g_inputKeyGuid, 0x78, 0x8000780c, 0},
    {&g_inputKeyGuid, 0x79, 0x8000790c, 0},
    {&g_inputKeyGuid, 0x7a, 0x80007a0c, 0},
    {&g_inputKeyGuid, 0x7b, 0x80007b0c, 0},
    {&g_inputKeyGuid, 0x7c, 0x80007c0c, 0},
    {&g_inputKeyGuid, 0x7d, 0x80007d0c, 0},
    {&g_inputKeyGuid, 0x7e, 0x80007e0c, 0},
    {&g_inputKeyGuid, 0x7f, 0x80007f0c, 0},
    {&g_inputKeyGuid, 0x80, 0x8000800c, 0},
    {&g_inputKeyGuid, 0x81, 0x8000810c, 0},
    {&g_inputKeyGuid, 0x82, 0x8000820c, 0},
    {&g_inputKeyGuid, 0x83, 0x8000830c, 0},
    {&g_inputKeyGuid, 0x84, 0x8000840c, 0},
    {&g_inputKeyGuid, 0x85, 0x8000850c, 0},
    {&g_inputKeyGuid, 0x86, 0x8000860c, 0},
    {&g_inputKeyGuid, 0x87, 0x8000870c, 0},
    {&g_inputKeyGuid, 0x88, 0x8000880c, 0},
    {&g_inputKeyGuid, 0x89, 0x8000890c, 0},
    {&g_inputKeyGuid, 0x8a, 0x80008a0c, 0},
    {&g_inputKeyGuid, 0x8b, 0x80008b0c, 0},
    {&g_inputKeyGuid, 0x8c, 0x80008c0c, 0},
    {&g_inputKeyGuid, 0x8d, 0x80008d0c, 0},
    {&g_inputKeyGuid, 0x8e, 0x80008e0c, 0},
    {&g_inputKeyGuid, 0x8f, 0x80008f0c, 0},
    {&g_inputKeyGuid, 0x90, 0x8000900c, 0},
    {&g_inputKeyGuid, 0x91, 0x8000910c, 0},
    {&g_inputKeyGuid, 0x92, 0x8000920c, 0},
    {&g_inputKeyGuid, 0x93, 0x8000930c, 0},
    {&g_inputKeyGuid, 0x94, 0x8000940c, 0},
    {&g_inputKeyGuid, 0x95, 0x8000950c, 0},
    {&g_inputKeyGuid, 0x96, 0x8000960c, 0},
    {&g_inputKeyGuid, 0x97, 0x8000970c, 0},
    {&g_inputKeyGuid, 0x98, 0x8000980c, 0},
    {&g_inputKeyGuid, 0x99, 0x8000990c, 0},
    {&g_inputKeyGuid, 0x9a, 0x80009a0c, 0},
    {&g_inputKeyGuid, 0x9b, 0x80009b0c, 0},
    {&g_inputKeyGuid, 0x9c, 0x80009c0c, 0},
    {&g_inputKeyGuid, 0x9d, 0x80009d0c, 0},
    {&g_inputKeyGuid, 0x9e, 0x80009e0c, 0},
    {&g_inputKeyGuid, 0x9f, 0x80009f0c, 0},
    {&g_inputKeyGuid, 0xa0, 0x8000a00c, 0},
    {&g_inputKeyGuid, 0xa1, 0x8000a10c, 0},
    {&g_inputKeyGuid, 0xa2, 0x8000a20c, 0},
    {&g_inputKeyGuid, 0xa3, 0x8000a30c, 0},
    {&g_inputKeyGuid, 0xa4, 0x8000a40c, 0},
    {&g_inputKeyGuid, 0xa5, 0x8000a50c, 0},
    {&g_inputKeyGuid, 0xa6, 0x8000a60c, 0},
    {&g_inputKeyGuid, 0xa7, 0x8000a70c, 0},
    {&g_inputKeyGuid, 0xa8, 0x8000a80c, 0},
    {&g_inputKeyGuid, 0xa9, 0x8000a90c, 0},
    {&g_inputKeyGuid, 0xaa, 0x8000aa0c, 0},
    {&g_inputKeyGuid, 0xab, 0x8000ab0c, 0},
    {&g_inputKeyGuid, 0xac, 0x8000ac0c, 0},
    {&g_inputKeyGuid, 0xad, 0x8000ad0c, 0},
    {&g_inputKeyGuid, 0xae, 0x8000ae0c, 0},
    {&g_inputKeyGuid, 0xaf, 0x8000af0c, 0},
    {&g_inputKeyGuid, 0xb0, 0x8000b00c, 0},
    {&g_inputKeyGuid, 0xb1, 0x8000b10c, 0},
    {&g_inputKeyGuid, 0xb2, 0x8000b20c, 0},
    {&g_inputKeyGuid, 0xb3, 0x8000b30c, 0},
    {&g_inputKeyGuid, 0xb4, 0x8000b40c, 0},
    {&g_inputKeyGuid, 0xb5, 0x8000b50c, 0},
    {&g_inputKeyGuid, 0xb6, 0x8000b60c, 0},
    {&g_inputKeyGuid, 0xb7, 0x8000b70c, 0},
    {&g_inputKeyGuid, 0xb8, 0x8000b80c, 0},
    {&g_inputKeyGuid, 0xb9, 0x8000b90c, 0},
    {&g_inputKeyGuid, 0xba, 0x8000ba0c, 0},
    {&g_inputKeyGuid, 0xbb, 0x8000bb0c, 0},
    {&g_inputKeyGuid, 0xbc, 0x8000bc0c, 0},
    {&g_inputKeyGuid, 0xbd, 0x8000bd0c, 0},
    {&g_inputKeyGuid, 0xbe, 0x8000be0c, 0},
    {&g_inputKeyGuid, 0xbf, 0x8000bf0c, 0},
    {&g_inputKeyGuid, 0xc0, 0x8000c00c, 0},
    {&g_inputKeyGuid, 0xc1, 0x8000c10c, 0},
    {&g_inputKeyGuid, 0xc2, 0x8000c20c, 0},
    {&g_inputKeyGuid, 0xc3, 0x8000c30c, 0},
    {&g_inputKeyGuid, 0xc4, 0x8000c40c, 0},
    {&g_inputKeyGuid, 0xc5, 0x8000c50c, 0},
    {&g_inputKeyGuid, 0xc6, 0x8000c60c, 0},
    {&g_inputKeyGuid, 0xc7, 0x8000c70c, 0},
    {&g_inputKeyGuid, 0xc8, 0x8000c80c, 0},
    {&g_inputKeyGuid, 0xc9, 0x8000c90c, 0},
    {&g_inputKeyGuid, 0xca, 0x8000ca0c, 0},
    {&g_inputKeyGuid, 0xcb, 0x8000cb0c, 0},
    {&g_inputKeyGuid, 0xcc, 0x8000cc0c, 0},
    {&g_inputKeyGuid, 0xcd, 0x8000cd0c, 0},
    {&g_inputKeyGuid, 0xce, 0x8000ce0c, 0},
    {&g_inputKeyGuid, 0xcf, 0x8000cf0c, 0},
    {&g_inputKeyGuid, 0xd0, 0x8000d00c, 0},
    {&g_inputKeyGuid, 0xd1, 0x8000d10c, 0},
    {&g_inputKeyGuid, 0xd2, 0x8000d20c, 0},
    {&g_inputKeyGuid, 0xd3, 0x8000d30c, 0},
    {&g_inputKeyGuid, 0xd4, 0x8000d40c, 0},
    {&g_inputKeyGuid, 0xd5, 0x8000d50c, 0},
    {&g_inputKeyGuid, 0xd6, 0x8000d60c, 0},
    {&g_inputKeyGuid, 0xd7, 0x8000d70c, 0},
    {&g_inputKeyGuid, 0xd8, 0x8000d80c, 0},
    {&g_inputKeyGuid, 0xd9, 0x8000d90c, 0},
    {&g_inputKeyGuid, 0xda, 0x8000da0c, 0},
    {&g_inputKeyGuid, 0xdb, 0x8000db0c, 0},
    {&g_inputKeyGuid, 0xdc, 0x8000dc0c, 0},
    {&g_inputKeyGuid, 0xdd, 0x8000dd0c, 0},
    {&g_inputKeyGuid, 0xde, 0x8000de0c, 0},
    {&g_inputKeyGuid, 0xdf, 0x8000df0c, 0},
    {&g_inputKeyGuid, 0xe0, 0x8000e00c, 0},
    {&g_inputKeyGuid, 0xe1, 0x8000e10c, 0},
    {&g_inputKeyGuid, 0xe2, 0x8000e20c, 0},
    {&g_inputKeyGuid, 0xe3, 0x8000e30c, 0},
    {&g_inputKeyGuid, 0xe4, 0x8000e40c, 0},
    {&g_inputKeyGuid, 0xe5, 0x8000e50c, 0},
    {&g_inputKeyGuid, 0xe6, 0x8000e60c, 0},
    {&g_inputKeyGuid, 0xe7, 0x8000e70c, 0},
    {&g_inputKeyGuid, 0xe8, 0x8000e80c, 0},
    {&g_inputKeyGuid, 0xe9, 0x8000e90c, 0},
    {&g_inputKeyGuid, 0xea, 0x8000ea0c, 0},
    {&g_inputKeyGuid, 0xeb, 0x8000eb0c, 0},
    {&g_inputKeyGuid, 0xec, 0x8000ec0c, 0},
    {&g_inputKeyGuid, 0xed, 0x8000ed0c, 0},
    {&g_inputKeyGuid, 0xee, 0x8000ee0c, 0},
    {&g_inputKeyGuid, 0xef, 0x8000ef0c, 0},
    {&g_inputKeyGuid, 0xf0, 0x8000f00c, 0},
    {&g_inputKeyGuid, 0xf1, 0x8000f10c, 0},
    {&g_inputKeyGuid, 0xf2, 0x8000f20c, 0},
    {&g_inputKeyGuid, 0xf3, 0x8000f30c, 0},
    {&g_inputKeyGuid, 0xf4, 0x8000f40c, 0},
    {&g_inputKeyGuid, 0xf5, 0x8000f50c, 0},
    {&g_inputKeyGuid, 0xf6, 0x8000f60c, 0},
    {&g_inputKeyGuid, 0xf7, 0x8000f70c, 0},
    {&g_inputKeyGuid, 0xf8, 0x8000f80c, 0},
    {&g_inputKeyGuid, 0xf9, 0x8000f90c, 0},
    {&g_inputKeyGuid, 0xfa, 0x8000fa0c, 0},
    {&g_inputKeyGuid, 0xfb, 0x8000fb0c, 0},
    {&g_inputKeyGuid, 0xfc, 0x8000fc0c, 0},
    {&g_inputKeyGuid, 0xfd, 0x8000fd0c, 0},
    {&g_inputKeyGuid, 0xfe, 0x8000fe0c, 0},
    {&g_inputKeyGuid, 0xff, 0x8000ff0c, 0}
};

// GLOBAL: GAME 0x0067c590
const SBInputDataFormat g_inputMouseFormat = {24, 16, 2, 16, 7, g_inputMouseObjects};
// GLOBAL: GAME 0x0067c5a8
const SBInputDataFormat g_inputBufferedMouseFormat = {24, 16, 2, 20, 11, g_inputBufferedMouseObjects};
// GLOBAL: GAME 0x0067c5c0
const SBInputDataFormat g_inputKeyboardFormat = {24, 16, 2, 256, 256, g_inputKeyboardObjects};

// STUB: GAME 0x005fa240
bool SBInputUnk005fb730::FUN_005fa240(unsigned short flags, void *window)
{
    m_00 = window;
    if (flags & 1)
    {
        if (flags & 2)
        {
            m_2aa = 4;
            return false;
        }
        long result = m_04->m_table->m_24(m_04, &g_inputKeyboardGuid, &g_inputDeviceInterfaceGuid, &m_08, 0);
        if (result != 0)
        {
            m_2aa = 5;
            typedef std::string &(std::string::*Assign)(const std::string &, unsigned, unsigned);
            Assign assign = &std::string::assign;
            (m_2ac.*assign)(FUN_005f81d0(result), 0, std::string::npos);
            SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBInput.cpp", 0x108,
                // STRING: GAME 0x006bb2e4
                "Creation of a Direct Input object has failed");
            return false;
        }
        m_2aa = 0;
        m_2a5 = 1;
        m_2a6 = 1;
        result = m_08->m_table->m_2c(m_08, &g_inputKeyboardFormat);
        if (result != 0)
        {
            m_2aa = 7;
            typedef std::string &(std::string::*Assign)(const std::string &, unsigned, unsigned);
            Assign assign = &std::string::assign;
            (m_2ac.*assign)(FUN_005f81d0(result), 0, std::string::npos);
            SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBInput.cpp", 0x119,
                // STRING: GAME 0x006bb2b4
                "Setting the data format of the keyboard failed");
            return false;
        }
        result = m_08->m_table->m_34(m_08, window, 0x16);
        if (result != 0)
        {
            m_2aa = 8;
            typedef std::string &(std::string::*Assign)(const std::string &, unsigned, unsigned);
            Assign assign = &std::string::assign;
            (m_2ac.*assign)(FUN_005f81d0(result), 0, std::string::npos);
            SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBInput.cpp", 0x128,
                // STRING: GAME 0x006bb278
                "Setting the cooperation level of the keyboard failed (%s)", m_2ac.c_str());
            return false;
        }
        SBInputPropertyValue property;
        property.header.size = sizeof(property);
        property.header.headerSize = sizeof(property.header);
        property.header.object = 0;
        property.header.how = 0;
        property.value = 16;
        result = m_08->m_table->m_18(m_08, (const void *)1, &property.header);
        if (result != 0)
        {
            m_2aa = 0x15;
            typedef std::string &(std::string::*Assign)(const std::string &, unsigned, unsigned);
            Assign assign = &std::string::assign;
            (m_2ac.*assign)(FUN_005f81d0(result), 0, std::string::npos);
            SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBInput.cpp", 0x138,
                // STRING: GAME 0x006bb258
                "Setting the buffer size failed");
            return false;
        }
    }
    if (flags & 2)
    {
        if (flags & 1)
        {
            m_2aa = 4;
            return false;
        }
        long result = m_04->m_table->m_24(m_04, &g_inputKeyboardGuid, &g_inputDeviceInterfaceGuid, &m_08, 0);
        if (result != 0)
        {
            m_2aa = 5;
            typedef std::string &(std::string::*Assign)(const std::string &, unsigned, unsigned);
            Assign assign = &std::string::assign;
            (m_2ac.*assign)(FUN_005f81d0(result), 0, std::string::npos);
            SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBInput.cpp", 0x14f,
                "Creation of a Direct Input object has failed");
            return false;
        }
        m_2aa = 0;
        m_2a5 = 1;
        m_2a6 = 0;
        result = m_08->m_table->m_2c(m_08, &g_inputKeyboardFormat);
        if (result != 0)
        {
            m_2aa = 7;
            typedef std::string &(std::string::*Assign)(const std::string &, unsigned, unsigned);
            Assign assign = &std::string::assign;
            (m_2ac.*assign)(FUN_005f81d0(result), 0, std::string::npos);
            SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBInput.cpp", 0x160,
                "Setting the data format of the keyboard failed");
            return false;
        }
        result = m_08->m_table->m_34(m_08, window, 0x15);
        if (result != 0)
        {
            m_2aa = 8;
            typedef std::string &(std::string::*Assign)(const std::string &, unsigned, unsigned);
            Assign assign = &std::string::assign;
            (m_2ac.*assign)(FUN_005f81d0(result), 0, std::string::npos);
            SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBInput.cpp", 0x16f,
                "Setting the cooperation level of the keyboard failed (%s)", m_2ac.c_str());
            return false;
        }
    }
    if (flags & 4)
    {
        if (flags & 8)
        {
            m_2aa = 4;
            return false;
        }
        long result = m_04->m_table->m_24(m_04, &g_inputMouseGuid, &g_inputDeviceInterfaceGuid, &m_0c, 0);
        if (result != 0)
        {
            m_2aa = 6;
            typedef std::string &(std::string::*Assign)(const std::string &, unsigned, unsigned);
            Assign assign = &std::string::assign;
            (m_2ac.*assign)(FUN_005f81d0(result), 0, std::string::npos);
            SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBInput.cpp", 0x188,
                "Creation of a Direct Input object has failed");
            return false;
        }
        m_2aa = 0;
        m_2a7 = 1;
        m_2a8 = 1;
        result = m_0c->m_table->m_2c(m_0c, &g_inputBufferedMouseFormat);
        if (result != 0)
        {
            m_2aa = 9;
            typedef std::string &(std::string::*Assign)(const std::string &, unsigned, unsigned);
            Assign assign = &std::string::assign;
            (m_2ac.*assign)(FUN_005f81d0(result), 0, std::string::npos);
            SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBInput.cpp", 0x199,
                // STRING: GAME 0x006bb22c
                "Setting the data format of the mouse failed");
            return false;
        }
        if (flags & 0x40)
            result = m_0c->m_table->m_34(m_0c, window, 5);
        else
            result = m_0c->m_table->m_34(m_0c, window, 6);
        if (result != 0)
        {
            m_2aa = 0x0a;
            typedef std::string &(std::string::*Assign)(const std::string &, unsigned, unsigned);
            Assign assign = &std::string::assign;
            (m_2ac.*assign)(FUN_005f81d0(result), 0, std::string::npos);
            SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBInput.cpp", 0x1ac,
                // STRING: GAME 0x006bb1f8
                "Setting the cooperation level of the mouse failed");
            return false;
        }
        SBInputPropertyValue property;
        property.header.size = sizeof(property);
        property.header.headerSize = sizeof(property.header);
        property.header.object = 0;
        property.header.how = 0;
        property.value = 16;
        result = m_0c->m_table->m_18(m_0c, (const void *)1, &property.header);
        if (result != 0)
        {
            m_2aa = 0x14;
            m_2ac = FUN_005f81d0(result);
            SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBInput.cpp", 0x1bc,
                "Setting the buffer size failed");
            return false;
        }
    }
    if (flags & 8)
    {
        if (flags & 4)
        {
            m_2aa = 4;
            return false;
        }
        long result = m_04->m_table->m_24(m_04, &g_inputMouseGuid, &g_inputDeviceInterfaceGuid, &m_0c, 0);
        if (result != 0)
        {
            m_2aa = 6;
            m_2ac = FUN_005f81d0(result);
            SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBInput.cpp", 0x1d3,
                "Creation of a Direct Input object has failed");
        }
        else
        {
            m_2aa = 0;
            m_2a7 = 1;
            m_2a8 = 0;
        }
        result = m_0c->m_table->m_2c(m_0c, &g_inputMouseFormat);
        if (result != 0)
        {
            m_2aa = 9;
            m_2ac = FUN_005f81d0(result);
            SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBInput.cpp", 0x1e3,
                "Setting the data format of the mouse failed");
        }
        if (flags & 0x40)
            result = m_0c->m_table->m_34(m_0c, window, 5);
        else
            result = m_0c->m_table->m_34(m_0c, window, 6);
        if (result != 0)
        {
            m_2aa = 0x0a;
            m_2ac = FUN_005f81d0(result);
            SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBInput.cpp", 0x1f0,
                "Setting the cooperation level of the mouse failed");
        }
    }
    return true;
}

// FUNCTION: GAME 0x005fae50
int __stdcall FUN_005fae50(void *value, SBInputUnk005fb730 *input)
{
    input->FUN_005fae70(value);
    return 1;
}

// FUNCTION: GAME 0x005fae70
void SBInputUnk005fb730::FUN_005fae70(void *value)
{
    int &count = *(int *)((char *)this + 0x10);
    if (count < 16)
    {
        std::string name((const char *)value + 0x28);
        ((std::list<std::string> *)((char *)this + 0x14))->push_back(name);
        *(bool *)((char *)this + 0x24) = true;
        ((SBInputDeviceGuid *)((char *)this + 0x44))[count] = *(const SBInputDeviceGuid *)((const char *)value + 4);
        ++count;
    }
}

#include "VMCore.h"

struct SBInputJoystickNameNode
{
    SBInputJoystickNameNode *next;
    SBInputJoystickNameNode *previous;
    VMUnk00634bb0 name;
};

// FUNCTION: GAME 0x005fafc0
RHUnk0051a4e0 *SBInputUnk005fb730::FUN_005fafc0()
{
    SBInputJoystickNames &names = *(SBInputJoystickNames *)((char *)this + 0x14);
    SBInputJoystickNameNode *head = *(SBInputJoystickNameNode **)((char *)&names.values + 4);
    SBInputJoystickNameNode *current = head->next;
    while (current != head)
    {
        SBInputJoystickNameNode *node = current;
        current = current->next;
        node->previous->next = node->next;
        node->next->previous = node->previous;
        node->name.FUN_00634bb0();
        operator delete(node);
        --*(unsigned *)((char *)&names.values + 8);
    }
    names.dirty = true;
    *(unsigned *)((char *)this + 0x10) = 0;
    void *device = *(void **)((char *)this + 4);
    typedef long (__stdcall *Enumerate)(void *, unsigned, int (__stdcall *)(void *, SBInputUnk005fb730 *), SBInputUnk005fb730 *, unsigned);
    Enumerate enumerate = *(Enumerate *)((char *)*(void **)device + 0x10);
    enumerate(device, 4, &FUN_005fae50, this, 1);
    return (RHUnk0051a4e0 *)&names;
}

extern "C" __declspec(dllimport) void *__stdcall GetKeyboardLayout(unsigned long);
extern "C" __declspec(dllimport) int __stdcall GetKeyboardState(unsigned char *);
extern "C" __declspec(dllimport) unsigned __stdcall MapVirtualKeyExA(unsigned, unsigned, void *);
extern "C" __declspec(dllimport) int __stdcall ToAscii(unsigned, unsigned, const unsigned char *, unsigned short *, unsigned);
extern "C" __declspec(dllimport) int __stdcall MultiByteToWideChar(unsigned, unsigned long, const char *, int, unsigned short *, int);

// GLOBAL: GAME 0x006c1834
void *g_inputTextKeyboardLayout = 0;
// GLOBAL: GAME 0x006c1424
unsigned char g_inputTextKeyboardState[256];
// GLOBAL: GAME 0x006c1730
void *g_inputModifierKeyboardLayout = 0;
// GLOBAL: GAME 0x006c1734
unsigned char g_inputModifierKeyboardState[256];

// GLOBAL: GAME 0x006c1528
void *g_inputKeyboardLayout = 0;
// GLOBAL: GAME 0x006c1630
unsigned char g_inputKeyboardState[256];

// Parked at 0.5986: zero hoisting saves EBX and shifts the buffer and arguments.
// STUB: GAME 0x005fb030
int FUN_005fb030(unsigned scanCode, unsigned short *output, int capacity, int mode)
{
    g_inputTextKeyboardLayout = GetKeyboardLayout(0);
    int stateResult = GetKeyboardState(g_inputTextKeyboardState);
    if (!stateResult)
        return stateResult;
    unsigned key = MapVirtualKeyExA(scanCode, 1, g_inputTextKeyboardLayout);
    if (!key)
        return key;
    switch (mode)
    {
    case 1:
        g_inputTextKeyboardState[0x14] = 1;
        break;
    case 2:
        g_inputTextKeyboardState[0x14] = 0;
        g_inputTextKeyboardState[0x10] = 0;
        break;
    }
    unsigned short characters[2];
    characters[0] = 0;
    ((char *)characters)[2] = 0;
    ToAscii(key, scanCode, g_inputTextKeyboardState, characters, 0);
    ToAscii(key, scanCode, g_inputTextKeyboardState, characters, 0);
    ((char *)characters)[1] = 0;
    return MultiByteToWideChar(0, 1, (const char *)characters, -1, output, capacity);
}

// Parked at 0.7826: buffer initialization and modifier-register scheduling differ.
// STUB: GAME 0x005fb0f0
int FUN_005fb0f0(unsigned scanCode, unsigned short *output, const void *input, unsigned capacity)
{
    g_inputModifierKeyboardLayout = GetKeyboardLayout(0);
    unsigned key = MapVirtualKeyExA(scanCode, 1, g_inputModifierKeyboardLayout);
    if (!GetKeyboardState(g_inputModifierKeyboardState))
        return 0;
    const unsigned char *state = (const unsigned char *)input;
    g_inputModifierKeyboardState[0xa0] = state[0x2a];
    g_inputModifierKeyboardState[0xa1] = state[0x36];
    g_inputModifierKeyboardState[0x10] = state[0x2a] | state[0x36];
    g_inputModifierKeyboardState[0xa2] = state[0x1d];
    g_inputModifierKeyboardState[0xa3] = state[0x9d];
    g_inputModifierKeyboardState[0x11] = state[0x9d] | state[0x1d];
    g_inputModifierKeyboardState[0xa4] = state[0x38];
    g_inputModifierKeyboardState[0xa5] = state[0xb8];
    g_inputModifierKeyboardState[0x12] = state[0x38] | state[0xb8];
    unsigned short characters[2];
    characters[0] = 0;
    ((char *)characters)[2] = 0;
    ToAscii(key, scanCode, g_inputModifierKeyboardState, characters, 0);
    return MultiByteToWideChar(0, 1, (const char *)characters, -1, output, capacity);
}

// FUNCTION: GAME 0x005fb1d0
unsigned FUN_005fb1d0(unsigned key)
{
    g_inputKeyboardLayout = GetKeyboardLayout(0);
    if (!GetKeyboardState(g_inputKeyboardState))
        return 0;
    return MapVirtualKeyExA(key, 1, g_inputKeyboardLayout);
}

#include "Decomp.h"

DECOMP_SIZE_ASSERT(SBInputUnk005fb730, 0x2bc)
DECOMP_SIZE_ASSERT(SBInputPropertyHeader, 0x10)
DECOMP_SIZE_ASSERT(SBInputPropertyRange, 0x18)
DECOMP_SIZE_ASSERT(SBInputPropertyValue, 0x14)
DECOMP_SIZE_ASSERT(SBInputDeviceData, 0x10)
DECOMP_SIZE_ASSERT(SBInputDeviceGuid, 0x10)
DECOMP_SIZE_ASSERT(SBInputJoystickNames, 0x30)
DECOMP_STATIC_ASSERT(offsetof(SBInputUnk005fb730, m_04) == 4)
DECOMP_STATIC_ASSERT(offsetof(SBInputUnk005fb730, m_14) == 0x14)
DECOMP_STATIC_ASSERT(offsetof(SBInputUnk005fb730, m_44) == 0x44)
DECOMP_STATIC_ASSERT(offsetof(SBInputJoystickNames, needle) == 0x20)
DECOMP_STATIC_ASSERT(offsetof(SBInputUnk005fb730, m_144) == 0x144)
DECOMP_STATIC_ASSERT(offsetof(SBInputUnk005fb730, m_2a4) == 0x2a4)
DECOMP_STATIC_ASSERT(offsetof(SBInputUnk005fb730, m_2a5) == 0x2a5)
DECOMP_STATIC_ASSERT(offsetof(SBInputUnk005fb730, m_2a6) == 0x2a6)
DECOMP_STATIC_ASSERT(offsetof(SBInputUnk005fb730, m_2a7) == 0x2a7)
DECOMP_STATIC_ASSERT(offsetof(SBInputUnk005fb730, m_2a8) == 0x2a8)
DECOMP_STATIC_ASSERT(offsetof(SBInputUnk005fb730, m_2a9) == 0x2a9)
DECOMP_STATIC_ASSERT(offsetof(SBInputInterfaceTable, m_08) == 0x08)
DECOMP_STATIC_ASSERT(offsetof(SBInputInterfaceTable, m_0c) == 0x0c)
DECOMP_STATIC_ASSERT(offsetof(SBInputInterfaceTable, m_24) == 0x24)
DECOMP_STATIC_ASSERT(offsetof(SBInputUnk005fb730, m_2aa) == 0x2aa)
DECOMP_STATIC_ASSERT(offsetof(SBInputUnk005fb730, m_2ac) == 0x2ac)

// FUNCTION: GAME 0x005fb210
bool SBInputUnk005fb730::FUN_005fb210(unsigned char index, unsigned long object,
    long minimum, long maximum, unsigned long deadzone)
{
    SBInputPropertyRange range;
    range.header.size = sizeof(range);
    range.header.headerSize = sizeof(range.header);
    range.header.object = object;
    range.header.how = 1;
    range.minimum = minimum;
    range.maximum = maximum;
    SBInputUnkDevice *&device = m_144[index];
    long result = device->m_table->m_18(device, (const void *)4, &range.header);
    if (result != 0)
    {
        m_2aa = 0x12;
        typedef std::string &(std::string::*Assign)(const std::string &, unsigned, unsigned);
        Assign assign = &std::string::assign;
        (m_2ac.*assign)(FUN_005f81d0(result), 0, std::string::npos);
        return false;
    }
    SBInputPropertyValue property;
    property.header.size = sizeof(property);
    property.header.headerSize = sizeof(property.header);
    property.header.object = object;
    property.header.how = 1;
    property.value = deadzone;
    result = device->m_table->m_18(device, (const void *)5, &property.header);
    if (result != 0)
    {
        m_2aa = 0x13;
        m_2ac = FUN_005f81d0(result);
        return false;
    }
    return true;
}

#include "SBInputData.h"

inline int SBInputJoystickNames::Find(const std::string &name)
{
    needle = name;
    searching = true;
    cursor = values.begin();
    int limit = values.size();
    int position;
    for (position = 0; position < limit; ++position, cursor++)
    {
        if (*cursor == needle)
            break;
    }
    if (position < limit)
    {
        foundIndex = position;
        cursorIndex = position;
        dirty = false;
    }
    else
    {
        dirty = true;
        foundIndex = -1;
    }
    return foundIndex;
}

// STUB: GAME 0x005fb410
unsigned char SBInputUnk005fb730::FUN_005fb410(std::string name, unsigned short flags, void *window)
{
    if (window == 0)
    {
        if (m_00 == 0)
        {
            m_2aa = 0x16;
            return 0xff;
        }
        window = m_00;
    }
    int index = m_14.Find(name);
    if (index == -1)
    {
        m_2aa = 0x0f;
        return 0xff;
    }
    SBInputUnkDevice *&device = m_144[index];
    long result = m_04->m_table->m_0c(m_04, &m_44[index], &device, 0);
    if (result != 0)
    {
        m_2aa = 0x0c;
        m_2ac = FUN_005f81d0(result);
        return 0xff;
    }
    result = device->m_table->m_2c(device, &g_inputJoystickFormat);
    if (result != 0)
    {
        m_2aa = 0x0d;
        m_2ac = FUN_005f81d0(result);
        return 0xff;
    }
    result = device->m_table->m_34(device, window, flags);
    if (result != 0)
    {
        m_2aa = 0x0e;
        m_2ac = FUN_005f81d0(result);
        return 0xff;
    }
    if (!FUN_005fb210(index, 0, -32768, 32767, 500))
        return 0xff;
    if (!FUN_005fb210(index, 4, -32768, 32767, 500))
        return 0xff;
    result = device->m_table->m_1c(device);
    if (result != 0)
    {
        m_2aa = 0x10;
        m_2ac = FUN_005f81d0(result);
        return 0xff;
    }
    m_2aa = 0;
    return index;
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
bool SBInputUnk005fb730::FUN_005fb770(unsigned char index, void *data, bool *)
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

// FUNCTION: GAME 0x005fbb70
bool SBInputUnk005fb730::FUN_005fbb70(SBInputDeviceData *data)
{
    unsigned long count = -1;
    long result = m_08->m_table->m_28(m_08, sizeof(*data), 0, &count, 1);
    if (count == 0)
        return false;
    bool more = result == 0 && count > 1;
    count = 1;
    result = m_08->m_table->m_28(m_08, sizeof(*data), data, &count, 0);
    if (result != 0)
    {
        m_2aa = 0x0b;
        if (result == (long)0x8007001e)
        {
            result = m_08->m_table->m_1c(m_08);
            if (result == 0)
                return FUN_005fbb70(data);
        }
        m_2ac = FUN_005f81d0(result);
        return false;
    }
    return more;
}

// FUNCTION: GAME 0x005fbdb0
bool SBInputUnk005fb730::FUN_005fbdb0(SBInputDeviceData *data)
{
    unsigned long count = 1;
    long result = m_0c->m_table->m_28(m_0c, sizeof(*data), data, &count, 0);
    if (result != 0)
    {
        m_2aa = 0x0b;
        if (result == (long)0x8007001e)
        {
            result = m_0c->m_table->m_1c(m_0c);
            if (result == 0)
                return FUN_005fbdb0(data);
        }
        m_2ac = FUN_005f81d0(result);
        return false;
    }
    count = -1;
    result = m_0c->m_table->m_28(m_0c, sizeof(*data), 0, &count, 1);
    if (result == 0 && count > 0)
        return true;
    return false;
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
    input->FUN_005fa240(index, 0);
    input->FUN_005fb210(index, 0, -32768, 32767, 500);
    input->FUN_005fb730(index);
    input->FUN_005fb770(index, 0, 0);
    input->FUN_005fb980(0);
    input->FUN_005fba70(0);
    input->FUN_005fbb70(0);
    input->FUN_005fbdb0(0);
    input->FUN_005fbfc0();
    input->~SBInputUnk005fb730();
}
