#include "SBNullstr.h"
#include "RHSaveGame.h"
#include "RHEngine.h"
#include "RHCivilianProfile.h"
#include <windows.h>
#include <algorithm>
#include <iterator>
#include <stdlib.h>

class RHFastFindGrid
{
public:
    void FUN_004e8bd0(void *sector, unsigned short layer, bool mode);
};

class RHSequenceElement;
struct RHScriptNode
{
    RHScriptNode *next;
    RHScriptNode *previous;
    void *data;
};

struct RHScriptIter
{
    RHScriptNode *node;
    RHScriptIter(RHScriptNode *value) : node(value) {}
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

class RHSeqList
{
public:
    int allocator;
    RHScriptNode *head;
    int count;
    RHScriptNode *cursor;
    void GoTo(int index);
    static void CopyData(RHSequenceElement **destination, RHSequenceElement *const *source);
};

class RHEngineBuildingActorCalls
{
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
    virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
    virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
    virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
    virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
    virtual void v40(unsigned short layer, void *building);
};

class RHActorPositionCalls
{
public:
    void FUN_00464530(const SBGeoPoint2D &point);
};

class RHUnk0046eb30
{
public:
    RHScriptIter FUN_0046eb80();
    RHScriptIter erase(RHScriptIter position);
};

struct RHUnk005c9010Iterator;
void FUN_005c9010(RHUnk005c9010Iterator &current, int distance, std::bidirectional_iterator_tag category);

class RHEngineSequenceList
{
public:
    int allocator;
    RHScriptNode *head;
    int count;
    RHScriptNode *cursor;
    bool dirty;
    int index;
    __forceinline void Advance(int distance)
    {
        while (distance > 0) { cursor = cursor->next; --distance; }
        while (distance < 0) { cursor = cursor->previous; ++distance; }
    }
    __forceinline void *Get(int wanted, bool inlineForward, bool inlineBegin)
    {
        int size = count;
        if (dirty)
        {
            if (wanted <= (size + 1) / 2)
            {
                std::bidirectional_iterator_tag category;
                if (inlineBegin)
                    FUN_005c9010((RHUnk005c9010Iterator &)(cursor = head->next), wanted, category);
                else
                    FUN_005c9010((RHUnk005c9010Iterator &)(cursor = ((RHUnk0046eb30 *)this)->FUN_0046eb80().node), wanted, category);
            }
            else
            {
                std::bidirectional_iterator_tag category;
                FUN_005c9010((RHUnk005c9010Iterator &)(cursor = head), wanted - size, category);
            }
            dirty = false;
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
                        std::bidirectional_iterator_tag category;
                        if (inlineForward)
                            FUN_005c9010((RHUnk005c9010Iterator &)(cursor = head->next), wanted, category);
                        else
                            FUN_005c9010((RHUnk005c9010Iterator &)(cursor = ((RHUnk0046eb30 *)this)->FUN_0046eb80().node), wanted, category);
                    }
                    else
                    {
                        std::bidirectional_iterator_tag category;
                        FUN_005c9010((RHUnk005c9010Iterator &)cursor, wanted - previous, category);
                    }
                }
                else if (wanted < (previous + size) / 2)
                {
                    if (inlineForward)
                        Advance(wanted - previous);
                    else
                    {
                        std::bidirectional_iterator_tag category;
                        FUN_005c9010((RHUnk005c9010Iterator &)cursor, wanted - previous, category);
                    }
                }
                else
                {
                    if (inlineForward)
                    {
                        cursor = head;
                        Advance(wanted - size);
                    }
                    else
                    {
                        std::bidirectional_iterator_tag category;
                        FUN_005c9010((RHUnk005c9010Iterator &)(cursor = head), wanted - size, category);
                    }
                }
                index = wanted;
            }
        }
        return cursor->data;
    }
};

class RHScriptFXArray
{
public:
    int grow;
    void **first;
    void **last;
    void **end;
    void **cursor;
    bool dirty;
    void **Unk004fe420(void **first, void **last, void **destination);
    void Unk004fe450(void **destination, unsigned count, void *const &value);
    void Unk005008e0(void **first, void **last);
    unsigned Size() { return first == 0 ? 0 : last - first; }
    void InsertLast(void *const &value)
    {
        void **position = last;
        if ((unsigned)(end - last) < 1)
        {
            unsigned grow = Size() > 1 ? Size() : 1;
            int size = Size() + grow;
            void **storage = (void **)operator new((size < 0 ? 0 : size) * 4);
            void **destination = storage;
            for (void **source = first; source != position; ++source, ++destination)
                RHSeqList::CopyData((RHSequenceElement **)destination, (RHSequenceElement *const *)source);
            Unk004fe450(destination, 1, value);
            ++destination;
            Unk004fe420(position, last, destination);
            Unk005008e0(first, last);
            operator delete(first);
            end = storage + size;
            unsigned previousSize = Size();
            first = storage;
            last = first + previousSize + 1;
        }
        else if ((unsigned)(last - position) < 1)
        {
            Unk004fe420(position, last, position + 1);
            Unk004fe450(last, 1 - (last - position), value);
            for (void **destination = position; destination != last; ++destination)
                *destination = value;
            ++last;
        }
        else
        {
            Unk004fe420(last - 1, last, last);
            void **source = last - 1;
            void **destination = last;
            while (source != position)
                *--destination = *--source;
            void **finish = position + 1;
            for (destination = position; destination != finish; ++destination)
                *destination = value;
            ++last;
        }
        dirty = true;
    }
};

DECOMP_SIZE_ASSERT(RHEngine, 0x4944)
DECOMP_SIZE_ASSERT(RHUnk0046ffe0, 0xa9c)
DECOMP_SIZE_ASSERT(RHUnk004ab090, 0x270)
DECOMP_SIZE_ASSERT(RHUnk004b9b70, 0x170)
DECOMP_SIZE_ASSERT(RHUnk004bac30, 0x18c)
DECOMP_SIZE_ASSERT(RHUnk004a8130, 0xfc)
DECOMP_SIZE_ASSERT(RHUnk005069a0, 0x14)
DECOMP_SIZE_ASSERT(RHUnk005055b0, 0x44)
DECOMP_SIZE_ASSERT(RHUnk004bc5b0, 0x160)
DECOMP_SIZE_ASSERT(RHUnk004e51e0, 0x30)
DECOMP_SIZE_ASSERT(RHMobileUnk00607da0, 0x14)
DECOMP_SIZE_ASSERT(RHUnk0058c590, 0xc8)
DECOMP_SIZE_ASSERT(RHUnk00551da0, 0x04)
DECOMP_SIZE_ASSERT(RHUnk0051d2c0, 0x20)
DECOMP_SIZE_ASSERT(RHHikingGuide, 0x1c)
DECOMP_SIZE_ASSERT(RHUnk005f4fc0, 0x58)
DECOMP_SIZE_ASSERT(RHUnk0054eab0, 0x1a0)
DECOMP_SIZE_ASSERT(RHUnk004a1bc0, 0xdd0)
DECOMP_SIZE_ASSERT(RHEngineExtendedMissionElementCalls, 0x04)
DECOMP_SIZE_ASSERT(RHUnk0057ee90, 0x70)
DECOMP_SIZE_ASSERT(RHEngineContinuationSectorCalls, 0x04)

void FUN_005e0c90(SBFile &file, std::string &value);
void RHSerializeName(SBFile &file, const char *name);
extern char g_unk0x6c0560[4];
extern void **g_unk0x6c0f34;
extern void **g_unk0x6c0f38;
extern float g_unk0x0067749c;

class RHEngineWidenedCalls
{
public:
    bool FUN_004b2010(char flag, void *description);
    void FUN_004c7f60(const void *point);
    void FUN_00556260();
    void FUN_005563f0(unsigned value);
    void FUN_0055ebf0();
    void FUN_004eb120(SBFile &file, void *pathFinder);
    void FUN_00558670(SBFile &file);
    void FUN_005bd450();
    bool FUN_005b76e0(unsigned row, unsigned flags);
    void FUN_0050efd0(void *actor);
    void FUN_004e3660(char flag);
    void FUN_00504b80(unsigned value);
    void FUN_005e5160(unsigned surface);
};

class RHUnk005bd5b0
{
public:
    bool Unk(bool);
};

void *FUN_004b3120(int type);

// GLOBAL: GAME 0x006c1058
unsigned g_unk0x006c1058 = 0;

// GLOBAL: GAME 0x006c1060
unsigned g_unk0x006c1060 = 0;

extern unsigned char *g_unk0x006c0bd4;

class RHUnk00523620Object
{
public:
    virtual void Unk00(); // vtable+0x00
    virtual void Unk04(); // vtable+0x04
    virtual void Unk08(unsigned flags); // vtable+0x08
    virtual void Unk0c(); // vtable+0x0c
    virtual void Unk10(); // vtable+0x10
    virtual void Unk14(); // vtable+0x14
    virtual void Unk18(); // vtable+0x18
};

class RHUnk00523620Owned
{
public:
    virtual void Unk00(unsigned flags); // vtable+0x00
};

class SBGeoVector2D;

// SIZE 0x08
class SBGeoPoint2D
{
public:
    SBGeoPoint2D();
    SBGeoPoint2D(float x, float y);
    ~SBGeoPoint2D();
    SBGeoPoint2D &operator=(const SBGeoPoint2D &value);
    SBGeoPoint2D operator+(const SBGeoVector2D &value) const;
    bool Serialize(SBFile &file);
    float m_x; // 0x00
    float m_y; // 0x04
};

DECOMP_SIZE_ASSERT(SBGeoPoint2D, 0x08)

class RHUnk00452030;
extern RHUnk00452030 *g_unk0x6c07fc;
class RHUnk0048a970;
extern RHUnk0048a970 *g_unk0x6c0b3c;

class RHElementActorPC
{
public:
    static RHElementActorPC *CreatePCFromMissionStream(SBFile &file);
};

// SIZE 0x100
class RHElementBonus
{
public:
    enum BonusType { BONUS_UNKNOWN = 0 };
    RHElementBonus(BonusType type, bool flag, unsigned short quantity);
    ~RHElementBonus();
    static RHElementBonus *CreateBonusFromMissionStream(SBFile &file);
    undefined m_data[0x100]; // 0x00
};

DECOMP_SIZE_ASSERT(RHElementBonus, 0x100)
struct RHBonusProjection;

class RHUnk0057d800
{
public:
    RHBonusProjection *Unk(const SBGeoPoint2D &point);
};

class RHUnk00582220
{
public:
    RHUnk00582220();
    ~RHUnk00582220();
    char m_data[0x3c];
};

class RHUnk00585500
{
public:
    void Unk(void *sequence);
};

class RHUnk0058a3d0
{
public:
    void Unk(void *context, int value, void *sequence);
};

class RHUnk005883a0
{
public:
    RHUnk005883a0(unsigned short level, int command, void *actor, int style,
        const SBGeoPoint2D &destination, int first, int second, int flags);
    ~RHUnk005883a0();
    char data[0x9c];
};

struct RHbeamMe
{
    SBGeoPoint2D m_point;
    unsigned short m_8;
    unsigned short m_a;
    unsigned short m_c;
    char m_e;
    char m_f;
    unsigned short m_10;
    unsigned short m_12;
    unsigned short m_14;
    char m_16[2];
    int m_required;
    int m_1c;
    RHProfileText m_text;
    RHbeamMe() {}
    RHbeamMe(const RHbeamMe &value);
    RHbeamMe &operator=(const RHbeamMe &value)
    {
        m_point = value.m_point;
        m_8 = value.m_8;
        m_a = value.m_a;
        m_c = value.m_c;
        m_e = value.m_e;
        m_10 = value.m_10;
        m_12 = value.m_12;
        m_14 = value.m_14;
        m_required = value.m_required;
        m_1c = value.m_1c;
        m_text.FUN_00401ce0((const std::string &)value.m_text, 0, std::string::npos);
        return *this;
    }
};

