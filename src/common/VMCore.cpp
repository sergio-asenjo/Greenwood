#include "SBNullstr.h"
#include "VMCore.h"
#include "SCQuad.h"
#include "SB.h"
#include <new>
#include <stddef.h>

typedef int VMArraySizeAssert[(sizeof(VMUnk0063a140) == 8) ? 1 : -1];
typedef int VMActivationSizeAssert[(sizeof(VMUnk0063a400) == 0x1c) ? 1 : -1];
typedef int VMStackSizeAssert[(sizeof(VMUnk0063a250) == 0x10) ? 1 : -1];
typedef int VMNativeStackSizeAssert[(sizeof(VMNativeStack) == 0x0c) ? 1 : -1];
typedef int VMCoreSizeAssert[(sizeof(VMCore) == 0x48) ? 1 : -1];
typedef int VMActivationAreaOffsetAssert[(offsetof(VMUnk0063a400, m_0c) == 0x0c) ? 1 : -1];
typedef int VMActivationLocalOffsetAssert[(offsetof(VMUnk0063a400, m_14) == 0x14) ? 1 : -1];
typedef int VMStackRecordsOffsetAssert[(offsetof(VMUnk0063a250, m_records) == 4) ? 1 : -1];
typedef int VMCoreStackOffsetAssert[(offsetof(VMCore, m_0c) == 0x0c) ? 1 : -1];
typedef int VMCoreAreaOffsetAssert[(offsetof(VMCore, m_1c) == 0x1c) ? 1 : -1];
typedef int VMCoreNativeOffsetAssert[(offsetof(VMCore, m_native) == 0x30) ? 1 : -1];

// GLOBAL: GAME 0x006c1940
int g_unk0x006c1940 = 0;

typedef int (__cdecl *VMUnk00635210Handler)(void *);

// GLOBAL: GAME 0x006c1944
VMUnk00635210Handler *g_unk0x006c1944 = 0;

#include <list>

// GLOBAL: GAME 0x006c1930
std::list<VMUnk00634ab0Record> g_unk0x006c1930;

// FUNCTION: GAME 0x00634ab0
void VMCore::RegisterSerializerForType(const std::string &name, void (__cdecl *serializer)(SBFile &, void *&))
{
    VMUnk00634ab0Record record;
    std::string &(std::string::*assign)(const std::string &, unsigned int, unsigned int) = &std::string::assign;
    (((std::string *)&record.m_name)->*assign)(name, 0, std::string::npos);
    record.m_serializer = serializer;
    g_unk0x006c1930.push_back(record);
}

// FUNCTION: GAME 0x00634bb0
void VMUnk00634bb0::FUN_00634bb0()
{
    if (m_04 != 0) {
        unsigned char *count = m_04 - 1;
        unsigned char value = *count;
        if (value != 0 && value != 0xff)
            *count = value - 1;
        else
            operator delete(count);
    }
    m_04 = 0;
    m_08 = 0;
    m_0c = 0;
}

// FUNCTION: GAME 0x00634bf0
void VMCore::Empty()
{
    SBAssert(0,
        // STRING: GAME 0x006be044
        "P:\\Robin Hood\\VirtualMachine\\VMCore.cpp", 100,
        // STRING: GAME 0x006be090
        "VMCore::Empty: Operation not allowed.\n");
    m_24 = -1;
}

// FUNCTION: GAME 0x00634c20
void VMCore::FUN_00634c20()
{
    ++m_24;
}

inline int *VMCore::GetSymbolValuePtr(unsigned short &value)
{
    unsigned short flags = value & 0xc000;
    if (flags == 0)
        return m_08->FUN_0063a1e0(value & 0x3fff);
    if (flags == 0x4000)
        return m_1c.FUN_0063a1e0(value & 0x3fff);
    if (flags == 0x8000) {
        VMUnk0063a400 *object = m_0c.m_records.back();
        return object->m_0c.FUN_0063a1e0(value & 0x3fff);
    }
    if (flags == 0xc000) {
        VMUnk0063a400 *object = m_0c.m_records.back();
        return object->m_14.FUN_0063a1e0(value & 0x3fff);
    }
    SBAssert(0, "P:\\Robin Hood\\VirtualMachine\\VMCore.cpp", 0x516,
        // STRING: GAME 0x006be0b8
        "VMCore::GetSymbolValuePtr: flags are not recognized.\n");
    return 0;
}

