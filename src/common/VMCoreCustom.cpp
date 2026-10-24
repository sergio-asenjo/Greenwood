#include "VMCoreCustom.h"
#include "RHScript.h"

int FUN_00579a20();
void FUN_005785d0(void *value);
void FUN_005782a0(void *object, bool value);
void FUN_005785b0(void *first, void *second);
unsigned FUN_0057aa20();
class RHElementScroll;

namespace VMCoreCustomDependencies
{
    void FUN_00576170();
    int FUN_0057b150();
    int FUN_00576a30();
    int FUN_00576af0();
    bool FUN_00577fe0();
    bool FUN_005761f0();
    bool FUN_00576260();
    RHElementScroll *FUN_005798c0();
    void *FUN_0057a8e0();
    int FUN_0057b370();
    void FUN_00578c60();
    int FUN_00578050();
    int FUN_005714d0();
    unsigned char FUN_00578820();
    int FUN_005791d0();
    int FUN_005792d0();
    unsigned char FUN_005795b0();
    bool FUN_00579690();
    int FUN_0057b5e0();
    unsigned char FUN_0057bfe0();
    void FUN_00577090(int, int);
    int FUN_00571760(int);
    int FUN_00571780(int);
    int FUN_00579bd0(int);
    int FUN_00579c90(int);
    int FUN_00579d00(int);
    int FUN_00579d70(int);
    void FUN_005714a0(int);
    bool FUN_005714b0(bool);
    void FUN_0057b780();
    void FUN_00570a30(int);
    bool FUN_00572a20(int);
    bool FUN_00575350(int);
    bool FUN_00573d10(int, int, int, int);
    bool Call006390a0(int);
    bool FUN_00570a70(int);
    bool FUN_00570a50(int);
    bool FUN_00570a60(int, int);
    bool FUN_00577cf0(int, int);
    void FUN_00578830(bool);
    bool FUN_00578690(int, int, int);
    void FUN_00576c30(bool);
    bool FUN_00570e20(int);
    bool FUN_00570e30(int);
    bool FUN_00570e50(int);
    void Call00578c50(int);
    int FUN_00578680(int);
    int FUN_005791f0(int);
    void FUN_00579000(int, int);
    void FUN_005786f0(int, int, bool);
    void FUN_005799d0(int, int, int);
    void FUN_00579a00(int, int);
    int FUN_0057a280(int, int);
    int FUN_0057a290(int, int);
    int FUN_0057a2a0(int, int);
    int FUN_0057a950(int);
    int FUN_0057aa50(int);
    void FUN_0057ae60(int);
    void FUN_00577df0(bool);
    void FUN_0057ae40(int);
    bool FUN_00571e30(int);
    void FUN_0057b2b0(int, int, int);
    void FUN_0057b350(int, bool);
    bool FUN_0057b3d0(int);
    void FUN_0057ba50(int, bool);
    void FUN_0057bff0(int);
}

// FUNCTION: GAME 0x00404a80
int VMCoreCustom::FUN_00404a80(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 8;
    VMCoreCustomDependencies::FUN_00577090(*(int *)(data + top - 8), *(int *)(data + size - 4));
    return 0;
}

// FUNCTION: GAME 0x00404ab0
int VMCoreCustom::ISetGlobal(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 8;
    RHScript::SetGlobal(*(int *)(data + top - 8), *(int *)(data + size - 4));
    return 0;
}

// FUNCTION: GAME 0x00404ae0
int VMCoreCustom::IGetGlobal(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return RHScript::GetGlobal(args[0]);
}

// FUNCTION: GAME 0x00404b00
int VMCoreCustom::IGetActorScript(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return (int)RHScript::GetActorScript(args[0]);
}

// FUNCTION: GAME 0x00404b20
int VMCoreCustom::IGetDoorScript(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return (int)RHScript::GetDoorScript(args[0]);
}

// FUNCTION: GAME 0x00404b40
int VMCoreCustom::IGetPatchScript(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return (int)RHScript::GetPatchScript(args[0]);
}

// FUNCTION: GAME 0x00404b60
int VMCoreCustom::IGetLocationScript(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return (int)RHScript::GetLocationScript(args[0]);
}

// FUNCTION: GAME 0x00404b80
int VMCoreCustom::IGetSoundSourceScript(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return (int)RHScript::GetSoundSourceScript(args[0]);
}

// FUNCTION: GAME 0x00404ba0
int VMCoreCustom::FUN_00404ba0(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return VMCoreCustomDependencies::FUN_00571760(args[0]);
}

// FUNCTION: GAME 0x00404bc0
int VMCoreCustom::FUN_00404bc0(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return VMCoreCustomDependencies::FUN_00571780(args[0]);
}

// FUNCTION: GAME 0x00404be0
int VMCoreCustom::FUN_00404be0(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return VMCoreCustomDependencies::FUN_00579bd0(args[0]);
}

// FUNCTION: GAME 0x00404c00
int VMCoreCustom::FUN_00404c00(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return VMCoreCustomDependencies::FUN_00579c90(args[0]);
}

// FUNCTION: GAME 0x00404c20
int VMCoreCustom::FUN_00404c20(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return VMCoreCustomDependencies::FUN_00579d00(args[0]);
}

// FUNCTION: GAME 0x00404c40
int VMCoreCustom::FUN_00404c40(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return VMCoreCustomDependencies::FUN_00579d70(args[0]);
}

// FUNCTION: GAME 0x00404c60
int VMCoreCustom::IGetSoundSourceIndex(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return RHScript::GetSoundSourceIndex((void *)args[0]);
}

// FUNCTION: GAME 0x00404c80
int VMCoreCustom::FUN_00404c80(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return RHScript::RHUnk579e80(args[0]);
}

// FUNCTION: GAME 0x00404ca0
int VMCoreCustom::FUN_00404ca0(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return RHScript::RHUnk579ef0(args[0]);
}

// FUNCTION: GAME 0x00404cc0
int VMCoreCustom::FUN_00404cc0(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    VMCoreCustomDependencies::FUN_005714a0(args[0]);
    return 0;
}

// FUNCTION: GAME 0x00404cf0
int VMCoreCustom::IScrollCameraTo(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return RHScript::ScrollCameraTo((void *)args[0]);
}

// FUNCTION: GAME 0x00404d20
int VMCoreCustom::IScrollCameraSlowlyTo(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 8;
    return RHScript::ScrollCameraSlowlyTo(*(void **)(data + top - 8), *(float *)(data + size - 4));
}

// FUNCTION: GAME 0x00404d50
int VMCoreCustom::IJumpCameraTo(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return RHScript::JumpCameraTo((void *)args[0]);
}

// FUNCTION: GAME 0x00404d80
int VMCoreCustom::ISetZoomLevel(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return RHScript::SetZoomLevel(*(float *)&args[0]);
}

// FUNCTION: GAME 0x00404db0
int VMCoreCustom::FUN_00404db0(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return VMCoreCustomDependencies::FUN_005714b0(args[0] != 0);
}

// FUNCTION: GAME 0x00404de0
int VMCoreCustom::FUN_00404de0(VMNativeStack *stack)
{
    VMCoreCustomDependencies::FUN_00576170();
    return 0;
}

