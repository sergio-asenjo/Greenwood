#include "RHElementActor.h"
#include "VMCore.h"

// TEMPLATE: GAME 0x00402a70
// ?erase@?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@QAEAAV12@II@Z

class RHSeqList
{
public:
    RHSeqList(const char &allocator);
    void GoTo(int index);
    char m_00[4];
    RHScriptNode *m_head;
    int m_count;
    RHScriptNode *m_current;
    bool m_valid;
    char m_11[3];
    int m_index;
};

struct RHUnk004b1520List
{
    char m_00[4];
    RHScriptNode *m_04;
    int m_08;
    RHScriptIter m_0c;
    bool m_10;
    int m_14;
    RHScriptIter end() { return RHScriptIter(m_04); }
    RHScriptIter FUN_00424410(RHScriptIter position, void *const &value);
};

struct RHSectorActorNode;
class RHSectorActorConstIter
{
public:
    RHSectorActorNode *m_p;
    RHSectorActorConstIter(RHSectorActorNode *value) : m_p(value) {}
};

class RHSectorActorIter : public RHSectorActorConstIter
{
public:
    RHSectorActorIter(RHSectorActorNode *value) : RHSectorActorConstIter(value) {}
    RHSectorActorIter operator++(int);
};

class RHActorValueList
{
public:
    int allocator;
    RHScriptNode *head;
    int count;
    RHScriptIter cursor;
    bool dirty;
    int index;
    bool searched;
    int found;
    int value;
    int Find(int wanted, bool inlineIterator)
    {
        int size = count;
        value = wanted;
        searched = true;
        if (inlineIterator)
            cursor.node = head->next;
        else
            cursor = ((RHUnk0046eb30 *)this)->FUN_0046eb80();
        int i = 0;
        for (; i < size; ++i)
        {
            RHScriptNode *node = *(RHScriptNode *volatile *)&cursor.node;
            int searchedValue = *(volatile int *)&value;
            if (*(int *)&node->data == searchedValue)
                break;
            if (inlineIterator)
                cursor.node = cursor.node->next;
            else
                (*(RHSectorActorIter *)&cursor)++;
        }
        if (i < size)
        {
            found = i;
            dirty = false;
            index = i;
        }
        else
        {
            dirty = true;
            found = -1;
        }
        return *(volatile int *)&found;
    }
    void Erase(RHScriptIter position)
    {
        RHScriptNode *node = position.node;
        node->previous->next = node->next;
        node->next->previous = node->previous;
        operator delete(node);
        --count;
        dirty = true;
    }
};

DECOMP_SIZE_ASSERT(RHHumanMapNode, 0x14)
DECOMP_SIZE_ASSERT(RHHumanMapIterator, 0x04)
DECOMP_SIZE_ASSERT(RHHumanMap, 0x10)
DECOMP_SIZE_ASSERT(RHActorSequencePointCalls, 0x74)
DECOMP_SIZE_ASSERT(RHMobileUnk00607da0, 0x14)
DECOMP_SIZE_ASSERT(RHUnk0053bf20, 0x0c)
DECOMP_SIZE_ASSERT(RHUnk00560410, 0x92)
DECOMP_SIZE_ASSERT(RHUnk0060fbf0, 0x0c)
DECOMP_SIZE_ASSERT(RHUnk004e52a0, 0x0c)
DECOMP_SIZE_ASSERT(RHUnk004679c0, 0x58c)
DECOMP_SIZE_ASSERT(RHElementActor, 0x1b8)
DECOMP_SIZE_ASSERT(RHOrder, 0x3c)
DECOMP_SIZE_ASSERT(SBGeoPoint2D, 0x08)
DECOMP_SIZE_ASSERT(SBGeoVector2D, 0x08)
DECOMP_SIZE_ASSERT(SBGeoBoundingBox2D, 0x14)

// FUNCTION: GAME 0x004030a0
int RHActorScriptContext::FUN_004030a0()
{
    // STRING: GAME 0x006a6ba0
    ((VMCore *)m_0)->FUN_00639300(&std::string("Initialize"));
    int value;
    ((VMCore *)m_0)->FUN_00639360(value);
    return value;
}

// FUNCTION: GAME 0x004033b0
void RHActorScriptContext::FUN_004033b0(int message, int argument1, int argument2)
{
    ((VMCore *)m_0)->FUN_006392e0(&message, 4);
    ((VMCore *)m_0)->FUN_006392e0(&argument1, 4);
    ((VMCore *)m_0)->FUN_006392e0(&argument2, 4);
    // STRING: GAME 0x006a6bcc
    ((VMCore *)m_0)->FUN_00639300(&std::string("ProcessMessage"));
}

// FUNCTION: GAME 0x004626e0
unsigned short RHElementActor::FUN_004626e0() const
{
    void *area = RHActorField<void *>(Info(), 0xe0);
    if (!area)
        return 0xffff;
    return RHActorField<unsigned short>(area, 0x38);
}

// FUNCTION: GAME 0x00462700
void RHElementActor::FUN_00462700(unsigned short value)
{
    void **areas = RHActorField<void **>(Grid(), 0x4064);
    RHActorField<void *>(Info(), 0xe0) = areas[value];
}

