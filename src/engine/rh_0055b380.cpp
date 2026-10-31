// Anonymous cluster at 0x0055b380.
// No __FILE__ or oracle evidence: class and method identity are unproven.
// Member offsets are exact from Game.exe.

#include "Decomp.h"
#include "SBGeoVector2D.h"
#include <vector>
#include "RHCampaignPointerArray.h"
#include "SBResourceManager.h"
#include "RHCampaignArrayOps.h"

#include "RHUnk0055b830Values.h"

class RHUnk0055b830
{
public:
    RHUnk0055b830Values m_values;

    RHUnk0055b830(const RHUnk0055b830 &other)
    {
        const unsigned long *last = other.m_values.end();
        const unsigned long *first = other.m_values.begin();
        m_values.clear();
        m_values.Insert(m_values.begin(), first, last);
        m_values.m_dirty = true;
    }
    ~RHUnk0055b830() { m_values.clear(); }
    RHUnk0055b830 &operator=(const RHUnk0055b830 &other)
    {
        if (&other != this)
        {
            m_values.clear();
            ((SBResourceSurfaceArray *)this)->Assign(*(const SBResourceSurfaceArray *)&other, 0);
        }
        return *this;
    }
};

DECOMP_SIZE_ASSERT(RHUnk0055b830Values, 0x20)
DECOMP_SIZE_ASSERT(RHUnk0055b830, 0x20)

// FUNCTION: GAME 0x004ff590
void RHUnk0055b830Values::Resize(unsigned count)
{
    unsigned long value = 0;
    if (size() < count)
        Insert(end(), count - size(), value);
    else if (count < size())
        erase(begin() + count, end());
    m_dirty = true;
}

// TEMPLATE: GAME 0x0051d120 FOLDED
// ??1RHUnk0055b830@@QAE@XZ

namespace std
{
    template<> void _Construct(RHUnk0055b830 *, const RHUnk0055b830 &);
    template<> void vector<RHUnk0055b830>::insert(RHUnk0055b830 *, unsigned, const RHUnk0055b830 &);
}

// TEMPLATE: GAME 0x0055b830
// ?_Construct@std@@YAXPAVRHUnk0055b830@@ABV2@@Z
template<> void std::_Construct(RHUnk0055b830 *destination, const RHUnk0055b830 &source)
{
    new (destination) RHUnk0055b830(source);
}

// TEMPLATE: GAME 0x0055b570
// ?insert@?$vector@VRHUnk0055b830@@V?$allocator@VRHUnk0055b830@@@std@@@std@@QAEXPAVRHUnk0055b830@@IABV3@@Z
template<> void std::vector<RHUnk0055b830>::insert(RHUnk0055b830 *position, unsigned count,
    const RHUnk0055b830 &value)
{
    if ((unsigned)(_End - _Last) < count)
    {
        unsigned capacity = size() + (count < size() ? size() : count);
        RHUnk0055b830 *storage = allocator.allocate(capacity, 0);
        RHUnk0055b830 *next = _Ucopy(_First, position, storage);
        _Ufill(next, count, value);
        _Ucopy(position, _Last, next + count);
        _Destroy(_First, _Last);
        allocator.deallocate(_First, _End - _First);
        _End = storage + capacity;
        _Last = storage + size() + count;
        _First = storage;
    }
    else if ((unsigned)(_Last - position) < count)
    {
        _Ucopy(position, _Last, position + count);
        _Ufill(_Last, count - (_Last - position), value);
        RHUnk0055b830 *last = _Last;
        for (RHUnk0055b830 *current = position; current != last; ++current)
            if (&value != current)
            {
                ((RHCampaignArrayOps *)current)->FUN_0044ea70();
                ((SBResourceSurfaceArray *)current)->Assign(*(const SBResourceSurfaceArray *)&value, 0);
            }
        _Last += count;
    }
    else if (0 < count)
    {
        _Ucopy(_Last - count, _Last, _Last);
        RHUnk0055b830 *first = _Last - count;
        RHUnk0055b830 *destination = _Last;
        while (position != first)
        {
            --first;
            --destination;
            if (first != destination)
            {
                ((RHCampaignArrayOps *)destination)->FUN_0044ea70();
                ((SBResourceSurfaceArray *)destination)->Assign(*(const SBResourceSurfaceArray *)first, 0);
            }
        }
        for (RHUnk0055b830 *current = position; current != position + count; ++current)
            if (&value != current)
            {
                typedef std::vector<int, std::allocator<int> > Values;
                int *(Values::*erase)(int *, int *) = &Values::erase;
                (((Values *)&current->m_values)->*erase)((int *)current->m_values.begin(), (int *)current->m_values.end());
                ((SBResourceSurfaceArray *)current)->Assign(*(const SBResourceSurfaceArray *)&value, 0);
            }
        _Last += count;
    }
}

void EmitPathPointerArrayInsert(std::vector<RHUnk0055b830> &values, RHUnk0055b830 *position,
    unsigned count, const RHUnk0055b830 &value)
{
    void (std::vector<RHUnk0055b830>::*insert)(RHUnk0055b830 *, unsigned, const RHUnk0055b830 &) = &std::vector<RHUnk0055b830>::insert;
    (values.*insert)(position, count, value);
}

class RHUnk0055b320 : public std::vector<SBGeoPoint2D>
{
public:
    RHUnk0055b320();
    undefined4 m_10;
    bool m_14;
    undefined m_18[4];
    SBGeoVector2D m_1c;
};

// FUNCTION: GAME 0x0055b320
RHUnk0055b320::RHUnk0055b320() : m_14(true)
{
}

class RHUnk0055b380
{
public:
    RHUnk0055b380();
    void FUN_0055b4d0();
    char m_0;
    char m_1[3];
    int m_4;
    int m_8;
    int m_c;
    char m_10[4];
    bool m_14;
    char m_15[3];
    char m_18[4];
    char m_1c;
    char m_1d[3];
    int m_20;
    int m_24;
    int m_28;
    char m_2c[4];
    bool m_30;
};

// FUNCTION: GAME 0x0055b380
RHUnk0055b380::RHUnk0055b380()
{
    char first;
    char second;
    m_0 = first;
    m_4 = 0;
    m_8 = 0;
    m_c = 0;
    m_14 = true;
    *(char volatile *)&m_1c = second;
    m_20 = 0;
    m_24 = 0;
    m_28 = 0;
    m_30 = 1;
}

// FUNCTION: GAME 0x0055b4d0
void RHUnk0055b380::FUN_0055b4d0()
{
    unsigned char *last = (unsigned char *)m_8;
    unsigned char *first = (unsigned char *)m_4;
    while (first != last)
    {
        ((SBResourceArrayLifecycle44 *)first)->FUN_0051d120();
        first += 0x20;
    }
    operator delete((void *)m_4);
    m_4 = 0;
    m_8 = 0;
    m_c = 0;
}
