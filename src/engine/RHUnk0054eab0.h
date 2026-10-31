#ifndef RHUNK0054EAB0_H
#define RHUNK0054EAB0_H

#include "RHSpriteListStorage.h"
#include "SBResourceManager.h"
#include "SBGeoPoint2D.h"
#include "RHTransientPointerList.h"

class RHUnk0054eab0
{
public:
    RHUnk0054eab0();
    ~RHUnk0054eab0();
    void FUN_0054eea0(SBFile &file, void *grid);
    undefined m_00[0x1c];
    RHUnk00564020 m_1c;
    undefined m_34[0xc];
    RHUnk00564020 m_40;
    undefined m_58[0xc];
    RHUnk00564020 m_64;
    undefined m_7c[0xc];
    RHUnk00564020 m_88;
    undefined m_a0[0xc];
    RHUnk00564020 m_ac;
    undefined m_c4[0xc];
    RHUnk00564020 m_d0;
    undefined m_e8[0xc];
    RHUnk00564020 m_f4;
    undefined m_10c[0xc];
    RHUnk00564020 m_118;
    undefined m_130[0x10];
    SBGeoPoint2D m_140;
    undefined m_148[0x10];
    SBResourceSurfaceArray m_158;
    RHTransientPointerList<void> m_178;
    bool m_19c;
};

#endif
