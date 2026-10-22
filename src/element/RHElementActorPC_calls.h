#ifndef RHELEMENTACTORPC_CALLS_H
#define RHELEMENTACTORPC_CALLS_H

#include "RHElementBonus.h"
#include "RHMessage.h"
#include "RHActorMessage.h"
#include "Decomp.h"
#include <string>
#include <vector>
#include <string.h>

#include "RHUnk00613e90.h"

class RHScriptBatchCalls
{
public:
    void *Unk0058a940(void *context, int value, void *element);
    bool Unk0049d560(int action);
    void Unk0049d6c0();
    void Unk00464630();
    void Unk0046bcf0(int state, int value);
    void Unk00485200(int index, int amount);
    int Unk005c2ec0(void *position, int first, int second, void *actor, int third, int fourth, int fifth, int sixth);
    void Unk0048ec00(void *scroll);
};

class RHActorPCVTableCalls
{
public:
    virtual void FUN_0() = 0;
    virtual void FUN_1() = 0;
    virtual void FUN_2() = 0;
    virtual void FUN_3() = 0;
    virtual void FUN_4() = 0;
    virtual void FUN_5() = 0;
    virtual void FUN_6() = 0;
    virtual void FUN_7() = 0;
    virtual void FUN_8() = 0;
    virtual void FUN_9() = 0;
    virtual void FUN_10() = 0;
    virtual void FUN_11() = 0;
    virtual void FUN_12() = 0;
    virtual void FUN_13() = 0;
    virtual void FUN_14() = 0;
    virtual void FUN_15() = 0;
    virtual void FUN_16() = 0;
    virtual void FUN_17(int command) = 0;
    virtual bool FUN_0049e720() = 0;
    virtual void FUN_19() = 0;
    virtual void FUN_20() = 0;
    virtual void FUN_21() = 0;
    virtual void FUN_22() = 0;
    virtual void FUN_23() = 0;
    virtual void FUN_24() = 0;
    virtual void FUN_25() = 0;
    virtual void FUN_26() = 0;
    virtual void FUN_27() = 0;
    virtual void FUN_28(unsigned amount) = 0;
    virtual void FUN_29() = 0;
    virtual void FUN_30() = 0;
    virtual void FUN_31() = 0;
    virtual void FUN_32() = 0;
    virtual void FUN_33() = 0;
    virtual void FUN_34(const RHUnk00613e90 &point, const RHUnk00613e90 &direction) = 0;
    virtual void FUN_35() = 0;
    virtual void FUN_36() = 0;
    virtual void FUN_37() = 0;
    virtual void FUN_38() = 0;
    virtual void FUN_39() = 0;
    virtual void FUN_40() = 0;
    virtual void FUN_41() = 0;
    virtual void FUN_42() = 0;
    virtual void FUN_43() = 0;
    virtual void FUN_44() = 0;
    virtual void FUN_45() = 0;
    virtual void FUN_46() = 0;
    virtual void FUN_47() = 0;
    virtual void FUN_48() = 0;
    virtual void FUN_49() = 0;
    virtual void FUN_50() = 0;
    virtual short FUN_51() = 0;
    virtual void FUN_52() = 0;
    virtual void FUN_slot53(int, int, int) = 0;
    virtual void FUN_slot54() = 0;
    virtual void FUN_slot55(int, int, int) = 0;
    virtual void FUN_56(int, int, int) = 0;
    virtual unsigned short FUN_57(unsigned action) = 0;
    virtual void FUN_58(unsigned action, unsigned amount) = 0;
    virtual void FUN_59() = 0;
    virtual void FUN_60() = 0;
    virtual void FUN_61() = 0;
    virtual bool FUN_62() = 0;
    virtual void FUN_63() = 0;
    virtual void FUN_64() = 0;
    virtual void FUN_slot65(int, int, int) = 0;
    virtual bool FUN_slot66(void *element, void *target) = 0;
    virtual void FUN_67() = 0;
    virtual void FUN_68() = 0;
    virtual void FUN_69() = 0;
    virtual void FUN_70() = 0;
    virtual void FUN_71() = 0;
    virtual void FUN_72() = 0;
    virtual void FUN_73() = 0;
    virtual void FUN_74() = 0;
    virtual void FUN_75() = 0;
    virtual void FUN_76() = 0;
    virtual void FUN_77() = 0;
    virtual void FUN_78() = 0;
    virtual void FUN_79() = 0;
    virtual void FUN_80() = 0;
    virtual void FUN_81() = 0;
    virtual void FUN_82() = 0;
    virtual void FUN_83() = 0;
    virtual void FUN_84() = 0;
    virtual void FUN_85() = 0;
    virtual void FUN_86() = 0;
    virtual void FUN_87() = 0;
    virtual void FUN_88() = 0;
    virtual void FUN_89() = 0;
    virtual void FUN_90() = 0;
    virtual void FUN_91() = 0;
    virtual void FUN_92(int, int, unsigned short, int) = 0;
};

class RHActorPCSequenceCalls
{
public:
    virtual void Destroy(unsigned flags) = 0;
};

#include "RHMalignityGeometryCalls.h"

class RHUnk005c38b0;
class RHUnk5490f0;
class RHMessenger
{
public:
    void RHUnk005460c0(RHUnk5490f0 &message);
};
class RHUnk00452030;
// SIZE 0x18
struct RHActorPCProfileNode
{
    RHActorPCProfileNode *next; // 0x00
    RHActorPCProfileNode *previous; // 0x04
    undefined value[0x10]; // 0x08
};

