#include "RHGame_calls.h"

class RHUnk0054cda0Data
{
public:
    char m_0[0x34];
    int m_34;
    char m_38[0x30];
    short m_68;
};

class RHUnk0054cda0
{
public:
    RHUnk0054cda0Data *m_0;
};

// FUNCTION: GAME 0x0054cda0
void FUN_0054cda0(RHUnk0054cda0 *value)
{
    if (value->m_0->m_34 == 5 && value->m_0->m_68 == 0)
        ((RHGameCampaignView *)g_unk0x6c07fc)->FUN_00456540(true, (RHGameMission *)value);
}
