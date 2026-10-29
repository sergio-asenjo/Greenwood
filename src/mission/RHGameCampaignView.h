#ifndef RHGAMECAMPAIGNVIEW_H
#define RHGAMECAMPAIGNVIEW_H

#include "Decomp.h"

struct RHGameMission;

class RHGameCampaignView
{
public:
    undefined m_00[0x178];
    RHGameMission *m_178;
    RHGameMission *m_17c;
    RHGameMission *m_180;
    void FUN_00453b70(RHGameMission *mission);
    int FUN_00456190(RHGameMission *mission);
    int FUN_004561d0(RHGameMission *mission);
    int FUN_00456230(RHGameMission *mission);
    void FUN_00456540(bool flag, RHGameMission *mission);
    unsigned short FUN_00456270();
    void FUN_00456e40(char value);
};

#endif