// FUNCTION: GAME 0x00634c30
void VMCore::FUN_00634c30()
{
    m_0c.FUN_0063a370(GetSymbolValuePtr(((unsigned short *)m_28)[2]), 4);
    ++m_24;
}

// FUNCTION: GAME 0x00634d30
void VMCore::FUN_00634d30()
{
    m_0c.m_records.back()->m_0c.FUN_0063a140(
        ((unsigned short *)m_28)[2], false);
    m_0c.m_records.back()->m_14.FUN_0063a140(
        ((unsigned short *)m_28)[3], false);
    ++m_24;
}

// FUNCTION: GAME 0x00634d80
void VMCore::EndFunction()
{
    SBAssert(0, "P:\\Robin Hood\\VirtualMachine\\VMCore.cpp", 140,
        // STRING: GAME 0x006be0f0
        "VMCore::EndFunction: Operation not allowed (add a Return !!!).\n");
    ++m_24;
}

// FUNCTION: GAME 0x00634db0
void VMCore::FUN_00634db0()
{
    m_0c.FUN_0063a250(m_24 + 1, 0);
    m_24 = m_28[1];
}

// FUNCTION: GAME 0x00634dd0
void VMCore::FUN_00634dd0()
{
    m_24 = m_0c.FUN_0063a320();
}

// Parked: return-value store chain and final reload use different registers.
// STUB: GAME 0x00634de0
void VMCore::FUN_00634de0()
{
    int *value = GetSymbolValuePtr(((unsigned short *)m_28)[2]);
    if (m_0c.m_records.size() != 1) {
        std::list<VMUnk0063a400 *>::iterator previous = m_0c.m_records.end();
        --previous;
        --previous;
        (*previous)->m_04 = *value;
    }
    m_2c = *value;
    m_24 = m_0c.FUN_0063a320();
}

// FUNCTION: GAME 0x00634eb0
void VMCore::FUN_00634eb0()
{
    int *source = m_0c.FUN_0063a3b0(m_28[2]);
    *GetSymbolValuePtr(((unsigned short *)m_28)[2]) = *source;
    ++m_24;
}

// FUNCTION: GAME 0x00634fa0
void VMCore::FUN_00634fa0()
{
    int *destination = m_0c.FUN_0063a3b0(m_28[2]);
    *destination = *GetSymbolValuePtr(((unsigned short *)m_28)[2]);
    ++m_24;
}

// FUNCTION: GAME 0x00635090
void VMCore::FUN_00635090()
{
    int *value = GetSymbolValuePtr(((unsigned short *)m_28)[2]);
    *value = m_0c.m_records.back()->m_04;
    ++m_24;
}

// Parked: native-stack store folds the address into SIB and interleaves increments.
// STUB: GAME 0x00635150
void VMCore::FUN_00635150()
{
    int *value = GetSymbolValuePtr(((unsigned short *)m_28)[2]);
    *(int *)(m_native.m_data + m_native.m_size) = *value;
    m_native.m_size += 4;
    ++m_24;
}

// FUNCTION: GAME 0x00635210
void VMCore::FUN_00635210()
{
    int index = m_24;
    int result = g_unk0x006c1944[m_28[1]](&m_native);
    m_24 = index + 1;
    m_native.m_result = result;
}

// FUNCTION: GAME 0x00635240
void VMCore::FUN_00635240()
{
    *GetSymbolValuePtr(((unsigned short *)m_28)[2]) = m_native.m_result;
    ++m_24;
}

// FUNCTION: GAME 0x00635320
void VMCore::FUN_00635320()
{
    m_24 = m_28[1];
}

// FUNCTION: GAME 0x00635330
void VMCore::FUN_00635330()
{
    int *value = GetSymbolValuePtr(((unsigned short *)m_28)[2]);
    if (*value != 0)
        m_24 = m_28[2];
    else
        ++m_24;
}

// FUNCTION: GAME 0x006353f0
void VMCore::FUN_006353f0()
{
    int *value = GetSymbolValuePtr(((unsigned short *)m_28)[2]);
    if (*value == 0)
        m_24 = m_28[2];
    else
        ++m_24;
}

