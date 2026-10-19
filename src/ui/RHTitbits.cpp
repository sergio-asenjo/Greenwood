#include "SBNullstr.h"
#include "RHTitbits.h"
#include "RHEngine.h"
#include <list>
#include <iterator>

struct RHUnk005c9010Iterator;
void FUN_005c9010(RHUnk005c9010Iterator &, int, std::bidirectional_iterator_tag);

struct RHScriptNode;
struct RHScriptIter
{
    RHScriptNode *node;
    RHScriptIter(RHScriptNode *value) : node(value) {}
};

class RHUnk0046eb30
{
public:
    RHScriptIter FUN_0046eb80();
    RHScriptIter erase(RHScriptIter position);
};

struct RHTitbitCursor : std::iterator<std::bidirectional_iterator_tag, RHTitbit>
{
    RHTitbitNode *node;
    RHTitbitCursor(RHTitbitNode *value = 0) : node(value) {}
    RHTitbitCursor &operator=(const RHTitbitCursor &other)
    {
        node = other.node;
        return *this;
    }
    RHTitbitCursor &AssignNode(RHTitbitNode *value)
    {
        *(RHTitbitNode *volatile *)&node = value;
        return *this;
    }
    RHTitbitCursor &operator++() { node = node->m_next; return *this; }
    RHTitbitCursor &operator--() { node = node->m_prev; return *this; }
    RHTitbit &operator*() { return node->m_data; }
};

class RHTitbitAccess
{
public:
    RHTitbitCursor Begin()
    {
        RHTitbitNode *head = ((RHTitbitList *)this)->m_head;
        RHTitbitNode *first = *(RHTitbitNode *volatile *)&head->m_next;
        return RHTitbitCursor(first);
    }
    RHTitbitCursor End()
    {
        RHTitbitNode *head = *(RHTitbitNode *volatile *)&((RHTitbitList *)this)->m_head;
        return RHTitbitCursor(head);
    }
    RHTitbit &Get(int index, bool removing = false)
    {
        int count = m_list.size();
        if (m_dirty)
        {
            if (index <= (count + 1) / 2)
            {
                m_current = Begin();
                std::bidirectional_iterator_tag category;
                FUN_005c9010((RHUnk005c9010Iterator &)m_current, index, category);
            }
            else
            {
                m_current = End();
                std::bidirectional_iterator_tag category;
                FUN_005c9010((RHUnk005c9010Iterator &)m_current, index - count, category);
            }
            m_dirty = false;
            m_index = index;
        }
        else
        {
            int previous = m_index;
            if (index != previous)
            {
                if (index < previous)
                {
                    if (index < (previous + 1) / 2)
                    {
                        std::bidirectional_iterator_tag category;
                        if (removing)
                        {
                            m_current.node = (RHTitbitNode *)((RHUnk0046eb30 *)this)->FUN_0046eb80().node;
                            FUN_005c9010((RHUnk005c9010Iterator &)m_current, index, category);
                        }
                        else
                            FUN_005c9010((RHUnk005c9010Iterator &)m_current.AssignNode(
                                *(RHTitbitNode *volatile *)&((RHTitbitList *)this)->m_head->m_next), index, category);
                    }
                    else
                    {
                        std::bidirectional_iterator_tag category;
                        FUN_005c9010((RHUnk005c9010Iterator &)m_current, index - previous, category);
                    }
                }
                else if (index < (previous + count) / 2)
                {
                    if (removing)
                    {
                        std::bidirectional_iterator_tag category;
                        FUN_005c9010((RHUnk005c9010Iterator &)m_current, index - previous, category);
                    }
                    else
                        std::advance(m_current, index - previous);
                }
                else
                {
                    m_current = End();
                    if (removing)
                    {
                        std::bidirectional_iterator_tag category;
                        FUN_005c9010((RHUnk005c9010Iterator &)m_current, index - count, category);
                    }
                    else
                        std::advance(m_current, index - count);
                }
                m_index = index;
            }
        }
        return *m_current;
    }
    std::list<RHTitbit> m_list;
    RHTitbitCursor m_current;
    bool m_dirty;
    int m_index;
};

// Parked: second cached traversal is outlined and leaves the frame four bytes short.
// STUB: GAME 0x005c3440
bool RHTitbits::RemoveQuickActionTitbitsFor(RHElementActorPC *actor, unsigned short action)
{
    unsigned long id = *(unsigned long *)((char *)actor + 0x538 + action * 4);
    if (id == -1)
        return false;
    bool removed = false;
    unsigned short count = m_list.m_count;
    for (int index = count - 1; count != 0; --count, --index)
    {
        RHTitbitAccess &list = *(RHTitbitAccess *)&m_list;
        if (list.Get(index, true).m_2c == id)
        {
            removed = true;
            list.Get(index, true);
            ((RHUnk0046eb30 *)&list)->erase(RHScriptIter((RHScriptNode *)list.m_current.node));
            list.m_dirty = true;
        }
    }
    return removed;
}

