#ifndef RHARTIFICIALINTELLIGENCE_H
#define RHARTIFICIALINTELLIGENCE_H
#include "RHSectorActorList.h"

#include "SB.h"
#include "RHSoundActorCalls.h"
#include <iterator>
#include <string>

class RHEngine;
extern RHEngine *g_pEngine;
class RHFastFindGrid;
extern RHFastFindGrid *g_unk0x6c0a9c;
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

#ifndef RHRECONNAISSANCEENGINE_VIEW
#define RHRECONNAISSANCEENGINE_VIEW
class RHReconnaissanceEngine
{
public:
    bool Unk004c3cb0(SBFile &file, void *&value);
    bool Unk004c4110(SBFile &file, void *&value);
};
#endif

struct RHArtificialIntelligenceInitialEntry
{
    char m_00[0x30];
    unsigned m_flags; // +0x30
    unsigned short Flag13() { return m_flags >> 13; }
};

#include "RHSpriteCore.h"
#include "RHArtificialIntelligenceActor.h"

class RHScriptBatchCalls
{
public:
    bool Unk0049d560(int action);
    void Unk00486f50(void *target, bool flag);
    void Unk00464630();
    void Unk0046bcf0(int first, int second);
    void Unk00418bc0();
};

class RHElementActor;

#include "RHArtificialIntelligenceCore.h"

#include "RHStimulus.h"

#endif