// FUNCTION: GAME 0x006354b0
void VMCore::FUN_006354b0()
{
    int *destination = GetSymbolValuePtr(((unsigned short *)m_28)[2]);
    *destination = *GetSymbolValuePtr(((unsigned short *)m_28)[3]);
    ++m_24;
}

// FUNCTION: GAME 0x00635630
void VMCore::FUN_00635630()
{
    int *destination = GetSymbolValuePtr(((unsigned short *)m_28)[2]);
    *destination = *GetSymbolValuePtr(((unsigned short *)m_28)[3]);
    ++m_24;
}

// FUNCTION: GAME 0x006357b0
void VMCore::FUN_006357b0()
{
    int *destination = GetSymbolValuePtr(((unsigned short *)m_28)[2]);
    *destination = m_28[2];
    ++m_24;
}

// FUNCTION: GAME 0x006358a0
void VMCore::FUN_006358a0()
{
    int *destination = GetSymbolValuePtr(((unsigned short *)m_28)[2]);
    *destination = m_28[2];
    ++m_24;
}

// FUNCTION: GAME 0x00635990
void VMCore::FUN_00635990()
{
    int *destination = GetSymbolValuePtr(((unsigned short *)m_28)[2]);
    *destination = -*GetSymbolValuePtr(((unsigned short *)m_28)[3]);
    ++m_24;
}

// FUNCTION: GAME 0x00635b20
void VMCore::FUN_00635b20()
{
    float *destination = (float *)GetSymbolValuePtr(((unsigned short *)m_28)[2]);
    *destination = -*(float *)GetSymbolValuePtr(((unsigned short *)m_28)[3]);
    ++m_24;
}

// FUNCTION: GAME 0x00635cb0
void VMCore::FUN_00635cb0()
{
    int *destination = GetSymbolValuePtr(((unsigned short *)m_28)[2]);
    *destination = (int)*(float *)GetSymbolValuePtr(((unsigned short *)m_28)[3]);
    ++m_24;
}

// FUNCTION: GAME 0x00635e50
void VMCore::FUN_00635e50()
{
    float *destination = (float *)GetSymbolValuePtr(((unsigned short *)m_28)[2]);
    *destination = (float)*GetSymbolValuePtr(((unsigned short *)m_28)[3]);
    ++m_24;
}

// FUNCTION: GAME 0x00635fd0
void VMCore::FUN_00635fd0()
{
    int *destination = GetSymbolValuePtr(((unsigned short *)m_28)[2]);
    int *left = GetSymbolValuePtr(((unsigned short *)m_28)[3]);
    *destination = *left + *GetSymbolValuePtr(((unsigned short *)m_28)[4]);
    ++m_24;
}

// FUNCTION: GAME 0x00636210
void VMCore::FUN_00636210()
{
    int *destination = GetSymbolValuePtr(((unsigned short *)m_28)[2]);
    int *left = GetSymbolValuePtr(((unsigned short *)m_28)[3]);
    *destination = *left - *GetSymbolValuePtr(((unsigned short *)m_28)[4]);
    ++m_24;
}

// FUNCTION: GAME 0x00636450
void VMCore::FUN_00636450()
{
    int *destination = GetSymbolValuePtr(((unsigned short *)m_28)[2]);
    int *left = GetSymbolValuePtr(((unsigned short *)m_28)[3]);
    *destination = *left * *GetSymbolValuePtr(((unsigned short *)m_28)[4]);
    ++m_24;
}

// FUNCTION: GAME 0x00636680
void VMCore::FUN_00636680()
{
    int *destination = GetSymbolValuePtr(((unsigned short *)m_28)[2]);
    int *left = GetSymbolValuePtr(((unsigned short *)m_28)[3]);
    *destination = *left / *GetSymbolValuePtr(((unsigned short *)m_28)[4]);
    ++m_24;
}

// FUNCTION: GAME 0x006368c0
void VMCore::FUN_006368c0()
{
    int *destination = GetSymbolValuePtr(((unsigned short *)m_28)[2]);
    int *left = GetSymbolValuePtr(((unsigned short *)m_28)[3]);
    *destination = *left | *GetSymbolValuePtr(((unsigned short *)m_28)[4]);
    ++m_24;
}

