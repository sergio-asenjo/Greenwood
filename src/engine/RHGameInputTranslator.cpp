#include "RHGameInputTranslator.h"
#include "SBUIRendererInputField.h"
#include "RHGamePad.h"
#include "RHFontManager.h"
#include "RHMessenger.h"
#include "RHEngine.h"
#include "RHActorMessage.h"
#include "RHMouseMessage.h"
#include "SBThreadedInput.h"
#include "RHElementActorHumanCore.h"
#include <string.h>
#include <iterator>

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

class RHUnk005fc3b0 : public SBGeoVector2D
{
public:
    RHUnk005fc3b0 &FUN_005fc4d0(float factor);
    float Unk005fc6a0(float value);
    void FUN_005fc7c0(float value);
    unsigned char FUN_005fcc50(float scale) const;
};

// GLOBAL: GAME 0x006c0b54
RHGameInputTranslator *RHGameInputTranslator::mpInstance = 0;

static inline bool RHGameInputUserLocked(const RHMessenger *messenger)
{
    return *(const bool *)((const char *)messenger + 0x23);
}

// FUNCTION: GAME 0x00517900
void RHGameInputTranslator::TranslateMouseInput(SBGeoPoint2D &point, short wheel)
{
    RHMessenger *messenger = RHUnk00546050();
    if (RHGameInputUserLocked(messenger) != true)
    {
        if (point.m_x == 0.0f && !IsInDeadZone(point))
            messenger->RHUnk005460c0(RHUnk5490f0(4));
        float x = point.m_x;
        if (*(float *)(((RHUnk0055dbb0 *)g_unk0x006c0e48)->FUN_0055dbb0() + 0x54) - 1.0f <= x && !IsInDeadZone(point))
            messenger->RHUnk005460c0(RHUnk5490f0(3));
        if (point.m_y == 0.0f && !IsInDeadZone(point))
            messenger->RHUnk005460c0(RHUnk5490f0(2));
        float y = point.m_y;
        if (*(float *)(((RHUnk0055dbb0 *)g_unk0x006c0e48)->FUN_0055dbb0() + 0x58) - 1.0f <= y && !IsInDeadZone(point))
            messenger->RHUnk005460c0(RHUnk5490f0(1));
        if (wheel > 0)
            messenger->RHUnk005460c0(RHUnk5490f0(5));
        if (wheel < 0)
            messenger->RHUnk005460c0(RHUnk5490f0(6));
    }
}

#include "RHGameSyncCalls.h"
#include "SBInputKeyboardState.h"

class RHUnk0048a970;
extern RHUnk0048a970 *g_unk0x6c0b3c;

