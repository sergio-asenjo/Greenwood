#ifndef RHPROFILEMANAGER_H
#define RHPROFILEMANAGER_H

#include "RHSaveGameManager.h"
#include "RHBow.h"
#include "RHHtHWeaponProfile.h"
#include "RHCivilianProfile.h"

class RHCharacterProfile;
class RHHtHWeaponProfile;
class RHMissionProfile;
class RHSoldierProfile;

void **FUN_004598e0(void **first, void **last, void **destination);

class RHScriptFXArray
{
public:
    int grow;
    void **first;
    void **last;
    void **end;
    void **cursor;
    bool dirty;
    void **Unk004fe420(void **first, void **last, void **destination);
    void Unk004fe450(void **destination, unsigned int count, void *const &value);
    void Unk005008e0(void **first, void **last);
    unsigned int Size() { return first == 0 ? 0 : last - first; }
};

template <class T>
struct RHProfileArray
{
    int m_grow;
    T *m_first;
    T *m_last;
    T *m_end;

    unsigned int GetSize() const { return m_first == 0 ? 0 : m_last - m_first; }
    T *begin() { return m_first; }
    T *end() { return m_last; }
    void RemoveAll()
    {
        T *last = copy(end(), end(), begin());
        ((RHScriptFXArray *)this)->Unk005008e0((void **)last, (void **)m_last);
        m_last = last;
    }
    void InsertLast(const T &value)
    {
        ((SBArray<RHSaveGame *> *)this)->Insert((RHSaveGame **)m_last, 1, (RHSaveGame *const &)value);
    }
};

class RHProfileManager
{
public:
    bool SerializeShootWeapon(SBFile &file);
    bool SerializeHandToHandWeapon(SBFile &file);
    bool SerializeCivilians(SBFile &file);
    bool SerializeCharacters(SBFile &file);
    bool SerializeSoldiers(SBFile &file);
    bool SerializeMissions(SBFile &file);
    void ImportBeamMes(RHMissionProfile *profile);
    RHMissionProfile *AddForcedMission(const std::string &first, const std::string &second, const std::string &third);
    bool SerializeProfilePointer(SBFile &file, const RHHtHWeaponProfile *&profile) const;
    bool SerializeProfilePointer(SBFile &file, RHMissionProfile *&profile) const;
    bool SerializeProfilePointer(SBFile &file, const RHBow::Profile *&profile) const;
    bool SerializeProfilePointer(SBFile &file, const RHCharacterProfile *&profile) const;

    int GetProfileIndex(const RHHtHWeaponProfile *profile) const;
    int GetProfileIndex(const RHMissionProfile *profile) const;
    int GetProfileIndex(const RHBow::Profile *profile) const;
    int GetProfileIndex(const RHCharacterProfile *profile) const;
    int FUN_0056cef0(const RHCharacterProfile *profile) const;

    void Emit(SBFile &file);

    char m_00[0x10];
    RHProfileArray<RHCharacterProfile *> m_characters; // [0x10]: first +0x14, last +0x18
    RHProfileArray<RHSoldierProfile *> m_soldiers; // [0x20]: first +0x24, last +0x28
    RHProfileArray<RHHtHWeaponProfile *> m_handToHand; // [0x30]: first +0x34, last +0x38
    RHProfileArray<RHBow::Profile *> m_shoot; // [0x40]: first +0x44, last +0x48
    RHProfileArray<RHMissionProfile *> m_missions; // [0x50]: first +0x54, last +0x58
    RHProfileArray<RHCivilianProfile *> m_civilians; // [0x60]: first +0x64, last +0x68
};

#endif
