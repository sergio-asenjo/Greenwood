#ifndef RHENGINE_H
#define RHENGINE_H

#include <vector>
#include <string>
#include "Decomp.h"
#include "RHEngineElementArray.h"
#include "RHSectorActorList.h"
#include "SBList.h"
#include "RHLoadingScreenCore.h"

class SBFile;
class RHElement;
class RHPCDescription;
class RHCharacterProfile;
class RHElementActor;
class RHElementActorPC;
class RHElementActorNPC;
class RHElementActorHuman;
class RHElementActorSoldier;
class SBDrawManager;
class RHFrameHolder;
struct RHnoise;
class RHMessenger;
class RHElementMobile;
class RHElementFX;
class RHMission;
class SBGeoPoint2D;
class SBGeoBoundingBox2D;
class RHDialogueSet;
class RHSectorGateCalls;
class RHFastFindGrid;
struct RHbeamMe;
struct RHUnk004e4660Entry;
struct RHEngineDrawEntry;
struct RHUnk004e48b0Entry;
class RHUnk004e49f0Entry;
class RHSequenceElementCalls;

unsigned long FUN_005e1d00(SBFile &file);
void FUN_005e2300(SBFile &file);

class RHEngineBuildingCalls
{
public:
    void FUN_0057e680(void *actor);
};

class RHPortraitBar;
typedef RHPortraitBar RHEngineRosterCalls;

#include "RHEngineMenuStateCalls.h"

#include "RHEngineSequenceStateCalls.h"

class RHUnk0054eab0;

class RHEngineGridCalls
{
public:
    void FUN_004eb830(SBFile &file);
    void FUN_004ebab0(SBFile &file);
    void FUN_004efd10(void *value, unsigned short layer, bool mode);
    short FUN_004e9760(const SBGeoPoint2D &point, const SBGeoPoint2D &origin, void *&sector, unsigned short &layer);
    short FUN_004e9920(const SBGeoPoint2D &point, const SBGeoPoint2D &origin, void *&sector, unsigned short &layer);
};

class RHEngineContinuationSectorCalls
{
public:
    virtual ~RHEngineContinuationSectorCalls();
    virtual bool Serialize(SBFile &file, bool mode);
};

class RHUnk0057ee40
{
public:
    void *FUN_0057ee60(unsigned flags);
    RHUnk0057ee40();
    ~RHUnk0057ee40();
    undefined m_00[0x68];
};

extern RHFastFindGrid *g_unk0x6c0a9c;
void FUN_005e1d50(SBFile &file, unsigned long tag, int level);
void FUN_005e20c0(SBFile &file);
void FUN_004be5c0(SBFile &file, void *&value);
void SerializeLocation(SBFile &file, void *&value);

// SIZE 0x4d68 (partial layout)
class RHElementActorPC;

class RHUnk0051e5e0;

class RHPathFinder;
struct RHpathRequest;

