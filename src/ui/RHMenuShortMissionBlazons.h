#ifndef RHMENUSHORTMISSIONBLAZONS_H
#define RHMENUSHORTMISSIONBLAZONS_H

class SBGeoBoundingBox2D;
class RHFocusManager;
class RHGameLifetime0044fe90;
#include "RHMapBox.h"

class RHMenuShortMissionBlazons
{
public:
    RHMenuShortMissionBlazons(void *mission, void *parent);
    ~RHMenuShortMissionBlazons();
    bool FUN_0044ef60(const RHMapBox &bounds, RHFocusManager *focus);
    unsigned long ComputeNumberOfBlazonsPerRow(const SBGeoBoundingBox2D &bounds, bool &normal) const;
    static void FUN_0044f400(RHGameLifetime0044fe90 &widget);
    static void FUN_0044f5d0(RHGameLifetime0044fe90 &widget);
    static void FUN_0044f750(RHGameLifetime0044fe90 &widget);
    void FUN_0044f8d0(unsigned long value);
    void FUN_0044f960(int value);
    void *m_mission;
    void *m_parent;
    RHGameLifetime0044fe90 *m_widgets;
    unsigned long m_count;
    unsigned long m_10;
    bool m_14;
    unsigned long m_18;
};

#endif
