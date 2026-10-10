#include "SBNullstr.h"
#include "RHSequenceElementGeneric.h"

RHGenericInsertResult RHGenericMap::FUN_005873a0(const RHGenericPair &)
{
    return RHGenericInsertResult(RHGenericIterator(head), false);
}

RHGenericIterator RHGenericMap::FUN_005874d0(RHGenericIterator, RHGenericIterator last)
{
    return last;
}

RHGenericIterator &RHGenericIterator::FUN_00587ed0()
{
    return *this;
}
