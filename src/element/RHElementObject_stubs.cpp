// Stub definitions for the external symbols RHElementObject.cpp calls.
//
// These are NOT decompiled implementations; they only give the linker a local
// target so the calls in RHElementObject::Serialize are direct `call rel32`
// (matching the original shape) instead of unresolved externals. They live in a
// separate translation unit so VC6 cannot inline them into the matched
// function.
//
// SBFile::Access / SBFile::GetError / SBAssert are already defined once, in
// RHSword_stubs.cpp; both TUs just declare them (include/SB.h).

#include "SBNullstr.h"
#include "RHElementObject.h"

#include "RHObjectConstructorCalls.h"

RHObjectConstructorCalls::RHObjectConstructorCalls(unsigned long, bool, int)
{
}

RHObjectConstructorCalls::~RHObjectConstructorCalls()
{
}


#include "SBGeoPoint2D.h"
#include "RHActorSequenceStorage.h"

// FUNCTION: GAME 0x0045abc0
bool RHUnk0045aaf0::FUN_0045abc0(unsigned short value, int first, int second)
{
    bool result = *(int *)((char *)this + 4) == 0;
    *(unsigned short *)((char *)this + 8) = value;
    *(int *)((char *)this + 0xc) = first;
    *(int *)((char *)this + 4) = 1;
    *(int *)((char *)this) = second;
    return result;
}

// FUNCTION: GAME 0x0045abf0
bool RHUnk0045aaf0::FUN_0045abf0(unsigned short value, const SBGeoPoint2D &point, int third, int fourth)
{
    bool result = *(int *)((char *)this + 4) == 0;
    *(int *)((char *)this + 4) = 4;
    m_24 = 1;
    m_2c = value;
    m_30 = third;
    m_34 = point;
    *(int *)((char *)this) = fourth;
    return result;
}



// The nested sub-object serialiser at RHElementObject+0xbc (target 0x00521210)
// is now the real RHUnk004b2190Member::Serialize defined in src/RHLine.cpp; the
// declaration stays in include/RHElementObject.h.
