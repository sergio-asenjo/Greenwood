#include "SBDrawManagerCore.h"

// Anonymous cluster at 0x005ef39x.
// No __FILE__ or oracle evidence: class and method identity are unproven.

class RHUnk005ef390
{
public:
    void FUN_005ef390();
    char m_00[0x78];
    int m_78;
};

// FUNCTION: GAME 0x005ef390
void RHUnk005ef390::FUN_005ef390()
{
    ((SBDrawManager *)this)->FUN_005e61e0(m_78, 0, 0, 0);
}
