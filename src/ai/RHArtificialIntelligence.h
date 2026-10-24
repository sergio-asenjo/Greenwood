#ifndef RHARTIFICIALINTELLIGENCE_H
#define RHARTIFICIALINTELLIGENCE_H

#include "SB.h"
#include "RHSoundActorCalls.h"
#include <iterator>
#include <string>

class RHEngine;
extern RHEngine *g_pEngine;
struct RHUnkSectorGlobal;
extern RHUnkSectorGlobal *g_unk0x6c0a9c;
class SBGeoPoint2D;
class RHUnkPathGeometry
{
public:
    bool Unk004f9170(const SBGeoPoint2D &a, const SBGeoPoint2D &b, unsigned short layer, void *radius);
    bool Unk004fbec0(SBFile &file, void *&value);
    bool Unk004fc030(SBFile &file, void *&value);
};
void RHSerializeName(SBFile &file, const char *name);
bool FUN_00416b30(void *&value, SBFile &file);

struct RHScriptNode;
struct RHScriptIter
{
    RHScriptNode *node;
    RHScriptIter(RHScriptNode *value) : node(value) {}
};

#include "RHSectorActorIterator.h"

class RHUnk0046eb30
{
public:
    RHScriptNode *Unk0059f720(RHScriptNode *next, RHScriptNode *previous);
    RHScriptIter begin();
    RHScriptIter FUN_0046eb80();
    RHScriptIter erase(RHScriptIter position);
};
class RHSequenceElement;
class RHSeqList
{
public:
    static void CopyData(RHSequenceElement **dst, RHSequenceElement *const *src);
    void GoTo(int index);
};
struct RHTitbitNode;
class RHTitbitList
{
public:
    void Clear(void *out, RHTitbitNode *first, RHTitbitNode *last);
    void At(int index);
};
struct RHUnk005c9010Iterator;
void FUN_005c9010(RHUnk005c9010Iterator &current, int distance, std::bidirectional_iterator_tag category);

struct RHArtificialIntelligenceElement
{
    char m_00[4];
    unsigned m_flags; // +0x04
};

struct RHArtificialIntelligenceNode
{
    RHArtificialIntelligenceNode *m_next; // +0x00
    RHArtificialIntelligenceNode *m_prev; // +0x04
    RHArtificialIntelligenceElement *m_data; // +0x08
};

struct RHArtificialIntelligenceIterator : std::iterator<std::bidirectional_iterator_tag, RHArtificialIntelligenceElement *>
{
    RHArtificialIntelligenceNode *m_node;
    RHArtificialIntelligenceIterator() {}
    RHArtificialIntelligenceIterator(RHArtificialIntelligenceNode *node) : m_node(node) {}
    RHArtificialIntelligenceIterator &operator=(const RHArtificialIntelligenceIterator &other)
    {
        m_node = other.m_node;
        return *this;
    }
    RHArtificialIntelligenceIterator &operator++() { m_node = m_node->m_next; return *this; }
    RHArtificialIntelligenceIterator &operator--() { m_node = m_node->m_prev; return *this; }
};

class RHArtificialIntelligenceList
{
public:
    int m_allocator; // +0x00
    RHArtificialIntelligenceNode *m_head; // +0x04
    int m_count; // +0x08
    RHArtificialIntelligenceIterator m_current; // +0x0c
    bool m_dirty; // +0x10
    char m_11[3];
    int m_index; // +0x14

