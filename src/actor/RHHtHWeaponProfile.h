#ifndef RHHTHWEAPONPROFILE_H
#define RHHTHWEAPONPROFILE_H

class RHHtHWeaponProfile
{
public:
    struct Record
    {
        int m_00;
        int m_04;
        int m_08;
        short m_0c;
        short m_0e;
        short m_10;
        short m_12;
        short m_14;
        short m_16;
        short m_18;
        short m_1a;
        short m_1c;
        short m_1e;
    };

    short m_00;
    short m_02;
    short m_04;
    short m_06;
    short m_08;
    short m_0a;
    short m_0c;
    short m_0e;
    short m_10;
    short m_12;
    short m_14;
    char m_16;
    char m_17;
    short m_18;
    short m_1a;
    Record m_1c[10];
};

#endif
