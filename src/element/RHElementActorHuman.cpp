#include "SBNullstr.h"
#include "RHElementActorHuman.h"
#include "RHActorCrossingHumanCalls.h"
#include "RHActorAreaCalls.h"
#include <stdlib.h>
#include <math.h>
#include <vector>
#include "RHActorPCHumanCalls.h"
#include "RHPlayerProfileAccess.h"
#include "RHSequenceGenericCalls.h"
#include "RHSequenceInteractionAction.h"

extern undefined g_unk0x006c0e48[0x2c];


// GLOBAL: GAME 0x006ae494
float g_unk0x006ae494[16] = { 0, 6.1f, 11.3f, 14.8f, 16, 14.8f, 11.3f, 6.1f, 0, -6.1f, -11.3f, -14.8f, -16, -14.8f, -11.3f, -6.1f };
// GLOBAL: GAME 0x006ae4d4
float g_unk0x006ae4d4[16] = { -9.18f, -8.49f, -6.48f, -3.5f, 0, 3.5f, 6.48f, 8.49f, 9.18f, 8.49f, 6.48f, 3.5f, 0, -3.5f, -6.48f, -8.49f };
class RHUnk0048a970;
extern RHUnk0048a970 *g_unk0x6c0b3c;
extern char g_unk0x6c0691;

// FUNCTION: GAME 0x0047a450
bool RHElementActorHuman::FUN_0047a450(RHElementActorHuman *other)
{
    void *current = *(void **)((char *)this + 0x134);
    if (!current)
        goto rejected;
    switch (*(int *)((char *)current + 0x24))
    {
    case 3:
    case 6:
    case 0x59:
        break;
    default:
rejected:
        return false;
    }
    return ((SBGeoPoint2D *)(*(char **)((char *)other + 0x50) + 0x24))->Unk005fc110(
        *(SBGeoPoint2D *)(*(char **)((char *)this + 0x50) + 0x24)).FUN_005fc660(
            ((RHMalignityActorCalls *)this)->FUN_004135b0()) > 0.0f;
}

// GLOBAL: GAME 0x006b793c
int g_unk0x006b793c[16] = { 0, 1, 2, 3, 1, 4, 5, 6, 2, 5, 7, 8, 3, 6, 8, 9 };
// GLOBAL: GAME 0x006b797c
int g_unk0x006b797c[9] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };

DECOMP_SIZE_ASSERT(RHElementActorHuman, 0x49c)
DECOMP_SIZE_ASSERT(RHUnk005864a0, 0x7c)
DECOMP_SIZE_ASSERT(RHUnk005c1d50, 0x08)
DECOMP_SIZE_ASSERT(RHHumanMapNode, 0x14)
DECOMP_SIZE_ASSERT(RHHumanMapIterator, 0x04)
DECOMP_SIZE_ASSERT(RHHumanMap, 0x10)
DECOMP_SIZE_ASSERT(RHUnk00586f70, 0x74)
DECOMP_SIZE_ASSERT(RHUnk0058bed0Object, 0x04)
DECOMP_SIZE_ASSERT(RHHumanEngineActorArray, 0x4964)
DECOMP_SIZE_ASSERT(RHHumanOpponent, 0x08)
DECOMP_SIZE_ASSERT(RHHumanOpponentNode, 0x10)
DECOMP_SIZE_ASSERT(RHHumanOpponentIterator, 0x04)
DECOMP_SIZE_ASSERT(RHHumanList, 0x18)
DECOMP_SIZE_ASSERT(RHHumanVirtualCalls, 0x04)
DECOMP_SIZE_ASSERT(RHUnk00613e90, 0x0c)
DECOMP_SIZE_ASSERT(RHUnk005866a0, 0x74)
DECOMP_SIZE_ASSERT(RHSoundSettings, 0x18)
DECOMP_SIZE_ASSERT(RHSoundChannelSettings, 0x20)
DECOMP_SIZE_ASSERT(RHUnk0044d400, 0x294)
DECOMP_SIZE_ASSERT(SBGeoBoundingBox2D, 0x14)
DECOMP_SIZE_ASSERT(SBGeoVector2D, 0x08)
DECOMP_SIZE_ASSERT(RHHumanFloatNode, 0x0c)
DECOMP_SIZE_ASSERT(RHHumanFloatIterator, 0x04)
DECOMP_SIZE_ASSERT(RHHumanFloatList, 0x18)
DECOMP_SIZE_ASSERT(RHUnkHumanPlacementA, 0x08)
DECOMP_SIZE_ASSERT(RHUnkHumanPlacementB, 0x08)

// GLOBAL: GAME 0x00677554
float g_unk0x677554 = 60.0f;

inline bool RHHumanAtDestination(void *info)
{
    void *position = (char *)info + 4;
    return RHActorField<SBGeoPoint2D>(position, 0x20).FUN_005fc0e0(RHActorField<SBGeoPoint2D>(position, 0x3c));
}

// FUNCTION: GAME 0x00471a50
bool RHElementActorHuman::FUN_00471a50()
{
    void *info = RHActorField<void *>(this, 0x50);
    if (RHActorField<SBGeoPoint2D>(info, 0x48).FUN_005fc0e0(RHActorField<SBGeoPoint2D>(info, 0x24)) &&
        RHActorField<SBGeoPoint2D>(RHActorField<void *>(this, 0x50), 0x48).FUN_005fc0e0(SBGeoPoint2D(0, 0)) ||
        RHHumanAtDestination(RHActorField<void *>(this, 0x50)))
        return true;
    return false;
}

inline bool RHHumanPositionUnchanged(void *base)
{
    return RHActorField<float>(base, 0x0c) == RHActorField<float>(base, 0x28) &&
        RHActorField<float>(base, 0x10) == RHActorField<float>(base, 0x2c) &&
        RHActorField<float>(base, 0x14) == RHActorField<float>(base, 0x30);
}

// FUNCTION: GAME 0x00471b00
bool RHElementActorHuman::FUN_00471b00()
{
    if (RHActorField<unsigned short>(this, 0x1c8) > 0 && ((RHHumanVirtualCalls *)this)->V0c0() > 0)
    {
        short remaining = RHActorField<short>(this, 0x1ca);
        if (remaining == 0)
        {
            ((RHHumanVirtualCalls *)this)->V0d8(-1, 0);
            remaining = ((RHHumanVirtualCalls *)this)->V0c0();
        }
        else
            --remaining;
        RHActorField<unsigned short>(this, 0x1ca) = remaining;
    }
    FUN_00485d90();
    if (!((RHElementActor *)this)->FUN_00464230())
        return false;
    FUN_0047ef70();
    if ((((RHActorField<unsigned>(this, 0x0c) & 31) ^ RHActorField<unsigned>(g_pEngine, 0x4a94)) & 63) == 0 &&
        m_260.count == 0 && RHHumanPositionUnchanged((char *)RHActorField<void *>(this, 0x50) + 4))
    {
        unsigned amount = (int)((RHHumanVirtualCalls *)this)->V12c() / 10;
        unsigned short previous = RHActorField<unsigned short>(this, 0x1cc);
        RHActorField<unsigned short>(this, 0x1cc) = previous - (amount > previous ? previous : amount);
    }
    return true;
}

// FUNCTION: GAME 0x00471e50
void RHElementActorHuman::FUN_00471e50(int amount, int source)
{
    if (!RHActorField<unsigned char>(this, 0x496))
    {
        if ((short)amount > 0)
            ((RHHumanVirtualCalls *)this)->V0dc(GetNewConcussionValue(amount), (void *)source, false);
        else
        {
            unsigned short current = RHActorField<unsigned short>(this, 0x1c8);
            if (current >= -(short)amount)
                ((RHHumanVirtualCalls *)this)->V0dc(current + amount, (void *)source, false);
            else
                ((RHHumanVirtualCalls *)this)->V0dc(0, (void *)source, false);
        }
    }
}

// FUNCTION: GAME 0x00471ed0
unsigned short RHElementActorHuman::GetNewConcussionValue(unsigned short amount) const
{
    unsigned short value = RHActorField<unsigned short>((void *)this, 0x1c8);
    if ((unsigned short)((RHHumanVirtualCalls *)this)->V0cc())
        value += amount * 100 / (short)((RHHumanVirtualCalls *)this)->V0cc();
    return value;
}

#include "RHActorPriorityCalls.h"

// FUNCTION: GAME 0x00471f20
int RHHumanPriorityCalls::FUN_00471f20(void *element)
{
    int kind = *(int *)((char *)element + 0x5c);
    if (kind == 0xb)
    {
        switch (*(int *)((char *)element + 0x10))
        {
        case 0x21: case 0x22: case 0x23: case 0x24:
        case 0x45: case 0x4b: case 0x55: case 0x56:
        case 0x6a: case 0x6b: case 0xb0: case 0xb2:
            return 8;
        case 0x37: case 0x38: case 0x39: case 0x3a: case 0x46:
            return 9;
        case 0x34: case 0x35: case 0x36: case 0x3b: case 0x3c:
        case 0x3d: case 0x3e: case 0x3f: case 0x40: case 0x41:
        case 0x42: case 0x43:
            return 7;
        case 0x26: case 0x27: case 0x28: case 0x29: case 0x2a:
        case 0x2b: case 0x2c: case 0x44:
            return 5;
        case 0x1d: case 0x1f: case 0x20: case 0x32: case 0x33: case 0x6c:
            return 1;
        case 0x4a:
            return 2;
        case 0xa1:
            if (((RHHumanVirtualCalls *)this)->V048())
                return 2;
            if (*(unsigned char *)((char *)this + 0x1ce))
                return 3;
        }
        return ((RHActorPriorityCalls *)this)->FUN_0046abd0(element);
    }
    return kind;
}

// FUNCTION: GAME 0x00474890
void RHElementActorHuman::FUN_00474890(void *value)
{
    if (RHActorField<int>(value, 0x3c) == 1 &&
        RHActorField<int>(value, 0x40) >= 7 && RHActorField<int>(value, 0x40) <= 11)
    {
        switch (RHActorField<int>(value, 0x94))
        {
        case 10:
            RHActorField<int>(value, 0x94) = 0x130;
            break;
        case 6: case 187:
            RHActorField<int>(value, 0x94) = 0x12f;
            break;
        }
    }
    else
        ((RHElementActor *)this)->FUN_00468f40(value);
}

// Parked: the nested switch compresses away the original explicit default-state span.
// STUB: GAME 0x004748f0
void RHElementActorHuman::FUN_004748f0(RHActorTranslationSequenceCalls *sequence)
{
    ((RHHumanVirtualCalls *)this)->V164();
    RHOrder *order = new RHOrder;
    int standing;
    int knocked;
    switch (RHActorField<int>(RHActorField<void *>(this, 0x50), 0x8c))
    {
    case 1: case 6: case 8: case 11: case 14: case 15:
    case 19: case 21: case 23: case 24:
        switch (RHActorField<unsigned>(this, 0x144))
        {
        default:
            standing = 0x28;
            knocked = 0x29;
            break;
        case 7: case 8: case 9: case 10: case 11: case 15:
            standing = 0x68;
            knocked = 0x69;
            break;
        case 4: case 5: case 6:
            standing = 0x6f;
            knocked = 0x70;
            break;
        }
        break;
    case 10: case 20: case 22:
        standing = 0x2a;
        knocked = 0x2b;
        break;
    case 3: case 7: case 9: case 16: case 17: case 18:
        if (((RHHumanVirtualCalls *)this)->V048() && !((RHHumanVirtualCalls *)this)->V0f4())
            ((RHHumanVirtualCalls *)this)->V044(12);
    case 12: case 13:
        if (((RHHumanVirtualCalls *)this)->V0f4() && ((RHHumanVirtualCalls *)this)->V048())
            knocked = 0x29;
        else
        {
            sequence->V0c(0, true);
            return;
        }
        break;
    case 4: case 5:
        FUN_004752d0(sequence);
        return;
    default:
        return;
    }
    if (((RHHumanVirtualCalls *)this)->V048())
        order->m_24 = knocked;
    else
        order->m_24 = standing;
    order->m_2a = 0;
    sequence->FUN_00585970(order);
    ((RHHumanVirtualCalls *)this)->V154(sequence);
}

// FUNCTION: GAME 0x00474ad0
void RHElementActorHuman::FUN_00474ad0(RHActorTranslationSequenceCalls *sequence)
{
    ((RHHumanVirtualCalls *)this)->V164();
    int concussed;
    int dead;
    int standing;
    switch (RHActorField<int>(RHActorField<void *>(this, 0x50), 0x8c))
    {
    case 1: case 6: case 8: case 11: case 14: case 15:
    case 19: case 21: case 23: case 24:
        switch (RHActorField<unsigned>(this, 0x144))
        {
        case 0: case 1: case 2: case 3: case 12: case 13: case 14: case 16: case 17:
            concussed = 0x2c; dead = 0x29; standing = 0x2c; break;
        case 7: case 8: case 9: case 10: case 11: case 15:
            concussed = 0x6b; dead = 0x69; standing = 0x66; break;
        case 4: case 5: case 6:
            concussed = 0x72; dead = 0x70; standing = concussed; break;
        default:
            return;
        }
        break;
    case 10: case 20: case 22:
        concussed = 0x2e; dead = 0x2b; standing = concussed; break;
    case 3: case 7: case 9: case 16: case 17: case 18:
        if (((RHHumanVirtualCalls *)this)->V048() && !((RHHumanVirtualCalls *)this)->V0f4())
            ((RHHumanVirtualCalls *)this)->V044(12);
    case 12: case 13:
        if (((RHHumanVirtualCalls *)this)->V0f4() && ((RHHumanVirtualCalls *)this)->V048())
            dead = 0x29;
        else
        {
            sequence->V0c(0, true);
            return;
        }
        break;
    case 4: case 5:
        FUN_004752d0(sequence);
        return;
    default:
        concussed = 0x2c; dead = 0x29; standing = concussed;
    }
    RHOrder *order;
    if (((RHHumanVirtualCalls *)this)->V048())
    {
        FUN_0047ca50();
        order = new RHOrder;
        order->m_24 = dead;
    }
    else if (!RHActorField<char>(this, 0x1ce))
    {
        order = new RHOrder;
        order->m_24 = standing;
    }
    else
    {
        FUN_0047ca50();
        order = new RHOrder;
        order->m_24 = concussed;
    }
    order->m_2a = 0;
    sequence->FUN_00585970(order);
    if (RHActorField<int>(sequence, 0x10) != 0x2c)
        ((RHHumanVirtualCalls *)this)->V154(sequence);
}

inline SBGeoPoint2D &RHHumanDoorPoint(void *area)
{
    return RHActorField<SBGeoPoint2D>(RHActorField<void *>(area, 0x100), 0x18);
}

inline RHActorAreaCalls *RHHumanDoorArea(void *area)
{
    return RHActorField<RHActorAreaCalls *>(RHActorField<void *>(area, 0x100), 0xc);
}

// FUNCTION: GAME 0x004752d0
void RHElementActorHuman::FUN_004752d0(RHActorTranslationSequenceCalls *sequence)
{
    ((RHHumanVirtualCalls *)this)->V164();
    void *area = RHActorField<void *>(RHActorField<void *>(this, 0x50), 0xe0);
    RHActorTranslationSequenceCalls *previous = RHActorField<RHActorTranslationSequenceCalls *>(sequence, 0x50);
    if (previous)
        previous->V0c(6, true);
    SBGeoPoint2D point(RHHumanDoorPoint(area));
    void *projection = RHHumanDoorArea(area)->FUN_0057d800(point);
    RHUnk00613e90 position;
    position.x = point.m_x;
    if (projection)
    {
        position.z = (point.m_x * RHActorField<float>(projection, 0xf4) +
            point.m_y * RHActorField<float>(projection, 0xf8) + RHActorField<float>(projection, 0xfc)) /
            (1.0f - RHActorField<float>(projection, 0xf8));
        position.y = point.m_y + position.z;
    }
    else
    {
        position.z = 0;
        position.y = point.m_y;
    }
    RHOrder *order = new RHOrder;
    order->m_24 = 0x12c;
    order->m_2a = 0;
    RHActorField<RHUnk00613e90>(order, 8) = position;
    sequence->FUN_00585970(order);
    ((RHActorAreaCalls *)area)->FUN_0057dfc0((RHElementActor *)this, false);
    ((RHActorAreaCalls *)area)->FUN_0057df20((RHElementActor *)this, false);
}

// FUNCTION: GAME 0x00475430
void RHElementActorHuman::GetTransitionFlags(RHSequenceElement *element, unsigned long &first, unsigned long &second, unsigned long &third)
{
    switch (*(int *)((char *)element + 0x10))
    {
    case 0xa0: case 0xa1:
        first = 0x1dff9; third = 4; break;
    case 0x1d: case 0x1f:
        first = 0x10099; second = 0x40001; third = 0x80; break;
    case 0x20:
        first = 0x89; second = 0x40001; break;
    case 0x21:
        first = 0x99; second = 0x40001; third = 0x10; break;
    case 0x22:
        first = 0x99; second = 0x40001; third = 8; break;
    case 0x24:
        first = 0x10089; second = 1; third = 8; break;
    case 0x23: case 0xb2:
        first = 0x10099; second = 0x44001; third = 8; break;
    case 0x34: case 0x35: case 0x37: case 0x38: case 0x39: case 0x3a:
    case 0x3b: case 0x3c: case 0x3d: case 0x3e: case 0x3f: case 0x40:
    case 0x41: case 0x42: case 0x43: case 0x44: case 0x46:
        first = 0x8a1; second = 1; third = 0x20; break;
    case 0x33: case 0x45:
        first = 0xa1; second = 1; third = 0x20; break;
    case 0x36:
        first = 0xe1; second = 1; third = 0x40; break;
    case 0x55:
        first = 0x81; second = 0x41; break;
    case 0x4b:
        first = 0x81; second = 1; break;
    case 0x56:
        first = 0x81; second = 1; break;
    case 0x6a:
        first = 0x281; second = 1; break;
    case 0xb0:
        first = 0x87; second = 1; break;
    case 0x6b:
        first = 0x281; second = 1; break;
    case 0x6c:
        first = 0x681; second = 1; third = 0x100; break;
    case 0x26: case 0x27: case 0x28: case 0x29: case 0x2a: case 0x2b:
    case 0x2c: case 0x47: case 0x4a:
        break;
    default:
        ((RHElementActor *)this)->GetTransitionFlags(element, first, second, third);
    }
}

// FUNCTION: GAME 0x00475750
bool RHElementActorHuman::FUN_00475750(unsigned flags, RHActorTranslationSequenceCalls *sequence)
{
    if (RHActorField<int>(RHActorField<void *>(this, 0x50), 0x8c) != 24)
        return ((RHElementActor *)this)->FUN_0046b2b0(flags, sequence);
    if ((flags & 1) && !(flags & 0x20000))
    {
        RHOrder *order = new RHOrder;
        order->m_24 = 0x10d;
        order->m_2a = 0;
        sequence->FUN_00585970(order);
        RHActorField<int>(sequence, 0x3c) = 1;
    }
    return true;
}

// Parked: the second switch duplicates the default state-store tail before its virtual-call cases.
#include "RHSoldierHumanCalls.h"

// STUB: GAME 0x00475970
bool RHElementActorHuman::FUN_00475970(unsigned flags, void *value)
{
    RHSoldierTransition *element = (RHSoldierTransition *)value;
    switch (*(int *)((char *)this + 0x144))
    {
    case 4:
        if ((flags & 1) && !(flags & 8))
        {
            ((RHHumanVirtualCalls *)this)->V078(element, 0x20);
            element->m_40 = 0;
        }
        return true;
    case 5:
    {
        unsigned char storedFlags = (unsigned char)flags;
        if ((storedFlags & 1) && !(storedFlags & 0x10))
        {
            ((RHHumanVirtualCalls *)this)->V078(element, 0x21);
            if (!(storedFlags & 8))
            {
                ((RHHumanVirtualCalls *)this)->V078(element, 0x20);
                element->m_40 = 0;
                return true;
            }
            element->m_40 = 4;
        }
        return true;
    }
    case 7: case 8: case 9:
        if (!(flags & 1) || (flags & 0x20))
            return true;
        ((RHHumanVirtualCalls *)this)->V078(element, 0x33);
        element->m_40 = 0;
        return true;
    case 10:
        if (!(flags & 0x40))
        {
            ((RHHumanVirtualCalls *)this)->V078(element, 0x36);
            element->m_40 = 7;
        }
        return true;
    case 11:
        return true;
    case 12: case 13: case 14:
        if (!(flags & 1) || (flags & 0x200))
            return true;
        ((RHHumanVirtualCalls *)this)->V078(element, 0x6b);
        element->m_40 = 0;
        return true;
    case 15:
        if ((flags & 1) && !(flags & 0x800))
        {
            ((RHHumanVirtualCalls *)this)->V078(element, 0x8b);
            element->m_40 = 0;
        }
        return true;
    case 16:
        if (!(flags & 1) || (flags & 0x1000))
            return true;
        ((RHHumanVirtualCalls *)this)->V078(element, 0x8e);
        element->m_40 = 0;
        return true;
    default:
        return ((RHElementActor *)this)->FUN_0046b4b0(flags, (RHActorTranslationSequenceCalls *)element);
    }
}

