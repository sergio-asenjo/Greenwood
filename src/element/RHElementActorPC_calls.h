#ifndef RHELEMENTACTORPC_CALLS_H
#define RHELEMENTACTORPC_CALLS_H

#include "RHElementBonus.h"
#include <string>
#include <string.h>

class RHUnk00613e90
{
public:
    RHUnk00613e90();
    float x;
    float y;
    float z;
};

class RHScriptBatchCalls
{
public:
    void Unk00464630();
    void Unk0046bcf0(int state, int value);
    void Unk005c2ec0(void *position, int first, int second, void *actor, int third, int fourth, int fifth, int sixth);
};

class RHUnk005c38b0;
class RHUnk00452030;
class RHCampaignProfiles
{
public:
    RHCampaignProfiles();
    ~RHCampaignProfiles();
    char m_0[0x14];
    void **m_14;
    char m_18[0x58];
};

class RHPCDescription
{
public:
    RHPCDescription(void *profile, bool playable);
    ~RHPCDescription();
    char m_0[0x14];
    unsigned short m_14;
    char m_16[0x2e];
    char m_44;
    char m_45[3];
};

class RHUnk0048f280
{
public:
    RHUnk0048f280(void *description);
    char m_data[0x60c];
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

class RHUnk005fc030
{
public:
    RHUnk005fc030();
    float x;
    float y;
};

class RHUnk0045aaf0
{
public:
    RHUnk0045aaf0();
};

struct RHScriptNode;
class RHUnk0046eb30
{
public:
    RHScriptNode *Unk0059f720(RHScriptNode *next, RHScriptNode *previous);
};

class RHUnk005492a0
{
public:
    RHUnk005492a0(int command, void *actor, int action);
    ~RHUnk005492a0();
    char m_data[0x14];
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
void FUN_005e0c90(SBFile &file, std::string &value);

#endif
