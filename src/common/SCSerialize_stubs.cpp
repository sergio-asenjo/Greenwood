#include "SBNullstr.h"
#include "SCSerialize.h"

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

int SCSerializeUnkObject::FUN_0063a940(FILE *, bool)
{
    return 0;
}
SCSerializeRecordIterator SCSerializeRecordList::Erase(SCSerializeRecordIterator position)
{
    SCSerializeRecordNode *node = position.node;
    SCSerializeRecordNode *next = node->next;
    node->previous->next = next;
    node->next->previous = node->previous;
    node->value.~SCSerializeRecordValue();
    operator delete(node);
    --count;
    return SCSerializeRecordIterator(next);
}

SCSerializeRecordValue::~SCSerializeRecordValue() {}
