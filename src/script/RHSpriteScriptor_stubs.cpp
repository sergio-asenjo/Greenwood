#include "RHSpriteScriptor.h"

// GLOBAL: GAME 0x006c0620
std::string g_unk0x006c0620;
// GLOBAL: GAME 0x006c0630
std::string g_unk0x006c0630;
// GLOBAL: GAME 0x006c0b1c
RHUnkSpriteBank *g_unk0x006c0b1c;

SBGeoVector2D &SBGeoVector2D::operator=(const SBGeoVector2D &) { return *this; }
RHUnkSpriteRow::RHUnkSpriteRow() {}
SBGeoVector2D::SBGeoVector2D(const SBGeoVector2D &other) : SBGeoPoint2D(other) {}
RHUnkSpriteCacheNode *RHUnkSpriteCache::FUN_005c15a0(const std::string &) { return m_head; }
std::pair<RHUnkSpriteCacheIterator, bool> RHUnkSpriteCache::FUN_005c09c0(const RHUnkSpriteCacheValue &) { return std::pair<RHUnkSpriteCacheIterator, bool>(end(), false); }
