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


void RHArtificialIntelligence::Unk00422b70(int, int) {}
bool RHArtificialIntelligence::Unk00419b20(int) { return false; }
void RHArtificialIntelligence::Unk00419970(int, int, int) {}
// Parked: effective-only; target returns full-width eax where a bool return gives al.
// STUB: GAME 0x00485e60
bool RHArtificialIntelligenceActorCalls::Unk00485e60()
{
    void *data = *(void **)((char *)this + 0x50);
    if (*(void **)((char *)data + 0xf4))
        return true;
    void *area = *(void **)((char *)data + 0xe0);
    if ((*(unsigned *)((char *)area + 0x30) >> 13) & 1)
        return true;
    return false;
}
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

// Parked: effective-only; VC6 sinks the flag store into the idiv latency window.
// STUB: GAME 0x00419c80
unsigned char RHArtificialIntelligence::Unk00419c80()
{
    if (!*(char *)((char *)this + 0x25f))
    {
        *(char *)((char *)this + 0x25f) = 1;
        *(char *)((char *)this + 0x25e) = (char)(rand() % 100 + 1);
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
void RHArtificialIntelligenceActorCalls::Unk0048d020() {}


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
