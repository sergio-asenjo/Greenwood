// Anonymous cluster at 0x0040bxxx-0x0040exxx.
// No __FILE__ or oracle evidence: class and method identity are unproven.
// Member offsets are exact from Game.exe.

#include "../script/RHScript.h"

class RHUnk0040bf00
{
public:
    void FUN_0040bf90(unsigned char value);
    char m_0[0x174];
    unsigned char m_174;
};

// FUNCTION: GAME 0x0040bf90
void RHUnk0040bf00::FUN_0040bf90(unsigned char value)
{
    m_174 |= value;
}

class RHUnk0040bc00List
{
public:
    RHUnk0040bc00List *m_next;
    RHUnk0040bc00List *m_prev;
    char m_08[0x10];
};

class RHUnk0040bc00
{
public:
    RHUnk0040bc00(const char *value);
    char m_0;
    char m_1[3];
    RHUnk0040bc00List *m_4;
    int m_8;
};

// FUNCTION: GAME 0x0040bc00
RHUnk0040bc00::RHUnk0040bc00(const char *value)
{
    m_0 = *value;
    RHUnk0040bc00List *list = new RHUnk0040bc00List;
    list->m_next = list;
    list->m_prev = list;
    m_4 = list;
    m_8 = 0;
}

// FUNCTION: GAME 0x0040eda0
bool FUN_0040eda0(const RHMalignityPosition *value, RHMalignityPosition other)
{
    return value->x == other.x && value->y == other.y && value->area == other.area && value->layer == other.layer;
}

void EmitRHUnk0040bf00(RHUnk0040bf00 *object)
{
    object->FUN_0040bf90(0);
}

void EmitRHUnk0040ed00(const RHMalignityPosition *object)
{
    FUN_0040eda0(object, *object);
}
