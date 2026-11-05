#ifndef RHELEMENTMOBILE_H
#define RHELEMENTMOBILE_H
#include "RHSectorActorList.h"

#include "SB.h"
#include "Decomp.h"
#include <new>

template <class T> inline T &RHMobileField(void *object, unsigned offset)
{
    return *(T *)((char *)object + offset);
}

template <class T> inline const T &RHMobileField(const void *object, unsigned offset)
{
    return *(const T *)((const char *)object + offset);
}

#include "RHUnkWaypointRef.h"
extern char g_unk0x6c0691;

class SBGeoSegment2D;
#include "RHFastFindGeometry.h"
#include "RHUnk00613e90.h"

#include "RHSpriteLastFrameCalls.h"

class RHUnk004af1d0
{
public:
    void Unk(bool value);
};

class RHUnkTargetSprite
{
public:
    bool FUN_005b76e0(unsigned index, unsigned short row);
    char m_0[0x10];
    RHUnk00613e90 m_10;
    char m_1c[8];
    SBGeoPoint2D m_24;
    RHUnk00613e90 m_2c;
    char m_38[8];
    SBGeoPoint2D m_40;
    char m_48[0x1c];
    RHUnk00613e90 m_64;
    char m_70[0x6e];
    unsigned short m_de;
    char m_e0[0xc];
    void *m_ec;
};


struct RHMobileElement
{
    void OffsetPoint(const SBGeoPoint2D &point);
    char m_0[0x50];
    RHUnkTargetSprite *m_50;
    char m_54[0x10];
    short m_64;
    short m_66;
    char m_68[0x94];
    float m_fc;
};

struct RHMobileWaypoints
{
    int m_0;
    RHMobileElement **m_4;
    RHMobileElement **m_8;
    unsigned short Size() const { if (!m_4) return 0; return (unsigned short)(m_8 - m_4); }
};

// SIZE 0x08
struct RHMobilePath
{
    undefined4 m_0; // 0x00
    RHMobileWaypoints *m_4; // 0x04
    SBGeoVector2D FUN_004ae380() const;
    unsigned short Size() const { return m_4 == 0 ? 0 : m_4->m_4 == 0 ? 0 : (unsigned short)(m_4->m_8 - m_4->m_4); }
    bool FUN_00550660(unsigned char value);
    void FUN_005505c0();
};

class RHMobileSegment
{
public:
    RHMobileSegment(const SBGeoPoint2D &first, const SBGeoPoint2D &second);
    ~RHMobileSegment();
    SBGeoPoint2D m_0;
    SBGeoPoint2D m_8;
};

class RHMobileGrid
{
public:
    void FUN_004ed370(void *lines, unsigned short layer, const RHMobileSegment &segment, unsigned mask);
    void FUN_004e9d90(class RHMobilePointerList &output, class RHMobilePolygon &polygon);
    void FUN_004ea7b0(class RHMobilePointerList &output, class RHMobilePolygon &polygon);
};

class RHMobilePolygon
{
public:
    virtual void v0(); // vtable+0x00
    virtual void FUN_00464530(SBFile &file, bool value); // vtable+0x04
    undefined m_4[0x38]; // 0x04
};

#include "RHUnkSectorPoints.h"

class RHMobilePolygonPoints
{
public:
    unsigned short FUN_0060ce80() const
    {
        return ((RHUnkSectorPoints *)this)->Unk0060ce80();
    }
    const SBGeoPoint2D &FUN_0060cef0(unsigned index) const
    {
        return ((RHUnkSectorPoints *)this)->Unk0060cef0(index);
    }
};

class __declspec(novtable) RHUnk005214b0
{
public:
    void *FUN_005214d0(unsigned flags);
    RHUnk005214b0();
    virtual ~RHUnk005214b0(); // vtable+0x00
    char m_04[0x10];
    int m_14;
    char m_18[8];
    unsigned short m_20;
};

