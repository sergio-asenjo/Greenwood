#include "RHSaveGame.h"
#include "RHEngine.h"
#include "RHCivilianProfile.h"
#include <windows.h>

void FUN_005e0c90(SBFile &file, std::string &value);
extern char g_unk0x6c0560[4];

class SBGeoVector2D;

class SBGeoPoint2D
{
public:
    SBGeoPoint2D();
    ~SBGeoPoint2D();
    SBGeoPoint2D &operator=(const SBGeoPoint2D &value);
    SBGeoPoint2D operator+(const SBGeoVector2D &value) const;
    bool Serialize(SBFile &file);
    float m_x;
    float m_y;
};

class RHUnk00452030;
extern RHUnk00452030 *g_unk0x6c07fc;
struct RHBonusProjection;

class RHUnk0057d800
{
public:
    RHBonusProjection *Unk(const SBGeoPoint2D &point);
};

class RHUnk00582220
{
public:
    RHUnk00582220();
    ~RHUnk00582220();
    char m_data[0x3c];
};

class RHUnk00585500
{
public:
    void Unk(void *sequence);
};

class RHUnk0058a3d0
{
public:
    void Unk(void *context, int value, void *sequence);
};

class RHUnk005883a0
{
public:
    RHUnk005883a0(unsigned short level, int command, void *actor, int style,
        const SBGeoPoint2D &destination, int first, int second, int flags);
    ~RHUnk005883a0();
    char data[0x9c];
};

struct RHbeamMe
{
    SBGeoPoint2D m_point;
    unsigned short m_8;
    unsigned short m_a;
    unsigned short m_c;
    char m_e;
    char m_f;
    unsigned short m_10;
    unsigned short m_12;
    unsigned short m_14;
    char m_16[2];
    int m_required;
    int m_1c;
    RHProfileText m_text;
    RHbeamMe() {}
    RHbeamMe(const RHbeamMe &value);
    RHbeamMe &operator=(const RHbeamMe &value)
    {
        m_point = value.m_point;
        m_8 = value.m_8;
        m_a = value.m_a;
        m_c = value.m_c;
        m_e = value.m_e;
        m_10 = value.m_10;
        m_12 = value.m_12;
        m_14 = value.m_14;
        m_required = value.m_required;
        m_1c = value.m_1c;
        m_text.FUN_00401ce0((const std::string &)value.m_text, 0, std::string::npos);
        return *this;
    }
};

class RHEngineBeamCalls
{
public:
    void FUN_004e4120(RHbeamMe *position, unsigned count, const RHbeamMe &value);
};

struct RHEngineBeamFlags
{
    unsigned char m_0 : 1;
    unsigned char m_1 : 1;
    unsigned char m_2 : 1;
    unsigned char m_3 : 1;
    unsigned char m_4 : 1;
    unsigned char m_5 : 1;
    unsigned char m_6 : 1;
    unsigned char m_7 : 1;
    unsigned char m_8 : 1;
    unsigned char m_9 : 1;
};

class RHEngineReinforcementCalls
{
public:
    void *FUN_00452130(void *profile);
    void FUN_004936a0(int value);
    void FUN_00491fd0(const RHbeamMe &beamMe);
    void FUN_004d8460(void *actor, int first, int second);
    unsigned FUN_004e4460(void **value, int insert);
    SBGeoPoint2D FUN_004a49e0();
    bool FUN_004f6c20(const SBGeoPoint2D &origin, SBGeoPoint2D &destination,
        unsigned short layer, const SBGeoPoint2D &extent);
};

class RHUnk0048f280
{
public:
    RHUnk0048f280(void *description);
    char m_data[0x60c];
};

class RHUnk00588830
{
public:
    RHUnk00588830(unsigned short level, int command, void *actor, int style, int value);
    char m_data[0x9c];
};

class SBGeoVector2D : public SBGeoPoint2D
{
public:
    SBGeoVector2D(float x, float y);
};

void FUN_0048c5b0(void *actor, int value);

class RHUnkFXDraw
{
public:
    unsigned long Unk005e4ed0(int, int, int, int);
    char m_00[0x10c];
    unsigned short m_depth;
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
    bool Unk00611e10(unsigned long, unsigned long);
    bool Unk00613530(RHUnkFXDraw *, unsigned long);
    char m_04[0x1c];
    unsigned short m_width;
    unsigned short m_height;
    char m_24[0x14];
};

class RHEngineBackgroundCalls
{
public:
    void FUN_00611660(const std::string &path);
    void FUN_004e7fa0(int width, int height);
};

extern std::string g_unk0x006c05f0;
extern float g_unk0x00677438;
bool FUN_005f6400(const std::string &path);
std::string FUN_004e4b40(const std::string &first, const std::string &second);
std::string FUN_004e4c70(const std::string &first, const char *second);

// GLOBAL: GAME 0x0067748c
float g_unk0x0067748c = 5.0f;

// GLOBAL: GAME 0x00677680
float g_unk0x00677680 = 0.015625f;

// GLOBAL: GAME 0x00677484
float g_unk0x00677484 = 50.0f;

// GLOBAL: GAME 0x00677f7c
float g_unk0x00677f7c = 0.00003051850944757461548f;

class RHMapDescription
{
public:
    bool FUN_0063cda0(unsigned mission);
};

// GLOBAL: GAME 0x006c0664
char *g_unk0x006c0664 = 0;