// FUNCTION: GAME 0x00517af0
bool RHGameInputTranslator::TranslateKeyboardInput(SBInputKeyboardState &keys, unsigned long flags)
{
    bool handled = false;
    RHMessenger *messenger = RHUnk00546050();
    if (keys[m_keys[0x21]] == 0 && m_previousKeys[m_keys[0x21]] > 0)
    {
        handled = (messenger->RHUnk005460c0(RHUnk5490f0(0x15)), true);
    }
    if (keys[m_keys[0x1f]] == 0 && m_previousKeys[m_keys[0x1f]] > 0)
    {
        handled = (messenger->RHUnk005460c0(RHUnk5490f0(0x23)), true);
    }
    if ((flags & 4) && keys[m_keys[0x1d]] == 0 && m_previousKeys[m_keys[0x1d]] > 0)
    {
        handled = (messenger->RHUnk005460c0(RHUnk5490f0(0x26)), true);
    }
    if ((flags & 1) && keys[m_keys[0x1b]] == 0 && m_previousKeys[m_keys[0x1b]] > 0)
    {
        handled = (messenger->RHUnk005460c0(RHUnk5490f0(0xc)), true);
    }
    if ((flags & 2) && keys[m_keys[0x1a]] == 0 && m_previousKeys[m_keys[0x1a]] > 0)
    {
        handled = (messenger->RHUnk005460c0(RHUnk5490f0(0xb)), true);
    }
    if (flags & 8)
    {
        if (keys[m_keys[0x20]] == 0 && m_previousKeys[m_keys[0x20]] > 0)
        {
            handled = (messenger->RHUnk005460c0(RHUnk5490f0(0x24)), true);
        }
        if (keys[0xf] > 0 && keys[0x38] > 0)
        {
            handled = (messenger->RHUnk005460c0(RHUnk5490f0(0x28)), true);
        }
        if (keys[1] > 0 && keys[0x1d] > 0)
        {
            handled = (messenger->RHUnk005460c0(RHUnk5490f0(0x28)), true);
        }
        if (keys[1] > 0 && keys[0x9d] > 0)
        {
            handled = (messenger->RHUnk005460c0(RHUnk5490f0(0x28)), true);
        }
        if (keys[m_keys[0x1e]] == 0 && m_previousKeys[m_keys[0x1e]] > 0)
        {
            handled = (messenger->RHUnk005460c0(RHUnk5490f0(0x17)), true);
        }
        if (RHGameInputUserLocked(messenger) == true)
        {
            memcpy(m_previousKeys, &keys, sizeof(m_previousKeys));
        }
        else
        {
            if (keys[m_keys[0x10]] > 0 && m_previousKeys[m_keys[0x10]] == 0)
            {
                handled = (messenger->RHUnk005460c0(RHUnk5490f0(0xd)), true);
            }
            if (keys[m_keys[0x19]] > 0 && m_previousKeys[m_keys[0x19]] == 0)
            {
                handled = (messenger->RHUnk005460c0(RHUnk5490f0(0xe)), true);
            }
            if (keys[m_keys[0x15]] > 0 && m_previousKeys[m_keys[0x15]] == 0)
            {
                handled = (messenger->RHUnk005460c0(RHUnk5490f0(0xf)), true);
            }
            if (keys[m_keys[0x10]] == 0 && m_previousKeys[m_keys[0x10]] > 0)
            {
                handled = (messenger->RHUnk005460c0(RHUnk5490f0(0x10)), true);
            }
            if (keys[m_keys[0x19]] == 0 && m_previousKeys[m_keys[0x19]] > 0)
            {
                handled = (messenger->RHUnk005460c0(RHUnk5490f0(0x11)), true);
            }
            if (keys[m_keys[0x15]] == 0 && m_previousKeys[m_keys[0x15]] > 0)
            {
                handled = (messenger->RHUnk005460c0(RHUnk5490f0(0x12)), true);
            }
            if (keys[m_keys[0x23]] == 0 && m_previousKeys[m_keys[0x23]] > 0)
            {
                handled = (messenger->RHUnk005460c0((RHUnk5490f0 &)RHUnk00549250(0x26, 0)), true);
            }
            if (keys[m_keys[0x11]] == 0 && m_previousKeys[m_keys[0x11]] > 0)
            {
                handled = (messenger->RHUnk005460c0(RHUnk5490f0(0x27)), true);
            }
            if (keys[m_keys[0x24]] == 0 && m_previousKeys[m_keys[0x24]] > 0)
            {
                handled = (messenger->RHUnk005460c0(RHUnk5490f0(0x14)), true);
            }
            if (keys[m_keys[0x17]] == 0 && m_previousKeys[m_keys[0x17]] > 0)
            {
                handled = (messenger->RHUnk005460c0((RHUnk5490f0 &)RHUnk00549250(1, 0)), true);
            }
            if (keys[m_keys[0x18]] == 0 && m_previousKeys[m_keys[0x18]] > 0)
            {
                handled = (messenger->RHUnk005460c0((RHUnk5490f0 &)RHUnk00549250(4, 0)), true);
            }
            if (keys[m_keys[0xd]] == 0 && m_previousKeys[m_keys[0xd]] > 0)
            {
                handled = (messenger->RHUnk005460c0((RHUnk5490f0 &)RHUnk00549250(0x12, 0)), true);
            }
            if (keys[m_keys[0xc]] == 0 && m_previousKeys[m_keys[0xc]] > 0)
            {
                handled = (messenger->RHUnk005460c0((RHUnk5490f0 &)RHUnk00549250(0xd, 0)), true);
            }
            if (keys[m_keys[0x22]] == 0 && m_previousKeys[m_keys[0x22]] > 0)
            {
                handled = (messenger->RHUnk005460c0(RHUnk5490f0(0x13)), true);
            }
            if (keys[m_keys[4]] > 0)
            {
                handled = (messenger->RHUnk005460c0(RHUnk5490f0(4)), true);
            }
            if (keys[m_keys[5]] > 0)
            {
                handled = (messenger->RHUnk005460c0(RHUnk5490f0(3)), true);
            }
            if (keys[m_keys[2]] > 0)
            {
                handled = (messenger->RHUnk005460c0(RHUnk5490f0(2)), true);
            }
            if (keys[m_keys[3]] > 0)
            {
                handled = (messenger->RHUnk005460c0(RHUnk5490f0(1)), true);
            }
            if (keys[m_keys[1]] == 0 && m_previousKeys[m_keys[1]] > 0)
            {
                handled = (messenger->RHUnk005460c0(RHUnk5490f0(6)), true);
            }
            if (keys[m_keys[0]] == 0 && m_previousKeys[m_keys[0]] > 0)
            {
                handled = (messenger->RHUnk005460c0(RHUnk5490f0(5)), true);
            }
            if (keys[m_keys[0x12]] == 0 && m_previousKeys[m_keys[0x12]] > 0)
            {
                handled = (messenger->RHUnk005460c0((RHUnk5490f0 &)RHUnk00549250(0x15, 0, 0)), true);
            }
            if (keys[m_keys[0x13]] == 0 && m_previousKeys[m_keys[0x13]] > 0)
            {
                handled = (messenger->RHUnk005460c0((RHUnk5490f0 &)RHUnk00549250(0x15, 0, 1)), true);
            }
            if (keys[m_keys[0x14]] == 0 && m_previousKeys[m_keys[0x14]] > 0)
            {
                handled = (messenger->RHUnk005460c0((RHUnk5490f0 &)RHUnk00549250(0x15, 0, 2)), true);
            }
            if (keys[m_keys[7]] == 0 && m_previousKeys[m_keys[7]] > 0)
            {
                void *actor = (void *)((RHGameSyncCalls *)g_unk0x6c0b3c)->FUN_0050f160(0);
                if (actor)
                {
                    handled = (messenger->RHUnk005460c0((RHUnk5490f0 &)RHUnk00549250(0xe, actor)), true);
                }
            }
            if (keys[m_keys[8]] == 0 && m_previousKeys[m_keys[8]] > 0)
            {
                void *actor = (void *)((RHGameSyncCalls *)g_unk0x6c0b3c)->FUN_0050f160(1);
                if (actor)
                {
                    handled = (messenger->RHUnk005460c0((RHUnk5490f0 &)RHUnk00549250(0xe, actor)), true);
                }
            }
            if (keys[m_keys[9]] == 0 && m_previousKeys[m_keys[9]] > 0)
            {
                void *actor = (void *)((RHGameSyncCalls *)g_unk0x6c0b3c)->FUN_0050f160(2);
                if (actor)
                {
                    handled = (messenger->RHUnk005460c0((RHUnk5490f0 &)RHUnk00549250(0xe, actor)), true);
                }
            }
            if (keys[m_keys[0xa]] == 0 && m_previousKeys[m_keys[0xa]] > 0)
            {
                void *actor = (void *)((RHGameSyncCalls *)g_unk0x6c0b3c)->FUN_0050f160(3);
                if (actor)
                {
                    handled = (messenger->RHUnk005460c0((RHUnk5490f0 &)RHUnk00549250(0xe, actor)), true);
                }
            }
            if (keys[m_keys[0xb]] == 0 && m_previousKeys[m_keys[0xb]] > 0)
            {
                void *actor = (void *)((RHGameSyncCalls *)g_unk0x6c0b3c)->FUN_0050f160(4);
                if (actor)
                {
                    handled = (messenger->RHUnk005460c0((RHUnk5490f0 &)RHUnk00549250(0xe, actor)), true);
                }
            }
        }
    }
    memcpy(m_previousKeys, &keys, sizeof(m_previousKeys));
    return handled;
}

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
    ManageScrollAxis(state);
    ManageMoveAxis(state);
    ManageMouseAxis(state);
    ManageQA(state);
    ManageCharacterSelect(state);
    ManageActionSelect(state);
    m_previous = state;
}