// VTABLE: GAME 0x006790f8
// SIZE 0x44
class RHMobileUnk0051fd10 : public RHUnk005214b0
{
public:
    RHMobileUnk0051fd10(float first, float second);
    virtual ~RHMobileUnk0051fd10(); // vtable+0x00
    virtual void FUN_00520480(); // vtable+0x04
    void FUN_0051fdc0();
    bool FUN_0051fea0(const SBGeoPoint2D &point, float &distance);
    float m_24; // 0x24
    float m_28; // 0x28
    float m_2c; // 0x2c
    float m_30; // 0x30
    RHUnk005fc3b0 m_34; // 0x34
    RHUnk005fc3b0 m_3c; // 0x3c
};

#include "RHRepulsivePoint.h"

struct RHMobilePointerNode
{
    RHMobilePointerNode *next; // 0x00
    RHMobilePointerNode *previous; // 0x04
    void *value; // 0x08
};

class RHMobilePointerList
{
public:
    RHMobilePointerList();
    ~RHMobilePointerList();
    __forceinline void FUN_005c8e40(int index) { ((RHSectorActorList *)this)->Unk005c8e40(index); }
    void Append(void *value)
    {
        RHMobilePointerNode *head = m_4;
        RHMobilePointerNode *previous = head->previous;
        RHMobilePointerNode *node = (RHMobilePointerNode *)::operator new(12);
        node->next = head ? head : node;
        node->previous = previous ? previous : node;
        head->previous = node;
        node->previous->next = node;
        if (&node->value)
            node->value = value;
        ++m_8;
        m_10 = true;
    }
    undefined4 m_0; // 0x00
    RHMobilePointerNode *m_4; // 0x04
    unsigned m_8; // 0x08
    RHMobilePointerNode *m_c; // 0x0c
    bool m_10; // 0x10
    undefined m_11[3]; // 0x11
    int m_14; // 0x14
    undefined m_18[0xc]; // 0x18
};

class RHMobilePosition;

#include "RHUnk0042fde0.h"

class RHMobileUnk0051fd90
{
public:
    void FUN_0051fd90(float first, float second);
    char m_0[0x24];
    float m_24;
    float m_28;
    float m_2c;
    float m_30;
};

class RHMobileUnk00520c50
{
public:
    void FUN_00520c50(float first, float second);
    char m_0[0x24];
    float m_24;
    float m_28;
    float m_2c;
    float m_30;
};

#include "RHMobileUnk006091b0.h"

class RHMobileUnk006100e0;

#include "RHMobileSegmentCalls.h"

class RHMobilePointAllocator
{
public:
    void deallocate(SBGeoPoint2D *pointer, unsigned)
    {
        operator delete(pointer);
    }
};

class RHMobilePointStorage
{
public:
    ~RHMobilePointStorage()
    {
        Destroy(m_4, m_8);
        m_0.deallocate(m_4, m_c - m_4);
        m_4 = 0;
        m_8 = 0;
        m_c = 0;
    }

    void Destroy(SBGeoPoint2D *first, SBGeoPoint2D *last)
    {
        for (; first != last; ++first)
            first->FUN_0044e990(0);
    }

    SBGeoPoint2D *begin() { return m_4; }
    SBGeoPoint2D *end() { return m_8; }

    static SBGeoPoint2D *Copy(SBGeoPoint2D *first, SBGeoPoint2D *last, SBGeoPoint2D *destination)
    {
        for (; first != last; ++destination, ++first)
            *destination = *first;
        return destination;
    }

    SBGeoPoint2D *Erase(SBGeoPoint2D *first, SBGeoPoint2D *last)
    {
        SBGeoPoint2D *destination = Copy(last, end(), first);
        Destroy(destination, end());
        m_8 = destination;
        return first;
    }

    RHMobilePointAllocator m_0;
    SBGeoPoint2D *m_4;
    SBGeoPoint2D *m_8;
    SBGeoPoint2D *m_c;
};

