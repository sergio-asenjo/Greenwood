#ifndef RHCIVILIANPROFILE_H
#define RHCIVILIANPROFILE_H

#include <string>

class RHProfileText
{
public:
    explicit RHProfileText(const std::allocator<char> &allocator = std::allocator<char>())
    {
        m_allocator = *(const char *)&allocator;
        FUN_00401ee0(false);
    }
    ~RHProfileText() { FUN_00401ee0(true); }
    explicit RHProfileText(const char *value, const std::allocator<char> &allocator = std::allocator<char>())
    {
        m_allocator = *(const char *)&allocator;
        FUN_00401ee0(false);
        unsigned int size = strlen(value);
        if (FUN_00402280(size, true))
        {
            memcpy(m_chars, value, size);
            FUN_00402260(size);
        }
    }
    const char *c_str() const { return m_chars ? m_chars : ""; }
    bool FUN_00402280(unsigned int size, bool trim);
    void FUN_00402260(unsigned int size);
    void FUN_00401ee0(bool release);
    void FUN_00401ce0(const std::string &value, unsigned int first, unsigned int count);
    int FUN_00460900(unsigned int first, unsigned int count, const char *value, unsigned int size) const;

    char m_allocator;
    char *m_chars;
    unsigned int m_size;
    unsigned int m_capacity;
};

class RHProfileString : public std::string
{
public:
    explicit RHProfileString(const std::allocator<char> &allocator = std::allocator<char>());
};

struct RHCivilianProfile
{
    RHProfileText m_00;
    RHProfileText m_10;
    RHProfileString m_20;
    int m_30;
    int m_34;
    int m_38;
};

bool FUN_005e0c90(SBFile &file, std::string &value);

#endif