// FUNCTION: GAME 0x00404df0
int VMCoreCustom::ICustomizeMinimapDisplay(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 8;
    RHScript::CustomizeMinimapDisplay(*(void **)(data + top - 8), *(int *)(data + size - 4));
    return 0;
}

// FUNCTION: GAME 0x00404e20
int VMCoreCustom::IDefineFlatTrajectoryZone(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 8;
    RHScript::DefineFlatTrajectoryZone(*(void **)(data + top - 8), *(int *)(data + size - 4));
    return 0;
}

// FUNCTION: GAME 0x00404e50
int VMCoreCustom::FUN_00404e50(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 8;
    ((void (*)(void *, bool))FUN_005785b0)(*(void **)(data + top - 8), *(int *)(data + size - 4) != 0);
    return 0;
}

// FUNCTION: GAME 0x00404e80
int VMCoreCustom::FUN_00404e80(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    FUN_005785d0((void *)args[0]);
    return 0;
}

// FUNCTION: GAME 0x00404eb0
int VMCoreCustom::FUN_00404eb0(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    VMCoreCustomDependencies::FUN_00570a30(args[0]);
    return 0;
}

// FUNCTION: GAME 0x00404ef0
int VMCoreCustom::IStart(VMNativeStack *stack)
{
    return RHScript::Start();
}

// FUNCTION: GAME 0x00404f00
int VMCoreCustom::IThanx(VMNativeStack *stack)
{
    return RHScript::Thanx();
}

// FUNCTION: GAME 0x00404f10
int VMCoreCustom::IThen(VMNativeStack *stack)
{
    return RHScript::Then();
}

// FUNCTION: GAME 0x00404f20
int VMCoreCustom::IRecordScrollCameraTo(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return RHScript::RecordScrollCameraTo((void *)args[0]);
}

// FUNCTION: GAME 0x00404f50
int VMCoreCustom::IRecordJumpCameraTo(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return RHScript::RecordJumpCameraTo((void *)args[0]);
}

// FUNCTION: GAME 0x00404f80
int VMCoreCustom::IRecordSetZoom(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return RHScript::RecordSetZoom(*(float *)&args[0]);
}

// FUNCTION: GAME 0x00404fb0
int VMCoreCustom::IRecordDisplayMap(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return RHScript::RecordDisplayMap(args[0] != 0);
}

// FUNCTION: GAME 0x00404fe0
int VMCoreCustom::IRecordActionAvailable(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 12;
    return RHScript::RecordActionAvailable(*(void **)(data + top - 12), *(int *)(data + top - 8), *(int *)(data + size - 4) != 0);
}

// FUNCTION: GAME 0x00404ee0
int VMCoreCustom::FUN_00404ee0(VMNativeStack *)
{
    VMCoreCustomDependencies::FUN_00578c60();
    return 0;
}

// FUNCTION: GAME 0x00405020
int VMCoreCustom::IRecordCharacterAvailable(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 8;
    return RHScript::RecordCharacterAvailable(*(void **)(data + top - 8), *(int *)(data + size - 4) != 0);
}

// FUNCTION: GAME 0x00405050
int VMCoreCustom::IRecordLockCameraOn(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return RHScript::RecordLockCameraOn((void *)args[0]);
}

// FUNCTION: GAME 0x00405080
int VMCoreCustom::FUN_00405080(VMNativeStack *)
{
    return VMCoreCustomDependencies::FUN_00577fe0();
}

// FUNCTION: GAME 0x00405090
int VMCoreCustom::FUN_00405090(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return VMCoreCustomDependencies::FUN_00572a20(args[0]);
}

// FUNCTION: GAME 0x004050c0
int VMCoreCustom::IRecordMoveCameraTo(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 8;
    return RHScript::RecordMoveCameraTo(*(void **)(data + top - 8), *(int *)(data + size - 4));
}

// FUNCTION: GAME 0x004050f0
int VMCoreCustom::IRecordSendMessage(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 8;
    RHScript::RecordSendMessage(*(void **)(data + top - 8), *(int *)(data + size - 4));
    return 0;
}

// FUNCTION: GAME 0x00405120
int VMCoreCustom::IRecordSendMessageWithArguments(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 16;
    RHScript::RecordSendMessageWithArguments(*(void **)(data + top - 16), *(int *)(data + top - 12), *(int *)(data + top - 8), *(int *)(data + size - 4));
    return 0;
}

// FUNCTION: GAME 0x00405150
int VMCoreCustom::IRecordMove(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 12;
    return RHScript::RecordMove(*(void **)(data + top - 12), *(void **)(data + top - 8), *(int *)(data + size - 4));
}

// FUNCTION: GAME 0x00405180
int VMCoreCustom::IRecordEnterGame(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 16;
    return RHScript::RecordEnterGame(*(void **)(data + top - 16), *(void **)(data + top - 12), *(int *)(data + top - 8), *(int *)(data + size - 4));
}

// FUNCTION: GAME 0x004051c0
int VMCoreCustom::IRecordLeaveGame(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 16;
    return RHScript::RecordLeaveGame(*(void **)(data + top - 16), *(void **)(data + top - 12), *(int *)(data + top - 8), *(int *)(data + size - 4));
}

// FUNCTION: GAME 0x00405200
int VMCoreCustom::IRecordTurnTo(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 8;
    return RHScript::RecordTurnTo(*(void **)(data + top - 8), *(void **)(data + size - 4));
}

// FUNCTION: GAME 0x00405230
int VMCoreCustom::IRecordPlayAnim(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 8;
    return RHScript::RecordPlayAnim(*(void **)(data + top - 8), *(int *)(data + size - 4));
}

// FUNCTION: GAME 0x00405260
int VMCoreCustom::IRecordPlayAnimLoop(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 8;
    return RHScript::RecordPlayAnimLoop(*(void **)(data + top - 8), *(int *)(data + size - 4));
}

// FUNCTION: GAME 0x00405290
int VMCoreCustom::IRecordPlayAnimFreeze(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 8;
    return RHScript::RecordPlayAnimFreeze(*(void **)(data + top - 8), *(int *)(data + size - 4));
}

// FUNCTION: GAME 0x004052c0
int VMCoreCustom::IRecordLockAI(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return RHScript::RecordLockAI((void *)args[0]);
}

// FUNCTION: GAME 0x004052f0
int VMCoreCustom::IRecordUnlockAI(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return RHScript::RecordUnlockAI((void *)args[0]);
}

// FUNCTION: GAME 0x00405320
int VMCoreCustom::IRecordLockUser(VMNativeStack *stack)
{
    return RHScript::RecordLockUser();
}

// FUNCTION: GAME 0x00405330
int VMCoreCustom::IRecordUnLockUser(VMNativeStack *stack)
{
    return RHScript::RecordUnLockUser();
}

// FUNCTION: GAME 0x00405340
int VMCoreCustom::FUN_00405340(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return VMCoreCustomDependencies::FUN_00575350(args[0]);
}

