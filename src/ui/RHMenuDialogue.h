// Declarations shared by RHMenuDialogue.cpp (the decompiled TU) and
// RHMenuDialogue_stubs.cpp (external-symbol stubs).
//
// Only the layout the target instructions actually touch is modelled:
//   - the returned "resource" object has an array of 24-byte elements whose
//     begin/end pointers live at +0xc / +0x10 (target 0x0052b2e0);
//   - the engine singleton pointer lives in the global at 0x006c0a88.

#include "SB.h"
#include <string>
#include <vector>

// A dialogue entry: the indexed stride is 24 bytes on Windows (target
// 0x0052b2e0 does `(end - begin) / 24` and `begin + id * 24`). The internal
// fields are not touched by this function, so the element is modelled as raw
// storage. (The Mac oracle uses a 20-byte stride — the structure differs
// between the two builds; the Windows layout is what matters here.)
struct RHDialogue
{
    unsigned char m_data[24];
};

// The resource object returned by RHEngine::GetDynResources. The oracle does
// not expose a name for it, so it stays provisional.
class RHDialogueSet
{
public:
    unsigned char m_pad0[0xc];
    RHDialogue *m_pDialoguesBegin; // [this+0xc]
    RHDialogue *m_pDialoguesEnd;   // [this+0x10]
};

// Oracle-backed target of the call at 0x0052b2e0: 0x004e35a0 is
// RHEngine::GetDynResources(unsigned long) (symbols/mac-RH.txt line 2110 and
// symbols/zeta-robin.txt `GetDynResources__8RHEngineUl`; the Mac
// RHMenuDialogue::GetDialogue calls the same method with the same 0 argument).
class RHEngine
{
public:
    RHDialogueSet *GetDynResources(unsigned long resources); // 0x004e35a0
};

// The engine singleton pointer read from the global at 0x006c0a88.
extern RHEngine *g_pEngine;

class RHMenuDialogue
{
public:
    RHMenuDialogue(class RHMenuScreenView *, unsigned long);
    ~RHMenuDialogue();
    void *FUN_0052a810(unsigned flags);
    bool Create();
    static void Display(const std::vector<unsigned long> &);
    static void Display(unsigned long);
    static void Display(class RHSequenceElement *);
    static void DisplayAll();
    static void DisplaySingleDialogue(class RHMenuScreenView *, unsigned long);
    void RouteEvent(struct RHMenuEvent *event);
    bool HandleEvent(struct RHMenuEvent *event);
    bool OnSkip(int message, void *widget, void *data);
    bool OnTimer(int message, void *widget, void *data);
    bool GetNextSentence(std::wstring &text, std::string &sound, unsigned long &portrait);
    void UpdateDialogue();
    void UpdatePortrait();
    // Windows codegen calls this WITHOUT a `this` (no `mov ecx, this` at the
    // ctor call site, 0x0052a7b0), so on this build it is a static member.
    static RHDialogue *GetDialogue(unsigned long id);
    unsigned char m_bytes[0x548];
    RHDialogue *m_dialogue;
    unsigned m_sentence;
    unsigned char m_tail[0xc];
};

class RHDialogueWidgetLifetimeCalls
{
public:
    void FUN_0052b890();
    void FUN_0052bd90();
    void FUN_0052be10();
    void FUN_0052bf00();
    void *FUN_0052bdf0(unsigned);
    void *FUN_0052bec0(unsigned);
    void *FUN_0052bee0(unsigned);
    void *FUN_0052bf60(unsigned);
};
