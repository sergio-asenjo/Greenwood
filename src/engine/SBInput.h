#ifndef SB_INPUT_H
#define SB_INPUT_H

#include <string>

struct SBInputUnkDevice;

struct SBInputUnkDeviceTable
{
    void *m_00[2];
    unsigned long (__stdcall *m_08)(SBInputUnkDevice *);
    void *m_0c[4];
    long (__stdcall *m_1c)(SBInputUnkDevice *);
    long (__stdcall *m_20)(SBInputUnkDevice *);
    long (__stdcall *m_24)(SBInputUnkDevice *, unsigned long, void *);
    void *m_28[2];
    long (__stdcall *m_30)(SBInputUnkDevice *, void *);
    void *m_34[12];
    long (__stdcall *m_64)(SBInputUnkDevice *);
};

struct SBInputUnkDevice
{
    SBInputUnkDeviceTable *m_table;
};

class SBInputUnk005fb730
{
public:
    char m_00[8];
    SBInputUnkDevice *m_08;
    SBInputUnkDevice *m_0c;
    char m_10[0x134];
    SBInputUnkDevice *m_144[16];
    char m_184[0x121];
    unsigned char m_2a5;
    unsigned char m_2a6;
    unsigned char m_2a7;
    char m_2a8[2];
    unsigned char m_2aa;
    char m_2ab;
    std::string m_2ac;

    void FUN_005fae70(void *);
    bool FUN_005fb730(unsigned char);
    bool FUN_005fb770(unsigned char, void *, int);
    bool FUN_005fb980(void *);
    bool FUN_005fba70(void *);
    bool FUN_005fbfc0();
};

int __stdcall FUN_005fae50(void *, SBInputUnk005fb730 *);
std::string FUN_005f81d0(long);

#endif