// FUNCTION: GAME 0x00405370
int VMCoreCustom::FUN_00405370(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 16;
    return VMCoreCustomDependencies::FUN_00573d10(*(int *)(data + top - 16), *(int *)(data + top - 12), *(int *)(data + top - 8), *(int *)(data + size - 4));
}

// Parked: cdecl stack argument conflicts with the existing virtual VMCore callee binding.
// STUB: GAME 0x004053b0
int VMCoreCustom::FUN_004053b0(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return VMCoreCustomDependencies::Call006390a0(args[0]);
}

// FUNCTION: GAME 0x004053e0
int VMCoreCustom::IRecordAction(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 12;
    return RHScript::RecordAction(*(void **)(data + top - 12), *(int *)(data + top - 8), *(int *)(data + size - 4));
}

// FUNCTION: GAME 0x00405410
int VMCoreCustom::IRecordReplaceAnim(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 12;
    return RHScript::RecordReplaceAnim(*(void **)(data + top - 12), *(int *)(data + top - 8), *(int *)(data + size - 4));
}

// FUNCTION: GAME 0x00405440
int VMCoreCustom::IRecordRestoreAnim(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 8;
    return RHScript::RecordRestoreAnim(*(void **)(data + top - 8), *(int *)(data + size - 4));
}

// FUNCTION: GAME 0x00405470
int VMCoreCustom::IRecordSpeakPC(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 12;
    return RHScript::RecordSpeakPC(*(void **)(data + top - 12), *(int *)(data + top - 8), *(int *)(data + size - 4));
}

// FUNCTION: GAME 0x004054a0
int VMCoreCustom::IRecordTakeCorpse(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 12;
    return RHScript::RecordTakeCorpse(*(void **)(data + top - 12), *(void **)(data + top - 8), *(int *)(data + size - 4));
}

// FUNCTION: GAME 0x004054d0
int VMCoreCustom::IRecordMoveIntoBuilding(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 12;
    return RHScript::RecordMoveIntoBuilding(*(void **)(data + top - 12), *(void **)(data + top - 8), *(int *)(data + size - 4));
}

// FUNCTION: GAME 0x00405500
int VMCoreCustom::IRecordLeaveCorpse(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return RHScript::RecordLeaveCorpse((void *)args[0]);
}

// FUNCTION: GAME 0x00405530
int VMCoreCustom::FUN_00405530(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return RHScript::FUN_00570dd0((void *)args[0]);
}

// FUNCTION: GAME 0x00405560
int VMCoreCustom::IRecordStartMobileElement(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    RHScript::RecordStartMobileElement(args[0]);
    return 0;
}

// FUNCTION: GAME 0x00405590
int VMCoreCustom::IRecordStopMobileElement(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    RHScript::RecordStopMobileElement(args[0]);
    return 0;
}

// FUNCTION: GAME 0x004055c0
int VMCoreCustom::IRecordSpeak(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 8;
    return RHScript::RecordSpeak(*(void **)(data + top - 8), *(int *)(data + size - 4));
}

// FUNCTION: GAME 0x004055f0
int VMCoreCustom::IRecordSeekActorMessage(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 24;
    return RHScript::RecordSeekActorMessage(*(void **)(data + top - 24), *(void **)(data + top - 20), *(int *)(data + top - 16), *(float *)(data + top - 12), *(void **)(data + top - 8), *(int *)(data + size - 4));
}

// FUNCTION: GAME 0x00405630
int VMCoreCustom::IRecordSeekActorMessageWithArguments(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 32;
    return RHScript::RecordSeekActorMessageWithArguments(*(void **)(data + top - 32), *(void **)(data + top - 28), *(int *)(data + top - 24), *(float *)(data + top - 20), *(void **)(data + top - 16), *(int *)(data + top - 12), *(int *)(data + top - 8), *(int *)(data + size - 4));
}

// FUNCTION: GAME 0x00405680
int VMCoreCustom::IRecordActivateMobileElement(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    RHScript::RecordActivateMobileElement(args[0]);
    return 0;
}

// FUNCTION: GAME 0x004056b0
int VMCoreCustom::IRecordDeactivateMobileElement(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    RHScript::RecordDeactivateMobileElement(args[0]);
    return 0;
}

// FUNCTION: GAME 0x004056e0
int VMCoreCustom::FUN_004056e0(VMNativeStack *)
{
    return VMCoreCustomDependencies::FUN_00578050();
}

// FUNCTION: GAME 0x004056f0
int VMCoreCustom::FUN_004056f0(VMNativeStack *)
{
    return VMCoreCustomDependencies::FUN_005714d0();
}

// FUNCTION: GAME 0x00405700
int VMCoreCustom::FUN_00405700(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return VMCoreCustomDependencies::FUN_00570a70(args[0]);
}

// FUNCTION: GAME 0x00405730
int VMCoreCustom::IIsActorObject(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return RHScript::IsActorObject((void *)args[0]);
}

// FUNCTION: GAME 0x00405760
int VMCoreCustom::IIsActorCharacter(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return RHScript::IsActorCharacter((void *)args[0]);
}

// FUNCTION: GAME 0x00405790
int VMCoreCustom::IIsActorPC(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return RHScript::IsActorPC((void *)args[0]);
}

// FUNCTION: GAME 0x004057c0
int VMCoreCustom::IIsActorNPC(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return RHScript::IsActorNPC((void *)args[0]);
}

// FUNCTION: GAME 0x004057f0
int VMCoreCustom::IIsActorSoldier(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return RHScript::IsActorSoldier((void *)args[0]);
}

// FUNCTION: GAME 0x00405820
int VMCoreCustom::IIsActorCivilian(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return RHScript::IsActorCivilian((void *)args[0]);
}

// FUNCTION: GAME 0x00405850
int VMCoreCustom::IIsActorAnimal(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return RHScript::IsActorAnimal((void *)args[0]);
}

// FUNCTION: GAME 0x00405880
int VMCoreCustom::IIsActorCart(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return RHScript::IsActorCart((void *)args[0]);
}

// FUNCTION: GAME 0x004058b0
int VMCoreCustom::FUN_004058b0(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return VMCoreCustomDependencies::FUN_00570a50(args[0]);
}

// FUNCTION: GAME 0x004058e0
int VMCoreCustom::FUN_004058e0(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 8;
    return VMCoreCustomDependencies::FUN_00570a60(*(int *)(data + top - 8), *(int *)(data + size - 4));
}

// FUNCTION: GAME 0x00405910
int VMCoreCustom::IIsActorDead(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return RHScript::IsActorDead((void *)args[0]);
}

// FUNCTION: GAME 0x00405940
int VMCoreCustom::IIsActorKO(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return (unsigned char)RHScript::IsActorKO((void *)args[0]);
}

// FUNCTION: GAME 0x00405970
int VMCoreCustom::IIsActorTied(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return RHScript::IsActorTied((void *)args[0]);
}

// FUNCTION: GAME 0x004059a0
int VMCoreCustom::IIsActorHS(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return RHScript::IsActorHS((void *)args[0]);
}

// FUNCTION: GAME 0x004059d0
int VMCoreCustom::IGetActorPosture(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return RHScript::GetActorPosture((void *)args[0]);
}

