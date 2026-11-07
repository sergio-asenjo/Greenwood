#ifndef RHSCRIPTACTORARRAY_H
#define RHSCRIPTACTORARRAY_H

#include <vector>

class RHPCDescription;

// SIZE 0x20
class RHScriptActorArray : public std::vector<void *>
{
public:
    RHScriptActorArray() : dirty(true) {}
    void **&First() { return _First; }
    void **&Last() { return _Last; }
    void Resize(unsigned count);
    void Remove(unsigned index);
    void **current; // 0x10
    bool dirty; // 0x14
    bool found; // 0x15
    int index; // 0x18
    void *value; // 0x1c
};

#include "RHScriptStaticStorage.h"
#define g_unk0x6c0f30 (*(RHScriptActorArray *)&RHScriptStaticStorage::marrayElementsScript)
bool FUN_00570850(void *actor);
void FUN_00570900(void *actor);

#endif
