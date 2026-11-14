#ifndef RHPROFILEMANAGER_H
#define RHPROFILEMANAGER_H

#include "RHSaveGameManager.h"
#include <list>
#include <string>
#include "RHBow.h"
#include "RHHtHWeaponProfile.h"
#include "RHCivilianProfile.h"
#include "RHProfileManagerCore.h"

class RHCharacterProfile;
class RHHtHWeaponProfile;
class RHMissionProfile;
class RHSoldierProfile;
class RHProfileManager;

#include "RHCopyPointers.h"

template <class T>
inline T *RHProfileConstructCopy(const T *first, const T *last, T *destination)
{
    for (; first != last; ++destination, ++first)
        std::_Construct(destination, *first);
    return destination;
}

template <class T>
inline void RHProfileConstructFill(T *first, unsigned int count, const T &value)
{
    for (; count > 0; --count, ++first)
        std::_Construct(first, value);
}

template <class T>
inline void RHProfileDestroy(T *first, T *last)
{
    for (; first != last; ++first)
        std::_Destroy(first);
}

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
inline void RHProfileArray<T>::RemoveAll()
{
    T *last = copy(end(), end(), begin());
    ((RHScriptFXArray *)this)->Unk005008e0((void **)last, (void **)m_last);
    m_last = last;
}

template <class T>
inline void RHProfileArray<T>::InsertLast(const T &value)
{
    ((SBArray<RHSaveGame *> *)this)->Insert((RHSaveGame **)m_last, 1, (RHSaveGame *const &)value);
}

#endif