// Parked: list/file register allocation and cursor scheduling remain different.
// STUB: GAME 0x005c3a60
bool RHTitbits::Serialize(SBFile &file)
{
    unsigned int count;
    unsigned int i;
    RHTitbit elem;

    // STRING: GAME 0x6b8bfc
    RHSerializeName(file, "RHTitbits");

    if (file.Access(&m_ac, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0,
                 // STRING: GAME 0x6b8bd8
                 "P:\\Robin Hood\\RHtitbit.cpp",
                 621,
                 "Serialize failed reason is %s",
                 reason);
        return false;
    }

    if (!file.m_bLoading)
    {
        count = m_list.m_count;
        if (file.Access(&count, 4) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHtitbit.cpp", 626, "Serialize failed reason is %s", reason);
            return false;
        }
    }
    else
    {
        RHTitbitList &list = m_list;
        typedef RHTitbitIterator (RHTitbitList::*Erase)(RHTitbitIterator, RHTitbitIterator);
        (list.*(Erase)&RHTitbitList::Clear)(RHTitbitIterator(list.m_head->m_next), RHTitbitIterator(list.m_head));
        list.m_valid = 1;
        if (file.Access(&count, 4) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHtitbit.cpp", 631, "Serialize failed reason is %s", reason);
            return false;
        }
        list.Resize(count);
        m_a4 = 0xf;
        m_a8 = 10.0f;
    }

    RHTitbitNode *node;
    for (i = 0; i < count; i++)
    {
        if (!file.m_bLoading)
        {
            RHTitbitList &list = m_list;
            list.At(i);
            node = list.m_cur;
            elem = node->m_data;
        }

        if (file.Access(&elem.m_00, 4) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHtitbit.cpp", 647, "Serialize failed reason is %s", reason);
            return false;
        }
        if (file.Access(&elem.m_0a, 2) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHtitbit.cpp", 648, "Serialize failed reason is %s", reason);
            return false;
        }
        if (file.Access(&elem.m_08, 2) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHtitbit.cpp", 649, "Serialize failed reason is %s", reason);
            return false;
        }
        if (file.Access(&elem.m_06, 2) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHtitbit.cpp", 650, "Serialize failed reason is %s", reason);
            return false;
        }
        if (file.Access(&elem.m_04, 2) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHtitbit.cpp", 651, "Serialize failed reason is %s", reason);
            return false;
        }
        if (file.Access(&elem.m_24, 4) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHtitbit.cpp", 652, "Serialize failed reason is %s", reason);
            return false;
        }
        if (file.Access(&elem.m_24, 4) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHtitbit.cpp", 653, "Serialize failed reason is %s", reason);
            return false;
        }
        if (file.Access(&elem.m_u14.m_14s, 2) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHtitbit.cpp", 654, "Serialize failed reason is %s", reason);
            return false;
        }
        if (file.Access(&elem.m_28, 1) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHtitbit.cpp", 655, "Serialize failed reason is %s", reason);
            return false;
        }
        if (file.Access(&elem.m_2c, 4) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHtitbit.cpp", 656, "Serialize failed reason is %s", reason);
            return false;
        }

        g_pEngine->SerializeElementPointer(file, *(RHElement **)(&elem.m_0c));
        g_pEngine->SerializeNestedB(file, &elem.m_10);
        ((RHUnk005df510 *)((char *)&elem + 0x1c))->Serialize(file);

        if (file.m_bLoading)
        {
            m_list.Seek(i);
            m_list.m_cur->m_data = elem;
        }
    }

    return true;
}

// FUNCTION: GAME 0x005c7fb0
short RHTitbits::FUN_005c7fb0(unsigned long id)
{
    RHTitbit value;
    unsigned count = m_list.m_count;
    for (int index = 0; (unsigned)index < count; ++index)
    {
        RHTitbit &entry = ((RHTitbitAccess *)&m_list)->Get(index);
        if (entry.m_2c == id)
            return entry.m_04;
    }
    return -1;
}

// Parked: VC6 outlines the second cached traversal, changing frame and branch layout.
// STUB: GAME 0x005c8120
void RHTitbits::FUN_005c8120(int kind, RHElement *element)
{
    for (int index = 0; (unsigned)index < (unsigned)m_list.m_count; ++index)
    {
        RHTitbitAccess &list = *(RHTitbitAccess *)&m_list;
        RHTitbit &entry = list.Get(index, true);
        if (entry.m_00 == kind && entry.m_0c == (int)element)
        {
            list.Get(index, true);
            ((RHUnk0046eb30 *)&list)->erase(RHScriptIter((RHScriptNode *)list.m_current.node));
            list.m_dirty = true;
            --index;
        }
    }
}

// FUNCTION: GAME 0x005c8340
bool RHTitbits::FUN_005c8340(int kind, RHElement *element)
{
    for (int index = 0; (unsigned)index < (unsigned)m_list.m_count; ++index)
    {
        RHTitbit &entry = ((RHTitbitAccess *)&m_list)->Get(index);
        if (entry.m_00 == kind && entry.m_0c == (int)element)
            return true;
    }
    return false;
}

class SBGeoPoint2D
{
public:
    SBGeoPoint2D();
    ~SBGeoPoint2D();
    SBGeoPoint2D &operator=(const SBGeoPoint2D &);
    SBGeoPoint2D &FUN_005fc1e0(const SBGeoPoint2D &);
    float m_x;
    float m_y;
};

