#ifndef RHPATHWORKLIST_H
#define RHPATHWORKLIST_H

#include "Decomp.h"
#include "RHMotionAreaList.h"

struct RHScriptNode;

// SIZE 0x24
class RHPathWorkList : public RHMotionAreaListStorage<void *>
{
public:
    RHScriptNode *cursor; // 0x0c
    bool valid; // 0x10
    int index; // 0x14
    undefined m_18[0x0c]; // 0x18
    RHPathWorkList() : RHMotionAreaListStorage<void *>(std::allocator<void *>()), valid(true) {}
};

#endif
