#ifndef RHUNKSECTORGLOBAL_H
#define RHUNKSECTORGLOBAL_H

struct RHUnkSectorGlobal
{
    char m_pad0[0x4064];
    void **m_4064;
    char m_pad4068[0x11c];
    void *m_4184;
};

extern RHUnkSectorGlobal *g_unk0x6c0a9c;

#endif