class SBGeoVector2D : public SBGeoPoint2D
{
public:
    SBGeoVector2D(float, float);
    SBGeoVector2D(const SBGeoVector2D &other);
    SBGeoVector2D &operator=(const SBGeoVector2D &other);
};

class SBGeoBoundingBox2D
{
public:
    SBGeoPoint2D m_min;
    SBGeoPoint2D m_max;
    char m_flag;
};

class RHMapBox
{
public:
    SBGeoPoint2D m_0;
    SBGeoPoint2D m_8;
    bool m_10;
};

class SBUIInputFieldDrawUnk
{
public:
    SBUIInputFieldDrawUnk();
    bool FUN_00614bf0(void *, std::wstring *, const SBGeoPoint2D &, unsigned);
    unsigned short FUN_00614230(void *, std::wstring *, const SBGeoBoundingBox2D &, unsigned, unsigned, unsigned);
    std::wstring m_00;
    unsigned m_10;
    char m_14;
    unsigned m_18;
    RHMapBox m_1c;
};

// FUNCTION: GAME 0x005c84a0
bool RHTitbits::RenderText(const std::wstring &text, const SBGeoBoundingBox2D &box, unsigned long flags) const
{
    SBUIInputFieldDrawUnk draw;
    draw.FUN_00614230(*(void *const *)((const char *)this + 0x78), (std::wstring *)&text, box, flags, 0, 1);
    return true;
}

// FUNCTION: GAME 0x005c8570
bool RHTitbits::RenderText(const std::wstring &text, const SBGeoPoint2D &point) const
{
    SBUIInputFieldDrawUnk draw;
    SBGeoPoint2D offset;
    void *outline = *(void *const *)((const char *)this + 0x7c);
    if (outline)
    {
        offset = point;
        offset.FUN_005fc1e0(SBGeoVector2D(-1.0f, -1.0f));
        draw.FUN_00614bf0(*(void *const *)((const char *)this + 0x7c), (std::wstring *)&text, offset, 1);
        offset = point;
        offset.FUN_005fc1e0(SBGeoVector2D(-1.0f, 1.0f));
        draw.FUN_00614bf0(*(void *const *)((const char *)this + 0x7c), (std::wstring *)&text, offset, 1);
        offset = point;
        offset.FUN_005fc1e0(SBGeoVector2D(1.0f, -1.0f));
        draw.FUN_00614bf0(*(void *const *)((const char *)this + 0x7c), (std::wstring *)&text, offset, 1);
        offset = point;
        offset.FUN_005fc1e0(SBGeoVector2D(1.0f, 1.0f));
        draw.FUN_00614bf0(*(void *const *)((const char *)this + 0x7c), (std::wstring *)&text, offset, 1);
    }
    draw.FUN_00614bf0(*(void *const *)((const char *)this + 0x78), (std::wstring *)&text, point, 1);
    return true;
}

// Parked: The second cached traversal is outlined instead of duplicated inline.
// STUB: GAME 0x005c8780
bool RHTitbits::IsRunningForQA(unsigned long id)
{
    unsigned count = m_list.m_count;
    for (int index = 0; (unsigned)index < count; ++index)
    {
        RHTitbitAccess &list = *(RHTitbitAccess *)&m_list;
        if (list.Get(index, true).m_2c == id && list.Get(index, true).m_00 == 17)
            return true;
    }
    return false;
}

inline bool operator<(const RHTitbit &first, const RHTitbit &second)
{
    return *(const float *)&first.m_24 < *(const float *)&second.m_24;
}

// Parked: Sort locals and shared destructor entities differ from the native instantiation.
// STUB: GAME 0x005c8980
void RHTitbitList::FUN_005c8980()
{
    std::list<RHTitbit> &list = *(std::list<RHTitbit> *)this;
    if (list.size() >= 2)
    {
        std::list<RHTitbit> carry(list.get_allocator());
        std::list<RHTitbit> bins[16];
        unsigned used = 0;
        while (!list.empty())
        {
            carry.splice(carry.begin(), list, list.begin());
            unsigned index;
            for (index = 0; index < used && !bins[index].empty(); ++index)
            {
                bins[index].merge(carry);
                bins[index].swap(carry);
            }
            if (index == 15)
                bins[index].merge(carry);
            else
            {
                bins[index].swap(carry);
                if (index == used)
                    ++used;
            }
        }
        while (used > 0)
            list.merge(bins[--used]);
    }
}

// SYNTHETIC: GAME 0x005c8bc0
// ??_F?$list@URHTitbit@@V?$allocator@URHTitbit@@@std@@@std@@QAEXXZ

// TEMPLATE: GAME 0x005c8bf0
// ?merge@?$list@URHTitbit@@V?$allocator@URHTitbit@@@std@@@std@@QAEXAAV12@@Z

void RHTitbitList::FUN_005c8bf0(RHTitbitList &other)
{
    typedef std::list<RHTitbit> List;
    typedef void (List::*Merge)(List &);
    Merge merge = &List::merge;
    (((List *)this)->*merge)(*(List *)&other);
}

// TEMPLATE: GAME 0x005c8cc0
// ?_Buynode@?$list@URHTitbit@@V?$allocator@URHTitbit@@@std@@@std@@IAEPAU_Node@12@PAU312@0@Z

