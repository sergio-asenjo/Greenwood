#ifndef RHHUMANENGINEACTORARRAY_H
#define RHHUMANENGINEACTORARRAY_H

#include "Decomp.h"

class RHMalignityActorCalls;

struct RHHumanEngineActorArray
{
    unsigned short Size() const
    {
        if (!m_first)
            return 0;
        return m_last - m_first;
    }
    RHMalignityActorCalls *&operator[](unsigned short index) const
    {
        return m_first[index];
    }
    undefined m_0000[0x495c];
    RHMalignityActorCalls **m_first;
    RHMalignityActorCalls **m_last;
};

#endif
