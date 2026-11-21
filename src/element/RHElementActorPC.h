#ifndef RHELEMENTACTORPC_H
#define RHELEMENTACTORPC_H

#include "Decomp.h"
#include "RHElementActorHumanCore.h"
#include <string>

class SBFile;
class RHSequenceElement;
class RHSequence;
class RHUnk00585ea0;
class RHActorTranslationSequenceCalls;
class SBGeoPoint2D;
class SBGeoBoundingBox2D;
class RHElementActorHuman;
class RHUnk00613e90;
class RHBonusInfo;
class RHPCDescription;
struct RHBonusGlobalView;
struct RHBonusProjection;

// SIZE 0x60c
class RHElementActorPC : public RHElementActorHuman
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
    std::wstring GetTooltipTextForAction(int action);
    int FUN_00493ae0(bool allow, void *unused);
    bool FUN_004936f0();
    bool FUN_004937e0(const SBGeoPoint2D &point, RHElementActorHuman *target, int focus);
    int FUN_00494850(void *element);
    float FUN_0049d520();
    void FUN_00495f90(void *element);
    bool FUN_00496270(unsigned flags, RHActorTranslationSequenceCalls *sequence);
    void FUN_0049b930(int amount, int unused, bool mode);
    void FUN_0049b9c0(int amount, void *source, bool force);
    bool FUN_00490450(void *owner, void *target);
    void FUN_004909a0(RHSequence *sequence);
    void *FUN_00490e10(RHElementActorHuman *target);
    void FUN_004913f0(const SBGeoBoundingBox2D &view, float scale);
    unsigned short FUN_00493b40(void *target, const SBGeoPoint2D &point, int unused1, int unused2);
    void FUN_00493c10(void *element);
    bool FUN_0049bdf0(RHSequenceElement *element);
    void FUN_0049d400(RHSequenceElement *element);
    void FUN_0049d450(RHSequenceElement *element);
    void FUN_0049c660(unsigned short value);
    virtual short GetLifePoints() const;
    unsigned short FUN_0049ff60();
    static RHElementActorPC *CreatePCFromMissionStream(SBFile &file);
    void ApplyProjection(RHBonusProjection *projection);
    void InitializeAction(int action);
    bool FUN_004a16c0(int action, RHUnk00613e90 &position, const void *target);
    bool FUN_004a18c0(void *target);
    void FUN_004a1900(unsigned short action);
    int FUN_0049d590(int action);
    int FUN_0049d5c0(unsigned short action);
    unsigned short FUN_0049d5e0(int action);
    void FUN_0049d680(int action);
    void FUN_0049d6c0();
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
    virtual unsigned short FUN_0049ec20(unsigned action);
    void FUN_0049ece0(const void *target);
    void FUN_0049eeb0(const void *target);
    void FUN_0049f080(const RHUnk00613e90 &point);
    void FUN_0049f210(const RHUnk00613e90 &point);
    void FUN_0049f380(const RHUnk00613e90 &point);
    void FUN_0049f520(unsigned action, unsigned short amount, char notify);
    void FUN_0049f5c0(unsigned action, unsigned short value);
    void FUN_0049f640(unsigned action, short value);
    unsigned FUN_0049f6c0(const SBGeoPoint2D &point);
    void FUN_0049fa20(unsigned index, void *value);
    bool FUN_0049fbc0();
    void FUN_0049fbf0(void *actor, bool consume);
    void FUN_0049fc80(int index, unsigned amount);
    void FUN_0049fcd0();
    void FUN_0049fe20();
    void FUN_0049ff70();
    void FUN_0049ffe0(void *first, unsigned char flag, unsigned third, unsigned fourth, unsigned fifth, unsigned sixth, unsigned seventh);
    void FUN_004a0020(RHUnk00585ea0 *action, bool interactive, unsigned distance, unsigned titbit, unsigned flag, unsigned offset, unsigned long flags);
    void FUN_004a0340(RHSequence *sequence, bool interactive, unsigned distance, unsigned titbit, RHElementActorHuman *target, bool flag);
    void FUN_004a05a0();
    char FUN_004a05f0(const RHElementActorPC *other);
    void FUN_004a0670();
    void FUN_004a06e0(unsigned char value);
    void FUN_004a07f0(const SBGeoBoundingBox2D &box, float zoom, unsigned long flags, int unused);
    bool FUN_004a0a30(RHUnk00613e90 &position);
    void FUN_004a0c90(int first, int second, bool third);
    void FUN_004a0cc0(RHElementActorPC *other);
    void FUN_004a0d10(float x, float y, void *area, unsigned short layer, unsigned short before, unsigned short after, void *target);
    bool FUN_0049d4f0(int value) const;

    virtual void Vfc() = 0;
    virtual void V100() = 0;
    virtual void FUN_0049bfd0(unsigned short action, unsigned short flags, unsigned short variant);
    virtual void V108() = 0;
    virtual void V10c() = 0;
    virtual void V110() = 0;
    virtual void V114() = 0;
    virtual void V118() = 0;
    virtual void V11c() = 0;
    virtual void V120() = 0;
    virtual void V124() = 0;
    virtual void V128() = 0;
    virtual void V12c() = 0;
    virtual void V130() = 0;
    virtual void V134() = 0;
    virtual void V138() = 0;
    virtual void V13c() = 0;
    virtual void V140() = 0;
    virtual void V144() = 0;
    virtual void V148() = 0;
    virtual void V14c() = 0;
    virtual void V150() = 0;
    virtual void V154() = 0;
    virtual void V158() = 0;
    virtual void V15c() = 0;
    virtual void V160() = 0;
    virtual void V164() = 0;
    virtual void V168() = 0;
    virtual void V16c() = 0;
    virtual bool SetQuickActionSequence(void *first, void *second, unsigned short action, unsigned long id);
    bool SetQuickActionSequence(int value, unsigned short action, unsigned long id);
    bool SetQuickActionSequence(int value, unsigned short action, unsigned long id, void *target, unsigned short amount);

    undefined m_49c[0x4c];
    char m_4e8; // 0x4e8
    undefined m_4e9[3];
    void *m_4ec; // 0x4ec
    undefined m_4f0[0x10];
    int m_500; // 0x500
    int m_504; // 0x504
    undefined m_508[3];
    bool m_50b[3]; // 0x50b
    undefined m_50e[0x2a];
    unsigned long m_quickActionIds[3];
    undefined m_544[0xa4];
    void *m_5e8;
    undefined m_5ec[0xc];
    RHPCDescription *m_5f8;
    void *m_5fc; // +0x5fc
    void *m_600; // +0x600
    undefined m_604[8]; // 0x604
};

#endif
