#include "Toolbox.h"

void RHUnk006114c0::FUN_00611aa0(SBFile &, void *) {}
int FUN_006277e0(void *, unsigned int *, const void *, unsigned int) { return 0; }
int __stdcall FUN_006273d0(void *, unsigned int *, const void *, unsigned int, int, int) { return 0; }

// parked, unannotated: base-constructor/vptr ordering and counted callers
RHUnk006114c0::RHUnk006114c0()
{
    FUN_00611b90();
    *(undefined4 *)(m_24 + 0x0c) = 2;
}

// parked, unannotated: base-destructor ILT tail jump and counted callers
RHUnk006114c0::~RHUnk006114c0()
{
    FUN_00611c00();
}

void RHUnk006114c0::FUN_00611b90() {}
void RHUnk006114c0::FUN_00611c00() {}
void RHUnk006114c0::Unk10() {}
bool RHUnk006114c0::Unk20(RHUnkFXDraw *draw, unsigned long surface)
{
    return Unk00613530(draw, surface);
}

void RHUnkFXDraw::FUN_005e5260() {}
void RHUnkFXDraw::FUN_005e61e0(unsigned long, unsigned long, unsigned long, unsigned long) {}
void RHUnkFXDraw::FUN_005e6440(unsigned long, int, int, unsigned long, unsigned long) {}
int RHUnk005f4fc0::FUN_005f5090(const RHProfileText &, int) { return 0; }
void RHUnk0060e4c0::FUN_0060e4c0() {}
bool RHUnk0060e4c0::FUN_0060f1c0(const RHUnk0060e4c0 &) { return false; }
void RHUnk0060e4c0::FUN_0060f1e0(SBFile &) {}
RHUnk0060e4c0 *FUN_005e1b20(RHUnk0060e4c0 *result, const char *) { return result; }
unsigned long ToolboxPositionFile::FUN_005f5440() { return 0; }
void ToolboxChunks::FUN_005e3070() { Buyback(); }
ToolboxChunk **ToolboxChunks::FUN_005e31d0(unsigned int count) { return _Growmap(count); }
ToolboxChunkIterator::ToolboxChunkIterator(ToolboxChunk *next, ToolboxChunk **map)
    : m_first(*map), m_last(*map + 512), m_next(next), m_map(map) {}
unsigned long FUN_005f0ce0() { return 0; }
bool FUN_005f1150(ToolboxMouseState &, unsigned char *) { return false; }
bool FUN_005e17a0(unsigned char *) { return false; }
void FUN_005e1380() {}
void FUN_005e1400() {}
namespace Toolbox
{
    void FUN_005f1000() {}
}
