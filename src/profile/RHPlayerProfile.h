#ifndef RHPLAYERPROFILE_H
#define RHPLAYERPROFILE_H

#include "RHSaveGame.h"
#include "RHSaveGameManager.h"
#include "RHKeyConfig.h"
#include "RHGraphicConfig.h"
#include "RHSoundConfig.h"

// VTABLE: GAME 0x00679bd8
// SIZE 0x74
class RHPlayerProfile : public RHSaveGameManager
{
public:
    RHPlayerProfile();
    RHPlayerProfile(unsigned long id, const std::wstring &name, unsigned long difficulty);
    bool Serialize(SBFile &file);
    static std::wstring ConvertDifficultyLevelToWideString(unsigned long difficulty);
    void CreateSaveGameDirectory() const;
    void DeleteSaveGameDirectory() const;
    const std::wstring &GetName() const;
    void SetName(const std::wstring &name);
    virtual std::string GetSaveGameDirectory() const;
    void FUN_0055cc80();
    RHGraphicConfig &FUN_0052ef80();
    void Emit(SBFile &file);
    undefined4 m_18;
    undefined4 m_1c;
    undefined4 m_20;
    undefined4 m_24;
    undefined4 m_28;
    undefined4 m_2c;
    undefined4 m_30;
    RHKeyConfig m_keys1;
    RHKeyConfig m_keys2;
    RHSoundConfig m_sound;
    RHGraphicConfig m_graphics;
    std::wstring m_name;
    SBGeoPoint2D m_point;
};

#endif