// FUNCTION: GAME 0x00518b30
void RHGamePad::ManageScrollAxis(SBInputJoystickState &state)
{
    switch (state.m_pov[0])
    {
    case 0:
        if (!state.m_buttons[5])
        {
            m_messenger->RHUnk005460c0(RHUnk5490f0(2));
            break;
        }
        m_messenger->RHUnk005460c0(RHUnk5490f0(5));
        return;
    case 4500:
        m_messenger->RHUnk005460c0(RHUnk5490f0(3));
        m_messenger->RHUnk005460c0(RHUnk5490f0(2));
        break;
    case 9000:
        m_messenger->RHUnk005460c0(RHUnk5490f0(3));
        break;
    case 13500:
        m_messenger->RHUnk005460c0(RHUnk5490f0(3));
        m_messenger->RHUnk005460c0(RHUnk5490f0(1));
        break;
    case 18000:
        if (!state.m_buttons[5])
        {
            m_messenger->RHUnk005460c0(RHUnk5490f0(1));
            break;
        }
        m_messenger->RHUnk005460c0(RHUnk5490f0(6));
        return;
    case 22500:
        m_messenger->RHUnk005460c0(RHUnk5490f0(1));
        m_messenger->RHUnk005460c0(RHUnk5490f0(4));
        break;
    case 27000:
        m_messenger->RHUnk005460c0(RHUnk5490f0(4));
        break;
    case 31500:
        m_messenger->RHUnk005460c0(RHUnk5490f0(4));
        m_messenger->RHUnk005460c0(RHUnk5490f0(2));
        break;
    default:
        return;
    }
    m_engine->SelectFollowElement(0);
}

