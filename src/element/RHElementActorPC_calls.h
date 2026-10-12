#ifndef RHELEMENTACTORPC_CALLS_H
#define RHELEMENTACTORPC_CALLS_H

#include "RHElementBonus.h"
#include "Decomp.h"
#include <string>
#include <vector>
#include <string.h>

// SIZE 0x0c
class RHUnk00613e90
{
public:
    RHUnk00613e90();
    float x; // 0x00
    float y; // 0x04
    float z; // 0x08
};

class RHScriptBatchCalls
{
public:
    void Unk00464630();
    void Unk0046bcf0(int state, int value);
    void Unk005c2ec0(void *position, int first, int second, void *actor, int third, int fourth, int fifth, int sixth);
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
    virtual void FUN_17() = 0;
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
    virtual void FUN_28() = 0;
    virtual void FUN_29() = 0;
    virtual void FUN_30() = 0;
    virtual void FUN_31() = 0;
    virtual void FUN_32() = 0;
    virtual void FUN_33() = 0;
    virtual void FUN_34() = 0;
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
    virtual void FUN_51() = 0;
    virtual void FUN_52() = 0;
    virtual void FUN_slot53(int, int, int) = 0;
    virtual void FUN_slot54() = 0;
    virtual void FUN_slot55(int, int, int) = 0;
    virtual void FUN_56() = 0;
    virtual void FUN_57() = 0;
    virtual void FUN_58() = 0;
    virtual void FUN_59() = 0;
    virtual void FUN_60() = 0;
    virtual void FUN_61() = 0;
    virtual void FUN_62() = 0;
    virtual void FUN_63() = 0;
    virtual void FUN_64() = 0;
    virtual void FUN_slot65(int, int, int) = 0;
};

class RHMalignityGeometryCalls
{
public:
    bool FUN_004eff80(const RHUnk00613e90 &first, const RHUnk00613e90 &second, int mode);
};

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

class RHEngineSerializationCalls
{
public:
    void FUN_0048fa30();
};

class RHActorPCProfileCalls
{
public:
    RHPCDescription *FUN_00455ce0(void *profile);
    void FUN_00455d40(RHPCDescription *description);
    undefined m_0[0x104]; // 0x00
    std::vector<RHPCDescription *> m_104; // 0x104
};

class RHUnkSectorScript
{
public:
    bool Unk00639a30(const std::string &name);
};

class RHUnk005fc3b0
{
public:
    RHUnk005fc3b0 &FUN_005fc430(const SBGeoPoint2D &vector);
};

class RHActorScriptContext
{
public:
    void FUN_004030a0();
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
};

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
class RHActorPCBoxCalls
{
public:
    RHActorPCBoxCalls();
    ~RHActorPCBoxCalls();
    undefined m_0[0x14]; // 0x00
};

class RHUnk0045aaf0
{
public:
    RHUnk0045aaf0();
    undefined4 m_0; // 0x00
    undefined4 m_4; // 0x04
    undefined m_8[8]; // 0x08
    RHActorPCBoxCalls m_10; // 0x10
    undefined m_24[0x10]; // 0x24
    SBGeoPoint2D m_34; // 0x34
};

struct RHScriptNode;
class RHUnk0046eb30
{
public:
    RHScriptNode *Unk0059f720(RHScriptNode *next, RHScriptNode *previous);
};

// SIZE 0x14
class RHUnk005492a0
{
public:
    RHUnk005492a0(int command, void *actor, int action);
    ~RHUnk005492a0();
    undefined4 m_0; // 0x00
    undefined m_4[8]; // 0x04
    int m_c; // 0x0c
    void *m_10; // 0x10
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

class RHActorPCMessageBaseCalls
{
public:
    void FUN_00549030(int level, int action);
};

class RHActorPCMenuCalls
{
public:
    void FUN_0055e710(void *value);
};

class RHActorPCEngineCalls
{
public:
    void FUN_0050efb0(void *value);
    undefined m_0[0x196c]; // 0x00
    RHActorPCMenuCalls *m_196c; // 0x196c
};

class RHActorPCWidgetCalls
{
public:
    void FUN_005d9950(int action);
    void FUN_005d9a60(int action);
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

#endif
