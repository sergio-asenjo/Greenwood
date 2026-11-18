#ifndef RHPORTRAITRENDERER0060D470_H
#define RHPORTRAITRENDERER0060D470_H

#include <string>
#include "Decomp.h"

#ifndef SBGEO_BOUNDINGBOX2D_VIEW
#include "SBGeoBoundingBox2D.h"
#endif

class RHMapResources;
class SBGeoPoint2D;
class SBDrawManager;

struct RHPortraitRendererSurfaces
{
    unsigned int values[2];
    unsigned int &operator[](unsigned int index) { return values[index]; }
    const unsigned int &operator[](unsigned int index) const { return values[index]; }
};

// VTABLE: GAME 0x0067a654
// SIZE 0x4c
class RHPortraitRenderer0060d470
{
public:
    RHPortraitRenderer0060d470();
    RHPortraitRenderer0060d470(const RHPortraitRenderer0060d470 &other);
    RHPortraitRenderer0060d470 &operator=(const RHPortraitRenderer0060d470 &other);
    virtual ~RHPortraitRenderer0060d470();
    virtual void FUN_0060d530(unsigned int surface);
    virtual void FUN_0060d780(const SBGeoPoint2D &point);
    virtual void FUN_0060d6a0(const SBGeoBoundingBox2D &box);
    void AssignName(const std::wstring &name)
    {
        m_name.assign(name, 0, std::wstring::npos);
    }
    void AssignPosition(const SBGeoBoundingBox2D &position);
    RHMapResources *m_resources;   // 0x04
    SBGeoBoundingBox2D m_position; // 0x08
    SBDrawManager *m_drawManager;   // 0x1c
    unsigned int m_hardware;       // 0x20
    unsigned int m_24;             // 0x24
    std::wstring m_name;           // 0x28
    long m_widgetResource;         // 0x38
    unsigned int m_3c;             // 0x3c
    RHPortraitRendererSurfaces m_surfaces;
    unsigned int m_48;             // 0x48
};

#endif
