#include "SBTrueTypeFont.h"
#include "SB.h"
#include <string.h>

DECOMP_SIZE_ASSERT(SBTrueTypeFont, 0x70)

// FUNCTION: GAME 0x006166c0
void *SBTrueTypeFont::FUN_006166c0(unsigned flags)
{
    this->SBTrueTypeFont::~SBTrueTypeFont();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x006166e0
SBTrueTypeFont::SBTrueTypeFont(const std::string &name)
{
    m_font = 0;
    m_deviceContext = 0;
    ((SBFontUnk0061e840 *)this)->FUN_0061ea80(name);
    CreateSystemObjects();
}

// FUNCTION: GAME 0x00616740
SBTrueTypeFont::~SBTrueTypeFont()
{
    DestroySystemObjects();
}

// FUNCTION: GAME 0x00616840
long SBTrueTypeFont::GetCharacterWidth(unsigned short character, long &left, long &right) const
{
    unsigned long code = character;
    left = 0;
    right = 0;
    return FUN_00616870(m_deviceContext, code);
}

// FUNCTION: GAME 0x006168e0
unsigned SBTrueTypeFont::GetImplementationVersion() const
{
    return 0x100;
}

// FUNCTION: GAME 0x006168f0
void SBTrueTypeFont::GetImplementationTag(char (&tag)[6]) const
{
    char value[6] = {'S', 'B', 'T', 'T', 'F', 'T'};
    memcpy(tag, value, sizeof(value));
}

// FUNCTION: GAME 0x00616930
bool SBTrueTypeFont::LoadFromStream(SBFile &file)
{
    bool loaded = ((SBFontUnk0061e840 *)this)->FUN_0061eb00(file);
    if (!loaded)
        return loaded;
    file.Access((char *)this + 0x44, 0x24);
    return true;
}

// FUNCTION: GAME 0x00616b90
bool SBTrueTypeFont::SaveToStream(SBFile &file)
{
    bool saved = ((SBFontUnk0061e840 *)this)->FUN_0061ed70(file);
    if (!saved)
        return saved;
    file.Access((char *)this + 0x44, 0x24);
    return true;
}

void EmitSBTrueTypeFont(SBTrueTypeFont *font, SBFile &file, char (&tag)[6], long &spacing)
{
    new SBTrueTypeFont(std::string());
    font->~SBTrueTypeFont();
    font->SBTrueTypeFont::GetImplementationVersion();
    font->GetCharacterWidth(0, spacing, spacing);
    font->GetBaseLine();
    font->GetImplementationTag(tag);
    font->LoadFromStream(file);
    font->SaveToStream(file);
}
