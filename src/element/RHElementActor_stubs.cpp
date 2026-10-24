#include "SBNullstr.h"
#include "RHElementActor.h"

extern int g_unk0x6c0c6c;


void RHUnk0060fbf0::FUN_0060fa20() {}
void RHUnk0060fbf0::FUN_0060fa30(const RHUnk0060fbf0 &) {}


void RHActorString::FUN_00402780() {}
bool RHActorString::FUN_00402280(unsigned, bool) { return true; }
// Parked: multi-view (no marker). SBFile::GetError and RHProfileString call this
// address as std::basic_string<...>::_Eos; any marker here demotes 26 prior
// exacts. Body: *(unsigned*)(this+8)=size; ((char*)m_4)[size]=0.
void RHActorString::FUN_00402260(unsigned) {}
void RHActorString::FUN_00401ee0(bool) {}

// LIBRARY: GAME 0x006416e6
// ?_Xran@std@@YAXXZ

// VTABLE: GAME 0x0067bd40
// class std::out_of_range

// STRING: GAME 0x0067bd4c
// "invalid string position"

// Throw-info data; bound by name only.
// STUB: GAME 0x0068ade8 SYMBOL
// __TI3?AVout_of_range@std@@

// LIBRARY: GAME 0x00642580
extern "C" void *memmove(void *destination, const void *, size_t) { return destination; }

// FUNCTION: GAME 0x006090d0
SBGeoBoundingBox2D SBGeoBoundingBox2D::FUN_006090d0(const SBGeoVector2D &offset) const
{
    return SBGeoBoundingBox2D(m_0.Unk005fc190(offset), m_8.Unk005fc190(offset));
}
RHScriptIter RHScriptIter::operator++(int) { return RHScriptIter(node); }
short RHActorGridCalls::FUN_004e8fc0(const SBGeoPoint2D &, const SBGeoPoint2D &, short, void *&) { return -1; }
bool RHActorGridCalls::FUN_004f5e50(SBGeoPoint2D &, const SBGeoPoint2D &, int) { return false; }
void *RHActorAreaCalls::FUN_0057d800(const SBGeoPoint2D &) { return 0; }
void RHElementActor::FUN_0046bcb0(int) {}

bool RHActorCrossingHumanCalls::FUN_004843d0(SBGeoPoint2D &, void *, bool) { return false; }
// FUNCTION: GAME 0x0054e730
void RHOrder::FUN_0054e730()
{
    *(int *)((char *)this + 0x34) = g_unk0x6c0c6c++;
}

// FUNCTION: GAME 0x005fc390
void SBGeoPoint2D::FUN_005fc390(const SBGeoPoint2D &other) throw()
{
    m_0 = other.m_0;
    m_4 = other.m_4;
}

// FUNCTION: GAME 0x005df4f0
RHUnk00613e90::RHUnk00613e90(float x, float y, float z)
{
    m_0 = x;
    m_4 = y;
    m_8 = z;
}

// FUNCTION: GAME 0x00468f10
SBGeoVector2D RHBonusInfoBase::FUN_00468f10(int value) const
{
    const SBGeoVector2D *point =
        (const SBGeoVector2D *)((const char *)((RHUnkPathActorInfoBase *)this)->Unk0055fa10(value) + 8);
    return *point;
}

RHOrder *RHActorSequenceCursor::FUN_005855a0()
{
    return 0;
}
float RHActorDistanceCalls::FUN_0060cab0(const SBGeoPoint2D &, float) { return 0.0f; }
