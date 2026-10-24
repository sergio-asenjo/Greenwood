#ifndef RHSEQUENCEINTERACTIONCALLS_H
#define RHSEQUENCEINTERACTIONCALLS_H

#include "RHSequenceElementCalls.h"

class SBFile;

class RHSequenceInteractionCalls : public RHSequenceElementCalls
{
public:
    RHSequenceInteractionCalls *FUN_00585ed0();
    bool FUN_00585f40(SBFile &file, bool pointers);
    int FUN_00585f70();
    void Emit(SBFile &file, bool pointers);
    void *m_64;
};

#endif