// FUNCTION: GAME 0x004059f0
int VMCoreCustom::ISetActorPosture(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 8;
    RHScript::SetActorPosture(*(void **)(data + top - 8), *(int *)(data + size - 4));
    return 0;
}

// FUNCTION: GAME 0x00405a20
int VMCoreCustom::IGetActorDirection(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return RHScript::GetActorDirection((void *)args[0]);
}

// FUNCTION: GAME 0x00405a40
int VMCoreCustom::ISetActorDirection(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 8;
    return RHScript::SetActorDirection(*(void **)(data + top - 8), *(int *)(data + size - 4));
}

// FUNCTION: GAME 0x00405a70
int VMCoreCustom::IGetActorLocation(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return (int)RHScript::GetActorLocation((void *)args[0]);
}

// FUNCTION: GAME 0x00405a90
int VMCoreCustom::ISetActorLocation(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 8;
    return RHScript::SetActorLocation(*(void **)(data + top - 8), *(void **)(data + size - 4));
}

// FUNCTION: GAME 0x00405ac0
int VMCoreCustom::IIsInside(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 8;
    return RHScript::IsInside(*(void **)(data + top - 8), *(void **)(data + size - 4));
}

// FUNCTION: GAME 0x00405af0
int VMCoreCustom::FUN_00405af0(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 8;
    return VMCoreCustomDependencies::FUN_00577cf0(*(int *)(data + top - 8), *(int *)(data + size - 4));
}

// FUNCTION: GAME 0x00405b20
int VMCoreCustom::IUnBlip(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return RHScript::UnBlip((void *)args[0]);
}

// FUNCTION: GAME 0x00405b50
int VMCoreCustom::IGetMovementStyle(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return RHScript::GetMovementStyle((void *)args[0]);
}

// FUNCTION: GAME 0x00405b70
int VMCoreCustom::IGetCurrentAction(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return RHScript::GetCurrentAction((void *)args[0]);
}

// FUNCTION: GAME 0x00405b90
int VMCoreCustom::IInflictPain(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 12;
    RHScript::InflictPain(*(void **)(data + top - 12), *(int *)(data + top - 8), *(int *)(data + size - 4) != 0);
    return 0;
}

// FUNCTION: GAME 0x00405bc0
int VMCoreCustom::IStopActor(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return RHScript::StopActor((void *)args[0]);
}

// FUNCTION: GAME 0x00405bf0
int VMCoreCustom::ISees(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 8;
    return RHScript::Sees(*(void **)(data + top - 8), *(void **)(data + size - 4));
}

// FUNCTION: GAME 0x00405c20
int VMCoreCustom::IEnableViewCone(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    RHScript::EnableViewCone((void *)args[0]);
    return 0;
}

// FUNCTION: GAME 0x00405c50
int VMCoreCustom::FUN_00405c50(VMNativeStack *)
{
    return VMCoreCustomDependencies::FUN_00578820();
}

// FUNCTION: GAME 0x00405c60
int VMCoreCustom::FUN_00405c60(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    VMCoreCustomDependencies::FUN_00578830(args[0] != 0);
    return 0;
}

// FUNCTION: GAME 0x00405c90
int VMCoreCustom::FUN_00405c90(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 12;
    return VMCoreCustomDependencies::FUN_00578690(*(int *)(data + top - 12), *(int *)(data + top - 8), *(int *)(data + size - 4));
}

// FUNCTION: GAME 0x00405cc0
int VMCoreCustom::ISendMessage(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 8;
    RHScript::SendMessage(*(void **)(data + top - 8), *(int *)(data + size - 4));
    return 0;
}

// FUNCTION: GAME 0x00405cf0
int VMCoreCustom::ISendMessageWithArguments(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 16;
    RHScript::SendMessageWithArguments(*(void **)(data + top - 16), *(int *)(data + top - 12), *(int *)(data + top - 8), *(int *)(data + size - 4));
    return 0;
}

// FUNCTION: GAME 0x00405d20
int VMCoreCustom::FUN_00405d20(VMNativeStack *stack)
{
    return FUN_00579a20();
}

// FUNCTION: GAME 0x00405d30
int VMCoreCustom::ISelect(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return RHScript::Select(args[0]);
}

// FUNCTION: GAME 0x00405d60
int VMCoreCustom::IDeactivate(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return RHScript::Deactivate((void *)args[0]);
}

// FUNCTION: GAME 0x00405d90
int VMCoreCustom::IActivate(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return RHScript::Activate((void *)args[0]);
}

// FUNCTION: GAME 0x00405dc0
int VMCoreCustom::ISetActionAvailable(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 12;
    return RHScript::SetActionAvailable(*(void **)(data + top - 12), *(int *)(data + top - 8), *(int *)(data + size - 4) != 0);
}

// FUNCTION: GAME 0x00405e00
int VMCoreCustom::IIsActionAvailable(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 8;
    return RHScript::IsActionAvailable(*(void **)(data + top - 8), *(int *)(data + size - 4));
}

// FUNCTION: GAME 0x00405e30
int VMCoreCustom::ISetPersistentProperty(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 12;
    return RHScript::SetPersistentProperty(*(void **)(data + top - 12), *(int *)(data + top - 8), *(int *)(data + size - 4));
}

// FUNCTION: GAME 0x00405e60
int VMCoreCustom::IGetPersistentProperty(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 8;
    return RHScript::GetPersistentProperty(*(void **)(data + top - 8), *(int *)(data + size - 4));
}

// FUNCTION: GAME 0x00405e90
int VMCoreCustom::FUN_00405e90(VMNativeStack *)
{
    return VMCoreCustomDependencies::FUN_005761f0();
}

// FUNCTION: GAME 0x00405ea0
int VMCoreCustom::FUN_00405ea0(VMNativeStack *)
{
    return VMCoreCustomDependencies::FUN_00576260();
}

// FUNCTION: GAME 0x00405eb0
int VMCoreCustom::FUN_00405eb0(VMNativeStack *)
{
    return VMCoreCustomDependencies::FUN_00576a30();
}

// FUNCTION: GAME 0x00405ec0
int VMCoreCustom::FUN_00405ec0(VMNativeStack *)
{
    return VMCoreCustomDependencies::FUN_00576af0();
}

// FUNCTION: GAME 0x00405ed0
int VMCoreCustom::ISetAIAlertStatus(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 8;
    return RHScript::SetAIAlertStatus(*(void **)(data + top - 8), *(int *)(data + size - 4));
}

// FUNCTION: GAME 0x00405f00
int VMCoreCustom::IGetAIAlertStatus(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return RHScript::GetAIAlertStatus((void *)args[0]);
}

// FUNCTION: GAME 0x00405f20
int VMCoreCustom::ISetAIState(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 8;
    return RHScript::SetAIState(*(void **)(data + top - 8), *(int *)(data + size - 4));
}

// FUNCTION: GAME 0x00405f50
int VMCoreCustom::IGetAIState(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return RHScript::GetAIState((void *)args[0]);
}

