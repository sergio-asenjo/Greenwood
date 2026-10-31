#include "SBNullstr.h"
#include "RHSectorActorList.h"
#include "RHSaveGame.h"
#include "RHSaveGameManager.h"
#include "RHEngine.h"
#include "RHCivilianProfile.h"
#include "VMCore.h"
#include <windows.h>
#include <algorithm>
#include <iterator>
#include <stdlib.h>
#include <math.h>

class RHFastFindGrid
{
public:
    void FUN_004e8bd0(void *sector, unsigned short layer, bool mode);
    void FUN_004efd10(void *value, unsigned short layer, bool mode);
};

class RHEngineActorUpdateCalls
{
public:
    void FUN_004af2a0();
};

#include "RHEngineActorActionCalls.h"

// GLOBAL: GAME 0x006785d8
float g_unk0x006785d8 = -1.0f;

class RHSequenceElement;
#include "RHScriptListCore.h"

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
    __forceinline void GoTo(int index) { ((RHSectorActorList *)this)->Unk005c8e40(index); }
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


struct RHUnk005c9010Iterator;
void FUN_005c9010(RHUnk005c9010Iterator &current, int distance, std::bidirectional_iterator_tag category);

#include "RHTitbitsCore.h"

class RHEngineActorOrderCalls
{
public:
    virtual void Unk00() = 0;
    virtual void Unk04() = 0;
    virtual void Unk08() = 0;
    virtual void Unk0c() = 0;
    virtual void Unk10() = 0;
    virtual void Unk14() = 0;
    virtual bool Matches(void *target, int mode, int flags) = 0;
};

class RHEngineSequenceList
{
public:
    int allocator;
    RHScriptNode *head;
    int count;
    RHScriptNode *cursor;
    bool dirty;
    int index;
    void Clear();
    __forceinline void Advance(int distance)
    {
        while (distance > 0) { cursor = cursor->next; --distance; }
        while (distance < 0) { cursor = cursor->prev; ++distance; }
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
    __forceinline RHScriptIter BeginUnk004e1fc0() { return RHScriptIter(head->next); }
    __forceinline RHScriptIter EndUnk004e1fc0() { return RHScriptIter(head); }
    __forceinline RHScriptNode *&SetCurrentUnk004e1fc0(RHScriptIter value)
    {
        cursor = value.node;
        return cursor;
    }
    __forceinline RHScriptIter &CurrentIterator() { return *(RHScriptIter *)&cursor; }
    __forceinline void GoToUnk004e1fc0(int wanted, bool inlineForward = false)
    {
        int size = count;
        if (dirty)
        {
            if (wanted <= (size + 1) / 2)
            {
                std::bidirectional_iterator_tag category;
                FUN_005c9010((RHUnk005c9010Iterator &)SetCurrentUnk004e1fc0(BeginUnk004e1fc0()), wanted, category);
            }
            else
            {
                std::bidirectional_iterator_tag category;
                FUN_005c9010((RHUnk005c9010Iterator &)SetCurrentUnk004e1fc0(EndUnk004e1fc0()), wanted - size, category);
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
                            FUN_005c9010((RHUnk005c9010Iterator &)SetCurrentUnk004e1fc0(BeginUnk004e1fc0()), wanted, category);
                        else
                            FUN_005c9010((RHUnk005c9010Iterator &)(CurrentIterator() = ((RHUnk0046eb30 *)this)->FUN_0046eb80()), wanted, category);
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
                        FUN_005c9010((RHUnk005c9010Iterator &)SetCurrentUnk004e1fc0(EndUnk004e1fc0()), wanted - size, category);
                    }
                }
                index = wanted;
            }
        }
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
DECOMP_SIZE_ASSERT(RHMobileBase004a8130, 0xfc)
DECOMP_SIZE_ASSERT(RHUnk005069a0, 0x14)
class RHUnk0057ee90
{
public:
    RHUnk0057ee90();
    virtual ~RHUnk0057ee90();
    undefined m_00[0x6c];
};

DECOMP_SIZE_ASSERT(RHUnk0057ee90, 0x70)
DECOMP_SIZE_ASSERT(RHUnk005055b0, 0x44)
DECOMP_SIZE_ASSERT(RHUnk004bc5b0, 0x160)
DECOMP_SIZE_ASSERT(RHUnk004e51e0, 0x30)
DECOMP_SIZE_ASSERT(RHUnk00551da0, 0x04)
DECOMP_SIZE_ASSERT(RHUnk0051d2c0, 0x20)
DECOMP_SIZE_ASSERT(RHHikingGuide, 0x24)
DECOMP_SIZE_ASSERT(RHUnk005f4fc0, 0x58)
DECOMP_SIZE_ASSERT(RHUnk004a1bc0, 0xdd0)
DECOMP_SIZE_ASSERT(RHEngineExtendedMissionElementCalls, 0x04)
DECOMP_SIZE_ASSERT(RHEngineContinuationSectorCalls, 0x04)

bool FUN_005e0c90(SBFile &file, std::string &value);
void RHSerializeName(SBFile &file, const char *name);
extern void **g_unk0x6c0f34;
extern void **g_unk0x6c0f38;

#include "RHEngineWidenedCalls.h"
#include "RHElementObject.h"
#include "RHUnkTargetSpriteCalls.h"
#include "RHPortraitBar.h"

class RHUnk005bd5b0
{
public:
    bool Unk(bool);
};

void *FUN_004b3120(int type);

// GLOBAL: GAME 0x006c1058
unsigned g_unk0x006c1058 = 0;

// GLOBAL: GAME 0x006c105c
float g_unk0x006c105c = 0.0f;

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
class SBGeoVector2D;
#include "SBGeoPoint2D.h"
#include "RHUnk0054eab0.h"

DECOMP_SIZE_ASSERT(RHUnk0054eab0, 0x1a0)

DECOMP_SIZE_ASSERT(SBGeoPoint2D, 0x08)

#include "RHPathRequest.h"

DECOMP_SIZE_ASSERT(RHpathRequest, 0x3c)

class RHUnk004bf6d0
{
public:
    ~RHUnk004bf6d0();
    undefined m_00[0x128];
    SBGeoPoint2D m_128;
    SBGeoPoint2D m_130;
    SBGeoPoint2D m_138;
};

class RHUnk00452030;
extern RHUnk00452030 *g_unk0x6c07fc;
class RHUnk0048a970;
extern RHUnk0048a970 *g_unk0x6c0b3c;

#include "RHElementActorPC.h"

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

#include "RHSequenceAppendCalls.h"

class RHUnk0058a3d0
{
public:
    void *Unk(void *context, int value, void *sequence);
};

#include "RHSequenceGenericCalls.h"

class RHUnk005866a0
{
public:
    RHUnk005866a0(unsigned short level, int command, void *actor);
    ~RHUnk005866a0();
    void Unk00586ed0(int property, int value);
    char data[0x74];
};

class RHUnk00588530
{
public:
    RHUnk00588530(unsigned short level, int command, void *actor, int style,
        void *target, float distance, void *value);
    RHUnk00588530(unsigned short level, int command, void *actor, int style, int value);
    ~RHUnk00588530();
    char data[0x68];
    RHUnk00582220 *sequence;
    char tail[0x30];
};

#include "RHActorCancelCalls.h"

#include "RHScriptEngineCalls.h"

class RHSequenceFilterCalls
{
public:
    virtual void Unk00() = 0; virtual void Unk04() = 0; virtual void Unk08() = 0;
    virtual void Unk0c() = 0; virtual void Unk10() = 0; virtual void Unk14() = 0;
    virtual bool Filter(void *value, void *sequence, int type) = 0;
};

class RHElementActorHuman
{
public:
    int FUN_0047b760(void *actor, int *value);
};

#include "RHSequenceInteractionAction.h"

class RHUnk5490f0
{
public:
    RHUnk5490f0(int value);
    ~RHUnk5490f0();
    char data[0x10];
};

class RHUnk00549250 : public RHUnk5490f0
{
public:
    RHUnk00549250(int type, void *actor);
    RHUnk00549250(int type, void *actor, int action);
    ~RHUnk00549250();
    char tail[4];
};

class RHMessenger
{
public:
    void RHUnk005460c0(RHUnk5490f0 &message);
};

RHMessenger *RHUnk00546050();

class RHEngineSequenceDispatchCalls
{
public:
    virtual void Unk00() = 0; virtual void Unk01() = 0; virtual void Unk02() = 0; virtual void Unk03() = 0;
    virtual void Unk04() = 0; virtual void Unk05() = 0; virtual void Unk06() = 0; virtual void Unk07() = 0;
    virtual void Unk08() = 0; virtual void Unk09() = 0; virtual void Unk10() = 0; virtual void Unk11() = 0;
    virtual void Unk12() = 0; virtual void Unk13() = 0; virtual void Unk14() = 0; virtual void Unk15() = 0;
    virtual void Unk16() = 0; virtual void Unk17() = 0; virtual void Unk18() = 0; virtual void Unk19() = 0;
    virtual void Unk20() = 0; virtual void Unk21() = 0; virtual void Unk22() = 0; virtual void Unk23() = 0;
    virtual void Unk24() = 0; virtual void Unk25() = 0; virtual void Unk26() = 0; virtual void Unk27() = 0;
    virtual void Unk28() = 0; virtual void Unk29() = 0; virtual void Unk30() = 0; virtual void Unk31() = 0;
    virtual void Unk32() = 0; virtual void Unk33() = 0; virtual void Unk34() = 0; virtual void Unk35() = 0;
    virtual void Unk36() = 0; virtual void Unk37() = 0; virtual void Unk38() = 0; virtual void Unk39() = 0;
    virtual void Unk40() = 0; virtual void Unk41() = 0; virtual void Unk42() = 0; virtual void Unk43() = 0;
    virtual void Unk44() = 0; virtual void Unk45() = 0; virtual void Unk46() = 0; virtual void Unk47() = 0;
    virtual void Unk48() = 0; virtual void Unk49() = 0; virtual void Unk50() = 0; virtual void Unk51() = 0;
    virtual void Unk52() = 0; virtual void Unk53() = 0; virtual void Unk54() = 0; virtual void Unk55() = 0;
    virtual void Unk56() = 0; virtual void Unk57() = 0; virtual void Unk58() = 0; virtual void Unk59() = 0;
    virtual void Unk60() = 0; virtual void Unk61() = 0; virtual bool Test() = 0; virtual void Unk63() = 0;
    virtual void Unk64() = 0;
    virtual void Dispatch(int first, int second, int third) = 0;
    virtual void Unk66() = 0; virtual void Unk67() = 0; virtual void Unk68() = 0; virtual void Unk69() = 0;
    virtual void Unk70() = 0; virtual void Unk71() = 0; virtual void Unk72() = 0; virtual void Unk73() = 0;
    virtual void Unk74() = 0; virtual void Unk75() = 0; virtual void Unk76() = 0; virtual void Unk77() = 0;
    virtual void Unk78() = 0; virtual void Unk79() = 0; virtual void Unk80() = 0; virtual void Unk81() = 0;
    virtual void Unk82() = 0; virtual void Unk83() = 0; virtual void Unk84() = 0; virtual void Unk85() = 0;
    virtual void Unk86() = 0; virtual void Unk87() = 0; virtual void Unk88() = 0; virtual void Unk89() = 0;
    virtual void Unk90() = 0; virtual void Unk91() = 0;
    virtual void Apply(RHUnk00582220 *node, int value, unsigned short layer, void *effect) = 0;
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
    ~RHbeamMe();
    void *FUN_004e51e0(unsigned flags);
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
    void FUN_004a4a40();
    bool FUN_004f6c20(const SBGeoPoint2D &origin, SBGeoPoint2D &destination,
        unsigned short layer, const SBGeoPoint2D &extent);
};

class RHUnk0048f280
{
public:
    RHUnk0048f280(void *description);
    char m_data[0x60c];
};


// SIZE 0x08
class SBGeoVector2D : public SBGeoPoint2D
{
public:
    SBGeoVector2D(float x, float y);
    SBGeoVector2D(const SBGeoPoint2D &value);
    SBGeoVector2D();
    SBGeoVector2D &operator=(const SBGeoVector2D &other);
    SBGeoVector2D(const SBGeoVector2D &other);
};

DECOMP_SIZE_ASSERT(SBGeoVector2D, 0x08)

void EmitRHEngineReset(RHEngine *engine)
{
    engine->FUN_004c04a0();
}

// SIZE 0x08
class RHUnk005fc3b0 : public SBGeoVector2D
{
public:
    RHUnk005fc3b0() {}
    SBGeoVector2D FUN_005fc5d0(float value);
    float Unk005fc6a0(float value);
};

class RHUnk005b5e00
{
public:
    void *Unk();
    SBGeoPoint2D *Unk005bdd30(short index);
    SBGeoPoint2D *FUN_004e0490(int index, short base);
};

#include "RHUnk00613e90.h"

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
    unsigned long Unk005e4ed0(int, int, int, bool);
    char m_00[0x10c];
    unsigned short m_depth;
};

#include "RHUnk006114c0.h"
#include "SBPicture.h"

#include "RHEngineBackgroundCalls.h"

