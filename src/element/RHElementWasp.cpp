#include "SBNullstr.h"
#include "RHElementWasp.h"
#include "RHElementWaspNest.h"
#include "RHEngineSerializationCalls.h"
#include "RHProjectileLifetime.h"
#include "RHTreeDec.h"
#include "RHUnk00641782.h"

DECOMP_SIZE_ASSERT(RHUnk004bc4d0, 0x178)

// FUNCTION: GAME 0x004bc4d0
RHUnk004bc4d0::RHUnk004bc4d0() : RHProjectileLifetime(0, 0), m_15c(0), m_160(0), m_164(0), m_168(0)
{
    *(unsigned long *)this = 0x00678a0c;
}

// FUNCTION: GAME 0x004bc540
RHUnk004bc4d0::RHUnk004bc4d0(const RHElementWaspNest *nest) : RHProjectileLifetime(0, 0), m_15c(nest), m_160(0), m_164(0), m_168(0)
{
    *(unsigned long *)this = 0x00678a0c;
}

#include <utility>
#include <memory>

struct RHsoundGroup;
extern unsigned g_unk0x006c0a40;

class RHWaspVictimTree
{
public:
    typedef RHElementWasp::VictimCandidature Value;
    typedef RHElementWasp::VictimCandidatureOrdering Compare;
    typedef RHTreeDecNode14 Node;
    struct Iterator
    {
        Iterator() {}
        Iterator(Node *value) : node(value) {}
        Iterator operator++(int)
        {
            Iterator previous = *this;
            ((RHTreeInc004bdef0 *)this)->FUN_004bdef0();
            return previous;
        }
        Node *node;
    };
    struct InsertResult
    {
        InsertResult() {}
        InsertResult(const Iterator &value, const bool &added) : position(value), inserted(added) {}
        Iterator position;
        bool inserted;
    };
    RHWaspVictimTree(const Compare &compare, bool multi, const undefined &allocator);
    // FUNCTION: GAME 0x004bce50
    ~RHWaspVictimTree()
    {
        FUN_004bd390(Begin(), End());
        operator delete(m_head);
        m_head = 0;
        m_count = 0;
        {
            RHUnk00641782 lock;
            if (--g_unk0x006c0a40 == 0) {
                operator delete(g_unk0x006c0a3c);
                g_unk0x006c0a3c = 0;
            }
        }
    }
    InsertResult FUN_004bd250(const Value &value);
    InsertResult Insert(const Value &value)
    {
        InsertResult result = FUN_004bd250(value);
        return InsertResult(result.position, result.inserted);
    }
    Iterator FUN_004bd390(Iterator first, Iterator last);
    Iterator FUN_004bd4c0(Iterator entry);
    void FUN_004bd9e0(Node *node);
    void FUN_004bda70();
    Iterator FUN_004bdb20(Node *node, Node *parent, const Value &value);
    static Value &ValueOf(Node *node) { return *(Value *)&node->m_0c; }
    bool Less(const Value &first, const Value &second) { return (*(Compare *)&m_01)(first, second); }
    Node *&Root() { return m_head->m_04; }
    Node *&Leftmost() { return m_head->m_00; }
    Node *&Rightmost() { return m_head->m_08; }
    Iterator Begin() { return Iterator(Leftmost()); }
    Iterator End() { return Iterator(m_head); }
    static Node *&Left(Node *node) { return node->m_00; }
    static Node *&Right(Node *node) { return node->m_08; }
    static Node *&Parent(Node *node) { return node->m_04; }
    static int &Color(Node *node) { return node->m_14; }
    void RotateLeft(Node *node)
    {
        RHUnk00641782 lock;
        Node *right = node->m_08;
        node->m_08 = right->m_00;
        if (right->m_00 != g_unk0x006c0a3c)
            right->m_00->m_04 = node;
        right->m_04 = node->m_04;
        if (node == m_head->m_04)
            m_head->m_04 = right;
        else if (node == node->m_04->m_00)
            node->m_04->m_00 = right;
        else
            node->m_04->m_08 = right;
        right->m_00 = node;
        node->m_04 = right;
    }
    void RotateRight(Node *node)
    {
        RHUnk00641782 lock;
        Node *left = node->m_00;
        node->m_00 = left->m_08;
        if (left->m_08 != g_unk0x006c0a3c)
            left->m_08->m_04 = node;
        left->m_04 = node->m_04;
        if (node == m_head->m_04)
            m_head->m_04 = left;
        else if (node == node->m_04->m_08)
            node->m_04->m_08 = left;
        else
            node->m_04->m_00 = left;
        left->m_08 = node;
        node->m_04 = left;
    }
    undefined m_00;
    undefined m_01;
    undefined m_02[2];
    Node *m_head;
    bool m_08;
    undefined m_09[3];
    unsigned m_count;
};

