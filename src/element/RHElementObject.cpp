// RHElementObject.cpp — translation unit with __FILE__ evidence at 0x004b2190
// ("P:\Robin Hood\RHelementobject.cpp", symbols/functions-by-file.tsv).
//
// BINDING (0x004b2190 -> RHElementObject::Serialize(SBFile&)):
//   - TU:        rhelementobject.cpp (embedded __FILE__ string 0x006aed04,
//                referenced only by this function at 0x004b2360).
//   - Class:     RHElementObject (symbols/oracle-correlation.tsv:
//                rhelementobject -> class RHElementObject, 23 methods).
//   - Signature: RHElementObject::Serialize(SBFile&) (symbols/mac-RH.txt).
//   - Signals:
//       * the function writes the type-name tag "RHElementObject" (string
//         0x006aed28) as its very first act via the 0x005e1b70 helper — the
//         name matches the class the TU is known to contain;
//       * every field access goes through SBFile::Access 0x005f52b0 /
//         SBFile::GetError 0x005f5f30 and the "Serialize failed reason is %s"
//         assert pattern (format 0x006a7390, empty fallback 0x006773d0) — the
//         exact serializer idiom seen in RHSword::SerializePointer;
//       * the final act is a direct call to 0x00462330, which itself begins by
//         writing the tag "RHElement" (string 0x006ae088) — i.e. the base
//         RHElement::Serialize is invoked last;
//       * 0x004b2190 occupies vtable slot 0 of the class (vtable 0x006781c4:
//         [0]=0x004b2190, [4]=0x004b23a0 = SetObjectType), so it is the first
//         virtual — consistent with an overridden Serialize;
//       * the same TU's neighbour 0x004b2010 is RHElementObject::Create
//         (Mac signature Create(bool, RHElementObject const&)), which copies
//         into the very offsets (+0xad, +0xb0, +0xb8) this function serialises.
//
// The `// STRING:` markers pin the literals to their original Game.exe
// addresses: the original is a fixed-base EXE, so its absolute string pointers
// carry no relocation records and reccmp cannot discover them by scanning.

#include "SBNullstr.h"
#include "RHElementObject.h"
#include "RHElementActorPC.h"
#include "SBDrawManager.h"
#include <stddef.h>

extern SBDrawManager *g_unk0x6c11d0;

#include "SBGeoVector2D.h"

#include "RHMobileUnk00607da0.h"

#include "RHSpriteCore.h"

inline void RHPositionInterface::SetPoint(const SBGeoPoint2D &point)
{
    m_20 = point;
    {
        SBGeoVector2D vector(point);
        ((RHMobileUnk00607da0 *)&m_c0)->FUN_00607da0((const RHMobileUnk00607da0 &)Box().FUN_006090d0(vector));
    }
    m_4 = 2;
}

DECOMP_SIZE_ASSERT(RHElementObject, 0x100)
DECOMP_SIZE_ASSERT(RHUnk00520ae0, 0x40)
DECOMP_STATIC_ASSERT(offsetof(RHElementObject, m_member) == 0xbc)
DECOMP_STATIC_ASSERT(offsetof(RHElementObject, m_96) == 0x96)
DECOMP_STATIC_ASSERT(offsetof(RHElementObject, m_98) == 0x98)
DECOMP_STATIC_ASSERT(offsetof(RHSprite, m_20) == 0x24)
DECOMP_STATIC_ASSERT(offsetof(RHSprite, m_da) == 0xde)

// FUNCTION: GAME 0x004b1eb0
RHElementObject::RHElementObject(unsigned long type, bool flag, int action)
    : RHElement(type, flag), m_a8(action), m_ac(0), m_ae(1), m_b0(0), m_b4(3), m_b8(0)
{
    m_12 = 0;
    m_98 = g_unk0x6c11d0->Unk(0xff, 0xf7, 0x5a);
    m_96 = g_unk0x6c11d0->Unk(0xff, 0xf7, 0x5a);
    m_fc = 0;
    m_fd = 0;
    m_ad = 0;
}

