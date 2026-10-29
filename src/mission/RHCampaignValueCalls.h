#ifndef RHCAMPAIGNVALUECALLS_H
#define RHCAMPAIGNVALUECALLS_H

#include <string>
#include <vector>

class RHUnk00452030
{
public:
    int Get(int index);
    int FUN_00453d60(const void *value);
    bool FUN_004565c0(const std::wstring &name);
    void FUN_00456670(const std::wstring &name);
    char m_pad0[0x108];
    void **m_108;
    void **m_10c;
    char m_110[0x24];
    std::vector<std::wstring> m_134;
};

#endif