// Parked: actor/receiver registers, point-temporary lifetime and copy scheduling differ.
// STUB: GAME 0x00462730
void RHElementActor::FUN_00462730(RHElementActor *actor, bool value)
{
    Position()->FUN_0055fa20(RHActorField<RHBonusProjection *>(actor->Info(), 0xec));
    RHActorField<unsigned short>(Position(), 0xda) = RHActorField<unsigned short>(actor->Info(), 0xde);
    RHActorField<void *>(Position(), 0xdc) = RHActorField<void *>(actor->Info(), 0xe0);
    unsigned short direction = RHActorField<unsigned short>(actor->Info(), 0xd8) & 15;
    RHActorField<unsigned short>(Position(), 0xd4) = direction;
    RHActorField<unsigned short>(Position(), 0xd6) = direction;
    if (value)
    {
        const SBGeoPoint2D &point = actor->FUN_00462920();
        RHBonusInfoBase *position = Position();
        RHActorField<SBGeoPoint2D>(position, 0x20) = point;
        {
            SBGeoVector2D displacement(point);
            SBGeoBoundingBox2D *bounds = (SBGeoBoundingBox2D *)
                ((RHUnkPathActorInfoBase *)position)->Unk0055fa10(RHActorField<int>(position, 0x88));
            ((RHMobileUnk00607da0 *)((char *)position + 0xc0))->FUN_00607da0(
                *(RHMobileUnk00607da0 *)&bounds->FUN_006090d0(displacement));
        }
        RHActorField<int>(position, 4) = 2;
    }
    else
    {
        RHBonusInfoBase *position = Position();
        SBGeoPoint2D &point = RHActorField<SBGeoPoint2D>(actor->Info(), 0x24);
        RHActorField<SBGeoPoint2D>(position, 0x20) = point;
        {
            SBGeoVector2D displacement(point);
            SBGeoBoundingBox2D *bounds = (SBGeoBoundingBox2D *)
                ((RHUnkPathActorInfoBase *)position)->Unk0055fa10(RHActorField<int>(position, 0x88));
            ((RHMobileUnk00607da0 *)((char *)position + 0xc0))->FUN_00607da0(
                *(RHMobileUnk00607da0 *)&bounds->FUN_006090d0(displacement));
        }
        RHActorField<int>(position, 4) = 2;
    }
    Position()->FUN_0055f290();
}

#define RH_ACTOR_ACCESS(value, size, line) \
    if (file.Access(&(value), size) < 0) \
    { \
        SBString *error = file.GetError(); \
        const char *reason = error->m_chars ? error->m_chars : ""; \
        SBAssert(0, "P:\\Robin Hood\\RHelementactor.cpp", line, "Serialize failed reason is %s", reason); \
        return false; \
    }

// Cached-list scheduling, cleanup, and named-call operands remain unmatched.
// STUB: GAME 0x00463430
bool RHElementActor::Serialize(SBFile &file)
{
    SBGeoPoint2D point;
    // STRING: GAME 0x006ae220
    RHSerializeName(file, "RHElementActor");
    RH_ACTOR_ACCESS(m_114, 4, 132);
    RH_ACTOR_ACCESS(m_10c, 4, 135);
    RH_ACTOR_ACCESS(m_144, 4, 136);
    RH_ACTOR_ACCESS(m_149, 1, 137);
    RH_ACTOR_ACCESS(m_118, 1, 138);
    RH_ACTOR_ACCESS(m_110, 1, 139);
    RH_ACTOR_ACCESS(m_119, 1, 140);
    RH_ACTOR_ACCESS(m_124, 4, 141);
    RH_ACTOR_ACCESS(m_148, 1, 143);
    RH_ACTOR_ACCESS(m_124, 4, 144);
    RH_ACTOR_ACCESS(m_140, 4, 145);
    RH_ACTOR_ACCESS(m_14c, 4, 146);
    RH_ACTOR_ACCESS(m_16c, 2, 147);
    RH_ACTOR_ACCESS(m_16e, 1, 149);
    RH_ACTOR_ACCESS(m_16f, 1, 150);
    RH_ACTOR_ACCESS(m_160, 4, 152);
    RH_ACTOR_ACCESS(m_165, 1, 153);
    RH_ACTOR_ACCESS(m_164, 1, 154);
    RH_ACTOR_ACCESS(m_1a4, 1, 156);
    m_174.Serialize(file);
    m_154.Serialize(file);
    m_128.Serialize(file);
    RHEngine *engine = g_pEngine;
    ((RHReconnaissanceEngine *)engine)->Unk004c3cb0(file, m_11c);
    engine->SerializeElementPointer(file, *(RHElement **)(&m_150));
    engine->SerializeElementPointer(file, *(RHElement **)(&m_170));
    ((RHUnkPathGeometry *)g_unk0x6c0a9c)->Unk004fbec0(file, m_120);
    ((RHUnkPathGeometry *)g_unk0x6c0a9c)->Unk004fbec0(file, m_168);
    (*(RHSequenceManager **)((char *)this + 0x5c))->PreSerializePointer(file, &m_130, true);
    (*(RHSequenceManager **)((char *)this + 0x5c))->PreSerializePointer(file, &m_138, true);
    (*(RHSequenceManager **)((char *)this + 0x5c))->PreSerializePointer(file, &m_134);
    if (file.m_version >= 36)
    {
        RH_ACTOR_ACCESS(m_13c, 1, 180);
    }
    else
        m_13c = 0;
    bool present;
    int count;
    if (!file.m_bLoading)
    {
        present = m_15c != 0;
        RH_ACTOR_ACCESS(present, 1, 192);
        if (present)
            m_15c->Serialize(file, false);
        count = m_17c.count;
        RH_ACTOR_ACCESS(count, 2, 199);
        for (unsigned short i = 0; i < (unsigned short)count; ++i)
        {
            point = m_17c.Get(i);
            point.Serialize(file);
        }
    }
    else
    {
        if (m_15c)
            FUN_0046c8e0(0);
        RH_ACTOR_ACCESS(present, 1, 213);
        if (present)
        {
            m_15c = (RHSequence *)new RHUnk00582220;
            m_15c->Serialize(file, false);
        }
        RH_ACTOR_ACCESS(count, 2, 220);
        for (unsigned short i = 0; i < (unsigned short)count; ++i)
        {
            point.Serialize(file);
            m_17c.insert(m_17c.end(), point);
        }
    }
    FUN_005e0c90(file, (std::string &)m_1a8);
    if (file.m_bLoading && !m_1a5 && m_1a8.m_8 != 0 && g_unk0x6c0691 == 1)
    {
        m_1a5 = 1;
        RHUnkSectorScript *script = (RHUnkSectorScript *)m_0;
        if (!script->Unk00639a30((std::string &)m_1a8))
            SBAssert(1, "P:\\Robin Hood\\RHelementactor.cpp", 239,
                     "ICH GLAUB' DEIN SCHWEIN PFEIFT : Structural error in RHM, an Actor has got a script reference that does not exist !");
        m_108.m_0 = (RHActorScriptBase *)this;
    }
    if (m_0[0x58])
        ((RHScrollScript *)m_0)->FUN_006348f0(file);
    RHSerializeName(file, "RHElementActor");
    return RHElement::Serialize(file);
}

