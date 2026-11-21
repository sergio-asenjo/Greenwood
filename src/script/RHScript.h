#ifndef RHSCRIPT_H
#define RHSCRIPT_H
#include "RHSectorActorList.h"

// RHScript — declarations for RHScript.cpp (decompiled TU).
//
// BINDING (0x00570a90 -> RHScript::IsActorCharacter(void*)):
//   - TU:        rhscript.cpp (embedded __FILE__ string 0x006b2388,
//                referenced by this function).
//   - Class:     RHScript (symbols/oracle-correlation.tsv:
//                rhscript -> class RHScript, 294 methods).
//   - Signature: RHScript::IsActorCharacter(void*) (symbols/mac-RH.txt:3618;
//                zeta-robin.txt:3957 IsActorCharacter__8RHScriptPv).
//   - Signals:
//       * the assert string references the method by name:
//         "ACHTUNG : Script error (\"IsActorCharacter\") : invalid actor !"
//         (string 0x006b23a4) — a Windows-side per-function signal binding this
//         address to that method;
//       * the body never uses ecx as `this` (arg is `[esp+4]`), and the exits
//         are a plain `ret`, so Windows emits it as a static member;
//       * shape: `if (actor == 0) return false;` then the validity helper
//         0x005709c0(actor); on failure SBAssert line 493 (0x1ed) with the
//         string above; on success `return (actor->flags & 3) == 0;` read as a
//         full dword at +0x4 (`mov eax,[esi+4]; and al,3`).
//
// The `// STRING:` markers pin the literals to their original Game.exe
// addresses: the original is a fixed-base EXE, so its absolute string pointers
// carry no relocation records and reccmp cannot discover them by scanning.

#include "SB.h"
#include "Decomp.h"
#include <iterator>

// SIZE 0x2c
class RHScriptStimulusValue
{
public:
    RHScriptStimulusValue() : m_24(0), m_28(0) {}
    ~RHScriptStimulusValue() {}
    undefined m_00[0x1c]; // 0x00
    unsigned m_type; // 0x1c
    unsigned m_20; // 0x20
    void *m_24; // 0x24
    char m_28; // 0x28
};

// SIZE 0x04
class RHScriptStimulusDispatch
{
public:
    virtual void v00() = 0; // vtable+0x00
    virtual void v01() = 0; // vtable+0x04
    virtual void v02() = 0; // vtable+0x08
    virtual void v03() = 0; // vtable+0x0c
    virtual void v04() = 0; // vtable+0x10
    virtual void v05() = 0; // vtable+0x14
    virtual void v06() = 0; // vtable+0x18
    virtual void v07() = 0; // vtable+0x1c
    virtual void v08() = 0; // vtable+0x20
    virtual void v09(RHScriptStimulusValue &value) = 0; // vtable+0x24
};

struct RHUnk00571160Position;
class RHUnk005fc3b0;
class SBGeoPoint2D;

#include "RHArtificialIntelligenceCore.h"

#include "RHUnk0046bd20.h"

class RHSoundSource;
class SBGeoPoint2D;
struct RHSoundSettings;
struct RHSoundChannelSettings;

#include "RHSoundCore.h"


// SIZE 0x0c
union RHScriptPropertyValue
{
    bool m_bool; // 0x00
    int m_int; // 0x00
    float m_float; // 0x00
    struct { float x; float y; } m_point; // 0x00
    undefined m_data[0x0c]; // 0x00
};

// SIZE 0x10
struct RHScriptPropertyPair
{
    int m_key; // 0x00
    RHScriptPropertyValue m_value; // 0x04
    RHScriptPropertyPair(int key, const RHScriptPropertyValue &value) : m_key(key), m_value(value) {}
};

// SIZE 0x08
struct RHScriptPropertyInsertResult
{
    void *m_node; // 0x00
    bool m_inserted; // 0x04
    undefined m_padding[3]; // 0x05
};

