#ifndef SB_DRAW_MANAGER_CORE_H
#define SB_DRAW_MANAGER_CORE_H

class SBGeoPoint2D;
class SBGeoBoundingBox2D;
class SBDrawViewport;

class SBDrawManager
{
public:
    void BlitAlphaKeying(unsigned long, unsigned long, unsigned long,
        SBGeoBoundingBox2D *, unsigned short, unsigned short, unsigned long);
    bool FUN_005e5a00(unsigned long, SBDrawViewport &, unsigned long);
    void FUN_005e5ea0(SBDrawViewport &);
    bool FUN_005e6000(SBGeoBoundingBox2D &destination, SBGeoBoundingBox2D &source);
    bool FUN_005e61e0(unsigned long surface, const SBGeoBoundingBox2D *box, unsigned short color, unsigned long flags);
    bool FUN_005e6440(unsigned long source, const SBGeoBoundingBox2D *sourceBox, unsigned long destination, const SBGeoBoundingBox2D *destinationBox, unsigned char flags);
    bool FUN_005ecbd0(unsigned long surface, const SBGeoPoint2D &first, const SBGeoPoint2D &second, unsigned short color);
    void FUN_005ecdc0(unsigned long surface, const SBGeoBoundingBox2D &box, unsigned short color, unsigned long flags);
    unsigned char m_00[0x10c];
    unsigned short m_10c;
    unsigned short m_10e;
    unsigned short m_110;
};

#endif
