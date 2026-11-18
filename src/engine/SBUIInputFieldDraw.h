#ifndef SB_UI_INPUT_FIELD_DRAW_H
#define SB_UI_INPUT_FIELD_DRAW_H

#include <string>
#include <vector>
#include "Decomp.h"
#ifndef SBGEO_BOUNDINGBOX2D_VIEW
#include "SBGeoBoundingBox2DCore.h"
#endif
#include "RHMapBox.h"

class SBFontUnk0061e840;
class SBGeoPoint2D;
class SBGeoBoundingBox2D;

class SBUIInputFieldDrawUnk
{
public:
    SBUIInputFieldDrawUnk();
    bool FUN_00614bf0(SBFontUnk0061e840 *, std::wstring *, const SBGeoPoint2D &, unsigned int);
    void FUN_00614d70(bool value);
    unsigned short FUN_00614230(SBFontUnk0061e840 *, const std::wstring &, const SBGeoBoundingBox2D &, unsigned int, unsigned short, bool);
    unsigned long FUN_00613940(const SBFontUnk0061e840 *,
        const std::vector<std::wstring>::const_iterator &,
        const std::vector<std::wstring>::const_iterator &,
        std::vector<std::wstring>::const_iterator &,
        std::vector<std::wstring>::const_iterator &, bool &, unsigned long, unsigned long) const;
    void FUN_00613c90(std::vector<std::wstring>::const_iterator,
        std::vector<std::wstring>::const_iterator, std::vector<std::wstring>::const_iterator,
        std::vector<std::wstring>::const_iterator);
    unsigned short FUN_00613ea0(SBFontUnk0061e840 *, const std::wstring *, const SBGeoBoundingBox2D &, unsigned int, unsigned int);
    RHMapBox *FUN_00613e70();
    unsigned int FUN_00613e80();
    std::wstring &FUN_00613e90();
    bool OneWordBiggerThanALine(const SBFontUnk0061e840 *, float, const std::vector<std::wstring> *);
    std::wstring m_00;
    undefined4 m_10;
    bool m_14;
    unsigned int m_18;
    RHMapBox m_1c;
};

#endif
