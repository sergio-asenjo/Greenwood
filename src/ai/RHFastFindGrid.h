#ifndef RHFASTFINDGRID_H
#define RHFASTFINDGRID_H
#include "RHSectorActorList.h"

#include "SB.h"
#include "Decomp.h"
#include <vector>

class RHSectorBuilding;
#include "RHFastFindGeometry.h"

class RHFastFindRepulsiveBase
{
public:
    virtual ~RHFastFindRepulsiveBase();
    RHFastFindRepulsiveBase &Unk004fdc20(const RHFastFindRepulsiveBase &other);
    char m_04[0x10];
};

class RHFastFindRepulsive : public RHFastFindRepulsiveBase
{
public:
    RHFastFindRepulsive &operator=(const RHFastFindRepulsive &other);
    SBGeoPoint2D m_14; // +0x14
    SBGeoPoint2D m_1c; // +0x1c
    int m_24; // +0x24
    int m_28; // +0x28
    int m_2c; // +0x2c
    int m_30; // +0x30
    char m_34; // +0x34
    char m_35; // +0x35
    char m_36; // +0x36
    char m_37; // +0x37
    char m_38; // +0x38
    unsigned long m_id; // +0x3c

};

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

struct RHFastFindLayer
{
    char m_00[8]; // +0x00
    unsigned short m_lineCount; // +0x08
    char m_0a[2];
    void **m_lines; // +0x0c
    char m_10[0xc];
    void **m_obstacles; // +0x1c
    char m_20[8];
    unsigned short m_pathCount;
    char m_2a[2];
    class RHUnk0054f870 **m_paths;
};

class SBGeoBoundingBox2D;
class RHMalignitySegment;
class SBGeoPoint3D;
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

class RHUnk0054f870
{
public:
    bool Unk0054f870(SBFile &file);
    void Unk00550220();
};

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

class RHUnk004b2190Member
{
public:
    RHUnk004b2190Member();
    ~RHUnk004b2190Member();
    bool Serialize(SBFile &file);
    char m_00[0x40];
};

class SBGeoPoint3D
{
public:
    SBGeoPoint3D(float x, float y, float z);
    float m_x;
    float m_y;
    float m_z;
};

#include "RHPlaneCalls.h"

#include "SBGeoBoundingBox2DCore.h"

class RHMalignitySegment
{
public:
    bool FUN_0060ad50(const SBGeoBoundingBox2D &box);
    undefined m_00[0x10];
};

class RHFastFindLine
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
    undefined m_00[0x2c];
};

#include "RHMobileUnk006100e0.h"

#include "sb3dstuff.h"
#include "RHUnk0060c2c0.h"
#include "RHFastFindSightStorage.h"

class RHUnk005a3450
{
public:
    RHUnk005a3450();
    RHUnk005a3450(int type);
    ~RHUnk005a3450();
    void Unk005a3810(SBFile &file, RHFastFindPointerArray &materials);
    void *Unk005a5780();
    unsigned short ProjectionFlag() { return m_flags >> 2; }
    RHUnk005df860 &FirstPlane() { return m_firstPlane; }
    RHUnk005df860 &SecondPlane() { return m_secondPlane; }
    SBGeoBoundingBox2D &Bounds() { return m_bounds; }
    SBGeoBoundingBox2D &OtherBounds() { return m_otherBounds; }
    void SetLayer(unsigned short layer) { m_layer = layer; }
    void SetSector(unsigned short sector) { m_sector = sector; }
    unsigned long m_flags;
    unsigned long m_id;
    bool m_enabled;
    char m_09[3];
    RHUnk005dfd00 m_box;
    SBGeoBoundingBox2D m_bounds;
    SBGeoBoundingBox2D m_otherBounds;
    RHFastFindSightList<RHFastFindSightVertex> m_vertices;
    RHUnk0060c2c0 m_polygon;
    RHUnk005df860 m_firstPlane;
    RHUnk005df860 m_secondPlane;
    char m_158[2];
    unsigned short m_layer;
    unsigned short m_sector;
    char m_15e[2];
    float m_160;
    float m_164;
    char m_168[8];
    RHFastFindSightList<void *> m_materials;
    void *m_motionArea;
    char m_198[0xe];
    bool m_active;
    char m_1a7;
};

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

