#ifndef RHFASTFINDGRID_H
#define RHFASTFINDGRID_H
#include "RHSectorActorList.h"

#include "SB.h"
#include "Decomp.h"
#include <vector>

class RHSectorBuilding;
#include "RHFastFindGeometry.h"

#include "RHRepulsivePoint.h"

namespace std
{
template <>
void vector<RHUnk00520ae0>::insert(RHUnk00520ae0 *position, unsigned count, const RHUnk00520ae0 &value);
}

class RHSaveGame;
template <class T> class SBArray
{
public:
    void Insert(T *position, unsigned int count, const T &value);
};

#include "RHFastFindGridCore.h"

inline void RHFastFindPointerArray::InsertLast(void *const &value)
{
    ((SBArray<RHSaveGame *> *)this)->Insert((RHSaveGame **)m_last, 1, (RHSaveGame *const &)value);
    m_changed = true;
}

inline void RHFastFindPointerArray::InsertSingleLast(void *const &value)
{
    typedef std::vector<unsigned long> Values;
    unsigned long *(Values::*insert)(unsigned long *, const unsigned long &) = &Values::insert;
    (((Values *)this)->*insert)((unsigned long *)end(), *(const unsigned long *)&value);
    m_changed = true;
}

struct RHFastFindLayer
{
    unsigned short m_00;
    char m_02[2];
    void **m_04;
    unsigned short m_lineCount; // +0x08
    char m_0a[2];
    void **m_lines; // +0x0c
    unsigned short m_sectorCount;
    char m_12[2];
    void **m_14;
    unsigned short m_obstacleCount;
    char m_1a[2];
    void **m_obstacles; // +0x1c
    unsigned short m_20Count;
    char m_22[2];
    void **m_24;
    unsigned short m_pathCount;
    char m_2a[2];
    class RHPatch **m_paths;
    void Destroy();
};

class SBGeoBoundingBox2D;
class RHMalignitySegment;
class RHFastFindSector
{
public:
    virtual void UnkSlot0();
    virtual void UnkSlot4();
    virtual void UnkSlot8();
    virtual void UnkSlotc();
    virtual void UnkSlot10(SBFile &file, RHFastFindGrid *grid);
    char m_04[0x2c];
    unsigned long m_flags; // +0x30
    char m_34[4];
    short m_id; // +0x38
    unsigned short LiftFlag() { return m_flags >> 9; }
    unsigned short SectorFlag() { return m_flags >> 1; }
    unsigned short BaseFlag() { return m_flags; }
};

class RHFastFindSightSector : public RHFastFindSector
{
public:
    char m_3c[0x6c];
    class RHSeqNode *m_head;
    int m_count;
    char m_b0[4];
    bool m_changed;
};

#include "RHPatchClass.h"

class RHFastFindSerializableGate
{
public:
    virtual void UnkSlot0();
    virtual bool UnkSlot4(SBFile &file);
};

class RHFastFindSerializableSector
{
public:
    virtual void UnkSlot0();
    virtual void UnkSlot4();
    virtual void UnkSlot8();
    virtual bool UnkSlotc(SBFile &file);
    char m_04[0x2c];
    unsigned long m_flags;
    unsigned short Flag12() { return m_flags >> 12; }
    unsigned short Flag13() { return m_flags >> 13; }
    unsigned short Flag9() { return m_flags >> 9; }
};

#include "RHPlaneCalls.h"
#include "RHUnk0051f0f0.h"

#include "SBGeoBoundingBox2DCore.h"

class RHFastFindLine : public RHUnk0051f0f0
{
public:
    void *FUN_0051f500(unsigned flags);
    RHFastFindLine();
    ~RHFastFindLine();
    int FUN_0051faf0(SBFile &, RHFastFindPointerArray &);
    float FUN_0051f450();
    float FUN_0051f470();
    float FUN_0051f490();
    float FUN_0051f4b0();
    void FUN_0051f530(SBDrawManager *draw, SBGeoBoundingBox2D box, float scale, unsigned short color);
    unsigned short m_20;
    unsigned short m_22;
    void *m_24;
    void *m_28;
};

#include "RHMobileUnk006100e0.h"

#include "RHUnk005a3450.h"

#include "../engine/RHGate.h"

class RHScriptRecordWorld
{
public:
    void Unk004fc8f0(SBGeoPoint2D &first, SBGeoPoint2D &second, const SBGeoPoint2D *destination, unsigned short direction);
};

#include "RHSeqList.h"

class RHSeqIter
{
public:
    void *m_p;
    RHSeqIter(void *value) : m_p(value) {}
};

class RHSequence;
class RHUnkListSeq
{
public:
    RHSeqIter insert(RHSeqIter position, RHSequence *const &value);
};

