#include "SBNullstr.h"
#include "SBUIRendererInputField.h"

void FUN_0048be30()
{
}

bool SBUIInputFieldBoxCalls::FUN_00608450(const SBGeoBoundingBox2D &) { return false; }
void SBUIInputFieldBoxCalls::FUN_0060a860(const RHMobileUnk006100e0 &) {}
unsigned short SBUIInputFieldDrawUnk::FUN_00614230(void *, std::wstring *, const SBGeoBoundingBox2D &, unsigned int, unsigned int, unsigned int) { return 0; }
#include "RHGameInputTranslator.h"
#include "RHKeyConfig.h"
#include <string.h>

RHKeyConfig::RHKeyConfig(const RHKeyConfig &other)
{
    m_keys = (short *)operator new(0x3a);
    m_count = other.m_count;
    memcpy(m_keys, other.m_keys, 0x3a);
}

unsigned short RHKeyConfig::GetKeyCount() const { return 0x1c; }
const short *RHKeyConfig::GetKeys() const { return m_keys; }

void RHGameInputSegment::FUN_004611c0() {}
bool RHGameInputSegment::FUN_0060a880(const SBGeoPoint2D &) const { return false; }
