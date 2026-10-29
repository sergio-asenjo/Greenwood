#ifndef RHBRIEFINGWINDOWCALLS_H
#define RHBRIEFINGWINDOWCALLS_H

#include <string>

class RHBriefingWindowCalls
{
public:
    virtual void V00();
    virtual void V04();
    virtual void V08();
    virtual void V0c();
    virtual void V10();
    virtual void V14();
    virtual void V18();
    virtual void V1c();
    virtual void V20();
    virtual void V24();
    virtual void V28();
    virtual void V2c();
    virtual void V30(void *widget);
    virtual void V34(void *widget);
    void *FUN_00544b60(const std::string &name);
};

#endif
