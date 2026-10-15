#include "RHSaveGameManager.h"
#include "SBUI.h"
#include <algorithm>
#include <vector>

#include "RHWidgetPortraitClass.h"

class RHPortraitCtorCalls
{
public:
    void FUN_005d6940(unsigned short index);
};

struct RHPortraitWindow
{
    virtual void V00() = 0;
    virtual void V04() = 0;
    virtual void V08() = 0;
    virtual void V0c() = 0;
    virtual void V10() = 0;
    virtual void V14() = 0;
    virtual void V18() = 0;
    virtual void V1c() = 0;
    virtual void V20() = 0;
    virtual void V24() = 0;
    virtual void V28() = 0;
    virtual void V2c() = 0;
    virtual void V30() = 0;
    virtual void V34() = 0;
    virtual void V38() = 0;
    virtual void V3c() = 0;
    virtual void V40() = 0;
    virtual bool V44() = 0;
    virtual void V48(bool visible) = 0;
};

template<class T> T &RHPortraitField(void *object, unsigned int offset)
{
    return *(T *)((char *)object + offset);
}

class RHMinimap;
extern RHMinimap *g_unk0x6c0c50;

class RHPortraitArray : public std::vector<RHWidgetPortrait *>
{
public:
    RHWidgetPortrait **First() const { return _First; }
    RHWidgetPortrait **Last() const { return _Last; }
    unsigned int GetSize() const { return size(); }
};

#define m_first First()
#define m_last Last()

class RHPortraitBar
{
public:
    RHPortraitBar(SBUI *owner);
    RHWidgetPortrait *FUN_0055e7e0(const void *actor) const;
    int GetPortraitIndex(const RHWidgetPortrait *portrait) const;
    void MakeAllAdditions();
    void MakeAllRemovals();
    void MakePlacement();
    void RemovePortrait(RHWidgetPortrait *portrait);
    void RemoveAllPortraits();
    void Resize();
    void SetPortraitOpened(const void *actor, bool opened);
    void ShiftPortraitsToLeft();
    void ShiftPortraitsToRight();
    void UpdateBlinkings();
    void Emit(RHWidgetPortrait *portrait, const void *actor);

    RHPortraitArray portraits;
    RHPortraitArray additions;
    RHPortraitArray removals;
    SBUI *ui;
    unsigned int shift;
    bool dirty;
};

DECOMP_SIZE_ASSERT(RHPortraitBar, 0x3c)

// FUNCTION: GAME 0x0055e6c0
RHPortraitBar::RHPortraitBar(SBUI *owner) : ui(owner), shift(0), dirty(false)
{
}

// FUNCTION: GAME 0x0055e7e0
RHWidgetPortrait *RHPortraitBar::FUN_0055e7e0(const void *actor) const
{
    RHWidgetPortrait *result = 0;
    RHWidgetPortrait **it;
    for (it = portraits.m_first; it != portraits.m_last; ++it)
    {
        if (RHPortraitField<void *>(*it, 0xe1c) == actor)
        {
            result = *it;
            break;
        }
    }
    for (it = additions.m_first; it != additions.m_last; ++it)
    {
        if (RHPortraitField<void *>(*it, 0xe1c) == actor)
        {
            result = *it;
            break;
        }
    }
    return result;
}

// FUNCTION: GAME 0x0055e840
int RHPortraitBar::GetPortraitIndex(const RHWidgetPortrait *portrait) const
{
    int result = -1;
    unsigned int index = 0;
    RHWidgetPortrait **it = portraits.m_first;
    while (index != portraits.GetSize())
    {
        if (*it == portrait)
        {
            result = index;
            break;
        }
        ++index;
        ++it;
    }
    return result;
}

// FUNCTION: GAME 0x0055e8a0
void RHPortraitBar::MakeAllAdditions()
{
    for (RHWidgetPortrait **it = additions.begin(); it != additions.end(); ++it)
    {
        RHWidgetPortrait *portrait = *it;
        if (GetPortraitIndex(portrait) == -1)
        {
            ((SBArray<RHSaveGame *> *)&portraits)->Insert((RHSaveGame **)portraits.end(), 1, (RHSaveGame *const &)portrait);
            ui->FUN_00619800((SBUIWindowView *)portrait);
        }
        ui->FUN_00619a00((SBUIWindowView *)g_unk0x6c0c50);
    }
    unsigned short remaining = (unsigned short)portraits.GetSize();
    if (remaining > 1)
    {
        remaining = (unsigned short)portraits.GetSize() - 1;
        while (remaining != 0)
        {
            bool sorted = true;
            for (unsigned short index = 1; index <= remaining; ++index)
            {
                RHWidgetPortrait **position = portraits.begin() + index;
                RHWidgetPortrait *previous = position[-1];
                RHWidgetPortrait *current = position[0];
                void *previousActor = RHPortraitField<void *>(previous, 0xe1c);
                void *currentActor = RHPortraitField<void *>(current, 0xe1c);
                void *previousProfile = RHPortraitField<void *>(previousActor, 0x5fc);
                void *currentProfile = RHPortraitField<void *>(currentActor, 0x5fc);
                if (RHPortraitField<unsigned short>(previousProfile, 0x8c) < RHPortraitField<unsigned short>(currentProfile, 0x8c))
                {
                    position[-1] = current;
                    position[0] = previous;
                    sorted = false;
                }
            }
            if (sorted)
                break;
            --remaining;
        }
    }
    ((std::vector<RHWidgetPortrait *> *)&additions)->erase(additions.begin(), additions.end());
}

