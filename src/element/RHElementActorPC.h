#ifndef RHELEMENTACTORPC_H
#define RHELEMENTACTORPC_H

class SBFile;
class RHBonusInfo;
struct RHBonusGlobalView;
struct RHBonusProjection;

class RHElementActorPC
{
public:
    static RHElementActorPC *CreatePCFromMissionStream(SBFile &file);
    void ApplyProjection(RHBonusProjection *projection);
    void InitializeAction(int action);
    void Emit(int action);

    char m_0[0x50];
    RHBonusInfo *m_50; // +0x50
    char m_54[0x10];
    RHBonusGlobalView *m_64; // +0x64
    char m_68[0x98];
    char m_100; // +0x100
    char m_101[3];
    unsigned m_104; // +0x104
    void *m_108; // +0x108
    char m_10c[0x4f0];
    void *m_5fc; // +0x5fc
    char m_600[0xc];
};

#endif
