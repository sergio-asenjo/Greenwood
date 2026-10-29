#ifndef RHHIKINGGUIDESTORAGE_H
#define RHHIKINGGUIDESTORAGE_H

#include <vector>
#include "Decomp.h"

class SBFile;

class RHUnk00551da0
{
public:
    bool FUN_00551da0(SBFile &file);
    undefined4 m_00;
};

class RHUnk0051d370Entry
{
public:
    virtual void V00(int flag) = 0;
};

class RHUnk0051d2c0Storage : public std::vector<RHUnk00551da0 *>
{
public:
    ~RHUnk0051d2c0Storage() { clear(); }
    RHUnk00551da0 **m_cursor;
    bool m_dirty;
    bool m_searching;
    int m_index;
    RHUnk00551da0 *m_value;
};

class RHUnk0051d2c0 : public RHUnk0051d2c0Storage
{
public:
    ~RHUnk0051d2c0();
    void FUN_0051d370();
};

class RHHikingGroupArrayStorage : public std::vector<RHUnk0051d2c0 *>
{
public:
    ~RHHikingGroupArrayStorage() { clear(); }
    RHUnk0051d2c0 **m_cursor;
    bool m_dirty;
    bool m_searching;
    int m_index;
    RHUnk0051d2c0 *m_value;
};

class RHHikingGroupArray : public RHHikingGroupArrayStorage
{
public:
    RHHikingGroupArray() { m_dirty = true; }
    ~RHHikingGroupArray()
    {
        typedef std::vector<RHUnk0051d2c0 *> Values;
        unsigned (Values::*size)() const = &Values::size;
        int count = (this->*size)();
        for (int index = 0; index < count; ++index)
            if ((*this)[index])
                delete (*this)[index];
        clear();
    }
    void Destroy()
    {
        int count = size();
        for (int index = 0; index < count; ++index)
        {
            if ((*this)[index])
                delete (*this)[index];
        }
        clear();
        m_dirty = true;
    }
};

// VTABLE: GAME 0x006790b8
class RHHikingGuide
{
public:
    RHHikingGuide();
    virtual ~RHHikingGuide();
    int FUN_0051cac0(SBFile &file);
    void FUN_0051cd10(SBFile &file);
    bool FUN_0051d020(SBFile &file);
    RHHikingGroupArray m_04;
};

#endif
