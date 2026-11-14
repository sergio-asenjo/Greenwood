#ifndef RHPROFILEMANAGERCORE_H
#define RHPROFILEMANAGERCORE_H

#include <list>
#include <string>
#include "RHBow.h"

class SBFile;
class RHCharacterProfile;
class RHHtHWeaponProfile;
class RHMissionProfile;
class RHSoldierProfile;
struct RHCivilianProfile;

template <class T>
struct RHProfileArray
{
    explicit RHProfileArray(const std::allocator<T> &allocator = std::allocator<T>())
        : m_allocator(allocator), m_first(0), m_last(0), m_end(0) {}
    ~RHProfileArray()
    {
        Destroy(m_first, m_last);
        m_allocator.deallocate(m_first, m_first == 0 ? 0 : m_end - m_first);
        m_first = 0;
        m_last = 0;
        m_end = 0;
    }
    void Destroy(T *first, T *last)
    {
        for (; first != last; ++first)
            m_allocator.destroy(first);
    }
    std::allocator<T> m_allocator;
    T *m_first;
    T *m_last;
    T *m_end;

    unsigned int GetSize() const { return m_first == 0 ? 0 : m_last - m_first; }
    T *begin() { return m_first; }
    T *end() { return m_last; }
    void RemoveAll();
    void InsertLast(const T &value);
};

class RHProfileManager
{
public:
    explicit RHProfileManager(const char *directory);
    ~RHProfileManager();
    void *FUN_00564560(unsigned flags);
    bool SerializeShootWeapon(SBFile &file);
    void AddWarning(char *format, ...);
    void FUN_00564bf0(const char *name);
    void FUN_00565100(const char *name);
    void FUN_0056a310(const char *name);
    void FUN_00565c10(const char *name);
    void FUN_005672d0(const char *name);
    void FUN_00569570(const char *name);
    void FUN_0056aee0(const char *name);
    bool SerializeHandToHandWeapon(SBFile &file);
    bool SerializeCivilians(SBFile &file);
    bool SerializeCharacters(SBFile &file);
    bool SerializeSoldiers(SBFile &file);
    bool SerializeMissions(SBFile &file);
    void FUN_00564e60(SBFile &file);
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

    unsigned m_vptr;
    std::list<std::string> m_warnings;
    RHProfileArray<RHCharacterProfile *> m_characters;
    RHProfileArray<RHSoldierProfile *> m_soldiers;
    RHProfileArray<RHHtHWeaponProfile *> m_handToHand;
    RHProfileArray<RHBow::Profile *> m_shoot;
    RHProfileArray<RHMissionProfile *> m_missions;
    RHProfileArray<RHCivilianProfile *> m_civilians;
};

#endif
