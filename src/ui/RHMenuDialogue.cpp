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
