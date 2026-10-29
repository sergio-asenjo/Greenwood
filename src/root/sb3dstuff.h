#include "SB.h"
#include "RHUnk00613e90.h"

class RHUnk005df510
{
public:
    int m_0;
    int m_4;
    int m_8;

    bool Serialize(SBFile &file);
};

class RHUnk005dfb00
{
public:
    RHUnk005df510 m_00;
    RHUnk005df510 m_0c;
    RHUnk005df510 m_18;
    RHUnk005df510 m_24;
    RHUnk005df510 m_30;
    RHUnk005df510 m_3c;
    int m_48;
    int m_4c;
    int m_50;
    int m_54;

    bool FUN_005dfb00(SBFile &file);
    void Emit(SBFile &file);
};

class RHUnk005dfd00
{
public:
    RHUnk005dfd00();
    void FUN_005dfc80(RHUnk00613e90 point);
    void Reset()
    {
        m_00 = 0x7149f2ca;
        m_04 = 0xf149f2ca;
        m_08 = 0x7149f2ca;
        m_0c = 0xf149f2ca;
        m_10 = 0x7149f2ca;
        m_14 = 0xf149f2ca;
    }
    int m_00;
    int m_04;
    int m_08;
    int m_0c;
    int m_10;
    int m_14;

    bool FUN_005dfd00(SBFile &file);
    void Emit(SBFile &file);
};
