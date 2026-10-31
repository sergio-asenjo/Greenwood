#ifndef RHELEMENTACTORPC_H
#define RHELEMENTACTORPC_H

#include "Decomp.h"
#include <string>

class SBFile;
class RHSequenceElement;
class SBGeoPoint2D;
class RHElementActorHuman;
class RHUnk00613e90;
class RHBonusInfo;
class RHPCDescription;
struct RHBonusGlobalView;
struct RHBonusProjection;

// SIZE 0x60c
class RHElementActorPC
{
public:
    void GetTransitionFlags(RHSequenceElement *element, unsigned long &first, unsigned long &second, unsigned long &third);
    void FUN_0049c270();
    bool FUN_0049c4b0(unsigned short action);
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
    void AbortQuickAction(unsigned short action);
    bool SetQuickActionSequence(void *first, void *second, unsigned short action, unsigned long id);
    bool SetQuickActionSequence(int value, unsigned short action, unsigned long id);
    bool SetQuickActionSequence(int value, unsigned short action, unsigned long id, void *target, unsigned short amount);
    std::wstring GetTooltipTextForAction(int action);
    int FUN_00493ae0(bool allow, void *unused);
    bool FUN_004936f0();
    int FUN_00494850(void *element);
    float FUN_0049d520();
    void FUN_00495f90(void *element);
    void FUN_0049b930(int amount, int unused, bool mode);
    bool FUN_00490450(void *owner, void *target);
    void *FUN_00490e10(RHElementActorHuman *target);
    unsigned short FUN_00493b40(void *target, const SBGeoPoint2D &point, int unused1, int unused2);
    void FUN_0049d400(RHSequenceElement *element);
    void FUN_0049c660(unsigned short value);
    unsigned short FUN_0049f500();
    unsigned short FUN_0049ff60();
    static RHElementActorPC *CreatePCFromMissionStream(SBFile &file);
    void ApplyProjection(RHBonusProjection *projection);
    void InitializeAction(int action);
    bool FUN_004a18c0(void *target);
    int FUN_0049d590(int action);
    int FUN_0049d5c0(unsigned short action);
    unsigned short FUN_0049d5e0(int action);
    void FUN_0049d680(int action);
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
    bool FUN_0049eab0(SBGeoPoint2D &result);
    void FUN_0049ec50(unsigned action, unsigned short amount);
    unsigned short FUN_0049ec20(unsigned action);
    void FUN_0049ece0(const void *target);
    void FUN_0049eeb0(const void *target);
    void FUN_0049f080(const RHUnk00613e90 &point);
    void FUN_0049f210(const RHUnk00613e90 &point);
    void FUN_0049f380(const RHUnk00613e90 &point);
    void FUN_0049f520(unsigned action, unsigned short amount, char notify);
    void FUN_0049f5c0(unsigned action, unsigned short value);
    void FUN_0049f640(unsigned action, short value);
    unsigned FUN_0049f6c0();
    void FUN_0049fa20(unsigned index, void *value);
    bool FUN_0049fbc0();
    void FUN_0049fbf0(void *actor, bool consume);
    void FUN_0049fc80(int index, unsigned amount);
    void FUN_0049fcd0();
    void FUN_0049fe20();
    void FUN_0049ff70();
    void FUN_0049ffe0(void *first, unsigned char flag, unsigned third, unsigned fourth, unsigned fifth, unsigned sixth, unsigned seventh);
    void FUN_004a0020(void *first, unsigned char second, unsigned third, unsigned fourth, unsigned fifth, unsigned sixth, unsigned seventh);
    void FUN_004a0340(void *first, void *second, unsigned third, unsigned fourth, int fifth, char sixth);
    void FUN_004a05a0();
    char FUN_004a05f0(const RHElementActorPC *other);
    void FUN_004a0670();
    void FUN_004a06e0(unsigned char value);
    void FUN_004a07f0(unsigned first, unsigned second, unsigned third);
    bool FUN_004a0a30(RHUnk00613e90 &position);
    void FUN_004a0c90(int first, int second, bool third);
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
    undefined m_10c[0x4ec];
    RHPCDescription *m_5f8;
    void *m_5fc; // +0x5fc
    void *m_600; // +0x600
    undefined m_604[8]; // 0x604
};

#endif
