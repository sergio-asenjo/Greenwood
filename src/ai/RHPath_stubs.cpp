#include "RHPath.h"

// GLOBAL: GAME 0x006c0b9c
RHUnkPathRegistry *g_unk0x6c0b9c;

void RHPathUnk0048f180(RHPathHistory *dst, const RHPathHistory *src)
{
    if (dst)
        *dst = *src;
}

RHPathHistoryNode *RHPathHistoryList::Unk00551de0(RHPathHistoryNode *next, RHPathHistoryNode *prev)
{
    RHPathHistoryNode *node = (RHPathHistoryNode *)::operator new(0x1c);
    node->m_next = next ? next : node;
    node->m_prev = prev ? prev : node;
    return node;
}

void SBGeoBoundingBox2D::FUN_00607e30(const RHMalignitySegment &) {}
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
