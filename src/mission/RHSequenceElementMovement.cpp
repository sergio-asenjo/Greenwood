#include "SBNullstr.h"
#include "RHSequenceElementMovement.h"
#include <iterator>

// STRING: GAME 0x006b757c
#define RH_MOVEMENT_FILE "P:\\Robin Hood\\RHSequenceElementMovement.cpp"

#define RH_MOVEMENT_ACCESS(value, size, line) \
    if (file.Access(&(value), size) < 0) \
    { \
        SBString *error = file.GetError(); \
        SBAssert(0, RH_MOVEMENT_FILE, line, "Serialize failed reason is %s", error->m_chars ? error->m_chars : ""); \
        return false; \
    }

void RHSequenceElementMovement::Emit(SBFile &file, bool pointers)
{
    Serialize(file, pointers);
    FUN_00588d40(0);
    FUN_005897e0();
}

class RHSequenceElementCalls
{
public:
    virtual void FUN_00585cc0(int value);
    virtual void FUN_00585c80();
    virtual void FUN_00585d00();
    virtual void FUN_00585d40();
    virtual void FUN_00585e30();
    void FUN_00585df0(RHSequenceElementCalls *other);
};

struct RHMovementSequenceView
{
    void *vtable;
    unsigned char type;
    char m_05[0x0b];
    int command;
    char m_14[0x34];
    void *owner;
    RHMovementSequenceView *next;
};

class RHUnk00584d60
{
public:
    RHUnk00584d60();
    RHUnk00584d60(unsigned short level, int command, void *actor);
    ~RHUnk00584d60();
    char m_00[4];
    unsigned char m_04;
    char m_05[0x5f];
};

class RHMovementOwned
{
public:
    virtual ~RHMovementOwned();
};

extern float g_unk0x006775d8;

struct RHMovementBox
{
    void Center(SBGeoPoint2D &point) const
    {
        point.m_x = (m_0c + m_04) * g_unk0x006775d8;
        point.m_y = (m_10 + m_08) * g_unk0x006775d8;
    }
    char m_00[4];
    float m_04;
    float m_08;
    float m_0c;
    float m_10;
};

extern float g_unk0x006775d8;

#define RH_MOVEMENT_FIELDS \
    void *m_64; \
    RHMovementOwned *m_68; \
    SBGeoPoint2D m_6c; \
    unsigned short m_74; \
    char m_76[2]; \
    void *m_78; \
    void *m_7c; \
    void *m_80; \
    void *m_84; \
    int m_88; \
    float m_8c; \
    unsigned short m_90; \
    char m_92[2]; \
    int m_94; \
    float m_98;

class RHUnk588270 : public RHUnk00584d60
{
public:
    RHUnk588270();
    RH_MOVEMENT_FIELDS
};

class RHUnk00588530 : public RHUnk00584d60
{
public:
    RHUnk00588530(unsigned short level, int command, void *actor);
    RHUnk00588530(unsigned short level, int command, void *actor, int value94, RHMovementBox *box, float value8c, int value88);
    RHUnk00588530(unsigned short level, int command, void *actor, int style, void *target, float distance, void *value);
    RHUnk00588530(unsigned short level, int command, void *actor, int value94, const SBGeoPoint2D &point, void *value78, unsigned short value74, float value8c, int value88);
    RHUnk00588530(unsigned short level, int command, void *actor, void *value78, const SBGeoPoint2D &point, void *value84, float value8c, int value88);
    RHUnk00588530(unsigned short level, int command, void *actor, const SBGeoPoint2D &point, void *value78, unsigned short value90, int value88);
    ~RHUnk00588530();
    void *FUN_005882f0(unsigned int flags);
    void FUN_00588b20();
    void FUN_00588b60();
    void FUN_00588d60();
    void FUN_00588f00();
    void FUN_005890c0();
    RHUnk00588530 *FUN_00589810();
    void EmitMovement();
    RH_MOVEMENT_FIELDS
};

class RHUnk005883a0 : public RHUnk00584d60
{
public:
    RHUnk005883a0(unsigned short priority, int command, void *element, int animation,
                  const SBGeoPoint2D &destination, void *target, float speed, unsigned long flags);
    RH_MOVEMENT_FIELDS
};

