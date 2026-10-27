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

// Parked at 0.9440: string-copy inlining and device-call registers differ.
// STUB: GAME 0x005f9ea0
bool SBInputUnk005fb730::FUN_005f9ea0(unsigned char active)
{
    if (active == 1 && m_2a8[1] == 0)
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
            m_2a8[1] = 1;
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
            m_2a8[1] = 1;
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
                m_2a8[1] = 1;
            }
        }
        return true;
    }
    m_08->m_table->m_1c(m_08);
    m_0c->m_table->m_1c(m_0c);
    if (active || m_2a8[1] != 1)
        return true;
    m_2a8[1] = 0;
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

// FUNCTION: GAME 0x005fae50
int __stdcall FUN_005fae50(void *value, SBInputUnk005fb730 *input)
{
    input->FUN_005fae70(value);
    return 1;
}

// SIZE 0x10
struct SBInputDeviceGuid
{
    unsigned long m_data[4];
};

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

struct SBInputJoystickNames
{
    unsigned allocator;
    SBInputJoystickNameNode *head;
    unsigned count;
    SBInputJoystickNameNode *cursor;
    bool dirty;
};

// FUNCTION: GAME 0x005fafc0
RHUnk0051a4e0 *SBInputUnk005fb730::FUN_005fafc0()
{
    SBInputJoystickNames &names = *(SBInputJoystickNames *)((char *)this + 0x14);
    SBInputJoystickNameNode *head = names.head;
    SBInputJoystickNameNode *current = head->next;
    while (current != head)
    {
        SBInputJoystickNameNode *node = current;
        current = current->next;
        node->previous->next = node->next;
        node->next->previous = node->previous;
        node->name.FUN_00634bb0();
        operator delete(node);
        --names.count;
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
