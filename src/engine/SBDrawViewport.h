#ifndef SBDRAWVIEWPORT_H
#define SBDRAWVIEWPORT_H

class SBGeoPoint2D;

class SBDrawViewport
{
public:
    SBDrawViewport();
    ~SBDrawViewport();
    unsigned short UnkWidth() const { return m_width; }
    unsigned short UnkDepth() const { return m_depth; }
    unsigned long UnkPitch() const { return m_pitch; }
    unsigned short *UnkData() const { return m_pixels; }
    unsigned short *operator[](const SBGeoPoint2D &point) const;
    unsigned short GetPixel(unsigned short x, unsigned short y) const;
    unsigned char m_00[4];
    unsigned short m_width;
    unsigned short m_height;
    unsigned long m_pitch;
    unsigned short m_depth;
    unsigned char m_0e[2];
    unsigned short *m_pixels;
    unsigned char m_locked;
    unsigned char m_15[3];
};

#endif