// STUB: GAME 0x00475b00
bool RHElementActorHuman::FUN_00475b00(unsigned flags, void *value)
{
    if (flags & 8)
    {
        switch (RHActorField<unsigned>(value, 0x40))
        {
        case 0:
            ((RHHumanVirtualCalls *)this)->V078(value, 29);
        case 4:
            RHActorField<unsigned>(value, 0x40) = 4;
            break;
        case 5:
            RHActorField<unsigned>(value, 0x40) = 5;
            break;
        case 6:
            RHActorField<unsigned>(value, 0x40) = 6;
            break;
        }
        return true;
    }
    if (flags & 16)
    {
        switch (RHActorField<unsigned>(value, 0x40))
        {
        case 0:
            ((RHHumanVirtualCalls *)this)->V078(value, 29);
        case 4: case 6:
            ((RHHumanVirtualCalls *)this)->V078(value, 34);
            break;
        }
        RHActorField<unsigned>(value, 0x40) = 5;
        return true;
    }
    if (flags & 128)
        return true;
    return ((RHElementActor *)this)->FUN_0046b760(flags, value);
}

struct RHHumanHeading
{
    char m_00[0xd8];
    unsigned m_heading : 4;
};


// FUNCTION: GAME 0x00479320
void RHHumanActorCalls::FUN_00479320(RHUnk00613e90 &point)
{
    point = RHActorField<RHUnk00613e90>(RHActorField<void *>(this, 0x50), 0x10);
    switch (RHActorField<int>(RHActorField<void *>(this, 0x50), 0x8c))
    {
    case 1: case 4: case 5: case 6: case 9: case 11: case 14: case 15:
    case 19: case 21: case 23: case 24:
    {
        bool alternate = ((RHHumanVirtualCalls *)this)->V0f4();
        float height = point.z;
        if (alternate)
            height += 30.0f;
        else
            height += 25.0f;
        point.z = height;
        break;
    }
    case 16:
    {
        float height = point.z;
        height += 65.0f;
        point.z = height;
        break;
    }
    case 7:
    {
        float height = point.z;
        height += 55.0f;
        point.z = height;
        break;
    }
    case 8: case 10: case 20: case 22:
    {
        float height = point.z;
        height += 10.0f;
        point.z = height;
        break;
    }
    case 3: case 12: case 13: case 17: case 18:
    {
        float height = point.z;
        height += 5.0f;
        point.z = height;
        break;
    }
    }
}

// FUNCTION: GAME 0x00479430
void RHHumanActorCalls::FUN_00479430(RHUnk00613e90 &point, float height)
{
    SBGeoPoint2D projected;
    {
        void *sprite = RHActorField<void *>(this, 0x50);
        const SBGeoVector2D &offset = SBGeoVector2D(*(SBGeoVector2D *)((RHUnk005b5e00 *)sprite)->Unk005bdd30(
            RHActorField<unsigned short>(sprite, 0x184)));
        projected = RHActorField<SBGeoPoint2D>(RHActorField<void *>(this, 0x50), 0x1c).Unk005fc190(offset);
    }
    float base = RHActorField<float>(RHActorField<void *>(this, 0x50), 0x18);
    point.x = projected.m_x;
    float y = base;
    y += projected.m_y;
    point.y = y;
    if (height >= 0.0f)
        point.z = base + height;
    else
    {
        switch (RHActorField<int>(RHActorField<void *>(this, 0x50), 0x8c))
        {
        case 1: case 4: case 5: case 6: case 9: case 11: case 14: case 15:
        case 21: case 23: case 24:
        {
            bool alternate = ((RHHumanVirtualCalls *)this)->V0f4();
            float z = base;
            if (alternate)
                z += 45.0f;
            else
                z += 25.0f;
            point.z = z;
            break;
        }
        case 19:
        {
            float z = base;
            z += 25.0f;
            point.z = z;
            break;
        }
        case 16:
        {
            float z = base;
            z += 65.0f;
            point.z = z;
            break;
        }
        case 7:
        {
            float z = point.z;
            z += 55.0f;
            point.z = z;
            break;
        }
        case 8: case 10: case 20: case 22:
        {
            float z = base;
            z += 10.0f;
            point.z = z;
            break;
        }
        case 3: case 12: case 13: case 17: case 18:
        {
            float z = base;
            z += 5.0f;
            point.z = z;
            break;
        }
        }
    }
}

SBGeoVector2D FUN_005fc580(const SBGeoVector2D &point, float factor);

// FUNCTION: GAME 0x00478960
void RHElementActor::FUN_00478960(RHUnk00613e90 &point)
{
    point = RHActorField<RHUnk00613e90>(RHActorField<void *>(this, 0x50), 0x10);
    switch (RHActorField<int>(RHActorField<void *>(this, 0x50), 0x8c))
    {
    case 1: case 4: case 5: case 6: case 9: case 11: case 14: case 15: case 21: case 23: case 24:
        if (((RHHumanVirtualCalls *)this)->V0f4())
        {
            float height = point.z;
            point.z = height + g_unk0x677554;
        }
        else
            point.z += 45.0f;
        break;
    case 19:
    {
        SBGeoVector2D offset = FUN_005fc580(((RHMalignityActorCalls *)this)->FUN_004135b0(), 40.0f);
        point.x += offset.m_x;
        point.y += offset.m_y;
        point.z += 45.0f;
        break;
    }
    case 16:
        point.z += 85.0f;
        break;
    case 7: case 8: case 10: case 20: case 22:
        point.z += 25.0f;
        break;
    case 3: case 12: case 13: case 17: case 18:
        point.z += 2.0f;
        break;
    }
}

// Residual: VC6 places the unscaled direction arm after the shared return tail.
// STUB: GAME 0x00478c20
void RHElementActor::FUN_00478c20(RHUnk00613e90 &point, int posture)
{
    point = RHActorField<RHUnk00613e90>(RHActorField<void *>(this, 0x50), 0x10);
    if (!posture)
        posture = RHActorField<int>(RHActorField<void *>(this, 0x50), 0x8c);
    switch (posture)
    {
    case 1: case 4: case 5: case 6: case 9: case 11: case 14: case 15: case 21: case 23: case 24:
        if (((RHHumanVirtualCalls *)this)->V0f4())
        {
            float height = point.z;
            point.z = height + g_unk0x677554;
            return;
        }
        point.z += 45.0f;
        return;
    case 16:
        point.z += 85.0f;
        return;
    case 8: case 10: case 20: case 22:
        point.z += 25.0f;
        return;
    case 3: case 12: case 13: case 17: case 18:
    {
        void *info = RHActorField<void *>(this, 0x50);
        short direction = RHActorField<short>(info, 0xd8);
        if (!RHActorField<unsigned char>(info, 0xc0))
        {
            point.x += g_unk0x006ae494[direction];
            point.y += g_unk0x006ae4d4[direction];
        }
        else
        {
            point.x += g_unk0x006ae494[direction] * 0.5f;
            point.y += g_unk0x006ae4d4[direction] * 0.5f;
        }
        point.z += 5.0f;
        return;
    }
    case 19:
    {
        SBGeoVector2D offset = FUN_005fc580(((RHMalignityActorCalls *)this)->FUN_004135b0(), 40.0f);
        point.x += offset.m_x;
        point.y += offset.m_y;
        point.z += 45.0f;
        break;
    }
    }
}

inline int RHHumanBowAnimation(int type)
{
    switch (type)
    {
    case 0:
        return 0x5d;
    case 1:
        return 0x5e;
    case 2:
        return 0xed;
    }
    return type;
}

// Residual: VC6 keeps the shoot type enregistered and rotates the frame-index registers.
// STUB: GAME 0x004795f0
void RHHumanActorCalls::FUN_004795f0(RHUnk00613e90 &point, int type, short direction)
{
    void *sprite = RHActorField<void *>(this, 0x50);
    float height = RHActorField<float>(sprite, 0x18);
    int animation = RHHumanBowAnimation(type);
    if (direction == -1)
        direction = RHActorField<short>(sprite, 0xd8);
    SBGeoPoint2D projected = RHActorField<SBGeoPoint2D>(RHActorField<void *>(this, 0x50), 0x1c).Unk005fc190(
        SBGeoVector2D(*(SBGeoVector2D *)((RHUnk005b5e00 *)sprite)->Unk005bdd30(
            RHActorField<short *>(((RHUnk005b5e00 *)sprite)->Unk(), 4)[animation] + direction)));
    point.x = projected.m_x;
    float y = height;
    y += projected.m_y;
    point.y = y;
    point.z = height;
    switch (type)
    {
    case 0:
        point.z += 40.0f;
        break;
    case 1:
        point.z += 50.0f;
        break;
    case 2:
    {
        SBGeoVector2D forward = FUN_005fc580(((RHMalignityActorCalls *)this)->FUN_004135b0(), 20.0f);
        point.x += forward.m_x;
        point.y += forward.m_y;
        point.z += 40.0f;
        break;
    }
    }
}

// FUNCTION: GAME 0x00478ae0
void RHElementActor::FUN_00478ae0(RHUnk00613e90 &point)
{
    point = RHActorField<RHUnk00613e90>(RHActorField<void *>(this, 0x50), 0x10);
    void *info = RHActorField<void *>(this, 0x50);
    switch (RHActorField<int>(info, 0x8c))
    {
    case 1: case 4: case 5: case 6: case 9: case 11: case 14: case 15: case 19: case 21: case 23: case 24:
    {
        if (((RHHumanVirtualCalls *)this)->V0f4())
        {
            float height = point.z;
            point.z = height + 5.0f;
        }
        else
        {
            float height = point.z;
            point.z = height + 5.0f;
        }
        break;
    }
    case 7: case 16:
    {
        float height = point.z;
        point.z = height + 45.0f;
        break;
    }
    case 3: case 12: case 13: case 17: case 18:
    {
        short direction = RHActorField<short>(info, 0xd8);
        if (RHActorField<unsigned char>(info, 0xc0))
        {
            float x = g_unk0x006ae494[direction];
            point.x -= x * 0.5f;
            float y = g_unk0x006ae4d4[direction];
            point.y -= y * 0.5f;
            float height = point.z;
            point.z = height + 5.0f;
            break;
        }
        point.x -= g_unk0x006ae494[direction];
        point.y -= g_unk0x006ae4d4[direction];
    }
    case 8: case 10: case 20: case 22:
    {
        float height = point.z;
        point.z = height + 5.0f;
    }
    }
}

// FUNCTION: GAME 0x00479920
void RHElementActorHuman::FUN_00479920(RHElementActorHuman *actor)
{
    if (actor)
    {
        m_254 = actor;
        RHActorField<char>(this, 0x110) = 0;
        return;
    }
    if (m_254)
    {
        RHActorField<unsigned short>(RHActorField<void *>(this, 0x50), 0xda) =
            RHActorField<RHHumanHeading *>(m_254, 0x50)->m_heading;
        m_254 = 0;
    }
}

#include "RHEngineSerializationCalls.h"

class RHElementNet
{
public:
    void FUN_004b1270();
};

class RHHumanTypeView
{
public:
    unsigned Type() const { return RHActorField<volatile unsigned>((void *)this, 4) & 15; }
};

// FUNCTION: GAME 0x00479970
void RHElementActorHuman::FUN_00479970(RHSequenceElement *element)
{
    if (element->m_10 == 0x54)
    {
        void *value = RHActorField<void *>(element, 0x64);
        if (RHActorField<int>(value, 0xb0) == 9 && RHActorField<char>(value, 0x12))
        {
            ((RHEngineSerializationCalls *)g_pEngine)->FUN_004d88e0(value, 0, 1);
            ((RHElementNet *)value)->FUN_004b1270();
            if (((RHHumanTypeView *)this)->Type() == 12)
                ((RHHumanVirtualCalls *)this)->V0e8(17, true);
        }
    }
    ((RHElementActor *)this)->FUN_0046bd40(element);
}

// FUNCTION: GAME 0x0047a870
void RHElementActorHuman::FUN_0047a870(void *value)
{
    FUN_0046e2e0(value);
}

// FUNCTION: GAME 0x0047a880
void RHElementActorHuman::FUN_0047a880(RHSequenceElement *element)
{
    ((RHElementActor *)this)->ExecuteImmediately(element);
}

// FUNCTION: GAME 0x0047a890
float RHElementActorHuman::FUN_0047a890()
{
    float value = ((RHSprite *)(*(void **)((char *)this + 0x50)))->FUN_005bdcb0();
    return value;
}
// FUNCTION: GAME 0x0047ac60
unsigned char RHElementActorHuman::FUN_0047ac60()
{
    void *value = *(void **)((char *)this + 0x134);
    if (value == 0)
        goto done;
    switch (*(int *)((char *)value + 0x24))
    {
    case 0x30:
    case 0x6c:
    case 0x73:
        return 1;
    }
done:
    return 0;
}

// FUNCTION: GAME 0x0047a8a0
void RHElementActorHuman::FUN_0047a8a0()
{
    unsigned &remaining = *(unsigned *)((char *)this + 0x480);
    unsigned &duration = *(unsigned *)((char *)this + 0x484);
    unsigned short &frame = *(unsigned short *)((char *)this + 0x488);
    unsigned char &completed = *(unsigned char *)((char *)this + 0x48a);
    float &progress = *(float *)((char *)this + 0x48c);

    if (remaining > 0)
    {
        --remaining;
        if (remaining > 0)
        {
            if (completed)
                frame = (unsigned short)((int)((float)remaining * g_unk0x677554 / (float)duration) + 0x28);
            else
                frame = (unsigned short)((int)(((float)duration - (float)remaining) * g_unk0x677554 / (float)duration) + 0x28);
        }
        else
        {
            completed = 1;
            progress = 1.0f;
        }
    }
}

// FUNCTION: GAME 0x0047ab00
void RHElementActorHuman::FUN_0047ab00(int first, int second)
{
    *(RHUnkHumanPlacementA **)((char *)this + 0x25c) = new RHUnkHumanPlacementA(first);

    if (second != -1)
    {
        *(RHUnkHumanPlacementB **)((char *)this + 0x258) = new RHUnkHumanPlacementB(second);
    }
}

struct RHHumanPositionRangeArray
{
    unsigned allocator;
    RHUnkHumanPositionRange **first;
    RHUnkHumanPositionRange **last;
    unsigned Size() const
    {
        if (!first)
            return 0;
        return last - first;
    }
    RHUnkHumanPositionRange *At(unsigned short index) { return first[index]; }
};

// FUNCTION: GAME 0x0047aba0
void RHElementActorHuman::FUN_0047aba0()
{
    if (*(unsigned char *)((char *)this + 0x110) != 0)
        return;

    RHHumanPositionRangeArray &ranges = RHActorField<RHHumanPositionRangeArray>(g_unk0x6c0a9c, 0x4080);
    RHUnk00571160Position position;
    ((RHUnk00560420 *)(*(char **)((char *)this + 0x50) + 4))->Unk(&position);
    unsigned short count = (unsigned short)ranges.Size();
    for (unsigned short index = 0; index < count; ++index)
    {
        RHUnkHumanPositionRange *entry = ranges.At(index);
        if (*(int *)((char *)entry + 4) == 1 &&
            entry->FUN_0051afe0(position))
        {
            *(unsigned char *)((char *)this + 0x110) = 1;
            return;
        }
    }

    *(unsigned char *)((char *)this + 0x110) = 0;
}

void RHHumanNotificationPrepare(void *) {}
void RHHumanNotificationAdvance(void *, int, void *, int) {}
void RHHumanNotificationAppend(void *, unsigned short, unsigned short, void *, int) {}
bool RHHumanNotificationCompose(void *, void *, void *, void *) { return false; }
void RHHumanNotificationEmit(void *, void *, int, void *, unsigned short, int) {}

// Parked: notification geometry, helper receivers and temporary destruction remain unresolved.
// STUB: GAME 0x0047a960
void RHElementActorHuman::FUN_0047a960(void *first, void *second, char force)
{
    int remaining = *(int *)((char *)this + 0x480);
    if (remaining == 0 && force == 0)
        return;

    struct NotificationState
    {
        void *source;
        unsigned char flags[8];
        unsigned short frame;
        unsigned short value;
    } state;

    state.source = *(void **)((char *)this + 0x54);
    state.frame = *(unsigned short *)((char *)this + 0x98);
    state.value = 4;
    for (unsigned index = 0; index < sizeof(state.flags); ++index)
        state.flags[index] = 0;
    state.flags[4] = 1;

    RHHumanNotificationPrepare(&state);
    void *channels = *(void **)((char *)this + 0x58);
    RHHumanNotificationAdvance(channels, 0, channels, 0);
    RHHumanNotificationAppend(channels, *(unsigned short *)((char *)this + 0x94),
        *(unsigned short *)((char *)this + 0xa4), &state, 1);
    if (RHHumanNotificationCompose(first, second, &state, &state))
        RHHumanNotificationEmit(channels, &state, 0, &state, force ? 100 :
        *(unsigned short *)((char *)this + 0x488), 1);
}

static bool RHHumanVirtualResult(void *object, unsigned offset)
{
    void **vtable = *(void ***)object;
    typedef int (__fastcall *Method)(void *);
    return ((Method)vtable[offset / 4])(object) != 0;
}

static float RHHumanDistanceSquared(void *first, void *second)
{
    char *firstProfile = *(char **)((char *)first + 0x50);
    char *secondProfile = *(char **)((char *)second + 0x50);
    float *a = (float *)(firstProfile + 0x24);
    float *b = (float *)(secondProfile + 0x24);
    float x = a[0] - b[0];
    float y = a[1] - b[1];
    float z = a[2] - b[2];
    return x * x + y * y + z * z;
}

// Parked: action-specific filters, geometry construction and exception cleanup remain approximate.
// STUB: GAME 0x0047ac90
bool RHElementActorHuman::FUN_0047ac90(void *element, bool checkRange)
{
    unsigned action = *(unsigned *)((char *)element + 0x10);
    void *other = *(void **)((char *)element + 0x64);

    switch (action)
    {
    case 0x23:
    case 0xb2:
        if (other == 0 || RHHumanVirtualResult(other, 0x130) == false ||
            RHHumanVirtualResult(other, 0xf8) || RHHumanVirtualResult(other, 0xf4) ||
            RHHumanVirtualResult(this, 0x168))
            return false;
        return !checkRange || RHHumanDistanceSquared(this, other) <= 2025.0f;
    case 0x32:
        if (other != 0 && RHHumanVirtualResult(other, 0xf4) &&
            *(int *)((char *)other + 0x144) == 3)
            return false;
        return other != 0;
    case 0x33:
    case 0x34:
    case 0x6a:
    case 0xb0:
        return true;
    case 0x45:
        if (other == 0 || RHHumanVirtualResult(other, 0x48) ||
            *(unsigned char *)((char *)other + 0x1ce) == 0)
            return false;
        return !checkRange || RHHumanDistanceSquared(this, other) <= 2025.0f;
    case 0x4b:
        return !checkRange || other == 0 ||
            RHHumanDistanceSquared(this, other) <= 20.0f;
    case 0x54:
        if (other == 0)
            return false;
        switch (*(int *)((char *)other + 0xb0))
        {
        case 7:
            return *(unsigned char *)((char *)other + 0xfd) == 0 &&
                (!checkRange || RHHumanDistanceSquared(this, other) <= 900.0f);
        case 9:
            return *(unsigned char *)((char *)other + 0x12) != 0 &&
                (!checkRange || RHHumanDistanceSquared(this, other) <= 4900.0f);
        case 12:
            return *(unsigned char *)((char *)other + 0x12) != 0 &&
                (!checkRange || RHHumanDistanceSquared(this, other) <= 900.0f);
        default:
            return *(unsigned char *)((char *)other + 0x12) != 0 &&
                (!checkRange || RHHumanDistanceSquared(this, other) <= 900.0f);
        }
    case 0x55:
        return other != 0 && *(unsigned char *)((char *)other + 8) == 0 &&
            *(unsigned char *)((char *)other + 0x12) != 0 &&
            (!checkRange || RHHumanDistanceSquared(this, other) < 1600.0f);
    case 0x56:
    case 0x73:
        if (other == 0 || RHHumanVirtualResult(other, 0x130) == false ||
            RHHumanVirtualResult(other, 0xf8) || RHHumanVirtualResult(other, 0xf4))
            return false;
        return !checkRange || RHHumanDistanceSquared(this, other) <= 1600.0f;
    default:
        return false;
    }
}

struct RHUnk0047c420Message
{
    void *m_00;
    undefined m_04[0x18];
    int m_1c;
    int m_20;
    int m_24;
    undefined m_28;
    RHUnk0047c420Message() : m_24(0), m_28(0) {}
    ~RHUnk0047c420Message() {}
};

DECOMP_SIZE_ASSERT(RHUnk0047c420Message, 0x2c)