class RHEngineBeamCalls
{
public:
    void FUN_004e4120(RHbeamMe *position, unsigned count, const RHbeamMe &value);
};

struct RHEngineBeamFlags
{
    unsigned char m_0 : 1;
    unsigned char m_1 : 1;
    unsigned char m_2 : 1;
    unsigned char m_3 : 1;
    unsigned char m_4 : 1;
    unsigned char m_5 : 1;
    unsigned char m_6 : 1;
    unsigned char m_7 : 1;
    unsigned char m_8 : 1;
    unsigned char m_9 : 1;
};

class RHEngineReinforcementCalls
{
public:
    void *FUN_00452130(void *profile);
    void FUN_004936a0(int value);
    void FUN_00491fd0(const RHbeamMe &beamMe);
    void FUN_004d8460(void *actor, int first, int second);
    unsigned FUN_004e4460(void **value, int insert);
    SBGeoVector2D FUN_004a49e0();
    bool FUN_004f6c20(const SBGeoPoint2D &origin, SBGeoPoint2D &destination,
        unsigned short layer, const SBGeoPoint2D &extent);
};

class RHUnk0048f280
{
public:
    RHUnk0048f280(void *description);
    char m_data[0x60c];
};

class RHUnk00588830
{
public:
    RHUnk00588830(unsigned short level, int command, void *actor, int style, int value);
    char m_data[0x9c];
};

// SIZE 0x08
class SBGeoVector2D : public SBGeoPoint2D
{
public:
    SBGeoVector2D(float x, float y);
    SBGeoVector2D(const SBGeoPoint2D &value);
};

DECOMP_SIZE_ASSERT(SBGeoVector2D, 0x08)

// SIZE 0x08
class RHUnk005fc3b0 : public SBGeoPoint2D
{
public:
    RHUnk005fc3b0();
    SBGeoVector2D FUN_005fc5d0(float value);
};

DECOMP_SIZE_ASSERT(RHUnk005fc3b0, 0x08)

class RHSpritePositionCalls
{
public:
    SBGeoVector2D FUN_004a4a10();
};

void FUN_0048c5b0(void *actor, int value);

class RHUnkFXDraw
{
public:
    unsigned long Unk005e4ed0(int, int, int, int);
    char m_00[0x10c];
    unsigned short m_depth;
};

class RHUnk006114c0
{
public:
    RHUnk006114c0();
    virtual ~RHUnk006114c0();
    virtual void Unk04();
    virtual void Unk08();
    virtual void Unk0c();
    virtual void Unk10();
    virtual void Unk14();
    virtual void Unk18();
    virtual void Unk1c();
    virtual bool Unk20(RHUnkFXDraw *, unsigned long);
    bool Unk00611e10(unsigned long, unsigned long);
    bool Unk00613530(RHUnkFXDraw *, unsigned long);
    char m_04[0x1c];
    unsigned short m_width;
    unsigned short m_height;
    char m_24[0x14];
};

class RHEngineBackgroundCalls
{
public:
    bool FUN_00611660(const std::string &path);
    bool FUN_004e7fa0(unsigned short width, unsigned short height);
};

// SIZE 0x14
class SBGeoBoundingBox2D
{
public:
    int FUN_00609050(const SBGeoPoint2D &first, const SBGeoPoint2D &second);
    float m_00; // 0x00
    float m_04; // 0x04
    float m_08; // 0x08
    float m_0c; // 0x0c
    undefined m_10; // 0x10
    undefined m_11[3]; // 0x11
};

DECOMP_SIZE_ASSERT(SBGeoBoundingBox2D, 0x14)

// SIZE 0x04 (call view)
class RHUnk00611660Calls
{
public:
    virtual void Unk00(); // vtable+0x00
    virtual void Unk04(); // vtable+0x04
    virtual void Unk08(); // vtable+0x08
    virtual void Unk0c(); // vtable+0x0c
    virtual bool Unk10(SBFile &file); // vtable+0x10
};

DECOMP_SIZE_ASSERT(RHUnk00611660Calls, 0x04)

extern std::string g_unk0x006c05f0;
extern float g_unk0x00677438;
bool FUN_005f6400(const std::string &path);
std::string FUN_004e4b40(const std::string &first, const std::string &second);
std::string FUN_004e4c70(const std::string &first, const char *second);

// GLOBAL: GAME 0x0067748c
float g_unk0x0067748c = 5.0f;

// GLOBAL: GAME 0x00677680
float g_unk0x00677680 = 0.015625f;

// GLOBAL: GAME 0x00677484
float g_unk0x00677484 = 50.0f;

// GLOBAL: GAME 0x00677f7c
float g_unk0x00677f7c = 0.00003051850944757461548f;

class RHMapDescription
{
public:
    bool FUN_0063cda0(unsigned mission);
};

// GLOBAL: GAME 0x006c0664
char *g_unk0x006c0664 = 0;

// GLOBAL: GAME 0x006c0a7c
int g_unk0x006c0a7c = 0;

// GLOBAL: GAME 0x006774a0
float g_unk0x006774a0 = 20.0f;

// GLOBAL: GAME 0x006c081c
unsigned g_unk0x006c081c = 0;

#define RHENGINE_POINTER_BODY(value) \
    int index; \
    if (file.m_bLoading == 1) \
    { \
        if (file.Access(&index, 4) < 0) \
        { \
            SBString *error = file.GetError(); \
            SBAssert(0, "P:\\Robin Hood\\RHengine.cpp", 0x8c6, \
                "Serialize failed reason is %s", error->m_chars ? error->m_chars : ""); \
            return false; \
        } \
        if (index == -1) \
        { \
            value = 0; \
            return true; \
        } \
        value = FUN_004622e0(index, g_pEngine->m_48d8); \
        return true; \
    } \
    else \
    { \
        if (!value) \
            index = -1; \
        else \
            index = *(int *)((char *)value + 0xc); \
        if (file.Access(&index, 4) < 0) \
        { \
            SBString *error = file.GetError(); \
            SBAssert(0, "P:\\Robin Hood\\RHengine.cpp", 0x8dc, \
                "Serialize failed reason is %s", error->m_chars ? error->m_chars : ""); \
            return false; \
        } \
        return true; \
    }

// Parked: two-vector cleanup operands and carried-register scheduling differ.
// STUB: GAME 0x00452130
void *RHEngineReinforcementCalls::FUN_00452130(void *profile)
{
    std::vector<unsigned long> preferred;
    std::vector<unsigned long> fallback;
    std::vector<void *> &missions = *(std::vector<void *> *)((char *)this + 0x114);
    unsigned count = missions.size();
    for (unsigned long i = 0; i < count; ++i)
    {
        void *mission = missions[i];
        if (!*((char *)mission + 0x44))
        {
            void *description = *(void **)((char *)mission + 0x40);
            if (!*((char *)description + 0x35))
            {
                std::vector<unsigned long> &candidates = description == profile ? preferred : fallback;
                ((RHMissionArrayStorage *)&candidates)->FUN_004e5820(candidates.end(), i);
            }
        }
    }
    if (preferred.size())
        return missions[preferred[(unsigned)rand() % preferred.size()]];
    if (fallback.size())
        return missions[fallback[(unsigned)rand() % fallback.size()]];
    return 0;
}

// STRING: GAME 0x006aef80
static const char *g_rhengineFile = "P:\\Robin Hood\\RHengine.cpp";

// FUNCTION: GAME 0x004622e0
void *FUN_004622e0(int index, void *container)
{
    void **first = *(void ***)((char *)container + 4);
    unsigned count = !first ? 0 : *(void ***)((char *)container + 8) - first;
    for (unsigned i = 0; i < count; ++i)
    {
        void *value = first[i];
        if (value && *(int *)((char *)value + 0xc) == index)
            return first[i];
    }
    return 0;
}

// FUNCTION: GAME 0x00462a90
void RHUnk00462a90::FUN_00462a90(const char *value)
{
    m_8e = value[1];
}

// FUNCTION: GAME 0x00486170
void RHUnk00486170::FUN_00486170(void *value, unsigned count)
{
    operator delete(value);
}

// FUNCTION: GAME 0x004936a0
void RHEngineReinforcementCalls::FUN_004936a0(int value)
{
    if ((char)value || *(unsigned *)((char *)**(void ***)((char *)g_unk0x6c07fc + 0x178) + 0x3c) != 8)
    {
        void *actor = *(void **)((char *)this + 0x4ec);
        if (*((char *)actor + 0xca9))
            ((RHEngineWidenedCalls *)g_unk0x6c0b3c)->FUN_0050efd0(actor);
    }
}

#define RHENGINE_OBJECT_CREATE(type, row, flag) \
    if (((RHEngineWidenedCalls *)this)->FUN_004b2010(flag, FUN_004b3120(type)) == true) \
    { \
        unsigned &current = *(unsigned *)((char *)this + 0xb4); \
        if (current != row) \
        { \
            RHEngineWidenedCalls *sprite = *(RHEngineWidenedCalls **)((char *)this + 0x50); \
            current = row; \
            sprite->FUN_005bd450(); \
            (*(RHEngineWidenedCalls **)((char *)this + 0x50))->FUN_005b76e0(row, 0); \
        } \
        return true; \
    } \
    return false;

// FUNCTION: GAME 0x004a49e0
SBGeoVector2D RHEngineReinforcementCalls::FUN_004a49e0()
{
    return ((RHSpritePositionCalls *)((char *)*(void **)((char *)this + 0x50) + 4))->FUN_004a4a10();
}

// FUNCTION: GAME 0x004a6000
bool RHUnk004a6000::FUN_004a6000()
{
    RHENGINE_OBJECT_CREATE(3, 0xc3, 1)
}

// FUNCTION: GAME 0x004a6310
bool RHUnk004a6310::FUN_004a6310(char flag)
{
    RHENGINE_OBJECT_CREATE(4, 0xc4, flag)
}

// FUNCTION: GAME 0x004a66d0
bool RHUnk004a66d0::FUN_004a66d0(char flag)
{
    return ((RHEngineWidenedCalls *)this)->FUN_004b2010(flag, FUN_004b3120(5));
}

// FUNCTION: GAME 0x004a7d70
bool RHUnk004a7d70::FUN_004a7d70(char flag)
{
    RHENGINE_OBJECT_CREATE(13, 0xbe, flag)
}

// FUNCTION: GAME 0x004a7ed0
bool RHUnk004a7ed0::FUN_004a7ed0(char flag)
{
    RHENGINE_OBJECT_CREATE(8, 0xc4, flag)
}

// FUNCTION: GAME 0x004b0980
bool RHUnk004b0980::FUN_004b0980(char flag)
{
    RHENGINE_OBJECT_CREATE(9, 0xc4, flag)
}

// FUNCTION: GAME 0x004b91a0
bool RHUnk004b91a0::FUN_004b91a0(char flag)
{
    RHENGINE_OBJECT_CREATE(7, 0xc4, flag)
}

// FUNCTION: GAME 0x004ba900
bool RHUnk004ba900::FUN_004ba900(char flag)
{
    if (((RHEngineWidenedCalls *)this)->FUN_004b2010(flag, FUN_004b3120(6)) == true)
    {
        unsigned &current = *(unsigned *)((char *)this + 0xb4);
        if (current != 0xc4)
        {
            RHEngineWidenedCalls *sprite = *(RHEngineWidenedCalls **)((char *)this + 0x50);
            current = 0xc4;
            sprite->FUN_005bd450();
            (*(RHEngineWidenedCalls **)((char *)this + 0x50))->FUN_005b76e0(0xc4, 0);
        }
        (*(RHUnk005bd5b0 **)((char *)this + 0x50))->Unk(false);
        return true;
    }
    return false;
}

