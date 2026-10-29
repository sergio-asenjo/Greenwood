#include "SBNullstr.h"
#include "RHSector.h"

// FUNCTION: GAME 0x0057d490
RHUnk0057d490::RHUnk0057d490()
{
    m_30 = 3;
    m_ec = false;
}

// SYNTHETIC: GAME 0x0057d590
// RHUnk0057d490::`scalar deleting destructor'
// FUNCTION: GAME 0x0057d5b0
RHUnk0057d490::~RHUnk0057d490() {}

void RHSector::DisplayAlpha(unsigned long, unsigned long, bool) {}
// TEMPLATE: GAME 0x0057cd50 FOLDED
// ?Serialize@RHSector@@UAE_NAAVSBFile@@@Z
bool RHSector::Serialize(SBFile &) { return true; }

// TEMPLATE: GAME 0x0057c9c0 FOLDED
// ??Eiterator@?$list@PAXV?$allocator@PAX@std@@@std@@QAE?AV012@H@Z

// TEMPLATE: GAME 0x0057c9c0 FOLDED
// ??Eiterator@?$list@_NV?$allocator@_N@std@@@std@@QAE?AV012@H@Z

// TEMPLATE: GAME 0x0044e8b0 FOLDED
// ?erase@?$list@_NV?$allocator@_N@std@@@std@@QAE?AViterator@12@V312@0@Z

// TEMPLATE: GAME 0x0046eb80 FOLDED
// ?begin@?$list@PAXV?$allocator@PAX@std@@@std@@QAE?AViterator@12@XZ

// TEMPLATE: GAME 0x0046eb80 FOLDED
// ?begin@?$list@_NV?$allocator@_N@std@@@std@@QAE?AViterator@12@XZ


// TEMPLATE: GAME 0x00424410 FOLDED
// ?insert@RHSectorActorList@@QAE?AVRHSectorActorIter@@V2@ABQAVRHElementActor@@@Z
RHSectorActorIter RHSectorActorList::insert(RHSectorActorIter pos, RHElementActor *const &actor)
{
    RHSectorActorNode *next = pos.m_p;
    RHSectorActorNode *previous = next->m_prev;
    RHSectorActorNode *node = (RHSectorActorNode *)operator new(sizeof(RHSectorActorNode));
    node->m_next = next ? next : node;
    node->m_prev = previous ? previous : node;
    next->m_prev = node;
    node->m_prev->m_next = node;
    new (&node->m_data) RHElementActor *(actor);
    ++m_count;
    return RHSectorActorIter(node);
}


// TEMPLATE: GAME 0x0046eb30 FOLDED
// ?erase@RHSectorActorList@@QAE?AVRHSectorActorIter@@V2@@Z
RHSectorActorIter RHSectorActorList::erase(RHSectorActorIter position)
{
    RHSectorActorIter erased = position;
    position.m_p = position.m_p->m_next;
    RHSectorActorNode *node = erased.m_p;
    node->m_prev->m_next = node->m_next;
    node->m_next->m_prev = node->m_prev;
    operator delete(node);
    --m_count;
    return position;
}

// FUNCTION: GAME 0x005c8e40
void RHProfileListCursor::GoTo(int wanted)
{
    int count = size();
    if (m_dirty)
    {
        if (wanted <= (count + 1) / 2)
        {
            m_current = begin();
            std::advance(m_current, wanted);
        }
        else
        {
            m_current = end();
            std::advance(m_current, wanted - count);
        }
        m_dirty = false;
        m_index = wanted;
    }
    else
    {
        int previous = m_index;
        if (wanted != previous)
        {
            if (wanted < previous)
            {
                if (wanted < (previous + 1) / 2)
                {
                    m_current = begin();
                    std::advance(m_current, wanted);
                }
                else
                    std::advance(m_current, wanted - previous);
            }
            else
            {
                if (wanted < (previous + count) / 2)
                    std::advance(m_current, wanted - previous);
                else
                {
                    m_current = end();
                    std::advance(m_current, wanted - count);
                }
            }
            m_index = wanted;
        }
    }
}

// SYNTHETIC: GAME 0x00522560
// RHUnk00522540::`scalar deleting destructor'


// FUNCTION: GAME 0x0060ce90
void RHUnkSectorPoints::FUN_0060ce90(const SBGeoPoint2D &point, unsigned int index)
{
    m_28 = 0;
    m_29 = 0;
    ((RHMobileUnk00611360 *)this)->FUN_00610f50(point, index);
}

int RHUnk005f5440::Unk() { return 0; }
// SYNTHETIC: GAME 0x0057d3c0
// RHUnk0057d3a0::`scalar deleting destructor'
// FUNCTION: GAME 0x0057d3e0
RHUnk0057d3a0::~RHUnk0057d3a0() {}
// SYNTHETIC: GAME 0x0057d410
// RHUnk0057d3f0::`scalar deleting destructor'
// FUNCTION: GAME 0x0057d430
RHUnk0057d3f0::~RHUnk0057d3f0() {}
// SYNTHETIC: GAME 0x0057eda0
// RHUnk0057ed80::`scalar deleting destructor'
// FUNCTION: GAME 0x0057edc0
RHUnk0057ed80::~RHUnk0057ed80() {}
// SYNTHETIC: GAME 0x0057d460
// RHUnk0057d440::`scalar deleting destructor'
// FUNCTION: GAME 0x0057d480
RHUnk0057d440::~RHUnk0057d440() {}
// SYNTHETIC: GAME 0x0057dcc0
// RHSectorLift::`scalar deleting destructor'

// FUNCTION: GAME 0x0057dce0
RHSectorLift::~RHSectorLift() {}
void RHUnk0051aa00::Unk0051b2a0(SBFile &, RHSectorBuilding *) {}
