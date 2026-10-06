#include <string>
#include "RHMission.h"

class SBGeoPoint2D
{
public:
    SBGeoPoint2D(float, float);
    ~SBGeoPoint2D();
    float m_x;
    float m_y;
};

class SBGeoVector2D : public SBGeoPoint2D
{
public:
    SBGeoVector2D(float, float);
    ~SBGeoVector2D() {}
};

class RHUnk00613e90
{
public:
    RHUnk00613e90();
    ~RHUnk00613e90();
    unsigned short UnkWidth() const { return m_width; }
    unsigned short UnkDepth() const { return m_depth; }
    unsigned long UnkPitch() const { return m_pitch; }
    unsigned short *UnkData() const { return m_data; }
    char m_00[4]; // +0x00
    unsigned short m_width; // +0x04
    char m_06[2]; // +0x06
    unsigned long m_pitch; // +0x08
    unsigned short m_depth; // +0x0c
    char m_0e[2]; // +0x0e
    unsigned short *m_data; // +0x10
    char m_14[4]; // +0x14; sizeof = 0x18
};

class RHUnkFXDraw
{
public:
    unsigned long Unk005e4ed0(int, int, int, int);
    void Unk005e5160(unsigned long);
    bool Unk005e5a00(unsigned long, RHUnk00613e90 &, unsigned long);
    void Unk005e5ea0(RHUnk00613e90 &);
    unsigned short UnkField10c() const { return m_depth; }
    char m_00[0x10c];
    unsigned short m_depth; // +0x10c
};

class RHUnk006114c0
{
public:
    RHUnk006114c0();
    virtual ~RHUnk006114c0();
    virtual void Unk04();
    virtual void Unk08();
    virtual void Unk0c();
    virtual void Unk10();
    virtual void Unk14();
    virtual void Unk18();
    virtual void Unk1c();
    virtual bool Unk20(RHUnkFXDraw *, unsigned long);
    bool Unk00611710(SBFile &);
    bool Unk00611e10(unsigned long, unsigned long);
    RHUnk006114c0 *Unk00612ad0(const SBGeoPoint2D &, const SBGeoVector2D &);
    bool Unk00613530(RHUnkFXDraw *, unsigned long);
    unsigned short UnkField20() const { return m_width; }
    unsigned short UnkField22() const { return m_height; }
    char m_04[0x1c];
    unsigned short m_width; // +0x20
    unsigned short m_height; // +0x22
    char m_24[0x14]; // +0x24; sizeof = 0x38
};

class RHMissionProfile
{
public:
    char m_00[4]; // +0x00
    std::string m_name; // +0x04
};

class RHLoadingScreen
{
public:
    unsigned long CreateSurfaceForPicture(SBFile &);
    void GenerateSand(SBFile &);
    static std::string GetDataFile(const RHMission *, unsigned long);
    void Emit(SBFile &, const RHMission *);
    char m_00[0x18];
    RHUnkFXDraw *m_draw; // +0x18
    unsigned long m_width; // +0x1c
    unsigned long m_height; // +0x20
};

bool FUN_005f6400(const std::string &);
extern std::string g_unk0x006c05f0;
extern std::string g_unk0x006c0650;
extern unsigned char *g_unk0x006c0bd4;
extern float g_unk0x00679148;
