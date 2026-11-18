#ifndef RHLOADINGSCREENCORE_H
#define RHLOADINGSCREENCORE_H

#include <string>
#include "Decomp.h"

class SBFile;
class RHMission;
class SBFontUnk0061e840;
class SBUIUnkSurface;
class SBDrawManager;

// SIZE 0x30
class RHLoadingScreen
{
public:
    unsigned long CreateSurfaceForPicture(SBFile &);
    bool Initialize(const RHMission *, unsigned long, float);
    void GenerateSand(SBFile &);
    void RenderSand(unsigned long);
    bool Refresh();
    static std::string GetDataFile(const RHMission *, unsigned long);
    void Emit(SBFile &, const RHMission *);
    undefined m_00[4]; // 0x00
    float m_duration; // +0x04
    float m_elapsed; // +0x08
    SBFontUnk0061e840 *m_font; // +0x0c
    SBFontUnk0061e840 *m_versionFont; // +0x10
    SBUIUnkSurface *m_context; // +0x14
    SBDrawManager *m_draw; // +0x18
    unsigned long m_width; // +0x1c
    unsigned long m_height; // +0x20
    unsigned long m_picture; // +0x24
    unsigned long m_sandPicture; // +0x28
    unsigned long m_status; // +0x2c
};

extern RHLoadingScreen g_unk0x6c0a50;

#endif