// STUB: GAME 0x00474d60
void RHElementActorHuman::FUN_00474d60(RHActorTranslationSequenceCalls *sequence, unsigned flags)
{
    if (flags == 4)
    {
        int weapon = RHActorField<int>(this, 0x144);
        if (weapon == 10 || weapon == 11)
            return;
        RHOrder *order = new RHOrder;
        order->m_24 = 0x4e;
        order->m_2a = 0;
        sequence->FUN_00585970(order);
        return;
    }
    int first;
    int second;
    int third;
    int fourth;
    ((RHHumanVirtualCalls *)this)->V164();
    switch (RHActorField<int>(RHActorField<void *>(this, 0x50), 0x8c))
    {
    case 1: case 6: case 8: case 11: case 14: case 15:
    case 19: case 21: case 23: case 24:
        switch (RHActorField<unsigned>(this, 0x144))
        {
        case 4: case 5: case 6:
            first = 0x70; second = 0x72; third = 0x75; fourth = 0x72;
            break;
        case 7: case 8: case 9: case 10: case 11: case 15:
            first = 0x69; second = 0x6b; third = 0x6e; fourth = 0x66;
            break;
        default:
            first = 0x29; second = 0x2c; third = 0x31; fourth = 0x2c;
            break;
        }
        break;
    case 10: case 20: case 22:
        first = 0x2b; second = 0x2e; third = 0x31; fourth = 0x2e;
        break;
    case 3: case 7: case 9: case 16: case 17: case 18:
        if (((RHHumanVirtualCalls *)this)->V048() && !((RHHumanVirtualCalls *)this)->V0f4())
            ((RHHumanVirtualCalls *)this)->V044(12);
    case 12: case 13:
        if (!((RHHumanVirtualCalls *)this)->V0f4() || (short)((RHHumanVirtualCalls *)this)->V0cc() > 0)
        {
            sequence->V0c(0, true);
            return;
        }
        first = 0x29;
        second = 0x29;
        break;
    case 4: case 5:
        FUN_004752d0(sequence);
        return;
    default:
        return;
    }
    if (((RHHumanVirtualCalls *)this)->V048())
    {
        FUN_0047ca50();
        if ((unsigned char)(RHActorField<unsigned>((void *)((RHUnk005864a0 *)sequence)->FUN_005864a0(), 4) & 0x1f) == 0x14)
        {
            void *actor = (void *)((RHUnk005864a0 *)sequence)->FUN_005864a0();
            RHUnk0047c420Message message;
            message.m_20 = 0x42;
            *(unsigned short *)&message.m_00 = 0;
            message.m_1c = 0;
            ((RHHumanVirtualCalls *)((char *)actor + 0x6e8 + RHActorField<int *>(actor, 0x6e8)[1]))->V024(&message);
        }
        if (!((RHHumanVirtualCalls *)this)->V0f4() &&
            ((RHHumanWeaponCalls *)((RHUnk005864a0 *)sequence)->FUN_005864b0())->FUN_005c1db0(((RHUnk005864a0 *)sequence)->FUN_005864d0()) != 0)
        {
            RHOrder *order = new RHOrder;
            order->m_24 = second;
            order->m_2a = 0;
            sequence->FUN_00585970(order);
        }
        else
        {
            RHOrder *order = new RHOrder;
            order->m_24 = first;
            order->m_2a = 0;
            sequence->FUN_00585970(order);
        }
        ((RHHumanVirtualCalls *)this)->V154(sequence);
    }
    else
    {
        if ((flags & 1) && (unsigned char)(RHActorField<unsigned>((void *)((RHUnk005864a0 *)sequence)->FUN_005864a0(), 4) & 0x1f) == 0x14)
        {
            void *actor = (void *)((RHUnk005864a0 *)sequence)->FUN_005864a0();
            RHUnk0047c420Message message;
            message.m_20 = 0x41;
            *(unsigned short *)&message.m_00 = 0;
            message.m_1c = 0;
            ((RHHumanVirtualCalls *)((char *)actor + 0x6e8 + RHActorField<int *>(actor, 0x6e8)[1]))->V024(&message);
        }
        if (RHActorField<char>(this, 0x1ce))
        {
            FUN_0047ca50();
            RHOrder *order = new RHOrder;
            order->m_24 = second;
            order->m_2a = 0;
            sequence->FUN_00585970(order);
            ((RHHumanVirtualCalls *)this)->V154(sequence);
        }
        else if (flags & 2)
        {
            RHOrder *order = new RHOrder;
            order->m_24 = second;
            order->m_2a = 0;
            sequence->FUN_00585970(order);
            ((RHHumanVirtualCalls *)this)->V154(sequence);
        }
        else if (flags & 1)
        {
            RHOrder *order = new RHOrder;
            order->m_24 = fourth;
            order->m_2a = 0;
            sequence->FUN_00585970(order);
        }
    }
    if (!((RHHumanVirtualCalls *)this)->V048() && !RHActorField<char>(this, 0x1ce) && (flags & 2))
    {
        RHOrder *order = new RHOrder;
        order->m_24 = third;
        order->m_2a = 0;
        sequence->FUN_00585970(order);
        if (RHActorField<void *>(this, 0x268) && RHActorField<unsigned short>(this, 0x1c8) > 40)
        {
            order = new RHOrder;
            order->m_24 = 0x67;
            order->m_2a = 0;
            sequence->FUN_00585970(order);
        }
    }
}

#include "RHMalignityGeometryCalls.h"

class RHHumanAddressCalls
{
public:
    unsigned short WeaponShort(void *target);
    float WeaponFloat(void *target);
    bool ActorFlag(int flag);
    bool IsVisible();
    void *Fallback(void *target);
    int Fallback3(void *first, void *second, void *third);
    void Queue(int command, int first, int second);
    bool Spawn(int first, int second, int third, int fourth, int fifth, int sixth);
};

// FUNCTION: GAME 0x004820e0
unsigned FUN_004820e0(unsigned value)
{
    switch (value)
    {
    case 0x43: return 0;
    case 0x44: return 1;
    case 0x4b: return 2;
    case 0x46: return 3;
    case 0x45: return 4;
    case 0x4a: return 5;
    case 0x49: return 6;
    case 0x48: return 7;
    case 0x47: return 8;
    default: return 0xb;
    }
}

unsigned short RHHumanWeaponCalls::FUN_005c1b50(int)
{
    return 0;
}

unsigned short RHHumanWeaponCalls::FUN_005c1d50(int)
{
    return 0;
}

bool RHUnkHumanPositionProvider::FUN_005b8240(void *, void *)
{
    return false;
}

int RHUnkHumanPositionProvider::FUN_005b8050(void *, void *, int, int)
{
    return 0;
}

void RHUnkHumanPositionProvider::FUN_005bd450() {}

void *RHUnkHumanPositionProvider::FUN_005b5e00()
{
    return 0;
}


// FUNCTION: GAME 0x005fcdb0
unsigned char FUN_005fcdb0(float value)
{
    if (value >= 0.0f)
        return (int)(value * 2.546479018608091) & 0xf;
    return 0xf - FUN_005fcdb0(-value);
}

double FUN_005fcdf0(unsigned short value);

// FUNCTION: GAME 0x0047f4f0
void RHElementActorHuman::FUN_0047f4f0(void *)
{
    FUN_0047ca50();
    g_unk0x6c10e8->Unk(this);
    *(char *)((char *)this + 0x1ce) = 0;
    *(unsigned short *)((char *)this + 0x1c8) = 0;
}

class RHMalignityAbilityCalls
{
public:
    unsigned short FUN_005c1b50(int index);
    int FUN_005c2130(float value, int first, int second);
};

// Parked: opponent-front and position-copy register scheduling remain different.
// STUB: GAME 0x0047f420
bool RHElementActorHuman::FUN_0047f420()
{
    RHElementActorHuman *other;
    if (m_260.count != 0)
        other = (RHElementActorHuman *)m_260.head->next->data;
    else
        other = 0;
    RHUnk00613e90 otherPosition = RHActorField<RHUnk00613e90>(RHActorField<void *>(other, 0x50), 0x10);
    RHUnk00613e90 &ourPosition = RHActorField<RHUnk00613e90>(RHActorField<void *>(this, 0x50), 0x10);
    float x = otherPosition.x - ourPosition.x;
    float y = otherPosition.y - ourPosition.y;
    float z = otherPosition.z - ourPosition.z;
    float distance = (float)sqrt((z * z + x * x) + y * y);
    if (RHActorField<RHMalignityAbilityCalls *>(this, 0x25c)->FUN_005c1b50(2) < distance &&
        RHActorField<RHMalignityAbilityCalls *>(other, 0x25c)->FUN_005c1b50(2) > distance)
        return true;
    return false;
}

// Parked: argument reload scheduling and duplicate angle-result return blocks remain different.
// STUB: GAME 0x00480e90
int RHElementActorHuman::FUN_00480e90(void *first, void *second, int weaponData)
{
    int kind = RHActorField<RHUnk005c1d50 *>(this, 0x25c)->FUN_005c1d50(weaponData);
    int direction = RHActorField<RHHumanWeaponCalls *>(this, 0x25c)->FUN_005c1d70(weaponData);
    int result;
    switch (kind)
    {
    case 3:
    case 4:
        result = FUN_00481050(first, *(void *volatile *)&second, weaponData);
        break;
    case 5:
    case 6:
        result = RHActorField<RHSprite *>(this, 0x50)->PerformAction((RHOrder *)first, (int)*(void *volatile *)&second, 0, false);
        break;
    default:
        result = (int)second;
        break;
    }
    switch (kind)
    {
    case 3:
    case 5:
        FUN_0047faf0(result, weaponData);
        break;
    case 4:
    case 6:
        FUN_0047f520(result, weaponData);
        break;
    }
    if (((RHUnkHumanPositionProvider *)RHActorField<void *>(this, 0x50))->FUN_005b8240(first, second) == true &&
        ((direction == 0 && m_234 < m_238) || (direction == 1 && m_234 > m_238)))
    {
        float candidate = m_234;
        float step;
        if (direction == 1)
            step = -RHActorField<RHHumanWeaponCalls *>(this, 0x25c)->FUN_005c1f50(weaponData);
        else
            step = RHActorField<RHHumanWeaponCalls *>(this, 0x25c)->FUN_005c1f50(weaponData);
        candidate += step;
        unsigned char candidateAngle = FUN_005fcdb0(candidate);
        unsigned char maximumAngle = FUN_005fcdb0(m_238);
        if ((direction == 0 && candidate < m_238) || (direction == 1 && candidate > m_238) ||
            candidateAngle == maximumAngle)
            m_234 = candidate;
        else
            m_234 = m_238;
    }
    return result;
}

#include "RHEngineWidenedCalls.h"

// FUNCTION: GAME 0x00481050
int RHElementActorHuman::FUN_00481050(void *first, void *second, int weaponData)
{
    if (!((RHUnkHumanPositionProvider *)RHActorField<void *>(this, 0x50))->FUN_005b8240(first, second))
        return RHActorField<RHSprite *>(this, 0x50)->PerformAction((RHOrder *)first, (int)second, 0, false);
    int direction = RHActorField<RHHumanWeaponCalls *>(this, 0x25c)->FUN_005c1d70(weaponData);
    unsigned short heading = FUN_005fcdb0(m_234);
    char *sprite = (char *)RHActorField<void *>(this, 0x50) + 4;
    *(unsigned short *)(sprite + 0xd4) = heading & 0xf;
    *(unsigned short *)(sprite + 0xd6) = heading & 0xf;
    void *position = RHActorField<void *>(this, 0x50);
    ((RHEngineWidenedCalls *)position)->FUN_005bd450();
    unsigned index = RHActorField<unsigned>(position, 0x1dc);
    void *table = ((RHUnk005b5e00 *)position)->Unk();
    RHActorField<unsigned short>(position, 0x184) = RHActorField<unsigned short *>(table, 4)[index] + heading;
    if ((direction == 0 && m_234 >= m_238) || (direction == 1 && m_234 <= m_238))
        return RHActorField<RHSprite *>(this, 0x50)->PerformAction((RHOrder *)first, (int)second, 0, false);
    return 2;
}

#include "RHSoldierHumanCalls.h"

// Parked: opponent-query registers, loop lowering, and masked-flag load widths differ.
// STUB: GAME 0x00481d40
int RHElementActorHuman::FUN_00481d40(void *first, void *second)
{
    struct Kind5 { unsigned value : 5; };
    if (RHActorField<char>(this, 0x148))
    {
        RHUnk005c38b0 *context = g_unk0x6c10e8;
        RHUnk00613e90 point;
        ((RHSoldierHumanCalls *)this)->FUN_00478e50(point);
        typedef void (RHScriptBatchCalls::*Effect)(void *, unsigned short, int, void *, int, int, int, int);
        (((RHScriptBatchCalls *)context)->*(Effect)&RHScriptBatchCalls::Unk005c2ec0)(&point,
            RHActorField<unsigned short>(RHActorField<void *>(this, 0x50), 0xde),
            2, this, 0, 0, 0, -1);
        m_288 = 0;
        if (*(volatile unsigned *)&m_260.count != 0)
        {
            RHScriptNode *node = m_260.head->next;
            RHElementActorHuman *other = (RHElementActorHuman *)node->data;
            if (other && (other->m_260.count ? other->m_260.head->next->data : 0) == this)
            {
                RHElementActorHuman *opponent = (RHElementActorHuman *)node->data;
                opponent->m_288 = 1;
                opponent->m_289 = 1;
            }
        }
        unsigned count = m_260.count;
        if ((unsigned short)count > 0)
        {
            count &= 0xffff;
            RHHumanList &opponents = m_260;
            for (int index = 0; count != 0; ++index, --count)
            {
                ((RHTitbitList *)&opponents)->At(index);
                void *actor = opponents.cursor->data;
                if (((Kind5 *)((char *)actor + 4))->value == 0x14)
                {
                    void *script = (char *)actor + 0x6e8;
                    ((RHScriptBatchCalls *)((char *)script + RHActorField<int *>(script, 0)[1]))->Unk0040d980(0x38);
                }
            }
        }
    }
    int result;
    short &delay = *(short *)((char *)this + 0x1cc);
    if (!((RHUnkHumanPositionProvider *)RHActorField<void *>(this, 0x50))->FUN_005b8240(first, second))
    {
        result = ((RHSprite *)RHActorField<void *>(this, 0x50))->PerformAction((RHOrder *)first, (int)second, 0, false);
        delay = delay - 5 > 0 ? delay - 5 : 0;
    }
    else
    {
        delay = delay - 5 > 0 ? delay - 5 : 0;
        if (delay == 0)
            result = ((RHSprite *)RHActorField<void *>(this, 0x50))->PerformAction((RHOrder *)first, (int)second, 0, false);
        else
            goto waiting;
    }
    if (result == 3 && ((Kind5 *)((char *)this + 4))->value == 0x14)
    {
        void *script = (char *)this + 0x6e8;
        ((RHScriptBatchCalls *)((char *)script + RHActorField<int *>(script, 0)[1]))->Unk0040d980(0x39);
    }
    return result;
waiting:
    return 2;
}

#include "RHSequenceTimedCalls.h"

class RHUnk004237d0
{
public:
    SBGeoPoint2D FUN_004237d0();
};

class RHPositionInterface
{
public:
    bool Turn();
};

class RHUnk6c1040;
extern RHUnk6c1040 *g_unk0x6c1040;

static inline void RHHumanSetTargetHeading(void *position, unsigned short heading)
{
    RHActorField<unsigned short>(position, 0xd6) = heading & 0xf;
}

// FUNCTION: GAME 0x00481ef0
int RHElementActorHuman::FUN_00481ef0(RHOrder *order, int animation, int weaponData)
{
    RHHumanSetTargetHeading((char *)RHActorField<void *>(this, 0x50) + 4,
        ((RHUnk005fc3b0 *)&((RHUnk004237d0 *)RHActorField<void *>(order, 0x30))->FUN_004237d0().Unk005fc110(
            ((RHUnk004237d0 *)this)->FUN_004237d0()))->FUN_005fcc50(0.57357645f));
    ((RHPositionInterface *)((char *)RHActorField<void *>(this, 0x50) + 4))->Turn();
    int result = RHActorField<RHSprite *>(this, 0x50)->PerformAction(order, animation, 0, false);
    if (result == 0)
    {
        RHUnk00613e90 delta;
        delta = RHActorField<RHUnk00613e90>(RHActorField<void *>(this, 0x50), 0x10);
        RHUnk00613e90 &target = RHActorField<RHUnk00613e90>(RHActorField<void *>(RHActorField<void *>(order, 0x30), 0x50), 0x10);
        delta.x -= target.x;
        delta.y -= target.y;
        delta.z -= target.z;
        float distance = (float)sqrt((delta.z * delta.z + delta.y * delta.y) + delta.x * delta.x);
        if (RHActorField<RHHumanWeaponCalls *>(this, 0x25c)->FUN_005c1e80(weaponData) <= distance &&
            RHActorField<RHHumanWeaponCalls *>(this, 0x25c)->FUN_005c1ea0(weaponData) >= distance)
        {
            RHUnk005861c0 *element = new RHUnk005861c0(1, 0x27, RHActorField<void *>(order, 0x30), this,
                RHActorField<RHSword *>(this, 0x25c), weaponData);
            ((RHScriptBatchCalls *)g_unk0x6c1040)->Unk0058a940("", 0, element);
        }
    }
    return result;
}

// Parked: target filtering, iterator-cache mutations, and EH cleanup differ.
// STUB: GAME 0x0047f520
void RHElementActorHuman::FUN_0047f520(int mode, int weaponData)
{
    RHHumanWeaponCalls *weapon =
        (RHHumanWeaponCalls *)RHActorField<void *>(this, 0x25c);
    if (mode == 0)
    {
        unsigned short direction = weapon->FUN_005c1d70(weaponData);
        float heading = FUN_005fcdf0(
            RHActorField<unsigned short>(RHActorField<void *>(this, 0x50), 0xd8));
        m_234 = heading;
        m_230 = heading + (direction == 1 ? weapon->FUN_005c1ed0(weaponData) :
                                             -weapon->FUN_005c1ed0(weaponData));
        m_238 = m_234 + (direction == 1 ? -6.2831855f : 6.2831855f);
        FUN_00482390(&m_20c, weaponData, true);
        return;
    }
    if (mode == 2)
    {
        if (m_20c.count > 0)
            FUN_00482600(&m_20c, weaponData);
        return;
    }
    if (mode == 3)
        m_20c.Clear();
}

// Parked: its cached range setup and actor-notification path remain approximate.
// STUB: GAME 0x0047faf0
void RHElementActorHuman::FUN_0047faf0(int mode, int weaponData)
{
    RHHumanWeaponCalls *weapon =
        (RHHumanWeaponCalls *)RHActorField<void *>(this, 0x25c);
    if (mode == 0)
    {
        unsigned short direction = weapon->FUN_005c1d70(weaponData);
        float heading = FUN_005fcdf0(
            RHActorField<unsigned short>(RHActorField<void *>(this, 0x50), 0xd8));
        m_234 = heading;
        m_230 = direction == 1 ? heading + weapon->FUN_005c1ed0(weaponData) :
                                 heading - weapon->FUN_005c1ed0(weaponData);
        m_238 = direction == 1 ? m_230 - 3.1415927f : m_230 + 3.1415927f;
        FUN_00482600(&m_20c, weaponData);
        return;
    }
    if (mode == 2)
    {
        FUN_00482390(&m_20c, weaponData, false);
        return;
    }
    if (mode == 3)
        m_20c.Clear();
}

// Parked: the source's grid response and paired angle-bound update differ.
// STUB: GAME 0x004801d0
int RHElementActorHuman::FUN_004801d0(void *first, void *second, int weaponData)
{
    RHUnkHumanPositionProvider *position =
        (RHUnkHumanPositionProvider *)RHActorField<void *>(this, 0x50);
    int result = position->FUN_005b8050(first, second, 0, 0);
    if (result != 0)
        return result;
    unsigned short direction =
        ((RHHumanWeaponCalls *)RHActorField<void *>(this, 0x25c))->FUN_005c1d70(weaponData);
    if (direction > 1)
        return 0;
    FUN_0047faf0(result, weaponData);
    return result;
}

// Parked: its multi-range geometry query and object-lifetime schedule differ.
// STUB: GAME 0x004808f0
int RHElementActorHuman::FUN_004808f0(void *first, void *second, int weaponData)
{
    int result = FUN_00480e90(first, second, weaponData);
    if (result != 0)
        return result;
    RHHumanWeaponCalls *weapon =
        (RHHumanWeaponCalls *)RHActorField<void *>(this, 0x25c);
    unsigned short low = weapon->FUN_005c1e80(weaponData);
    unsigned short high = weapon->FUN_005c1ea0(weaponData);
    for (unsigned short index = 0; index < m_20c.count; ++index)
    {
        RHElementActorHuman *candidate =
            (RHElementActorHuman *)RHHumanAt(m_20c, index);
        if (candidate && FUN_00483070(candidate) && low <= high)
            ((RHScriptBatchCalls *)candidate)->Unk0040d980(0x32);
    }
    return result;
}

// Parked: the polygon construction and per-opponent attack event remain approximate.
// STUB: GAME 0x00481150
int RHElementActorHuman::FUN_00481150(int weaponData)
{
    if (RHActorField<char>(this, 0x148))
    {
        FUN_00482390(&m_20c, weaponData, true);
        FUN_00482600(&m_20c, weaponData);
    }
    unsigned short count = m_20c.count;
    for (unsigned short index = 0; index < count; ++index)
    {
        RHElementActorHuman *candidate =
            (RHElementActorHuman *)RHHumanAt(m_20c, index);
        if (candidate && FUN_00483070(candidate))
            FUN_00483160(this, candidate, 16);
    }
    return FUN_00480e90(this, this, weaponData);
}


