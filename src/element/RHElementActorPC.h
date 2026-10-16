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
    unsigned short FUN_0048f910();
    char FUN_0048f920();
    bool FUN_0048f930();
    static bool FUN_0048f980();
    char FUN_0048f9a0();
    unsigned short FUN_0048f9b0();
    unsigned short FUN_0048f9c0();
    unsigned short FUN_0048f9d0();
    char FUN_0048f9e0();
    unsigned FUN_0048f9f0();
    unsigned FUN_0048fa00();
    static RHElementActorPC *CreatePCFromMissionStream(SBFile &file);
    void ApplyProjection(RHBonusProjection *projection);
    void InitializeAction(int action);
    bool FUN_004a18c0(void *target);
    int FUN_0049d590(int action);
    int FUN_0049d5c0(unsigned short action);
    void FUN_0049d890(unsigned short action);
    void FUN_0049d960(unsigned short action);
    void FUN_0049da00(unsigned short action);
    void FUN_0049dad0(unsigned short action);
    void FUN_0049dbc0();
    char FUN_0049e720();
    void FUN_0049e760(int value);
    void FUN_0049e7b0(int value);
    void FUN_0049e800(int value);
    void FUN_0049e850(int first, int second);
    void FUN_0049e8a0(int first, int second);
    void FUN_0049e8f0(int value);
    bool FUN_0049eab0();
    void FUN_0049ec50(unsigned action, unsigned short amount);
    unsigned short FUN_0049ec20(unsigned action);
    void FUN_0049ece0(unsigned action);
    void FUN_0049eeb0(unsigned action);
    void FUN_0049f080(void *value);
    void FUN_0049f210(void *value);
    void FUN_0049f380(void *value);
    void FUN_0049f520(unsigned action, unsigned short amount, char notify);
    void FUN_0049f5c0(unsigned action, unsigned short value);
    void FUN_0049f640(unsigned action, short value);
    unsigned FUN_0049f6c0();
    void FUN_0049fa20(unsigned index, void *value);
    bool FUN_0049fbc0();
    void FUN_0049fbf0(void *actor);
    void FUN_0049fc80(int index, void *value);
    void FUN_0049fcd0();
    void FUN_0049fe20();
    void FUN_0049ff70();
    void FUN_0049ffe0(void *first, unsigned char flag, unsigned third, unsigned fourth, unsigned fifth, unsigned sixth, unsigned seventh);
    void FUN_004a0020(void *first, unsigned second, unsigned third, unsigned fourth, unsigned fifth, unsigned sixth, unsigned seventh);
    void FUN_004a0340(void *first, void *second, unsigned third, unsigned fourth, int fifth, char sixth);
    void FUN_004a05a0();
    char FUN_004a05f0(const RHElementActorPC *other);
    void FUN_004a0670();
    void FUN_004a06e0(unsigned char value);
    void FUN_004a07f0(unsigned first, unsigned second, unsigned third);
    unsigned FUN_004a0a30(void *position);
    void FUN_004a0c90(int first, int second, int third);
    void FUN_004a0cc0(RHElementActorPC *other);
    void FUN_004a0d10(void *first, void *second, unsigned third, unsigned fourth, unsigned fifth, unsigned sixth, void *seventh);
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
    void *m_600; // +0x600
    undefined m_604[8]; // 0x604
};

#endif