// FUNCTION: GAME 0x0055e9e0
void RHPortraitBar::MakeAllRemovals()
{
    for (RHWidgetPortrait **it = removals.begin(); it != removals.end(); ++it)
    {
        RHWidgetPortrait **position = std::find(portraits.begin(), portraits.end(), *it);
        if (position != portraits.end())
        {
            ((std::vector<RHWidgetPortrait *> *)&portraits)->erase(position);
            ((RHMapWindowPart *)ui)->FUN_00619ad0(*it);
        }
    }
    ((std::vector<RHWidgetPortrait *> *)&removals)->erase(removals.begin(), removals.end());
}

// FUNCTION: GAME 0x0055ea80
void RHPortraitBar::MakePlacement()
{
    if (portraits.GetSize() <= 5)
    {
        for (unsigned int index = 0; index < portraits.GetSize(); ++index)
        {
            ((RHPortraitCtorCalls *)portraits.m_first[index])->FUN_005d6940((unsigned short)index);
            ((RHPortraitWindow *)portraits.m_first[index])->V48(true);
        }
        shift = 0;
    }
    else
    {
        shift %= portraits.GetSize();
        for (unsigned int index = 0; index < portraits.GetSize(); ++index)
        {
            unsigned int slot = (index + portraits.GetSize() - shift) % portraits.GetSize();
            if (slot < 5)
            {
                ((RHPortraitCtorCalls *)portraits.m_first[index])->FUN_005d6940((unsigned short)slot);
                ((RHPortraitWindow *)portraits.m_first[index])->V48(true);
            }
            else
                ((RHPortraitWindow *)portraits.m_first[index])->V48(false);
        }
    }
    dirty = false;
}

// FUNCTION: GAME 0x0055eb30
void RHPortraitBar::RemovePortrait(RHWidgetPortrait *portrait)
{
    RHWidgetPortrait **position = std::find(removals.begin(), removals.end(), portrait);
    if (position == removals.end())
    {
        ((SBArray<RHSaveGame *> *)&removals)->InsertLast((RHSaveGame *const &)portrait);
        RHPortraitField<bool>(portrait, 0xca9) = false;
    }
    position = std::find(additions.begin(), additions.end(), portrait);
    if (position != additions.end())
    {
        ((std::vector<RHWidgetPortrait *> *)&additions)->erase(position);
    }
}

// FUNCTION: GAME 0x0055ebc0
void RHPortraitBar::RemoveAllPortraits()
{
    for (RHWidgetPortrait **it = portraits.begin(); it != portraits.end(); ++it)
        RemovePortrait(*it);
}

// FUNCTION: GAME 0x0055ec40
void RHPortraitBar::Resize()
{
    unsigned int count = portraits.GetSize() < 5 ? portraits.GetSize() : 5;
    for (unsigned int index = 0; index != count; ++index)
        ((RHPortraitCtorCalls *)portraits.m_first[(shift + index) % portraits.GetSize()])->FUN_005d6940((unsigned short)index);
}

// FUNCTION: GAME 0x0055ed10
void RHPortraitBar::SetPortraitOpened(const void *actor, bool opened)
{
    RHWidgetPortrait *portrait = FUN_0055e7e0(actor);
    if (portrait)
    {
        if (opened)
            portrait->Method005d6690();
        else
            portrait->Method005d67e0();
    }
}

// Parked: LEA base and index registers are encoded in the opposite order.
// STUB: GAME 0x0055ed40
void RHPortraitBar::ShiftPortraitsToLeft()
{
    if (portraits.GetSize() > 5)
    {
        dirty = true;
        shift = (shift + portraits.GetSize() - 1) % portraits.GetSize();
    }
}

// FUNCTION: GAME 0x0055ed70
void RHPortraitBar::ShiftPortraitsToRight()
{
    unsigned int count = portraits.GetSize();
    if (count > 5)
    {
        dirty = true;
        shift = (shift + 1) % count;
    }
}

// FUNCTION: GAME 0x0055ee00
void RHPortraitBar::UpdateBlinkings()
{
    for (RHWidgetPortrait **it = portraits.begin(); it != portraits.end(); ++it)
        (*it)->FUN_005d9180();
}

void RHPortraitBar::Emit(RHWidgetPortrait *portrait, const void *actor)
{
    new RHPortraitBar(ui);
    FUN_0055e7e0(actor);
    GetPortraitIndex(portrait);
    MakeAllAdditions();
    MakeAllRemovals();
    MakePlacement();
    RemovePortrait(portrait);
    RemoveAllPortraits();
    Resize();
    SetPortraitOpened(actor, true);
    ShiftPortraitsToLeft();
    ShiftPortraitsToRight();
    UpdateBlinkings();
}