// GLOBAL: GAME 0x006c0a40
unsigned g_unk0x006c0a40;

#include "RHElementActorHumanBase.h"
#include "RHMalignityActorCalls.h"
#include "RHArtificialMalignityCore.h"
#include "RHMalignityGeometryCalls.h"
#include "RHBonusInfo.h"
#include "RHSequenceGenericCalls.h"
#include "RHScriptEngineCalls.h"
#include "RHActorCancelCalls.h"
#include "RHHumanEngineActorArray.h"
#include <stdlib.h>

class RHUnk6c1040;
extern RHUnk6c1040 *g_unk0x6c1040;

template<class T> inline T &RHWaspField(const void *object, unsigned offset)
{
    return *(T *)((char *)object + offset);
}

inline void RHWaspNormalize(RHUnk00613e90 &direction)
{
    float scale = 5.0f / direction.Norm();
    direction.x *= scale;
    direction.y *= scale;
    direction.z *= scale;
}

// STUB: GAME 0x004bc660
void RHElementWasp::ChangeDirection()
{
    int count = 10;
    RHUnk00613e90 position = RHWaspField<RHUnk00613e90>(RHWaspField<void *>(this, 0x50), 0x10);
    RHUnk00613e90 nest = RHWaspField<RHUnk00613e90>(RHWaspField<void *>(m_15c, 0x50), 0x10);
    RHUnk00613e90 offset(position, nest);
    do {
        RHUnk00613e90 direction((float)(rand() % 11 - 6), (float)(rand() % 11 - 6), (float)(rand() % 11 - 6));
        float length = direction.Norm();
        RHUnk00613e90 destination;
        if (length == 0.0f) {
            m_16c.m_0 = 0;
            m_16c.m_4 = 0;
            m_16c.m_8 = 0;
            return;
        }
        float scale = 5.0f / length;
        direction.x *= scale;
        direction.y *= scale;
        direction.z *= scale;
        if (abs((int)(position.z - nest.z)) < 20)
            direction.z = (float)abs((int)direction.z);
        if (offset.Norm() > 50.0f && !m_160) {
            RHUnk00613e90 correction;
            correction.FUN_00467990(offset.x * 0.08f, offset.y * 0.08f, offset.z * 0.08f);
            direction.x += correction.x;
            direction.y += correction.y;
            direction.z += correction.z;
        }
        if (m_160) {
            RHUnk00613e90 target;
            RHUnk00613e90 delta;
            ((RHElementActor *)m_160)->FUN_00478c20(target, 0);
            delta = RHUnk00613e90(position, target);
            unsigned distance = RHWaspField<int>(m_160, 0xa3c) ? 75 : 25;
            if (!(delta.Norm() > distance))
                direction = delta;
            else
                direction = delta.Scaled(0.08f);
        }
        RHWaspNormalize(direction);
        RHUnk00613e90 step = direction.Scaled(7.0f);
        destination = position.FUN_005df5a0(step);
        if (((RHMalignityGeometryCalls *)g_unk0x6c0a9c)->FUN_004eff80(position, destination, 1)) {
            *(RHUnk00613e90 *)&m_16c = direction;
            return;
        }
        if (count == 1) {
            ((RHMalignityActorCalls *)this)->V5c(0);
            if (m_160)
                RHWaspField<char>(m_160, 0x4f4) = 0;
            return;
        }
    } while (--count);
}

// FUNCTION: GAME 0x004bcad0
void RHElementWasp::ChangeVictim()
{
    if (!m_160) {
        m_160 = ChooseVictim();
        if (m_160)
            RHWaspField<char>(m_160, 0x4f4) = 1;
    }
    else {
        RHUnk00613e90 position = RHWaspField<RHUnk00613e90>(RHWaspField<void *>(this, 0x50), 0x10);
        unsigned distance = RHWaspField<int>(m_160, 0xa3c) ? 210 : 70;
        if (RHUnk00613e90(position, RHWaspField<RHUnk00613e90>(RHWaspField<void *>(m_160, 0x50), 0x10)).Norm() >= distance) {
            RHWaspField<char>(m_160, 0x4f4) = 0;
            m_160 = 0;
        }
    }
}

