#include "SBNullstr.h"
#include "RHFastFindGrid.h"

DECOMP_SIZE_ASSERT(RHUnk0051a5e0, 0x94)
DECOMP_SIZE_ASSERT(RHUnk0051aa00, 0xbc)
DECOMP_SIZE_ASSERT(RHUnk005209d0, 0x14)
DECOMP_SIZE_ASSERT(RHUnk00520ae0, 0x40)

void RHFastFindGrid::FUN_004faf40(SBFile &) {}
void RHFastFindGrid::FUN_004fb230(SBFile &) {}
RHUnk0057e4d0::RHUnk0057e4d0() {}
RHUnk0057e4d0::~RHUnk0057e4d0() {}
void RHFastFindGrid::FUN_004e8bd0(void *, unsigned short, bool) {}
void RHFastFindSector::UnkSlot0() {}
void RHFastFindSector::UnkSlot4() {}
void RHFastFindSector::UnkSlot8() {}
void RHFastFindSector::UnkSlotc() {}
void RHFastFindSector::UnkSlot10(SBFile &, RHFastFindGrid *) {}
void RHUnk00522470::FUN_00520a90(SBFile &) {}
RHSectorScript::RHSectorScript() {}
RHSectorScript::~RHSectorScript() {}
void RHFastFindGrid::FUN_004ebfe0(RHUnk00522470 *, unsigned short, bool) {}
void RHFastFindGrid::FUN_004e99e0(void *, unsigned short, bool) {}
void RHUnk0051e5e0::FUN_0057ca80() {}
RHUnk0051e5e0::~RHUnk0051e5e0() {}
void RHUnk0051e1e0::FUN_0051f0f0() {}
RHUnk0051e1e0::~RHUnk0051e1e0() {}
void RHUnk0051e1e0::Unk0051e230(SBFile &, RHSeqList &) {}
RHUnk0051b6e0::RHUnk0051b6e0(RHUnk0051e1e0 *, RHUnk0051e1e0 *) {}
RHUnk0051b6e0::~RHUnk0051b6e0() {}
void RHFastFindGrid::FUN_004ed690(void *, unsigned short, bool) {}
RHUnk005a3450::RHUnk005a3450() {}
RHUnk005a3450::RHUnk005a3450(int) {}
RHUnk005a3450::~RHUnk005a3450() {}
void RHUnk005a3450::Unk005a3810(SBFile &, RHFastFindPointerArray &) {}
void *RHUnk005a3450::Unk005a5780() { return 0; }
SBGeoPoint3D::SBGeoPoint3D(float, float, float) {}
void RHUnk005df860::FUN_005df8b0() {}
void RHUnk005df860::FUN_005df900() {}
void RHUnk005df860::FUN_005df9a0() {}
void RHUnk005df860::FUN_005df9c0() {}
void RHFastFindGrid::FUN_004ef8e0(RHUnk005a3450 *, unsigned short, bool) {}
void RHUnk0054f870::Unk00550220() {}
RHUnk004b2190Member::RHUnk004b2190Member() {}
RHUnk004b2190Member::~RHUnk004b2190Member() {}
void SBArray<RHUnk004b2190Member>::Insert(RHUnk004b2190Member *, unsigned int, const RHUnk004b2190Member &) {}
void SBArray<unsigned short>::Insert(unsigned short *, unsigned int, const unsigned short &) {}
void RHUnk005223f0::FUN_005223f0(SBFile &) {}
void FUN_00418390(RHUnk005223f0 *) {}
void RHUnk004ff7b0::FUN_004ff7b0(unsigned int, const float &) {}
RHUnk005209d0::RHUnk005209d0(int) {}
RHUnk005209d0::~RHUnk005209d0() {}
RHUnk0051a5e0::RHUnk0051a5e0() {}
RHUnk0051a5e0::~RHUnk0051a5e0() {}
RHUnk0051aa00::~RHUnk0051aa00() {}

bool RHUnk0051a5e0::FUN_0051abe0(bool, RHElementActor *, bool, bool, bool) { return false; }
bool RHUnk0051a5e0::Serialize(SBFile &) { return true; }

// STUB: GAME 0x0051abe0
bool RHUnk0051aa00::FUN_0051abe0(bool, RHElementActor *, bool, bool, bool) { return false; }

// The target annotation remains owned by RHGate::Serialize.
bool RHUnk0051aa00::Serialize(SBFile &file)
{
    RHSerializeName(file, "RHDoor");
    if (file.Access(&m_8c[0], 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHGate.cpp", 413, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_8c[1], 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHGate.cpp", 414, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_8c[2], 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHGate.cpp", 415, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_8c[3], 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHGate.cpp", 416, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_b4[0], 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHGate.cpp", 418, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_b4[2], 2) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHGate.cpp", 419, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_b4[4], 2) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHGate.cpp", 420, "Serialize failed reason is %s", reason);
        return false;
    }
    return true;
}

// STUB: GAME 0x0051b870
bool RHUnk0051aa00::FUN_0051b870(bool, RHElementActor *, bool, bool, bool) { return false; }

// FUNCTION: GAME 0x0057cd50
bool RHUnk0051aa00::FUN_0057cd50(undefined4) { return true; }