// SIZE 0x14
class SBGeoBoundingBox2D
{
public:
    SBGeoBoundingBox2D();
    int FUN_00609050(const SBGeoPoint2D &first, const SBGeoPoint2D &second);
    bool FUN_00608400(const SBGeoPoint2D &point) const;
    void SetFirst(const SBGeoPoint2D &point) { m_10 = true; m_first = point; }
    void SetSecond(const SBGeoPoint2D &point) { m_10 = true; m_second = point; }
    ~SBGeoBoundingBox2D() {}
    SBGeoPoint2D m_first;
    SBGeoPoint2D m_second;
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
bool FUN_005f6400(const std::string &path);
std::string FUN_004e4b40(const std::string &first, const std::string &second);





#include "RHMapDescription.h"

DECOMP_SIZE_ASSERT(RHMapDescription, 0x1c)
DECOMP_SIZE_ASSERT(RHMapDescription::Entry, 0x48)

// GLOBAL: GAME 0x006c0664
char *g_unk0x006c0664 = 0;

// GLOBAL: GAME 0x006c0a7c
int g_unk0x006c0a7c = 0;

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
        value = FUN_004622e0(index, &g_pEngine->m_elements); \
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

class RHUnkEngineScriptRef
{
public:
    int FUN_00404080(int value);
    int FUN_00404180(int value);
    int FUN_00404280(int value);
    void FUN_00404380(int message, int argument1, int argument2);
    void FUN_00404480(int value);
    void FUN_00404570();
    void *m_0;
};

// FUNCTION: GAME 0x00404080
int RHUnkEngineScriptRef::FUN_00404080(int value)
{
    ((VMCore *)m_0)->FUN_006392e0(&value, 4);
    ((VMCore *)m_0)->FUN_00639300(&std::string("Initialize"));
    int result;
    ((VMCore *)m_0)->FUN_00639360(result);
    return result;
}

// FUNCTION: GAME 0x00404180
int RHUnkEngineScriptRef::FUN_00404180(int value)
{
    ((VMCore *)m_0)->FUN_006392e0(&value, 4);
    // STRING: GAME 0x006a6ca0
    ((VMCore *)m_0)->FUN_00639300(&std::string("Hourglass"));
    int result;
    ((VMCore *)m_0)->FUN_00639360(result);
    return result;
}

// FUNCTION: GAME 0x00404280
int RHUnkEngineScriptRef::FUN_00404280(int value)
{
    ((VMCore *)m_0)->FUN_006392e0(&value, 4);
    // STRING: GAME 0x006a6cac
    ((VMCore *)m_0)->FUN_00639300(&std::string("CheckVictoryCondition"));
    int result;
    ((VMCore *)m_0)->FUN_00639360(result);
    return result;
}

// FUNCTION: GAME 0x00404380
void RHUnkEngineScriptRef::FUN_00404380(int message, int argument1, int argument2)
{
    ((VMCore *)m_0)->FUN_006392e0(&message, 4);
    ((VMCore *)m_0)->FUN_006392e0(&argument1, 4);
    ((VMCore *)m_0)->FUN_006392e0(&argument2, 4);
    ((VMCore *)m_0)->FUN_00639300(&std::string("ProcessMessage"));
}

// FUNCTION: GAME 0x00404480
void RHUnkEngineScriptRef::FUN_00404480(int value)
{
    ((VMCore *)m_0)->FUN_006392e0(&value, 4);
    // STRING: GAME 0x006a6cc4
    ((VMCore *)m_0)->FUN_00639300(&std::string("Finalize"));
}

// FUNCTION: GAME 0x00404570
void RHUnkEngineScriptRef::FUN_00404570()
{
    // STRING: GAME 0x006a6cd0
    ((VMCore *)m_0)->FUN_00639300(&std::string("PostInitialize"));
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

class RHUnk00486180
{
public:
    RHUnk00486180 *FUN_00486180();
};

// FUNCTION: GAME 0x00486180
RHUnk00486180 *RHUnk00486180::FUN_00486180()
{
    *(int *)this = *(int *)*(int *)this;
    return this;
}

void EmitRHUnk00486180(RHUnk00486180 *a)
{
    a->FUN_00486180();
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
    if (((RHElementObject *)this)->Create(flag, *(const RHElementObject *)FUN_004b3120(type)) == true) \
    { \
        unsigned &current = *(unsigned *)((char *)this + 0xb4); \
        if (current != row) \
        { \
            RHEngineWidenedCalls *sprite = *(RHEngineWidenedCalls **)((char *)this + 0x50); \
            current = row; \
            sprite->FUN_005bd450(); \
            (*(RHUnkTargetSprite **)((char *)this + 0x50))->FUN_005b76e0(row, 0); \
        } \
        return true; \
    } \
    return false;

// FUNCTION: GAME 0x004a49e0
SBGeoVector2D RHEngineReinforcementCalls::FUN_004a49e0()
{
    return ((RHSpritePositionCalls *)((char *)*(void **)((char *)this + 0x50) + 4))->FUN_004a4a10();
}

class RHUnkPathActorInfoBase
{
public:
    void *Unk0055fa10(int index);
};

// FUNCTION: GAME 0x004a4a10
SBGeoVector2D RHSpritePositionCalls::FUN_004a4a10()
{
    return *(SBGeoVector2D *)((char *)((RHUnkPathActorInfoBase *)this)->Unk0055fa10(*(int *)((char *)this + 0x88)) + 8);
}

class RHPositionInterface
{
public:
    bool TurnSlow(unsigned char delay);
};

// Parked: the first TurnSlow argument push precedes the receiver adjustment.
// STUB: GAME 0x004a4a40
void RHEngineReinforcementCalls::FUN_004a4a40()
{
    char *sprite = *(char **)((char *)this + 0x50);
    switch ((*(unsigned short *)(sprite + 0xd8) - *(unsigned short *)(sprite + 0xda)) & 15)
    {
    case 0:
    case 1:
    case 2:
    case 14:
    case 15:
        ((RHPositionInterface *)(sprite + 4))->TurnSlow(5);
        break;
    default:
        ((RHPositionInterface *)(sprite + 4))->TurnSlow(2);
        break;
    }
}

void EmitRHDirectionTurn(RHEngineReinforcementCalls *element)
{
    element->FUN_004a4a40();
}

// FUNCTION: GAME 0x004a6000
bool RHUnk004a6000::FUN_004a6000()
{
    RHENGINE_OBJECT_CREATE(3, 0xc3, 1)
}

// FUNCTION: GAME 0x004a6060
char RHUnk004a6000::FUN_004a6060() const
{
    return *(const char *)((const char *)this + 0x12);
}

// FUNCTION: GAME 0x004a6310
bool RHUnk004a6310::FUN_004a6310(bool flag)
{
    RHENGINE_OBJECT_CREATE(4, 0xc4, flag)
}

// FUNCTION: GAME 0x004a6370
int RHUnk004a6310::FUN_004a6370() const
{
    return 0x1fd;
}

class RHProjectileLifetime
{
public:
    RHProjectileLifetime(int action, void *victim);
    char m_00[0xb0];
    int m_b0;
    char m_b4[0xa8];
    int m_15c;
    char m_160;
    char m_161;
    char m_162;
    char m_163;
    unsigned short m_164;
    char m_166;
};

class __declspec(novtable) RHUnk004a6670 : public RHProjectileLifetime
{
public:
    RHUnk004a6670(void *victim, int value);
};

class __declspec(novtable) RHUnk004a65f0 : public RHProjectileLifetime
{
public:
    RHUnk004a65f0();
};

// FUNCTION: GAME 0x004a65f0
RHUnk004a65f0::RHUnk004a65f0() : RHProjectileLifetime(1, 0)
{
    m_15c = 0;
    m_160 = 1;
    m_161 = 0;
    m_162 = 0;
    m_163 = 0;
    m_164 = 0;
    m_166 = 0;
    *(unsigned *)this = 0x678288;
    m_b0 = 5;
}

// FUNCTION: GAME 0x004a6670
RHUnk004a6670::RHUnk004a6670(void *victim, int value) : RHProjectileLifetime(1, victim)
{
    m_161 = 0;
    m_162 = 0;
    m_163 = 0;
    m_164 = 0;
    m_15c = value;
    m_160 = 1;
    *(unsigned *)this = 0x678288;
    m_b0 = 5;
}

// FUNCTION: GAME 0x004a66d0
bool RHUnk004a66d0::FUN_004a66d0(bool flag)
{
    return ((RHElementObject *)this)->Create(flag, *(const RHElementObject *)FUN_004b3120(5));
}

class RHUnk004a7b00
{
public:
    bool FUN_004a7b00();
};

class RHUnk004a7820
{
public:
    bool FUN_004a7820();
    void FUN_004a7900();
};

// FUNCTION: GAME 0x004a7820
bool RHUnk004a7820::FUN_004a7820()
{
    ((RHEngineWidenedCalls *)*(void **)((char *)this + 0x50))->FUN_005b7f60(0);
    FUN_004a7900();
    return true;
}

void RHUnk004a7820::FUN_004a7900()
{
}

// FUNCTION: GAME 0x004a7b00
bool RHUnk004a7b00::FUN_004a7b00()
{
    int value = *(int *)((char *)this + 0xb0);
    if (value == 0x1a || value == 0x1b || value == 0x1c || value == 0x1d ||
        value == 0x1e || value == 0x1f || value == 0x20)
        return true;
    return false;
}

class RHUnk004a7d10
{
public:
    void *FUN_004a7d40(unsigned flags);
    RHUnk004a7d10();
    ~RHUnk004a7d10();
    bool FUN_004a7d30(int first, int second, int third);
    bool FUN_004a7dd0();
    void FUN_004b1eb0(int first, int second, int third);
    void FUN_004b1fb0();
};

// FUNCTION: GAME 0x004a7d10
RHUnk004a7d10::RHUnk004a7d10()
{
    FUN_004b1eb0(3, 0, 0);
    *(unsigned *)this = 0x67839c;
}

// FUNCTION: GAME 0x004a7d30
bool RHUnk004a7d10::FUN_004a7d30(int first, int second, int third)
{
    return false;
}

// FUNCTION: GAME 0x004a7d40
void *RHUnk004a7d10::FUN_004a7d40(unsigned flags)
{
    this->~RHUnk004a7d10();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x004a7d60
RHUnk004a7d10::~RHUnk004a7d10()
{
    *(unsigned *)this = 0x67839c;
    FUN_004b1fb0();
}

void RHUnk004a7d10::FUN_004b1eb0(int, int, int) {}
void RHUnk004a7d10::FUN_004b1fb0() {}

// FUNCTION: GAME 0x004a7dd0
bool RHUnk004a7d10::FUN_004a7dd0()
{
    ((RHEngineWidenedCalls *)*(void **)((char *)this + 0x50))->FUN_005b7f60(0);
    return true;
}

void EmitRHUnk004a7d10(RHUnk004a7d10 *a, RHUnk004a7b00 *b)
{
    a->FUN_004a7d30(0, 0, 0);
    b->FUN_004a7b00();
}

class RHElementCoin;

class RHElementPurse
{
public:
    void AddChild(RHElementCoin *coin);
};

class RHElementProjectile
{
public:
    virtual bool Serialize(SBFile &file);
};

class __declspec(novtable) RHUnk004a7e90 : public RHProjectileLifetime
{
public:
    RHUnk004a7e90(void *victim);
    bool Serialize(SBFile &file);
};

// FUNCTION: GAME 0x004a7e90
RHUnk004a7e90::RHUnk004a7e90(void *victim) : RHProjectileLifetime(4, victim)
{
    m_15c = 0;
    *(unsigned *)this = 0x678410;
    m_b0 = 8;
}

// FUNCTION: GAME 0x004a8040
bool RHUnk004a7e90::Serialize(SBFile &file)
{
    g_pEngine->FUN_004c43b0(file, *(void **)&m_15c);
    if (file.m_bLoading && m_15c)
        (*(RHElementPurse **)&m_15c)->AddChild((RHElementCoin *)this);
    return ((RHElementProjectile *)this)->RHElementProjectile::Serialize(file);
}

void EmitRHUnk004a7e90(void *storage, void *victim)
{
    ((RHUnk004a7e90 *)storage)->Serialize(*(SBFile *)victim);
    ((RHUnk004a7e90 *)storage)->RHUnk004a7e90::RHUnk004a7e90(victim);
    ((RHUnk004a6670 *)storage)->RHUnk004a6670::RHUnk004a6670(victim, 0);
    ((RHUnk004a65f0 *)storage)->RHUnk004a65f0::RHUnk004a65f0();
}

// FUNCTION: GAME 0x004a7d70
bool RHUnk004a7d70::FUN_004a7d70(bool flag)
{
    RHENGINE_OBJECT_CREATE(13, 0xbe, flag)
}

// FUNCTION: GAME 0x004a7ed0
bool RHUnk004a7ed0::FUN_004a7ed0(bool flag)
{
    RHENGINE_OBJECT_CREATE(8, 0xc4, flag)
}

// FUNCTION: GAME 0x004a7f30
int RHUnk004a7ed0::FUN_004a7f30()
{
    return 3;
}

// FUNCTION: GAME 0x004a7f40
void RHUnk004a7ed0::FUN_004a7f40(int first, int second, int third)
{
}

// FUNCTION: GAME 0x004a7f50
void RHUnk004a7ed0::FUN_004a7f50()
{
    *(int *)((char *)*(RHEngineWidenedCalls **)((char *)this + 0x50) + 0xe0) = *(int *)((char *)*(RHEngineWidenedCalls **)((char *)this + 0x50) + 0xe8);
    *(short *)((char *)*(RHEngineWidenedCalls **)((char *)this + 0x50) + 0xde) = *(short *)((char *)*(RHEngineWidenedCalls **)((char *)this + 0x50) + 0xe4);
    FUN_0048c5b0(this, 2);
}

#include "RHProjectileSoundCalls.h"

// FUNCTION: GAME 0x004a7f80
bool RHUnk004a7ed0::FUN_004a7f80()
{
    if (*((char *)this + 0x132))
    {
        ((RHProjectileRefreshCalls *)this)->FUN_004b82e0();
        (*(RHEngineWidenedCalls **)((char *)this + 0x50))->FUN_005b7f60(3);
        return true;
    }
    RHEngineWidenedCalls *sprite = *(RHEngineWidenedCalls **)((char *)this + 0x50);
    if (*(unsigned *)((char *)sprite + 0x1dc) != 0xc5 && *(unsigned *)((char *)this + 0xb4) != 0xc5)
    {
        *(unsigned *)((char *)this + 0xb4) = 0xc5;
        sprite->FUN_005bd450();
        (*(RHUnkTargetSprite **)((char *)this + 0x50))->FUN_005b76e0(0xc5, 0);
    }
    (*(RHEngineWidenedCalls **)((char *)this + 0x50))->FUN_005b7f60(8);
    return true;
}

// FUNCTION: GAME 0x004ba970
int RHUnk004ba900::FUN_004ba970()
{
    return 0x1fc;
}

class RHUnk6c1040;
extern RHUnk6c1040 *g_unk0x6c1040;

// FUNCTION: GAME 0x004ba980
bool RHUnk004ba900::FUN_004ba980(void *target)
{
    (*(RHUnkTargetSprite **)((char *)this + 0x50))->FUN_005b76e0(0xc5, 0);
    if (((RHScriptBatchCalls *)target)->Unk004baea0() & 0x20)
    {
        RHUnk00585ea0 *action = new RHUnk00585ea0(1, 0x98, target, InteractionTarget());
        ((RHScriptBatchCalls *)g_unk0x6c1040)->Unk0058a940("", 0, action);
        return true;
    }
    return false;
}

// FUNCTION: GAME 0x004b0980
bool RHUnk004b0980::FUN_004b0980(bool flag)
{
    RHENGINE_OBJECT_CREATE(9, 0xc4, flag)
}

class RHUnk004b09e0
{
public:
    char FUN_004b09e0();
};

// FUNCTION: GAME 0x004b09e0
char RHUnk004b09e0::FUN_004b09e0()
{
    return *(char *)((char *)this + 0x1c4) ? 0x0a : 0x28;
}

void EmitRHUnk004b09e0(RHUnk004b09e0 *a)
{
    a->FUN_004b09e0();
}

// FUNCTION: GAME 0x004b91a0
bool RHUnk004b91a0::FUN_004b91a0(bool flag)
{
    RHENGINE_OBJECT_CREATE(7, 0xc4, flag)
}

// FUNCTION: GAME 0x004ba900
bool RHUnk004ba900::FUN_004ba900(bool flag)
{
    if (((RHElementObject *)this)->Create(flag, *(const RHElementObject *)FUN_004b3120(6)) == true)
    {
        unsigned &current = *(unsigned *)((char *)this + 0xb4);
        if (current != 0xc4)
        {
            RHEngineWidenedCalls *sprite = *(RHEngineWidenedCalls **)((char *)this + 0x50);
            current = 0xc4;
            sprite->FUN_005bd450();
            (*(RHUnkTargetSprite **)((char *)this + 0x50))->FUN_005b76e0(0xc4, 0);
        }
        (*(RHUnk005bd5b0 **)((char *)this + 0x50))->Unk(false);
        return true;
    }
    return false;
}

// FUNCTION: GAME 0x004be080
bool RHUnk004be080::FUN_004be080(bool flag)
{
    RHENGINE_OBJECT_CREATE(11, 0xc4, flag)
}

#undef RHENGINE_OBJECT_CREATE

class RHElementActor
{
public:
    void FUN_00462730(RHElementActor *actor, bool value);
    void FUN_0046bcb0(int value);
    int FUN_00462a30(RHElementActor *other);
    void FUN_0046bab0();
    void FUN_0046bb80();
};

// SIZE 0x0c
struct RHEngineSpritePoint
{
    RHEngineSpritePoint();
    undefined4 m_00; // 0x00
    undefined4 m_04; // 0x04
    undefined4 m_08; // 0x08
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

inline void RHSetWaspState(RHUnk004bc5b0 *wasp, unsigned type, unsigned row)
{
    unsigned current = wasp->m_b4;
    wasp->m_b0 = type;
    if (current != row)
    {
        RHEngineWidenedCalls *sprite = (RHEngineWidenedCalls *)wasp->m_sprite;
        wasp->m_b4 = row;
        sprite->FUN_005bd450();
        ((RHUnkTargetSprite *)wasp->m_sprite)->FUN_005b76e0(row, 0);
    }
}

// FUNCTION: GAME 0x004bc5b0
bool RHUnk004bc5b0::FUN_004bc5b0(bool flag)
{
    if (!((RHElementObject *)this)->Create(flag, *(const RHElementObject *)FUN_004b3120(10)))
        return false;
    if (m_parent)
    {
        ((RHElementActor *)this)->FUN_00462730((RHElementActor *)m_parent, false);
        RHEngineSpritePosition *sprite = (RHEngineSpritePosition *)((char *)m_sprite + 4);
        sprite->Assign(*(RHEngineSpritePoint *)((char *)m_parent->m_sprite + 0x10));
        *(unsigned *)((char *)m_sprite + 8) = 7;
    }
    RHSetWaspState(this, 10, 0xbe);
    return true;
}

inline unsigned RHEngineIndexedPointerCount(RHEngine *engine, void **first)
{
    if (first == 0)
        return 0;
    return *(void ***)((char *)engine + 0x48e0) - first;
}

// FUNCTION: GAME 0x004be5c0
void FUN_004be5c0(SBFile &file, void *&value)
{
    bool loading = file.m_bLoading;
    RHEngine *engine = g_pEngine;
    unsigned identifier;
    if (!loading) {
        void *saved = value;
        void **first = *(void ***)((char *)engine + 0x48dc);
        for (unsigned short i = 0; i < RHEngineIndexedPointerCount(engine, first); ++i) {
            if ((*(void **volatile *)((char *)engine + 0x48dc))[i] == saved) {
                identifier = *(unsigned *)((char *)saved + 0x0c);
                file.Access(&identifier, 4);
                return;
            }
        }
        identifier = 0xffffffff;
        file.Access(&identifier, 4);
        return;
    }
    file.Access(&identifier, 4);
    if (identifier == 0xffffffff) {
        value = 0;
        return;
    }
    void **first = *(void **volatile *)((char *)engine + 0x48dc);
    for (unsigned short i = 0; i < RHEngineIndexedPointerCount(engine, first); ++i) {
        if (*(unsigned *)((char *)(*(void ***)((char *)engine + 0x48dc))[i] + 0x0c) == identifier) {
            value = (*(void ***)((char *)engine + 0x48dc))[i];
            return;
        }
    }
    value = 0;
}

// FUNCTION: GAME 0x004bf6d0
RHUnk004bf6d0::~RHUnk004bf6d0()
{
}

class RHUnk004bf740Item
{
public:
    unsigned m_0;
    char *m_4;
    unsigned m_8;
    unsigned m_c;
};

class RHUnk004bf740
{
public:
    void FUN_004bf740();
    char m_0[0x2c];
    RHUnk004bf740Item *m_2c;
    RHUnk004bf740Item *m_30;
    RHUnk004bf740Item *m_34;
};

// Parked at 0.7294: the inlined std::string destroy differs from the original's string layout (extra SSO byte store and tail ret).
// STUB: GAME 0x004bf740
void RHUnk004bf740::FUN_004bf740()
{
    char *last = (char *)m_30;
    char *first = (char *)m_2c;
    while (first != last)
    {
        ((std::string *)first)->~basic_string();
        first += 0x10;
    }
    operator delete(m_2c);
    m_2c = 0;
    m_30 = 0;
    m_34 = 0;
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


// Parked: cached-selection probes retain different payload registers, flag stores and return scheduling.
// STUB: GAME 0x0049b590
int RHEngine::FUN_0049b590(void *actor)
{
    int count = *(int *)((char *)this + 0x4a00);
    if (!actor)
        return count != 0;
    void *&wanted = *(void **)((char *)this + 0x4a18);
    RHScriptNode *&cursor = *(RHScriptNode **)((char *)this + 0x4a04);
    int &found = *(int *)((char *)this + 0x4a14);
    wanted = actor;
    *(bool *)((char *)this + 0x4a10) = true;
    cursor = (*(RHScriptNode **)((char *)this + 0x49fc))->next;
    int index = 0;
    for (; index < count; ++index)
    {
        RHScriptNode *node = *(RHScriptNode *volatile *)&cursor;
        void *value = *(void *volatile *)&wanted;
        if (node->data == value)
            break;
        cursor = cursor->next;
    }
    if (index < count)
    {
        found = index;
        *(bool *)((char *)this + 0x4a08) = false;
        *(int *)((char *)this + 0x4a0c) = index;
    }
    else
    {
        *(bool *)((char *)this + 0x4a08) = true;
        found = -1;
    }
    return *(volatile int *)&found != -1;
}

class RHShadowPolygon
{
public:
    void FUN_0058c6f0(bool);
};

extern undefined g_unk0x006c0e48[];

// FUNCTION: GAME 0x004c02d0
bool RHEngine::FUN_004c02d0()
{
    char *profile = ((RHUnk0055dbb0 *)g_unk0x006c0e48)->FUN_0055dbb0();
    (*(RHShadowPolygon **)((char *)this + 0x43f4))->FUN_0058c6f0(*(bool *)(profile + 0x52));
    for (unsigned short i = 0;; i++)
    {
        void **first = *(void **volatile *)((char *)this + 0x48dc);
        if (i >= (first == 0 ? 0 : *(void ***)((char *)this + 0x48e0) - first))
            break;
        ((RHUnk00462a90 *)(*(void ***)((char *)this + 0x48dc))[i])->FUN_00462a90(profile + 0x50);
    }
    return true;
}

// FUNCTION: GAME 0x004c0340
bool RHEngine::FUN_004c0340(SBGeoPoint2D &point)
{
    bool top = false;
    bool left = top;
    if (point.m_x < 0.0f) {
        point.m_x = 0.0f;
        left = true;
    }
    if (point.m_y < 0.0f) {
        point.m_y = 0.0f;
        top = true;
    }
    float right = *(volatile float *)((char *)this + 0x4730);
    if (point.m_x + *(volatile float *)((char *)this + 0x4728) /
        *(float *)((char *)this + 0x475c) > right) {
        if (left == true)
            point = SBGeoPoint2D(0.0f, 0.0f);
        else {
            float maximum = *(volatile float *)((char *)this + 0x4730);
            point.m_x = maximum -
                *(float *)((char *)this + 0x4728) / *(float *)((char *)this + 0x475c);
        }
    }
    float bottom = *(volatile float *)((char *)this + 0x4734);
    if (point.m_y + (*(volatile float *)((char *)this + 0x472c) - 80.0f) /
        *(float *)((char *)this + 0x475c) > bottom) {
        if (top == true)
            point = SBGeoPoint2D(0.0f, 0.0f);
        else {
            point.m_y = *(volatile float *)((char *)this + 0x4734) -
                (*(float *)((char *)this + 0x472c) - 80.0f) /
                *(float *)((char *)this + 0x475c);
        }
    }
    return top | left;
}

// FUNCTION: GAME 0x004c04a0
bool RHEngine::FUN_004c04a0()
{
    SBGeoVector2D point;
    ((RHEngineReset51bd90 *)((char *)this + 0x4624))->FUN_0051bd90();
    ((RHEngineReset581c70 *)((char *)this + 0x4608))->FUN_00581c70();
    ((RHEngineReset5c2570 *)((char *)this + 0x4668))->FUN_005c2570();
    return true;
}

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
        (g_unk0x006c05f0 + "\\"),
        *(std::string *)((char *)this + 0xa4)), protoExtension);
    std::string missionExtension(".rhm");
    missionPath = FUN_004e4b40(FUN_004e4b40(
        (g_unk0x006c05f0 + "\\"),
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

// FUNCTION: GAME 0x004c1be0
void RHEngine::InitializeActorsFromMissionStream(SBFile &file, std::vector<RHbeamMe> &beamMes)
{
    FUN_005e1d50(file, 0x424f595a, 3);
    unsigned short count;
    file.Access(&count, 2);
    for (unsigned short i = 0; i < count; ++i)
    {
        g_unk0x006c0a7c = 9;
        g_unk0x6c0a50.m_progress += 20.0f / (int)count;
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
            {
                FUN_005e2300(file);
                typedef void (*Assert)(int, const char *, int, const char *, ...);
                Assert report = &SBAssert;
                report(0, "P:\\Robin Hood\\RHengine.cpp", 0x544,
                    // STRING: GAME 0x006af3b0
                    "ACHTUNG : Unimplemented chunk skipped");
            }
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
            void *actor = m_elements[index];
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
            unsigned length = strlen("");
            if (beamMe.m_text.FUN_00402280(length, true))
            {
                memcpy(beamMe.m_text.m_chars, "", length);
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

class RHEngineActorVector : public std::vector<void *>
{
public:
    __forceinline size_type ReloadingSize() const
    {
        void **first = *(void **volatile *)&_First;
        return first == 0 ? 0 : _Last - first;
    }
};

#include "RHCampaignCore.h"

// FUNCTION: GAME 0x004c2720
void RHEngine::FUN_004c2720(SBFile &file)
{
    *(int *)((char *)this + 0x4a44) = g_unk0x6c0f34 == 0 ? 0 : g_unk0x6c0f38 - g_unk0x6c0f34;
    *(unsigned *)((char *)this + 0x4a48) = g_unk0x006c081c;
    std::vector<void *> &actors = *(std::vector<void *> *)((char *)this + 0x48d8);
    ((RHCampaign *)g_unk0x6c07fc)->FUN_00450c10(*(SBArray<RHElement *> *)&actors, *(std::vector<RHbeamMe> *)&file);
    std::vector<void *> &remaining = *(std::vector<void *> *)((char *)this + 0x4978);
    int index = *(int *)((char *)this + 0x4a44) + remaining.size();
    for (; index < (int)((RHEngineActorVector *)&actors)->ReloadingSize(); ++index)
        ((RHEngineReinforcementCalls *)this)->FUN_004d8460((*(std::vector<void *> *)((char *)this + 0x48d8))[index], 0, 0);
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
        mapPath = FUN_004e4b40(FUN_004e4b40((g_unk0x006c05f0 + "\\Day\\"), name), mapExtension);
        if (!FUN_005f6400(mapPath))
        {
            mapPath = FUN_004e4b40(FUN_004e4b40((g_unk0x006c05f0 + "\\"), name), mapExtension);
            if (!FUN_005f6400(mapPath))
                SBAssert(1, "P:\\Robin Hood\\RHengine.cpp", 0x73d,
                    // STRING: GAME 0x006af4f4
                    "STRENG VERBOTEN : Unable to find map file %s in directory %s (ambiance %s), file error",
                    name.c_str(), g_unk0x006c05f0.c_str(), ambiance.c_str());
        }
    }
    ((RHEngineBackgroundCalls *)&map)->FUN_00611660(mapPath);
    g_unk0x006c0a7c = 7;
    g_unk0x6c0a50.m_progress += 10.0f;
    g_unk0x6c0a50.FUN_00523300();
    float &width = *(float *)((char *)this + 0x4730);
    float &height = *(float *)((char *)this + 0x4734);
    width = (float)map.m_width;
    height = (float)map.m_height;
    RHUnkFXDraw *draw = *(RHUnkFXDraw **)((char *)this + 0xdc);
    unsigned long surface = draw->Unk005e4ed0((int)width, (int)height, 0, 0);
    *(unsigned long *)((char *)this + 0x48c4) = surface;
    extern float g_unk0x00677680;
    float backgroundWidth = width;
    float backgroundHeight = height;
    ((RHEngineBackgroundCalls *)((char *)this + 0x11c))->FUN_004e7fa0(
        (int)(backgroundWidth * g_unk0x00677680), (int)(backgroundHeight * g_unk0x00677680));
    map.Unk00611e10(draw->m_depth == 16 ? 3 : 2, 0);
    ((SBPicture *)&map)->SBPicture::Unk00613530(draw, surface);
    g_unk0x006c0a7c = 7;
    g_unk0x6c0a50.m_progress += 5.0f;
    g_unk0x6c0a50.FUN_00523300();
    // STRING: GAME 0x006af4ec
    std::string minimapExtension(".min");
    minimapPath = FUN_004e4b40(FUN_004e4b40(FUN_004e4b40(g_unk0x006c05f0, ambiance), name), minimapExtension);
    if (!FUN_005f6400(minimapPath))
    {
        minimapPath = FUN_004e4b40(FUN_004e4b40((g_unk0x006c05f0 + "\\Day\\"), name), minimapExtension);
        if (!FUN_005f6400(minimapPath))
        {
            minimapPath = FUN_004e4b40(FUN_004e4b40((g_unk0x006c05f0 + "\\"), name), minimapExtension);
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
    ((SBPicture *)&minimap)->SBPicture::Unk00613530(draw, surface);
    g_unk0x006c0a7c = 7;
    g_unk0x6c0a50.m_progress += 5.0f;
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
        RHMobileBase004a8130 *actor = new RHMobileBase004a8130(1);
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
        ((RHFastFindGrid *)grid)->FUN_004efd10(value,
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

#include "RHCampaignValueCalls.h"

class RHUnk0048a970;
extern RHUnk0048a970 *g_unk0x6c0b3c;

#include "RHEngineSerializationCalls.h"

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

// Parked: mission-state dispatch, helper calls, and nested container cleanup remain unrecovered.
// STUB: GAME 0x004c6ef0
int RHEngine::FUN_004c6ef0()
{
    char *engine = (char *)this;
    int result = 0;
    bool active = *(char *)(engine + 0x4790) != 0;
    if (active && engine[0x4a50])
    {
        void **actors = *(void ***)(engine + 0x493c);
        unsigned count = actors ? (unsigned)(*(void ***)(engine + 0x4940) - actors) : 0;
        for (unsigned i = 0; i < count; ++i)
        {
            void *actor = actors[i];
            if (*(void **)((char *)actor + 0x5e8))
                ((RHPortraitBar *)actor)->FUN_0055ebf0();
        }
    }
    if (*(void **)(engine + 0x4be0))
        *(void **)(engine + 0x4be0) = 0;
    extern unsigned short g_unk0x006c08f2;
    if (g_unk0x006c08f2)
        --g_unk0x006c08f2;
    if (engine[0x4a52])
        return 2;
    if (engine[0x4a53])
        return 3;
    if (engine[0x4a54])
        return 3;
    if (engine[0x4be5])
        engine[0x4be5] = 0;
    if (engine[0x4be6])
        engine[0x4be6] = 0;
    if (engine[0x4be7])
        engine[0x4be7] = 0;
    if (engine[0x4be8])
        engine[0x4be8] = 0;
    ++*(unsigned *)(engine + 0x4a94);
    if (engine[0x4790] || engine[0x4791] || engine[0xd0])
        result = 1;
    else if (FUN_004c7cf0())
        result = 1;
    else
    {
        void **actors = *(void ***)(engine + 0x493c);
        unsigned count = actors ? (unsigned)(*(void ***)(engine + 0x4940) - actors) : 0;
        for (unsigned i = 0; i < count; ++i)
        {
            void *actor = actors[i];
            if (*(char *)((char *)actor + 0x4e8) &&
                !*(void **)((char *)actor + 0x5e8))
            {
                result = 1;
                break;
            }
        }
    }
    return result;
}

// FUNCTION: GAME 0x004c7c90
bool RHEngine::FUN_004c7c90()
{
    char *engine = (char *)this;
    return engine[0x4768] == 0 && engine[0x48c0] != 4 &&
        engine[0x4790] == 0 && engine[0x4791] == 0;
}

// FUNCTION: GAME 0x004c7cc0
int RHEngine::FUN_004c7cc0()
{
    return !FUN_004c7c90();
}

extern double g_unk0x006774b8;


// FUNCTION: GAME 0x004c7cd0
bool RHEngine::FUN_004c7cd0()
{
    return *(float *)((char *)this + 0x475c) < 2.0f;
}

// FUNCTION: GAME 0x004c7cf0
bool RHEngine::FUN_004c7cf0()
{
    char *engine = (char *)this;
    if (*(float *)(engine + 0x475c) > g_unk0x006774b8)
    {
        double inverse = 2.0f / *(float *)(engine + 0x475c);
        if (*(float *)(engine + 0x4728) * inverse <= *(float *)(engine + 0x4730) &&
            (*(float *)(engine + 0x472c) - 80.0f) * inverse <=
            *(float *)(engine + 0x4734))
            return true;
    }
    return false;
}

// FUNCTION: GAME 0x004c7d50
unsigned RHEngine::FUN_004c7d50()
{
    if (*(char *)0x006c069b == 1)
        return 0;
    switch (*(unsigned *)((char *)this + 0x4ad0))
    {
    case 2:
        return 2;
    case 4:
        return 1;
    default:
        return 0;
    }
}

// FUNCTION: GAME 0x004c7d80
bool RHEngine::FUN_004c7d80(void *first, int second, void **result)
{
    *result = 0;
    if (*(int *)((char *)this + 0x4a00) != 0)
    {
        void **actors = *(void ***)((char *)this + 0x48fc);
        unsigned count = actors == 0
            ? 0 : (unsigned)(*(void ***)((char *)this + 0x4900) - actors);
        for (unsigned index = count - 1; index != (unsigned)-1; --index)
        {
            void *context = **(void ***)((char *)this + 0x49fc);
            if (((RHEngineActorOrderCalls *)(*(void ***)((char *)this + 0x48fc))[index])->Matches(first,
                *(int *)((char *)context + 8), second) == true)
            {
                if (result)
                    *result = (*(void ***)((char *)this + 0x48fc))[index];
                return true;
            }
        }
    }
    return false;
}

// FUNCTION: GAME 0x004c7e10
bool RHEngine::FUN_004c7e10(void *first, int second, void **result)
{
    unsigned size = *(volatile unsigned *)((char *)this + 0x4a00);
    void *context;
    if (size) {
        RHScriptNode *head = *(RHScriptNode *volatile *)((char *)this + 0x49fc);
        context = head->next->data;
    }
    else
        context = 0;
    void **actors = *(void ***)((char *)this + 0x493c);
    unsigned count = actors == 0
        ? 0 : (unsigned)(*(void ***)((char *)this + 0x4940) - actors);
    for (unsigned index = count - 1; index != (unsigned)-1; --index)
    {
        RHEngineActorOrderCalls *actor = (RHEngineActorOrderCalls *)(*(void ***)((char *)this + 0x493c))[index];
        if (actor->Matches(first, (int)context, second) == true)
        {
            if (result)
                *result = (*(void ***)((char *)this + 0x493c))[index];
            return true;
        }
    }
    return false;
}

// FUNCTION: GAME 0x004c7eb0
bool RHEngine::FUN_004c7eb0(void *first, int second, void **result)
{
    unsigned size = *(volatile unsigned *)((char *)this + 0x4a00);
    void *context;
    if (size) {
        RHScriptNode *head = *(RHScriptNode *volatile *)((char *)this + 0x49fc);
        context = head->next->data;
    }
    else
        context = 0;
    void **actors = *(void ***)((char *)this + 0x495c);
    unsigned count = actors == 0
        ? 0 : (unsigned)(*(void ***)((char *)this + 0x4960) - actors);
    for (unsigned index = count - 1; index != (unsigned)-1; --index)
    {
        RHEngineActorOrderCalls *actor = (RHEngineActorOrderCalls *)(*(void ***)((char *)this + 0x495c))[index];
        if (actor->Matches(first, (int)context, second) == true)
        {
            if (result)
                *result = (*(void ***)((char *)this + 0x495c))[index];
            return true;
        }
    }
    return false;
}

#include "RHPCSelectionQueryCalls.h"

// FUNCTION: GAME 0x004c7f50
void __stdcall FUN_004c7f50(void *value)
{
    ((RHUnk00493a80 *)value)->FUN_00493a80();
}

// Parked: x87 clamp ordering and non-trivial point temporary cleanup differ from target.
// STUB: GAME 0x004c7f60
void RHEngine::FUN_004c7f60(const void *point)
{
    char *engine = (char *)this;
    SBGeoPoint2D position(*(const SBGeoPoint2D *)point);
    engine[0x72] = 0;
    engine[0x73] = 0;
    engine[0x48d0] = 0;
    float scale = *(float *)(engine + 0x475c);
    float minimumX = *(float *)(engine + 0x4730) -
        *(float *)(engine + 0x4728) / scale;
    float minimumY = *(float *)(engine + 0x4734) -
        (*(float *)(engine + 0x472c) - 80.0f) / scale;
    if (position.m_x < 0.0f)
        position.m_x = 0.0f;
    if (position.m_y < 0.0f)
        position.m_y = 0.0f;
    if (position.m_x >= minimumX)
        position.m_x = minimumX;
    if (position.m_y >= minimumY)
        position.m_y = minimumY;
    FUN_004db7f0(position);
    *(unsigned short *)(engine + 0x4782) = 0;
    *(unsigned short *)(engine + 0x4784) = 0;
}

// FUNCTION: GAME 0x004c8120
void RHEngine::FUN_004c8120(void *actor)
{
    FUN_004c7f60((char *)*(void **)((char *)actor + 0x50) + 0x24);
}

// FUNCTION: GAME 0x004cab20
bool __stdcall FUN_004cab20(unsigned short first, unsigned short second, void *list)
{
    unsigned key = first < second
        ? ((unsigned)first << 16) | second
        : ((unsigned)second << 16) | first;
    void *head = *(void **)((char *)list + 4);
    void *node = *(void **)head;
    while (node != head)
    {
        if (*(unsigned *)((char *)node + 8) == key)
            return false;
        node = *(void **)node;
    }
    return true;
}

// FUNCTION: GAME 0x004cab80
void __stdcall FUN_004cab80(unsigned short first, unsigned short second, void *list)
{
    unsigned key = first < second
        ? ((unsigned)first << 16) | second
        : ((unsigned)second << 16) | first;
    void *head = *(void **)((char *)list + 4);
    void *previous = *(void **)((char *)head + 4);
    void *node = (void *)operator new(12);
    *(void **)node = head ? head : node;
    *(void **)((char *)node + 4) = previous ? previous : node;
    *(void **)((char *)head + 4) = node;
    *(void **)*(void **)((char *)node + 4) = node;
    unsigned *payload = (unsigned *)((char *)node + 8);
    if (payload)
        *payload = key;
    ++*(unsigned *)((char *)list + 8);
}

// Parked: target's actor geometry, visibility, and message passes are not reconstructed.
// STUB: GAME 0x004cac00
int RHEngine::FUN_004cac00(void *first, void *second, int third, char fourth)
{
    (void)first;
    (void)second;
    (void)third;
    (void)fourth;
    struct Node
    {
        Node *next;
        Node *previous;
        unsigned value;
        unsigned unused;
    };
    struct PairSet
    {
        char prefix[4];
        Node *head;
        unsigned count;
    } pairs;
    Node sentinel;
    sentinel.next = &sentinel;
    sentinel.previous = &sentinel;
    pairs.head = &sentinel;
    pairs.count = 0;
    unsigned count = *(unsigned *)((char *)this + 0x4a00) & 0xffff;
    for (unsigned firstIndex = 0; firstIndex < count; ++firstIndex)
    {
        for (unsigned secondIndex = firstIndex + 1; secondIndex < count; ++secondIndex)
        {
            if (FUN_004cab20((unsigned short)firstIndex, (unsigned short)secondIndex, &pairs))
                FUN_004cab80((unsigned short)firstIndex, (unsigned short)secondIndex, &pairs);
        }
    }
    Node *node = sentinel.next;
    while (node != &sentinel)
    {
        Node *next = node->next;
        operator delete(node);
        node = next;
    }
    return 1;
}

struct RHUnk004cc030Value
{
    unsigned m_00;
    unsigned m_04;
};

struct RHUnk004cc030Node
{
    RHUnk004cc030Node *next;
    RHUnk004cc030Node *previous;
    RHUnk004cc030Value value;
};

class RHUnk004cc030
{
public:
    void *FUN_004e6a90(unsigned flags);
    char m_00;
    char m_01[3];
    SBGeoPoint2D point;
    char enabled;
    char padding[3];
    RHUnk004cc030Node *head;
    unsigned count;
    RHUnk004cc030();
    RHUnk004cc030(const RHUnk004cc030 &other);
    ~RHUnk004cc030();
};

inline RHUnk004cc030::RHUnk004cc030(const RHUnk004cc030 &other)
    : m_00(other.m_00), point(other.point), enabled(other.enabled)
{
    RHUnk004cc030Node *sentinel = (RHUnk004cc030Node *)operator new(sizeof(RHUnk004cc030Node));
    sentinel->next = sentinel;
    sentinel->previous = sentinel;
    head = sentinel;
    count = 0;
    RHUnk004cc030Node *position = sentinel->next;
    RHUnk004cc030Node *last = other.head;
    for (RHUnk004cc030Node *source = last->next; source != last; source = source->next)
    {
        RHUnk004cc030Node *previous = position->previous;
        RHUnk004cc030Node *node = (RHUnk004cc030Node *)operator new(sizeof(RHUnk004cc030Node));
        node->next = position != 0 ? position : node;
        node->previous = previous != 0 ? previous : node;
        position->previous = node;
        node->previous->next = node;
        new (&node->value) RHUnk004cc030Value(source->value);
        ++count;
    }
}

// Parked: 74.07%; constructor frame/argument-slot layout differs after local-node source shape.
// FUNCTION: GAME 0x004cc030
RHUnk004cc030::RHUnk004cc030() : point()
{
    char flag;
    enabled = flag;
    RHUnk004cc030Node *node = new RHUnk004cc030Node;
    node->next = node;
    node->previous = node;
    head = node;
    count = 0;
}

// Parked: 30.99%; cleanup semantics are present, but compiler emits an EH frame and different node/cursor register schedule.
// FUNCTION: GAME 0x004cc0a0
RHUnk004cc030::~RHUnk004cc030()
{
    RHUnk004cc030Node *sentinel = head;
    RHUnk004cc030Node *node = sentinel->next;
    while (node != sentinel)
    {
        RHUnk004cc030Node *removed = node;
        node = node->next;
        removed->previous->next = removed->next;
        removed->next->previous = removed->previous;
        operator delete(removed);
        --count;
    }
    operator delete(*(RHUnk004cc030Node *volatile *)((char *)this + 0x10));
    head = 0;
    count = 0;
}

// FUNCTION: GAME 0x004e6a90
void *RHUnk004cc030::FUN_004e6a90(unsigned flags)
{
    this->~RHUnk004cc030();
    if (flags & 1)
        operator delete(this);
    return this;
}

// Parked: selector/list branches beyond coordinate validation remain unresolved.
// STUB: GAME 0x004cc100
unsigned short RHEngine::FUN_004cc100(void *first, void *second)
{
    *(char *)((char *)this + 0x4718) = 1;
    bool active = FUN_004e1890();
    void *game = *(void **)((char *)this + 0x68);
    if (*(char *)((char *)game + 0x1f) && active)
        return 0x40;
    if (*(char *)((char *)this + 0x74))
        return 0x11;
    SBGeoPoint2D point(*(SBGeoPoint2D *)second);
    short x = (short)point.m_x;
    short y = (short)point.m_y;
    if (x < 0 || y < 0 || (int)x >= (int)*(unsigned short *)((char *)this + 0x3fb4) * 0x40 ||
        (int)y >= (int)*(unsigned short *)((char *)this + 0x3fb6) * 0x40)
        return 0x23;
    RHEngineSequenceList &sequences = *(RHEngineSequenceList *)((char *)this + 0x49f8);
    unsigned count = *(unsigned *)((char *)this + 0x4a00) & 0xffff;
    for (unsigned index = 0; index < count; ++index)
    {
        ((RHTitbitList *)&sequences)->At(index);
        void *actor = sequences.cursor->data;
        void *sprite = *(void **)((char *)actor + 0x50);
        void *order = *(void **)((char *)sprite + 0xe0);
        if (order && *(void **)((char *)order + 0x64) == first)
        {
            *(char *)((char *)this + 0x4718) = 0;
            return *(unsigned short *)((char *)order + 8);
        }
    }
    if (count == 0)
        return 0x11;
    return 0x11;
}

// Parked: 30.70%; register/branch residual on the dispatch body.
// STUB: GAME 0x004cc970
int RHEngine::FUN_004cc970(void *first, void *second, void *third)
{
    (void)second;
    char *result = (char *)first;
    char *object = (char *)third;
    *result = 0;
    if (!object)
        return *(char *)(*(char **)((char *)this + 0xcc) + 0xc) != 0 ? 0x10f : 0x10e;
    if (*(char *)(object + 0x8c))
    {
        if (!*(char *)(object + 0xb4))
        {
            int status = *(char *)(object + 0x8f) ? 0x60 : 0x61;
            typedef char (__cdecl *ModeCheck)();
            return ((ModeCheck)0x004e34f0)() ? status : 0x10f;
        }
        bool found = false;
        unsigned short count = *(unsigned short *)((char *)this + 0x4a00);
        for (unsigned short firstIndex = 0; firstIndex < count; ++firstIndex)
        {
            ((RHTitbitList *)((char *)this + 0x49f8))->At(firstIndex);
            void *actor = *(void **)((char *)((RHEngineSequenceList *)((char *)this + 0x49f8))->cursor->data + 0x50);
            typedef char (__cdecl *ActorCheck)(void *, int);
            if (*(void **)((char *)actor + 0xe0) == *(void **)(object + 0x10) && ((ActorCheck)0x0057deb0)(actor, 0))
                found = true;
        }
        for (unsigned short secondIndex = 0; secondIndex < count; ++secondIndex)
        {
            ((RHTitbitList *)((char *)this + 0x49f8))->At(secondIndex);
            void *actor = *(void **)((char *)((RHEngineSequenceList *)((char *)this + 0x49f8))->cursor->data + 0x50);
            typedef char (__cdecl *ActorCheck)(void *, int);
            if (*(void **)((char *)actor + 0xe0) == *(void **)(object + 0xc) && ((ActorCheck)0x0057deb0)(actor, 1))
                found = true;
        }
        return found ? 0x10e : 0x10f;
    }
    return 0x10e;
}

// Parked: command construction, route scoring, and the nested sequence-list passes are incomplete.
// STUB: GAME 0x004ccad0
void RHEngine::FUN_004ccad0(const SBGeoPoint2D &first, bool second)
{
    *(void **)((char *)this + 0x8c) = 0;
    char *entries = *(char **)((char *)this + 0x48fc);
    char *entriesEnd = *(char **)((char *)this + 0x4900);
    int count = entries ? (int)(entriesEnd - entries) / 4 : 0;
    unsigned sequenceCount = *(unsigned *)((char *)this + 0x4a00);
    if (sequenceCount == 1)
    {
        RHEngineSequenceList &sequences = *(RHEngineSequenceList *)((char *)this + 0x49f8);
        ((RHTitbitList *)&sequences)->At(0);
        void *actor = *(void **)((char *)sequences.cursor->data + 8);
        if (actor)
            *(void **)((char *)this + 0x8c) = actor;
    }
    if (sequenceCount == 0)
    {
        for (int index = count - 1; index >= 0; --index)
        {
            void *actor = *(void **)(entries + index * 4);
            if (!((RHEngineActorOrderCalls *)actor)->Matches((void *)&first, 0, 1))
                continue;
            *(void **)((char *)this + 0x8c) = actor;
            break;
        }
    }
    else if (!FUN_004e1890())
    {
        for (int index = count - 1; index >= 0; --index)
        {
            void *actor = *(void **)(entries + index * 4);
            if (second && ((*(unsigned *)((char *)actor + 4) & 7) == 4))
                continue;
            if (((RHEngineActorOrderCalls *)actor)->Matches((void *)&first, 1, 1))
            {
                *(void **)((char *)this + 0x8c) = actor;
                break;
            }
        }
    }
    if (sequenceCount && !*(void **)((char *)this + 0x8c))
        FUN_004cac00((void *)&first, (void *)second, 6, 1);
}

// Parked: remaining loop/exception instruction schedule is not yet aligned to the target.
// STUB: GAME 0x004cd400
void RHEngine::FUN_004cd400()
{
    RHEngineSequenceList &sequences = *(RHEngineSequenceList *)((char *)this + 0x49f8);
    unsigned count = *(unsigned *)((char *)this + 0x4a00);
    unsigned index = 0;
    while (index < count)
    {
        ((RHTitbitList *)&sequences)->At(index);
        int *actor = (int *)sequences.cursor->data;
        char *sprite = *(char **)((char *)actor + 0x50);
        unsigned mode = *(unsigned *)(sprite + 0x8c);
        if (mode == 1)
        {
            switch (actor[0x51])
            {
            case 4:
            case 5:
            case 6:
                break;
            case 0xc:
            case 0xe:
            {
                RHUnk00584d60 *action = new RHUnk00584d60(1, 0x6b, actor);
                ((RHScriptBatchCalls *)((char *)this + 0x43f8))->Unk0058a940("", 0, action);
                break;
            }
            default:
                ((RHElementActor *)actor)->FUN_0046bcb0(8);
                break;
            }
        }
        else if (mode == 0xb || mode == 0xe || mode == 0xf || mode == 0x10)
        {
            typedef char (__fastcall *ActorTest)(void *, void *);
            char active = (*(ActorTest *)(*(void ***)actor + 0x74 / 4))(actor, 0);
            if (active != 1 || ((*(unsigned *)(*(int *)(sprite + 0xe0) + 0x30) >> 13) & 1) != 0)
            {
                if (mode == 0xb)
                {
                    RHUnk00584d60 *action = new RHUnk00584d60(1, 0x66, actor);
                    ((RHScriptBatchCalls *)((char *)this + 0x43f8))->Unk0058a940("", 0, action);
                }
                else if (mode == 0x10)
                {
                    RHUnk00584d60 *action = new RHUnk00584d60(1, 0x60, actor);
                    ((RHScriptBatchCalls *)((char *)this + 0x43f8))->Unk0058a940("", 0, action);
                }
            }
        }
        else
            ((RHElementActor *)actor)->FUN_0046bcb0(8);
        ++index;
    }
}

// Parked: ~1.2 KB sequence-list serialization; not attempted in the probe budget.
// STUB: GAME 0x004cd600
void RHEngine::FUN_004cd600(const SBGeoPoint2D &a, bool b)
{
    (void)a;
    (void)b;
}

// Parked: build box then per-PC string/message dispatch; VC6 operand scheduling
// not reproduced in the probe budget.
// STUB: GAME 0x004cdab0
void RHEngine::FUN_004cdab0(void *a)
{
    (void)a;
}

// Parked: build box from two engine points, per-PC predicate/message loop; VC6
// operand scheduling not reproduced in the probe budget.
// STUB: GAME 0x004cdcc0
void RHEngine::FUN_004cdcc0()
{
}

// Parked: PC-vector scan with sequence-list insertion; VC6 operand scheduling
// not reproduced in the probe budget.
// STUB: GAME 0x004cde00
void RHEngine::FUN_004cde00()
{
}

// Parked: ~3.2 KB element/sequence serialization body; not attempted in the budget.
// STUB: GAME 0x004cdfc0
void RHEngine::FUN_004cdfc0()
{
}

// Parked: 55.21%; VC6 FPU operand-order/comparison-idiom scheduling plus a dead
// int store into the local point are not reproducible from any probed source shape.
// STUB: GAME 0x004cec60
bool RHEngine::FUN_004cec60()
{
    return true;
}

// Parked: ~2.1 KB element serialization body; not attempted in the budget.
// STUB: GAME 0x004cede0
void RHEngine::FUN_004cede0()
{
}

// Parked: ~1.7 KB bounding-box/FPU body; not attempted in the budget.
// STUB: GAME 0x004cf610
void RHEngine::FUN_004cf610()
{
}

// Parked: ~1.8 KB FPU/geometry body; not attempted in the budget.
// STUB: GAME 0x004cfce0
void RHEngine::FUN_004cfce0()
{
}

// Parked: ~1.5 KB body; not attempted in the budget.
// STUB: GAME 0x004d0400
void RHEngine::FUN_004d0400()
{
}

// Parked: ~3.1 KB body; not attempted in the budget.
// STUB: GAME 0x004d0a10
void RHEngine::FUN_004d0a10(void *a)
{
    (void)a;
}

class RHDrawManager
{
public:
    static RHDrawManager *mpDrawManager;
};

// FUNCTION: GAME 0x004d1630
void *FUN_004d1630()
{
    return RHDrawManager::mpDrawManager;
}

#include "RHMobileUnk00607da0.h"

class RHUnk004d1640
{
public:
    void FUN_004d1640(unsigned first, SBGeoBoundingBox2D box, unsigned second);
    SBGeoBoundingBox2D m_box;
    unsigned m_14;
    unsigned m_18;
};

// FUNCTION: GAME 0x004d1640
void RHUnk004d1640::FUN_004d1640(unsigned first, SBGeoBoundingBox2D box, unsigned second)
{
    m_18 = first;
    ((RHMobileUnk00607da0 *)&m_box)->FUN_00607da0((const RHMobileUnk00607da0 &)box);
    m_14 = second;
}

// Parked: event dispatch and nested list ownership are only partially reconstructed.
class RHUnk004d17c0
{
public:
    SBGeoPoint2D FUN_004d17c0();
};

class RHSoundSource;
class SBThreadedInput
{
public:
    static bool SetCursor(unsigned short cursor, bool selfIncrement);
};

class RHKeyConfig
{
public:
    const short *GetKeys() const;
};

struct RHUnk004d16b0Node
{
    void *m_00;
    int m_04;
    unsigned short m_08;
    char m_0a[0x1a];
    char m_24;
    char m_25[3];
    int m_28;
    unsigned short m_2c;
    char m_2e[2];
    int m_30;
};

// STUB: GAME 0x004d16b0
unsigned short RHEngine::FUN_004d16b0(void *first, void *second, unsigned third)
{
    RHUnk004d16b0Node *node = (RHUnk004d16b0Node *)first;
    unsigned visited = 0;
    while (node)
    {
        unsigned type = (unsigned)node->m_04;
        ++visited;
        switch (type)
        {
        case 1:
            SBThreadedInput::SetCursor(node->m_08, true);
            break;
        case 4:
            if (node->m_24)
            {
                SBGeoPoint2D point = ((RHUnk004d17c0 *)node)->FUN_004d17c0();
                ((RHSound *)*(void **)((char *)this + 0x45e0))->FUN_005a8070(
                    node->m_2c, point, node->m_30);
            }
            else
            {
                ((RHSound *)*(void **)((char *)this + 0x45e0))->FUN_005a8880(
                    (RHSoundSource *)node->m_28);
                ((RHSound *)*(void **)((char *)this + 0x45e0))->FUN_005a87f0(
                    (RHSoundSource *)node->m_28);
            }
            break;
        case 5:
            if (!node->m_24)
                ((RHSound *)*(void **)((char *)this + 0x45e0))->FUN_005a88a0(
                    (void *)node->m_28);
            break;
        }
        node = (RHUnk004d16b0Node *)((RHKeyConfig *)node)->GetKeys();
    }
    return visited;
}

// FUNCTION: GAME 0x004d17c0
SBGeoPoint2D RHUnk004d17c0::FUN_004d17c0()
{
    return *(SBGeoPoint2D *)((char *)this + 0x34);
}

// FUNCTION: GAME 0x004d17e0
bool FUN_004d17e0(const void *first, const void *second)
{
    return *(const unsigned *)((const char *)first + 0xc) < *(const unsigned *)((const char *)second + 0xc);
}

// FUNCTION: GAME 0x004d1800
int FUN_004d1800(RHElementActor *first, RHElementActor *second)
{
    return first->FUN_00462a30(second);
}

// FUNCTION: GAME 0x004d1810
bool FUN_004d1810(const void *first, const void *second)
{
    float firstValue = *(const float *)((const char *)first + 0xf8);
    float secondValue = *(const float *)((const char *)second + 0xf8);
    return firstValue < secondValue;
}

// Parked: the in-place range sort still differs in vector-growth and comparator call shape.
// FUNCTION: GAME 0x004d1840
bool RHEngine::FUN_004d1840()
{
    void **first = *(void ***)((char *)this + 0x48dc);
    void **last = *(void ***)((char *)this + 0x48e0);
    std::sort(first, last, (bool (*)(void *, void *))FUN_004d17e0);
    return true;
}

struct RHMinimapSortElement;
bool FUN_00549ae0(const RHMinimapSortElement *a, const RHMinimapSortElement *b);

// FUNCTION: GAME 0x004d1aa0
bool RHEngine::FUN_004d1aa0()
{
    void **first = *(void ***)((char *)this + 0x48dc);
    void **last = *(void ***)((char *)this + 0x48e0);
    std::sort(first, last, (bool (*)(void *, void *))FUN_00549ae0);
    return true;
}

// Parked: the mixed-list migration and nested object cleanup remain incomplete.
// STUB: GAME 0x004d1d00
void RHEngine::FUN_004d1d00()
{
    *(char *)((char *)this + 0x490c) = 1;
    void **begin = *(void ***)((char *)this + 0x49dc);
    void **end = *(void ***)((char *)this + 0x49e0);
    for (void **it = begin; it && it != end; ++it)
    {
        void *entry = *it;
        if (entry && *((char *)entry + 0x12))
            *(char *)((char *)this + 0x48f8 + 0x14) = 1;
    }
}

// FUNCTION: GAME 0x004d1f50
void RHEngine::FUN_004d1f50()
{
    void **first = *(void ***)((char *)this + 0x499c);
    void **last = *(void ***)((char *)this + 0x49a0);
    std::sort(first, last, FUN_004d1810);
}

// FUNCTION: GAME 0x004d21b0
void RHEngine::FUN_004d21b0(bool enabled, bool queued)
{
    unsigned short action = *(unsigned short *)((char *)RHUnk00546050() + 0x26);
    unsigned count = *(unsigned *)((char *)this + 0x4a00);
    if ((unsigned short)count > 0)
    {
        RHEngineSequenceList &actors = *(RHEngineSequenceList *)((char *)this + 0x49f8);
        unsigned i = 0;
        count &= 0xffff;
        do
        {
            ((RHTitbitList *)&actors)->At(i);
            void *actor = actors.cursor->data;
            if (enabled)
            {
                if (!queued)
                    ((RHScriptBatchCalls *)actor)->Unk0046b9e0();
                else
                {
                    RHEngineSpritePoint position;
                    int id = ((RHScriptBatchCalls *)((char *)this + 0x4668))->Unk005c2ec0(
                        &position, 0, 3, actor, 5, (int)actor, 0, -1);
                    ((RHElementActorPC *)actor)->SetQuickActionSequence(1, action, id);
                }
            }
            else
            {
                if (!queued)
                    ((RHElementActor *)actor)->FUN_0046bab0();
                else
                {
                    RHEngineSpritePoint position;
                    int id = ((RHScriptBatchCalls *)((char *)this + 0x4668))->Unk005c2ec0(
                        &position, 0, 3, actor, 4, (int)actor, 0, -1);
                    ((RHElementActorPC *)actor)->SetQuickActionSequence(2, action, id);
                }
            }
            ++i;
            --count;
        } while (count != 0);
    }
    if (queued)
        RHUnk00546050()->RHUnk005460c0((RHUnk5490f0 &)RHUnk00549250(6, 0));
}

// TEMPLATE: GAME 0x00613e90 FOLDED
// ??0RHEngineSpritePoint@@QAE@XZ
RHEngineSpritePoint::RHEngineSpritePoint()
{
}

class RHEngineActionCalls
{
public:
    int FUN_004d2300(void *actor, unsigned index);
};

// FUNCTION: GAME 0x004d2300
int RHEngineActionCalls::FUN_004d2300(void *actor, unsigned index)
{
    unsigned short slot = (unsigned short)index;
    if (*(void **)((char *)actor + 0x514 + slot * 4) ||
        *(void **)((char *)actor + 0x52c + slot * 4))
        return true;
    return false;
}

// FUNCTION: GAME 0x004d2330
bool __stdcall FUN_004d2330(int type)
{
    if (type != 0x11)
        return false;
    return true;
}

#include "RHPathFinderCore.h"

// FUNCTION: GAME 0x004d23b0
bool RHEngine::TurnPathFinderOn()
{
    return (*(RHPathFinder **)((char *)this + 0x45b8))->TurnOn();
}

// FUNCTION: GAME 0x004d23c0
void RHEngine::TurnPathFinderOff()
{
    (*(RHPathFinder **)((char *)this + 0x45b8))->FUN_00554750();
}

// FUNCTION: GAME 0x004d2d10
RHpathRequest::~RHpathRequest()
{
}

// FUNCTION: GAME 0x004d2d60
void RHEngine::FUN_004d2d60(unsigned, const SBGeoBoundingBox2D &bounds, float scale,
    unsigned short layer, bool, bool second, bool third)
{
    if (second)
        (*(RHPathFinder **)((char *)this + 0x45b8))->FUN_005596d0(bounds, scale, layer);
    if (third)
        (*(RHPathFinder **)((char *)this + 0x45b8))->FUN_00559e00(bounds, scale, layer);
}

void EmitRHEngine004d2d60(RHEngine *engine, const SBGeoBoundingBox2D &bounds)
{
    engine->FUN_004d2d60(0, bounds, 1.0f, 0, false, true, true);
}

#include <list>

template<class T> class RHEngineDrawList
{
public:
    struct Node { Node *next; Node *previous; T value; };
    char allocator[4];
    Node *head;
    unsigned count;
    Node *cursor;
    bool dirty;
    void Add(const T &value)
    {
        Node *position = head;
        Node *previous = position->previous;
        Node *node = (Node *)operator new(sizeof(Node));
        node->next = position ? position : node;
        node->previous = previous ? previous : node;
        position->previous = node;
        node->previous->next = node;
        if (&node->value)
            new (&node->value) T(value);
        ++count;
        dirty = true;
    }
};

// FUNCTION: GAME 0x004d52d0
void RHEngine::FUN_004d52d0(void *first, void *second, unsigned third)
{
    unsigned count = *(unsigned short *)((char *)this + 0x3fb8);
    for (unsigned index = 0; index < count; ++index)
        FUN_004d3d00(first, second, third, index, 0x4000, 0xffff);
}

// FUNCTION: GAME 0x004d5320
void RHEngine::FUN_004d5320(const void *value)
{
    if (*(char *)((char *)this + 0x4b34))
    {
        struct Entry { unsigned words[7]; };
        Entry *entry = (Entry *)operator new(sizeof(Entry));
        *entry = *(const Entry *)value;
        ((RHEngineDrawList<void *> *)((char *)this + 0x4bec))->Add(entry);
        ((RHEngineDrawList<unsigned short> *)((char *)this + 0x4c10))->Add(0);
    }
}

class RHEngineSoundCalls
{
public:
    void FUN_005a5060(void *source, void *first, void *second, unsigned third, unsigned volume);
};

// FUNCTION: GAME 0x004d7800
void RHEngine::FUN_004d7800(void *first, void *second, unsigned third)
{
    FUN_004d3e90(first, second, third, 0, 2, 0xffff);
}

// FUNCTION: GAME 0x004d7820
void RHEngine::FUN_004d7820(void *first, void *second, unsigned third)
{
    FUN_004d3e90(first, second, third, 0, 4, 0xffff);
    void *pc = *(void **)((char *)this + 0xd4);
    if (pc)
    {
        RHEngineSoundCalls *sound = *(RHEngineSoundCalls **)(*(char **)((char *)pc + 0x50) + 0xec);
        if (sound)
            sound->FUN_005a5060(*(void **)((char *)this + 0xdc), first, second, third, 0xfa00);
    }
}

class RHUnk004d96d0
{
public:
    SBGeoVector2D FUN_004d96d0() const;
};

class RHUnk004d96a0
{
public:
    SBGeoVector2D FUN_004d96a0() const;
};

// FUNCTION: GAME 0x004d8fd0
void RHEngine::FUN_004d8fd0(RHPCDescription *description)
{
    RHElementActorPC *actor = GetPC(description);
    RHUnk00546050()->RHUnk005460c0(RHUnk00549250(18, actor));
    *(char *)((char *)actor + 0x4e8) = 0;
    RHUnk00546050()->RHUnk005460c0(RHUnk00549250(12, actor));
    ((RHEngineSerializationCalls *)this)->FUN_004d88e0(actor, 0, 1);
}

class RHEngineFollowDispatch
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

SBGeoVector2D operator*(float factor, const SBGeoVector2D &point);
SBGeoVector2D FUN_005fc580(const SBGeoVector2D &point, float factor);

// Parked: target caches 1 in BL and gives the vector-conversion temporary the lowest frame slot.
// STUB: GAME 0x004d90b0
void RHEngine::SelectFollowElement(RHElementActor *actor)
{
    SBGeoPoint2D offset;
    if (actor)
    {
        SBGeoBoundingBox2D view;
        SBGeoPoint2D &camera = *(SBGeoPoint2D *)((char *)this + 0x4738);
        float &zoom = *(float *)((char *)this + 0x475c);
        view.SetFirst(camera);
        view.SetSecond(camera.Unk005fc190(operator*(1.0f / zoom,
            SBGeoVector2D((const SBGeoVector2D &)((SBGeoPoint2D *)((char *)this + 0x4728))->Unk005fc190(SBGeoVector2D(0.0f, -80.0f))))));
        if (!((RHEngineFollowDispatch *)actor)->V48() && !*((char *)actor + 0x1ce))
        {
            *(RHElementActor **)((char *)this + 0xd8) = actor;
            SBGeoPoint2D &position = *(SBGeoPoint2D *)(*(char **)((char *)actor + 0x50) + 0x24);
            offset = FUN_005fc580(position.Unk005fc110(camera), zoom);
            if (!view.FUN_00608400(position))
                FUN_004c8120(actor);
            offset = FUN_005fc580(position.Unk005fc110(camera), zoom);
            *(SBGeoPoint2D *)((char *)this + 0x476c) = offset;
            *((char *)this + 0x4719) = true;
            *(short *)((char *)this + 0x477c) = 0;
        }
    }
    else
        *((char *)this + 0x4719) = false;
}

#include "RHSequenceTimedCalls.h"
extern bool g_unk0x006c068d;
class RHUnk6c1040;
extern RHUnk6c1040 *g_unk0x6c1040;

// FUNCTION: GAME 0x004d9330
void RHScriptBatchCalls::Unk004d9330(void *actor, bool flag)
{
    if (g_unk0x006c068d && actor)
    {
        RHUnk005861c0 *element = new RHUnk005861c0(1, 0x26, actor, 10000, 0);
        ((RHScriptBatchCalls *)g_unk0x6c1040)->Unk0058a940("", 0, element);
        return;
    }
    if (!actor && flag != true)
    {
        (*(RHMessenger **)((char *)this + 0x68))->RHUnk005460c0(RHUnk5490f0(27));
        return;
    }
    *(void **)((char *)this + 0xd4) = actor;
}

// FUNCTION: GAME 0x004d96a0
SBGeoVector2D RHUnk004d96a0::FUN_004d96a0() const
{
    return ((RHUnk004d96d0 *)((char *)*(void **)((char *)this + 0x50) + 4))->FUN_004d96d0();
}

// FUNCTION: GAME 0x004d96d0
SBGeoVector2D RHUnk004d96d0::FUN_004d96d0() const
{
    return ((SBGeoPoint2D *)((char *)this + 0x20))->Unk005fc110(*(SBGeoPoint2D *)((char *)this + 0x3c));
}

#include "RHConsole.h"

// GLOBAL: GAME 0x006c068d
bool g_unk0x006c068d = false;

// FUNCTION: GAME 0x004db7a0
bool RHConsoleEngine::FUN_004db7a0()
{
    g_unk0x006c068d = !g_unk0x006c068d;
    return g_unk0x006c068d;
}

#include "SBPictureTargaCore.h"
#include "RHGameActionCalls.h"

class RHEnginePictureSurfaceCalls
{
public:
    virtual void V00() = 0;
    virtual void V04() = 0;
    virtual void V08() = 0;
    virtual void V0c() = 0;
    virtual void V10() = 0;
    virtual void V14(void *surface, unsigned flags) = 0;
};

// FUNCTION: GAME 0x004da2f0
bool RHGameActionCalls::FUN_004da2f0()
{
    SBPictureTarga picture;
    RHEnginePictureSurfaceCalls *destination = (RHEnginePictureSurfaceCalls *)((char *)this + 0xe4);
    destination->V14(*(void **)((char *)this + 0xdc), 0);
    ((SBPicture *)destination)->FUN_00612300(SBGeoVector2D(160.0f, 120.0f), 1);
    return true;
}

// FUNCTION: GAME 0x004db7b0
int RHEngine::FUN_004db7b0(void *actor)
{
    void *state = *(void **)((char *)actor + 0x50);
    return *(int *)((char *)state + 0x8c) == 5 || *(int *)((char *)state + 0x8c) == 4
        || ((unsigned char)(*(unsigned int *)((char *)*(void **)((char *)state + 0xe0) + 0x30) >> 13) & 1) != 0;
}

// FUNCTION: GAME 0x004db7f0
void RHEngine::FUN_004db7f0(SBGeoPoint2D &point)
{
    *(float *)((char *)this + 0x4738) = (float)floor(point.m_x);
    float y = (float)floor(point.m_y);
    *(float *)((char *)this + 0x473c) = y;
    if (*(unsigned int *)((char *)this + 0x475c) == 0x3f000000)
    {
        if ((int)*(float *)((char *)this + 0x4738) & 1)
            *(float *)((char *)this + 0x4738) -= 1.0f;
        if ((int)y & 1)
            *(float *)((char *)this + 0x473c) = y - 1.0f;
    }
}

// FUNCTION: GAME 0x004db880
void RHEngine::FUN_004db880()
{
    std::vector<RHEngineActorUpdateCalls *> &actors = *(std::vector<RHEngineActorUpdateCalls *> *)((char *)this + 0x4978);
    unsigned int count = actors.size();
    for (unsigned int index = 0; index < count; ++index)
        actors[index]->FUN_004af2a0();
}

// FUNCTION: GAME 0x004db8c0
void RHEngine::FUN_004db8c0(unsigned char value)
{
    unsigned char &current = *(unsigned char *)((char *)this + 0x48c0);
    if (value > current)
        current = value;
}

// FUNCTION: GAME 0x004db8e0
bool RHEngine::FUN_004db8e0(unsigned short index)
{
    RHUnk00546050();
    if (*(float *)((char *)this + 0x4748) == g_unk0x006785d8
        && !*((unsigned char *)this + 0x6d + index))
        return true;
    return false;
}

// FUNCTION: GAME 0x004db920
void RHEngine::FUN_004db920(const void *)
{
    RHMessenger *messenger;
    if (*(bool *)((char *)this + 0x4b3b)
        && !*((unsigned char *)(messenger = RHUnk00546050()) + 0x15)
        && !*((unsigned char *)messenger + 0x19))
    {
        if (*((unsigned char *)RHUnk00546050() + 0x14))
        {
            if (*(float *)((char *)this + 0x4bd8) > 1.0f)
                *(float *)((char *)this + 0x4bd8) -= 1.0f;
        }
        else
        {
            float position = *(float *)((char *)this + 0x4bd4);
            *(float *)((char *)this + 0x4bd4) = position + 1.0f;
        }
        return;
    }
    if (FUN_004db8e0(3))
    {
        *(bool *)((char *)this + 0x471a) = false;
        if (*(unsigned char *)((char *)this + 0x4781) == 1)
        {
            *(unsigned short *)((char *)this + 0x4784) = 0;
            *(unsigned char *)((char *)this + 0x4781) = 0;
        }
        else if (*(unsigned short *)((char *)this + 0x4784) < 31)
            ++*(unsigned short *)((char *)this + 0x4784);
        float speed = ((float *)((char *)this + 0x4818))[*(unsigned short *)((char *)this + 0x4784)]
            / *(float *)((char *)this + 0x475c);
        *(volatile float *)((char *)this + 0x48bc) = speed;
        *(volatile bool *)((char *)this + 0x70) = true;
        int distance = (int)*(float *)((char *)this + 0x48bc);
        float maximum = *(float *)((char *)this + 0x472c);
        distance = abs(distance);
        if (distance > (unsigned short)(maximum * *(float *)((char *)this + 0x475c)))
        {
            FUN_004db8c0(5);
            *(unsigned short *)((char *)this + 0x4782) = 0;
            *(unsigned short *)((char *)this + 0x4784) = 0;
        }
        else
            FUN_004db8c0(2);
    }
}

#include "SBGeoVectorRotation.h"

// FUNCTION: GAME 0x004dba50
void RHEngine::FUN_004dba50(const void *)
{
    RHMessenger *messenger;
    if (*(bool *)((char *)this + 0x4b3b)
        && !*((unsigned char *)(messenger = RHUnk00546050()) + 0x15)
        && !*((unsigned char *)messenger + 0x19))
    {
        if (*((unsigned char *)RHUnk00546050() + 0x14))
            ((RHEngineCameraRotationCalls *)((char *)this + 0x4b88))->FUN_005fc9a0(-0.01f, 1.0f);
        else
            *(float *)((char *)this + 0x4bd0) -= 1.0f;
        return;
    }
    if (FUN_004db8e0(1))
    {
        *(bool *)((char *)this + 0x471a) = false;
        if (*(unsigned char *)((char *)this + 0x4780) == 0)
        {
            *(unsigned short *)((char *)this + 0x4782) = 0;
            *(unsigned char *)((char *)this + 0x4780) = 1;
        }
        else if (*(unsigned short *)((char *)this + 0x4782) < 31)
            ++*(unsigned short *)((char *)this + 0x4782);
        *(float *)((char *)this + 0x48b8) = -(((float *)((char *)this + 0x4798))[*(unsigned short *)((char *)this + 0x4782)]
            / *(float *)((char *)this + 0x475c));
        *(bool *)((char *)this + 0x6e) = true;
        int distance = (int)*(float *)((char *)this + 0x48b8);
        float maximum = *(float *)((char *)this + 0x4728);
        distance = abs(distance);
        if (distance > (unsigned short)(maximum * *(float *)((char *)this + 0x475c)))
        {
            FUN_004db8c0(5);
            *(unsigned short *)((char *)this + 0x4782) = 0;
            *(unsigned short *)((char *)this + 0x4784) = 0;
        }
        else
            FUN_004db8c0(2);
    }
}

// FUNCTION: GAME 0x004dbb70
void RHEngine::FUN_004dbb70(const void *)
{
    RHMessenger *messenger;
    if (*(bool *)((char *)this + 0x4b3b)
        && !*((unsigned char *)(messenger = RHUnk00546050()) + 0x15)
        && !*((unsigned char *)messenger + 0x19))
    {
        if (*((unsigned char *)RHUnk00546050() + 0x14))
            ((RHEngineCameraRotationCalls *)((char *)this + 0x4b88))->FUN_005fc9a0(0.01f, 1.0f);
        else
        {
            float position = *(float *)((char *)this + 0x4bd0);
            *(float *)((char *)this + 0x4bd0) = position + 1.0f;
        }
        return;
    }
    if (FUN_004db8e0(2))
    {
        *(bool *)((char *)this + 0x471a) = false;
        if (*(unsigned char *)((char *)this + 0x4780) == 1)
        {
            *(unsigned short *)((char *)this + 0x4782) = 0;
            *(unsigned char *)((char *)this + 0x4780) = 0;
        }
        else if (*(unsigned short *)((char *)this + 0x4782) < 31)
            ++*(unsigned short *)((char *)this + 0x4782);
        *(float *)((char *)this + 0x48b8) = ((float *)((char *)this + 0x4798))[*(unsigned short *)((char *)this + 0x4782)]
            / *(float *)((char *)this + 0x475c);
        *(bool *)((char *)this + 0x6f) = true;
        int distance = (int)*(float *)((char *)this + 0x48b8);
        float maximum = *(float *)((char *)this + 0x4728);
        distance = abs(distance);
        if (distance > (unsigned short)(maximum * *(float *)((char *)this + 0x475c)))
        {
            FUN_004db8c0(5);
            *(unsigned short *)((char *)this + 0x4782) = 0;
            *(unsigned short *)((char *)this + 0x4784) = 0;
        }
        else
            FUN_004db8c0(2);
    }
}

// FUNCTION: GAME 0x004dbc90
void RHEngine::FUN_004dbc90(const void *)
{
    RHMessenger *messenger;
    if (*(bool *)((char *)this + 0x4b3b)
        && !*((unsigned char *)(messenger = RHUnk00546050()) + 0x15)
        && !*((unsigned char *)messenger + 0x19))
    {
        if (*((unsigned char *)RHUnk00546050() + 0x14))
        {
            float position = *(float *)((char *)this + 0x4bd8);
            *(float *)((char *)this + 0x4bd8) = position + 1.0f;
        }
        else
            *(float *)((char *)this + 0x4bd4) -= 1.0f;
        return;
    }
    if (FUN_004db8e0(0))
    {
        *(bool *)((char *)this + 0x471a) = false;
        if (*(unsigned char *)((char *)this + 0x4781) == 0)
        {
            *(unsigned short *)((char *)this + 0x4784) = 0;
            *(unsigned char *)((char *)this + 0x4781) = 1;
        }
        else if (*(unsigned short *)((char *)this + 0x4784) < 31)
            ++*(unsigned short *)((char *)this + 0x4784);
        *(volatile float *)((char *)this + 0x48bc) = -(((float *)((char *)this + 0x4818))[*(unsigned short *)((char *)this + 0x4784)]
            / *(float *)((char *)this + 0x475c));
        *(volatile bool *)((char *)this + 0x6d) = true;
        int distance = (int)*(float *)((char *)this + 0x48bc);
        float maximum = *(float *)((char *)this + 0x472c);
        distance = abs(distance);
        if (distance > (unsigned short)(maximum * *(float *)((char *)this + 0x475c)))
        {
            FUN_004db8c0(5);
            *(unsigned short *)((char *)this + 0x4782) = 0;
            *(unsigned short *)((char *)this + 0x4784) = 0;
        }
        else
            FUN_004db8c0(2);
    }
}

// FUNCTION: GAME 0x004dbdb0
void RHEngine::FUN_004dbdb0(const void *event)
{
    if (FUN_004c7cf0() && FUN_004c7c90())
    {
        *(bool *)((char *)this + 0x4793) = false;
        *(bool *)((char *)this + 0x4769) = *(const unsigned int *)((const char *)event + 8) > 0;
        if (*(unsigned short *)((char *)this + 0x4782) != 0
            || *(unsigned short *)((char *)this + 0x4784) != 0
            || *(unsigned char *)((char *)this + 0x48c0) == 3
            || *(unsigned char *)((char *)this + 0x48c0) == 4)
        {
            *(bool *)((char *)this + 0x4792) = false;
            *(bool *)((char *)this + 0x4793) = true;
        }
        else if (*(unsigned short *)((char *)this + 0x4898) > 0)
        {
            --*(unsigned short *)((char *)this + 0x4898);
            *(bool *)((char *)this + 0x4791) = true;
            FUN_004db8c0(3);
        }
    }
}

// FUNCTION: GAME 0x004dbe40
void RHEngine::FUN_004dbe40(const void *event)
{
    if (FUN_004c7cd0() && FUN_004c7c90())
    {
        *(bool *)((char *)this + 0x4792) = false;
        *(bool *)((char *)this + 0x4769) = *(const unsigned int *)((const char *)event + 8) > 0;
        if (*(unsigned short *)((char *)this + 0x4782) != 0
            || *(unsigned short *)((char *)this + 0x4784) != 0
            || *(unsigned char *)((char *)this + 0x48c0) == 3
            || *(unsigned char *)((char *)this + 0x48c0) == 4)
        {
            *(bool *)((char *)this + 0x4792) = true;
            *(bool *)((char *)this + 0x4793) = false;
        }
        else if (*(unsigned short *)((char *)this + 0x4898) < 2)
        {
            ++*(unsigned short *)((char *)this + 0x4898);
            *(bool *)((char *)this + 0x4790) = true;
            FUN_004db8c0(3);
        }
    }
}

// FUNCTION: GAME 0x004dbed0
void RHEngine::FUN_004dbed0(const void *event)
{
    unsigned int value = *(const unsigned int *)((const char *)event + 8);
    std::vector<RHEngineActorActionCalls *> &actors = *(std::vector<RHEngineActorActionCalls *> *)((char *)this + 0x4938);
    unsigned int count = actors.size();
    for (unsigned int index = 0; index < count; ++index)
        actors[index]->FUN_00490910(value);
}

inline void RHEngineSequenceList::Clear()
{
    RHScriptNode *last = head;
    RHScriptIter position(head->next);
    while (position.node != last)
    {
        RHScriptIter erased = position;
        position.node = position.node->next;
        ((RHUnk0046eb30 *)this)->erase(erased);
    }
    dirty = true;
}

// Parked: branch-local register saves and cached-search load scheduling differ.
// STUB: GAME 0x004dc190
bool RHEngine::FUN_004dc190(void *actor)
{
    if (!actor)
    {
        RHEngineSequenceList &actors = *(RHEngineSequenceList *)((char *)this + 0x49f8);
        actors.Clear();
        return true;
    }
    RHEngineSequenceList &actors = *(RHEngineSequenceList *)((char *)this + 0x49f8);
    int count = actors.count;
    *(void **)((char *)&actors + 0x20) = actor;
    *((bool *)&actors + 0x18) = true;
    actors.cursor = actors.head->next;
    int index;
    for (index = 0; index < count; ++index, actors.cursor = actors.cursor->next)
    {
        RHScriptNode *node = *(RHScriptNode *volatile *)&actors.cursor;
        void *value = *(void *volatile *)((char *)&actors + 0x20);
        if (node->data == value)
            break;
    }
    if (index < count)
    {
        *(int *)((char *)&actors + 0x1c) = index;
        actors.dirty = false;
        actors.index = index;
    }
    else
    {
        actors.dirty = true;
        *(int *)((char *)&actors + 0x1c) = -1;
    }
    ((RHTitbitList *)&actors)->At(*(int *)((char *)&actors + 0x1c));
    RHScriptNode *removed = actors.cursor;
    removed->prev->next = removed->next;
    removed->next->prev = removed->prev;
    ::operator delete(removed);
    int remaining = actors.count - 1;
    actors.dirty = true;
    actors.count = remaining;
    return true;
}

// FUNCTION: GAME 0x004dc260
void RHEngine::FUN_004dc260(const void *)
{
    *(bool *)((char *)this + 0x6c) = false;
    (*(RHMessenger **)((char *)this + 0x68))->RHUnk005460c0(RHUnk00549250(42, 0));
}

// FUNCTION: GAME 0x004dce20
void RHEngine::FUN_004dce20(void *actor)
{
    if (!*(void **)((char *)actor + 0x268))
    {
        RHUnk00584d60 *action;
        switch (*(int *)((char *)actor + 0x500))
        {
        case 1:
            if (*(int *)((char *)actor + 0x144) != 4 && *(int *)((char *)actor + 0x144) != 5)
                break;
            ((RHUnk0046bcb0 *)actor)->Unk(7);
            action = new RHUnk00584d60(1, 0x20, actor);
            ((RHScriptBatchCalls *)((char *)this + 0x43f8))->Unk0058a940("", 0, action);
            break;
        case 10:
        {
            int posture = *(int *)(*(char **)((char *)actor + 0x50) + 0x8c);
            if (posture != 0xe && posture != 0xf)
                break;
            action = new RHUnk00584d60(1, 0x5e, actor);
            ((RHScriptBatchCalls *)((char *)this + 0x43f8))->Unk0058a940("", 0, action);
            break;
        }
        case 18:
            if (*(int *)(*(char **)((char *)actor + 0x50) + 0x8c) != 0x14)
                break;
            action = new RHUnk00584d60(1, 0x62, actor);
            ((RHScriptBatchCalls *)((char *)this + 0x43f8))->Unk0058a940("", 0, action);
            break;
        case 15:
            if (*(int *)((char *)actor + 0x144) != 0x11)
                break;
            action = new RHUnk00584d60(1, 0x64, actor);
            ((RHScriptBatchCalls *)((char *)this + 0x43f8))->Unk0058a940("", 0, action);
            break;
        }
    }
    *(bool *)((char *)this + 0x471a) = false;
    ((RHElementActorPC *)actor)->FUN_0049d680(0);
}

// Parked: flag argument widths, cached selection loads and point-store scheduling differ.
// STUB: GAME 0x004ddfb0
void RHEngine::FUN_004ddfb0()
{
    if (!*(bool *)((char *)this + 0x88))
    {
        bool flag = *(bool *)((char *)RHUnk00546050() + 0x20);
        SBGeoPoint2D point;
        FUN_004dee70((float *)&point);
        char *messenger = *(char **)((char *)this + 0x68);
        switch (*(unsigned short *)(messenger + 0xa2))
        {
        case 10:
        {
            void *actor = (*(RHScriptNode **)((char *)this + 0x49fc))->next->data;
            if (*(int *)(*(char **)((char *)actor + 0x50) + 0x8c) != 0xe)
                break;
        }
        case 0:
            if (!messenger[0x15] && !messenger[0x19] && !messenger[0x1a])
            {
                if (!*(bool *)((char *)this + 0x72) && !FUN_004e1890())
                {
                    *(bool *)((char *)this + 0x72) = true;
                    *(SBGeoPoint2D *)((char *)this + 0x78) = point;
                }
                *(SBGeoPoint2D *)((char *)this + 0x80) = point;
            }
            break;
        case 11: FUN_004df7b0(point, flag); break;
        case 5: FUN_004dfb50(point, flag); break;
        case 2: case 3: FUN_004e0550(point, (void *)(unsigned char)flag, 0); break;
        case 16: FUN_004df550(point, (void *)(unsigned char)flag, 0, 0); break;
        case 9: FUN_004e0770(point, (void *)(unsigned char)flag, 0); break;
        case 8: FUN_004df330(point, (void *)(unsigned char)flag, 0); break;
        }
    }
}

// FUNCTION: GAME 0x004de170
void RHEngine::FUN_004de170(bool first, bool second, bool third)
{
    if (first)
    {
        *(bool *)((char *)this + 0x89) = true;
        *((bool *)*(void **)((char *)this + 0x68) + 0xaa) = true;
    }
    if (second)
        *(bool *)((char *)this + 0x88) = true;
    *(bool *)((char *)this + 0x8a) = third;
    if (first || third)
    {
        char *messenger = *(char **)((char *)this + 0x68);
        *(unsigned short *)(messenger + 0xa4) = *(unsigned short *)(messenger + 0xa2);
        messenger[0x21] = messenger[0x20];
        *(SBGeoPoint2D *)(messenger + 0x94) = *(SBGeoPoint2D *)(messenger + 0x84);
    }
}

// FUNCTION: GAME 0x004de1e0
void RHEngine::FUN_004de1e0()
{
    RHUnk00546050();
    SBGeoPoint2D point;
    FUN_004dee70((float *)&point);
    char *messenger = *(char **)((char *)this + 0x68);
    if (*(unsigned short *)(messenger + 0xa2) == 0 && !messenger[0x15]
        && !messenger[0x19] && !messenger[0x1a])
    {
        if (!*(bool *)((char *)this + 0x73))
        {
            *(bool *)((char *)this + 0x73) = true;
            *(SBGeoPoint2D *)((char *)this + 0x78) = point;
        }
        *(SBGeoPoint2D *)((char *)this + 0x80) = point;
    }
}

// FUNCTION: GAME 0x004debe0
void RHEngine::FUN_004debe0()
{
    *(bool *)((char *)this + 0x6c) = true;
    ((RHTitbits *)((char *)this + 0x4668))->ResetBlinking();
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

#include "RHPCActionQueryCalls.h"

// Parked: boolean-local spilling and loop-register allocation still differ after two shapes.
// STUB: GAME 0x004ded90
unsigned char RHEngine::FUN_004ded90(void *actor)
{
    if (!actor)
    {
        unsigned count = *(unsigned *)((char *)this + 0x4a00);
        bool first = false;
        bool second = false;
        RHSeqList *actors = (RHSeqList *)((char *)this + 0x49f8);
        for (unsigned i = 0; i < count; ++i)
        {
            actors->GoTo(i);
            actor = actors->cursor->data;
            if (!FUN_004db7b0(actor))
            {
                switch (*(int *)((char *)*(void **)((char *)actor + 0x50) + 0x8c))
                {
                case 3:
                case 10:
                    second = true;
                    break;
                case 5:
                    break;
                default:
                    first = true;
                }
            }
        }
        if (first)
            return second ? 3 : 1;
        if (second)
            return 2;
        return 0;
    }
    if (!FUN_004db7b0(actor))
        return 0;
    int type = *(int *)((char *)*(void **)((char *)actor + 0x50) + 0x8c);
    return type == 3 || type == 10 ? 2 : 1;
}

// FUNCTION: GAME 0x004dee70
void RHEngine::FUN_004dee70(float *point)
{
    float scale = 1.0f / *(float *)((char *)this + 0x475c);
    float *offset = (float *)((char *)*(void **)((char *)this + 0x68) + 0x84);
    float y = offset[1] * scale + *(float *)((char *)this + 0x473c);
    point[0] = offset[0] * scale + *(float *)((char *)this + 0x4738);
    point[1] = y;
}

// FUNCTION: GAME 0x004deeb0
int RHEngine::FUN_004deeb0(const SBGeoPoint2D &point, SBGeoPoint2D &result)
{
    result = point;
    {
        SBGeoVector2D origin(*(SBGeoVector2D *)((char *)this + 0x4738));
        result.FUN_005fc250(origin);
    }
    float y = result.m_y * *(float *)((char *)this + 0x475c);
    double x = result.m_x;
    result.m_x = x * *(float *)((char *)this + 0x475c);
    result.m_y = y;
    if (result.m_x >= 0.0f && result.m_x <= (double)*(float *)((char *)this + 0x4728) &&
        result.m_y >= 0.0f && result.m_y <= (double)*(float *)((char *)this + 0x472c))
        return 1;
    return 0;
}

// FUNCTION: GAME 0x004defa0
void RHEngine::FUN_004defa0(char flag)
{
    if (flag)
        return;
    RHSeqList *sequences = (RHSeqList *)((char *)this + 0x49f8);
    sequences->GoTo(0);
    void *sequence = sequences->cursor->data;
    unsigned type = *(unsigned *)((char *)sequence + 0x144);
    if (type == 4 || type == 5 || type == 6)
        return;
    ((RHUnk0046bcb0 *)sequence)->Unk(7);
    RHUnk00584d60 *action = new RHUnk00584d60(1, 0x1d, sequence);
    ((RHScriptBatchCalls *)((char *)this + 0x43f8))->Unk0058a940(
        "", 0, action);
    ((RHEngineSequenceDispatchCalls *)sequence)->Dispatch(12, 0, 0xff);
}

// Parked: 50.86%; sequence/action register scheduling and mode-specific cleanup differ after three loop shapes.
// STUB: GAME 0x004df070
void RHEngine::FUN_004df070(void *value, char flag)
{
    unsigned count = *(unsigned *)((char *)this + 0x4a00);
    if (!count)
        return;
    RHSeqList *sequences = (RHSeqList *)((char *)this + 0x49f8);
    sequences->GoTo(0);
    void *sequence = sequences->cursor->data;
    if (!flag)
    {
        void *sprite = *(void **)((char *)sequence + 0x50);
        void *state = *(void **)((char *)sprite + 0xe0);
        unsigned flags = *(unsigned *)((char *)state + 0x30);
        if ((flags & 0x2000) || ((flags & 0x200) && *(int *)((char *)state + 0xf0) != 1))
            return;
    }
    void **first = *(void ***)((char *)this + 0x48fc);
    void **last = *(void ***)((char *)this + 0x4900);
    void *selected = 0;
    for (void **cursor = last; first && cursor != first;)
    {
        void *candidate = *--cursor;
        if (((RHSequenceFilterCalls *)candidate)->Filter(value, sequence, 4))
        {
            selected = candidate;
            break;
        }
    }
    if (!selected)
        return;
    unsigned type = *(unsigned *)((char *)selected + 4);
    if (!flag)
    {
        if ((type & 0xf) == 4 && ((RHEngineSequenceDispatchCalls *)selected)->Test())
            return;
        if ((type & 0x1f) == 4)
            return;
        void *sprite = *(void **)((char *)sequence + 0x50);
        if (*(unsigned *)((char *)sprite + 0x8c) == 0x17)
        {
            ((RHEngineSequenceDispatchCalls *)sequence)->Dispatch(14, 0, 0xff);
            return;
        }
        int position[3];
        if (((RHElementActorHuman *)sequence)->FUN_0047b760(selected, position))
            return;
        RHUnk00585ea0 *action = new RHUnk00585ea0(1, 0x23, sequence, selected);
        ((RHScriptBatchCalls *)((char *)this + 0x43f8))->Unk0058a940(
            "", 0, action);
        return;
    }
    if (!*(char *)((char *)selected + 8) && (type & 0xf) == 4 &&
        ((RHEngineSequenceDispatchCalls *)selected)->Test())
        return;
    if (!*(char *)((char *)selected + 8) && (type & 0x1f) == 4)
        return;
    RHUnk00582220 *node = new RHUnk00582220;
    RHUnk00585ea0 *action = new RHUnk00585ea0(1, 0x23, sequence, selected);
    ((RHUnk00585500 *)action)->Unk(node);
    ((RHScriptBatchCalls *)((char *)this + 0x4668))->Unk005c2ec0(
        0, 0, 3, selected, 0xe, (int)sequence, 0, -1);
    unsigned short layer = *(unsigned short *)((char *)*(void **)((char *)this + 0x68) + 0x26);
    ((RHEngineSequenceDispatchCalls *)sequence)->Apply(node, 0, layer, selected);
    RHUnk00549250 message(6, sequence);
    RHUnk00546050()->RHUnk005460c0(message);
}

// Residual: target's constructor/EH frame and direct 0x004a0020 callback are not reproduced.
// STUB: GAME 0x004df330
void RHEngine::FUN_004df330(const SBGeoPoint2D &point, void *actor, int index)
{
    void *target = FUN_004e04c0(0xf, point, index, actor);
    if (!target)
        return;
    RHEngineSequenceList &sequences = *(RHEngineSequenceList *)((char *)this + 0x49f8);
    void *element = sequences.Get(index, false, true);
    if (!element)
        return;
    void *sequenceActor = element;
    RHUnk00585ea0 *action = new RHUnk00585ea0(1, 0x73, sequenceActor, target);
    char *sprite = *(char **)((char *)sequenceActor + 0x50);
    SBGeoVector2D vector(*(SBGeoPoint2D *)(sprite + 0x1c));
    short frame = *(short *)(sprite + 0xd8);
    RHUnk005b5e00 *spriteCalls = (RHUnk005b5e00 *)sprite;
    void *holder = spriteCalls->Unk();
    short offset = *(short *)(*(char **)((char *)holder + 4) + 0x1e8);
    SBGeoPoint2D *framePoint = spriteCalls->Unk005bdd30(offset + frame);
    float distance = ((RHUnk005fc3b0 *)&framePoint->Unk005fc190(vector).Unk005fc110(
        *(SBGeoPoint2D *)(sprite + 0x24)))->Unk005fc6a0(1.0f);
    (void)action;
    (void)distance;
}

// Residual: the target's supplied-object branch and direct 0x004a0020 callback remain unmatched.
// STUB: GAME 0x004df550
void RHEngine::FUN_004df550(const SBGeoPoint2D &point, void *actor, int flag, void *provided)
{
    void *target = provided;
    if (!target)
        target = FUN_004e04c0(0xa, point, flag, actor);
    if (!target)
        return;
    RHEngineSequenceList &sequences = *(RHEngineSequenceList *)((char *)this + 0x49f8);
    void *element = sequences.Get(flag, false, true);
    if (!element)
        return;
    RHUnk00585ea0 *action = new RHUnk00585ea0(1, 0x57, element, target);
    char *sprite = *(char **)((char *)element + 0x50);
    SBGeoVector2D vector(*(SBGeoPoint2D *)(sprite + 0x1c));
    short frame = *(short *)(sprite + 0xd8);
    RHUnk005b5e00 *spriteCalls = (RHUnk005b5e00 *)sprite;
    void *holder = spriteCalls->Unk();
    short offset = *(short *)(*(char **)((char *)holder + 4) + 0x1b2);
    SBGeoPoint2D *framePoint = spriteCalls->Unk005bdd30(offset + frame);
    float distance = ((RHUnk005fc3b0 *)&framePoint->Unk005fc190(vector).Unk005fc110(
        *(SBGeoPoint2D *)(sprite + 0x24)))->Unk005fc6a0(1.0f);
    (void)distance;
}

static inline void *RHEnginePositionAddress(const RHEngineSpritePoint &position);

// FUNCTION: GAME 0x004df7b0
void RHEngine::FUN_004df7b0(const SBGeoPoint2D &point, bool flag)
{
    if (!*(char *)((char *)this + 0x471a) && !flag)
        return;
    void *target = FUN_004e04c0(7, point, false, flag);
    if (!target)
        return;
    RHSeqList *sequences = (RHSeqList *)((char *)this + 0x49f8);
    sequences->GoTo(0);
    void *element = sequences->cursor->data;
    if (!flag)
    {
        RHUnk00585ea0 *action = new RHUnk00585ea0(1, 0x58, element, target);
        ((RHScriptBatchCalls *)((char *)this + 0x43f8))->Unk0058a940(
            "", 0, action);
        return;
    }
    RHUnk00582220 *node = new RHUnk00582220;
    RHUnk00585ea0 *action = new RHUnk00585ea0(1, 0x58, element, target);
    ((RHUnk00585500 *)action)->Unk(node);
    const RHEngineSpritePoint &position = RHEngineSpritePoint();
    int effect = ((RHScriptBatchCalls *)((char *)this + 0x4668))->Unk005c2ec0(
        RHEnginePositionAddress(position), 0, 3, target, 0x25, (int)element, 0, -1);
    unsigned short layer = *(unsigned short *)((char *)*(void **)((char *)this + 0x68) + 0x26);
    ((RHEngineSequenceDispatchCalls *)element)->Apply(node, 0, layer, (void *)effect);
    RHUnk00546050()->RHUnk005460c0((RHUnk5490f0 &)RHUnk00549250(6, element));
}

// FUNCTION: GAME 0x004dfb50
void RHEngine::FUN_004dfb50(const SBGeoPoint2D &point, bool flag)
{
    if (!*(char *)((char *)this + 0x471a) && !flag)
        return;
    void *target = FUN_004e04c0(8, point, false, flag);
    if (!target)
        return;
    RHSeqList *sequences = (RHSeqList *)((char *)this + 0x49f8);
    sequences->GoTo(0);
    void *element = sequences->cursor->data;
    if (!flag)
    {
        RHUnk00585ea0 *action = new RHUnk00585ea0(1, 0x59, element, target);
        ((RHScriptBatchCalls *)((char *)this + 0x43f8))->Unk0058a940(
            "", 0, action);
        return;
    }
    RHUnk00582220 *node = new RHUnk00582220;
    RHUnk00585ea0 *action = new RHUnk00585ea0(1, 0x59, element, target);
    ((RHUnk00585500 *)action)->Unk(node);
    const RHEngineSpritePoint &position = RHEngineSpritePoint();
    int effect = ((RHScriptBatchCalls *)((char *)this + 0x4668))->Unk005c2ec0(
        RHEnginePositionAddress(position), 0, 3, target, 0xa, (int)element, 0, -1);
    unsigned short layer = *(unsigned short *)((char *)*(void **)((char *)this + 0x68) + 0x26);
    ((RHEngineSequenceDispatchCalls *)element)->Apply(node, 0, layer, (void *)effect);
    RHUnk00546050()->RHUnk005460c0((RHUnk5490f0 &)RHUnk00549250(6, element));
}

// Residual: the target resolver at 0x004fbd30 is outside the assigned range.
// STUB: GAME 0x004dfcf0
void RHEngine::FUN_004dfcf0(char flag)
{
    if (!*(char *)((char *)this + 0x471a) && !flag)
        return;
    RHUnk00613e90 first;
    RHUnk00613e90 second;
    RHSeqList *sequences = (RHSeqList *)((char *)this + 0x49f8);
    sequences->GoTo(0);
    void *element = sequences->cursor->data;
    RHUnk00585ea0 *action = new RHUnk00585ea0(1, 0x5b, element, 0);
    if (!flag)
    {
        ((RHScriptBatchCalls *)((char *)this + 0x43f8))->Unk0058a940(
            "", 0, action);
        return;
    }
    RHUnk00582220 *node = new RHUnk00582220;
    ((RHUnk00585500 *)action)->Unk(node);
    ((RHScriptBatchCalls *)((char *)this + 0x4668))->Unk005c2ec0(
        &first, *(unsigned short *)((char *)this + 0xc4), 3, element,
        0x1d, 0, 0, -1);
    unsigned short layer = *(unsigned short *)((char *)*(void **)((char *)this + 0x68) + 0x26);
    ((RHEngineSequenceDispatchCalls *)element)->Apply(node, 0, layer, element);
    RHUnk00549250 message(6, element);
    RHUnk00546050()->RHUnk005460c0(message);
}

// Residual: target's resolver call at 0x004fbd30 and animation-setting helper are unresolved.
// STUB: GAME 0x004df950
void RHEngine::FUN_004df950(const SBGeoPoint2D &point, char flag)
{
    if (!*(char *)((char *)this + 0x471a))
        return;
    RHUnk00613e90 first;
    RHUnk00613e90 second;
    RHSeqList *sequences = (RHSeqList *)((char *)this + 0x49f8);
    sequences->GoTo(0);
    void *element = sequences->cursor->data;
    if (!flag)
    {
        RHUnk005866a0 *action = new RHUnk005866a0(1, 0x5a, element);
        action->Unk00586ed0(0x1e, (int)&first);
        ((RHScriptBatchCalls *)((char *)this + 0x43f8))->Unk0058a940(
            "", 0, action);
        return;
    }
    RHUnk00584d60 *action = new RHUnk00584d60(1, 0x5a, element);
    ((RHScriptBatchCalls *)((char *)this + 0x43f8))->Unk0058a940(
        "", 0, action);
    RHUnk00549250 message(0x16, 0);
    RHUnk00546050()->RHUnk005460c0(message);
    (void)point;
    (void)second;
}

// Residual: target's resolver and animation-setting helpers are outside the assigned range.
// STUB: GAME 0x004dfe70
void RHEngine::FUN_004dfe70(const SBGeoPoint2D &point, char flag)
{
    if (!*(char *)((char *)this + 0x471a) && !flag)
        return;
    RHUnk00613e90 first;
    RHUnk00613e90 second;
    RHSeqList *sequences = (RHSeqList *)((char *)this + 0x49f8);
    sequences->GoTo(0);
    void *element = sequences->cursor->data;
    RHUnk005866a0 *action = new RHUnk005866a0(1, 0x5b, element);
    action->Unk00586ed0(0x20, (int)&first);
    if (!flag)
    {
        ((RHScriptBatchCalls *)((char *)this + 0x43f8))->Unk0058a940(
            "", 0, action);
        return;
    }
    RHUnk00582220 *node = new RHUnk00582220;
    ((RHUnk00585500 *)action)->Unk(node);
    ((RHScriptBatchCalls *)((char *)this + 0x4668))->Unk005c2ec0(
        (void *)&point, *(unsigned short *)((char *)this + 0xc4), 3,
        element, 0x1d, 0, 0, -1);
    unsigned short layer = *(unsigned short *)((char *)*(void **)((char *)this + 0x68) + 0x26);
    ((RHEngineSequenceDispatchCalls *)element)->Apply(node, 0, layer, action);
}

// Residual: target's 0x004f5890 validity test and 0x004fbd30 resolver are unavailable in scope.
// STUB: GAME 0x004e0030
void RHEngine::FUN_004e0030(const SBGeoPoint2D &point, void *actor, char flag)
{
    void *current = *(void **)((char *)this + 0xc8);
    if (!current)
        return;
    unsigned state = *(unsigned *)((char *)current + 0x30);
    if ((state & 0x1000) || ((state & 0x200) &&
        (*(int *)((char *)current + 0xf0) == 2 || *(int *)((char *)current + 0xf0) == 3)))
        return;
    RHSeqList *sequences = (RHSeqList *)((char *)this + 0x49f8);
    sequences->GoTo(0);
    void *element = sequences->cursor->data;
    char *sprite = *(char **)((char *)element + 0x50);
    unsigned type = *(unsigned *)(sprite + 0x8c);
    int style = flag ? 0xa : type == 0xa ? 0x10 : 0x16;
    RHUnk005883a0 *action = new RHUnk005883a0(1, 0x15, element, style,
        point, (int)actor, 0, 0);
    ((RHScriptBatchCalls *)((char *)this + 0x43f8))->Unk0058a940(
        "", 0, action);
}

// FUNCTION: GAME 0x004e0490
SBGeoPoint2D *RHUnk005b5e00::FUN_004e0490(int index, short base)
{
    char *resource = (char *)Unk();
    return Unk005bdd30((short)(*(short *)(*(char **)(resource + 4) + index * 2) + base));
}

// Parked at 0.8989: cache address load and shared return scheduling differ.
// STUB: GAME 0x004e04c0
void *RHEngine::FUN_004e04c0(int type, const SBGeoPoint2D &point, bool useCache, bool notify)
{
    if (useCache && *(void **)((char *)this + 0x8c))
        return *(void **)((char *)this + 0x8c);
    void *&result = *(void **)((char *)this + 0x8c);
    FUN_004c7d80((void *)&point, type, &result);
    if (result)
    {
        if (*(bool *)((char *)*(void **)((char *)this + 0x68) + 0x1f))
        {
            void *&previous = *(void **)((char *)this + 0x90);
            if (previous == result)
                return 0;
            previous = result;
            FUN_004de170(true, notify, false);
        }
        return result;
    }
    *(void **)((char *)this + 0x90) = 0;
    return result;
}

// Residual: target's direct 0x004a0020 callback and point-register schedule remain unmatched.
// STUB: GAME 0x004e0550
void RHEngine::FUN_004e0550(const SBGeoPoint2D &point, void *actor, int index)
{
    void *target = FUN_004e04c0(6, point, index, actor);
    if (!target)
        return;
    RHSeqList *sequences = (RHSeqList *)((char *)this + 0x49f8);
    sequences->GoTo(0);
    void *element = sequences->cursor->data;
    RHUnk00585ea0 *action = new RHUnk00585ea0(1, 0x56, element, target);
    char *sprite = *(char **)((char *)element + 0x50);
    SBGeoVector2D vector(*(SBGeoPoint2D *)(sprite + 0x1c));
    short frame = *(short *)(sprite + 0xd8);
    RHUnk005b5e00 *spriteCalls = (RHUnk005b5e00 *)sprite;
    void *holder = spriteCalls->Unk();
    short offset = *(short *)(*(char **)((char *)holder + 4) + 0xf6);
    SBGeoPoint2D *framePoint = spriteCalls->Unk005bdd30(offset + frame);
    float distance = ((RHUnk005fc3b0 *)&framePoint->Unk005fc190(vector).Unk005fc110(
        *(SBGeoPoint2D *)(sprite + 0x24)))->Unk005fc6a0(1.0f);
    (void)action;
    (void)distance;
}

// Residual: target's direct 0x004a0020 callback and action-constructor schedule remain unmatched.
// STUB: GAME 0x004e0770
void RHEngine::FUN_004e0770(const SBGeoPoint2D &point, void *actor, int index)
{
    void *target = FUN_004e04c0(9, point, index, actor);
    if (!target)
        return;
    RHSeqList *sequences = (RHSeqList *)((char *)this + 0x49f8);
    sequences->GoTo(0);
    void *element = sequences->cursor->data;
    RHUnk00585ea0 *action = new RHUnk00585ea0(1, 0x6e, element, target);
    char *sprite = *(char **)((char *)element + 0x50);
    SBGeoVector2D vector(*(SBGeoPoint2D *)(sprite + 0x1c));
    short frame = *(short *)(sprite + 0xd8);
    RHUnk005b5e00 *spriteCalls = (RHUnk005b5e00 *)sprite;
    void *holder = spriteCalls->Unk();
    short offset = *(short *)(*(char **)((char *)holder + 4) + 0x170);
    SBGeoPoint2D *framePoint = spriteCalls->Unk005bdd30(offset + frame);
    float distance = ((RHUnk005fc3b0 *)&framePoint->Unk005fc190(vector).Unk005fc110(
        *(SBGeoPoint2D *)(sprite + 0x24)))->Unk005fc6a0(1.0f);
    (void)action;
    (void)distance;
}

// FUNCTION: GAME 0x004e0bf0
void RHEngine::FUN_004e0bf0(const SBGeoPoint2D &, bool flag, bool)
{
    RHSeqList *sequences = (RHSeqList *)((char *)this + 0x49f8);
    sequences->GoTo(0);
    void *element = sequences->cursor->data;
    if (flag)
    {
        RHUnk00584d60 *action = new RHUnk00584d60(1, 0x63, element);
        RHUnk00582220 *node = new RHUnk00582220;
        ((RHUnk00585500 *)action)->Unk(node);
        const RHEngineSpritePoint &position = RHEngineSpritePoint();
        int effect = ((RHScriptBatchCalls *)((char *)this + 0x4668))->Unk005c2ec0(
            RHEnginePositionAddress(position), 0, 3, element, 0x18, (int)element, 0, -1);
        unsigned short actionIndex = *(unsigned short *)((char *)*(void **)((char *)this + 0x68) + 0x26);
        ((RHEngineSequenceDispatchCalls *)element)->Apply(node, 0, actionIndex, (void *)effect);
    }
    else
    {
        RHUnk00584d60 *action = new RHUnk00584d60(1, 0x63, element);
        ((RHScriptBatchCalls *)((char *)this + 0x43f8))->Unk0058a940(
            "", 0, action);
        ((RHMessenger *)*(void **)((char *)this + 0x68))->RHUnk005460c0(
            (RHUnk5490f0 &)RHUnk00549250(0x16, 0, 0));
    }
    if (flag)
    {
        ((RHMessenger *)*(void **)((char *)this + 0x68))->RHUnk005460c0(
            (RHUnk5490f0 &)RHUnk00549250(6, 0));
    }
}

// FUNCTION: GAME 0x004e14a0
void RHEngine::FUN_004e14a0(const SBGeoPoint2D &, bool flag, bool)
{
    RHSeqList *sequences = (RHSeqList *)((char *)this + 0x49f8);
    sequences->GoTo(0);
    void *element = sequences->cursor->data;
    if (flag)
    {
        RHUnk00584d60 *action = new RHUnk00584d60(1, 0x69, element);
        RHUnk00582220 *node = new RHUnk00582220;
        ((RHUnk00585500 *)action)->Unk(node);
        const RHEngineSpritePoint &position = RHEngineSpritePoint();
        int effect = ((RHScriptBatchCalls *)((char *)this + 0x4668))->Unk005c2ec0(
            RHEnginePositionAddress(position), 0, 3, element, 0x21, (int)element, 0, -1);
        unsigned short actionIndex = *(unsigned short *)((char *)*(void **)((char *)this + 0x68) + 0x26);
        ((RHEngineSequenceDispatchCalls *)element)->Apply(node, 0, actionIndex, (void *)effect);
    }
    else
    {
        RHUnk00584d60 *action = new RHUnk00584d60(1, 0x69, element);
        ((RHScriptBatchCalls *)((char *)this + 0x43f8))->Unk0058a940(
            "", 0, action);
        ((RHMessenger *)*(void **)((char *)this + 0x68))->RHUnk005460c0(
            (RHUnk5490f0 &)RHUnk00549250(0x16, 0, 0));
    }
    if (flag)
    {
        ((RHMessenger *)*(void **)((char *)this + 0x68))->RHUnk005460c0(
            (RHUnk5490f0 &)RHUnk00549250(6, 0));
    }
}

// FUNCTION: GAME 0x004e1630
void RHEngine::FUN_004e1630(const SBGeoPoint2D &, bool flag)
{
    RHSeqList *sequences = (RHSeqList *)((char *)this + 0x49f8);
    sequences->GoTo(0);
    void *element = sequences->cursor->data;
    if (flag)
    {
        RHUnk00584d60 *action = new RHUnk00584d60(1, 0x75, element);
        RHUnk00582220 *node = new RHUnk00582220;
        ((RHUnk00585500 *)action)->Unk(node);
        const RHEngineSpritePoint &position = RHEngineSpritePoint();
        int effect = ((RHScriptBatchCalls *)((char *)this + 0x4668))->Unk005c2ec0(
            RHEnginePositionAddress(position), 0, 3, element, 0x2c, (int)element, 0, -1);
        unsigned short actionIndex = *(unsigned short *)((char *)*(void **)((char *)this + 0x68) + 0x26);
        ((RHEngineSequenceDispatchCalls *)element)->Apply(node, 0, actionIndex, (void *)effect);
    }
    else
    {
        RHUnk00584d60 *action = new RHUnk00584d60(1, 0x75, element);
        ((RHScriptBatchCalls *)((char *)this + 0x43f8))->Unk0058a940(
            "", 0, action);
        ((RHMessenger *)*(void **)((char *)this + 0x68))->RHUnk005460c0(
            (RHUnk5490f0 &)RHUnk00549250(0x16, 0, 0));
    }
    if (flag)
    {
        ((RHMessenger *)*(void **)((char *)this + 0x68))->RHUnk005460c0(
            (RHUnk5490f0 &)RHUnk00549250(6, 0));
    }
}

static inline void *RHEnginePositionAddress(const RHEngineSpritePoint &position)
{
    return (void *)&position;
}

// FUNCTION: GAME 0x004e09d0
void RHEngine::FUN_004e09d0(const SBGeoPoint2D &point, bool queued, bool immediate)
{
    RHSeqList *sequences = (RHSeqList *)((char *)this + 0x49f8);
    sequences->GoTo(0);
    void *element = sequences->cursor->data;
    unsigned animation = *(volatile unsigned *)((char *)*(void **)((char *)element + 0x50) + 0x8c);
    switch (animation)
    {
    default:
        if (queued)
        {
            RHUnk00584d60 *action = new RHUnk00584d60(1, 0x61, element);
            RHUnk00582220 *node = new RHUnk00582220;
            ((RHUnk00585500 *)action)->Unk(node);
            const RHEngineSpritePoint &position = RHEngineSpritePoint();
            int effect = ((RHScriptBatchCalls *)((char *)this + 0x4668))->Unk005c2ec0(
                RHEnginePositionAddress(position), 0, 3, element, 0x22, (int)element, 0, -1);
            unsigned short actionIndex = *(unsigned short *)((char *)*(void **)((char *)this + 0x68) + 0x26);
            ((RHEngineSequenceDispatchCalls *)element)->Apply(node, 0, actionIndex, (void *)effect);
        }
        else if (immediate)
        {
            ((RHMessenger *)*(void **)((char *)this + 0x68))->RHUnk005460c0(
                (RHUnk5490f0 &)RHUnk00549250(0x16, 0, 0));
            return;
        }
        else
        {
            RHUnk00584d60 *action = new RHUnk00584d60(1, 0x61, element);
            ((RHScriptBatchCalls *)((char *)this + 0x43f8))->Unk0058a940("", 0, action);
            return;
        }
        break;
    case 0x14:
        if (immediate)
        {
            if (queued)
                FUN_004cd600(point, queued);
            else
            {
                ((RHElementActor *)element)->FUN_0046bb80();
                return;
            }
        }
        else
            FUN_004ccad0(point, queued);
        break;
    }
    if (queued)
    {
        ((RHMessenger *)*(void **)((char *)this + 0x68))->RHUnk005460c0(
            (RHUnk5490f0 &)RHUnk00549250(6, 0));
    }
}

// FUNCTION: GAME 0x004e0d80
void RHEngine::FUN_004e0d80(const SBGeoPoint2D &point, bool queued, bool immediate)
{
    RHSeqList *sequences = (RHSeqList *)((char *)this + 0x49f8);
    sequences->GoTo(0);
    void *element = sequences->cursor->data;
    switch (*(unsigned *)((char *)*(void **)((char *)element + 0x50) + 0x8c))
    {
    default:
        if (queued)
        {
            RHUnk00584d60 *action = new RHUnk00584d60(1, 0x5d, element);
            RHUnk00582220 *node = new RHUnk00582220;
            ((RHUnk00585500 *)action)->Unk(node);
            const RHEngineSpritePoint &position = RHEngineSpritePoint();
            int effect = ((RHScriptBatchCalls *)((char *)this + 0x4668))->Unk005c2ec0(
                RHEnginePositionAddress(position), 0, 3, element, 0x34, (int)element, 0, -1);
            unsigned short actionIndex = *(unsigned short *)((char *)*(void **)((char *)this + 0x68) + 0x26);
            ((RHEngineSequenceDispatchCalls *)element)->Apply(node, 0, actionIndex, (void *)effect);
            break;
        }
        if (immediate)
        {
            ((RHMessenger *)*(void **)((char *)this + 0x68))->RHUnk005460c0(
                (RHUnk5490f0 &)RHUnk00549250(0x16, 0, 0));
            return;
        }
        else
        {
            RHUnk00584d60 *action = new RHUnk00584d60(1, 0x5d, element);
            ((RHScriptBatchCalls *)((char *)this + 0x43f8))->Unk0058a940("", 0, action);
            return;
        }
    case 14:
        goto active;
    case 15:
active:
        if (immediate)
        {
            if (queued)
                FUN_004cd600(point, queued);
            else
            {
                ((RHElementActor *)element)->FUN_0046bb80();
                return;
            }
        }
        else
            FUN_004ccad0(point, queued);
        break;
    }
    if (queued)
    {
        ((RHMessenger *)*(void **)((char *)this + 0x68))->RHUnk005460c0(
            (RHUnk5490f0 &)RHUnk00549250(6, 0));
    }
}

// Residual: target's switch dispatch and parameter staging do not match these wrapper calls.
// STUB: GAME 0x004e17c0
void RHEngine::FUN_004e17c0(unsigned value, void *actor)
{
    if (value == 0x10)
    {
        SBGeoPoint2D point;
        FUN_004df550(point, actor, 0, 0);
        return;
    }
    if (value >= 6 && value <= 7)
    {
        SBGeoPoint2D point;
        FUN_004e0fb0(point, actor, 0, (int)value);
    }
}

// Residual: resolver helpers 0x004c7e10 and 0x004fbd30 lie outside the assigned range.
// STUB: GAME 0x004e0fb0
void RHEngine::FUN_004e0fb0(const SBGeoPoint2D &point, void *actor, char flag, int value)
{
    RHSeqList *sequences = (RHSeqList *)((char *)this + 0x49f8);
    sequences->GoTo(0);
    void *element = sequences->cursor->data;
    void *&selected = *(void **)((char *)this + 0x4d94);
    if (!selected)
        selected = actor;
    *(char *)((char *)this + 0x4d85) = 1;
    if (!flag)
    {
        RHUnk005866a0 *action = new RHUnk005866a0(1, 0x6a, element);
        action->Unk00586ed0(0x1c, (int)selected);
        ((RHScriptBatchCalls *)((char *)this + 0x43f8))->Unk0058a940(
            "", 0, action);
        return;
    }
    RHUnk00582220 *node = new RHUnk00582220;
    RHUnk00588530 *action = new RHUnk00588530(1, 0x15, element, 0xa, selected, 50.0f, 0);
    action->sequence = node;
    RHUnk005866a0 *target = new RHUnk005866a0(1, 0x6a, element);
    target->Unk00586ed0(0x1c, (int)selected);
    ((RHScriptBatchCalls *)((char *)this + 0x4668))->Unk005c2ec0(
        (void *)&point, 0, 3, actor, value, (int)selected, 0, -1);
    unsigned short layer = *(unsigned short *)((char *)*(void **)((char *)this + 0x68) + 0x26);
    ((RHEngineSequenceDispatchCalls *)element)->Apply(node, 0, layer, target);
}

// FUNCTION: GAME 0x004e1890
bool RHEngine::FUN_004e1890()
{
    unsigned count = *(unsigned *)((char *)this + 0x4a00);
    for (unsigned i = 0; i < count; ++i)
    {
        RHEngineSequenceList &actors = *(RHEngineSequenceList *)((char *)this + 0x49f8);
        actors.GoToUnk004e1fc0(i);
        if (*(void **)((char *)actors.cursor->data + 0x268))
            return true;
    }
    return false;
}

// FUNCTION: GAME 0x004e19c0
unsigned RHEngine::FUN_004e19c0(unsigned value)
{
    switch (value)
    {
    case 2: return 0x3b;
    case 3: return 0x3c;
    case 4: return 0x3d;
    case 5: return 0x3e;
    case 6: return 0x3f;
    case 7: return 0x40;
    case 8: return 0x41;
    case 9: return 0x42;
    case 10: return 0x43;
    default: return 0x3b;
    }
}

// FUNCTION: GAME 0x004e1f30
unsigned RHEngine::FUN_004e1f30(unsigned value)
{
    switch (value)
    {
    case 2: return 0;
    case 3: return 1;
    case 4: return 2;
    case 5: return 3;
    case 6: return 4;
    case 7: return 5;
    case 8: return 6;
    case 9: return 7;
    case 10: return 8;
    default: return 10;
    }
}



// Parked at 0.8621: iterator-call argument scheduling differs.
// STUB: GAME 0x004e1fc0
void RHEngine::FUN_004e1fc0()
{
    unsigned count = *(unsigned *)((char *)this + 0x4a00);
    for (unsigned index = 0; index < count; ++index)
    {
        RHEngineSequenceList &actors = *(RHEngineSequenceList *)((char *)this + 0x49f8);
        actors.GoToUnk004e1fc0(index);
        void *actor = actors.cursor->data;
        if (*(unsigned *)((char *)actor + 0x268))
        {
            RHUnk00584d60 *action = new RHUnk00584d60(1, 0x34, actor);
            ((RHScriptBatchCalls *)((char *)this + 0x43f8))->Unk0058a940("", 0, action);
        }
    }
}

void EmitRHEngine004e1fc0(RHEngine *engine)
{
    engine->FUN_004e1fc0();
}

// FUNCTION: GAME 0x004e2150
void *RHEngine::FUN_004e2150(RHUnk0051e790 *target, const SBGeoPoint2D &point)
{
    unsigned count = ((RHSectorActorList *)((char *)this + 0x49f8))->m_count;
    for (unsigned index = 0; index < count; ++index)
    {
        RHSectorActorList &selection = *(RHSectorActorList *)((char *)this + 0x49f8);
        selection.Unk005c8e40(index);
        RHElementActorPC *pc = (RHElementActorPC *)selection.CurrentValue();
        if (((RHScriptBatchCalls *)pc)->Unk0049d560(0x16))
        {
            if (*(void **)((char *)pc + 0x268))
            {
                if (pc->FUN_0049d520() < 100.0f)
                    pc->FUN_0049d520();
            }
            else
                pc->FUN_0049d520();
            return target->FUN_0051e790(pc, *(char **)((char *)pc + 0x50) + 0x24, point, 0);
        }
    }
    return 0;
}

// FUNCTION: GAME 0x004e21e0
bool RHEngine::FUN_004e21e0(void *actor)
{
    if (!actor)
    {
        unsigned count = *(unsigned *)((char *)this + 0x4a00);
        for (unsigned index = 0; index < count; ++index)
        {
            RHEngineSequenceList &actors = *(RHEngineSequenceList *)((char *)this + 0x49f8);
            actors.GoToUnk004e1fc0(index, true);
            if (!((RHScriptBatchCalls *)actors.cursor->data)->Unk0049d560(0x15))
                return false;
        }
        return true;
    }
    return ((RHScriptBatchCalls *)actor)->Unk0049d560(0x15);
}

bool EmitRHEngine004e21e0(RHEngine *engine, void *actor)
{
    return engine->FUN_004e21e0(actor);
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
    RHUnk00588530 *arrival = new RHUnk00588530(1, 0x13, reinforcement, 6, 0);
    *(void **)((char *)arrival + 0x7c) = door;
    *(int *)((char *)arrival + 0x88) = 2;
    ((RHUnk00585500 *)arrival)->Unk(sequence);
    SBGeoPoint2D destination;
    unsigned attempt;
    SBGeoPoint2D &exit = *(SBGeoPoint2D *)((char *)door + 0x20);
    for (attempt = 0; attempt < 10; ++attempt)
    {
        destination = exit + SBGeoVector2D(
            (float)(rand() * 100) * 0.00003051850944757461548f - 50.0f,
            (float)(rand() * 100) * 0.00003051850944757461548f - 50.0f);
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
    ((RHUnk0058a3d0 *)((char *)this + 0x43f8))->Unk("", 0, sequence);
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

// FUNCTION: GAME 0x004e3100
void RHEngine::FUN_004e3100(int action)
{
    if (*(int *)((char *)**(void ***)((char *)g_unk0x6c07fc + 0x178) + 0x3c) != 8)
        return;
    unsigned count = PCCount();
    if (action == 25)
    {
        for (unsigned i = 0; i < count; ++i)
        {
            void *actor = m_493c[i];
            if (*(char *)((char *)actor + 0x12) &&
                (((RHUnk0049d4f0 *)actor)->Unk(25) || ((RHUnk0049d4f0 *)actor)->Unk(26) ||
                 ((RHScriptBatchCalls *)actor)->Unk0049d560(25) || ((RHScriptBatchCalls *)actor)->Unk0049d560(26)))
            {
                *(char *)((char *)actor + 0x92) = 1;
                *(int *)((char *)actor + 0xa0) = 0;
                *(unsigned short *)((char *)actor + 0xa4) = 2;
            }
        }
    }
    else
    {
        for (unsigned i = 0; i < count; ++i)
        {
            void *actor = m_493c[i];
            if (*(char *)((char *)actor + 0x12) &&
                (((RHUnk0049d4f0 *)actor)->Unk(action) || ((RHScriptBatchCalls *)actor)->Unk0049d560(action)))
            {
                *(char *)((char *)actor + 0x92) = 1;
                *(int *)((char *)actor + 0xa0) = 0;
                *(unsigned short *)((char *)actor + 0xa4) = 2;
            }
        }
    }
}

// FUNCTION: GAME 0x004e34f0
int RHEngine::FUN_004e34f0()
{
    if (*(unsigned int *)((char *)this + 0x4a00) == 1)
    {
        void **node = **(void ****)((char *)this + 0x49fc);
        if (((RHScriptBatchCalls *)node[2])->Unk0049d560(28))
            return 1;
    }
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

// FUNCTION: GAME 0x004e35a0
RHDialogueSet *RHEngine::GetDynResources(unsigned long mission)
{
    if (!mission)
        mission = ***((unsigned ***)((char *)g_unk0x6c07fc + 0x178));
    RHMapDescription &description = *(RHMapDescription *)((char *)this + 0x4d68);
    if (!description.FUN_0063c9e0(mission))
        LoadDynRes(mission);
    return (RHDialogueSet *)description.FUN_0063c9e0(mission);
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

// FUNCTION: GAME 0x004e3660
void RHEngineWidenedCalls::FUN_004e3660(char flag)
{
    *(char *)((char *)this + 0x4e8) = flag;
    RHUnk00546050()->RHUnk005460c0(RHUnk00549250(flag ? 11 : 12, this));
}

#include "RHEngineSpriteCalls.h"

// FUNCTION: GAME 0x004e36d0
void RHEngine::FUN_004e36d0()
{
    void **first = *(void ***)((char *)this + 0x48dc);
    unsigned count = first == 0 ? 0 : *(void ***)((char *)this + 0x48e0) - first;
    for (unsigned i = 0; i < count; ++i) {
        void *element = (*(void ***)((char *)this + 0x48dc))[i];
        if ((*(unsigned *)((char *)element + 4) & 3) == 1)
            (*(RHEngineSpriteCalls **)((char *)element + 0x50))->FUN_005bd4e0();
    }
}

// FUNCTION: GAME 0x004e3720
int RHEngine::FUN_004e3720(void *first, int second, unsigned short type, void *fourth, void *fifth)
{
    *(unsigned short *)((char *)this + 0xc4) = type;
    *(void **)((char *)this + 0xcc) = fifth;
    *(void **)((char *)this + 0xc8) = fourth;
    return FUN_004cac00(first, 0, second, 0);
}

#include "RHEngineAccessors.h"

// FUNCTION: GAME 0x004e3760
void *RHUnk004e3760::Get()
{
    return (char *)this + 0x42f4;
}

// FUNCTION: GAME 0x004e3c20
void RHEngine::FUN_004e3c20(void *point)
{
    void *actor = 0;
    int command;
    if (!*(char *)((char *)this + 0x72) && !*(char *)((char *)this + 0x73) &&
        FUN_004c7e10(point, 1, &actor))
        command = 41;
    else
        command = 42;
    (*(RHMessenger **)((char *)this + 0x68))->RHUnk005460c0(RHUnk00549250(command, actor));
}

// FUNCTION: GAME 0x004e3cd0
bool RHEngine::FUN_004e3cd0()
{
    void **first = *(void **volatile *)((char *)this + 0x493c);
    unsigned count;
    if (first == 0)
        count = 0;
    else
        count = *(void ***)((char *)this + 0x4940) - first;
    for (unsigned index = 0; index < count; ++index)
    {
        void *value = (*(void ***)((char *)this + 0x493c))[index];
        if (*(int *)((char *)value + 0x5e8))
            return true;
    }
    return false;
}

class RHEngineActorArray : public SBArray<RHSaveGame *>
{
public:
    void Resize(unsigned count)
    {
        if (GetSize() < count)
        {
            RHSaveGame *value = 0;
            Insert(end(), count - GetSize(), value);
        }
        else if (count < GetSize())
            m_last = copy(end(), end(), begin() + count);
        dirty = true;
    }
    void *cursor;
    bool dirty;
};

// Parked: array size reloads, zero-local colouring and resize branch scheduling differ.
// STUB: GAME 0x004e3d20
void RHEngine::FUN_004e3d20(int index, int value)
{
    RHEngineActorArray &values = *(RHEngineActorArray *)((char *)this + 0x4c58);
    if (index >= (int)values.GetSize())
        values.Resize(index + 16);
    (*(int **)((char *)this + 0x4c5c))[index] = value;
}

#include <list>

class RHEnginePairList
{
public:
    RHEnginePairList &FUN_004e4000(const RHEnginePairList &other);
    char m_allocator[4];
    RHUnk004cc030Node *m_head;
    unsigned m_count;
};

// FUNCTION: GAME 0x004e4000
RHEnginePairList &RHEnginePairList::FUN_004e4000(const RHEnginePairList &other)
{
    typedef std::list<std::pair<unsigned, unsigned> > List;
    return (RHEnginePairList &)((*(List *)this) = *(const List *)&other);
}

void EmitRHEnginePairList(RHEnginePairList *list, const RHEnginePairList &other)
{
    list->FUN_004e4000(other);
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

#include "SBGeoSegment2D.h"
#include "RHGameInputTranslator.h"

#include "SBUIInputFieldBoxCalls.h"

// SIZE 0x10
struct RHUnk004e4500Segments
{
    std::allocator<SBGeoSegment2D> m_allocator; // 0x00
    RHGameInputSegment *m_first; // 0x04
    RHGameInputSegment *m_last; // 0x08
    RHGameInputSegment *m_end; // 0x0c
    static RHGameInputSegment *Copy(RHGameInputSegment *first, RHGameInputSegment *last, RHGameInputSegment *destination)
    {
        for (; first != last; ++first, ++destination)
            ((SBUIInputFieldBoxCalls *)destination)->FUN_0060a860((const RHMobileUnk006100e0 &)*first);
        return destination;
    }
    static void Destroy(RHGameInputSegment *first, RHGameInputSegment *last)
    {
        for (; first != last; ++first)
            first->FUN_004611c0();
    }
    RHGameInputSegment *Erase(RHGameInputSegment *first, RHGameInputSegment *last)
    {
        RHGameInputSegment *end = m_last;
        RHGameInputSegment *kept = Copy(last, end, first);
        Destroy(kept, m_last);
        m_last = kept;
        return first;
    }
};

// SIZE 0x2c
class RHUnk004e4500
{
public:
    RHUnk004e4500();
    ~RHUnk004e4500();
    std::vector<SBGeoSegment2D> m_segments; // 0x00
    undefined4 m_10; // 0x10
    bool m_dirty; // 0x14
    undefined m_15[7]; // 0x15
    SBGeoSegment2D m_1c; // 0x1c
};

DECOMP_SIZE_ASSERT(RHUnk004e4500, 0x2c)

// FUNCTION: GAME 0x004e4500
RHUnk004e4500::RHUnk004e4500()
    : m_dirty(true), m_1c(SBGeoPoint2D(0.0f, 0.0f), SBGeoPoint2D(0.0f, 0.0f))
{
}

// FUNCTION: GAME 0x004e45a0
RHUnk004e4500::~RHUnk004e4500()
{
    RHUnk004e4500Segments &segments = *(RHUnk004e4500Segments *)&m_segments;
    segments.Erase(segments.m_first, segments.m_last);
}

void EmitRHUnk004e4500()
{
    RHUnk004e4500 value;
}

// FUNCTION: GAME 0x004e51e0
void *RHbeamMe::FUN_004e51e0(unsigned flags)
{
    this->~RHbeamMe();
    if (flags & 1)
        operator delete(this);
    return this;
}

class RHUnk004e5230
{
public:
    void FUN_004e5230();
    char m_0[4];
    char *m_4;
    char *m_8;
    char *m_c;
};

// FUNCTION: GAME 0x004e5230
void RHUnk004e5230::FUN_004e5230()
{
    char *last = m_8;
    char *first = m_4;
    while (first != last)
    {
        ((RHGameInputSegment *)first)->FUN_004611c0();
        first += 0x10;
    }
    operator delete(m_4);
    m_4 = 0;
    m_8 = 0;
    m_c = 0;
}

class RHUnk004e52f0
{
public:
    struct Node
    {
        Node *next;
        Node *previous;
        RHUnk004cc030 value;
    };
    struct Iterator
    {
        Node *node;
        Iterator(Node *value) : node(value) {}
        Iterator operator++(int)
        {
            Iterator previous = *this;
            node = node->next;
            return previous;
        }
    };
    RHUnk004e52f0(const char &allocator);
    ~RHUnk004e52f0();
    Iterator Erase(Iterator position);
    Iterator FUN_004e5fe0(Iterator position, const RHUnk004cc030 &value);
    Iterator FUN_004e6040(Iterator first, Iterator last);
    char m_allocator[4];
    Node *m_head;
    unsigned m_count;
};

DECOMP_SIZE_ASSERT(RHUnk004cc030, 0x18)
DECOMP_SIZE_ASSERT(RHUnk004e52f0::Node, 0x20)
DECOMP_SIZE_ASSERT(RHUnk004e52f0, 0x0c)

// FUNCTION: GAME 0x004e52f0
RHUnk004e52f0::RHUnk004e52f0(const char &allocator)
{
    m_allocator[0] = allocator;
    Node *node = (Node *)operator new(sizeof(Node));
    node->next = node;
    node->previous = node;
    m_head = node;
    m_count = 0;
}

// FUNCTION: GAME 0x004e5320
RHUnk004e52f0::~RHUnk004e52f0()
{
    Node *last = m_head;
    Node *current = last->next;
    while (current != last)
    {
        Node *node = current;
        current = current->next;
        node->previous->next = node->next;
        node->next->previous = node->previous;
        node->value.~RHUnk004cc030();
        operator delete(node);
        --m_count;
    }
    operator delete(m_head);
    m_head = 0;
    m_count = 0;
}

// FUNCTION: GAME 0x004e5380
RHUnk004e52f0::Iterator RHUnk004e52f0::Erase(Iterator position)
{
    Node *node = (position++).node;
    node->previous->next = node->next;
    node->next->previous = node->previous;
    node->value.~RHUnk004cc030();
    operator delete(node);
    --m_count;
    return position;
}

void EmitRHEnginePayloadList(RHUnk004e52f0 &list, RHUnk004e52f0::Iterator position)
{
    list.Erase(position);
    char allocator = 0;
    RHUnk004e52f0 temporary(allocator);
}

RHElementActorPC *&EmitRHEnginePCArrayAccess(std::vector<RHElementActorPC *> &actors, unsigned index)
{
    return actors.at(index);
}

// TEMPLATE: GAME 0x004e5aa0
// ?_Xran@?$vector@PAVRHElementActorPC@@V?$allocator@PAVRHElementActorPC@@@std@@@std@@IBEXXZ

class RHElementActorNPC;
class RHElementMobile;
class RHElementFX;
class RHElementActorSoldier;

RHElement *&EmitRHEngineElementArrayAccess(std::vector<RHElement *> &elements, unsigned index)
{
    RHElement *&(std::vector<RHElement *>::*at)(unsigned) = &std::vector<RHElement *>::at;
    return (elements.*at)(index);
}

RHElementActor *&EmitRHEngineActorArrayAccess(std::vector<RHElementActor *> &actors, unsigned index)
{
    return actors.at(index);
}

RHElementActorNPC *&EmitRHEngineNPCArrayAccess(std::vector<RHElementActorNPC *> &actors, unsigned index)
{
    return actors.at(index);
}

RHElementMobile *&EmitRHEngineMobileArrayAccess(std::vector<RHElementMobile *> &elements, unsigned index)
{
    return elements.at(index);
}

RHElementFX *&EmitRHEngineFXArrayAccess(std::vector<RHElementFX *> &elements, unsigned index)
{
    return elements.at(index);
}

RHElementActorHuman *&EmitRHEngineHumanArrayAccess(std::vector<RHElementActorHuman *> &actors, unsigned index)
{
    return actors.at(index);
}

RHElementActorSoldier *&EmitRHEngineSoldierArrayAccess(std::vector<RHElementActorSoldier *> &actors, unsigned index)
{
    return actors.at(index);
}

// TEMPLATE: GAME 0x004e5200
// ?at@?$vector@PAVRHElement@@V?$allocator@PAVRHElement@@@std@@@std@@QAEAAPAVRHElement@@I@Z

// TEMPLATE: GAME 0x004e53c0
// ?_Xran@?$vector@PAVRHElement@@V?$allocator@PAVRHElement@@@std@@@std@@IBEXXZ

// TEMPLATE: GAME 0x004e54a0
// ?what@logic_error@std@@UBEPBDXZ

// TEMPLATE: GAME 0x004e54b0
// ??0logic_error@std@@QAE@ABV01@@Z

// TEMPLATE: GAME 0x004e5610
// ?_Doraise@logic_error@std@@MBEXXZ

// TEMPLATE: GAME 0x004e5630
// ??1out_of_range@std@@UAE@XZ

// TEMPLATE: GAME 0x004e5680
// ?_Doraise@out_of_range@std@@MBEXXZ

// TEMPLATE: GAME 0x004e56a0
// ??_Eout_of_range@std@@UAEPAXI@Z

// TEMPLATE: GAME 0x004e56c0
// ??0out_of_range@std@@QAE@ABV01@@Z

// TEMPLATE: GAME 0x004e59c0
// ?_Xran@?$vector@PAVRHElementActor@@V?$allocator@PAVRHElementActor@@@std@@@std@@IBEXXZ

// TEMPLATE: GAME 0x004e5b80
// ?_Xran@?$vector@PAVRHElementActorNPC@@V?$allocator@PAVRHElementActorNPC@@@std@@@std@@IBEXXZ

// TEMPLATE: GAME 0x004e5c60
// ?_Xran@?$vector@PAVRHElementMobile@@V?$allocator@PAVRHElementMobile@@@std@@@std@@IBEXXZ

// TEMPLATE: GAME 0x004e5d40
// ?_Xran@?$vector@PAVRHElementFX@@V?$allocator@PAVRHElementFX@@@std@@@std@@IBEXXZ

// TEMPLATE: GAME 0x004e5e20
// ?_Xran@?$vector@PAVRHElementActorHuman@@V?$allocator@PAVRHElementActorHuman@@@std@@@std@@IBEXXZ

// TEMPLATE: GAME 0x004e5f00
// ?_Xran@?$vector@PAVRHElementActorSoldier@@V?$allocator@PAVRHElementActorSoldier@@@std@@@std@@IBEXXZ

// FUNCTION: GAME 0x004e5fe0
RHUnk004e52f0::Iterator RHUnk004e52f0::FUN_004e5fe0(Iterator position, const RHUnk004cc030 &value)
{
    Node *next = position.node;
    Node *previous = next->previous;
    Node *node = (Node *)operator new(sizeof(Node));
    node->next = next != 0 ? next : node;
    node->previous = previous != 0 ? previous : node;
    next->previous = node;
    node->previous->next = node;
    std::_Construct(&node->value, value);
    ++m_count;
    return Iterator(node);
}

// FUNCTION: GAME 0x004e6040
RHUnk004e52f0::Iterator RHUnk004e52f0::FUN_004e6040(Iterator first, Iterator last)
{
    Node *current = first.node;
    Node *end = last.node;
    while (current != end)
    {
        Node *node = current;
        current = current->next;
        node->previous->next = node->next;
        node->next->previous = node->previous;
        node->value.~RHUnk004cc030();
        operator delete(node);
        --m_count;
    }
    return Iterator(current);
}

// FUNCTION: GAME 0x004e6690
void FUN_004e6690(void **first, void **last,
                  bool (*compare)(void *, void *), int)
{
    void (*sort)(void **, void **, bool (*)(void *, void *), void **) = &std::_Sort;
    if (last - first <= std::_SORT_MAX)
        std::_Insertion_sort(first, last, compare);
    else
    {
        void **rangeLast = last;
        void **rangeFirst = first;
        while (std::_SORT_MAX < rangeLast - rangeFirst)
        {
            void **middle = std::_Unguarded_partition(rangeFirst, rangeLast,
                std::_Median(*rangeFirst, *(rangeFirst + (rangeLast - rangeFirst) / 2), *(rangeLast - 1), compare), compare);
            if (rangeLast - middle <= middle - rangeFirst)
            {
                sort(middle, rangeLast, compare, (void **)0);
                rangeLast = middle;
            }
            else
            {
                sort(rangeFirst, middle, compare, (void **)0);
                rangeFirst = middle;
            }
        }
        std::_Insertion_sort(first, first + std::_SORT_MAX, compare);
        for (first += std::_SORT_MAX; first != last; ++first)
            std::_Unguarded_insert(first, (void *)*first, compare);
    }
}

// Parked: inlined inner-list copy keeps p in EDI; target holds p in ESI and reuses the source register.
// STUB: GAME 0x004e6930
// ?_Construct@std@@YAXPAVRHUnk004cc030@@ABV2@@Z

// TEMPLATE: GAME 0x004e6f70
// ?_Sort@std@@YAXPAPAX0P6A_NPAX1@Z0@Z
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

void EmitRHEngineConstSort(void **first, void **last, bool (*compare)(const void *, const void *))
{
    std::_Sort(first, last, compare, (void **)0);
}

// TEMPLATE: GAME 0x004e70e0
// ?_Sort@std@@YAXPAPAX0P6A_NPBX1@Z0@Z

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
        ((RHUnk005069a0 *)it)->FUN_00504b80(
            g_pEngine->FUN_004d2340(15));
    for (it = m_3c; it != m_40; it += 0x14)
        ((RHUnk005069a0 *)it)->FUN_00504b80(
            g_pEngine->FUN_004d2340(15));
    for (it = m_2c; it != m_30; it += 0x14)
        ((RHUnk005069a0 *)it)->FUN_00504b80(
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
    (*(RHPortraitBar **)((char *)this + 0x196c))->FUN_0055ebf0();
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
    m_04.m_dirty = true;
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
        unsigned short entries = group->size();
        for (unsigned short j = 0; j < entries; ++j)
        {
            RHUnk00551da0 *entry = (*group)[j];
            result |= entry->FUN_00551da0(file);
        }
    }
    return result;
}

// FUNCTION: GAME 0x0051d370
void RHUnk0051d2c0::FUN_0051d370()
{
    int count = size();
    for (int index = 0; index < count; ++index)
    {
        RHUnk00551da0 *entry = (*this)[index];
        if (entry)
            ((RHUnk0051d370Entry *)((char *)entry + 0x5c))->V00(1);
    }
    clear();
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
    ((RHPathFinder *)this)->FUN_00556260();
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

// Parked: cached-cursor address lifetime, frame size and loop registers differ.
// STUB: GAME 0x0058a670
bool RHEngineSequenceStateCalls::FUN_0058a670(void *sequence)
{
    unsigned short count = *(unsigned *)((char *)this + 0xc);
    RHEngineSequenceList &sequences = *(RHEngineSequenceList *)((char *)this + 4);
    for (unsigned short i = 0; i < count; ++i)
        if (sequences.Get(i, true, true) == sequence)
            return true;
    return false;
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

// FUNCTION: GAME 0x005a5c50
void RHEngineSerializationCalls::FUN_005a5c50()
{
    *(unsigned *)((char *)this + 0x198) = 0;
    *(unsigned *)((char *)this + 0x1a0) = 0;
}

// FUNCTION: GAME 0x005a5c60
float RHEngineSerializationCalls::FUN_005a5c60(unsigned index)
{
    if (index == *(unsigned *)((char *)this + 0x198) &&
        *(unsigned *)((char *)this + 0x1a0) == *(unsigned *)((char *)g_pEngine + 0x4a94))
        return *(float *)((char *)this + 0x19c);
    return 0.0f;
}

// FUNCTION: GAME 0x005a5ca0
void RHEngineSerializationCalls::FUN_005a5ca0(unsigned first, float second)
{
    *(unsigned *)((char *)this + 0x198) = first;
    *(float *)((char *)this + 0x19c) = second;
    *(unsigned *)((char *)this + 0x1a0) = *(unsigned *)((char *)*(void **)0x006c0a88 + 0x4a94);
}

// FUNCTION: GAME 0x005a5cd0
void FUN_005a5cd0()
{
    g_unk0x006c1058 = 0;
    g_unk0x006c1060 = 0;
}

// FUNCTION: GAME 0x005a5ce0
float FUN_005a5ce0(unsigned index)
{
    if (index == g_unk0x006c1058 &&
        g_unk0x006c1060 == *(unsigned *)((char *)g_pEngine + 0x4a94))
        return g_unk0x006c105c;
    return 0.0f;
}

// FUNCTION: GAME 0x005a5d10
void FUN_005a5d10(unsigned first, float second)
{
    g_unk0x006c1058 = first;
    g_unk0x006c105c = second;
    g_unk0x006c1060 = *(unsigned *)((char *)g_pEngine + 0x4a94);
}

void EmitRHEngineSerializationCalls(RHEngineSerializationCalls *a)
{
    a->FUN_005a5c60(0);
    a->FUN_005a5ca0(0, 0.0f);
    FUN_005a5ce0(0);
    FUN_005a5d10(0, 0.0f);
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
    ((RHGameActionCalls *)this)->FUN_004da2f0();
    FUN_004e3c20(value);
    FUN_004d8fd0(0);
    FUN_004e3d20(0, 0);
    ((RHpathRequest *)value)->~RHpathRequest();
    ((RHUnk004a7ed0 *)value)->FUN_004a7f30();
    ((RHUnk004a7ed0 *)value)->FUN_004a7f80();
    ((RHUnk004a7ed0 *)value)->FUN_004a7f40(0, 0, 0);
    ((RHUnk004ba900 *)value)->FUN_004ba970();
    ((RHUnk004ba900 *)value)->FUN_004ba980(value);
    ((RHUnk004d96a0 *)value)->FUN_004d96a0();
    ((RHUnk004d96d0 *)value)->FUN_004d96d0();
    TurnPathFinderOn();
    TurnPathFinderOff();
    FUN_004e34f0();
    FUN_004e1f30(0);
    FUN_004e3cd0();
    FUN_004e3720(0, 0, 0, 0, 0);
    FUN_004be5c0(file, value);
    FUN_004c0340(*(SBGeoPoint2D *)value);
    FUN_0049b590(value);
    FUN_004db7b0(value);
    FUN_004db880();
    FUN_004db8c0(0);
    FUN_004db8e0(0);
    FUN_004db920(value);
    FUN_004dba50(value);
    FUN_004dbb70(value);
    FUN_004dbc90(value);
    FUN_004dbdb0(value);
    FUN_004dbe40(value);
    FUN_004dbed0(value);
    FUN_004dc190(value);
    FUN_004dc260(value);
    FUN_004de170(false, false, false);
    FUN_004de1e0();
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
    ((RHUnk004a6000 *)value)->FUN_004a6060();
    ((RHUnk004a6310 *)value)->FUN_004a6310(0);
    ((RHUnk004a6310 *)value)->FUN_004a6370();
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

void EmitRHEngineVariants(void *storage)
{
    ((RHUnk0057ee40 *)storage)->RHUnk0057ee40::~RHUnk0057ee40();
}

void EmitRHEngineWordArrayClear(std::vector<unsigned short> &values)
{
    typedef std::vector<unsigned short> Values;
    void (Values::*clear)() = &Values::clear;
    (values.*clear)();
}

// TEMPLATE: GAME 0x004e6bd0
// ?clear@?$vector@GV?$allocator@G@std@@@std@@QAEXXZ
