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

#include "SBPictureUnkView.h"

class SBPictureUnkDrawManager
{
public:
    bool Unk005e5a00(unsigned long, SBPictureUnkView &, unsigned long);
    void Unk005e5ea0(SBPictureUnkView &);
};

SBPictureUnkView::SBPictureUnkView() {}
SBPictureUnkView::~SBPictureUnkView() {}
bool SBPictureUnkDrawManager::Unk005e5a00(unsigned long, SBPictureUnkView &, unsigned long) { return false; }
void SBPictureUnkDrawManager::Unk005e5ea0(SBPictureUnkView &) {}
