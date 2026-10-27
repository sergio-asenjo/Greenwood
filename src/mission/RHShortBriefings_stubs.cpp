#include "SBNullstr.h"
#include "SBGeoBoundingBox2DCore.h"
#include "RHShortBriefings.h"

RHShortBriefingsWidgetBase::RHShortBriefingsWidgetBase() {}
RHShortBriefingsWidgetBase::~RHShortBriefingsWidgetBase() {}
RHShortBriefingsRenderer::RHShortBriefingsRenderer() {}
RHShortBriefingsRenderer::~RHShortBriefingsRenderer() {}
void RHShortBriefingsCalls::FUN_005a2450(void *, void *) {}

// FUNCTION: GAME 0x00607ad0
SBGeoBoundingBox2D::SBGeoBoundingBox2D(const SBGeoPoint2D &point)
{
    m_p0 = point;
    m_p1 = point;
    m_flag = true;
}
