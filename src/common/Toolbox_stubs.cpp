#include "SBNullstr.h"
#include "Toolbox.h"
#include "SBPicture.h"

// FUNCTION: GAME 0x00611aa0
void RHUnk006114c0::FUN_00611aa0(SBFile &file, void *header)
{
    file.Access(header, 2);
    file.Access((char *)header + 2, 2);
    file.Access((char *)header + 4, 4);
    file.Access((char *)header + 8, 4);
}
int FUN_006277e0(void *, unsigned int *, const void *, unsigned int) { return 0; }
int __stdcall FUN_006273d0(void *, unsigned int *, const void *, unsigned int, int, int) { return 0; }

// FUNCTION: GAME 0x006114c0
RHUnk006114c0::RHUnk006114c0()
{
    ((SBPicture *)this)->SBPicture::SBPicture();
    *(unsigned *)this = 0x67a880;
    *(undefined4 *)(m_24 + 0x0c) = 2;
}

// FUNCTION: GAME 0x006114e0
void *SBPicture::FUN_006114e0()
{
    return m_14;
}

// FUNCTION: GAME 0x006114f0
unsigned int SBPicture::FUN_006114f0()
{
    return m_1c;
}

// FUNCTION: GAME 0x00611500
unsigned short SBPicture::FUN_00611500()
{
    return m_20;
}

// FUNCTION: GAME 0x00611510
unsigned short SBPicture::FUN_00611510()
{
    return m_22;
}

// FUNCTION: GAME 0x00611520
unsigned short SBPicture::FUN_00611520()
{
    return m_24;
}

// FUNCTION: GAME 0x00611530
int SBPicture::FUN_00611530()
{
    return m_1c != 0;
}

// FUNCTION: GAME 0x00611540
void *RHUnk006114c0::FUN_00611540(unsigned flags)
{
    this->RHUnk006114c0::~RHUnk006114c0();
    if (flags & 1)
        operator delete(this);
    return this;
}

#pragma inline_depth(0)
void EmitPictureAccessors(SBPicture *picture)
{
    picture->SBPicture::FUN_006114e0();
    picture->SBPicture::FUN_006114f0();
    picture->SBPicture::FUN_00611500();
    picture->SBPicture::FUN_00611510();
    picture->SBPicture::FUN_00611520();
    picture->SBPicture::FUN_00611530();
}
#pragma inline_depth(8)

// FUNCTION: GAME 0x00611560
RHUnk006114c0::~RHUnk006114c0()
{
    *(unsigned *)this = 0x67a880;
    ((SBPicture *)this)->SBPicture::~SBPicture();
}

void RHUnk006114c0::Unk10() {}
bool RHUnk006114c0::Unk1c(SBFile &) { return false; }
bool RHUnk006114c0::Unk20(RHUnkFXDraw *draw, unsigned long surface)
{
    return ((SBPicture *)this)->SBPicture::Unk00613530(draw, surface);
}

void RHUnkFXDraw::FUN_005e5260() {}
void RHUnkFXDraw::FUN_005e6440(unsigned long, int, int, unsigned long, unsigned long) {}
int RHUnk005f4fc0::FUN_005f5090(const RHProfileText &, int) { return 0; }
// FUNCTION: GAME 0x005e3070
void ToolboxChunks::FUN_005e3070() { _Buyback(); }
// LIBRARY: GAME 0x005e2ea0
// ?substr@?$basic_string@GU?$char_traits@G@std@@V?$allocator@G@2@@std@@QBE?AV12@II@Z

// FUNCTION: GAME 0x005e31d0
ToolboxChunk **ToolboxChunks::FUN_005e31d0(unsigned int count) { return _Growmap(count); }
// TEMPLATE: GAME 0x0053dca0
// ??0const_iterator@?$deque@UToolboxChunk@@V?$allocator@UToolboxChunk@@@std@@@std@@QAE@XZ

// FUNCTION: GAME 0x0053e080
ToolboxChunkIterator::ToolboxChunkIterator(ToolboxChunk *next, ToolboxChunk **map) : m_first(*map), m_last(*map + 512), m_next(next), m_map(map) {}