// FUNCTION: GAME 0x004be080
bool RHUnk004be080::FUN_004be080(char flag)
{
    RHENGINE_OBJECT_CREATE(11, 0xc4, flag)
}

#undef RHENGINE_OBJECT_CREATE

class RHElementActor
{
public:
    void FUN_00462730(RHElementActor *actor, bool value);
};

// SIZE 0x0c
struct RHEngineSpritePoint
{
    undefined4 m_00; // 0x00
    undefined4 m_04; // 0x04
    undefined4 m_08; // 0x08
    RHEngineSpritePoint &operator=(const RHEngineSpritePoint &value)
    {
        m_00 = value.m_00;
        m_04 = value.m_04;
        m_08 = value.m_08;
        return *this;
    }
};

// SIZE 0x18 (partial layout)
struct RHEngineSpritePosition
{
    undefined4 m_00; // 0x00
    unsigned m_04; // 0x04
    undefined4 m_08; // 0x08
    RHEngineSpritePoint m_point; // 0x0c
    void Assign(const RHEngineSpritePoint &point)
    {
        m_point = point;
        m_04 = 1;
    }
};

DECOMP_SIZE_ASSERT(RHEngineSpritePoint, 0x0c)
DECOMP_SIZE_ASSERT(RHEngineSpritePosition, 0x18)

// STUB: GAME 0x004bc5b0
bool RHUnk004bc5b0::FUN_004bc5b0(char flag)
{
    if (!((RHEngineWidenedCalls *)this)->FUN_004b2010(flag, FUN_004b3120(10)))
        return false;
    if (m_parent)
    {
        ((RHElementActor *)this)->FUN_00462730((RHElementActor *)m_parent, false);
        RHEngineSpritePosition *sprite = (RHEngineSpritePosition *)((char *)m_sprite + 4);
        sprite->Assign(*(RHEngineSpritePoint *)((char *)m_parent->m_sprite + 0x10));
        *(unsigned *)((char *)m_sprite + 8) = 7;
    }
    unsigned current = m_b4;
    m_b0 = 10;
    if (current != 0xbe)
    {
        m_b4 = 0xbe;
        ((RHEngineWidenedCalls *)m_sprite)->FUN_005bd450();
        ((RHEngineWidenedCalls *)m_sprite)->FUN_005b76e0(0xbe, 0);
    }
    return true;
}

class RHEngineMissionCalls
{
public:
    void FUN_004c1ab0(SBFile &file, RHMission *mission, std::string &background, unsigned *version);
    void FUN_004c3680(SBFile &file);
    void FUN_004c3630(SBFile &file);
    void FUN_004c3930(SBFile &file, int protoLevel);
    void FUN_004c1ee0(SBFile &file);
    void FUN_004c20a0(SBFile &file);
    void FUN_004c2830(SBFile &file);
};

// Parked: 21.13%; partial chunk dispatch.
// STUB: GAME 0x004c0510
bool RHEngine::InitializeFromMission(RHMission *mission)
{
    RHUnk005f4fc0 protoFile, missionFile;
    std::string protoPath, missionPath, background;
    std::vector<RHbeamMe> beamMes;
    void *profile = *(void **)mission;
    ((RHMissionArrayStorage *)((char *)this + 0x4c58))->FUN_004609a0(
        *(void **)((char *)this + 0x4c5c), *(void **)((char *)this + 0x4c60));
    *((char *)this + 0x4c6c) = 1;
    ((RHProfileText *)((char *)this + 0x94))->FUN_00401ce0(
        *(std::string *)((char *)profile + 0x14), 0, std::string::npos);
    ((RHProfileText *)((char *)this + 0xa4))->FUN_00401ce0(
        *(std::string *)((char *)profile + 4), 0, std::string::npos);
    // STRING: GAME 0x006af388
    std::string protoExtension(".rhp");
    protoPath = FUN_004e4b40(FUN_004e4b40(
        FUN_004e4c70(g_unk0x006c05f0, "\\"),
        *(std::string *)((char *)this + 0xa4)), protoExtension);
    std::string missionExtension(".rhm");
    missionPath = FUN_004e4b40(FUN_004e4b40(
        FUN_004e4c70(g_unk0x006c05f0, "\\"),
        *(std::string *)((char *)this + 0x94)), missionExtension);
    if (protoFile.FUN_005f5090(protoPath, 1))
    {
        SBAssert(1, "P:\\Robin Hood\\RHengine.cpp", 0x37f,
            // STRING: GAME 0x006af340
            "STRENGSTENS UNTERSAGT : Unable to open proto-level file !");
        return false;
    }
    FUN_005e1d50(protoFile, 0x4d455548, 2);
    if (missionFile.FUN_005f5090(missionPath, 1))
    {
        SBAssert(1, "P:\\Robin Hood\\RHengine.cpp", 0x389,
            "STRENGSTENS UNTERSAGT : Unable to open mission file !");
        return false;
    }
    FUN_005e1d50(missionFile, 0x44555459, 2);
    unsigned version[2];
    ((RHEngineMissionCalls *)this)->FUN_004c1ab0(missionFile, mission, background, version);
    g_unk0x006c0a7c = 7;
    g_unk0x6c0a50.FUN_00523300();
    FUN_004c28c0(background);
    while (*(unsigned *)((char *)&protoFile + 0xc) < *(unsigned *)((char *)&protoFile + 8))
    {
        switch (FUN_005e1d00(protoFile))
        {
        case 0x464c494d:
            ((RHEngineMissionCalls *)this)->FUN_004c3680(protoFile);
            break;
        case 0x53544154:
            ((RHEngineMissionCalls *)this)->FUN_004c3630(protoFile);
            break;
        case 0x5455504f:
            ((RHEngineMissionCalls *)this)->FUN_004c3930(protoFile, 1);
            break;
        case 0x42474e44:
            break;
        default:
            FUN_005e2300(protoFile);
            SBAssert(0, "P:\\Robin Hood\\RHengine.cpp", 0x41d,
                // STRING: GAME 0x006af168
                "ACHTUNG : Unknown chunk skipped in proto-level file");
            break;
        }
    }
    while (*(unsigned *)((char *)&missionFile + 0xc) < *(unsigned *)((char *)&missionFile + 8))
    {
        switch (FUN_005e1d00(missionFile))
        {
        case 0x424f595a:
            g_unk0x006c0a7c = 9;
            g_unk0x6c0a50.FUN_00523300();
            InitializeActorsFromMissionStream(missionFile, beamMes);
            break;
        case 0x43415645:
            InitializeBuildingTenantsFromMissionStream(missionFile);
            break;
        case 0x54494e47:
            ((RHEngineMissionCalls *)this)->FUN_004c1ee0(missionFile);
            break;
        case 0x534b524f:
            ((RHEngineMissionCalls *)this)->FUN_004c20a0(missionFile);
            break;
        case 0x504f5546:
        case 0x5455504f:
            ((RHEngineMissionCalls *)this)->FUN_004c3930(missionFile, 0);
            break;
        case 0x5a4f5247:
            ((RHEngineMissionCalls *)this)->FUN_004c2830(missionFile);
            break;
        default:
            FUN_005e2300(missionFile);
            SBAssert(0, "P:\\Robin Hood\\RHengine.cpp", 0x459,
                // STRING: GAME 0x006af0e0
                "ACHTUNG : Unknown chunk skipped in mission file");
            break;
        }
    }
    return true;
}

// cdecl cleanup seam, not proven irreducible.
// STUB: GAME 0x004c1be0
void RHEngine::InitializeActorsFromMissionStream(SBFile &file, std::vector<RHbeamMe> &beamMes)
{
    FUN_005e1d50(file, 0x424f595a, 3);
    unsigned short count;
    file.Access(&count, 2);
    for (unsigned short i = 0; i < count; ++i)
    {
        g_unk0x006c0a7c = 9;
        g_unk0x6c0a50.m_progress += g_unk0x006774a0 / (int)count;
        g_unk0x6c0a50.FUN_00523300();
        switch (FUN_005e1d00(file))
        {
        case 0x4f494c45:
            FUN_004c1d20(file);
            break;
        case 0x424f5247:
            FUN_004c1df0(file);
            break;
        case 0x424f4f4d:
            FUN_004c2150(file);
            break;
        case 0x53434f54:
            FUN_004c2200(file, beamMes);
            break;
        case 0x544f544f:
            FUN_004e35f0(file);
            break;
        case 0x4d454f57:
            FUN_005e2300(file);
            SBAssert(0, "P:\\Robin Hood\\RHengine.cpp", 0x544,
                // STRING: GAME 0x006af3b0
                "ACHTUNG : Unimplemented chunk skipped");
            break;
        default:
            SBAssert(1, "P:\\Robin Hood\\RHengine.cpp", 0x548,
                // STRING: GAME 0x006af390
                "Unknow sub chunk in actor chunk");
            break;
        }
    }
    FUN_005e20c0(file);
}

// FUNCTION: GAME 0x004c1ab0
void RHEngineMissionCalls::FUN_004c1ab0(SBFile &file, RHMission *mission,
    std::string &background, unsigned *version)
{
    FUN_005e1d50(file, 0x464f4f54, 4);
    file.Access(version, 4);
    unsigned &type = *(unsigned *)((char *)this + 0x4ad0);
    file.Access(&type, 4);
    switch (type)
    {
    case 1:
    case 8:
    case 16:
    case 32:
    case 64:
    case 128:
        *(unsigned short *)((char *)this + 0x4cc0) = 400;
        break;
    case 2:
    case 4:
        *(unsigned short *)((char *)this + 0x4cc0) = 300;
        break;
    }
    FUN_005e0c90(file, background);
    unsigned value;
    file.Access(&value, 4);
    ((RHEngine *)this)->LoadDynRes(**(unsigned **)mission);
    FUN_005e20c0(file);
}

// FUNCTION: GAME 0x004c1d20
void RHEngine::FUN_004c1d20(SBFile &file)
{
    FUN_005e1d50(file, 0x4f494c45, 3);
    unsigned short count;
    file.Access(&count, 2);
    for (unsigned short i = 0; i < count; ++i)
    {
        RHUnk0046ffe0 *actor = new RHUnk0046ffe0(true);
        actor->Unk3c(file);
        *(unsigned *)((char *)this + 0x4a68) += *(unsigned *)((char *)actor + 0x4f0);
        ((RHEngineReinforcementCalls *)this)->FUN_004d8460(actor, 1, 1);
    }
    FUN_005e20c0(file);
}

// FUNCTION: GAME 0x004c1df0
void RHEngine::FUN_004c1df0(SBFile &file)
{
    FUN_005e1d50(file, 0x424f5247, 4);
    unsigned short count;
    file.Access(&count, 2);
    for (unsigned short i = 0; i < count; ++i)
    {
        RHUnk004a1bc0 *actor = new RHUnk004a1bc0(true);
        ((RHEngineMissionElementCalls *)actor)->Unk3c(file);
        ((RHEngineReinforcementCalls *)this)->FUN_004d8460(actor, 1, 1);
        *(unsigned *)((char *)this + 0x4a68) += *(unsigned *)((char *)actor + 0x4f0);
        if (((RHEngineExtendedMissionElementCalls *)actor)->Unk130() == 1)
            ++*(unsigned *)((char *)this + 0x4a70);
    }
    FUN_005e20c0(file);
}

// FUNCTION: GAME 0x004c1ee0
void RHEngineMissionCalls::FUN_004c1ee0(SBFile &file)
{
    FUN_005e1d50(file, 0x54494e47, 3);
    unsigned short count;
    file.Access(&count, 2);
    for (unsigned short i = 0; i < count; ++i)
    {
        RHUnk004ab090 *actor = new RHUnk004ab090;
        actor->Unk3c(file);
        ((RHEngineReinforcementCalls *)this)->FUN_004d8460(actor, 1, 1);
    }
    FUN_005e20c0(file);
}