class RHMobileUnk00611360 : public RHMobilePointStorage
{
public:
    RHMobileUnk00611360();
    ~RHMobileUnk00611360() { Erase(begin(), end()); }
    void FUN_00611360(const SBGeoPoint2D &value);
    unsigned short Size() const { SBGeoPoint2D *first = *(SBGeoPoint2D *volatile *)&m_4; if (!first) return 0; return (unsigned short)(m_8 - first); }
    int m_10;
    bool m_14;
    undefined m_18[4];
    SBGeoPoint2D m_1c;
};

class RHMobileUnk004b06f0
{
public:
    unsigned FUN_004afd50() const;
    RHUnk005fc3b0 *FUN_004afd70(RHUnk005fc3b0 *position, const RHUnk005fc3b0 &value);
    void FUN_004b01b0(RHUnk005fc3b0 *position, unsigned count, const RHUnk005fc3b0 &value);
    RHUnk005fc3b0 *FUN_004b04d0(RHUnk005fc3b0 *first, RHUnk005fc3b0 *last, RHUnk005fc3b0 *destination);
    void FUN_004b0510(RHUnk005fc3b0 *first, unsigned count, const RHUnk005fc3b0 &value);
    void FUN_004aff00(RHUnk005fc3b0 *first, RHUnk005fc3b0 *last);
    unsigned Size() const { return m_4 == 0 ? 0 : m_8 - m_4; }
    RHUnk005fc3b0 *FUN_004b06f0(RHUnk005fc3b0 *first, RHUnk005fc3b0 *last);
    int m_0;
    RHUnk005fc3b0 *m_4;
    RHUnk005fc3b0 *m_8;
    RHUnk005fc3b0 *m_c;
};

void FUN_004b0620(RHUnk005fc3b0 *destination, const RHUnk005fc3b0 &value);
void FUN_004b05b0(RHUnk005fc3b0 *first, RHUnk005fc3b0 *last, const RHUnk005fc3b0 &value);
void FUN_004b05e0(RHUnk005fc3b0 *first, RHUnk005fc3b0 *last, RHUnk005fc3b0 *destination);

#include "RHMobileUnk00607da0.h"

#include "RHMobileUnk006100e0.h"

class RHSoundSource;
class RHMobileUnk005b4fa0
{
public:
    int FUN_005b4fa0(RHSoundSource *value);
    char m_0[8];
    RHSoundSource **m_8;
    RHSoundSource **m_c;
    char m_10[4];
    RHSoundSource **m_14;
    bool m_18;
    bool m_19;
    char m_1a[2];
    int m_1c;
    RHSoundSource *m_20;
};

// SIZE 0x1c
struct RHMobileNode005504d0
{
    RHMobileNode005504d0 *next; // 0x00
    RHMobileNode005504d0 *previous; // 0x04
    undefined m_8[0x14]; // 0x08
};

// SIZE 0x20
class RHMobileUnk005504d0
{
public:
    RHMobileUnk005504d0();
    bool m_0; // 0x00
    bool m_1; // 0x01
    bool m_2; // 0x02
    undefined m_3; // 0x03
    undefined4 m_4; // 0x04
    unsigned short m_8; // 0x08
    undefined m_a[2]; // 0x0a
    undefined m_c; // 0x0c
    undefined m_d[3]; // 0x0d
    RHMobileNode005504d0 *m_10; // 0x10
    unsigned m_14; // 0x14
    undefined4 m_18; // 0x18
    bool m_1c; // 0x1c
};

class RHSoundPendingData
{
public:
    void FUN_0052c5a0();
};

class RHMobileUnk005a5960
{
public:
    void FUN_005a5960(const SBGeoPoint2D &value);
    undefined m_0[0x1a8]; // 0x00
};

#include "RHPlaneCalls.h"
typedef RHUnk005df860 RHMobileUnk005dfaa0;

struct RHMobilePointNode
{
    RHMobilePointNode *next; // 0x00
    RHMobilePointNode *previous; // 0x04
    SBGeoPoint2D value; // 0x08
};

