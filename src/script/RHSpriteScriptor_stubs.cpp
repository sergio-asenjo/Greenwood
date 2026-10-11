#include "SBNullstr.h"
#include "RHSpriteScriptor.h"

// GLOBAL: GAME 0x006c0620
std::string g_unk0x006c0620;
// GLOBAL: GAME 0x006c0630
std::string g_unk0x006c0630;
// GLOBAL: GAME 0x006c0b1c
RHUnkSpriteBank *g_unk0x006c0b1c;

SBGeoVector2D &SBGeoVector2D::operator=(const SBGeoVector2D &) { return *this; }
// Parked: frame lacks four bytes and two temporary stores in count-zero vector construction.
// STUB: GAME 0x005bed50
RHUnkSpriteRow::RHUnkSpriteRow() : m_resources(0), m_frames(0), m_rates(0, (unsigned short)0), m_positions(0), m_flags(0, (unsigned short)0)
{
    SBGeoPoint2D &position = m_position;
    m_04 = 0;
    position.m_x = 0;
    position.m_y = 0;
    m_00 = 0;
    m_10 = 0;
}
SBGeoVector2D::SBGeoVector2D(const SBGeoVector2D &other) : SBGeoPoint2D(other) {}
RHUnkSpriteCacheNode *RHUnkSpriteCache::FUN_005c15a0(const std::string &) { return m_head; }
std::pair<RHUnkSpriteCacheIterator, bool> RHUnkSpriteCache::FUN_005c09c0(const RHUnkSpriteCacheValue &) { return std::pair<RHUnkSpriteCacheIterator, bool>(end(), false); }