class RHEngine
{
public:
    void AddElement(RHElement *element, bool initialize, bool registerElement);
    bool RemoveElement(RHElement *element, bool uninitialize, bool deferred);
    void FUN_004da7a0(unsigned long surface, const SBGeoBoundingBox2D &view, float scale);
    void FUN_004dae10(unsigned long surface, const SBGeoBoundingBox2D &view, float scale);
    void FUN_004e39b0(RHElementActorHuman *actor, bool value);
    bool TurnPathFinderOn();
    void FUN_004c9d20(void *box);
    void FUN_004ca410(RHSequenceElementCalls *element);
    // FUNCTION: GAME 0x0049b590
    bool FUN_0049b590(void *actor)
    {
        if (actor)
            return m_49f8.Find((RHElementActor *)actor, true) != -1;
        return m_49f8.m_count != 0;
    }
    void TurnPathFinderOff();
    void ProcessPathRequests(const SBGeoBoundingBox2D &bounds);
    void PerformPathFinderStateChange(unsigned short layer, unsigned short sector, unsigned long state, bool mode);
    void FUN_004d2b70(void *actor);
    bool FUN_004c0340(SBGeoPoint2D &point);
    bool FUN_004c04a0();
    unsigned short FUN_004d16b0(void *first, void *second, unsigned third);
    bool FUN_004d1840();
    bool FUN_004d1aa0();
    void FUN_004d1d00();
    void FUN_004d1f50();
    void FUN_004d21b0(bool enabled, bool queued);
    void FUN_004c8120(void *actor);
    unsigned int FUN_004d2340(int type);
    void FUN_004d2d60(unsigned surface, const SBGeoBoundingBox2D &bounds, float scale,
        unsigned short layer, bool first, bool second, bool third);
    void FUN_004c38d0(SBFile &file, unsigned *value);
    void FUN_004dee70(float *point);
    void FUN_004dce20(void *actor);
    void FUN_004dcfd0(void *actor, unsigned short action);
    void FUN_004ddfb0();
    int FUN_004deeb0(const SBGeoPoint2D &point, SBGeoPoint2D &result);
    void FUN_004defa0(char flag);
    void FUN_004df070(void *value, char flag);
    void FUN_004df330(const SBGeoPoint2D &point, bool first, bool second);
    void FUN_004df550(const SBGeoPoint2D &point, bool queued, bool immediate, void *provided);
    void FUN_004df7b0(const SBGeoPoint2D &point, bool flag);
    void FUN_004dfb50(const SBGeoPoint2D &point, bool flag);
    void FUN_004dfcf0(const SBGeoPoint2D &point, bool queued);
    void FUN_004df950(const SBGeoPoint2D &point, char flag);
    void FUN_004dfe70(const SBGeoPoint2D &point, bool queued);
    void *FUN_004e04c0(int type, const SBGeoPoint2D &point, bool useCache, bool notify);
    void FUN_004e0550(const SBGeoPoint2D &point, bool first, bool second);
    void FUN_004e0770(const SBGeoPoint2D &point, bool first, bool second);
    void FUN_004e0bf0(const SBGeoPoint2D &point, bool flag, bool);
    void FUN_004e14a0(const SBGeoPoint2D &point, bool flag, bool);
    void FUN_004e1630(const SBGeoPoint2D &point, bool flag);
    void FUN_004e09d0(const SBGeoPoint2D &point, bool queued, bool immediate);
    void FUN_004e0d80(const SBGeoPoint2D &point, bool queued, bool immediate);
    void FUN_004e17c0(void *actor, int value);
    void FUN_004e0030(const SBGeoPoint2D &point, bool queued, char flag);
    void FUN_004e0fb0(const SBGeoPoint2D &point, bool queued, bool immediate, void *provided);
    void FUN_004debe0();
    void FUN_004debf0(const SBGeoPoint2D &point);
    unsigned FUN_004e19c0(unsigned value);
    unsigned FUN_004e1f30(unsigned value);
    bool FUN_004e3cd0();
    bool FUN_004e1890();
    int FUN_004e34f0();
    void FUN_004e36d0();
    int FUN_004e3720(void *, int, unsigned short, void *, void *);
    unsigned FUN_004e4110(unsigned value);
    bool InitializeFromMission(RHMission *mission);
    bool FUN_004c4570(SBFile &file);
    void FUN_004c3740();
    bool FUN_004c6040(SBFile &file);
    int FUN_004c6ef0();
    bool FUN_004c7c90();
    bool FUN_004d2330(int type);
    int FUN_004c7cc0();
    bool FUN_004c7cd0();
    bool FUN_004c7cf0();
    void FUN_004c8140();
    void FUN_004c94c0();
    bool FUN_004c9b30(unsigned long destination);
    unsigned FUN_004c7d50();
    bool FUN_004c7d80(void *first, int second, void **result);
    bool FUN_004c7e10(void *first, int second, void **result);
    void FUN_004e3c20(void *point);
    void FUN_004d8fd0(RHPCDescription *description);
    void SelectFollowElement(RHElementActor *actor);
    __forceinline RHElementActor *FollowedElement() const
    {
        return *(const char *)((const char *)this + 0x4719) == 1 ?
            *(RHElementActor *const *)((const char *)this + 0xd8) : 0;
    }
    void FUN_004d9420();
    void DisplayNoises(const SBGeoBoundingBox2D &bounds, float scale);
    void DisplayNoise(RHnoise *noise, unsigned short startRadius, const SBGeoBoundingBox2D &bounds, float scale);
    void FUN_004d52d0(void *first, void *second, float third);
    void FUN_004d5320(const void *value);
    void FUN_004d53f0(void *surface, const SBGeoBoundingBox2D &bounds, float scale);
    bool FUN_004c0040();
    bool FUN_004c02d0();
    void FUN_004d3d00(void *first, const SBGeoBoundingBox2D &second, float third, unsigned fourth, unsigned fifth, unsigned sixth);
    void FUN_004d3e90(unsigned long surface, const SBGeoBoundingBox2D &bounds, float scale, unsigned fourth, unsigned fifth, unsigned sixth);
    void FUN_004d40a0(void *first, const SBGeoBoundingBox2D &second, unsigned third, unsigned fourth, unsigned fifth, unsigned short sixth);
    void FUN_004d4230(const SBGeoBoundingBox2D &bounds, unsigned second);
    void FUN_004d7800(unsigned long surface, const SBGeoBoundingBox2D &bounds, float scale);
    void FUN_004d7820(unsigned long surface, const SBGeoBoundingBox2D &bounds, float scale);
    void FUN_004d7f40(SBGeoBoundingBox2D &bounds, float scale);
    void FUN_004d7460(void *first, void *second, float third);
    void FUN_004d7490(unsigned long surface, SBGeoBoundingBox2D &view, float scale);
    void FUN_004d5a90(void *actor);
    void FUN_004d5ba0(void *actor, float alpha, int first, int second, int third, int fourth);
    void FUN_004d7dd0(void *first, void *second, void *third);
    void FUN_004e3100(int action);
    void FUN_004e3260();
    unsigned char FUN_004ded90(void *actor);
    void FUN_004e3d20(int index, int value);
    void FUN_004e3e70();
    bool FUN_004c7eb0(void *first, int second, void **result);
    char FUN_004c7f50(void *actor);
    void FUN_004c7f60(const void *point);
    void FUN_004db7f0(SBGeoPoint2D &point);
    bool FUN_004db7a0();
    int FUN_004db7b0(void *actor);
    void FUN_004db880();
    void FUN_004db8c0(unsigned char value);
    bool FUN_004db8e0(unsigned short index);
    void FUN_004db920(const void *event);
    void FUN_004dba50(const void *event);
    void FUN_004dbb70(const void *event);
    void FUN_004dbc90(const void *event);
    void FUN_004dbdb0(const void *event);
    void FUN_004dbe40(const void *event);
    void FUN_004dbed0(const void *event);
    bool FUN_004dbf20(void *actor, bool additive, bool notify);
    bool FUN_004dc190(void *actor);
    void FUN_004dc260(const void *event);
    void FUN_004de170(bool first, bool second, bool third);
    void FUN_004de1e0();
    void FUN_004de290();
    void FUN_004de5e0();
    bool FUN_004e1a40(const SBGeoPoint2D &point, int mode);
    void FUN_004de840();
    void InitializeActorsFromMissionStream(SBFile &file, std::vector<RHbeamMe> &beamMes);
    void InitializeBuildingTenantsFromMissionStream(SBFile &file);
    void FUN_004c1d20(SBFile &file);
    void FUN_004c1df0(SBFile &file);
    void FUN_004c2150(SBFile &file);
    void FUN_004c2200(SBFile &file, std::vector<RHbeamMe> &beamMes);
    void FUN_004c2720(SBFile &file);
    void FUN_004c28c0(const std::string &name);
    int FUN_004cac00(const void *first, bool second, int third, char fourth);
    unsigned short FUN_004cc100(void *first, void *second);
    unsigned short FUN_004cc970(bool &first, const SBGeoPoint2D &second, RHSectorGateCalls *third);
    void FUN_004ccad0(const SBGeoPoint2D &first, bool second);
    void FUN_004cd400(void *first, void *second);
    void FUN_004e35f0(SBFile &file);
    void FUN_004e2390(void *actor);
    void FUN_004e1fc0();
    bool FUN_004e21e0(void *actor);
    void *FUN_004e2150(RHUnk0051e5e0 *target, const SBGeoPoint2D &point);
    void FUN_004cd600(const SBGeoPoint2D &a, bool b);
    bool FUN_004cdab0(const SBGeoPoint2D &destination);
    void FUN_004cdcc0();
    void FUN_004cde00();
    void FUN_004cdfc0();
    bool FUN_004cec60();
    void FUN_004cede0();
    bool FUN_004cf610();
    bool FUN_004cfce0();
    void FUN_004d0400();
    void FUN_004d0a10(void *a);
    bool SerializeElementPointer(SBFile &file, RHElement *&element);
    bool SerializeNestedB(SBFile &file, void *value);
    bool FUN_004c3af0(SBFile &file, void *&value);
    bool FUN_004c3bd0(SBFile &file, void *&value);
    bool FUN_004c3d90(SBFile &file, void *&value);
    bool FUN_004c3f50(SBFile &file, void *&value);
    bool FUN_004c4030(SBFile &file, void *&value);
    bool FUN_004c41f0(SBFile &file, void *&value);
    bool FUN_004c42d0(SBFile &file, void *&value);
    bool FUN_004c43b0(SBFile &file, void *&value);
    bool FUN_004c4490(SBFile &file, void *&value);
    static void CreateMasters();
    RHElementActorPC *GetPC(RHPCDescription *description) const;
    RHElementActorPC *GetPC(const RHCharacterProfile *profile) const;
    void LoadDynRes(unsigned mission);
    RHDialogueSet *GetDynResources(unsigned long mission);
    unsigned PCCount() const
    {
        RHElementActorPC **first = *(RHElementActorPC **const volatile *)&m_pcs.First();
        if (!first)
            return 0;
        return m_pcs.end() - first;
    }
    void Emit(SBFile &file, void *&value);