    RHArtificialIntelligenceIterator begin()
    {
        RHArtificialIntelligenceNode *head = m_head;
        RHArtificialIntelligenceNode *first = head->m_next;
        return RHArtificialIntelligenceIterator(first);
    }
    RHArtificialIntelligenceIterator end()
    {
        RHArtificialIntelligenceNode *head = m_head;
        return RHArtificialIntelligenceIterator(head);
    }
    RHArtificialIntelligenceIterator erase(RHArtificialIntelligenceIterator first, RHArtificialIntelligenceIterator last)
    {
        RHArtificialIntelligenceIterator result;
        ((RHTitbitList *)this)->Clear(&result, (RHTitbitNode *)first.m_node, (RHTitbitNode *)last.m_node);
        return result;
    }
    void clear()
    {
        erase(begin(), end());
        m_dirty = true;
    }
    RHArtificialIntelligenceIterator insert(RHArtificialIntelligenceIterator position, void *const &value)
    {
        RHArtificialIntelligenceNode *node = position.m_node;
        node->m_prev = (RHArtificialIntelligenceNode *)((RHUnk0046eb30 *)this)->Unk0059f720((RHScriptNode *)node, (RHScriptNode *)node->m_prev);
        node = node->m_prev;
        node->m_prev->m_next = node;
        RHSeqList::CopyData((RHSequenceElement **)&node->m_data, (RHSequenceElement *const *)&value);
        ++m_count;
        return RHArtificialIntelligenceIterator(node);
    }
    void InsertLast(void *const &value)
    {
        insert(end(), value);
        m_dirty = true;
    }
    void GoTo(int wanted)
    {
        int count = m_count;
        if (m_dirty)
        {
            if (wanted <= (count + 1) / 2)
            {
                m_current.m_node = m_head->m_next;
                std::bidirectional_iterator_tag category;
                FUN_005c9010((RHUnk005c9010Iterator &)m_current, wanted, category);
            }
            else
            {
                m_current.m_node = m_head;
                std::bidirectional_iterator_tag category;
                FUN_005c9010((RHUnk005c9010Iterator &)m_current, wanted - count, category);
            }
            m_dirty = false;
            m_index = wanted;
        }
        else
        {
            int previous = m_index;
            if (wanted != previous)
            {
                if (wanted < previous)
                {
                    if (wanted < (previous + 1) / 2)
                    {
                        m_current.m_node = m_head->m_next;
                        std::bidirectional_iterator_tag category;
                        FUN_005c9010((RHUnk005c9010Iterator &)m_current, wanted, category);
                    }
                    else
                    {
                        std::bidirectional_iterator_tag category;
                        FUN_005c9010((RHUnk005c9010Iterator &)m_current, wanted - previous, category);
                    }
                }
                else
                {
                    if (wanted < (previous + count) / 2)
                    {
                        std::bidirectional_iterator_tag category;
                        FUN_005c9010((RHUnk005c9010Iterator &)m_current, wanted - previous, category);
                    }
                    else
                    {
                        m_current.m_node = m_head;
                        int distance = wanted - count;
                        for (; distance > 0; --distance)
                            ++m_current;
                        for (; distance < 0; ++distance)
                            --m_current;
                    }
                }
                m_index = wanted;
            }
        }
    }
    RHArtificialIntelligenceElement *&operator[](int wanted)
    {
        GoTo(wanted);
        return m_current.m_node->m_data;
    }
    RHArtificialIntelligenceElement *&FUN_00423c20(int wanted);
};

struct RHArtificialIntelligencePointerArray
{
    int m_grow; // +0x00
    void **m_first; // +0x04
    void **m_last; // +0x08
    unsigned size()
    {
        void **first = *(void **volatile *)&m_first;
        return first == 0 ? 0 : m_last - first;
    }
    void *operator[](unsigned index) { return m_first[index]; }
    void Find(void *value, unsigned short &index)
    {
        index = 0;
        unsigned count = size();
        while ((*this)[index] != value)
        {
            if (++index >= count)
            {
                index = 0xd431;
                break;
            }
        }
    }
};

struct RHArtificialIntelligenceEngineView
{
    char m_00[0x48d8];
    RHArtificialIntelligencePointerArray m_elements; // +0x48d8: first +0x48dc, last +0x48e0
};

struct RHArtificialIntelligencePosition
{
    int m_00; // +0x00
    int m_04; // +0x04
    void *m_08; // +0x08
    unsigned short m_0c; // +0x0c
};

