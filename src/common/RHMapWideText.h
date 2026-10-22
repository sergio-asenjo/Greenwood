#ifndef RH_MAP_WIDE_TEXT_H
#define RH_MAP_WIDE_TEXT_H

#include <string>

// SIZE 0x10
class RHMapWideText
{
public:
    std::allocator<unsigned short> m_allocator; // 0x00
    unsigned short *m_chars; // 0x04
    unsigned m_size; // 0x08
    unsigned m_capacity; // 0x0c
    RHMapWideText(const std::allocator<unsigned short> &allocator = std::allocator<unsigned short>())
        : m_allocator(allocator) { Tidy(false); }
    void Tidy(bool);
    bool Grow(unsigned, bool);
    void End(unsigned);
    void FUN_004580c0(const std::wstring &text, unsigned first, unsigned count);
    ~RHMapWideText()
    {
        if (m_chars == 0)
            ;
        else if (*((unsigned char *)m_chars - 1) == 0 || *((unsigned char *)m_chars - 1) == 255)
            operator delete(m_chars - 1);
        else
            --*((unsigned char *)m_chars - 1);
        m_chars = 0, m_size = 0, m_capacity = 0;
    }
};

#endif
