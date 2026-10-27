#ifndef RHMISSIONSTATCORE_H
#define RHMISSIONSTATCORE_H

#include <string>

class SBFile;
class RHPCDescription;

class RHUnk0054e250List
{
public:
    char m_pad0[4];
    std::wstring *m_first;
    std::wstring *m_last;
    std::wstring *m_end;

    unsigned size() const { return m_first == 0 ? 0 : (unsigned)(m_last - m_first); }
};

class RHMissionStat
{
public:
    virtual bool Serialize(SBFile &file);
    void Emit(SBFile &file);
    void AddNewPC(const RHPCDescription *source);
    void FUN_0054d150(const void *value);
    void FUN_0054d310(std::wstring &text) const;
    void FUN_0054d550(std::wstring &text) const;
    void FUN_0054d760(std::wstring &text) const;
    void FUN_0054d9c0(std::wstring &text) const;
    void FUN_0054db50(std::wstring &text) const;
    void FUN_0054dd10(std::wstring &text) const;
    void FUN_0054dee0(std::wstring &text) const;
    std::wstring FUN_0054e090() const;

    int m_f04;
    int m_f08;
    int m_f0c;
    int m_f10;
    int m_f14;
    int m_f18;
    int m_f1c;
    int m_f20;
    int m_f24;
    RHUnk0054e250List m_list;
};

#endif
