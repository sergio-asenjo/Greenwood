#include "SBNullstr.h"
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


extern float g_unk0x00677488;
extern float g_unk0x0067749c;
extern float g_unk0x006775d8;
extern float g_actorEffectOffset;

// GLOBAL: GAME 0x006787e8
float g_unk0x006787e8 = -8.01f;
// GLOBAL: GAME 0x006787ec
float g_unk0x006787ec = 16.02f;

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
    float traveled = g_unk0x00677488;
    RHProjectileVector result;
    if (frames == 0) {
        float acceleration = gravity;
        traveled = g_unk0x00677488;
        acceleration *= g_unk0x006787ec;
        while (traveled < distance) {
            ++frames;
            traveled += frames * acceleration;
        }
        frames *= 2;
    }
    if (frames == 1)
        result = direction.Scaled(g_unk0x006775d8);
    else {
        struct RawVector { float x; float y; float z; };
        RawVector half = *(RawVector *)&direction.Scaled(g_unk0x006775d8);
        float scale = g_unk0x0067749c / (frames + 1);
        result = ((RHProjectileVector *)&half)->Scaled(scale);
        result.z -= (frames * gravity) * g_unk0x006787e8;
    }
    if (actor) {
        struct RawVector { float x; float y; float z; };
        RawVector half = *(RawVector *)&((const RHProjectileVector *)((char *)*(void **)((char *)actor + 0x50) + 0x138))->Scaled(g_unk0x006775d8);
        RHProjectileVector offset = ((RHProjectileVector *)&half)->Scaled(g_actorEffectOffset);
        result.x += offset.x;
        result.y += offset.y;
        result.z += offset.z;
    }
    return result;
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
            RHUnk00613e90 *value = (RHUnk00613e90 *)list.m_cursor.node->data;
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
            RHUnk00613e90 *value = new RHUnk00613e90;
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
    ((RHProjectileSoundCalls *)g_unk0x006c1070)->FUN_005a8070(sound, position, 9);
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
}
