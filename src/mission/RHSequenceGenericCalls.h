#ifndef RHSEQUENCEGENERICCALLS_H
#define RHSEQUENCEGENERICCALLS_H

#include <list>

class RHUnkSequenceOrder
{
public:
    virtual ~RHUnkSequenceOrder();
};

// SIZE 0x14
class RHSequenceOrderList : public std::list<RHUnkSequenceOrder *>
{
public:
    RHSequenceOrderList() : m_dirty(true) {}
    ~RHSequenceOrderList() { clear(); }
    void clear()
    {
        iterator position = begin();
        iterator last = end();
        iterator (std::list<RHUnkSequenceOrder *>::*eraseOne)(iterator) = &std::list<RHUnkSequenceOrder *>::erase;
        while (position != last)
            (this->*eraseOne)(position++);
    }
    void DeleteAll()
    {
        for (m_cursor = begin(); m_cursor != end(); ++m_cursor)
            delete *m_cursor;
        clear();
    }
    iterator m_cursor; // 0x0c
    bool m_dirty;      // 0x10
};

// VTABLE: GAME 0x00679cd8
// SIZE 0x64
class RHUnk00584d60
{
public:
    RHUnk00584d60();
    RHUnk00584d60(unsigned short level, int command, void *actor);
    ~RHUnk00584d60();
    void *FUN_00584d40(unsigned int flags);
    virtual void FUN_00584d30();
    void SetFlag(bool value) { m_60 = value; }
    unsigned char m_04;          // 0x04
    char m_05[3];                // 0x05
    int m_08;                    // 0x08
    unsigned char m_0c;          // 0x0c
    char m_0d[3];                // 0x0d
    int m_10;                    // 0x10
    unsigned short m_14;         // 0x14
    char m_16[2];                // 0x16
    RHSequenceOrderList m_orders; // 0x18
    char m_2c[0x1c];             // 0x2c
    void *m_48;                  // 0x48
    void *m_4c;                  // 0x4c
    void *m_50;                  // 0x50
    void *m_54;                  // 0x54
    int m_58;                    // 0x58
    int m_5c;                    // 0x5c
    bool m_60;                   // 0x60
    char m_61[3];                // 0x61
};

#endif
