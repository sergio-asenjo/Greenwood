#ifndef RHSCRIPTLOCATION_H
#define RHSCRIPTLOCATION_H

class SBFile;

class RHUnk00522470
{
public:
    RHUnk00522470();
    ~RHUnk00522470();
    void Unk005224d0(SBFile &file);
    void FUN_00520a90(SBFile &file);
    char m_pad0[4];
    float x;
    float y;
    unsigned m_0c;
    unsigned char m_10;
    char m_pad11[3];
    bool m_14;
    char m_pad15[3];
    int m_18;
    char m_pad1c[4];
    union
    {
        short layer;
        unsigned short m_layer;
    };
    char m_pad22[2];
    void *area;
    void SetLayer(short value) { layer = value; }
    void SetArea(void *value) { area = value; }
};

#endif
