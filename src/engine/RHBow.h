#ifndef RHBOW_H
#define RHBOW_H

class SBFile;

class RHBow
{
public:
    struct Profile
    {
        short m_00;
        short m_02;
        short m_04[6];
        short m_10[6];
        short m_1c[6];
        short m_28;
        short m_2a;
        short m_2c[6];
        short m_38[6];
        short m_44[6];
        char m_50[0x28];
        char m_78;
        char m_79;
    };
    static bool SerializePointer(SBFile &file, RHBow *&ptr);
};

#endif