// FUNCTION: GAME 0x004c1f90
void RHEngine::InitializeBuildingTenantsFromMissionStream(SBFile &file)
{
    void *buildings = (char *)g_unk0x6c0a9c + 0x40c0;
    FUN_005e1d50(file, 0x43415645, 3);
    unsigned short count;
    file.Access(&count, 2);
    for (unsigned short i = 0; i < count; ++i)
    {
        void *building = (*(void ***)((char *)buildings + 4))[i];
        unsigned short tenants;
        file.Access(&tenants, 2);
        for (unsigned short j = 0; j < tenants; ++j)
        {
            unsigned short index;
            file.Access(&index, 2);
            void *actor = (*(void ***)(m_48d8 + 4))[index];
            if ((*(unsigned *)((char *)actor + 4) & 7) == 4)
                ((RHEngineBuildingCalls *)building)->FUN_0057e680(actor);
            else
                SBAssert(0, "P:\\Robin Hood\\RHengine.cpp", 0x5d9,
                    // STRING: GAME 0x006af3d8
                    "VERBOTEN : A building occupant is not a human !");
        }
        char flag;
        file.Access(&flag, 1);
        *((char *)building + 0x118) = flag;
    }
    FUN_005e20c0(file);
}

// FUNCTION: GAME 0x004c20a0
void RHEngineMissionCalls::FUN_004c20a0(SBFile &file)
{
    FUN_005e1d50(file, 0x534b524f, 4);
    unsigned short count;
    file.Access(&count, 2);
    for (unsigned short i = 0; i < count; ++i)
    {
        RHUnk004b9b70 *actor = new RHUnk004b9b70;
        actor->Unk3c(file);
        ((RHEngineReinforcementCalls *)this)->FUN_004d8460(actor, 1, 1);
    }
    FUN_005e20c0(file);
}

// FUNCTION: GAME 0x004c2150
void RHEngine::FUN_004c2150(SBFile &file)
{
    FUN_005e1d50(file, 0x424f4f4d, 5);
    unsigned short count;
    file.Access(&count, 2);
    for (unsigned short i = 0; i < count; ++i)
    {
        RHUnk004bac30 *actor = new RHUnk004bac30;
        actor->Unk3c(file);
        ((RHEngineReinforcementCalls *)this)->FUN_004d8460(actor, 1, 1);
    }
    FUN_005e20c0(file);
}

// Parked: 44.80%.
// STUB: GAME 0x004c2200
void RHEngine::FUN_004c2200(SBFile &file, std::vector<RHbeamMe> &beamMes)
{
    unsigned index = 0;
    RHbeamMe beamMe;
    RHProfileText unused;
    FUN_005e1d50(file, 0x53434f54, 4);
    unsigned short count;
    file.Access(&count, 2);
    for (unsigned short i = 0; i < count; ++i)
    {
        short x, y;
        file.Access(&x, 2);
        file.Access(&y, 2);
        beamMe.m_point.m_x = (float)x;
        beamMe.m_point.m_y = (float)y;
        unsigned value;
        file.Access(&value, 4);
        beamMe.m_10 = (unsigned short)value;
        file.Access(&value, 4);
        beamMe.m_1c = value;
        file.Access(&beamMe.m_c, 2);
        file.Access(&beamMe.m_a, 2);
        file.Access(&beamMe.m_8, 2);
        if (beamMe.m_8 > *(unsigned short *)((char *)this + 0x3fb8))
            SBAssert(1, "P:\\Robin Hood\\RHengine.cpp", 0x654,
                // STRING: GAME 0x006af44c
                "AUF WIEDERSEHEN : Beam-me at (%f,%f) lying on wrong layer (%d) !",
                beamMe.m_point.m_x, beamMe.m_point.m_y, beamMe.m_8);
        void *sector = beamMe.m_a == 0xffff
            ? *(void **)((char *)this + 0x42a0)
            : (*(void ***)((char *)this + 0x4180))[beamMe.m_a];
        if ((*(unsigned *)((char *)sector + 0x30) & 3) != 3)
            SBAssert(1, "P:\\Robin Hood\\RHengine.cpp", 0x659,
                // STRING: GAME 0x006af408
                "AUF WIEDERSEHEN : Beam-me at (%f,%f) lying on wrong sector (%d) !",
                beamMe.m_point.m_x, beamMe.m_point.m_y, beamMe.m_a);
        file.Access(&value, 4);
        if (value >= 9)
            value = *(unsigned *)((char *)this + 0x42a4);
        beamMe.m_e = (char)value;
        unsigned char flag;
        RHEngineBeamFlags &flags = *(RHEngineBeamFlags *)&beamMe.m_14;
        file.Access(&flag, 1);
        flags.m_0 = flag;
        file.Access(&flag, 1);
        flags.m_1 = flag;
        file.Access(&flag, 1);
        flags.m_2 = flag;
        file.Access(&flag, 1);
        flags.m_3 = flag;
        file.Access(&flag, 1);
        flags.m_4 = flag;
        file.Access(&flag, 1);
        flags.m_5 = flag;
        file.Access(&flag, 1);
        flags.m_6 = flag;
        file.Access(&flag, 1);
        flags.m_7 = flag;
        file.Access(&flag, 1);
        flags.m_8 = flag;
        file.Access(&flag, 1);
        flags.m_9 = flag;
        beamMe.m_12 = (unsigned short)index++;
        file.Access(&flag, 1);
        if (flag)
            FUN_005e0c90(file, (std::string &)beamMe.m_text);
        else
        {
            unsigned length = strlen(g_unk0x6c0560);
            if (beamMe.m_text.FUN_00402280(length, true))
            {
                memcpy(beamMe.m_text.m_chars, g_unk0x6c0560, length);
                beamMe.m_text.FUN_00402260(length);
            }
        }
        file.Access(&flag, 1);
        beamMe.m_required = flag;
        ((RHEngineBeamCalls *)&beamMes)->FUN_004e4120(beamMes.end(), 1, beamMe);
    }
    FUN_005e20c0(file);
    *(unsigned *)((char *)this + 0x4a4c) = beamMes.size();
}

// Parked: first-vector receiver reload and compared function-tail extent differ.
// STUB: GAME 0x004c2720
void RHEngine::FUN_004c2720(SBFile &file)
{
    *(int *)((char *)this + 0x4a44) = g_unk0x6c0f34 == 0 ? 0 : g_unk0x6c0f38 - g_unk0x6c0f34;
    *(unsigned *)((char *)this + 0x4a48) = g_unk0x006c081c;
    std::vector<void *> &actors = *(std::vector<void *> *)((char *)this + 0x48d8);
    ((RHEngineContinuationCampaignCalls *)g_unk0x6c07fc)->FUN_00450c10(&actors, file);
    std::vector<void *> &remaining = *(std::vector<void *> *)((char *)this + 0x4978);
    int index = *(int *)((char *)this + 0x4a44) + remaining.size();
    for (; index < (int)actors.size(); ++index)
        ((RHEngineReinforcementCalls *)this)->FUN_004d8460(actors[index], 0, 0);
    std::vector<void *> &pcs = *(std::vector<void *> *)((char *)this + 0x4938);
    unsigned count = pcs.size();
    for (unsigned slot = 0; slot < *(unsigned *)((char *)this + 0x4a4c); ++slot)
    {
        unsigned pc = 0;
        for (; pc < count; ++pc)
        {
            void *actor = pcs[pc];
            if (*(unsigned short *)((char *)actor + 0x4ea) == slot)
            {
                FUN_00570850(actor);
                break;
            }
        }
        if (pc == count)
            FUN_00570850(0);
    }
}

// FUNCTION: GAME 0x004c2830
void RHEngineMissionCalls::FUN_004c2830(SBFile &file)
{
    FUN_005e1d50(file, 0x5a4f5247, 2);
    unsigned short count;
    file.Access(&count, 2);
    while (count)
    {
        RHElementBonus *actor = RHElementBonus::CreateBonusFromMissionStream(file);
        ((RHEngineReinforcementCalls *)this)->FUN_004d8460(actor, 1, 1);
        if (*(unsigned *)((char *)actor + 0xb0) == 0x17)
            *(unsigned *)((char *)this + 0x4a64) += *(unsigned short *)((char *)actor + 0xae);
        --count;
    }
    FUN_005e20c0(file);
}

// Parked: 26.09%.
// STUB: GAME 0x004c28c0
void RHEngine::FUN_004c28c0(const std::string &name)
{
    std::string mapPath, minimapPath, ambiance;
    RHUnk006114c0 minimap, map;
    RHUnk005f4fc0 file;
    switch (*(unsigned *)((char *)this + 0x4ad0))
    {
    case 1:
        // STRING: GAME 0x006af5a0
        ambiance = "\\Day\\";
        break;
    case 2:
        // STRING: GAME 0x006af598
        ambiance = "\\Fog\\";
        break;
    case 4:
        // STRING: GAME 0x006af590
        ambiance = "\\Night\\";
        break;
    case 8:
        // STRING: GAME 0x006af584
        ambiance = "\\Attack\\";
        break;
    case 16:
        // STRING: GAME 0x006af578
        ambiance = "\\Custom1\\";
        break;
    case 32:
        // STRING: GAME 0x006af56c
        ambiance = "\\Custom2\\";
        break;
    case 64:
        // STRING: GAME 0x006af560
        ambiance = "\\Custom3\\";
        break;
    case 128:
        // STRING: GAME 0x006af554
        ambiance = "\\Custom4\\";
        break;
    }
    // STRING: GAME 0x006af54c
    std::string mapExtension(".map");
    mapPath = FUN_004e4b40(FUN_004e4b40(FUN_004e4b40(g_unk0x006c05f0, ambiance), name), mapExtension);
    if (!FUN_005f6400(mapPath))
    {
        mapPath = FUN_004e4b40(FUN_004e4b40(FUN_004e4c70(g_unk0x006c05f0, "\\Day\\"), name), mapExtension);
        if (!FUN_005f6400(mapPath))
        {
            mapPath = FUN_004e4b40(FUN_004e4b40(FUN_004e4c70(g_unk0x006c05f0, "\\"), name), mapExtension);
            if (!FUN_005f6400(mapPath))
                SBAssert(1, "P:\\Robin Hood\\RHengine.cpp", 0x73d,
                    // STRING: GAME 0x006af4f4
                    "STRENG VERBOTEN : Unable to find map file %s in directory %s (ambiance %s), file error",
                    name.c_str(), g_unk0x006c05f0.c_str(), ambiance.c_str());
        }
    }
    ((RHEngineBackgroundCalls *)&map)->FUN_00611660(mapPath);
    g_unk0x006c0a7c = 7;
    g_unk0x6c0a50.m_progress += g_unk0x00677438;
    g_unk0x6c0a50.FUN_00523300();
    float &width = *(float *)((char *)this + 0x4730);
    float &height = *(float *)((char *)this + 0x4734);
    width = (float)map.m_width;
    height = (float)map.m_height;
    RHUnkFXDraw *draw = *(RHUnkFXDraw **)((char *)this + 0xdc);
    unsigned long surface = draw->Unk005e4ed0((int)width, (int)height, 0, 0);
    *(unsigned long *)((char *)this + 0x48c4) = surface;
    ((RHEngineBackgroundCalls *)((char *)this + 0x11c))->FUN_004e7fa0(
        (int)(width * g_unk0x00677680), (int)(height * g_unk0x00677680));
    map.Unk00611e10(draw->m_depth == 16 ? 3 : 2, 0);
    map.Unk00613530(draw, surface);
    g_unk0x006c0a7c = 7;
    g_unk0x6c0a50.m_progress += g_unk0x0067748c;
    g_unk0x6c0a50.FUN_00523300();
    // STRING: GAME 0x006af4ec
    std::string minimapExtension(".min");
    minimapPath = FUN_004e4b40(FUN_004e4b40(FUN_004e4b40(g_unk0x006c05f0, ambiance), name), minimapExtension);
    if (!FUN_005f6400(minimapPath))
    {
        minimapPath = FUN_004e4b40(FUN_004e4b40(FUN_004e4c70(g_unk0x006c05f0, "\\Day\\"), name), minimapExtension);
        if (!FUN_005f6400(minimapPath))
        {
            minimapPath = FUN_004e4b40(FUN_004e4b40(FUN_004e4c70(g_unk0x006c05f0, "\\"), name), minimapExtension);
            if (!FUN_005f6400(minimapPath))
                SBAssert(1, "P:\\Robin Hood\\RHengine.cpp", 0x76b,
                    // STRING: GAME 0x006af490
                    "STRENG VERBOTEN : Unable to find mini-map file %s in directory %s (ambiance %s), file error",
                    name.c_str(), g_unk0x006c05f0.c_str(), ambiance.c_str());
        }
    }
    ((RHEngineBackgroundCalls *)&minimap)->FUN_00611660(minimapPath);
    surface = draw->Unk005e4ed0(*(int *)&minimap.m_width, *(int *)&minimap.m_height, 0, 0);
    *(unsigned long *)((char *)this + 0x48c8) = surface;
    minimap.Unk00613530(draw, surface);
    g_unk0x006c0a7c = 7;
    g_unk0x6c0a50.m_progress += g_unk0x0067748c;
    g_unk0x6c0a50.FUN_00523300();
}

