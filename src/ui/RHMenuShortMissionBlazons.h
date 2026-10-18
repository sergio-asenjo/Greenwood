#ifndef RHMENUSHORTMISSIONBLAZONS_H
#define RHMENUSHORTMISSIONBLAZONS_H

class SBGeoBoundingBox2D;

class RHMenuShortMissionBlazons
{
public:
    ~RHMenuShortMissionBlazons();
    unsigned long ComputeNumberOfBlazonsPerRow(const SBGeoBoundingBox2D &bounds, bool &normal) const;
    void *m_mission;
    void *m_parent;
    void *m_widgets;
    unsigned long m_count;
    unsigned long m_10;
    bool m_14;
    unsigned long m_18;
};

#endif