// Parked: propagation register lifetimes and EH scheduling differ.
// STUB: GAME 0x0044d400
void RHUnk0044d400::FUN_0044d400(int value, bool propagate)
{
    bool shared;
    switch (value)
    {
    case 59: case 60: case 61: case 62: case 63: case 64: case 65:
        shared = false;
        break;
    case 66: case 67:
        shared = true;
        break;
    default:
        return;
    }
    if (propagate && shared)
    {
        int offset = ((RHHumanVirtualCalls *)Actor())->V130() << 5;
        void **first = RHActorField<void **>(g_pEngine, offset + 0x4ccc);
        unsigned short count = first ? RHActorField<void **>(g_pEngine, offset + 0x4cd0) - first : 0;
        SBGeoVector2D radius(400.0f, 400.0f);
        SBGeoPoint2D center(RHActorField<SBGeoPoint2D>(RHActorField<void *>(Actor(), 0x50), 0x24));
        SBGeoBoundingBox2D box(center.FUN_005fc200(radius), center.Unk005fc190(radius));
        for (unsigned short i = 0; i < count; ++i)
        {
            void *actor = RHActorField<void **>(g_pEngine, offset + 0x4ccc)[i];
            if (actor != Actor() && (RHActorField<unsigned>(actor, 4) & 31) == 20)
            {
                int *base = RHActorField<int *>(actor, 0x49c);
                if (RHActorField<int>(actor, base[1] + 0x4a8) == 4 &&
                    ((RHHumanVirtualCalls *)actor)->V124() >= 70 &&
                    box.FUN_00608400(((RHHumanActorCalls *)actor)->FUN_004237d0()))
                    ((RHUnk0044d400 *)((char *)actor + 0x6e8))->FUN_0044d400(value, false);
            }
        }
    }
    if (value != m_288)
    {
        if (value != m_28c)
            m_290 = m_28c;
        m_28c = m_288;
        m_288 = value;
        unsigned short amount = ((RHHumanVirtualCalls *)Actor())->V124();
        if (amount < 50)
            m_28c = 0;
        if (amount < 80)
            m_290 = 0;
    }
}

// FUNCTION: GAME 0x0044d6a0
void RHUnk0044d400::FUN_0044d6a0()
{
    m_288 = 0;
    m_28c = 0;
    m_290 = 0;
}

void EmitRHUnk0044d400(RHUnk0044d400 *a)
{
    a->FUN_0044d6a0();
}

// FUNCTION: GAME 0x0046bd20
int RHUnk0046bd20::FUN_0046bd20()
{
    RHSequenceElement *element = *(RHSequenceElement **)((char *)this + 0x130);
    if (!element)
        return 0xa1;
    return element->m_10;
}

#define RH_HUMAN_ACCESS(value, size, line) \
    if (file.Access(&(value), size) < 0) \
    { \
        SBString *error = file.GetError(); \
        const char *reason = error->m_chars ? error->m_chars : ""; \
        SBAssert(0, sourceFile, line, "Serialize failed reason is %s", reason); \
        return false; \
    }

// LIBRARY: GAME 0x00471440
// ?_Ucopy@?$vector@GV?$allocator@G@std@@@std@@IAEPAGPBG0PAG@Z

// LIBRARY: GAME 0x00471470
// ?_Ufill@?$vector@GV?$allocator@G@std@@@std@@IAEXPAGIABG@Z

// Parked: posture/combat dispatch and original EH states remain incomplete.
// STUB: GAME 0x00472070
void RHElementActorHuman::Translate(RHSequenceElement *element, RHcommand command)
{
    RHUnk005fc3b0 point;
    int selected = command ? command : element->m_10;
    RHActorTranslationSequenceCalls *sequence = (RHActorTranslationSequenceCalls *)element;
    int orderCode;
    bool target = true;
    switch (selected)
    {
    case 60: orderCode = 0x44; break;
    case 61: orderCode = 0x4b; break;
    case 62: orderCode = 0x46; break;
    case 63: orderCode = 0x45; break;
    case 64: orderCode = 0x4a; break;
    case 65: orderCode = 0x49; break;
    case 66: orderCode = 0x48; break;
    case 67: orderCode = 0x47; break;
    case 68:
        orderCode = 0x65;
        target = false;
        break;
    case 69: orderCode = 0x64; break;
    case 70:
        orderCode = 0x60;
        target = false;
        break;
    case 71:
    {
        int action = command ? RHActorField<int>(element, 0x40) : RHActorField<int>(this, 0x144);
        orderCode = action >= 4 && action <= 6 ? 0x75 :
            ((action >= 7 && action <= 11) || action == 15) ? 0x6e : 0x31;
        target = false;
        break;
    }
    case 85:
        orderCode = RHActorField<int>(RHActorField<void *>(this, 0x50), 0x8c) == 10 ? 0x11a : 0x17a;
        break;
    case 110:
        if (RHActorField<int>(this, 0x144) == 12)
        {
            sequence->V0c(0, true);
            return;
        }
        orderCode = 0xaa;
        target = false;
        break;
    case 111:
        orderCode = 0xad;
        target = false;
        break;
    case 112:
        orderCode = 0xac;
        target = false;
        break;
    case 29:
    case 31:
    case 32:
    case 33:
    case 34:
    case 35:
    case 38:
    case 39:
    case 40:
    case 41:
    case 42:
    case 43:
    case 50:
    case 51:
    case 52:
    case 53:
    case 54:
    case 55:
    case 56:
    case 57:
    case 58:
    case 59:
    case 74:
    case 75:
    case 76:
    case 84:
    case 86:
    case 160:
    case 161:
    case 169:
    case 176:
    case 178:
        return;
    default:
        ((RHElementActor *)this)->Translate(element, command);
        return;
    }
    RHOrder *order = new RHOrder;
    order->m_24 = orderCode;
    order->m_2a = 0;
    if (target)
        order->m_30 = RHActorField<void *>(element, 0x64);
    sequence->FUN_00585970(order);
}

// Parked: sequence-list cursor uses ebx instead of ebp, shifting failure branches.
// STUB: GAME 0x004799e0
bool RHElementActorHuman::Serialize(SBFile &file)
{
    // STRING: GAME 0x006ae46c
    const char *sourceFile = "P:\\Robin Hood\\RHelementactorhuman.cpp";
    // STRING: GAME 0x006ae55c
    RHSerializeName(file, "RHElementActorHuman");
    if (file.m_version >= 21)
    {
        RH_HUMAN_ACCESS(m_23f, 1, 5745);
    }
    RH_HUMAN_ACCESS(*(short *)((char *)this + 0x1ca), 2, 5748);
    RH_HUMAN_ACCESS(*((char *)this + 0x1ce), 1, 5751);
    RH_HUMAN_ACCESS(*(short *)((char *)this + 0x1cc), 2, 5752);
    RH_HUMAN_ACCESS(*(short *)((char *)this + 0x1c8), 2, 5753);
    RH_HUMAN_ACCESS(m_492, 2, 5754);
    RH_HUMAN_ACCESS(m_494, 2, 5755);
    RH_HUMAN_ACCESS(m_496, 1, 5756);
    RH_HUMAN_ACCESS(m_497, 1, 5757);
    RH_HUMAN_ACCESS(m_288, 1, 5758);
    RH_HUMAN_ACCESS(m_289, 1, 5759);
    RH_HUMAN_ACCESS(m_28a, 2, 5760);
    RH_HUMAN_ACCESS(m_23e, 1, 5761);
    unsigned opponentCount;
    RHHumanOpponent opponent;
    if (file.m_bLoading)
    {
        RHHumanList &list = m_260;
        list.Clear();
        RH_HUMAN_ACCESS(opponentCount, 2, 5772);
        for (unsigned short i = 0; i < (unsigned short)opponentCount; ++i)
        {
            g_pEngine->FUN_004c3bd0(file, opponent.m_actor);
            (*(RHFastFindGrid **)((char *)this + 0x64))->SerializeLinePointer(file, opponent.m_line);
            ((RHHumanOpponentListCalls *)&list)->FUN_00486110(RHHumanOpponentIterator((RHHumanOpponentNode *)list.head), opponent);
            list.valid = 1;
        }
    }
    else
    {
        opponentCount = m_260.count;
        RH_HUMAN_ACCESS(opponentCount, 2, 5786);
        for (unsigned short i = 0; i < (unsigned short)opponentCount; ++i)
        {
            RHHumanList &list = m_260;
            ((RHTitbitList *)&list)->At(i);
            opponent = ((RHHumanOpponentNode *)list.cursor)->value;
            g_pEngine->FUN_004c3bd0(file, opponent.m_actor);
            (*(RHFastFindGrid **)((char *)this + 0x64))->SerializeLinePointer(file, opponent.m_line);
        }
    }
    RH_HUMAN_ACCESS(m_490, 1, 5797);
    RH_HUMAN_ACCESS(m_480, 4, 5800);
    RH_HUMAN_ACCESS(m_484, 4, 5801);
    RH_HUMAN_ACCESS(m_488, 2, 5802);
    RH_HUMAN_ACCESS(m_48a, 1, 5803);
    RH_HUMAN_ACCESS(m_48c, 4, 5804);
    RHEngine *engine = g_pEngine;
    engine->SerializeNestedB(file, &m_254);
    ((RHUnk004b2190Member *)m_43c)->Serialize(file);
    RH_HUMAN_ACCESS(m_47c, 1, 5812);
    ((RHUnkPathGeometry *)g_unk0x6c0a9c)->Unk004fbec0(file, m_498);
    RH_HUMAN_ACCESS(m_1d0, 28, 5816);
    ((RHElementActor *)this)->RHElementActor::Serialize(file);
    ((RHSightObstacle *)m_294)->Serialize(file);
    unsigned actorCount;
    void *actor;
    if (file.m_bLoading)
    {
        RHHumanList &list = m_20c;
        list.Clear();
        RH_HUMAN_ACCESS(actorCount, 2, 5832);
        for (unsigned short i = 0; i < (unsigned short)actorCount; ++i)
        {
            g_pEngine->FUN_004c3bd0(file, actor);
            list.Insert(actor);
            list.valid = 1;
        }
    }
    else
    {
        actorCount = m_20c.count;
        RH_HUMAN_ACCESS(actorCount, 2, 5844);
        for (unsigned short i = 0; i < (unsigned short)actorCount; ++i)
        {
            RHHumanList &list = m_20c;
            ((RHTitbitList *)&list)->At(i);
            actor = list.cursor->data;
            g_pEngine->FUN_004c3bd0(file, actor);
        }
    }
    RH_HUMAN_ACCESS(m_230, 4, 5853);
    RH_HUMAN_ACCESS(m_234, 4, 5854);
    RH_HUMAN_ACCESS(m_238, 4, 5855);
    RH_HUMAN_ACCESS(m_23c, 2, 5858);
    for (unsigned i = 0; i < 9; ++i)
    {
        RH_HUMAN_ACCESS(m_240[i], 2, 5863);
    }
    if (file.m_bLoading)
    {
        RHHumanList &list = m_1b8;
        RHScriptNode *sentinel = list.head;
        RHScriptNode *current = sentinel->next;
        while (current != sentinel)
        {
            RHScriptNode *previous = current;
            current = current->next;
            ((RHUnk0046eb30 *)&list)->erase(RHScriptIter(previous));
        }
        if (file.m_version >= 28)
        {
            unsigned count;
            RH_HUMAN_ACCESS(count, 4, 5876);
            list.Resize(count, (void *)0);
            for (std::list<RHSequenceElement *>::iterator node = ((std::list<RHSequenceElement *> *)&m_1b8)->begin(); node != ((std::list<RHSequenceElement *> *)&m_1b8)->end(); ++node)
                (*(RHSequenceManager **)((char *)this + 0x5c))->PreSerializePointer(file, &*node, true);
        }
    }
    else
    {
        unsigned count = m_1b8.count;
        RH_HUMAN_ACCESS(count, 4, 5889);
        for (std::list<RHSequenceElement *>::iterator node = ((std::list<RHSequenceElement *> *)&m_1b8)->begin(); node != ((std::list<RHSequenceElement *> *)&m_1b8)->end(); ++node)
            (*(RHSequenceManager **)((char *)this + 0x5c))->PreSerializePointer(file, &*node, true);
    }
    if (file.m_version >= 33)
    {
        RH_HUMAN_ACCESS(m_28c, 4, 5899);
        engine->FUN_004c3bd0(file, m_290);
    }
    return true;
}

// FUNCTION: GAME 0x0047b760
int RHElementActorHuman::FUN_0047b760(void *actor, int *value)
{
    int other;
    if ((RHActorField<unsigned>(actor, 4) & 7) == 4)
    {
        if (RHActorField<int>(RHActorField<void *>(actor, 0x50), 0x8c) != 19)
        {
            RHUnk00613e90 point;
            ((RHHumanActorCalls *)actor)->FUN_00479320(point);
            return ((RHHumanActorCalls *)this)->FUN_0047b8a0(point, value, false);
        }
        else
        {
            RHUnk00613e90 point;
            ((RHHumanActorCalls *)actor)->FUN_00479320(point);
            if (!((RHHumanActorCalls *)this)->FUN_0047b8a0(point, value, false))
            {
                if (*value == 1)
                {
                    ((RHElementActor *)actor)->FUN_00478c20(point, false);
                    if (((RHHumanActorCalls *)this)->FUN_0047b8a0(point, &other, false) && other == 0)
                        *value = 0;
                }
                return 0;
            }
            ((RHElementActor *)actor)->FUN_00478c20(point, false);
            return ((RHHumanActorCalls *)this)->FUN_0047b8a0(point, value, false);
        }
    }
    if (RHActorField<undefined>(g_pEngine, 0x4aa8))
        return ((RHHumanActorCalls *)this)->FUN_0047b8a0(RHActorField<RHUnk00613e90>(RHActorField<void *>(actor, 0x50), 0x10), value, true);
    return ((RHHumanActorCalls *)this)->FUN_0047b8a0(RHActorField<RHUnk00613e90>(RHActorField<void *>(actor, 0x50), 0x10), value, false);
}

// FUNCTION: GAME 0x0047c420
void RHElementActorHuman::FUN_0047c420(void *value)
{
    if (m_260.count == 0)
    {
        ((RHUnk0046bcb0 *)this)->Unk(7);
        if ((RHActorField<unsigned>(this, 4) & 31) == 20)
        {
            RHUnk0047c420Message message;
            message.m_20 = 23;
            message.m_00 = value;
            message.m_1c = 3;
            ((RHHumanVirtualCalls *)((char *)this + 0x49c + RHActorField<int *>(this, 0x49c)[1]))->V024(&message);
        }
    }
}

// FUNCTION: GAME 0x0047c4c0
int RHElementActorHuman::FUN_0047c4c0(RHElementActorHuman *actor)
{
    if (((RHHumanVirtualCalls *)this)->V048() || RHActorField<undefined>(this, 0x1ce) || m_23c != 0)
        return 0;
    if (!actor || ((RHHumanVirtualCalls *)actor)->V048() || RHActorField<undefined>(actor, 0x1ce) || actor->m_23c != 0)
        return 0;
    void *first = RHActorField<void *>(RHActorField<void *>(this, 0x50), 0xe0);
    if ((undefined)(RHActorField<unsigned>(first, 0x30) >> 13) & 1)
        return 0;
    void *second = RHActorField<void *>(RHActorField<void *>(actor, 0x50), 0xe0);
    if ((undefined)(RHActorField<unsigned>(second, 0x30) >> 13) & 1)
        return 0;
    if ((RHActorField<unsigned>(this, 4) & 31) == 20 &&
        ((RHHumanVirtualCalls *)this)->V0f8() && !((RHHumanVirtualCalls *)actor)->V168())
        return 0;
    if ((RHActorField<unsigned>(actor, 4) & 31) == 20 &&
        ((RHHumanVirtualCalls *)actor)->V0f8() && !((RHHumanVirtualCalls *)this)->V168())
        return 0;
    first = RHActorField<void *>(RHActorField<void *>(this, 0x50), 0xe0);
    if (((undefined)(RHActorField<unsigned>(first, 0x30) >> 9) & 1) &&
        (RHActorField<int>(first, 0xf0) == 3 || RHActorField<int>(first, 0xf0) == 2))
        return 0;
    second = RHActorField<void *>(RHActorField<void *>(actor, 0x50), 0xe0);
    if (((undefined)(RHActorField<unsigned>(second, 0x30) >> 9) & 1) &&
        (RHActorField<int>(second, 0xf0) == 3 || RHActorField<int>(second, 0xf0) == 2))
        return 0;
    return 1;
}

// FUNCTION: GAME 0x0047d4c0
void RHHumanActorCalls::FUN_0047d4c0()
{
    RHElementActorHuman *actor = (RHElementActorHuman *)this;
    unsigned count = actor->m_260.count;
    RHElementActorHuman *other;
    if (count)
        other = (RHElementActorHuman *)((RHHumanOpponentNode *)actor->m_260.head->next)->value.m_actor;
    else
        other = 0;
    if (count)
    {
        if (other->m_260.count)
        {
            actor->m_288 = 1;
            actor->m_289 = 1;
            if (other->m_260.count &&
                ((RHHumanOpponentNode *)other->m_260.head->next)->value.m_actor == actor)
                other->m_288 = 0;
        }
    }
}

#include "RHArtificialIntelligenceActorCalls.h"

// Residual: the argument-load order and compare registers remain different after five source shapes.
// STUB: GAME 0x0047d520
void RHHumanActorCalls::FUN_0047d520(void *actor, int value)
{
    RHElementActorHuman *self = (RHElementActorHuman *)this;
    if (self->m_260.count == 0)
        return;
    if (((RHHumanOpponentNode *)self->m_260.head->next)->value.m_actor == actor)
    {
        self->m_290 = actor;
        self->m_28c = value;
    }
}

static inline RHElementActorHuman *RHHumanFirstOpponent(RHElementActorHuman *actor)
{
    return actor->m_260.count ? (RHElementActorHuman *)((RHHumanOpponentNode *)actor->m_260.head->next)->value.m_actor : 0;
}

// FUNCTION: GAME 0x0047d270
bool RHHumanActorCalls::FUN_0047d270(void *actor)
{
    RHElementActorHuman *self = (RHElementActorHuman *)this;
    unsigned count = self->m_260.count;
    for (unsigned i = 0; i < count; ++i)
    {
        RHHumanList &list = self->m_260;
        ((RHTitbitList *)&list)->At(i);
        if (actor == list.cursor->data)
        {
            ((RHTitbitList *)&list)->At(i);
            RHScriptNode *node = list.cursor;
            node->prev->next = node->next;
            node->next->prev = node->prev;
            ::operator delete(node);
            --list.count;
            list.valid = 1;
            self->FUN_0047ebc0();
            if (self->m_260.count != 0)
            {
                RHElementActorHuman *first = RHHumanFirstOpponent(self);
                if (first->m_260.count != 0)
                    FUN_0047d4c0();
            }
            else
                self->FUN_0047ca50();
            return true;
        }
    }
    return false;
}

// Parked: the first opponent's count loads use different registers.
// STUB: GAME 0x0047ce70
bool RHElementActorHuman::FUN_0047ce70(RHElementActorHuman *actor, void *line)
{
    unsigned count = m_260.count;
    for (unsigned index = 0; index < count; ++index)
    {
        RHHumanList &opponents = m_260;
        ((RHTitbitList *)&opponents)->At(index);
        if (*(RHElementActorHuman *volatile *)&actor == ((RHHumanOpponentNode *)opponents.cursor)->value.m_actor)
        {
            if (index)
            {
                ((RHTitbitList *)&opponents)->At(index);
                RHHumanOpponent &selected = ((RHHumanOpponentNode *)opponents.cursor)->value;
                ((RHTitbitList *)&opponents)->At(0);
                RHHumanOpponentNode *first = (RHHumanOpponentNode *)opponents.cursor;
                RHHumanOpponent previous = first->value;
                first->value = selected;
                ((RHTitbitList *)&opponents)->At(index);
                ((RHHumanOpponentNode *)opponents.cursor)->value = previous;
                ((RHTitbitList *)&opponents)->At(0);
                ((RHHumanOpponentNode *)opponents.cursor)->value.m_line = line;
            }
            return false;
        }
    }
    RHHumanOpponent value;
    value.m_actor = actor;
    value.m_line = line;
    RHHumanList &opponents = m_260;
    ((RHHumanOpponentListCalls *)&opponents)->FUN_00486110(
        RHHumanOpponentIterator((RHHumanOpponentNode *)opponents.head->next), value);
    opponents.valid = 1;
    FUN_0047ebc0();
    if (m_260.count)
    {
        RHElementActorHuman *other = RHHumanFirstOpponent(this);
        if (other->m_260.count)
            ((RHHumanActorCalls *)this)->FUN_0047d4c0();
    }
    return true;
}

// Parked: cached-list lookup and line-update scheduling need codegen alignment.
// STUB: GAME 0x0047cf80
bool RHElementActorHuman::FUN_0047cf80(RHElementActorHuman *actor, void *line)
{
    unsigned count = m_260.count;
    for (unsigned index = 0; index < count; ++index)
    {
        RHHumanList &opponents = m_260;
        void *opponent = RHHumanOpponentAt(opponents, index).m_actor;
        if (*(RHElementActorHuman *volatile *)&actor == opponent)
        {
            RHHumanOpponentAt(opponents, index).m_line = line;
            return true;
        }
    }
    return false;
}

