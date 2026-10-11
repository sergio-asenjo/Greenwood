#include "SBNullstr.h"
#include "SBPicture.h"

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
