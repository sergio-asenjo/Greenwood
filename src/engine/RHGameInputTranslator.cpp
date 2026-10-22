#include "RHGameInputTranslator.h"
#include "SBUIRendererInputField.h"
#include "RHGamePad.h"
#include "RHFontManager.h"
#include <string.h>
#include <iterator>

class RHUnk0055dbb0
{
public:
    char *FUN_0055dbb0();
};

extern unsigned char g_unk0x006c0e48[];

class RHMalignitySegment;

class RHMalignityArrayCalls
{
public:
    void FUN_0059fba0(const unsigned &value);
    void FUN_004e60a0(void *position, unsigned count, const unsigned &value);
    void FUN_004e62b0(void *position, unsigned count, const RHMalignitySegment &value);
};

class RHGameInputSegmentTemporary
{
public:
    RHGameInputSegmentTemporary(const SBGeoPoint2D &first, const SBGeoPoint2D &second)
    {
        ((SBGeoSegment2D *)this)->SBGeoSegment2D::SBGeoSegment2D(first, second);
    }
    ~RHGameInputSegmentTemporary()
    {
        ((RHMobileUnk006100e0 *)this)->~RHMobileUnk006100e0();
    }
    const RHMalignitySegment &Value() const { return *(const RHMalignitySegment *)this; }
    unsigned char m_00[0x10];
};

class RHUnk0051a4e0
{
public:
    char *FUN_0051a4e0();
    bool FUN_0051a680(int first, int second, int third, int fourth, int fifth);
};

class RHUnk005ef320;
extern RHUnk005ef320 *g_unk0x6c11d0;
extern RHEngine *g_pEngine;
RHMessenger *RHUnk00546050();

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
    unsigned PCCount() const
    {
        RHElementActorPC **first = *(RHElementActorPC **const volatile *)&m_493c;
        if (!first)
            return 0;
        return m_4940 - first;
    }
};

// GLOBAL: GAME 0x006c0b54
RHGameInputTranslator *RHGameInputTranslator::mpInstance = 0;

// FUNCTION: GAME 0x005185b0
void RHGameInputTranslator::ResetState()
{
    memset(m_previousKeys, 0, sizeof(m_previousKeys));
}

// FUNCTION: GAME 0x005185c0
void RHGameInputTranslator::ClearDeadZone()
{
    RHGameInputSegment *source = m_last;
    RHGameInputSegment *end = m_last;
    RHGameInputSegment *destination = m_first;
    for (; source != end; ++source, ++destination)
        ((SBUIInputFieldBoxCalls *)destination)->FUN_0060a860((const RHMobileUnk006100e0 &)*source);
    end = m_last;
    for (RHGameInputSegment *entry = destination; entry != end; ++entry)
        entry->FUN_004611c0();
    m_last = destination;
    m_deadZoneChanged = true;
}

// Parked: constructor-return receiver and segment-array scheduling differ.
// STUB: GAME 0x00518620
void RHGameInputTranslator::AddToDeadZone(const SBGeoPoint2D &first, const SBGeoPoint2D &second)
{
    RHGameInputSegmentTemporary segment(first, second);
    ((RHMalignityArrayCalls *)((char *)this + 0x120))->FUN_004e62b0(m_last, 1, segment.Value());
    m_deadZoneChanged = true;
}

// FUNCTION: GAME 0x005186a0
bool RHGameInputTranslator::IsInDeadZone(const SBGeoPoint2D &point) const
{
    unsigned int count = !m_first ? 0 : m_last - m_first;
    for (unsigned short index = 0; index < count; ++index) {
        const RHGameInputSegment *entries = m_first;
        if (entries[index].FUN_0060a880(point) == true)
            return true;
    }
    return false;
}

#include "RHKeyConfig.h"

// FUNCTION: GAME 0x00518700
void RHGameInputTranslator::ReflectActiveKeyConfig()
{
    RHKeyConfig keys(*(const RHKeyConfig *)(((RHUnk0055dbb0 *)g_unk0x006c0e48)->FUN_0055dbb0() + 0x34));
    memcpy(m_keys, keys.GetKeys(), keys.GetKeyCount() * sizeof(short));
}

// FUNCTION: GAME 0x005187a0
void RHGameInputTranslator::DeityCall()
{
    m_keys[0x23] = 0xc7;
    m_keys[0x1e] = 0x9c;
    m_keys[0x22] = 0xcf;
    m_keys[0x21] = 0x46;
}

// FUNCTION: GAME 0x00518930
RHGamePad::RHGamePad()
    : m_input(SBInputUnk005fb730::mpInput), m_messenger(RHUnk00546050()), m_engine(g_pEngine)
{
    RHUnk0051a4e0 *joysticks = m_input->FUN_005fafc0();
    void *window = *(void **)((char *)g_unk0x6c11d0 + 0x100);
    m_joystick = m_input->FUN_005fb410(*(RHFontText *)joysticks->FUN_0051a4e0(), 5, window);
    memset(&m_previous, 0, sizeof(m_previous));
    m_68 = 0;
    m_64 = false;
}

// SYNTHETIC: GAME 0x005189f0
// RHGamePad::`scalar deleting destructor'

// FUNCTION: GAME 0x00518a10
RHGamePad::~RHGamePad()
{
    m_input->FUN_005fb730(m_joystick);
}

// FUNCTION: GAME 0x00518ab0
void RHGamePad::ProcessGamepadInput()
{
    SBInputJoystickState state;
    bool lost;
    m_input->FUN_005fb770(m_joystick, &state, &lost);
    FUN_00518b30(state);
    FUN_00518ed0(state);
    FUN_00519620(state);
    FUN_00519c70(state);
    FUN_005191e0(state);
    FUN_00519840(state);
    m_previous = state;
}

// Parked: target keeps a second frame slot for the clean-cursor seek and holds the count in ECX.
// STUB: GAME 0x00519080
unsigned char RHGamePad::GetSelectedIndexPC()
{
    RHElementActorPC **first = ((RHGamePadEngine *)g_pEngine)->m_493c;
    unsigned char count = first == 0 ? 0 : ((RHGamePadEngine *)g_pEngine)->m_4940 - first;
    RHGamePadSelection &selection = ((RHGamePadEngine *)m_engine)->m_selection;
    if (selection.m_count > 0)
    {
        RHElementActorPC *pc = selection.At(0);
        for (unsigned char index = 0; index < count; ++index)
        {
            if (((RHGamePadEngine *)g_pEngine)->m_493c[index] == pc)
                return index;
        }
    }
    return 0xff;
}


// FUNCTION: GAME 0x0051a4e0
char *RHUnk0051a4e0::FUN_0051a4e0()
{
    void *value = *(void **)((char *)this + 4);
    return (char *)(*(void **)value) + 8;
}

// FUNCTION: GAME 0x0051a680
bool RHUnk0051a4e0::FUN_0051a680(int first, int second, int third, int fourth, int fifth)
{
    return false;
}

void EmitRHGameInputTranslator(RHGameInputTranslator *translator, const SBGeoPoint2D &point)
{
    translator->ResetState();
    translator->ClearDeadZone();
    translator->AddToDeadZone(point, point);
    translator->IsInDeadZone(point);
    translator->ReflectActiveKeyConfig();
    translator->DeityCall();
}

void EmitRHGamePad()
{
    RHGamePad *pad = new RHGamePad;
    pad->ProcessGamepadInput();
    pad->GetSelectedIndexPC();
    delete pad;
}

void EmitRHUnk0051a4e0(RHUnk0051a4e0 *a)
{
    a->FUN_0051a4e0();
    a->FUN_0051a680(0, 0, 0, 0, 0);
}
