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

bool RHUnkPathGeometry::Unk004f9260(const SBGeoPoint2D &, const SBGeoPoint2D &, unsigned short) { return true; }
bool RHUnkPathGeometry::Unk004f9170(const SBGeoPoint2D &, const SBGeoPoint2D &, unsigned short, void *) { return true; }
void RHUnkPathEngine::Unk004dab90(RHPathArray *, unsigned short) {}
void *RHUnkPathActorInfoBase::Unk0055fa10(int) { return this; }
void RHUnkWaypointRef::Unk00408660() {}
