#include "SBNullstr.h"
extern float g_unk0x006774e4;
#include "RHElementProjectile.h"

#include "RHProjectileLifetime.h"
#include "RHProjectileVector.h"

// FUNCTION: GAME 0x004b4020
RHProjectileLifetime::RHProjectileLifetime(int action, void *victim)
    : RHObjectConstructorCalls(7, false, action), target(victim), count130(0),
      flag132(0), flag133(0), flag134(0), list(*(unsigned char *)&action)
{
    *(bool *)((char *)this + 0x12) = true;
    *(unsigned long *)this = 0x00678758;
    flag135 = 0;
    material = 0;
}

void EmitRHProjectileLifetime(void *storage, int action, void *victim)
{
    ((RHProjectileLifetime *)storage)->RHProjectileLifetime::RHProjectileLifetime(action, victim);
}

// FUNCTION: GAME 0x004b40f0
void *RHProjectileLifetime::FUN_004b40f0(unsigned flags)
{
    this->~RHProjectileLifetime();
    if (flags & 1)
        operator delete(this);
    return this;
}

RHProjectileLifetime::~RHProjectileLifetime() {}




struct RHProjectilePathStep
{
    RHProjectilePathStep()
    {
        ((RHUnk00613e90 *)this)->RHUnk00613e90::RHUnk00613e90();
    }
    unsigned long values[5];
};

struct RHProjectilePathList
{
    void Clear()
    {
        RHScriptNode *last = head;
        for (RHScriptNode *position = last->next; position != last;) {
            RHScriptNode *removed = position;
            position = position->next;
            typedef RHScriptIter (RHUnk0046eb30::*Erase)(RHScriptNode *);
            (((RHUnk0046eb30 *)this)->*reinterpret_cast<Erase>(&RHUnk0046eb30::erase))(removed);
        }
        dirty = true;
    }
    void PushBack(RHProjectilePathStep *value)
    {
        RHScriptNode *next = head;
        RHScriptNode *previous = next->previous;
        RHScriptNode *created = (RHScriptNode *)operator new(12);
        created->next = next ? next : created;
        created->previous = previous ? previous : created;
        next->previous = created;
        created->previous->next = created;
        void **payload = &created->data;
        if (payload)
            *payload = value;
        ++count;
        dirty = true;
    }
    void Advance(int distance)
    {
        std::bidirectional_iterator_tag category;
        FUN_005c9010((RHUnk005c9010Iterator &)cursor, distance, category);
    }
    RHScriptNode *&SetCursor(RHScriptNode *node)
    {
        *(RHScriptNode *volatile *)&cursor = node;
        return cursor;
    }
    void ResetAndAdvance(RHScriptNode *node, int distance)
    {
        std::bidirectional_iterator_tag category;
        FUN_005c9010((RHUnk005c9010Iterator &)SetCursor(node), distance, category);
    }
    void InlineAdvance(int distance)
    {
        while (distance > 0) {
            cursor = cursor->next;
            --distance;
        }
        while (distance < 0) {
            cursor = cursor->previous;
            ++distance;
        }
    }
    RHProjectilePathStep *Get(int wanted, bool InlineHead)
    {
        int size = count;
        if (dirty) {
            if (wanted <= (size + 1) / 2) {
                ResetAndAdvance(InlineHead ? *(RHScriptNode *volatile *)&head->next : ((RHUnk0046eb30 *)this)->FUN_0046eb80().node, wanted);
            }
            else {
                RHScriptNode *node = *(RHScriptNode *volatile *)&head;
                cursor = node;
                Advance(wanted - size);
            }
            dirty = false;
            index = wanted;
        }
        else {
            int previous = index;
            if (wanted != previous) {
                if (wanted < previous) {
                    if (wanted < (previous + 1) / 2) {
                        if (InlineHead) {
                            std::bidirectional_iterator_tag category;
                            RHScriptIter &position = *(RHScriptIter *)&cursor;
                            FUN_005c9010((RHUnk005c9010Iterator &)(position =
                                RHScriptIter(*(RHScriptNode *volatile *)&head->next)), wanted, category);
                        }
                        else {
                            ResetAndAdvance(((RHUnk0046eb30 *)this)->FUN_0046eb80().node, wanted);
                        }
                    }
                    else
                        Advance(wanted - previous);
                }
                else if (wanted < (size + previous) / 2) {
                    if (InlineHead)
                        InlineAdvance(wanted - previous);
                    else
                        Advance(wanted - previous);
                }
                else {
                    cursor = head;
                    if (InlineHead)
                        InlineAdvance(wanted - size);
                    else
                        Advance(wanted - size);
                }
                index = wanted;
            }
        }
        return (RHProjectilePathStep *)cursor->data;
    }
    unsigned char allocator;
    RHScriptNode *head;
    int count;
    RHScriptNode *cursor;
    bool dirty;
    int index;
};

