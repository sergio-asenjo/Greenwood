#ifndef SB_TRUE_TYPE_FONT_H
#define SB_TRUE_TYPE_FONT_H

#include "SBFont.h"
#include "SBNativeFontBase.h"

class SBGeoPoint2D;
class SBGeoBoundingBox2D;

// VTABLE: GAME 0x0067a940
class SBTrueTypeFont : public SBNativeFontBase
{
public:
    SBTrueTypeFont(const std::string &name);
    ~SBTrueTypeFont();
    void *FUN_006166c0(unsigned flags);
    void CreateSystemObjects();
    void DestroySystemObjects();
    long GetBaseLine() const;
    int FUN_00616870(void *context, unsigned long character) const;
    bool Render(unsigned short character, SBGeoPoint2D &position, const SBGeoBoundingBox2D &bounds, bool measure) const;
    virtual unsigned GetImplementationVersion() const;
    long GetCharacterWidth(unsigned short character, long &left, long &right) const;
    void GetImplementationTag(char (&tag)[6]) const;
    bool LoadFromStream(SBFile &file);
    bool SaveToStream(SBFile &file);
    unsigned char m_trueTypeHeader[0x24];
    void *m_font;
    void *m_deviceContext;
};

#endif
