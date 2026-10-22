#include "SBNullstr.h"
#include "SBPicture.h"
#include "../common/SBGeoVector2D.h"

// FUNCTION: GAME 0x00611b90
SBPicture::SBPicture()
{
    m_04 = 0xffff;
    m_14 = 0;
    m_1c = 0;
    ((SBGeoVector2D *)m_28)->SBGeoVector2D::SBGeoVector2D();
    *(unsigned int *)(m_pad08 + 8) = 0;
    *(unsigned short *)(m_pad08 + 4) = 0;
    *(unsigned short *)(m_pad08 + 2) = 0;
    *(unsigned short *)m_pad08 = 0;
    *(unsigned *)m_pad0 = 0x67a8bc;
}

class SBPictureUnkView
{
public:
    SBPictureUnkView();
    ~SBPictureUnkView();
};

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