struct RHMobilePointIterator
{
    RHMobilePointNode *node;
};

class RHMobilePointList
{
public:
    __forceinline void FUN_005c8e40(int index) { ((RHSectorActorList *)this)->Unk005c8e40(index); }
    RHMobilePointIterator FUN_0046eb80();
    static void FUN_005c9010(RHMobilePointNode *&node, int distance, unsigned count);
    void GoToInline(int index, unsigned count)
    {
        int size = m_8;
        if (m_10)
        {
            if (index <= (size + 1) / 2)
            {
                m_c = m_4->next;
                FUN_005c9010(m_c, index, count);
            }
            else
            {
                m_c = m_4;
                FUN_005c9010(m_c, index - size, count);
            }
            m_10 = false;
        }
        else
        {
            int current = m_14;
            if (index == current)
                return;
            if (index < current)
            {
                if (index < (current + 1) / 2)
                {
                    m_c = FUN_0046eb80().node;
                    FUN_005c9010(m_c, index, count);
                }
                else
                    FUN_005c9010(m_c, index - current, count);
            }
            else if (index < (current + size) / 2)
                FUN_005c9010(m_c, index - current, count);
            else
            {
                m_c = m_4;
                FUN_005c9010(m_c, index - size, count);
            }
        }
        m_14 = index;
    }
    undefined4 m_0; // 0x00
    RHMobilePointNode *m_4; // 0x04
    unsigned m_8; // 0x08
    RHMobilePointNode *m_c; // 0x0c
    bool m_10; // 0x10
    undefined m_11[3]; // 0x11
    int m_14; // 0x14
};

// SIZE 0x24
struct RHMobileSoundNode
{
    RHMobileSoundNode *next; // 0x00
    RHMobileSoundNode *previous; // 0x04
    int m_8; // 0x08
    undefined m_c[0x10]; // 0x0c
    void *m_1c; // 0x1c
    int m_20; // 0x20
};

#include "RHSoundCore.h"

#include "SBGeoBoundingBox2DCore.h"
#include "RHPositionInterface.h"

class RHMobileElementBase
{
public:
    RHMobileElementBase(int type, int value);
    virtual ~RHMobileElementBase();
    undefined m_04[0xb0]; // 0x04
};

// VTABLE: GAME 0x006784a0
// SIZE 0xfc
class RHMobileBase004a8130 : public RHMobileElementBase
{
public:
    RHMobileBase004a8130(int type);
    virtual ~RHMobileBase004a8130(); // vtable+0x00
    virtual void v1(); // vtable+0x04
    virtual void v2(); // vtable+0x08
    virtual void v3(); // vtable+0x0c
    virtual void v4(); // vtable+0x10
    virtual void v5(); // vtable+0x14
    virtual void v6(); // vtable+0x18
    virtual void v7(); // vtable+0x1c
    virtual void v8(); // vtable+0x20
    virtual void v9(); // vtable+0x24
    virtual void v10(); // vtable+0x28
    virtual void v11(); // vtable+0x2c
    virtual void v12(); // vtable+0x30
    virtual void v13(); // vtable+0x34
    virtual void v14(SBFile &file); // vtable+0x38
    virtual void v15(); // vtable+0x3c
    virtual bool v16(SBFile &file); // vtable+0x40
    virtual void v17(bool value); // vtable+0x44
    virtual void v18(); // vtable+0x48
    virtual void v19(); // vtable+0x4c
    virtual void v20(); // vtable+0x50
    virtual void v21(); // vtable+0x54
    virtual void v22(); // vtable+0x58
    virtual void v23(); // vtable+0x5c
    virtual void v24(); // vtable+0x60
    virtual void v25(); // vtable+0x64
    SBGeoBoundingBox2D m_b4; // 0xb4
    char m_c8; // 0xc8
    int m_cc; // 0xcc
    char m_d0; // 0xd0
    RHMobileUnk00611360 m_d4; // 0xd4
    undefined m_f8[4]; // 0xf8
};

