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

class RHArtificialIntelligence
{
public:
    void Unk00410600();
};

class RHUnk0046bd20
{
public:
    int FUN_0046bd20();
};

class RHSound
{
public:
    void PlayJingle(int jingle);
};

class RHScriptSoundStateCalls
{
public:
    void FUN_005a7ef0(int state);
    void FUN_005a7fb0(int state);
};

class RHUnk004a5230
{
public:
    void FUN_004a5230(bool value, bool flag);
};

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

class RHScriptPropertyMap
{
public:
    RHScriptPropertyInsertResult FUN_005873a0(const RHScriptPropertyPair &value);
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
    virtual bool v62();
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
    virtual void v90();
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
class RHUnk00585500
{
public:
    void Unk(void *sequence);
};

// Callee 0x00452030 — __thiscall, one stack arg, plain `ret 4`: a 6-byte index
// getter reading the dword at [this + index*4 + 0x94]
// (`mov eax,[esp+4]; mov eax,[ecx+eax*4+0x94]; ret 4`). PROVISIONAL: named by
// address only. It has no Windows-side __FILE__/tag/string of its own (checked:
// no `push <file string>` in its body, and it is not listed in
// symbols/functions-by-file.tsv); tools/attribute.py gives it a *weak*
// rhscript.cpp TU from 3 agreeing / 22 other callers, which is a hint, not a
// name. Modelled as a provisional class method so the caller emits
// `mov ecx,[g]; push index; call`. Defined once in RHScript_stubs.cpp.
class RHUnk00452030
{
public:
    int Get(int index);
};

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

class RHScript
{
public:
    static bool IsActorCharacter(void *actor);
    static bool IsActorObject(void *actor);
    static bool IsActorCart(void *actor);
    static bool IsActorPC(void *actor);
    static bool IsActorAnimal(void *actor);
    static bool IsActorNPC(void *actor);
    static bool IsActorSoldier(void *actor);
    static bool IsActorCivilian(void *actor);
    static char IsAnimationActive(void *actor);
    static char IsActorActive(void *actor);
    static bool SetAnimationState(void *actor, bool state);
    static bool FUN_00570dd0(void *actor);
    static bool UnBlip(void *actor);
    static bool IsUnblipped(void *actor);
    static bool Start();
    static bool Thanx();
    static int Then();
    static void MakeNoise(void *location, int noise);
    static bool SetZoomLevel(float zoom);
    static bool ScrollCameraTo(void *location);
    static bool ScrollCameraSlowlyTo(void *location, float speed);
    static bool JumpCameraTo(void *location);
    static void *GetLocationScript(int index);
    static int GetMovementStyle(void *actor);
    static void *GetActorScript(int index);
    static void *GetActorForBeamMe(unsigned int index);
    static void *GetDoorScript(int index);
    static void *GetPatchScript(int index);
    static void *GetActorLocation(void *actor);
    static bool SetActorLocation(void *actor, void *location);
    static int GetActorDirection(void *actor);
    static bool SetActorDirection(void *actor, int direction);
    static bool StopActor(void *actor);
    static int GetDistance(void *first, void *second);
    static void *ComputeLocationBetween(void *first, void *second, float ratio);
    static bool IsInside(void *actor, void *sector);
    static void *GetAnyActorInsideBuilding(void *sector);
    static bool AreAllEnemiesInsideHS(void *sector);
    static int GetPersistentProperty(void *actor, int property);
    static bool SetPersistentProperty(void *actor, int property, int value);
    static void ConfiscateMoney(void *actor);
    static bool RecordScrollCameraTo(void *location);
    static bool RecordJumpCameraTo(void *location);
    static bool RecordMoveCameraTo(void *location, int speed);
    static bool RecordSetZoom(float zoom);
    static bool RecordDisplayMap(bool display);
    static bool RecordSpeak(void *actor, int index);
    static void ForbidNPCRemark(void *actor, int index, bool forbidden);
    static bool RecordSpeakPC(void *actor, int index, int variant);
    static bool RecordPlayAnim(void *actor, int animation);
    static bool RecordPlayAnimLoop(void *actor, int animation);
    static bool RecordPlayAnimFreeze(void *actor, int animation);
    static bool RecordAction(void *actor, int action, int argument);
    static bool RecordSeekActorMessage(void *actor, void *target, int style, float distance, void *recipient, int event);
    static bool RecordSeekActorMessageWithArguments(void *actor, void *target, int style, float distance, void *recipient, int event, int first, int second);
    static bool RecordMove(void *actor, void *location, int style);
    static bool RecordMoveNear(void *actor, void *location, int style, int distance);
    static bool RecordMoveIntoBuilding(void *actor, void *location, int style);
    static bool RecordTakeCorpse(void *actor, void *corpse, int style);
    static bool RecordLeaveCorpse(void *actor);
    static bool RecordTurnTo(void *actor, void *location);
    static bool RecordReplaceAnim(void *actor, int oldAnimation, int newAnimation);
    static bool RecordRestoreAnim(void *actor, int animation);
    static bool RecordLockAI(void *actor);
    static bool RecordUnlockAI(void *actor);
    static bool RecordUnBlip(void *actor);
    static bool RecordLockUser();
    static bool RecordUnLockUser();
    static void *GetSoundSourceScript(int index);
    static bool Deactivate(void *actor);
    static bool Activate(void *actor);
    static bool SetActionAvailable(void *actor, int action, bool available);
    static bool IsActionAvailable(void *actor, int action);
    static bool SetAIAlertStatus(void *actor, int state);
    static int GetAIAlertStatus(void *actor);
    static bool SetAIState(void *actor, int state);
    static int GetAIState(void *actor);
    static bool SetAIAttitude(void *actor, int attitude);
    static int GetAIAttitude(void *actor);
    static bool SetAILevel(void *actor, int first, int second);
    static void StareActor(void *actor, void *target, bool flag);
    static void StareLocation(void *actor, void *location, bool flag);
    static int GetActorPosture(void *actor);
    static void SetActorPosture(void *actor, int posture);
    static int GetActorActionState(void *actor);
    static void SetActorActionState(void *actor, int state);
    static void Freeze(void *actor, bool frozen);
    static void AssignPath(void *actor, void *path);
    static void AssignPost(void *actor, void *location, int direction);
    static void LockAI(void *actor, bool flag);
    static void UnlockAI(void *actor);
    static void ForceBattleDecision(void *actor, int decision);
    static void SetGlobal(int index, int value);
    static int GetGlobal(int index);
    static bool CleanFromHisBuildingBeforeTeleport(void *actor);
    static bool CleanFromScriptZoneBeforeTeleport(void *actor, void *zone);
    static bool AddToScriptZoneAfterTeleport(void *actor, void *zone);
    static bool InflictPain(void *actor, int amount, bool flag);
    static bool RecordEnterGame(void *actor, void *location, int direction, int style);
    static bool RecordLeaveGame(void *actor, void *location, int direction, int style);
    static bool RecordActionAvailable(void *actor, int action, bool available);
    static bool RecordCharacterAvailable(void *actor, bool available);
    static bool RecordLockCameraOn(void *actor);
    static int GetCurrentAction(void *actor);
    static void SetPathWalkingStyle(void *actor, int style);
    static bool Sees(void *actor, void *target);
    static void PutActorInBulding(void *actor, void *building);
    static void AttachScrollToNPC(void *actor, void *scroll);
    static void EnableViewCone(void *actor);
    static bool Select(int code);
    static void ActivateDoorMouseSector(bool active, void *door);
    static void CustomizeMinimapDisplay(void *actor, int code);
    static void DefineFlatTrajectoryZone(void *sector, int height);
    static void RecordSendMessage(void *actor, int message);
    static void SendMessage(void *actor, int message);
    static void RecordSendMessageWithArguments(void *actor, int message, int first, int second);
    static void SendMessageWithArguments(void *actor, int message, int first, int second);
    static void SetCompanyNumber(void *actor, short number);
    static void SetAlwaysAttentive(void *actor, bool attentive);
    static void DeclareAsCombatTrainer(void *actor);
    static void AddPCToMissionTeam(void *actor);
    static void RemovePCFromMissionTeam(void *actor);
    static int GetNumberOfBeamMes();
    static int GetCustomCampaignValue(int index);
    static void SetCustomCampaignValue(int index, int value);
    static int GetCustomNPCValue(void *actor, int index);
    static void SetCustomNPCValue(void *actor, int index, int value);
    static void WinBlazon(void *blazon);
    static void LoseBlazon(void *blazon);
    static bool IsBlazonWon(void *blazon);
    static int GetSoundSourceIndex(void *source);
    static void *GetActorInSector(void *sector, int index);
    static bool HasPCAction(void *actor, int action);
    static bool HasAnyPCAction(int action);
    static bool HasAnyActivePCAction(int action);
    static bool HasAnyPCActionWhoIsInThisLevelOrCouldMaybeComeFromSherwood(int action);
    static void SetNPCEmoticon(void *actor, int emoticon, int duration);
    static bool IsPCSelected(void *actor);
    static void AddAsSubordinate(void *chief, void *subordinate);
    static bool HasAnyActionSelected(void *actor);
    static void LinkTargetToFX(void *target, void *fx);
    static void *GetSelectedPC(int index);
    static int GetPCType(void *actor);
    static int AddRepulsivePoint(void *location, float radius, float strength, int value);
    static void AddPCToGang(void *actor);
    static bool IsBonusItemPickedUp(void *actor);
    static int GetRansomMoney();
    static void SetRansomMoney(int value);
    static void SetExperiences(void *actor, int first, int second);
    static void TransformHandleTargetToTakeTarget(void *actor);
    static void MakePCCrouched(void *actor);
    static void SelectActorPC(void *actor, bool selected);
    static void SetInvisible(void *actor, bool invisible);
    static char IsInvisible(void *actor);

