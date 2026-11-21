#include "SBNullstr.h"
#include "RHElementActorNPC_calls.h"
#include "RHMalignityActorCalls.h"
#include "RHMalignityOwnerCalls.h"
#include "RHElementActorHumanCore.h"
#include "RHShadowPolygon.h"
#include "RHSectorCore.h"
#include "RHElementObject.h"
#include "RHFastFindGridCore.h"

DECOMP_SIZE_ASSERT(RHNPCDetectableRecord, 0x14)
DECOMP_SIZE_ASSERT(RHNPCDetectableNode, 0x1c)
DECOMP_SIZE_ASSERT(RHNPCDetectableStorage, 0x18)
DECOMP_SIZE_ASSERT(RHNPCDetectableList, 0x34)
DECOMP_STATIC_ASSERT(offsetof(RHElementActorNPC, m_detectables) == 0x504)
DECOMP_SIZE_ASSERT(RHElementActorNPC, 0x704)
DECOMP_STATIC_ASSERT(offsetof(RHElementActorNPC, m_4cc) == 0x4cc)
DECOMP_STATIC_ASSERT(offsetof(RHElementActorNPC, m_detectableStrength) == 0x63c)
DECOMP_STATIC_ASSERT(offsetof(RHElementActorNPC, m_654) == 0x654)
DECOMP_STATIC_ASSERT(offsetof(RHviewParameters, m_viewStatus) == 0x08)
DECOMP_STATIC_ASSERT(offsetof(RHviewParameters, m_48) == 0x48)
DECOMP_STATIC_ASSERT(offsetof(RHviewParameters, m_50) == 0x50)
DECOMP_STATIC_ASSERT(offsetof(RHviewParameters, m_58) == 0x58)
DECOMP_STATIC_ASSERT(offsetof(RHviewParameters, m_78) == 0x78)
DECOMP_STATIC_ASSERT(offsetof(RHElementObject, m_fc) == 0xfc)
DECOMP_STATIC_ASSERT(offsetof(RHSprite, m_c) == 0x10)
DECOMP_STATIC_ASSERT(offsetof(RHSprite, m_d4) == 0xd8)
DECOMP_STATIC_ASSERT(offsetof(RHSprite, m_dc) == 0xe0)
DECOMP_STATIC_ASSERT(offsetof(RHElement, m_64) == 0x64)
DECOMP_STATIC_ASSERT(offsetof(RHEngine, m_showSightRadius) == 0x4b3c)

#define RHNPC_ACCESS(buffer, size, line) \
    if (file.Access(buffer, size) < 0) \
    { \
        SBString *error = file.GetError(); \
        SBAssert(0, "P:\\Robin Hood\\RHelementactornpc.cpp", line, "Serialize failed reason is %s", error->m_chars ? error->m_chars : ""); \
        return false; \
    }

#define RHNPC_CHECK(expression, line) \
    if (!(expression)) \
    { \
        SBAssert(1, "P:\\Robin Hood\\RHelementactornpc.cpp", line, "Serialization failed"); \
        return false; \
    }

// FUNCTION: GAME 0x00486260
bool RHDetectable::Serialize(SBFile &file)
{
    RHSerializeName(file,
                    // STRING: GAME 0x006ae5bc
                    "RHDetectable");
    RHNPC_ACCESS(&m_04, 4, 144);
    RHNPC_ACCESS(&m_08, 1, 145);
    RHNPC_ACCESS(&m_0a, 1, 146);
    RHNPC_ACCESS(&m_0c, 1, 147);
    RHNPC_ACCESS(&m_09, 1, 148);
    RHNPC_ACCESS(&m_10, 4, 149);
    if (!FUN_00416b30(m_00, file))
    {
        SBAssert(1,
                 // STRING: GAME 0x006ae598
                 "P:\\Robin Hood\\RHelementactornpc.cpp", 150, "Serialization failed");
        return false;
    }
    return true;
}

#define RHNPC_FIELD(type, offset) (*(type *)((char *)this + (offset)))

struct RHNPCCachedCursor
{
    RHScriptNode *node;
    RHNPCCachedCursor(RHScriptNode *value) : node(value) {}
    RHNPCCachedCursor &operator=(const RHNPCCachedCursor &other)
    {
        node = other.node;
        return *this;
    }
};

struct RHNPCCachedList
{
    int allocator;
    RHScriptNode *head;
    int size;
    RHNPCCachedCursor current;
    bool valid;
    int index;
    RHNPCCachedCursor Begin()
    {
        return RHNPCCachedCursor(*(RHScriptNode *volatile *)&head->next);
    }
    RHNPCCachedCursor End()
    {
        return RHNPCCachedCursor(*(RHScriptNode *volatile *)&head);
    }
    RHDetectable &Get(int wanted)
    {
        int count = size;
        if (valid)
        {
            if (wanted <= (count + 1) / 2)
            {
                current = Begin();
                std::bidirectional_iterator_tag category;
                FUN_005c9010((RHUnk005c9010Iterator &)current, wanted, category);
            }
            else
            {
                current = End();
                std::bidirectional_iterator_tag category;
                FUN_005c9010((RHUnk005c9010Iterator &)current, wanted - count, category);
            }
            valid = false;
            index = wanted;
        }
        else
        {
            int previous = index;
            if (wanted != previous)
            {
                if (wanted < previous)
                {
                    if (wanted < (previous + 1) / 2)
                    {
                        current = RHNPCCachedCursor(((RHUnk0046eb30 *)this)->FUN_0046eb80().node);
                        std::bidirectional_iterator_tag category;
                        FUN_005c9010((RHUnk005c9010Iterator &)current, wanted, category);
                    }
                    else
                    {
                        std::bidirectional_iterator_tag category;
                        FUN_005c9010((RHUnk005c9010Iterator &)current, wanted - previous, category);
                    }
                }
                else if (wanted < (previous + count) / 2)
                {
                    std::bidirectional_iterator_tag category;
                    FUN_005c9010((RHUnk005c9010Iterator &)current, wanted - previous, category);
                }
                else
                {
                    current = End();
                    std::bidirectional_iterator_tag category;
                    FUN_005c9010((RHUnk005c9010Iterator &)current, wanted - count, category);
                }
                index = wanted;
            }
        }
        return *(RHDetectable *)&current.node->data;
    }
};

extern unsigned *g_unk0x006c08a4;

// FUNCTION: GAME 0x00486790
int RHElementActorNPC::FUN_00486790()
{
    return 0;
}

// FUNCTION: GAME 0x004867d0
RHNPCUnk004867d0::~RHNPCUnk004867d0()
{
}

// GLOBAL: GAME 0x006c087c
unsigned char g_unk0x006c087c = 0;
// GLOBAL: GAME 0x006c087d
unsigned char g_unk0x006c087d = 0;
// GLOBAL: GAME 0x006c0880
unsigned char g_unk0x006c0880 = 0;
// GLOBAL: GAME 0x006c0881
unsigned char g_unk0x006c0881 = 0;
// GLOBAL: GAME 0x006c08a8
unsigned char g_unk0x006c08a8 = 0;
// GLOBAL: GAME 0x006c08a9
unsigned char g_unk0x006c08a9 = 0;
// GLOBAL: GAME 0x006c08ac
unsigned char g_unk0x006c08ac[32] = {0};
// GLOBAL: GAME 0x006c08cc
unsigned char g_unk0x006c08cc[32] = {0};
// GLOBAL: GAME 0x006c0884
unsigned char g_unk0x006c0884[32] = {0};

inline void RHNPCColorChannels(unsigned long color, unsigned char &red, unsigned char &green, unsigned char &blue)
{
    red = color;
    green = color >> 8;
    blue = color >> 16;
}

// Parked: byte-local storage, channel conversion order and x87 lifetimes differ.
// STUB: GAME 0x00486940
void RHElementActorNPC::FUN_00486940(unsigned long first, unsigned long second, unsigned long third)
{
    unsigned char red = first;
    unsigned char green = first >> 8;
    unsigned char blue = first >> 16;
    RHNPCColorChannels(second, g_unk0x006c0881, g_unk0x006c087d, g_unk0x006c08a8);
    RHNPCColorChannels(third, g_unk0x006c0880, g_unk0x006c087c, g_unk0x006c08a9);
    float redStart = red;
    float redEnd = g_unk0x006c0881;
    float greenStart = green;
    float greenEnd = g_unk0x006c087d;
    float blueStart = blue;
    float blueEnd = g_unk0x006c08a8;
    int i = 0;
    int count = 32;
    do {
        g_unk0x006c08ac[i] = redStart * (1.0f - i * (1.0f / 36.0f)) + redEnd * (i * (1.0f / 36.0f));
        g_unk0x006c08cc[i] = greenStart * (1.0f - i * (1.0f / 36.0f)) + greenEnd * (i * (1.0f / 36.0f));
        g_unk0x006c0884[i] = blueStart * (1.0f - i * (1.0f / 36.0f)) + blueEnd * (i * (1.0f / 36.0f));
        ++i;
    } while (--count);
}

// FUNCTION: GAME 0x00486f30
void RHElementActorNPC::FUN_00486f30(unsigned char status)
{
    RHNPC_FIELD(unsigned char, 0x65d) = RHNPC_FIELD(unsigned char, 0x65c) != status;
    RHNPC_FIELD(unsigned char, 0x65c) = status;
}

// FUNCTION: GAME 0x00486f70
void RHElementActorNPC::FUN_00486f70()
{
    RHNPC_FIELD(unsigned char, 0x65d) = 1;
    RHNPC_FIELD(unsigned short, 0x6c2) = 5;
    RHNPC_FIELD(unsigned short, 0x6c0) = *(unsigned short *)((char *)g_pEngine + 0x4cc0);
    RHNPC_FIELD(unsigned char, 0x65c) = 8;
}

// FUNCTION: GAME 0x00487aa0
void RHElementActorNPC::FUN_00487aa0(void *target)
{
    if (target)
    {
        RHNPC_FIELD(void *, 0x6bc) = target;
        RHNPC_FIELD(unsigned char, 0x65c) = 6;
        RHNPC_FIELD(float, 0x660) = 1.3f;
    }
    else
        FUN_00487b70();
}

