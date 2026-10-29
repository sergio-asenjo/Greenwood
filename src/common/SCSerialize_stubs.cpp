#include "SBNullstr.h"
#include "SCSerialize.h"

// TEMPLATE: GAME 0x0057c9c0 FOLDED
// ??Eiterator@?$list@PAVSCFunctionArg@@V?$allocator@PAVSCFunctionArg@@@std@@@std@@QAE?AV012@H@Z

int SCSerializeUnk00643c56(FILE *)
{
    return 0;
}

FILE *SCSerializeUnk00643c43(const char *, const char *)
{
    return 0;
}

int SCSerializeUnk00642a2f(const char *, ...) throw()
{
    return 0;
}

SCSerializeUnkList::~SCSerializeUnkList() {}
SCSerializeUnkList00424340::~SCSerializeUnkList00424340() {}
SCSerializeUnkArray::~SCSerializeUnkArray() {}

SCSerializeUnkObject::~SCSerializeUnkObject() {}

// FUNCTION: GAME 0x0063af90
SCSerializeUnk0063af90::~SCSerializeUnk0063af90()
{
}

void SCSerializeUnkList::PushBack(void *value)
{
    SCSerializeUnkNode *head = (SCSerializeUnkNode *)m_head;
    SCSerializeUnkNode *node = (SCSerializeUnkNode *)((RHUnk0046eb30 *)this)->Unk0059f720(
        (RHScriptNode *)head, (RHScriptNode *)head->m_previous);
    head->m_previous = node;
    node->m_previous->m_next = node;
    if (&node->m_object)
        node->m_object = (SCSerializeUnkObject *)value;
    ++m_count;
}
SCSerializeRecordValue::~SCSerializeRecordValue() {}

// FUNCTION: GAME 0x0063b8a0
SCSerializeNamedType::~SCSerializeNamedType() {}
