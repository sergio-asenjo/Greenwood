#ifndef SBRESOURCEUNKKEYTREE_H
#define SBRESOURCEUNKKEYTREE_H

struct SBResourceUnkKeyNode
{
    char m_00[0x0c];
    unsigned long m_key;
};

struct SBResourceUnkKeyIterator
{
    SBResourceUnkKeyNode *m_node;
    SBResourceUnkKeyIterator() {}
    SBResourceUnkKeyIterator(SBResourceUnkKeyNode *node) : m_node(node) {}
    bool operator!=(const SBResourceUnkKeyIterator &other) const { return m_node != other.m_node; }
    void FUN_00617ed0();
    SBResourceUnkKeyIterator operator++(int)
    {
        SBResourceUnkKeyIterator previous = *this;
        FUN_00617ed0();
        return previous;
    }
};

class SBResourceUnkTreeEnd
{
public:
    char m_00[4];
    SBResourceUnkKeyNode *m_head;
    SBResourceUnkKeyIterator FUN_00617690();
};

#endif