// Parked: vector copies coalesce; frame is 0x28 versus 0x34 and float operand order differs.
// STUB: GAME 0x004b4260
RHProjectileVector RHProjectileThrowCalls::FUN_004b4260(const RHProjectileVector &direction, float distance, float gravity, unsigned short frames, const void *actor)
{
    float traveled = 0.0f;
    RHProjectileVector result;
    if (frames == 0) {
        float acceleration = gravity;
        traveled = 0.0f;
        acceleration *= 16.02f;
        while (traveled < distance) {
            ++frames;
            traveled += frames * acceleration;
        }
        frames *= 2;
    }
    if (frames == 1)
        result = direction.Scaled(0.5f);
    else {
        struct RawVector { float x; float y; float z; };
        RawVector half = *(RawVector *)&direction.Scaled(0.5f);
        float scale = 1.0f / (frames + 1);
        result = ((RHProjectileVector *)&half)->Scaled(scale);
        result.z -= (frames * gravity) * (-8.01f);
    }
    if (actor) {
        struct RawVector { float x; float y; float z; };
        RawVector half = *(RawVector *)&((const RHProjectileVector *)((char *)*(void **)((char *)actor + 0x50) + 0x138))->Scaled(0.5f);
        RHProjectileVector offset = ((RHProjectileVector *)&half)->Scaled(4.0f);
        result.x += offset.x;
        result.y += offset.y;
        result.z += offset.z;
    }
    return result;
}

#include "SBGeoPoint2D.h"
#include "SBGeoSegment2D.h"
#include "SBGeoIntersection2D.h"
#include "RHUnk005fc3b0.h"
#include "RHUnkSectorPoints.h"
#include "RHUnk0053bf20.h"
#include "SCQuad.h"

DECOMP_SIZE_ASSERT(RHUnk00613e90, 0x0c)
DECOMP_SIZE_ASSERT(RHProjectileVector, 0x0c)
DECOMP_SIZE_ASSERT(RHProjectileSerializedStep, 0x14)
DECOMP_SIZE_ASSERT(RHProjectilePathStep, 0x14)
DECOMP_SIZE_ASSERT(RHProjectilePathList, 0x18)

// STUB: GAME 0x004b5ab0
void RHElementProjectile::AddTrajectoryFallIntoHole(void *material)
{
    m_134 = true;
    unsigned count = m_138.m_count;
    if (count >= 2) {
        RHProjectilePathList &path = *(RHProjectilePathList *)&m_138;
        ((RHProfileListCursor *)&path)->GoTo(count - 1);
        RHProjectileVector last = *(RHProjectileVector *)path.cursor->data;
        ((RHProfileListCursor *)&path)->GoTo(count - 2);
        RHProjectileVector previous = *(RHProjectileVector *)path.cursor->data;
        SBGeoPoint2D end(last.x, last.y - last.z);
        SBGeoPoint2D start(previous.x, previous.y - previous.z);
        RHUnk0060fbf0 intersection;
        RHMobileUnk006100e0 line(end, start);
        SBGeoPoint2D lowest(end);
        lowest.m_y += 2000.0f;
        bool found = false;
        bool alternate = false;
        SBGeoSegment2D edge(SBGeoPoint2D(0.0f, 0.0f), SBGeoPoint2D(0.0f, 0.0f));
        edge.First() = start;
        RHUnkSectorPoints &points = *(RHUnkSectorPoints *)((char *)material + 4);
        unsigned size = points.Unk0060ce80();
        for (unsigned index = 0; index < size; ++index) {
            if (alternate) {
                edge.First() = points.Unk0060cef0(index);
                alternate = false;
            }
            else {
                edge.Second() = points.Unk0060cef0(index);
                alternate = true;
            }
            intersection.FUN_0060fca0(line.FUN_006101c0(edge.Line()));
            if (((SCQuadArg *)&intersection)->GetType() == 1 &&
                ((SBGeoPoint2D *)((RHUnk0053bf20 *)&intersection)->FUN_0053bf20())->m_y > end.m_y &&
                ((SBGeoPoint2D *)((RHUnk0053bf20 *)&intersection)->FUN_0053bf20())->m_y < lowest.m_y) {
                lowest = *(SBGeoPoint2D *)((RHUnk0053bf20 *)&intersection)->FUN_0053bf20();
                found = true;
            }
        }
        if (found) {
            ((RHProfileListCursor *)&path)->GoTo(count - 1);
            float scale = (unsigned short)((RHProjectileSerializedStep *)path.cursor->data)->m_0c /
                ((RHUnk005fc3b0 *)&end.Unk005fc110(start))->Unk005fc6a0(1.0f);
            RHProjectileSerializedStep *step = new RHProjectileSerializedStep;
            step->m_0e = 0;
            ((RHProjectileVector *)step)->Set(lowest.m_x, lowest.m_y + last.z, last.z);
            step->m_0c = ((RHUnk005fc3b0 *)&lowest.Unk005fc110(end))->Unk005fc6a0(1.0f) * scale;
            ((SBListCursorStorage<std::list<RHProjectileSerializedStep *> > *)&path)->InsertLast(step);
        }
    }
}

