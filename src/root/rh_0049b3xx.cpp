// Anonymous class at the 0x0049b3xx-0x0049b4xx cluster.
//
// VALIDATION (2026-10-02): this cluster has NO __FILE__ evidence in
// symbols/functions-by-file.tsv. It must NOT be labelled RHSprite — the real
// rhsprite.cpp functions live at 0x5b5xxx (see functions-by-file.tsv).
// The class name is therefore unknown until evidence proves it.
//
// The five getters below were located by disassembly; offsets are exact, but
// member and method identity are unproven. Neutral names until then.
//
// Target offsets (from Game.exe):
//   0x0049b350 -> byte  [ecx + 0x08]
//   0x0049b4c0 -> dword [ecx + 0x10]
//   0x0049b340 -> byte  [ecx + 0x12]
//   0x0049b4d0 -> dword [ecx + 0x64]
//   0x0049b4e0 -> byte  [ecx + 0x148]

#define AT(type, off) (*(type *)((char *)this + off))

class RHUnk0049b3xx
{
public:
    char GetField08();
    int GetField10();
    char GetField12();
    int GetField64();
    char GetField148();
    void Emit();
};

// FUNCTION: GAME 0x0049b350
char RHUnk0049b3xx::GetField08()
{
    return AT(char, 0x08);
}

// FUNCTION: GAME 0x0049b4c0
int RHUnk0049b3xx::GetField10()
{
    return AT(int, 0x10);
}

// FUNCTION: GAME 0x0049b340
char RHUnk0049b3xx::GetField12()
{
    return AT(char, 0x12);
}

// FUNCTION: GAME 0x0049b4d0
int RHUnk0049b3xx::GetField64()
{
    return AT(int, 0x64);
}

// FUNCTION: GAME 0x0049b4e0
char RHUnk0049b3xx::GetField148()
{
    return AT(char, 0x148);
}

void RHUnk0049b3xx::Emit()
{
    GetField08();
    GetField10();
    GetField12();
    GetField64();
    GetField148();
}

RHUnk0049b3xx g_unk49b3xx;

void rh_emit_getters()
{
    g_unk49b3xx.Emit();
}