RHUnk00613e90 FUN_00414360(const RHMalignityPosition &position, bool mode);

struct RHNPCProjectionCopy
{
    RHNPCProjectionCopy(const RHUnk00613e90 &value)
        : x(value.m_0), y(value.m_4), z(value.m_8) {}
    float x;
    float y;
    float z;
};

// Parked: projection return-buffer and scalar-copy stack slots differ.
// STUB: GAME 0x00487ad0
void RHElementActorNPC::FUN_00487ad0(const RHMalignityPosition &position)
{
    RHNPCProjectionCopy projected(FUN_00414360(position, false));
    SBGeoPoint2D point(projected.x, projected.y);
    RHNPC_FIELD(SBGeoPoint2D, 0x6b4) = point;
    RHNPC_FIELD(unsigned char, 0x65c) = 7;
    RHNPC_FIELD(float, 0x660) = 1.3f;
}

// FUNCTION: GAME 0x00487b70
void RHElementActorNPC::FUN_00487b70()
{
    RHNPC_FIELD(unsigned char, 0x65c) = 1;
    RHNPC_FIELD(float, 0x660) = 0.8f;
}

// FUNCTION: GAME 0x00487b90
void RHElementActorNPC::FUN_00487b90(
    const SBGeoBoundingBox2D &box, float zoom, unsigned long flags, int)
{
    SBGeoVector2D vector;
    RHUnk00613e90 origin;
    if (FUN_004860b0())
        return;
    char viewStatus = m_654.m_viewStatus;
    if (!viewStatus || !m_12)
        return;
    const RHSector *area = static_cast<const RHSector *>(m_50->m_dc);
    if (area && ((unsigned char)((unsigned)area->m_30 >> 13) & 1))
        return;
    if (viewStatus == 5)
        return;

    FUN_00478c20(origin, 0);
    if (origin.z >= 0.0f)
    {
        unsigned char red, green, blue;
        FUN_0048a650(red, green, blue);
        unsigned short blueChannel = blue;
        unsigned short greenChannel = green;
        RHShadowPolygon *polygon = m_4cc;
        unsigned short redChannel = red;
        polygon->m_c6 = blueChannel;
        unsigned long displayFlags = flags;
        polygon->m_c4 = greenChannel;
        polygon->m_c2 = redChannel;
        m_4cc->DisplayDebug(box, zoom, this, origin, m_654, displayFlags);
        if (g_pEngine->m_showSightRadius)
            m_4cc->FUN_0058ea70();
    }
}

// FUNCTION: GAME 0x00487ce0
void RHElementActorNPC::FUN_00487ce0()
{
    RHNPC_FIELD(RHSprite *, 0x50)->FUN_005bd8b0();
    RHNPC_FIELD(unsigned char, 0x08) = 0;
}

// Parked: VC6 lays out and cross-jumps the two state-range switch bodies differently.
// STUB: GAME 0x004887a0
bool RHElementActorNPC::FUN_004887a0(int kind)
{
    int state;
    if (((RHNPCActorCalls *)this)->V130() == 1)
    {
        switch (kind)
        {
        case 0:
        case 1:
            state = *(int *)((char *)this + 0x4a8 + (*(int **)((char *)this + 0x49c))[1]);
            if (state >= 0 && state <= 2)
                return false;
            return true;
        case 2:
            state = *(int *)((char *)this + 0x4a8 + (*(int **)((char *)this + 0x49c))[1]);
            if (state >= 0 && state <= 1)
                return false;
            return true;
        case 3:
        case 4:
        case 5:
            return true;
        }
    }
    else
    {
        switch (kind)
        {
        case 0:
            return true;
        case 1:
            state = *(int *)((char *)this + 0x4a8 + (*(int **)((char *)this + 0x49c))[1]);
            if (state >= 0 && state <= 2)
                return false;
            return true;
        case 2:
            state = *(int *)((char *)this + 0x4a8 + (*(int **)((char *)this + 0x49c))[1]);
            if (state >= 0 && state <= 1)
                return false;
            return true;
        case 3:
        case 4:
        case 5:
            return true;
        }
    }
    return false;
}

#include "RHMalignityPosition.h"
#include "RHMalignityStimulus.h"

struct RHNPCDetectableTimerPayload
{
    RHMalignityPosition position;
    int mode;
    unsigned short timer;
    char m_16[6];
};

DECOMP_SIZE_ASSERT(RHMalignityStimulus, 0x2c)
DECOMP_SIZE_ASSERT(RHDetectable, 0x14)
DECOMP_SIZE_ASSERT(RHNPCCachedList, 0x18)
DECOMP_SIZE_ASSERT(RHNPCDetectableTimerPayload, 0x1c)

inline void RHNPCDetectableList::Seek(int wanted)
{
    int count = size();
    if (m_dirty)
    {
        if (wanted <= (count + 1) / 2)
        {
            m_cursor = begin();
            std::advance(m_cursor, wanted);
        }
        else
        {
            m_cursor = end();
            std::advance(m_cursor, wanted - count);
        }
        m_dirty = false;
    }
    else if (wanted == m_index)
        return;
    else if (wanted < m_index)
    {
        if (wanted < (m_index + 1) / 2)
        {
            m_cursor = begin();
            std::advance(m_cursor, wanted);
        }
        else
            std::advance(m_cursor, wanted - m_index);
    }
    else if (wanted < (m_index + count) / 2)
        std::advance(m_cursor, wanted - m_index);
    else
    {
        m_cursor = end();
        std::advance(m_cursor, wanted - count);
    }
    m_index = wanted;
}

// STUB: GAME 0x00488870
void RHElementActorNPC::CleanUpDetectables(int kind)
{
    RHNPCDetectableList &list = m_detectables[kind];
    unsigned short count = list.size();
    for (unsigned short i = 0; i < count; ++i)
    {
        list.Seek(i);
        void *object = list.m_cursor->m_00;
        bool remove;
        switch (kind)
        {
        case 0: remove = static_cast<RHElement *>(object)->IsDead() != 0; break;
        case 2: remove = !static_cast<RHElement *>(object)->m_12; break;
        case 5: remove = !static_cast<RHElementActorHuman *>(object)->IsTrueOrFalseBeggar(); break;
        default: continue;
        }
        if (remove)
        {
            list.Seek(i);
            list.erase(list.m_cursor);
            list.m_dirty = true;
            --i;
            --count;
        }
    }
}

// FUNCTION: GAME 0x00488a40
void RHElementActorNPC::FUN_00488a40(unsigned char index, unsigned short timer)
{
    RHMalignityStimulus stimulus;
    if (!((RHNPCActorCalls *)(*(RHArtificialIntelligence *)((char *)this + (*(int **)((char *)this + 0x49c))[1] + 0x49c)).m_actor)->V48())
    {
        RHNPCCachedList &list = RHNPC_FIELD(RHNPCCachedList, 0x504);
        ((RHSectorActorList *)&list)->Unk005c8e40(index);
        RHDetectable &value = *(RHDetectable *)&list.current.node->data;
        char previous = value.m_09;
        value.m_09 = timer > 0;
        if (!previous && value.m_09 && !value.m_08)
        {
            RHNPCDetectableTimerPayload payload;
            payload.mode = *(void **)((char *)value.m_00 + 0x268) ? 13 : 3;
            payload.position = ((RHArtificialIntelligence *)((char *)this + (*(int **)((char *)this + 0x49c))[1] + 0x49c))->FUN_004165e0(value.m_00, true);
            payload.timer = timer;
            stimulus.m_20 = 2;
            *(RHNPCDetectableTimerPayload *)stimulus.m_00 = payload;
            stimulus.m_type = 1;
            ((RHArtificialIntelligence *)((char *)this + (*(int **)((char *)this + 0x49c))[1] + 0x49c))->V24(&stimulus);
        }
    }
}

void EmitRHNPCDetectableTimer(RHElementActorNPC &actor)
{
    actor.FUN_00488a40(0, 0);
}

#include "RHArtificialIntelligenceValueList.h"
#include "RHStimulus.h"
#include "RHElementActorPC.h"

DECOMP_STATIC_ASSERT(offsetof(RHElementActorPC, m_5e8) == 0x5e8)

static inline int RHNPCDetectionCamp(RHElementActorNPC *actor)
{
    typedef int (__fastcall *GetCamp)(RHElementActorNPC *);
    return (*reinterpret_cast<GetCamp **>(actor))[0x130 / 4](actor);
}

static inline void RHNPCQueueDetection(RHArtificialIntelligenceValueList<RHStimulus> &stimuli,
                                      RHStimulus &stimulus, RHDetectable &value,
                                      unsigned type, unsigned event)
{
    memcpy(stimulus.m_00, &value.m_00, sizeof(value.m_00));
    stimulus.m_20 = event;
    stimulus.m_type = type;
    RHArtificialIntelligenceValueList<RHStimulus>::Iterator position = {stimuli.m_head};
    stimuli.Insert(position, stimulus);
    stimuli.m_dirty = true;
}

// FUNCTION: GAME 0x00488b80
bool RHElementActorNPC::HandleDetection(RHDetectable &value, bool visible,
                                       RHArtificialIntelligenceValueList<RHStimulus> &stimuli)
{
    RHStimulus stimulus;
    bool react = false;
    int kind = value.m_04;
    if (visible && !value.m_08)
    {
        switch (kind)
        {
        case 0:
        {
            RHElement *actor = static_cast<RHElement *>(value.m_00);
            stimulus.m_20 = 0;
            memcpy(stimulus.m_00, &actor, sizeof(actor));
            stimulus.m_type = 3;
            stimuli.Append(stimulus);
            stimuli.m_dirty = true;
            value.m_08 = true;
            if (actor->m_elementType == 4 && RHNPCDetectionCamp(this) == 0 && actor->m_08)
                actor->FUN_004621f0();
            break;
        }
        case 3:
            RHNPCQueueDetection(stimuli, stimulus, value, 3, 11);
            react = true;
            break;
        case 4:
            RHNPCQueueDetection(stimuli, stimulus, value, 3, 18);
            react = true;
            break;
        case 1:
            RHNPCQueueDetection(stimuli, stimulus, value, 3, 9);
            react = true;
            break;
        case 5:
            RHNPCQueueDetection(stimuli, stimulus, value, 3, 31);
            react = true;
            break;
        case 2:
            RHNPCQueueDetection(stimuli, stimulus, value, 5, 10);
            react = true;
            break;
        }
    }
    else if (kind == 0 && !visible && value.m_08)
    {
        void *actor = value.m_00;
        RHArtificialIntelligenceValueList<RHStimulus>::Iterator position = {stimuli.m_head};
        stimulus.m_20 = 1;
        memcpy(stimulus.m_00, &actor, sizeof(actor));
        stimulus.m_type = 3;
        stimuli.Insert(position, stimulus);
        stimuli.m_dirty = true;
        value.m_08 = false;
    }
    return react;
}