    undefined m_0000[0x68];
    RHMessenger *m_0068;
    undefined m_006c[6];
    bool m_0072;
    bool m_0073;
    bool m_0074;
    undefined m_0075[0x13];
    bool m_0088;
    bool m_0089;
    bool m_008a;
    undefined m_008b;
    RHElement *m_008c;
    void *m_0090;
    undefined m_0094[0x40];
    RHElement *m_focusElement;
    undefined m_00d8[4];
    SBDrawManager *m_draw;
    undefined m_00e0[0x3c];
    undefined m_011c[0x3e9c];
    unsigned short m_3fb8;
    undefined m_3fba[0x336];
    RHFrameHolder *m_frameHolder;
    undefined m_42f4[0x104];
    undefined m_43f8[0x1c0];
    RHPathFinder *m_pathFinder;
    SBList<RHpathRequest *> m_failedPathRequests;
    undefined m_45e0[0x17c];
    float m_475c;
    undefined m_4760[0x164];
    void *m_48c4;
    undefined m_48c8[0x10];
    RHEngineElementArray<RHElement> m_elements;
    RHEngineElementArray<RHElement> m_48f8;
    RHEngineElementArray<RHElementActor> m_actors;
    RHEngineElementArray<RHElementActorPC> m_pcs;
    RHEngineElementArray<RHElementActorNPC> m_npcs;
    RHEngineElementArray<RHElementMobile> m_mobiles;
    RHEngineElementArray<RHElementFX> m_fx;
    RHEngineElementArray<RHElementFX> m_groundFX;
    RHEngineElementArray<RHElement> m_activeElements;
    RHSectorActorList m_49f8;
    undefined m_4a1c[0x36];
    char m_4a52;
    char m_4a53;
    char m_4a54;
    char m_4a55;
    undefined m_4a56[0x3e];
    unsigned m_frameCount;
    undefined m_4a98[0xe];
    unsigned short m_shadowColor;
    char m_4aa8;
    undefined m_4aa9[3];
    SBListAutoDelete<RHUnk004e4660Entry *> m_4aac;
    undefined m_4ac4[0xc];
    unsigned m_4ad0;
    undefined m_4ad4[0x58];
    char m_4b2c;
    char m_4b2d;
    char m_4b2e;
    char m_4b2f;
    unsigned short m_4b30;
    char m_4b32;
    char m_4b33;
    char m_4b34;
    char m_4b35;
    char m_4b36;
    char m_4b37;
    char m_4b38;
    char ShowMobileGeometry() const { return m_4b38; }
    char m_4b39;
    char m_4b3a;
    char m_4b3b;
    bool m_showSightRadius;
    char m_4b3d;
    char m_4b3e;
    undefined m_4b3f[0x9d];
    char m_4bdc;
    undefined m_4bdd[7];
    char m_4be4;
    undefined m_4be5[7];
    SBListAutoDelete<RHEngineDrawEntry *> m_4bec;
    undefined m_4c04[0xc];
    SBList<unsigned short> m_noiseRadii;
    undefined m_4c34[0x44];
    SBListAutoDelete<RHUnk004e48b0Entry *> m_4c78;
    undefined m_4c90[0xc];
    SBListAutoDelete<RHUnk004e49f0Entry *> m_4c9c;
    undefined m_4cb4[0xc];
    unsigned short m_discoveryRange;
    undefined m_4cc2[6];
    RHEngineElementArray<RHElementActorHuman> m_teamHumans[2];
    RHEngineElementArray<RHElementActorSoldier> m_teamSoldiers[2];
    RHEngineElementArray<RHElementActorSoldier> m_soldiers;
};

