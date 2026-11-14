extern "C" int rand(void);

class RHMenuDialogue
{
public:
    static void Display(unsigned long id);
};

namespace VMCoreCustomDependencies
{
    // FUNCTION: GAME 0x005714a0
    void FUN_005714a0(int value) { RHMenuDialogue::Display(value); }
    // TEMPLATE: GAME 0x006390a0 FOLDED
    // ?Call006390a0@VMCoreCustomDependencies@@YA_NH@Z
    bool Call006390a0(int) { return false; }
    // FUNCTION: GAME 0x00577cf0
    bool FUN_00577cf0(int object, int value)
    {
        if (!value)
            return (*(unsigned *)((char *)*(void **)((char *)*(void **)((char *)object + 0x50) + 0xe0) + 0x30) >> 13) & 1;
        return *(void **)((char *)*(void **)((char *)object + 0x50) + 0xe0) == (void *)value;
    }
    void Call00578c50(int) {}
    // FUNCTION: GAME 0x00578680
    int FUN_00578680(int count) { return rand() % count; }
}

#include "RHPatchClass.h"

class RHFastFindGrid
{
public:
    void DeleteStaticRepulsivePoint(unsigned long id);
};

struct RHUnkSectorGlobal;
extern char *g_unk0x6c0fa8;
extern RHUnkSectorGlobal *g_unk0x6c0a9c;

namespace VMCoreCustomDependencies
{
    // FUNCTION: GAME 0x00570e30
    bool FUN_00570e30(int value)
    {
        ((RHPatch *)value)->FUN_00550150();
        g_unk0x6c0fa8[0x48d0] = 0;
        return true;
    }

    // FUNCTION: GAME 0x00570e50
    bool FUN_00570e50(int value)
    {
        ((RHPatch *)value)->FUN_00550220();
        g_unk0x6c0fa8[0x48d0] = 0;
        return true;
    }

    // FUNCTION: GAME 0x0057ae40
    void FUN_0057ae40(int id)
    {
        ((RHFastFindGrid *)g_unk0x6c0a9c)->DeleteStaticRepulsivePoint(id);
    }
}


#include "RHMinimapVisibilityCalls.h"

// FUNCTION: GAME 0x0054b150
void RHUnk0054b150::FUN_0054b150(bool flag, bool immediate)
{
    if (flag == true)
    {
        if (!m_120 && m_124 == 0.0f)
        {
            if (!immediate)
            {
                m_124 = 1.0f;
                m_121 = true;
            }
            else
            {
                m_124 = 0.0f;
                m_120 = true;
            }
        }
    }
    else if (flag == false)
    {
        if (m_120 == true && m_124 == 0.0f)
        {
            if (!immediate)
            {
                m_121 = false;
                m_124 = 0.1f;
            }
            else
            {
                m_120 = false;
                m_124 = 0.0f;
            }
        }
    }
}
