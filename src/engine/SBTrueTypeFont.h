#ifndef SB_TRUE_TYPE_FONT_H
#define SB_TRUE_TYPE_FONT_H

#include "SBFont.h"

int __stdcall FUN_00616870(void *, unsigned long);

class SBTrueTypeFont
{
public:
    unsigned FUN_006168e0() const;
    long GetCharacterWidth(unsigned short character, long &left, long &right) const;
    void GetImplementationTag(char (&tag)[6]) const;
    bool LoadFromStream(SBFile &file);
    bool SaveToStream(SBFile &file);
    unsigned char m_00[0x68];
    void *m_font;
    void *m_deviceContext;
};

#endif
