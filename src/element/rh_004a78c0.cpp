#include "SBNullstr.h"
#include "RHElementObject.h"

class RHUnk00452030
{
public:
    int Get(int index);
};
extern RHUnk00452030 *g_unk0x6c07fc;

// FUNCTION: GAME 0x004a78c0
bool RHElementObject::FUN_004a78c0(void *actor)
{
    if (m_b0 == 0xe)
    {
        if (g_unk0x6c07fc->Get(0) >= 0xa)
            return false;
    }
    return FUN_004b2420(actor);
}
