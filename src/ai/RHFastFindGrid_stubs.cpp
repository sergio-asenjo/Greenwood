#include "SBNullstr.h"
#include "RHFastFindGrid.h"

typedef std::vector<void *> RHFastFindPointerVector;

bool RHFastFindGrid::IsReachableImpact(const RHUnk00613e90 &, const RHUnk00613e90 &, RHUnk00613e90 &, void *&, int)
{
    return false;
}

// FUNCTION: GAME 0x0051e630
void *RHUnk0051e5e0::FUN_0051e630(unsigned flags)
{
    this->RHUnk0051e5e0::~RHUnk0051e5e0();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x0051e650
RHUnk0051e5e0::~RHUnk0051e5e0()
{
    *(unsigned long *)this = 0x006790c8;
    RHFastFindPointerVector *second = (RHFastFindPointerVector *)((char *)this + 0x78);
    second->clear();
    second->~RHFastFindPointerVector();
    RHFastFindPointerVector *lines = (RHFastFindPointerVector *)&m_lines;
    lines->clear();
    lines->~RHFastFindPointerVector();
    ((RHSector *)this)->RHSector::~RHSector();
}



// FUNCTION: GAME 0x0051f450
float RHFastFindLine::FUN_0051f450() { return ((float *)m_00)[1] > ((float *)m_00)[3] ? ((float *)m_00)[1] : ((float *)m_00)[3]; }
// FUNCTION: GAME 0x0051f470
float RHFastFindLine::FUN_0051f470() { return ((float *)m_00)[1] > ((float *)m_00)[3] ? ((float *)m_00)[3] : ((float *)m_00)[1]; }
// FUNCTION: GAME 0x0051f490
float RHFastFindLine::FUN_0051f490() { return ((float *)m_00)[2] > ((float *)m_00)[4] ? ((float *)m_00)[4] : ((float *)m_00)[2]; }
// FUNCTION: GAME 0x0051f4b0
float RHFastFindLine::FUN_0051f4b0() { return ((float *)m_00)[2] > ((float *)m_00)[4] ? ((float *)m_00)[2] : ((float *)m_00)[4]; }
bool RHFastFindSegmentCalls::FUN_0060a990(const RHMalignitySegment &) { return false; }

DECOMP_SIZE_ASSERT(RHUnk0051a5e0, 0x94)
DECOMP_SIZE_ASSERT(RHUnk0051aa00, 0xbc)
DECOMP_SIZE_ASSERT(RHUnk005209d0, 0x14)
DECOMP_SIZE_ASSERT(RHUnk00520ae0, 0x40)

// FUNCTION: GAME 0x0060ad50
bool RHMalignitySegment::FUN_0060ad50(const SBGeoBoundingBox2D &box)
{
    return box.FUN_00608650((const RHMobileUnk006100e0 &)*this);
}


void RHFastFindGrid::FUN_004faf40(SBFile &) {}
void RHFastFindGrid::FUN_004fb230(SBFile &) {}
void RHFastFindGrid::FUN_004e8bd0(void *, unsigned short, bool) {}
void RHFastFindSector::UnkSlot0() {}
void RHFastFindSector::UnkSlot4() {}
void RHFastFindSector::UnkSlot8() {}
void RHFastFindSector::UnkSlotc() {}
void RHFastFindSector::UnkSlot10(SBFile &, RHFastFindGrid *) {}

// FUNCTION: GAME 0x00520a90
void RHUnk00522470::FUN_00520a90(SBFile &file)
{
    short x;
    short y;
    file.Access(&x, 2);
    file.Access(&y, 2);
    *(float *)(m_00 + 4) = x;
    *(float *)(m_00 + 8) = y;
}
RHSectorScript::RHSectorScript() {}
RHSectorScript::~RHSectorScript() {}
void RHFastFindGrid::FUN_004e99e0(void *, unsigned short, bool) {}
void RHUnk0051e1e0::Unk0051e230(SBFile &, RHSeqList &) {}
RHUnk0051b6e0::RHUnk0051b6e0(RHUnk0051e1e0 *, RHUnk0051e1e0 *) {}
RHUnk0051b6e0::~RHUnk0051b6e0() {}
RHUnk005a3450::RHUnk005a3450() {}
RHUnk005a3450::RHUnk005a3450(int) {}
RHUnk005a3450::~RHUnk005a3450() {}
void RHUnk005a3450::Unk005a3810(SBFile &, RHFastFindPointerArray &) {}
void *RHUnk005a3450::Unk005a5780() { return 0; }
SBGeoPoint3D::SBGeoPoint3D(float, float, float) {}
void RHFastFindGrid::FUN_004ef8e0(RHUnk005a3450 *, unsigned short, bool) {}
void RHUnk0054f870::Unk00550220() {}
RHUnk004b2190Member::RHUnk004b2190Member() {}
RHUnk004b2190Member::~RHUnk004b2190Member() {}
void SBArray<RHUnk004b2190Member>::Insert(RHUnk004b2190Member *, unsigned int, const RHUnk004b2190Member &) {}
void SBArray<unsigned short>::Insert(unsigned short *, unsigned int, const unsigned short &) {}
// FUNCTION: GAME 0x005223f0
void RHUnk005223f0::FUN_005223f0(SBFile &file)
{
    short x;
    short y;
    file.Access(&x, 2);
    file.Access(&y, 2);
    *(float *)this = (float)x;
    *(float *)((char *)this + 4) = (float)y;
    ((RHUnkPathGeometry *)g_unk0x6c0a9c)->Unk004fbec0(file, *(void **)((char *)this + 8));
    file.Access((char *)this + 0xc, 2);
    file.Access((char *)this + 0x10, 2);
}
void FUN_00418390(RHUnk005223f0 *) {}
// FUNCTION: GAME 0x005209d0
RHUnk005209d0::RHUnk005209d0(int type)
{
    *(unsigned *)this = 0x678b58;
    m_0c = type;
    m_10 = 1;
}

// FUNCTION: GAME 0x00520a00
RHUnk005209d0::RHUnk005209d0(SBGeoPoint2D point, int type) : SBGeoPoint2D(point)
{
    *(unsigned *)this = 0x678b58;
    m_0c = type;
    m_10 = 1;
}

// FUNCTION: GAME 0x00520a70
RHUnk005209d0::~RHUnk005209d0()
{
    *(unsigned *)this = 0x678b58;
}
// FUNCTION: GAME 0x0051a5e0
RHUnk0051a5e0::RHUnk0051a5e0()
{
    *(int *)m_04 = 0;
}
RHUnk0051a5e0::~RHUnk0051a5e0() {}
RHUnk0051aa00::~RHUnk0051aa00() {}

bool RHUnk0051a5e0::FUN_0051abe0(bool, RHElementActor *, bool, bool, bool) { return false; }
bool RHUnk0051a5e0::Serialize(SBFile &) { return true; }

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

class RHScriptBatchCalls
{
public:
    bool Unk0049d560(int action);
};

// FUNCTION: GAME 0x0051b870
bool RHUnk0051aa00::FUN_0051b870(bool first, RHElementActor *actor, bool second, bool third, bool)
{
    if ((*(unsigned *)((char *)actor + 0x4) & 0xf) != 0xc ||
        !((RHScriptBatchCalls *)actor)->Unk0049d560(0x16))
        return false;
    if (first)
    {
        if (*(char *)(*(char **)((char *)this + 0x88) + 0x39))
            goto check;
    }
    else if (*(char *)(*(char **)((char *)this + 0x8c) + 0x39))
        goto check;
    return true;
check:
    if (second)
        return *(int *)(*(char **)((char *)actor + 0x50) + 0x8c) == 0x10;
    return third;
}

// FUNCTION: GAME 0x0057cd50
bool RHUnk0051aa00::FUN_0057cd50(undefined4) { return true; }

struct RHFastFindRecordC0;
struct RHFastFindRecordA0;
void FUN_004fe9d0(RHFastFindRecordC0 *, const RHFastFindRecordC0 &) {}
void FUN_004feb10(RHFastFindRecordA0 *, const RHFastFindRecordA0 &) {}
