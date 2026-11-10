#ifndef RHACTORTRANSLATION_H
#define RHACTORTRANSLATION_H

#include <new>

template <class T>
inline T &RHActorField(void *object, int offset)
{
    return *(T *)((char *)object + offset);
}

#include "RHOrderCore.h"

#include "RHActorTranslationSequenceCalls.h"

#endif
