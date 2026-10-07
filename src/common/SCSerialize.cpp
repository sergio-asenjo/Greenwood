#include "SCSerialize.h"
#include <new>
#include <string.h>

// STUB: GAME 0x0063b5c0
bool SCSerialize::Destroy()
{
    while (m_0c != 0) {
        SCSerializeUnkObject *object = m_08->m_previous->m_object;
        if (object != 0)
            object->FUN_00(1);
        SCSerializeUnkNode *node = m_08->m_previous;
        node->m_previous->m_next = node->m_next;
        node->m_next->m_previous = node->m_previous;
        operator delete(node);
        --m_0c;
    }
    return true;
}

// FUNCTION: GAME 0x0063b610
bool SCSerialize::OpenSCB(const char *name, bool reading)
{
    char path[128];
    strcpy(path, name);
    strcat(path,
        // STRING: GAME 0x006be3d4
        ".scb");
    if (reading)
        m_00 = SCSerializeUnk00643c43(path,
            // STRING: GAME 0x006b9db4
            "rb");
    else
        m_00 = SCSerializeUnk00643c43(path,
            // STRING: GAME 0x006be3d0
            "w+b");
    if (m_00 == 0) {
        if (reading)
            SCSerializeUnk00642a2f(
                // STRING: GAME 0x006be398
                "SCSerialize::OpenSCB: Could not open input file(.scb)\n");
        else
            SCSerializeUnk00642a2f(
                // STRING: GAME 0x006be35c
                "SCSerialize::OpenSCB: Could not create output file(.scb)\n");
        return false;
    }
    return true;
}

// FUNCTION: GAME 0x0063b6f0
bool SCSerialize::CloseSCB()
{
    if (SCSerializeUnk00643c56(m_00) != 0)
        return false;
    return true;
}

// FUNCTION: GAME 0x0063b710
int SCSerialize::ReadSCB()
{
    return Serialize(false);
}

void EmitSCSerialize(SCSerialize *serializer)
{
    serializer->Destroy();
    serializer->OpenSCB(0, false);
    serializer->CloseSCB();
    serializer->ReadSCB();
}
