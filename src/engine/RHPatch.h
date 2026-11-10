#ifndef RHPATCH_H
#define RHPATCH_H

#include "RHSector.h"
#include "RHEngine.h"
#include "RHPatchClass.h"

class RHProfileFile
{
public:
    int FUN_005f5370(int offset, int origin);
};

class RHSequenceElement;
class RHSeqList
{
public:
    static void CopyData(RHSequenceElement **destination, RHSequenceElement *const *source);
};

#include "RHScriptListCore.h"

struct RHTitbitNode;
#include "RHTitbitsCore.h"

class RHPatchVirtualCalls
{
public:
    virtual void Slot0();
    virtual void Slot1();
    virtual void Slot2();
    virtual void Slot3();
    virtual void Slot4();
    virtual void Slot5();
    virtual void Slot6();
    virtual void Slot7();
    virtual void Slot8();
    virtual void Slot9();
    virtual void Slot10();
    virtual void Slot11();
    virtual void Slot12();
    virtual void Slot13();
    virtual void Slot14();
    virtual void Slot15();
    virtual void Slot16(SBFile &file);
};

class RHPatchDoorCalls
{
public:
    void FUN_0051b660();
};

extern RHEngine *g_pEngine;

#endif