// FUNCTION: GAME 0x00464530
void RHActorPositionCalls::FUN_00464530(const SBGeoPoint2D &point)
{
    RHActorField<SBGeoPoint2D>(this, 0x20) = point;
    {
        SBGeoVector2D displacement(point);
        SBGeoBoundingBox2D *box = (SBGeoBoundingBox2D *)
            ((RHUnkPathActorInfoBase *)this)->Unk0055fa10(RHActorField<int>(this, 0x88));
        RHActorField<SBGeoBoundingBox2D>(this, 0xc0) = box->FUN_006090d0(displacement);
    }
    RHActorField<int>(this, 4) = 2;
}

// GLOBAL: GAME 0x006775b4
float g_actorStepScale = 0.25f;
// GLOBAL: GAME 0x006777c4
float g_actorEffectOffset = 4.0f;

// Local placement, register scheduling, and cleanup remain unmatched.
// STUB: GAME 0x00467230
void RHElementActor::ExecuteImmediately(RHSequenceElement *element)
{
    switch (element->m_10)
    {
    case 24:
    {
        RHUnk00613e90 unused;
        RHUnk0040f060 areas;
        SBGeoPoint2D point;
        RHUnk00613e90 origin;
        RHUnk00613e90 destination;
        RHUnk00613e90 step;
        FUN_0046bcb0(8);
        ((RHActorEngineFlags *)g_pEngine)->m_4d98 |= 1;
        point = element->m_6c;
        bool same = point == *(SBGeoPoint2D *)((char *)Info() + 0x24);
        bool draw;
        int effect;
        if (Type() == 12 && !same)
        {
            draw = !((RHUnk004679c0 *)this)->FUN_004679c0(FUN_004679b0(), 20);
            if (draw)
            {
                FUN_00478c20(destination, false);
                FUN_00478ae0(origin);
                RHUnk00613e90 delta = destination.FUN_005df550(origin);
                RHUnk00613e90 scaled;
                scaled.FUN_00467990(delta.m_0 * g_actorStepScale, delta.m_4 * g_actorStepScale, delta.m_8 * g_actorStepScale);
                origin.m_0 -= g_actorEffectOffset;
                origin.m_4 -= g_actorEffectOffset;
                step = scaled;
                for (unsigned i = 0; i < 5; ++i)
                {
                    switch (i)
                    {
                    case 0:
                    case 4: effect = 4; break;
                    case 1:
                    case 3: effect = 12; break;
                    case 2: effect = 20; break;
                    }
                    unsigned short layer = *(unsigned short *)((char *)Info() + 0xde);
                    typedef void (RHScriptBatchCalls::*Effect)(void *, unsigned short, int, void *, int, int, int, int);
                    (((RHScriptBatchCalls *)g_unk0x6c10e8)->*(Effect)&RHScriptBatchCalls::Unk005c2ec0)(&origin, layer, 1, (void *)0, effect, 0, 0, -1);
                    origin.m_0 += step.m_0;
                    origin.m_4 += step.m_4;
                    origin.m_8 += step.m_8;
                }
            }
        }
        void *area;
        int layer = 100;
        unsigned short cell = Grid()->FUN_004e9800(point, area, layer);
        if (cell != 0xffff)
        {
            SBGeoBoundingBox2D box = ((SBGeoBoundingBox2D *)((RHUnkPathActorInfoBase *)Position())->Unk0055fa10(*(int *)((char *)Position() + 0x88)))->FUN_006090d0(SBGeoVector2D(point));
            if (Grid()->FUN_004f5e50(box.m_8, point, layer))
                point = box.FUN_00608f40();
            else
                cell = 0xffff;
        }
        if (cell != 0xffff)
        {
            void *projection = ((RHActorAreaCalls *)area)->FUN_0057d800(point);
            ((RHActorPositionCalls *)Position())->FUN_00464530(point);
            *(unsigned short *)((char *)Position() + 0xda) = (unsigned short)layer;
            FUN_00462700(cell);
            Position()->FUN_0055fa70(projection);
            Position()->FUN_0055f290();
            Info()->FUN_005bd560(0, true);
            void *current = *(void **)((char *)Info() + 0xe0);
            if ((char)(*(unsigned *)((char *)current + 0x30) >> 9) & 1)
            {
                switch (*(int *)((char *)current + 0xf0))
                {
                case 2: ((RHScriptBatchCalls *)this)->Unk0046bcf0(4, 0); break;
                case 3: ((RHScriptBatchCalls *)this)->Unk0046bcf0(5, 0); break;
                }
            }
            if (Type() == 12)
            {
                RHElementActor *related = *(RHElementActor **)((char *)this + 0x5cc);
                if (related)
                    related->FUN_00462730(this, false);
                related = *(RHElementActor **)((char *)this + 0x254);
                if (related)
                    related->FUN_00462730(this, false);
            }
        }
        if (Type() == 12 && !same && draw)
        {
            FUN_00478c20(destination, false);
            FUN_00478ae0(origin);
            RHUnk00613e90 delta = destination.FUN_005df550(origin);
            RHUnk00613e90 scaled;
            scaled.m_8 = delta.m_8 * g_actorStepScale;
            scaled.m_4 = delta.m_4 * g_actorStepScale;
            scaled.m_0 = delta.m_0 * g_actorStepScale;
            step = scaled;
            origin.m_0 -= g_actorEffectOffset;
            origin.m_4 -= g_actorEffectOffset;
            for (unsigned i = 0; i < 5; ++i)
            {
                switch (i)
                {
                case 0:
                case 4: effect = 4; break;
                case 1:
                case 3: effect = 12; break;
                case 2: effect = 20; break;
                }
                unsigned short layer = *(unsigned short *)((char *)Info() + 0xde);
                typedef void (RHScriptBatchCalls::*Effect)(void *, unsigned short, int, void *, int, int, int, int);
                (((RHScriptBatchCalls *)g_unk0x6c10e8)->*(Effect)&RHScriptBatchCalls::Unk005c2ec0)(&origin, layer, 1, (void *)0, effect, 0, 0, -1);
                origin.m_0 += step.m_0;
                origin.m_4 += step.m_4;
                origin.m_8 += step.m_8;
            }
        }
        FUN_00464630();
        break;
    }
    case 170:
        Info()->FUN_005bd650(element->Unk00587160(37), element->Unk00587160(38));
        element->FUN_00585970(0, true);
        break;
    case 171:
        Info()->FUN_005bd7b0(element->Unk00587160(37));
        element->FUN_00585970(0, true);
        break;
    case 15:
        if (m_0[0x58])
        {
            RHElementActor *saved = g_unk0x6c100c;
            g_unk0x6c100c = this;
            m_108.FUN_004033b0(element->Unk00587160(3), element->Unk00587160(4), element->Unk00587160(5));
            g_unk0x6c100c = saved;
        }
        else
            SBAssert(0, "P:\\Robin Hood\\RHelementactor.cpp", 2948,
                     // STRING: GAME 0x006ae230
                     "Can't process a send message command on a npc without a script class");
        element->FUN_00585970(0, true);
        break;
    }
}

