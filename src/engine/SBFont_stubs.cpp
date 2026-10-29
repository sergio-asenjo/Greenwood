#include "SBNullstr.h"
#include "SBFont.h"

void FUN_005f8030(int, const char *, int, const char *, ...) {}

// FUNCTION: GAME 0x00620c70
SBFontNode0061fcb0 *SBFontTree0061fcb0::FUN_00620c70(SBFontNode0061fcb0 *parent, int color)
{
    SBFontNode0061fcb0 *node = (SBFontNode0061fcb0 *)operator new(sizeof(SBFontNode0061fcb0));
    node->m_04 = parent;
    node->m_10 = color;
    return node;
}
// FUNCTION: GAME 0x00620c90
SBFontUnk00620c90 *SBFontUnk00620c90::FUN_00620c90(int value)
{
    *(int *)this = value;
    return this;
}

void EmitSBFontUnk00620c90(SBFontUnk00620c90 *a)
{
    a->FUN_00620c90(0);
}

// FUNCTION: GAME 0x00620d60
SBFontNode0061fcb0 *SBFontTree0061fcb0::FUN_00620d60(SBFontNode0061fcb0 *source, SBFontNode0061fcb0 *parent)
{
    SBFontLock lock;
    SBFontNode0061fcb0 *result = source;
    for (; source != g_unk0x006c191c; source = source->m_00) {
        int color = source->m_10;
        SBFontNode0061fcb0 *node = (SBFontNode0061fcb0 *)operator new(sizeof(SBFontNode0061fcb0));
        node->m_04 = parent;
        node->m_10 = color;
        if (result == source) result = node;
        node->m_08 = FUN_00620d60(source->m_08, node);
        std::_Construct(&node->m_0c, source->m_0c);
        parent->m_00 = node;
        parent = node;
    }
    parent->m_00 = g_unk0x006c191c;
    return result;
}

void SBFontConstructValue(SBFontValue0061f120 *destination, const SBFontValue0061f120 &source)
{
    new (destination) SBFontValue0061f120(source);
}

// FUNCTION: GAME 0x006211e0
SBFontNode0061fcb0 *SBFontTree0061fcb0::Maximum(SBFontNode0061fcb0 *node)
{
    SBFontLock lock;
    while (node->m_08 != g_unk0x006c191c)
        node = node->m_08;
    return node;
}
