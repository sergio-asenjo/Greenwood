#include "RHSaveGame.h"

RHSaveGame::Header::Header()
{
    m_00 = 0x52485347;
    m_04 = 0x30;
    m_08 = 0xbad;
}

std::string RHSaveGame::FUN_0056e5d0() const { return std::string(); }
RHUnk005f4fc0::RHUnk005f4fc0() {}
RHUnk005f4fc0::~RHUnk005f4fc0() {}
int RHUnk005f4fc0::FUN_005f5090(const std::string &, int) { return 0; }
bool RHUnk005f4fc0::FUN_005f6200(void *) { return true; }
bool FUN_005f6400(const std::string &) { return true; }