// Actor sub-object model used by RHScript::UnBlip (0x00570e70): the target
// loads the vtable pointer from actor+0, sets ecx = actor and dispatches the
// virtual at vtable byte offset +0x34 (`mov eax,[esi]; mov ecx,esi;
// call dword ptr [eax+0x34]`). Slot 0x34 is index 13, so the preceding slots
// exist only to place it at that offset. RHScript::IsActorDead (0x00579a70) and
// RHScript::IsActorHS (0x00579b60) dispatch the same object's virtual at byte
// offset +0x48 (slot index 18), so the table is extended through v18.
// RHScript::IsActorRider (0x0057ad90) dispatches the same object's virtual at
// byte offset +0xf4 (slot index 61, `call dword ptr [edx+0xf4]`), so the table
// is extended through v61 (bool).
class RHUnk00570e70Vtbl
{
public:
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04();
    virtual void v05();
    virtual void v06();
    virtual void v07();
    virtual void v08();
    virtual void v09();
    virtual void v10();
    virtual void v11();
    virtual void v12();
    virtual void v13();
    virtual void v14();
    virtual void v15();
    virtual void v16();
    virtual void v17(int posture);
    virtual bool v18();
    virtual void v19();
    virtual void v20();
    virtual void v21();
    virtual void v22();
    virtual void v23();
    virtual void v24();
    virtual void v25();
    virtual void v26();
    virtual void v27();
    virtual void v28();
    virtual void v29();
    virtual void v30();
    virtual void v31();
    virtual void v32();
    virtual void v33();
    virtual void v34();
    virtual void v35();
    virtual void v36();
    virtual void v37();
    virtual void v38();
    virtual void v39();
    virtual void v40();
    virtual void v41();
    virtual void v42();
    virtual void v43();
    virtual void v44();
    virtual void v45();
    virtual void v46();
    virtual void v47();
    virtual void v48();
    virtual void v49();
    virtual void v50();
    virtual short v51();
    virtual void v52();
    virtual void v53(int value, int mode, bool flag);
    virtual void v54();
    virtual void v55(int value, int mode, bool flag);
    virtual void v56();
    virtual unsigned short v57(int property);
    virtual void v58();
    virtual void v59(int property, int value);
    virtual void v60();
    virtual bool v61();
    virtual bool IsVIP() const;
    virtual void v63();
    virtual void v64();
    virtual void v65();
    virtual void v66();
    virtual void v67();
    virtual void v68();
    virtual void v69();
    virtual void v70();
    virtual void v71();
    virtual void v72();
    virtual void v73();
    virtual void v74();
    virtual void v75();
    virtual int v76();
    virtual void v77();
    virtual void v78();
    virtual void v79();
    virtual void v80();
    virtual void v81();
    virtual void v82();
    virtual void v83();
    virtual void v84();
    virtual void v85();
    virtual void v86();
    virtual void v87();
    virtual void v88();
    virtual void v89();
    virtual bool v90();
    virtual void v91();
    virtual void v92(int first, int second, int index, int value);
};

struct RHUnk00570e70Actor
{
    void *m_vtbl;         // +0
    unsigned int m_flags; // +4
    char m_blip;          // +8
};

class RHSequenceElement;

// Callee 0x00585500 — __thiscall, one stack arg, plain `ret 4`. PROVISIONAL
// identity: named by address only. It has no string/__FILE__/tag of its own, so
// no Windows-side signal binds a method name. Its shape (`this` is the element,
// the arg is a sequence: sets element->[0x54]=arg, links a new 0xc-byte node
// into arg->[0xc], increments arg->[0x10], sets arg->[0x18]=1, allocates via
// 0x006428b5) matches RHSequenceElement::AppendToSequence(RHSequence*) in the
// Mac oracle, but a cross-binary signature/position match is not accepted as
// evidence (docs/05-naming.md). Modelled as a provisional class method so the
// caller emits `mov ecx,element; push global; call`. Defined once in
// RHScript_stubs.cpp.

// Callee 0x00452030 — __thiscall, one stack arg, plain `ret 4`: a 6-byte index
// getter reading the dword at [this + index*4 + 0x94]
// (`mov eax,[esp+4]; mov eax,[ecx+eax*4+0x94]; ret 4`). PROVISIONAL: named by
// address only. It has no Windows-side __FILE__/tag/string of its own (checked:
// no `push <file string>` in its body, and it is not listed in
// symbols/functions-by-file.tsv); tools/attribute.py gives it a *weak*
// rhscript.cpp TU from 3 agreeing / 22 other callers, which is a hint, not a
// name. Modelled as a provisional class method so the caller emits
// `mov ecx,[g]; push index; call`. Defined once in RHScript_stubs.cpp.
#include "RHCampaignValueCalls.h"