// FUNCTION: GAME 0x00467990
void RHUnk00613e90::FUN_00467990(float x, float y, float z)
{
    m_0 = x;
    m_4 = y;
    m_8 = z;
}

// FUNCTION: GAME 0x004679b0
const SBGeoPoint2D &RHElementActor::FUN_004679b0() const
{
    return *(SBGeoPoint2D *)((char *)Info() + 0x24);
}

// FUNCTION: GAME 0x004679c0
bool RHUnk004679c0::FUN_004679c0(SBGeoPoint2D point, unsigned short value)
{
    bool result = m_580 > 0;
    if (!(m_584 == *(SBGeoPoint2D *)(m_info + 0x24)))
    {
        m_584 = point;
        m_580 = value;
        m_582 = value;
    }
    return result;
}

// Parked: movement/interaction branches and original EH scheduling remain incomplete.
// STUB: GAME 0x00467a50
void RHElementActor::Translate(RHSequenceElement *element, RHcommand command)
{
    int selected = command ? command : element->m_10;
    RHActorTranslationSequenceCalls *sequence = (RHActorTranslationSequenceCalls *)element;
    switch (selected)
    {
    case 2:
    {
        void *area = RHActorField<void *>(element, 0x78);
        void *other = RHActorField<void *>(element, 0x84);
        void *position = RHActorField<void *>(other, 0x50);
        if (area)
        {
            sequence->V0c(RHActorField<void *>(position, 0xe0) == area ? 0 : 6, true);
        }
        else
        {
            SBGeoPoint2D difference = RHActorField<SBGeoPoint2D>(position, 0x24).Unk005fc110(element->m_6c);
            float x = difference.m_0 < 0.0f ? -difference.m_0 : difference.m_0;
            float y = difference.m_4 < 0.0f ? -difference.m_4 : difference.m_4;
            float distance = x > y ? x : y;
            sequence->V0c(distance >= RHActorField<float>(element, 0x8c) + 1.0f ? 6 : 0, true);
        }
        break;
    }
    case 18:
    {
        RHOrder *order = new RHOrder;
        order->m_24 = 0x124;
        sequence->FUN_00585970(order);
        break;
    }
    case 160:
    case 161:
    case 169:
    {
        if (selected == 160)
            m_14c = element->Unk00587160(2);
        RHOrder *order = new RHOrder;
        int posture = RHActorField<int>(element, 0x3c);
        int action = RHActorField<int>(element, 0x40);
        switch (posture)
        {
        case 1: order->m_24 = 0; break;
        case 3: order->m_24 = 0x30; break;
        case 4:
        case 5: order->m_24 = 0x124; break;
        case 8: order->m_24 = 0x9f; break;
        case 10: order->m_24 = 0x0e; break;
        case 12:
            order->m_24 = action >= 4 && action <= 6 ? 0x71 :
                action >= 7 && action <= 11 ? 0x6a : 0x2f;
            break;
        case 13:
            order->m_24 = action >= 4 && action <= 6 ? 0x74 :
                ((action >= 7 && action <= 11) || action == 15) ? 0x6d : 0x2d;
            break;
        }
        sequence->FUN_00585970(order);
        break;
    }
    case 164:
    case 165:
    case 166:
    case 167:
    {
        RHOrder *order = new RHOrder;
        order->m_24 = 0x11c + selected - 164;
        order->m_2a = 0;
        sequence->FUN_00585970(order);
        break;
    }
    }
}

// FUNCTION: GAME 0x00468ee0
SBGeoVector2D RHElementActor::FUN_00468ee0(int value) const
{
    return Position()->FUN_00468f10(value);
}

static void RHActorApplyCrossingFlags(RHElementActor *actor, RHElevationLine *line)
{
    SBGeoPoint2D &point = RHActorField<SBGeoPoint2D>(actor->Info(), 0x24);
    if ((line->m_14 & 0x40) && actor->Type() == 12)
    {
        RHPatch *patch = RHActorField<RHPatch *>(line, 0x20);
        if (RHActorField<unsigned char>(patch, 2))
        {
            void *area = RHActorField<void *>(patch, 0x148);
            RHElementAreaShape *shape = area ? (RHElementAreaShape *)((char *)area + 4) : 0;
            if (shape->FUN_0060c660(point))
            {
                patch->Enter(actor);
                if (!RHActorField<unsigned char>(patch, 0))
                    patch->FUN_00550150();
            }
            else
            {
                patch->Leave(actor);
                if (RHActorField<unsigned char>(patch, 0))
                {
                    RHScriptNode *head = RHActorField<RHScriptNode *>(patch, 0x17c);
                    if (!RHActorField<unsigned>(patch, 0x180) || !head->next->data)
                        patch->FUN_00550150();
                }
            }
        }
    }
    if (line->m_14 & 0x10)
    {
        RHSectorScript *script = RHActorField<RHSectorScript *>(line, 0x30);
        if (script)
        {
            RHElementAreaShape *shape = (RHElementAreaShape *)((char *)script + 4);
            if (shape->FUN_0060c660(RHActorField<SBGeoPoint2D>(actor->Info(), 0x24)))
                script->Enter(actor);
            else
                script->Leave(actor);
        }
        else
            FUN_0048a970(actor);
    }
    if (line->m_14 & 0x20)
    {
        void *area = RHActorField<void *>(line, 0x1c);
        void *value = RHActorField<void *>(area, 0x60);
        RHElementAreaShape *shape = area ? (RHElementAreaShape *)((char *)area + 4) : 0;
        void *position = actor->Info();
        if (shape->FUN_0060c660(RHActorField<SBGeoPoint2D>(position, 0x24)))
            RHActorField<void *>(position, 0xfc) = value;
        else
        {
            void *owner = RHActorField<void *>(position, 0xec);
            RHActorField<void *>(position, 0xfc) = owner ? RHActorField<void *>(owner, 0x168) :
                RHActorField<void *>(actor->Grid(), 0x4188);
        }
    }
}