// GLOBAL: GAME 0x006c0a7c
int g_unk0x006c0a7c = 0;

// GLOBAL: GAME 0x006774a0
float g_unk0x006774a0 = 20.0f;

#define RHENGINE_POINTER_BODY(value) \
    int index; \
    if (file.m_bLoading == 1) \
    { \
        if (file.Access(&index, 4) < 0) \
        { \
            SBString *error = file.GetError(); \
            SBAssert(0, "P:\\Robin Hood\\RHengine.cpp", 0x8c6, \
                "Serialize failed reason is %s", error->m_chars ? error->m_chars : ""); \
            return false; \
        } \
        if (index == -1) \
        { \
            value = 0; \
            return true; \
        } \
        value = FUN_004622e0(index, g_pEngine->m_48d8); \
        return true; \
    } \
    else \
    { \
        if (!value) \
            index = -1; \
        else \
            index = *(int *)((char *)value + 0xc); \
        if (file.Access(&index, 4) < 0) \
        { \
            SBString *error = file.GetError(); \
            SBAssert(0, "P:\\Robin Hood\\RHengine.cpp", 0x8dc, \
                "Serialize failed reason is %s", error->m_chars ? error->m_chars : ""); \
            return false; \
        } \
        return true; \
    }

// STRING: GAME 0x006aef80
static const char *g_rhengineFile = "P:\\Robin Hood\\RHengine.cpp";

class RHEngineMissionCalls
{
public:
    void FUN_004c1ab0(SBFile &file, RHMission *mission, std::string &background, unsigned *version);
    void FUN_004c3680(SBFile &file);
    void FUN_004c3630(SBFile &file);
    void FUN_004c3930(SBFile &file, int protoLevel);
    void FUN_004c1ee0(SBFile &file);
    void FUN_004c20a0(SBFile &file);
    void FUN_004c2830(SBFile &file);
};

class RHMissionArrayStorage
{
public:
    void FUN_004609a0(void *first, void *last);
};

// STUB: GAME 0x004c0510
// Parked: 21.13%; partial chunk dispatch.
bool RHEngine::InitializeFromMission(RHMission *mission)
{
    RHUnk005f4fc0 protoFile, missionFile;
    std::string protoPath, missionPath, background;
    std::vector<RHbeamMe> beamMes;
    void *profile = *(void **)mission;
    ((RHMissionArrayStorage *)((char *)this + 0x4c58))->FUN_004609a0(
        *(void **)((char *)this + 0x4c5c), *(void **)((char *)this + 0x4c60));
    *((char *)this + 0x4c6c) = 1;
    ((RHProfileText *)((char *)this + 0x94))->FUN_00401ce0(
        *(std::string *)((char *)profile + 0x14), 0, std::string::npos);
    ((RHProfileText *)((char *)this + 0xa4))->FUN_00401ce0(
        *(std::string *)((char *)profile + 4), 0, std::string::npos);
    // STRING: GAME 0x006af388
    std::string protoExtension(".rhp");
    protoPath = FUN_004e4b40(FUN_004e4b40(
        FUN_004e4c70(g_unk0x006c05f0, "\\"),
        *(std::string *)((char *)this + 0xa4)), protoExtension);
    std::string missionExtension(".rhm");
    missionPath = FUN_004e4b40(FUN_004e4b40(
        FUN_004e4c70(g_unk0x006c05f0, "\\"),
        *(std::string *)((char *)this + 0x94)), missionExtension);
    if (protoFile.FUN_005f5090(protoPath, 1))
    {
        SBAssert(1, "P:\\Robin Hood\\RHengine.cpp", 0x37f,
            // STRING: GAME 0x006af340
            "STRENGSTENS UNTERSAGT : Unable to open proto-level file !");
        return false;
    }
    FUN_005e1d50(protoFile, 0x4d455548, 2);
    if (missionFile.FUN_005f5090(missionPath, 1))
    {
        SBAssert(1, "P:\\Robin Hood\\RHengine.cpp", 0x389,
            "STRENGSTENS UNTERSAGT : Unable to open mission file !");
        return false;
    }
    FUN_005e1d50(missionFile, 0x44555459, 2);
    unsigned version[2];
    ((RHEngineMissionCalls *)this)->FUN_004c1ab0(missionFile, mission, background, version);
    g_unk0x006c0a7c = 7;
    g_unk0x6c0a50.FUN_00523300();
    FUN_004c28c0(background);
    while (*(unsigned *)((char *)&protoFile + 0xc) < *(unsigned *)((char *)&protoFile + 8))
    {
        switch (FUN_005e1d00(protoFile))
        {
        case 0x464c494d:
            ((RHEngineMissionCalls *)this)->FUN_004c3680(protoFile);
            break;
        case 0x53544154:
            ((RHEngineMissionCalls *)this)->FUN_004c3630(protoFile);
            break;
        case 0x5455504f:
            ((RHEngineMissionCalls *)this)->FUN_004c3930(protoFile, 1);
            break;
        case 0x42474e44:
            break;
        default:
            FUN_005e2300(protoFile);
            SBAssert(0, "P:\\Robin Hood\\RHengine.cpp", 0x41d,
                // STRING: GAME 0x006af168
                "ACHTUNG : Unknown chunk skipped in proto-level file");
            break;
        }
    }
    while (*(unsigned *)((char *)&missionFile + 0xc) < *(unsigned *)((char *)&missionFile + 8))
    {
        switch (FUN_005e1d00(missionFile))
        {
        case 0x424f595a:
            g_unk0x006c0a7c = 9;
            g_unk0x6c0a50.FUN_00523300();
            InitializeActorsFromMissionStream(missionFile, beamMes);
            break;
        case 0x43415645:
            InitializeBuildingTenantsFromMissionStream(missionFile);
            break;
        case 0x54494e47:
            ((RHEngineMissionCalls *)this)->FUN_004c1ee0(missionFile);
            break;
        case 0x534b524f:
            ((RHEngineMissionCalls *)this)->FUN_004c20a0(missionFile);
            break;
        case 0x504f5546:
        case 0x5455504f:
            ((RHEngineMissionCalls *)this)->FUN_004c3930(missionFile, 0);
            break;
        case 0x5a4f5247:
            ((RHEngineMissionCalls *)this)->FUN_004c2830(missionFile);
            break;
        default:
            FUN_005e2300(missionFile);
            SBAssert(0, "P:\\Robin Hood\\RHengine.cpp", 0x459,
                // STRING: GAME 0x006af0e0
                "ACHTUNG : Unknown chunk skipped in mission file");
            break;
        }
    }
    return true;
}

