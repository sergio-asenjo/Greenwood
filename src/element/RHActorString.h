#ifndef RHACTORSTRING_H
#define RHACTORSTRING_H

#include <string>
#include <memory.h>

class RHActorString
{
public:
    char m_0;
    char *m_4;
    unsigned m_8;
    unsigned m_c;

    const char *c_str() const { return m_4 ? m_4 : ""; }
    void FUN_00402780();
    bool FUN_00402280(unsigned length, bool trim = false);
    void FUN_00402260(unsigned length);
    void FUN_00401ee0(bool release);
    void Assign(const RHActorString &source)
    {
        unsigned count = std::string::npos;
        unsigned length = source.m_8;
        if (count < length)
            length = count;
        if (this == &source)
        {
            if (m_8 < length)
                std::_Xran();
            FUN_00402780();
            if (m_8 - length < count)
                count = m_8 - length;
            if (count > 0)
            {
                memmove(m_4 + length, m_4 + length + count, m_8 - length - count);
                unsigned remaining = m_8 - count;
                if (FUN_00402280(remaining))
                    FUN_00402260(remaining);
            }
            typedef std::string &(std::string::*Erase)(unsigned, unsigned);
            Erase erase = &std::string::erase;
            (((std::string *)this)->*erase)(0, 0);
        }
        else if (length > 0 && length == source.m_8 && (unsigned char)source.c_str()[-1] < 254)
        {
            FUN_00401ee0(true);
            m_4 = (char *)source.c_str();
            m_8 = source.m_8;
            m_c = source.m_c;
            ++m_4[-1];
        }
        else if (FUN_00402280(length, true))
        {
            memcpy(m_4, source.c_str(), length);
            FUN_00402260(length);
        }
    }
};

#endif
