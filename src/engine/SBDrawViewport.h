#ifndef SBDRAWVIEWPORT_H
#define SBDRAWVIEWPORT_H

class SBGeoPoint2D;

class SBDrawViewport
{
public:
    unsigned short *operator[](const SBGeoPoint2D &point) const;
    unsigned short GetPixel(unsigned short x, unsigned short y) const;
    unsigned char m_00[4];
    unsigned short m_width;
    unsigned short m_height;
    unsigned long m_pitch;
    unsigned short m_depth;
    unsigned char m_0e[2];
    unsigned short *m_pixels;
};

#endif