// FUNCTION: GAME 0x0046c8e0
void RHElementActor::FUN_0046c8e0(int value)
{
    m_15c = (RHSequence *)value;
}

// Parked: intersection sorting and original list/EH scheduling remain incomplete.
// STUB: GAME 0x0046c8f0
void RHElementActor::CheckForLineCrossing()
{
    RHUnk0040f060 lines;
    void *position = Info();
    SBGeoPoint2D &current = RHActorField<SBGeoPoint2D>(position, 0x24);
    SBGeoPoint2D &previous = RHActorField<SBGeoPoint2D>(position, 0x40);
    if (!current.FUN_005fc0e0(previous) || RHActorField<int>(position, 0x8c) == 9)
        return;
    if ((RHActorField<unsigned>(this, 4) & 7) == 4 && RHActorField<void *>(this, 0x254))
        return;
    void *grid = Grid();
    if (!((SBGeoBoundingBox2D *)((char *)grid + 0x3e84))->FUN_00608400(current))
        return;
    ((RHMobileGrid *)grid)->FUN_004ed370(&lines,
        RHActorField<unsigned short>(position, 0xde), RHMobileSegment(previous, current), 8);

    RHScriptNode *head = lines.head;
    for (RHScriptNode *node = head->next; node != head; node = node->next)
    {
        RHElevationLine *line = (RHElevationLine *)node->data;
        if (line->m_14 & 4)
        {
            SBGeoPoint2D first(line->m_04);
            SBGeoPoint2D second(line->m_0c);
            RHScriptNode *other = node->next;
            while (other != head)
            {
                RHElevationLine *candidate = (RHElevationLine *)other->data;
                RHScriptNode *next = other->next;
                if (candidate->m_14 == line->m_14 &&
                    ((first == candidate->m_04 && second == candidate->m_0c) ||
                     (second == candidate->m_04 && first == candidate->m_0c)))
                {
                    other->previous->next = next;
                    next->previous = other->previous;
                    ::operator delete(other);
                    --lines.count;
                    RHActorField<unsigned char>(&lines, 0x10) = 1;
                }
                other = next;
            }
        }
    }

    for (RHScriptNode *filter = head->next; filter != head; )
    {
        RHElevationLine *line = (RHElevationLine *)filter->data;
        float dx = previous.m_0 - line->m_04.m_0;
        float dy = previous.m_4 - line->m_04.m_4;
        float nx = line->m_0c.m_0 - line->m_04.m_0;
        float ny = line->m_0c.m_4 - line->m_04.m_4;
        RHScriptNode *next = filter->next;
        if (dx * nx + dy * ny == 0.0f)
        {
            filter->previous->next = next;
            next->previous = filter->previous;
            ::operator delete(filter);
            --lines.count;
            RHActorField<unsigned char>(&lines, 0x10) = 1;
        }
        filter = next;
    }

    unsigned short count = (unsigned short)lines.count;
    if (count == 0)
        return;
    if (count == 1)
    {
        RHElevationLine *line = (RHElevationLine *)head->next->data;
        if (line->m_14 & 4)
        {
            CrossElevationLine(line);
            if ((RHActorField<unsigned>(this, 4) & 7) == 4)
                ((RHActorCrossingHumanCalls *)this)->FUN_004846d0();
            if (m_134)
                ((RHMobilePosition *)Position())->FUN_0055fc20(m_134->m_2a != 0);
        }
        RHActorApplyCrossingFlags(this, line);
        return;
    }

    void *area = RHActorField<void *>(position, 0xec);
    RHScriptNode *destination = head->next;
    unsigned short elevationCount = 0;
    for (RHScriptNode *partition = head->next; partition != head; partition = partition->next)
    {
        RHElevationLine *line = (RHElevationLine *)partition->data;
        if (line->m_14 & 4)
        {
            void *saved = destination->data;
            destination->data = partition->data;
            partition->data = saved;
            destination = destination->next;
            ++elevationCount;
        }
    }
    destination = head->next;
    for (unsigned short i = 0; i < elevationCount; ++i)
    {
        RHScriptNode *selected = destination;
        while (selected != head)
        {
            RHElevationLine *line = (RHElevationLine *)selected->data;
            if ((line->m_14 & 4) && (line->m_24 == area || line->m_28 == area))
                break;
            selected = selected->next;
        }
        if (selected == head)
            selected = destination;
        RHElevationLine *line = (RHElevationLine *)selected->data;
        area = line->m_28 == area ? line->m_24 : line->m_28;
        void *saved = destination->data;
        destination->data = selected->data;
        selected->data = saved;
        CrossElevationLine(line);
        destination = destination->next;
    }
    if (elevationCount)
    {
        if ((RHActorField<unsigned>(this, 4) & 7) == 4)
            ((RHActorCrossingHumanCalls *)this)->FUN_004846d0();
        if (m_134)
            ((RHMobilePosition *)Position())->FUN_0055fc20(m_134->m_2a != 0);
    }
    while (destination != head)
    {
        RHActorApplyCrossingFlags(this, (RHElevationLine *)destination->data);
        destination = destination->next;
    }
}

class RHUnk0048a970
{
public:
    void Unk(int mode);
};

class RHActorAreaTransitionView
{
public:
    virtual void V00() = 0;
    virtual void V04() = 0;
    virtual void V08() = 0;
    virtual void V0c() = 0;
    virtual void V10() = 0;
    virtual void V14() = 0;
    virtual void V18() = 0;
    virtual void V1c() = 0;
    virtual void V20() = 0;
    virtual void V24() = 0;
    virtual void V28() = 0;
    virtual void V2c() = 0;
    virtual void V30() = 0;
    virtual void V34() = 0;
    virtual void V38() = 0;
    virtual void V3c() = 0;
    virtual void V40() = 0;
    virtual void V44() = 0;
    virtual void V48() = 0;
    virtual void V4c() = 0;
    virtual void V50() = 0;
    virtual void V54() = 0;
    virtual void V58() = 0;
    virtual void V5c() = 0;
    virtual void V60() = 0;
    virtual void V64() = 0;
    virtual void V68() = 0;
    virtual void V6c() = 0;
    virtual void V70() = 0;
    virtual void V74() = 0;
    virtual void V78() = 0;
    virtual void V7c() = 0;
    virtual void V80() = 0;
    virtual void V84() = 0;
    virtual void V88() = 0;
    virtual void V8c() = 0;
    virtual void V90() = 0;
    virtual void V94() = 0;
    virtual void V98() = 0;
    virtual void V9c() = 0;
    virtual void Va0(unsigned short layer, void *area) = 0;
};