// VTABLE: GAME 0x00678508
// SIZE 0x104
class RHUnk004aac40 : public RHMobileBase004a8130
{
public:
    RHUnk004aac40();
    virtual ~RHUnk004aac40(); // vtable+0x00
    virtual void v9(); // vtable+0x24
    virtual void v10(); // vtable+0x28
    virtual bool v16(SBFile &file); // vtable+0x40
    float m_fc; // 0xfc
    RHElementMobile *m_100; // 0x100
};

class RHElevationLine
{
public:
    char m_0[4];
    SBGeoPoint2D m_4;
    SBGeoPoint2D m_c;
    unsigned m_14;
    char m_18[0xc];
    void *m_24;
    void *m_28;
};

class RHElement
{
public:
    virtual bool Serialize(SBFile &file);
    void CrossElevationLine(RHElevationLine *line);
};

struct RHScriptNode
{
    RHScriptNode *next;
    RHScriptNode *previous;
    RHElevationLine *data;
};

struct RHScriptIter
{
    RHScriptNode *node;
    RHScriptIter(RHScriptNode *value) : node(value) {}
};

class RHUnk0046eb30
{
public:
    RHScriptIter erase(RHScriptIter position);
};

void *FUN_0048f170(void *value);

#include "RHTransientPointerList.h"
#include "RHMobileVectorArray.h"
typedef RHTransientPointerList<RHElevationLine> RHMobileLineTransientList;

#include "RHElementMobileCore.h"

// SIZE 0x260
class RHUnk004af060 : public RHElementMobile
{
public:
    void Unk(int direction);
};

extern bool g_mobileAssertDoubleBond;

void RHSerializeName(SBFile &file, const char *name);
class RHEngine
{
public:
    bool FUN_004c3af0(SBFile &file, void *&value);
    bool FUN_004c3f50(SBFile &file, void *&value);
};
extern RHEngine *g_pEngine;
class RHArtificialIntelligenceSoundCalls;
extern RHArtificialIntelligenceSoundCalls *g_unk0x006c1070;
void FUN_005e1d50(SBFile &file, unsigned long tag, int level);
void FUN_005e20c0(SBFile &file);
class RHMobilePointerArray
{
public:
    RHMobilePointerArray();
    ~RHMobilePointerArray();
    void Append(void *value);
    unsigned short Size() const { void **first = *(void **volatile *)&m_4; if (!first) return 0; return (unsigned short)(m_8 - first); }
    undefined4 m_0;
    void **m_4;
    void **m_8;
    void **m_c;
    undefined m_10[4];
    bool m_14;
    undefined m_15[3];
    undefined4 m_18;
    void *m_1c;
};
class RHMobileAreaLoad
{
public:
    RHMobileAreaLoad();
    void FUN_005a3810(SBFile &file, RHMobilePointerArray &materials);
    undefined m_0[0x1a8];
};
class RHArtificialIntelligencePathCursor
{
public:
    void Unk00550f60(unsigned short index);
    void Unk005505b0(unsigned short index);
};
#include "RHActorPositionCalls.h"
class RHBonusInfo
{
public:
    void FUN_005bd560(void *value, bool second);
};
struct RHBonusProjection;

class RHBonusInfoBase
{
public:
    void FUN_0055f290();
    void FUN_0055fa20(RHBonusProjection *projection);
};
class RHMobileEvent
{
public:
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3(int value, bool complete);
    undefined m_4[0xc];
    int m_10;
};
class RHMobilePartCalls
{
public:
    bool FUN_004aafc0(void *value);
    undefined m_00[0x50];
    void *m_50;
    void *m_54;
};
class RHPath
{
public:
    bool SerializeStatus(SBFile &file);
};

inline void RHMobileElement::OffsetPoint(const SBGeoPoint2D &point)
{
    SBGeoVector2D offset((const SBGeoVector2D &)point);
    ((RHMobilePosition *)((char *)m_50 + 4))->FUN_004abf20(offset);
}

#endif
