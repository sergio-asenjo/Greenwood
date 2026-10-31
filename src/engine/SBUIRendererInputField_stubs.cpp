#include "SBNullstr.h"
#include "SBUIRendererInputField.h"

// FUNCTION: GAME 0x0048be30
void FUN_0048be30()
{
}

// FUNCTION: GAME 0x00608450
bool SBUIInputFieldBoxCalls::FUN_00608450(const SBGeoSegment2D &other)
{
    SBGeoBoundingBox2D &box = *(SBGeoBoundingBox2D *)this;
    if (!box.m_10)
        return false;
    return box.FUN_00608400(other.First()) && box.FUN_00608400(other.Second());
}

// FUNCTION: GAME 0x0060a860
SBUIInputFieldBoxCalls &SBUIInputFieldBoxCalls::FUN_0060a860(const RHMobileUnk006100e0 &other)
{
    ((RHMobileUnk0060a820 *)this)->FUN_006158f0(other);
    return *this;
}

unsigned short SBUIInputFieldDrawUnk::FUN_00614230(void *, std::wstring *, const SBGeoBoundingBox2D &, unsigned int, unsigned int, unsigned int) { return 0; }
#include "RHGameInputTranslator.h"
#include "RHKeyConfig.h"
#include <string.h>

// FUNCTION: GAME 0x0045ac40
const short *RHKeyConfig::GetKeys() const { return m_keys; }

// TEMPLATE: GAME 0x004611c0 FOLDED
// ?FUN_004611c0@RHGameInputSegment@@QAEXXZ
void RHGameInputSegment::FUN_004611c0()
{
    ((RHMobileUnk006100e0 *)this)->~RHMobileUnk006100e0();
}