inline unsigned char RHWaspElementType(const void *actor)
{
    unsigned type = RHWaspField<unsigned>(actor, 4) & 0x1f;
    return (unsigned char)type;
}

inline RHArtificialIntelligence &RHWaspIntelligence(void *actor)
{
    return *(RHArtificialIntelligence *)((char *)actor + RHWaspField<int *>(actor, 0x49c)[1] + 0x49c);
}

// STUB: GAME 0x004bcba0
void *RHElementWasp::ChooseVictim() const
{
    void *victim = 0;
    RHUnk00613e90 position = RHWaspField<RHUnk00613e90>(RHWaspField<void *>(this, 0x50), 0x10);
    VictimCandidatureOrdering firstCompare;
    undefined firstAllocator;
    RHWaspVictimTree first(firstCompare, false, firstAllocator);
    VictimCandidatureOrdering secondCompare;
    undefined secondAllocator;
    RHWaspVictimTree second(secondCompare, false, secondAllocator);
    unsigned short count = ((RHHumanEngineActorArray *)g_pEngine)->Size();
    for (int index = count - 1; index >= 0; --index) {
        RHMalignityActorCalls *actor = (*(RHHumanEngineActorArray *)g_pEngine)[(unsigned short)index];
        if (RHWaspField<char>(actor, 0x12) && RHWaspElementType(actor) == 0x14 &&
            actor->V130() == 1 && !RHWaspField<int>(actor, 0x268)) {
            RHUnk00613e90 target;
            ((RHElementActor *)actor)->FUN_00478c20(target, 0);
            unsigned distance = (unsigned)RHUnk00613e90(position, target).Norm();
            if (distance <= (RHWaspField<int>(actor, 0xa3c) ? 150U : 50U) && !RHWaspField<char>(actor, 0x4f4)) {
                VictimCandidature candidate(distance, actor);
                if (((RHMalignityActorCalls *)candidate.m_04)->Vf8()) {
                    RHWaspIntelligence(actor).Unk00418c40(0x76, 0);
                }
                else if (RHWaspField<int>(actor, 0xa3c))
                    first.Insert(candidate);
                else
                    second.Insert(candidate);
            }
        }
    }
    if (first.m_count)
        victim = RHWaspVictimTree::ValueOf(first.Begin().node).m_04;
    else if (second.m_count)
        victim = RHWaspVictimTree::ValueOf(second.Begin().node).m_04;
    return victim;
}

inline void RHWaspSavePosition(RHBonusInfoBase &info)
{
    info.m_28 = info.m_c;
    info.m_3c = info.m_20;
}

inline void RHWaspSetPosition(RHBonusInfoBase &info, const RHBonusTriple &position)
{
    info.m_c = position;
    info.m_4 = 1;
}

// FUNCTION: GAME 0x004bcec0
bool RHElementWasp::Hourglass()
{
    if (!RHWaspField<char>(this, 0x12))
        return false;
    if (!m_164) {
        if (!m_168) {
            ChangeVictim();
            ChangeDirection();
            m_164 = rand() % 3 + 7;
        }
        else {
            if (!((RHMalignityActorCalls *)m_160)->V48() && !RHWaspField<char>(m_160, 0x1ce) && !RHWaspField<int>(m_160, 0x268)) {
                ((RHUnk0046bcb0 *)m_160)->Unk(5);
                RHUnk00584d60 *action = new RHUnk00584d60(1, 0x89, m_160);
                ((RHScriptBatchCalls *)g_unk0x6c1040)->Unk0058a940("", 0, action);
            }
            ((RHMalignityActorCalls *)this)->V5c(0);
        }
    }
    else
        --m_164;
    if (!m_168) {
        RHWaspSavePosition(RHWaspField<RHBonusInfo *>(this, 0x50)->m_4);
        RHWaspSetPosition(RHWaspField<RHBonusInfo *>(this, 0x50)->m_4,
            (const RHBonusTriple &)RHWaspField<RHUnk00613e90>(RHWaspField<void *>(this, 0x50), 0x10).FUN_005df5a0(*(RHUnk00613e90 *)&m_16c));
        RHWaspField<RHBonusInfo *>(this, 0x50)->m_4.FUN_0055f290();
        RHWaspField<RHBonusInfo *>(this, 0x50)->FUN_005bd560(0, true);
    }
    if (m_160 && !m_168) {
        RHUnk00613e90 target;
        ((RHElementActor *)m_160)->FUN_00478c20(target, 0);
        if (RHUnk00613e90(RHWaspField<RHUnk00613e90>(RHWaspField<void *>(this, 0x50), 0x10), target).Norm() <= 10.0f) {
            m_168 = 1;
            m_164 = rand() % 60 + 1;
        }
    }
    return true;
}

