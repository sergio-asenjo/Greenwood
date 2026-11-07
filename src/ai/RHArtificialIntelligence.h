#ifndef RHARTIFICIALINTELLIGENCE_H
#define RHARTIFICIALINTELLIGENCE_H
#include "RHSectorActorList.h"

#include "SB.h"
#include "RHSoundActorCalls.h"
#include <iterator>
#include <string>

class RHEngine;
extern RHEngine *g_pEngine;
struct RHUnkSectorGlobal;
extern RHUnkSectorGlobal *g_unk0x6c0a9c;
class SBGeoPoint2D;
#include "RHPathGeometryCalls.h"
void RHSerializeName(SBFile &file, const char *name);
bool FUN_00416b30(void *&value, SBFile &file);

#include "RHScriptListCore.h"

#include "RHSectorActorIterator.h"

class RHSequenceElement;
class RHSeqList
{
public:
    static void CopyData(RHSequenceElement **dst, RHSequenceElement *const *src);
    __forceinline void GoTo(int index) { ((RHSectorActorList *)this)->Unk005c8e40(index); }
};
struct RHTitbitNode;
#include "RHTitbitsCore.h"
struct RHUnk005c9010Iterator;
void FUN_005c9010(RHUnk005c9010Iterator &current, int distance, std::bidirectional_iterator_tag category);

#include "RHArtificialIntelligenceTripleList.h"

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

#include "SBGeoPoint2D.h"
#include "SBGeoVector2D.h"
#include "RHUnk005fc3b0.h"



#include "SBGeoBoundingBox2DCore.h"

#include "SBDrawManagerCore.h"

#include "RHUnk00571160Position.h"

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

#include "RHPathCore.h"

#include "RHArtificialIntelligenceActorCalls.h"

class RHArtificialIntelligenceActor;
std::string FUN_00420d40(int remark);


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

#include "RHSpriteCore.h"

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
    virtual bool V48() = 0;
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

    union
    {
        unsigned m_flags;
        struct
        {
            unsigned m_kind : 5;
            unsigned m_otherFlags : 27;
        };
    };
    char m_08[0x48];
    RHSprite *m_data; // +0x50
};

class RHScriptBatchCalls
{
public:
    void Unk00486f50(void *target, bool flag);
    void Unk00464630();
    void Unk0046bcf0(int first, int second);
    void Unk00419fb0(int value);
    void Unk0040d980(int value);
    void Unk0041ac50();
    void Unk00418bc0();
};

class RHElementActor;

#include "RHArtificialIntelligenceCore.h"

#include "RHStimulus.h"

#endif