// FUNCTION: GAME 0x00405f70
int VMCoreCustom::ISetAIAttitude(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 8;
    return RHScript::SetAIAttitude(*(void **)(data + top - 8), *(int *)(data + size - 4));
}

// FUNCTION: GAME 0x00405fa0
int VMCoreCustom::IGetAIAttitude(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return RHScript::GetAIAttitude((void *)args[0]);
}

// FUNCTION: GAME 0x00405fc0
int VMCoreCustom::ISetAILevel(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 12;
    return RHScript::SetAILevel(*(void **)(data + top - 12), *(int *)(data + top - 8), *(int *)(data + size - 4));
}

// FUNCTION: GAME 0x00405ff0
int VMCoreCustom::IStareActor(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 12;
    RHScript::StareActor(*(void **)(data + top - 12), *(void **)(data + top - 8), *(int *)(data + size - 4) != 0);
    return 0;
}

// FUNCTION: GAME 0x00406020
int VMCoreCustom::IStareLocation(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 12;
    RHScript::StareLocation(*(void **)(data + top - 12), *(void **)(data + top - 8), *(int *)(data + size - 4) != 0);
    return 0;
}

// FUNCTION: GAME 0x00406050
int VMCoreCustom::IAssignPath(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 8;
    RHScript::AssignPath(*(void **)(data + top - 8), *(void **)(data + size - 4));
    return 0;
}

// FUNCTION: GAME 0x00406080
int VMCoreCustom::IAssignPost(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 12;
    RHScript::AssignPost(*(void **)(data + top - 12), *(void **)(data + top - 8), *(int *)(data + size - 4));
    return 0;
}

// FUNCTION: GAME 0x004060b0
int VMCoreCustom::ILockAI(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 8;
    RHScript::LockAI(*(void **)(data + top - 8), *(int *)(data + size - 4) != 0);
    return 0;
}

// FUNCTION: GAME 0x004060e0
int VMCoreCustom::IUnlockAI(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    RHScript::UnlockAI((void *)args[0]);
    return 0;
}

// FUNCTION: GAME 0x00406110
int VMCoreCustom::IForceBattleDecision(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 8;
    RHScript::ForceBattleDecision(*(void **)(data + top - 8), *(int *)(data + size - 4));
    return 0;
}

// FUNCTION: GAME 0x00406140
int VMCoreCustom::IMakeNoise(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 8;
    RHScript::MakeNoise(*(void **)(data + top - 8), *(int *)(data + size - 4));
    return 0;
}

// FUNCTION: GAME 0x00406170
int VMCoreCustom::IFreeze(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 8;
    RHScript::Freeze(*(void **)(data + top - 8), *(int *)(data + size - 4) != 0);
    return 0;
}

// FUNCTION: GAME 0x004061a0
int VMCoreCustom::FUN_004061a0(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    VMCoreCustomDependencies::FUN_00576c30(args[0] != 0);
    return 0;
}

// FUNCTION: GAME 0x004061d0
int VMCoreCustom::ISetPathWalkingStyle(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 8;
    RHScript::SetPathWalkingStyle(*(void **)(data + top - 8), *(int *)(data + size - 4));
    return 0;
}

// FUNCTION: GAME 0x00406200
int VMCoreCustom::IGetSoldierRank(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return RHScript::GetSoldierRank((void *)args[0]);
}

// FUNCTION: GAME 0x00406220
int VMCoreCustom::IIsAnimationActive(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return (unsigned char)RHScript::IsAnimationActive((void *)args[0]);
}

// FUNCTION: GAME 0x00406250
int VMCoreCustom::ISetAnimationState(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 8;
    return RHScript::SetAnimationState(*(void **)(data + top - 8), *(int *)(data + size - 4) != 0);
}

// FUNCTION: GAME 0x00406280
int VMCoreCustom::FUN_00406280(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return VMCoreCustomDependencies::FUN_00570e20(args[0]);
}

// FUNCTION: GAME 0x004062b0
int VMCoreCustom::FUN_004062b0(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return VMCoreCustomDependencies::FUN_00570e30(args[0]);
}

// FUNCTION: GAME 0x004062e0
int VMCoreCustom::FUN_004062e0(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return VMCoreCustomDependencies::FUN_00570e50(args[0]);
}

// FUNCTION: GAME 0x00406310
int VMCoreCustom::FUN_00406310(VMNativeStack *stack)
{
    return (unsigned char)RHScript::RHUnk575510();
}

// FUNCTION: GAME 0x00406320
int VMCoreCustom::FUN_00406320(VMNativeStack *stack)
{
    return (unsigned char)RHScript::RHUnk575530();
}

// FUNCTION: GAME 0x00406330
int VMCoreCustom::FUN_00406330(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return (unsigned char)RHScript::RHUnk575560((void *)args[0]);
}

// FUNCTION: GAME 0x00406360
int VMCoreCustom::FUN_00406360(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return (unsigned char)RHScript::RHUnk575590((void *)args[0]);
}

// FUNCTION: GAME 0x00406390
int VMCoreCustom::FUN_00406390(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return (unsigned char)RHScript::RHUnk5755c0((void *)args[0]);
}

// FUNCTION: GAME 0x004063c0
int VMCoreCustom::ICleanFromHisBuildingBeforeTeleport(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return RHScript::CleanFromHisBuildingBeforeTeleport((void *)args[0]);
}

// FUNCTION: GAME 0x004063f0
int VMCoreCustom::ICleanFromScriptZoneBeforeTeleport(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 8;
    return RHScript::CleanFromScriptZoneBeforeTeleport(*(void **)(data + top - 8), *(void **)(data + size - 4));
}

// FUNCTION: GAME 0x00406420
int VMCoreCustom::IAddToScriptZoneAfterTeleport(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 8;
    return RHScript::AddToScriptZoneAfterTeleport(*(void **)(data + top - 8), *(void **)(data + size - 4));
}

// FUNCTION: GAME 0x00406450
int VMCoreCustom::FUN_00406450(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    VMCoreCustomDependencies::Call00578c50(args[0]);
    return 0;
}

// FUNCTION: GAME 0x00406480
int VMCoreCustom::IPutActorInBulding(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 8;
    RHScript::PutActorInBulding(*(void **)(data + top - 8), *(void **)(data + size - 4));
    return 0;
}

// FUNCTION: GAME 0x004064b0
int VMCoreCustom::FUN_004064b0(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 8;
    FUN_005782a0(*(void **)(data + top - 8), *(int *)(data + size - 4) != 0);
    return 0;
}

// FUNCTION: GAME 0x004064e0
int VMCoreCustom::IGetAnyActorInsideBuilding(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return (int)RHScript::GetAnyActorInsideBuilding((void *)args[0]);
}

// FUNCTION: GAME 0x00406500
int VMCoreCustom::IGetDistance(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 8;
    return RHScript::GetDistance(*(void **)(data + top - 8), *(void **)(data + size - 4));
}

// FUNCTION: GAME 0x00406530
int VMCoreCustom::FUN_00406530(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return VMCoreCustomDependencies::FUN_00578680(args[0]);
}