// FUNCTION: GAME 0x00518ed0
void RHGamePad::ManageMoveAxis(SBInputJoystickState &state)
{
    if (((RHGamePadEngine *)m_engine)->m_selection.m_count)
    {
        RHGamePadSelection &selection = ((RHGamePadEngine *)m_engine)->m_selection;
        selection.GoTo(0);
        RHElementActorPC *pc = selection.m_current.node->value;
        long x = state.m_axes[0];
        if (x || state.m_axes[1])
        {
            SBGeoVector2D move((float)x, (float)state.m_axes[1]);
            bool fast = ((RHUnk005fc3b0 &)move).Unk005fc6a0(1.0f) > 28000.0f;
            ((RHUnk005fc3b0 &)move).FUN_005fc7c0(1.0f);
            if (fast)
                ((RHUnk005fc3b0 &)move).FUN_005fc4d0(75.0f);
            else
                ((RHUnk005fc3b0 &)move).FUN_005fc4d0(25.0f);
            CheckValidityOfPosition(move, fast);
        }
        if (!*(int *)((char *)pc + 0x268) && !state.m_buttons[10] && m_previous.m_buttons[10])
        {
            int mode = *(int *)(*(char **)((char *)pc + 0x50) + 0x8c);
            m_messenger->RHUnk005460c0((RHUnk5490f0 &)RHUnk00549250(0x25, 0, mode != 10));
        }
        if (*(int *)((char *)pc + 0x268) && !state.m_buttons[10] && m_previous.m_buttons[10])
            m_messenger->RHUnk005460c0((RHUnk5490f0 &)RHUnk00549120(3, *(SBGeoPoint2D *)&g_inputPosition, 2));
    }
}

