#ifndef SBPICTURE_H
#define SBPICTURE_H

extern float g_unk0x00677488;

class SBPictureUnkDrawManager;

class SBPictureUnkVector2D
{
public:
    float m_x;
    float m_y;

    float GetX() const { return m_x; }
    float GetY() const { return m_y; }
};

class SBPicture
{
public:
    char m_pad0[4];
    int m_04;
    char m_pad08[0x0c];
    unsigned char *m_14;
    void *m_18;
    unsigned int m_1c;
    unsigned short m_20;
    unsigned short m_22;
    unsigned short m_24;

    void *FUN_00611bd0(int);
    void FUN_00611c50();
    bool FUN_00611c80(SBPictureUnkDrawManager *, unsigned long);
    bool FUN_00611ea0(int);
    bool FUN_00611f70(int);
    bool FUN_00612040(int);
    bool FUN_00612150(int);
    bool FUN_00612260(int);
    bool FUN_006122b0(int);
    bool FUN_00612300(const SBPictureUnkVector2D &, int);
    bool FUN_00612350(const SBPictureUnkVector2D &);
    unsigned short FUN_006124f0(unsigned short *, unsigned short, unsigned short, unsigned short);
    unsigned short FUN_006125c0(unsigned short *, unsigned short, unsigned short, unsigned short);
    bool FUN_00612690(const SBPictureUnkVector2D &);
    bool FUN_006128b0(const SBPictureUnkVector2D &);
    bool FUN_00612d80(unsigned short, unsigned short);
    bool FUN_00612e30(unsigned short, unsigned short);
    bool FUN_006131a0(unsigned short, unsigned short);
};

#endif
