#include "RHElementActorHuman.h"

RHHumanOpponentIterator RHHumanOpponentListCalls::FUN_00486110(RHHumanOpponentIterator position, const RHHumanOpponent &value)
{
    return position;
}

class RHNPCBaseCalls
{
public:
    bool FUN_004799e0(SBFile &file);
};

bool RHNPCBaseCalls::FUN_004799e0(SBFile &file)
{
    return ((RHElementActorHuman *)this)->Serialize(file);
}
