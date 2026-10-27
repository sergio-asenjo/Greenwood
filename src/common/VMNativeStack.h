#ifndef VMNATIVESTACK_H
#define VMNATIVESTACK_H

#include <new>

struct VMNativeStack
{
    VMNativeStack() : m_data(new char[48]), m_size(0), m_result(0) {}
    ~VMNativeStack()
    {
        if (m_data)
            operator delete(m_data);
    }
    char *m_data;
    int m_size;
    int m_result;
};

#endif