class SBGeoVector2D;
class SBGeoPoint2D
{
public:
    SBGeoPoint2D();
    SBGeoPoint2D(const SBGeoPoint2D &other);
    ~SBGeoPoint2D();
    SBGeoPoint2D &operator=(const SBGeoPoint2D &other);
    SBGeoVector2D Unk005fc110(const SBGeoPoint2D &other) const;
    SBGeoPoint2D Unk005fc190(const SBGeoPoint2D &other) const;
    SBGeoPoint2D FUN_005fc200(const SBGeoPoint2D &other) const;
    float FUN_005fc700(float scale) const;
    float m_x;
    float m_y;
};

class SBGeoVector2D : public SBGeoPoint2D
{
public:
    SBGeoVector2D();
    SBGeoVector2D(float x, float y);
    SBGeoVector2D(const SBGeoPoint2D &point);
    float FUN_005fc660(const SBGeoPoint2D &point) const;
    ~SBGeoVector2D() {}
    SBGeoVector2D &operator=(const SBGeoVector2D &other);
    SBGeoVector2D(const SBGeoVector2D &other);
};

class RHUnk005fc3b0 : public SBGeoVector2D
{
public:
    RHUnk005fc3b0() {}
    ~RHUnk005fc3b0() {}
    RHUnk005fc3b0 &Unk005fcd40(unsigned char direction, float length);
    RHUnk005fc3b0 &FUN_005fc430(const SBGeoPoint2D &other)
    {
        return (RHUnk005fc3b0 &)SBGeoVector2D::operator=((const SBGeoVector2D &)other);
    }
    unsigned char FUN_005fcc50(float value) const;
};



class SBGeoBoundingBox2D
{
public:
    SBGeoBoundingBox2D();
    SBGeoBoundingBox2D(const SBGeoBoundingBox2D &other);
    SBGeoBoundingBox2D FUN_00417a20();
    int FUN_00609050(const SBGeoPoint2D &first, const SBGeoPoint2D &second);
    SBGeoBoundingBox2D FUN_006090d0(const SBGeoVector2D &other) const;
    SBGeoBoundingBox2D FUN_006092c0(const SBGeoBoundingBox2D &other) const;
    bool Unk00608f30() const;
    SBGeoBoundingBox2D &operator-=(const SBGeoVector2D &offset);
    SBGeoBoundingBox2D &FUN_006091d0(float scale);
    SBGeoPoint2D first;
    SBGeoPoint2D last;
    bool valid;
};

#include "SBDrawManagerCore.h"

struct RHUnk00571160Position
{
    float x;
    float y;
    void *area;
    short layer;
};

#include "RHPositionProvider.h"

struct RHAIPathArray;

class RHArtificialIntelligencePathCursor
{
public:
    void Unk00550f60(unsigned short path);
    void Unk005505b0(unsigned short waypoint);
    RHArtificialIntelligencePathCursor &Unk005505c0();
    RHArtificialIntelligencePathCursor &Unk00550640();
    unsigned char m_current;
    unsigned char m_previous;
    char m_forward;
    char m_03;
    RHAIPathArray *m_path;
    unsigned short m_id;
};

class RHPath
{
public:
    bool SerializeStatus(SBFile &file);
};

#include "RHArtificialIntelligenceActorCalls.h"

class RHArtificialIntelligenceActor;
std::string FUN_00420d40(int remark);

struct RHArtificialIntelligenceTriple
{
    int m_00;
    int m_04;
    int m_08;
};

class RHArtificialIntelligenceTripleList
{
public:
    RHArtificialIntelligenceIterator insert(RHArtificialIntelligenceIterator position, const RHArtificialIntelligenceTriple &value);
};

class RHStimulus;
struct RHArtificialIntelligenceStimulusNode
{
    RHArtificialIntelligenceStimulusNode *m_next;
    RHArtificialIntelligenceStimulusNode *m_previous;
};

class RHArtificialIntelligenceStimulusList
{
public:
    RHArtificialIntelligenceStimulusNode *Unk00424340(RHArtificialIntelligenceStimulusNode *next, RHArtificialIntelligenceStimulusNode *previous);
};

class RHAIUnk0044e8b0
{
public:
    int m_allocator;
    RHArtificialIntelligenceNode *m_head;
    unsigned m_count;
    RHArtificialIntelligenceIterator FUN_0044e8b0(RHArtificialIntelligenceIterator first, RHArtificialIntelligenceIterator last);
};