// STUB: GAME 0x004c1be0
// cdecl cleanup seam, not proven irreducible.
void RHEngine::InitializeActorsFromMissionStream(SBFile &file, std::vector<RHbeamMe> &beamMes)
{
    FUN_005e1d50(file, 0x424f595a, 3);
    unsigned short count;
    file.Access(&count, 2);
    for (unsigned short i = 0; i < count; ++i)
    {
        g_unk0x006c0a7c = 9;
        g_unk0x6c0a50.m_progress += g_unk0x006774a0 / (int)count;
        g_unk0x6c0a50.FUN_00523300();
        switch (FUN_005e1d00(file))
        {
        case 0x4f494c45:
            FUN_004c1d20(file);
            break;
        case 0x424f5247:
            FUN_004c1df0(file);
            break;
        case 0x424f4f4d:
            FUN_004c2150(file);
            break;
        case 0x53434f54:
            FUN_004c2200(file, beamMes);
            break;
        case 0x544f544f:
            FUN_004e35f0(file);
            break;
        case 0x4d454f57:
            FUN_005e2300(file);
            SBAssert(0, "P:\\Robin Hood\\RHengine.cpp", 0x544,
                // STRING: GAME 0x006af3b0
                "ACHTUNG : Unimplemented chunk skipped");
            break;
        default:
            SBAssert(1, "P:\\Robin Hood\\RHengine.cpp", 0x548,
                // STRING: GAME 0x006af390
                "Unknow sub chunk in actor chunk");
            break;
        }
    }
    FUN_005e20c0(file);
}

// FUNCTION: GAME 0x004c1f90
void RHEngine::InitializeBuildingTenantsFromMissionStream(SBFile &file)
{
    void *buildings = (char *)g_unk0x6c0a9c + 0x40c0;
    FUN_005e1d50(file, 0x43415645, 3);
    unsigned short count;
    file.Access(&count, 2);
    for (unsigned short i = 0; i < count; ++i)
    {
        void *building = (*(void ***)((char *)buildings + 4))[i];
        unsigned short tenants;
        file.Access(&tenants, 2);
        for (unsigned short j = 0; j < tenants; ++j)
        {
            unsigned short index;
            file.Access(&index, 2);
            void *actor = (*(void ***)(m_48d8 + 4))[index];
            if ((*(unsigned *)((char *)actor + 4) & 7) == 4)
                ((RHEngineBuildingCalls *)building)->FUN_0057e680(actor);
            else
                SBAssert(0, "P:\\Robin Hood\\RHengine.cpp", 0x5d9,
                    // STRING: GAME 0x006af3d8
                    "VERBOTEN : A building occupant is not a human !");
        }
        char flag;
        file.Access(&flag, 1);
        *((char *)building + 0x118) = flag;
    }
    FUN_005e20c0(file);
}

