#include "RHFontManager.h"

// Parked: frame 0xcc versus 0xd8 and map-result temporary layout.
// STUB: GAME 0x00502500
void RHFontManager::LoadConfiguration(const std::string &name)
{
    RHUnk005f4fc0 file;
    if (file.FUN_005f5090(name, 1) != 0)
    {
        SBAssert(0,
                 // STRING: GAME 0x006affac
                 "P:\\Robin Hood\\RHFontManager.cpp", 0x134,
                 // STRING: GAME 0x006affcc
                 "RHFontManager : unable to open the specified file : '%s'\n", ((SBString *)&name)->m_chars ? ((SBString *)&name)->m_chars : "");
        return;
    }
    FILE *stream = *(FILE **)&file;
    while (!feof(stream) && !ferror(stream))
    {
        std::string key;
        Fonts *fonts = new Fonts;
        key = Get(stream, ':');
        TrimString((std::string &)key);
        fgetc(stream);
        fonts->m_00 = Get(stream, ',');
        TrimString((std::string &)fonts->m_00);
        fgetc(stream);
        fonts->m_10 = Get(stream, 0);
        TrimString((std::string &)fonts->m_10);
        m_fonts[(const std::string &)key] = fonts;
    }
}

void RHFontManager::Emit(const std::string &name)
{
    LoadConfiguration(name);
}
