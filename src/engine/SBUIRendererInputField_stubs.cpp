#include "SBNullstr.h"
#include "SBUIRendererInputField.h"

// FUNCTION: GAME 0x0048be30
void FUN_0048be30()
{
}

bool SBUIInputFieldBoxCalls::FUN_00608450(const SBGeoBoundingBox2D &) { return false; }
void SBUIInputFieldBoxCalls::FUN_0060a860(const RHMobileUnk006100e0 &) {}
unsigned short SBUIInputFieldDrawUnk::FUN_00614230(void *, std::wstring *, const SBGeoBoundingBox2D &, unsigned int, unsigned int, unsigned int) { return 0; }
#include "RHGameInputTranslator.h"
#include "RHKeyConfig.h"
#include <string.h>

// FUNCTION: GAME 0x0045ac40
const short *RHKeyConfig::GetKeys() const { return m_keys; }

void RHGameInputSegment::FUN_004611c0() {}
bool RHGameInputSegment::FUN_0060a880(const SBGeoPoint2D &) const { return false; }
