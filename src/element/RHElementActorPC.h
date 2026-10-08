#ifndef RHELEMENTACTORPC_H
#define RHELEMENTACTORPC_H

#include "Decomp.h"

class SBFile;
class RHBonusInfo;
struct RHBonusGlobalView;
struct RHBonusProjection;

// SIZE 0x60c
class RHElementActorPC
{
public:
    static RHElementActorPC *CreatePCFromMissionStream(SBFile &file);
    void ApplyProjection(RHBonusProjection *projection);
    void InitializeAction(int action);
    int FUN_0049d590(int action);
    int FUN_0049d5c0(unsigned short action);
    void FUN_0049d890(unsigned short action);
    void FUN_0049d960(unsigned short action);
    void FUN_0049da00(unsigned short action);
    void FUN_0049dad0(unsigned short action);
    void Emit(int action);

    undefined m_0[0x50]; // 0x00
    RHBonusInfo *m_50; // +0x50
    undefined m_54[0x10]; // 0x54
    RHBonusGlobalView *m_64; // +0x64
    undefined m_68[0x98]; // 0x68
    char m_100; // +0x100
    undefined m_101[3]; // 0x101
    unsigned m_104; // +0x104
    void *m_108; // +0x108
    undefined m_10c[0x4f0]; // 0x10c
    void *m_5fc; // +0x5fc
    undefined m_600[0xc]; // 0x600
};

#endif
