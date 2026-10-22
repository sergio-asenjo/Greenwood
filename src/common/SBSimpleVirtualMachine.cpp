#include "SBNullstr.h"
#include "SBSimpleVirtualMachine.h"
#include <new>
#include "RHUnkSectorScript.h"
#include "VMCore.h"
#include <string.h>

typedef int SBSimpleVirtualMachineSizeAssert[(sizeof(SBSimpleVirtualMachine) == 0x5c) ? 1 : -1];

// GLOBAL: GAME 0x006c1950
SBSimpleUnkCodeManager g_unk0x006c1950;

// GLOBAL: GAME 0x006c1960
unsigned char *g_unk0x006c1960 = 0;

// GLOBAL: GAME 0x006c1969
bool g_unk0x006c1969 = false;

// GLOBAL: GAME 0x006c13c0
char g_unk0x006c13c0[16] = { 0 };

inline const char *SBSimpleText(const std::string &text)
{
    const char *value = *(const char *const *)((const char *)&text + 4);
    return value != 0 ? value : "";
}

class RHUnk00639bc0
{
public:
    RHUnk00639bc0 *FUN_00639bc0(int size);
    void FUN_00639740();
    unsigned char *m_memory;
    int m_size;
};

// FUNCTION: GAME 0x00639740
void RHUnk00639bc0::FUN_00639740()
{
    if (m_memory)
        operator delete(m_memory);
}

// FUNCTION: GAME 0x00639920
void FUN_00639920()
{
    ((RHUnk00639bc0 *)&g_unk0x006c1960)->FUN_00639bc0(0);
}

void EmitSBSimpleVirtualMachineGlue()
{
    FUN_00639920();
    ((RHUnk00639bc0 *)&g_unk0x006c1960)->FUN_00639740();
}

// FUNCTION: GAME 0x00639960
SBSimpleVirtualMachine::SBSimpleVirtualMachine()
    : VMCore((VMUnk0063a490 *)&g_unk0x006c1950, (VMUnk0063a140 *)&g_unk0x006c1960), m_bound(false)
{
}

// FUNCTION: GAME 0x006399a0
bool SBSimpleVirtualMachine::Initialize(std::string &name)
{
    if (g_unk0x006c1950.FUN_0063a450(SBSimpleText(name)) == 0) {
        SBSimpleUnk005f9510(g_unk0x006c13c0,
            // STRING: GAME 0x006be1c4
            "SBSimpleVirtualMachine::Initialize: Unable to load the bytecode file %s\n",
            SBSimpleText(name));
        g_unk0x006c1969 = false;
    } else {
        g_unk0x006c1969 = true;
    }
    return g_unk0x006c1969;
}

// FUNCTION: GAME 0x00639a00
bool SBSimpleVirtualMachine::Destroy()
{
    g_unk0x006c1969 = false;
    g_unk0x006c1950.Destroy();
    if (g_unk0x006c1960 != 0) {
        operator delete(g_unk0x006c1960);
        g_unk0x006c1960 = 0;
    }
    return true;
}

// FUNCTION: GAME 0x00639a30
bool RHUnkSectorScript::Unk00639a30(const std::string &name)
{
    if (!((VMCore *)this)->FUN_00639280((void *)&name)) {
        SBAssert(0,
            // STRING: GAME 0x006be18c
            "P:\\Robin Hood\\VirtualMachine\\SBSimpleVirtualMachine.cpp", 103,
            // STRING: GAME 0x006be210
            "Bind failed, unable to find the class %s\n", SBSimpleText(name));
        *(bool *)((char *)this + 0x58) = false;
        return *(volatile bool *)((char *)this + 0x58);
    }
    *(bool *)((char *)this + 0x58) = true;
    return *(volatile bool *)((char *)this + 0x58);
}

// FUNCTION: GAME 0x00639a80
SBSimpleVirtualMachine::~SBSimpleVirtualMachine()
{
    if (m_bound)
        FUN_006392c0();
}

// FUNCTION: GAME 0x00639bc0
RHUnk00639bc0 *RHUnk00639bc0::FUN_00639bc0(int size)
{
    m_size = size;
    if (size > 0) {
        m_memory = (unsigned char *)operator new(size);
        memset(m_memory, 0, size);
    } else {
        m_memory = 0;
    }
    return this;
}
