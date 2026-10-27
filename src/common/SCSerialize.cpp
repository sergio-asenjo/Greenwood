#include "SBNullstr.h"
#include "SCSerialize.h"
#include "SBFile.h"
#include <new>
#include <string.h>

typedef int SCSerializeSizeAssert[(sizeof(SCSerialize) == 0x10) ? 1 : -1];
typedef int SCSerializeObjectSizeAssert[(sizeof(SCSerializeUnkObject) == 0x6c) ? 1 : -1];
typedef int SCSerializeRecordSizeAssert[(sizeof(SCSerializeRecordValue) == 0x38) ? 1 : -1];
typedef int SCSerializeFunctionSizeAssert[(sizeof(SCSerializeUnk0063af90) == 0x44) ? 1 : -1];


void EmitSCSerialize(SCSerialize *serializer)
{
    serializer->Destroy();
    serializer->OpenSCB(0, false);
    serializer->CloseSCB();
    serializer->ReadSCB();
}

void EmitSCSerializeRecordValue(SCSerializeRecordValue *record)
{
    record->FUN_0063a5c0(0, false);
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

// STUB: GAME 0x0063a5c0
int SCSerializeRecordValue::FUN_0063a5c0(FILE *file, bool writing)
{
    int result;
    int length;
    char text[256];
    if (writing) {
        result = SCType::Serialize(file, writing);
        length = strlen(m_24.c_str());
        result += SBFileUnk00643cd3(&length, 1, 4, file);
        result += SBFileUnk00643cd3(m_24.c_str(), length, 1, file);
        result += SBFileUnk00643cd3(&m_34, 1, 4, file);
    } else {
        result = SCType::Serialize(file, false);
        result += SBFileUnk00643e0c(&length, 1, 4, file);
        result += SBFileUnk00643e0c(text, length, 1, file);
        result += SBFileUnk00643e0c(&m_34, 1, 4, file);
        text[length] = 0;
        m_24.append(text);
    }
    return result;
}

// SYNTHETIC: GAME 0x0063a920
// ??_GSCSerializeUnkObject@@UAEPAXI@Z

// STUB: GAME 0x0063a940
int SCSerializeUnkObject::FUN_0063a940(FILE *file, bool writing)
{
    int result;
    int length;
    int count;
    char text[256];
    if (writing) {
        length = strlen(m_04.c_str());
        result = SBFileUnk00643cd3(&length, 1, 4, file);
        result += SBFileUnk00643cd3(m_04.c_str(), length, 1, file);
        length = strlen(m_14.c_str());
        result += SBFileUnk00643cd3(&length, 1, 4, file);
        result += SBFileUnk00643cd3(m_14.c_str(), length, 1, file);
        count = m_28.m_count;
        result += SBFileUnk00643cd3(&count, 1, 4, file);
        result += SBFileUnk00643cd3(&m_24, 1, 4, file);
        SCSerializeUnkNode *head = (SCSerializeUnkNode *)m_28.m_head;
        for (SCSerializeUnkNode *node = head->m_next; node != (SCSerializeUnkNode *)m_28.m_head; node = node->m_next)
            ((SCSerializeRecordValue *)node->m_object)->FUN_0063a5c0(file, writing);
        count = m_34.m_count;
        result += SBFileUnk00643cd3(&count, 1, 4, file);
        head = (SCSerializeUnkNode *)m_34.m_head;
        for (node = head->m_next; node != (SCSerializeUnkNode *)m_34.m_head; node = node->m_next)
            result += ((SCSerializeUnk0063af90 *)node->m_object)->FUN_0063b070(file, writing);
        count = m_40.m_count;
        result += SBFileUnk00643cd3(&count, 1, 4, file);
        head = (SCSerializeUnkNode *)m_40.m_head;
        for (node = head->m_next; node != (SCSerializeUnkNode *)m_40.m_head; node = node->m_next)
            ((SCQuad *)&node->m_object)->Serialize(file, writing, true);
    } else {
        result = SBFileUnk00643e0c(&length, 1, 4, file);
        result += SBFileUnk00643e0c(text, length, 1, file);
        text[length] = 0;
        ((std::string *)&m_04)->append(text);
        result += SBFileUnk00643e0c(&length, 1, 4, file);
        result += SBFileUnk00643e0c(text, length, 1, file);
        text[length] = 0;
        ((std::string *)&m_14)->append(text);
        result += SBFileUnk00643e0c(&count, 1, 4, file);
        result += SBFileUnk00643e0c(&m_24, 1, 4, file);
        for (int index = 0; index < count; ++index) {
            SCSerializeRecordValue *record = new SCSerializeRecordValue;
            record->FUN_0063a5c0(file, false);
            m_28.PushBack(record);
        }
        result += SBFileUnk00643e0c(&count, 1, 4, file);
        for (index = 0; index < count; ++index) {
            SCSerializeUnk0063af90 *record = new SCSerializeUnk0063af90;
            record->FUN_0063b070(file, false);
            m_34.PushBack(record);
        }
        result += SBFileUnk00643e0c(&count, 1, 4, file);
        std::vector<VMQuad> &quads = *(std::vector<VMQuad> *)&m_4c;
        VMQuad value;
        if (quads.size() < (unsigned)count) {
            void (std::vector<VMQuad>::*insert)(VMQuad *, unsigned, const VMQuad &) = &std::vector<VMQuad>::insert;
            (quads.*insert)(quads.end(), count - quads.size(), value);
        } else if ((unsigned)count < quads.size()) {
            VMQuad *(std::vector<VMQuad>::*erase)(VMQuad *, VMQuad *) = &std::vector<VMQuad>::erase;
            (quads.*erase)(quads.begin() + count, quads.end());
        }
        for (index = 0; index < count; ++index) {
            result += SBFileUnk00643e0c(&quads[index].m_00, 1, 1, file);
            result += SBFileUnk00643e0c(&quads[index].m_04, 8, 1, file);
        }
    }
    return result;
}

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

// STUB: GAME 0x0063b070
int SCSerializeUnk0063af90::FUN_0063b070(FILE *file, bool writing)
{
    int result;
    int length;
    char text[256];
    if (writing) {
        length = strlen(m_04.c_str());
        result = SBFileUnk00643cd3(&length, 1, 4, file);
        result += SBFileUnk00643cd3(m_04.c_str(), length, 1, file);
        result += SBFileUnk00643cd3(&m_14, 1, 4, file);
        result += SBFileUnk00643cd3(&m_18, 1, 4, file);
        result += SBFileUnk00643cd3(&m_1c, 1, 4, file);
        result += SBFileUnk00643cd3(&m_20, 1, 4, file);
        result += SBFileUnk00643cd3(&m_30, 1, 4, file);
        result += SBFileUnk00643cd3(&m_34, 1, 4, file);
    } else {
        result = SBFileUnk00643e0c(&length, 1, 4, file);
        result += SBFileUnk00643e0c(text, length, 1, file);
        text[length] = 0;
        m_04.append(text);
        result += SBFileUnk00643e0c(&m_14, 1, 4, file);
        result += SBFileUnk00643e0c(&m_18, 1, 4, file);
        result += SBFileUnk00643e0c(&m_1c, 1, 4, file);
        result += SBFileUnk00643e0c(&m_20, 1, 4, file);
        result += SBFileUnk00643e0c(&m_30, 1, 4, file);
        result += SBFileUnk00643e0c(&m_34, 1, 4, file);
    }
    return result;
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
    records->FUN_0063b070(0, false);
    records->SCSerializeUnk0063af90::~SCSerializeUnk0063af90();
    record->~SCSerializeUnk0063b780();
}
