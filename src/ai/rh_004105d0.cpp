#include "RHUnkWaypointRef.h"

class RHElementMobile;
class RHScriptBatchCalls
{
public:
    void Unk0040d980(int value);
};
extern char g_unk0x6c0691;

class RHUnk004105d0
{
public:
    void FUN_004105d0(RHElementMobile *target);
    int m_0;
    RHElementMobile *m_4;
    char m_8[0xc];
    int m_14;
};

// FUNCTION: GAME 0x004105d0
void RHUnk004105d0::FUN_004105d0(RHElementMobile *target)
{
    if (g_unk0x6c0691)
    {
        ((RHUnkWaypointRef *)((char *)target + 0x60))->Unk00408750(m_4);
        if (m_14 != 0xe)
            ((RHScriptBatchCalls *)this)->Unk0040d980(0x14);
    }
}
