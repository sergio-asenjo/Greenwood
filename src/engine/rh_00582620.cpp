// Anonymous cluster at 0x0058253x / 0x0058262x.
// No __FILE__ or oracle evidence: class and method identity are unproven.

#include "RHSequenceManager.h"
#include "RHSequenceElementCalls.h"

inline unsigned RHSequenceDispatchCount(unsigned short first, unsigned short last, unsigned &index)
{
    index = first;
    return last - (unsigned)first;
}

class RHUnk00582620
{
public:
    bool FUN_00582530();
    void FUN_00582560();
    void FUN_00582620(int arg);
    char m_00[8];
    RHManagerList<RHSequenceElement *> m_list;
    unsigned short m_2c;
    unsigned short m_2e;
    short m_30;
    char m_32[2];
    char m_34;
};

// FUNCTION: GAME 0x00582530
bool RHUnk00582620::FUN_00582530()
{
    if (!m_34)
        m_34 = 1;
    if ((unsigned short)m_2c == m_list.Count())
        return false;
    FUN_00582560();
    return true;
}

// FUNCTION: GAME 0x00582560
void RHUnk00582620::FUN_00582560()
{
    unsigned short count = (unsigned short)m_list.Count();
    if (m_2c < count)
    {
        m_2e = *(unsigned short *)((char *)m_list[m_2c] + 0x14);
        unsigned short first = m_2c;
        while (m_2c < count)
        {
            if (*(unsigned short *)((char *)m_list[m_2c] + 0x14) != m_2e)
                break;
            ++m_2c;
            ++m_30;
        }
        unsigned short last = m_2c;
        if (first < last)
        {
            unsigned index;
            unsigned remaining = RHSequenceDispatchCount(first, last, index);
            do
            {
                RHSequenceElementCalls *element = (RHSequenceElementCalls *)m_list[index];
                if (element->m_58 != 6)
                {
                    if (element->m_5c == 9)
                        element->FUN_00585570();
                    else
                        ((RHSequenceManager *)g_unk0x6c1040)->FUN_0058bb80((RHSequenceElement *)element);
                }
                ++index;
            }
            while (--remaining);
        }
    }
}

// FUNCTION: GAME 0x00582620
void RHUnk00582620::FUN_00582620(int arg)
{
    m_30--;
    if (m_30 == 0)
        FUN_00582560();
}
