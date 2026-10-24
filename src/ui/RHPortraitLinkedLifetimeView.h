#ifndef RHPORTRAITLINKEDLIFETIMEVIEW_H
#define RHPORTRAITLINKEDLIFETIMEVIEW_H

#include "Decomp.h"

// SIZE 0x114
class RHPortraitLinkedLifetime
{
public:
    RHPortraitLinkedLifetime();
    ~RHPortraitLinkedLifetime();
    undefined m_00[0xd8]; // 0x00
    bool m_selected; // 0xd8
    undefined m_d9[0x3b]; // 0xd9
};

#endif
