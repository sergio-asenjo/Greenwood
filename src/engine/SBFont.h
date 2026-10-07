#ifndef SB_FONT_H
#define SB_FONT_H

#include <string>

class SBFile;

struct SBFontTextView
{
    int m_00;
    unsigned short *m_04;
    unsigned m_08;
    unsigned short *end()
    {
        unsigned short *value = m_04;
        if (value) value += m_08;
        return value;
    }
};

class SBFontUnk0061e840
{
public:
    virtual int v0();
    virtual void v1(void *);
    virtual void v2();
    virtual int v3(unsigned short, int &, int &);
    virtual void v4(unsigned short, void *, const void *, bool);
    virtual void v5();
    virtual void v6();
    virtual void v7();
    virtual int v8();
    virtual bool v9(SBFile &);
    int m_04;
    char m_08[0x0c];
    int m_14;
    char m_18[0x24];
    int m_3c;
    int m_40;

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
    bool FUN_0061ed70(SBFile &);
};

#endif