// FUNCTION: GAME 0x00406550
int VMCoreCustom::FUN_00406550(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    RHScript::RHUnk579f10(args[0]);
    return 0;
}

// FUNCTION: GAME 0x00406580
int VMCoreCustom::FUN_00406580(VMNativeStack *)
{
    return VMCoreCustomDependencies::FUN_005791d0();
}

// FUNCTION: GAME 0x00406590
int VMCoreCustom::FUN_00406590(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return VMCoreCustomDependencies::FUN_005791f0(args[0]);
}

// FUNCTION: GAME 0x004065b0
int VMCoreCustom::IAddPCToMissionTeam(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    RHScript::AddPCToMissionTeam((void *)args[0]);
    return 0;
}

// FUNCTION: GAME 0x004065e0
int VMCoreCustom::IRemovePCFromMissionTeam(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    RHScript::RemovePCFromMissionTeam((void *)args[0]);
    return 0;
}

// FUNCTION: GAME 0x00406620
int VMCoreCustom::IGetPCFromMissionTeam(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return (int)RHScript::GetPCFromMissionTeam(args[0]);
}

// FUNCTION: GAME 0x00406640
int VMCoreCustom::FUN_00406640(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return (unsigned char)RHScript::RHUnk5793a0((void *)args[0]);
}

// FUNCTION: GAME 0x00406670
int VMCoreCustom::FUN_00406670(VMNativeStack *stack)
{
    return (int)(unsigned char)RHScript::RHUnk5793e0();
}

// FUNCTION: GAME 0x00406680
int VMCoreCustom::FUN_00406680(VMNativeStack *stack)
{
    return (int)RHScript::RHUnk5793f0();
}

// FUNCTION: GAME 0x00406690
int VMCoreCustom::FUN_00406690(VMNativeStack *stack)
{
    return (int)RHScript::RHUnk579410();
}

// FUNCTION: GAME 0x004066b0
int VMCoreCustom::IGetNumberOfBeamMes(VMNativeStack *stack)
{
    return RHScript::GetNumberOfBeamMes();
}

// FUNCTION: GAME 0x00406610
int VMCoreCustom::FUN_00406610(VMNativeStack *)
{
    return VMCoreCustomDependencies::FUN_005792d0();
}

// FUNCTION: GAME 0x004066a0
int VMCoreCustom::FUN_004066a0(VMNativeStack *)
{
    return VMCoreCustomDependencies::FUN_005795b0();
}

// FUNCTION: GAME 0x004066c0
int VMCoreCustom::FUN_004066c0(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 8;
    VMCoreCustomDependencies::FUN_00579000(*(int *)(data + top - 8), *(int *)(data + size - 4));
    return 0;
}

// FUNCTION: GAME 0x004066f0
int VMCoreCustom::ISetCompanyNumber(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 8;
    int value = *(int *)(data + size - 4);
    RHScript::SetCompanyNumber(*(void **)(data + top - 8), (short)value);
    return 0;
}

// FUNCTION: GAME 0x00406720
int VMCoreCustom::ISetAlwaysAttentive(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 8;
    RHScript::SetAlwaysAttentive(*(void **)(data + top - 8), *(int *)(data + size - 4) != 0);
    return 0;
}

// FUNCTION: GAME 0x00406750
int VMCoreCustom::IWinBlazon(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    RHScript::WinBlazon((void *)args[0]);
    return 0;
}

// FUNCTION: GAME 0x00406780
int VMCoreCustom::ILoseBlazon(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    RHScript::LoseBlazon((void *)args[0]);
    return 0;
}

// FUNCTION: GAME 0x004067b0
int VMCoreCustom::ISetInvisible(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 8;
    RHScript::SetInvisible(*(void **)(data + top - 8), *(int *)(data + size - 4) != 0);
    return 0;
}

// FUNCTION: GAME 0x004067e0
int VMCoreCustom::IIsInvisible(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return (unsigned char)RHScript::IsInvisible((void *)args[0]);
}

// FUNCTION: GAME 0x00406810
int VMCoreCustom::FUN_00406810(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return (unsigned char)RHScript::RHUnk579810((void *)args[0]);
}

// FUNCTION: GAME 0x00406840
int VMCoreCustom::FUN_00406840(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return (unsigned char)RHScript::RHUnk579820((void *)args[0]);
}

// FUNCTION: GAME 0x00406870
int VMCoreCustom::FUN_00406870(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return (unsigned char)RHScript::RHUnk579830((void *)args[0]);
}

// FUNCTION: GAME 0x004068a0
int VMCoreCustom::FUN_004068a0(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return (unsigned char)RHScript::RHUnk579840((void *)args[0]);
}

// FUNCTION: GAME 0x004068d0
int VMCoreCustom::FUN_004068d0(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 8;
    RHScript::RHUnk579850(*(void **)(data + top - 8), *(int *)(data + size - 4) != 0);
    return 0;
}

// FUNCTION: GAME 0x00406900
int VMCoreCustom::FUN_00406900(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 8;
    RHScript::RHUnk579870(*(void **)(data + top - 8), *(int *)(data + size - 4) != 0);
    return 0;
}

// FUNCTION: GAME 0x00406930
int VMCoreCustom::FUN_00406930(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 8;
    RHScript::RHUnk579880(*(void **)(data + top - 8), *(int *)(data + size - 4) != 0);
    return 0;
}

// FUNCTION: GAME 0x00406960
int VMCoreCustom::FUN_00406960(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 8;
    RHScript::RHUnk5798a0(*(void **)(data + top - 8), *(int *)(data + size - 4) != 0);
    return 0;
}

// FUNCTION: GAME 0x00406990
int VMCoreCustom::FUN_00406990(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 12;
    VMCoreCustomDependencies::FUN_005786f0(*(int *)(data + top - 12), *(int *)(data + top - 8), *(int *)(data + size - 4) != 0);
    return 0;
}

// FUNCTION: GAME 0x004069c0
int VMCoreCustom::IActivateDoorMouseSector(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 8;
    RHScript::ActivateDoorMouseSector(*(int *)(data + top - 8) != 0, *(void **)(data + size - 4));
    return 0;
}

// FUNCTION: GAME 0x004069f0
int VMCoreCustom::FUN_004069f0(VMNativeStack *)
{
    return (int)VMCoreCustomDependencies::FUN_005798c0();
}

// FUNCTION: GAME 0x00406a00
int VMCoreCustom::IGetScrollStatus(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return RHScript::GetScrollStatus((void *)args[0]);
}

// FUNCTION: GAME 0x00406a20
int VMCoreCustom::ISetScrollStatus(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 8;
    RHScript::SetScrollStatus(*(void **)(data + top - 8), *(int *)(data + size - 4));
    return 0;
}

// FUNCTION: GAME 0x00406a50
int VMCoreCustom::IGetCustomCampaignValue(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return RHScript::GetCustomCampaignValue(args[0]);
}

// FUNCTION: GAME 0x00406a70
int VMCoreCustom::ISetCustomCampaignValue(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 8;
    RHScript::SetCustomCampaignValue(*(int *)(data + top - 8), *(int *)(data + size - 4));
    return 0;
}

