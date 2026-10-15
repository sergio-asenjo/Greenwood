#include "SBNullstr.h"
#include "RHSaveGame.h"

RHUnk005f4fc0::~RHUnk005f4fc0() {}
bool RHUnk005f4fc0::FUN_005f6200(void *) { return true; }
bool FUN_005f6400(const std::string &) { return true; }
const _SYSTEMTIME &RHSaveGame::GetTime() const { return *(const _SYSTEMTIME *)(m_data + 0x38); }
