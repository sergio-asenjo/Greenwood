#ifndef RHPCSTATUS_H
#define RHPCSTATUS_H

#include "RHHumanStatus.h"
#include <string>

class RHCharacterProfile
{
public:
    char m_00[0x18];
    char *m_18; // [0x18]
    char m_1c[0x19];
    char m_35; // [0x35]
};

class RHUnk00452030
{
public:
    bool FUN_004565c0(const std::wstring &name);
    void FUN_00456670(const std::wstring &name);
};

class RHPCStatus : public RHHumanStatus
{
public:
    static std::wstring GenerateName(const RHCharacterProfile &profile);
    virtual bool Serialize(SBFile &file);
    void Emit(SBFile &file, const RHCharacterProfile &profile);

    unsigned short m_14; // [0x14]
    char m_16; // [0x16]
    char m_17;
    unsigned short m_18; // [0x18]
    unsigned short m_1a; // [0x1a]
    unsigned short m_1c; // [0x1c]
    unsigned short m_1e; // [0x1e]
    unsigned short m_20; // [0x20]
    unsigned short m_22; // [0x22]
    unsigned short m_24; // [0x24]
    unsigned short m_26; // [0x26]
    unsigned short m_28; // [0x28]
    unsigned short m_2a;
    std::wstring m_2c; // [0x2c]
    unsigned short m_3c; // [0x3c]
};

std::wstring FUN_0055bdf0(unsigned long first, unsigned long count);
std::wstring FUN_005e23d0(unsigned long id);
void FUN_005e0ea0(SBFile &file, std::wstring &value);
extern RHUnk00452030 *g_unk0x6c07fc;

#endif