// Callee 0x004ba7a0 — __thiscall, one stack arg, plain `ret 4`: a 0x32-byte
// setter that stores the arg to [this+0x164], and when it equals 3 forwards to
// 0x005b76e0 with ([this+0x50]+0xd8, 0xc0) before tail-calling 0x004ba7e0,
// which normalizes the WORD at [this+0x8c] from [this+0x164]. PROVISIONAL:
// named by address only. It has no Windows-side __FILE__/tag/string of its own
// (checked: no `push <file string>` in its body, and it is not listed in
// symbols/functions-by-file.tsv); tools/attribute.py gives it a *mixed*
// rhelementscroll.cpp TU. The Mac/Zeta oracles expose
// RHElementScroll::SetStatus(RHElementScroll::Status) at the matching
// [this+0x164]/[this+0x8c] shape (and RHElementScroll::GetStatus() const reads
// the same +0x164), but a cross-binary signature/offset match is not accepted
// as evidence (docs/05-naming.md). Modelled as a provisional class method so
// the caller emits `mov ecx,element; push status; call`. Defined once in
// RHScript_stubs.cpp.
class RHUnk004ba7a0
{
public:
    void Set(int status);
};

// Singleton object pointer used by the campaign-value methods (original
// 0x006c07fc). SetCustomCampaignValue (0x005795c0), Fun_00579690 (0x00579690)
// and this TU's GetCustomCampaignValue all load it and dispatch through
// RHUnk00452030::Get. PROVISIONAL name: the address is otherwise unclaimed; no
// Windows-side name exists. // GLOBAL: marker sits on its definition in
// RHScript.cpp.
extern RHUnk00452030 *g_unk0x6c07fc;

#include "RHScriptCore.h"

// Callee 0x0041b0e0 — __thiscall, no stack args, plain `ret`: the sub-object
// reached from a chief at `chief+0x49c` after the vbase-style adjustment
// (`mov ecx,[chief+0x49c]; mov edx,[ecx+4]; lea ecx,[edx+chief+0x49c]`).
// PROVISIONAL: named by address only. Its only caller is
// RHScript::RemoveAllSubordinates, and it has no Windows-side __FILE__/tag/string
// of its own (checked: no `push <file string>` in its body, and it is not listed
// in symbols/functions-by-file.tsv). Defined in RHScript.cpp.
class RHUnk0041b0e0
{
public:
    void Clear();
};

// Callee 0x0044cae0 — __thiscall, no stack args, plain `ret`: the sub-object at
// `soldier + 0x6e8` (called from RHScript::SwitchToAlertPath, `lea ecx,[esi+0x6e8];
// call 0x44cae0`). PROVISIONAL: named by address only. It has no Windows-side
// __FILE__/tag/string of its own (checked: no `push <file string>` in its body,
// and it is not listed in symbols/functions-by-file.tsv); its body reads a
// vbase-style offset at [this]+4, gates on WORD [this+vbase+0xa] != 0xffff, sets
// [this+0x22f]=1, calls 0x550f60 on the list at +0x4cc, and dispatches a virtual
// `mov edx,[ecx]; call [edx]` when [this+vbase+0xc]==1. tools/attribute.py gives
// it a *probable* rhscript.cpp TU from its single caller, which is a hint, not a
// name. Defined once in RHScript_stubs.cpp.
class RHUnk0044cae0
{
public:
    void Switch();
};

// Callee 0x004b9f30 — __thiscall, no stack args, plain `ret`: a 7-byte getter
// reading the dword at [this+0x164] (`mov eax,[ecx+0x164]; ret`). Reached only
// via a tail `jmp` from RHScript::GetScrollStatus (the element's status), and
// also called from 0x0047ac90. PROVISIONAL: named by address only. It has no
// Windows-side __FILE__/tag/string of its own (checked: no `push <file string>`
// in its body, and it is not listed in symbols/functions-by-file.tsv), so no
// Windows-side signal binds a method name. The Mac oracle exposes
// RHElementScroll::GetStatus() const, but a cross-binary signature/offset match
// is not accepted as evidence (docs/05-naming.md). Modelled as a class method so
// the caller emits the element in ecx and a direct tail jump. Defined once in
// RHScript_stubs.cpp.
class RHUnk004b9f30
{
public:
    int Get();
};

// Callee 0x005709c0 — cdecl(this == none, void*): takes an actor pointer,
// stores it to the global 0x006c0f4c, linearly searches the global pointer
// array at 0x006c0f34/0x006c0f38 for it, records the index at 0x006c0f48 and
// cursor state at 0x006c0f40/0x006c0f44/0x006c0f45, then returns whether the
// pointer was found. PROVISIONAL: named by address only — it has no
// Windows-side __FILE__/tag/string, and no function-pointer literal anywhere in
// Game.exe references it (checked), so no Windows-side signal binds a method
// name. The Mac/Zeta oracles expose RHScript::ActorExists(void*) and
// RHScript::GetActorIndex(void*) as candidates, but a cross-binary
// signature/position match is not accepted as evidence (docs/05-naming.md).
// Defined once in RHScript_stubs.cpp.
bool RHUnk005709c0(void *actor);

