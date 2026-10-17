// RHMenuPopupScroll.cpp — popup scroll menu TU (code 0x005394e0..). See
// RHMenuPopupScroll.h for the binding evidence.

#include "SBNullstr.h"
#include "RHMenuPopupScroll.h"

// FUNCTION: GAME 0x005394e0
void RHMenuPopupScroll::FUN_005394e0(RHMenuEvent *event)
{
    if (FUN_00539500(event))
        ((RHUnk0048a970 *)this)->Unk((int)event);
}

// FUNCTION: GAME 0x00539500
bool RHMenuPopupScroll::FUN_00539500(RHMenuEvent *event)
{
    bool handled = false;
    if (event->m_type == 2 && event->m_widget == (char *)this + 0x144)
        handled = FUN_0053a860(2, event->m_widget, event->m_data);
    return handled;
}

// FUNCTION: GAME 0x00539710
void *RHMenuPopupScroll::FUN_00539710(unsigned flags)
{
    this->~RHMenuPopupScroll();
    if (flags & 1)
        operator delete(this);
    return this;
}

extern RHUnk0048a970 *g_unk0x6c0b3c;

// GLOBAL: GAME 0x006b0f8c
unsigned long g_unk0x006b0f8c = 0xffffffff;

// FUNCTION: GAME 0x0053a000
void RHMenuPopupScroll::FUN_0053a000(void *text, void *title, bool flag)
{
    bool paused = FUN_0053a840();
    RHMenuScreenView screen(0, 0, paused, paused, (char *)g_unk0x6c0b3c + 0x68);
    screen.FUN_0053be40(0);
    FUN_0053a380(&screen, *(const std::wstring *)text, *(const std::string *)title, flag);
}

// FUNCTION: GAME 0x0053a0b0
void RHMenuPopupScroll::FUN_0053a0b0(int id)
{
    bool paused = FUN_0053a840();
    RHMenuScreenView screen(0, 0, paused, paused, (char *)g_unk0x6c0b3c + 0x68);
    screen.FUN_0053be40(0);
    FUN_0053a4c0(&screen, id, std::string(), 4);
}

// FUNCTION: GAME 0x0053a1d0
void RHMenuPopupScroll::FUN_0053a1d0(const std::vector<int> &ids)
{
    RHMenuScreenView screen(0, 0, FUN_0053a840(), FUN_0053a840(), (char *)g_unk0x6c0b3c + 0x68);
    screen.FUN_0053be40(0);
    for (const int *id = ids.begin(); id != ids.end(); ++id)
        FUN_0053a4c0(&screen, *id, std::string(), 4);
}

// Parked: the loop-invariant screen/title/flag arguments take different callee-saved registers.
// STUB: GAME 0x0053a380
void RHMenuPopupScroll::FUN_0053a380(RHMenuScreenView *screen, const std::wstring &message, const std::string &title, bool flag)
{
    std::wstring text(message);
    while (text.length() != 0) {
        RHMenuPopupScroll menu(screen, text, title, flag);
        menu.FUN_00539b30();
        menu.FUN_00544b80(true, true);
        const std::wstring &next = menu.FUN_0053a820();
        typedef std::wstring &(std::wstring::*Assign)(const std::wstring &, unsigned, unsigned);
        Assign assign = &std::wstring::assign;
        (text.*assign)(next, 0, std::wstring::npos);
    }
    g_unk0x006b0f8c = *(unsigned long *)((char *)g_pEngine + 0x4a94);
}

// FUNCTION: GAME 0x0053a4c0
void RHMenuPopupScroll::FUN_0053a4c0(RHMenuScreenView *screen, int id, const std::string &title, int flags)
{
    std::wstring text = FUN_0053a660(id);
    while (text.length() != 0) {
        RHMenuPopupScroll menu(screen, text, id, title, flags);
        menu.FUN_00539b30();
        menu.FUN_00544b80(true, true);
        const std::wstring &next = menu.FUN_0053a820();
        typedef std::wstring &(std::wstring::*Assign)(const std::wstring &, unsigned, unsigned);
        Assign assign = &std::wstring::assign;
        (text.*assign)(next, 0, std::wstring::npos);
    }
    g_unk0x006b0f8c = *(unsigned long *)((char *)g_pEngine + 0x4a94);
}

struct RHPopupScrollSet
{
    undefined m_00[0x20];
    int *m_first;
    int *m_last;
};

// FUNCTION: GAME 0x0053a2d0
void RHMenuPopupScroll::FUN_0053a2d0()
{
    RHPopupScrollSet *set = (RHPopupScrollSet *)g_pEngine->GetDynResources(0);
    std::vector<int> ids;
    for (int id = 0; id != (set->m_first == 0 ? 0 : set->m_last - set->m_first); ++id)
        ((SBArray<RHSaveGame *> *)&ids)->Insert((RHSaveGame **)ids.end(), 1, (RHSaveGame *const &)id);
    FUN_0053a1d0(ids);
}

#include "SBResourceManager.h"

extern RHMapResources *g_unk0x006c1840;

// FUNCTION: GAME 0x0053a5f0
unsigned long RHMenuPopupScroll::FUN_0053a5f0()
{
    return (char)((SBResourceManager *)g_unk0x006c1840)->FUN_00600f10(0xa4) ? 0xa4 : 0;
}

// Parked: retained resource receiver and array-base reloads have different register lifetimes.
// STUB: GAME 0x0053a610
unsigned long RHMenuPopupScroll::FUN_0053a610(unsigned long index)
{
    RHPopupScrollSet *set = (RHPopupScrollSet *)g_pEngine->GetDynResources(0);
    if (set != 0)
    {
        if (set->m_first != 0 && index < (unsigned)(set->m_last - set->m_first))
            return set->m_first[index];
        ((SBResourceManager *)g_unk0x006c1840)->FUN_00600f10(set->m_first[index]);
    }
    return FUN_0053a5f0();
}

void RHMenuPopupScrollEmitPictures(unsigned long index)
{
    RHMenuPopupScroll::FUN_0053a610(index);
}

// FUNCTION: GAME 0x0053a820
const std::wstring &RHMenuPopupScroll::FUN_0053a820()
{
    return *(const std::wstring *)((char *)this + 0x440);
}

// FUNCTION: GAME 0x0053a830
void FUN_0053a830()
{
    g_unk0x006b0f8c = 0xffffffff;
}

// FUNCTION: GAME 0x0053a840
bool RHMenuPopupScroll::FUN_0053a840()
{
    if (*(unsigned long *)((char *)g_pEngine + 0x4a94) == g_unk0x006b0f8c)
        return false;
    return true;
}