struct RHActorTransitionType
{
    unsigned kind : 5;
    unsigned remaining : 27;
};

class RHActorTransitionPosition
{
public:
    RHActorTransitionPosition &Set(void *value)
    {
        RHActorField<void *>(this, 0xf0) = value;
        return *this;
    }
};

// Parked: 85.13%; final position receiver arithmetic and area/type register scheduling differ.
// STUB: GAME 0x0046d5f0
void RHElementActor::FUN_0046d5f0(void *door, bool reverse)
{
    void *area = RHActorField<void *>(Info(), 0xe0);
    bool building;
    unsigned flags = RHActorField<unsigned>(area, 0x30);
    if ((unsigned char)(flags >> 13) & 1)
    {
        building = true;
        if (RHActorField<RHActorTransitionType>(this, 4).kind == 20)
            ((RHUnk0048a970 *)((char *)this + 0x6e8))->Unk(0);
        ((RHScriptBatchCalls *)area)->Unk0057ec80(this);
    }
    else
    {
        building = false;
        if ((((unsigned char)(flags >> 9) & 1) && RHActorField<int>(area, 0xf0) == 2) ||
            RHActorField<int>(area, 0xf0) == 3)
        {
            if (RHActorField<int>(door, 0x88) == 4)
                ((RHActorAreaCalls *)area)->FUN_0057dfc0(this, false);
            else
                ((RHActorAreaCalls *)area)->FUN_0057df20(this, false);
        }
    }
    if (reverse == true)
    {
        area = RHActorField<void *>(door, 0x10);
        ((RHActorAreaTransitionView *)this)->Va0(RHActorField<unsigned short>(door, 0x16), area);
    }
    else
    {
        area = RHActorField<void *>(door, 0x0c);
        ((RHActorAreaTransitionView *)this)->Va0(RHActorField<unsigned short>(door, 0x14), area);
        if (building)
        {
            void *projection = ((RHActorAreaCalls *)area)->FUN_0057d800(RHActorField<SBGeoPoint2D>(door, 0x18));
            Position()->FUN_0055fa70(projection);
        }
        Position()->FUN_0055f290();
    }
    ((RHActorTransitionPosition *)Position())->Set(0);
    if ((unsigned char)(RHActorField<unsigned>(area, 0x30) >> 13) & 1)
    {
        if (RHActorField<RHActorTransitionType>(this, 4).kind == 20)
            ((RHUnk0048a970 *)((char *)this + 0x6e8))->Unk(1);
        ((RHScriptBatchCalls *)area)->Unk0057ebd0(this);
    }
    if (RHActorField<RHPatch *>(door, 0xb0))
        RHActorField<RHPatch *>(door, 0xb0)->FUN_00550150();
}

// FUNCTION: GAME 0x0046d710
bool RHElementActor::FUN_0046d710()
{
    int state = *(int *)((char *)Info() + 0x8c);
    if (state >= 4 && (state <= 5 || state == 9))
        return true;
    if (m_130)
    {
        int command = m_130->m_10;
        if (command == 0x13 || command == 0x2d)
            return true;
    }
    return false;
}

struct RHActorSeekPosition
{
    float x;
    float y;
    void *area;
    unsigned layer;
};

class RHFastFindTacticalArray;
extern RHFastFindTacticalArray g_unk0x006c06f0;

class RHActorSeekList : public RHSeqList
{
public:
    RHActorSeekList(const char &allocator) : RHSeqList(allocator) { m_valid = true; }
    ~RHActorSeekList()
    {
        Clear();
        Clear();
        operator delete(m_head);
        m_head = 0;
        m_count = 0;
    }
    void Clear()
    {
        RHSectorActorIter current((RHSectorActorNode *)m_head->next);
        while (current.m_p != (RHSectorActorNode *)m_head)
        {
            RHSectorActorIter removed = current++;
            ((RHUnk0046eb30 *)this)->erase(RHScriptIter((RHScriptNode *)removed.m_p));
        }
    }
};

// Parked: 35.08%; seek-position copies, list cleanup temporaries and stack/register allocation differ.
// STUB: GAME 0x0046d750
void *RHElementActor::FUN_0046d750(const SBGeoPoint2D &origin, unsigned short radius)
{
    SBGeoPoint2D point;
    char allocator;
    RHActorSeekList sectors(allocator);
    RHActorGridCalls *grid = (RHActorGridCalls *)g_unk0x6c0a9c;
    void *result = 0;
    float farthest = 10.0f;
    void **first = RHActorField<void **>(&g_unk0x006c06f0, 4);
    unsigned short count = first ? RHActorField<void **>(&g_unk0x006c06f0, 8) - first : 0;
    for (unsigned short index = 0; index < count; ++index)
    {
        void *seek = RHActorField<void **>(&g_unk0x006c06f0, 4)[index];
        RHActorSeekPosition position = RHActorField<RHActorSeekPosition>(seek, 4);
        RHActorSeekPosition copy = RHActorField<RHActorSeekPosition>(seek, 4);
        float x = copy.x;
        float y = position.y;
        point.m_0 = x;
        point.m_4 = y;
        float distance = origin.Unk005fc110(point).FUN_005fc700(1.0f);
        if (distance > farthest && distance <= radius)
        {
            RHActorSeekPosition destination = RHActorField<RHActorSeekPosition>(seek, 4);
            void *info = Info();
            if (RHActorField<void *>(info, 0xe0) == destination.area ||
                grid->FUN_004f9a80(&sectors, this, RHActorField<SBGeoPoint2D>(info, 0x24),
                    RHActorField<void *>(info, 0xe0), RHActorField<unsigned short>(info, 0xde), point,
                    destination.area, destination.layer, 0))
            {
                farthest = distance;
                result = seek;
            }
        }
    }
    if (!result && radius < 10000)
        result = FUN_0046d750(origin, 10000);
    return result;
}

