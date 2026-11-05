// RHMenuShortMissionDescription.cpp — the short mission description menu TU
// (code 0x00540730..0x005412cb). See RHMenuShortMissionDescription.h for the
// binding evidence.

#include "SBNullstr.h"
#include "SBGeoBoundingBox2DCore.h"
#include "SBGeoVector2D.h"
#include "RHMenuShortMissionDescription.h"
#include "RHMapBox.h"
#include "RHMapResources.h"
#include "RHShortMissionUpdateCalls.h"
#include "RHMission.h"
#include "RHGameBlazonWidget.h"
#include "RHMapWidget.h"
#include "RHMenuCampaignMapClass.h"
#include "SBUIRenderer.h"
#include "SBThreadedInput.h"
#include "SBFrameWnd.h"
#include <stddef.h>

extern RHEngine *g_pEngine;
extern RHMapResources *g_unk0x006c1840;

DECOMP_SIZE_ASSERT(RHMenuShortMissionDescription, 0x380)
DECOMP_STATIC_ASSERT(offsetof(RHMenuShortMissionDescription, m_box) == 0x364)
DECOMP_STATIC_ASSERT(offsetof(RHMenuShortMissionDescription, m_blazons) == 0x378)
DECOMP_STATIC_ASSERT(offsetof(RHMenuShortMissionDescription, m_mission) == 0x37c)

class RHShortMissionWidgetCalls
{
public:
    virtual void V00();
    virtual void V04();
    virtual void V08();
    virtual void V0c();
    virtual void V10();
    virtual void V14();
    virtual void V18();
    virtual void V1c();
    virtual void V20();
    virtual void V24();
    virtual void V28();
    virtual void V2c(const std::wstring &);
    virtual void V30();
    virtual void V34();
    virtual void V38(unsigned);
};

// FUNCTION: GAME 0x00540730
RHMenuShortMissionDescription::RHMenuShortMissionDescription(RHMenuWindowScreen *screen)
    : RHMenuWindow(0, screen, false), m_blazons(0), m_mission(0)
{
}

