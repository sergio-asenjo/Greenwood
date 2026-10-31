#include "SBNullstr.h"
#include "RHLoadingScreen.h"

// LIBRARY: GAME 0x00642913
extern "C" int sprintf(char *, const char *, ...) { return 0; }

// LIBRARY: GAME 0x0063f890
// ??1?$basic_string@GU?$char_traits@G@std@@V?$allocator@G@2@@std@@QAE@XZ

// LIBRARY: GAME 0x0064159a
// ?_Xlen@std@@YAXXZ

// VTABLE: GAME 0x0067bd10
// class std::length_error

// STRING: GAME 0x0067bd1c
// "string too long"

// Throw-info data; bound by name only.
// STUB: GAME 0x006a4638 SYMBOL
// __TI3?AVlength_error@std@@

// Constructor 0x00613e90 is shared with RHTitbits_stubs.cpp.
void RHUnkFXDraw::Unk005e5160(unsigned long) {}
void RHUnk006114c0::Unk04() {}
void RHUnk006114c0::Unk08() {}
void RHUnk006114c0::Unk0c() {}
void RHUnk006114c0::Unk14() {}
void RHUnk006114c0::Unk18() {}
void RHUnk006114c0::Unk1c() {}
