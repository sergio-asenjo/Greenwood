// RHMenuDialogue.cpp — translation unit with __FILE__ evidence at 0x0052b2e0
// ("P:\Robin Hood\RHMenuDialogue.cpp", symbols/functions-by-file.tsv).
//
// BINDING (0x0052b2e0 -> RHMenuDialogue::GetDialogue(unsigned long)):
//   - TU:        rhmenudialogue.cpp (embedded __FILE__ string 0x006b0b48).
//   - Class:     RHMenuDialogue (symbols/oracle-correlation.tsv:
//                rhmenudialogue -> class RHMenuDialogue, 23 methods).
//   - Method:    RHMenuDialogue::GetDialogue(unsigned long)
//                (symbols/mac-RH.txt; symbols/mac-functions-by-file.tsv maps
//                0x0014b2c8 in rhmenudialogue.cpp to GetDialogue). The Mac
//                oracle disassembly of that address confirms the shape:
//                it fetches the resource, bounds-checks `id` against the
//                array element count and indexes the array — identical to
//                the Windows function.
//   - Signals:
//       * argument shape: exactly one stack argument, used as an index into a
//         24-byte-element array and echoed as "dialogue ... ID %i" — a
//         dialogue lookup by id. GetDialogue is the only RHMenuDialogue method
//         taking a single unsigned long and returning a pointer (Display(
//         unsigned long) returns void; DisplaySingleDialogue takes two args).
//       * the two warnings name the domain: "Unable to get a dialogue." and
//         "Trying to play an invalid dialogue. The current level has no
//         dialogue withe ID %i." — the function's job is to fetch a dialogue.
//       * the callee (0x004e35a0) is RHEngine::GetDynResources(unsigned long):
//         the Mac oracle's GetDialogue calls RHEngine::GetDynResources(0) in
//         the same position with the same argument.
//       * the only caller, 0x0052a7b0, is the RHMenuDialogue constructor
//         (vtable 0x00679320): it pushes the ctor's `unsigned long` argument
//         and stores the result at [this+0x548].
//       * called WITHOUT a `this`: the ctor does not set ecx to the object
//         before the call (ecx holds the pushed id), so Windows emits it as a
//         static member — declared `static` here to reproduce that codegen.
//
// STATUS: exact 100% — instruction-for-instruction identical to the original.
//
// CODEGEN (why the bound check reads through a volatile pointer):
//   The original loads m_pDialoguesBegin once into eax for the bound check;
//   the /24 division then clobbers eax, and the return re-reads the member
//   into edx. A plain `set->m_pDialoguesBegin` would be CSE'd into a
//   callee-saved register (VC6 keeps the first load alive and never
//   re-reads). Reading the bound-check value through a volatile pointer
//   forces that first load to be a distinct memory access, so the return's
//   plain re-read survives as the original's `mov edx,[esi+0xc]`. The
//   volatile read also commits `set` to esi and orders the tail as the
//   original does (load, scale, pop edi, pop esi, combine).

#include "SBNullstr.h"
#include "RHMenuDialogue.h"
#include "RHMapWindowPart.h"
#include "RHMenuScreenView.h"
#include "RHMenuCloseCalls.h"
#include <stdlib.h>

typedef char RHMenuDialogueSize[(sizeof(RHMenuDialogue) == 0x55c) ? 1 : -1];

struct RHMenuEvent
{
    int m_type;
    void *m_widget;
    void *m_data;
};

class RHUnk0048a970
{
public:
    void Unk(int);
};

#include "RHSoundCore.h"

class RHGameMenuCalls
{
public:
    void FUN_00544b30();
};

class RHMenuWindow
{
public:
    void FUN_00544b80(bool, bool);
};

extern RHUnk0048a970 *g_unk0x6c0b3c;

#include "RHMapResources.h"

class SBUIUnk0060d530
{
public:
    bool FUN_0060d550(long);
    void *FUN_0060d690();
};

class RHMenuWindowUI;
class RHDialogueTextView
{
public:
    virtual void V00();
    virtual void V04();
    virtual void V08();
    virtual void V0c();
    virtual void V10();
    virtual void V14();
    virtual void V18();
    virtual void V1c();
    virtual void V20();
    virtual void V24();
    virtual void V28();
    virtual void V2c(const std::wstring &);
};

struct RHDialogueEntryView
{
    unsigned m_text;
    unsigned m_sound;
    unsigned m_08;
    unsigned long *m_first;
    unsigned long *m_last;
    unsigned long *m_end;
};