// TEMPLATE: GAME 0x005c8cf0
// ?_Splice@?$list@URHTitbit@@V?$allocator@URHTitbit@@@std@@@std@@IAEXViterator@12@AAV12@00@Z

// Parked: initial size/count registers are exchanged despite matching insertion and erase loops.
// STUB: GAME 0x005c8d30
void RHTitbitList::Resize(long count)
{
    RHTitbit *value = new RHTitbit;
    std::list<RHTitbit> &list = *(std::list<RHTitbit> *)this;
    if (count <= m_count)
    {
        for (long remaining = m_count - count; remaining > 0; --remaining)
            list.pop_back();
    }
    else
    {
        for (long remaining = count - m_count; remaining > 0; --remaining)
            list.insert(list.end(), *value);
    }
    delete value;
    m_valid = 1;
}

void RHTitbitList::At(int index)
{
    std::list<RHTitbit> &list = *(std::list<RHTitbit> *)this;
    std::list<RHTitbit>::iterator &current = *(std::list<RHTitbit>::iterator *)&m_cur;
    long count = list.size();
    if (m_valid)
    {
        if (index <= (count + 1) / 2)
        {
            current = list.begin();
            std::advance(current, (long)index);
        }
        else
        {
            current = list.end();
            std::advance(current, index - count);
        }
        m_valid = 0;
        m_index = index;
    }
    else
    {
        long previous = m_index;
        if (index != previous)
        {
            if (index < previous)
            {
                if (index < (previous + 1) / 2)
                {
                    current = list.begin();
                    std::advance(current, (long)index);
                }
                else
                    std::advance(current, index - previous);
            }
            else if (index < (previous + count) / 2)
                std::advance(current, index - previous);
            else
            {
                current = list.end();
                std::advance(current, index - count);
            }
            m_index = index;
        }
    }
}

#include <map>

class RHGameRenderer005c9270
{
public:
    RHGameRenderer005c9270();
    ~RHGameRenderer005c9270();
    undefined m_data[0x50];
};

class SBResourceWidgetID
{
public:
    int m_value;
    bool operator<(const SBResourceWidgetID &other) const
    {
        return m_value < other.m_value;
    }
};

class RHUIRendererBlinking
{
public:
    struct BlinkingItem
    {
        BlinkingItem() {}
        unsigned long m_period;
        SBResourceWidgetID m_first;
        SBResourceWidgetID m_second;
    };
    void SetBlinking(SBResourceWidgetID, SBResourceWidgetID, SBResourceWidgetID, unsigned long);
    void RemoveBlinking(SBResourceWidgetID);
    void *FUN_005c9250(unsigned flags);
    char m_data[0x64];
    std::map<SBResourceWidgetID, BlinkingItem> m_items;
};

typedef std::map<SBResourceWidgetID, RHUIRendererBlinking::BlinkingItem> RHBlinkingMap;
typedef std::_Tree<SBResourceWidgetID,
    std::pair<const SBResourceWidgetID, RHUIRendererBlinking::BlinkingItem>,
    std::map<SBResourceWidgetID, RHUIRendererBlinking::BlinkingItem>::_Kfn,
    std::less<SBResourceWidgetID>,
    std::allocator<RHUIRendererBlinking::BlinkingItem> > RHBlinkingTree;

typedef int RHBlinkingItemSize[(sizeof(RHUIRendererBlinking::BlinkingItem) == 0x0c) ? 1 : -1];
typedef int RHBlinkingMapSize[(sizeof(RHBlinkingMap) == 0x10) ? 1 : -1];
typedef int RHBlinkingRendererViewSize[(sizeof(RHUIRendererBlinking) == 0x74) ? 1 : -1];

template<> RHBlinkingTree::_Nodeptr RHBlinkingTree::_Min(_Nodeptr node)
{
    std::_Lockit lock;
    while (_Left(node) != _Nil)
        node = _Left(node);
    return node;
}

template<> RHBlinkingTree::_Nodeptr RHBlinkingTree::_Max(_Nodeptr node)
{
    std::_Lockit lock;
    while (_Right(node) != _Nil)
        node = _Right(node);
    return node;
}

template<> RHBlinkingTree::_Nodeptr RHBlinkingTree::_Lbound(const SBResourceWidgetID &id) const;
template<> RHBlinkingTree::_Nodeptr RHBlinkingTree::_Ubound(const SBResourceWidgetID &id) const;
template<> void RHBlinkingTree::_Erase(_Nodeptr node);
template<> void RHBlinkingTree::const_iterator::_Dec();
template<> void RHBlinkingTree::const_iterator::_Inc();
template<> RHBlinkingTree::_Pairib RHBlinkingTree::insert(const value_type &value);
template<> RHBlinkingTree::iterator RHBlinkingTree::erase(iterator first, iterator last);
template<> RHBlinkingTree::iterator RHBlinkingTree::erase(iterator position);
template<> RHBlinkingTree::iterator RHBlinkingTree::_Insert(_Nodeptr node, _Nodeptr parent, const value_type &value);

template<> void RHBlinkingTree::_Lrotate(_Nodeptr node)
{
    std::_Lockit lock;
    _Nodeptr right = _Right(node);
    _Right(node) = _Left(right);
    if (_Left(right) != _Nil)
        _Parent(_Left(right)) = node;
    _Parent(right) = _Parent(node);
    if (node == _Root())
        _Root() = right;
    else if (node == _Left(_Parent(node)))
        _Left(_Parent(node)) = right;
    else
        _Right(_Parent(node)) = right;
    _Left(right) = node;
    _Parent(node) = right;
}

