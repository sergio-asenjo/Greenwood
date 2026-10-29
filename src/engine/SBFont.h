#ifndef SB_FONT_H
#define SB_FONT_H

#include <string>
#include "Decomp.h"

class SBFile;
void FUN_005f8030(int, const char *, int, const char *, ...);

// SIZE 0x01
typedef std::_Lockit SBFontLock;

// SIZE 0x0c
struct SBFontTextView
{
    undefined4 m_00; // 0x00
    unsigned short *m_04; // 0x04
    unsigned m_08; // 0x08
    unsigned short *end()
    {
        unsigned short *value = m_04;
        if (value) value += m_08;
        return value;
    }
};

// SIZE 0x44
class SBFontUnk0061e840
{
public:
    virtual int v0(); // vtable+0x00
    virtual void v1(void *); // vtable+0x04
    virtual void v2(); // vtable+0x08
    virtual int v3(unsigned short, int &, int &); // vtable+0x0c
    virtual void v4(unsigned short, void *, const void *, bool); // vtable+0x10
    virtual void v5(); // vtable+0x14
    virtual void v6(); // vtable+0x18
    virtual void v7(); // vtable+0x1c
    virtual int v8(); // vtable+0x20
    virtual bool v9(SBFile &); // vtable+0x24
    int m_04; // 0x04
    char m_08[0x0c]; // 0x08
    int m_14; // 0x14
    char m_18[0x24]; // 0x18
    int m_3c; // 0x3c
    undefined4 m_40; // 0x40

    void FUN_0061e810(int, int);
    void FUN_0061e840();
    int FUN_0061e850(unsigned short);
    int FUN_0061e880();
    std::string FUN_0061e8a0();
    int FUN_0061e970();
    int FUN_0061e980(void *, int &, int &);
    int FUN_0061ea50(void *);
    bool FUN_0061ea80(const std::string &);
    int FUN_0061eb80(SBFontTextView *, void *, const void *, bool);
    bool FUN_0061eb00(SBFile &);
    void FUN_0061ebd0(unsigned short);
    bool FUN_0061ed70(SBFile &);
};

// SIZE 0x14
struct SBFontNode0061fcb0
{
    SBFontNode0061fcb0 *m_00; // 0x00
    SBFontNode0061fcb0 *m_04; // 0x04
    SBFontNode0061fcb0 *m_08; // 0x08
    unsigned short m_0c; // 0x0c
    undefined2 m_0e; // 0x0e
    int m_10; // 0x10
};

// SIZE 0x04
struct SBFontIterator0061fe10
{
    SBFontNode0061fcb0 *m_00; // 0x00
    SBFontIterator0061fe10() {}
    SBFontIterator0061fe10(SBFontNode0061fcb0 *node) : m_00(node) {}
    bool operator!=(const SBFontIterator0061fe10 &other) const { return m_00 != other.m_00; }
    static SBFontNode0061fcb0 *&Left(SBFontNode0061fcb0 *value) { return value->m_00; }
    void FUN_00620ca0();
    void FUN_00620fa0();
    SBFontIterator0061fe10 operator++(int)
    {
        SBFontIterator0061fe10 previous = *this;
        FUN_00620fa0();
        return previous;
    }
};

// SIZE 0x08
struct SBFontPair0061f2b0
{
    SBFontIterator0061fe10 m_00; // 0x00
    bool m_04; // 0x04
    SBFontPair0061f2b0(const SBFontIterator0061fe10 &value, const bool &inserted) : m_00(value), m_04(inserted) {}
};

extern SBFontNode0061fcb0 *g_unk0x006c191c;
extern unsigned g_unk0x006c1920;

