#ifndef RH_ARTIFICIAL_INTELLIGENCE_CORE_H
#define RH_ARTIFICIAL_INTELLIGENCE_CORE_H

#include "RHPathCore.h"
#ifndef SBGEO_POINT2D_VIEW
#include "SBGeoPoint2D.h"
#endif
#include "RHUnk0056de50.h"
#include "RHStimulus.h"
#include "RHArtificialIntelligenceTripleList.h"
#include "RHArtificialIntelligenceCachedList.h"
#include "RHMalignityPosition.h"
#include "RHMalignityStimulus.h"

class SBFile;
class SBGeoPoint2D;
class RHUnk005fc3b0;
class RHArtificialIntelligenceActor;
class RHElementActorNPC;
class RHArtificialIntelligenceList;
class RHSeekPoint;
struct RHArtificialIntelligencePosition;
struct RHUnk00571160Position;
struct RHMalignityPosition;
struct RHMalignityStimulus;
class RHWaypoint;
class SBGeoBoundingBox2D;
class RHFastFindAmbushArray;
class RHFastFindSeekArray;
class RHFastFindArcheryArray;
class RHUnk00564020;
class RHUnk004241a0List;
class RHUnk00424060List;

// VTABLE: GAME 0x0067743c
class RHArtificialIntelligence
{
public:
    static SBGeoBoundingBox2D mboxViewRect;
    static RHFastFindAmbushArray marrayAmbushPoints;
    static RHFastFindSeekArray marraySeekPoints;
    static RHFastFindArcheryArray marrayArcherySectors;
    static RHUnk00564020 mlistHouses;
    static RHUnk004241a0List mlistScreenRemarks;
    static RHUnk00424060List mlistForbiddenRemarks;
    RHArtificialIntelligence();
    virtual void V00(int value);
    virtual void V04(int value);
    virtual bool V08(SBFile &file) = 0;
    virtual int V0c(SBFile &file) = 0;
    virtual void V10(int first, int second) = 0;
    virtual void V14();
    virtual void V18(unsigned char value);
    virtual void V1c();
    virtual ~RHArtificialIntelligence();
    virtual bool V24(RHMalignityStimulus *stimulus);
    virtual bool V28();
    virtual void FUN_00417580();
    virtual void V30(void *target, bool flag) = 0;
    virtual void V34(unsigned first, unsigned second);
    virtual void V38(bool enabled);
    virtual void V3c(int value);
    virtual void V40(unsigned short first, unsigned short second, unsigned short third);
    void *FUN_0040fd20(unsigned flags);
    void DispatchActorEvent(RHElementActor *actor, unsigned event)
    {
        RHMalignityStimulus stimulus;
        stimulus.m_actor = actor;
        stimulus.m_20 = event;
        stimulus.m_type = 3;
        V24(&stimulus);
    }
    void DispatchPositionEvent(const RHMalignityPosition &position, unsigned event)
    {
        RHMalignityStimulus stimulus(RHMalignityStimulus::Position);
        stimulus.m_20 = event;
        stimulus.m_type = 2;
        stimulus.m_position = position;
        V24(&stimulus);
    }
    bool InitState();
    bool AcceptStimulus(RHMalignityStimulus stimulus);
    void SetMusicState(int state, unsigned char flags);
    void SetReactionState(int value);
    void FinishStimulus();
    void DispatchWorldEvent(int event);
    void ActivateWaypoint(RHWaypoint *waypoint);
    bool HandleWaypointStimulus(const RHMalignityStimulus &stimulus);
    void Unk0041ac50();
    void Unk00416710(unsigned value);
    unsigned short Unk0041a420();
    void FUN_0041a490();
    void Unk00486f60();
    static bool SerializeAllAI(SBFile &file);
    static bool SerializeListOfPointersToActorsNPC(RHArtificialIntelligenceList &list, SBFile &file);
    static bool SerializeListOfPointersToHumans(RHArtificialIntelligenceList &list, SBFile &file);
    static bool SerializeListOfPointersToObjects(RHArtificialIntelligenceList &list, SBFile &file);
    static bool SerializePosition(RHArtificialIntelligencePosition &position, SBFile &file);
    void Emit(SBFile &file, RHArtificialIntelligencePosition &position);
    void Unk00410010(bool mode);
    bool Unk00414be0(SBFile &file);
    bool Unk00418600(unsigned short path);
    void *FUN_00417ed0(SBGeoPoint2D *position, bool active);
    void Unk00418c40(int remark, unsigned flags);
    void Unk00410600();
    void FUN_004121a0();
    void FUN_00411a00(unsigned flags);
    SBGeoPoint2D FUN_00412160(const RHWaypoint *source);
    bool Unk00412c80(void *waypoint, unsigned short flags);
    void FUN_00412d60(RHMalignityPosition position, short height, int mode);
    void FUN_00412e90(SBGeoPoint2D point, int mode);
    bool Unk00412f40(RHUnk005fc3b0 *direction, int mode);
    void FUN_00413240(SBGeoPoint2D point, int first, int second);
    void FUN_004130b0(RHMalignityPosition position);
    void FUN_004132d0(int first, int mode, int second);
    bool Unk00412f70(unsigned short value, int mode);
    bool Unk00412240(const RHUnk00571160Position &position, unsigned short flags, float length);
    bool FUN_00413cb0(RHUnk00571160Position &position);
    RHSeekPoint *FUN_004137a0();
    bool FUN_004139d0(RHMalignityPosition &position, float scale, unsigned short extra);
    bool Unk00419cc0();
    void FUN_00419e40(int &state, unsigned short &amount);
    void Unk0041a960(unsigned short direction);
    void Unk00422b70(int property, int value);
    void Unk004195f0(unsigned short flags);
    bool Unk00419b20(int remark);
    void Unk00419970(int remark, int time, int flags);
    unsigned char Unk00419c50();
    unsigned char Unk00419c80();
    void Unk0041ab10(unsigned short direction);
    void SetPathWalkingFlags(unsigned short flags);
    SBGeoPoint2D FUN_0040cc20(void *actor);
    RHMalignityPosition FUN_004165e0(void *actor, bool mode);
    SBGeoPoint2D FUN_0040cbf0(const RHMalignityPosition &position);
    void FUN_0041a300(void *actor);
    void FUN_0041be60(const RHMalignityPosition &position);
    void FUN_0041ab30();
    void FUN_004235a0();
    bool FUN_00419e10(void *actor);
    float FUN_0041a010(void *actor);
    float FUN_0041a060(void *actor);
    float FUN_0041a0b0(void *actor);
    void FUN_0041a140(RHMalignityPosition position, unsigned value);
    int ValueBetween(unsigned short first, unsigned short second, unsigned char percent);
    void FUN_00412cf0(const RHMalignityPosition &position, unsigned short heading, int mode);