void *FUN_004d1630();

class RHEngineMissionElementCalls
{
public:
    virtual void Unk00(); // vtable+0x00
    virtual void Unk04(); // vtable+0x04
    virtual void Unk08(); // vtable+0x08
    virtual void Unk0c(); // vtable+0x0c
    virtual void Unk10(); // vtable+0x10
    virtual void Unk14(); // vtable+0x14
    virtual void Unk18(); // vtable+0x18
    virtual void Unk1c(); // vtable+0x1c
    virtual void Unk20(); // vtable+0x20
    virtual void Unk24(); // vtable+0x24
    virtual void Unk28(); // vtable+0x28
    virtual void Unk2c(); // vtable+0x2c
    virtual void Unk30(); // vtable+0x30
    virtual void Unk34(); // vtable+0x34
    virtual void Unk38(SBFile &file); // vtable+0x38
    virtual void Unk3c(SBFile &file); // vtable+0x3c
};

// SIZE 0xa9c
class RHUnk0046ffe0 : public RHEngineMissionElementCalls
{
public:
    RHUnk0046ffe0(bool flag);
    undefined m_04[0xa98]; // 0x04
};

// SIZE 0xdd0 (partial layout)
class RHUnk004a1bc0
{
public:
    RHUnk004a1bc0(bool flag);
    undefined m_00[0xdd0]; // 0x00
};

