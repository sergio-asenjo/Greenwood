#ifndef RHENGINE_H
#define RHENGINE_H

#include <vector>
#include <string>

class SBFile;
class RHElement;
class RHPCDescription;
class RHCharacterProfile;
class RHElementActorPC;
class RHMission;
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

extern RHUnkSectorGlobal *g_unk0x6c0a9c;
void FUN_005e1d50(SBFile &file, unsigned long tag, int level);
void FUN_005e20c0(SBFile &file);

class RHEngine
{
public:
    bool InitializeFromMission(RHMission *mission);
    bool FUN_004c4570(SBFile &file);
    bool FUN_004c6040(SBFile &file);
    void InitializeActorsFromMissionStream(SBFile &file, std::vector<RHbeamMe> &beamMes);
    void InitializeBuildingTenantsFromMissionStream(SBFile &file);
    void FUN_004c1d20(SBFile &file);
    void FUN_004c1df0(SBFile &file);
    void FUN_004c2150(SBFile &file);
    void FUN_004c2200(SBFile &file, std::vector<RHbeamMe> &beamMes);
    void FUN_004c28c0(const std::string &name);
    void FUN_004e35f0(SBFile &file);
    void FUN_004e2390(void *actor);
    bool SerializeElementPointer(SBFile &file, RHElement *&element);
    bool SerializeNestedA(SBFile &file, void *value);
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
    unsigned PCCount() const
    {
        void **first = *(void **const volatile *)&m_493c;
        if (!first)
            return 0;
        return m_4940 - first;
    }
    void Emit(SBFile &file, void *&value);

    char m_0000[0x48d8];
    char m_48d8[0x64]; // +0x48d8: element lookup container
    void **m_493c; // +0x493c: first actor pointer
    void **m_4940; // +0x4940: one-past-last actor pointer
};

class RHReconnaissanceEngine
{
public:
    bool Unk004c3cb0(SBFile &file, void *&value);
    bool Unk004c4110(SBFile &file, void *&value);
};

extern RHEngine *g_pEngine;
void *FUN_004622e0(int index, void *container);

#endif
