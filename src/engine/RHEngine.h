#ifndef RHENGINE_H
#define RHENGINE_H

#include <vector>
#include <string>
#include "Decomp.h"

class SBFile;
class RHElement;
class RHPCDescription;
class RHCharacterProfile;
class RHElementActorPC;
class RHMission;
class SBGeoPoint2D;
class RHDialogueSet;
struct RHUnkSectorGlobal;
struct RHbeamMe;

class RHCampaignLoadingProgress
{
public:
    char m_0[8];
    float m_progress;
    void FUN_00523300();
};

extern RHCampaignLoadingProgress g_unk0x6c0a50;
extern int g_unk0x006c0a7c;
extern float g_unk0x006774a0;
unsigned long FUN_005e1d00(SBFile &file);
void FUN_005e2300(SBFile &file);

class RHEngineBuildingCalls
{
public:
    void FUN_0057e680(void *actor);
};

class RHPortraitBar;
typedef RHPortraitBar RHEngineRosterCalls;

class RHEngineMenuStateCalls
{
public:
    bool FUN_00514970();
};

class RHEngineSequenceStateCalls
{
public:
    bool FUN_005823f0();
    bool FUN_0058a670(void *sequence);
    bool FUN_0058a7d0(void *element);
};

// SIZE 0x1a0
class RHUnk0054eab0
{
public:
    RHUnk0054eab0();
    void FUN_0054eea0(SBFile &file, void *grid);
    undefined m_00[0x1a0]; // 0x00
};

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

class RHUnk0057ee90
{
public:
    RHUnk0057ee90();
    undefined m_00[0x70];
};

class RHUnk0057ee40
{
public:
    RHUnk0057ee40();
    undefined m_00[0x68];
};

extern RHUnkSectorGlobal *g_unk0x6c0a9c;
void FUN_005e1d50(SBFile &file, unsigned long tag, int level);
void FUN_005e20c0(SBFile &file);
void FUN_004be5c0(SBFile &file, void *&value);

