#include "SBNativeFont.h"

SBNativeFontBase::SBNativeFontBase() {}
SBNativeFontBase::~SBNativeFontBase() {}

class SBGeoBoundingBox2D
{
public:
    bool FUN_006090a0() const;
};

bool SBGeoBoundingBox2D::FUN_006090a0() const { return false; }

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
