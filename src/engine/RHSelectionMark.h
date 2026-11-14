#ifndef RHSELECTIONMARK_H
#define RHSELECTIONMARK_H

class RHSprite;
class RHUnk005ef320;
class RHFrameHolder;
class SBGeoBoundingBox2D;
class SBGeoPoint2D;

class RHUnk00581c40
{
public:
    RHUnk00581c40();
    ~RHUnk00581c40();
    void *FUN_00581c20(unsigned flags);
    unsigned long LoadFromResource();
    bool FUN_00581ee0(unsigned long surface, float scale, const SBGeoBoundingBox2D &view,
        const SBGeoPoint2D &point, unsigned short layer, bool, bool selected);
    unsigned m_vptr;
    RHSprite *m_4;
    RHUnk005ef320 *m_8;
    RHFrameHolder *m_c;
    unsigned m_10;
    int m_14;
    char m_18;
    char m_19;
    short m_1a;
};

#endif