// SIZE 0x4944 (partial layout)
class RHEngine
{
public:
    bool TurnPathFinderOn();
    int FUN_0049b590(void *actor);
    void TurnPathFinderOff();
    bool FUN_004c0340(SBGeoPoint2D &point);
    void FUN_004d1640(unsigned first, unsigned second, unsigned third, unsigned fourth, unsigned fifth, unsigned sixth, unsigned seventh);
    unsigned short FUN_004d16b0(void *first, void *second, unsigned third);
    bool FUN_004d1840();
    bool FUN_004d1aa0();
    void FUN_004d1d00();
    void FUN_004d1f50();
    void FUN_004d21b0();
    void FUN_004c8120(void *actor);
    unsigned int FUN_004d2340(int type);
    void FUN_004c38d0(SBFile &file, unsigned *value);
    void FUN_004dee70(float *point);
    void FUN_004dce20(void *actor);
    void FUN_004ddfb0();
    int FUN_004deeb0(const SBGeoPoint2D &point, SBGeoPoint2D &result);
    void FUN_004defa0(char flag);
    void FUN_004df070(void *value, char flag);
    void FUN_004df330(const SBGeoPoint2D &point, void *actor, int index);
    void FUN_004df550(const SBGeoPoint2D &point, void *actor, int flag, void *provided);
    void FUN_004df7b0(const SBGeoPoint2D &point, char flag);
    void FUN_004dfb50(const SBGeoPoint2D &point, char flag);
    void FUN_004dfcf0(char flag);
    void FUN_004df950(const SBGeoPoint2D &point, char flag);
    void FUN_004dfe70(const SBGeoPoint2D &point, char flag);
    void *FUN_004e04c0(int type, const SBGeoPoint2D &point, int index, void *actor);
    void FUN_004e0550(const SBGeoPoint2D &point, void *actor, int index);
    void FUN_004e0770(const SBGeoPoint2D &point, void *actor, int index);
    void FUN_004e0bf0(const SBGeoPoint2D &point, void *actor, char flag);
    void FUN_004e14a0(const SBGeoPoint2D &point, int value, char flag);
    void FUN_004e1630(const SBGeoPoint2D &point, char flag);
    void FUN_004e09d0(const SBGeoPoint2D &point, void *actor, char flag);
    void FUN_004e0d80(const SBGeoPoint2D &point, void *actor, char flag);
    void FUN_004e17c0(unsigned value, void *actor);
    void FUN_004e0030(const SBGeoPoint2D &point, void *actor, char flag);
    void FUN_004e0fb0(const SBGeoPoint2D &point, void *actor, char flag, int value);
    void FUN_004debe0();
    void FUN_004debf0(const SBGeoPoint2D &point);
    unsigned FUN_004e19c0(unsigned value);
    unsigned FUN_004e1f30(unsigned value);
    bool FUN_004e3cd0();
    bool FUN_004e1890();
    int FUN_004e34f0();
    int FUN_004e3720(void *, int, unsigned short, void *, void *);
    unsigned FUN_004e4110(unsigned value);
    bool InitializeFromMission(RHMission *mission);
    bool FUN_004c4570(SBFile &file);
    bool FUN_004c6040(SBFile &file);
    int FUN_004c6ef0();
    bool FUN_004c7c90();
    int FUN_004c7cc0();
    bool FUN_004c7cd0();
    bool FUN_004c7cf0();
    unsigned FUN_004c7d50();
    bool FUN_004c7d80(void *first, int second, void **result);
    bool FUN_004c7e10(void *first, int second, void **result);
    void FUN_004e3c20(void *point);
    void FUN_004d8fd0(RHPCDescription *description);
    void FUN_004d5320(const void *value);
    void FUN_004e3100(int action);
    unsigned char FUN_004ded90(void *actor);
    void FUN_004e3d20(int index, int value);
    bool FUN_004c7eb0(void *first, int second, void **result);
    void FUN_004c7f60(const void *point);
    void FUN_004db7f0(SBGeoPoint2D &point);
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
    bool FUN_004dc190(void *actor);
    void FUN_004dc260(const void *event);
    void FUN_004de170(bool first, bool second, bool third);
    void FUN_004de1e0();
    void InitializeActorsFromMissionStream(SBFile &file, std::vector<RHbeamMe> &beamMes);
    void InitializeBuildingTenantsFromMissionStream(SBFile &file);
    void FUN_004c1d20(SBFile &file);
    void FUN_004c1df0(SBFile &file);
    void FUN_004c2150(SBFile &file);
    void FUN_004c2200(SBFile &file, std::vector<RHbeamMe> &beamMes);
    void FUN_004c2720(SBFile &file);
    void FUN_004c28c0(const std::string &name);
    int FUN_004cac00(void *first, void *second, int third, char fourth);
    unsigned short FUN_004cc100(void *first, void *second);
    int FUN_004cc970(void *first, void *second, void *third);
    void FUN_004ccad0(void *first, void *second);
    void FUN_004cd400();
    void FUN_004e35f0(SBFile &file);
    void FUN_004e2390(void *actor);
    void FUN_004cd600(void *a, void *b);
    void FUN_004cdab0(void *a);
    void FUN_004cdcc0();
    void FUN_004cde00();
    void FUN_004cdfc0();
    bool FUN_004cec60();
    void FUN_004cede0();
    void FUN_004cf610();
    void FUN_004cfce0();
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
    RHElementActorPC *GetPC(RHPCDescription *description) const;
    RHElementActorPC *GetPC(const RHCharacterProfile *profile) const;
    void LoadDynRes(unsigned mission);
    RHDialogueSet *GetDynResources(unsigned long mission);
    unsigned PCCount() const
    {
        void **first = *(void **const volatile *)&m_493c;
        if (!first)
            return 0;
        return m_4940 - first;
    }
    void Emit(SBFile &file, void *&value);

    undefined m_0000[0x48d8]; // 0x0000
    undefined m_48d8[0x64]; // 0x48d8
    void **m_493c; // 0x493c
    void **m_4940; // 0x4940
};

void *FUN_004d1630();
bool __stdcall FUN_004d2330(int type);

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
    virtual void Unkcc();
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

// SIZE 0x270
class RHUnk004ab090 : public RHEngineMissionElementCalls
{
public:
    RHUnk004ab090();
    undefined m_04[0x26c]; // 0x04
};

