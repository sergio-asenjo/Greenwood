#include "SBUIRenderer.h"
#include "SBUIRendererListbox.h"
#include "RHUIRendererShifting.h"

class RHUnk005ef320;
extern RHUnk005ef320 *g_unk0x6c11d0;

class RHUnk005e6440
{
public:
    void Blit(unsigned long, SBGeoBoundingBox2D *, unsigned long,
        SBGeoBoundingBox2D *, unsigned long);
};

// FUNCTION: GAME 0x0060d500
unsigned int SBUIUnk0060d530::FUN_0060d500(unsigned int id)
{
    m_resource->GetSurfaceForResource(m_resourceId, id, id);
    return id;
}

// FUNCTION: GAME 0x0060d520
void SBUIUnk0060d530::FUN_0060d520()
{
    ((SBUIUnk005fd4a0 *)m_resource)->FUN_005fd4a0(m_resourceId);
}

// FUNCTION: GAME 0x0060d530
void SBUIUnk0060d530::FUN_0060d530(unsigned int surface)
{
    *(RHUnk005ef320 **)(m_bytes + 0x1c) = g_unk0x6c11d0;
    *(unsigned int *)(m_bytes + 0x20) = surface;
}

// FUNCTION: GAME 0x0060d690
void *SBUIUnk0060d530::FUN_0060d690()
{
    return m_bytes + 8;
}

// FUNCTION: GAME 0x0060da20
bool SBUIUnk0060da20::FUN_0060da20(unsigned int id)
{
    *(unsigned int *)(m_bytes + 0x3c) = id;
    if (id == 0xff)
    {
        ((unsigned int *)(m_bytes + 0x40))[*(unsigned int *)(m_bytes + 0x48) & 1] = 0;
        return false;
    }
    unsigned int surface;
    if (m_resource->GetSurfaceForResource(m_resourceId, id, surface) != true)
    {
        SBAssert(0,
            // STRING: GAME 0x006bb558
            "P:\\Robin Hood\\SBLibNG\\SBUIRenderer.cpp", 0x13e,
            "Unable to retrieve a resource for the bitmap renderer");
        return false;
    }
    ((unsigned int *)(m_bytes + 0x40))[*(unsigned int *)(m_bytes + 0x48) & 1] = surface;
    if (surface)
        ((RHUnk005e6440 *)m_draw)->Blit(surface, 0, m_unk20, &m_box, 1);
    return true;
}

// FUNCTION: GAME 0x0060dae0
bool SBUIUnk0060dae0::FUN_0060dae0(unsigned int id)
{
    *(unsigned int *)(m_bytes + 0x3c) = id;
    if (id != 0xff && m_resourceId != -1)
    {
        unsigned int surface;
        if (m_resource->GetSurfaceForResource(m_resourceId, id, surface) != true)
        {
            SBAssert(0, "P:\\Robin Hood\\SBLibNG\\SBUIRenderer.cpp", 0x173,
                "Unable to retrieve a resource for the bitmap renderer");
            return false;
        }
        ((unsigned int *)(m_bytes + 0x40))[*(unsigned int *)(m_bytes + 0x48) & 1] = surface;
        if (surface)
            m_draw->BlitAlphaKeying(surface, 0, m_unk20, &m_box,
                *(unsigned short *)(m_bytes + 0x4c), *(unsigned short *)(m_bytes + 0x4e), 1);
        return true;
    }
    ((unsigned int *)(m_bytes + 0x40))[*(unsigned int *)(m_bytes + 0x48) & 1] = 0;
    return false;
}

// FUNCTION: GAME 0x0060db80
unsigned int SBUIUnk0060dae0::FUN_0060db80(unsigned int id)
{
    m_resource->GetSurfaceForResource(m_resourceId, id, id);
    if (((unsigned int *)(m_bytes + 0x40))[*(unsigned int *)(m_bytes + 0x48) & 1] != id)
        id = -1;
    return id;
}

// FUNCTION: GAME 0x0060dc20
int SBUIUnk0060dd00::FUN_0060dc20(unsigned int id)
{
    int result = 0;
    if (m_bytes[0x78] == 1)
        return -1;
    unsigned int index = id;
    unsigned int value;
    switch (index) {
    case 0: value = *(unsigned int *)(m_bytes + 0x54); break;
    case 1: value = *(unsigned int *)(m_bytes + 0x50); break;
    case 2: value = *(unsigned int *)(m_bytes + 0x58); break;
    case 3: value = *(unsigned int *)(m_bytes + 0x5c); break;
    }
    if (value)
        result = index + 1;
    return result;
}

// FUNCTION: GAME 0x0060dcd0
int SBUIUnk0060dd00::FUN_0060dcd0()
{
    if (*(SBUIListboxUnk0061e890 **)(m_bytes + 0x50)) {
        int value = FUN_0060dda0(*(SBUIListboxUnk0061e890 **)(m_bytes + 0x50), true);
        return (*(SBUIListboxUnk0061e890 **)(m_bytes + 0x50))->FUN_0061e890() * value;
    }
    return 0;
}

// FUNCTION: GAME 0x0060dd00
void *SBUIUnk0060dd00::FUN_0060dd00()
{
    return m_bytes + 0x68;
}

// FUNCTION: GAME 0x0060e0d0
bool SBUIUnk0060dd00::FUN_0060e0d0(void *first, void *second, void *third, void *fourth)
{
    *(void **)(m_bytes + 0x54) = first;
    *(void **)(m_bytes + 0x50) = second;
    *(void **)(m_bytes + 0x58) = third;
    *(void **)(m_bytes + 0x5c) = fourth;
    return true;
}

void EmitSBUIRenderer(SBUIUnk0060da20 *bitmap, SBUIUnk0060dae0 *alpha,
    SBUIUnk0060d530 *base, SBUIUnk0060dd00 *text)
{
    base->FUN_0060d500(0);
    base->FUN_0060d520();
    base->FUN_0060d530(0);
    base->FUN_0060d690();
    bitmap->FUN_0060da20(0);
    alpha->FUN_0060dae0(0);
    alpha->FUN_0060db80(0);
    text->FUN_0060dc20(0);
    text->FUN_0060dcd0();
    text->FUN_0060dd00();
    text->FUN_0060e0d0(0, 0, 0, 0);
}
