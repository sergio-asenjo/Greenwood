#ifndef RHPORTRAITBAR_H
#define RHPORTRAITBAR_H

#include <vector>

class SBUI;
class RHWidgetPortrait;

class RHPortraitArray : public std::vector<RHWidgetPortrait *>
{
public:
    RHWidgetPortrait **First() const { return _First; }
    RHWidgetPortrait **Last() const { return _Last; }
    unsigned int GetSize() const { return size(); }
};

class RHPortraitBar
{
public:
    RHPortraitBar(SBUI *owner);
    ~RHPortraitBar();
    void AddPortrait(RHWidgetPortrait *portrait);
    void FUN_0055e7a0(unsigned index);
    RHWidgetPortrait *FUN_0055e7e0(const void *actor) const;
    int GetPortraitIndex(const RHWidgetPortrait *portrait) const;
    unsigned FUN_0055e880();
    void MakeAllAdditions();
    void MakeAllRemovals();
    void MakePlacement();
    void RemovePortrait(RHWidgetPortrait *portrait);
    void RemoveAllPortraits();
    void FUN_0055ecb0(bool opened);
    void FUN_0055ebf0();
    void Resize();
    void SetPortraitOpened(const void *actor, bool opened);
    void ShiftPortraitsToLeft();
    void ShiftPortraitsToRight();
    void FUN_0055eda0();
    void UpdateBlinkings();
    void Emit(RHWidgetPortrait *portrait, const void *actor);

    RHPortraitArray portraits;
    RHPortraitArray additions;
    RHPortraitArray removals;
    SBUI *ui;
    unsigned int shift;
    bool dirty;
};

#endif