// FUNCTION: GAME 0x00540830
void *RHMenuShortMissionDescription::FUN_00540830(unsigned flags)
{
    this->~RHMenuShortMissionDescription();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x00540850
RHMenuShortMissionDescription::~RHMenuShortMissionDescription()
{
    FUN_00540d20();
    ((RHPortraitRootList *)this)->FUN_005df300((RHUnk005d92c0Sub *)&m_title);
    ((RHPortraitRootList *)this)->FUN_005df300((RHUnk005d92c0Sub *)&m_text);
    ((RHPortraitRootList *)this)->FUN_005df300((RHUnk005d92c0Sub *)&m_picture);
}

extern wchar_t g_unk0x006c0b50[1];

// FUNCTION: GAME 0x00540970
bool RHMenuShortMissionDescription::Create()
{
    if (FUN_00544b40(
            // STRING: GAME 0x006b1070
            L"Short mission description",
            RHMapBox(0.0f, 0.0f, 220.0f, 100.0f), 0))
    {
        void *font = m_screen->FUN_0053be80(std::string("PopupScroll"));
        ((RHMapWidget *)&m_text)->V30(g_unk0x006c0b50, RHMapBox(0.0f, 0.0f, 0.0f, 0.0f), 0, 0x85);
        ((RHMenuCampaignMap *)this)->V30(&m_text);
        ((RHMapWidget *)&m_picture)->V30(g_unk0x006c0b50, RHMapBox(9.0f, 8.0f, 9.0f, 8.0f), 0, 0x117);
        ((RHMenuCampaignMap *)this)->V30(&m_picture);
        ((RHMapWidget *)&m_title)->V30(g_unk0x006c0b50, RHMapBox(48.0f, 5.0f, 215.0f, 80.0f), 0, unsigned(-1));
        ((SBUIUnk0060dd00 *)&m_title.m_renderer)->FUN_0060e0d0(font, font, font, font);
        m_title.m_renderer.SetM64(2);
        ((RHMenuCampaignMap *)this)->V30(&m_title);
        return true;
    }
    return false;
}

// FUNCTION: GAME 0x00540d20
void RHMenuShortMissionDescription::FUN_00540d20()
{
    if (m_blazons)
    {
        delete m_blazons;
        m_blazons = 0;
    }
}

// FUNCTION: GAME 0x00540d50
std::wstring RHMenuShortMissionDescription::FUN_00540d50()
{
    RHDialogueSet *resources = g_pEngine->GetDynResources(**(unsigned long **)m_mission);
    RHMapResources *manager = g_unk0x006c1840;
    std::wstring text;
    if (!resources)
        text =
            // STRING: GAME 0x006b10a4
            L"Unable to get the dynamic resouces...";
    else if (!manager->FUN_006009e0(*(unsigned *)resources, 1, (RHMapWideText &)text))
        text =
            // STRING: GAME 0x006b0e48
            L"Invalid resource ID...";
    return text;
}

// FUNCTION: GAME 0x00540ed0
void RHShortMissionUpdateCalls::FUN_00540ed0(RHMission *mission)
{
    RHMenuShortMissionDescription *menu = (RHMenuShortMissionDescription *)this;
    if (menu->m_mission != mission)
    {
        menu->m_mission = mission;
        ((RHShortMissionWidgetCalls *)&menu->m_title)->V2c(menu->FUN_00540d50());
        menu->FUN_00540d20();
        if (mission && (char)mission->FUN_0054cbf0())
        {
            menu->m_blazons = new RHMenuShortMissionBlazons(mission, this);
            menu->m_blazons->FUN_0044ef60(RHMapBox(5.0f, 80.0f, 215.0f, 95.0f), 0);
        }
        unsigned picture = *(unsigned short *)((char *)mission->m_profile + 0x4c) - (unsigned short)mission->m_4 - 1;
        if (picture <= 3)
            ((RHShortMissionWidgetCalls *)&menu->m_picture)->V38(picture);
        else
            ((RHShortMissionWidgetCalls *)&menu->m_picture)->V38(4);
    }
    if (mission && (char)mission->FUN_0054cbf0())
        menu->m_blazons->FUN_0044f960(0);
}

// FUNCTION: GAME 0x00541060
void RHMenuShortMissionDescription::FUN_00541060()
{
    SBGeoPoint2D position = ((SBGeoPoint2D &)g_inputPosition).Unk005fc190(SBGeoVector2D(25.0f, 25.0f));
    RHUnkFXDraw *draw = (RHUnkFXDraw *)g_unk0x6c11d0;
    SBGeoVector2D offset;
    SBGeoBoundingBox2D bounds(((RHMapWidget *)this)->V24());
    SBGeoBoundingBox2D previous(((RHMapWidget *)this)->V24());
    offset = position.Unk005fc110(bounds.Min());
    ((RHMobileUnk006091b0 *)&bounds)->FUN_006091b0(offset);
    if ((char)bounds.FUN_00609170(m_box)) {
        if ((float)draw->FUN_005e56c0(0) < bounds.Max().GetX())
            offset.m_x = (float)draw->FUN_005e56c0(0) - bounds.Max().GetX();
        else
            offset.m_x = 0.0f;
        if ((float)draw->FUN_005e5750(0) < bounds.Max().GetY())
            offset.m_y = (float)draw->FUN_005e5750(0) - bounds.Max().GetY();
        else
            offset.m_y = 0.0f;
        ((RHMobileUnk006091b0 *)&bounds)->FUN_006091b0(offset);
        ((SBFrameWnd *)this)->FUN_0061ad20(bounds);
        previous.FUN_00607e90(bounds);
        m_screen->FUN_0053c7f0((unsigned long)&previous);
        ((RHMobileUnk00607da0 *)&m_box)->FUN_00607da0((const RHMobileUnk00607da0 &)bounds);
    }
    ((RHMapWidget *)this)->V1c();
}

void EmitRHShortMissionUpdate(RHMenuShortMissionDescription *menu, RHMission *mission)
{
    ((RHShortMissionUpdateCalls *)menu)->FUN_00540ed0(mission);
    menu->FUN_00541060();
}
