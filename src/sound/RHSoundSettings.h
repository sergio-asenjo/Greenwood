#ifndef RHSOUNDSETTINGS_H
#define RHSOUNDSETTINGS_H

#include "Decomp.h"

// SIZE 0x18
struct RHSoundSettings
{
    RHSoundSettings();
    RHSoundSettings(const RHSoundSettings &other);
    ~RHSoundSettings();
    int m_00; // 0x00
    undefined m_04[8]; // 0x04
    void *m_0c; // 0x0c
    undefined m_10[4]; // 0x10
    void *m_14; // 0x14
};

#endif
