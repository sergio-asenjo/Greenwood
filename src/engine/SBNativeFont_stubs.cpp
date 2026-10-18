#include "SBNativeFont.h"

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

// FUNCTION: GAME 0x006090a0
bool SBGeoBoundingBox2D::FUN_006090a0() const
{
    if (m_10)
        return m_00 <= m_08 && m_04 <= m_0c;
    return true;
}

// FUNCTION: GAME 0x00617e20
SBResourceUnkKeyIterator SBNativeFontCharacterTree::FUN_00617e20(const unsigned short &character)
{
    return SBResourceUnkKeyIterator(FUN_00618280(character));
}

SBResourceUnkKeyNode *SBNativeFontCharacterTree::FUN_00618280(const unsigned short &) { return 0; }