// FUNCTION: GAME 0x00636b00
void VMCore::FUN_00636b00()
{
    int *destination = GetSymbolValuePtr(((unsigned short *)m_28)[2]);
    int *left = GetSymbolValuePtr(((unsigned short *)m_28)[3]);
    *destination = *left & *GetSymbolValuePtr(((unsigned short *)m_28)[4]);
    ++m_24;
}

// FUNCTION: GAME 0x00636d40
void VMCore::FUN_00636d40()
{
    int *destination = GetSymbolValuePtr(((unsigned short *)m_28)[2]);
    int *left = GetSymbolValuePtr(((unsigned short *)m_28)[3]);
    *destination = *left ^ *GetSymbolValuePtr(((unsigned short *)m_28)[4]);
    ++m_24;
}

// FUNCTION: GAME 0x00636f80
void VMCore::FUN_00636f80()
{
    float *destination = (float *)GetSymbolValuePtr(((unsigned short *)m_28)[2]);
    float *left = (float *)GetSymbolValuePtr(((unsigned short *)m_28)[3]);
    *destination = *left + *(float *)GetSymbolValuePtr(((unsigned short *)m_28)[4]);
    ++m_24;
}

// FUNCTION: GAME 0x006371b0
void VMCore::FUN_006371b0()
{
    float *destination = (float *)GetSymbolValuePtr(((unsigned short *)m_28)[2]);
    float *left = (float *)GetSymbolValuePtr(((unsigned short *)m_28)[3]);
    *destination = *left - *(float *)GetSymbolValuePtr(((unsigned short *)m_28)[4]);
    ++m_24;
}

// FUNCTION: GAME 0x006373e0
void VMCore::FUN_006373e0()
{
    float *destination = (float *)GetSymbolValuePtr(((unsigned short *)m_28)[2]);
    float *left = (float *)GetSymbolValuePtr(((unsigned short *)m_28)[3]);
    *destination = *left * *(float *)GetSymbolValuePtr(((unsigned short *)m_28)[4]);
    ++m_24;
}

// FUNCTION: GAME 0x00637610
void VMCore::FUN_00637610()
{
    float *destination = (float *)GetSymbolValuePtr(((unsigned short *)m_28)[2]);
    float *left = (float *)GetSymbolValuePtr(((unsigned short *)m_28)[3]);
    *destination = *left / *(float *)GetSymbolValuePtr(((unsigned short *)m_28)[4]);
    ++m_24;
}

// FUNCTION: GAME 0x00637840
void VMCore::FUN_00637840()
{
    int *destination = GetSymbolValuePtr(((unsigned short *)m_28)[2]);
    int *left = GetSymbolValuePtr(((unsigned short *)m_28)[3]);
    *destination = *left <= *GetSymbolValuePtr(((unsigned short *)m_28)[4]);
    ++m_24;
}

// FUNCTION: GAME 0x00637a40
void VMCore::FUN_00637a40()
{
    int *destination = GetSymbolValuePtr(((unsigned short *)m_28)[2]);
    int *left = GetSymbolValuePtr(((unsigned short *)m_28)[3]);
    *destination = *left < *GetSymbolValuePtr(((unsigned short *)m_28)[4]);
    ++m_24;
}

// FUNCTION: GAME 0x00637c40
void VMCore::FUN_00637c40()
{
    int *destination = GetSymbolValuePtr(((unsigned short *)m_28)[2]);
    int *left = GetSymbolValuePtr(((unsigned short *)m_28)[3]);
    *destination = *left >= *GetSymbolValuePtr(((unsigned short *)m_28)[4]);
    ++m_24;
}

// FUNCTION: GAME 0x00637e40
void VMCore::FUN_00637e40()
{
    int *destination = GetSymbolValuePtr(((unsigned short *)m_28)[2]);
    int *left = GetSymbolValuePtr(((unsigned short *)m_28)[3]);
    *destination = *left > *GetSymbolValuePtr(((unsigned short *)m_28)[4]);
    ++m_24;
}

// FUNCTION: GAME 0x00638040
void VMCore::FUN_00638040()
{
    int *destination = GetSymbolValuePtr(((unsigned short *)m_28)[2]);
    int *left = GetSymbolValuePtr(((unsigned short *)m_28)[3]);
    *destination = *left != *GetSymbolValuePtr(((unsigned short *)m_28)[4]);
    ++m_24;
}

