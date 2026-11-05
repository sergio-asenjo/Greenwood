#ifndef RHSEEKPOINT_H
#define RHSEEKPOINT_H

#include "RHMalignityPosition.h"
#include <vector>

class SBFile;

class RHSeekPointVector : public std::vector<unsigned short>
{
public:
    RHSeekPointVector(const std::allocator<unsigned short> &allocator = std::allocator<unsigned short>())
        : std::vector<unsigned short>(allocator) {}
    void Clear()
    {
        unsigned short *last = std::copy(end(), end(), begin());
        typedef std::vector<unsigned short> Values;
        void (Values::*destroy)(unsigned short *, unsigned short *) = &RHSeekPointVector::_Destroy;
        (this->*destroy)(last, end());
        _Last = last;
    }
    void InsertLast(const unsigned short &value)
    {
        typedef std::vector<unsigned short> Base;
        typedef iterator (Base::*Ucopy)(const_iterator, const_iterator, iterator);
        typedef void (Base::*Ufill)(iterator, unsigned, const unsigned short &);
        typedef void (Base::*Destroy)(iterator, iterator);
        typedef unsigned (Base::*Size)() const;
        Ucopy copy = &RHSeekPointVector::_Ucopy;
        Ufill fill = &RHSeekPointVector::_Ufill;
        Destroy destroy = &RHSeekPointVector::_Destroy;
        Size getSize = &Base::size;
        iterator position = end();
        if ((unsigned)(_End - _Last) < 1) {
            unsigned grow = size() > 1 ? (this->*getSize)() : 1;
            int count = (this->*getSize)() + grow;
            iterator storage = allocator.allocate(count, (void *)0);
            iterator destination = (this->*copy)(_First, position, storage);
            (this->*fill)(destination, 1, value);
            ++destination;
            (this->*copy)(position, _Last, destination);
            (this->*destroy)(_First, _Last);
            allocator.deallocate(_First, _End - _First);
            _End = storage + count;
            _Last = storage + (this->*getSize)() + 1;
            _First = storage;
        } else if ((unsigned)(_Last - position) < 1) {
            (this->*copy)(position, _Last, position + 1);
            (this->*fill)(_Last, 1 - (_Last - position), value);
            std::fill(position, _Last, value);
            ++_Last;
        } else {
            (this->*copy)(_Last - 1, _Last, _Last);
            std::copy_backward(position, _Last - 1, _Last);
            std::fill(position, position + 1, value);
            ++_Last;
        }
    }
};

class RHSeekPointIndices
{
public:
    RHSeekPointIndices() : m_dirty(true) {}
    // FUNCTION: GAME 0x00521d00
    ~RHSeekPointIndices() { m_values.clear(); }
    long FUN_005226a0(const unsigned short &value, bool forward);
    long Find(const unsigned short &value, bool forward)
    {
        m_dirty = false;
        m_value = value;
        int count = m_values.size();
        int index = 0;
        if (forward == true) {
            m_forward = true;
            m_current = m_values.begin();
            for (; index < count; ++index, ++m_current) {
                if (*m_current == m_value)
                    break;
            }
            return m_index = index < count ? index : -1;
        } else {
            m_forward = false;
            m_current = m_values.end() - 1;
            for (; count > 0; --count, --m_current) {
                if (*m_current == m_value)
                    break;
            }
            return m_index = count > 0 ? count - 1 : -1;
        }
    }
    void Add(const unsigned short &value)
    {
        if (Find(value, true) == -1) {
            m_values.InsertLast(value);
            m_dirty = true;
        }
    }
    void AddDirection(const unsigned short &value)
    {
        if (FUN_005226a0(value, true) == -1) {
            m_values.insert(m_values.end(), value);
            m_dirty = true;
        }
    }
    void AddDirections(const unsigned short &value, unsigned count)
    {
        if (FUN_005226a0(value, true) == -1) {
            m_values.insert(m_values.end(), count, value);
            m_dirty = true;
        }
    }
    RHSeekPointVector m_values;
    unsigned short *m_current;
    bool m_dirty;
    bool m_forward;
    long m_index;
    unsigned short m_value;
};

struct RHSeekPointDirectionView
{
    RHMalignityPosition position;
    unsigned short value;
};

// VTABLE: GAME 0x00679134
class RHSeekPoint
{
public:
    RHSeekPoint();
    RHSeekPoint(RHMalignityPosition *position);
    RHSeekPoint(const RHSeekPointDirectionView *source);
    virtual ~RHSeekPoint();
    bool FUN_00522070(const RHSeekPointDirectionView *source);
    bool SerializeStatus(SBFile &file);
    bool SerializeAllData(SBFile &file);
    void Emit(SBFile &file);
    RHMalignityPosition Position() const { return *(const RHMalignityPosition *)&m_4; }
    int m_4;
    int m_8;
    void *m_c;
    short m_10;
    int m_14;
    RHSeekPointIndices m_18;
    char m_38;
    char m_39;
};

#endif
