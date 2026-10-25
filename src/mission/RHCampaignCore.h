#ifndef RHCAMPAIGNCORE_H
#define RHCAMPAIGNCORE_H

#include "Decomp.h"
#include "RHMission.h"
#include <vector>
#include <string>

class SBFile;
class RHPCDescription;
class RHElement;
class RHSectorProduction;
class RHSaveGame;
struct RHbeamMe;
template<class T> class SBArray;

// SIZE 0x1c4
class RHCampaign
{
public:
    undefined m_pad0[0x104]; // 0x00
    std::vector<RHPCDescription *> m_104; // 0x104
    std::vector<RHPCDescription *> m_114; // 0x114
    std::vector<RHPCDescription *> m_124; // 0x124
    std::vector<std::wstring> m_134; // 0x134
    std::vector<RHMission> m_144; // 0x144
    std::vector<RHMission *> m_154; // 0x154
    std::vector<RHMission *> m_164; // 0x164
    RHMission *m_174; // 0x174
    RHMission *m_178; // 0x178
    RHMission *m_17c; // 0x17c
    undefined m_pad180[0x30]; // 0x180
    std::vector<RHPCDescription *> m_1b0; // 0x1b0
    bool m_1c0; // 0x1c0

    void CreateGang();
    void SelectMissions(bool forced);
    void SelectMissionsByLocation(std::vector<RHMission *> &missions);
    void SelectMissionsByObligation(std::vector<RHMission *> &missions);
    bool Serialize(SBFile &file);
    bool SerializeAllCharacters(SBFile &file);
    void CreatePlayableCharacterSet(SBArray<RHElement *> &elements, std::vector<RHbeamMe> &beamMes);
    void FUN_00450c10(SBArray<RHElement *> &elements, std::vector<RHbeamMe> &beamMes);
    void FUN_004526f0(std::vector<RHMission *> &missions);
    void FUN_00452810(std::vector<RHMission *> &missions);
    void FUN_00452a50(std::vector<RHMission *> &missions);
    void FUN_00452c90(std::vector<RHMission *> &missions);
    std::vector<RHPCDescription *> *FUN_004553f0();
    void FUN_00455650();
    RHMission *FUN_004539f0();
    void ForceNextMission(const std::string &first, const std::string &second, bool create);
    bool FUN_00453cd0();
    void FUN_00455f00(std::vector<RHMission *> &missions);
    void FUN_004560d0(RHMission *mission);
    void FUN_004562a0();
    void FUN_004564e0(std::vector<RHMission *> &missions);
    void CreateProductionSectors();
    void FUN_00456e60();
    bool FUN_00454c00(RHbeamMe beamMe, unsigned short character);
    void FUN_004552f0(SBArray<RHElement *> &elements, RHbeamMe beamMe, unsigned short character);
    void FUN_00455810();
    void FUN_004559f0();
    bool FUN_00455a40(RHPCDescription *character);
    unsigned short FUN_00455af0();
    void FUN_00455b20(RHPCDescription *character);
    void FUN_00455b80(RHPCDescription *character);
    void FUN_00455bf0(RHPCDescription *character);
    bool FUN_00455d10(RHPCDescription *character);
    RHSectorProduction *FUN_00456a10(unsigned long index);
    void FUN_00456a40();
    void FUN_00456a70();
    void FUN_00456af0(const void *object);
    unsigned FUN_00456db0() const;
    unsigned short GetNumberOfPeasantsToConvertToBlazons() const;
    bool LoadFromSaveGame(const RHSaveGame *saveGame);
    bool CreateBackup();
    bool CopyBackupTo(SBFile &file) const;
    void Emit(std::vector<RHMission *> &missions);
};

#endif