class RHEngineExtendedMissionElementCalls : public RHEngineMissionElementCalls
{
public:
    virtual void Unk40();
    virtual void Unk44();
    virtual void Unk48();
    virtual void Unk4c();
    virtual void Unk50();
    virtual void Unk54();
    virtual void Unk58();
    virtual void Unk5c();
    virtual void Unk60();
    virtual void Unk64();
    virtual void Unk68();
    virtual void Unk6c();
    virtual void Unk70();
    virtual void Unk74();
    virtual void Unk78();
    virtual void Unk7c();
    virtual void Unk80();
    virtual void Unk84();
    virtual void Unk88();
    virtual void Unk8c();
    virtual void Unk90();
    virtual void Unk94();
    virtual void Unk98();
    virtual void Unk9c();
    virtual void Unka0();
    virtual void Unka4();
    virtual void Unka8();
    virtual void Unkac();
    virtual void Unkb0();
    virtual void Unkb4();
    virtual void Unkb8();
    virtual void Unkbc();
    virtual void Unkc0();
    virtual void Unkc4();
    virtual void Unkc8();
    virtual unsigned short Unkcc();
    virtual void Unkd0();
    virtual void Unkd4();
    virtual void Unkd8();
    virtual void Unkdc();
    virtual void Unke0();
    virtual void Unke4();
    virtual void Unke8();
    virtual void Unkec();
    virtual void Unkf0();
    virtual void Unkf4();
    virtual void Unkf8();
    virtual void Unkfc();
    virtual void Unk100();
    virtual void Unk104();
    virtual void Unk108();
    virtual void Unk10c();
    virtual void Unk110();
    virtual void Unk114();
    virtual void Unk118();
    virtual void Unk11c();
    virtual void Unk120();
    virtual void Unk124();
    virtual void Unk128();
    virtual void Unk12c();
    virtual int Unk130();
};