extern RHMapResources *g_unk0x006c1840;
extern std::string g_unk0x006c0660;
std::string FUN_004e4c70(const std::string &, const char *);
std::string FUN_004e4b40(const std::string &, const std::string &);

// GLOBAL: GAME 0x006b0b6c
unsigned long g_dialoguePortraits[16] = {
    0x102, 0xfd, 0x106, 0x103, 0xff, 0x100, 0x101, 0x108,
    0x107, 0x10a, 0x109, 0xfe, 0xfc, 0x104, 0x105, 0x10b
};

class RHDialoguePortraitView
{
public:
    virtual void V00();
    virtual void V04();
    virtual void V08();
    virtual void V0c();
    virtual void V10();
    virtual void V14();
    virtual void V18();
    virtual void V1c();
    virtual void V20();
    virtual void V24();
    virtual void V28();
    virtual void V2c();
    virtual void V30();
    virtual void V34();
    virtual void V38(int frame);
    virtual int V3c();
};

extern float g_unk0x006774f0;

// GLOBAL: GAME 0x006774fc
float g_dialogueVolumeHigh = 0.3f;

// GLOBAL: GAME 0x00679460
float g_dialogueVolumeMedium = 0.15f;

// GLOBAL: GAME 0x00679464
float g_dialogueVolumeLow = 0.02f;

template<class T>
static T &RHDialogueField(void *object, unsigned offset)
{
    return *(T *)((char *)object + offset);
}

// FUNCTION: GAME 0x0052a640
void RHMenuDialogue::RouteEvent(RHMenuEvent *event)
{
    if (HandleEvent(event))
        ((RHUnk0048a970 *)this)->Unk((int)event);
}

// FUNCTION: GAME 0x0052a660
bool RHMenuDialogue::HandleEvent(RHMenuEvent *event)
{
    bool handled = false;
    if (event->m_type == 2 && event->m_widget == m_bytes + 0x240)
        handled = OnSkip(2, event->m_widget, event->m_data);
    if (event->m_type == 2 && event->m_widget == m_bytes + 0x140)
        handled = ((RHMenuCloseCalls *)this)->FUN_0052b520(2, event->m_widget, event->m_data);
    if (event->m_type == 0x1000 && event->m_widget == RHDialogueField<void *>(this, 0x550))
        handled = OnTimer(0x1000, event->m_widget, event->m_data);
    return handled;
}

