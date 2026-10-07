#include "RHElementActor.h"

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
    engine->SerializeNestedA(file, &m_150);
    engine->SerializeNestedA(file, &m_170);
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
            draw = !FUN_004679c0(FUN_004679b0(), 20);
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

void RHElementActor::Emit(SBFile &file, std::string &name)
{
    Serialize(file);
    ExecuteImmediately(0);
    Translate(0, RHcommandUnk0);
    CheckForLineCrossing();
    InitializeScript(name);
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

void RHActorTranslationSequenceCalls::FUN_00585970(RHOrder *order)
{
    if (order->m_24 == 0x123)
    {
        delete order;
        return;
    }
    RHScriptNode *head = RHActorField<RHScriptNode *>(this, 0x1c);
    RHScriptNode *node = (RHScriptNode *)::operator new(sizeof(RHScriptNode));
    node->next = head;
    node->previous = head->previous;
    head->previous = node;
    node->previous->next = node;
    node->data = order;
    ++RHActorField<unsigned>(this, 0x20);
    RHActorField<unsigned char>(this, 0x28) = 1;
    order->m_38 = this;
}

void RHActorCrossingHumanCalls::FUN_004846d0() {}
void __stdcall FUN_0048a970(RHElementActor *) {}
