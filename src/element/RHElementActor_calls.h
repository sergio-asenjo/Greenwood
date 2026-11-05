#ifndef RHELEMENTACTOR_CALLS_H
#define RHELEMENTACTOR_CALLS_H

#include "SB.h"
#include <string>
#include <memory.h>
#include <iterator>
#include <new>
#include "RHActorTranslation.h"

#include "SBGeoPoint2D.h"
#include "SBGeoVector2D.h"
#include "RHPositionInterface.h"

#include "RHTripleVectorCalls.h"

struct RHScriptNode
{
    RHScriptNode *next;
    RHScriptNode *previous;
    void *data;
};
struct RHScriptIter
{
    RHScriptNode *node;
    RHScriptIter(RHScriptNode *value) : node(value) {}
    RHScriptIter operator++(int);
};
class RHUnk0046eb30
{
public:
    RHScriptIter FUN_0046eb80();
    RHScriptIter erase(RHScriptIter position);
};

#include "RHTransientPointerList.h"
typedef RHTransientPointerList<void> RHActorTransientList;

#include "RHActorElementBase.h"

class RHEngine
{
public:
    bool SerializeElementPointer(SBFile &file, RHElement *&element);
};
class RHReconnaissanceEngine
{
public:
    bool Unk004c3cb0(SBFile &file, void *&value);
};
class RHOrder;
class RHSequenceElement
{
public:
    virtual void Unk0();
    virtual void Unk1();
    virtual void Unk2();
    virtual void FUN_00585970(void *value, bool flag);
    int Unk00587160(int argument);
    char m_4[0xc];
    int m_10;
    char m_14[0x58];
    SBGeoPoint2D m_6c;
};
class RHSequenceManager
{
public:
    bool PreSerializePointer(SBFile &file, RHOrder **order);
    bool PreSerializePointer(SBFile &file, RHSequenceElement **element, bool launch);
    bool FUN_0058bd70(void *actor, int command);
};
class RHSequence
{
public:
    bool Serialize(SBFile &file, bool loading);
};
#include "RHSequenceConstructionCalls.h"
struct RHUnkSectorGlobal;
extern RHEngine *g_pEngine;
extern RHUnkSectorGlobal *g_unk0x6c0a9c;
void RHSerializeName(SBFile &file, const char *name);
bool FUN_005e0c90(SBFile &file, std::string &value);

#include "RHActorPointList.h"

#include "RHActorString.h"

#include "RHUnkSectorScript.h"

#include "RHActorScriptContext.h"

struct RHBonusProjection;

class RHBonusInfoBase
{
public:
    char FUN_004671d0() const;
    void FUN_004671e0(char value);
    SBGeoVector2D FUN_00468f10(int value) const;
    void FUN_0055f290();
    void FUN_0055fa20(RHBonusProjection *projection);
    void FUN_0055fa70(void *area);
    void FUN_00462970(int action);
    void SetFlagFd() { *((char *)this + 0xfd) = 1; }
    void ResetTarget(const SBGeoPoint2D &point)
    {
        *(SBGeoPoint2D *)((char *)this + 0x44) = point;
        *(int *)((char *)this + 8) = 0;
    }
};
class RHBonusInfo
{
public:
    void FUN_005bd560(void *value, bool flag);
    void FUN_005bd650(int value1, int value2);
    void FUN_005bd7b0(int value);
};
class RHElementActor;

#include "RHActorGridCalls.h"
class RHElementActor;

#include "RHActorAreaCalls.h"
class RHElementActor;
#include "RHTitbitsCore.h"
class RHScriptBatchCalls
{
public:
    void Unk0040d980(int stimulus);
    void Unk0046bcf0(int posture, int value);
    void Unk0046bd10(int state);
    void Unk00464630();
    void Unk0046b9e0();
    void *Unk0058a940(void *context, int value, void *element);
};
extern RHTitbits *g_unk0x6c10e8;
extern RHElementActor *g_unk0x6c100c;
extern float g_actorStepScale;


#include "RHActorPositionCalls.h"

class RHMobileSegment
{
public:
    RHMobileSegment(const SBGeoPoint2D &first, const SBGeoPoint2D &second);
    ~RHMobileSegment();
    SBGeoPoint2D first;
    SBGeoPoint2D second;
};

class RHMobileGrid
{
public:
    void FUN_004ed370(void *lines, unsigned short layer, const RHMobileSegment &segment, unsigned mask);
};

class RHElevationLine
{
public:
    char m_00[4];
    SBGeoPoint2D m_04;
    SBGeoPoint2D m_0c;
    unsigned m_14;
    char m_18[0xc];
    void *m_24;
    void *m_28;
};

#include "RHActorCrossingHumanCalls.h"

#include "RHElementAreaShape.h"

class RHPatch
{
public:
    void Enter(RHElementActor *actor);
    void Leave(RHElementActor *actor);
    void FUN_00550150();
};

#include "RHSectorScript.h"

void __stdcall FUN_0048a970(RHElementActor *actor);

struct RHActorEngineFlags
{
    char m_0[0x4d98];
    unsigned m_4d98;
};

enum RHActorUnkType { RHActorUnkType12 = 12 };

#include "RHActorCancelCalls.h"

class RHUnk0058a3d0
{
public:
    void *Unk(void *context, int value, void *sequence);
};


extern char g_unk0x6c0691;

class RHActorSequenceCursor
{
public:
    RHOrder *FUN_005855a0();
    virtual void V00();
    virtual void V04();
    virtual void V08();
    virtual void V0c(int first, int second);
};

#endif