// FUNCTION: GAME 0x00638240
void VMCore::FUN_00638240()
{
    int *destination = GetSymbolValuePtr(((unsigned short *)m_28)[2]);
    int *left = GetSymbolValuePtr(((unsigned short *)m_28)[3]);
    *destination = *left == *GetSymbolValuePtr(((unsigned short *)m_28)[4]);
    ++m_24;
}

// FUNCTION: GAME 0x00638440
void VMCore::FUN_00638440()
{
    float *destination = (float *)GetSymbolValuePtr(((unsigned short *)m_28)[2]);
    float *left = (float *)GetSymbolValuePtr(((unsigned short *)m_28)[3]);
    *destination = (float)(int)(*left <= *(float *)GetSymbolValuePtr(((unsigned short *)m_28)[4]));
    ++m_24;
}

// FUNCTION: GAME 0x00638650
void VMCore::FUN_00638650()
{
    float *destination = (float *)GetSymbolValuePtr(((unsigned short *)m_28)[2]);
    float *left = (float *)GetSymbolValuePtr(((unsigned short *)m_28)[3]);
    *destination = (float)(int)(*left < *(float *)GetSymbolValuePtr(((unsigned short *)m_28)[4]));
    ++m_24;
}

// FUNCTION: GAME 0x00638860
void VMCore::FUN_00638860()
{
    float *destination = (float *)GetSymbolValuePtr(((unsigned short *)m_28)[2]);
    float *left = (float *)GetSymbolValuePtr(((unsigned short *)m_28)[3]);
    *destination = (float)(int)(*left >= *(float *)GetSymbolValuePtr(((unsigned short *)m_28)[4]));
    ++m_24;
}

// FUNCTION: GAME 0x00638a70
void VMCore::FUN_00638a70()
{
    float *destination = (float *)GetSymbolValuePtr(((unsigned short *)m_28)[2]);
    float *left = (float *)GetSymbolValuePtr(((unsigned short *)m_28)[3]);
    *destination = (float)(int)(*left > *(float *)GetSymbolValuePtr(((unsigned short *)m_28)[4]));
    ++m_24;
}

// FUNCTION: GAME 0x00638c80
void VMCore::FUN_00638c80()
{
    float *destination = (float *)GetSymbolValuePtr(((unsigned short *)m_28)[2]);
    float *left = (float *)GetSymbolValuePtr(((unsigned short *)m_28)[3]);
    *destination = (float)(int)(*left != *(float *)GetSymbolValuePtr(((unsigned short *)m_28)[4]));
    ++m_24;
}

// FUNCTION: GAME 0x00638e90
void VMCore::FUN_00638e90()
{
    float *destination = (float *)GetSymbolValuePtr(((unsigned short *)m_28)[2]);
    float *left = (float *)GetSymbolValuePtr(((unsigned short *)m_28)[3]);
    *destination = (float)(int)(*left == *(float *)GetSymbolValuePtr(((unsigned short *)m_28)[4]));
    ++m_24;
}

// TEMPLATE: GAME 0x006390a0 FOLDED
// ?FUN_006390a0@VMCore@@UAE_NXZ
bool VMCore::FUN_006390a0()
{
    return false;
}

bool VMCore::FUN_006390a0_1()
{
    return false;
}

// FUNCTION: GAME 0x006390b0
VMCore::VMCore(VMUnk0063a490 *code, VMUnk0063a140 *memory)
    : m_04(code), m_08(memory), m_24(0), m_28(0), m_2c(0), m_3c(1), m_40(0), m_44(0)
{
}

// FUNCTION: GAME 0x00639170
VMCore::~VMCore()
{
    if (--g_unk0x006c1940 == 0 && g_unk0x006c1944)
        operator delete(g_unk0x006c1944);
}

// FUNCTION: GAME 0x00639230
bool VMCore::FUN_00639230()
{
    bool result = true;
    if (g_unk0x006c1940 == 0 && !FUN_006390a0()) {
        SBAssert(0, "P:\\Robin Hood\\VirtualMachine\\VMCore.cpp", 0x3bb,
            // STRING: GAME 0x006be130
            "VMCore::VMCore: InitializeStaticExtensions() unsuccessful.\n");
        result = false;
    }
    ++g_unk0x006c1940;
    return result;
}

