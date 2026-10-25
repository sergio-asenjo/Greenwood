#ifndef RHSAVEGAME_H
#define RHSAVEGAME_H

#include "SB.h"
#include <string>

class RHSaveGameManager;
struct _SYSTEMTIME;

#include "RHUnk005f4fc0.h"

class RHSaveGame
{
public:
    struct Header
    {
        Header();
        unsigned long m_00; // [0x00]: magic 0x52485347
        unsigned long m_04; // [0x04]: version
        unsigned long m_08; // [0x08]
    };

    RHSaveGame(RHSaveGameManager *mgr);
    RHSaveGame(RHSaveGameManager *mgr, const std::string &fileName, const std::wstring &name);
    ~RHSaveGame();
    bool Serialize(SBFile &file);
    std::string FUN_0056e5d0() const;
    static bool SerializeHeader(SBFile &file, Header &header);
    void SynchronizeWithFile();
    const _SYSTEMTIME &GetTime() const;
    const std::wstring &FUN_0056e780() const;
    int FUN_0056e8b0() const;
    bool operator<(const RHSaveGame &other) const;
    void CopyFiles(const RHSaveGame *source);
    void SetText(const std::wstring &text);
    void Emit(SBFile &file, Header &header);

    char m_data[0x48]; // [0x00, 0x48): compatible with RHSaveGameManager.h
};

#define RHSaveGame_m_04 (*(unsigned long *)(m_data + 0x04)) // [0x04]: header.m_08
#define RHSaveGame_m_38 ((void *)(m_data + 0x38)) // [0x38, 0x40): file-time output

bool FUN_005f6400(const std::string &name);

#endif