#include "RHUnk00571160Position.h"

// FUNCTION: GAME 0x00488e00
void RHElementActorNPC::HandlePredetection(RHDetectable &value, unsigned short amount,
                                          RHArtificialIntelligenceValueList<RHStimulus> &stimuli)
{
    int kind = value.m_04;
    RHStimulus stimulus;
    if (kind >= 3 && kind <= 5)
        return;
    RHElement *actor = static_cast<RHElement *>(value.m_00);
    if (actor->m_elementType != 12 || static_cast<RHElementActorPC *>(value.m_00)->m_5e8)
        return;
    bool detected = amount > 0 && m_detectableStrength[kind] >= 100;
    char previous = value.m_0c;
    value.m_0c = detected;
    if (previous || !detected)
        return;
    RHUnk00571160Position position;
    switch (kind)
    {
    case 0:
    case 1:
    case 2:
        actor->m_50->GetPosition(position);
        break;
    case 3:
    case 4:
    case 5:
        return;
    }
    stimulus.m_20 = 53;
    memcpy(stimulus.m_00, &position, sizeof(position));
    stimulus.m_type = 2;
    RHArtificialIntelligenceValueNode<RHStimulus> *next = stimuli.m_head;
    RHArtificialIntelligenceValueNode<RHStimulus> *previousNode = next->m_previous;
    RHArtificialIntelligenceValueNode<RHStimulus> *node =
        static_cast<RHArtificialIntelligenceValueNode<RHStimulus> *>(operator new(sizeof(*node)));
    node->m_next = next ? next : node;
    node->m_previous = previousNode ? previousNode : node;
    next->m_previous = node;
    node->m_previous->m_next = node;
    new (&node->m_value) RHStimulus(stimulus);
    stimuli.m_dirty = true;
    ++stimuli.m_count;
}

#include "../engine/RHMessenger.h"

RHMessenger *RHUnk00546050();
extern bool g_unk0x006c068d;

// STUB: GAME 0x0048af40
bool RHElementActorNPC::FUN_0048af40(const SBGeoPoint2D &point, RHElementActorHuman *pc, int focus)
{
    if (!RHNPC_FIELD(char, 0x12))
        return false;
    if (focus != 5 && focus != 0x10 && focus != 2 &&
        *(unsigned *)((char *)g_pEngine + 0x4a00) > 1)
        return false;

    unsigned char state = *(unsigned char *)((char *)RHUnk00546050() + 0x20);
    bool includeKey;
    RHMalignityActorCalls *self = (RHMalignityActorCalls *)this;

    switch (focus)
    {
    case 4:
        if (state)
        {
            if (!RHNPC_FIELD(char, 8) &&
                (self->V48() || self->V130() == 0 ||
                 (RHNPC_FIELD(unsigned, 4) & 0x1f) == 4 || self->Vf8()))
                return false;
            includeKey = RHNPC_FIELD(bool, 8);
            return ((RHSprite *)RHNPC_FIELD(void *, 0x50))->FUN_005b9e30(
                (void *)&point, RHNPC_FIELD(void *, 0x54), includeKey);
        }
        if (RHNPC_FIELD(char, 8) ||
            FUN_004860b0() ||
            (self->V130() == 0 && (RHNPC_FIELD(unsigned, 4) & 0x1f) == 0x14))
            return false;
        return ((RHSprite *)RHNPC_FIELD(void *, 0x50))->FUN_005b9e30(
            (void *)&point, RHNPC_FIELD(void *, 0x54), false);
    case 7:
        if (state)
        {
            if (!RHNPC_FIELD(char, 8) &&
                ((RHNPC_FIELD(unsigned, 4) & 0x1f) != 0x14 || self->V130() == 0 || self->V48()))
                return false;
            return ((RHSprite *)RHNPC_FIELD(void *, 0x50))->FUN_005b9e30(
                (void *)&point, RHNPC_FIELD(void *, 0x54), RHNPC_FIELD(bool, 8));
        }
        if (RHNPC_FIELD(char, 8) || (RHNPC_FIELD(unsigned, 4) & 0x1f) != 0x14 ||
            self->V130() == 0 || FUN_004860b0())
            return false;
        return ((RHSprite *)RHNPC_FIELD(void *, 0x50))->FUN_005b9e30(
            (void *)&point, RHNPC_FIELD(void *, 0x54), false);
    case 8:
        if (state)
        {
            if (!RHNPC_FIELD(char, 8) &&
                ((RHNPC_FIELD(unsigned, 4) & 0x1f) != 0x14 || self->V130() == 0 ||
                 self->V48() || self->Vf8()))
                return false;
            return ((RHSprite *)RHNPC_FIELD(void *, 0x50))->FUN_005b9e30(
                (void *)&point, RHNPC_FIELD(void *, 0x54), RHNPC_FIELD(bool, 8));
        }
        if (RHNPC_FIELD(char, 8) || (RHNPC_FIELD(unsigned, 4) & 0x1f) != 0x14 ||
            self->V130() == 0 || FUN_004860b0() || self->Vf8())
            return false;
        return ((RHSprite *)RHNPC_FIELD(void *, 0x50))->FUN_005b9e30(
            (void *)&point, RHNPC_FIELD(void *, 0x54), false);
    case 6:
        if (state)
        {
            if (!RHNPC_FIELD(char, 8) &&
                (self->V48() || self->V130() != 1 || self->Vf4() || self->Vf8()))
                return false;
            return ((RHSprite *)RHNPC_FIELD(void *, 0x50))->FUN_005b9e30(
                (void *)&point, RHNPC_FIELD(void *, 0x54), RHNPC_FIELD(bool, 8));
        }
        if (RHNPC_FIELD(char, 8) || FUN_004860b0() ||
            self->V130() != 1 || self->Vf8() || self->Vf4())
            return false;
        return ((RHSprite *)RHNPC_FIELD(void *, 0x50))->FUN_005b9e30(
            (void *)&point, RHNPC_FIELD(void *, 0x54), false);
    case 2:
        if (RHNPC_FIELD(char, 8))
            return false;
        return ((RHSprite *)RHNPC_FIELD(void *, 0x50))->FUN_005b9e30(
            (void *)&point, RHNPC_FIELD(void *, 0x54), g_unk0x006c068d);
    case 3:
        if (RHNPC_FIELD(void *, 0x500))
        {
            if (RHNPC_FIELD(char, 8))
                return ((RHElementActorHuman *)this)->FUN_00483160((void *)&point, pc, focus);
            if (!FUN_004860b0())
                return ((RHSprite *)RHNPC_FIELD(void *, 0x50))->FUN_005b9e30(
                    (void *)&point, RHNPC_FIELD(void *, 0x54), false);
        }
        if (RHNPC_FIELD(char, 8))
            return ((RHElementActorHuman *)this)->FUN_00483160((void *)&point, pc, focus);
        if (RHNPC_FIELD(int, 0x4f0) &&
            FUN_004860b0() &&
            RHNPC_FIELD(unsigned short, 0x23c) == 0 &&
            *(int *)((char *)RHNPC_FIELD(void *, 0x50) + 0x8c) != 7 &&
            ((RHScriptBatchCalls *)pc)->Unk0049d560(0x17))
        {
            if (!self->Vf8())
                return ((RHSprite *)RHNPC_FIELD(void *, 0x50))->FUN_005b9e30(
                    (void *)&point, RHNPC_FIELD(void *, 0x54), false);
            if (pc && ((RHMalignityActorCalls *)pc)->V168())
                return ((RHSprite *)RHNPC_FIELD(void *, 0x50))->FUN_005b9e30(
                    (void *)&point, RHNPC_FIELD(void *, 0x54), false);
        }
        if (RHNPC_FIELD(char, 8))
            return ((RHElementActorHuman *)this)->FUN_00483160((void *)&point, pc, focus);
        if (!self->V48() &&
            RHNPC_FIELD(char, 0x1ce) &&
            *(int *)((char *)RHNPC_FIELD(void *, 0x50) + 0x8c) == 3 &&
            (RHNPC_FIELD(unsigned, 4) & 0x1f) == 0x14 &&
            self->V130() != 0 &&
            !self->Vf8() &&
            ((RHScriptBatchCalls *)pc)->Unk0049d560(0x1d))
            return ((RHSprite *)RHNPC_FIELD(void *, 0x50))->FUN_005b9e30(
                (void *)&point, RHNPC_FIELD(void *, 0x54), false);
        if (RHNPC_FIELD(char, 8))
            return ((RHElementActorHuman *)this)->FUN_00483160((void *)&point, pc, focus);
        if (RHNPC_FIELD(char, 0x1ce) &&
            !self->V48() &&
            *(int *)((char *)RHNPC_FIELD(void *, 0x50) + 0x8c) != 0x12 &&
            *(int *)((char *)RHNPC_FIELD(void *, 0x50) + 0x8c) != 7 &&
            !self->Vf4() &&
            !self->Vf8() &&
            !FUN_0048efa0() &&
            ((RHScriptBatchCalls *)pc)->Unk0049d560(0x1b))
            return ((RHSprite *)RHNPC_FIELD(void *, 0x50))->FUN_005b9e30(
                (void *)&point, RHNPC_FIELD(void *, 0x54), false);
        return ((RHElementActorHuman *)this)->FUN_00483160((void *)&point, pc, focus);
    default:
        return ((RHElementActorHuman *)this)->FUN_00483160((void *)&point, pc, focus);
    }
}

