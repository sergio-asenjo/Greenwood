#ifndef RHPCSTATUS_H
#define RHPCSTATUS_H

#include "RHHumanStatus.h"
#include "RHPCStatusCore.h"
#include "Decomp.h"
#include <string>
#include <vector>

class RHMapWideText;

// SIZE 0x9c
class RHCharacterProfile
{
public:
    undefined m_00[0x18]; // 0x00
    char *m_18; // [0x18]
    undefined m_1c[0x19]; // 0x1c
    char m_35; // [0x35]
    undefined m_36[0x12]; // 0x36
    int m_48[3]; // 0x48
    unsigned short m_54[3]; // 0x54
    undefined m_5a[0x42]; // 0x5a
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

#include "RHMapWideText.h"

inline void RHPCWideText::TidyExternal(bool built)
{
    ((RHMapWideText *)this)->Tidy(built);
}

std::wstring FUN_0055bdf0(unsigned long first, unsigned long count);
std::wstring FUN_005e23d0(unsigned long id);
bool FUN_005e0ea0(SBFile &file, std::wstring &value);
extern RHUnk00452030 *g_unk0x6c07fc;

#endif