// FUNCTION: GAME 0x004bd0f0
void RHElementWasp::FUN_004bd0f0(void *)
{
    ((RHEngineSerializationCalls *)g_pEngine)->FUN_004d88e0(this, 0, 1);
    ((RHElementWaspNest *)m_15c)->WaspKilled();
}

// FUNCTION: GAME 0x004bd120
bool RHElementWasp::Serialize(SBFile &file)
{
    RHEngine *engine = g_pEngine;
    RHSerializeName(file,
                    // STRING: GAME 0x006aef4c
                    "RHElementWasp");
    engine->FUN_004c42d0(file, m_15c);
    engine->FUN_004c3d90(file, m_160);
    if (file.Access(&m_168, 1) < 0)
    {
        SBString *error = file.GetError();
        SBAssert(0,
                 // STRING: GAME 0x006aef2c
                 "P:\\Robin Hood\\RHElementWasp.cpp",
                 554, "Serialize failed reason is %s", error->m_chars ? error->m_chars : "");
        return false;
    }
    if (file.Access(&m_164, 4) < 0)
    {
        SBString *error = file.GetError();
        SBAssert(0, "P:\\Robin Hood\\RHElementWasp.cpp", 555,
                 "Serialize failed reason is %s", error->m_chars ? error->m_chars : "");
        return false;
    }
    m_16c.Serialize(file);
    return RHElementObject::Serialize(file);
}

// FUNCTION: GAME 0x004bd200
bool RHElementWasp::VictimCandidatureOrdering::operator()(const VictimCandidature &first, const VictimCandidature &second) const
{
    return first.m_00 < second.m_00;
}

// FUNCTION: GAME 0x004bd220
RHWaspVictimTree::RHWaspVictimTree(const Compare &compare, bool multi, const undefined &allocator)
    : m_00(allocator), m_01(*(const undefined *)&compare), m_08(multi)
{
    FUN_004bda70();
}

// FUNCTION: GAME 0x004bd250
RHWaspVictimTree::InsertResult RHWaspVictimTree::FUN_004bd250(const Value &value)
{
    Node *node = Root();
    Node *parent = m_head;
    bool before = true;
    {
        RHUnk00641782 lock;
        while (node != g_unk0x006c0a3c) {
            parent = node;
            before = Less(value, ValueOf(node));
            node = before ? node->m_00 : node->m_08;
        }
    }
    if (m_08) {
        InsertResult result(FUN_004bdb20(node, parent, value), true);
        return result;
    }
    Iterator position(parent);
    if (before) {
        if (position.node == m_head->m_00) {
            InsertResult result(FUN_004bdb20(node, parent, value), true);
            return result;
        }
        ((RHTreeDec004bde30 *)&position)->FUN_004bde30();
    }
    if (Less(ValueOf(position.node), value)) {
        InsertResult result(FUN_004bdb20(node, parent, value), true);
        return result;
    }
    InsertResult result(position, false);
    return result;
}

static inline RHTreeDecNode14 *RHWaspVictimMin(RHTreeDecNode14 *node)
{
    RHUnk00641782 lock;
    while (node->m_00 != g_unk0x006c0a3c)
        node = node->m_00;
    return node;
}

static inline RHTreeDecNode14 *RHWaspVictimMax(RHTreeDecNode14 *node)
{
    RHUnk00641782 lock;
    while (node->m_08 != g_unk0x006c0a3c)
        node = node->m_08;
    return node;
}

// FUNCTION: GAME 0x004bd390
RHWaspVictimTree::Iterator RHWaspVictimTree::FUN_004bd390(Iterator first, Iterator last)
{
    if (m_count != 0 && first.node == m_head->m_00 && last.node == m_head) {
        RHUnk00641782 lock;
        Node *node = m_head->m_04;
        {
            RHUnk00641782 inner;
            for (Node *next = node; next != g_unk0x006c0a3c; node = next) {
                FUN_004bd9e0(next->m_08);
                next = next->m_00;
                operator delete(node);
            }
        }
        Root() = g_unk0x006c0a3c;
        m_count = 0;
        Leftmost() = m_head;
        Rightmost() = m_head;
        return Begin();
    }
    while (first.node != last.node)
        FUN_004bd4c0(first++);
    return first;
}