    union
    {
        RHArtificialIntelligenceActor *m_actor;
        RHElementActorNPC *m_npcActor;
    };
    unsigned short m_08;
    unsigned short m_0a;
    int m_0c;
    char m_10[4];
    int m_14;
    int m_18;
    int m_1c;
    int m_20;
    bool m_24;
    char m_25[3];
    int m_initialAction;
    char m_2c[4];
    RHPath m_30;
    char m_54[0x1c];
    bool m_hasWaypoints;
    char m_71;
    bool m_72;
    char m_73;
    unsigned short m_74;
    char m_76[2];
    unsigned char *m_waypointCommands;
    short m_waypointCommandCount;
    bool m_7e;
    bool m_7f;
    RHElement *m_80;
    unsigned long m_84;
    unsigned long m_88;
    unsigned long m_8c;
    union
    {
        unsigned long m_90;
        RHElementActorNPC *m_reactionTarget;
    };
    unsigned long m_94;
    bool m_98;
    char m_99[3];
    unsigned int m_9c;
    bool m_a0;
    char m_a1[3];
    unsigned int m_a4;
    unsigned short m_a8;
    unsigned short m_aa;
    unsigned long m_ac;
    unsigned long m_b0;
    unsigned long m_b4;
    unsigned long m_b8;
    unsigned long m_bc;
    unsigned short m_c0;
    unsigned short m_c2;
    unsigned short m_c4;
    unsigned short m_c6;
    unsigned short m_c8;
    char m_ca[2];
    unsigned long m_cc;
    union
    {
        RHMalignityPosition m_reactionPosition;
        struct
        {
            char m_d0[8];
            unsigned long m_d8;
            char m_dc[4];
        };
    };
    RHMalignityPosition m_e0;
    bool m_hasEvaded;
    char m_f1[3];
    SBGeoPoint2D m_f4;
    unsigned char m_fc;
    char m_fd[3];
    RHArtificialIntelligenceCachedList<void *> m_100;
    RHArtificialIntelligenceCachedList<void *> m_124;
    RHArtificialIntelligenceCachedList<void *> m_148;
    char m_16c[3];
    char m_16f;
    char m_170;
    char m_171[2];
    char m_173;
    unsigned char m_174;
    bool m_175;
    char m_176[2];
    RHArtificialIntelligenceCachedList<RHStimulus> m_178;
    bool m_1c4;
    char m_1c5[3];
    unsigned m_1c8;
    int m_1cc;
    void *m_1d0;
    RHArtificialIntelligenceCachedList<void *> m_1d4;
    void *m_1f8;
    void *m_1fc;
    void *m_200;
    bool m_204;
    char m_205[3];
    RHArtificialIntelligenceCachedList<void *> m_208;
    unsigned short m_22c;
    char m_22e[2];
    RHArtificialIntelligenceCachedList<int> m_230;
    unsigned long m_254;
    unsigned long m_258;
    unsigned short m_25c;
    bool m_25e;
    bool m_25f;
    unsigned long m_260;
    unsigned int m_264;
    bool m_268;
    char m_269[3];
    RHUnk0056de50 m_26c;
    bool m_2ac;
    bool m_2ad;
    char m_2ae[2];
    RHElementActor *m_2b0;
    RHArtificialIntelligenceCachedList<void *> m_2b4;
    RHArtificialIntelligenceCachedList<void *> m_2d8;
    RHArtificialIntelligenceCachedList<void *> m_2fc;
    RHArtificialIntelligenceCachedList<void *> m_320;
    bool m_344;
    char m_345;
    unsigned short m_346;
    bool m_348;
    char m_349[3];
    RHArtificialIntelligenceCachedList<RHArtificialIntelligenceTriple> m_34c;
    char m_378[8];
    unsigned long m_380;
    char m_384[4];
    unsigned short m_388;
    unsigned short m_38a;
};

#endif
