#include "RHArtificialIntelligence.h"

// LIBRARY: GAME 0x00642a70
extern "C" void __cdecl srand(unsigned) {}

// LIBRARY: GAME 0x00642a9f
extern "C" long __cdecl time(long *) { return 0; }

void RHArtificialIntelligence::Unk00416710(unsigned) {}
unsigned short RHArtificialIntelligence::Unk0041a420() { return 0; }
void RHArtificialIntelligence::Unk00486f60() {}

void RHArtificialIntelligence::Unk00410600() {}
void RHArtificialIntelligencePathCursor::Unk00550f60(unsigned short) {}
void RHArtificialIntelligencePathCursor::Unk005505b0(unsigned short) {}
void RHArtificialIntelligencePathCursor::Unk005505c0() {}
void RHUnk005fc3b0::Unk005fcd40(unsigned short, float) {}
void RHStimulus::Unk004188d0(int value)
{
    *(unsigned short *)m_00 = 0;
    m_20 = value;
    m_type = 0;
}

void RHArtificialIntelligence::Unk00412c80(void *, unsigned short) {}
void RHArtificialIntelligence::Unk00412f70(unsigned short, int) {}
bool RHArtificialIntelligence::Unk00419cc0() { return false; }
void RHArtificialIntelligence::Unk0041a960(unsigned short) {}
void RHArtificialIntelligence::Unk00422b70(int, int) {}
void RHArtificialIntelligence::Unk004195f0(unsigned) {}
bool RHArtificialIntelligence::Unk00419b20(int) { return false; }
void RHArtificialIntelligence::Unk00419970(int, int, int) {}
void RHArtificialIntelligenceActorCalls::Unk0048b450(unsigned, int) {}
void RHArtificialIntelligenceActorCalls::Unk0048b4e0(int) {}
bool RHArtificialIntelligenceActorCalls::Unk00485e60() { return false; }
bool RHArtificialIntelligenceActorCalls::Unk00470ce0() { return false; }
void RHArtificialIntelligenceSoundCalls::Unk005a8d10(RHArtificialIntelligenceActor *) {}
void RHArtificialIntelligenceSoundCalls::Unk005a8b70(int, void *, int, short, SBGeoPoint2D *, RHArtificialIntelligenceActor *) {}
std::string FUN_00420d40(int) { return std::string(); }
RHArtificialIntelligenceIterator RHArtificialIntelligenceTripleList::insert(RHArtificialIntelligenceIterator position, const RHArtificialIntelligenceTriple &) { return position; }
RHArtificialIntelligenceStimulusNode *RHArtificialIntelligenceStimulusList::Unk00424340(RHArtificialIntelligenceStimulusNode *next, RHArtificialIntelligenceStimulusNode *) { return next; }
void FUN_00424470(RHStimulus *destination, const RHStimulus *source) { *destination = *source; }