// FUNCTION: GAME 0x0047d1b0
void RHElementActorHuman::FUN_0047d1b0()
{
    unsigned count = m_260.count;
    for (unsigned index = 0; index < count; ++index)
    {
        RHHumanList &opponents = m_260;
        ((RHTitbitList *)&opponents)->At(index);
        RHHumanOpponent &opponent = ((RHHumanOpponentNode *)opponents.cursor)->value;
        RHElementActorHuman *other = (RHElementActorHuman *)opponent.m_actor;
        void *otherArea = RHActorField<void *>(RHActorField<void *>(other, 0x50), 0xe0);
        void *ownArea = RHActorField<void *>(RHActorField<void *>(this, 0x50), 0xe0);
        if (otherArea == ownArea)
        {
            if (opponent.m_line)
            {
clearLine:
                opponent.m_line = 0;
                other->FUN_0047cf80(this, 0);
            }
        }
        else if (!opponent.m_line || RHActorField<void *>(opponent.m_line, 0x1c) != ownArea ||
            RHActorField<void *>(RHActorField<void *>(opponent.m_line, 0x20), 0x1c) != otherArea)
        {
            void *ownLine = FUN_00484870(other);
            if (!ownLine)
                goto clearLine;
            void *otherLine = other->FUN_00484870(this);
            if (!otherLine || ownLine != RHActorField<void *>(otherLine, 0x20))
                goto clearLine;
            opponent.m_line = ownLine;
            other->FUN_0047cf80(this, otherLine);
        }
    }
}

static inline RHHumanOpponent &RHHumanPrunedOpponentAt(RHHumanList &list, int wanted)
{
    int size = list.count;
    if (list.valid)
    {
        if (wanted <= (size + 1) / 2)
            FUN_005c9010((RHUnk005c9010Iterator &)(list.cursor = list.head->next), wanted, std::bidirectional_iterator_tag());
        else
            FUN_005c9010((RHUnk005c9010Iterator &)(list.cursor = list.head), wanted - size, std::bidirectional_iterator_tag());
        list.valid = 0;
        list.index = wanted;
    }
    else
    {
        int previous = list.index;
        if (wanted != previous)
        {
            if (wanted < previous)
            {
                if (wanted < (previous + 1) / 2)
                    FUN_005c9010((RHUnk005c9010Iterator &)(list.cursor = list.head->next), wanted, std::bidirectional_iterator_tag());
                else
                    FUN_005c9010((RHUnk005c9010Iterator &)list.cursor, wanted - previous, std::bidirectional_iterator_tag());
            }
            else if (wanted < (previous + size) / 2)
                FUN_005c9010((RHUnk005c9010Iterator &)list.cursor, wanted - previous, std::bidirectional_iterator_tag());
            else
            {
                list.cursor = list.head;
                int distance = wanted - size;
                while (distance > 0) { list.cursor = list.cursor->next; --distance; }
                while (distance < 0) { list.cursor = list.cursor->prev; ++distance; }
            }
            list.index = wanted;
        }
    }
    return ((RHHumanOpponentNode *)list.cursor)->value;
}

// Parked: cached cursor address liveness adds a frame slot and changes traversal registers.
// STUB: GAME 0x0047cb00
void RHElementActorHuman::FUN_0047cb00()
{
    float maximum = ((RHMalignityAbilityCalls *)RHActorField<void *>(this, 0x25c))->FUN_005c1b50(3);
    bool changed = false;
    for (int index = (int)m_260.count - 1; index >= 0; --index)
    {
        RHHumanList &opponents = m_260;
        ((RHTitbitList *)&opponents)->At(index);
        RHElementActorHuman *other = (RHElementActorHuman *)opponents.cursor->data;
        float distance = ((RHUnk005fc3b0 *)&RHActorField<SBGeoPoint2D>(RHActorField<void *>(other, 0x50), 0x24).Unk005fc110(
            RHActorField<SBGeoPoint2D>(RHActorField<void *>(this, 0x50), 0x24)))->Unk005fc6a0(1.0f);
        if (distance > maximum &&
            (float)((RHMalignityAbilityCalls *)RHActorField<void *>(other, 0x25c))->FUN_005c1b50(3) < distance)
        {
            RHHumanPrunedOpponentAt(opponents, index);
            RHScriptNode *node = opponents.cursor;
            node->prev->next = node->next;
            node->next->prev = node->prev;
            ::operator delete(node);
            --opponents.count;
            opponents.valid = 1;
            ((RHHumanActorCalls *)other)->FUN_0047d270(this);
            other->FUN_0047cd40();
            changed = true;
        }
    }
    if (changed)
        FUN_0047cd40();
}

// Parked: sequence pointer registers and message-construction scheduling differ.
// STUB: GAME 0x0047cd40
void RHElementActorHuman::FUN_0047cd40()
{
    if (m_260.count == 0)
    {
        void *sequence = RHActorField<void *>(this, 0x130);
        if (sequence && RHActorField<unsigned char>(sequence, 4) == 4)
            RHActorField<int>(sequence, 0x94) = RHActorField<int>(sequence, 0x94) == 0x12f ? 6 : 10;
        RHUnk00584d60 *event = new RHUnk00584d60(1, 0x33, this);
        ((RHScriptBatchCalls *)RHActorField<void *>(this, 0x5c))->Unk0058a940("", 0, event);
        if ((RHActorField<unsigned>(this, 4) & 0xf) == 0xc)
            ((RHHumanActorCalls *)this)->FUN_0049d780();
        else if ((RHActorField<unsigned>(this, 4) & 0x1f) == 0x14)
        {
            RHUnk0047c420Message message;
            message.m_20 = 0x18;
            *(unsigned short *)&message.m_00 = 0;
            message.m_1c = 0;
            int *base = RHActorField<int *>(this, 0x49c);
            ((RHHumanVirtualCalls *)((char *)this + 0x49c + base[1]))->V024(&message);
        }
    }
    else if (m_260.count >= 2)
        FUN_0047d670();
}

// Residual: line-of-sight geometry, distance filtering, and actor-list insertion remain unimplemented.
// STUB: GAME 0x0047c600
bool RHElementActorHuman::FUN_0047c600(RHElementActorHuman *actor, int mode, bool flag)
{
    if (!actor || !FUN_0047c4c0(actor))
        return false;
    if (FUN_0047d320(actor))
        return true;
    if (m_260.count == 0 && actor->m_260.count != 0)
    {
        RHHumanOpponentNode *node = (RHHumanOpponentNode *)actor->m_260.head->next;
        FUN_0047ce70(actor, node->value.m_line);
    }
    if (flag && mode != 0)
        ((RHHumanActorCalls *)this)->FUN_0047d520(actor, mode);
    return true;
}

// Residual: the target chooses candidates from heading/3D distance and updates a temporary list.
// STUB: GAME 0x0047d670
void RHElementActorHuman::FUN_0047d670()
{
    if (m_260.count == 0)
        return;
    unsigned selected = 0;
    for (unsigned index = 1; index < m_260.count; ++index)
    {
        RHHumanOpponentNode *candidate = (RHHumanOpponentNode *)m_260.head->next;
        RHHumanOpponentNode *current = candidate;
        for (unsigned step = 0; step < index; ++step)
            candidate = candidate->next;
        for (unsigned selectedStep = 0; selectedStep < selected; ++selectedStep)
            current = current->next;
        RHElementActorHuman *candidateActor = (RHElementActorHuman *)candidate->value.m_actor;
        RHElementActorHuman *currentActor = (RHElementActorHuman *)current->value.m_actor;
        float candidateX = RHActorField<float>(RHActorField<void *>(candidateActor, 0x50), 0x18);
        float currentX = RHActorField<float>(RHActorField<void *>(currentActor, 0x50), 0x18);
        float selfX = RHActorField<float>(RHActorField<void *>(this, 0x50), 0x18);
        if (candidateX - selfX < currentX - selfX)
            selected = index;
    }
    RHHumanOpponentNode *node = (RHHumanOpponentNode *)m_260.head->next;
    for (unsigned selectedIndex = 0; selectedIndex < selected; ++selectedIndex)
        node = node->next;
    ((RHHumanActorCalls *)this)->FUN_0047d520(node->value.m_actor, 0xc);
}

// FUNCTION: GAME 0x0047ca50
void RHElementActorHuman::FUN_0047ca50()
{
    unsigned count = m_260.count;
    for (unsigned index = 0; index < count; ++index)
    {
        RHHumanList &opponents = m_260;
        ((RHTitbitList *)&opponents)->At(index);
        ((RHHumanActorCalls *)opponents.cursor->data)->FUN_0047d270(this);
    }
    RHHumanList &opponents = m_260;
    RHScriptNode *sentinel = opponents.head;
    RHScriptNode *current = sentinel->next;
    while (current != sentinel)
    {
        RHScriptNode *previous = current;
        current = current->next;
        ((RHUnk0046eb30 *)&opponents)->erase(RHScriptIter(previous));
    }
    opponents.valid = 1;
    if (((RHHumanVirtualCalls *)this)->V048())
        return;
    struct Kind4 { unsigned value : 4; };
    struct Kind5 { unsigned value : 5; };
    if (((Kind4 *)((char *)this + 4))->value == 0xc)
        ((RHHumanActorCalls *)this)->FUN_0049d780();
    else if (((Kind5 *)((char *)this + 4))->value == 0x14)
    {
        ((RHScriptBatchCalls *)((char *)this + 0x49c + RHActorField<int *>(this, 0x49c)[1]))->Unk0040d980(0x18);
    }
}

static inline RHHumanOpponent &RHHumanStrengthOpponentAt(RHHumanList &list, int wanted)
{
    int size = list.count;
    if (list.valid)
    {
        if (wanted <= (size + 1) / 2)
            FUN_005c9010((RHUnk005c9010Iterator &)(list.cursor = list.head->next), wanted, std::bidirectional_iterator_tag());
        else
            FUN_005c9010((RHUnk005c9010Iterator &)(list.cursor = list.head), wanted - size, std::bidirectional_iterator_tag());
        list.valid = 0;
        list.index = wanted;
    }
    else
    {
        int previous = list.index;
        if (wanted != previous)
        {
            if (wanted < previous)
            {
                if (wanted < (previous + 1) / 2)
                    FUN_005c9010((RHUnk005c9010Iterator &)(list.cursor = list.head->next), wanted, std::bidirectional_iterator_tag());
                else
                    FUN_005c9010((RHUnk005c9010Iterator &)list.cursor, wanted - previous, std::bidirectional_iterator_tag());
            }
            else
            {
                if (wanted < (previous + size) / 2)
                {
                    int distance = wanted - previous;
                    while (distance > 0) { list.cursor = list.cursor->next; --distance; }
                    while (distance < 0) { list.cursor = list.cursor->prev; ++distance; }
                }
                else
                {
                    list.cursor = list.head;
                    int distance = wanted - size;
                    while (distance > 0) { list.cursor = list.cursor->next; --distance; }
                    while (distance < 0) { list.cursor = list.cursor->prev; ++distance; }
                }
            }
            list.index = wanted;
        }
    }
    return ((RHHumanOpponentNode *)list.cursor)->value;
}

// Parked: the iterator tag occupies an extra saved register and reset-load scheduling differs.
// STUB: GAME 0x0047d320
bool RHElementActorHuman::FUN_0047d320(RHElementActorHuman *actor)
{
    unsigned count = m_260.count;
    for (unsigned index = 0; index < count; ++index)
    {
        void *opponent = RHHumanStrengthOpponentAt(m_260, index).m_actor;
        if (*(RHElementActorHuman *volatile *)&actor == opponent)
            return true;
    }
    return false;
}

// FUNCTION: GAME 0x0047d560
bool RHElementActorHuman::FUN_0047d560()
{
    bool changed = false;
    RHUnk00585ea0 *event;
    if (m_28c != 0xb)
    {
        switch (m_28c)
        {
        case 0xc:
            event = new RHUnk00585ea0(1, 0x39, this, m_290);
            goto dispatch;
        case 0xd:
            event = new RHUnk00585ea0(1, 0x3a, this, m_290);
            goto dispatch;
        case 0xe:
            event = new RHUnk00585ea0(1, 0x35, this, m_290);
dispatch:
            ((RHScriptBatchCalls *)RHActorField<void *>(this, 0x5c))->Unk0058a940("", 0, event);
            changed = true;
        }
    }
    m_28c = 0xb;
    m_290 = 0;
    return changed;
}

// FUNCTION: GAME 0x00482150
void RHElementActorHuman::FUN_00482150(int value, int second, bool flag)
{
    if (((RHHumanVirtualCalls *)this)->V048())
        return;
    int amount = value;
    if ((short)amount < 0)
        amount = 0;
    struct Kind4 { unsigned value : 4; };
    if (RHActorField<char>(g_unk0x6c0b3c, 0x5a) &&
        ((Kind4 *)((char *)this + 4))->value == 0xc)
    {
        short current = (short)((RHHumanVirtualCalls *)this)->V0cc();
        if ((short)amount < current && g_unk0x6c0691)
            return;
    }
    if (flag)
    {
        short current = (short)((RHHumanVirtualCalls *)this)->V0cc();
        if ((short)amount <= current)
        {
            unsigned short frame = *(unsigned short *)((char *)RHActorField<void *>(this, 0x50) + 0xde);
            RHUnk00613e90 point(0.0f, 0.0f, 2.0f);
            RHUnk005c38b0 *context = g_unk0x6c10e8;
            typedef void (RHScriptBatchCalls::*Effect)(void *, unsigned short, int, void *, int, int, int, int);
            (((RHScriptBatchCalls *)context)->*(Effect)&RHScriptBatchCalls::Unk005c2ec0)(
                &point, frame, 4, this, ((RHHumanVirtualCalls *)this)->V0cc() - amount, 0, 0, -1);
        }
    }
    ((RHHumanVirtualCalls *)this)->V0c4(RHActorField<char>(this, 0x496) ? 100 : (short)amount);
    if (((RHHumanVirtualCalls *)this)->V048())
    {
        ((RHHumanVirtualCalls *)this)->V05c((void *)second);
    }
}

// FUNCTION: GAME 0x00482240
unsigned short RHElementActorHuman::FUN_00482240(int index, RHElementActorHuman *other)
{
    RHUnk005fc3b0 point;
    RHUnk005c1d50 *otherWeapon = RHActorField<RHUnk005c1d50 *>(other, 0x25c);
    unsigned short chance = RHActorField<RHUnk005c1d50 *>(this, 0x25c)->FUN_005c1dd0(index, this);
    if ((int)chance > (short)((RHHumanVirtualCalls *)other)->V0cc())
        chance = ((RHHumanVirtualCalls *)other)->V0cc();
    unsigned short adjustedChance;
    if (otherWeapon)
    {
        unsigned short opponentWeaponChance = ((RHHumanWeaponCalls *)otherWeapon)->FUN_005c1b70(
            other, this, RHActorField<RHHumanWeaponCalls *>(this, 0x25c)->FUN_005c1d70(index));
        int remaining = 100 - opponentWeaponChance;
        float adjusted = (float)remaining;
        adjusted *= chance;
        adjusted *= 0.01f;
        adjustedChance = (unsigned short)adjusted;
        if (adjustedChance > 0)
            chance = adjustedChance;
    }
    else
        adjustedChance = index;
    unsigned short weaponChance = RHActorField<RHHumanWeaponCalls *>(this, 0x25c)->FUN_005c1db0(index);
    if (otherWeapon)
    {
        unsigned short modifier = *(unsigned short *)(*(char **)((char *)otherWeapon + 4) + 0x12);
        weaponChance = (unsigned short)((float)(100 - modifier) * weaponChance * 0.01f);
        if (adjustedChance > 0)
            weaponChance = adjustedChance;
    }
    (void)point;
    return chance + weaponChance;
}

// FUNCTION: GAME 0x00483070
bool RHElementActorHuman::FUN_00483070(RHElementActorHuman *other)
{
    struct Kind3 { unsigned value : 3; };
    struct Kind4 { unsigned value : 4; };
    struct Kind5 { unsigned value : 5; };
    if (((Kind3 *)((char *)other + 4))->value != 4 || !RHActorField<char>(other, 0x12) || other == this ||
        RHActorField<char>(other, 0x1ce) || ((RHHumanVirtualCalls *)other)->V048() ||
        RHActorField<int>(RHActorField<void *>(other, 0x50), 0x8c) == 22 ||
        other->m_23c != 0)
        return false;
    if (((Kind5 *)((char *)other + 4))->value == 20 &&
        ((RHHumanVirtualCalls *)other)->V0f8() &&
        ((Kind4 *)((char *)this + 4))->value == 12 &&
        !((RHHumanVirtualCalls *)this)->V168())
        return false;
    RHUnk00613e90 first;
    RHUnk00613e90 second;
    ((RHHumanActorCalls *)this)->FUN_00479320(first);
    ((RHHumanActorCalls *)other)->FUN_00479320(second);
    typedef unsigned char (RHMalignityGeometryCalls::*Geometry)(const RHUnk00613e90 &, const RHUnk00613e90 &, int);
    Geometry geometry = (Geometry)&RHMalignityGeometryCalls::FUN_004eff80;
    if ((((RHMalignityGeometryCalls *)g_unk0x6c0a9c)->*geometry)(first, second, 1))
        return true;
    return false;
}

static inline unsigned short RHHumanScanHeading(void *actor)
{
    return RHActorField<unsigned short>(RHActorField<void *>(actor, 0x50), 0xd8);
}

// FUNCTION: GAME 0x00482390
void RHElementActorHuman::FUN_00482390(RHHumanList *result, int weaponData, bool alternate)
{
    RHActorField<RHHumanWeaponCalls *>(this, 0x25c)->FUN_005c1d70(weaponData);
    for (unsigned i = 0; i < (unsigned short)RHActorField<std::vector<RHElementActorHuman *> >(g_pEngine, 0x4918).size(); ++i)
    {
        RHElementActorHuman *candidate = RHActorField<std::vector<RHElementActorHuman *> >(g_pEngine, 0x4918)[(unsigned short)i];
        if (!FUN_00483070(candidate))
            continue;
        SBGeoVector2D delta;
        {
            SBGeoVector2D own(RHActorField<SBGeoVector2D>(RHActorField<void *>(this, 0x50), 0x24));
            delta = own;
        }
        {
            SBGeoVector2D other(RHActorField<SBGeoVector2D>(RHActorField<void *>(candidate, 0x50), 0x24));
            delta.FUN_005fc250(other);
        }
        if (delta.FUN_005fc700(1.0f) < 150.0f)
        {
            float distance = ((RHUnk005fc3b0 *)&delta)->Unk005fc6a0(1.0f);
            unsigned short reach = RHActorField<RHHumanWeaponCalls *>(this, 0x25c)->FUN_005c1ea0(weaponData);
            if (alternate && RHActorField<void *>(candidate, 0x134) &&
                RHActorField<int>(RHActorField<void *>(candidate, 0x134), 0x24) == 0x12f)
            {
                short facing = RHActorField<short>(RHActorField<void *>(this, 0x50), 0xd8);
                unsigned short turn = (((RHUnk005fc3b0 *)&delta)->FUN_005fcc50(1.0f) - facing + 16) % 16;
                float angle = turn * 5 * 3.1415927f;
                reach = angle / (RHActorField<RHHumanWeaponCalls *>(this, 0x25c)->FUN_005c1f50(weaponData) * 8.0f) +
                    reach + 10.0f;
            }
            if (reach >= distance)
            {
                ((std::list<RHElementActorHuman *> *)result)->push_back(candidate);
                result->valid = 1;
            }
        }
    }
}

// FUNCTION: GAME 0x00482600
void RHElementActorHuman::FUN_00482600(RHHumanList *result, int weaponData)
{
    unsigned side = RHActorField<RHHumanWeaponCalls *>(this, 0x25c)->FUN_005c1d70(weaponData);
    float facing = FUN_005fcdf0(RHHumanScanHeading(this));
    unsigned char first;
    unsigned char last;
    if (side == 1)
    {
        m_230 = RHActorField<RHHumanWeaponCalls *>(this, 0x25c)->FUN_005c1ed0(weaponData) + facing;
        m_238 = m_230 - 3.1415927f;
        first = FUN_005fcdb0(m_238);
        last = FUN_005fcdb0(m_230);
    }
    else
    {
        m_230 = facing - RHActorField<RHHumanWeaponCalls *>(this, 0x25c)->FUN_005c1ed0(weaponData);
        m_238 = m_230 + 3.1415927f;
        first = FUN_005fcdb0(m_230);
        last = FUN_005fcdb0(m_238);
    }
    m_234 = facing;
    for (unsigned i = 0; i < (unsigned short)RHActorField<std::vector<RHElementActorHuman *> >(g_pEngine, 0x4918).size(); ++i)
    {
        RHElementActorHuman *candidate = RHActorField<std::vector<RHElementActorHuman *> >(g_pEngine, 0x4918)[(unsigned short)i];
        if (!FUN_00483070(candidate))
            continue;
        SBGeoVector2D delta;
        {
            SBGeoVector2D other(RHActorField<SBGeoVector2D>(RHActorField<void *>(candidate, 0x50), 0x24));
            delta = other;
        }
        {
            SBGeoVector2D own(RHActorField<SBGeoVector2D>(RHActorField<void *>(this, 0x50), 0x24));
            delta.FUN_005fc250(own);
        }
        if (delta.FUN_005fc700(1.0f) < 150.0f)
        {
            float distance = ((RHUnk005fc3b0 *)&delta)->Unk005fc6a0(1.0f);
            if (RHActorField<RHHumanWeaponCalls *>(this, 0x25c)->FUN_005c1e80(weaponData) <= distance &&
                RHActorField<RHHumanWeaponCalls *>(this, 0x25c)->FUN_005c1ea0(weaponData) >= distance &&
                delta.IsBetween(first, last))
            {
                ((std::list<RHElementActorHuman *> *)result)->push_back(candidate);
                result->valid = 1;
            }
        }
    }
}