class RHUnk00588830 : public RHUnk00584d60
{
public:
    RHUnk00588830(unsigned short level, int command, void *actor, int style, int value);
    RH_MOVEMENT_FIELDS
};

// FUNCTION: GAME 0x00588270
RHUnk588270::RHUnk588270()
{
    m_84 = 0;
    m_7c = 0;
    m_78 = 0;
    m_80 = 0;
    m_68 = 0;
    m_64 = 0;
    *(unsigned *)this = 0x679d88;
    m_04 = 4;
    m_98 = 1.0f;
}

// FUNCTION: GAME 0x005882f0
void *RHUnk00588530::FUN_005882f0(unsigned int flags)
{
    this->~RHUnk00588530();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x00588310
RHUnk00588530::RHUnk00588530(unsigned short level, int command, void *actor)
    : RHUnk00584d60(level, command, actor)
{
    m_84 = 0;
    m_7c = 0;
    m_78 = 0;
    m_80 = 0;
    m_68 = 0;
    m_64 = 0;
    *(unsigned *)this = 0x679d88;
    m_98 = 1.0f;
    m_04 = 4;
}

// FUNCTION: GAME 0x005883a0
RHUnk005883a0::RHUnk005883a0(unsigned short priority, int command, void *element, int animation,
                             const SBGeoPoint2D &destination, void *target, float speed, unsigned long flags)
    : RHUnk00584d60(priority, command, element)
{
    *(unsigned *)this = 0x679d88;
    m_84 = target;
    m_80 = 0;
    m_7c = 0;
    m_78 = 0;
    m_6c = destination;
    m_94 = animation;
    m_8c = speed;
    m_88 = flags;
    m_68 = 0;
    m_64 = 0;
    m_04 = 4;
    m_98 = 1.0f;
}

// FUNCTION: GAME 0x00588460
RHUnk00588530::RHUnk00588530(unsigned short level, int command, void *actor, int value94, RHMovementBox *box, float value8c, int value88)
    : RHUnk00584d60(level, command, actor)
{
    m_94 = value94;
    m_8c = value8c;
    *(unsigned *)this = 0x679d88;
    m_88 = value88;
    m_80 = box;
    m_7c = 0;
    m_78 = 0;
    m_84 = 0;
    box->Center(m_6c);
    m_88 = value88 | 0x80;
    m_68 = 0;
    m_64 = 0;
    m_98 = 1.0f;
    m_04 = 4;
}

// FUNCTION: GAME 0x00588530
RHUnk00588530::RHUnk00588530(unsigned short level, int command, void *actor, int style, void *target, float distance, void *value)
    : RHUnk00584d60(level, command, actor)
{
    m_94 = style;
    *(unsigned *)this = 0x679d88;
    m_8c = distance;
    m_88 = (int)value;
    m_84 = target;
    m_78 = 0;
    m_80 = 0;
    m_7c = 0;
    m_68 = 0;
    m_64 = 0;
    m_98 = 1.0f;
    m_04 = 4;
}

// FUNCTION: GAME 0x005885e0
RHUnk00588530::RHUnk00588530(unsigned short level, int command, void *actor, int value94, const SBGeoPoint2D &point, void *value78, unsigned short value74, float value8c, int value88)
    : RHUnk00584d60(level, command, actor)
{
    m_94 = value94;
    m_74 = value74;
    *(unsigned *)this = 0x679d88;
    m_8c = value8c;
    m_88 = value88;
    m_6c = point;
    m_80 = 0;
    m_84 = 0;
    m_78 = value78;
    m_7c = 0;
    m_68 = 0;
    m_64 = 0;
    m_98 = 1.0f;
    m_04 = 4;
}

// FUNCTION: GAME 0x005886b0
RHUnk00588530::RHUnk00588530(unsigned short level, int command, void *actor, void *value78, const SBGeoPoint2D &point, void *value84, float value8c, int value88)
    : RHUnk00584d60(level, command, actor)
{
    *(unsigned *)this = 0x679d88;
    m_6c = point;
    m_8c = value8c;
    m_88 = value88;
    m_84 = value84;
    m_78 = value78;
    m_80 = 0;
    m_7c = 0;
    m_68 = 0;
    m_64 = 0;
    m_98 = 1.0f;
    m_04 = 4;
}

// FUNCTION: GAME 0x00588770
RHUnk00588530::RHUnk00588530(unsigned short level, int command, void *actor, const SBGeoPoint2D &point, void *value78, unsigned short value90, int value88)
    : RHUnk00584d60(level, command, actor)
{
    *(unsigned *)this = 0x679d88;
    m_6c = point;
    m_90 = value90;
    m_88 = value88;
    m_78 = value78;
    m_84 = 0;
    m_80 = 0;
    m_7c = 0;
    m_68 = 0;
    m_64 = 0;
    m_98 = 1.0f;
    m_04 = 4;
}

// FUNCTION: GAME 0x00588830
RHUnk00588830::RHUnk00588830(unsigned short level, int command, void *actor, int style, int value)
    : RHUnk00584d60(level, command, actor)
{
    m_94 = style;
    m_88 = value;
    m_84 = 0;
    m_80 = 0;
    m_78 = 0;
    m_7c = 0;
    m_68 = 0;
    m_64 = 0;
    *(unsigned *)this = 0x679d88;
    m_98 = 1.0f;
    m_04 = 4;
}

// Implicit-vptr scheduling: the EH state store lands after the null test instead of before it.
// STUB: GAME 0x005888d0
RHUnk00588530::~RHUnk00588530()
{
    *(unsigned *)this = 0x679d88;
    RHMovementOwned **slot = &m_68;
    delete *slot;
}

struct RHMovementOrder
{
    char m_00[0x24];
    int action;
};

struct RHMovementOrderNode
{
    RHMovementOrderNode *next;
    RHMovementOrderNode *previous;
    RHMovementOrder *value;
};

struct RHMovementOrderIterator
{
    RHMovementOrderNode *node;
    RHMovementOrderIterator(RHMovementOrderNode *value) : node(value) {}
};

struct RHUnk005c9010Iterator;
void FUN_005c9010(RHUnk005c9010Iterator &, int, std::bidirectional_iterator_tag);

class RHMovementOrderList
{
public:
    RHMovementOrder *Value(int wanted)
    {
        int size = count;
        if (dirty)
        {
            if (wanted <= (size + 1) / 2)
            {
                current = RHMovementOrderIterator(head->next);
                std::bidirectional_iterator_tag category;
                FUN_005c9010((RHUnk005c9010Iterator &)current, wanted, category);
            }
            else
            {
                current = RHMovementOrderIterator(head);
                std::bidirectional_iterator_tag category;
                FUN_005c9010((RHUnk005c9010Iterator &)current, wanted - size, category);
            }
            dirty = false;
            index = wanted;
        }
        else if (wanted != index)
        {
            int previous = index;
            if (wanted < previous)
            {
                if (wanted < (previous + 1) / 2)
                {
                    current = RHMovementOrderIterator(head->next);
                    std::bidirectional_iterator_tag category;
                    FUN_005c9010((RHUnk005c9010Iterator &)current, wanted, category);
                }
                else
                {
                    std::bidirectional_iterator_tag category;
                    FUN_005c9010((RHUnk005c9010Iterator &)current, wanted - previous, category);
                }
            }
            else if (wanted < (previous + size) / 2)
            {
                std::bidirectional_iterator_tag category;
                FUN_005c9010((RHUnk005c9010Iterator &)current, wanted - previous, category);
            }
            else
            {
                current = RHMovementOrderIterator(head);
                int distance = wanted - size;
                for (; 0 < distance; --distance)
                    current.node = current.node->next;
                for (; distance < 0; ++distance)
                    current.node = current.node->previous;
            }
            index = wanted;
        }
        return current.node->value;
    }
    char m_00[4];
    RHMovementOrderNode *head;
    int count;
    RHMovementOrderIterator current;
    bool dirty;
    int index;
};

template<class T> T &RHMovementField(void *object, unsigned offset)
{
    return *(T *)((char *)object + offset);
}

class RHMovementPathFinderCalls
{
public:
    void FUN_00553100(void *actor);
};

class RHMovementEngineCalls
{
public:
    void FUN_004d2b70(void *actor);
};

// FUNCTION: GAME 0x00588b20
void RHUnk00588530::FUN_00588b20()
{
    if (RHMovementField<int>(this, 0x10) == 23)
    {
        RHMovementField<RHMovementPathFinderCalls *>(g_pEngine, 0x45b8)->FUN_00553100(RHMovementField<void *>(this, 0x48));
        ((RHMovementEngineCalls *)g_pEngine)->FUN_004d2b70(RHMovementField<void *>(this, 0x48));
        RHMovementField<int>(this, 0x10) = 20;
    }
}

// Parked: cached-cursor live ranges, count guards and switch layout differ.
// STUB: GAME 0x00588b60
void RHUnk00588530::FUN_00588b60()
{
    m_88 |= 0x8000;
    switch (m_94)
    {
    case 6:
    case 16:
    case 305:
        m_94 = 10;
        break;
    case 303:
        m_94 = 304;
        break;
    }
    RHMovementOrderList &orders = RHMovementField<RHMovementOrderList>(this, 0x18);
    if (RHMovementField<int>(this, 0x58) != 3 && (unsigned short)orders.count > 0)
    {
        int count = (unsigned short)orders.count;
        int i = 0;
        do
        {
            RHMovementOrder *order = orders.Value(i);
            switch (order->action)
            {
            case 5:
            case 6:
            case 8:
            case 15:
            case 16:
            case 17:
            case 305:
                order->action = 10;
                break;
            case 303:
                order->action = 304;
                break;
            }
        } while (++i, --count != 0);
    }
    ((RHSequenceElementCalls *)this)->RHSequenceElementCalls::FUN_00585c80();
}

// FUNCTION: GAME 0x00588d40
void RHSequenceElementMovement::FUN_00588d40(int value)
{
    m_94 = value;
    ((RHSequenceElementCalls *)this)->RHSequenceElementCalls::FUN_00585cc0(value);
}

// Parked: cached-cursor live ranges and count guards differ.
// STUB: GAME 0x00588d60
void RHUnk00588530::FUN_00588d60()
{
    m_88 &= ~0x8000;
    switch (m_94)
    {
    case 10:
        m_94 = 6;
        break;
    case 304:
        m_94 = 303;
        break;
    }
    RHMovementOrderList &orders = RHMovementField<RHMovementOrderList>(this, 0x18);
    if (RHMovementField<int>(this, 0x58) != 3 && (unsigned short)orders.count > 0)
    {
        int count = (unsigned short)orders.count;
        int i = 0;
        do
        {
            RHMovementOrder *order = orders.Value(i);
            switch (order->action)
            {
            case 10:
            case 12:
            case 51:
            case 84:
                order->action = 6;
                break;
            case 304:
                order->action = 303;
                break;
            }
        } while (++i, --count != 0);
    }
    ((RHSequenceElementCalls *)this)->RHSequenceElementCalls::FUN_00585d00();
}

// Parked: cached-cursor live ranges and count guards differ.
// STUB: GAME 0x00588f00
void RHUnk00588530::FUN_00588f00()
{
    if (m_94 == 16)
        m_94 = 6;
    RHMovementOrderList &orders = RHMovementField<RHMovementOrderList>(this, 0x18);
    if (RHMovementField<int>(this, 0x58) != 3 && (unsigned short)orders.count > 0)
    {
        int count = (unsigned short)orders.count;
        int i = 0;
        do
        {
            RHMovementOrder *order = orders.Value(i);
            switch (order->action)
            {
            case 15:
            case 16:
            case 17:
            case 81:
            case 83:
                order->action = 6;
                break;
            }
        } while (++i, --count != 0);
    }
    ((RHSequenceElementCalls *)this)->RHSequenceElementCalls::FUN_00585d40();
}

// Parked: cached-cursor live ranges and count guards differ.
// STUB: GAME 0x005890c0
void RHUnk00588530::FUN_005890c0()
{
    m_88 &= ~0x8000;
    if (m_94 == 6 || m_94 == 10)
        m_94 = 16;
    RHMovementOrderList &orders = RHMovementField<RHMovementOrderList>(this, 0x18);
    if (RHMovementField<int>(this, 0x58) != 3 && (unsigned short)orders.count > 0)
    {
        int count = (unsigned short)orders.count;
        int i = 0;
        do
        {
            RHMovementOrder *order = orders.Value(i);
            switch (order->action)
            {
            case 5:
            case 6:
            case 8:
            case 10:
            case 11:
            case 12:
            case 82:
                order->action = 16;
                break;
            }
        } while (++i, --count != 0);
    }
    ((RHSequenceElementCalls *)this)->RHSequenceElementCalls::FUN_00585e30();
}

// FUNCTION: GAME 0x005897e0
bool RHSequenceElementMovement::FUN_005897e0()
{
    RHMovementSequenceView *element = (RHMovementSequenceView *)this;
    if (element->next && element->owner == element->next->owner)
        return element->next->type == 4 || element->next->command == 0x53;
    return false;
}

// FUNCTION: GAME 0x00589810
RHUnk00588530 *RHUnk00588530::FUN_00589810()
{
    RHUnk00588530 *copy = new RHUnk00588530(RHMovementField<unsigned short>(this, 0x14), RHMovementField<int>(this, 0x10), RHMovementField<void *>(this, 0x48));
    ((RHSequenceElementCalls *)copy)->FUN_00585df0((RHSequenceElementCalls *)this);
    copy->m_94 = m_94;
    *(int *)&copy->m_8c = *(int *)&m_8c;
    copy->m_7c = m_7c;
    copy->m_84 = m_84;
    copy->m_80 = m_80;
    copy->m_78 = m_78;
    copy->m_64 = m_64;
    copy->m_6c = m_6c;
    copy->m_90 = m_90;
    copy->m_88 = m_88;
    copy->m_74 = m_74;
    copy->m_68 = m_68;
    m_68 = 0;
    return copy;
}

void RHUnk00588530::EmitMovement()
{
    FUN_00588b20();
    FUN_00588b60();
    FUN_00588d60();
    FUN_00588f00();
    FUN_005890c0();
    FUN_00589810();
}

// FUNCTION: GAME 0x00589910
bool RHSequenceElementMovement::Serialize(SBFile &file, bool pointers)
{
    FUN_00584ef0(file, pointers);
    RH_MOVEMENT_ACCESS(m_94, 4, 1308);
    RH_MOVEMENT_ACCESS(m_8c, 4, 1310);
    RH_MOVEMENT_ACCESS(m_90, 2, 1311);
    RH_MOVEMENT_ACCESS(m_88, 4, 1312);
    RH_MOVEMENT_ACCESS(m_74, 2, 1313);
    RH_MOVEMENT_ACCESS(m_98, 4, 1314);
    m_6c.Serialize(file);
    g_pEngine->SerializeElementPointer(file, *(RHElement **)(&m_84));
    RHUnkPathGeometry *grid = (RHUnkPathGeometry *)g_unk0x6c0a9c;
    grid->Unk004fc030(file, m_7c);
    ((RHFastFindGrid *)grid)->SerializeLinePointer(file, m_80);
    grid->Unk004fbec0(file, m_78);
    bool exists;
    if (!file.m_bLoading)
    {
        exists = m_68 != 0;
        RH_MOVEMENT_ACCESS(exists, 1, 1334);
        if (exists)
            m_68->Serialize(file, false);
    }
    else
    {
        RH_MOVEMENT_ACCESS(exists, 1, 1342);
        if (exists)
        {
            m_68 = (RHSequence *)new RHUnk00582220;
            m_68->Serialize(file, false);
        }
        else
            m_68 = 0;
    }
    if (pointers)
        ((RHSequenceManager *)g_unk0x6c1040)->PreSerializePointer(file, &m_64, false);
    else if (file.m_bLoading)
        m_64 = 0;
    return true;
}
