#ifndef RHSPRITERENDERINGINFOCORE_H
#define RHSPRITERENDERINGINFOCORE_H

struct RHspriteRenderingInfo
{
    RHspriteRenderingInfo()
    {
        m_surface = 0;
        m_kind = 0;
        m_04 = 0;
        m_05 = 0;
        m_color = 0;
        m_flags = 0;
        m_masks = 0;
        m_18 = 0;
    }
    unsigned long m_surface;
    unsigned char m_04;
    char m_05;
    unsigned char m_06[2];
    unsigned m_flags;
    int m_kind;
    char m_masks;
    unsigned char m_11;
    unsigned short m_color;
    unsigned short m_14;
    unsigned char m_16[2];
    int m_18;
};

#endif
