#ifndef SB_UI_INPUT_FIELD_TEXT_H
#define SB_UI_INPUT_FIELD_TEXT_H

#include "SBUIInputFieldCharacters.h"
#include <string>

#ifndef SBGEO_BOUNDINGBOX2D_VIEW
#include "SBGeoBoundingBox2DCore.h"
#endif

// VTABLE: GAME 0x0067ae2c
// SIZE 0x48
class RHPortraitText0061db10
{
public:
    RHPortraitText0061db10();
    virtual ~RHPortraitText0061db10(); // vtable+0x00
    bool Insert(unsigned short character);
    void FUN_0061e240(unsigned int direction);
    SBUIInputFieldCharacters m_characters; // 0x04
    SBUIInputFieldCharacters::iterator m_cursor; // 0x10
    void *m_font; // 0x14
    void *m_alternate; // 0x18
    bool m_caretShown; // 0x1c
    unsigned int m_maximum; // 0x20
    SBGeoBoundingBox2D m_bounds; // 0x24
    std::wstring m_saved; // 0x38
};

#endif
