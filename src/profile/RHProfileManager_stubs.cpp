#include "SBNullstr.h"
#include "RHProfileManager.h"
#include "RHMissionProfile.h"
#include "RHActorProfiles.h"
#include "RHProfileFile.h"
#include <algorithm>

// TEMPLATE: GAME 0x00401ee0 FOLDED
// ?_Tidy@?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@AAEX_N@Z

// TEMPLATE: GAME 0x00401ee0 FOLDED
// ?FUN_00401ee0@RHProfileText@@QAEX_N@Z
void RHProfileText::FUN_00401ee0(bool release)
{
    if (release && m_chars != 0)
    {
        unsigned char *reference = (unsigned char *)m_chars - 1;
        if (*reference != 0 && *reference != 255)
            --*reference;
        else
            operator delete(reference);
    }
    m_chars = 0;
    m_size = 0;
    m_capacity = 0;
}

// FUNCTION: GAME 0x0059fba0
RHProfileString::RHProfileString(const std::allocator<char> &allocator) : std::basic_string<char>(allocator) {}
void RHProfileText::FUN_00401ce0(const std::string &, unsigned int, unsigned int) {}


void FUN_0056cf40(const RHProfileManager *, const char *, ...) {}



bool RHProfileText::FUN_00402280(unsigned int, bool) { return false; }
RHProfileText operator+(const RHProfileText &, const RHProfileText &) { return RHProfileText(); }
RHProfileFile::RHProfileFile() {}
RHProfileFile::~RHProfileFile() {}
int RHProfileFile::FUN_005f5090(const RHProfileText &, int) { return -1; }
