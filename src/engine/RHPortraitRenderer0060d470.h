#ifndef RHPORTRAITRENDERER0060D470_H
#define RHPORTRAITRENDERER0060D470_H

#include <string>
#include "Decomp.h"

#ifndef SBGEO_BOUNDINGBOX2D_VIEW
#include "SBGeoBoundingBox2D.h"
#endif

class RHMapResources;

// VTABLE: GAME 0x0067a654
// SIZE 0x4c
class RHPortraitRenderer0060d470
{
public:
    RHPortraitRenderer0060d470();
    ~RHPortraitRenderer0060d470();
    virtual void FUN_0060d530(unsigned int surface);
    RHMapResources *m_resources;   // 0x04
    SBGeoBoundingBox2D m_position; // 0x08
    void *m_drawManager;           // 0x1c
    unsigned int m_hardware;       // 0x20
    unsigned int m_24;             // 0x24
    std::wstring m_name;           // 0x28
    long m_widgetResource;         // 0x38
    unsigned int m_3c;             // 0x3c
    unsigned int m_40;             // 0x40
    unsigned int m_44;             // 0x44
    unsigned int m_48;             // 0x48
};

#endif