void EmitRHProjectileFall(RHElementProjectile *projectile, void *material)
{
    projectile->AddTrajectoryFallIntoHole(material);
}

// Parked: allocation and cached-cursor live ranges select different registers and schedules.
// STUB: GAME 0x004b5ee0
void RHElementProjectile::CopyTrajectory(RHElementProjectile *other)
{
    unsigned count = other->m_138.m_count;
    ((RHProjectilePathList *)&m_138)->Clear();
    int index = 0;
    unsigned remaining = (unsigned short)count;
    while (remaining != 0) {
        RHProjectilePathStep *value = new RHProjectilePathStep;
        *value = *((RHProjectilePathList *)&other->m_138)->Get(index, false);
        ((RHProjectilePathList *)&m_138)->PushBack(value);
        ++index;
        --remaining;
    }
    m_100 = other->m_100;
    struct TrajectoryState { unsigned long values[4]; };
    *(TrajectoryState *)m_118 = *(TrajectoryState *)other->m_118;
    m_133 = other->m_133;
    m_12c = other->m_12c;
    m_130 = other->m_130;
}

// FUNCTION: GAME 0x004b6170
void RHElementProjectile::ComputeTrajectoryJump(const RHProjectileVector &from, const RHProjectileVector &to)
{
    RHProjectileVector direction;
    RHProjectileVector velocity;
    RHProjectileVector nextVelocity;
    RHProjectileVector position;
    RHProjectileVector nextPosition;
    RHProjectilePathList &path = *(RHProjectilePathList *)&m_138;
    path.Clear();
    *(RHProjectileVector *)&m_100 = from;
    direction = to;
    direction.x -= from.x;
    direction.y -= from.y;
    direction.z -= from.z;
    velocity = ((RHProjectileThrowCalls *)this)->FUN_004b4260(direction, 0.5f, 0.7f, 0, 0);
    position = from;
    for (unsigned short count = 0; count < 50; ++count) {
        nextVelocity.z = velocity.z - 11.214f;
        if (position.z < 0.0f && nextVelocity.z <= 0.0f)
            return;
        nextPosition.x = position.x + velocity.x * 2.0f;
        nextPosition.y = position.y + velocity.y * 2.0f;
        nextPosition.z = position.z + velocity.z * 2.0f;
        RHProjectileSerializedStep *step = new RHProjectileSerializedStep;
        path.PushBack((RHProjectilePathStep *)step);
        step->m_0c = 4;
        if (((RHUnk00613e90 *)&direction)->FUN_005df5f0(
                ((RHUnk00613e90 *)&nextPosition)->FUN_005df550((const RHUnk00613e90 &)to)) > -0.1f) {
            *(RHProjectileVector *)step = to;
            return;
        }
        else {
            *(RHProjectileVector *)step = nextPosition;
            velocity.z = nextVelocity.z;
            position = nextPosition;
        }
    }
}

void EmitRHProjectileTrajectory(RHElementProjectile *projectile, const RHProjectileVector &from, const RHProjectileVector &to)
{
    projectile->ComputeTrajectoryJump(from, to);
}

