#ifndef RHCAMPAIGNPOINTERARRAY_H
#define RHCAMPAIGNPOINTERARRAY_H

#include <vector>

class RHScriptFXArray
{
public:
    int grow;
    void **first;
    void **last;
    void **end;
    void **Unk004fe420(void **first, void **last, void **destination);
    void Unk004fe450(void **destination, unsigned count, void *const &value);
    void Unk005008e0(void **first, void **last);
};

class RHFastFindGateArray : public RHScriptFXArray
{
public:
    unsigned FUN_0059fbc0()
    {
        typedef unsigned (std::vector<unsigned long>::*Size)() const;
        Size size = &std::vector<unsigned long>::size;
        return (((const std::vector<unsigned long> *)this)->*size)();
    }
};

template<class T>
class RHCampaignPointerArray
{
public:
    char m_allocator[4];
    T *m_first;
    T *m_last;
    T *m_end;
    T *begin() { return m_first; }
    T *end() { return m_last; }
    unsigned size() { return m_first == 0 ? 0 : m_last - m_first; }
    T *erase(T *first, T *last)
    {
        T *next = copy(last, end(), first);
        Destroy(next, end());
        m_last = next;
        return first;
    }
    void Destroy(T *first, T *last)
    {
        for (; first != last; ++first)
            ;
    }
    static T *copy(T *source, T *last, T *destination)
    {
        while (source != last)
        {
            *destination = *source;
            ++destination;
            ++source;
        }
        return destination;
    }
    void insert(T *position, unsigned count, const T &value)
    {
        RHScriptFXArray *array = (RHScriptFXArray *)this;
        RHFastFindGateArray *sizes = (RHFastFindGateArray *)this;
        if ((unsigned)(m_end - m_last) < count)
        {
            unsigned grow = count < size() ? size() : count;
            int capacity = sizes->FUN_0059fbc0() + grow;
            T *storage = std::_Allocate(capacity, (T *)0);
            T *destination = (T *)array->Unk004fe420((void **)m_first, (void **)position, (void **)storage);
            array->Unk004fe450((void **)destination, count, reinterpret_cast<void *const &>(value));
            array->Unk004fe420((void **)position, (void **)m_last, (void **)(destination + count));
            array->Unk005008e0((void **)m_first, (void **)m_last);
            operator delete(m_first);
            m_end = storage + capacity;
            m_last = storage + sizes->FUN_0059fbc0() + count;
            m_first = storage;
        }
        else if ((unsigned)(m_last - position) < count)
        {
            array->Unk004fe420((void **)position, (void **)m_last, (void **)(position + count));
            array->Unk004fe450((void **)m_last, count - (m_last - position), reinterpret_cast<void *const &>(value));
            T *last = m_last;
            for (T *destination = position; destination != last; ++destination)
                *destination = value;
            m_last += count;
        }
        else if (count > 0)
        {
            array->Unk004fe420((void **)(m_last - count), (void **)m_last, (void **)m_last);
            T *source = m_last - count;
            T *destination = m_last;
            while (position != source)
                *--destination = *--source;
            for (destination = position; destination != position + count; ++destination)
                *destination = value;
            m_last += count;
        }
    }
};

#endif
