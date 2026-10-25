#ifndef RH_GAME_PAD_H
#define RH_GAME_PAD_H
#include "RHSectorActorList.h"

#include "Decomp.h"
#include "SBInput.h"
#ifndef SBGEO_VECTOR2D_VIEW
#include "SBGeoVector2D.h"
#endif
#include <list>
#include <iterator>

class RHMessenger;
class RHEngine;

// SIZE 0x50
struct SBInputJoystickState
{
    long m_axes[8]; // 0x00
    unsigned long m_pov[4]; // 0x20
    unsigned char m_buttons[0x20]; // 0x30
};

class RHElementActorPC;

struct RHGamePadListNode
{
    RHGamePadListNode *next;
    RHGamePadListNode *previous;
    RHElementActorPC *value;
};

struct RHScriptIter
{
    RHGamePadListNode *node;
};

class RHUnk0046eb30
{
public:
    RHScriptIter FUN_0046eb80();
};

struct RHUnk005c9010Iterator;
void FUN_005c9010(RHUnk005c9010Iterator &current, int distance, std::bidirectional_iterator_tag category);

struct RHGamePadSelection
{
    unsigned m_allocator;
    RHGamePadListNode *m_head;
    unsigned m_count;
    RHScriptIter m_current;
    bool m_dirty;
    int m_index;
    void Move(int wanted, int count)
    {
        int previous = m_index;
        if (wanted < previous)
        {
            if (wanted < (previous + 1) / 2)
            {
                m_current = ((RHUnk0046eb30 *)this)->FUN_0046eb80();
                std::bidirectional_iterator_tag category;
                FUN_005c9010((RHUnk005c9010Iterator &)m_current, wanted, category);
            }
            else
            {
                std::bidirectional_iterator_tag category;
                FUN_005c9010((RHUnk005c9010Iterator &)m_current, wanted - previous, category);
            }
        }
        else if (wanted < (previous + count) / 2)
        {
            std::bidirectional_iterator_tag category;
            FUN_005c9010((RHUnk005c9010Iterator &)m_current, wanted - previous, category);
        }
        else
        {
            m_current.node = m_head;
            std::bidirectional_iterator_tag category;
            FUN_005c9010((RHUnk005c9010Iterator &)m_current, wanted - count, category);
        }
        m_index = wanted;
    }
    __forceinline void GoTo(int index) { ((RHSectorActorList *)this)->Unk005c8e40(index); }
    unsigned GetCount() const { return m_count; }
    RHElementActorPC *GetCurrent() const { return m_current.node->value; }
    RHElementActorPC *Selected()
    {
        GoTo(0);
        return GetCurrent();
    }
    RHElementActorPC *At(int wanted)
    {
        int count = m_count;
        if (m_dirty)
        {
            if (wanted <= (count + 1) / 2)
            {
                m_current = ((RHUnk0046eb30 *)this)->FUN_0046eb80();
                std::bidirectional_iterator_tag category;
                FUN_005c9010((RHUnk005c9010Iterator &)m_current, wanted, category);
            }
            else
            {
                m_current.node = m_head;
                std::bidirectional_iterator_tag category;
                FUN_005c9010((RHUnk005c9010Iterator &)m_current, wanted - count, category);
            }
            m_dirty = false;
            m_index = wanted;
        }
        else if (wanted != m_index)
            Move(wanted, count);
        return m_current.node->value;
    }
};

struct RHGamePadEngine
{
    char m_0000[0x493c];
    RHElementActorPC **m_493c;
    RHElementActorPC **m_4940;
    char m_4944[0xb4];
    RHGamePadSelection m_selection;
    RHGamePadSelection &GetSelection() { return m_selection; }
    unsigned PCCount() const
    {
        RHElementActorPC **first = *(RHElementActorPC **const volatile *)&m_493c;
        if (!first)
            return 0;
        return m_4940 - first;
    }
};

class RHGamePadSwing : public std::list<SBGeoVector2D>
{
public:
    void Append(const SBGeoVector2D &point)
    {
        _Nodeptr node = _Head;
        _Acc::_Prev(node) = _Buynode(node, _Acc::_Prev(node));
        node = _Acc::_Prev(node);
        _Acc::_Next(_Acc::_Prev(node)) = node;
        void (*construct)(SBGeoVector2D *, const SBGeoVector2D &) = &std::_Construct;
        construct(&_Acc::_Value(node), point);
        ++_Size;
    }
};

// VTABLE: GAME 0x00679090
// SIZE 0x78
class RHGamePad
{
public:
    RHGamePad();
    virtual ~RHGamePad();
    void ProcessGamepadInput();
    unsigned char GetSelectedIndexPC();
    void ManageScrollAxis(SBInputJoystickState &state);
    void ManageMoveAxis(SBInputJoystickState &state);
    void ManageCharacterSelect(SBInputJoystickState &state);
    void ManageMouseAxis(SBInputJoystickState &state);
    void ManageActionSelect(SBInputJoystickState &state);
    bool CheckValidityOfPosition(SBGeoVector2D &move, bool fast);
    void RecognizeSwing();
    void ChooseOpponent(RHElementActorPC *pc, unsigned short direction, short step);
    void ManageQA(SBInputJoystickState &state);

    SBInputUnk005fb730 *m_input; // 0x04
    RHMessenger *m_messenger; // 0x08
    RHEngine *m_engine; // 0x0c
    unsigned char m_joystick; // 0x10
    SBInputJoystickState m_previous; // 0x14
    bool m_64; // 0x64
    undefined4 m_68; // 0x68
    RHGamePadSwing m_points; // 0x6c
};

DECOMP_SIZE_ASSERT(RHGamePad, 0x78)

#endif