// FUNCTION: GAME 0x0046e270
bool RHElementActor::FUN_0046e270()
{
    if (m_15c)
    {
        if (m_150 && (*(unsigned *)((char *)m_150 + 4) & 15) == 12)
            ((RHUnk0046bcb0 *)m_150)->Unk(8);
        m_150 = 0;
        m_130->FUN_00585970(0, true);
        ((RHUnk0058a3d0 *)*(void **)((char *)this + 0x5c))->Unk(g_unk0x6c0560, 0, m_15c);
        FUN_0046c8e0(0);
        return true;
    }
    return false;
}

// FUNCTION: GAME 0x0046e7e0
void RHElementActor::InitializeScript(std::string &name)
{
    if (g_unk0x6c0691 == 1)
    {
        m_1a5 = 1;
        m_1a8.Assign((const RHActorString &)name);
        RHUnkSectorScript *script = (RHUnkSectorScript *)m_0;
        if (!script->Unk00639a30(name))
            SBAssert(1,
                     // STRING: GAME 0x006ae188
                     "P:\\Robin Hood\\RHelementactor.cpp", 7964,
                     // STRING: GAME 0x006ae1ac
                     "ICH GLAUB' DEIN SCHWEIN PFEIFT : Structural error in RHM, an Actor has got a script reference that does not exist !");
        m_108.m_0 = (RHActorScriptBase *)this;
    }
    m_108.FUN_004030a0();
}

// FUNCTION: GAME 0x004846d0
void RHActorCrossingHumanCalls::FUN_004846d0()
{
    RHOrder *order = RHActorField<RHOrder *>(this, 0x134);
    if (order && order->m_24 == 0x7f &&
        RHActorField<RHSequenceElement *>(this, 0x130)->m_10 != 0x4c)
    {
        void *area = RHActorField<void *>(RHActorField<void *>(this, 0x50), 0xec);
        SBGeoPoint2D point;
        if (FUN_004843a0(area) && FUN_004843d0(point, area, true))
        {
            RHActorField<SBGeoPoint2D>(RHActorField<RHOrder *>(this, 0x134), 0x14) = point;
            RHActorField<RHOrder *>(this, 0x134)->FUN_0054e730();
            void *position = (char *)RHActorField<void *>(this, 0x50) + 4;
            RHActorField<SBGeoPoint2D>(position, 0x44) = point;
            RHActorField<int>(position, 8) = 0;
        }
        else
        {
            void *position = RHActorField<void *>(this, 0x50);
            SBGeoPoint2D *source = (SBGeoPoint2D *)((char *)position + 0x24);
            SBGeoPoint2D *destination = (SBGeoPoint2D *)((char *)position + 0x48);
            *destination = *source;
            RHActorField<int>(position, 0xc) = 0;
        }
    }
}

// FUNCTION: GAME 0x004e52a0
void RHUnk004e52a0::FUN_004e52a0()
{
    RHScriptNode *head = m_head;
    RHScriptNode *current = head->next;
    while (current != head)
    {
        RHScriptNode *node = current;
        current = current->next;
        node->previous->next = node->next;
        node->next->previous = node->previous;
        ::operator delete(node);
        --m_count;
    }
    ::operator delete(m_head);
    m_head = 0;
    m_count = 0;
}

// Parked: receiver/layer registers and sector-flag shift/test lowering differ.
// STUB: GAME 0x004e9800
unsigned short RHActorGridCalls::FUN_004e9800(const SBGeoPoint2D &point, void *&area, int &layer)
{
    for (short index = RHActorField<unsigned short>(this, 0x3e9c) - 1; index >= 0; --index)
    {
        short result = FUN_004e8fc0(point, SBGeoPoint2D(), index, area);
        if (result >= 0)
        {
            if (((RHActorField<unsigned>(area, 0x30) >> 1) & 1) &&
                (RHActorField<unsigned>(area, 0x30) & 1))
            {
                *(unsigned short *)&layer = index;
                return RHActorField<unsigned short>(area, 0x38);
            }
            if (result > 0)
            {
                if ((RHActorField<unsigned>(area, 0x30) >> 10) & 1)
                {
                    area = RHActorField<void *>(area, 0x58);
                    if ((RHActorField<unsigned>(area, 0x30) >> 9) & 1)
                    {
                        *(unsigned short *)&layer = RHActorField<unsigned short>(this, 0x3e9c);
                        return RHActorField<unsigned short>(area, 0x38);
                    }
                }
                else if ((RHActorField<unsigned>(area, 0x30) & 0x8000) == 0x8000)
                {
                    *(unsigned short *)&layer = RHActorField<unsigned short>(area, 0x36);
                    area = RHActorField<void *>(area, 0x98);
                    return RHActorField<unsigned short>(area, 0x38);
                }
            }
        }
    }
    return 0xffff;
}

// FUNCTION: GAME 0x0053bf20
void *RHUnk0053bf20::FUN_0053bf20() const
{
    return m_8;
}

// FUNCTION: GAME 0x00560410
unsigned short RHUnk00560410::FUN_00560410(int value) const
{
    return m_90;
}

// FUNCTION: GAME 0x00585970
void RHActorTranslationSequenceCalls::FUN_00585970(RHOrder *order)
{
    if (order->m_24 == 0x123)
        delete order;
    else
    {
        RHScriptNode *head = RHActorField<RHScriptNode *>(this, 0x1c);
        RHScriptNode *previous = head->previous;
        RHScriptNode *node = (RHScriptNode *)::operator new(sizeof(RHScriptNode));
        node->next = head ? head : node;
        node->previous = previous ? previous : node;
        head->previous = node;
        node->previous->next = node;
        new (&node->data) RHOrder *(order);
        unsigned count = RHActorField<unsigned>(this, 0x20);
        RHActorField<undefined>(this, 0x28) = 1;
        RHActorField<unsigned>(this, 0x20) = count + 1;
        order->m_38 = this;
    }
}

// FUNCTION: GAME 0x00587160
int RHSequenceElement::Unk00587160(int argument)
{
    return ((RHHumanMap *)((char *)this + 0x64))->find(argument)->m_value;
}