// STUB: GAME 0x004c2200
// Parked: 44.80%.
void RHEngine::FUN_004c2200(SBFile &file, std::vector<RHbeamMe> &beamMes)
{
    unsigned index = 0;
    RHbeamMe beamMe;
    RHProfileText unused;
    FUN_005e1d50(file, 0x53434f54, 4);
    unsigned short count;
    file.Access(&count, 2);
    for (unsigned short i = 0; i < count; ++i)
    {
        short x, y;
        file.Access(&x, 2);
        file.Access(&y, 2);
        beamMe.m_point.m_x = (float)x;
        beamMe.m_point.m_y = (float)y;
        unsigned value;
        file.Access(&value, 4);
        beamMe.m_10 = (unsigned short)value;
        file.Access(&value, 4);
        beamMe.m_1c = value;
        file.Access(&beamMe.m_c, 2);
        file.Access(&beamMe.m_a, 2);
        file.Access(&beamMe.m_8, 2);
        if (beamMe.m_8 > *(unsigned short *)((char *)this + 0x3fb8))
            SBAssert(1, "P:\\Robin Hood\\RHengine.cpp", 0x654,
                // STRING: GAME 0x006af44c
                "AUF WIEDERSEHEN : Beam-me at (%f,%f) lying on wrong layer (%d) !",
                beamMe.m_point.m_x, beamMe.m_point.m_y, beamMe.m_8);
        void *sector = beamMe.m_a == 0xffff
            ? *(void **)((char *)this + 0x42a0)
            : (*(void ***)((char *)this + 0x4180))[beamMe.m_a];
        if ((*(unsigned *)((char *)sector + 0x30) & 3) != 3)
            SBAssert(1, "P:\\Robin Hood\\RHengine.cpp", 0x659,
                // STRING: GAME 0x006af408
                "AUF WIEDERSEHEN : Beam-me at (%f,%f) lying on wrong sector (%d) !",
                beamMe.m_point.m_x, beamMe.m_point.m_y, beamMe.m_a);
        file.Access(&value, 4);
        if (value >= 9)
            value = *(unsigned *)((char *)this + 0x42a4);
        beamMe.m_e = (char)value;
        unsigned char flag;
        RHEngineBeamFlags &flags = *(RHEngineBeamFlags *)&beamMe.m_14;
        file.Access(&flag, 1);
        flags.m_0 = flag;
        file.Access(&flag, 1);
        flags.m_1 = flag;
        file.Access(&flag, 1);
        flags.m_2 = flag;
        file.Access(&flag, 1);
        flags.m_3 = flag;
        file.Access(&flag, 1);
        flags.m_4 = flag;
        file.Access(&flag, 1);
        flags.m_5 = flag;
        file.Access(&flag, 1);
        flags.m_6 = flag;
        file.Access(&flag, 1);
        flags.m_7 = flag;
        file.Access(&flag, 1);
        flags.m_8 = flag;
        file.Access(&flag, 1);
        flags.m_9 = flag;
        beamMe.m_12 = (unsigned short)index++;
        file.Access(&flag, 1);
        if (flag)
            FUN_005e0c90(file, (std::string &)beamMe.m_text);
        else
        {
            unsigned length = strlen(g_unk0x6c0560);
            if (beamMe.m_text.FUN_00402280(length, true))
            {
                memcpy(beamMe.m_text.m_chars, g_unk0x6c0560, length);
                beamMe.m_text.FUN_00402260(length);
            }
        }
        file.Access(&flag, 1);
        beamMe.m_required = flag;
        ((RHEngineBeamCalls *)&beamMes)->FUN_004e4120(beamMes.end(), 1, beamMe);
    }
    FUN_005e20c0(file);
    *(unsigned *)((char *)this + 0x4a4c) = beamMes.size();
}

// STUB: GAME 0x004c28c0
// Parked: 26.09%.
void RHEngine::FUN_004c28c0(const std::string &name)
{
    std::string mapPath, minimapPath, ambiance;
    RHUnk006114c0 minimap, map;
    RHUnk005f4fc0 file;
    switch (*(unsigned *)((char *)this + 0x4ad0))
    {
    case 1:
        // STRING: GAME 0x006af5a0
        ambiance = "\\Day\\";
        break;
    case 2:
        // STRING: GAME 0x006af598
        ambiance = "\\Fog\\";
        break;
    case 4:
        // STRING: GAME 0x006af590
        ambiance = "\\Night\\";
        break;
    case 8:
        // STRING: GAME 0x006af584
        ambiance = "\\Attack\\";
        break;
    case 16:
        // STRING: GAME 0x006af578
        ambiance = "\\Custom1\\";
        break;
    case 32:
        // STRING: GAME 0x006af56c
        ambiance = "\\Custom2\\";
        break;
    case 64:
        // STRING: GAME 0x006af560
        ambiance = "\\Custom3\\";
        break;
    case 128:
        // STRING: GAME 0x006af554
        ambiance = "\\Custom4\\";
        break;
    }
    // STRING: GAME 0x006af54c
    std::string mapExtension(".map");
    mapPath = FUN_004e4b40(FUN_004e4b40(FUN_004e4b40(g_unk0x006c05f0, ambiance), name), mapExtension);
    if (!FUN_005f6400(mapPath))
    {
        mapPath = FUN_004e4b40(FUN_004e4b40(FUN_004e4c70(g_unk0x006c05f0, "\\Day\\"), name), mapExtension);
        if (!FUN_005f6400(mapPath))
        {
            mapPath = FUN_004e4b40(FUN_004e4b40(FUN_004e4c70(g_unk0x006c05f0, "\\"), name), mapExtension);
            if (!FUN_005f6400(mapPath))
                SBAssert(1, "P:\\Robin Hood\\RHengine.cpp", 0x73d,
                    // STRING: GAME 0x006af4f4
                    "STRENG VERBOTEN : Unable to find map file %s in directory %s (ambiance %s), file error",
                    name.c_str(), g_unk0x006c05f0.c_str(), ambiance.c_str());
        }
    }
    ((RHEngineBackgroundCalls *)&map)->FUN_00611660(mapPath);
    g_unk0x006c0a7c = 7;
    g_unk0x6c0a50.m_progress += g_unk0x00677438;
    g_unk0x6c0a50.FUN_00523300();
    float &width = *(float *)((char *)this + 0x4730);
    float &height = *(float *)((char *)this + 0x4734);
    width = (float)map.m_width;
    height = (float)map.m_height;
    RHUnkFXDraw *draw = *(RHUnkFXDraw **)((char *)this + 0xdc);
    unsigned long surface = draw->Unk005e4ed0((int)width, (int)height, 0, 0);
    *(unsigned long *)((char *)this + 0x48c4) = surface;
    ((RHEngineBackgroundCalls *)((char *)this + 0x11c))->FUN_004e7fa0(
        (int)(width * g_unk0x00677680), (int)(height * g_unk0x00677680));
    map.Unk00611e10(draw->m_depth == 16 ? 3 : 2, 0);
    map.Unk00613530(draw, surface);
    g_unk0x006c0a7c = 7;
    g_unk0x6c0a50.m_progress += g_unk0x0067748c;
    g_unk0x6c0a50.FUN_00523300();
    // STRING: GAME 0x006af4ec
    std::string minimapExtension(".min");
    minimapPath = FUN_004e4b40(FUN_004e4b40(FUN_004e4b40(g_unk0x006c05f0, ambiance), name), minimapExtension);
    if (!FUN_005f6400(minimapPath))
    {
        minimapPath = FUN_004e4b40(FUN_004e4b40(FUN_004e4c70(g_unk0x006c05f0, "\\Day\\"), name), minimapExtension);
        if (!FUN_005f6400(minimapPath))
        {
            minimapPath = FUN_004e4b40(FUN_004e4b40(FUN_004e4c70(g_unk0x006c05f0, "\\"), name), minimapExtension);
            if (!FUN_005f6400(minimapPath))
                SBAssert(1, "P:\\Robin Hood\\RHengine.cpp", 0x76b,
                    // STRING: GAME 0x006af490
                    "STRENG VERBOTEN : Unable to find mini-map file %s in directory %s (ambiance %s), file error",
                    name.c_str(), g_unk0x006c05f0.c_str(), ambiance.c_str());
        }
    }
    ((RHEngineBackgroundCalls *)&minimap)->FUN_00611660(minimapPath);
    surface = draw->Unk005e4ed0(*(int *)&minimap.m_width, *(int *)&minimap.m_height, 0, 0);
    *(unsigned long *)((char *)this + 0x48c8) = surface;
    minimap.Unk00613530(draw, surface);
    g_unk0x006c0a7c = 7;
    g_unk0x6c0a50.m_progress += g_unk0x0067748c;
    g_unk0x6c0a50.FUN_00523300();
}

