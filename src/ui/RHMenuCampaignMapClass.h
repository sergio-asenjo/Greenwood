#ifndef RHMENUCAMPAIGNMAPCLASS_H
#define RHMENUCAMPAIGNMAPCLASS_H

#include <vector>
#include "RHMenuWindowClass.h"
#include "RHUnk00527870.h"
#include "RHMenuShortMissionDescriptionCore.h"

class RHMapTitleText;
#include "RHMapBox.h"

struct RHMapByte
{
    signed char value;
};

// VTABLE: GAME 0x00679218
class RHMenuCampaignMap : public RHMenuWindow
{
public:
    virtual ~RHMenuCampaignMap();
    virtual void RouteEvent(struct RHMenuEvent *event);
    virtual void FUN_00528a60();
    bool HandleEvent(struct RHMenuEvent *event);
    bool Create();
    void DisplayPseudoMissionDebriefing();
    void FUN_00527a70(RHMapByte);
    void FUN_00527ae0(RHMapByte);
    void FUN_00527c00(const std::vector<void *> &);
    void FUN_005284b0();
    bool FUN_00528520(unsigned, unsigned, unsigned);
    bool FUN_00528550(unsigned, unsigned, unsigned);
    bool FUN_00528560(int, void *, void *);
    bool FUN_00528730(int, void *, void *);
    bool FUN_005287d0(int, void *, void *);
    void FUN_00528810();
    void Emit();
    SBFontUnk0061e840 *m_font;
    RHGameLifetime00515d30 m_close;
    RHUnk005276d0 m_locations[10];
    RHGameLifetime00515f00 m_arrows[10];
    RHMenuShortMissionDescription m_description;
    RHGameLifetime00525560 m_label;
    std::wstring m_message;
    unsigned m_26fc;
    unsigned m_2700;
};

#endif