// FUNCTION: GAME 0x00519620
void RHGamePad::ManageMouseAxis(SBInputJoystickState &state)
{
    SBGeoVector2D move;
    if (!((RHGamePadEngine *)m_engine)->GetSelection().GetCount() || !*(int *)((char *)((RHGamePadEngine *)m_engine)->GetSelection().Selected() + 0x268))
    {
        if (state.m_axes[6] - 0x7fff)
            move.m_y = (state.m_axes[6] - 0x7fff) * 0.00061050063f;
        if (state.m_axes[5] - 0x8000)
            move.m_x = (state.m_axes[5] - 0x7fff) * 0.00061050063f;
        SBThreadedInput::ReachPosition((*(SBGeoPoint2D *)&g_inputPosition).Unk005fc190(move));
        if (state.m_buttons[11] && !m_previous.m_buttons[11])
            SBThreadedInput::PushButton(SBButtonLeft);
        if (!state.m_buttons[11] && m_previous.m_buttons[11])
            SBThreadedInput::ReleaseButton(SBButtonLeft);
    }
    if (((RHGamePadEngine *)m_engine)->GetSelection().GetCount() > 0 && *(int *)((char *)((RHGamePadEngine *)m_engine)->GetSelection().Selected() + 0x268))
    {
        if (state.m_axes[6] - 0x7fff)
            move.m_y = (state.m_axes[6] - 0x7fff) * 0.00061050063f;
        if (state.m_axes[5] - 0x8000)
            move.m_x = (state.m_axes[5] - 0x7fff) * 0.00061050063f;
        if (move.m_x == 0.0f && move.m_y == 0.0f)
        {
            if (m_points.size())
                RecognizeSwing();
        }
        else
            m_points.Append(move);
    }
}

static inline int *RHGamePadActions(RHElementActorPC *pc)
{
    return *(int **)((char *)pc + 0x5fc);
}

static inline unsigned RHGamePadOpponentCount(RHElementActorPC *pc)
{
    return *(unsigned *)((char *)pc + 0x268);
}

static inline unsigned short RHGamePadFacing(RHElementActorPC *pc)
{
    return *(unsigned short *)(*(char **)((char *)pc + 0x50) + 0xd8);
}