// deferred: unannotated pending reccmp #534 (0x004c3a10)
bool RHEngine::SerializeNestedA(SBFile &file, void *storage)
{
    RHENGINE_POINTER_BODY((*(void **)storage))
}

// deferred: unannotated pending reccmp #534 (0x004c3a10)
bool RHEngine::SerializeElementPointer(SBFile &file, RHElement *&element)
{
    RHENGINE_POINTER_BODY((*(void **)&element))
}

// FUNCTION: GAME 0x004c3af0
bool RHEngine::FUN_004c3af0(SBFile &file, void *&value)
{
    RHENGINE_POINTER_BODY(value)
}

// FUNCTION: GAME 0x004c3bd0
bool RHEngine::FUN_004c3bd0(SBFile &file, void *&value)
{
    RHENGINE_POINTER_BODY(value)
}

// deferred: unannotated pending reccmp #534 (0x004c3cb0)
bool RHReconnaissanceEngine::Unk004c3cb0(SBFile &file, void *&value)
{
    RHENGINE_POINTER_BODY(value)
}

// FUNCTION: GAME 0x004c3d90
bool RHEngine::FUN_004c3d90(SBFile &file, void *&value)
{
    RHENGINE_POINTER_BODY(value)
}

// deferred: unannotated pending reccmp #534 (0x004c3e70)
bool RHEngine::SerializeNestedB(SBFile &file, void *storage)
{
    RHENGINE_POINTER_BODY((*(void **)storage))
}

// FUNCTION: GAME 0x004c3f50
bool RHEngine::FUN_004c3f50(SBFile &file, void *&value)
{
    RHENGINE_POINTER_BODY(value)
}

// FUNCTION: GAME 0x004c4030
bool RHEngine::FUN_004c4030(SBFile &file, void *&value)
{
    RHENGINE_POINTER_BODY(value)
}

// deferred: unannotated pending reccmp #534 (0x004c4110)
bool RHReconnaissanceEngine::Unk004c4110(SBFile &file, void *&value)
{
    RHENGINE_POINTER_BODY(value)
}

// FUNCTION: GAME 0x004c41f0
bool RHEngine::FUN_004c41f0(SBFile &file, void *&value)
{
    RHENGINE_POINTER_BODY(value)
}

// FUNCTION: GAME 0x004c42d0
bool RHEngine::FUN_004c42d0(SBFile &file, void *&value)
{
    RHENGINE_POINTER_BODY(value)
}

// FUNCTION: GAME 0x004c43b0
bool RHEngine::FUN_004c43b0(SBFile &file, void *&value)
{
    RHENGINE_POINTER_BODY(value)
}

// FUNCTION: GAME 0x004c4490
bool RHEngine::FUN_004c4490(SBFile &file, void *&value)
{
    RHENGINE_POINTER_BODY(value)
}

#undef RHENGINE_POINTER_BODY

class RHUnk00452030
{
public:
    int FUN_00453d60(const void *description);
};

class RHElementBonus
{
public:
    enum BonusType { BONUS_UNKNOWN = 0 };
    RHElementBonus(BonusType type, bool flag, unsigned short quantity);
    ~RHElementBonus();
    char m_data[0x100];
};

class RHUnk0048a970;
extern RHUnk0048a970 *g_unk0x6c0b3c;

class RHEngineSerializationCalls
{
public:
    void FUN_0058a430();
    void FUN_005a5c50();
    void FUN_0048fa30();
    void FUN_004d88e0(void *element, int first, int second);
    void FUN_0050f000();
    void FUN_0050f010();
};

