#ifndef RHPORTRAITANIMATED_H
#define RHPORTRAITANIMATED_H

#include "RHWidgetStateMap.h"
#include "RHUnk00641782.h"

extern RHUnk00514e10::Node *g_unk0x006c0b48;
extern unsigned g_unk0x006c0b4c;

inline void RHPortraitClearMap(RHUnk00514e10 &map)
{
    map.FUN_00514ec0(RHUnk00514e10::Iterator(map.m_head->left), RHUnk00514e10::Iterator(map.m_head));
    void *allocation = map.m_head;
    operator delete(allocation);
    map.m_head = 0;
    map.m_size = 0;
}

class RHPortraitAnimated
{
public:
    RHPortraitAnimated(int id);
    ~RHPortraitAnimated()
    {
        RHUnk00514e10 &map = m_map;
        RHPortraitClearMap(map);
        {
            RHUnk00641782 guard;
            if (--g_unk0x006c0b4c == 0)
            {
                void *allocation = g_unk0x006c0b48;
                operator delete(allocation);
                g_unk0x006c0b48 = 0;
            }
        }
    }
    int m_id;
    RHUnk00514e10 m_map;
    int m_state;
    char m_handled;
};

#endif
