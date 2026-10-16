// RHElementActorCivilian — declarations shared by RHElementActorCivilian.cpp
// (decompiled TU) and RHElementActorCivilian_stubs.cpp (external-symbol stubs).
//
// BINDING (0x004711c0): RHElementActorCivilian::Serialize(SBFile&). See
// src/RHElementActorCivilian.cpp for the evidence chain.
//
// Member layout is derived from the target instructions of
// RHElementActorCivilian::Serialize (0x004711c0): the base RHElementActorNPC
// occupies [0x00, 0x704) (vptr + its own fields), and RHElementActorCivilian's
// own 4-byte field sits at +0x704. Only the bytes the matched function touches
// are laid out; every other byte is opaque padding.

#include "SB.h"
#include "Decomp.h"
#include <vector>
#include <string>

template<class T> T &RHCivilianField(void *object, unsigned offset)
{
    return *(T *)((char *)object + offset);
}

// SIZE 0x34
struct RHCivilianProfileView
{
    undefined m_00[0x30]; // 0x00
    int m_30; // 0x30
};

// SIZE 0x704
class RHElementActorNPC
{
public:
    virtual bool Serialize(SBFile &file); // vtable+0x00 (serializer-only view)

private:
    char m_unkBase[0x700]; // [0x04, 0x704): RHElementActorNPC-owned, untouched here
};

// SIZE 0x70c
class RHElementActorCivilian : public RHElementActorNPC
{
public:
    virtual bool Serialize(SBFile &file); // vtable+0x00 (serializer-only view)

    bool FUN_00470ca0();
    bool FUN_00470cc0();
    bool FUN_00470ce0();
    bool FUN_00470310();
    void FUN_00470a10(SBFile &file);
    void FUN_00470480(SBFile &file);
    bool FUN_00470d00(void *first, void *second, int kind);
    bool FUN_00470e50(void *first, void *second, int kind);
    void *FUN_00470f70(void *element);
    void FUN_00471090();

    void Emit(SBFile &file);

private:
    undefined4 m_unk704; // 0x704
    RHCivilianProfileView *m_708; // 0x708
};


// SIZE 0x19e
class RHCivilianSpriteView
{
public:
    unsigned short FUN_005bdef0();
    unsigned short FUN_005bdf20();
    undefined m_00[0x19a]; // 0x00
    undefined2 m_19a; // 0x19a
    undefined2 m_19c; // 0x19c
};

// SIZE 0x10e
class RHUnk005ef320
{
public:
    unsigned short Unk(int red, int green, int blue);
    undefined m_00[0x10c]; // 0x00
    undefined2 m_10c; // 0x10c
};

// SIZE 0x08
class SBGeoPoint2D
{
public:
    SBGeoPoint2D();
    SBGeoPoint2D(float x, float y);
    ~SBGeoPoint2D();
    SBGeoPoint2D &operator=(const SBGeoPoint2D &other);
    float m_x; // 0x00
    float m_y; // 0x04
};

// SIZE 0x08
class SBGeoVector2D : public SBGeoPoint2D
{
public:
    SBGeoVector2D();
    SBGeoVector2D(const SBGeoPoint2D &other);
    ~SBGeoVector2D() {}
    SBGeoVector2D operator-() const;
};

// SIZE 0x14
class SBGeoBoundingBox2D
{
public:
    SBGeoBoundingBox2D(const SBGeoPoint2D &first, const SBGeoPoint2D &second);
    ~SBGeoBoundingBox2D() {}
    SBGeoBoundingBox2D &operator=(const SBGeoBoundingBox2D &other);
    SBGeoBoundingBox2D FUN_006090d0(const SBGeoVector2D &other) const;
    bool FUN_00608400(const SBGeoPoint2D &point) const;
    SBGeoPoint2D m_p0; // 0x00
    SBGeoPoint2D m_p1; // 0x08
    bool m_flag; // 0x10
};

// SIZE 0x70
class RHCampaignProfiles
{
public:
    RHCampaignProfiles();
    ~RHCampaignProfiles();
    undefined m_00[0x70]; // 0x00
};

class RHUnkTargetSprite
{
public:
    bool FUN_005bd050(int kind, const std::string &name, const std::string &profile, int flag);
};

class RHUnkFXDraw
{
public:
    unsigned long Unk005e4ed0(int width, int height, int flags, int retain);
};

struct RHBonusProjection;
class RHBonusInfoBase
{
public:
    void FUN_0055f290();
    void FUN_0055fa20(RHBonusProjection *projection);
};

class RHBonusInfo
{
public:
    void FUN_005bd560(void *action, bool initialize);
};

class RHUnkPathActorInfoBase
{
public:
    void *Unk0055fa10(int index);
};

class RHEngine;
class RHElementActor
{
public:
    void InitializeScript(std::string &script);
};

extern RHEngine *g_pEngine;
extern RHCampaignProfiles *g_unk0x6c0e84;
extern RHUnk005ef320 *g_unk0x6c11d0;
extern char g_unk0x6c0691;
bool FUN_005e0c90(SBFile &file, std::string &value);

// Target 0x005e1b70 (RHSerializeName): serialises a type-name tag into the
// stream. Declared identically in include/RHElementObject.h,
// include/RHMissionStat.h and include/RHHumanStatus.h; no TU includes more than
// one of those headers.
void RHSerializeName(SBFile &file, const char *name);
