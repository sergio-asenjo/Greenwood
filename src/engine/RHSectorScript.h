#ifndef RHSECTORSCRIPT_H
#define RHSECTORSCRIPT_H

#include "RHSectorCore.h"
#include "VMCoreCustom.h"
#include "RHMotionAreaList.h"

class SBFile;
class RHElementActor;

class RHObjectScript
{
public:
    char m_active;
    int m_unk04;
    char *m_unk08;
};

class RHUnkSectorScriptRef
{
public:
    RHUnkSectorScriptRef() : m_0(0) {}
    int Unk004089f0(RHElementActor *actor);
    int Unk00408af0(RHElementActor *actor);
    int Unk00408900();
    void *m_0;
};

// VTABLE: GAME 0x00679cb0
// VTABLE: GAME 0x00679cc0 SBSimpleVirtualMachine
// VTABLE: GAME 0x00679cac RHScript
// SIZE 0xf8
class RHSectorScript : public RHSector, public RHObjectScript, public RHUnkSectorScriptRef, public VMCoreCustom
{
public:
    RHSectorScript();
    virtual ~RHSectorScript();
    bool FUN_0057ff00(RHElementActor *actor);
    void Enter(RHElementActor *actor);
    void Leave(RHElementActor *actor);
    void InitializeFromMissionStream(SBFile &file);
    virtual bool Serialize(SBFile &file);
    void Emit(RHElementActor *actor);
    void Emit(SBFile &file);

    unsigned short m_c8;
    char m_padca[2];
    RHMotionAreaList<RHElementActor *> m_cc;
    char m_padf0[4];
    int m_f4;
};

#endif
