#ifndef RHPCSTATUS_H
#define RHPCSTATUS_H

#include "RHHumanStatus.h"
#include "Decomp.h"
#include <string>
#include <vector>

class RHMapWideText;

// SIZE 0x38
class RHCharacterProfile
{
public:
    undefined m_00[0x18]; // 0x00
    char *m_18; // [0x18]
    undefined m_1c[0x19]; // 0x1c
    char m_35; // [0x35]
};

// SIZE 0x144
class RHUnk00452030
{
public:
    bool FUN_004565c0(const std::wstring &name);
    void FUN_00456670(const std::wstring &name);
    undefined m_00[0x134]; // 0x00
    std::vector<std::wstring> m_134; // 0x134
};

// SIZE 0x40
class RHPCStatus : public RHHumanStatus
{
public:
    static std::wstring GenerateName(const RHCharacterProfile &profile);
    virtual bool Serialize(SBFile &file); // vtable+0x00
    void Emit(SBFile &file, const RHCharacterProfile &profile);

    unsigned short m_14; // [0x14]
    char m_16; // [0x16]
    undefined m_17; // 0x17
    unsigned short m_18; // [0x18]
    unsigned short m_1a; // [0x1a]
    unsigned short m_1c; // [0x1c]
    unsigned short m_1e; // [0x1e]
    unsigned short m_20; // [0x20]
    unsigned short m_22; // [0x22]
    unsigned short m_24; // [0x24]
    unsigned short m_26; // [0x26]
    unsigned short m_28; // [0x28]
    undefined2 m_2a; // 0x2a
    std::wstring m_2c; // [0x2c]
    unsigned short m_3c; // [0x3c]
};

// SIZE 0x10
class RHUnk00423b10
{
public:
    void FUN_00423b10(unsigned int);
    undefined m_allocator; // 0x00
    unsigned short *m_chars; // 0x04
    unsigned int m_size; // 0x08
    unsigned int m_capacity; // 0x0c
};

// SIZE 0x10
class RHPCWideText
{
public:
    void FUN_004239c0(unsigned count);
    bool FUN_004239e0(unsigned count, bool trim);
    RHPCWideText &FUN_0055c680(const std::wstring &text, unsigned first, unsigned count);
    void Tidy(bool built = false)
    {
        if (built && m_chars)
        {
            unsigned char &refs = ((unsigned char *)m_chars)[-1];
            if (refs == 0 || refs == 255)
                operator delete(m_chars - 1);
            else
                --refs;
        }
        m_chars = 0;
        m_size = 0;
        m_capacity = 0;
    }
    void Copy(unsigned count)
    {
        ((RHUnk00423b10 *)this)->FUN_00423b10(count);
    }
    bool Grow(unsigned count)
    {
        if (count > 0x7ffffffd)
            std::_Xlen();
        if (m_chars && ((unsigned char *)m_chars)[-1] != 0 && ((unsigned char *)m_chars)[-1] != 255)
        {
            if (count == 0)
            {
                --((unsigned char *)m_chars)[-1];
                TidyExternal(false);
                return false;
            }
            Copy(count);
            return true;
        }
        if (count == 0)
        {
            if (m_chars)
                m_chars[m_size = count] = 0;
            return false;
        }
        if (m_capacity < count)
            Copy(count);
        return true;
    }
    void TidyExternal(bool built);
    undefined m_allocator; // 0x00
    unsigned short *m_chars; // 0x04
    unsigned m_size; // 0x08
    unsigned m_capacity; // 0x0c
};

// SIZE 0x10
class RHMapWideText
{
public:
    std::allocator<unsigned short> m_allocator; // 0x00
    unsigned short *m_chars; // 0x04
    unsigned m_size; // 0x08
    unsigned m_capacity; // 0x0c
    void Tidy(bool);
    void FUN_004580c0(const std::wstring &text, unsigned first, unsigned count);
};

inline void RHPCWideText::TidyExternal(bool built)
{
    ((RHMapWideText *)this)->Tidy(built);
}

std::wstring FUN_0055bdf0(unsigned long first, unsigned long count);
std::wstring FUN_005e23d0(unsigned long id);
bool FUN_005e0ea0(SBFile &file, std::wstring &value);
extern RHUnk00452030 *g_unk0x6c07fc;

#endif
