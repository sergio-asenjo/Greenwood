#ifndef RHPORTRAITQUICKLIST_H
#define RHPORTRAITQUICKLIST_H

struct RHPortraitQuickEntry;
struct RHPortraitWidgetEvent;
class RHPortraitPCList;

class RHPortraitQuickList : public RHPortraitRootList
{
public:
    bool FUN_005dd1d0(RHPortraitPCList &list);
    RHPortraitWidgetEvent *FUN_005dd370(const void *input);
    int m_b0;
    RHPortraitQuickEntry *m_first;
    RHPortraitQuickEntry *m_last;
    RHPortraitQuickEntry *m_end;
};

#endif