// FUNCTION: GAME 0x005871b0
SBGeoPoint2D RHActorSequencePointCalls::FUN_005871b0(int key)
{
    SBGeoPoint2D point;
    RHHumanMapIterator position = m_64.find(key);
    if (!(position == m_64.end()))
        point = SBGeoPoint2D(RHActorField<float>(position.m_node, 0x10),
                             RHActorField<float>(position.m_node, 0x14));
    return point;
}

// Parked: search-loop registers, iterator temporaries and insertion scheduling differ.
// STUB: GAME 0x005bd650
void RHBonusInfo::FUN_005bd650(int value1, int value2)
{
    RHActorValueList &keys = *(RHActorValueList *)((char *)this + 0x1e0);
    unsigned short index = keys.Find(value1, true);
    if (index == 0xffff)
    {
        RHActorValueList &values = *(RHActorValueList *)((char *)this + 0x204);
        index = values.Find(value1, false);
        if (index == 0xffff)
        {
            RHUnk004b1520List &keyList = *(RHUnk004b1520List *)&keys;
            keyList.FUN_00424410(keyList.end(), *(void *const *)&value1);
            keys.dirty = true;
            RHUnk004b1520List &valueList = *(RHUnk004b1520List *)&values;
            valueList.FUN_00424410(valueList.end(), *(void *const *)&value2);
            values.dirty = true;
            return;
        }
    }
    RHActorValueList &values = *(RHActorValueList *)((char *)this + 0x204);
    ((RHSeqList *)&values)->GoTo(index);
    *(int *)&values.cursor.node->data = value2;
}

// Parked: cached-search loads and postincrement erase scheduling differ.
// STUB: GAME 0x005bd7b0
void RHBonusInfo::FUN_005bd7b0(int value)
{
    RHActorValueList &keys = *(RHActorValueList *)((char *)this + 0x1e0);
    unsigned short index = keys.Find(value, true);
    if (index != 0xffff)
    {
        ((RHSeqList *)&keys)->GoTo(index);
        keys.Erase(keys.cursor);
        RHActorValueList &values = *(RHActorValueList *)((char *)this + 0x204);
        ((RHSeqList *)&values)->GoTo(index);
        RHSectorActorIter position((RHSectorActorNode *)values.cursor.node);
        RHSectorActorIter previous = position++;
        values.Erase(RHScriptIter((RHScriptNode *)previous.m_p));
    }
}

// FUNCTION: GAME 0x005df550
RHUnk00613e90 RHUnk00613e90::FUN_005df550(const RHUnk00613e90 &other) const
{
    RHUnk00613e90 result(m_0 - other.m_0, m_4 - other.m_4, m_8 - other.m_8);
    return result;
}

// FUNCTION: GAME 0x005fc040
SBGeoPoint2D::SBGeoPoint2D(const SBGeoPoint2D &other)
{
    FUN_005fc390(other);
}

// FUNCTION: GAME 0x005fc0b0
bool SBGeoPoint2D::operator==(const SBGeoPoint2D &other) const
{
    return m_0 == other.m_0 && m_4 == other.m_4;
}

// deferred: unannotated pending reccmp #534 (0x005fc3e0).
SBGeoVector2D::SBGeoVector2D(const SBGeoPoint2D &other) : SBGeoPoint2D()
{
    FUN_005fc390(other);
}

extern float g_unk0x00677488;

// Parked: x87 spills and branch scheduling differ.
// STUB: GAME 0x005fc700
float SBGeoPoint2D::FUN_005fc700(float scale) const
{
    scale = m_4 / scale;
    if (m_0 > g_unk0x00677488)
    {
        float other = scale > g_unk0x00677488 ? scale : -scale;
        return other < m_0 ? m_0 : other;
    }
    if (scale > g_unk0x00677488)
        return -m_0 >= scale ? -m_0 : scale;
    scale = -scale;
    return -m_0 >= scale ? -m_0 : scale;
}

// FUNCTION: GAME 0x00607a70
SBGeoBoundingBox2D::SBGeoBoundingBox2D(const SBGeoBoundingBox2D &other)
{
    ((RHMobileUnk00607da0 *)this)->FUN_00607990((const RHMobileUnk00607da0 &)other);
}

// FUNCTION: GAME 0x0060fbf0
RHUnk0060fbf0::RHUnk0060fbf0()
{
    m_0 = 0;
    m_2 = 0;
    m_4 = 0;
}

// FUNCTION: GAME 0x0060fca0
RHUnk0060fbf0 &RHUnk0060fbf0::FUN_0060fca0(const RHUnk0060fbf0 &other)
{
    if (this != &other)
    {
        FUN_0060fa20();
        FUN_0060fa30(other);
    }
    return *this;
}

void RHActorEmitWidened(RHUnk0053bf20 *first, RHUnk00560410 *second,
                        RHUnk0060fbf0 *third, RHUnk004e52a0 *list,
                        SBGeoPoint2D *point)
{
    first->FUN_0053bf20();
    second->FUN_00560410(0);
    new RHUnk0060fbf0;
    third->FUN_0060fca0(*third);
    list->FUN_004e52a0();
    point->FUN_005fc700(1.0f);
    ((RHActorSequencePointCalls *)first)->FUN_005871b0(0);
    ((RHActorCrossingHumanCalls *)first)->FUN_004846d0();
    ((RHSequenceElement *)first)->Unk00587160(0);
    new SBGeoBoundingBox2D(*(SBGeoBoundingBox2D *)first);
}

void RHElementActor::Emit(SBFile &file, std::string &name)
{
    FUN_0046d710();
    FUN_0046d5f0(this, false);
    FUN_0046d750(m_128, 10000);
    FUN_0046e270();
    Serialize(file);
    ExecuteImmediately(0);
    Translate(0, RHcommandUnk0);
    CheckForLineCrossing();
    InitializeScript(name);
    FUN_004626e0();
    FUN_00468ee0(0);
}

RHOrder::RHOrder()
{
    memset(m_04, 0, sizeof(m_04));
    m_24 = 0x123;
    m_28 = m_29 = m_2b = m_2c = m_2d = m_2e = 0;
    m_2a = 1;
    m_30 = m_38 = 0;
    m_34 = 0;
}

void __stdcall FUN_0048a970(RHElementActor *) {}