// FUNCTION: GAME 0x004c3630
void RHEngineMissionCalls::FUN_004c3630(SBFile &file)
{
    FUN_005e1d50(file, 0x53544154, 2);
    ((RHEngineWidenedCalls *)((char *)this + 0x11c))->FUN_004eb120(
        file, *(void **)((char *)this + 0x45b8));
    (*(RHEngineWidenedCalls **)((char *)this + 0x45b8))->FUN_00558670(file);
    FUN_005e20c0(file);
}

// FUNCTION: GAME 0x004c3680
void RHEngineMissionCalls::FUN_004c3680(SBFile &file)
{
    FUN_005e1d50(file, 0x464c494d, 2);
    unsigned short count;
    file.Access(&count, 2);
    for (unsigned short i = 0; i < count; ++i)
    {
        RHUnk004a8130 *actor = new RHUnk004a8130(true);
        actor->Unk38(file);
        *(unsigned short *)((char *)actor + 0x10) = 0x1001;
        ((RHEngineReinforcementCalls *)this)->FUN_004d8460(actor, 1, 1);
    }
    FUN_005e20c0(file);
}

// FUNCTION: GAME 0x004c38d0
void RHEngine::FUN_004c38d0(SBFile &file, unsigned *value)
{
    FUN_005e1d50(file, 0x53504f4b, 3);
    file.Access(value, 4);
    file.Access((char *)this + 0x4aa8, 1);
    unsigned scalar;
    file.Access(&scalar, 4);
    *(unsigned *)((char *)this + 0x42a4) = scalar;
    FUN_005e20c0(file);
}

// FUNCTION: GAME 0x004c3930
void RHEngineMissionCalls::FUN_004c3930(SBFile &file, int protoLevel)
{
    FUN_005e1d50(file, (char)protoLevel ? 0x5455504f : 0x504f5546, 3);
    unsigned short count;
    file.Access(&count, 2);
    for (unsigned short i = 0; i < count; ++i)
    {
        RHUnk0054eab0 *value = new RHUnk0054eab0;
        void *grid = (char *)this + 0x11c;
        value->FUN_0054eea0(file, grid);
        ((RHEngineGridCalls *)grid)->FUN_004efd10(value,
            *(unsigned short *)((char *)value + 0x13c), true);
        ((RHEngineReinforcementCalls *)this)->FUN_004d8460(
            *(void **)((char *)value + 0x18), 1, 1);
    }
    FUN_005e20c0(file);
}

// FUNCTION: GAME 0x004c3a10
bool RHEngine::SerializeElementPointer(SBFile &file, RHElement *&element)
{
    RHENGINE_POINTER_BODY((*(void **)&element))
}

// FUNCTION: GAME 0x004c3af0
bool RHEngine::FUN_004c3af0(SBFile &file, void *&value)
{
    RHENGINE_POINTER_BODY(value)
}

// FUNCTION: GAME 0x004c3bd0
bool RHEngine::FUN_004c3bd0(SBFile &file, void *&value)
{
    RHENGINE_POINTER_BODY(value)
}

// FUNCTION: GAME 0x004c3cb0
bool RHReconnaissanceEngine::Unk004c3cb0(SBFile &file, void *&value)
{
    RHENGINE_POINTER_BODY(value)
}

// FUNCTION: GAME 0x004c3d90
bool RHEngine::FUN_004c3d90(SBFile &file, void *&value)
{
    RHENGINE_POINTER_BODY(value)
}

// FUNCTION: GAME 0x004c3e70
bool RHEngine::SerializeNestedB(SBFile &file, void *storage)
{
    RHENGINE_POINTER_BODY((*(void **)storage))
}

// FUNCTION: GAME 0x004c3f50
bool RHEngine::FUN_004c3f50(SBFile &file, void *&value)
{
    RHENGINE_POINTER_BODY(value)
}

// FUNCTION: GAME 0x004c4030
bool RHEngine::FUN_004c4030(SBFile &file, void *&value)
{
    RHENGINE_POINTER_BODY(value)
}

// FUNCTION: GAME 0x004c4110
bool RHReconnaissanceEngine::Unk004c4110(SBFile &file, void *&value)
{
    RHENGINE_POINTER_BODY(value)
}

// FUNCTION: GAME 0x004c41f0
bool RHEngine::FUN_004c41f0(SBFile &file, void *&value)
{
    RHENGINE_POINTER_BODY(value)
}

// FUNCTION: GAME 0x004c42d0
bool RHEngine::FUN_004c42d0(SBFile &file, void *&value)
{
    RHENGINE_POINTER_BODY(value)
}

// FUNCTION: GAME 0x004c43b0
bool RHEngine::FUN_004c43b0(SBFile &file, void *&value)
{
    RHENGINE_POINTER_BODY(value)
}

// FUNCTION: GAME 0x004c4490
bool RHEngine::FUN_004c4490(SBFile &file, void *&value)
{
    RHENGINE_POINTER_BODY(value)
}

#undef RHENGINE_POINTER_BODY

class RHUnk00452030
{
public:
    int FUN_00453d60(const void *description);
};

class RHUnk0048a970;
extern RHUnk0048a970 *g_unk0x6c0b3c;

class RHEngineSerializationCalls
{
public:
    void FUN_0058a430();
    void FUN_005a5c50();
    void FUN_0048fa30();
    void FUN_004d88e0(void *element, int first, int second);
    void FUN_0050f000();
    void FUN_0050f010();
};

void FUN_005a5cd0();

class RHEngineMenuWidgetCalls
{
public:
    virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
    virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
    virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
    virtual void v12(); virtual void v13();
    virtual void v14(void *widget);
    virtual void v15(void *widget);
    virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
    virtual void v20();
    virtual void v21(bool enabled);
};

class RHEngineSerializedElement
{
public:
    virtual ~RHEngineSerializedElement();
    virtual void Unk04();
    virtual void Unk08();
    virtual void Unk0c();
    virtual void Unk10();
    virtual void Unk14();
    virtual void Unk18();
    virtual void Unk1c();
    virtual void Unk20();
    virtual void Unk24();
    virtual void Unk28();
    virtual void Unk2c();
    virtual void Unk30();
    virtual void Unk34();
    virtual void Unk38();
    virtual void Unk3c();
    virtual bool Serialize(SBFile &file);
};

// GLOBAL: GAME 0x006c0a86
char g_unk0x006c0a86 = 0;

#define RHENGINE_ACCESS(storage, size, line) \
    if (file.Access(storage, size) < 0) \
    { \
        SBString *error = file.GetError(); \
        SBAssert(0, "P:\\Robin Hood\\RHengine.cpp", line, \
            "Serialize failed reason is %s", error->m_chars ? error->m_chars : ""); \
        return false; \
    }

// Parked: 39.37%; partial scalar and element serialization.
// STUB: GAME 0x004c4570
bool RHEngine::FUN_004c4570(SBFile &file)
{
    char *engine = (char *)this;
    g_unk0x006c0a86 = 0;
    if (file.m_version >= 13)
    {
        RHENGINE_ACCESS(engine + 0x4d98, 4, 0x9bf)
    }
    if (file.m_version >= 12)
    {
        RHENGINE_ACCESS(engine + 0x4d85, 1, 0x9c4)
    }
    else
        engine[0x4d85] = 1;
    if (file.m_version == 2 || file.m_version >= 11)
    {
        RHENGINE_ACCESS(engine + 0x4d84, 1, 0x9cd)
    }
    if (!file.m_bLoading)
        ((RHEngineSerializationCalls *)(engine + 0x43f8))->FUN_0058a430();
    ((SBGeoPoint2D *)(engine + 0x4738))->Serialize(file);
    RHENGINE_ACCESS(engine + 0x475c, 4, 0x9fb)
    ((SBGeoPoint2D *)(engine + 0x4748))->Serialize(file);
    RHENGINE_ACCESS(engine + 0x4758, 2, 0x9fe)
    RHENGINE_ACCESS(engine + 0x45b0, 4, 0x9ff)
    RHENGINE_ACCESS(engine + 0x45b4, 2, 0xa00)
    RHENGINE_ACCESS(engine + 0x4764, 4, 0xa01)
    RHENGINE_ACCESS(engine + 0x4760, 4, 0xa02)
    RHENGINE_ACCESS(engine + 0x4780, 0x140, 0xa04)
    RHENGINE_ACCESS(engine + 0x4a94, 4, 0xa14)
    RHENGINE_ACCESS(engine + 0xd0, 1, 0xa19)
    RHENGINE_ACCESS(engine + 0x4a50, 1, 0xa1c)
    RHENGINE_ACCESS(engine + 0x4a51, 1, 0xa1d)
    if (file.m_bLoading)
    {
        engine[0x4a52] = 0;
        engine[0x4a53] = 0;
        engine[0x4a54] = 0;
    }
    RHENGINE_ACCESS(engine + 0x4750, 8, 0xa26)
    RHENGINE_ACCESS(engine + 0x4719, 1, 0xa29)
    FUN_005e0c90(file, *(std::string *)(engine + 0xb4));
    if (!FUN_004c6040(file))
        return false;
    if (file.m_bLoading)
    {
        FUN_005a5cd0();
        void **first = *(void ***)(engine + 0x4160);
        unsigned short count = first ? (unsigned short)(*(void ***)(engine + 0x4164) - first) : 0;
        for (unsigned short i = 0; i < count; ++i)
            ((RHEngineSerializationCalls *)first[i])->FUN_005a5c50();
        if (file.m_version < 6)
        {
            *(unsigned *)(engine + 0x4d88) = 0;
            *(unsigned *)(engine + 0x4d8c) = 0;
            *(unsigned *)(engine + 0x4d90) = 0;
            *(unsigned *)(engine + 0x4d94) = 0;
        }
    }
    return true;
}

