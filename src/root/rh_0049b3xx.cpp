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

#include <math.h>
#include "RHScript.h"

#define AT(type, off) (*(type *)((char *)this + off))

class RHUnk0049b100
{
public:
    float FUN_0049b100();
    float FUN_0049b110();
    float FUN_0049b120();
    void FUN_0049b130(float scale);
    float FUN_0049b150();
    float m_0;
    float m_4;
    float m_8;
};

class RHUnk0049b200
{
public:
    void FUN_0049b200(char value);
    void FUN_0049b210(char value);
    void FUN_0049b220(char value);
    void FUN_0049b230(char value);
};

class RHUnk0049b240
{
public:
    void FUN_0049b240(int value);
    void FUN_0049b260(const RHUnk0049b100 &value);
    void FUN_0049b290();
};

class RHUnk0049b2e0
{
public:
    struct Kind2 { unsigned value : 2; };
    struct Kind4 { unsigned value : 4; };
    struct Kind5 { unsigned value : 5; };
    bool FUN_0049b2e0();
    bool FUN_0049b2f0();
    bool FUN_0049b300();
    bool FUN_0049b310();
    bool FUN_0049b320();
    bool FUN_0049b330();
};

class RHUnk0049b3b0
{
public:
    enum Kind4 { KindZero, KindMaximum = 255 };
    unsigned short FUN_0049b3b0();
    unsigned short FUN_0049b3c0();
    void FUN_0049b3d0(unsigned value);
    void FUN_0049b3f0(Kind4 value);
    void FUN_0049b4f0(unsigned char value);
};

class RHUnk0049b390
{
public:
    void FUN_0049b390(const SBGeoPoint2D &point);
    void FUN_0049b430();
    void FUN_0049b470(void *value, bool flag);
};

class RHUnk0049b690
{
public:
    void FUN_0049b690(RHUnk00585500 *value);
};

class RHUnk0049b510
{
public:
    struct Flags { unsigned char other : 5; unsigned char value : 1; };
    unsigned char FUN_0049b510();
};

class RHUnk0049b550
{
public:
    unsigned FUN_0049b550();
    void *FUN_0049b570(unsigned index);
};

class RHUnk0049b650
{
public:
    short FUN_0049b650();
};

class RHUnk0049b660
{
public:
    int FUN_0049b660();
};

class RHUnk0049b670
{
public:
    void FUN_0049b670();
};

class RHUnk0049b680
{
public:
    void FUN_0049b680(int value);
};

class RHUnk0049bb00
{
public:
    char FUN_0049bb00();
};

class RHUnk00452030;
class RHUnk005c38b0;
class RHEngine;
struct RHUnkSectorGlobal;
extern RHUnk00452030 *g_unk0x6c07fc;
extern RHUnkSectorGlobal *g_unk0x6c0a9c;
extern RHUnk005c38b0 *g_unk0x6c10e8;
extern RHEngine *g_pEngine;

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

// FUNCTION: GAME 0x0049b100
float RHUnk0049b100::FUN_0049b100() { return AT(float, 0); }

// FUNCTION: GAME 0x0049b110
float RHUnk0049b100::FUN_0049b110() { return AT(float, 4); }

// FUNCTION: GAME 0x0049b120
float RHUnk0049b100::FUN_0049b120() { return AT(float, 8); }

// FUNCTION: GAME 0x0049b130
void RHUnk0049b100::FUN_0049b130(float scale)
{
    AT(float, 0) *= scale;
    AT(float, 4) *= scale;
    AT(float, 8) *= scale;
}

// FUNCTION: GAME 0x0049b150
float RHUnk0049b100::FUN_0049b150()
{
    return (float)sqrt(AT(float, 0) * AT(float, 0) + AT(float, 4) * AT(float, 4) + AT(float, 8) * AT(float, 8));
}

// FUNCTION: GAME 0x0049b200
void RHUnk0049b200::FUN_0049b200(char value) { AT(char, 0x8c) = value; }

// FUNCTION: GAME 0x0049b210
void RHUnk0049b200::FUN_0049b210(char value) { AT(char, 0x8d) = value; }

// FUNCTION: GAME 0x0049b220
void RHUnk0049b200::FUN_0049b220(char value) { AT(char, 0x8e) = value; }