// FUNCTION: GAME 0x00639280
bool VMCore::FUN_00639280(void *arg)
{
    m_40 = m_04->FUN_0063a490(arg);
    if (m_40 == 0)
        return false;
    m_1c.FUN_0063a140(m_40->m_24, true);
    m_3c = 2;
    return true;
}

// FUNCTION: GAME 0x006392c0
bool VMCore::FUN_006392c0()
{
    m_40 = 0;
    m_1c.FUN_0063a140(0, true);
    m_3c = 1;
    return true;
}

// FUNCTION: GAME 0x006392e0
bool VMCore::FUN_006392e0(void *arg, int size)
{
    return m_0c.FUN_0063a370(arg, size);
}

// FUNCTION: GAME 0x00639300
bool VMCore::FUN_00639300(void *arg)
{
    m_44 = (int *)m_04->FUN_0063a510(m_40, arg);
    m_0c.FUN_0063a250(-1, m_44[12]);
    m_24 = m_44[5];
    FUN_00639370();
    return true;
}

// FUNCTION: GAME 0x00639340
int VMCore::FUN_00639340(void *arg)
{
    return m_04->FUN_0063a510(m_40, arg) != 0;
}

// FUNCTION: GAME 0x00639360
void VMCore::FUN_00639360(int &value)
{
    value = m_2c;
}

// FUNCTION: GAME 0x00639370
void VMCore::FUN_00639370()
{
    for (;;) {
        int index = m_24;
        VMQuad *quads = m_40->m_50;
        m_28 = (int *)(quads + index);
        switch (*(unsigned char *)m_28) {
        case 0: Empty(); break;
        case 1: FUN_00634c20(); break;
        case 2: FUN_00634c30(); break;
        case 3: FUN_00634d30(); break;
        case 4: EndFunction(); break;
        case 5: FUN_00634db0(); break;
        case 6:
            FUN_00634dd0();
            if (m_24 == -1)
                return;
            break;
        case 7:
            FUN_00634de0();
            if (m_24 == -1)
                return;
            break;
        case 8: FUN_00634eb0(); break;
        case 9: FUN_00634fa0(); break;
        case 10: FUN_00635090(); break;
        case 11: FUN_00635150(); break;
        case 12: FUN_00635210(); break;
        case 13: FUN_00635240(); break;
        case 14: FUN_00635320(); break;
        case 15: FUN_00635330(); break;
        case 16: FUN_006353f0(); break;
        case 17: FUN_006354b0(); break;
        case 18: FUN_00635630(); break;
        case 19: FUN_006357b0(); break;
        case 20: FUN_006358a0(); break;
        case 21: FUN_00635990(); break;
        case 22: FUN_00635b20(); break;
        case 23: FUN_00635cb0(); break;
        case 24: FUN_00635e50(); break;
        case 25: FUN_00635fd0(); break;
        case 26: FUN_00636210(); break;
        case 27: FUN_00636450(); break;
        case 28: FUN_00636680(); break;
        case 29: FUN_006368c0(); break;
        case 30: FUN_00636b00(); break;
        case 31: FUN_00636d40(); break;
        case 32: FUN_00636f80(); break;
        case 33: FUN_006371b0(); break;
        case 34: FUN_006373e0(); break;
        case 35: FUN_00637610(); break;
        case 36: FUN_00637840(); break;
        case 37: FUN_00637a40(); break;
        case 38: FUN_00637c40(); break;
        case 39: FUN_00637e40(); break;
        case 40: FUN_00638040(); break;
        case 41: FUN_00638240(); break;
        case 42: FUN_00638440(); break;
        case 43: FUN_00638650(); break;
        case 44: FUN_00638860(); break;
        case 45: FUN_00638a70(); break;
        case 46: FUN_00638c80(); break;
        case 47: FUN_00638e90(); break;
        default:
            SBAssert(0, "P:\\Robin Hood\\VirtualMachine\\VMCore.cpp", 0x4f1,
                // STRING: GAME 0x006be16c
                "VMCore::Run: Unexpected quad.\n");
            break;
        }
    }
}

