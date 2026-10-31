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

    RHSaveGameManager *m_manager;
    unsigned long m_04;
    std::string m_08;
    std::string m_18;
    std::wstring m_28;
    unsigned long m_38[4];
};

bool FUN_005f6400(const std::string &name);

#endif