// FUNCTION: GAME 0x004bd4c0
RHWaspVictimTree::Iterator RHWaspVictimTree::FUN_004bd4c0(Iterator entry)
{
    Node *removed = (entry++).node;
    Node *original = removed;
    Node *replacement;
    RHUnk00641782 lock;
    if (Left(removed) == g_unk0x006c0a3c)
        replacement = Right(removed);
    else if (Right(removed) == g_unk0x006c0a3c)
        replacement = Left(removed);
    else {
        removed = RHWaspVictimMin(Right(removed));
        replacement = Right(removed);
    }
    if (removed != original) {
        Parent(Left(original)) = removed;
        Left(removed) = Left(original);
        if (removed == Right(original))
            Parent(replacement) = removed;
        else {
            Parent(replacement) = Parent(removed);
            Left(Parent(removed)) = replacement;
            Right(removed) = Right(original);
            Parent(Right(original)) = removed;
        }
        if (Root() == original)
            Root() = removed;
        else if (Left(Parent(original)) == original)
            Left(Parent(original)) = removed;
        else
            Right(Parent(original)) = removed;
        Parent(removed) = Parent(original);
        int color = Color(removed);
        Color(removed) = Color(original);
        Color(original) = color;
        removed = original;
    }
    else {
        Parent(replacement) = Parent(removed);
        if (Root() == original)
            Root() = replacement;
        else if (Left(Parent(original)) == original)
            Left(Parent(original)) = replacement;
        else
            Right(Parent(original)) = replacement;
        if (Leftmost() == original) {
            if (Right(original) == g_unk0x006c0a3c)
                Leftmost() = Parent(original);
            else
                Leftmost() = RHWaspVictimMin(replacement);
        }
        if (Rightmost() == original) {
            if (Left(original) == g_unk0x006c0a3c)
                Rightmost() = Parent(original);
            else
                Rightmost() = RHWaspVictimMax(replacement);
        }
    }
    if (Color(removed) == 1) {
        while (replacement != Root() && Color(replacement) == 1) {
            if (replacement == Left(Parent(replacement))) {
                Node *sibling = Right(Parent(replacement));
                if (Color(sibling) == 0) {
                    Color(sibling) = 1;
                    Color(Parent(replacement)) = 0;
                    RotateLeft(Parent(replacement));
                    sibling = Right(Parent(replacement));
                }
                if (Color(Left(sibling)) == 1 && Color(Right(sibling)) == 1) {
                    Color(sibling) = 0;
                    replacement = Parent(replacement);
                }
                else {
                    if (Color(Right(sibling)) == 1) {
                        Color(Left(sibling)) = 1;
                        Color(sibling) = 0;
                        RotateRight(sibling);
                        sibling = Right(Parent(replacement));
                    }
                    Color(sibling) = Color(Parent(replacement));
                    Color(Parent(replacement)) = 1;
                    Color(Right(sibling)) = 1;
                    RotateLeft(Parent(replacement));
                    break;
                }
            }
            else {
                Node *sibling = Left(Parent(replacement));
                if (Color(sibling) == 0) {
                    Color(sibling) = 1;
                    Color(Parent(replacement)) = 0;
                    RotateRight(Parent(replacement));
                    sibling = Left(Parent(replacement));
                }
                if (Color(Right(sibling)) == 1 && Color(Left(sibling)) == 1) {
                    Color(sibling) = 0;
                    replacement = Parent(replacement);
                }
                else {
                    if (Color(Left(sibling)) == 1) {
                        Color(Right(sibling)) = 1;
                        Color(sibling) = 0;
                        RotateLeft(sibling);
                        sibling = Left(Parent(replacement));
                    }
                    Color(sibling) = Color(Parent(replacement));
                    Color(Parent(replacement)) = 1;
                    Color(Left(sibling)) = 1;
                    RotateRight(Parent(replacement));
                    break;
                }
            }
        }
        Color(replacement) = 1;
    }
    operator delete(removed);
    --m_count;
    return entry;
}

