#ifndef RHSEQUENCEMOVEMENTCONSTRUCTION_H
#define RHSEQUENCEMOVEMENTCONSTRUCTION_H

#include "RHSequenceGenericCalls.h"

#ifndef SBGEO_POINT2D_VIEW
#include "SBGeoPoint2D.h"
#endif

struct RHMovementBox;

class RHMovementOwned
{
public:
    virtual ~RHMovementOwned();
};

// VTABLE: GAME 0x00679d88
class RHUnk00588530 : public RHUnk00584d60
{
public:
    RHUnk00588530();
    RHUnk00588530(unsigned short level, int command, void *actor);
    RHUnk00588530(unsigned short level, int command, void *actor, int value94, RHMovementBox *box, float value8c, int value88);
    RHUnk00588530(unsigned short level, int command, void *actor, int style, void *target, float distance, void *value);
    RHUnk00588530(unsigned short level, int command, void *actor, int value94, const SBGeoPoint2D &point, void *value78, unsigned short value74, float value8c, int value88);
    RHUnk00588530(unsigned short level, int command, void *actor, void *value78, const SBGeoPoint2D &point, void *value84, float value8c, int value88);
    RHUnk00588530(unsigned short level, int command, void *actor, const SBGeoPoint2D &point, void *value78, unsigned short value90, int value88);
    RHUnk00588530(unsigned short priority, int command, void *element, int animation, const SBGeoPoint2D &destination, void *target, float speed, unsigned long flags);
    RHUnk00588530(unsigned short level, int command, void *actor, int style, int value);
    ~RHUnk00588530();
    virtual void *FUN_00584d40(unsigned int flags);
    void FUN_00588940();
    void FUN_00588b20();
    void FUN_00588b60();
    void FUN_00588d60();
    void FUN_00588f00();
    void FUN_005890c0();
    void FUN_005892a0(int replacement, int action, float distance, const SBGeoPoint2D &origin);
    void FUN_00589490(int replacement, int action, float distance, const SBGeoPoint2D &origin);
    RHUnk00588530 *FUN_00589810();
    void FUN_00589c00(int state, int value);
    void FUN_00589c70(int priority);
    void EmitMovement();
    void *m_64;
    RHMovementOwned *m_68;
    SBGeoPoint2D m_6c;
    unsigned short m_74;
    char m_76[2];
    void *m_78;
    void *m_7c;
    void *m_80;
    void *m_84;
    int m_88;
    float m_8c;
    unsigned short m_90;
    char m_92[2];
    int m_94;
    float m_98;
};

#endif
