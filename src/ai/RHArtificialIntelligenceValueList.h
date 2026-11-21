#ifndef RHARTIFICIALINTELLIGENCEVALUELIST_H
#define RHARTIFICIALINTELLIGENCEVALUELIST_H

template <class T> struct RHArtificialIntelligenceValueNode
{
    RHArtificialIntelligenceValueNode *m_next;
    RHArtificialIntelligenceValueNode *m_previous;
    T m_value;
};

template <class T> struct RHArtificialIntelligenceValueList
{
    struct Iterator
    {
        RHArtificialIntelligenceValueNode<T> *node;
    };
    Iterator Insert(Iterator position, const T &value);
    void Append(const T &value);
    int m_allocator;
    RHArtificialIntelligenceValueNode<T> *m_head;
    unsigned m_count;
    RHArtificialIntelligenceValueNode<T> *m_current;
    bool m_dirty;
    char m_11[3];
    int m_index;
    void clear();
    T &operator[](unsigned index);
};

#endif