// Parked: 19.63%; partial element construction cases.
// STUB: GAME 0x004c6040
bool RHEngine::FUN_004c6040(SBFile &file)
{
    char *engine = (char *)this;
    void **first = *(void ***)(engine + 0x48dc);
    void **last = *(void ***)(engine + 0x48e0);
    unsigned count = first ? last - first : 0;
    for (unsigned i = 1; i < count; ++i)
    {
        void *value = first[i];
        unsigned j = i;
        while (j && *(unsigned *)((char *)value + 0xc) < *(unsigned *)((char *)first[j - 1] + 0xc))
        {
            first[j] = first[j - 1];
            --j;
        }
        first[j] = value;
    }
    if (!file.m_bLoading)
    {
        g_unk0x006c0a86 = 1;
        RHENGINE_ACCESS(&count, 4, 0xc0a)
        for (unsigned pass = 0; pass < 2; ++pass)
        {
            for (unsigned index = 0; index < count; ++index)
            {
                void *element = first[index];
                unsigned short type = *(unsigned short *)((char *)element + 0x10);
                unsigned id = *(unsigned *)((char *)element + 0xc);
                RHENGINE_ACCESS(&type, 2, pass ? 0xc25 : 0xc12)
                RHENGINE_ACCESS(&id, 4, pass ? 0xc26 : 0xc13)
                if (type == 1)
                {
                    int description = g_unk0x6c07fc->FUN_00453d60(
                        *(void **)((char *)element + 0x5f8));
                    RHENGINE_ACCESS(&description, 4, pass ? 0xc2d : 0xc1a)
                }
                if (pass && !((RHEngineSerializedElement *)element)->Serialize(file))
                    return false;
            }
        }
        return true;
    }
    ((RHEngineSerializationCalls *)g_unk0x6c0b3c)->FUN_0050f000();
    unsigned cutoff = *(unsigned *)(engine + 0x4a48);
    for (int removed = (int)count - 1; removed >= 0; --removed)
    {
        void *element = (*(void ***)(engine + 0x48dc))[removed];
        if (*(unsigned *)((char *)element + 0xc) >= cutoff)
        {
            ((RHEngineSerializationCalls *)this)->FUN_004d88e0(element, 0, 0);
            if (element)
                delete (RHEngineSerializedElement *)element;
        }
    }
    unsigned serializedCount;
    RHENGINE_ACCESS(&serializedCount, 4, 0xc50)
    for (unsigned created = 0; created < serializedCount; ++created)
    {
        unsigned short type;
        unsigned id, description;
        RHENGINE_ACCESS(&type, 2, 0xc54)
        RHENGINE_ACCESS(&id, 4, 0xc55)
        if (type == 1)
        {
            RHENGINE_ACCESS(&description, 4, 0xc5a)
        }
        void *element = 0;
        first = *(void ***)(engine + 0x48dc);
        if (id < cutoff)
            for (unsigned existing = 0; existing < count; ++existing)
                if (*(unsigned *)((char *)first[existing] + 0xc) == id)
                {
                    element = first[existing];
                    break;
                }
        if (element)
            continue;
        int bonusType = -1;
        switch (type)
        {
        case 1:
            element = new RHUnk0048f280((*(void ***)((char *)g_unk0x6c07fc + 0x108))[description]);
            *(unsigned short *)((char *)element + 0x10) = 1;
            ((RHEngineSerializationCalls *)element)->FUN_0048fa30();
            break;
        case 0x4001: bonusType = 12; break;
        case 0x4003: bonusType = 1; break;
        case 0x4004: bonusType = 11; break;
        case 0x4006: bonusType = 13; break;
        case 0x4007: bonusType = 17; break;
        case 0x4008: bonusType = 16; break;
        case 0x4009: bonusType = 4; break;
        case 0x400a: bonusType = 5; break;
        case 0x400b: bonusType = 19; break;
        default: return false;
        }
        if (bonusType >= 0)
            element = new RHElementBonus((RHElementBonus::BonusType)bonusType, false, 1);
        *(unsigned *)((char *)element + 0xc) = id;
        ((RHEngineReinforcementCalls *)this)->FUN_004d8460(element, 0, 1);
    }
    g_unk0x006c0a86 = 1;
    first = *(void ***)(engine + 0x48dc);
    count = first ? *(void ***)(engine + 0x48e0) - first : 0;
    for (unsigned restored = 0; restored < serializedCount; ++restored)
    {
        unsigned short type;
        unsigned id, description;
        RHENGINE_ACCESS(&type, 2, 0xd3a)
        RHENGINE_ACCESS(&id, 4, 0xd3b)
        if (type == 1)
        {
            RHENGINE_ACCESS(&description, 4, 0xd40)
        }
        void *element = 0;
        for (int found = (int)count - 1; found >= 0; --found)
            if (*(unsigned *)((char *)first[found] + 0xc) == id)
            {
                element = first[found];
                break;
            }
        if (!element || !((RHEngineSerializedElement *)element)->Serialize(file))
            return false;
    }
    ((RHEngineSerializationCalls *)g_unk0x6c0b3c)->FUN_0050f010();
    return true;
}

#undef RHENGINE_ACCESS

// FUNCTION: GAME 0x004c8120
void RHEngine::FUN_004c8120(void *actor)
{
    ((RHEngineWidenedCalls *)this)->FUN_004c7f60(
        (char *)*(void **)((char *)actor + 0x50) + 0x24);
}

// Parked: layer/point receiver scheduling and sector-bit lowering differ.
// STUB: GAME 0x004debf0
void RHEngine::FUN_004debf0(const SBGeoPoint2D &point)
{
    SBGeoPoint2D origin;
    void *&sector = *(void **)((char *)this + 0xc8);
    void *&building = *(void **)((char *)this + 0xcc);
    building = 0;
    *(unsigned short *)((char *)this + 0xc4) = 0;
    sector = 0;
    unsigned short layer;
    if (*(int *)((char *)this + 0x4a00))
    {
        void *node = **(void ***)((char *)this + 0x49fc);
        void *actor = *(void **)((char *)node + 8);
        void *sprite = *(void **)((char *)actor + 0x50);
        layer = *(unsigned short *)((char *)sprite + 0xde);
        node = **(void ***)((char *)this + 0x49fc);
        actor = *(void **)((char *)node + 8);
        sprite = *(void **)((char *)actor + 0x50);
        origin = *(SBGeoPoint2D *)((char *)sprite + 0x24);
    }
    else
        layer = 0;
    if (*(float *)((char *)this + 0x4730) > point.m_x &&
        *(float *)((char *)this + 0x4734) > point.m_y)
    {
        RHEngineGridCalls *grid = (RHEngineGridCalls *)((char *)this + 0x11c);
        if (*((char *)*(void **)((char *)this + 0x68) + 0x14))
        {
            if (grid->FUN_004e9920(point, origin, sector, layer) < 0)
                sector = 0;
        }
        else if (grid->FUN_004e9760(point, origin, sector, layer) < 0)
            sector = 0;
    }
    else
        sector = 0;
    *(unsigned short *)((char *)this + 0xc4) = layer;
    if (sector && ((*(unsigned *)((char *)sector + 0x30) >> 2) & 1))
    {
        building = *(void **)((char *)sector + 0x58);
        unsigned short index = *(unsigned short *)((char *)building + 0x13e);
        sector = index == 0xffff ? *(void **)((char *)this + 0x42a0) :
            (*(void ***)((char *)this + 0x4180))[index];
        *(unsigned short *)((char *)this + 0xc4) = *(unsigned short *)((char *)building + 0x13c);
    }
    bool result = true;
    if (!building)
    {
        if (!sector ||
            !((*(unsigned *)((char *)sector + 0x30) & 1) &&
                ((*(unsigned *)((char *)sector + 0x30) >> 1) & 1)) &&
            !((*(unsigned *)((char *)sector + 0x30) >> 12) & 1) &&
            (*(unsigned *)((char *)sector + 0x30) & 0x8000) != 0x8000)
            result = false;
    }
    *((char *)this + 0x4a98) = result;
}

// FUNCTION: GAME 0x004dee70
void RHEngine::FUN_004dee70(float *point)
{
    float scale = g_unk0x0067749c / *(float *)((char *)this + 0x475c);
    float *offset = (float *)((char *)*(void **)((char *)this + 0x68) + 0x84);
    float y = offset[1] * scale + *(float *)((char *)this + 0x473c);
    point[0] = offset[0] * scale + *(float *)((char *)this + 0x4738);
    point[1] = y;
}

// Parked: 53.01%.
// STUB: GAME 0x004e2390
void RHEngine::FUN_004e2390(void *actor)
{
    RHbeamMe beamMe;
    void **first = *(void ***)((char *)this + 0x4220);
    unsigned count = first ? *(void ***)((char *)this + 0x4224) - first : 0;
    if (!count)
    {
        SBAssert(0,
            // STRING: GAME 0x006af60c
            "P:\\Robin Hood\\RHengine.cpp", 0x3e44,
            // STRING: GAME 0x006af628
            "ACH DU DICKES SCHWEIN : Reinforcement cannot arrive because there is no reinforcement door !");
        return;
    }
    void *door = first[(unsigned)rand() % count];
    SBGeoPoint2D &origin = *(SBGeoPoint2D *)((char *)door + 0x18);
    beamMe.m_point = origin;
    beamMe.m_8 = *(unsigned short *)((char *)door + 0x14);
    void *doorSector = *(void **)((char *)door + 0xc);
    beamMe.m_a = doorSector ? *(unsigned short *)((char *)doorSector + 0x38) : 0xffff;
    void *sector = beamMe.m_a == 0xffff
        ? *(void **)((char *)this + 0x42a0)
        : (*(void ***)((char *)this + 0x4180))[beamMe.m_a];
    RHBonusProjection *projection = ((RHUnk0057d800 *)sector)->Unk(origin);
    if (!projection)
        beamMe.m_c = 0xffff;
    else
        beamMe.m_c = (unsigned short)((RHEngineReinforcementCalls *)((char *)this + 0x425c))->FUN_004e4460((void **)&projection, 1);
    beamMe.m_e = (char)*(unsigned *)((char *)this + 0x42a4);
    beamMe.m_10 = 0;
    void *description = ((RHEngineReinforcementCalls *)g_unk0x6c07fc)->FUN_00452130(*(void **)((char *)actor + 0x5fc));
    if (!description)
        return;
    ((RHEngineReinforcementCalls *)actor)->FUN_004936a0(0);
    RHUnk0048f280 *reinforcement = new RHUnk0048f280(description);
    *((char *)description + 0x44) = 1;
    *(unsigned short *)((char *)description + 0x3c) = 0xffff;
    ((RHEngineReinforcementCalls *)reinforcement)->FUN_00491fd0(beamMe);
    *(unsigned short *)((char *)reinforcement + 0x10) = 1;
    ((RHEngineReinforcementCalls *)this)->FUN_004d8460(reinforcement, 1, 1);
    FUN_0048c5b0(reinforcement, 0);
    RHUnk00582220 *sequence = new RHUnk00582220;
    RHUnk00588830 *arrival = new RHUnk00588830(1, 0x13, reinforcement, 6, 0);
    *(void **)((char *)arrival + 0x7c) = door;
    *(int *)((char *)arrival + 0x88) = 2;
    ((RHUnk00585500 *)arrival)->Unk(sequence);
    SBGeoPoint2D destination;
    unsigned attempt;
    SBGeoPoint2D &exit = *(SBGeoPoint2D *)((char *)door + 0x20);
    for (attempt = 0; attempt < 10; ++attempt)
    {
        destination = exit + SBGeoVector2D(
            (float)(rand() * 100) * g_unk0x00677f7c - g_unk0x00677484,
            (float)(rand() * 100) * g_unk0x00677f7c - g_unk0x00677484);
        if (((RHEngineReinforcementCalls *)((char *)this + 0x11c))->FUN_004f6c20(
            exit, destination, *(unsigned short *)((char *)door + 0x16),
            ((RHEngineReinforcementCalls *)reinforcement)->FUN_004a49e0()))
            break;
    }
    if (attempt < 10)
    {
        RHUnk005883a0 *movement = new RHUnk005883a0(2, 0x14, reinforcement, 6, destination, 0, 0, 1);
        ((RHUnk00585500 *)movement)->Unk(sequence);
    }
    ((RHUnk0058a3d0 *)((char *)this + 0x43f8))->Unk(g_unk0x6c0560, 0, sequence);
}