#ifndef RHRECONNAISSANCEENGINE_VIEW
#define RHRECONNAISSANCEENGINE_VIEW
class RHReconnaissanceEngine
{
public:
    bool Unk004c3cb0(SBFile &file, void *&value);
    bool Unk004c4110(SBFile &file, void *&value);
};
#endif

extern RHEngine *g_pEngine;
void *FUN_004622e0(int index, void *container);

class RHUnk00462a90
{
public:
    void FUN_00462a90(const char *value);
    char m_00[0x8e];
    char m_8e;
};

class RHUnk00486170
{
public:
    void FUN_00486170(void *value, unsigned count);
};

class RHUnk004a66d0
{
public:
    bool FUN_004a66d0(bool flag);
};

#include "RHUnk004a6310.h"

class RHUnk004a7d70
{
public:
    bool FUN_004a7d70(bool flag);
};

class RHUnk004a7ed0
{
public:
    bool FUN_004a7ed0(bool flag);
    int FUN_004a7f30();
    void FUN_004a7f40(int first, int second, int third);
    void FUN_004a7f50();
    bool FUN_004a7f80();
};

#include "RHProjectileInitCalls.h"

#include "RHPlayerProfileAccess.h"

class RHUnk00556470
{
public:
    void FUN_00556470();
};

void FUN_005709a0(void *value, unsigned index);
bool FUN_00570850(void *actor);

#include "RHMissionArrayStorage.h"
void FUN_004e70a0(void **position, void *value, bool (*compare)(void *, void *));
void FUN_004e6f70(void **first, void **last, bool (*compare)(void *, void *), void **value);

#include "RHHikingGuideStorage.h"

#include "RHFrameDictionary.h"

// SIZE 0x44
class RHUnk005055b0
{
public:
    void FUN_005052c0();
    void FUN_00505520(int value);
    void FUN_005055b0();
    void FUN_00505640();
    undefined m_00[0x1c]; // 0x00
    char *m_1c; // 0x1c
    char *m_20; // 0x20
    undefined m_24[8]; // 0x24
    char *m_2c; // 0x2c
    char *m_30; // 0x30
    undefined m_34[8]; // 0x34
    char *m_3c; // 0x3c
    char *m_40; // 0x40
};

class RHUnk00523620
{
public:
    bool FUN_00523620();
};

// SIZE 0x160 (partial layout)
class RHUnk004bc5b0
{
public:
    bool FUN_004bc5b0(bool flag);
    undefined m_00[0x50]; // 0x00
    void *m_sprite; // 0x50
    undefined m_54[0x5c]; // 0x54
    unsigned m_b0; // 0xb0
    unsigned m_b4; // 0xb4
    undefined m_b8[0xa4]; // 0xb8
    RHUnk004bc5b0 *m_parent; // 0x15c
};

// SIZE 0x30 (partial layout)
class RHUnk004e51e0
{
public:
    void FUN_00454bb0();
    void *FUN_004e51e0(unsigned flags);
    undefined m_00[0x30]; // 0x00
};

#include "RHMobileUnk00607da0.h"

#endif
