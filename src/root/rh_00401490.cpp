// Anonymous cluster at 0x00401490.
// No __FILE__ or oracle evidence: class and method identity are unproven.
// Member offsets are exact from Game.exe.

#include "RHUnk00401490.h"
#include "RHSaveGame.h"
#include <algorithm>
#include <string.h>

namespace std
{
    template <> inline RHUnk00401490Table::iterator RHUnk00401490Table::erase(iterator first, iterator last)
    {
        iterator remaining = copy(last, end(), first);
        iterator limit = end();
        for (iterator row = remaining; row != limit; ++row)
            ((RHUnk00402d60 *)row)->FUN_00402d60(0);
        _Last = remaining;
        return first;
    }
}

// FUNCTION: GAME 0x00401490
RHUnk00401490::RHUnk00401490()
{
    m_vptr = 0x6773d4;
}

// FUNCTION: GAME 0x004014b0
void *RHUnk00401490::FUN_004014b0(unsigned flags)
{
    this->RHUnk00401490::~RHUnk00401490();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x004014d0
RHUnk00401490::~RHUnk00401490()
{
    m_vptr = 0x6773d4;
}

// Parked at 0.5014: string construction, cleanup boundaries and frame layout differ.
// STUB: GAME 0x00401550
void RHUnk00401490::FUN_00401550(const char *name)
{
    RHUnk005f4fc0 file;
    std::string line;
    if (file.FUN_005f5090(std::string(name), 1) != 0)
    {
        // STRING: GAME 0x006a6b8c
        throw std::string("Csv file not found");
    }
    for (;;)
    {
        unsigned length = 0;
        if (!(unsigned char)file.FUN_005f6220(line) && line.empty())
            break;
        std::vector<std::string> row;
        const char *text = line.c_str();
        char token[0x50];
        for (unsigned column = 0; column < strlen(text); ++column)
        {
            switch (text[column])
            {
            case '\n':
            case '\r':
                break;
            case ',':
            case ';':
                token[length] = 0;
                length = 0;
                row.insert(row.end(), 1, std::string(token));
                break;
            default:
                token[length++] = text[column];
                break;
            }
        }
        if (length > 0)
        {
            token[length] = 0;
            row.insert(row.end(), 1, std::string(token));
        }
        m_4.insert(m_4.end(), 1, row);
    }
    file.FUN_005f5290();
}

static inline bool RHUnk00401490RemoveRow(const std::vector<std::string> &row)
{
    return (unsigned char)FUN_00401aa0(row) != 0;
}

// FUNCTION: GAME 0x00401b10
void RHUnk00401490::FUN_00401b10()
{
    RHUnk00401490Table::iterator last = std::remove_if(m_4.begin(), m_4.end(), RHUnk00401490RemoveRow);
    m_4.resize(last - m_4.begin());
}