// SIZE 0x10
class SBFontTree0061fcb0
{
public:
    undefined m_00; // 0x00
    undefined m_01; // 0x01
    undefined2 m_02; // 0x02
    SBFontNode0061fcb0 *m_04; // 0x04
    bool m_08; // 0x08
    undefined m_09[3]; // 0x09
    unsigned m_0c; // 0x0c
    SBFontTree0061fcb0(const undefined &, bool, const undefined &);
    unsigned size() const { return m_0c; }
    SBFontNode0061fcb0 *&root() { return m_04->m_04; }
    SBFontNode0061fcb0 *&leftmost() { return m_04->m_00; }
    SBFontNode0061fcb0 *&rightmost() { return m_04->m_08; }
    SBFontTree0061fcb0(const SBFontTree0061fcb0 &other)
        : m_00(other.m_00), m_01(other.m_01), m_08(other.m_08)
    {
        {
            SBFontLock lock;
            if (!g_unk0x006c191c) {
                SBFontNode0061fcb0 *node = (SBFontNode0061fcb0 *)operator new(0x14);
                node->m_04 = 0;
                node->m_10 = 1;
                g_unk0x006c191c = node;
                g_unk0x006c191c->m_00 = 0;
                g_unk0x006c191c->m_08 = 0;
            }
            ++g_unk0x006c1920;
            m_04 = FUN_00620c70(g_unk0x006c191c, 0);
            m_0c = 0;
            m_04->m_00 = m_04;
            m_04->m_08 = m_04;
        }
        FUN_00620960(other);
    }
    ~SBFontTree0061fcb0()
    {
        FUN_0061fce0(begin(), end());
        operator delete(m_04);
        m_04 = 0;
        m_0c = 0;
        {
            SBFontLock lock;
            if (--g_unk0x006c1920 == 0) {
                operator delete(g_unk0x006c191c);
                g_unk0x006c191c = 0;
            }
        }
    }
    SBFontIterator0061fe10 begin() { return SBFontIterator0061fe10(leftmost()); }
    SBFontIterator0061fe10 end() { return SBFontIterator0061fe10(m_04); }
    void FUN_0061eea0();
    SBFontPair0061f2b0 FUN_0061f2b0(const unsigned short &);
    SBFontIterator0061fe10 FUN_0061fe10(const unsigned short &);
    void FUN_00620b70();
    SBFontNode0061fcb0 *FUN_00620c20(const unsigned short &);
    SBFontIterator0061fe10 FUN_0061fe30(SBFontNode0061fcb0 *, SBFontNode0061fcb0 *, const unsigned short &);
    SBFontIterator0061fe10 FUN_0061fce0(SBFontIterator0061fe10, SBFontIterator0061fe10);
    void FUN_00620960(const SBFontTree0061fcb0 &);
    void FUN_00620ae0(SBFontNode0061fcb0 *);
    SBFontIterator0061fe10 FUN_00620440(SBFontIterator0061fe10);
    SBFontNode0061fcb0 *FUN_00620d60(SBFontNode0061fcb0 *, SBFontNode0061fcb0 *);
    SBFontNode0061fcb0 *FUN_00620c70(SBFontNode0061fcb0 *, int);
    static SBFontNode0061fcb0 *Maximum(SBFontNode0061fcb0 *);
};

// SIZE 0x20
class SBFontValue0061f120
{
public:
    std::string m_00; // 0x00
    SBFontTree0061fcb0 m_10; // 0x10
    SBFontValue0061f120(const std::string &, const SBFontTree0061fcb0 &);
    ~SBFontValue0061f120();
};

// SIZE 0x30
struct SBFontNode0061f3e0
{
    SBFontNode0061f3e0 *m_00; // 0x00
    SBFontNode0061f3e0 *m_04; // 0x04
    SBFontNode0061f3e0 *m_08; // 0x08
    SBFontValue0061f120 m_0c; // 0x0c
    int m_2c; // 0x2c
};

class SBFontUnk00620c90
{
public:
    SBFontUnk00620c90 *FUN_00620c90(int value);
};

// SIZE 0x04
struct SBFontIterator0061f3e0
{
    SBFontNode0061f3e0 *m_00; // 0x00
    static SBFontNode0061f3e0 *&Left(SBFontNode0061f3e0 *value) { return value->m_00; }
    void FUN_00620e30();
    void FUN_00620ef0();
    SBFontIterator0061f3e0 operator++(int)
    {
        SBFontIterator0061f3e0 previous = *this;
        FUN_00620ef0();
        return previous;
    }
};

// SIZE 0x08
struct SBFontPair0061f3e0
{
    SBFontIterator0061f3e0 m_00; // 0x00
    bool m_04; // 0x04
    SBFontPair0061f3e0(const SBFontIterator0061f3e0 &value, const bool &inserted) : m_00(value), m_04(inserted) {}
};

// SIZE 0x10
class SBFontTree0061f3e0
{
public:
    SBFontTree0061f3e0() {}
    SBFontTree0061f3e0(const undefined &, const undefined &);
    undefined m_00[4]; // 0x00
    SBFontNode0061f3e0 *m_04; // 0x04
    bool m_08; // 0x08
    undefined m_09[3]; // 0x09
    unsigned m_0c; // 0x0c
    void FUN_0061e740();
    SBFontIterator0061f3e0 FUN_0061efe0(SBFontIterator0061f3e0, SBFontIterator0061f3e0);
    SBFontIterator0061f3e0 FUN_0061f550(SBFontIterator0061f3e0);
    void FUN_0061fb40(SBFontNode0061f3e0 *);
    SBFontNode0061f3e0 *&root() { return m_04->m_04; }
    SBFontNode0061f3e0 *&leftmost() { return m_04->m_00; }
    SBFontNode0061f3e0 *&rightmost() { return m_04->m_08; }
    SBFontIterator0061f3e0 begin()
    {
        SBFontIterator0061f3e0 result;
        result.m_00 = leftmost();
        return result;
    }
    SBFontPair0061f3e0 FUN_0061f3e0(const SBFontValue0061f120 &);
    SBFontIterator0061f3e0 FUN_00620130(SBFontNode0061f3e0 *, SBFontNode0061f3e0 *, const SBFontValue0061f120 &);
};

extern SBFontNode0061f3e0 *g_unk0x006c1914;
void SBFontConstructValue(SBFontValue0061f120 *, const SBFontValue0061f120 &);

#endif
