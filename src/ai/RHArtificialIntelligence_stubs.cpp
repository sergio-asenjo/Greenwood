#include "SBNullstr.h"
#include "RHArtificialIntelligence.h"

void SBGeoBoundingBox2D::FUN_006091d0(float) {}

void SBDrawManager::FUN_005ecdc0(unsigned long, const SBGeoBoundingBox2D &, unsigned short, unsigned long) {}

// LIBRARY: GAME 0x00642a70
extern "C" void __cdecl srand(unsigned) {}

// LIBRARY: GAME 0x00642a9f
extern "C" long __cdecl time(long *) { return 0; }


void RHArtificialIntelligence::Unk00422b70(int, int) {}
bool RHArtificialIntelligence::Unk00419b20(int) { return false; }
void RHArtificialIntelligence::Unk00419970(int, int, int) {}
bool RHArtificialIntelligenceActorCalls::Unk00485e60() { return false; }
bool RHArtificialIntelligenceActorCalls::Unk00470ce0() { return false; }
void RHArtificialIntelligenceSoundCalls::Unk005a8d10(RHArtificialIntelligenceActor *) {}
void RHArtificialIntelligenceSoundCalls::Unk005a8b70(int, void *, int, short, SBGeoPoint2D *, RHArtificialIntelligenceActor *) {}
std::string FUN_00420d40(int) { return std::string(); }
bool RHArtificialIntelligence::Unk00412240(const RHUnk00571160Position &, unsigned short, float) { return false; }
unsigned char RHArtificialIntelligence::Unk00419c80() { return 0; }
void RHArtificialIntelligence::Unk0041ab10(unsigned short) {}
void RHArtificialIntelligenceActorCalls::Unk0048d020() {}

class RHUnk005866a0
{
public:
    void Unk00586e90(int property, unsigned short value);
};
void RHUnk005866a0::Unk00586e90(int, unsigned short) {}

class RHAIUnk00550660
{
public:
    int Unk00550660(int value);
};
int RHAIUnk00550660::Unk00550660(int) { return 0; }
