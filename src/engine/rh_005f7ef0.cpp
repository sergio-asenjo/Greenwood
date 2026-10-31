// Anonymous cluster at 0x005f7c3x-0x005f7f1x (release log stream holder).
// No __FILE__ or oracle evidence: class and method identity are unproven.

#include "SBNullstr.h"
#include <windows.h>
#include <string>
#include "rh_005f7ff0.h"

extern "C" BZFILE *__stdcall BZ2_bzopen(const char *path, const char *mode);
extern "C" void __stdcall BZ2_bzclose(BZFILE *b);

// FUNCTION: GAME 0x005f7c30
std::string FUN_005f7c30()
{
    // GLOBAL: GAME 0x006c13f0
    static std::string directory;
    if (directory.size() == 0)
    {
        char buffer[256];
        GetCurrentDirectoryA(sizeof(buffer), buffer);
        directory = buffer;
    }
    return directory;
}

// LIBRARY: GAME 0x005f7d80
// $E15

// TEMPLATE: GAME 0x004e4c70
// ??Hstd@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@0@ABV10@PBD@Z

// GLOBAL: GAME 0x006c1400
RHUnk005f7ff0 g_unk0x006c1400;

// FUNCTION: GAME 0x005f7e10
RHUnk005f7ff0::RHUnk005f7ff0()
{
    m_0 = BZ2_bzopen((FUN_005f7c30() +
                      // STRING: GAME 0x006ba018
                      "\\Data\\Configuration\\release.log").c_str(),
        "wb");
}

// FUNCTION: GAME 0x005f7ef0
RHUnk005f7ff0::~RHUnk005f7ff0()
{
    if (m_0)
        BZ2_bzclose(m_0);
    m_0 = 0;
}

// FUNCTION: GAME 0x005f7f10
void RHUnk005f7ff0::FUN_005f7f10()
{
    if (m_0)
        BZ2_bzclose(m_0);
    m_0 = BZ2_bzopen((FUN_005f7c30() + "\\Data\\Configuration\\release.log").c_str(), "ab");
}
