#include "Toolbox.h"

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
