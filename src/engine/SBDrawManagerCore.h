#ifndef SB_DRAW_MANAGER_CORE_H
#define SB_DRAW_MANAGER_CORE_H

#include "SBDrawManagerStorage.h"
#ifndef SBGEO_BOUNDINGBOX2D_VIEW
#include "SBGeoBoundingBox2DCore.h"
#endif

class SBGeoVector2D;
class SBDrawViewport;
class RHMobileUnk00607da0;
template<class T> class SBList;
class SBDrawManager;
struct HWND__;

bool FUN_005ede40(SBDrawManager *, const char *, ...);
bool FUN_005ed740(SBDrawManager *, unsigned short, const char *, ...);
extern SBDrawManager *g_unk0x6c11d0;

class SBDrawManager
{
public:
    ~SBDrawManager();
    unsigned short Unk(int red, int green, int blue);
    bool FUN_005ef380(int);
    bool FUN_005e3f40(const std::string &);
    bool FUN_005e3f70();
    bool FUN_005e5890(unsigned long, void **, unsigned long);
    void FUN_005e57e0(unsigned, SBGeoVector2D &);
    bool FUN_005e5bd0(unsigned long, void *);
    bool FUN_005e5d30(unsigned long);
    bool FUN_005ee640(SBList<SBGeoPoint2D> &, const SBGeoVector2D &);
    bool FUN_005eec00(unsigned long, unsigned long, void *, unsigned long,
        unsigned long, unsigned long, unsigned long, unsigned long);
    bool FUN_005e4810(unsigned short, unsigned short, unsigned short);
    bool FUN_005ed270(const RHMobileUnk00607da0 &);
    unsigned long Unk005e4ed0(unsigned short, unsigned short, unsigned long, bool);
    bool FUN_005e4f70(unsigned long, unsigned short, unsigned short, unsigned long);
    unsigned short FUN_005e56c0(unsigned long);
    unsigned short FUN_005e5750(unsigned long);
    unsigned short UnkField10c() const { return m_depth; }
    HWND__ *GetWindow() const { return m_window; }
    bool FUN_005e5160(unsigned long surface);
    bool FUN_005e5260();
    unsigned char IsOnScreen(const SBGeoBoundingBox2D &box) const;
    bool BlitAlphaKeying(unsigned long, SBGeoBoundingBox2D *, unsigned long,
        SBGeoBoundingBox2D *, unsigned short, unsigned short, unsigned long);
    bool BlitColoredAlphaKeying(unsigned long, SBGeoBoundingBox2D *, unsigned long,
        SBGeoBoundingBox2D *, unsigned short, unsigned short, unsigned short, unsigned long);
    bool BlitAlphaConstant(unsigned long, SBGeoBoundingBox2D *, unsigned long,
        SBGeoBoundingBox2D *, unsigned short, unsigned long);
    bool BlitAlpha(unsigned long, SBGeoBoundingBox2D *, unsigned long,
        SBGeoBoundingBox2D *, unsigned long, unsigned long);
    bool FUN_005e5a00(unsigned long, SBDrawViewport &, unsigned long);
    bool FUN_005e5ea0(SBDrawViewport &);
    bool FUN_005e5ec0(unsigned long, unsigned long);
    unsigned short FUN_005e5f60(unsigned long);
    bool FUN_005e6000(SBGeoBoundingBox2D &destination, SBGeoBoundingBox2D &source);
    bool FUN_005e61e0(unsigned long surface, const SBGeoBoundingBox2D *box, unsigned short color, unsigned long flags);
    bool FUN_005e6440(unsigned long source, const SBGeoBoundingBox2D *sourceBox, unsigned long destination, const SBGeoBoundingBox2D *destinationBox, unsigned long flags);
    bool FUN_005ecbd0(unsigned long surface, const SBGeoPoint2D &first, const SBGeoPoint2D &second, unsigned short color);
    bool FUN_005ecdc0(unsigned long surface, SBGeoBoundingBox2D &box, unsigned short color, unsigned long flags);
    char m_section[0x18];
    SBDrawDriverList m_driverList;
    int m_48;
    int m_4c;
    unsigned long m_50;
    SBDrawUnk005efc10 m_surfaces;
    std::list<unsigned long> m_released;
    unsigned long m_70;
    unsigned long m_74;
    unsigned long m_consoleSurface;
    unsigned char m_7c;
    char m_pad7d[0x03];
    unsigned char m_fullscreen;
    unsigned char m_81;
    char m_pad82[0x02];
    SBDrawUnk005e5ec0Surface *m_84;
    SBDrawUnk005e5ec0Surface *m_88;
    SBDrawUnk005e5ec0Surface *m_8c;
    char m_90[0x6c];
    void *m_instance;
    HWND__ *m_window;
    char m_104[0x08];
    unsigned short m_depth;
    unsigned short m_width;
    unsigned short m_height;
    unsigned char m_112;
    unsigned char m_113;
    unsigned char m_114;
    unsigned char m_115;
    char m_pad116[0x02];
    SBGeoBoundingBox2D m_bounds;
    char m_12c[0x04];
    unsigned long m_130;
    SBDrawUnk005eec00Edge *m_134;
    unsigned long m_138;
    unsigned long *m_13c;
    unsigned long m_140;
    unsigned long m_144;
    unsigned long m_148;
    unsigned long m_14c;
};

#endif
