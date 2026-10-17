#include "SBNativeFont.h"

SBNativeFontBase::SBNativeFontBase() {}
SBNativeFontBase::~SBNativeFontBase() {}

class SBGeoBoundingBox2D
{
public:
    bool FUN_006090a0() const;
    float m_00;
    float m_04;
    float m_08;
    float m_0c;
    bool m_10;
};

// Parked: VC6 lays the `!m_10` return-true block inline; the target jumps to it
// at the end (je). All comparisons and the shared false block match. 0.842105.
// STUB: GAME 0x006090a0
bool SBGeoBoundingBox2D::FUN_006090a0() const
{
    if (!m_10)
        return true;
    return m_00 <= m_08 && m_04 <= m_0c;
}

SBResourceUnkKeyIterator SBNativeFontCharacterTree::FUN_00617e20(const unsigned short &)
{
    return SBResourceUnkKeyIterator(0);
}

SBResourceUnkKeyNode *SBNativeFontCharacterTree::FUN_00618280(const unsigned short &) { return 0; }

SBNativeFontCharacterPair SBNativeFontCharacterTree::FUN_006177d0(const SBNativeFontCharacterValue &)
{
    SBNativeFontCharacterPair result;
    result.m_iterator.m_node = 0;
    result.m_inserted = false;
    return result;
}

void SBNativeFontCharacterIterator::FUN_00617ed0() {}

SBResourceUnkKeyIterator SBNativeFontCharacterTree::FUN_006176a0(
    SBResourceUnkKeyIterator first, SBResourceUnkKeyIterator)
{
    return first;
}