// FUNCTION: GAME 0x0048b440
void RHElementActorNPC::SetUniversalFrameCounter(unsigned long &counter)
{
    g_unk0x006c08a4 = (unsigned *)&counter;
}

#include "RHSoldierNPCCalls.h"

#include "RHAIStateCalls.h"

class RHNPCAIStateCalls
{
public:
    virtual void V00() = 0;
    virtual void V04() = 0;
    virtual void V08() = 0;
    virtual void V0c() = 0;
    virtual void V10(int state, bool flag) = 0;
};

#define RHNPC_AI(type) ((type *)((char *)this + 0x49c + (*(int **)((char *)this + 0x49c))[1]))

// FUNCTION: GAME 0x0048b510
void RHSoldierNPCCalls::FUN_0048b510(void *element)
{
    RHNPC_AI(RHArtificialIntelligence)->SetMusicState(0, true);
    RHNPC_AI(RHNPCAIStateCalls)->V10(0, true);
    if (*((char *)this + 0x65c))
        ((RHElementActorNPC *)this)->FUN_00486f30(5);
    *((bool *)this + 0x4ee) = element && (*(unsigned *)((char *)element + 4) & 0xf) == 0xc;
    *((char *)RHNPC_AI(char) + 0x2ac) = 0;
    RHNPC_AI(RHArtificialIntelligence)->SetReactionState(0);
    RHElementActorNPC::FUN_0048c6a0(this, 3);
    RHElementActorNPC::FUN_0048c6a0(this, 4);
    ((RHElementActorHuman *)this)->FUN_0047f4f0(element);
}

// STRING: GAME 0x006ae570
static const char *g_rhelementactornpcFile = "P:\\Robin Hood\\RHelementactornpc.cpp";

// parked: 0x0048b5d0, 84.82%; unannotated to preserve coupled callers.
bool RHElementActorNPC::Serialize(SBFile &file)
{
    unsigned count;
    unsigned char type;
    RHDetectable value;
    RHEngine *engine = g_pEngine;
    RHSerializeName(file,
                    // STRING: GAME 0x006ae5cc
                    "RHElementActorNPC");
    RHNPC_ACCESS((char *)this + 0x4c8, 2, 3973);
    RHNPC_ACCESS((char *)this + 0x4ca, 2, 3974);
    RHNPC_ACCESS((char *)this + 0x4d0, 2, 3975);
    RHNPC_ACCESS((char *)this + 0x4ec, 2, 3976);
    if (file.m_version >= 3)
        engine->FUN_004c4490(file, *(void **)((char *)this + 0x500));
    else
    {
        int oldValue;
        RHNPC_ACCESS(&oldValue, 4, 3984);
        if (file.m_bLoading)
            *(void **)((char *)this + 0x500) = 0;
    }
    RHNPC_ACCESS((char *)this + 0x4ee, 1, 3991);
    RHNPC_ACCESS((char *)this + 0x4f0, 4, 3994);
    RHNPC_ACCESS((char *)this + 0x4f4, 1, 3995);
    RHNPC_ACCESS((char *)this + 0x4f6, 2, 3997);
    RHNPC_ACCESS((char *)this + 0x654, 0x90, 4000);
    engine->SerializeElementPointer(file, *(RHElement **)((char *)this + 0x6bc));
    RHNPC_ACCESS((char *)this + 0x4dc, 0x10, 4003);
    RHNPC_CHECK(((RHUnkPathGeometry *)g_unk0x6c0a9c)->Unk004fbec0(file, *(void **)((char *)this + 0x4e4)), 4004);
    ((SBGeoPoint2D *)((char *)this + 0x4d4))->Serialize(file);
    RHNPC_ACCESS((char *)this + 0x6e4, 1, 4009);
    char *ai = (char *)this + 0x49c;
    RHNPC_CHECK(((RHArtificialIntelligence *)(ai + (*(int **)ai)[1]))->Unk00414be0(file), 4012);
    RHNPC_ACCESS((char *)this + 0x4fa, 2, 4014);
    RHNPC_ACCESS((char *)this + 0x4fc, 4, 4015);
    for (type = 0; type < 6; ++type)
    {
        if (file.m_bLoading)
        {
            RHNPC_ACCESS(&count, 4, 4022);
            RHNPCDetectableStorage &list = (RHNPCDetectableStorage &)((RHNPCDetectableList *)((char *)this + 0x504))[type];
            RHSectorActorIter current((RHSectorActorNode *)list.m_head->m_next);
            RHSectorActorNode *end = (RHSectorActorNode *)list.m_head;
            while (current.m_p != end)
                ((RHUnk0046eb30 *)&list)->erase(RHScriptIter((RHScriptNode *)(current++).m_p));
            list.m_valid = 1;
            for (unsigned index = 0; index < count; ++index)
            {
                RHNPC_CHECK(value.Serialize(file), 4028);
                list.insert(list.end(), value);
            }
        }
        else
        {
            RHNPCDetectableStorage &list = (RHNPCDetectableStorage &)((RHNPCDetectableList *)((char *)this + 0x504))[type];
            count = list.m_count;
            RHNPC_ACCESS(&count, 4, 4036);
            for (unsigned index = 0; index < count; ++index)
            {
                ((RHTitbitList *)&list)->At(index);
                RHNPC_CHECK(((RHDetectable *)&list.m_cur->m_data)->Serialize(file), 4041);
            }
        }
        RHNPC_ACCESS((char *)this + 0x63c + type * 2, 2, 4046);
    }
    RHNPC_ACCESS((char *)this + 0x648, 2, 4049);
    RHNPC_ACCESS((char *)this + 0x64c, 4, 4050);
    RHNPC_ACCESS((char *)this + 0x4a0, 0x28, 4051);
    RHNPC_ACCESS((char *)this + 0x652, 1, 4054);
    if (file.m_bLoading)
    {
        *(short *)((char *)this + 0x4f8) = 0;
        *((char *)this + 0x6e5) = 0;
    }
    return ((RHNPCBaseCalls *)this)->FUN_004799e0(file);
}

#define SBGEO_BOUNDINGBOX2D_VIEW
#include "RHActorSequenceStorage.h"

#include "RHElementActorPC.h"
#include "RHSequenceConstructionCalls.h"
#include "RHSequenceInteractionAction.h"
#include "RHSequenceGenericConstruction.h"

// STUB: GAME 0x0048be40
bool RHElementActorNPC::FUN_0048be40(void *context, unsigned flags, RHElementActorHuman *target)
{
    if (RHNPC_FIELD(void *, 0x500))
    {
        RHSequence *sequence = new RHSequence;
        if (!*(char *)((char *)this + (*(int **)((char *)this + 0x49c))[1] + 0x660))
        {
            RHUnk00584d60 *action = new RHUnk00584d60(1, 0x7f, this);
            action->AppendToSequence(sequence);
        }
        RHUnk00585ea0 *first = new RHUnk00585ea0(1, 0x1b, target, this);
        first->AppendToSequence(sequence);
        RHUnk00585ea0 *second = new RHUnk00585ea0(1, 0x1b, this, target);
        second->AppendToSequence(sequence);
        if (!*(char *)((char *)this + (*(int **)((char *)this + 0x49c))[1] + 0x660))
        {
            RHUnk00584d60 *action = new RHUnk00584d60(2, 0x80, this);
            action->AppendToSequence(sequence);
        }
        RHUnk005866a0 *action = new RHUnk005866a0(2, 0xaf, 0);
        action->Unk00586ed0(0x28, (int)RHNPC_FIELD(void *, 0x500));
        action->Unk00586ed0(0x29, (int)target);
        action->Unk00586ed0(0x2a, (int)this);
        action->AppendToSequence(sequence);
        ((RHElementActorPC *)target)->FUN_004a0340(sequence, (flags & 8) != 0, 0x1e, 0x32, (RHElementActorHuman *)this, true);
        return true;
    }
    if ((RHNPC_FIELD(char, 0x1ce) || ((RHNPCActorCalls *)this)->V48()) &&
        *(int *)(RHNPC_FIELD(char *, 0x50) + 0x8c) != 7 &&
        RHNPC_FIELD(int, 0x4f0) && ((RHScriptBatchCalls *)target)->Unk0049d560(0x17))
    {
        RHUnk00585ea0 *action = new RHUnk00585ea0(1, 0x55, target, this);
        char *sprite = *(char **)((char *)target + 0x50);
        float duration;
        {
            SBGeoVector2D offset(*(SBGeoPoint2D *)(sprite + 0x1c));
            unsigned short heading = *(unsigned short *)(sprite + 0xd8);
            void *profile = ((RHUnk005b5e00 *)sprite)->Unk();
            SBGeoPoint2D *point = ((RHUnk005b5e00 *)sprite)->Unk005bdd30(
                *(short *)(*(char **)((char *)profile + 4) + 0xf4) + heading);
            duration = ((RHUnk005fc3b0 *)&point->Unk005fc190(offset)
                .Unk005fc110(*(SBGeoPoint2D *)(sprite + 0x24)))->Unk005fc6a0(1.0f);
        }
        ((RHElementActorPC *)target)->FUN_0049ffe0(action, flags, (int)duration, 0x33, 0, 0, 0x80000);
        return true;
    }
    if (RHNPC_FIELD(char, 0x1ce) && !RHNPC_FIELD(char, 8) &&
        !((RHNPCActorCalls *)this)->V48() &&
        (RHNPC_FIELD(unsigned, 4) & 0x1f) == 0x14 &&
        !((RHNPCActorCalls *)this)->Vf8() &&
        *(int *)(RHNPC_FIELD(char *, 0x50) + 0x8c) == 3 &&
        ((RHScriptBatchCalls *)target)->Unk0049d560(0x1d))
    {
        RHUnk00585ea0 *action = new RHUnk00585ea0(1, 0x45, target, this);
        ((RHElementActorPC *)target)->FUN_0049ffe0(action, flags, 0x28, 0xb, 0, 0, 0x80000);
        return true;
    }
    if (RHNPC_FIELD(char, 0x1ce) &&
        *(int *)(RHNPC_FIELD(char *, 0x50) + 0x8c) == 3 &&
        ((RHScriptBatchCalls *)target)->Unk0049d560(0x1b))
    {
        RHUnk00585ea0 *action = new RHUnk00585ea0(1, 0x72, target, this);
        char *sprite = *(char **)((char *)target + 0x50);
        float duration;
        {
            SBGeoVector2D offset(*(SBGeoPoint2D *)(sprite + 0x1c));
            unsigned short heading = *(unsigned short *)(sprite + 0xd8);
            void *profile = ((RHUnk005b5e00 *)sprite)->Unk();
            SBGeoPoint2D *point = ((RHUnk005b5e00 *)sprite)->Unk005bdd30(
                *(short *)(*(char **)((char *)profile + 4) + 0x1e0) + heading);
            duration = ((RHUnk005fc3b0 *)&point->Unk005fc190(offset)
                .Unk005fc110(*(SBGeoPoint2D *)(sprite + 0x24)))->Unk005fc6a0(1.0f);
        }
        ((RHElementActorPC *)target)->FUN_0049ffe0(action, flags, (int)duration, 0x20, 0, 0, 0x80000);
        return true;
    }
    return ((RHElementActorHuman *)this)->FUN_00483500(context, flags, target);
}