// FUNCTION: GAME 0x00406aa0
int VMCoreCustom::IGetCustomNPCValue(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 8;
    return RHScript::GetCustomNPCValue(*(void **)(data + top - 8), *(int *)(data + size - 4));
}

// FUNCTION: GAME 0x00406ad0
int VMCoreCustom::ISetCustomNPCValue(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 12;
    RHScript::SetCustomNPCValue(*(void **)(data + top - 12), *(int *)(data + top - 8), *(int *)(data + size - 4));
    return 0;
}

// FUNCTION: GAME 0x00406b00
int VMCoreCustom::FUN_00406b00(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 12;
    VMCoreCustomDependencies::FUN_005799d0(*(int *)(data + top - 12), *(int *)(data + top - 8), *(int *)(data + size - 4));
    return 0;
}

// FUNCTION: GAME 0x00406b30
int VMCoreCustom::FUN_00406b30(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 8;
    VMCoreCustomDependencies::FUN_00579a00(*(int *)(data + top - 8), *(int *)(data + size - 4));
    return 0;
}

// FUNCTION: GAME 0x00406b60
int VMCoreCustom::IGetActorForBeamMe(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return (int)RHScript::GetActorForBeamMe(args[0]);
}

// FUNCTION: GAME 0x00406b80
int VMCoreCustom::FUN_00406b80(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    RHScript::RHUnk579f30(args[0]);
    return 0;
}

// FUNCTION: GAME 0x00406bb0
int VMCoreCustom::IRecordDisplayPopupText(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    RHScript::RecordDisplayPopupText(args[0]);
    return 0;
}

// FUNCTION: GAME 0x00406be0
int VMCoreCustom::IGetNumberOfActorsInSector(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return RHScript::GetNumberOfActorsInSector((void *)args[0]);
}

// FUNCTION: GAME 0x00406c00
int VMCoreCustom::IGetActorInSector(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 8;
    return (int)RHScript::GetActorInSector(*(void **)(data + top - 8), *(int *)(data + size - 4));
}

// FUNCTION: GAME 0x00406c30
int VMCoreCustom::FUN_00406c30(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 8;
    return VMCoreCustomDependencies::FUN_0057a280(*(int *)(data + top - 8), *(int *)(data + size - 4));
}

// FUNCTION: GAME 0x00406c60
int VMCoreCustom::FUN_00406c60(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 8;
    return VMCoreCustomDependencies::FUN_0057a290(*(int *)(data + top - 8), *(int *)(data + size - 4));
}

// FUNCTION: GAME 0x00406c90
int VMCoreCustom::FUN_00406c90(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 8;
    return VMCoreCustomDependencies::FUN_0057a2a0(*(int *)(data + top - 8), *(int *)(data + size - 4));
}

// FUNCTION: GAME 0x00406cc0
int VMCoreCustom::IHasPCAction(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 8;
    return RHScript::HasPCAction(*(void **)(data + top - 8), *(int *)(data + size - 4));
}

// FUNCTION: GAME 0x00406cf0
int VMCoreCustom::IHasAnyPCAction(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return RHScript::HasAnyPCAction(args[0]);
}

// FUNCTION: GAME 0x00406d20
int VMCoreCustom::FUN_00406d20(VMNativeStack *)
{
    return (int)VMCoreCustomDependencies::FUN_0057a8e0();
}

// FUNCTION: GAME 0x00406d30
int VMCoreCustom::IRecordMoveNear(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 16;
    return RHScript::RecordMoveNear(*(void **)(data + top - 16), *(void **)(data + top - 12), *(int *)(data + top - 8), *(int *)(data + size - 4));
}

// FUNCTION: GAME 0x00406d70
int VMCoreCustom::IComputeLocationBetween(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 12;
    return (int)RHScript::ComputeLocationBetween(*(void **)(data + top - 12), *(void **)(data + top - 8), *(float *)(data + size - 4));
}

// FUNCTION: GAME 0x00406da0
int VMCoreCustom::IDeclareAsCombatTrainer(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    RHScript::DeclareAsCombatTrainer((void *)args[0]);
    return 0;
}

// FUNCTION: GAME 0x00406dd0
int VMCoreCustom::FUN_00406dd0(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return VMCoreCustomDependencies::FUN_0057a950(args[0]);
}

// FUNCTION: GAME 0x00406df0
int VMCoreCustom::FUN_00406df0(VMNativeStack *)
{
    return FUN_0057aa20();
}

// FUNCTION: GAME 0x00406e00
int VMCoreCustom::FUN_00406e00(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return VMCoreCustomDependencies::FUN_0057aa50(args[0]);
}

// FUNCTION: GAME 0x00406e20
int VMCoreCustom::IAddAsSubordinate(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 8;
    RHScript::AddAsSubordinate(*(void **)(data + top - 8), *(void **)(data + size - 4));
    return 0;
}

// FUNCTION: GAME 0x00406e50
int VMCoreCustom::IRemoveAllSubordinates(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    RHScript::RemoveAllSubordinates((void *)args[0]);
    return 0;
}

// FUNCTION: GAME 0x00406e80
int VMCoreCustom::ISwitchToAlertPath(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    RHScript::SwitchToAlertPath((void *)args[0]);
    return 0;
}

// FUNCTION: GAME 0x00406eb0
int VMCoreCustom::IIsActorRider(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return RHScript::IsActorRider((void *)args[0]);
}

// FUNCTION: GAME 0x00406ee0
int VMCoreCustom::IIsUnblipped(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return RHScript::IsUnblipped((void *)args[0]);
}

// FUNCTION: GAME 0x00406f10
int VMCoreCustom::IIsBlazonWon(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return RHScript::IsBlazonWon((void *)args[0]);
}

// FUNCTION: GAME 0x00406f40
int VMCoreCustom::IAddRepulsivePoint(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 16;
    return RHScript::AddRepulsivePoint(*(void **)(data + top - 16), *(float *)(data + top - 12), *(float *)(data + top - 8), *(int *)(data + size - 4));
}

// FUNCTION: GAME 0x00406f70
int VMCoreCustom::FUN_00406f70(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    VMCoreCustomDependencies::FUN_0057ae60(args[0]);
    return 0;
}

// FUNCTION: GAME 0x00406fa0
int VMCoreCustom::FUN_00406fa0(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    VMCoreCustomDependencies::FUN_00577df0(args[0] != 0);
    return 0;
}

// FUNCTION: GAME 0x00406fd0
int VMCoreCustom::FUN_00406fd0(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    VMCoreCustomDependencies::FUN_0057ae40(args[0]);
    return 0;
}

// FUNCTION: GAME 0x00407000
int VMCoreCustom::ISetNPCEmoticon(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 12;
    RHScript::SetNPCEmoticon(*(void **)(data + top - 12), *(int *)(data + top - 8), *(int *)(data + size - 4));
    return 0;
}

// FUNCTION: GAME 0x00407030
int VMCoreCustom::IConfiscateMoney(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    RHScript::ConfiscateMoney((void *)args[0]);
    return 0;
}