// FUNCTION: GAME 0x004828b0
void RHElementActorHuman::FUN_004828b0(RHHumanList *result, int weaponData)
{
    unsigned side = RHActorField<RHHumanWeaponCalls *>(this, 0x25c)->FUN_005c1d70(weaponData);
    float facing = FUN_005fcdf0(RHHumanScanHeading(this));
    unsigned char minimumAngle;
    unsigned char maximumAngle;
    if (side == 1)
    {
        m_230 = RHActorField<RHHumanWeaponCalls *>(this, 0x25c)->FUN_005c1ed0(weaponData) + facing;
        m_238 = facing - RHActorField<RHHumanWeaponCalls *>(this, 0x25c)->FUN_005c1f10(weaponData);
        minimumAngle = FUN_005fcdb0(m_238);
        maximumAngle = FUN_005fcdb0(m_230);
    }
    else
    {
        m_230 = facing - RHActorField<RHHumanWeaponCalls *>(this, 0x25c)->FUN_005c1ed0(weaponData);
        m_238 = RHActorField<RHHumanWeaponCalls *>(this, 0x25c)->FUN_005c1f10(weaponData) + facing;
        minimumAngle = FUN_005fcdb0(m_230);
        maximumAngle = FUN_005fcdb0(m_238);
    }
    m_234 = facing;
    for (unsigned long i = 0; i < (unsigned short)RHActorField<std::vector<RHElementActorHuman *> >(g_pEngine, 0x4918).size(); ++i)
    {
        RHElementActorHuman *candidate = RHActorField<std::vector<RHElementActorHuman *> >(g_pEngine, 0x4918)[(unsigned short)i];
        struct Kind3 { unsigned value : 3; };
        if (((Kind3 *)((char *)candidate + 4))->value != 4 ||
            RHActorField<char>(candidate, 0x12) != 1 || candidate == this || !candidate)
            continue;
        SBGeoVector2D delta;
        {
            SBGeoVector2D other(RHActorField<SBGeoVector2D>(RHActorField<void *>(candidate, 0x50), 0x24));
            delta = other;
        }
        {
            SBGeoVector2D own(RHActorField<SBGeoVector2D>(RHActorField<void *>(this, 0x50), 0x24));
            delta.FUN_005fc250(own);
        }
        if (delta.FUN_005fc700(1.0f) < 150.0f)
        {
            float distance = ((RHUnk005fc3b0 *)&delta)->Unk005fc6a0(1.0f);
            if (RHActorField<RHHumanWeaponCalls *>(this, 0x25c)->FUN_005c1e80(weaponData) <= distance &&
                RHActorField<RHHumanWeaponCalls *>(this, 0x25c)->FUN_005c1ea0(weaponData) >= distance &&
                delta.IsBetween(minimumAngle, maximumAngle))
            {
                ((std::list<RHElementActorHuman *> *)result)->push_back(candidate);
                result->valid = 1;
            }
        }
    }
}

#include "SBGeoVectorRotation.h"
#include "RHSword.h"

// FUNCTION: GAME 0x00482b90
void RHElementActorHuman::FUN_00482b90(RHHumanList *result, int weaponData)
{
    SBGeoVector2D direction;
    unsigned i = 0;
    SBGeoVector2D perpendicular;
    unsigned minimum = RHActorField<RHHumanWeaponCalls *>(this, 0x25c)->FUN_005c1e80(weaponData);
    unsigned maximum = RHActorField<RHHumanWeaponCalls *>(this, 0x25c)->FUN_005c1ea0(weaponData);
    unsigned width = RHActorField<RHSword *>(this, 0x25c)->FUN_005c1f90(weaponData);
    direction = ((RHMalignityActorCalls *)this)->FUN_004135b0();
    perpendicular = direction;
    ((RHEngineCameraRotationCalls *)&perpendicular)->FUN_005fc9a0(1.5707963705062866211f, 1.0f);
    ((RHUnk005fc3b0 *)&direction)->FUN_005fc7c0(1.0f);
    ((RHUnk005fc3b0 *)&perpendicular)->FUN_005fc7c0(1.0f);
    for (; i < (unsigned short)RHActorField<std::vector<RHElementActorHuman *> >(g_pEngine, 0x4918).size(); ++i)
    {
        RHElementActorHuman *candidate = RHActorField<std::vector<RHElementActorHuman *> >(g_pEngine, 0x4918)[(unsigned short)i];
        if (!FUN_00483070(candidate))
            continue;
        RHElementActorHuman *victim = candidate;
        SBGeoVector2D delta;
        {
            SBGeoVector2D other(RHActorField<SBGeoVector2D>(RHActorField<void *>(victim, 0x50), 0x24));
            delta = other;
        }
        {
            SBGeoVector2D own(RHActorField<SBGeoVector2D>(RHActorField<void *>(this, 0x50), 0x24));
            delta.FUN_005fc250(own);
        }
        if (delta.FUN_005fc700(1.0f) < 150.0f)
        {
            float along = delta.FUN_005fc660(direction);
            float across = delta.FUN_005fc660(perpendicular);
            if (minimum <= along && maximum >= along && (unsigned)abs((int)across) <= width / 2)
            {
                RHScriptNode *node = result->head;
                node->prev = ((RHUnk0046eb30 *)result)->Unk0059f720(node, node->prev);
                node = node->prev;
                RHScriptNode *previous = node->prev;
                *(RHScriptNode *volatile *)&previous->next = node;
                RHSequenceElement *const &payload = *(RHSequenceElement *const *)&victim;
                RHSeqList::CopyData((RHSequenceElement **)&node->data, &payload);
                unsigned count = result->count + 1;
                result->valid = 1;
                result->count = count;
            }
        }
    }
}

// Parked: the list-node access and nested vector/EH cleanup shape still differ.
// Parked: VC6 jump-threads the null first-opponent test that the target keeps.
// STUB: GAME 0x00482e50
void RHElementActorHuman::FUN_00482e50(RHHumanList *result, int weaponData)
{
    RHElementActorHuman *target = RHHumanFirstOpponent(this);
    if (target)
    {
        SBGeoVector2D delta;
        {
            SBGeoVector2D own(RHActorField<SBGeoVector2D>(RHActorField<void *>(this, 0x50), 0x24));
            delta = own;
        }
        {
            SBGeoVector2D other(RHActorField<SBGeoVector2D>(RHActorField<void *>(target, 0x50), 0x24));
            delta.FUN_005fc250(other);
        }
        float distance = ((RHUnk005fc3b0 *)&delta)->Unk005fc6a0(1.0f);
        if (RHActorField<RHHumanWeaponCalls *>(this, 0x25c)->FUN_005c1e80(weaponData) <= distance &&
            RHActorField<RHHumanWeaponCalls *>(this, 0x25c)->FUN_005c1ea0(weaponData) >= distance)
        {
            ((std::list<RHElementActorHuman *> *)result)->push_back(target);
            result->valid = 1;
        }
    }
}

// FUNCTION: GAME 0x00482fd0
void RHElementActorHuman::FUN_00482fd0(RHHumanList *result, int weaponData, bool alternate)
{
    unsigned type = ((RHUnk005c1d50 *)RHActorField<void *>(this, 0x25c))->FUN_005c1d50(weaponData);
    switch (type)
    {
    case 0: FUN_00482e50(result, weaponData); return;
    case 1: FUN_004828b0(result, weaponData); return;
    case 2:
    {
        FUN_00482b90(result, weaponData);
        return;
    }
    case 3:
    case 5: FUN_00482600(result, weaponData); return;
    case 4:
    case 6: FUN_00482390(result, weaponData, alternate); return;
    default: return;
    }
}

#include "RHElementActorCivilianCore.h"
#include "RHPortraitActorCalls.h"
#include "RHMalignityVisibilityCalls.h"

// Parked: recovered action eligibility needs byte-local and branch-layout alignment.
// STUB: GAME 0x00483160
bool RHElementActorHuman::FUN_00483160(void *context, RHElementActorHuman *target, unsigned type)
{
    if (!RHActorField<char>(this, 0x12))
        return false;
    if (type != 5 && type != 16 && RHActorField<unsigned>(g_pEngine, 0x4a00) > 1)
        return false;
    switch (type)
    {
    case 16:
    {
    bool armed = ((RHScriptBatchCalls *)target)->Unk0049d560(0x19) ||
        ((RHScriptBatchCalls *)target)->Unk0049d560(0x1a);
    bool action17 = ((RHScriptBatchCalls *)target)->Unk0049d560(0x17);
    bool action1d = ((RHScriptBatchCalls *)target)->Unk0049d560(0x1d);
    bool action18 = ((RHScriptBatchCalls *)target)->Unk0049d560(0x18);
    bool action1b = ((RHScriptBatchCalls *)target)->Unk0049d560(0x1b);
    bool standing = !((RHHumanVirtualCalls *)this)->V048() &&
        (RHActorField<unsigned>(this, 4) & 31) == 20 && !((RHHumanVirtualCalls *)this)->V0f8();
    if (!((RHHumanVirtualCalls *)this)->V048())
        ((RHHumanVirtualCalls *)this)->V0f8();
    bool teamZero = ((RHHumanVirtualCalls *)this)->V130() == 0;
    if (armed && (RHActorField<char>(this, 8) || !((RHHumanVirtualCalls *)this)->V0f4()))
        return RHActorField<RHSprite *>(this, 0x50)->FUN_005b9e30(context, RHActorField<void *>(this, 0x54), RHActorField<bool>(this, 8));
    if (((RHHumanVirtualCalls *)target)->V0f8() &&
        (RHActorField<char>(this, 8) || ((RHActorField<unsigned>(this, 4) & 31) == 4 &&
            ((RHElementActorCivilian *)this)->FUN_00470ca0())))
        return RHActorField<RHSprite *>(this, 0x50)->FUN_005b9e30(context, RHActorField<void *>(this, 0x54), RHActorField<bool>(this, 8));
    bool compatible = ((RHHumanVirtualCalls *)target)->V168() || !((RHHumanVirtualCalls *)this)->V0f8();
    bool available = !((RHHumanVirtualCalls *)this)->V048() ||
        ((RHActorField<unsigned>(this, 4) & 15) == 4 && RHActorField<int>(this, 0x4f0) != 0);
    bool permitted = RHActorField<char>(this, 8) || (compatible && available);
    if ((action17 && permitted) || (action1d && (RHActorField<char>(this, 8) || standing)))
        return RHActorField<RHSprite *>(this, 0x50)->FUN_005b9e30(context, RHActorField<void *>(this, 0x54), RHActorField<bool>(this, 8));
    if (action18 && (RHActorField<char>(this, 8) || (!((RHHumanVirtualCalls *)this)->V048() &&
            (RHActorField<unsigned>(this, 4) & 31) != 4 && teamZero)))
        return RHActorField<RHSprite *>(this, 0x50)->FUN_005b9e30(context, RHActorField<void *>(this, 0x54), RHActorField<bool>(this, 8));
    if (action1b && (RHActorField<char>(this, 8) || ((RHActorField<unsigned>(this, 4) & 15) == 4 &&
            !((RHHumanVirtualCalls *)this)->V048() && !((RHHumanVirtualCalls *)this)->V0f8() &&
            !((RHHumanVirtualCalls *)this)->V0f4())))
        return RHActorField<RHSprite *>(this, 0x50)->FUN_005b9e30(context, RHActorField<void *>(this, 0x54), RHActorField<bool>(this, 8));
    return false;
    }
    case 3:
        if (!RHActorField<char>(this, 8) && !((RHHumanVirtualCalls *)this)->V048() &&
            ((RHHumanVirtualCalls *)this)->V130() == 0 &&
            (RHActorField<unsigned>(this, 4) & 31) != 4 && RHActorField<char>(this, 0x1ce) &&
            ((RHActorField<unsigned>(this, 4) & 15) != 12 ||
                !((RHUnk005d73d0Actor *)this)->FUN_0049f510()) &&
            ((RHScriptBatchCalls *)target)->Unk0049d560(0x18))
            return RHActorField<RHSprite *>(this, 0x50)->FUN_005b9e30(context, RHActorField<void *>(this, 0x54), false);
        if (RHActorField<char>(this, 8) || !((RHMalignityVisibilityCalls *)this)->FUN_004860b0() ||
            RHActorField<int>(RHActorField<void *>(this, 0x50), 0x8c) == 7 || RHActorField<short>(this, 0x23c) != 0 ||
            ((RHHumanVirtualCalls *)this)->V0f4() || RHActorField<char>(this, 0xa6) ||
            (!((RHScriptBatchCalls *)target)->Unk0049d560(0x19) &&
                !((RHScriptBatchCalls *)target)->Unk0049d560(0x1a)))
            return false;
        return RHActorField<RHSprite *>(this, 0x50)->FUN_005b9e30(context, RHActorField<void *>(this, 0x54), false);
    default:
        return false;
    }
}

// Parked: action allocation, coordinate/heading setup, and enqueue ABI remain mismatched.
// STUB: GAME 0x00483500
unsigned RHElementActorHuman::FUN_00483500(void *context, unsigned command, RHElementActorHuman *target)
{
    unsigned type = RHActorField<unsigned>(this, 4);
    bool sameGroup = (type & 15) == 12;
    if (!sameGroup && (type & 31) == 20)
        sameGroup = ((RHHumanVirtualCalls *)target)->V130() ==
            ((RHHumanVirtualCalls *)this)->V130();
    if (sameGroup && RHActorField<char>(this, 0x1ce) &&
        ((RHScriptBatchCalls *)target)->Unk0049d560(0x18))
    {
        union { unsigned long address; void *(RHHumanAddressCalls::*call)(int, int, void *, void *); } createCall;
        createCall.address = 0x00585ea0;
        void *action = (((RHHumanAddressCalls *)context)->*createCall.call)(1, 0x4b, target, this);
        union { unsigned long address; unsigned (RHHumanAddressCalls::*call)(int, int, int, int, int, int, int); } enqueueCall;
        enqueueCall.address = 0x0049ffe0;
        (((RHHumanAddressCalls *)action)->*enqueueCall.call)(command, 0x28, 0, 0, 0, 0, 0);
        return 1;
    }
    bool enabled = ((RHHumanVirtualCalls *)this)->V048() || RHActorField<char>(this, 0x1ce);
    bool armed = ((RHScriptBatchCalls *)target)->Unk0049d560(0x19) ||
        ((RHScriptBatchCalls *)target)->Unk0049d560(0x1a);
    if (enabled && armed && !((RHHumanVirtualCalls *)this)->V0f0())
    {
        union { unsigned long address; void *(RHHumanAddressCalls::*call)(int, int, void *, void *); } createCall;
        createCall.address = 0x00585ea0;
        void *action = (((RHHumanAddressCalls *)context)->*createCall.call)(1, 0x65, target, this);
        union { unsigned long address; unsigned (RHHumanAddressCalls::*call)(int, int, int, int, int, int, int); } enqueueCall;
        enqueueCall.address = 0x0049ffe0;
        (((RHHumanAddressCalls *)action)->*enqueueCall.call)(command, 0x27, 0, 0, 0, 0, 0x80000);
        return 1;
    }
    union { unsigned long address; unsigned (RHHumanAddressCalls::*call)(void *, unsigned, void *); } fallbackCall;
    fallbackCall.address = 0x00463d80;
    return (((RHHumanAddressCalls *)context)->*fallbackCall.call)(this, command, target);
}

#define SBGEO_BOUNDINGBOX2D_VIEW
#include "RHActorSequenceStorage.h"

// Parked: group-comparison registers and sequence-address scheduling remain different.
// STUB: GAME 0x004837f0
void *RHElementActorHuman::FUN_004837f0(RHElementActorHuman *target)
{
    RHUnk0045aaf0 *sequence;
    bool alternate;
    if (RHActorField<char>(this, 0x1ce) &&
        ((RHScriptBatchCalls *)target)->Unk0049d560(0x18))
    {
        struct Kind4 { unsigned value : 4; };
        struct Kind5 { unsigned value : 5; };
        if (((Kind4 *)((char *)this + 4))->value == 12 ||
            ((Kind5 *)((char *)this + 4))->value == 20 &&
            ((RHHumanVirtualCalls *)this)->V130() == ((RHHumanVirtualCalls *)target)->V130())
        {
            sequence = (RHUnk0045aaf0 *)((char *)this + 0x14);
            sequence->FUN_0045abc0(0x5d, 0, 0);
            goto changed;
        }
    }
    if (!RHActorField<char>(this, 0x1ce) &&
        !((RHHumanVirtualCalls *)this)->V048())
    {
        goto fallback;
    }
    if (!((RHScriptBatchCalls *)target)->Unk0049d560(0x19) &&
        !((RHScriptBatchCalls *)target)->Unk0049d560(0x1a))
    {
        goto fallback;
    }
    if (RHActorField<int>(RHActorField<void *>(this, 0x50), 0x8c) != 7)
    {
        alternate = ((RHHumanVirtualCalls *)this)->V0f0();
        sequence = (RHUnk0045aaf0 *)((char *)this + 0x14);
        if (alternate)
        {
            sequence->FUN_0045abc0(0x5c, 0, 0);
            return sequence;
        }
        sequence->FUN_0045abc0(0x5b, 0, 0);
changed:
        RHActorField<char>(this, 0x92) = 1;
        RHActorField<int>(this, 0xa0) = 0;
        RHActorField<unsigned short>(this, 0xa4) = 2;
        return sequence;
    }
fallback:
    return (void *)((RHElementActor *)this)->FUN_00463d90((unsigned)target);
}

// deferred: coupled to RHScript::StopActor pending reccmp #534.
void RHUnk0047ca50::Unk()
{
    RHElementActorHuman *actor = (RHElementActorHuman *)this;
    unsigned count = actor->m_260.count;
    for (unsigned i = 0; i < count; ++i)
    {
        ((RHTitbitList *)&actor->m_260)->At(i);
        ((RHHumanActorCalls *)actor->m_260.cursor->data)->FUN_0047d270(this);
    }
    RHHumanList &list = actor->m_260;
    RHScriptNode *sentinel = list.head;
    RHScriptNode *current = sentinel->next;
    while (current != sentinel)
    {
        RHScriptNode *previous = current;
        current = current->next;
        ((RHUnk0046eb30 *)&list)->erase(RHScriptIter(previous));
    }
    list.valid = 1;
    if (!((RHHumanVirtualCalls *)this)->V048())
    {
        unsigned type = RHActorField<unsigned>(this, 4);
        if ((type & 15) == 12)
            ((RHHumanActorCalls *)this)->FUN_0049d780();
        else if ((type & 31) == 20)
        {
            int *base = RHActorField<int *>(this, 0x49c);
            ((RHScriptBatchCalls *)((char *)this + 0x49c + base[1]))->Unk0040d980(24);
        }
    }
}

// Parked: cached-cursor expansion and opponent-swap receiver scheduling differ.
// STUB: GAME 0x0047d920
void RHElementActorHuman::FUN_0047d920(RHElementActorHuman *actor)
{
    unsigned count = m_260.count;
    for (unsigned short i = 0; i < (unsigned short)count; ++i)
    {
        if (RHHumanOpponentAt(m_260, i).m_actor == actor)
        {
            ((RHTitbitList *)&m_260)->At(0);
            RHHumanOpponent &first = ((RHHumanOpponentNode *)m_260.cursor)->value;
            ((RHTitbitList *)&m_260)->At(i);
            RHHumanOpponent &selected = ((RHHumanOpponentNode *)m_260.cursor)->value;
            RHHumanOpponent previous = selected;
            selected = first;
            RHHumanOpponentAt(m_260, 0) = previous;
            ((RHHumanActorCalls *)this)->FUN_0047d4c0();
            return;
        }
    }
    if ((undefined)FUN_0047c4c0(actor))
    {
        RHUnk005866a0 *element = new RHUnk005866a0(1, 50, this);
        element->Unk00586ed0(33, (int)actor);
        element->Unk00586ed0(24, 0);
        element->Unk00586e00(34, false);
        ((RHScriptBatchCalls *)RHActorField<void *>(this, 0x5c))->Unk0058a940("", 0, element);
    }
}