void FUN_005a5cd0();

class RHEngineSerializedElement
{
public:
    virtual ~RHEngineSerializedElement();
    virtual void Unk04();
    virtual void Unk08();
    virtual void Unk0c();
    virtual void Unk10();
    virtual void Unk14();
    virtual void Unk18();
    virtual void Unk1c();
    virtual void Unk20();
    virtual void Unk24();
    virtual void Unk28();
    virtual void Unk2c();
    virtual void Unk30();
    virtual void Unk34();
    virtual void Unk38();
    virtual void Unk3c();
    virtual bool Serialize(SBFile &file);
};

// GLOBAL: GAME 0x006c0a86
char g_unk0x006c0a86 = 0;

#define RHENGINE_ACCESS(storage, size, line) \
    if (file.Access(storage, size) < 0) \
    { \
        SBString *error = file.GetError(); \
        SBAssert(0, "P:\\Robin Hood\\RHengine.cpp", line, \
            "Serialize failed reason is %s", error->m_chars ? error->m_chars : ""); \
        return false; \
    }

// STUB: GAME 0x004c4570
// Parked: 39.37%; partial scalar and element serialization.
bool RHEngine::FUN_004c4570(SBFile &file)
{
    char *engine = (char *)this;
    g_unk0x006c0a86 = 0;
    if (file.m_version >= 13)
    {
        RHENGINE_ACCESS(engine + 0x4d98, 4, 0x9bf)
    }
    if (file.m_version >= 12)
    {
        RHENGINE_ACCESS(engine + 0x4d85, 1, 0x9c4)
    }
    else
        engine[0x4d85] = 1;
    if (file.m_version == 2 || file.m_version >= 11)
    {
        RHENGINE_ACCESS(engine + 0x4d84, 1, 0x9cd)
    }
    if (!file.m_bLoading)
        ((RHEngineSerializationCalls *)(engine + 0x43f8))->FUN_0058a430();
    ((SBGeoPoint2D *)(engine + 0x4738))->Serialize(file);
    RHENGINE_ACCESS(engine + 0x475c, 4, 0x9fb)
    ((SBGeoPoint2D *)(engine + 0x4748))->Serialize(file);
    RHENGINE_ACCESS(engine + 0x4758, 2, 0x9fe)
    RHENGINE_ACCESS(engine + 0x45b0, 4, 0x9ff)
    RHENGINE_ACCESS(engine + 0x45b4, 2, 0xa00)
    RHENGINE_ACCESS(engine + 0x4764, 4, 0xa01)
    RHENGINE_ACCESS(engine + 0x4760, 4, 0xa02)
    RHENGINE_ACCESS(engine + 0x4780, 0x140, 0xa04)
    RHENGINE_ACCESS(engine + 0x4a94, 4, 0xa14)
    RHENGINE_ACCESS(engine + 0xd0, 1, 0xa19)
    RHENGINE_ACCESS(engine + 0x4a50, 1, 0xa1c)
    RHENGINE_ACCESS(engine + 0x4a51, 1, 0xa1d)
    if (file.m_bLoading)
    {
        engine[0x4a52] = 0;
        engine[0x4a53] = 0;
        engine[0x4a54] = 0;
    }
    RHENGINE_ACCESS(engine + 0x4750, 8, 0xa26)
    RHENGINE_ACCESS(engine + 0x4719, 1, 0xa29)
    FUN_005e0c90(file, *(std::string *)(engine + 0xb4));
    if (!FUN_004c6040(file))
        return false;
    if (file.m_bLoading)
    {
        FUN_005a5cd0();
        void **first = *(void ***)(engine + 0x4160);
        unsigned short count = first ? (unsigned short)(*(void ***)(engine + 0x4164) - first) : 0;
        for (unsigned short i = 0; i < count; ++i)
            ((RHEngineSerializationCalls *)first[i])->FUN_005a5c50();
        if (file.m_version < 6)
        {
            *(unsigned *)(engine + 0x4d88) = 0;
            *(unsigned *)(engine + 0x4d8c) = 0;
            *(unsigned *)(engine + 0x4d90) = 0;
            *(unsigned *)(engine + 0x4d94) = 0;
        }
    }
    return true;
}

