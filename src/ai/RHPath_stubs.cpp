#include "SBNullstr.h"
#include "RHPath.h"

// GLOBAL: GAME 0x006c0b9c
RHUnkPathRegistry *g_unk0x6c0b9c;

// FUNCTION: GAME 0x0048f180
void RHPathUnk0048f180(RHPathHistory *dst, const RHPathHistory *src)
{
    if (dst)
        *dst = *src;
}

// FUNCTION: GAME 0x00551de0
RHPathHistoryNode *RHPathHistoryList::Unk00551de0(RHPathHistoryNode *next, RHPathHistoryNode *prev)
{
    RHPathHistoryNode *node = (RHPathHistoryNode *)::operator new(0x1c);
    node->m_next = next ? next : node;
    node->m_prev = prev ? prev : node;
    return node;
}

// FUNCTION: GAME 0x00607e30
void SBGeoBoundingBox2D::FUN_00607e30(const RHMalignitySegment &segment)
{
    Unk00607dc0(*(const SBGeoPoint2D *)&segment);
    Unk00607dc0(*(const SBGeoPoint2D *)((const char *)&segment + 8));
}
bool RHMalignitySegment::FUN_0060a990(const RHMalignitySegment &) { return false; }
RHPathHelperList::RHPathHelperList(const char &allocator)
{
    *(char *)&m_0 = allocator;
    m_head = (RHPathHelperNode *)operator new(0x0c);
    m_head->m_next = m_head;
    m_head->m_prev = m_head;
    m_count = 0;
}

RHUnk004dab90Rectangle::~RHUnk004dab90Rectangle() {}