// SYNTHETIC: GAME 0x004b1f90
// RHElementObject::`scalar deleting destructor'

// FUNCTION: GAME 0x004b1fb0
RHElementObject::~RHElementObject()
{
}

// FUNCTION: GAME 0x004b2010
bool RHElementObject::Create(bool flag, const RHElementObject &source)
{
    m_b8 = (int)&source;
    *(short *)((char *)this + 0x10) = *(const short *)((const char *)&source + 0x10);
    *(bool *)((char *)this + 0x12) = flag;
    m_b0 = source.m_b0;
    SBDrawManager *&draw = *(SBDrawManager **)((char *)this + 0x60);
    const unsigned long *surfaces = (const unsigned long *)((const char *)&source + 0x54);
    if (surfaces[0] != (unsigned long)-1)
        *(unsigned long *)((char *)this + 0x54) = draw->Unk005e4ed0(
            draw->FUN_005e56c0(surfaces[0]), draw->FUN_005e5750(surfaces[0]), 0, 0);
    if (surfaces[1] != (unsigned long)-1)
        *(unsigned long *)((char *)this + 0x58) = draw->Unk005e4ed0(
            draw->FUN_005e56c0(surfaces[1]), draw->FUN_005e5750(surfaces[1]), 0, 0);
    (*(RHSprite **)((char *)this + 0x50))->FUN_005bd3a0(**(RHSprite **)((const char *)&source + 0x50));
    m_50->SetPoint(SBGeoPoint2D(0.0f, 0.0f));
    m_ad = source.m_ad;
    return true;
}

