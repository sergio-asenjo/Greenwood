#ifndef RHMENUSHORTMISSIONDESCRIPTIONCORE_H
#define RHMENUSHORTMISSIONDESCRIPTIONCORE_H

#include <string>
#ifndef SBGEO_BOUNDINGBOX2D_VIEW
#include "SBGeoBoundingBox2DCore.h"
#endif
#include "RHMenuWindowClass.h"
#include "RHMenuShortMissionBlazons.h"
#include "RHMenuShortMissionTitle.h"

typedef RHGameRenderer0060dbc0 RHMenuShortMissionRenderer;
typedef RHGameLifetime00515f00 RHMenuShortMissionText;
typedef RHGameLifetime0044fe90 RHMenuShortMissionPicture;

// SIZE 0x380
// VTABLE: GAME 0x00679940
class RHMenuShortMissionDescription : public RHMenuWindow
{
public:
    RHMenuShortMissionDescription(RHMenuWindowScreen *screen);
    ~RHMenuShortMissionDescription();
    void *FUN_00540830(unsigned flags);
    bool Create();
    void FUN_00540d20();
    std::wstring FUN_00540d50();
    void FUN_00541060();

    RHMenuShortMissionTitle m_title; // 0xc8
    RHMenuShortMissionText m_text; // 0x1c8
    RHMenuShortMissionPicture m_picture; // 0x294
    SBGeoBoundingBox2D m_box; // 0x364
    RHMenuShortMissionBlazons *m_blazons; // 0x378
    void *m_mission; // 0x37c
};

#endif
