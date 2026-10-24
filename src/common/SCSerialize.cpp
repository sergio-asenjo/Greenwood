#include "SBNullstr.h"
#include "SCSerialize.h"
#include "SBFile.h"
#include <new>
#include <string.h>

typedef int SCSerializeSizeAssert[(sizeof(SCSerialize) == 0x10) ? 1 : -1];
typedef int SCSerializeObjectSizeAssert[(sizeof(SCSerializeUnkObject) == 0x6c) ? 1 : -1];


void EmitSCSerialize(SCSerialize *serializer)
{
    serializer->Destroy();
    serializer->OpenSCB(0, false);
    serializer->CloseSCB();
    serializer->ReadSCB();
}

// FUNCTION: GAME 0x00639b40
SCSerialize::SCSerialize()
{
    std::allocator<char> allocator;
    m_00 = 0;
    m_pad04[0] = *(const char *)&allocator;
    SCSerializeUnkNode *head = (SCSerializeUnkNode *)operator new(sizeof(SCSerializeUnkNode));
    head->m_next = head;
    head->m_previous = head;
    m_08 = head;
    m_0c = 0;
}

// FUNCTION: GAME 0x00639b70
SCSerialize::~SCSerialize()
{
    SCSerializeUnkNode *head = m_08;
    SCSerializeUnkNode *node = head->m_next;
    while (node != head) {
        SCSerializeUnkNode *removed = node;
        node = node->m_next;
        removed->m_previous->m_next = removed->m_next;
        removed->m_next->m_previous = removed->m_previous;
        operator delete(removed);
        --m_0c;
    }
    operator delete(m_08);
    m_08 = 0;
    m_0c = 0;
}

// SYNTHETIC: GAME 0x0063a920
// ??_GSCSerializeUnkObject@@UAEPAXI@Z

inline SCSerializeRecordList::~SCSerializeRecordList()
{
    SCSerializeRecordNode *stop = head;
    SCSerializeRecordNode *current = stop->next;
    while (current != stop)
    {
        SCSerializeRecordNode *removed = current;
        current = current->next;
        Erase(SCSerializeRecordIterator(removed));
    }
    std::allocator<SCSerializeRecordNode> allocator;
    allocator.deallocate(head, 1);
    head = 0;
    count = 0;
}

// SYNTHETIC: GAME 0x0063af70
// SCSerializeUnk0063af90::`scalar deleting destructor'

// FUNCTION: GAME 0x0063af90
SCSerializeUnk0063af90::~SCSerializeUnk0063af90()
{
}

// FUNCTION: GAME 0x0063b2d0
int SCSerialize::Serialize(bool writing)
{
    int result;
    if (writing) {
        float version = 1.5f;
        int count = m_0c;
        result = SBFileUnk00643cd3(
            // STRING: GAME 0x006be350
            "SBSCRIPT", 8, 1, m_00);
        result += SBFileUnk00643cd3(&version, 1, 4, m_00);
        result += SBFileUnk00643cd3(&count, 1, 4, m_00);
        for (SCSerializeUnkNode *node = m_08->m_next; node != m_08; node = node->m_next)
            node->m_object->FUN_0063a940(m_00, writing);
    } else {
        char tag[9];
        float version;
        int count;
        result = SBFileUnk00643e0c(tag, 8, 1, m_00);
        result += SBFileUnk00643e0c(&version, 1, 4, m_00);
        result += SBFileUnk00643e0c(&count, 1, 4, m_00);
        tag[8] = 0;
        if (strcmp(tag, "SBSCRIPT") != 0) {
            SBAssert(1,
                // STRING: GAME 0x006be2bc
                "P:\\Robin Hood\\VirtualMachine\\SCSerialize.cpp", 0x129,
                // STRING: GAME 0x006be320
                "Trying to load a corrupted file script file\n");
            return result;
        }
        if (version != 1.5f) {
            SBAssert(1, "P:\\Robin Hood\\VirtualMachine\\SCSerialize.cpp", 0x12f,
                // STRING: GAME 0x006be2ec
                "File version of .scb not good expecting %f got %f.\n", 1.5, (double)version);
            return result;
        }
        for (int index = 0; index < count; ++index) {
            SCSerializeUnkObject *object = new SCSerializeUnkObject;
            result += object->FUN_0063a940(m_00, false);
            SCSerializeUnkNode *head = m_08;
            SCSerializeUnkNode *previous = head->m_previous;
            SCSerializeUnkNode *node = (SCSerializeUnkNode *)operator new(0xc);
            node->m_next = head ? head : node;
            node->m_previous = previous ? previous : node;
            head->m_previous = node;
            node->m_previous->m_next = node;
            SCSerializeUnkObject **destination = &node->m_object;
            if (destination)
                *destination = object;
            ++m_0c;
        }
    }
    return result;
}

// Parked: loop-count register copy and explicit test differ.
// STUB: GAME 0x0063b5c0
bool SCSerialize::Destroy()
{
    while (m_0c != 0) {
        SCSerializeUnkObject *object = m_08->m_previous->m_object;
        delete object;
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

// FUNCTION: GAME 0x0063b780
SCSerializeUnk0063b780::~SCSerializeUnk0063b780()
{
}

void EmitSCSerializeRecords(SCSerializeUnk0063af90 *records, SCSerializeUnk0063b780 *record)
{
    records->SCSerializeUnk0063af90::~SCSerializeUnk0063af90();
    record->~SCSerializeUnk0063b780();
}