// FUNCTION: GAME 0x0049b230
void RHUnk0049b200::FUN_0049b230(char value) { AT(char, 0x8f) = value; }

// FUNCTION: GAME 0x0049b240
void RHUnk0049b240::FUN_0049b240(int value)
{
    AT(int, 4) = 1;
    AT(int, 0x14) = value;
}

// FUNCTION: GAME 0x0049b260
void RHUnk0049b240::FUN_0049b260(const RHUnk0049b100 &value)
{
    AT(int, 8) = 2;
    AT(RHUnk0049b100, 0x60) = value;
}

// FUNCTION: GAME 0x0049b290
void RHUnk0049b240::FUN_0049b290()
{
    AT(float, 0xc) += AT(float, 0x60);
    AT(float, 0x10) += AT(float, 0x64);
    AT(float, 0x14) += AT(float, 0x68);
    AT(volatile int, 4) = 1;
}

// FUNCTION: GAME 0x0049b2e0
bool RHUnk0049b2e0::FUN_0049b2e0() { return AT(Kind2, 4).value == 2; }

// FUNCTION: GAME 0x0049b2f0
bool RHUnk0049b2e0::FUN_0049b2f0() { return AT(Kind2, 4).value == 3; }

// FUNCTION: GAME 0x0049b300
bool RHUnk0049b2e0::FUN_0049b300() { return AT(Kind4, 4).value == 4; }

// FUNCTION: GAME 0x0049b310
bool RHUnk0049b2e0::FUN_0049b310() { return AT(Kind5, 4).value == 4; }

// FUNCTION: GAME 0x0049b320
bool RHUnk0049b2e0::FUN_0049b320() { return AT(Kind5, 4).value == 20; }

// FUNCTION: GAME 0x0049b330
bool RHUnk0049b2e0::FUN_0049b330() { return AT(Kind4, 4).value == 9; }

// FUNCTION: GAME 0x0049b340
char RHUnk0049b3xx::GetField12()
{
    return AT(char, 0x12);
}

// FUNCTION: GAME 0x0049b350
char RHUnk0049b3xx::GetField08() { return AT(char, 0x08); }

// FUNCTION: GAME 0x0049b390
void RHUnk0049b390::FUN_0049b390(const SBGeoPoint2D &point)
{
    ((RHActorPositionCalls *)(AT(char *, 0x50) + 4))->FUN_00464530(point);
}

// FUNCTION: GAME 0x0049b3b0
unsigned short RHUnk0049b3b0::FUN_0049b3b0() { return *(unsigned short *)(AT(char *, 0x50) + 0xde); }

// FUNCTION: GAME 0x0049b3c0
unsigned short RHUnk0049b3b0::FUN_0049b3c0() { return *(unsigned short *)(AT(char *, 0x50) + 0xd8); }

// FUNCTION: GAME 0x0049b3d0
void RHUnk0049b3b0::FUN_0049b3d0(unsigned value)
{
    char *position = AT(char *, 0x50) + 4;
    value &= 15;
    *(unsigned short *)(position + 0xd4) = value;
    *(unsigned short *)(position + 0xd6) = value;
}

// FUNCTION: GAME 0x0049b3f0
void RHUnk0049b3b0::FUN_0049b3f0(Kind4 value)
{
    *(unsigned short *)(AT(char *, 0x50) + 0xda) = value & 15;
}

// FUNCTION: GAME 0x0049b430
void RHUnk0049b390::FUN_0049b430()
{
    ((RHBonusInfoBase *)(AT(char *, 0x50) + 4))->FUN_0055f290();
}

// FUNCTION: GAME 0x0049b470
void RHUnk0049b390::FUN_0049b470(void *value, bool flag)
{
    AT(RHBonusInfo *, 0x50)->FUN_005bd560(value, flag);
}

// FUNCTION: GAME 0x0049b4c0
int RHUnk0049b3xx::GetField10() { return AT(int, 0x10); }

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

// FUNCTION: GAME 0x0049b4f0
void RHUnk0049b3b0::FUN_0049b4f0(unsigned char value) { AT(unsigned char, 0x174) &= ~value; }

// FUNCTION: GAME 0x0049b510
unsigned char RHUnk0049b510::FUN_0049b510() { return ((Flags *)(AT(char *, 0x334) + 0x5c))->value; }

