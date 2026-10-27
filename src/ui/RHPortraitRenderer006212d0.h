#ifndef RHPORTRAITRENDERER006212D0_H
#define RHPORTRAITRENDERER006212D0_H

#include "RHRendererGeometry.h"
#include "RHPortraitRenderer0060dab0.h"

// VTABLE: GAME 0x0067ae60
class RHPortraitRenderer006212d0 : public RHPortraitRenderer0060dab0
{
public:
    RHPortraitRenderer006212d0();
    ~RHPortraitRenderer006212d0();
    virtual void FUN_0060d530(unsigned int surface);
    virtual void FUN_0060d6a0(const SBGeoBoundingBox2D &box);
    std::wstring m_prompt;
    bool m_promptEnabled;
    void *m_font;
    void *m_alternateFont;
    void *m_textObject;
    SBGeoBoundingBox2D m_bounds;
    bool m_enabled;
    SBGeoVector2D m_offset;
};

#endif