// FUNCTION: GAME 0x004e3020
RHElementActorPC *RHEngine::GetPC(RHPCDescription *description) const
{
    unsigned count = PCCount();
    for (unsigned i = 0; i < count; ++i)
    {
        void *actor = m_493c[i];
        if (*(RHPCDescription **)((char *)actor + 0x5f8) == description)
            return (RHElementActorPC *)actor;
    }
    void *profile = *(void **)((char *)description + 0x40);
    SBString *name = (SBString *)((char *)profile + 0x14);
    SBAssert(0, "P:\\Robin Hood\\RHengine.cpp", 0x3edf,
        // STRING: GAME 0x006afa58
        "ACHTUNG : PC for profile \"%s\" was not found !", name->m_chars ? name->m_chars : "");
    return 0;
}

// FUNCTION: GAME 0x004e3090
RHElementActorPC *RHEngine::GetPC(const RHCharacterProfile *profile) const
{
    unsigned count = PCCount();
    for (unsigned i = 0; i < count; ++i)
    {
        void *actor = m_493c[i];
        if (*(const RHCharacterProfile **)((char *)actor + 0x5fc) == profile)
            return (RHElementActorPC *)actor;
    }
    const char *name = *(const char **)((const char *)profile + 0x18);
    SBAssert(0, "P:\\Robin Hood\\RHengine.cpp", 0x3efc,
        "ACHTUNG : PC for profile \"%s\" was not found !", name ? name : "");
    return 0;
}

// FUNCTION: GAME 0x004e3520
void RHEngine::LoadDynRes(unsigned mission)
{
    char directory[0x104];
    GetCurrentDirectoryA(0x104, directory);
    SetCurrentDirectoryA(g_unk0x006c0664 ? g_unk0x006c0664 : "");
    if (!((RHMapDescription *)((char *)this + 0x4d68))->FUN_0063cda0(mission))
    {
        SBAssert(0, "P:\\Robin Hood\\RHengine.cpp", 0x4055,
            "Warning: unable to load the resource description for the mission '%s'\n", &mission);
    }
    SetCurrentDirectoryA(directory);
}

// FUNCTION: GAME 0x004e35f0
void RHEngine::FUN_004e35f0(SBFile &file)
{
    FUN_005e1d50(file, 0x544f544f, 2);
    unsigned short count;
    file.Access(&count, 2);
    while (count)
    {
        RHElementActorPC *actor = RHElementActorPC::CreatePCFromMissionStream(file);
        ((RHEngineReinforcementCalls *)this)->FUN_004d8460(actor, 1, 1);
        ((RHEngineWidenedCalls *)actor)->FUN_004e3660(0);
        --count;
    }
    FUN_005e20c0(file);
}

// TEMPLATE: GAME 0x004e40d0
// ??1?$vector@URHbeamMe@@V?$allocator@URHbeamMe@@@std@@@std@@QAE@XZ

// FUNCTION: GAME 0x004e4110
unsigned RHEngine::FUN_004e4110(unsigned value)
{
    return value - 1;
}

// SIZE 0x20
struct RHEnginePointerSearchLayout
{
    undefined4 m_00; // 0x00
    void **m_first; // 0x04
    void **m_last; // 0x08
    undefined4 m_0c; // 0x0c
    void **m_cursor; // 0x10
    char m_dirty; // 0x14
    char m_forward; // 0x15
    undefined m_16[2]; // 0x16
    int m_index; // 0x18
    void *m_key; // 0x1c
};

DECOMP_SIZE_ASSERT(RHEnginePointerSearchLayout, 0x20)

// Parked: vector-wrapper frame/inlining and shared beam destructor ABI differ.
// STUB: GAME 0x004e4120
void RHEngineBeamCalls::FUN_004e4120(RHbeamMe *position, unsigned count, const RHbeamMe &value)
{
    ((std::vector<RHbeamMe> *)this)->insert(position, count, value);
}

// STUB: GAME 0x004e4460
unsigned RHEngineReinforcementCalls::FUN_004e4460(void **value, int insert)
{
    RHEnginePointerSearchLayout &data = *(RHEnginePointerSearchLayout *)this;
    data.m_dirty = 0;
    data.m_key = *value;
    int count = !data.m_first ? 0 : data.m_last - data.m_first;
    int i = 0;
    if ((char)insert == 1)
    {
        data.m_forward = 1;
        data.m_cursor = data.m_first;
        for (; i < count; ++i, ++data.m_cursor)
        {
            if (*data.m_cursor == data.m_key)
                break;
        }
        return data.m_index = i < count ? i : -1;
    }
    else
    {
        data.m_forward = 0;
        data.m_cursor = data.m_last - 1;
        for (; count > 0; --count, --data.m_cursor)
        {
            if (*data.m_cursor == data.m_key)
                break;
        }
        return data.m_index = count > 0 ? count - 1 : -1;
    }
}

