#include "SBNullstr.h"
#include "RHPCStatus.h"
#include <cstring>
#include <cstdlib>
#include <algorithm>

DECOMP_SIZE_ASSERT(RHCharacterProfile, 0x38)
DECOMP_SIZE_ASSERT(RHUnk00452030, 0x144)
DECOMP_SIZE_ASSERT(RHPCStatus, 0x40)
DECOMP_SIZE_ASSERT(RHUnk00423b10, 0x10)
DECOMP_SIZE_ASSERT(RHPCWideText, 0x10)
DECOMP_SIZE_ASSERT(RHMapWideText, 0x10)

void (RHPCWideText::*g_rhpcWideEos)(unsigned) = &RHPCWideText::FUN_004239c0;
RHPCWideText &(RHPCWideText::*g_rhpcWideAppend)(const std::wstring &, unsigned, unsigned) = &RHPCWideText::FUN_0055c680;

void RHPCStatus::Emit(SBFile &file, const RHCharacterProfile &profile)
{
    GenerateName(profile);
    Serialize(file);
}

// FUNCTION: GAME 0x00419940
// wmemcpy

// deferred: unannotated pending reccmp #534.
void RHPCWideText::FUN_004239c0(unsigned count)
{
    m_chars[m_size = count] = 0;
}

// parked: unannotated because GenerateName calls this helper.
bool RHPCWideText::FUN_004239e0(unsigned count, bool trim)
{
    if (count > 0x7ffffffd)
        std::_Xlen();
    if (m_chars && ((unsigned char *)m_chars)[-1] != 0 && ((unsigned char *)m_chars)[-1] != 255)
    {
        if (count == 0)
        {
            --((unsigned char *)m_chars)[-1];
            Tidy();
            return false;
        }
        Copy(count);
        return true;
    }
    if (count == 0)
    {
        if (trim)
            Tidy(true);
        else if (m_chars)
            m_chars[m_size = 0] = 0;
        return false;
    }
    if (trim && (31 < m_capacity || m_capacity < count))
    {
        Tidy(true);
        Copy(count);
    }
    else if (!trim && m_capacity < count)
        Copy(count);
    return true;
}

// FUNCTION: GAME 0x004565c0
bool RHUnk00452030::FUN_004565c0(const std::wstring &name)
{
    return std::find(m_134.begin(), m_134.end(), name) != m_134.end();
}

// FUNCTION: GAME 0x00456670
void RHUnk00452030::FUN_00456670(const std::wstring &name)
{
    std::vector<std::wstring> &values = m_134;
    std::vector<std::wstring>::iterator last = values.end();
    values.insert(last, name);
}

// parked: unannotated because GenerateName and DisplayLostLeicester call this helper.
void RHMapWideText::FUN_004580c0(const std::wstring &text, unsigned first, unsigned count)
{
    RHPCWideText &value = *(RHPCWideText *)this;
    if (text.size() < first)
        std::_Xran();
    unsigned length = text.size() - first;
    if (count < length)
        length = count;
    if ((const void *)this == (const void *)&text)
    {
        std::wstring &self = *(std::wstring *)this;
        self.erase(first + length);
        self.erase(0, first);
    }
    else if (length > 0 && length == text.size() && ((const unsigned char *)text.c_str())[-1] < 254)
    {
        value.Tidy(true);
        m_chars = (unsigned short *)text.c_str();
        m_size = text.size();
        m_capacity = text.capacity();
        ++((unsigned char *)m_chars)[-1];
    }
    else if (value.FUN_004239e0(length, true))
    {
        std::char_traits<unsigned short>::copy(m_chars, text.c_str() + first, length);
        m_chars[m_size = length] = 0;
    }
}

// FUNCTION: GAME 0x0055bdf0
std::wstring FUN_0055bdf0(unsigned long first, unsigned long count)
{
    std::wstring name;
    name = FUN_005e23d0((unsigned)rand() % count + first);
    return name;
}