// FUNCTION: GAME 0x00519840
void RHGamePad::ManageActionSelect(SBInputJoystickState &state)
{
    if (((RHGamePadEngine *)m_engine)->m_selection.m_count)
    {
        RHGamePadSelection &selection = ((RHGamePadEngine *)m_engine)->m_selection;
        selection.GoTo(0);
        RHElementActorPC *pc = selection.m_current.node->value;
        if (!RHGamePadOpponentCount(pc))
        {
            if (!state.m_buttons[1] && m_previous.m_buttons[1])
                m_messenger->RHUnk005460c0((RHUnk5490f0 &)RHUnk00549250(0x16, pc, RHGamePadActions(pc)[0x12]));
            if (!state.m_buttons[0] && m_previous.m_buttons[0])
                m_messenger->RHUnk005460c0((RHUnk5490f0 &)RHUnk00549250(0x16, pc, RHGamePadActions(pc)[0x13]));
            if (!state.m_buttons[2] && m_previous.m_buttons[2])
                m_messenger->RHUnk005460c0((RHUnk5490f0 &)RHUnk00549250(0x16, pc, RHGamePadActions(pc)[0x14]));
        }
        else
        {
            if (!state.m_buttons[1] && m_previous.m_buttons[1])
                ChooseOpponent(pc, (RHGamePadFacing(pc) + 8) % 16, 1);
            if (!state.m_buttons[0] && m_previous.m_buttons[0])
                ChooseOpponent(pc, (RHGamePadFacing(pc) + 15) % 16, -1);
            if (!state.m_buttons[2] && m_previous.m_buttons[2])
                ChooseOpponent(pc, RHGamePadFacing(pc) + 1, 1);
        }
    }
    if (state.m_buttons[3] && !m_previous.m_buttons[3])
        m_messenger->RHUnk005460c0((RHUnk5490f0 &)RHUnk00549120(3, *(SBGeoPoint2D *)&g_inputPosition, 0x80));
    if (!state.m_buttons[3] && m_previous.m_buttons[3])
        m_messenger->RHUnk005460c0((RHUnk5490f0 &)RHUnk00549120(3, *(SBGeoPoint2D *)&g_inputPosition, 2));
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


static inline SBGeoPoint2D &RHGamePadPosition(RHElementActorPC *actor)
{
    return *(SBGeoPoint2D *)(*(char **)((char *)actor + 0x50) + 0x24);
}

static inline unsigned short RHGamePadLayer(RHElementActorPC *pc)
{
    return *(unsigned short *)(*(char **)((char *)pc + 0x50) + 0xde);
}

static inline char *RHGamePadSector(unsigned short index)
{
    if (index == 0xffff)
        return *(char **)((char *)g_unk0x6c0a9c + 0x4184);
    return (*(char ***)((char *)g_unk0x6c0a9c + 0x4064))[index];
}

static inline float RHGamePadMapWidth(RHEngine *engine)
{
    return *(float *)((char *)engine + 0x4730);
}

static inline float RHGamePadMapHeight(RHEngine *engine)
{
    return *(float *)((char *)engine + 0x4734);
}

// Parked: target keeps the null constant in EBP for sector/patch tests and stores.
// STUB: GAME 0x00519a90
bool RHGamePad::CheckValidityOfPosition(SBGeoVector2D &move, bool fast)
{
    char *sector;
    RHGamePadSelection &selection = ((RHGamePadEngine *)m_engine)->m_selection;
    selection.GoTo(0);
    RHElementActorPC *pc = selection.m_current.node->value;
    SBGeoPoint2D position(RHGamePadPosition(pc));
    SBGeoPoint2D destination = position.Unk005fc190(move);
    bool valid = false;
    unsigned short layer = RHGamePadLayer(pc);
    if (*(unsigned *)((char *)m_engine + 0x4a94) % 5 == 0)
    {
        sector = 0;
        char *patch = 0;
        if (!(destination.m_x < RHGamePadMapWidth(m_engine) && destination.m_y < RHGamePadMapHeight(m_engine)
            && ((RHEngineGridCalls *)g_unk0x6c0a9c)->FUN_004e9760(destination, position, (void *&)sector, layer) >= 0))
            sector = 0;
        else if (sector && (unsigned short)(*(unsigned long *)(sector + 0x30) >> 2) & 1)
        {
            patch = *(char **)(sector + 0x58);
            sector = RHGamePadSector(*(unsigned short *)(patch + 0x13e));
            layer = *(unsigned short *)(patch + 0x13c);
        }
        valid = patch || (sector && ((((unsigned short)*(unsigned long *)(sector + 0x30) & 1) && ((unsigned short)(*(unsigned long *)(sector + 0x30) >> 1) & 1))
            || ((unsigned short)(*(unsigned long *)(sector + 0x30) >> 12) & 1) || (*(unsigned long *)(sector + 0x30) & 0x8000) == 0x8000));
        if (valid)
            m_engine->FUN_004e3720(&destination, fast ? 10 : 6, layer, sector, patch);
    }
    return valid;
}

static inline RHGamePadSelection &RHGamePadOpponents(RHElementActorPC *pc)
{
    return *(RHGamePadSelection *)((char *)pc + 0x260);
}

// FUNCTION: GAME 0x0051a3c0
void RHGamePad::ChooseOpponent(RHElementActorPC *pc, unsigned short direction, short step)
{
    if (RHGamePadOpponents(pc).m_count > 1)
    {
        for (;;)
        {
            for (unsigned short i = 1; i < RHGamePadOpponents(pc).m_count; ++i)
            {
                RHGamePadSelection &opponents = RHGamePadOpponents(pc);
                opponents.GoTo(i);
                RHElementActorPC *opponent = opponents.m_current.node->value;
                bool found = (unsigned short)((const RHUnk005fc3b0 &)RHGamePadPosition(opponent).Unk005fc110(RHGamePadPosition(pc))).FUN_005fcc50(1.0f) == direction;
                if (found)
                {
                    ((RHElementActorHuman *)pc)->FUN_0047d920((RHElementActorHuman *)opponent);
                    return;
                }
            }
            if (direction - step < 0)
                direction += step + 16;
            else
                direction = (direction + step) % 16;
        }
    }
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

void EmitRHGameInputTranslator(RHGameInputTranslator *translator, SBGeoPoint2D &point, SBInputKeyboardState &keys)
{
    translator->TranslateMouseInput(point, 0);
    translator->TranslateKeyboardInput(keys, 0);
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
