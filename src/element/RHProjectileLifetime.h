#ifndef RHPROJECTILELIFETIME_H
#define RHPROJECTILELIFETIME_H

#include "RHElementProjectile.h"
#include "RHMalignityPosition.h"

struct RHProjectilePointLifetime
{
    RHProjectilePointLifetime()
    {
        ((RHUnk00613e90 *)this)->RHUnk00613e90::RHUnk00613e90();
    }
    unsigned char data[12];
};

struct RHProjectileCtorList
{
    RHProjectileCtorList(const unsigned char &allocation)
    {
        allocator = allocation;
        RHScriptNode *created = (RHScriptNode *)operator new(12);
        created->next = created;
        created->prev = created;
        head = created;
        count = 0;
        dirty = true;
    }
    unsigned char allocator;
    RHScriptNode *head;
    unsigned count;
    RHScriptNode *cursor;
    bool dirty;
    int index;
};

class __declspec(novtable) RHProjectileLifetime : public RHElementObject
{
public:
    RHProjectileLifetime(int action, void *victim);
    ~RHProjectileLifetime();
    virtual char FUN_004b9f40();
    virtual unsigned V68();
    void *FUN_004b40f0(unsigned flags);
    RHProjectilePointLifetime point100;
    RHProjectilePointLifetime point10c;
    union
    {
        struct
        {
            unsigned char data118[8];
            void *material;
            unsigned char data124[8];
        };
        RHMalignityPosition impactPosition;
    };
    void *target;
    unsigned short count130;
    unsigned char flag132;
    unsigned char flag133;
    unsigned char flag134;
    unsigned char flag135;
    unsigned char data136[2];
    RHProjectileCtorList list;
    unsigned char data150[0xc];
};

#endif