    // Display-flags byte accessors at object +0x8c..+0x8f. All are static-style
    // (no `this`: the object arrives as the first stack arg, exits are a plain
    // `ret`), like the rest of this TU's helpers. Identity is UNPROVEN: these
    // functions carry no Windows-side signal — no __FILE__/assert string, no
    // string literal, no xref (they are reached only through the script VM's
    // registration table, which does not hold literal function pointers), and
    // symbols/functions-by-file.tsv does not list them. tools/attribute.py does
    // not cover them either. The Mac oracle exposes RHScript::GetOutlineDisplay()
    // and RHScript::SetOutlineDisplay(bool) with the matching access shape, but a
    // cross-binary signature/offset match is NOT evidence (docs/05-naming.md), so
    // the methods keep neutral `RHUnk<addr>` names. The offset -> accessor mapping
    // is exact and recorded per definition in RHScript.cpp.
    static char RHUnk579810(void *object);
    static char RHUnk579820(void *object);
    static char RHUnk579830(void *object);
    static char RHUnk579840(void *object);
    static void RHUnk579850(void *object, bool value);
    static void RHUnk579870(void *object, bool value);
    static void RHUnk579880(void *object, bool value);
    static void RHUnk5798a0(void *object, bool value);

    static int GetScrollStatus(void *element);
    static void SetScrollStatus(void *element, int status);
    static int GetSoldierRank(void *actor);
    static bool IsActorDead(void *actor);
    static char IsActorKO(void *actor);
    static bool IsActorTied(void *actor);
    static bool IsActorHS(void *actor);
    static bool AddToSequence(RHSequenceElement *element, const char *where);
    static int GetNumberOfActorsInSector(void *sector);
    static void RemoveAllSubordinates(void *chief);
    static void SwitchToAlertPath(void *soldier);
    static bool IsActorRider(void *actor);

