#include "RHGameInputTranslator.h"
#include "SBUIRendererInputField.h"
#include <string.h>

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
        ((RHMobileUnk0060a820 *)this)->FUN_0060a820(first, second);
    }
    ~RHGameInputSegmentTemporary()
    {
        ((RHMobileUnk006100e0 *)this)->~RHMobileUnk006100e0();
    }
    const RHMalignitySegment &Value() const { return *(const RHMalignitySegment *)this; }
    unsigned char m_00[0x10];
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

class RHUnk0051a4e0
{
public:
    char *FUN_0051a4e0();
    bool FUN_0051a680(int first, int second, int third, int fourth, int fifth);
};

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

void EmitRHUnk0051a4e0(RHUnk0051a4e0 *a)
{
    a->FUN_0051a4e0();
    a->FUN_0051a680(0, 0, 0, 0, 0);
}
