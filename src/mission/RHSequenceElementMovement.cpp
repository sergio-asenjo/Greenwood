#include "SBNullstr.h"
#include "RHSequenceElementMovement.h"
#include <iterator>
#include "RHActorTranslation.h"

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

#include "RHSequenceElementCalls.h"

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
    void FUN_00588940();
    void FUN_00588b20();
    void FUN_00588b60();
    void FUN_00588d60();
    void FUN_00588f00();
    void FUN_005890c0();
    void FUN_005892a0(int replacement, int action, float distance, const SBGeoPoint2D &origin);
    void FUN_00589490(int replacement, int action, float distance, const SBGeoPoint2D &origin);
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

#include "RHMovementPathFinderCalls.h"

class RHMovementEngineCalls
{
public:
    void FUN_004d2b70(void *actor);
};

class RHUnk005fc3b0 : public SBGeoPoint2D
{
public:
    RHUnk005fc3b0();
    ~RHUnk005fc3b0() {}
    RHUnk005fc3b0 &FUN_005fc430(const SBGeoPoint2D &other);
    RHUnk005fc3b0 &FUN_005fc4d0(float factor);
    float Unk005fc6a0(float factor);
};

class RHSpriteList
{
public:
    void FUN_005c8e40(int index);
};

class RHSpriteSequenceCalls
{
public:
    void FUN_005859e0(RHOrder *order, unsigned short index);
};

class RHSectorActorIter
{
public:
    RHMovementOrderNode *m_p;
    RHSectorActorIter(RHMovementOrderNode *node) : m_p(node) {}
    RHSectorActorIter operator++(int);
};

extern float g_unk0x00677438;
extern float g_unk0x00677488;

// Parked: receiver/index registers and iterator/point argument scheduling differ.
// STUB: GAME 0x00588940
void RHUnk00588530::FUN_00588940()
{
    RHOrder *order = (RHOrder *)RHMovementField<RHMovementOrderNode *>(this, 0x1c)->next->value;
    SBGeoPoint2D position;
    RHUnk005fc3b0 direction;
    m_88 &= ~4;
    switch (order->m_24)
    {
    case 6:
        order->m_24 = 8;
        break;
    case 10:
        order->m_24 = 12;
        break;
    case 16:
        order->m_24 = 17;
        break;
    default:
        ((RHActorTranslationSequenceCalls *)this)->V0c(6, true);
        return;
    }
    order->FUN_0054e730();
    int remaining = RHMovementField<int>(this, 0x20);
    for (int i = remaining - 1; i > 0; --i)
    {
        RHMovementOrderList &orders = RHMovementField<RHMovementOrderList>(this, 0x18);
        ((RHSpriteList *)&orders)->FUN_005c8e40(i);
        delete (RHOrder *)orders.current.node->value;
        RHMovementOrderNode *node = (RHSectorActorIter(orders.current.node)++).m_p;
        node->previous->next = node->next;
        node->next->previous = node->previous;
        operator delete(node);
        --orders.count;
        orders.dirty = true;
    }
    void *owner = RHMovementField<void *>(this, 0x48);
    position = RHMovementField<SBGeoPoint2D>(RHMovementField<void *>(owner, 0x50), 0x24);
    direction.FUN_005fc430(RHMovementField<SBGeoPoint2D>(order, 0x14).Unk005fc110(position));
    float distance = direction.Unk005fc6a0(1.0f);
    if (distance > g_unk0x00677438)
    {
        direction.FUN_005fc4d0(g_unk0x00677438 / distance);
        m_6c = position.Unk005fc190(direction);
    }
}

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

// Parked: count/index widths and receiver/index register allocation differ.
// STUB: GAME 0x005892a0
void RHUnk00588530::FUN_005892a0(int replacement, int action, float distance, const SBGeoPoint2D &origin)
{
    if (distance == g_unk0x00677488)
        distance = 0.01f;
    SBGeoPoint2D previous(origin);
    RHUnk005fc3b0 direction;
    unsigned short count = (unsigned short)RHMovementField<unsigned>(this, 0x20);
    for (unsigned short i = 0; i < count; ++i)
    {
        RHMovementOrderList &orders = RHMovementField<RHMovementOrderList>(this, 0x18);
        ((RHSpriteList *)&orders)->FUN_005c8e40((unsigned short)i);
        RHOrder *order = (RHOrder *)orders.current.node->value;
        if (order->m_24 == action)
        {
            direction.FUN_005fc430(RHMovementField<SBGeoPoint2D>(order, 0x14).Unk005fc110(previous));
            float length = direction.Unk005fc6a0(1.0f);
            if (length < distance)
            {
                distance -= length;
                order->m_24 = replacement;
            }
            else
            {
                order = new RHOrder;
                order->m_24 = replacement;
                order->m_2a = 1;
                RHMovementField<SBGeoPoint2D>(order, 0x14) = previous;
                if (length != g_unk0x00677488)
                {
                    direction.FUN_005fc4d0(distance / length);
                    RHMovementField<SBGeoPoint2D>(order, 0x14).FUN_005fc1e0(direction);
                }
                ((RHSpriteSequenceCalls *)this)->FUN_005859e0(order, (unsigned short)i);
                break;
            }
        }
        SBGeoPoint2D &point = RHMovementField<SBGeoPoint2D>(order, 0x14);
        if (point.m_x != g_unk0x00677488 || point.m_y != g_unk0x00677488)
            previous = point;
    }
}

