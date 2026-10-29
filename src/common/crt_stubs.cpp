// CRT seed: the original Game.exe statically links its own operator new at
// 0x006428b5 (Ghidra: operator_new, class LIBRARY). Defining it here gives the
// recompiled binary a local `??2@YAPAXI@Z` at a matching entity, so reccmp can
// resolve the `call` operand in RHSword::SerializePointer instead of leaving a
// placeholder on one side. LIBRARY functions are not compared, so the body is
// a minimal stand-in.

extern "C" void *malloc(unsigned int);

// LIBRARY: GAME 0x006428b5
// ??2@YAPAXI@Z

// LIBRARY: GAME 0x0064158f
// ??3@YAXPAX@Z

void *operator new(unsigned int size)
{
    return malloc(size);
}