void FUN_00424470(RHStimulus *destination, const RHStimulus *source);

class RHOrder;
class RHUnkIter
{
public:
    void *m_p;
    RHUnkIter(void *node) : m_p(node) {}
};

class RHUnkList
{
public:
    RHUnkIter insert(RHUnkIter position, RHOrder *const &value);
};

class RHReconnaissanceReport
{
public:
    bool Serialize(SBFile &file);
};

class RHReconnaissanceEngine
{
public:
    bool Unk004c3cb0(SBFile &file, void *&value);
    bool Unk004c4110(SBFile &file, void *&value);
};

struct RHArtificialIntelligenceInitialEntry
{
    char m_00[0x30];
    unsigned m_flags; // +0x30
    unsigned short Flag13() { return m_flags >> 13; }
};

struct RHArtificialIntelligenceInitialData
{
    char m_00[0x24];
    float m_x; // +0x24
    float m_y; // +0x28
    char m_2c[0xb4];
    RHArtificialIntelligenceInitialEntry *m_entry; // +0xe0
};

class RHArtificialIntelligenceActor
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
    virtual void Va0() = 0;
    virtual void Va4() = 0;
    virtual void Va8() = 0;
    virtual void Vac() = 0;
    virtual void Vb0() = 0;
    virtual void Vb4() = 0;
    virtual void Vb8() = 0;
    virtual void Vbc() = 0;
    virtual void Vc0() = 0;
    virtual void Vc4(int value) = 0;
    virtual void Vc8() = 0;
    virtual void Vcc() = 0;
    virtual void Vd0() = 0;
    virtual void Vd4() = 0;
    virtual void Vd8() = 0;
    virtual void Vdc(int value, int first, int second) = 0;
    virtual void Ve0() = 0;
    virtual void Ve4() = 0;
    virtual void Ve8() = 0;
    virtual void Vec() = 0;
    virtual void Vf0() = 0;
    virtual void Vf4() = 0;
    virtual bool Vf8() = 0;
    virtual void Vfc() = 0;
    virtual void V100() = 0;
    virtual void V104() = 0;
    virtual void V108() = 0;
    virtual void V10c() = 0;
    virtual void V110() = 0;
    virtual void V114() = 0;
    virtual void V118() = 0;
    virtual void V11c() = 0;
    virtual void V120() = 0;
    virtual void V124() = 0;
    virtual void V128() = 0;
    virtual void V12c() = 0;
    virtual int V130() = 0;
    virtual void V134() = 0;
    virtual void V138() = 0;
    virtual void V13c() = 0;
    virtual void V140() = 0;
    virtual void V144() = 0;
    virtual void V148() = 0;
    virtual void V14c() = 0;
    virtual void V150() = 0;
    virtual void V154() = 0;
    virtual void V158() = 0;
    virtual void V15c() = 0;
    virtual void V160() = 0;
    virtual void V164() = 0;
    virtual void V168() = 0;
    virtual void V16c() = 0;
    virtual void V170() = 0;
    virtual void V174() = 0;
    virtual void *V178() = 0;

    char m_04[0x4c];
    RHArtificialIntelligenceInitialData *m_data; // +0x50
};

class RHScriptBatchCalls
{
public:
    void Unk00464630();
    void Unk0046bcf0(int first, int second);
    void Unk00419fb0(int value);
    void Unk0040d980(int value);
    void Unk0041ac50();
    void Unk00418bc0();
};

class RHElementActor;
class RHSectorActorList
{
public:
    int Unk004b8f80(RHElementActor *const &value, bool mode);
};

#include "RHArtificialIntelligenceCore.h"

class RHStimulus
{
public:
    bool Serialize(SBFile &file);
    RHStimulus() : m_type(0), m_24(0), m_28(0) {}
    ~RHStimulus() {}
    void Unk004188d0(int value);
    char m_00[0x1c];
    unsigned m_type; // +0x1c
    unsigned m_20; // +0x20
    void *m_24; // +0x24
    char m_28; // +0x28
};

#endif
