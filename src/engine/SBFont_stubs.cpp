#include "SBNullstr.h"
#include "SBFont.h"

SBFontLock::SBFontLock() {}
SBFontLock::~SBFontLock() {}
void FUN_005f8030(int, const char *, int, const char *, ...) {}

// FUNCTION: GAME 0x00620c70
SBFontNode0061fcb0 *SBFontTree0061fcb0::FUN_00620c70(SBFontNode0061fcb0 *parent, int color)
{
    SBFontNode0061fcb0 *node = (SBFontNode0061fcb0 *)operator new(sizeof(SBFontNode0061fcb0));
    node->m_04 = parent;
    node->m_10 = color;
    return node;
}
SBFontIterator0061fe10 SBFontTree0061fcb0::FUN_0061fce0(SBFontIterator0061fe10 first, SBFontIterator0061fe10) { return first; }
SBFontNode0061fcb0 *SBFontTree0061fcb0::FUN_00620d60(SBFontNode0061fcb0 *source, SBFontNode0061fcb0 *parent)
{
    SBFontLock lock;
    SBFontNode0061fcb0 *result = source;
    for (; source != g_unk0x006c191c; source = source->m_00) {
        SBFontNode0061fcb0 *node = FUN_00620c70(parent, source->m_10);
        if (result == source) result = node;
        node->m_08 = FUN_00620d60(source->m_08, node);
        std::_Construct(&node->m_0c, source->m_0c);
        parent->m_00 = node;
        parent = node;
    }
    parent->m_00 = g_unk0x006c191c;
    return result;
}
void SBFontIterator0061fe10::FUN_00620ca0() {}
void SBFontIterator0061f3e0::FUN_00620e30() {}
void SBFontIterator0061fe10::FUN_00620fa0()
{
    SBFontLock lock;
    if (m_00->m_08 != g_unk0x006c191c) {
        SBFontNode0061fcb0 *node = m_00->m_08;
        {
            SBFontLock inner;
            while (node->m_00 != g_unk0x006c191c) node = node->m_00;
        }
        m_00 = node;
    } else {
        SBFontNode0061fcb0 *parent;
        while (m_00 == (parent = m_00->m_04)->m_08) m_00 = parent;
        if (m_00->m_08 != parent) m_00 = parent;
    }
}

void SBFontConstructValue(SBFontValue0061f120 *destination, const SBFontValue0061f120 &source)
{
    new (destination) SBFontValue0061f120(source);
}
