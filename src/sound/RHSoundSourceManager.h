#ifndef RHSOUNDSOURCEMANAGER_H
#define RHSOUNDSOURCEMANAGER_H

#include "RHSoundSourceManagerCore.h"
#include "RHSaveGameManager.h"
#include "RHSoundSourceCore.h"
#include <vector>

inline RHSoundSourceArray::~RHSoundSourceArray()
{
    ((std::vector<RHSoundSource *> *)this)->erase(begin(), end());
    ((std::vector<RHSoundSource *> *)this)->~vector();
}

inline void RHSoundSourceArray::RemoveAll()
{
    ((std::vector<RHSoundSource *> *)this)->erase(begin(), end());
    m_changed = true;
}

inline void RHSoundSourceArray::InsertLast(RHSoundSource *const &value)
{
    ((SBArray<RHSaveGame *> *)this)->Insert(
        (RHSaveGame **)m_last, 1, (RHSaveGame *const &)value);
    m_changed = true;
}

#endif