// Parked: word narrowing and posture-result liveness still disagree after two bounded shapes.
// STUB: GAME 0x0047e7d0
int RHElementActorHuman::FUN_0047e7d0(RHUnk005864a0 *element)
{
    int result = 0;
    RHUnk005c1d50 *weapon = (RHUnk005c1d50 *)element->FUN_005864b0();
    if (RHActorField<int>(this, 0x144) == 11 || RHActorField<int>(this, 0x144) == 10)
    {
        if ((RHActorField<int>(this, 0x144) == 10 && element->FUN_005864d0() != 12 && element->FUN_005864d0() != 13) ||
            RHActorField<int>(this, 0x144) == 11)
            return 4;
    }
    else if (RHActorField<RHHumanWeaponCalls *>(this, 0x25c))
    {
        unsigned short chance = RHActorField<RHHumanWeaponCalls *>(this, 0x25c)->FUN_005c1b70(
            this, (void *)element->FUN_005864a0(), RHActorField<RHHumanWeaponCalls *>(this, 0x25c)->FUN_005c1d70(element->FUN_005864d0()));
        if (rand() % 99 + 1 > chance)
        {
            chance = weapon->FUN_005c1dd0(element->FUN_005864d0(), (void *)element->FUN_005864a0());
            if (chance > 0)
            {
                ((RHHumanVirtualCalls *)this)->V0bc(chance, (void *)element->FUN_005864a0());
                if (((RHHumanVirtualCalls *)this)->V048())
                {
                    unsigned count = RHActorField<unsigned>(RHActorField<void *>(this, 0x1c4), 8);
                    unsigned amount = 20;
                    unsigned other = RHActorField<unsigned>(RHActorField<void *>((void *)element->FUN_005864a0(), 0x1c4), 8);
                    if (count > other)
                        amount += count - other;
                    ((RHHumanVirtualCalls *)element->FUN_005864a0())->V0c8(0, amount);
                }
                result = 1;
            }
        }
        chance = RHActorField<unsigned short>(RHActorField<void *>(RHActorField<void *>(this, 0x25c), 4), 0x12);
        if (rand() % 99 + 1 > chance)
        {
            chance = ((RHHumanWeaponCalls *)weapon)->FUN_005c1db0(element->FUN_005864d0());
            if (chance > 0)
            {
                ((RHHumanVirtualCalls *)this)->V0d8(chance, (void *)element->FUN_005864a0());
                return result | 2;
            }
        }
    }
    else
        return 3;
    return result;
}

// FUNCTION: GAME 0x0047b660
void RHElementActorHuman::FUN_0047b660(const RHUnk00613e90 &point)
{
    int action = RHActorField<int>(this, 0x144);
    int state;
    ((RHHumanActorCalls *)this)->FUN_0047b8a0(point, &state, false);
    switch (state)
    {
    case 0:
        if (action == 5 && RHActorField<void *>(this, 0x134) &&
            RHActorField<int>(RHActorField<void *>(this, 0x134), 0x24) == 0x5c)
        {
            RHUnk00584d60 *element = new RHUnk00584d60(1, 0x21, this);
            ((RHScriptBatchCalls *)g_unk0x6c1040)->Unk0058a940("", 0, element);
        }
        break;
    case 1:
        if (action == 4 && RHActorField<void *>(this, 0x134) &&
            RHActorField<int>(RHActorField<void *>(this, 0x134), 0x24) == 0x59)
        {
            RHUnk00584d60 *element = new RHUnk00584d60(1, 0x22, this);
            ((RHScriptBatchCalls *)g_unk0x6c1040)->Unk0058a940("", 0, element);
        }
        break;
    }
}

// FUNCTION: GAME 0x0047e9a0
void RHElementActorHuman::FUN_0047e9a0(int amount, int source)
{
    ((RHHumanVirtualCalls *)this)->V0d4(
        ((RHHumanVirtualCalls *)this)->V0cc() - amount,
        (void *)source, true);
}

// FUNCTION: GAME 0x0047e9d0
void RHElementActorHuman::FUN_0047e9d0(RHUnk005864a0 *element)
{
    unsigned short value = RHActorField<unsigned short>(element, 0x68);
    ((RHHumanVirtualCalls *)this)->V0bc(value, (void *)element->FUN_005864a0());
    value = RHActorField<unsigned short>(element, 0x6a);
    ((RHHumanVirtualCalls *)this)->V0d8(value, (void *)element->FUN_005864a0());
}

// Parked: cached-list branch merging and the V124 return-width view differ.
// STUB: GAME 0x0047ea20
unsigned short RHElementActorHuman::FUN_0047ea20()
{
    unsigned short total = 0;
    unsigned count = m_260.count;
    for (unsigned i = 0; i < count; ++i)
        total += ((RHHumanVirtualCalls *)RHHumanStrengthOpponentAt(m_260, i).m_actor)->V124();
    return total;
}

// FUNCTION: GAME 0x0047ebc0
void RHElementActorHuman::FUN_0047ebc0()
{
    unsigned short own = ((RHHumanVirtualCalls *)this)->V124();
    unsigned short other = FUN_0047ea20();
    if (own == other)
        m_28a = 50;
    else
        m_28a = own * 100 / (own + other);
}

// FUNCTION: GAME 0x004838f0
int RHElementActorHuman::FUN_004838f0(bool alternate)
{
    switch (RHActorField<int>(RHActorField<void *>(this, 0x50), 0x8c))
    {
    case 1:
    case 6:
    case 8:
    case 11:
    case 14:
    case 15:
    case 19:
    case 21:
    case 23:
    case 24:
        switch (RHActorField<unsigned>(this, 0x144))
        {
        case 0:
        case 1:
        case 2:
        case 3:
        case 12:
        case 14:
        case 16:
        case 17:
            return alternate ? 0x137 : 0x133;
        case 4:
        case 5:
        case 6:
            return alternate ? 0x138 : 0x134;
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 15:
            return alternate ? 0x139 : 0x135;
        case 13:
            break;
        }
        return alternate ? 0x137 : 0x133;
    case 10:
    case 20:
    case 22:
        return alternate ? 0x13a : 0x136;
    default:
        return 0x11b;
    }
}

class RHSequenceElementDamage
{
public:
    bool FUN_005864e0();
};

// FUNCTION: GAME 0x00483c90
void RHElementActorHuman::FUN_00483c90(RHActorTranslationSequenceCalls *sequence)
{
    switch (RHActorField<int>(RHActorField<void *>(this, 0x50), 0x8c))
    {
    case 3: case 7: case 9: case 12: case 13: case 16: case 17: case 18:
        sequence->V0c(0, true);
        return;
    }
    ((RHHumanVirtualCalls *)this)->V164();
    RHOrder *order = new RHOrder;
    order->m_24 = FUN_004838f0(((RHSequenceElementDamage *)sequence)->FUN_005864e0());
    order->m_2a = 0;
    order->m_30 = (void *)((RHUnk005864a0 *)sequence)->FUN_005864a0();
    sequence->FUN_00585970(order);
    ((RHHumanVirtualCalls *)this)->V154(sequence);
}

#include "RHSectorProductionPC.h"

// FUNCTION: GAME 0x00484360
void RHSectorProductionPC::FUN_00484360(int amount)
{
    short value = ((RHHumanVirtualCalls *)this)->V0cc() + amount;
    if (value > 100)
        ((RHHumanVirtualCalls *)this)->V0d4(100, 0, true);
    else
        ((RHHumanVirtualCalls *)this)->V0d4(value, 0, true);
}

// Parked: neutral-constant lifetime changes the frame and switch scheduling; two complete shapes exhausted.
// STUB: GAME 0x00483d90
void RHElementActorHuman::FUN_00483d90(RHActorTranslationSequenceCalls *sequence, unsigned flags)
{
    int third = 0x11b;
    int second = third;
    int first;
    ((RHHumanVirtualCalls *)this)->V164();
    if (((RHHumanVirtualCalls *)this)->V0f4() && ((RHHumanVirtualCalls *)this)->V048())
        first = 0x29;
    else
    {
        switch (RHActorField<int>(RHActorField<void *>(this, 0x50), 0x8c))
        {
        case 1: case 6: case 8: case 11: case 14: case 15:
        case 19: case 21: case 23: case 24:
            switch (RHActorField<unsigned>(this, 0x144))
            {
            case 0: case 1: case 2: case 3: case 12: case 13: case 14: case 16: case 17:
                first = 0x13b; second = 0x31; break;
            case 4: case 5: case 6:
                first = 0x13c; second = 0x75; break;
            case 7: case 8: case 9: case 10: case 11: case 15:
                first = 0x13d; second = 0x6e; third = 0x67; break;
            default:
                return;
            }
            break;
        case 10: case 20: case 22:
            first = 0x13e;
            break;
        case 4: case 5:
            FUN_004752d0(sequence);
            return;
        default:
            if (((RHHumanVirtualCalls *)this)->V048())
                ((RHHumanVirtualCalls *)this)->V044(12);
            else if (RHActorField<char>(this, 0x1ce))
                ((RHHumanVirtualCalls *)this)->V044(3);
            return;
        }
    }
    RHOrder *order = new RHOrder;
    order->m_24 = first;
    order->m_2a = 0;
    order->m_30 = (void *)((RHUnk005864a0 *)sequence)->FUN_005864a0();
    sequence->FUN_00585970(order);
    if (!((RHHumanVirtualCalls *)this)->V048() && !RHActorField<char>(this, 0x1ce) && (flags & 2))
    {
        order = new RHOrder;
        order->m_24 = second;
        order->m_2a = 0;
        order->m_30 = (void *)((RHUnk005864a0 *)sequence)->FUN_005864a0();
        sequence->FUN_00585970(order);
        if (third != 0x11b && RHActorField<unsigned short>(this, 0x1c8) > 40)
        {
            order = new RHOrder;
            order->m_24 = third;
            order->m_2a = 0;
            order->m_30 = (void *)((RHUnk005864a0 *)sequence)->FUN_005864a0();
            sequence->FUN_00585970(order);
        }
    }
    ((RHHumanVirtualCalls *)this)->V154(sequence);
}

// FUNCTION: GAME 0x00484610
void RHElementActorHuman::FUN_00484610(RHActorTranslationSequenceCalls *sequence)
{
    void *area = RHActorField<void *>(RHActorField<void *>(this, 0x50), 0xec);
    SBGeoPoint2D point;
    if (((RHActorCrossingHumanCalls *)this)->FUN_004843a0(area) &&
        ((RHActorCrossingHumanCalls *)this)->FUN_004843d0(point, area, false))
    {
        RHOrder *order = new RHOrder;
        order->m_24 = 0x7f;
        RHActorField<SBGeoPoint2D>(order, 0x14) = point;
        sequence->FUN_00585970(order);
    }
}

#include "RHPathQueryCalls.h"

// FUNCTION: GAME 0x004847c0
void *RHElementActorHuman::FUN_004847c0(float maximum, void *filter) const
{
    void *area = RHActorField<void *>(RHActorField<void *>((void *)this, 0x50), 0xe0);
    float nearest = 1.0e15f;
    void *result = 0;
    unsigned count = RHActorField<unsigned>(area, 0xd0);
    for (unsigned index = 0; index < count; ++index)
    {
        RHHumanList &list = RHActorField<RHHumanList>(area, 0xc8);
        ((RHPathQueryCalls *)&list)->FUN_005c8e40(index);
        void *entry = list.cursor->data;
        if (!filter || RHActorField<void *>(RHActorField<void *>(entry, 0x20), 0x1c) == filter)
        {
            float distance = ((RHUnk0042fde0 *)((char *)entry + 4))->FUN_0060b7a0(
                RHActorField<SBGeoPoint2D>(RHActorField<void *>((void *)this, 0x50), 0x24));
            if (distance < nearest && distance < maximum)
            {
                nearest = distance;
                result = entry;
            }
        }
    }
    return result;
}


inline float RHHumanJumpHeight(void *line)
{
    return RHActorField<float>(line, 0x30);
}

inline void *RHHumanSector(const RHElementActorHuman *actor)
{
    return RHActorField<void *>(RHActorField<void *>((void *)actor, 0x50), 0xe0);
}

inline const SBGeoPoint2D &RHHumanPosition(const RHElementActorHuman *actor)
{
    return RHActorField<SBGeoPoint2D>(RHActorField<void *>((void *)actor, 0x50), 0x24);
}

inline void RHHumanJumpCenter(void *line, SBGeoPoint2D &center)
{
    center.m_x = (RHActorField<float>(line, 0x0c) + RHActorField<float>(line, 4)) * 0.5f;
    center.m_y = (RHActorField<float>(line, 0x10) + RHActorField<float>(line, 8)) * 0.5f;
}

// FUNCTION: GAME 0x00484870
void *RHElementActorHuman::FUN_00484870(RHElementActorHuman *actor)
{
    void *sector = RHActorField<void *>(RHActorField<void *>(this, 0x50), 0xe0);
    if (sector == RHActorField<void *>(RHActorField<void *>(actor, 0x50), 0xe0))
        return 0;
    float maximum = ((RHMalignityAbilityCalls *)RHActorField<void *>(this, 0x25c))->FUN_005c1b50(2);
    void *line = actor->FUN_004847c0(maximum, RHHumanSector(this));
    if (!line)
        return 0;
    void *linked = RHActorField<void *>(line, 0x20);
    if ((float)fabs(RHHumanJumpHeight(linked) - RHHumanJumpHeight(line)) > 40.0f)
        return 0;
    SBGeoPoint2D first;
    SBGeoPoint2D second;
    RHHumanJumpCenter(linked, second);
    RHHumanJumpCenter(line, first);
    if (((RHUnk0042fde0 *)((char *)line + 4))->FUN_0060b7a0(RHHumanPosition(actor)) +
        ((RHUnk005fc3b0 *)&second.Unk005fc110(first))->Unk005fc6a0(1.0f) > maximum)
        return 0;
    return linked;
}

// Parked: cached-cursor reset and advance paths merge differently.
// STUB: GAME 0x00484a70
int RHElementActorHuman::FUN_00484a70(void *value)
{
    unsigned count = m_260.count;
    int result = 0;
    if (count != 0)
    {
        for (int i = 0; i < count; ++i)
        {
            void *actor = RHHumanOpponentAt(m_260, i).m_actor;
            if (RHActorField<void *>(RHActorField<void *>(actor, 0x50), 0xe0) == value)
                ++result;
        }
    }
    return result;
}

// Parked: cached-list expansion, local frame size and x87 scheduling differ.
// STUB: GAME 0x00484bb0
bool RHElementActorHuman::FUN_00484bb0(RHElementActorHuman *actor, SBGeoPoint2D &result, void *line)
{
    unsigned count = actor->m_260.count;
    void *area = RHActorField<void *>(RHActorField<void *>(this, 0x50), 0xe0);
    RHUnk0042fde0 *segment = (RHUnk0042fde0 *)((char *)line + 4);
    SBGeoVector2D direction = segment->FUN_0042fde0();
    float margin = 15.0f / ((RHUnk005fc3b0 *)&direction)->Unk005fc6a0(1.0f);
    char allocator;
    RHHumanFloatList fractions(allocator);
    float position = segment->FUN_0060ba80(RHActorField<SBGeoPoint2D>(RHActorField<void *>(this, 0x50), 0x24));
    float fraction;
    for (unsigned i = 0; i < count; ++i)
    {
        ((RHTitbitList *)&actor->m_260)->At((unsigned short)i);
        void *opponent = actor->m_260.cursor->data;
        if (opponent != this && RHActorField<void *>(RHActorField<void *>(opponent, 0x50), 0xe0) == area)
        {
            fraction = segment->FUN_0060ba80(RHActorField<SBGeoPoint2D>(RHActorField<void *>(opponent, 0x50), 0x24));
            fractions.FUN_00424410(RHHumanFloatIterator(fractions.m_head), fraction);
            fractions.valid = 1;
        }
    }
    float lower;
    switch (fractions.m_count)
    {
    case 0:
        if (position >= 1.0f)
            result = RHActorField<SBGeoPoint2D>(line, 0x0c);
        else if (position <= 0.0f)
            result = *(SBGeoPoint2D *)segment;
        else
            result = ((SBGeoPoint2D *)segment)->Unk005fc190(operator*(position, (const SBGeoVector2D &)direction));
        return true;
    case 1:
        lower = fraction - margin;
        margin += fraction;
        break;
    case 2:
    {
        lower = fractions.m_head->next->value;
        fractions.At(1);
        float other = fractions.cursor->value;
        if (lower > other)
        {
            float temporary = lower;
            lower = other;
            other = temporary;
        }
        lower -= margin;
        margin += other;
        break;
    }
    default:
        return false;
    }
    if (position >= 0.0f && position <= 1.0f &&
        (position <= lower || position >= margin))
    {
        result = RHActorField<SBGeoPoint2D>(RHActorField<void *>(this, 0x50), 0x24);
        return true;
    }
    if (lower >= 0.0f)
    {
        if (margin <= 1.0f)
        {
            result = ((SBGeoPoint2D *)segment)->Unk005fc190(operator*(margin, (const SBGeoVector2D &)direction));
            SBGeoPoint2D alternate = ((SBGeoPoint2D *)segment)->Unk005fc190(operator*(lower, (const SBGeoVector2D &)direction));
            SBGeoPoint2D &current = RHActorField<SBGeoPoint2D>(RHActorField<void *>(this, 0x50), 0x24);
            if (current.Unk005fc110(alternate).Unk005fc6d0(1.0f) < current.Unk005fc110(result).Unk005fc6d0(1.0f))
                result = alternate;
        }
        else
            result = ((SBGeoPoint2D *)segment)->Unk005fc190(operator*(lower, (const SBGeoVector2D &)direction));
        fractions.FUN_0044e8b0(fractions.FUN_0046eb80(), RHHumanFloatIterator(fractions.m_head));
        return true;
    }
    if (margin <= 1.0f)
    {
        result = ((SBGeoPoint2D *)segment)->Unk005fc190(operator*(margin, (const SBGeoVector2D &)direction));
        fractions.Release();
        return true;
    }
    fractions.Release();
    return false;
}

// FUNCTION: GAME 0x004851b0
void RHElementActorHuman::FUN_004851b0(unsigned short value, void *owner)
{
    RHActorField<unsigned short>(RHActorField<void *>(this, 0x50), 0xde) = value;
    RHActorField<void *>(RHActorField<void *>(this, 0x50), 0xe0) = owner;
    if (((RHHumanTypeView *)this)->Type() == 12)
    {
        RHElementActorHuman *other = RHActorField<RHElementActorHuman *>(this, 0x5cc);
        if (other)
        {
            RHActorField<unsigned short>(RHActorField<void *>(other, 0x50), 0xde) = value;
            RHActorField<void *>(RHActorField<void *>(other, 0x50), 0xe0) = owner;
        }
    }
    FUN_0047d1b0();
}

extern float g_unk0x006774a0;

inline int RHHumanFindActor(void *actor, RHElementActorHuman *const &value)
{
    RHHumanList &list = RHActorField<RHHumanList>(actor, 0x19c);
    typedef std::list<RHElementActorHuman *> Actors;
    Actors::iterator &cursor = (Actors::iterator &)list.cursor;
    RHScriptNode *head = list.head;
    int count = list.count;
    RHActorField<RHElementActorHuman *>(actor, 0x1bc) = value;
    RHActorField<undefined>(actor, 0x1b4) = 1;
    list.cursor = head->next;
    int index = 0;
    while (index < count)
    {
        if (*cursor == RHActorField<RHElementActorHuman *>(actor, 0x1bc))
            break;
        ++index;
        ++cursor;
    }
    if (index < count)
    {
        RHActorField<int>(actor, 0x1b8) = index;
        list.valid = 0;
        list.index = index;
    }
    else
    {
        list.valid = 1;
        RHActorField<int>(actor, 0x1b8) = -1;
    }
    return RHActorField<int>(actor, 0x1b8);
}

inline unsigned short RHHumanCandidateCount(void *engine)
{
    void **first = RHActorField<void **>(engine, 0x48dc);
    return first ? RHActorField<void **>(engine, 0x48e0) - first : 0;
}

// Parked at 0.6095: engine-vector register allocation and cached-list cursor reload differ.
// STUB: GAME 0x004857b0
void RHElementActorHuman::FUN_004857b0(RHHumanList &result)
{
    unsigned short remaining = m_23c;
    unsigned short count = RHHumanCandidateCount(g_pEngine);
    for (unsigned short index = 0; index < count && remaining > 0; ++index)
    {
        void *actor = RHActorField<void **>(g_pEngine, 0x48dc)[index];
        if ((RHActorField<unsigned>(actor, 4) & 3) == 3 &&
            RHActorField<int>(actor, 0xb0) == 9 && RHHumanFindActor(actor, this) != -1)
        {
            ((std::list<void *> *)&result)->push_back(actor);
            result.valid = 1;
            --remaining;
        }
    }
}

// FUNCTION: GAME 0x00485940
void RHElementActorHuman::FUN_00485940(int color, unsigned short value, bool completed, float duration)
{
    double ticks = duration;
    ticks *= g_unk0x006774a0;
    RHActorField<bool>(this, 0x48a) = completed;
    RHActorField<float>(this, 0x48c) = duration;
    RHActorField<int>(this, 0x480) = RHActorField<int>(this, 0x484) = (int)ticks;
    RHActorField<int>(this, 0xa0) = color;
    RHActorField<unsigned short>(this, 0xa4) = value;
}

inline unsigned RHHumanKind(void *actor, unsigned mask)
{
    return RHActorField<volatile unsigned>(actor, 4) & mask;
}

