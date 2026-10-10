#include "SBNullstr.h"
#include "VMCore.h"
#include "SCQuad.h"
#include "SB.h"
#include <new>

// GLOBAL: GAME 0x006c1940
int g_unk0x006c1940 = 0;

typedef int (__cdecl *VMUnk00635210Handler)(void *);

// GLOBAL: GAME 0x006c1944
VMUnk00635210Handler *g_unk0x006c1944 = 0;

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

class VMUnk00634d30Object
{
public:
    char m_pad0[4];
    int m_04;
    char m_pad08[4];
    VMUnk0063a140 m_0c;
    VMUnk0063a140 m_14;
};

class VMUnk00634d30Node
{
public:
    char m_pad0[8];
    VMUnk00634d30Object *m_08;
};

class VMUnk00634d30Stack
{
public:
    char m_pad0[4];
    VMUnk00634d30Node *m_04;
};

inline int *VMCore::GetSymbolValuePtr(unsigned short &value)
{
    unsigned short flags = value & 0xc000;
    if (flags == 0)
        return m_08->FUN_0063a1e0(value & 0x3fff);
    if (flags == 0x4000)
        return m_1c.FUN_0063a1e0(value & 0x3fff);
    if (flags == 0x8000) {
        VMUnk00634d30Object *object = (*(VMUnk00634d30Stack **)(m_0c.m_pad0 + 8))->m_04->m_08;
        return object->m_0c.FUN_0063a1e0(value & 0x3fff);
    }
    if (flags == 0xc000) {
        VMUnk00634d30Object *object = (*(VMUnk00634d30Stack **)(m_0c.m_pad0 + 8))->m_04->m_08;
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
    (*(VMUnk00634d30Stack **)(m_0c.m_pad0 + 8))->m_04->m_08->m_0c.FUN_0063a140(
        ((unsigned short *)m_28)[2], false);
    (*(VMUnk00634d30Stack **)(m_0c.m_pad0 + 8))->m_04->m_08->m_14.FUN_0063a140(
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
    if (*(int *)(m_0c.m_pad0 + 12) != 1) {
        VMUnk00634d30Node *node = (*(VMUnk00634d30Stack **)(m_0c.m_pad0 + 8))->m_04;
        (*(VMUnk00634d30Node **)(node->m_pad0 + 4))->m_08->m_04 = *value;
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
    *value = (*(VMUnk00634d30Stack **)(m_0c.m_pad0 + 8))->m_04->m_08->m_04;
    ++m_24;
}

// Parked: native-stack store folds the address into SIB and interleaves increments.
// STUB: GAME 0x00635150
void VMCore::FUN_00635150()
{
    int *value = GetSymbolValuePtr(((unsigned short *)m_28)[2]);
    *(int *)(*(char **)m_pad30 + *(int *)(m_pad30 + 4)) = *value;
    *(int *)(m_pad30 + 4) += 4;
    ++m_24;
}

// FUNCTION: GAME 0x00635210
void VMCore::FUN_00635210()
{
    int index = m_24;
    int result = g_unk0x006c1944[m_28[1]](m_pad30);
    m_24 = index + 1;
    *(int *)(m_pad30 + 8) = result;
}

// FUNCTION: GAME 0x00635240
void VMCore::FUN_00635240()
{
    *GetSymbolValuePtr(((unsigned short *)m_28)[2]) = *(int *)(m_pad30 + 8);
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

// FUNCTION: GAME 0x006390a0
bool VMCore::FUN_006390a0()
{
    return false;
}

bool VMCore::FUN_006390a0_1()
{
    return false;
}

// FUNCTION: GAME 0x00639170
VMCore::~VMCore()
{
    if (--g_unk0x006c1940 == 0 && g_unk0x006c1944)
        operator delete(g_unk0x006c1944);
    if (*(void **)m_pad30)
        operator delete(*(void **)m_pad30);
    if (*(void **)m_1c.m_pad0)
        operator delete(*(void **)m_1c.m_pad0);
    VMUnk0063a140 *area = *(VMUnk0063a140 **)m_0c.m_pad0;
    if (area) {
        if (*(void **)area->m_pad0)
            operator delete(*(void **)area->m_pad0);
        operator delete(area);
    }
    struct Node {
        Node *next;
        Node *previous;
        void *value;
    };
    Node *head = *(Node **)(m_0c.m_pad0 + 8);
    Node *node = head->next;
    while (node != head) {
        Node *erased = node;
        node = node->next;
        erased->previous->next = erased->next;
        erased->next->previous = erased->previous;
        operator delete(erased);
        --*(int *)(m_0c.m_pad0 + 12);
    }
    operator delete(*(Node **)(m_0c.m_pad0 + 8));
    *(Node **)(m_0c.m_pad0 + 8) = 0;
    *(int *)(m_0c.m_pad0 + 12) = 0;
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

struct VMUnk0063a320Node
{
    VMUnk0063a320Node *m_next;
    VMUnk0063a320Node *m_previous;
    VMUnk0063a400 *m_value;
};

// FUNCTION: GAME 0x0063a320
int VMUnk0063a250::FUN_0063a320()
{
    VMUnk0063a400 *value = (*(VMUnk0063a320Node **)(m_pad0 + 8))->m_previous->m_value;
    int result = value->m_08;
    if (value) {
        value->FUN_0063a400();
        operator delete(value);
    }
    VMUnk0063a320Node *node = (*(VMUnk0063a320Node **)(m_pad0 + 8))->m_previous;
    node->m_previous->m_next = node->m_next;
    node->m_next->m_previous = node->m_previous;
    operator delete(node);
    --*(int *)(m_pad0 + 12);
    return result;
}

// FUNCTION: GAME 0x0063a370
bool VMUnk0063a250::FUN_0063a370(void *source, int size)
{
    int previous = ((RHUnk0063a1d0 *)*(VMUnk0063a140 **)m_pad0)->FUN_0063a1d0();
    (*(VMUnk0063a140 **)m_pad0)->FUN_0063a140(previous + size, true);
    (*(VMUnk0063a140 **)m_pad0)->FUN_0063a1f0(previous, (unsigned char *)source, size);
    return true;
}

// FUNCTION: GAME 0x0063a3b0
int *VMUnk0063a250::FUN_0063a3b0(int offset)
{
    VMUnk00634d30Object *object = (*(VMUnk00634d30Stack **)(m_pad0 + 8))->m_04->m_08;
    return (*(VMUnk0063a140 **)object)->FUN_0063a1e0(offset);
}

void EmitVMUnk0063a3b0(VMUnk0063a250 *stack)
{
    stack->FUN_0063a3b0(0);
}

// FUNCTION: GAME 0x0063a400
void VMUnk0063a400::FUN_0063a400()
{
    VMUnk0063a140 *area = m_00;
    if (area) {
        void *buffer = *(void **)area->m_pad0;
        if (buffer)
            operator delete(buffer);
        operator delete(area);
    }
    if (m_14)
        operator delete(m_14);
    if (m_0c)
        operator delete(m_0c);
}

void EmitVMUnk0063a400(VMUnk0063a400 *record)
{
    record->FUN_0063a400();
}
