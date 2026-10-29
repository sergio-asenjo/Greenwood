#ifndef RHSOUNDCACHESTRING_H
#define RHSOUNDCACHESTRING_H

#include "Decomp.h"
#include "RHCivilianProfile.h"

void FUN_006416e6();
#include <string.h>

struct RHSoundCacheString
{
    undefined m_00;
    char *m_04;
    unsigned int m_08;
    unsigned int m_0c;

    const char *c_str() const { return m_04 ? m_04 : ""; }
    unsigned int size() const { return m_08; }
    unsigned int capacity() const { return m_0c; }
    __forceinline void Release()
    {
        if (m_04)
        {
            char *storage = m_04 - 1;
            unsigned char references = (unsigned char)*storage;
            if (references != 0 && references != 255)
                *storage = references - 1;
            else
                operator delete(storage);
        }
        m_04 = 0;
        m_08 = 0;
        m_0c = 0;
    }
    void FUN_00402780();
    RHSoundCacheString &erase(unsigned int position, unsigned int count = std::string::npos)
    {
        if (m_08 < position)
            std::_Xran();
        FUN_00402780();
        unsigned int available = m_08 - position;
        if (available < count)
            count = available;
        if (0 < count)
        {
            memmove(m_04 + position, m_04 + position + count, available - count);
            unsigned int size = m_08 - count;
            if (((RHProfileText *)this)->FUN_00402280(size, false))
                ((RHProfileText *)this)->FUN_00402260(size);
        }
        return *this;
    }
    RHSoundCacheString &assign(const RHSoundCacheString &value, unsigned int position, unsigned int count)
    {
        if (value.size() < position)
            FUN_006416e6();
        unsigned int size = value.size() - position;
        if (count < size)
            size = count;
        if (this == &value)
        {
            erase(position + size);
            typedef std::string &(std::string::*Erase)(unsigned, unsigned);
            Erase eraseFront = &std::string::erase;
            (((std::string *)this)->*eraseFront)(0, position);
        }
        else if (0 < size && size == value.size() && (unsigned char)value.c_str()[-1] < 254)
        {
            ((RHProfileText *)this)->FUN_00401ee0(true);
            m_04 = (char *)value.c_str();
            m_08 = value.size();
            m_0c = value.capacity();
            ++m_04[-1];
        }
        else if (((RHProfileText *)this)->FUN_00402280(size, true))
        {
            memcpy(m_04, value.c_str() + position, size);
            ((RHProfileText *)this)->FUN_00402260(size);
        }
        return *this;
    }
    RHSoundCacheString &operator=(const RHSoundCacheString &value)
    {
        return assign(value, 0, std::string::npos);
    }
};

#endif