// FUNCTION: GAME 0x00407060
int VMCoreCustom::FUN_00407060(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return VMCoreCustomDependencies::FUN_00571e30(args[0]);
}

// FUNCTION: GAME 0x00407090
int VMCoreCustom::IAreAllEnemiesInsideHS(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return RHScript::AreAllEnemiesInsideHS((void *)args[0]);
}

// FUNCTION: GAME 0x004070c0
int VMCoreCustom::IAddPCToGang(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    RHScript::AddPCToGang((void *)args[0]);
    return 0;
}

// FUNCTION: GAME 0x004070f0
int VMCoreCustom::IAttachScrollToNPC(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 8;
    RHScript::AttachScrollToNPC(*(void **)(data + top - 8), *(void **)(data + size - 4));
    return 0;
}

// FUNCTION: GAME 0x00407120
int VMCoreCustom::FUN_00407120(VMNativeStack *)
{
    return (unsigned char)VMCoreCustomDependencies::FUN_00579690();
}

// FUNCTION: GAME 0x00407130
int VMCoreCustom::IIsBonusItemPickedUp(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return RHScript::IsBonusItemPickedUp((void *)args[0]);
}

// FUNCTION: GAME 0x00407160
int VMCoreCustom::IGetRansomMoney(VMNativeStack *stack)
{
    return RHScript::GetRansomMoney();
}

// FUNCTION: GAME 0x00407170
int VMCoreCustom::ISetRansomMoney(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    RHScript::SetRansomMoney(args[0]);
    return 0;
}

// FUNCTION: GAME 0x004071c0
int VMCoreCustom::IIsActorActive(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return (unsigned char)RHScript::IsActorActive((void *)args[0]);
}

// FUNCTION: GAME 0x004071a0
int VMCoreCustom::FUN_004071a0(VMNativeStack *)
{
    return VMCoreCustomDependencies::FUN_0057b150();
}

// FUNCTION: GAME 0x004071f0
int VMCoreCustom::FUN_004071f0(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 12;
    VMCoreCustomDependencies::FUN_0057b2b0(*(int *)(data + top - 12), *(int *)(data + top - 8), *(int *)(data + size - 4));
    return 0;
}

// FUNCTION: GAME 0x00407220
int VMCoreCustom::ISetExperiences(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 12;
    RHScript::SetExperiences(*(void **)(data + top - 12), *(int *)(data + top - 8), *(int *)(data + size - 4));
    return 0;
}

// FUNCTION: GAME 0x00407250
int VMCoreCustom::IRecordUnBlip(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return RHScript::RecordUnBlip((void *)args[0]);
}

// FUNCTION: GAME 0x00407280
int VMCoreCustom::FUN_00407280(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 8;
    VMCoreCustomDependencies::FUN_0057b350(*(int *)(data + top - 8), *(int *)(data + size - 4) != 0);
    return 0;
}

// FUNCTION: GAME 0x004072b0
int VMCoreCustom::FUN_004072b0(VMNativeStack *)
{
    return VMCoreCustomDependencies::FUN_0057b370();
}

// FUNCTION: GAME 0x004072c0
int VMCoreCustom::FUN_004072c0(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return VMCoreCustomDependencies::FUN_0057b3d0(args[0]);
}

// FUNCTION: GAME 0x004072f0
int VMCoreCustom::ITransformHandleTargetToTakeTarget(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    RHScript::TransformHandleTargetToTakeTarget((void *)args[0]);
    return 0;
}

// FUNCTION: GAME 0x00407320
int VMCoreCustom::IIsPCSelected(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return RHScript::IsPCSelected((void *)args[0]);
}

// FUNCTION: GAME 0x00407350
int VMCoreCustom::FUN_00407350(VMNativeStack *)
{
    return VMCoreCustomDependencies::FUN_0057b5e0();
}

// FUNCTION: GAME 0x00407360
int VMCoreCustom::IGetSelectedPC(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return (int)RHScript::GetSelectedPC(args[0]);
}

// FUNCTION: GAME 0x00407380
int VMCoreCustom::FUN_00407380(VMNativeStack *)
{
    VMCoreCustomDependencies::FUN_0057b780();
    return 0;
}

// FUNCTION: GAME 0x00407390
int VMCoreCustom::IMakePCCrouched(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    RHScript::MakePCCrouched((void *)args[0]);
    return 0;
}

// FUNCTION: GAME 0x004073c0
int VMCoreCustom::IHasAnyPCActionWhoIsInThisLevelOrCouldMaybeComeFromSherwood(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return RHScript::HasAnyPCActionWhoIsInThisLevelOrCouldMaybeComeFromSherwood(args[0]);
}

// FUNCTION: GAME 0x004073f0
int VMCoreCustom::FUN_004073f0(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 8;
    VMCoreCustomDependencies::FUN_0057ba50(*(int *)(data + top - 8), *(int *)(data + size - 4) != 0);
    return 0;
}

// FUNCTION: GAME 0x00407420
int VMCoreCustom::IHasAnyActivePCAction(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return RHScript::HasAnyActivePCAction(args[0]);
}

// FUNCTION: GAME 0x00407450
int VMCoreCustom::IGetPCType(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return RHScript::GetPCType((void *)args[0]);
}

// FUNCTION: GAME 0x00407470
int VMCoreCustom::ISelectActorPC(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 8;
    RHScript::SelectActorPC(*(void **)(data + top - 8), *(int *)(data + size - 4) != 0);
    return 0;
}

// FUNCTION: GAME 0x004074a0
int VMCoreCustom::IHasAnyActionSelected(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return RHScript::HasAnyActionSelected((void *)args[0]);
}

// FUNCTION: GAME 0x004074d0
int VMCoreCustom::IGetActorActionState(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    return RHScript::GetActorActionState((void *)args[0]);
}

// FUNCTION: GAME 0x004074f0
int VMCoreCustom::ISetActorActionState(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 8;
    RHScript::SetActorActionState(*(void **)(data + top - 8), *(int *)(data + size - 4));
    return 0;
}

// FUNCTION: GAME 0x00407520
int VMCoreCustom::FUN_00407520(VMNativeStack *)
{
    return VMCoreCustomDependencies::FUN_0057bfe0();
}

// FUNCTION: GAME 0x00407530
int VMCoreCustom::FUN_00407530(VMNativeStack *stack)
{
    int *args = (int *)(stack->m_data + stack->m_size) - 1;
    stack->m_size -= 4;
    VMCoreCustomDependencies::FUN_0057bff0(args[0]);
    return 0;
}

// FUNCTION: GAME 0x00407560
int VMCoreCustom::ILinkTargetToFX(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 8;
    RHScript::LinkTargetToFX(*(void **)(data + top - 8), *(void **)(data + size - 4));
    return 0;
}

// FUNCTION: GAME 0x00407590
int VMCoreCustom::IForbidNPCRemark(VMNativeStack *stack)
{
    int size = stack->m_size;
    char *data = stack->m_data;
    int top = stack->m_size;
    stack->m_size -= 12;
    RHScript::ForbidNPCRemark(*(void **)(data + top - 12), *(int *)(data + top - 8), *(int *)(data + size - 4) != 0);
    return 0;
}