template<> void RHBlinkingTree::_Rrotate(_Nodeptr node)
{
    std::_Lockit lock;
    _Nodeptr left = _Left(node);
    _Left(node) = _Right(left);
    if (_Right(left) != _Nil)
        _Parent(_Right(left)) = node;
    _Parent(left) = _Parent(node);
    if (node == _Root())
        _Root() = left;
    else if (node == _Right(_Parent(node)))
        _Right(_Parent(node)) = left;
    else
        _Left(_Parent(node)) = left;
    _Right(left) = node;
    _Parent(node) = left;
}

struct RHUnk00571160Position;
class RHScriptPositionList
{
public:
    static void Unk00588190(RHUnk00571160Position *, const RHUnk00571160Position *);
};

template<> RHBlinkingMap::_Pairib RHBlinkingMap::insert(const value_type &value)
{
    typedef RHBlinkingTree::_Pairib (RHBlinkingTree::*Insert)(const RHBlinkingTree::value_type &);
    Insert insert = &RHBlinkingTree::insert;
    _Imp::_Pairib result = (_Tr.*insert)(value);
    return _Pairib(result.first, result.second);
}

// FUNCTION: GAME 0x005c9250
void *RHUIRendererBlinking::FUN_005c9250(unsigned flags)
{
    ((RHGameRenderer005c9270 *)this)->~RHGameRenderer005c9270();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x005c9430
void RHUIRendererBlinking::SetBlinking(SBResourceWidgetID id, SBResourceWidgetID first,
    SBResourceWidgetID second, unsigned long period)
{
    BlinkingItem value;
    value.m_first = first;
    value.m_second = second;
    value.m_period = period;
    m_items[id] = value;
    if (*(bool *)((char *)this + 0x60) && id.m_value == *(int *)((char *)this + 0x58))
    {
        *(BlinkingItem *)((char *)this + 0x4c) = value;
    }
}

// FUNCTION: GAME 0x005c94c0
void RHUIRendererBlinking::RemoveBlinking(SBResourceWidgetID id)
{
    RHBlinkingTree &tree = *(RHBlinkingTree *)&m_items;
    RHBlinkingTree::iterator last = tree.upper_bound(id);
    RHBlinkingTree::iterator first = tree.lower_bound(id);
    RHBlinkingTree::iterator current = first;
    for (; current != last; ++current) {}
    typedef RHBlinkingTree::iterator (RHBlinkingTree::*Erase)(RHBlinkingTree::iterator, RHBlinkingTree::iterator);
    Erase erase = &RHBlinkingTree::erase;
    (tree.*erase)(first, last);
}

// TEMPLATE: GAME 0x005c9520
// ?erase@?$_Tree@VSBResourceWidgetID@@U?$pair@$$CBVSBResourceWidgetID@@UBlinkingItem@RHUIRendererBlinking@@@std@@U_Kfn@?$map@VSBResourceWidgetID@@UBlinkingItem@RHUIRendererBlinking@@U?$less@VSBResourceWidgetID@@@std@@V?$allocator@UBlinkingItem@RHUIR11e2b553
template<> RHBlinkingTree::iterator RHBlinkingTree::erase(iterator first, iterator last)
{
    if (size() == 0 || first != begin() || last != end())
    {
        while (first != last)
            erase(first++);
        return first;
    }
    else
    {
        std::_Lockit lock;
        _Erase(_Root());
        _Root() = _Nil;
        _Size = 0;
        _Lmost() = _Head;
        _Rmost() = _Head;
        return begin();
    }
}

// TEMPLATE: GAME 0x005c9650
// ?insert@?$_Tree@VSBResourceWidgetID@@U?$pair@$$CBVSBResourceWidgetID@@UBlinkingItem@RHUIRendererBlinking@@@std@@U_Kfn@?$map@VSBResourceWidgetID@@UBlinkingItem@RHUIRendererBlinking@@U?$less@VSBResourceWidgetID@@@std@@V?$allocator@UBlinkingItem@RHUIab12b7a4
template<> RHBlinkingTree::_Pairib RHBlinkingTree::insert(const value_type &value)
{
    typedef iterator (RHBlinkingTree::*Insert)(_Nodeptr, _Nodeptr, const value_type &);
    Insert insert = &RHBlinkingTree::_Insert;
    _Nodeptr parent = _Head;
    _Nodeptr node = _Root();
    bool left = true;
    {
        std::_Lockit lock;
        while (node != _Nil)
        {
            parent = node;
            left = key_compare(_Kfn()(value), _Key(node));
            node = left ? _Left(node) : _Right(node);
        }
    }
    if (_Multi)
    {
        _Pairib result((this->*insert)(node, parent, value), true);
        return result;
    }
    iterator position(parent);
    if (!left) {}
    else if (position == begin())
    {
        _Pairib result((this->*insert)(node, parent, value), true);
        return result;
    }
    else
    {
        void (const_iterator::*decrement)() = &const_iterator::_Dec;
        (position.*decrement)();
    }
    if (key_compare(_Key(position._Mynode()), _Kfn()(value)))
    {
        _Pairib result((this->*insert)(node, parent, value), true);
        return result;
    }
    _Pairib result(position, false);
    return result;
}

// TEMPLATE: GAME 0x005c9780
// ?erase@?$_Tree@VSBResourceWidgetID@@U?$pair@$$CBVSBResourceWidgetID@@UBlinkingItem@RHUIRendererBlinking@@@std@@U_Kfn@?$map@VSBResourceWidgetID@@UBlinkingItem@RHUIRendererBlinking@@U?$less@VSBResourceWidgetID@@@std@@V?$allocator@UBlinkingItem@RHUIR31e38f0d
template<> RHBlinkingTree::iterator RHBlinkingTree::erase(iterator position)
{
    _Nodeptr node;
    _Nodeptr removed = position._Mynode();
    void (const_iterator::*increment)() = &const_iterator::_Inc;
    (position.*increment)();
    _Nodeptr replacement = removed;
    std::_Lockit lock;
    if (_Left(replacement) == _Nil)
        node = _Right(replacement);
    else if (_Right(replacement) == _Nil)
        node = _Left(replacement);
    else
    {
        replacement = _Min(_Right(replacement));
        node = _Right(replacement);
    }
    if (replacement != removed)
    {
        _Parent(_Left(removed)) = replacement;
        _Left(replacement) = _Left(removed);
        if (replacement == _Right(removed))
            _Parent(node) = replacement;
        else
        {
            _Parent(node) = _Parent(replacement);
            _Left(_Parent(replacement)) = node;
            _Right(replacement) = _Right(removed);
            _Parent(_Right(removed)) = replacement;
        }
        if (_Root() == removed)
            _Root() = replacement;
        else if (_Left(_Parent(removed)) == removed)
            _Left(_Parent(removed)) = replacement;
        else
            _Right(_Parent(removed)) = replacement;
        _Parent(replacement) = _Parent(removed);
        std::swap(_Color(replacement), _Color(removed));
        replacement = removed;
    }
    else
    {
        _Parent(node) = _Parent(replacement);
        if (_Root() == removed)
            _Root() = node;
        else if (_Left(_Parent(removed)) == removed)
            _Left(_Parent(removed)) = node;
        else
            _Right(_Parent(removed)) = node;
        if (_Lmost() != removed) {}
        else if (_Right(removed) == _Nil)
            _Lmost() = _Parent(removed);
        else
            _Lmost() = _Min(node);
        if (_Rmost() != removed) {}
        else if (_Left(removed) == _Nil)
            _Rmost() = _Parent(removed);
        else
            _Rmost() = _Max(node);
    }
    if (_Color(replacement) == _Black)
    {
        while (node != _Root() && _Color(node) == _Black)
        {
            if (node == _Left(_Parent(node)))
            {
                _Nodeptr sibling = _Right(_Parent(node));
                if (_Color(sibling) == _Red)
                {
                    _Color(sibling) = _Black;
                    _Color(_Parent(node)) = _Red;
                    _Lrotate(_Parent(node));
                    sibling = _Right(_Parent(node));
                }
                if (_Color(_Left(sibling)) == _Black && _Color(_Right(sibling)) == _Black)
                {
                    _Color(sibling) = _Red;
                    node = _Parent(node);
                }
                else
                {
                    if (_Color(_Right(sibling)) == _Black)
                    {
                        _Color(_Left(sibling)) = _Black;
                        _Color(sibling) = _Red;
                        _Rrotate(sibling);
                        sibling = _Right(_Parent(node));
                    }
                    _Color(sibling) = _Color(_Parent(node));
                    _Color(_Parent(node)) = _Black;
                    _Color(_Right(sibling)) = _Black;
                    _Lrotate(_Parent(node));
                    break;
                }
            }
            else
            {
                _Nodeptr sibling = _Left(_Parent(node));
                if (_Color(sibling) == _Red)
                {
                    _Color(sibling) = _Black;
                    _Color(_Parent(node)) = _Red;
                    _Rrotate(_Parent(node));
                    sibling = _Left(_Parent(node));
                }
                if (_Color(_Right(sibling)) == _Black && _Color(_Left(sibling)) == _Black)
                {
                    _Color(sibling) = _Red;
                    node = _Parent(node);
                }
                else
                {
                    if (_Color(_Left(sibling)) == _Black)
                    {
                        _Color(_Right(sibling)) = _Black;
                        _Color(sibling) = _Red;
                        _Lrotate(sibling);
                        sibling = _Left(_Parent(node));
                    }
                    _Color(sibling) = _Color(_Parent(node));
                    _Color(_Parent(node)) = _Black;
                    _Color(_Left(sibling)) = _Black;
                    _Rrotate(_Parent(node));
                    break;
                }
            }
        }
        _Color(node) = _Black;
    }
    _Destval(&_Value(replacement));
    _Freenode(replacement);
    --_Size;
    return position;
}

// TEMPLATE: GAME 0x005c9ca0
// std::_Tree<SBResourceWidgetID,std::pair<SBResourceWidgetID const,RHUIRendererBlinking::BlinkingItem>,std::map<SBResourceWidgetID,RHUIRendererBlinking::BlinkingItem,std::less<SBResourceWidgetID>,std::allocator<RHUIRendererBlinking::BlinkingItem> >:c34947a4
template<> void RHBlinkingTree::_Erase(_Nodeptr node)
{
    std::_Lockit lock;
    for (_Nodeptr current = node; current != _Nil; node = current)
    {
        _Erase(_Right(current));
        current = _Left(current);
        _Destval(&_Value(node));
        _Freenode(node);
    }
}

// TEMPLATE: GAME 0x005c9d30
// std::_Tree<SBResourceWidgetID,std::pair<SBResourceWidgetID const,RHUIRendererBlinking::BlinkingItem>,std::map<SBResourceWidgetID,RHUIRendererBlinking::BlinkingItem,std::less<SBResourceWidgetID>,std::allocator<RHUIRendererBlinking::BlinkingItem> >:b3fae52b
template<> RHBlinkingTree::iterator RHBlinkingTree::_Insert(_Nodeptr node, _Nodeptr parent, const value_type &value)
{
    std::_Lockit lock;
    _Nodeptr inserted = _Buynode(parent, _Red);
    _Left(inserted) = _Nil;
    _Right(inserted) = _Nil;
    RHScriptPositionList::Unk00588190((RHUnk00571160Position *)&_Value(inserted),
        (const RHUnk00571160Position *)&value);
    ++_Size;
    if (parent == _Head || node != _Nil || key_compare(_Kfn()(value), _Key(parent)))
    {
        _Left(parent) = inserted;
        if (parent == _Head)
        {
            _Root() = inserted;
            _Rmost() = inserted;
        }
        else if (parent == _Lmost())
            _Lmost() = inserted;
    }
    else
    {
        _Right(parent) = inserted;
        if (parent == _Rmost())
            _Rmost() = inserted;
    }
    for (node = inserted; node != _Root() && _Color(_Parent(node)) == _Red; )
    {
        if (_Parent(node) == _Left(_Parent(_Parent(node))))
        {
            parent = _Right(_Parent(_Parent(node)));
            if (_Color(parent) == _Red)
            {
                _Color(_Parent(node)) = _Black;
                _Color(parent) = _Black;
                _Color(_Parent(_Parent(node))) = _Red;
                node = _Parent(_Parent(node));
            }
            else
            {
                if (node == _Right(_Parent(node)))
                {
                    node = _Parent(node);
                    _Lrotate(node);
                }
                _Color(_Parent(node)) = _Black;
                _Color(_Parent(_Parent(node))) = _Red;
                _Rrotate(_Parent(_Parent(node)));
            }
        }
        else
        {
            parent = _Left(_Parent(_Parent(node)));
            if (_Color(parent) == _Red)
            {
                _Color(_Parent(node)) = _Black;
                _Color(parent) = _Black;
                _Color(_Parent(_Parent(node))) = _Red;
                node = _Parent(_Parent(node));
            }
            else
            {
                if (node == _Left(_Parent(node)))
                {
                    node = _Parent(node);
                    _Rrotate(node);
                }
                _Color(_Parent(node)) = _Black;
                _Color(_Parent(_Parent(node))) = _Red;
                _Lrotate(_Parent(_Parent(node)));
            }
        }
    }
    _Color(_Root()) = _Black;
    return iterator(inserted);
}

// TEMPLATE: GAME 0x005ca030
// std::_Tree<SBResourceWidgetID,std::pair<SBResourceWidgetID const,RHUIRendererBlinking::BlinkingItem>,std::map<SBResourceWidgetID,RHUIRendererBlinking::BlinkingItem,std::less<SBResourceWidgetID>,std::allocator<RHUIRendererBlinking::BlinkingItem> >:dbee9ff7
template<> RHBlinkingTree::_Nodeptr RHBlinkingTree::_Lbound(const SBResourceWidgetID &id) const
{
    std::_Lockit lock;
    _Nodeptr node = _Root();
    _Nodeptr result = _Head;
    while (node != _Nil)
    {
        if (key_compare(_Key(node), id))
            node = _Right(node);
        else
        {
            result = node;
            node = _Left(node);
        }
    }
    return result;
}

// TEMPLATE: GAME 0x005ca080
// std::_Tree<SBResourceWidgetID,std::pair<SBResourceWidgetID const,RHUIRendererBlinking::BlinkingItem>,std::map<SBResourceWidgetID,RHUIRendererBlinking::BlinkingItem,std::less<SBResourceWidgetID>,std::allocator<RHUIRendererBlinking::BlinkingItem> >:ff37cca4
template<> RHBlinkingTree::_Nodeptr RHBlinkingTree::_Ubound(const SBResourceWidgetID &id) const
{
    std::_Lockit lock;
    _Nodeptr node = _Root();
    _Nodeptr result = _Head;
    while (node != _Nil)
    {
        if (key_compare(id, _Key(node)))
        {
            result = node;
            node = _Left(node);
        }
        else
            node = _Right(node);
    }
    return result;
}

// TEMPLATE: GAME 0x005ca0d0
// std::_Tree<SBResourceWidgetID,std::pair<SBResourceWidgetID const,RHUIRendererBlinking::BlinkingItem>,std::map<SBResourceWidgetID,RHUIRendererBlinking::BlinkingItem,std::less<SBResourceWidgetID>,std::allocator<RHUIRendererBlinking::BlinkingItem> >:1eace2aa
template<> void RHBlinkingTree::const_iterator::_Dec()
{
    std::_Lockit lock;
    if (_Color(_Ptr) == _Red && _Parent(_Parent(_Ptr)) == _Ptr)
        _Ptr = _Right(_Ptr);
    else if (_Left(_Ptr) != _Nil)
        _Ptr = _Max(_Left(_Ptr));
    else
    {
        _Nodeptr parent;
        while (_Ptr == _Left(parent = _Parent(_Ptr)))
            _Ptr = parent;
        _Ptr = parent;
    }
}

// TEMPLATE: GAME 0x005ca190
// std::_Tree<SBResourceWidgetID,std::pair<SBResourceWidgetID const,RHUIRendererBlinking::BlinkingItem>,std::map<SBResourceWidgetID,RHUIRendererBlinking::BlinkingItem,std::less<SBResourceWidgetID>,std::allocator<RHUIRendererBlinking::BlinkingItem> >:f580a832
template<> void RHBlinkingTree::const_iterator::_Inc()
{
    std::_Lockit lock;
    if (_Right(_Ptr) != _Nil)
        _Ptr = _Min(_Right(_Ptr));
    else
    {
        _Nodeptr parent;
        while (_Ptr == _Right(parent = _Parent(_Ptr)))
            _Ptr = parent;
        if (_Right(_Ptr) != parent)
            _Ptr = parent;
    }
}

// GLOBAL: GAME 0x006c10fc
// std::_Tree<SBResourceWidgetID,std::pair<SBResourceWidgetID const,RHUIRendererBlinking::BlinkingItem>,std::map<SBResourceWidgetID,RHUIRendererBlinking::BlinkingItem,std::less<SBResourceWidgetID>,std::allocator<RHUIRendererBlinking::BlinkingItem> >:cd8bb598

class RHBlinkingNativeAccess : public RHBlinkingTree
{
public:
    void Emit(const SBResourceWidgetID &id, const value_type &value, iterator position)
    {
        typedef _Nodeptr (RHBlinkingTree::*Bound)(const SBResourceWidgetID &) const;
        Bound lower = &RHBlinkingNativeAccess::_Lbound;
        Bound upper = &RHBlinkingNativeAccess::_Ubound;
        (this->*lower)(id);
        (this->*upper)(id);
        typedef void (RHBlinkingTree::*Erase)(_Nodeptr);
        Erase erase = &RHBlinkingNativeAccess::_Erase;
        (this->*erase)(position._Mynode());
        typedef iterator (RHBlinkingTree::*Insert)(_Nodeptr, _Nodeptr, const value_type &);
        Insert insert = &RHBlinkingNativeAccess::_Insert;
        (this->*insert)(position._Mynode(), position._Mynode(), value);
        typedef _Pairib (RHBlinkingTree::*InsertValue)(const value_type &);
        InsertValue insertValue = &RHBlinkingTree::insert;
        (this->*insertValue)(value);
        typedef iterator (RHBlinkingTree::*EraseRange)(iterator, iterator);
        EraseRange eraseRange = &RHBlinkingTree::erase;
        (this->*eraseRange)(position, position);
        typedef iterator (RHBlinkingTree::*EraseOne)(iterator);
        EraseOne eraseOne = &RHBlinkingTree::erase;
        (this->*eraseOne)(position);
        void (const_iterator::*decrement)() = &const_iterator::_Dec;
        void (const_iterator::*increment)() = &const_iterator::_Inc;
        (position.*decrement)();
        (position.*increment)();
    }
};

void EmitRHBlinkingHelpers(RHBlinkingNativeAccess *tree, RHUIRendererBlinking *renderer)
{
    SBResourceWidgetID id;
    RHBlinkingTree::value_type value;
    tree->Emit(id, value, tree->begin());
    renderer->SetBlinking(id, id, id, 0);
    renderer->RemoveBlinking(id);
    renderer->FUN_005c9250(0);
}

void RHTitbits::Emit(SBFile &file)
{
    Serialize(file);
    FUN_005c7fb0(0);
    FUN_005c8120(0, 0);
    FUN_005c8340(0, 0);
    RenderText(*(std::wstring *)0, *(SBGeoPoint2D *)0);
    RenderText(*(std::wstring *)0, *(SBGeoBoundingBox2D *)0, 0);
    IsRunningForQA(0);
    m_list.FUN_005c8980();
    m_list.FUN_005c8bf0(m_list);
    m_list.Resize(0);
    m_list.At(0);
}

void (std::list<RHTitbit>::*g_rhtitbitMerge)(std::list<RHTitbit> &) = &std::list<RHTitbit>::merge;

class RHTitbitNativeAccess : public std::list<RHTitbit>
{
public:
    void EmitBuynode()
    {
        typedef _Nodeptr (std::list<RHTitbit>::*Buy)(_Nodeptr, _Nodeptr);
        Buy buy = &RHTitbitNativeAccess::_Buynode;
        (this->*buy)(0, 0);
    }
};

void EmitRHTitbitNativeHelpers(RHTitbitNativeAccess *list)
{
    list->EmitBuynode();
}
