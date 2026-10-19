#include "SBNullstr.h"
#include "RHSoundCacheCore.h"
#include "RHTreeDec.h"

struct RHTreeDecNode14
{
    RHTreeDecNode14 *m_00;
    RHTreeDecNode14 *m_04;
    RHTreeDecNode14 *m_08;
    int m_0c;
    int m_10;
    int m_14;
};

// GLOBAL: GAME 0x006c1088
RHTreeDecNode10 *g_unk0x006c1088 = 0;
// GLOBAL: GAME 0x006c0a3c
RHTreeDecNode14 *g_unk0x006c0a3c = 0;
// GLOBAL: GAME 0x006c0ae8
RHTreeDecNode20 *g_unk0x006c0ae8 = 0;
// GLOBAL: GAME 0x006c10e0
RHTreeDecNode34 *g_unk0x006c10e0 = 0;

static inline RHTreeDecNode10 *&RHTreeDecLeft10(RHTreeDecNode10 *value) { return value->m_00; }
static inline RHTreeDecNode14 *&RHTreeDecLeft14(RHTreeDecNode14 *value) { return value->m_00; }
static inline RHTreeDecNode20 *&RHTreeDecLeft20(RHTreeDecNode20 *value) { return value->m_00; }
static inline RHTreeDecNode34 *&RHTreeDecLeft34(RHTreeDecNode34 *value) { return value->m_00; }

static inline RHTreeDecNode10 *RHTreeDecMax10(RHTreeDecNode10 *node)
{
    RHUnk00641782Lock lock;
    while (node->m_08 != g_unk0x006c1088)
        node = node->m_08;
    return node;
}

static inline RHTreeDecNode14 *RHTreeDecMax14(RHTreeDecNode14 *node)
{
    RHUnk00641782Lock lock;
    while (node->m_08 != g_unk0x006c0a3c)
        node = node->m_08;
    return node;
}

static inline RHTreeDecNode20 *RHTreeDecMaxA8(RHTreeDecNode20 *node)
{
    RHUnk00641782Lock lock;
    while (node->m_08 != g_unk0x006c0ae8)
        node = node->m_08;
    return node;
}

static inline RHTreeDecNode34 *RHTreeDecMax34(RHTreeDecNode34 *node)
{
    RHUnk00641782Lock lock;
    while (node->m_08 != g_unk0x006c10e0)
        node = node->m_08;
    return node;
}

struct RHTreeDec004bde30
{
    RHTreeDecNode14 *m_node;
    void FUN_004bde30();
};

// FUNCTION: GAME 0x004bde30
void RHTreeDec004bde30::FUN_004bde30()
{
    RHUnk00641782Lock lock;
    if (m_node->m_14 == 0 && m_node->m_04->m_04 == m_node)
        m_node = m_node->m_08;
    else if (RHTreeDecLeft14(m_node) != g_unk0x006c0a3c)
        m_node = RHTreeDecMax14(RHTreeDecLeft14(m_node));
    else
    {
        RHTreeDecNode14 *parent;
        while (m_node == (parent = m_node->m_04)->m_00)
            m_node = parent;
        m_node = parent;
    }
}

struct RHTreeInc004bdef0
{
    RHTreeDecNode14 *m_node;
    void FUN_004bdef0();
};

static inline RHTreeDecNode14 *RHTreeMinimumA3c(RHTreeDecNode14 *node)
{
    RHUnk00641782Lock lock;
    while (node->m_00 != g_unk0x006c0a3c)
        node = node->m_00;
    return node;
}

// FUNCTION: GAME 0x004bdef0
void RHTreeInc004bdef0::FUN_004bdef0()
{
    RHUnk00641782Lock lock;
    if (m_node->m_08 != g_unk0x006c0a3c)
        m_node = RHTreeMinimumA3c(m_node->m_08);
    else {
        RHTreeDecNode14 *parent;
        while (m_node == (parent = m_node->m_04)->m_08)
            m_node = parent;
        if (m_node->m_08 != parent)
            m_node = parent;
    }
}

// FUNCTION: GAME 0x005038a0
void RHTreeDec005038a0::FUN_005038a0()
{
    RHUnk00641782Lock lock;
    if (m_node->m_20 == 0 && m_node->m_04->m_04 == m_node)
        m_node = m_node->m_08;
    else if (RHTreeDecLeft20(m_node) != g_unk0x006c0ae8)
        m_node = RHTreeDecMaxA8(RHTreeDecLeft20(m_node));
    else
    {
        RHTreeDecNode20 *parent;
        while (m_node == (parent = m_node->m_04)->m_00)
            m_node = parent;
        m_node = parent;
    }
}

static inline RHTreeDecNode10 *RHTreeMinimum1088(RHTreeDecNode10 *node)
{
    RHUnk00641782Lock lock;
    while (node->m_00 != g_unk0x006c1088)
        node = node->m_00;
    return node;
}

// FUNCTION: GAME 0x005aa7b0
void RHTreeInc005aa7b0::FUN_005aa7b0()
{
    RHUnk00641782Lock lock;
    if (m_node->m_08 != g_unk0x006c1088)
        m_node = RHTreeMinimum1088(m_node->m_08);
    else {
        RHTreeDecNode10 *parent;
        while (m_node == (parent = m_node->m_04)->m_08)
            m_node = parent;
        if (m_node->m_08 != parent)
            m_node = parent;
    }
}

// FUNCTION: GAME 0x005b5720
void RHTreeDec005b5720::FUN_005b5720()
{
    RHUnk00641782Lock lock;
    if (m_node->m_10 == 0 && m_node->m_04->m_04 == m_node)
        m_node = m_node->m_08;
    else if (RHTreeDecLeft10(m_node) != g_unk0x006c1088)
        m_node = RHTreeDecMax10(RHTreeDecLeft10(m_node));
    else
    {
        RHTreeDecNode10 *parent;
        while (m_node == (parent = m_node->m_04)->m_00)
            m_node = parent;
        m_node = parent;
    }
}

// FUNCTION: GAME 0x005c1660
void RHTreeDec005c1660::FUN_005c1660()
{
    RHUnk00641782Lock lock;
    if (m_node->m_34 == 0 && m_node->m_04->m_04 == m_node)
        m_node = m_node->m_08;
    else if (RHTreeDecLeft34(m_node) != g_unk0x006c10e0)
        m_node = RHTreeDecMax34(RHTreeDecLeft34(m_node));
    else
    {
        RHTreeDecNode34 *parent;
        while (m_node == (parent = m_node->m_04)->m_00)
            m_node = parent;
        m_node = parent;
    }
}

void EmitRHTreeDec()
{
    RHTreeInc004bdef0 firstIncrement;
    firstIncrement.FUN_004bdef0();
    RHTreeInc005aa7b0 secondIncrement;
    secondIncrement.FUN_005aa7b0();
    RHTreeDec005b5720 zeroth;
    zeroth.FUN_005b5720();
    RHTreeDec004bde30 first;
    first.FUN_004bde30();
    RHTreeDec005038a0 second;
    second.FUN_005038a0();
    RHTreeDec005c1660 third;
    third.FUN_005c1660();
}