// FUNCTION: GAME 0x0049b520
RHUnk00452030 *FUN_0049b520() { return g_unk0x6c07fc; }

// FUNCTION: GAME 0x0049b530
RHUnkSectorGlobal *FUN_0049b530() { return g_unk0x6c0a9c; }

// FUNCTION: GAME 0x0049b540
RHUnk005c38b0 *FUN_0049b540() { return g_unk0x6c10e8; }

// FUNCTION: GAME 0x0049b550
unsigned RHUnk0049b550::FUN_0049b550()
{
    void **first = AT(void **, 0x48dc);
    return first == 0 ? 0 : AT(void **, 0x48e0) - first;
}

// FUNCTION: GAME 0x0049b570
void *RHUnk0049b550::FUN_0049b570(unsigned index) { return AT(void **, 0x48dc)[index]; }

// FUNCTION: GAME 0x0049b580
RHEngine *FUN_0049b580() { return g_pEngine; }

// FUNCTION: GAME 0x0049b650
short RHUnk0049b650::FUN_0049b650() { return AT(short, 0xae); }

// FUNCTION: GAME 0x0049b660
int RHUnk0049b660::FUN_0049b660() { return AT(int, 0xa8); }

// FUNCTION: GAME 0x0049b670
void RHUnk0049b670::FUN_0049b670() { AT(char, 0xa8) = 0; }

// FUNCTION: GAME 0x0049b680
void RHUnk0049b680::FUN_0049b680(int value) { AT(int, 0x68) = value; }

// FUNCTION: GAME 0x0049b690
void RHUnk0049b690::FUN_0049b690(RHUnk00585500 *value) { value->Unk(this); }

// Parked: VC6 places the successful return before the shared false return.
// STUB: GAME 0x0049bb00
char RHUnk0049bb00::FUN_0049bb00()
{
    char *value = AT(char *, 0x134);
    if (value != 0)
    {
        if (*(int *)(value + 0x24) == 6)
            goto found;
    }
    return 0;
found:
    return 1;
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

void rh_emit_accessors(void *object, const RHUnk0049b100 &point)
{
    RHUnk0049b100 *vector = (RHUnk0049b100 *)object;
    vector->FUN_0049b100();
    vector->FUN_0049b110();
    vector->FUN_0049b120();
    vector->FUN_0049b130(2);
    vector->FUN_0049b150();
    RHUnk0049b200 *flags = (RHUnk0049b200 *)object;
    flags->FUN_0049b200(1);
    flags->FUN_0049b210(1);
    flags->FUN_0049b220(1);
    flags->FUN_0049b230(1);
    RHUnk0049b240 *position = (RHUnk0049b240 *)object;
    position->FUN_0049b240(1);
    position->FUN_0049b260(point);
    position->FUN_0049b290();
    RHUnk0049b2e0 *type = (RHUnk0049b2e0 *)object;
    type->FUN_0049b2e0();
    type->FUN_0049b2f0();
    type->FUN_0049b300();
    type->FUN_0049b310();
    type->FUN_0049b320();
    type->FUN_0049b330();
    RHUnk0049b3b0 *actor = (RHUnk0049b3b0 *)object;
    actor->FUN_0049b3b0();
    actor->FUN_0049b3c0();
    actor->FUN_0049b3d0(1);
    actor->FUN_0049b3f0(RHUnk0049b3b0::KindZero);
    actor->FUN_0049b4f0(1);
    ((RHUnk0049b510 *)object)->FUN_0049b510();
    ((RHUnk0049b550 *)object)->FUN_0049b550();
    ((RHUnk0049b550 *)object)->FUN_0049b570(0);
    ((RHUnk0049b650 *)object)->FUN_0049b650();
    ((RHUnk0049b660 *)object)->FUN_0049b660();
    ((RHUnk0049b670 *)object)->FUN_0049b670();
    ((RHUnk0049b680 *)object)->FUN_0049b680(0);
    ((RHUnk0049bb00 *)object)->FUN_0049bb00();
    ((RHUnk0049b390 *)object)->FUN_0049b390(*(SBGeoPoint2D *)object);
    ((RHUnk0049b390 *)object)->FUN_0049b430();
    ((RHUnk0049b390 *)object)->FUN_0049b470(0, false);
    ((RHUnk0049b690 *)object)->FUN_0049b690((RHUnk00585500 *)object);
}