// Parked at 0.5524: kind-mask registers and virtual-call/return paths differ.
// STUB: GAME 0x004859b0
char RHActorPCHumanCalls::FUN_004859b0(void *target)
{
    RHHumanVirtualCalls *actor = RHActorField<RHHumanVirtualCalls *>(target, 0x12c);
    unsigned type = RHHumanKind(actor, 15);
    if ((unsigned char)type == 4)
    {
        unsigned own = RHHumanKind(this, 31);
        if ((unsigned char)own == (unsigned char)type)
            return 0;
        int camp = actor->V130();
        return ((RHHumanVirtualCalls *)this)->V130() != camp;
    }
    else
    {
        if (RHActorField<int>(((RHUnk0055dbb0 *)g_unk0x006c0e48)->FUN_0055dbb0(), 0x1c) == 2)
            goto accepted;
        unsigned own = RHHumanKind(this, 31);
        if ((unsigned char)own == 4)
            return 0;
        int camp = actor->V130();
        if (((RHHumanVirtualCalls *)this)->V130() != camp)
            goto accepted;
    }
    return 0;
accepted:
    return 1;
}

#include <algorithm>

// Parked at 0.7273: layer word-store width and accessor scheduling differ.
// STUB: GAME 0x00485a40
void RHElementActorHuman::FUN_00485a40(void *result, unsigned short &heading)
{
    SBGeoPoint2D point;
    void *line = RHActorField<void *>(RHActorField<void *>(this, 0x50), 0xf4);
    void *sector;
    volatile unsigned short layer;
    bool forward;
    if ((char)((RHElementActor *)this)->FUN_0046e960() && line)
    {
        if (RHActorField<char>(this, 0x1a4))
        {
            layer = RHActorField<unsigned short>(line, 0x16);
            sector = RHActorField<void *>(line, 0x10);
            point = RHActorField<SBGeoPoint2D>(line, 0x20);
            switch (RHActorField<int>(line, 0x88))
            {
            case 2: case 4: case 6:
                forward = false;
                break;
            default:
                forward = true;
            }
        }
        else
        {
            layer = RHActorField<unsigned short>(line, 0x14);
            sector = RHActorField<void *>(line, 0x0c);
            point = RHActorField<SBGeoPoint2D>(line, 0x18);
            switch (RHActorField<int>(line, 0x88))
            {
            case 2: case 4: case 6:
                forward = true;
                break;
            default:
                forward = false;
            }
        }
    }
    else
    {
        sector = RHHumanSector(this);
        layer = RHActorField<unsigned short>(RHActorField<void *>(this, 0x50), 0xde);
        point = RHHumanPosition(this);
        forward = RHActorField<float>(RHActorField<void *>(this, 0x50), 0x140) > 0.0f;
    }
    unsigned flags = RHActorField<unsigned>(sector, 0x30);
    if ((unsigned char)(flags >> 9) & 1)
    {
        if (forward)
        {
            void *&exit = RHActorField<void *>(sector, 0x104);
            sector = RHActorField<void *>(exit, 0x0c);
            layer = RHActorField<unsigned short>(exit, 0x14);
            point = RHActorField<SBGeoPoint2D>(exit, 0x18);
            unsigned short direction = ((RHUnk005fc3b0 *)&RHActorField<SBGeoPoint2D>(exit, 0x18).Unk005fc110(
                RHActorField<SBGeoPoint2D>(exit, 0x94)))->FUN_005fcc50(0.57357645f);
            heading = direction;
        }
        else
        {
            void *&exit = RHActorField<void *>(sector, 0x100);
            sector = RHActorField<void *>(exit, 0x0c);
            layer = RHActorField<unsigned short>(exit, 0x14);
            point = RHActorField<SBGeoPoint2D>(exit, 0x18);
            unsigned short direction = ((RHUnk005fc3b0 *)&RHActorField<SBGeoPoint2D>(exit, 0x18).Unk005fc110(
                RHActorField<SBGeoPoint2D>(exit, 0x94)))->FUN_005fcc50(0.57357645f);
            heading = direction;
        }
    }
    else if (((unsigned char)(flags >> 13) & 1) && RHActorField<char>(this, 0x1a4))
    {
        RHHumanList &lines = RHActorField<RHHumanList>(sector, 0x5c);
        unsigned short count = lines.count;
        if (count > 1)
        {
            void *exit;
            do
            {
                ((RHPathQueryCalls *)&lines)->FUN_005c8e40(rand() % count);
                exit = lines.cursor->data;
            } while (exit == line);
            layer = RHActorField<unsigned short>(exit, 0x14);
            sector = RHActorField<void *>(exit, 0x0c);
            point = RHActorField<SBGeoPoint2D>(exit, 0x18);
            heading = ((RHUnk005fc3b0 *)&RHActorField<SBGeoPoint2D>(exit, 0x18).Unk005fc110(
                RHActorField<SBGeoPoint2D>(exit, 0x20)))->FUN_005fcc50(0.57357645f);
        }
    }
    else
        heading = RHActorField<unsigned short>(RHActorField<void *>(this, 0x50), 0xd8);
    float x = point.m_x;
    RHActorField<float>(result, 4) = point.m_y;
    RHActorField<float>(result, 0) = x;
    RHActorField<void *>(result, 8) = sector;
    RHActorField<unsigned short>(result, 0x0c) = layer;
}

// FUNCTION: GAME 0x00485d20
void RHElementActorHuman::FUN_00485d20(RHSequenceElement *element)
{
    typedef std::list<RHSequenceElement *> Elements;
    Elements &elements = *(Elements *)&m_1b8;
    if (std::find(elements.begin(), elements.end(), element) == elements.end())
    {
        RHScriptNode *next = m_1b8.head;
        RHScriptNode *previous = next->prev;
        RHScriptNode *node = (RHScriptNode *)::operator new(sizeof(RHScriptNode));
        node->next = next ? next : node;
        node->prev = previous ? previous : node;
        next->prev = node;
        node->prev->next = node;
        new (&node->data) void *(element);
        ++m_1b8.count;
    }
}

// FUNCTION: GAME 0x00485d90
void RHElementActorHuman::FUN_00485d90()
{
    if (m_1b8.count > 0)
    {
        int state = RHActorField<int>(RHActorField<void *>(this, 0x50), 0x1dc);
        if ((state == 0x59 || state == 0x5c) &&
            ((RHHumanVirtualCalls *)this)->V050(((std::list<RHSequenceElement *> *)&m_1b8)->front()))
        {
            RHScriptNode *node = m_1b8.head->next;
            node->prev->next = node->next;
            node->next->prev = node->prev;
            ::operator delete(node);
            --m_1b8.count;
        }
    }
}

// FUNCTION: GAME 0x00485e00
int RHElementActorHuman::FUN_00485e00()
{
    bool empty = m_1b8.count == 0;
    RHScriptNode *head = m_1b8.head;
    RHScriptNode *node = head->next;
    while (node != head)
    {
        RHScriptNode *old = node;
        node = node->next;
        old->prev->next = old->next;
        old->next->prev = old->prev;
        ::operator delete(old);
        --m_1b8.count;
    }
    return !empty;
}

// FUNCTION: GAME 0x00485e60
bool RHArtificialIntelligenceActorCalls::Unk00485e60()
{
    void *data = *(void **)((char *)this + 0x50);
    return *(void **)((char *)data + 0xf4) != 0 ||
        ((unsigned short)(*(unsigned *)((char *)(*(void **)((char *)data + 0xe0)) + 0x30) >> 13) & 1) != 0;
}

// FUNCTION: GAME 0x00485e90
void RHElementActorHuman::FUN_00485e90(int value)
{
    int previous = RHActorField<int>(RHActorField<void *>(this, 0x50), 0x8c);
    bool wasBlocking = previous == 3 || previous == 13 || previous == 12 || previous == 18 || previous == 17;
    ((RHElementActor *)this)->FUN_00462940(value);
    bool isBlocking = value == 3 || value == 13 || value == 12 || value == 18 || value == 17;
    if (wasBlocking)
    {
        if (!isBlocking)
            g_pEngine->FUN_004e39b0(this, false);
    }
    else if (isBlocking)
        g_pEngine->FUN_004e39b0(this, true);
}

class RHHumanVisibilityDispatch
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
    virtual bool V48() = 0;
};

class RHMapBox
{
public:
    RHMapBox(float left, float top, float right, float bottom);
    SBGeoPoint2D m_first;
    SBGeoPoint2D m_second;
    int m_10;
};

class RHMobileUnk006091b0
{
public:
    RHMobileUnk006091b0 &FUN_006091b0(const SBGeoPoint2D &point);
};

class RHMobileUnk00607da0
{
public:
    void FUN_00607990(const RHMobileUnk00607da0 &other);
    RHMobileUnk00607da0 &FUN_00607da0(const RHMobileUnk00607da0 &other);
    undefined m_00[0x14];
};

class RHMalignityGridCalls
{
public:
    bool FUN_004f5e50(SBGeoBoundingBox2D &box, const SBGeoPoint2D &point, unsigned short layer);
};

class RHUnkPathActorInfoBase
{
public:
    void *Unk0055fa10(int value);
};

inline SBGeoBoundingBox2D *RHHumanPositionBounds(void *base)
{
    return (SBGeoBoundingBox2D *)((RHUnkPathActorInfoBase *)base)->Unk0055fa10(RHActorField<int>(base, 0x88));
}

inline unsigned short RHHumanLayer(const RHElementActorHuman *actor)
{
    return RHActorField<unsigned short>(RHActorField<void *>((void *)actor, 0x50), 0xde);
}

inline void RHHumanUpdatePosition(void *base, const SBGeoPoint2D &point)
{
    RHActorField<SBGeoPoint2D>(base, 0x20) = point;
    {
        SBGeoVector2D offset((const SBGeoVector2D &)point);
        ((RHMobileUnk00607da0 *)((char *)base + 0xc0))->FUN_00607da0(
            (const RHMobileUnk00607da0 &)RHHumanPositionBounds(base)->FUN_006090d0(offset));
    }
    RHActorField<int>(base, 4) = 2;
}

// FUNCTION: GAME 0x00485f20
void RHElementActorHuman::FUN_00485f20()
{
    RHMapBox bounds(-10.0f, -5.0f, 10.0f, 5.0f);
    {
        SBGeoVector2D offset(RHActorField<SBGeoVector2D>(RHActorField<void *>(this, 0x50), 0x24));
        ((RHMobileUnk006091b0 *)&bounds)->FUN_006091b0(offset);
    }
    if (((RHMalignityGridCalls *)RHActorField<void *>(this, 0x64))->FUN_004f5e50(
        (SBGeoBoundingBox2D &)bounds, RHHumanPosition(this), RHHumanLayer(this)))
    {
        RHHumanUpdatePosition((char *)RHActorField<void *>(this, 0x50) + 4,
            ((SBGeoBoundingBox2D *)&bounds)->FUN_00608f40());
        ((RHBonusInfoBase *)((char *)RHActorField<void *>(this, 0x50) + 4))->FUN_0055f290();
        ((RHBonusInfo *)RHActorField<void *>(this, 0x50))->FUN_005bd560(0, true);
    }
}

// FUNCTION: GAME 0x004860b0
bool RHMalignityVisibilityCalls::FUN_004860b0()
{
    int state = *(int *)(*(char **)((char *)this + 0x50) + 0x8c);
    return ((RHHumanVisibilityDispatch *)this)->V48() ||
        *((char *)this + 0x1ce) ||
        *(short *)((char *)this + 0x23c) != 0 ||
        state == 0x12 || state == 7 ||
        (*(unsigned *)((char *)this + 4) & 0xf) == 0xc && ((RHUnk005d73d0Actor *)this)->FUN_0049f510();
}

// FUNCTION: GAME 0x00486110
RHHumanOpponentIterator RHHumanOpponentListCalls::FUN_00486110(RHHumanOpponentIterator position, const RHHumanOpponent &value)
{
    RHHumanOpponentNode *next = position.node;
    RHHumanOpponentNode *previous = next->previous;
    RHHumanOpponentNode *node = (RHHumanOpponentNode *)::operator new(sizeof(RHHumanOpponentNode));
    node->next = next ? next : node;
    node->previous = previous ? previous : node;
    next->previous = node;
    node->previous->next = node;
    new (&node->value) RHHumanOpponent(value);
    ++((RHHumanList *)this)->count;
    return RHHumanOpponentIterator(node);
}

// FUNCTION: GAME 0x0048c5b0
void FUN_0048c5b0(void *actor, int value)
{
    unsigned short count = ((RHHumanEngineActorArray *)g_pEngine)->Size();
    for (unsigned short i = 0; i < count; ++i)
        ((RHHumanEngineActorArray *)g_pEngine)->m_first[i]->FUN_0048c700(actor, value);
    if (value == 1)
        RHActorField<undefined>(actor, 0x23f) = 1;
}

// FUNCTION: GAME 0x005864a0
undefined4 RHUnk005864a0::FUN_005864a0()
{
    return m_64;
}

// FUNCTION: GAME 0x005864b0
undefined4 RHUnk005864a0::FUN_005864b0()
{
    return m_70;
}

// FUNCTION: GAME 0x005864c0
undefined4 RHUnk005864a0::FUN_005864c0()
{
    return m_78;
}

// FUNCTION: GAME 0x005864d0
undefined4 RHUnk005864a0::FUN_005864d0()
{
    return m_74;
}

// FUNCTION: GAME 0x00586f70
void RHUnk00586f70::FUN_00586f70(int key, undefined value)
{
    *(undefined *)&m_64.find(key)->m_value = value;
}

// FUNCTION: GAME 0x005870c0
undefined RHUnk00586f70::FUN_005870c0(int key)
{
    return *(undefined *)&m_64.find(key)->m_value;
}

// FUNCTION: GAME 0x00587340
undefined4 RHUnk00586f70::FUN_00587340(int key)
{
    RHHumanMapIterator position = m_64.find(key);
    if (position != m_64.end())
        return position->m_value;
    return *(volatile int *)&key;
}

struct RHUnk0058bed0List
{
    std::list<RHUnk0058bed0Object *> m_list;
    std::list<RHUnk0058bed0Object *>::iterator m_current;
};

// FUNCTION: GAME 0x0058bed0
void RHManagerListCalls::FUN_0058bed0()
{
    RHUnk0058bed0List &self = *(RHUnk0058bed0List *)this;
    std::list<RHUnk0058bed0Object *>::iterator end;
    for (self.m_current = self.m_list.begin(); end = self.m_list.end(), self.m_current != end; ++self.m_current)
        delete *self.m_current;
    self.m_list.clear();
}

// FUNCTION: GAME 0x005a8220
bool RHSound::FUN_005a8220(int first, int second, int third, const SBGeoPoint2D &point)
{
    if (RHActorField<undefined>(this, 0x20b))
    {
        RHSoundSettings sound;
        sound.m_00 = 3;
        *(SBGeoPoint2D *)sound.m_04 = point;
        int variant = (rand() * 2) * 0.00003051850944757461548f;
        *(undefined *)sound.m_10 = 0;
        sound.m_0c = (void *)(variant + (g_unk0x006b793c[third + second * 4] + first * 10) * 2);
        RHSoundChannelSettings settings;
        if (((RHSoundGeometryView *)((char *)this + 0x138))->FUN_005b2ff0(sound, false, settings))
            FUN_005a72c0(sound, settings, 0);
        else
            return false;
    }
    return true;
}

// FUNCTION: GAME 0x005a8330
bool RHSound::FUN_005a8330(int first, int second, int third, const SBGeoPoint2D &point)
{
    if (RHActorField<undefined>(this, 0x20b))
    {
        RHSoundSettings sound;
        sound.m_00 = 3;
        *(SBGeoPoint2D *)sound.m_04 = point;
        *(undefined *)sound.m_10 = 0;
        sound.m_0c = (void *)(g_unk0x006b797c[third + second * 3] + first * 12 + 30);
        RHSoundChannelSettings settings;
        if (((RHSoundGeometryView *)((char *)this + 0x138))->FUN_005b2ff0(sound, false, settings))
            FUN_005a72c0(sound, settings, 0);
        else
            return false;
    }
    return true;
}

extern float g_unk0x006774a0;

// Parked: the original spills the facing direction to the actor argument slot; VC6 keeps it in EBX.
// STUB: GAME 0x005c1b70
unsigned short RHHumanWeaponCalls::FUN_005c1b70(void *actor, void *target, unsigned value)
{
    unsigned short direction = RHActorField<unsigned short>(RHActorField<void *>(actor, 0x50), 0xd8);
    unsigned short facing = ((RHUnk005fc3b0 *)&((RHUnk004237d0 *)target)->FUN_004237d0().Unk005fc110(
        ((RHUnk004237d0 *)actor)->FUN_004237d0()))->FUN_005fcc50(0.57357645f);
    float targetZ = RHActorField<float>(RHActorField<void *>(target, 0x50), 0x18);
    float actorZ = RHActorField<float>(RHActorField<void *>(actor, 0x50), 0x18);
    if (targetZ >= actorZ + g_unk0x006774a0)
        return *(unsigned short *)(*(char **)((char *)this + 4) + 8);
    unsigned short side = direction;
    switch (value)
    {
    case 0:
        side = facing + 4;
        break;
    case 1:
        side = facing - 4;
        break;
    case 2:
        side = facing;
        break;
    }
    switch ((side - direction) & 0xf)
    {
    case 0: case 1: case 15:
        return *(unsigned short *)(*(char **)((char *)this + 4) + 0xa);
    case 2: case 3: case 4: case 5:
        return *(unsigned short *)(*(char **)((char *)this + 4) + 0x10);
    case 6: case 7: case 8: case 9: case 10:
        return *(unsigned short *)(*(char **)((char *)this + 4) + 0xe);
    case 11: case 12: case 13: case 14:
        return *(unsigned short *)(*(char **)((char *)this + 4) + 0xc);
    }
    return 0;
}

// FUNCTION: GAME 0x005c1d50
undefined4 RHUnk005c1d50::FUN_005c1d50(int index)
{
    if (index < 10)
        return *(undefined4 *)(m_04 + ((index + 1) << 5));
    return 0;
}

// FUNCTION: GAME 0x005c1dd0
unsigned short RHUnk005c1d50::FUN_005c1dd0(int index, void *actor)
{
    float scale;
    if ((RHActorField<unsigned>(actor, 4) & 31) == 20 &&
        RHActorField<int>(RHActorField<void *>(actor, 0xa1c), 0x58) == 0)
        scale = ((RHHumanVirtualCalls *)actor)->V124() * 0.01f + 1.0f;
    else
        scale = 1.0f;
    switch (index)
    {
    case 0: case 1: case 2: case 3: case 4:
    case 5: case 6: case 7: case 8: case 9:
        return RHActorField<unsigned short>(m_04, (index << 5) + 0x2a) * scale;
    case 12: case 13:
        return 1;
    default:
        return 0;
    }
}

void RHElementActorHuman::Emit(SBFile &file, RHSequenceElement *element, RHcommand command)
{
    FUN_00471a50();
    FUN_00471b00();
    GetNewConcussionValue(0);
    FUN_004851b0(0, 0);
    FUN_004857b0(*(RHHumanList *)element);
    FUN_00485940(0, 0, false, 0.0f);
    FUN_00485a40(element, *(unsigned short *)element);
    FUN_00485d20(element);
    FUN_00485d90();
    FUN_00485e00();
    FUN_00485e90(0);
    FUN_00485f20();
    FUN_00474890(element);
    FUN_004748f0((RHActorTranslationSequenceCalls *)element);
    FUN_00475750(command, (RHActorTranslationSequenceCalls *)element);
    FUN_00475b00(command, element);
    FUN_00479920((RHElementActorHuman *)element);
    FUN_00479970(element);
    Translate(element, command);
    ((RHUnk0044d400 *)this)->FUN_0044d400(59, false);
    Serialize(file);
    FUN_004838f0(false);
    FUN_0047c4c0(this);
    FUN_0047b760(this, (int *)element);
    FUN_0047c420(element);
    ((RHUnk0047ca50 *)this)->Unk();
    FUN_0047e7d0((RHUnk005864a0 *)element);
    FUN_0047d920(this);
    FUN_00484a70(element);
    FUN_004847c0(0.0f, element);
    FUN_00484870(this);
    FUN_00484bb0(this, *(SBGeoPoint2D *)element, element);
    ((RHSound *)this)->FUN_005a8220(0, 0, 0, *(SBGeoPoint2D *)element);
    ((RHSound *)this)->FUN_005a8330(0, 0, 0, *(SBGeoPoint2D *)element);
    FUN_0047e9d0((RHUnk005864a0 *)element);
    FUN_0047ebc0();
    FUN_0047b660(*(RHUnk00613e90 *)element);
    FUN_00484610((RHActorTranslationSequenceCalls *)element);
    ((RHUnk0046bd20 *)this)->FUN_0046bd20();
    ((RHUnk005864a0 *)element)->FUN_005864a0();
    ((RHUnk005864a0 *)element)->FUN_005864b0();
    ((RHUnk005864a0 *)element)->FUN_005864c0();
    ((RHUnk005864a0 *)element)->FUN_005864d0();
    ((RHUnk005c1d50 *)this)->FUN_005c1d50(0);
    ((RHUnk005c1d50 *)this)->FUN_005c1dd0(0, this);
    ((RHUnk00586f70 *)element)->FUN_00586f70(0, 0);
    ((RHUnk00586f70 *)element)->FUN_005870c0(0);
    ((RHUnk00586f70 *)element)->FUN_00587340(0);
    ((RHManagerListCalls *)this)->FUN_0058bed0();
}
