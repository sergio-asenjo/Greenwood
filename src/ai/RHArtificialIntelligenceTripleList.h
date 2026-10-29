#ifndef RHARTIFICIALINTELLIGENCETRIPLELIST_H
#define RHARTIFICIALINTELLIGENCETRIPLELIST_H

#include <iterator>

struct RHArtificialIntelligenceElement
{
    char m_00[4];
    unsigned m_flags; // +0x04
};

struct RHArtificialIntelligenceNode
{
    RHArtificialIntelligenceNode *m_next; // +0x00
    RHArtificialIntelligenceNode *m_prev; // +0x04
    RHArtificialIntelligenceElement *m_data; // +0x08
};

struct RHArtificialIntelligenceIterator : std::iterator<std::bidirectional_iterator_tag, RHArtificialIntelligenceElement *>
{
    RHArtificialIntelligenceNode *m_node;
    RHArtificialIntelligenceIterator() {}
    RHArtificialIntelligenceIterator(RHArtificialIntelligenceNode *node) : m_node(node) {}
    RHArtificialIntelligenceIterator &operator=(const RHArtificialIntelligenceIterator &other)
    {
        m_node = other.m_node;
        return *this;
    }
    RHArtificialIntelligenceIterator &operator++() { m_node = m_node->m_next; return *this; }
    RHArtificialIntelligenceIterator &operator--() { m_node = m_node->m_prev; return *this; }
};

struct RHArtificialIntelligenceTriple
{
    int m_00;
    int m_04;
    int m_08;
};

class RHArtificialIntelligenceTripleList
{
public:
    RHArtificialIntelligenceIterator insert(RHArtificialIntelligenceIterator position, const RHArtificialIntelligenceTriple &value);
};

#endif
