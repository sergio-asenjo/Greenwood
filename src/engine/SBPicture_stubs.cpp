#include "SBNullstr.h"
#include "../common/SBGeoVector2D.h"
#include "SBPicture.h"

// FUNCTION: GAME 0x00611b90
SBPicture::SBPicture() : m_04(0xffff), m_14(0), m_1c(0)
{
    *(unsigned int *)(m_pad08 + 8) = 0;
    *(unsigned short *)(m_pad08 + 4) = 0;
    *(unsigned short *)(m_pad08 + 2) = 0;
    *(unsigned short *)m_pad08 = 0;
}

bool SBPicture::LoadFromFile(const std::string &)
{
    return false;
}

bool SBPicture::LoadFromStream(SBFile &)
{
    return false;
}

bool SBPicture::SaveToFile(const std::string &)
{
    return false;
}

bool SBPicture::SaveToStream(SBFile &)
{
    return false;
}
