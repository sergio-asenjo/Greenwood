#ifndef RHMENUMISSIONDESCRIPTION_H
#define RHMENUMISSIONDESCRIPTION_H

#include "rhmenuwindowfocus_00544c50.h"

class RHMission;

class RHMenuMissionDescription : public RHMenuWindowFocus
{
public:
    static unsigned long FUN_00535620(const RHMission *mission);
    int GetUserChoice() const;
    bool FUN_005357e0(int message, void *widget, void *data);
    bool FUN_005358d0(int message, void *widget, void *data);
    bool FUN_00535910(int message, void *widget, void *data);

    undefined m_140[0x7ec];
    RHMission *m_mission;
    void *m_930;
    int m_choice;
};

#endif
