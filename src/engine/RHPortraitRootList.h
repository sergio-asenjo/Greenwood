#ifndef RHPORTRAITROOTLIST_H
#define RHPORTRAITROOTLIST_H

#include "RHPortraitRootLifetime.h"
#include <vector>

class RHUnk005d92c0Sub;

// SIZE 0xb0
class __declspec(novtable) RHPortraitRootList : public RHPortraitRootLifetime
{
public:
    RHPortraitRootList() { *(unsigned *)this = 0x00678ea8; }
    ~RHPortraitRootList();
    void *FUN_0050e770(unsigned flags);
    virtual bool FUN_0061a920(void *widget);
    virtual bool FUN_0061a800(void *widget)
    {
        return FUN_005df120(static_cast<RHUnk005d92c0Sub *>(widget));
    }
    bool FUN_005df300(void *widget) { return RHPortraitRootList::FUN_0061a920(widget); }
    bool FUN_005df120(RHUnk005d92c0Sub *widget);
    std::vector<RHUnk005d92c0Sub *> m_items; // 0xa0
};

#endif