// FUNCTION: GAME 0x0048c380
void *RHElementActorNPC::FUN_0048c380(RHElementActorHuman *target)
{
    if (!((RHNPCActorCalls *)this)->V48() && !RHNPC_FIELD(char, 0x1ce) && RHNPC_FIELD(void *, 0x500))
    {
        RHUnk0045aaf0 *sequence = (RHUnk0045aaf0 *)((char *)this + 0x14);
        sequence->FUN_0045abc0(0xf8, 0, 0);
        RHNPC_FIELD(char, 0x92) = 1;
        RHNPC_FIELD(int, 0xa0) = 0;
        RHNPC_FIELD(unsigned short, 0xa4) = 2;
        return sequence;
    }
    if (((RHNPCActorCalls *)this)->V48() || RHNPC_FIELD(char, 0x1ce))
    {
        if (RHNPC_FIELD(int, 0x4f0) && ((RHScriptBatchCalls *)target)->Unk0049d560(0x17))
        {
            RHUnk0045aaf0 *sequence = (RHUnk0045aaf0 *)((char *)this + 0x14);
            sequence->FUN_0045abc0(0x70, 0, 0);
            RHNPC_FIELD(char, 0x92) = 1;
            RHNPC_FIELD(int, 0xa0) = 0;
            RHNPC_FIELD(unsigned short, 0xa4) = 2;
            return sequence;
        }
        if (RHNPC_FIELD(char, 0x1ce) && ((RHScriptBatchCalls *)target)->Unk0049d560(0x1d) &&
            *(int *)(RHNPC_FIELD(char *, 0x50) + 0x8c) == 3)
        {
            RHUnk0045aaf0 *sequence = (RHUnk0045aaf0 *)((char *)this + 0x14);
            sequence->FUN_0045abc0(0x41, 0, 0);
            RHNPC_FIELD(char, 0x92) = 1;
            RHNPC_FIELD(int, 0xa0) = 0;
            RHNPC_FIELD(unsigned short, 0xa4) = 2;
            return sequence;
        }
        if (RHNPC_FIELD(char, 0x1ce) && ((RHScriptBatchCalls *)target)->Unk0049d560(0x1b))
        {
            RHUnk0045aaf0 *sequence = (RHUnk0045aaf0 *)((char *)this + 0x14);
            sequence->FUN_0045abc0(0x66, 0, 0);
            RHNPC_FIELD(char, 0x92) = 1;
            RHNPC_FIELD(int, 0xa0) = 0;
            RHNPC_FIELD(unsigned short, 0xa4) = 2;
            return sequence;
        }
    }
    return ((RHElementActorHuman *)this)->FUN_004837f0(target);
}

inline unsigned short RHNPCActorCount()
{
    RHMalignityActorCalls **first = *(RHMalignityActorCalls ***)((char *)g_pEngine + 0x495c);
    if (!first)
        return 0;
    return (unsigned short)(*(RHMalignityActorCalls ***)((char *)g_pEngine + 0x4960) - first);
}

#include <vector>

// FUNCTION: GAME 0x0048c620
void RHElementActorNPC::FUN_0048c620(void *actor)
{
    RHEngine *engine = g_pEngine;
    typedef std::vector<RHMalignityActorCalls *> Actors;
    unsigned short count = ((Actors *)((char *)engine + 0x4d28))->size();
    for (unsigned short index = 0; index < count; ++index)
    {
        RHMalignityActorCalls *npc = (*(Actors *)((char *)engine + 0x4d28))[index];
        if (((RHMalignityOwnerCalls *)((char *)npc + 0x6e8))->FUN_00438600() >= 30)
        {
            int state = *(int *)((char *)npc + (*(int **)((char *)npc + 0x49c))[1] + 0x4b0);
            if (state >= 73 && state <= 81)
                npc->FUN_0048c700(actor, 5);
        }
    }
}

// FUNCTION: GAME 0x0048c6a0
void RHElementActorNPC::FUN_0048c6a0(void *actor, unsigned mode)
{
    unsigned short count = RHNPCActorCount();
    for (unsigned short i = 0; i < count; ++i)
        (*(RHMalignityActorCalls ***)((char *)g_pEngine + 0x495c))[i]->FUN_0048ca20(actor, mode);
}

#include "RHActorPriorityCalls.h"
#include "RHSoldierNPCCalls.h"

struct RHUnk00571160Position;

void FUN_0048cc20(void *noise, void *source);

// FUNCTION: GAME 0x0048cca0
void RHElementActorNPC::Noise(int type, RHAnimalNoisePosition &position, float radius, void *source)
{
    RHMalignityStimulus stimulus;
    RHnoise noise;
    noise.m_10 = type;
    *(RHAnimalNoisePosition *)&noise = position;
    noise.m_16 = (unsigned short)radius;
    FUN_0048cc20(&noise, source);
    RHnoise heard = noise;
    unsigned short count = RHNPCActorCount();
    for (unsigned short i = 0; i < count; ++i)
    {
        RHMalignityActorCalls *npc = (*(RHMalignityActorCalls ***)((char *)g_pEngine + 0x495c))[i];
        if ((*(unsigned *)((char *)npc + 4) & 0x1f) == 4 || npc->V130() == 1)
        {
            unsigned short volume = ((RHElementActorNPC *)npc)->FUN_0048cec0(&noise);
            if (volume > 0)
            {
                heard.m_14 = volume;
                switch (type)
                {
                case 3:
                case 13:
                    heard.m_18 = *(unsigned short *)((char *)source + 0xc);
                    break;
                case 7:
                case 8:
                    heard.m_18 = *(unsigned short *)((char *)source + 0xc);
                    break;
                }
                stimulus.m_20 = 2;
                *(RHnoise *)stimulus.m_00 = heard;
                stimulus.m_type = 1;
                ((RHArtificialIntelligence *)((char *)npc + (*(int **)((char *)npc + 0x49c))[1] + 0x49c))->V24(&stimulus);
            }
        }
    }
    g_pEngine->FUN_004d5320(&noise);
}

// FUNCTION: GAME 0x0048ce80
void RHUnk0048ce80(int noise, RHUnk00571160Position *position)
{
    RHElementActorNPC::Noise(noise, *(RHAnimalNoisePosition *)position,
        FUN_00414360(*(RHMalignityPosition *)position, true).m_8, 0);
}

// GLOBAL: GAME 0x006ae594
float g_unk0x006ae594 = 1.0f;

// FUNCTION: GAME 0x0048cec0
unsigned short RHElementActorNPC::FUN_0048cec0(const RHnoise *noise)
{
    RHUnk00613e90 position;
    RHUnk00613e90 source;
    RHUnk00613e90 delta;
    position = *(RHUnk00613e90 *)((char *)RHNPC_FIELD(void *, 0x50) + 0x10);
    float x = noise->m_x;
    source.x = x;
    float height = noise->m_16;
    source.y = noise->m_y + height;
    source.z = height;
    delta = position.FUN_005df550(source);
    delta.y *= 1.7434468f;
    float radius = noise->m_14 * g_unk0x006ae594;
    if (noise->m_10 != 14 && (position.x != source.x || position.y != source.y || position.z != source.z) &&
        delta.FUN_005df680() <= radius)
    {
        short volume = (short)(radius - delta.Norm());
        if (volume > 0)
        {
            volume -= FUN_0048a830();
            if (volume > 0)
                return volume;
        }
    }
    return 0;
}

// FUNCTION: GAME 0x0048d100
int RHSoldierNPCCalls::FUN_0048d100(RHSoldierSequenceElement *element)
{
    int kind = element->m_5c;
    if (kind == 0xb)
    {
        switch (element->m_10)
        {
        case 0x7b:
            return 3;
        case 0x48: case 0x77: case 0x78: case 0x79: case 0x7a:
        case 0x7c: case 0x7d: case 0x86: case 0x87: case 0x88:
        case 0x8f: case 0x90:
            return 8;
        case 0x83: case 0x84: case 0x85:
            return 1;
        }
        return ((RHHumanPriorityCalls *)this)->FUN_00471f20(element);
    }
    return kind;
}

#include "RHActorTranslationSequenceCalls.h"

// FUNCTION: GAME 0x0048d1b0
void RHElementActorNPC::Translate(RHSequenceElement *element, RHcommand command)
{
    int selected = !command ? *(int *)((char *)element + 0x10) : command;
    RHActorTranslationSequenceCalls *sequence = (RHActorTranslationSequenceCalls *)element;
    switch (selected)
    {
    case 0x77:
    {
        RHOrder *order = new RHOrder;
        order->m_24 = 0xce;
        order->m_2a = 0;
        sequence->FUN_00585970(order);
        return;
    }
    case 0x7a:
    {
        RHOrder *order = new RHOrder;
        order->m_24 = 0x9e;
        order->m_2a = 0;
        sequence->FUN_00585970(order);
        return;
    }
    case 0x8f:
    {
        RHOrder *order = new RHOrder;
        order->m_2a = 0;
        order->m_24 = 0x10b;
        sequence->FUN_00585970(order);
        return;
    }
    case 0x90:
    {
        RHOrder *order = new RHOrder;
        order->m_2a = 0;
        order->m_24 = 0x10c;
        sequence->FUN_00585970(order);
        return;
    }
    default:
        ((RHElementActorHuman *)this)->Translate(element, command);
    }
}