// SIZE 0x70
class RHCampaignProfiles
{
public:
    RHCampaignProfiles();
    ~RHCampaignProfiles();
    undefined m_0[0x14]; // 0x00
    void **m_14; // 0x14
    undefined m_18[0x58]; // 0x18
};

// SIZE 0x48
class RHPCDescription
{
public:
    RHPCDescription(void *profile, bool playable);
    ~RHPCDescription();
    undefined m_0[0x14]; // 0x00
    unsigned short m_14; // 0x14
    undefined m_16[0x2e]; // 0x16
    char m_44; // 0x44
    undefined m_45[3]; // 0x45
};

// SIZE 0x60c
class RHUnk0048f280
{
public:
    RHUnk0048f280(void *description);
    undefined m_data[0x60c]; // 0x00
};

#include "RHEngineSerializationCalls.h"

class RHActorPCProfileCalls
{
public:
    RHPCDescription *FUN_00455ce0(void *profile);
    void FUN_00455d40(RHPCDescription *description);
    undefined m_0[0x104]; // 0x00
    std::vector<RHPCDescription *> m_104; // 0x104
};

#include "RHUnkSectorScript.h"

class RHUnk005fc3b0
{
public:
    float Unk005fc6a0(float value);
};

class RHActorScriptContext
{
public:
    int FUN_004030a0();
};

class RHActorPCInfo : public RHBonusInfo
{
public:
    RHBonusInfoBase &Position() { return *(RHBonusInfoBase *)((char *)this + 4); }
    void Layer(unsigned short layer) { Position().m_da = layer; }
    void Value(int value) { *(int *)((char *)&Position() + 0xf8) = value; }
    void ByteValue(unsigned char value) { *(int *)((char *)this + 0xfc) = value; }
    void Area(void *area) { m_e0 = area; }
    void Restore()
    {
        RHBonusTriple *source = &m_4.m_c;
        RHBonusTriple *destination = &m_4.m_28;
        *destination = *source;
    }
};

struct RHbeamMe
{
    SBGeoPoint2D m_point;
    unsigned short m_8;
    unsigned short m_a;
    unsigned short m_c;
    unsigned char m_e;
    char m_f;
    unsigned short m_10;
    unsigned short m_12;
    char m_14[0x8];
    int m_1c;
    std::string m_20;
};

class RHEngineReinforcementCalls
{
public:
    void FUN_00491fd0(const RHbeamMe &beamMe);
};

class RHActorPCTemplateCalls
{
public:
    void FUN_00493660(int value);
};

class RHElementActor
{
public:
    void InitializeScript(std::string &name);
    void FUN_00478c20(RHUnk00613e90 &point, bool value);
};

#include "RHElementPositionCalls.h"

template<class T>
inline T &RHActorPCField(void *actor, unsigned offset)
{
    return *(T *)((char *)actor + offset);
}

class RHUnk00471630
{
public:
    RHUnk00471630(int type, int value, void *description);
};

// SIZE 0x14
#include "RHActorSequenceStorage.h"

struct RHScriptNode;
class RHUnk0046eb30
{
public:
    RHScriptNode *Unk0059f720(RHScriptNode *next, RHScriptNode *previous);
};

class RHUnk005ef320
{
public:
    unsigned short Unk(int red, int green, int blue);
};

extern RHUnk005ef320 *g_unk0x6c11d0;
extern char g_unk0x6c0689;
class RHUnk0048a970;
extern RHUnk0048a970 *g_unk0x6c0b3c;

extern RHCampaignProfiles *g_unk0x6c0e84;
extern RHUnk00452030 *g_unk0x6c07fc;
extern char g_unk0x6c0691;
bool FUN_005e0c90(SBFile &file, std::string &value);

#include "RHPortraitBar.h"
typedef RHPortraitBar RHActorPCMenuCalls;

class RHPCCombatCalls
{
public:
    void FUN_0049bb20(int action, int flag);
    int FUN_00485240(int value);
};

class RHActorPCEngineCalls
{
public:
    void FUN_0050efb0(void *value);
    undefined m_0[0x196c]; // 0x00
    RHActorPCMenuCalls *m_196c; // 0x196c
};

class RHGamePortraitCalls
{
public:
    void FUN_005d9950(unsigned action);
    void FUN_005d9a60(unsigned action);
    void FUN_005d9b70();
};

class RHActorPCWidgetCalls
{
public:
    void FUN_005d9860();
    void FUN_005d9700(unsigned short action);
};

// SIZE 0xe8
class RHActorPCWidgetState
{
public:
    void FUN_005db620(RHActorPCWidgetState *state);
    void Mark()
    {
        if (!m_cc)
        {
            m_cc = 1;
            if (m_7c == 5)
                m_7c = 8;
            if (m_7c == 6)
                m_7c = 9;
        }
    }
    void ClearLinked()
    {
        if (m_d0 && this != m_d0)
        {
            RHActorPCWidgetState *linked = m_d0;
            if (linked->m_cc == 1)
            {
                if (linked->m_7c == 9)
                    linked->m_7c = 6;
                if (linked->m_7c == 8)
                    linked->m_7c = 5;
                linked->m_cc = 0;
            }
            linked->m_d0->FUN_005db620(this);
        }
    }
    undefined m_0[0x7c]; // 0x00
    int m_7c; // 0x7c
    undefined m_80[0x4c]; // 0x80
    char m_cc; // 0xcc
    undefined m_cd[3]; // 0xcd
    RHActorPCWidgetState *m_d0; // 0xd0
    undefined m_d4[0x14]; // 0xd4
};

#include "RHActorPCHumanCalls.h"

#endif
