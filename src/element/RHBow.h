#ifndef RHBOW_H
#define RHBOW_H

class SBFile;

class RHBow
{
public:
    RHBow();
    ~RHBow();
    virtual bool Serialize(SBFile &file);
    unsigned FUN_00450070(int type) const;
    unsigned FUN_004500a0() const;
    unsigned FUN_004500c0(unsigned skill, unsigned range) const;
    short FUN_004502e0(unsigned type) const;
    static float Interpolat(float firstX, float secondX, float firstY, float secondY, float value);
    int FUN_004504b0(float value) const;
    int m_04; // [0x04]; allocation size 0x08

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