// FUNCTION: GAME 0x0048d390
void RHElementActorNPC::GetTransitionFlags(RHSequenceElement *element, unsigned long &first, unsigned long &second, unsigned long &third)
{
    switch (*(int *)((char *)element + 0x10))
    {
    case 0x77:
        first = 0x81; second = 1; break;
    case 0x7a:
        first = 1; second = 1; break;
    case 0x8f:
        first = 1; second = 1; break;
    case 0x90:
        first = 1; second = 0x20001; break;
    default:
        ((RHElementActorHuman *)this)->GetTransitionFlags(element, first, second, third);
    }
}

class RHNPCAIReactionCalls
{
public:
    virtual void V00(int value) = 0;
    virtual void V04() = 0;
    virtual void V08() = 0;
    virtual void V0c() = 0;
    virtual void V10() = 0;
    virtual void V14() = 0;
    virtual void V18(int value) = 0;
    virtual void V1c() = 0;
    virtual void V20() = 0;
    virtual void V24() = 0;
    virtual void V28() = 0;
    virtual void V2c() = 0;
    virtual void V30() = 0;
    virtual void V34() = 0;
    virtual void V38() = 0;
    virtual void V3c(int reaction) = 0;
};

// FUNCTION: GAME 0x0048d790
void RHSoldierNPCCalls::FUN_0048d790(RHSoldierSequenceElement *element)
{
    ((RHElementActorHuman *)this)->FUN_00479970((RHSequenceElement *)element);
    if (!FUN_0048da40((RHUnk0048da10 *)element) || *((char *)RHNPC_AI(char) + 0x204))
        return;
    switch (element->m_10)
    {
    case 0x13: case 0x14: case 0x16: case 0x7a:
        if (element->m_58 != 0)
        {
            if (element->m_58 == 5)
            {
                if (!*((char *)RHNPC_AI(char) + 0x175) && ((RHElementActor *)this)->FUN_0046d710())
                {
                    RHNPC_AI(RHNPCAIReactionCalls)->V3c(2);
                    *((char *)RHNPC_AI(char) + 0x175) = 1;
                }
                RHNPC_AI(RHArtificialIntelligence)->DispatchWorldEvent(4);
            }
        }
        else
            RHNPC_AI(RHArtificialIntelligence)->DispatchWorldEvent(3);
        break;
    case 0x19: case 0x1a: case 0x1b: case 0x1c: case 0x1d: case 0x1e: case 0x1f: case 0x22:
    case 0x23: case 0x27: case 0x2a: case 0x2e: case 0x2f: case 0x30: case 0x32: case 0x36:
    case 0x3b: case 0x3c: case 0x3d: case 0x3e: case 0x3f: case 0x40: case 0x41: case 0x42:
    case 0x43: case 0x44: case 0x45: case 0x47: case 0x48: case 0x4b: case 0x54: case 0x55:
    case 0x56: case 0x6b: case 0x77: case 0x78: case 0x7b: case 0x7c: case 0x87: case 0x88:
    case 0x8a: case 0x8d:
        if (element->m_58 == 0 || element->m_58 == 6)
            RHNPC_AI(RHArtificialIntelligence)->DispatchWorldEvent(5);
        else
            RHNPC_AI(RHArtificialIntelligence)->DispatchWorldEvent(6);
        break;
    case 0x37: case 0x38: case 0x39: case 0x3a:
        if (element->m_58 == 0 || element->m_58 == 6)
            RHNPC_AI(RHArtificialIntelligence)->DispatchWorldEvent(5);
        break;
    case 0xa1:
        if (element->m_58 == 0)
            RHNPC_AI(RHArtificialIntelligence)->DispatchWorldEvent(5);
        break;
    case 0x89:
        if (element->m_58 == 0 || (element->m_58 > 4 && element->m_58 <= 6))
            RHNPC_AI(RHArtificialIntelligence)->DispatchWorldEvent(0x1b);
        break;
    }
}

// FUNCTION: GAME 0x0048d990
void RHElementActorNPC::FUN_0048d990(unsigned short amount, void *source, bool force)
{
    char previous = RHNPC_FIELD(char, 0x1ce);
    ((RHElementActorHuman *)this)->FUN_00471c00(amount, source, force);
    if (previous)
    {
        if (!RHNPC_FIELD(char, 0x1ce) && *(int *)((char *)RHNPC_AI(char) + 0x14) == 2)
            RHNPC_AI(RHArtificialIntelligence)->DispatchWorldEvent(13);
    }
    else if (RHNPC_FIELD(char, 0x1ce))
    {
        ((RHMalignityActorCalls *)this)->FUN_0048e580();
        RHNPC_AI(RHArtificialIntelligence)->DispatchWorldEvent(15);
        RHNPC_FIELD(bool, 0x4ee) = source && (*(unsigned *)((char *)source + 4) & 15) == 12;
    }
}

#include "RHUnk0046bd20.h"
#include "RHArtificialBonhomie.h"
#include "RHArtificialIntelligenceCore.h"
#include "RHPathCore.h"

RHArtificialIntelligence &RHElementActorNPC::Intelligence()
{
    return *Intelligence(m_aiBaseOffsets[1]);
}

RHPath &RHElementActorNPC::ActorPath()
{
    return *reinterpret_cast<RHPath *>(reinterpret_cast<char *>(&m_aiBaseOffsets) + m_aiBaseOffsets[1] + 0x4cc - OffsetAI);
}

// STUB: GAME 0x0048a980
void RHSoldierNPCCalls::FUN_0048a980()
{
    if (!((RHElementActorHuman *)this)->FUN_00471b00())
        return;
    if (RHNPC_FIELD(bool, 0x4ee) && !*((char *)g_pEngine + 0x4d84))
    {
        RHNPC_FIELD(bool, 0x4ee) = false;
        ((RHElementActorNPC *)this)->FUN_0048c4d0();
    }
    if (!*((char *)g_pEngine + 0x4d84))
    {
        RHNPC_AI(RHNPCAIReactionCalls)->V1c();
        ((RHElementActorNPC *)this)->FUN_0048a830();
    }
    if (!*((char *)RHNPC_AI(char) + 0x175))
    {
        if (((RHElementActor *)this)->FUN_0046d710())
        {
            RHNPC_AI(RHNPCAIReactionCalls)->V3c(2);
            goto awake;
        }
    }
    if (*((char *)RHNPC_AI(char) + 0x175) && !((RHElementActor *)this)->FUN_0046d710())
        *((char *)RHNPC_AI(char) + 0x174) &= ~2;
awake:
    *((char *)RHNPC_AI(char) + 0x175) = ((RHElementActor *)this)->FUN_0046d710();
    if (*(int *)(RHNPC_FIELD(char *, 0x50) + 0x8c) == 4)
    {
        if (((RHUnk0046bd20 *)this)->FUN_0046bd20() == 0xa1 ||
            ((RHUnk0046bd20 *)this)->FUN_0046bd20() == 0x17)
        {
            if (!*((char *)RHNPC_AI(char) + 0x1c4) &&
                (*(unsigned int *)(*(char **)(RHNPC_FIELD(char *, 0x50) + 0xe0) + 0x30) & 0x2000) == 0)
            {
                if (++RHNPC_FIELD(unsigned short, 0x4f8) > 0x19)
                    RHNPC_AI(RHNPCAIReactionCalls)->V00(0);
            }
        }
    }
    RHNPC_FIELD(unsigned short, 0x4f8) = 0;
    unsigned char delta = (unsigned char)*g_unk0x006c08a4 - RHNPC_FIELD(unsigned char, 0x4ec) - 100;
    if ((RHNPC_FIELD(unsigned int, 0x4) & 0x1f) == 4)
        ((RHArtificialBonhomie *)((char *)this + 0x6e8))->FUN_0040dbe0((bool)delta);
    RHArtificialIntelligence *intelligence = RHNPC_AI(RHArtificialIntelligence);
    if (!(intelligence->m_174 > 0) && !intelligence->m_1c4 &&
        !*((char *)g_pEngine + 0x4d84))
    {
        if (!((RHNPCActorCalls *)this)->V48() && (delta & 0xf) == 0)
            RHNPC_AI(RHNPCAIReactionCalls)->V18(delta);
        if (intelligence->m_98)
        {
            if (intelligence->m_a4 <= *g_unk0x006c08a4)
            {
                intelligence->m_98 = false;
                if (intelligence->m_14 == 0xf)
                    intelligence->Unk00410010(false);
            }
        }
        if (intelligence->m_268)
        {
            if (intelligence->m_264 <= *g_unk0x006c08a4)
                RHNPC_AI(RHArtificialIntelligence)->SetReactionState(0);
        }
        while (!intelligence->m_178.empty())
        {
            if (intelligence->m_174 > 0 || intelligence->m_1c4)
                break;
            RHStimulus stimulus = intelligence->m_178.front();
            intelligence->m_178.pop_front();
            intelligence->m_178.dirty = true;
            intelligence->V24((RHMalignityStimulus *)&stimulus);
        }
    }
    else
    {
        ++intelligence->m_9c;
        ++intelligence->m_a4;
        ++intelligence->m_264;
    }
}

#include "RHHumanSequenceElement.h"
#include "RHActorTranslationSequenceCalls.h"

