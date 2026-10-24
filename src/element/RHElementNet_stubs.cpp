#include "SBNullstr.h"
#include "RHElementNet.h"

RHScriptIter RHNetListStorage::FUN_0044e8b0(RHScriptIter first, RHScriptIter last)
{
    RHScriptNode *node = first.node;
    while (node != last.node)
    {
        RHScriptNode *erased = node;
        node = node->next;
        erased->previous->next = erased->next;
        erased->next->previous = erased->previous;
        operator delete(erased);
        --m_08;
    }
    return RHScriptIter(node);
}

RHScriptIter RHNetListStorage::FUN_00424410(RHScriptIter position, void *const &value)
{
    RHScriptNode *next = position.node;
    RHScriptNode *previous = next->previous;
    RHScriptNode *node = (RHScriptNode *)operator new(sizeof(RHScriptNode));
    node->next = next ? next : node;
    node->previous = previous ? previous : node;
    next->previous = node;
    node->previous->next = node;
    new (&node->data) void *(value);
    ++m_08;
    return RHScriptIter(node);
}

void RHElementNet::FUN_004b1730() {}
