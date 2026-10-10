#include "SBNullstr.h"
#include "SBSimpleVirtualMachine.h"
#include <new>

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