// FUNCTION: GAME 0x0055bf00
std::wstring RHPCStatus::GenerateName(const RHCharacterProfile &profile)
{
    std::wstring name;
    if (profile.m_35 == 1)
    {
        const char *names[] = {
            // STRING: GAME 0x006ab9a0
            "Robin des bois",
            // STRING: GAME 0x006abb98
            "Robin des villes",
            // STRING: GAME 0x006ab970
            "Will Ecarlate",
            // STRING: GAME 0x006ab994
            "Petit Jean",
            // STRING: GAME 0x006ab988
            "Frere Tuck",
            // STRING: GAME 0x006ab960
            "Lady Marianne",
            // STRING: GAME 0x006ab980
            "Stutely"
        };
        unsigned int i;
        for (i = 0; i < sizeof(names); ++i)
        {
            if (_stricmp(names[i], profile.m_18 ? profile.m_18 : "") == 0)
            {
                name = FUN_005e23d0(i + 0x90);
                break;
            }
        }
        if (i == sizeof(names))
        {
            SBAssert(0,
                // STRING: GAME 0x006b1744
                "P:\\Robin Hood\\RHPCStatus.cpp", 0xd4,
                // STRING: GAME 0x006b1764
                "RHPCStatus : unable to retrive the right VIP name for the profile '%s'",
                profile.m_18 ? profile.m_18 : "");
            // STRING: GAME 0x006b1728
            name = L"Super Star !";
        }
    }
    else
    {
        RHUnk00452030 *campaign = g_unk0x6c07fc;
        int remaining = 10;
        while (remaining != 0)
        {
            name = FUN_0055bdf0(100, 22);
            // STRING: GAME 0x006b1724
            name += L" " + FUN_0055bdf0(122, 22);
            if (!campaign->FUN_004565c0(name))
            {
                campaign->FUN_00456670(name);
                break;
            }
            --remaining;
        }
        if (remaining == 0)
        {
            SBAssert(0, "P:\\Robin Hood\\RHPCStatus.cpp", 0xf9,
                // STRING: GAME 0x006b16f8
                "PCStatus : unable to build a new PC name.");
            // STRING: GAME 0x006b16e0
            name = L"Misteryman";
        }
    }
    return name;
}

// FUNCTION: GAME 0x0055c3c0
bool RHPCStatus::Serialize(SBFile &file)
{
    if (!RHHumanStatus::Serialize(file))
        return false;
    // STRING: GAME 0x006b17ac
    RHSerializeName(file, "RHPCStatus");
    if (file.Access(&m_14, 2) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0,
            // STRING: GAME 0x006b16c0
            "P:\\Robin Hood\\RHPCStatus.cpp", 0x1b0, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_16, 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHPCStatus.cpp", 0x1b1, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_18, 2) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHPCStatus.cpp", 0x1b2, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_1c, 2) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHPCStatus.cpp", 0x1b3, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_1a, 2) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHPCStatus.cpp", 0x1b4, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_24, 2) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHPCStatus.cpp", 0x1b5, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_26, 2) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHPCStatus.cpp", 0x1b6, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_28, 2) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHPCStatus.cpp", 0x1b7, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_1e, 2) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHPCStatus.cpp", 0x1b8, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_20, 2) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHPCStatus.cpp", 0x1b9, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_22, 2) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHPCStatus.cpp", 0x1ba, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_3c, 2) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHPCStatus.cpp", 0x1bb, "Serialize failed reason is %s", reason);
        return false;
    }
    FUN_005e0ea0(file, m_2c);
    return true;
}

// TEMPLATE: GAME 0x0055c680
// ?append@?$basic_string@GU?$char_traits@G@std@@V?$allocator@G@2@@std@@QAEAAV12@ABV12@II@Z

RHPCWideText &RHPCWideText::FUN_0055c680(const std::wstring &text, unsigned first, unsigned count)
{
    if (text.size() < first)
        std::_Xran();
    unsigned length = text.size() - first;
    if (length < count)
        count = length;
    if (std::wstring::npos - m_size <= count)
        std::_Xlen();
    if (count > 0 && Grow(length = m_size + count))
    {
        std::char_traits<unsigned short>::copy(m_chars + m_size, text.c_str() + first, count);
        m_chars[m_size = length] = 0;
    }
    return *this;
}

// TEMPLATE: GAME 0x0055c770
// ??Hstd@@YA?AV?$basic_string@GU?$char_traits@G@std@@V?$allocator@G@2@@0@PBGABV10@@Z
