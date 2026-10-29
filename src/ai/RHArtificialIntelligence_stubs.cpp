#include "SBNullstr.h"
#include "RHArtificialIntelligence.h"

// FUNCTION: GAME 0x006091d0
SBGeoBoundingBox2D &SBGeoBoundingBox2D::FUN_006091d0(float scale)
{
    first.m_x *= scale;
    first.m_y *= scale;
    last.m_x *= scale;
    last.m_y *= scale;
    return *this;
}

void SBDrawManager::FUN_005ecdc0(unsigned long, const SBGeoBoundingBox2D &, unsigned short, unsigned long) {}

// LIBRARY: GAME 0x00642a70
extern "C" void __cdecl srand(unsigned) {}

// LIBRARY: GAME 0x00642a9f
extern "C" long __cdecl time(long *) { return 0; }


bool RHArtificialIntelligenceActorCalls::Unk00470ce0() { return false; }
std::string FUN_00420d40(int) { return std::string(); }
bool RHArtificialIntelligence::Unk00412240(const RHUnk00571160Position &, unsigned short, float) { return false; }
extern "C" int __cdecl rand();

// FUNCTION: GAME 0x00419c50
unsigned char RHArtificialIntelligence::Unk00419c50()
{
    if (*(char *)((char *)this + 0x25f))
    {
        *(char *)((char *)this + 0x25f) = 0;
        return *(char *)((char *)this + 0x25e);
    }
    return (unsigned char)(rand() % 100 + 1);
}

// FUNCTION: GAME 0x00419c80
unsigned char RHArtificialIntelligence::Unk00419c80()
{
    if (!*(char *)((char *)this + 0x25f))
    {
        int value = rand();
        *(char *)((char *)this + 0x25f) = 1;
        *(char *)((char *)this + 0x25e) = (char)(value % 100 + 1);
    }
    return *(char *)((char *)this + 0x25e);
}

// FUNCTION: GAME 0x0041ab10
void RHArtificialIntelligence::Unk0041ab10(unsigned short direction)
{
    *(unsigned short *)((char *)this + 0x346) = direction;
    if (*(int *)((char *)this + 0x14) == 0x18)
        Unk00412f70(direction, 0);
}
#include "RHActorCancelCalls.h"

// FUNCTION: GAME 0x0048d020
void RHArtificialIntelligenceActorCalls::Unk0048d020()
{
    *((char *)this + (*(int **)((char *)this + 0x49c))[1] + 0x6a0) = 1;
    ((RHUnk0046bcb0 *)this)->Unk(7);
    *((char *)this + (*(int **)((char *)this + 0x49c))[1] + 0x6a0) = 0;
}


class RHAIUnk00550660
{
public:
    int Unk00550660(int value);
};
// Parked: VC6 folds the if-chain into a ternary (setne) instead of the target's shared boolean tail.
// STUB: GAME 0x00550660
int RHAIUnk00550660::Unk00550660(int value)
{
    char flag = *(char *)((char *)this + 2);
    if (flag && value == 2)
        return 0;
    if (flag)
        return 1;
    if (value != 1)
        return 1;
    return 0;
}
void RHArtificialIntelligence::FUN_00411a00(unsigned) {}