// STUB: GAME 0x004c6040
// Parked: 19.63%; partial element construction cases.
bool RHEngine::FUN_004c6040(SBFile &file)
{
    char *engine = (char *)this;
    void **first = *(void ***)(engine + 0x48dc);
    void **last = *(void ***)(engine + 0x48e0);
    unsigned count = first ? last - first : 0;
    for (unsigned i = 1; i < count; ++i)
    {
        void *value = first[i];
        unsigned j = i;
        while (j && *(unsigned *)((char *)value + 0xc) < *(unsigned *)((char *)first[j - 1] + 0xc))
        {
            first[j] = first[j - 1];
            --j;
        }
        first[j] = value;
    }
    if (!file.m_bLoading)
    {
        g_unk0x006c0a86 = 1;
        RHENGINE_ACCESS(&count, 4, 0xc0a)
        for (unsigned pass = 0; pass < 2; ++pass)
        {
            for (unsigned index = 0; index < count; ++index)
            {
                void *element = first[index];
                unsigned short type = *(unsigned short *)((char *)element + 0x10);
                unsigned id = *(unsigned *)((char *)element + 0xc);
                RHENGINE_ACCESS(&type, 2, pass ? 0xc25 : 0xc12)
                RHENGINE_ACCESS(&id, 4, pass ? 0xc26 : 0xc13)
                if (type == 1)
                {
                    int description = g_unk0x6c07fc->FUN_00453d60(
                        *(void **)((char *)element + 0x5f8));
                    RHENGINE_ACCESS(&description, 4, pass ? 0xc2d : 0xc1a)
                }
                if (pass && !((RHEngineSerializedElement *)element)->Serialize(file))
                    return false;
            }
        }
        return true;
    }
    ((RHEngineSerializationCalls *)g_unk0x6c0b3c)->FUN_0050f000();
    unsigned cutoff = *(unsigned *)(engine + 0x4a48);
    for (int removed = (int)count - 1; removed >= 0; --removed)
    {
        void *element = (*(void ***)(engine + 0x48dc))[removed];
        if (*(unsigned *)((char *)element + 0xc) >= cutoff)
        {
            ((RHEngineSerializationCalls *)this)->FUN_004d88e0(element, 0, 0);
            if (element)
                delete (RHEngineSerializedElement *)element;
        }
    }
    unsigned serializedCount;
    RHENGINE_ACCESS(&serializedCount, 4, 0xc50)
    for (unsigned created = 0; created < serializedCount; ++created)
    {
        unsigned short type;
        unsigned id, description;
        RHENGINE_ACCESS(&type, 2, 0xc54)
        RHENGINE_ACCESS(&id, 4, 0xc55)
        if (type == 1)
        {
            RHENGINE_ACCESS(&description, 4, 0xc5a)
        }
        void *element = 0;
        first = *(void ***)(engine + 0x48dc);
        if (id < cutoff)
            for (unsigned existing = 0; existing < count; ++existing)
                if (*(unsigned *)((char *)first[existing] + 0xc) == id)
                {
                    element = first[existing];
                    break;
                }
        if (element)
            continue;
        int bonusType = -1;
        switch (type)
        {
        case 1:
            element = new RHUnk0048f280((*(void ***)((char *)g_unk0x6c07fc + 0x108))[description]);
            *(unsigned short *)((char *)element + 0x10) = 1;
            ((RHEngineSerializationCalls *)element)->FUN_0048fa30();
            break;
        case 0x4001: bonusType = 12; break;
        case 0x4003: bonusType = 1; break;
        case 0x4004: bonusType = 11; break;
        case 0x4006: bonusType = 13; break;
        case 0x4007: bonusType = 17; break;
        case 0x4008: bonusType = 16; break;
        case 0x4009: bonusType = 4; break;
        case 0x400a: bonusType = 5; break;
        case 0x400b: bonusType = 19; break;
        default: return false;
        }
        if (bonusType >= 0)
            element = new RHElementBonus((RHElementBonus::BonusType)bonusType, false, 1);
        *(unsigned *)((char *)element + 0xc) = id;
        ((RHEngineReinforcementCalls *)this)->FUN_004d8460(element, 0, 1);
    }
    g_unk0x006c0a86 = 1;
    first = *(void ***)(engine + 0x48dc);
    count = first ? *(void ***)(engine + 0x48e0) - first : 0;
    for (unsigned restored = 0; restored < serializedCount; ++restored)
    {
        unsigned short type;
        unsigned id, description;
        RHENGINE_ACCESS(&type, 2, 0xd3a)
        RHENGINE_ACCESS(&id, 4, 0xd3b)
        if (type == 1)
        {
            RHENGINE_ACCESS(&description, 4, 0xd40)
        }
        void *element = 0;
        for (int found = (int)count - 1; found >= 0; --found)
            if (*(unsigned *)((char *)first[found] + 0xc) == id)
            {
                element = first[found];
                break;
            }
        if (!element || !((RHEngineSerializedElement *)element)->Serialize(file))
            return false;
    }
    ((RHEngineSerializationCalls *)g_unk0x6c0b3c)->FUN_0050f010();
    return true;
}

#undef RHENGINE_ACCESS