// The 4-byte global that holds the "current sequence" pointer (original
// 0x006c0f78). RHScript::AddToSequence passes it to the 0x00585500 callee when
// non-null, else asserts. PROVISIONAL name: the address is otherwise unclaimed;
// no Windows-side name exists. // GLOBAL: marker sits on its definition in
// RHScript.cpp.
extern void *g_unk0x6c0f78;

#include "RHSpriteLastFrameCalls.h"

#include "RHActorCancelCalls.h"

#include "RHUnk00571160Position.h"

void RHUnk0048ce80(int noise, RHUnk00571160Position *position);

class SBGeoVector2D;
#include "SBGeoPoint2D.h"

SBGeoPoint2D RHUnk005758d0(const SBGeoPoint2D &point);

#include "RHSequenceConstructionCalls.h"

#include "RHScriptListCore.h"

class RHScriptSequenceVtable
{
public:
    virtual ~RHScriptSequenceVtable();
};

#include "RHScriptLocation.h"

class RHOrder;
class RHUnkIter
{
public:
    void *m_p;
    RHUnkIter(void *value) : m_p(value) {}
};

class RHUnkList
{
public:
    RHUnkIter insert(RHUnkIter position, RHOrder *const &value);
    char m_pad0[4];
    void *m_4;
    int m_8;
    char m_pad12[4];
    char m_flag10;
};

class RHUnk0047ca50
{
public:
    void Unk();
};

#include "RHEngineWidenedCalls.h"

class RHUnk00418b80
{
public:
    void Unk(bool value);
};

#include "RHActorPositionCalls.h"

struct RHBonusProjection;
class RHBonusInfoBase
{
public:
    void FUN_0055f290();
    void FUN_0055fa20(RHBonusProjection *projection);
};

class RHBonusInfo
{
public:
    void FUN_005bd560(void *value, bool flag);
};

struct RHScriptPositionFields
{
    char padding[0xde];
    short layer;
    void *area;
};

struct RHScriptActorPositionFields
{
    char padding[0x50];
    RHScriptPositionFields *position;
};


#include "RHCampaignPropertyCalls.h"

#include "RHUnk00419a40.h"

#include "RHSequenceGenericConstruction.h"

#if !defined(SBGEO_VECTOR2D_VIEW) && !defined(SBGEOVECTOR2D_H)
#include "SBGeoVector2D.h"
#endif

#define SBGEO_VECTOR2D_VIEW
#include "RHUnk005fc3b0.h"

class RHSeqList
{
public:
    int allocator;
    RHScriptNode *head;
    int count;
    RHScriptNode *cursor;
    __forceinline void GoTo(int index) { ((RHSectorActorList *)this)->Unk005c8e40(index); }
    static void CopyData(RHSequenceElement **destination, RHSequenceElement *const *source);
};

#include "RHSequenceGenericCalls.h"

#include "RHEngineAccessors.h"



class RHUnk0048a970
{
public:
    void Unk(int index);
};

#include "RHAIStateCalls.h"

#include "RHMalignityPosition.h"

class RHScriptAIStateCalls
{
public:
    void FUN_0043a220(RHMalignityPosition position, int first, int second, int third);
};

// SIZE 0x04
class RHUnk004169c0
{
public:
    void Unk(int state, int value);
    virtual void v00(); // vtable+0x00
    virtual void v01(); // vtable+0x04
    virtual void v02(); // vtable+0x08
    virtual void v03(); // vtable+0x0c
    virtual void v04(int state, int value); // vtable+0x10
};

#include "RHSoundSourceManagerCore.h"

#include "RHSequenceMovementConstruction.h"

#include "RHMessenger.h"
RHMessenger *RHUnk00546050();
RHMessenger *__stdcall RHUnk00546050(RHUnk5490f0 *message);

#include "RHSequenceInteractionAction.h"

void RHUnk00574690(void *actor, RHUnk00571160Position *position, void *location);




#if !defined(RHSPRITECORE_H) && !defined(RHELEMENTACTORANIMAL_H)
class RHUnk005b5e00
{
public:
    void *Unk();
    SBGeoPoint2D *Unk005bdd30(short index);
    void *FUN_005b5de0();
};
#endif

enum RHanimalStimulusType
{
};

class RHElementActorAnimal
{
public:
    void Think(RHanimalStimulusType stimulus);
    void ThisIsYourNewHome();
};