// FUNCTION: GAME 0x004b2190
bool RHElementObject::Serialize(SBFile &file)
{
    // STRING: GAME 0x6aed28
    RHSerializeName(file, "RHElementObject");

    if (file.Access(&m_ac, 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        // NOTE: the empty string 0x006773d0 and the format
        // "Serialize failed reason is %s" (0x006a7390) are the same original
        // entities used by RHSword::SerializePointer; reccmp allows exactly one
        // marker per original address (parser.codebase.prune_reused_addrs), so
        // those two are annotated once in src/RHSword.cpp. This function's
        // reference resolves to the same pooled entities.
        SBAssert(0,
                 // STRING: GAME 0x6aed04
                 "P:\\Robin Hood\\RHelementobject.cpp",
                 177,
                 "Serialize failed reason is %s",
                 reason);
        return false;
    }

    if (file.Access(&m_fe, 2) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHelementobject.cpp", 178, "Serialize failed reason is %s", reason);
        return false;
    }

    if (file.Access(&m_ae, 2) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHelementobject.cpp", 179, "Serialize failed reason is %s", reason);
        return false;
    }

    if (file.Access(&m_b4, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHelementobject.cpp", 180, "Serialize failed reason is %s", reason);
        return false;
    }

    if (file.Access(&m_b0, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHelementobject.cpp", 181, "Serialize failed reason is %s", reason);
        return false;
    }

    if (file.Access(&m_a8, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHelementobject.cpp", 182, "Serialize failed reason is %s", reason);
        return false;
    }

    m_member.Serialize(file);

    if (file.Access(&m_fc, 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHelementobject.cpp", 186, "Serialize failed reason is %s", reason);
        return false;
    }

    if (file.Access(&m_fd, 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHelementobject.cpp", 187, "Serialize failed reason is %s", reason);
        return false;
    }

    return RHElement::Serialize(file);
}

// FUNCTION: GAME 0x004b2390
void RHElementObject::FUN_004b2390(int value)
{
    m_b0 = value;
}

class RHEngine;
extern RHEngine *g_pEngine;

// FUNCTION: GAME 0x004b23c0
bool RHElementObject::FUN_004b23c0(const void *first, void *second, int third)
{
    if (*((char *)this + 0x12) &&
        (second == 0 || *(void **)((char *)second + 0x268) == 0) &&
        *(unsigned int *)((char *)g_pEngine + 0x4a00) <= 1 &&
        third == 3 &&
        *(unsigned short *)(*(char **)((char *)this + 0x50) + 0xde) != -1)
        return FUN_004b24d0(*(const SBGeoPoint2D *)first);
    return false;
}

#include "RHPCActionQueryCalls.h"

// FUNCTION: GAME 0x004b2420
bool RHElementObject::FUN_004b2420(void *actor) const
{
    if (m_a8 == 0)
        return true;
    if (((RHUnk0049d4f0 *)actor)->Unk(m_a8)) {
        if (((RHElementActorPC *)actor)->FUN_0049d5e0(m_a8) - ((RHObjectPCQuantity *)actor)->Ve4(m_a8) != 0)
            return true;
    }
    else if (m_a8 == 13 && ((RHUnk0049d4f0 *)actor)->Unk(14)) {
        if (((RHElementActorPC *)actor)->FUN_0049d5e0(14) - ((RHObjectPCQuantity *)actor)->Ve4(14) != 0)
            return true;
    }
    return false;
}

void EmitRHObjectQuantity(const RHElementObject *object, void *actor)
{
    object->FUN_004b2420(actor);
}

// FUNCTION: GAME 0x004b24d0
bool RHElementObject::FUN_004b24d0(const SBGeoPoint2D &point) const
{
    SBGeoBoundingBox2D box;
    box.SetMin(((SBGeoPoint2D *)((char *)*(void **)((char *)this + 0x50) + 0x24))->FUN_005fc200(SBGeoVector2D(10.0f, 20.0f)));
    box.SetMax(((SBGeoPoint2D *)((char *)*(void **)((char *)this + 0x50) + 0x24))->Unk005fc190(SBGeoVector2D(10.0f, 0.0f)));
    return box.FUN_00608400(point);
}

void EmitRHObjectPoint(const RHElementObject *object, const SBGeoPoint2D &point)
{
    object->FUN_004b24d0(point);
}

class RHMobileUnk00520c50
{
public:
    void FUN_00520c50(float first, float second);
};

struct RHObjectRepulsiveNode
{
    RHObjectRepulsiveNode *next;
    RHObjectRepulsiveNode *previous;
    void *value;
};

struct RHObjectRepulsiveList
{
    void PushBack(void *value)
    {
        RHObjectRepulsiveNode *next = head;
        RHObjectRepulsiveNode *previous = next->previous;
        RHObjectRepulsiveNode *node = (RHObjectRepulsiveNode *)operator new(12);
        node->next = next ? next : node;
        node->previous = previous ? previous : node;
        next->previous = node;
        node->previous->next = node;
        void **payload = &node->value;
        if (payload)
            *payload = value;
        ++count;
        dirty = true;
    }
    unsigned char allocator;
    RHObjectRepulsiveNode *head;
    unsigned count;
    RHObjectRepulsiveNode *cursor;
    bool dirty;
};

struct RHObjectSpritePoint
{
    char unknown[0x24];
    float x;
    float y;
};

// FUNCTION: GAME 0x004b2600
void RHElementObject::FUN_004b2600(void *points, void *, void *)
{
    unsigned radius = V68();
    if (radius != 0) {
        RHObjectSpritePoint *center = *(RHObjectSpritePoint **)((char *)this + 0x50);
        float x = center->x;
        float y = center->y;
        *(float *)((char *)this + 0xc0) = x;
        *(float *)((char *)this + 0xc4) = y;
        __int64 radiusValue = radius;
        void *point = &m_member;
        ((RHMobileUnk00520c50 *)point)->FUN_00520c50((float)radiusValue, 10.0f);
        ((RHObjectRepulsiveList *)points)->PushBack(point);
    }
}

void EmitRHObjectRepulsive(RHElementObject *object, void *points)
{
    object->FUN_004b2600(points, points, object);
}

#define SBGEO_BOUNDINGBOX2D_VIEW
#include "RHActorSequenceStorage.h"

class RHMessenger;
RHMessenger *RHUnk00546050();
extern "C" int __cdecl atexit(void (__cdecl *callback)());

// GLOBAL: GAME 0x006c0968
unsigned char g_unk0x006c0968[0x3c] = {0};
// GLOBAL: GAME 0x006c09a4
unsigned char g_unk0x006c09a4 = 0;

// Parked: guard-byte temporary coalesces into AL instead of the target DL copy.
// STUB: GAME 0x004b29c0
void *RHElementObject::FUN_004b29c0(void *actor)
{
    unsigned char initialized = g_unk0x006c09a4;
    if (!(initialized & 1)) {
        g_unk0x006c09a4 = initialized | 1;
        ((RHUnk0045aaf0 *)g_unk0x006c0968)->RHUnk0045aaf0::RHUnk0045aaf0();
        atexit((void (__cdecl *)())0x004b2b50);
    }
    if (*(bool *)((char *)RHUnk00546050() + 0x20) && ((RHUnk0049d4f0 *)actor)->Unk(m_a8)) {
        *(unsigned char *)((char *)this + 0x92) = 1;
        *(int *)((char *)this + 0xa0) = 0;
        *(unsigned short *)((char *)this + 0xa4) = 2;
        ((RHUnk0045aaf0 *)g_unk0x006c0968)->FUN_0045abc0(0x5b, 0, 0);
        return g_unk0x006c0968;
    }
    if (!FUN_004b2420(actor)) {
        ((RHUnk0045aaf0 *)g_unk0x006c0968)->FUN_0045abc0(0x5c, 0, 0);
        return g_unk0x006c0968;
    }
    char unique = (char)FUN_004b2d70();
    *(unsigned char *)((char *)this + 0x92) = 1;
    *(int *)((char *)this + 0xa0) = 0;
    *(unsigned short *)((char *)this + 0xa4) = 2;
    if (!unique) {
        switch ((unsigned short)m_ae) {
        case 1:
            ((RHUnk0045aaf0 *)g_unk0x006c0968)->FUN_0045abc0(0xca, 0, 0);
            return g_unk0x006c0968;
        case 2:
            ((RHUnk0045aaf0 *)g_unk0x006c0968)->FUN_0045abc0(0xcb, 0, 0);
            return g_unk0x006c0968;
        case 3:
            ((RHUnk0045aaf0 *)g_unk0x006c0968)->FUN_0045abc0(0xcc, 0, 0);
            return g_unk0x006c0968;
        case 4:
            ((RHUnk0045aaf0 *)g_unk0x006c0968)->FUN_0045abc0(0xcd, 0, 0);
            return g_unk0x006c0968;
        case 5:
            ((RHUnk0045aaf0 *)g_unk0x006c0968)->FUN_0045abc0(0xce, 0, 0);
            return g_unk0x006c0968;
        }
    }
    ((RHUnk0045aaf0 *)g_unk0x006c0968)->FUN_0045abc0(0x5b, 0, 0);
    return g_unk0x006c0968;
}

void EmitRHObjectFocus(RHElementObject *object, void *actor)
{
    object->FUN_004b29c0(actor);
}

#include "RHFastFindGridCore.h"
#include "RHUnkSectorGlobal.h"
#include "RHEngine.h"

// STUB: GAME 0x004b2b60
void *RHElementObject::Refresh(unsigned long surface, float value, const SBGeoBoundingBox2D &box, unsigned long flags)
{
    RHspriteRenderingInfo info;
    SBGeoBoundingBox2D sourceBox;
    SBGeoBoundingBox2D destinationBox;
    if (!m_12)
        return 0;
    unsigned short frame = m_50->FUN_005bb5f0();
    if (frame != 0)
        m_14.FUN_0045abf0(frame, m_50->m_20, 9, 0);
    if (m_50->FUN_005b9b60(box, value))
    {
        info.m_surface = m_54;
        info.m_color = m_98;
        info.m_masks = 1;
        info.m_05 = *(char *)((char *)RHUnk00546050() + 0x17);
        if (m_ad)
        {
            info.m_18 = g_pEngine->FUN_004c7d50();
            if ((info.m_18 == 2 || info.m_18 == 1) &&
                ((RHFastFindGrid *)g_unk0x6c0a9c)->FUN_004e9570(m_50->m_20, m_50->m_da))
                info.m_18 = 0;
        }
        m_50->CreateTargetSprite(info);
        if (m_50->FUN_005ba130(box, value, sourceBox, destinationBox))
            ((SBDrawManager *)m_60)->BlitAlphaKeying(m_54, &sourceBox, surface, &destinationBox, m_90,
                *(unsigned short *)((char *)m_68 + 0x48), 1);
    }
    return 0;
}

// FUNCTION: GAME 0x004b2d60
void RHElementObject::FUN_004b2d60(unsigned short value)
{
    m_ae = value;
}

// FUNCTION: GAME 0x004b2d70
int RHElementObject::FUN_004b2d70()
{
    if (m_b0 < 26 && m_b0 >= 14)
        return 0;
    return 1;
}

// Force emission: a virtual is only emitted if its vtable is needed; this
// non-inlinable out-of-line call keeps RHElementObject::Serialize in the build.
void RHElementObject::Emit(SBFile &file)
{
    FUN_004b2390(0);
    FUN_004b2d60(0);
    FUN_004b2d70();
    Serialize(file);
}

// GLOBAL: GAME 0x006c09c0
RHObjectMasterNode *g_unk0x006c09c0 = 0;
// GLOBAL: GAME 0x006c09c4
unsigned g_unk0x006c09c4 = 0;

class RHObjectMasterStorage
{
public:
    static RHObjectMasterTree mmasterMap;
};

// GLOBAL: GAME 0x006c09b0
RHObjectMasterTree RHObjectMasterStorage::mmasterMap;

#define g_unk0x006c09b0 ((unsigned char *)&RHObjectMasterStorage::mmasterMap)

struct RHObjectMasterMap
{
    RHObjectMasterInsertResult Insert(const RHObjectMasterValue &value)
    {
        RHObjectMasterInsertResult answer;
        answer = ((RHObjectMasterTree *)this)->FUN_004b33d0(value);
        RHObjectMasterInsertResult result(answer.position, answer.inserted);
        return result;
    }
    RHElementObjectMaster *&operator[](const int &key)
    {
        RHObjectMasterValue value;
        value.key = key;
        value.value = 0;
        RHObjectMasterIterator position = Insert(value).position;
        return (RHElementObjectMaster *&)position.node->value;
    }
};

// SYNTHETIC: GAME 0x004b2e50
// $E15

// SYNTHETIC: GAME 0x004b2e80
// $E16

// FUNCTION: GAME 0x004b2ea0
RHObjectMasterTree::~RHObjectMasterTree()
{
    RHObjectMasterIterator first;
    first.node = head->left;
    RHObjectMasterIterator last;
    last.node = head;
    FUN_004b32a0(first, last);
    operator delete(head);
    head = 0;
    size = 0;
    {
        RHUnk00641782 lock;
        if (--g_unk0x006c09c4 == 0) {
            operator delete(g_unk0x006c09c0);
            g_unk0x006c09c0 = 0;
        }
    }
}

class __declspec(novtable) RHObjectMasterLifetime : public RHElementObject
{
public:
    RHObjectMasterLifetime(const char *first, const char *second, unsigned short value, int type, bool flag);
};

// FUNCTION: GAME 0x004b2f20
RHObjectMasterLifetime::RHObjectMasterLifetime(const char *first, const char *second, unsigned short value, int type, bool flag)
    : RHElementObject(11, false, 0)
{
    *(unsigned short *)((char *)this + 0x10) = value;
    *(int *)((char *)this + 0xb0) = type;
    *(unsigned long *)this = 0x006786e4;
    ((RHElementObjectMaster *)this)->FUN_004b3170(std::string(first), std::string(second), flag);
}

void EmitRHObjectMasterConstructor(void *storage, const char *first, const char *second)
{
    ((RHObjectMasterLifetime *)storage)->RHObjectMasterLifetime::RHObjectMasterLifetime(first, second, 0, 0, false);
}

// FUNCTION: GAME 0x004b3090
void RHElementObjectMaster::AddMasterObject(int key, RHElementObjectMaster *master)
{
    ((RHObjectMasterMap *)g_unk0x006c09b0)->operator[](key) = master;
}

// FUNCTION: GAME 0x004b30d0
void RHElementObjectMaster::DeleteMasters()
{
    RHObjectMasterTree &tree = *(RHObjectMasterTree *)g_unk0x006c09b0;
    RHObjectMasterNode *head = tree.head;
    RHObjectMasterIterator first(head->left);
    while (first.node != head) {
        delete (RHElementObjectMaster *)first.node->value;
        first.FUN_004b3ab0();
        head = tree.head;
    }
    tree.FUN_004b32a0(RHObjectMasterIterator(head->left), RHObjectMasterIterator(head));
}

// FUNCTION: GAME 0x004b3120
void *FUN_004b3120(int type)
{
    RHObjectMasterTree &tree = *(RHObjectMasterTree *)g_unk0x006c09b0;
    RHObjectMasterIterator position = tree.Find(type);
    if (position.node != tree.head)
        return position.node->value;
    return 0;
}

#include "RHSpriteCore.h"

#include "RHCivilianSpriteView.h"

// FUNCTION: GAME 0x004b3170
void RHElementObjectMaster::FUN_004b3170(const std::string &first, const std::string &second, bool flag)
{
    *(bool *)((char *)this + 0xad) = flag;
    (*(RHSprite **)((char *)this + 0x50))->FUN_005bd050(3, first, second, false);
    *(unsigned long *)((char *)this + 0x54) = (*(SBDrawManager **)((char *)this + 0x60))->Unk005e4ed0(
        (*(RHCivilianSpriteView **)((char *)this + 0x50))->FUN_005bdef0(),
        (*(RHCivilianSpriteView **)((char *)this + 0x50))->FUN_005bdf20(), 0, 0);
}

// FUNCTION: GAME 0x004b31c0
int RHElementObjectMaster::FUN_004b31c0(int first, int second, int third, int fourth)
{
    return 0;
}

void EmitRHObjectMasterLoad(RHElementObjectMaster *master, const std::string &first, const std::string &second)
{
    master->FUN_004b3170(first, second, false);
    master->FUN_004b31c0(0, 0, 0, 0);
}

// FUNCTION: GAME 0x004b31d0
RHObjectMasterTree::RHObjectMasterTree(const RHObjectMasterArgument &comparison, const RHObjectMasterArgument &allocation)
{
    allocator = allocation.m_value;
    compare = comparison.m_value;
    multi = false;
    RHUnk00641782 lock;
    if (g_unk0x006c09c0 == 0) {
        RHObjectMasterNode *node = (RHObjectMasterNode *)operator new(0x18);
        node->parent = 0;
        node->color = 1;
        g_unk0x006c09c0 = node;
        g_unk0x006c09c0->left = 0;
        g_unk0x006c09c0->right = 0;
    }
    ++g_unk0x006c09c4;
    RHObjectMasterNode *sentinel = g_unk0x006c09c0;
    RHObjectMasterNode *node = (RHObjectMasterNode *)operator new(0x18);
    node->parent = sentinel;
    node->color = 0;
    head = node;
    size = 0;
    head->left = head;
    head->right = head;
}

// FUNCTION: GAME 0x004b32a0
RHObjectMasterIterator RHObjectMasterTree::FUN_004b32a0(RHObjectMasterIterator first, RHObjectMasterIterator last)
{
    if (size != 0 && first.node == head->left && last.node == head) {
        RHUnk00641782 lock;
        RHObjectMasterNode *node = head->parent;
        {
            RHUnk00641782 inner;
            for (RHObjectMasterNode *next = node; next != g_unk0x006c09c0; node = next) {
                FUN_004b3a20(next->right);
                next = next->left;
                operator delete(node);
            }
        }
        Root() = g_unk0x006c09c0;
        size = 0;
        Leftmost() = head;
        Rightmost() = head;
        return Begin();
    }
    while (first.node != last.node)
        FUN_004b3500(first++);
    return first;
}

// FUNCTION: GAME 0x004b33d0
RHObjectMasterInsertResult RHObjectMasterTree::FUN_004b33d0(const RHObjectMasterValue &value)
{
    RHObjectMasterNode *parent = head;
    RHObjectMasterNode *node = parent->parent;
    bool before = true;
    {
        RHUnk00641782 lock;
        while (node != g_unk0x006c09c0) {
            parent = node;
            before = value.key < node->key;
            node = before ? node->left : node->right;
        }
    }
    if (multi) {
        RHObjectMasterInsertResult result(FUN_004b3b60(node, parent, value), true);
        return result;
    }
    RHObjectMasterIterator position(parent);
    if (before) {
        if (position.node == head->left) {
            RHObjectMasterInsertResult result(FUN_004b3b60(node, parent, value), true);
            return result;
        }
        position.FUN_004b3eb0();
    }
    if (position.node->key < value.key) {
        RHObjectMasterInsertResult result(FUN_004b3b60(node, parent, value), true);
        return result;
    }
    RHObjectMasterInsertResult result(position, false);
    return result;
}

static inline RHObjectMasterNode *RHObjectMasterMin(RHObjectMasterNode *node);
static inline RHObjectMasterNode *RHObjectMasterMax(RHObjectMasterNode *node);

// FUNCTION: GAME 0x004b3500
RHObjectMasterIterator RHObjectMasterTree::FUN_004b3500(RHObjectMasterIterator entry)
{
    RHObjectMasterNode *removed = (entry++).node;
    RHObjectMasterNode *original = removed;
    RHObjectMasterNode *replacement;
    RHUnk00641782 lock;
    if (Left(removed) == g_unk0x006c09c0)
        replacement = Right(removed);
    else if (Right(removed) == g_unk0x006c09c0)
        replacement = Left(removed);
    else {
        removed = RHObjectMasterMin(Right(removed));
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
            if (Right(original) == g_unk0x006c09c0)
                Leftmost() = Parent(original);
            else
                Leftmost() = RHObjectMasterMin(replacement);
        }
        if (Rightmost() == original) {
            if (Left(original) == g_unk0x006c09c0)
                Rightmost() = Parent(original);
            else
                Rightmost() = RHObjectMasterMax(replacement);
        }
    }
    if (Color(removed) == 1) {
        while (replacement != Root() && Color(replacement) == 1) {
            if (replacement == Left(Parent(replacement))) {
                RHObjectMasterNode *sibling = Right(Parent(replacement));
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
                RHObjectMasterNode *sibling = Left(Parent(replacement));
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
    --size;
    return entry;
}

// FUNCTION: GAME 0x004b3a20
void RHObjectMasterTree::FUN_004b3a20(RHObjectMasterNode *node)
{
    RHUnk00641782 lock;
    for (RHObjectMasterNode *next = node; next != g_unk0x006c09c0; node = next) {
        FUN_004b3a20(next->right);
        next = next->left;
        operator delete(node);
    }
}

// FUNCTION: GAME 0x004b3ab0
void RHObjectMasterIterator::FUN_004b3ab0()
{
    RHUnk00641782 lock;
    if (node->right != g_unk0x006c09c0)
        node = RHObjectMasterMin(node->right);
    else {
        RHObjectMasterNode *parent;
        while (node == (parent = node->parent)->right)
            node = parent;
        if (node->right != parent)
            node = parent;
    }
}

#include <utility>
#include <memory>

struct RHsoundGroup;

// FUNCTION: GAME 0x004b3b60
RHObjectMasterIterator RHObjectMasterTree::FUN_004b3b60(RHObjectMasterNode *child, RHObjectMasterNode *parent, const RHObjectMasterValue &value)
{
    RHUnk00641782 lock;
    RHObjectMasterNode *inserted = (RHObjectMasterNode *)operator new(sizeof(RHObjectMasterNode));
    inserted->parent = parent;
    inserted->color = 0;
    inserted->left = g_unk0x006c09c0;
    inserted->right = g_unk0x006c09c0;
    typedef std::pair<const unsigned long, RHsoundGroup *> Pair;
    void (*construct)(Pair *, const Pair &) = &std::_Construct;
    construct((Pair *)&inserted->key, (const Pair &)value);
    ++size;
    if (parent == head || child != g_unk0x006c09c0 || value.key < parent->key) {
        parent->left = inserted;
        if (parent == head) {
            head->parent = inserted;
            head->right = inserted;
        }
        else if (parent == head->left)
            head->left = inserted;
    }
    else {
        parent->right = inserted;
        if (parent == head->right)
            head->right = inserted;
    }
    for (child = inserted; child != head->parent && child->parent->color == 0;) {
        if (Parent(child) == Left(Parent(Parent(child)))) {
            parent = child->parent->parent->right;
            if (parent->color == 0) {
                child->parent->color = 1;
                parent->color = 1;
                child->parent->parent->color = 0;
                child = child->parent->parent;
            }
            else {
                if (child == child->parent->right) {
                    child = child->parent;
                    RotateLeft(child);
                }
                child->parent->color = 1;
                child->parent->parent->color = 0;
                RotateRight(child->parent->parent);
            }
        }
        else {
            parent = Left(Parent(Parent(child)));
            if (parent->color == 0) {
                child->parent->color = 1;
                parent->color = 1;
                child->parent->parent->color = 0;
                child = child->parent->parent;
            }
            else {
                if (child == child->parent->left) {
                    child = child->parent;
                    RotateRight(child);
                }
                child->parent->color = 1;
                child->parent->parent->color = 0;
                RotateLeft(child->parent->parent);
            }
        }
    }
    head->parent->color = 1;
    return RHObjectMasterIterator(inserted);
}

// FUNCTION: GAME 0x004b3e60
RHObjectMasterNode *RHObjectMasterTree::FUN_004b3e60(const int &key)
{
    RHUnk00641782 lock;
    RHObjectMasterNode *node = head->parent;
    RHObjectMasterNode *result = head;
    while (node != g_unk0x006c09c0) {
        if (node->key < key)
            node = node->right;
        else {
            result = node;
            node = node->left;
        }
    }
    return result;
}

// FUNCTION: GAME 0x004b3eb0
void RHObjectMasterIterator::FUN_004b3eb0()
{
    RHUnk00641782 lock;
    if (node->color == 0 && node->parent->parent == node)
        node = node->right;
    else if (Left(node) != g_unk0x006c09c0)
        node = RHObjectMasterMax(Left(node));
    else {
        RHObjectMasterNode *parent;
        while (node == (parent = node->parent)->left)
            node = parent;
        node = parent;
    }
}

static inline RHObjectMasterNode *RHObjectMasterMin(RHObjectMasterNode *node)
{
    RHUnk00641782 lock;
    while (node->left != g_unk0x006c09c0)
        node = node->left;
    return node;
}

static inline RHObjectMasterNode *RHObjectMasterMax(RHObjectMasterNode *node)
{
    RHUnk00641782 lock;
    while (node->right != g_unk0x006c09c0)
        node = node->right;
    return node;
}

void EmitRHObjectMasterTree(RHObjectMasterTree *tree, RHObjectMasterIterator *iterator, const int &key)
{
    RHObjectMasterTree created;
    tree->~RHObjectMasterTree();
    tree->FUN_004b32a0(*iterator, RHObjectMasterIterator(tree->head));
    RHObjectMasterValue value;
    value.key = key;
    value.value = 0;
    tree->FUN_004b33d0(value);
    tree->FUN_004b3a20(iterator->node);
    iterator->FUN_004b3ab0();
    tree->FUN_004b3e60(key);
    iterator->FUN_004b3eb0();
}