// FUNCTION: GAME 0x0052a810
void *RHMenuDialogue::FUN_0052a810(unsigned flags)
{
    this->~RHMenuDialogue();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x0052afd0
void RHMenuDialogue::Display(const std::vector<unsigned long> &dialogues)
{
    RHMenuScreenView screen(0, 0, true, true, (char *)g_unk0x6c0b3c + 0x68);
    for (std::vector<unsigned long>::const_iterator it = dialogues.begin(); it != dialogues.end(); ++it)
        DisplaySingleDialogue(&screen, *it);
}

// FUNCTION: GAME 0x0052b070
void RHMenuDialogue::Display(unsigned long id)
{
    RHMenuScreenView screen(0, 0, true, true, (char *)g_unk0x6c0b3c + 0x68);
    DisplaySingleDialogue(&screen, id);
}

class RHSequenceElement
{
public:
    virtual void Unk0();
    virtual void Unk1();
    virtual void Unk2();
    virtual void FUN_00585970(void *, bool);
    int Unk00587160(int);
};

// FUNCTION: GAME 0x0052b100
void RHMenuDialogue::Display(RHSequenceElement *sequence)
{
    RHMenuScreenView *screen = new RHMenuScreenView(0, 0, true, true, (char *)g_unk0x6c0b3c + 0x68);
    DisplaySingleDialogue(screen, sequence->Unk00587160(0x12));
    delete screen;
    sequence->FUN_00585970(0, true);
}

class RHSaveGame;

template<class T>
class SBArray
{
public:
    int m_grow;
    T *m_first;
    T *m_last;
    T *m_end;
    void Insert(T *position, unsigned count, const T &value);
};

// FUNCTION: GAME 0x0052b1b0
void RHMenuDialogue::DisplayAll()
{
    RHDialogueSet *set = g_pEngine->GetDynResources(0);
    std::vector<unsigned long> ids;
    for (unsigned long id = 0; id != (unsigned)(set->m_pDialoguesBegin == 0 ? 0 : set->m_pDialoguesEnd - set->m_pDialoguesBegin); ++id)
    {
        SBArray<RHSaveGame *> &array = (SBArray<RHSaveGame *> &)ids;
        array.Insert(array.m_last, 1, (RHSaveGame *const &)id);
    }
    Display(ids);
}

// FUNCTION: GAME 0x0052b260
void RHMenuDialogue::DisplaySingleDialogue(RHMenuScreenView *screen, unsigned long id)
{
    RHMenuDialogue dialogue(screen, id);
    dialogue.Create();
    ((RHMenuWindow *)&dialogue)->FUN_00544b80(true, true);
}

// FUNCTION: GAME 0x0052b2e0
RHDialogue *RHMenuDialogue::GetDialogue(unsigned long id)
{
    RHDialogueSet *set = g_pEngine->GetDynResources(0);
    if (set == 0)
    {
        SBAssert((int)set,
                 // STRING: GAME 0x6b0b48
                 "P:\\Robin Hood\\RHMenuDialogue.cpp",
                 280,
                 // STRING: GAME 0x6b0c0c
                 "Warning : Unable to get a dialogue.");
        return 0;
    }

    RHDialogue *begin = *(RHDialogue *volatile *)&set->m_pDialoguesBegin;
    if (begin != 0 &&
        (unsigned)(((char *)set->m_pDialoguesEnd - (char *)begin) / 24) > id)
    {
        return set->m_pDialoguesBegin + id;
    }

    SBAssert(0,
             "P:\\Robin Hood\\RHMenuDialogue.cpp",
             291,
             // STRING: GAME 0x6b0bac
             "Warning : Trying to play an invalid dialogue. The current level has no dialogue withe ID %i.",
             id);
    return 0;
}

// FUNCTION: GAME 0x0052b370
bool RHMenuDialogue::GetNextSentence(std::wstring &text, std::string &sound, unsigned long &portrait)
{
    ++m_sentence;
    RHDialogueEntryView *entry = (RHDialogueEntryView *)m_dialogue;
    unsigned index = m_sentence;
    if (entry == 0)
    {
        text =
            // STRING: GAME 0x006b0d20
            L"Invalid dialogue ID...";
        return true;
    }
    if (entry->m_first != 0 && index < (unsigned)(entry->m_last - entry->m_first))
    {
        RHMapResources *resources = g_unk0x006c1840;
        if (!resources->FUN_006009e0(entry->m_text, index, (RHMapWideText &)text))
        {
            const wchar_t *fallback =
                // STRING: GAME 0x006b0ca8
                L"Unable to retrieve the sentence text : invalide resource !";
            text.assign(fallback, std::char_traits<wchar_t>::length(fallback));
        }
        if (!resources->FUN_00600bb0(RHDialogueField<RHDialogueEntryView *>(this, 0x548)->m_sound,
                                     RHDialogueField<unsigned>(this, 0x54c), sound))
            text +=
                // STRING: GAME 0x006b0c30
                L"Unable to retreive the sentence sound : invalide resource !";
        portrait = RHDialogueField<RHDialogueEntryView *>(this, 0x548)->m_first[RHDialogueField<unsigned>(this, 0x54c)];
        return true;
    }
    return false;
}

// FUNCTION: GAME 0x0052b510
bool RHMenuDialogue::OnSkip(int, void *, void *)
{
    UpdateDialogue();
    return false;
}

// FUNCTION: GAME 0x0052b530
bool RHMenuDialogue::OnTimer(int, void *, void *)
{
    if (RHDialogueField<RHSound *>(this, 0x558)->IsDialogFinished() == true)
        UpdateDialogue();
    else
        UpdatePortrait();
    return false;
}

// FUNCTION: GAME 0x0052b560
void RHMenuDialogue::UpdateDialogue()
{
    std::wstring text;
    std::string sound;
    unsigned long portrait;
    if (GetNextSentence(text, sound, portrait) == true)
    {
        ((RHDialogueTextView *)(m_bytes + 0x340))->V2c(text);
        if (portrait > 15)
            portrait = 15;
        ((SBUIUnk0060d530 *)(m_bytes + 0x4e0))->FUN_0060d550(g_dialoguePortraits[portrait]);
        ((RHDialoguePortraitView *)(m_bytes + 0x460))->V38(0);
        RHSound *player = RHDialogueField<RHSound *>(this, 0x558);
        if (!player->IsDialogFinished())
            RHDialogueField<RHSound *>(this, 0x558)->CloseDialog();
        ((RHMapWindowPart *)RHDialogueField<RHMenuWindowScreen *>(this, 0xb4)->FUN_0053bf30())->FUN_00618850(0);
        RHDialogueField<RHSound *>(this, 0x558)->PlayDialog(FUN_004e4c70(g_unk0x006c0660, "\\") + sound);
    }
    else
        ((RHGameMenuCalls *)this)->FUN_00544b30();
}

// FUNCTION: GAME 0x0052b760
void RHMenuDialogue::UpdatePortrait()
{
    float volume = RHDialogueField<RHSound *>(this, 0x558)->GetDialogVolume();
    int frame;
    if (volume < g_unk0x006774f0)
        frame = 0;
    else if (volume < g_dialogueVolumeLow)
        frame = 1;
    else if (volume < g_dialogueVolumeMedium)
        frame = 2;
    else if (volume < g_dialogueVolumeHigh)
        frame = 3;
    else
        frame = 4;
    RHDialoguePortraitView *portrait = (RHDialoguePortraitView *)(m_bytes + 0x460);
    if (frame == portrait->V3c())
        ++RHDialogueField<int>(this, 0x554);
    else
        RHDialogueField<int>(this, 0x554) = 0;
    if (RHDialogueField<int>(this, 0x554) == 3)
    {
        frame = rand() % 2;
        RHDialogueField<int>(this, 0x554) = 0;
    }
    portrait->V38(frame);
}

#include "rhuirenderer_005cb420.h"
#include "RHUnk005cbb80.h"
#include "RHGameWidgetLifetime.h"

class RHUnk0052b860
{
public:
    virtual void V00();
    virtual void V04();
    virtual void V08();
    virtual void V0c();
    virtual void V10();
    virtual void V14();
    virtual void V18();
    virtual void V1c();
    virtual void V20();
    virtual unsigned V24();
    unsigned FUN_0052b850();
    void FUN_0052b860();
    void FUN_0052bc20();
};

struct RHDialogueWidgetEvent;
struct RHDialogueWidgetInput;

class RHUnk0052bd70
{
public:
    void FUN_0052b830(unsigned value);
    unsigned FUN_0052b840();
    RHDialogueWidgetEvent *FUN_0052bc40(const RHDialogueWidgetInput &input);
    unsigned FUN_0052bd70();
    unsigned char m_bytes[0xe8];
};

// FUNCTION: GAME 0x0052b830
void RHUnk0052bd70::FUN_0052b830(unsigned value)
{
    RHDialogueField<unsigned>(this, 0xe4) = value;
}

// FUNCTION: GAME 0x0052b840
unsigned RHUnk0052bd70::FUN_0052b840()
{
    return RHDialogueField<unsigned>(this, 0xe4);
}

// FUNCTION: GAME 0x0052b850
unsigned RHUnk0052b860::FUN_0052b850()
{
    return 255;
}

// FUNCTION: GAME 0x0052b860
void RHUnk0052b860::FUN_0052b860()
{
    ((RHUnk005cba10 *)((char *)this + 0x80))->FUN_005cba10(V24());
}

struct RHDialogueCachedEvent
{
    unsigned char m_prefix[0x5c];
    unsigned m_type;
    unsigned m_bounds[5];
    void *m_widget;
    void *m_next;
};

class RHUnk0052bbb0
{
public:
    virtual void V00();
    virtual void V04();
    virtual void V08();
    virtual void V0c();
    virtual void V10();
    virtual void V14();
    virtual void V18();
    virtual void V1c();
    virtual void V20();
    virtual unsigned V24();
    virtual void V28();
    virtual void V2c();
    virtual void V30();
    virtual unsigned V34(unsigned);
    unsigned FUN_0052b880();
    unsigned *FUN_0052bb40(unsigned);
    void FUN_0052b940(const std::wstring &);
    void SetText(const std::wstring &text)
    {
        m_dirtyFirst = true;
        m_dirtySecond = true;
        m_text.assign(text, 0, std::wstring::npos);
    }
    void FUN_0052bbb0();
    unsigned *FUN_0052bbd0(unsigned);
    unsigned *MakeEvent(unsigned index)
    {
        RHDialogueField<unsigned>(this, 0xc8) = index;
        ((RHMobileUnk00607da0 *)((char *)this + 0x60))->FUN_00607da0(
            *(RHMobileUnk00607da0 *)((SBUIUnk0060d530 *)((char *)this + 0x80))->FUN_0060d690());
        RHDialogueCachedEvent *event = (RHDialogueCachedEvent *)this;
        event->m_type = V34(V24());
        event->m_next = 0;
        event->m_widget = this;
        return &event->m_type;
    }
    unsigned char m_04[0xc];
    std::wstring m_text;
    unsigned char m_20[0x88];
    std::wstring m_rendererText;
    unsigned char m_b8[0x64];
    bool m_dirtyFirst;
    bool m_dirtySecond;
};

// FUNCTION: GAME 0x0052b880
unsigned RHUnk0052bbb0::FUN_0052b880()
{
    return RHDialogueField<char>(this, 4) == 1 ? 1 : 255;
}

// Parked: first wide-string cleanup stays out-of-line and erase scheduling differs.
// STUB: GAME 0x0052b940
void RHUnk0052bbb0::FUN_0052b940(const std::wstring &text)
{
    SetText(text);
    RHDialogueField<std::wstring>(this, 0xa8) = text;
}

// FUNCTION: GAME 0x0052bb40
unsigned *RHUnk0052bbb0::FUN_0052bb40(unsigned index)
{
    bool &dirty = RHDialogueField<bool>(this, 0x11c + (index & 1));
    if (dirty == true)
    {
        dirty = false;
        return MakeEvent(index);
    }
    return 0;
}

// FUNCTION: GAME 0x0052bbb0
void RHUnk0052bbb0::FUN_0052bbb0()
{
    RHDialogueField<bool>(this, 0x11c) = true;
    RHDialogueField<bool>(this, 0x11d) = true;
    RHDialogueField<int>(this, 0xc0) = -1;
    RHDialogueField<int>(this, 0xc4) = -1;
}

// FUNCTION: GAME 0x0052bbd0
unsigned *RHUnk0052bbb0::FUN_0052bbd0(unsigned index)
{
    return MakeEvent(index);
}

// FUNCTION: GAME 0x0052bc20
void RHUnk0052b860::FUN_0052bc20()
{
    ((RHUnk005cbb80 *)((char *)this + 0x80))->FUN_005cbc80(V24());
}

class RHGameWidgetRendererCalls
{
public:
    bool FUN_0060d890(const SBGeoPoint2D &point);
};

#include "SBUIKeyboardCalls.h"

struct RHDialogueWidgetInput
{
    SBGeoPoint2D m_point;
    unsigned short m_08;
    unsigned char m_flags;
    unsigned char m_0b;
    RHGameWidgetInputCalls *m_shortcuts;
};

struct RHDialogueWidgetEvent
{
    int m_type;
    void *m_widget;
    unsigned m_value;
    void *m_next;
};

class RHDialogueButtonView
{
public:
    RHDialogueWidgetEvent *Raise(int type)
    {
        m_event.m_next = 0;
        m_event.m_value = 0;
        m_event.m_widget = this;
        RHDialogueWidgetEvent *event = &m_event;
        event->m_type = type;
        return event;
    }
    RHDialogueWidgetEvent *Toggle()
    {
        if (m_event.m_type != 2 && m_event.m_type != 7)
            return Raise(2);
        return Raise(7);
    }
    unsigned char m_00[4];
    bool m_enabled;
    unsigned char m_05[5];
    unsigned short m_shortcut;
    unsigned char m_0c[0x24];
    SBGeoBoundingBox2D m_box;
    unsigned char m_44[8];
    RHDialogueWidgetEvent m_event;
    unsigned char m_5c[0x20];
    int m_state;
    RHGameWidgetRendererCalls m_renderer;
};

// FUNCTION: GAME 0x0052bc40
RHDialogueWidgetEvent *RHUnk0052bd70::FUN_0052bc40(const RHDialogueWidgetInput &input)
{
    RHDialogueButtonView *self = (RHDialogueButtonView *)this;
    if (self->m_enabled)
    {
        SBGeoBoundingBox2D &box = self->m_box;
        if (box.FUN_006083b0(input.m_point) == 1 &&
            self->m_renderer.FUN_0060d890(input.m_point.Unk005fc110(*(SBGeoPoint2D *)&box)) == 1)
        {
            if (!(input.m_flags & 1))
            {
                RHDialogueWidgetEvent *event = &self->m_event;
                self->m_event.m_next = 0;
                self->m_event.m_value = 0;
                self->m_event.m_widget = self;
                event->m_type = 0;
                return event;
            }
        }
        else if (!self->m_shortcut || input.m_shortcuts->FUN_0060e240(self->m_shortcut) != 2)
        {
            self->m_state = 0;
            return 0;
        }
        RHDialogueWidgetEvent *event = &self->m_event;
        if (self->m_event.m_type != 2 && self->m_event.m_type != 7)
        {
            self->m_event.m_next = 0;
            self->m_event.m_value = 0;
            self->m_event.m_widget = self;
            event->m_type = 2;
            return event;
        }
        self->m_event.m_next = 0;
        self->m_event.m_value = 0;
        self->m_event.m_widget = self;
        event->m_type = 7;
        return event;
    }
    return 0;
}

// FUNCTION: GAME 0x0052bd70
unsigned RHUnk0052bd70::FUN_0052bd70()
{
    if (!RHDialogueField<bool>(this, 4))
        return 255;
    return RHDialogueField<unsigned>(this, 0xe4);
}

// FUNCTION: GAME 0x0052bdf0
void *RHDialogueWidgetLifetimeCalls::FUN_0052bdf0(unsigned flags)
{
    FUN_0052be10();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x0052bec0
void *RHDialogueWidgetLifetimeCalls::FUN_0052bec0(unsigned flags)
{
    FUN_0052b890();
    if (flags & 1)
        operator delete(this);
    return this;
}

// VTABLE: GAME 0x00679428
class RHDialogueLifetime0052bf00 : public RHGameWidgetLifetimeBase
{
public:
    ~RHDialogueLifetime0052bf00() {}
    void *FUN_0052bee0(unsigned flags);
    RHPortraitRenderer0060d470 m_renderer;
};

// VTABLE: GAME 0x00679378
class RHDialogueLifetime0052bd90 : public RHDialogueLifetime0052bf00
{
public:
    ~RHDialogueLifetime0052bd90() {}
    void *FUN_0052bf60(unsigned flags);
};

// SYNTHETIC: GAME 0x0052bd90
// ??1RHDialogueLifetime0052bd90@@QAE@XZ

// SYNTHETIC: GAME 0x0052bf00
// ??1RHDialogueLifetime0052bf00@@QAE@XZ

#pragma inline_depth(1)
// FUNCTION: GAME 0x0052bee0
void *RHDialogueLifetime0052bf00::FUN_0052bee0(unsigned flags)
{
    this->~RHDialogueLifetime0052bf00();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x0052bf60
void *RHDialogueLifetime0052bd90::FUN_0052bf60(unsigned flags)
{
    this->~RHDialogueLifetime0052bd90();
    if (flags & 1)
        operator delete(this);
    return this;
}
#pragma inline_depth()

void RHMenuDialogueEmit(RHMenuDialogue *dialogue, RHMenuEvent *event,
                        RHUnk0052bbb0 *text, RHUnk0052bd70 *button,
                        RHUnk0052b860 *renderer)
{
    dialogue->RouteEvent(event);
    dialogue->OnTimer(0, 0, 0);
    dialogue->UpdatePortrait();
    dialogue->FUN_0052a810(0);
    RHMenuDialogue::Display((unsigned long)0);
    RHMenuDialogue::Display((RHSequenceElement *)0);
    RHMenuDialogue::Display(std::vector<unsigned long>());
    RHMenuDialogue::DisplayAll();
    text->FUN_0052bbb0();
    text->FUN_0052b940(std::wstring());
    text->FUN_0052bb40(0);
    text->FUN_0052bbd0(0);
    button->FUN_0052bd70();
    button->FUN_0052b830(0);
    button->FUN_0052b840();
    text->FUN_0052b880();
    renderer->FUN_0052b850();
    button->FUN_0052bc40(*(RHDialogueWidgetInput *)0);
    renderer->FUN_0052b860();
    renderer->FUN_0052bc20();
    RHDialogueWidgetLifetimeCalls *lifetime = (RHDialogueWidgetLifetimeCalls *)button;
    lifetime->FUN_0052bdf0(0);
    lifetime->FUN_0052bec0(0);
    ((RHDialogueLifetime0052bf00 *)button)->FUN_0052bee0(0);
    ((RHDialogueLifetime0052bd90 *)button)->FUN_0052bf60(0);
}