class RHUnk004e5270 : public RHSeqList
{
public:
    RHUnk004e5270(const char &allocator) : RHSeqList(allocator)
    {
        m_valid = true;
    }
    ~RHUnk004e5270()
    {
        Clear();
        Clear();
        operator delete(m_head);
    }
    void Clear()
    {
        RHSeqNode *node = m_head->m_next;
        while (node != m_head)
        {
            RHSeqNode *removed = node;
            node = node->m_next;
            removed->m_prev->m_next = removed->m_next;
            removed->m_next->m_prev = removed->m_prev;
            operator delete(removed);
            --m_count;
        }
    }
    void InsertLast(void *const &value)
    {
        ((RHUnkListSeq *)this)->insert(RHSeqIter(m_head), (RHSequence *const &)value);
        m_valid = true;
    }
};

#include "RHFastFindArrayOps.h"

inline void RHFastFindGateArray::InsertLast(void *const &value, bool inlineCopy, bool externalSize, bool sourceFirst)
{
    void **position = last;
    if ((unsigned int)(end - last) < 1)
    {
        unsigned int growCount = Size() > 1 ? (externalSize ? FUN_0059fbc0() : Size()) : 1;
        int capacity = (externalSize ? FUN_0059fbc0() : Size()) + growCount;
        void **storage = std::_Allocate(capacity, (void **)0);
        void **destination = storage;
        if (inlineCopy)
        {
            if (sourceFirst)
            {
                for (void **source = first; source != position; ++source, ++destination)
                    RHSeqList::CopyData((RHSequenceElement **)destination, (RHSequenceElement *const *)source);
            }
            else
            {
                for (void **source = first; source != position; ++destination, ++source)
                    RHSeqList::CopyData((RHSequenceElement **)destination, (RHSequenceElement *const *)source);
            }
        }
        else
            destination = Unk004fe420(first, position, storage);
        Unk004fe450(destination, 1, value);
        ++destination;
        Unk004fe420(position, last, destination);
        Unk005008e0(first, last);
        delete[] first;
        end = storage + capacity;
        last = storage + (inlineCopy || externalSize ? FUN_0059fbc0() : Size()) + 1;
        first = storage;
    }
    else if ((unsigned int)(last - position) < 1)
    {
        Unk004fe420(position, last, position + 1);
        Unk004fe450(last, 1 - (last - position), value);
        void **fillEnd = last;
        for (void **destination = position; destination != fillEnd; ++destination)
            *destination = value;
        ++last;
    }
    else
    {
        Unk004fe420(last - 1, last, last);
        void **source = last - 1;
        void **destination = last;
        while (position != source)
            *--destination = *--source;
        for (destination = position; destination != position + 1; ++destination)
            *destination = value;
        ++last;
    }
    dirty = true;
}

#include "RHScriptLocation.h"

#include "RHUnkSectorPoints.h"

#include "RHSectorScript.h"

class RHUnk0051e1e0;

#include "RHJumpSector.h"

class RHUnk0051e1e0 : public RHUnk0051f0f0
{
public:
    void *FUN_0051e200(unsigned flags);
    RHUnk0051e1e0();
    ~RHUnk0051e1e0();
    int Unk0051e230(SBFile &file, RHSeqList &sectors);
    unsigned short GetLayer() const { return m_layer; }
    void *Owner() const { return (void *)m_1c; }
    void SetOwner(void *owner) { m_1c = (unsigned)owner; }
    RHUnk0051e1e0 *m_other;
    void *m_gate;
    RHUnk0051e5e0 *m_sector;
    unsigned short m_layer;
    char m_2e[2];
    float m_30;
    float m_34;
    char m_38;
    bool m_mode;
    char m_3a[2];
};

#define fastfind_lifts (*(RHFastFindPointerArray *)((char *)this + 0x40c0))
#define fastfind_gateObjects (*(RHFastFindGateArray *)((char *)this + 0x4080))
#define fastfind_defaultSector ((RHSector *)m_4184)

class RHProfileFile : public SBFile
{
public:
    int FUN_005f5370(int offset, int origin);
};

void FUN_005e1d50(SBFile &file, unsigned long tag, int level);
void FUN_005e20c0(SBFile &file);
unsigned long FUN_005e1d00(SBFile &file);
void FUN_005e2300(SBFile &file);
void RHSerializeName(SBFile &file, const char *name);

#include "RHFastFindAmbushArray.h"
#include "RHFastFindSeekArray.h"

#include "RHUnkSectorGlobal.h"

inline void *RHFastFindLookup(unsigned short sector)
{
    if (sector == 0xffff)
        return g_unk0x6c0a9c->m_4184;
    return g_unk0x6c0a9c->m_sectors.m_first[sector];
}

class RHUnk005f5440
{
public:
    int Unk();
};

#include "RHSectorCore.h"

#include "RHRepulsivePoint.h"

#include "RHUnk004ff7b0.h"

class RHUnk005223f0
{
public:
    void FUN_005223f0(SBFile &file);
    char m_00[0x14];
};

void FUN_00418390(RHUnk005223f0 *hole);

#include "RHPathGeometryCalls.h"

#endif