#define RH_PROJECTILE_ACCESS(field, width, line) \
    if (file.Access(&(field), width) < 0) \
    { \
        SBString *error = file.GetError(); \
        const char *reason = error->m_chars ? error->m_chars : ""; \
        SBAssert(0, g_projectileFile, line, "Serialize failed reason is %s", reason); \
        return false; \
    }

// GLOBAL: GAME 0x006aed38
static const char g_projectileFile[] = "P:\\Robin Hood\\RHelementprojectile.cpp";
// GLOBAL: GAME 0x006aed60
static const char g_projectileNestedFile[] = "P:\\Robin Hood\\RHelementprojectile.cpp";

// Parked: frame and cursor scheduling; unannotated to preserve matched callers.
bool RHElementProjectile::Serialize(SBFile &file)
{
    unsigned count;
    // STRING: GAME 0x006aed88
    RHSerializeName(file, "RHElementProjectile");
    RH_PROJECTILE_ACCESS(m_132, 1, 1404);
    RH_PROJECTILE_ACCESS(m_133, 1, 1405);
    RH_PROJECTILE_ACCESS(m_135, 1, 1406);
    RH_PROJECTILE_ACCESS(m_130, 2, 1407);
    RH_PROJECTILE_ACCESS(m_118, 16, 1408);
    if (!((RHUnkPathGeometry *)g_unk0x6c0a9c)->Unk004fbec0(file, m_120))
    {
        SBAssert(1, g_projectileNestedFile, 1409, "Serialization failed");
        return false;
    }
    RH_PROJECTILE_ACCESS(m_128, 2, 1411);
    m_100.Serialize(file);
    unsigned version = file.m_version;
    if (version >= 44)
        m_10c.Serialize(file);
    g_pEngine->FUN_004c3bd0(file, m_12c);
    if (!file.m_bLoading)
    {
        count = m_138.m_count;
        RH_PROJECTILE_ACCESS(count, 4, 1427);
        for (unsigned i = 0; i < count; ++i)
        {
            RHProjectileList &list = m_138;
            ((RHTitbitList *)&list)->At(i);
            RHProjectileSerializedStep *value = (RHProjectileSerializedStep *)list.m_cursor.node->data;
            RH_PROJECTILE_ACCESS(value->m_0c, 2, 1433);
            RH_PROJECTILE_ACCESS(value->m_0e, 1, 1434);
            RH_PROJECTILE_ACCESS(value->m_10, 4, 1435);
            value->m_00.Serialize(file);
        }
    }
    else
    {
        RH_PROJECTILE_ACCESS(count, 4, 1441);
        m_138.Resize(count);
        for (unsigned i = 0; i < count; ++i)
        {
            RHProjectileSerializedStep *value = new RHProjectileSerializedStep;
            RH_PROJECTILE_ACCESS(value->m_0c, 2, 1448);
            RH_PROJECTILE_ACCESS(value->m_0e, 1, 1449);
            RH_PROJECTILE_ACCESS(value->m_10, 4, 1450);
            value->m_00.Serialize(file);
            m_138.Get(i) = value;
        }
    }
    RHElementObject::Serialize(file);
    if (file.m_version < 44)
    {
        const RHUnk005df510 *value;
        if (m_138.m_count == 0)
            value = (RHUnk005df510 *)((char *)*(void **)((char *)this + 0x50) + 0x10);
        else
            value = (RHUnk005df510 *)m_138.m_head->previous->data;
        m_10c = *value;
    }
    return true;
}

void RHElementProjectile::Emit(SBFile &file)
{
    Serialize(file);
}

// FUNCTION: GAME 0x004b7fc0
int RHProjectileVector::FUN_004b7fc0(const RHProjectileVector &other) const
{
    if (x == other.x && y == other.y && z == other.z)
        return 0;
    return 1;
}

#include "RHElementPositionCalls.h"
#include "RHScriptEngineCalls.h"
#include "RHElementObjectTypeBits.h"

static inline RHobjectType RHProjectileObjectType(const void *element)
{
    return (RHobjectType)((const RHElementObjectTypeBits *)((const char *)element + 4))->type;
}

