#ifndef RHPCSTATUSCORE_H
#define RHPCSTATUSCORE_H

#include "RHHumanStatus.h"
#include "Decomp.h"
#include <string>

class RHCharacterProfile;

// SIZE 0x40
class __declspec(novtable) RHPCStatus : public RHHumanStatus
{
public:
    RHPCStatus();
    unsigned short *GetAmmoCounter(int action);
    void SetAmmoAmount(int action, unsigned short amount);
    static std::wstring GenerateName(const RHCharacterProfile &profile);
    void FUN_0055c390();
    virtual bool Serialize(SBFile &file); // vtable+0x00
    void Emit(SBFile &file, const RHCharacterProfile &profile);

    unsigned short m_14; // 0x14
    char m_16; // 0x16
    undefined m_17; // 0x17
    unsigned short m_18; // 0x18
    unsigned short m_1a; // 0x1a
    unsigned short m_1c; // 0x1c
    unsigned short m_1e; // 0x1e
    unsigned short m_20; // 0x20
    unsigned short m_22; // 0x22
    unsigned short m_24; // 0x24
    unsigned short m_26; // 0x26
    unsigned short m_28; // 0x28
    undefined2 m_2a; // 0x2a
    std::wstring m_2c; // 0x2c
    unsigned short m_3c; // 0x3c
};

#endif
