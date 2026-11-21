// Stub definitions for the external symbols RHOrder.cpp calls.
//
// These are NOT decompiled implementations; they only give the linker a local
// target so the calls in RHOrder::Serialize are direct `call rel32` (matching
// the original shape) instead of unresolved externals. They live in a separate
// translation unit so VC6 cannot inline them into the matched function.
//
// SBFile::Access / SBFile::GetError / SBAssert are defined once in
// RHSword_stubs.cpp; RHSerializeName once in RHElementObject_stubs.cpp;
// RHEngine::SerializeElementPointer once in RHMinimap_stubs.cpp; the g_pEngine
// global once in RHMenuDialogue_stubs.cpp; SBGeoPoint2D::Serialize once in
// RHGraphicConfig_stubs.cpp; RHUnk005df510::Serialize once in
// RHTitbits_stubs.cpp. This TU only defines the one new target.

#include "SBNullstr.h"
#include "RHOrder.h"
#include "RHSequenceManagerListOps.h"

struct RHOrderListNode
{
    RHOrderListNode *next;
    RHOrderListNode *previous;
    RHOrder *value;
};

// TEMPLATE: GAME 0x00424410 FOLDED
// ?insert@RHUnkList@@QAE?AVRHUnkIter@@V2@ABQAVRHOrder@@@Z
RHUnkIter RHUnkList::insert(RHUnkIter pos, RHOrder *const &value)
{
    RHOrderListNode *next = (RHOrderListNode *)pos.m_p;
    RHOrderListNode *previous = next->previous;
    RHOrderListNode *node = (RHOrderListNode *)operator new(sizeof(RHOrderListNode));
    node->next = next ? next : node;
    node->previous = previous ? previous : node;
    next->previous = node;
    node->previous->next = node;
    new (&node->value) RHOrder *(value);
    ++m_8;
    return RHUnkIter(node);
}

struct RHSequenceElementListNode
{
    RHSequenceElementListNode *next;
    RHSequenceElementListNode *previous;
    RHSequenceElement *value;
};

// TEMPLATE: GAME 0x00424410 FOLDED
// ?insert@RHSequenceElementCursor@@QAE?AVRHUnkIter@@V2@ABQAVRHSequenceElement@@@Z
RHUnkIter RHSequenceElementCursor::insert(RHUnkIter pos, RHSequenceElement *const &value)
{
    RHSequenceElementListNode *next = (RHSequenceElementListNode *)pos.m_p;
    RHSequenceElementListNode *previous = next->previous;
    RHSequenceElementListNode *node = (RHSequenceElementListNode *)operator new(sizeof(RHSequenceElementListNode));
    node->next = next ? next : node;
    node->previous = previous ? previous : node;
    next->previous = node;
    node->previous->next = node;
    new (&node->value) RHSequenceElement *(value);
    ++_Size;
    return RHUnkIter(node);
}