// STUB: GAME 0x004b8000
void *RHElementProjectile::FUN_004b8000() const
{
    unsigned mask;
    switch (*(const int *)((const char *)this + 0xb0)) {
    case 4:
        mask = 0x40;
        break;
    case 5:
        mask = 1;
        break;
    case 6:
        mask = 0x20;
        break;
    default:
        return 0;
    }
    RHEngine *engine = g_pEngine;
    void *result = 0;
    RHUnk00613e90 movement;
    char *sprite = *(char **)((char *)this + 0x50);
    movement = *(RHUnk00613e90 *)(sprite + 0x10);
    movement.x -= *(float *)(sprite + 0x2c);
    movement.y -= *(float *)(sprite + 0x30);
    movement.z -= *(float *)(sprite + 0x34);
    float length = movement.Norm();
    void **first = *(void ***)((char *)engine + 0x48dc);
    unsigned size;
    if (!first)
        size = 0;
    else
        size = *(void ***)((char *)engine + 0x48e0) - first;
    for (unsigned index = 0; index < size; ++index) {
        char *target = (char *)(*(void ***)((char *)engine + 0x48dc))[index];
        if (RHProjectileObjectType(target) == 9) {
            RHProjectileVector center = *(RHProjectileVector *)&((RHElementPositionCalls *)target)->FUN_004bb180();
            RHUnk00613e90 distance;
            RHUnk00613e90 delta;
            sprite = *(char **)((char *)this + 0x50);
            distance = ((RHUnk00613e90 *)&center)->DistanceVectorToLine(*(RHUnk00613e90 *)(sprite + 0x10), *(RHUnk00613e90 *)(sprite + 0x2c));
            sprite = *(char **)((char *)this + 0x50);
            delta = *(RHUnk00613e90 *)(sprite + 0x10);
            delta.x -= center.x;
            delta.y -= center.y;
            delta.z -= center.z;
            if (*(bool *)(target + 0x12) && distance.Norm() <= g_unk0x006774e4 && delta.Norm() <= length &&
                (mask & ((RHScriptBatchCalls *)target)->Unk004baea0()) > 0) {
                result = target;
                break;
            }
        }
    }
    return result;
}

void *EmitRHProjectileTarget(RHElementProjectile *projectile)
{
    return projectile->FUN_004b8000();
}

struct RHUnk00571160Position;
#include "RHPositionProvider.h"

class RHBonusInfoBase
{
public:
    void FUN_0055f290();
    void SetHeight(float value)
    {
        *(int *)((char *)this + 4) = 1;
        *(float *)((char *)this + 0x14) = value;
    }
    float Height() const { return *(float *)((char *)this + 0x14); }
};

class RHShadowUnk005df9e0
{
public:
    float FUN_005df9e0(float x, float y);
};

struct RHAnimalNoisePosition;
class RHElementActorNPC
{
public:
    static void Noise(int kind, RHAnimalNoisePosition &position, float height, void *source);
};

extern float g_unk0x006774cc;

// FUNCTION: GAME 0x004b8230
void RHElementProjectile::FUN_004b8230()
{
    unsigned char position[16];
    ((RHUnk00560420 *)((char *)*(void **)((char *)this + 0x50) + 4))->Unk((RHUnk00571160Position *)position);
    char *sprite = *(char **)((char *)this + 0x50);
    void *material = *(void **)(sprite + 0xec);
    if (!material) {
        *(float *)(sprite + 0x18) = 0.001f;
        *(int *)(sprite + 8) = 1;
    }
    else if (*(unsigned short *)(sprite + 0xde) != 0xffff && *(int *)((char *)this + 0xb0) != 5) {
        float height = ((RHShadowUnk005df9e0 *)((char *)material + 0xa8))->FUN_005df9e0(*(float *)(sprite + 0x10), *(float *)(sprite + 0x14)) + g_unk0x006774cc;
        sprite = *(char **)((char *)this + 0x50);
        ((RHBonusInfoBase *)(sprite + 4))->SetHeight(height);
    }
    ((RHBonusInfoBase *)((char *)*(void **)((char *)this + 0x50) + 4))->FUN_0055f290();
    if (*(int *)((char *)this + 0xb0) == 5)
        RHElementActorNPC::Noise(2, *(RHAnimalNoisePosition *)position, ((RHBonusInfoBase *)((char *)*(void **)((char *)this + 0x50) + 4))->Height(), 0);
}

// FUNCTION: GAME 0x004b8840
void RHProjectileVector::FUN_004b8840(const RHProjectileVector &other)
{
    x = other.x + x;
    y = other.y + y;
    z = other.z + z;
}