// SIZE 0x170
class RHUnk004b9b70 : public RHEngineMissionElementCalls
{
public:
    RHUnk004b9b70();
    undefined m_04[0x16c]; // 0x04
};

// SIZE 0x18c
class RHUnk004bac30 : public RHEngineMissionElementCalls
{
public:
    RHUnk004bac30();
    undefined m_04[0x188]; // 0x04
};

// SIZE 0xfc
class RHUnk004a8130 : public RHEngineMissionElementCalls
{
public:
    RHUnk004a8130(bool flag);
    undefined m_04[0xf8]; // 0x04
};

class RHReconnaissanceEngine
{
public:
    bool Unk004c3cb0(SBFile &file, void *&value);
    bool Unk004c4110(SBFile &file, void *&value);
};

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
    bool FUN_004a66d0(char flag);
};

class RHUnk004a6000
{
public:
    bool FUN_004a6000();
    char FUN_004a6060() const;
};

class RHUnk004a6310
{
public:
    bool FUN_004a6310(char flag);
    int FUN_004a6370() const;
};

class RHUnk004a7d70
{
public:
    bool FUN_004a7d70(char flag);
};

class RHUnk004a7ed0
{
public:
    bool FUN_004a7ed0(char flag);
    int FUN_004a7f30();
    void FUN_004a7f40(int first, int second, int third);
    void FUN_004a7f50();
    bool FUN_004a7f80();
};

class RHUnk004b0980
{
public:
    bool FUN_004b0980(char flag);
};

class RHUnk004b91a0
{
public:
    bool FUN_004b91a0(char flag);
};

class RHUnk004be080
{
public:
    bool FUN_004be080(char flag);
};

class RHUnk004ba900
{
public:
    bool FUN_004ba900(char flag);
    int FUN_004ba970();
};

#include "RHPlayerProfileAccess.h"

class RHUnk00556470
{
public:
    void FUN_00556470();
};

void FUN_005709a0(void *value, unsigned index);
class RHEngineContinuationCampaignCalls
{
public:
    void FUN_00450c10(void *actors, SBFile &file);
};

void FUN_00570850(void *actor);

class RHMissionArrayStorage
{
public:
    void *FUN_004609a0(void *first, void *last)
    {
        typedef std::vector<int> Values;
        int *(Values::*erase)(int *, int *) = &Values::erase;
        return (((Values *)this)->*erase)((int *)first, (int *)last);
    }
    void FUN_004e5820(void *position, const unsigned long &value)
    {
        typedef std::vector<unsigned long> Values;
        unsigned long *(Values::*insert)(unsigned long *, const unsigned long &) = &Values::insert;
        (((Values *)this)->*insert)((unsigned long *)position, value);
    }
};
void FUN_004e70a0(void **position, void *value, bool (*compare)(void *, void *));
void FUN_004e6f70(void **first, void **last, bool (*compare)(void *, void *), void **value);

// SIZE 0x04 (call view)
class RHUnk00551da0
{
public:
    bool FUN_00551da0(SBFile &file);
    undefined4 m_00; // 0x00
};

// SIZE 0x20
class RHUnk0051d2c0
{
public:
    ~RHUnk0051d2c0();
    std::vector<RHUnk00551da0 *> m_00; // 0x00
    undefined m_10[0x10]; // 0x10
};

// SIZE 0x1c (partial layout)
class RHHikingGuide
{
public:
    int FUN_0051cac0(SBFile &file);
    void FUN_0051cd10(SBFile &file);
    bool FUN_0051d020(SBFile &file);
    undefined4 m_00; // 0x00
    std::vector<RHUnk0051d2c0 *> m_04; // 0x04
    undefined4 m_14; // 0x14
    char m_18; // 0x18
    undefined m_19[3]; // 0x19
};

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
    bool FUN_004bc5b0(char flag);
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

// SIZE 0x14
class RHMobileUnk00607da0
{
public:
    RHMobileUnk00607da0 &FUN_00607da0(const RHMobileUnk00607da0 &other);
    undefined m_00[0x14]; // 0x00
};

#endif
