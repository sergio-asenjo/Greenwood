#ifndef RHPROJECTILEINITCALLS_H
#define RHPROJECTILEINITCALLS_H

class RHUnk004b0980
{
public:
    bool FUN_004b0980(bool flag);
};

class RHUnk004b91a0
{
public:
    bool FUN_004b91a0(bool flag);
};

class RHUnk004be080
{
public:
    bool FUN_004be080(bool flag);
};

class RHUnk004ba900
{
public:
    bool FUN_004ba900(bool flag);
    int FUN_004ba970();
    bool FUN_004ba980(void *target);
    void *InteractionTarget() const { return *(void **)((char *)this + 0x12c); }
};

#endif
