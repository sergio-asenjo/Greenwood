#ifndef RHELEMENTMOBILE_H
#define RHELEMENTMOBILE_H
#include "RHSectorActorList.h"

#include "SB.h"
#include "Decomp.h"
#include "RHPathCore.h"
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
class RHSprite;
#include "RHFastFindGeometry.h"
#include "RHUnk00613e90.h"

#include "RHSpriteLastFrameCalls.h"

class RHUnkTargetSprite
{
public:
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
    char m_0[0x12];
    bool m_12;
    char m_13[0x3d];
    RHSprite *m_50;
    char m_54[0x10];
    short m_64;
    short m_66;
    char m_68[0x94];
    float m_fc;
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
    undefined m_4[0x2c]; // 0x04
    unsigned m_30;
    bool m_34;
    undefined m_35[7];
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

#include "RHSpatialLines.h"

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
        RHMobilePointerNode *link = *(RHMobilePointerNode *volatile *)&node->previous;
        link->next = node;
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

#include "RHElementCore.h"

#include "RHElementFXMasked.h"

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

#include "RHScriptListCore.h"

void *FUN_0048f170(void *value);

#include "RHTransientPointerList.h"
#include "RHMobileVectorArray.h"
typedef RHTransientPointerList<RHElevationLine> RHMobileLineTransientList;

#include "RHElementMobileCore.h"

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
inline void RHMobileElement::OffsetPoint(const SBGeoPoint2D &point)
{
    SBGeoVector2D offset((const SBGeoVector2D &)point);
    ((RHMobilePosition *)((char *)m_50 + 4))->FUN_004abf20(offset);
}

#endif