// FUNCTION: GAME 0x0048d510
int RHElementActorNPC::FUN_0048d510(RHOrder *order)
{
    if (RHNPC_FIELD(char, 0x149))
        return 2;
    RHUnk00613e90 point;
    if (order)
    {
        int command = *(int *)((char *)order + 0x24);
        int result;
        switch (command)
        {
        case 0x9f:
            switch (((RHSprite *)RHNPC_FIELD(void *, 0x50))->PerformAction(order, command, 0, false))
            {
            case 1:
                ((RHScriptBatchCalls *)this)->Unk0046bcf0(8, 0);
            }
            return 2;
        case 0x9e:
            result = ((RHSprite *)RHNPC_FIELD(void *, 0x50))->PerformAction(order, command, 0, false);
            if (result == 3)
                ((RHScriptBatchCalls *)this)->Unk0046bcf0(8, 0);
            return result;
        case 0x10b:
        {
            unsigned short *animations = *(unsigned short **)((char *)((RHUnk005b5e00 *)RHNPC_FIELD(void *, 0x50))->Unk() + 4);
            if (animations[command] != 0xffff)
                result = ((RHSprite *)RHNPC_FIELD(void *, 0x50))->PerformAction(order, command, 0, false);
            else
                result = ((RHSprite *)RHNPC_FIELD(void *, 0x50))->PerformAction(order, 0x7f, 0, false);
            if (result == 3)
                ((RHScriptBatchCalls *)this)->Unk0046bcf0(1, 0);
            return result;
        }
        case 0xce:
            if (RHNPC_FIELD(char, 0x148))
                *(short *)((char *)RHNPC_FIELD(void *, 0x50) + 0xda) = (short)(((RHSequenceElement *)RHNPC_FIELD(void *, 0x130))->Unk00587160(0) & 15);
            ((RHSprite *)RHNPC_FIELD(void *, 0x50))->Turn();
        case 0xa0:
            result = ((RHSprite *)RHNPC_FIELD(void *, 0x50))->PerformAction(order, command, 0, false);
            if (result == 3)
                ((RHScriptBatchCalls *)this)->Unk0046bcf0(1, 0);
            return result;
        case 0x7a:
            ((RHSprite *)RHNPC_FIELD(void *, 0x50))->Turn();
            result = ((RHSprite *)RHNPC_FIELD(void *, 0x50))->PerformAction(order, command, 0, false);
            if (result == 0)
            {
                ((RHScriptBatchCalls *)this)->Unk0046bcf0(1, 0);
                void *target = *(void **)((char *)order + 0x30);
                if (target && (*(volatile unsigned *)((char *)target + 4) & 15) == 4 && *(int *)((char *)target + 0x4f0))
                {
                    RHNPC_FIELD(int, 0x4f0) += *(int *)((char *)target + 0x4f0);
                    *(int *)((char *)target + 0x4f0) = 0;
                }
            }
            return result;
        }
        return ((RHElementActorHuman *)this)->FUN_00475bd0(order);
    }
    return 3;
}


class RHUnk00418b80
{
public:
    void Unk(bool value);
};

// FUNCTION: GAME 0x0048da80
void RHElementActorNPC::FUN_0048da80(RHSequenceElement *element)
{
    switch (element->m_10)
    {
    case 0x7f:
        RHNPC_AI(RHUnk00418b80)->Unk(false);
        ((RHActorTranslationSequenceCalls *)element)->V0c(0, true);
        return;
    case 0x80:
        RHNPC_AI(RHScriptBatchCalls)->Unk00418bc0();
        ((RHActorTranslationSequenceCalls *)element)->V0c(0, true);
        return;
    case 0x81:
        if (RHNPC_FIELD(char, 8))
            ((RHNPCActorCalls *)this)->V34();
        ((RHActorTranslationSequenceCalls *)element)->V0c(0, true);
        return;
    case 0x92:
        ((RHNPCActorCalls *)this)->V100(element->Unk00587160(15), element->Unk00587160(16));
        ((RHActorTranslationSequenceCalls *)element)->V0c(0, true);
        return;
    default:
        ((RHElementActorHuman *)this)->FUN_0047a880(element);
    }
}

// FUNCTION: GAME 0x0048e580
void RHMalignityActorCalls::FUN_0048e580()
{
    struct Position
    {
        float x;
        float y;
        void *area;
        unsigned short layer;
    };
    Position &position = RHNPC_FIELD(Position, 0x63c);
    position.x = 0.0f;
    position.y = 0.0f;
    position.area = 0;
    position.layer = 0;
    RHNPC_FIELD(unsigned, 0x64c) = 7;
}

// FUNCTION: GAME 0x0048e5b0
void RHMalignityActorCalls::FUN_0048e5b0(unsigned operation, unsigned short value, unsigned)
{
    switch (operation)
    {
    case 1:
        unsigned short current = RHNPC_FIELD(unsigned short, 0x4ca);
        RHNPC_FIELD(unsigned short, 0x4ca) = value >= current ? 0 : current - value;
    }
}

// FUNCTION: GAME 0x0048e5f0
unsigned short RHMalignityActorCalls::FUN_0048e5f0(unsigned operation)
{
    switch (operation)
    {
    default:
        return 0xffff;
    case 1:
        return RHNPC_FIELD(unsigned short, 0x4ca);
    }
}

#include "RHActorTranslationSequenceCalls.h"

// FUNCTION: GAME 0x0048d460
bool RHElementActorNPC::FUN_0048d460(unsigned flags, RHActorTranslationSequenceCalls *sequence)
{
    if (*(int *)((char *)RHNPC_FIELD(void *, 0x50) + 0x8c) != 8)
        return ((RHElementActorHuman *)this)->FUN_00475750(flags, sequence);
    if (flags & 1)
    {
        RHOrder *order = new RHOrder;
        order->m_24 = 0xa0;
        order->m_2a = 0;
        sequence->FUN_00585970(order);
        *(int *)((char *)sequence + 0x3c) = 1;
    }
    return true;
}

#include "RHElementActorCivilianCore.h"
#include "RHSoundActorCalls.h"
#include "RHMalignityPosition.h"

extern RHArtificialIntelligenceSoundCalls *g_unk0x006c1070;

inline float RHNPCNoiseHeight(void *sprite)
{
    return *(float *)((char *)sprite + 0x18);
}

// FUNCTION: GAME 0x0048ec70
void RHElementActorNPC::FUN_0048ec70()
{
    int state = *(int *)((char *)RHNPC_AI(char) + 0x14);
    if (state >= 41 && state <= 52)
        return;
    if (RHNPC_FIELD(char, 0x1ce))
    {
        if (*(int *)((char *)RHNPC_AI(char) + 0x258) != 121)
        {
            g_unk0x006c1070->Unk005a8d10((RHArtificialIntelligenceActor *)this);
            *(int *)((char *)RHNPC_AI(char) + 0x258) = 121;
        }
        return;
    }
    RHUnk00571160Position position;
    m_50->GetPosition(position);
    if ((RHNPC_FIELD(unsigned, 4) & 31) == 4)
    {
        if (((RHElementActorCivilian *)this)->FUN_00470ce0())
            RHNPC_AI(RHArtificialIntelligence)->Unk00418c40(((RHNPCActorCalls *)this)->V48() ? 110 : 109, 2);
        else
            RHNPC_AI(RHArtificialIntelligence)->Unk00418c40(((RHNPCActorCalls *)this)->V48() ? 85 : 84, 2);
    }
    else
    {
        if (((RHNPCActorCalls *)this)->Vf8())
            RHNPC_AI(RHArtificialIntelligence)->Unk00418c40(((RHNPCActorCalls *)this)->V48() ? 110 : 109, 2);
        else
            RHNPC_AI(RHArtificialIntelligence)->Unk00418c40(((RHNPCActorCalls *)this)->V48() ? 30 : 29, 2);
    }
    Noise(7, (RHAnimalNoisePosition &)position, RHNPCNoiseHeight(RHNPC_FIELD(void *, 0x50)), this);
}

// FUNCTION: GAME 0x0048ed90
void RHElementActorNPC::FUN_0048ed90(unsigned short state)
{
    unsigned short current;
    RHNPCActorCalls *actor = *(RHNPCActorCalls **)((char *)RHNPC_AI(char) + 4);
    if ((*(unsigned *)((char *)actor + 4) & 31) == 20)
    {
        if (actor->Vf8())
            current = *(unsigned short *)((char *)RHNPC_AI(char) + 0x258) - 106;
        else
            current = *(unsigned short *)((char *)RHNPC_AI(char) + 0x258);
    }
    else if (((RHElementActorCivilian *)actor)->FUN_00470ce0())
        current = *(unsigned short *)((char *)RHNPC_AI(char) + 0x258) - 106;
    else
        current = *(unsigned short *)((char *)RHNPC_AI(char) + 0x258) - 78;
    if (current == state)
    {
        unsigned short flags = *(unsigned short *)((char *)RHNPC_AI(char) + 0x25c);
        *(int *)((char *)RHNPC_AI(char) + 0x258) = 121;
        *(unsigned short *)((char *)RHNPC_AI(char) + 0x25c) = 0;
        RHNPC_AI(RHArtificialIntelligence)->Unk00422b70(6, 0);
        RHNPC_AI(RHArtificialIntelligence)->Unk004195f0(flags);
    }
}

// FUNCTION: GAME 0x0048ee90
void *RHMalignityActorCalls::FUN_0048ee90(unsigned short index)
{
    return ((RHNPCCachedList *)((char *)this + 0x504))->Get(index).m_00;
}

// FUNCTION: GAME 0x0048efa0
int RHElementActorNPC::FUN_0048efa0()
{
    if (((RHNPCActorCalls *)this)->V130() == 0 &&
        *(char *)((char *)g_pEngine + 0x4aa8) &&
        !((RHNPCActorCalls *)this)->Vf4())
        return 1;
    return 0;
}

inline void RHNPCDetectableList::ClearNodes()
{
    typedef std::list<unsigned long> Native;
    ((Native *)this)->clear();
}

// FUNCTION: GAME 0x0048efe0
RHNPCDetectableList::RHNPCDetectableList() : m_dirty(true)
{
}

// FUNCTION: GAME 0x0048f020
RHNPCDetectableList::~RHNPCDetectableList()
{
    ClearNodes();
}

// TEMPLATE: GAME 0x004e52a0 FOLDED
// ??1?$list@VRHDetectable@@V?$allocator@VRHDetectable@@@std@@@std@@QAE@XZ

// TEMPLATE: GAME 0x0048be30 FOLDED
// ??1RHDetectable@@QAE@XZ

// TEMPLATE: GAME 0x0040eab0 FOLDED
// ??_GRHDetectable@@QAEPAXI@Z