// STUB: GAME 0x004e2390
// Parked: 53.01%.
void RHEngine::FUN_004e2390(void *actor)
{
    RHbeamMe beamMe;
    void **first = *(void ***)((char *)this + 0x4220);
    unsigned count = first ? *(void ***)((char *)this + 0x4224) - first : 0;
    if (!count)
    {
        SBAssert(0,
            // STRING: GAME 0x006af60c
            "P:\\Robin Hood\\RHengine.cpp", 0x3e44,
            // STRING: GAME 0x006af628
            "ACH DU DICKES SCHWEIN : Reinforcement cannot arrive because there is no reinforcement door !");
        return;
    }
    void *door = first[(unsigned)rand() % count];
    SBGeoPoint2D &origin = *(SBGeoPoint2D *)((char *)door + 0x18);
    beamMe.m_point = origin;
    beamMe.m_8 = *(unsigned short *)((char *)door + 0x14);
    void *doorSector = *(void **)((char *)door + 0xc);
    beamMe.m_a = doorSector ? *(unsigned short *)((char *)doorSector + 0x38) : 0xffff;
    void *sector = beamMe.m_a == 0xffff
        ? *(void **)((char *)this + 0x42a0)
        : (*(void ***)((char *)this + 0x4180))[beamMe.m_a];
    RHBonusProjection *projection = ((RHUnk0057d800 *)sector)->Unk(origin);
    if (!projection)
        beamMe.m_c = 0xffff;
    else
        beamMe.m_c = (unsigned short)((RHEngineReinforcementCalls *)((char *)this + 0x425c))->FUN_004e4460((void **)&projection, 1);
    beamMe.m_e = (char)*(unsigned *)((char *)this + 0x42a4);
    beamMe.m_10 = 0;
    void *description = ((RHEngineReinforcementCalls *)g_unk0x6c07fc)->FUN_00452130(*(void **)((char *)actor + 0x5fc));
    if (!description)
        return;
    ((RHEngineReinforcementCalls *)actor)->FUN_004936a0(0);
    RHUnk0048f280 *reinforcement = new RHUnk0048f280(description);
    *((char *)description + 0x44) = 1;
    *(unsigned short *)((char *)description + 0x3c) = 0xffff;
    ((RHEngineReinforcementCalls *)reinforcement)->FUN_00491fd0(beamMe);
    *(unsigned short *)((char *)reinforcement + 0x10) = 1;
    ((RHEngineReinforcementCalls *)this)->FUN_004d8460(reinforcement, 1, 1);
    FUN_0048c5b0(reinforcement, 0);
    RHUnk00582220 *sequence = new RHUnk00582220;
    RHUnk00588830 *arrival = new RHUnk00588830(1, 0x13, reinforcement, 6, 0);
    *(void **)((char *)arrival + 0x7c) = door;
    *(int *)((char *)arrival + 0x88) = 2;
    ((RHUnk00585500 *)arrival)->Unk(sequence);
    SBGeoPoint2D destination;
    unsigned attempt;
    SBGeoPoint2D &exit = *(SBGeoPoint2D *)((char *)door + 0x20);
    for (attempt = 0; attempt < 10; ++attempt)
    {
        destination = exit + SBGeoVector2D(
            (float)(rand() * 100) * g_unk0x00677f7c - g_unk0x00677484,
            (float)(rand() * 100) * g_unk0x00677f7c - g_unk0x00677484);
        if (((RHEngineReinforcementCalls *)((char *)this + 0x11c))->FUN_004f6c20(
            exit, destination, *(unsigned short *)((char *)door + 0x16),
            ((RHEngineReinforcementCalls *)reinforcement)->FUN_004a49e0()))
            break;
    }
    if (attempt < 10)
    {
        RHUnk005883a0 *movement = new RHUnk005883a0(2, 0x14, reinforcement, 6, destination, 0, 0, 1);
        ((RHUnk00585500 *)movement)->Unk(sequence);
    }
    ((RHUnk0058a3d0 *)((char *)this + 0x43f8))->Unk(g_unk0x6c0560, 0, sequence);
}

// FUNCTION: GAME 0x004e3020
RHElementActorPC *RHEngine::GetPC(RHPCDescription *description) const
{
    unsigned count = PCCount();
    for (unsigned i = 0; i < count; ++i)
    {
        void *actor = m_493c[i];
        if (*(RHPCDescription **)((char *)actor + 0x5f8) == description)
            return (RHElementActorPC *)actor;
    }
    void *profile = *(void **)((char *)description + 0x40);
    SBString *name = (SBString *)((char *)profile + 0x14);
    SBAssert(0, "P:\\Robin Hood\\RHengine.cpp", 0x3edf,
        // STRING: GAME 0x006afa58
        "ACHTUNG : PC for profile \"%s\" was not found !", name->m_chars ? name->m_chars : "");
    return 0;
}

// FUNCTION: GAME 0x004e3090
RHElementActorPC *RHEngine::GetPC(const RHCharacterProfile *profile) const
{
    unsigned count = PCCount();
    for (unsigned i = 0; i < count; ++i)
    {
        void *actor = m_493c[i];
        if (*(const RHCharacterProfile **)((char *)actor + 0x5fc) == profile)
            return (RHElementActorPC *)actor;
    }
    const char *name = *(const char **)((const char *)profile + 0x18);
    SBAssert(0, "P:\\Robin Hood\\RHengine.cpp", 0x3efc,
        "ACHTUNG : PC for profile \"%s\" was not found !", name ? name : "");
    return 0;
}

// FUNCTION: GAME 0x004e3520
void RHEngine::LoadDynRes(unsigned mission)
{
    char directory[0x104];
    GetCurrentDirectoryA(0x104, directory);
    SetCurrentDirectoryA(g_unk0x006c0664 ? g_unk0x006c0664 : "");
    if (!((RHMapDescription *)((char *)this + 0x4d68))->FUN_0063cda0(mission))
    {
        SBAssert(0, "P:\\Robin Hood\\RHengine.cpp", 0x4055,
            "Warning: unable to load the resource description for the mission '%s'\n", &mission);
    }
    SetCurrentDirectoryA(directory);
}

void RHEngine::Emit(SBFile &file, void *&value)
{
    InitializeActorsFromMissionStream(file, *(std::vector<RHbeamMe> *)value);
    InitializeBuildingTenantsFromMissionStream(file);
    FUN_004c3af0(file, value);
    FUN_004c3bd0(file, value);
    FUN_004c3d90(file, value);
    FUN_004c3f50(file, value);
    FUN_004c4030(file, value);
    FUN_004c41f0(file, value);
    FUN_004c42d0(file, value);
    FUN_004c43b0(file, value);
    FUN_004c4490(file, value);
    GetPC((RHPCDescription *)value);
    GetPC((const RHCharacterProfile *)value);
    LoadDynRes(0);
}