class RHScriptBatchCalls
{
public:
    void Unk00486f50(void *target, bool flag);
    void Unk00464630();
    void Unk0046bd10(int state);
    bool Unk004188f0(void *path);
    bool Unk00418a80(RHUnk00571160Position position, int direction);
    void Unk00418bc0();
    bool Unk004e3e30(int index);
    void Unk004e3e00(int index, int value);
    int Unk004e3e20(int index);
    void Unk0046bcf0(int state, int value);
    bool Unk00489e80(void *target);
    void Unk0048ec00(void *scroll);
    void Unk004d9330(void *actor, bool flag);
    void Unk0057ff70(float height);
    void Unk004520e0(int index, int value);
    void Unk004e3220(int value);
    void Unk00450be0(int property, int value);
    int Unk004ec910(void *location, float radius, float strength, int value);
    RHScriptBatchCalls *Unk004e3cc0();
    void Unk0054cfa0(void *description);
    void Unk00485200(int index, int amount);
    void Unk00485220(int index, int value);
    unsigned int Unk004baea0();
    void Unk0046b9e0();
    bool Unk0049d560(int action);
    bool Unk00456ce0(void *type);
    void Unk00419fd0(int value, int duration);
    float FUN_00489680(void *target);
    void FUN_00456d20();
    RHScriptBatchCalls *FUN_005209b0();
    void FUN_00520a70();
    void FUN_00549090();
};

#include "RHUnk00613e90.h"

#include "RHSequenceTimedCalls.h"

class RHElementActor;
#include "RHSectorScript.h"

struct RHScriptZoneAccess
{
    static RHScriptNode *&Next(RHScriptNode *node) { return node->next; }
    static void *&Value(RHScriptNode *node) { return node->data; }
};

struct RHScriptZoneIterator
{
    RHScriptNode *node;
    RHScriptZoneIterator(RHScriptNode *value) : node(value) {}
    RHScriptZoneIterator operator++(int)
    {
        RHScriptZoneIterator previous = *this;
        node = RHScriptZoneAccess::Next(node);
        return previous;
    }
    void *&operator*() const { return RHScriptZoneAccess::Value(node); }
};

struct RHScriptZoneList
{
    int allocator;
    RHScriptNode *head;
    int count;
    RHScriptZoneIterator cursor;
    bool valid;
    char padding[3];
    int index;
    bool searchValid;
    char searchPadding[3];
    int searchIndex;
    void *searchValue;
    __forceinline void GoTo(int index) { ((RHProfileListCursor *)this)->GoTo(index); }
    int Find(void *actor)
    {
        int size = count;
        searchValue = actor;
        searchValid = true;
        cursor = RHScriptZoneIterator(RHScriptZoneAccess::Next(head));
        int current = 0;
        for (; current < size; ++current, cursor++)
        {
            if (*cursor == searchValue)
                break;
        }
        if (current < size)
        {
            searchIndex = current;
            valid = false;
            index = current;
        }
        else
        {
            valid = true;
            searchIndex = -1;
        }
        return searchIndex;
    }
};

class RHUnk005883a0
{
public:
    RHUnk005883a0(unsigned short level, int command, void *actor, int style, const SBGeoPoint2D &destination, int first, int second, int flags);
    ~RHUnk005883a0();
    char data[0x9c];
};

class RHScriptRecordWorld
{
public:
    void Unk004fc8f0(SBGeoPoint2D &first, SBGeoPoint2D &second, const SBGeoPoint2D *destination, unsigned short direction);
    RHUnk00613e90 Unk004fbdd0(const RHUnk00571160Position &position);
};

class RHScriptPositionList
{
public:
    RHScriptNode *Unk004242b0(RHScriptNode *next, RHScriptNode *previous);
    static void Unk00588190(RHUnk00571160Position *destination, const RHUnk00571160Position *source);
};

class RHUnk00549250 : public RHUnk5490f0
{
public:
    RHUnk00549250(int command, void *actor);
    RHUnk00549250(int command, void *actor, int action);
    ~RHUnk00549250();
    char data[4];
};

#include "SBDrawManagerCore.h"

extern SBDrawManager *g_unk0x6c11d0;

class RHUnk0046bcb0Dispatch
{
public:
    virtual void v00();
    virtual void v01();
    virtual void v02();
    virtual void v03();
    virtual void v04(int value);
};

struct RHScriptActionCursor
{
    RHScriptNode *node;
    RHScriptActionCursor operator++(int);
};

#include "RHSectorActorIterator.h"

class RHScriptFXArray
{
public:
    int grow;
    void **first;
    void **last;
    void **end;
    void **cursor;
    bool dirty;
    void **Unk004fe420(void **first, void **last, void **destination);
    void Unk004fe450(void **destination, unsigned int count, void *const &value);
    void Unk005008e0(void **first, void **last);
    unsigned int Size() { return first == 0 ? 0 : last - first; }
};

#endif
