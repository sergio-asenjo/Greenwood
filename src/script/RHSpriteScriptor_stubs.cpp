#include "RHSpriteScriptor.h"

// GLOBAL: GAME 0x006c0620
std::string g_unk0x006c0620;
// GLOBAL: GAME 0x006c0630
std::string g_unk0x006c0630;
// GLOBAL: GAME 0x006c0b1c
RHUnkSpriteBank *g_unk0x006c0b1c;

SBGeoVector2D &SBGeoVector2D::operator=(const SBGeoVector2D &) { return *this; }
RHUnkSpriteScriptInfo::~RHUnkSpriteScriptInfo() {}
RHUnkSpriteCacheValue::RHUnkSpriteCacheValue(const std::string &key, const RHUnkSpriteScriptInfo &info) : m_key(key), m_info(info) {}
RHUnkSpriteCacheIterator RHUnkSpriteCache::FUN_005c0800(const std::string &) { return end(); }
RHUnkSpriteCacheInsertResult RHUnkSpriteCache::FUN_005c0690(const RHUnkSpriteCacheValue &) { RHUnkSpriteCacheInsertResult result; result.m_first = end(); result.m_second = false; return result; }
bool RHUnkSpriteBank::FUN_00506b10(SBFile &) { return true; }
bool RHSpriteScriptor::FUN_005c0490(SBFile &, const char *) { return true; }
void RHSpriteScriptor::FUN_005bfef0(SBFile &, unsigned short, std::vector<RHUnkSpriteRow> &, std::vector<unsigned short> &) {}
