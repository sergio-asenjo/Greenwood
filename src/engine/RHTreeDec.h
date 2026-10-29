#ifndef RH_TREE_DEC_H
#define RH_TREE_DEC_H

struct RHTreeDecNode20
{
    RHTreeDecNode20 *m_00;
    RHTreeDecNode20 *m_04;
    RHTreeDecNode20 *m_08;
    int m_0c;
    int m_10;
    int m_14;
    int m_18;
    int m_1c;
    int m_20;
};

struct RHTreeDecNode34
{
    RHTreeDecNode34 *m_00;
    RHTreeDecNode34 *m_04;
    RHTreeDecNode34 *m_08;
    int m_0c;
    int m_10;
    int m_14;
    int m_18;
    int m_1c;
    int m_20;
    int m_24;
    int m_28;
    int m_2c;
    int m_30;
    int m_34;
};

struct RHTreeDecNode14
{
    RHTreeDecNode14 *m_00;
    RHTreeDecNode14 *m_04;
    RHTreeDecNode14 *m_08;
    int m_0c;
    int m_10;
    int m_14;
};

extern RHTreeDecNode14 *g_unk0x006c0a3c;

struct RHTreeDec004bde30
{
    RHTreeDecNode14 *m_node;
    void FUN_004bde30();
};

struct RHTreeInc004bdef0
{
    RHTreeDecNode14 *m_node;
    void FUN_004bdef0();
};

struct RHTreeDecNode10
{
    RHTreeDecNode10 *m_00;
    RHTreeDecNode10 *m_04;
    RHTreeDecNode10 *m_08;
    int m_0c;
    int m_10;
};

extern RHTreeDecNode10 *g_unk0x006c1088;

struct RHTreeInc005aa7b0
{
    RHTreeDecNode10 *m_node;
    void FUN_005aa7b0();
};

struct RHTreeDec005b5720
{
    RHTreeDecNode10 *m_node;
    void FUN_005b5720();
};

struct RHTreeDec005038a0
{
    RHTreeDecNode20 *m_node;
    void FUN_005038a0();
};

struct RHTreeDec005c1660
{
    RHTreeDecNode34 *m_node;
    void FUN_005c1660();
};

#endif