void RHElementActorNPC::Emit(SBFile &file)
{
    Translate(0, (RHcommand)0);
    FUN_00487ad0(*(RHMalignityPosition *)this);
    FUN_0048d460(0, 0);
    FUN_0048c380(0);
    FUN_00487ce0();
    FUN_0048c620(this);
    FUN_0048c6a0(this, 0);
    Serialize(file);
    RHDetectable value;
    value.Serialize(file);
    FUN_0048efa0();
    RHNPCDetectableList detectables;
}

#include "RHArtificialMalignityCore.h"


// Parked at 0.6974: actor/receiver registers and tag comparison width differ.
// STUB: GAME 0x0048c4d0
void RHElementActorNPC::FUN_0048c4d0()
{
    *(unsigned short *)((char *)this + 0x4f6) = 0;
    unsigned short count = RHNPCActorCount();
    for (unsigned short index = 0; index < count; ++index)
    {
        RHMalignityActorCalls *actor = (*(RHMalignityActorCalls ***)((char *)g_pEngine + 0x495c))[index];
        if (actor != (RHMalignityActorCalls *)this)
        {
            char *ai = (char *)this + 0x49c;
            if (!*(char *)(ai + (*(int **)ai)[1] + 0x2ac) ||
                (*(RHUnk00613e90 *)(*(char **)((char *)this + 0x50) + 0x10)).FUN_005df550(
                    *(RHUnk00613e90 *)(*(char **)((char *)actor + 0x50) + 0x10)).FUN_005df680() > 700.0f)
            {
                if (!actor->FUN_0048c8e0(this, 1))
                    actor->FUN_0048c700(this, 1);
            }
            unsigned type = *(unsigned *)((char *)this + 4) & 0x1f;
            if (type == 0x14 && (*(unsigned *)((char *)actor + 4) & 0x1f) == type)
                ((RHArtificialMalignity *)((char *)actor + 0x6e8))->FUN_00446eb0(this);
        }
    }
}

extern float g_unk0x006774cc;
extern float g_actorStepScale;

// FUNCTION: GAME 0x00489b30
float RHElementActorNPC::ComputeVisibility(RHElementObject *object)
{
    SBGeoVector2D planar;
    RHUnk00613e90 offset;
    RHUnk00613e90 origin;
    RHUnk00613e90 target;
    if (!m_654.m_viewStatus || m_654.m_viewStatus == 5)
        return 0.0f;
    const RHSector *sector = static_cast<RHSector *>(m_50->m_dc);
    if (!((unsigned char)((unsigned)sector->m_30 >> 13) & 1) && !object->m_fc)
    {
        FUN_00478c20(origin, 0);
        target = object->m_50->m_c;
        target.z += 1.0f;
        offset = target.FUN_005df550(origin).ScaleY(1.7434468269348145f);
        planar.Set(offset.x, offset.y);
        float distance = offset.x * offset.x + offset.y * offset.y + offset.z * offset.z;
        int range = m_654.m_78;
        if (!(distance > range * range) &&
            !(planar.FUN_005fc660(m_654.m_48) < 0.0f) && IsDetecting(target, false))
            return FUN_00489d00(offset);
    }
    return 0.0f;
}

// FUNCTION: GAME 0x00489d00
float RHElementActorNPC::FUN_00489d00(const RHUnk00613e90 &offset)
{
    RHUnk005fc3b0 direction;
    RHUnk005fc3b0 planar;
    direction.FUN_005fc430(RHNPC_FIELD(SBGeoPoint2D, 0x69c));
    float y = offset.y;
    planar.m_x = offset.x;
    planar.m_y = y;
    if (planar.Unk005fc6d0(1.0f) <= 3600.0f)
        return 1.0f;
    float distance = (float)sqrt(offset.z * offset.z + offset.x * offset.x + offset.y * offset.y) /
        RHNPC_FIELD(unsigned short, 0x6cc);
    float visibility;
    if (distance < 0.3f)
        visibility = 1.0f - distance * 0.166666701436043f;
    else if (distance < 0.7f)
        visibility = 0.95f - (distance - 0.3f) * 1.7500001192092896f;
    else
        visibility = g_actorStepScale - (distance - 0.7f) * 0.3333333134651184f;
    if (visibility < 0.0f)
        visibility = 0.0f;
    return visibility;
}

// FUNCTION: GAME 0x00489eb0
bool RHElementActorNPC::IsDetecting(RHUnk00613e90 &point, bool checkRange)
{
    RHUnk005fc3b0 planar;
    RHUnk00613e90 offset;
    RHUnk00613e90 origin;
    if (!m_654.m_viewStatus || m_654.m_viewStatus == 5)
        return false;
    const RHSector *sector = static_cast<RHSector *>(m_50->m_dc);
    if ((unsigned char)((unsigned)sector->m_30 >> 13) & 1)
        return false;
    FUN_00478c20(origin, 0);
    offset = point.FUN_005df550(origin);
    planar.Set(offset.x, offset.y);
    offset.y *= 1.7434468269348145f;
    float zz = offset.z * offset.z;
    if (offset.x * offset.x + (offset.y * offset.y + zz) > 3600.0f)
    {
        if (checkRange)
        {
            offset.y *= 1.7434468269348145f;
            int range = m_654.m_78;
            if (offset.x * offset.x + (offset.y * offset.y + zz) > range * range ||
                planar.FUN_005fc660(m_654.m_48) < 0.0f)
                return false;
        }
        if (m_654.m_50.FUN_005fc680(planar, 1.0f) < 0.0f || m_654.m_58.FUN_005fc680(planar, 1.0f) > 0.0f)
            return false;
        return static_cast<RHFastFindGrid *>(m_64)->FUN_004eff80(origin, point, 2);
    }
    else
    {
        short heading = m_50->m_d4;
        unsigned short relative = (planar.FUN_005fcc50(0.57357645f) - heading + 16) % 16;
        switch (relative)
        {
        case 0: case 1: case 2: case 3: case 4: case 12: case 13: case 14: case 15:
            return static_cast<RHFastFindGrid *>(m_64)->FUN_004eff80(origin, point, 2);
        }
    }
    return false;
}

// STUB: GAME 0x0048a650
void RHElementActorNPC::FUN_0048a650(unsigned char &red, unsigned char &green, unsigned char &blue)
{
    RHUnk00613e90 position;
    if (RHNPC_FIELD(unsigned char, 0x65c) == 5)
    {
        float ratio = (float)RHNPC_FIELD(unsigned short, 0x6c2) / *(unsigned short *)((char *)g_pEngine + 0x4cc0);
        ratio = ratio * ratio;
        red = g_unk0x006c0880 * ratio;
        green = g_unk0x006c087c * ratio;
        blue = g_unk0x006c08a9 * ratio;
        return;
    }
    switch (RHNPC_FIELD(int, 0x658))
    {
    case 2:
        red = g_unk0x006c0880;
        green = g_unk0x006c087c;
        blue = g_unk0x006c08a9;
        return;
    case 1:
        red = g_unk0x006c0881;
        green = g_unk0x006c087d;
        blue = g_unk0x006c08a8;
        return;
    case 0:
    {
        unsigned short noise = RHNPC_FIELD(unsigned short, 0x648);
        unsigned short alert = *(unsigned short *)((char *)this + 0x546 + (*(int **)((char *)this + 0x49c))[1]);
        unsigned short level = 1000 < (noise > alert ? noise : alert) ? 1000 : (noise > alert ? noise : alert);
        unsigned short index = level * g_unk0x006774cc * 32.0f;
        if (index >= 32)
            index = 31;
        unsigned short minimum = alert * g_unk0x006774cc * 32.0f;
        if (minimum > index)
            index = minimum;
        red = g_unk0x006c08ac[index];
        green = g_unk0x006c08cc[index];
        blue = g_unk0x006c0884[index];
        break;
    }
    }
}

#include "RHSoundSourceManagerCore.h"
#include "RHSoundSourceCore.h"

// FUNCTION: GAME 0x0048a830
unsigned short RHElementActorNPC::FUN_0048a830()
{
    RHUnk00613e90 position;
    if (*g_unk0x006c08a4 == RHNPC_FIELD(unsigned, 0x4fc))
        return RHNPC_FIELD(unsigned short, 0x4fa);
    for (; RHNPC_FIELD(unsigned, 0x4fc) < *g_unk0x006c08a4; )
    {
        if (RHNPC_FIELD(unsigned short, 0x4fa) <= 0)
            break;
        RHNPC_FIELD(unsigned short, 0x4fa) -= RHNPC_FIELD(unsigned short, 0x4fa) > 300
            ? RHNPC_FIELD(unsigned short, 0x4fa) / 300 * 50 : 10;
        if ((short)RHNPC_FIELD(unsigned short, 0x4fa) < 0)
            RHNPC_FIELD(unsigned short, 0x4fa) = 0;
        unsigned next = RHNPC_FIELD(unsigned, 0x4fc) + 1;
        RHNPC_FIELD(unsigned, 0x4fc) = next;
    }
    position = *(RHUnk00613e90 *)((char *)RHNPC_FIELD(void *, 0x50) + 0x10);
    unsigned short maximum = RHNPC_FIELD(unsigned short, 0x4fa);
    RHArtificialIntelligenceSoundCalls *sound = g_unk0x006c1070;
    unsigned short count = (unsigned short)(*(RHSoundSourceManager **)((char *)sound + 0x200))->m_sources.GetSize();
    for (unsigned short index = 0; index < count; ++index)
    {
        RHSoundSource *source = (*(RHSoundSourceManager **)((char *)sound + 0x200))->GetSoundSource(index);
        if (source)
        {
            unsigned short value = source->FUN_005b3c40(position);
            if (value > maximum)
                maximum = value;
        }
    }
    RHNPC_FIELD(unsigned short, 0x4fa) = maximum;
    RHNPC_FIELD(unsigned, 0x4fc) = *g_unk0x006c08a4;
    return maximum;
}

void EmitRHElementActorNPCVoice(RHElementActorNPC *npc)
{
    npc->FUN_00489d00(*(RHUnk00613e90 *)npc);
    npc->FUN_0048a830();
    unsigned char channel;
    npc->FUN_0048a650(channel, channel, channel);
}
