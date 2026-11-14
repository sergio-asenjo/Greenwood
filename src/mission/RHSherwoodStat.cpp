#include "SBNullstr.h"
#include "RHSherwoodStat.h"
#include "RHSectorProduction.h"
#include "RHCampaignCore.h"
#include "RHCampaignValueCalls.h"
#include "RHPlayerProfileAccess.h"
#include "RHPlayerProfileManagerStorage.h"

extern template class std::basic_string<unsigned short>;

DECOMP_SIZE_ASSERT(RHSherwoodStat, 0x04)
DECOMP_SIZE_ASSERT(std::string, 0x10)
DECOMP_SIZE_ASSERT(std::wstring, 0x10)
DECOMP_SIZE_ASSERT(RHSectorProduction, 0x34)

extern RHUnk00452030 *g_unk0x6c07fc;
std::wstring FUN_005e23d0(unsigned long id);
std::wstring FUN_005e2bf0(int value);
extern "C" int __cdecl wsprintfW(unsigned short *buffer, const unsigned short *format, ...);

// STUB: GAME 0x005a1370
std::wstring RHSherwoodStat::GetAmmoText(const RHSectorProduction *sector)
{
    unsigned long id;
    *(volatile unsigned long *)&id = 0;
    wchar_t buffer[512];
    switch (sector->GetType())
    {
    case 0: id = 0x59; break;
    case 1: id = 0x61; break;
    case 2: id = 0x5e; break;
    case 3: id = 0x5a; break;
    case 4: id = 0x5f; break;
    case 5: id = 0x5c; break;
    case 6: id = 0x5d; break;
    case 7: id = 0x60; break;
    case 8: id = 0x5b; break;
    }
    wsprintfW(buffer, FUN_005e23d0(id).c_str(), sector->FUN_005806b0());
    return std::wstring(buffer);
}

// FUNCTION: GAME 0x005a1550
void RHSherwoodStat::GetProductionText(const RHSectorProduction *sector, std::wstring &text)
{
    wchar_t buffer[512];
    if (sector->FUN_005806b0())
    {
        unsigned count = sector->FUN_00580500();
        RHPCDescription *character = sector->FUN_005806c0();
        text += GetAmmoText(sector);
        if (count >= 1)
        {
            unsigned suffix = count == 1 ? 0x62 : 0x63;
            wsprintfW(buffer,
                      // STRING: GAME 0x006b7794
                      L" %s %i %s", FUN_005e23d0(0x56).c_str(), count,
                      FUN_005e23d0(suffix).c_str());
            text += buffer;
        }
        if (character && count > 1)
        {
            wsprintfW(buffer, FUN_005e23d0(0x57).c_str(),
                      reinterpret_cast<const std::wstring *>(reinterpret_cast<const char *>(character) + 0x2c)->c_str());
            text += buffer;
        }
        if (sector->FUN_00580960())
        {
            text += L" ";
            text += FUN_005e23d0(0x47).c_str();
        }
        // STRING: GAME 0x006b778c
        text += L".\n";
    }
}

// FUNCTION: GAME 0x005a1900
void RHSherwoodStat::GetScoreText(std::wstring &text)
{
    wchar_t buffer[512];
    const char *profile = reinterpret_cast<RHUnk0055dbb0 *>(g_unk0x006c0e48)->FUN_0055dbb0();
    unsigned first = *reinterpret_cast<const unsigned *>(profile + 0x20);
    wsprintfW(buffer, FUN_005e23d0(0x4f).c_str(), first);
    text += buffer;
    text += L"\n";
    unsigned second = *reinterpret_cast<const unsigned *>(profile + 0x28);
    wsprintfW(buffer, FUN_005e23d0(0x51).c_str(), second);
    text += buffer;
    text += L"\n";
    int third = *reinterpret_cast<const int *>(profile + 0x30);
    wsprintfW(buffer, FUN_005e23d0(0x53).c_str(), FUN_005e2bf0(third).c_str());
    text += buffer;
    text += L"\n";
}

// STUB: GAME 0x005a1c30
std::wstring RHSherwoodStat::GetText() const
{
    std::wstring text;
    std::wstring production;
    RHCampaign *campaign = reinterpret_cast<RHCampaign *>(g_unk0x6c07fc);
    text += FUN_005e23d0(0x48);
    for (unsigned index = 0; index != 13; ++index)
    {
        RHSectorProduction *sector = campaign->FUN_00456a10(index);
        switch (sector->GetType())
        {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
            GetProductionText(sector, production);
            break;
        case 9:
        case 10:
        case 11:
            GetTrainHealText(sector, production);
            break;
        }
    }
    if (production.empty())
    {
        text += L" " + FUN_005e23d0(0x149);
        text += L"\n";
    }
    else
    {
        text += L"\n";
        text += production;
    }
    text += L"\n";
    GetScoreText(text);
    return text;
}

// STUB: GAME 0x005a1f80
void RHSherwoodStat::GetTrainHealText(const RHSectorProduction *sector, std::wstring &text)
{
    wchar_t buffer[512];
    unsigned count = sector->FUN_00580500();
    if (count)
    {
        RHPCDescription *character = sector->FUN_005806c0();
        unsigned id;
        switch (sector->GetType())
        {
        case 9: id = 0x45; break;
        case 10: id = 0x44; break;
        case 11: id = 0x46; break;
        }
        if (character)
            --count;
        wsprintfW(buffer, FUN_005e23d0(id).c_str(), count);
        text += buffer;
        if (character)
        {
            wsprintfW(buffer, FUN_005e23d0(0x57).c_str(),
                      reinterpret_cast<const std::wstring *>(reinterpret_cast<const char *>(character) + 0x2c)->c_str());
            text += L" ";
            text += buffer;
        }
        text += L".\n";
    }
}
