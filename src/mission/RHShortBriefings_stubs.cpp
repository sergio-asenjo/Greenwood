#include "SBNullstr.h"
#include "RHShortBriefings.h"

RHShortBriefingsWidgetBase::RHShortBriefingsWidgetBase() {}
RHShortBriefingsWidgetBase::~RHShortBriefingsWidgetBase() {}
RHShortBriefingsRenderer::RHShortBriefingsRenderer() {}
RHShortBriefingsRenderer::~RHShortBriefingsRenderer() {}
void RHShortBriefingsCalls::FUN_005a2450(void *, void *) {}

class RHBriefingNarrowText;
class RHBriefingParentCalls
{
public:
    void *FUN_00544b60(const RHBriefingNarrowText &name);
};

void *RHBriefingParentCalls::FUN_00544b60(const RHBriefingNarrowText &) { return 0; }

class RHBriefingTitleBase
{
public:
    RHBriefingTitleBase();
    ~RHBriefingTitleBase();
};

RHBriefingTitleBase::RHBriefingTitleBase() {}
RHBriefingTitleBase::~RHBriefingTitleBase() {}

class SBGeoPoint2D;
class SBGeoBoundingBox2D
{
public:
    SBGeoBoundingBox2D(const SBGeoPoint2D &point);
};

SBGeoBoundingBox2D::SBGeoBoundingBox2D(const SBGeoPoint2D &) {}
