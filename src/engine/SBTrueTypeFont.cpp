#include "SBTrueTypeFont.h"
#include "SB.h"
#include <string.h>

DECOMP_SIZE_ASSERT(SBTrueTypeFont, 0x70)

// Parked: the device-context load uses ECX instead of the target EDX.
// STUB: GAME 0x00616840
long SBTrueTypeFont::GetCharacterWidth(unsigned short character, long &left, long &right) const
{
    unsigned long code = character;
    left = 0;
    right = 0;
    return FUN_00616870(m_deviceContext, code);
}

// FUNCTION: GAME 0x006168e0
unsigned SBTrueTypeFont::FUN_006168e0() const
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
    font->FUN_006168e0();
    font->GetCharacterWidth(0, spacing, spacing);
    font->GetImplementationTag(tag);
    font->LoadFromStream(file);
    font->SaveToStream(file);
}