// SYNTHETIC: GAME 0x006396c0
// VMUnk0063a250::~VMUnk0063a250

// SYNTHETIC: GAME 0x00639740
// VMUnk0063a140::~VMUnk0063a140

// SYNTHETIC: GAME 0x00639bc0
// VMUnk0063a140::VMUnk0063a140

void EmitVMCoreSerializer(VMCore *core, const std::string &name, void (__cdecl *serializer)(SBFile &, void *&))
{
    core->RegisterSerializerForType(name, serializer);
}

void EmitVMCore(VMCore *core)
{
    core->Empty();
    core->FUN_00634c20();
    core->FUN_00634c30();
    core->FUN_00634d30();
    core->EndFunction();
    core->FUN_00634db0();
    core->FUN_00634dd0();
    core->FUN_00634de0();
    core->FUN_00634eb0();
    core->FUN_00634fa0();
    core->FUN_00635090();
    core->FUN_00635150();
    core->FUN_00635210();
    core->FUN_00635240();
    core->FUN_00635320();
    core->FUN_00635330();
    core->FUN_006353f0();
    core->FUN_006354b0();
    core->FUN_00635630();
    core->FUN_006357b0();
    core->FUN_006358a0();
    core->FUN_00635990();
    core->FUN_00635b20();
    core->FUN_00635cb0();
    core->FUN_00635e50();
    core->FUN_00635fd0();
    core->FUN_00636210();
    core->FUN_00636450();
    core->FUN_00636680();
    core->FUN_006368c0();
    core->FUN_00636b00();
    core->FUN_00636d40();
    core->FUN_00636f80();
    core->FUN_006371b0();
    core->FUN_006373e0();
    core->FUN_00637610();
    core->FUN_00637840();
    core->FUN_00637a40();
    core->FUN_00637c40();
    core->FUN_00637e40();
    core->FUN_00638040();
    core->FUN_00638240();
    core->FUN_00638440();
    core->FUN_00638650();
    core->FUN_00638860();
    core->FUN_00638a70();
    core->FUN_00638c80();
    core->FUN_00638e90();
    core->VMCore::FUN_006390a0();
    core->~VMCore();
    core->FUN_00639230();
    core->FUN_00639280(0);
    core->FUN_006392c0();
    core->FUN_006392e0(0, 0);
    core->FUN_00639300(0);
    core->FUN_00639340(0);
    core->FUN_00639360(core->m_2c);
}

void EmitVMUnk00634bb0(VMUnk00634bb0 *value)
{
    value->FUN_00634bb0();
}

// FUNCTION: GAME 0x0063a250
bool VMUnk0063a250::FUN_0063a250(int address, int size)
{
    VMUnk0063a400 *record = new VMUnk0063a400(m_area);
    m_area = new VMUnk0063a140;
    record->m_08 = address;
    record->m_0c.FUN_0063a140(size, true);
    m_records.push_back(record);
    return true;
}

// FUNCTION: GAME 0x0063a320
int VMUnk0063a250::FUN_0063a320()
{
    VMUnk0063a400 *value = m_records.back();
    int result = value->m_08;
    if (value) {
        value->~VMUnk0063a400();
        operator delete(value);
    }
    m_records.pop_back();
    return result;
}

// FUNCTION: GAME 0x0063a370
bool VMUnk0063a250::FUN_0063a370(void *source, int size)
{
    int previous = ((RHUnk0063a1d0 *)m_area)->FUN_0063a1d0();
    m_area->FUN_0063a140(previous + size, true);
    m_area->FUN_0063a1f0(previous, (unsigned char *)source, size);
    return true;
}

// FUNCTION: GAME 0x0063a3b0
int *VMUnk0063a250::FUN_0063a3b0(int offset)
{
    VMUnk0063a400 *object = m_records.back();
    return object->m_00->FUN_0063a1e0(offset);
}

void EmitVMUnk0063a3b0(VMUnk0063a250 *stack)
{
    stack->FUN_0063a3b0(0);
}

// SYNTHETIC: GAME 0x0063a400
// VMUnk0063a400::~VMUnk0063a400

void EmitVMUnk0063a400(VMUnk0063a400 *record)
{
    record->~VMUnk0063a400();
}