// FUNCTION: GAME 0x004bd9e0
void RHWaspVictimTree::FUN_004bd9e0(Node *node)
{
    RHUnk00641782 lock;
    for (Node *next = node; next != g_unk0x006c0a3c; node = next) {
        FUN_004bd9e0(next->m_08);
        next = next->m_00;
        operator delete(node);
    }
}

// FUNCTION: GAME 0x004bda70
void RHWaspVictimTree::FUN_004bda70()
{
    RHUnk00641782 lock;
    if (g_unk0x006c0a3c == 0) {
        Node *node = (Node *)operator new(sizeof(Node));
        node->m_04 = 0;
        node->m_14 = 1;
        g_unk0x006c0a3c = node;
        g_unk0x006c0a3c->m_00 = 0;
        g_unk0x006c0a3c->m_08 = 0;
    }
    ++g_unk0x006c0a40;
    Node *sentinel = g_unk0x006c0a3c;
    Node *head = (Node *)operator new(sizeof(Node));
    head->m_04 = sentinel;
    head->m_14 = 0;
    m_head = head;
    m_count = 0;
    m_head->m_00 = m_head;
    m_head->m_08 = m_head;
}

// FUNCTION: GAME 0x004bdb20
RHWaspVictimTree::Iterator RHWaspVictimTree::FUN_004bdb20(Node *child, Node *parent, const Value &value)
{
    RHUnk00641782 lock;
    Node *inserted = (Node *)operator new(sizeof(Node));
    inserted->m_04 = parent;
    inserted->m_14 = 0;
    inserted->m_00 = g_unk0x006c0a3c;
    inserted->m_08 = g_unk0x006c0a3c;
    typedef std::pair<const unsigned long, RHsoundGroup *> Pair;
    void (*construct)(Pair *, const Pair &) = &std::_Construct;
    construct((Pair *)&ValueOf(inserted), (const Pair &)value);
    ++m_count;
    if (parent == m_head || child != g_unk0x006c0a3c || Less(value, ValueOf(parent))) {
        parent->m_00 = inserted;
        if (parent == m_head) {
            m_head->m_04 = inserted;
            m_head->m_08 = inserted;
        }
        else if (parent == m_head->m_00)
            m_head->m_00 = inserted;
    }
    else {
        parent->m_08 = inserted;
        if (parent == m_head->m_08)
            m_head->m_08 = inserted;
    }
    for (child = inserted; child != m_head->m_04 && child->m_04->m_14 == 0;) {
        if (Parent(child) == Left(Parent(Parent(child)))) {
            parent = child->m_04->m_04->m_08;
            if (parent->m_14 == 0) {
                child->m_04->m_14 = 1;
                parent->m_14 = 1;
                child->m_04->m_04->m_14 = 0;
                child = child->m_04->m_04;
            }
            else {
                if (child == child->m_04->m_08) {
                    child = child->m_04;
                    RotateLeft(child);
                }
                child->m_04->m_14 = 1;
                child->m_04->m_04->m_14 = 0;
                RotateRight(child->m_04->m_04);
            }
        }
        else {
            parent = Left(Parent(Parent(child)));
            if (parent->m_14 == 0) {
                child->m_04->m_14 = 1;
                parent->m_14 = 1;
                child->m_04->m_04->m_14 = 0;
                child = child->m_04->m_04;
            }
            else {
                if (child == child->m_04->m_00) {
                    child = child->m_04;
                    RotateRight(child);
                }
                child->m_04->m_14 = 1;
                child->m_04->m_04->m_14 = 0;
                RotateLeft(child->m_04->m_04);
            }
        }
    }
    m_head->m_04->m_14 = 1;
    return Iterator(inserted);
}

void EmitRHWaspVictimTree(const RHElementWasp::VictimCandidature &value)
{
    RHElementWasp::VictimCandidatureOrdering compare;
    undefined allocator;
    RHWaspVictimTree tree(compare, false, allocator);
    tree.FUN_004bd250(value);
}

void RHElementWasp::Emit(SBFile &file)
{
    RHUnk004bc4d0 *storage = (RHUnk004bc4d0 *)this;
    storage->RHUnk004bc4d0::RHUnk004bc4d0();
    storage->RHUnk004bc4d0::RHUnk004bc4d0((const RHElementWaspNest *)this);
    FUN_004bd0f0(0);
    ChangeVictim();
    Hourglass();
    Serialize(file);
    VictimCandidatureOrdering ordering;
    VictimCandidature first(0, this);
    ordering(first, first);
}
