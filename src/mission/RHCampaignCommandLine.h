#ifndef RH_CAMPAIGN_COMMAND_LINE_H
#define RH_CAMPAIGN_COMMAND_LINE_H

#include <string>

class RHProfileText;

class RHCampaignCommandLine
{
public:
    char m_allocator[4];
    char *m_chars;
    unsigned m_length;
    unsigned m_capacity;
    int FUN_0045a010(const RHProfileText &value);
    void FUN_00457be0() { ((std::string *)this)->begin(); }
    char operator[](unsigned index)
    {
        if (m_length >= index && m_chars != 0)
        {
            FUN_00457be0();
            return m_chars[index];
        }
        return *"";
    }
};

#endif