// FUNCTION: GAME 0x004e51e0
void *RHUnk004e51e0::FUN_004e51e0(unsigned flags)
{
    FUN_00454bb0();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x004e6f70
void FUN_004e6f70(void **first, void **last, bool (*compare)(void *, void *), void **value)
{
    while (16 < last - first)
    {
        void **middle = std::_Unguarded_partition(first, last,
            std::_Median(*first, *(first + (last - first) / 2), *(last - 1), compare), compare);
        if (last - middle <= middle - first)
        {
            FUN_004e6f70(middle, last, compare, (void **)0);
            last = middle;
        }
        else
        {
            FUN_004e6f70(first, middle, compare, (void **)0);
            first = middle;
        }
    }
}

// FUNCTION: GAME 0x004e70a0
void FUN_004e70a0(void **position, void *value, bool (*compare)(void *, void *))
{
    void **previous = position - 1;
    while (compare(value, *previous))
    {
        *position = *previous;
        position = previous;
        --previous;
    }
    *position = value;
}

// FUNCTION: GAME 0x004e7fa0
bool RHEngineBackgroundCalls::FUN_004e7fa0(unsigned short width, unsigned short height)
{
    *(unsigned short *)((char *)this + 0x3e98) = width;
    *(unsigned short *)((char *)this + 0x3e9a) = height + 4;
    ((SBGeoBoundingBox2D *)((char *)this + 0x3e84))->FUN_00609050(
        SBGeoPoint2D(0.0f, 0.0f),
        SBGeoPoint2D((float)((width << 6) - 1), (float)((height << 6) - 1)));
    return true;
}

// Parked: pointer-container allocation branch and insertion-loop register scheduling differ.
// STUB: GAME 0x004eb830
void RHEngineGridCalls::FUN_004eb830(SBFile &file)
{
    FUN_005e1d50(file, 0x54455854, 2);
    unsigned short count;
    file.Access(&count, 2);
    for (unsigned short i = 0; i < count; ++i)
    {
        unsigned char type;
        file.Access(&type, 1);
        void *sector = new RHUnk0057ee40;
        if (type >= 9)
            *(unsigned *)((char *)sector + 0x60) = *(unsigned *)((char *)this + 0x4188);
        else
            *(unsigned *)((char *)sector + 0x60) = type;
        ((RHEngineContinuationSectorCalls *)sector)->Serialize(file, false);
        RHScriptFXArray &sectors = *(RHScriptFXArray *)((char *)this + 0x4120);
        sectors.InsertLast(sector);
    }
    FUN_005e20c0(file);
}

// FUNCTION: GAME 0x004ebab0
void RHEngineGridCalls::FUN_004ebab0(SBFile &file)
{
    FUN_005e1d50(file, 0x4441524b, 2);
    unsigned short count;
    file.Access(&count, 2);
    for (unsigned short i = 0; i < count; ++i)
    {
        RHUnk0057ee90 *sector = new RHUnk0057ee90;
        *(unsigned *)((char *)sector + 0x30) = 0x4000;
        unsigned short layer;
        file.Access(&layer, 2);
        *(unsigned short *)((char *)sector + 0x36) = layer;
        ((RHEngineContinuationSectorCalls *)sector)->Serialize(file, false);
        unsigned flags;
        file.Access(&flags, 4);
        if (*(unsigned *)((char *)g_pEngine + 0x4ad0) & flags)
            ((RHFastFindGrid *)this)->FUN_004e8bd0(sector, layer, true);
        else
            delete (RHEngineContinuationSectorCalls *)sector;
    }
    FUN_005e20c0(file);
}

// FUNCTION: GAME 0x005052c0
void RHUnk005055b0::FUN_005052c0()
{
    for (RHUnk005069a0 *entry = (RHUnk005069a0 *)m_1c;
        entry != (RHUnk005069a0 *)m_20; ++entry)
    {
        RHUnk005069a0 value(*entry, 2);
        std::vector<RHUnk005069a0> &values = *(std::vector<RHUnk005069a0> *)((char *)this + 0x38);
        values.insert(values.end(), value);
    }
}

// FUNCTION: GAME 0x00505520
void RHUnk005055b0::FUN_00505520(int value)
{
    switch (value)
    {
    case 1:
    {
        std::vector<RHUnk005069a0> &items = *(std::vector<RHUnk005069a0> *)((char *)this + 0x28);
        items.erase(items.begin(), items.end());
        break;
    }
    case 2:
    {
        std::vector<RHUnk005069a0> &items = *(std::vector<RHUnk005069a0> *)((char *)this + 0x38);
        items.erase(items.begin(), items.end());
        break;
    }
    }
}

// FUNCTION: GAME 0x005055b0
void RHUnk005055b0::FUN_005055b0()
{
    for (char *it = m_1c; it != m_20; it += 0x14)
        ((RHEngineWidenedCalls *)it)->FUN_00504b80(
            g_pEngine->FUN_004d2340(15));
    for (it = m_3c; it != m_40; it += 0x14)
        ((RHEngineWidenedCalls *)it)->FUN_00504b80(
            g_pEngine->FUN_004d2340(15));
    for (it = m_2c; it != m_30; it += 0x14)
        ((RHEngineWidenedCalls *)it)->FUN_00504b80(
            g_pEngine->FUN_004d2340(15));
}

// FUNCTION: GAME 0x00505640
void RHUnk005055b0::FUN_00505640()
{
    for (RHUnk005069a0 *entry = (RHUnk005069a0 *)m_1c;
        entry != (RHUnk005069a0 *)m_20; ++entry)
    {
        RHUnk005069a0 value(*entry, 1);
        std::vector<RHUnk005069a0> &values = *(std::vector<RHUnk005069a0> *)((char *)this + 0x28);
        values.insert(values.end(), value);
    }
}

// FUNCTION: GAME 0x0050f000
void RHEngineSerializationCalls::FUN_0050f000()
{
    (*(RHEngineWidenedCalls **)((char *)this + 0x196c))->FUN_0055ebf0();
}

// FUNCTION: GAME 0x0050f010
void RHEngineSerializationCalls::FUN_0050f010()
{
    (*(RHEngineRosterCalls **)((char *)this + 0x196c))->FUN_0055eda0();
    if (*(char *)((char *)this + 0x5a))
    {
        RHUnk00452030 *campaign = g_unk0x6c07fc;
        unsigned count = (*(RHEngineRosterCalls **)((char *)this + 0x196c))->FUN_0055e880();
        RHEngineMenuWidgetCalls *menu = (RHEngineMenuWidgetCalls *)((char *)this + 0x1970);
        if (count > 5)
        {
            menu->v14((char *)this + 0x1f7c);
            menu->v14((char *)this + 0x1eac);
            ((RHEngineMenuWidgetCalls *)((char *)this + 0x1c48))->v21(true);
            ((RHEngineMenuWidgetCalls *)((char *)this + 0x1d14))->v21(true);
        }
        else
        {
            menu->v15((char *)this + 0x1f7c);
            menu->v15((char *)this + 0x1eac);
            ((RHEngineMenuWidgetCalls *)((char *)this + 0x1c48))->v21(false);
            ((RHEngineMenuWidgetCalls *)((char *)this + 0x1d14))->v21(false);
        }
        void **mission = *(void ***)((char *)campaign + 0x17c);
        if (mission)
            ((RHEngineMenuWidgetCalls *)((char *)this + 0x21e4))->v21(
                count != 0 &&
                (count <= *(unsigned short *)((char *)*mission + 0x72) || *(char *)((char *)this + 0x57) == 1) &&
                !((RHEngineMenuStateCalls *)this)->FUN_00514970());
        if (count)
            menu->v14((char *)this + 0x1de0);
        else
            menu->v15((char *)this + 0x1de0);
    }
}

// FUNCTION: GAME 0x0051cd10
void RHHikingGuide::FUN_0051cd10(SBFile &file)
{
    FUN_005e1d50(file, 0x5241494c, 3);
    int count = m_04.size();
    for (int i = 0; i < count; ++i)
        delete m_04[i];
    m_04.erase(m_04.begin(), m_04.end());
    m_18 = 1;
    unsigned short loaded;
    file.Access(&loaded, 2);
    for (unsigned short index = 0; index < loaded; ++index)
        FUN_0051cac0(file);
    FUN_005e20c0(file);
}

// FUNCTION: GAME 0x0051d020
bool RHHikingGuide::FUN_0051d020(SBFile &file)
{
    // STRING: GAME 0x006b0668
    RHSerializeName(file, "RHHikingGuide");
    bool result = true;
    unsigned short count = m_04.size();
    for (unsigned short i = 0; i < count; ++i)
    {
        RHUnk0051d2c0 *group = m_04[i];
        unsigned short entries = group->m_00.size();
        for (unsigned short j = 0; j < entries; ++j)
        {
            RHUnk00551da0 *entry = group->m_00[j];
            result |= entry->FUN_00551da0(file);
        }
    }
    return result;
}

// FUNCTION: GAME 0x00523620
bool RHUnk00523620::FUN_00523620()
{
    char *storage = (char *)this;
    (*(RHEngineWidenedCalls **)(storage + 0x18))->FUN_005e5160(*(unsigned *)(storage + 0x24));
    (*(RHEngineWidenedCalls **)(storage + 0x18))->FUN_005e5160(*(unsigned *)(storage + 0x28));
    operator delete(g_unk0x006c0bd4);
    g_unk0x006c0bd4 = 0;
    (*(RHUnk00523620Object **)(storage + 0xc))->Unk18();
    (*(RHUnk00523620Object **)(storage + 0x10))->Unk18();
    if (*(RHUnk00523620Object **)(storage + 0xc))
        (*(RHUnk00523620Object **)(storage + 0xc))->Unk08(1);
    if (*(RHUnk00523620Object **)(storage + 0x10))
        (*(RHUnk00523620Object **)(storage + 0x10))->Unk08(1);
    if (*(RHUnk00523620Owned **)(storage + 0x14))
        (*(RHUnk00523620Owned **)(storage + 0x14))->Unk00(1);
    return true;
}

// FUNCTION: GAME 0x00556470
void RHUnk00556470::FUN_00556470()
{
    ((RHEngineWidenedCalls *)this)->FUN_005563f0(0x55555555);
    ((RHEngineWidenedCalls *)this)->FUN_00556260();
}

// FUNCTION: GAME 0x0055dbb0
char *RHUnk0055dbb0::FUN_0055dbb0()
{
    return *(char **)((char *)this + 0x28);
}

// FUNCTION: GAME 0x005709a0
void FUN_005709a0(void *value, unsigned index)
{
    g_unk0x6c0f34[index] = value;
    if (value)
        *(unsigned short *)((char *)value + 0x8a) = (unsigned short)index;
}

// FUNCTION: GAME 0x0057e680
void RHEngineBuildingCalls::FUN_0057e680(void *actor)
{
    RHUnk004b1520List &occupants = *(RHUnk004b1520List *)((char *)this + 0xf4);
    occupants.FUN_00424410(occupants.end(), actor);
    occupants.m_10 = true;
    ((RHEngineBuildingActorCalls *)actor)->v40(*(unsigned short *)((char *)g_unk0x6c0a9c + 0x3e9c) - 1, this);
    ((RHSeqList *)((char *)this + 0x80))->GoTo(0);
    RHSeqList *locations = (RHSeqList *)((char *)this + 0x5c);
    locations->GoTo(0);
    ((RHActorPositionCalls *)(*(char **)((char *)actor + 0x50) + 4))->FUN_00464530(
        *(SBGeoPoint2D *)((char *)locations->cursor->data + 0x20));
    *(char *)((char *)actor + 0x12) = 0;
}

// Parked: cached-cursor address lifetime, frame size and iterator scheduling differ.
// STUB: GAME 0x0058a430
void RHEngineSerializationCalls::FUN_0058a430()
{
    unsigned short count = *(volatile unsigned *)((char *)this + 0xc);
    RHEngineSequenceList &sequences = *(RHEngineSequenceList *)((char *)this + 4);
    for (unsigned short i = 0; i < count; ++i)
    {
        if (((RHEngineSequenceStateCalls *)sequences.Get(i, false, true))->FUN_005823f0())
        {
            RHEngineSerializedElement *sequence = (RHEngineSerializedElement *)sequences.Get(i, false, false);
            if (sequence)
                delete sequence;
            ((RHUnk0046eb30 *)&sequences)->erase(RHScriptIter(sequences.cursor));
            sequences.dirty = true;
            --i;
            --count;
        }
    }
}

// Parked: cached-cursor address lifetime and loop/receiver register allocation differ.
// STUB: GAME 0x0058a7d0
bool RHEngineSequenceStateCalls::FUN_0058a7d0(void *element)
{
    void *sequence = *(void **)((char *)element + 0x54);
    if (FUN_0058a670(sequence))
    {
        unsigned short count = *(volatile unsigned *)((char *)sequence + 0x10);
        RHEngineSequenceList &elements = *(RHEngineSequenceList *)((char *)sequence + 8);
        for (unsigned short i = 0; i < count; ++i)
            if (elements.Get(i, true, true) == element)
                return true;
    }
    return false;
}

// FUNCTION: GAME 0x0058c590
void RHUnk0058c590::FUN_0058c590(char flag, unsigned short width, unsigned short height)
{
    m_64.FUN_00607da0(*(RHMobileUnk00607da0 *)((char *)g_unk0x6c0a9c + 0x3e84));
    m_4c = *(undefined4 *)((char *)g_pEngine + 0x48c4);
    FUN_0058c6f0(flag);
    FUN_0058c630(width, height);
    m_c2 = 0xff;
    m_c4 = 0xff;
    m_c6 = 0xff;
    int value = *(int *)((char *)g_pEngine + 0x4ad0);
    m_60 = value == 4 || value == 2;
    if (m_60)
        m_c0 = 0x78;
    else
        m_c0 = 0xc0;
}

// FUNCTION: GAME 0x005a5c50
void RHEngineSerializationCalls::FUN_005a5c50()
{
    *(unsigned *)((char *)this + 0x198) = 0;
    *(unsigned *)((char *)this + 0x1a0) = 0;
}

// FUNCTION: GAME 0x005a5cd0
void FUN_005a5cd0()
{
    g_unk0x006c1058 = 0;
    g_unk0x006c1060 = 0;
}

class RHProfileFile
{
public:
    int FUN_005f5370(int offset, int origin);
};

// FUNCTION: GAME 0x005e1d00
unsigned long FUN_005e1d00(SBFile &file)
{
    unsigned long value;
    file.Access(&value, 4);
    ((RHProfileFile *)&file)->FUN_005f5370(-4, 1);
    return ((value & 0xff00 | value << 16) << 8) |
        ((value & 0xff0000 | value >> 16) >> 8);
}

// FUNCTION: GAME 0x005e2300
void FUN_005e2300(SBFile &file)
{
    unsigned long tag;
    int size;
    file.Access(&tag, 4);
    file.Access(&size, 4);
    ((RHProfileFile *)&file)->FUN_005f5370(size, 1);
}

// FUNCTION: GAME 0x005fc5d0
SBGeoVector2D RHUnk005fc3b0::FUN_005fc5d0(float value)
{
    RHUnk005fc3b0 result;
    result.m_x = m_x / value;
    result.m_y = m_y / value;
    return SBGeoVector2D(result);
}

// FUNCTION: GAME 0x00611660
bool RHEngineBackgroundCalls::FUN_00611660(const std::string &path)
{
    RHUnk005f4fc0 file;
    if (file.FUN_005f5090(path, 1) != 0)
        return false;
    bool result = ((RHUnk00611660Calls *)this)->Unk10(file);
    file.FUN_005f5290();
    return result;
}

void RHEngine::Emit(SBFile &file, void *&value)
{
    ((RHEngineGridCalls *)this)->FUN_004eb830(file);
    ((RHEngineGridCalls *)this)->FUN_004ebab0(file);
    FUN_004debf0(*(SBGeoPoint2D *)&value);
    FUN_004c2720(file);
    FUN_004e6f70((void **)0, (void **)0, (bool (*)(void *, void *))0, (void **)0);
    ((RHUnk005055b0 *)this)->FUN_005052c0();
    ((RHUnk005055b0 *)this)->FUN_00505640();
    ((RHHikingGuide *)value)->FUN_0051cd10(file);
    ((RHHikingGuide *)value)->FUN_0051d020(file);
    ((RHUnk00462a90 *)value)->FUN_00462a90((const char *)value);
    ((RHUnk00486170 *)value)->FUN_00486170(value, 0);
    ((RHUnk004a66d0 *)value)->FUN_004a66d0(0);
    ((RHUnk004a6000 *)value)->FUN_004a6000();
    ((RHUnk004a6310 *)value)->FUN_004a6310(0);
    ((RHUnk004a7d70 *)value)->FUN_004a7d70(0);
    ((RHUnk004a7ed0 *)value)->FUN_004a7ed0(0);
    ((RHUnk004b0980 *)value)->FUN_004b0980(0);
    ((RHUnk004b91a0 *)value)->FUN_004b91a0(0);
    ((RHUnk004be080 *)value)->FUN_004be080(0);
    ((RHUnk004ba900 *)value)->FUN_004ba900(0);
    FUN_004c8120(value);
    FUN_004c38d0(file, (unsigned *)value);
    FUN_004dee70((float *)value);
    value = (void *)FUN_004e4110((unsigned)value);
    ((RHUnk00556470 *)value)->FUN_00556470();
    ((RHUnk005055b0 *)value)->FUN_005055b0();
    ((RHUnk005055b0 *)value)->FUN_00505520(1);
    ((RHUnk00523620 *)value)->FUN_00523620();
    value = ((RHUnk0055dbb0 *)value)->FUN_0055dbb0();
    InitializeActorsFromMissionStream(file, *(std::vector<RHbeamMe> *)value);
    FUN_004c1d20(file);
    FUN_004c2150(file);
    InitializeBuildingTenantsFromMissionStream(file);
    FUN_004c3af0(file, value);
    FUN_004c3bd0(file, value);
    FUN_004c3d90(file, value);
    FUN_004c3f50(file, value);
    FUN_004c4030(file, value);
    FUN_004c41f0(file, value);
    FUN_004c42d0(file, value);
    FUN_004c43b0(file, value);
    FUN_004c4490(file, value);
    GetPC((RHPCDescription *)value);
    GetPC((const RHCharacterProfile *)value);
    LoadDynRes(0);
    ((RHUnk005fc3b0 *)value)->FUN_005fc5d0(1.0f);
}