class RHUnk00522470
{
public:
    RHUnk00522470();
    ~RHUnk00522470();
    void Unk005224d0(SBFile &file);
    void FUN_00520a90(SBFile &file);
    char m_00[0x20];
    unsigned short m_layer;
    char m_22[6];
};

#include "RHUnkSectorPoints.h"

class RHSectorScript
{
public:
    RHSectorScript();
    ~RHSectorScript();
    bool FUN_0057ff00(RHElementActor *actor);
    void InitializeFromMissionStream(SBFile &file);
    char m_00[0x30];
    unsigned long m_flags;
    char m_34[2];
    unsigned short m_layer;
    char m_38[0x80];
    bool m_active;
    char m_b9[0x3f];
};

class RHUnk0051e1e0;

class RHUnk0051e5e0
{
public:
    RHUnk0051e5e0();
    ~RHUnk0051e5e0();
    void *FUN_0051e630(unsigned flags);
    int Unk0051e700(SBFile &file);
    bool FUN_0051e7b0(unsigned int index, RHElementActor *actor, bool mode);
    void Unk0051e800();
    float FUN_0051e890(RHUnk0051e1e0 *line);
    char m_00[0x36];
    unsigned short m_layer;
    char m_38[0x20];
    RHFastFindPointerArray m_lines;
    char m_78[0x28];
};

class RHFastFindJumpSector
{
public:
    char m_00[0x36];
    unsigned short m_layer;
    char m_38[0x60];
    void *m_98;
};

class RHUnk0051e1e0
{
public:
    void *FUN_0051e200(unsigned flags);
    RHUnk0051e1e0();
    ~RHUnk0051e1e0();
    void Unk0051e230(SBFile &file, RHSeqList &sectors);
    unsigned short GetLayer() const { return m_layer; }
    char m_00[0x1c];
    void *m_owner;
    RHUnk0051e1e0 *m_other;
    void *m_gate;
    RHFastFindJumpSector *m_sector;
    unsigned short m_layer;
    char m_2e[0xa];
    bool m_mode;
    char m_39[3];
};

#define fastfind_lifts (*(RHFastFindPointerArray *)((char *)this + 0x40c0))
#define fastfind_gateObjects (*(RHFastFindGateArray *)((char *)this + 0x4080))
#define fastfind_defaultSector (*(RHFastFindSector **)((char *)this + 0x4184))

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

class RHFastFindTacticalItem
{
public:
    virtual ~RHFastFindTacticalItem();
};

class RHFastFindTacticalArray : public std::vector<RHFastFindTacticalItem *>
{
public:
    RHFastFindTacticalItem **m_search; // +0x10
    bool m_changed; // +0x14
    bool m_searching; // +0x15
    int m_index; // +0x18
    RHFastFindTacticalItem *m_value; // +0x1c
    int GetSize() { return size(); }
    void RemoveAll()
    {
        erase(begin(), end());
        m_changed = true;
    }
};

inline void RHFastFindClearTactical(RHFastFindTacticalArray &array)
{
    int count = array.GetSize();
    for (int i = 0; i < count; ++i)
        delete array[i];
    array.RemoveAll();
}

extern RHFastFindTacticalArray g_unk0x006c06f0;
extern RHFastFindTacticalArray g_unk0x006c0718;

struct RHUnkSectorGlobal
{
    char m_pad0[0x4064];
    void **m_4064;
    char m_pad4068[0x11c];
    void *m_4184;
};

extern RHUnkSectorGlobal *g_unk0x6c0a9c;

inline void *RHFastFindLookup(unsigned short sector)
{
    if (sector == 0xffff)
        return g_unk0x6c0a9c->m_4184;
    return g_unk0x6c0a9c->m_4064[sector];
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

class RHUnkPathGeometry
{
public:
    bool Unk004fbec0(SBFile &file, void *&value);
    bool Unk004fc030(SBFile &file, void *&value);
    bool Unk004fc180(SBFile &file, void *&value);
    bool Unk004fc2d0(SBFile &file, void *&value);
};

#endif