    void Emit();
};

// Callee 0x0041b0e0 — __thiscall, no stack args, plain `ret`: the sub-object
// reached from a chief at `chief+0x49c` after the vbase-style adjustment
// (`mov ecx,[chief+0x49c]; mov edx,[ecx+4]; lea ecx,[edx+chief+0x49c]`).
// PROVISIONAL: named by address only. Its only caller is
// RHScript::RemoveAllSubordinates, and it has no Windows-side __FILE__/tag/string
// of its own (checked: no `push <file string>` in its body, and it is not listed
// in symbols/functions-by-file.tsv). Its body walks list/count fields at
// [this+0x2fc..+0x304] and [this+0x2b8..+0x2e8] and rewrites [this+0x49c]+[0x4]
// style offsets; tools/attribute.py gives it a *probable* rhscript.cpp TU from
// that single caller, which is a hint, not a name. The direct call site emits as
// a non-inline member; defined once in RHScript_stubs.cpp.
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

class RHUnk005bd5b0
{
public:
    bool Unk(bool value);
};

class RHUnk004af060
{
public:
    void Unk(int direction);
};

class RHUnk0046bcb0
{
public:
    void Unk(int value);
};

struct RHUnk00571160Position
{
    float x;
    float y;
    void *area;
    short layer;
};

void RHUnk0048ce80(int noise, RHUnk00571160Position *position);

class SBGeoPoint2D
{
public:
    float m_x;
    float m_y;
    SBGeoPoint2D();
    SBGeoPoint2D(float x, float y);
    ~SBGeoPoint2D();
    SBGeoPoint2D(const SBGeoPoint2D &other);
    SBGeoPoint2D &operator=(const SBGeoPoint2D &other);
    SBGeoPoint2D Unk005fc110(const SBGeoPoint2D &other) const;
    SBGeoPoint2D Unk005fc190(const SBGeoPoint2D &other) const;
    float Unk005fc6d0(float value) const;
    void FUN_005fc390(const SBGeoPoint2D &other) throw();
};

SBGeoPoint2D RHUnk005758d0(const SBGeoPoint2D &point);

class RHUnk00582220
{
public:
    RHUnk00582220();
    ~RHUnk00582220();
    char m_data[0x3c];
};

struct RHScriptNode
{
    RHScriptNode *next;
    RHScriptNode *prev;
    void *data;
};

struct RHScriptIter
{
    RHScriptNode *node;
    RHScriptIter(RHScriptNode *value) : node(value) {}
};

struct RHUnk005c9010Iterator;
void FUN_005c9010(RHUnk005c9010Iterator &current, int distance, std::bidirectional_iterator_tag category);

class RHUnk0046eb30
{
public:
    int allocator;
    RHScriptNode *head;
    int count;
    RHScriptNode *cursor;
    bool valid;
    char padding[3];
    int index;
    RHScriptIter erase(RHScriptIter position);
    RHScriptIter begin();
    RHScriptIter FUN_0046eb80();
    RHScriptIter Unk0057c950(RHScriptIter position, const RHUnk00571160Position &value);
    RHScriptNode *Unk0059f720(RHScriptNode *next, RHScriptNode *previous);
    void *&Get(int wanted)
    {
        int size = count;
        if (valid)
        {
            if (wanted <= (size + 1) / 2)
            {
                cursor = head->next;
                std::bidirectional_iterator_tag category;
                FUN_005c9010((RHUnk005c9010Iterator &)cursor, wanted, category);
            }
            else
            {
                cursor = head;
                std::bidirectional_iterator_tag category;
                FUN_005c9010((RHUnk005c9010Iterator &)cursor, wanted - size, category);
            }
            valid = false;
            index = wanted;
        }
        else
        {
            int previous = index;
            if (wanted != previous)
            {
                if (wanted < previous)
                {
                    if (wanted < (previous + 1) / 2)
                    {
                        cursor = FUN_0046eb80().node;
                        std::bidirectional_iterator_tag category;
                        FUN_005c9010((RHUnk005c9010Iterator &)cursor, wanted, category);
                    }
                    else
                    {
                        std::bidirectional_iterator_tag category;
                        FUN_005c9010((RHUnk005c9010Iterator &)cursor, wanted - previous, category);
                    }
                }
                else
                {
                    if (wanted < (previous + size) / 2)
                    {
                        std::bidirectional_iterator_tag category;
                        FUN_005c9010((RHUnk005c9010Iterator &)cursor, wanted - previous, category);
                    }
                    else
                    {
                        cursor = head;
                        std::bidirectional_iterator_tag category;
                        FUN_005c9010((RHUnk005c9010Iterator &)cursor, wanted - size, category);
                    }
                }
                index = wanted;
            }
        }
        return cursor->data;
    }
};

class RHUnk0058a3d0
{
public:
    void Unk(void *context, int value, void *sequence);
};

class RHScriptSequenceVtable
{
public:
    virtual ~RHScriptSequenceVtable();
};

class RHUnk00522470
{
public:
    RHUnk00522470();
    ~RHUnk00522470();
    char m_pad0[4];
    float x;
    float y;
    char m_pad12[0x14];
    short layer;
    char m_pad34[2];
    void *area;
    void SetLayer(short value) { layer = value; }
    void SetArea(void *value) { area = value; }
};

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

class RHUnk005c38b0
{
public:
    void Unk(void *actor);
};

class RHUnk004e3660
{
public:
    void Unk(bool value);
};

class RHUnk00418b80
{
public:
    void Unk(bool value);
};

class RHActorPositionCalls
{
public:
    void FUN_00464530(const SBGeoPoint2D &point);
};

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

class RHUnk0057d800
{
public:
    RHBonusProjection *Unk(const SBGeoPoint2D &point);
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

class RHUnk0057ff00
{
public:
    bool Unk(void *actor);
};

class RHUnk00450b60
{
public:
    void Unk(int property, int amount);
};

class RHUnk00419a40
{
public:
    void Unk(int index, bool forbidden);
};

// SIZE 0x74
class RHUnk005866a0
{
public:
    RHUnk005866a0(unsigned short level, int command, void *actor);
    ~RHUnk005866a0();
    void Unk00586ed0(int property, int value);
    void Unk00586fd0(int property, float value);
    void Unk00587010(int property, const SBGeoPoint2D &value);
    void Unk00586e00(int property, bool value);
    undefined data[0x74]; // 0x00
};

class RHUnk005fc3b0 : public SBGeoPoint2D
{
public:
    RHUnk005fc3b0();
    ~RHUnk005fc3b0() {}
    float Unk005fc6a0(float value);
    RHUnk005fc3b0 &Unk005fcd40(unsigned short direction, float length);
    RHUnk005fc3b0 &FUN_005fc430(const SBGeoPoint2D &other);
    void Set(float x, float y) { m_x = x; m_y = y; }
};

class RHSeqList
{
public:
    int allocator;
    RHScriptNode *head;
    int count;
    RHScriptNode *cursor;
    void GoTo(int index);
    static void CopyData(RHSequenceElement **destination, RHSequenceElement *const *source);
};

class RHUnk00584d60
{
public:
    RHUnk00584d60(unsigned short level, int command, void *actor);
    ~RHUnk00584d60();
    char data[0x64];
    void SetFlag(bool value) { data[0x60] = value; }
};

class RHUnk0049d4f0
{
public:
    bool Unk(int value);
};

class RHUnk004af1d0
{
public:
    void Unk(bool value);
};

class RHUnk0048a970
{
public:
    void Unk(int index);
};

class RHUnk00413640
{
public:
    void Unk(int state, bool flag);
};

// SIZE 0x10
struct RHMalignityPosition
{
    float x; // 0x00
    float y; // 0x04
    void *area; // 0x08
    unsigned short layer; // 0x0c
};

class RHMalignityBaseView
{
public:
    RHMalignityPosition FUN_004165e0(void *actor, bool mode);
};

class RHScriptAIStateCalls
{
public:
    bool FUN_00410620(RHScriptStimulusValue value);
    void FUN_004132d0(int first, int second, int third);
    void FUN_00410d30();
    void FUN_0043a220(RHMalignityPosition position, int first, int second, int third);
};

struct RHAIPathArray;

// SIZE 0x0c
class RHArtificialIntelligencePathCursor
{
public:
    void Unk00550f60(unsigned short path);
    void FUN_00550fa0(void *path);
    unsigned char m_current; // 0x00
    unsigned char m_previous; // 0x01
    char m_forward; // 0x02
    undefined m_03; // 0x03
    RHAIPathArray *m_path; // 0x04
    unsigned short m_id; // 0x08
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

class RHSoundSource;
class RHSoundSourceManager
{
public:
    RHSoundSource *GetSoundSource(unsigned short id);
};

class RHUnk00588530
{
public:
    RHUnk00588530(unsigned short level, int command, void *actor, int style, void *target, float distance, void *value);
    ~RHUnk00588530();
    char data[0x68];
    RHUnk00582220 *sequence;
    char tail[0x30];
};

class RHUnk005492a0
{
public:
    RHUnk005492a0(int command, void *actor, int action);
    ~RHUnk005492a0();
    char data[0x14];
};

class RHUnk5490f0
{
public:
    RHUnk5490f0(int value);
    ~RHUnk5490f0();
private:
    void *m_vt;
    int m_unk04;
    int m_unk08;
    int m_unk0c;
};
class RHMessenger
{
public:
    void RHUnk005460c0(RHUnk5490f0 &message);
};
RHMessenger *RHUnk00546050();

class RHUnk00585ea0 : public RHUnk00584d60
{
public:
    RHUnk00585ea0(unsigned short level, int command, void *actor, void *target);
    ~RHUnk00585ea0();
    char tail[4];
};

void RHUnk00574690(void *actor, RHUnk00571160Position *position, void *location);
class RHUnk00582640
{
public:
    void Unk(unsigned short &level, void *actor, int style, const SBGeoPoint2D &start, void *startArea, unsigned short startLayer, const SBGeoPoint2D &end, void *endArea, unsigned short endLayer, void *element, float distance, unsigned long flags, float scale);
};

class SBGeoVector2D : public SBGeoPoint2D
{
public:
    SBGeoVector2D(const SBGeoPoint2D &point);
};

class RHUnk00560420
{
public:
    void Unk(RHUnk00571160Position *position);
};

class RHUnk005b5e00
{
public:
    void *Unk();
    SBGeoPoint2D *Unk005bdd30(short index);
    void *FUN_005b5de0();
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
    void Unk0046fe00();
    void Unk0046ec50(int value);
    bool Unk004e3e30(int index);
    void Unk004e3e00(int index, int value);
    int Unk004e3e20(int index);
    void Unk0040d980(int state);
    void Unk0048cbc0();
    void Unk0048c4d0();
    void Unk0046bcf0(int state, int value);
    void Unk0057ec80(void *actor);
    void Unk005c2ec0(void *position, int first, int second, void *actor, int third, int fourth, int fifth, int sixth);
    void Unk0058a940(void *context, int value, void *element);
    void Unk0041bd20(int style);
    bool Unk00489e80(void *target);
    void Unk0049d6c0();
    void Unk0057ebd0(void *actor);
    void Unk0048ec00(void *scroll);
    void Unk004d9330(void *actor, bool flag);
    void Unk0057ff70(float height);
    void Unk00444440(bool attentive);
    void Unk00455400(void *description);
    void Unk00514670();
    void Unk004555f0(void *description);
    void Unk004520e0(int index, int value);
    void Unk004e3220(int value);
    void Unk0050ed40();
    void Unk00450be0(int property, int value);
    int Unk004ec910(void *location, float radius, float strength, int value);
    bool Unk00456cb0(int type);
    void Unk004522e0(void *description);
    RHScriptBatchCalls *Unk004e3cc0();
    void Unk0054cfa0(void *description);
    void Unk00485220(int index, int value);
    unsigned int Unk004baea0();
    void Unk0046b9e0();
    bool Unk0049d560(int action);
    bool Unk00456ce0(void *type);
    void Unk00419fb0(int value);
    void Unk00419fd0(int value, int duration);
    void Unk0041ac50();
    float FUN_00489680(void *target);
    void FUN_0051d540(int index, int value);
    void FUN_0058bbe0(void *actor, int value);
    void FUN_0050eb80(bool value);
    void FUN_0050eca0(bool value);
    void FUN_00456d20();
    void FUN_005209b0();
    void FUN_00520a70();
    void FUN_00549090();
};

class RHUnk00613e90
{
public:
    RHUnk00613e90();
    float x;
    float y;
    float z;
};

class RHUnk005861c0
{
public:
    RHUnk005861c0(unsigned short level, int command, void *actor, unsigned short amount, unsigned short value);
    ~RHUnk005861c0();
    char data[0x7c];
};

class RHElementActor;
class RHSectorScript
{
public:
    void Enter(RHElementActor *actor);
    void Leave(RHElementActor *actor);
};

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
    ~RHUnk00549250();
    char data[4];
};

class RHUnk005ef320
{
public:
    unsigned short Unk(int red, int green, int blue);
};

extern RHUnk005ef320 *g_unk0x6c11d0;

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

struct RHSectorActorNode;

class RHSectorActorConstIter
{
public:
    RHSectorActorNode *m_p;
    RHSectorActorConstIter(RHSectorActorNode *node) : m_p(node) {}
};

class RHSectorActorIter : public RHSectorActorConstIter
{
public:
    RHSectorActorIter(RHSectorActorNode *node) : RHSectorActorConstIter(node) {}
    RHSectorActorIter operator++(int);
};

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