class RHProjectileImpactVirtuals
{
public:
    virtual void V00(); virtual void V04(); virtual void V08(); virtual void V0c();
    virtual void V10(); virtual void V14(); virtual void V18(); virtual void V1c();
    virtual void V20(); virtual void V24(); virtual void V28(); virtual void V2c();
    virtual void V30(); virtual void V34(); virtual void V38(); virtual void V3c();
    virtual void V40(); virtual void V44(); virtual void V48(); virtual void V4c();
    virtual void V50(); virtual void V54(); virtual void V58(); virtual void V5c();
    virtual void V60(); virtual void V64(); virtual void V68(); virtual void V6c();
    virtual void V70(); virtual int V74() const;
};

#include "RHProjectileSoundCalls.h"
#include "RHScrollObjectCalls.h"
class RHArtificialIntelligenceSoundCalls;
extern RHArtificialIntelligenceSoundCalls *g_unk0x006c1070;

// FUNCTION: GAME 0x004b8860
void RHElementProjectile::PlayImpactSound(const void *position, bool special) const
{
    int sound;
    if (special)
        sound = 0x1d6;
    else {
        sound = ((const RHProjectileImpactVirtuals *)this)->V74();
        if (sound == -1)
            return;
    }
    ((RHSound *)g_unk0x006c1070)->FUN_005a8070(sound, *(const SBGeoPoint2D *)position, 9);
}

// FUNCTION: GAME 0x004b8bd0
unsigned RHElementProjectile::ComputeNumberOfFramesLeft() const
{
    unsigned total = 0;
    unsigned count = m_138.m_count;
    for (int index = 0; (unsigned)index < count; ++index) {
        RHProjectilePathStep *value = ((RHProjectilePathList *)&m_138)->Get(index, true);
        total += *(unsigned short *)((char *)value + 0xc);
    }
    return total;
}

// FUNCTION: GAME 0x004b8d70
int RHElementProjectile::FUN_004b8d70(void *first, void *second, void *third)
{
    if (!m_132 && ((RHScrollObjectCalls *)this)->FUN_004b23c0(first, second, third))
        return 1;
    return 0;
}

// FUNCTION: GAME 0x004b8da0
int RHElementProjectile::FUN_004b8da0() const
{
    return -1;
}

#include "RHHumanActorCalls.h"

static inline RHobjectType RHProjectileBaseType(const void *element)
{
    return (RHobjectType)(((const RHElementObjectTypeBits *)((const char *)element + 4))->type & 7);
}

// STUB: GAME 0x004b8db0
bool RHElementProjectile::WillHit(void *target)
{
    RHUnk00613e90 center;
    if (RHProjectileBaseType(target) == 4)
        ((RHHumanActorCalls *)target)->FUN_00479320(center);
    else if (RHProjectileObjectType(target) == 9)
        center = ((RHElementPositionCalls *)target)->FUN_004bb180();
    else
        center = *(RHUnk00613e90 *)(*(char **)((char *)target + 0x50) + 0x10);
    RHUnk00613e90 first;
    RHUnk00613e90 second;
    unsigned count = m_138.m_count;
    if (count)
        first = *(RHUnk00613e90 *)m_138.m_head->next->data;
    for (unsigned index = 1; index < count; ++index) {
        RHProjectilePathList &path = *(RHProjectilePathList *)&m_138;
        ((RHProfileListCursor *)&path)->GoTo(index);
        second = *(RHUnk00613e90 *)path.cursor->data;
        float length = second.FUN_005df550(first).Norm();
        if (first.FUN_005df550(center).Norm() < length &&
            center.DistanceVectorToLine(first, second).Norm() <= g_unk0x006774e4)
            return true;
        first = second;
    }
    return false;
}

void EmitRHProjectileMedium(RHElementProjectile *projectile, RHProjectileVector *vector)
{
    ((RHProjectileThrowCalls *)projectile)->FUN_004b4260(*vector, 1.0f, 1.0f, 1, projectile);
    projectile->CopyTrajectory(projectile);
    vector->FUN_004b7fc0(*vector);
    projectile->FUN_004b8230();
    vector->FUN_004b8840(*vector);
    projectile->PlayImpactSound(vector, false);
    projectile->ComputeNumberOfFramesLeft();
    projectile->FUN_004b8d70(0, 0, 0);
    projectile->FUN_004b8da0();
    projectile->WillHit(projectile);
}
