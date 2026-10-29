#include "SBNullstr.h"
#include "RHSightObstacle.h"

// TEMPLATE: GAME 0x005c9010 FOLDED
// ?FUN_005c9010@@YAXAAURHUnkSightVertexIter@@HUbidirectional_iterator_tag@std@@@Z
void FUN_005c9010(RHUnkSightVertexIter &current, int distance, std::bidirectional_iterator_tag category)
{
    std::_Advance(current, distance, category);
}