// GLOBAL: GAME 0x00679db4
float g_unk0x00679db4 = 1.01f;

// Parked: initial count load, loop branches and floating multiply operand order differ.
// STUB: GAME 0x00589490
void RHUnk00588530::FUN_00589490(int replacement, int action, float distance, const SBGeoPoint2D &origin)
{
    if (distance == g_unk0x00677488)
        distance = 0.01f;
    bool scaled = ((unsigned)m_88 >> 16) & 1;
    SBGeoPoint2D previous;
    RHUnk005fc3b0 direction;
    float length;
    distance += m_8c;
    RHMovementOrderList &orders = RHMovementField<RHMovementOrderList>(this, 0x18);
    for (int i = (unsigned short)orders.count - 1; i >= 0; --i)
    {
        ((RHSpriteList *)&orders)->FUN_005c8e40(i);
        RHOrder *order = (RHOrder *)orders.current.node->value;
        if (order->m_24 != action)
            continue;
        order->m_24 = replacement;
        previous = RHMovementField<SBGeoPoint2D>(order, 0x14);
        int j;
        for (j = i - 1; j >= 0; --j)
        {
            ((RHSpriteList *)&orders)->FUN_005c8e40((unsigned short)j);
            order = (RHOrder *)orders.current.node->value;
            SBGeoPoint2D &point = RHMovementField<SBGeoPoint2D>(order, 0x14);
            if (point.m_x != g_unk0x00677488 || point.m_y != g_unk0x00677488)
                goto foundPoint;
        }
        goto useOrigin;
        {
        foundPoint:
            direction.FUN_005fc430(RHMovementField<SBGeoPoint2D>(order, 0x14).Unk005fc110(previous));
            if (scaled)
                length = direction.Unk005fc6a0(0.57357645f);
            else
                length = direction.Unk005fc6a0(1.0f);
            if (length * g_unk0x00679db4 < distance)
            {
                distance -= length;
                continue;
            }
            order = new RHOrder;
            order->m_24 = action;
            order->m_2a = 1;
            RHMovementField<SBGeoPoint2D>(order, 0x14) = previous;
            if (length != g_unk0x00677488)
            {
                direction.FUN_005fc4d0(distance / length);
                RHMovementField<SBGeoPoint2D>(order, 0x14).FUN_005fc1e0(direction);
            }
            RHMovementField<int>(order, 4) = 0;
            if (!(m_88 & 4) || !(m_88 & 0x400))
                order->m_30 = m_84;
            ((RHSpriteSequenceCalls *)this)->FUN_005859e0(order, (unsigned short)i);
            break;
        }
        {
        useOrigin:
            direction.FUN_005fc430(origin.Unk005fc110(previous));
            if (scaled)
                length = direction.Unk005fc6a0(0.57357645f);
            else
                length = direction.Unk005fc6a0(1.0f);
            if (length < distance)
                break;
            order = new RHOrder;
            order->m_24 = action;
            order->m_2a = 1;
            RHMovementField<SBGeoPoint2D>(order, 0x14) = previous;
            if (length != g_unk0x00677488)
            {
                direction.FUN_005fc4d0(distance / length);
                RHMovementField<SBGeoPoint2D>(order, 0x14).FUN_005fc1e0(direction);
            }
            RHMovementField<int>(order, 4) = 0;
            if (!(m_88 & 4) || !(m_88 & 0x400))
                order->m_30 = m_84;
            ((RHSpriteSequenceCalls *)this)->FUN_005859e0(order, (unsigned short)i);
            break;
        }
    }
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
    FUN_00588940();
    FUN_005892a0(0, 0, 1.0f, m_6c);
    FUN_00589490(0, 0, 1.0f, m_6c);
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
