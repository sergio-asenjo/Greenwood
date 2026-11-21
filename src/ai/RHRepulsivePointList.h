#ifndef RHREPULSIVEPOINTLIST_H
#define RHREPULSIVEPOINTLIST_H

#include "RHUnk004b1520List.h"
#include <new>

class RHUnk00520ae0;

class RHRepulsivePointList : public RHUnk004b1520List
{
public:
    void Append(void *const &value)
    {
        FUN_00424410(end(), value);
        m_10 = true;
    }

    void AppendInline(RHUnk00520ae0 *point)
    {
        RHScriptNode *next = m_04;
        RHScriptNode *previous = next->prev;
        RHScriptNode *node = (RHScriptNode *)operator new(sizeof(RHScriptNode));
        node->next = next ? next : node;
        node->prev = previous ? previous : node;
        next->prev = node;
        node->prev->next = node;
        new (&node->data) void *(point);
        ++m_08;
        m_10 = true;
    }
};

#endif
