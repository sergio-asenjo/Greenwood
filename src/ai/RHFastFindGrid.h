#ifndef RHFASTFINDGRID_H
#define RHFASTFINDGRID_H

#include "SB.h"
#include "Decomp.h"
#include <vector>

class SBGeoPoint2D
{
public:
    SBGeoPoint2D();
    SBGeoPoint2D(const SBGeoPoint2D &);
    SBGeoPoint2D(float x, float y);
    ~SBGeoPoint2D();
    SBGeoPoint2D &operator=(const SBGeoPoint2D &other);
    SBGeoPoint2D Unk005fc190(const SBGeoPoint2D &other) const;
    SBGeoPoint2D Unk005fc110(const SBGeoPoint2D &other) const;
    void Set(short x, short y)
    {
        m_x = (float)x;
        m_y = (float)y;
    }
    float m_x;
    float m_y;
};

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
    RHFastFindRepulsive &FUN_004fdb90(const RHFastFindRepulsive &other);
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

    RHFastFindRepulsive &operator=(const RHFastFindRepulsive &other)
    {
        Unk004fdc20(other);
        m_14 = other.m_14;
        m_1c = other.m_1c;
        m_24 = other.m_24;
        m_28 = other.m_28;
        m_2c = other.m_2c;
        m_30 = other.m_30;
        m_34 = other.m_34;
        m_35 = other.m_35;
        m_36 = other.m_36;
        m_37 = other.m_37;
        m_38 = other.m_38;
        m_id = other.m_id;
        return *this;
    }
};

class RHSaveGame;
template <class T> class SBArray
{
public:
    void Insert(T *position, unsigned int count, const T &value);
};

struct RHFastFindPointerArray
{
    int m_grow; // +0x00
    void **m_first; // +0x04
    void **m_last; // +0x08
    void **m_end; // +0x0c
    void **m_search; // +0x10
    bool m_changed; // +0x14
    bool m_searching; // +0x15
    int m_index; // +0x18
    void *m_value; // +0x1c

    void Initialize(const char &allocator)
    {
        *(char *)&m_grow = allocator;
        m_first = 0;
        m_last = 0;
        m_end = 0;
        m_changed = true;
    }

    int size() const { return m_first == 0 ? 0 : m_last - m_first; }
    void InsertLast(void *const &value)
    {
        ((SBArray<RHSaveGame *> *)this)->Insert((RHSaveGame **)m_last, 1, (RHSaveGame *const &)value);
        m_changed = true;
    }
    long Find(void *const &value)
    {
        m_changed = false;
        m_value = value;
        int count = size();
        m_search = m_first;
        int index = 0;
        m_searching = true;
        for (; index < count; ++index, ++m_search)
            if (*m_search == m_value)
                break;
        m_index = index < count ? index : -1;
        return m_index;
    }
};

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
class RHFastFindGrid
{
public:
    void FUN_004ec240(class RHFastFindUniqueList &, unsigned short, const SBGeoBoundingBox2D &, unsigned long);
    void FUN_004ec450(class RHFastFindUniqueList &, unsigned long, unsigned long);
    void FUN_004ec560(class RHFastFindUniqueList &, unsigned short, const SBGeoBoundingBox2D &, unsigned long);
    void FUN_004ec700(class RHFastFindUniqueList &, unsigned short, const RHMalignitySegment &, unsigned long);
    bool FUN_004ecb50(class RHFastFindUniqueList &, unsigned short, const SBGeoBoundingBox2D &, unsigned long);
    bool FUN_004ecc60(class RHFastFindUniqueList &, class RHFastFindUniqueList &, class RHFastFindUniqueList &, unsigned short, const SBGeoBoundingBox2D &);
    void FUN_004ecf60(class RHFastFindUniqueList &, unsigned long, unsigned long);
    void FUN_004ed070(class RHFastFindUniqueList &, unsigned short, const SBGeoBoundingBox2D &, unsigned long);
    void FUN_004ed370(class RHFastFindUniqueList &, unsigned short, const RHMalignitySegment &, unsigned long);
    void FUN_004ed9b0(SBFile &);
    void FUN_004eda80(void *value, unsigned short layer, bool mode);
    void FUN_004edcf0(class RHFastFindUniqueList &output, unsigned long cell, unsigned long mask);
    void FUN_004ede00(class RHFastFindUniqueList &output, unsigned short layer, const SBGeoBoundingBox2D &box, void *point);
    void FUN_004ee120(class RHFastFindUniqueList &output, unsigned short layer, const SBGeoBoundingBox2D &box, void *point, undefined4 mode);
    void FUN_004ee470(class RHFastFindUniqueList &output, unsigned short layer, const SBGeoBoundingBox2D &box);
    void FUN_004ee770(class RHFastFindUniqueList &output, unsigned long cell, unsigned long mask);
    void FUN_004ee880(class RHFastFindUniqueList &output, unsigned short layer, const SBGeoBoundingBox2D &box, unsigned long mask);
    void FUN_004eea50(class RHFastFindUniqueList &output, unsigned short layer, const RHMalignitySegment &segment, unsigned long mask);
    void FUN_004eec20(class RHFastFindUniqueList &output, unsigned short layer, const SBGeoBoundingBox2D &box, unsigned long mask);
    void FUN_004eef30(class RHFastFindUniqueList &output, unsigned short layer, const RHMalignitySegment &segment, unsigned long mask);
    void FUN_004efd10(void *patch, unsigned short layer, bool mode);
    bool FUN_004efe40(const SBGeoPoint3D &first, const SBGeoPoint3D &second, float &slope, float &intercept);
    class RHFastFindPathGate *FUN_004f9d60(class RHElementActor *, const SBGeoPoint2D &, void *, unsigned short, const SBGeoPoint2D &, void *, unsigned, int);
    bool FUN_004fa080(class RHFastFindUniqueList &, class RHElementActor *, const SBGeoPoint2D &, void *, unsigned short, class RHFastFindPathGate *, int);
    class RHFastFindPathGate *FUN_004fa340(class RHElementActor *, const SBGeoPoint2D &, void *, unsigned short, class RHFastFindPathGate *, int);
    void FUN_004fa660();
    void FUN_004fa6f0(void *);
    void InitializeLiftsFromProtoStream(SBFile &file);
    void InitializeBuildingsFromProtoStream(SBFile &file);
    void DeleteStaticRepulsivePoint(unsigned long id);
    void InitializeSightObstaclesFromProtoStream(SBFile &file);
    bool Serialize(SBFile &file);
    void InitializeTacticalInfosFromMissionStream(SBFile &file);
    void InitializeReinforcementPointsFromMissionStream(SBFile &file);
    void InitializeJumpStuffFromProtoStream(SBFile &file);
    void InitializeScriptStuffFromMissionStream(SBFile &file);
    void FUN_004faf40(SBFile &file);
    void FUN_004fc590();
    void FUN_004fc660();
    bool FUN_004fc8f0(void *first, void *second, void *third, void *fourth);
    bool FUN_004fcfd0(void *value);
    void FUN_004fb1d0(SBFile &file);
    void FUN_004fb230(SBFile &file);
    void FUN_004e8bd0(void *sector, unsigned short layer, bool mode);
    void FUN_004fad80(void *gate);
    void FUN_004ebfe0(void *point, unsigned short layer, bool mode);
    void FUN_004e99e0(void *sector, unsigned short layer, bool mode);
    void FUN_004ed690(void *point, unsigned short layer, bool mode);
    void FUN_004ef8e0(class RHUnk005a3450 *area, unsigned short layer, bool mode);
    bool Unk004efbb0(SBFile &file, void **value);
    bool SerializeLinePointer(SBFile &file, void *&value);
    void Emit(SBFile &file, void *&value);

    char m_00[0x3e98];
    unsigned short m_width;
    unsigned short m_height;
    unsigned short m_layerCount; // +0x3e9c
    char m_3e9e[0x19a];
    RHFastFindLayer *m_layers; // +0x4038
    struct RHFastFindCell *m_cells;
    RHFastFindPointerArray m_projectionAreas; // +0x4040
    RHFastFindPointerArray m_sectors; // +0x4060
    RHFastFindPointerArray m_gates; // +0x4080
    RHFastFindPointerArray m_patches; // +0x40a0
    char m_40c0[0xf4];
    std::vector<RHFastFindRepulsive> m_repulsivePoints; // +0x41b4; first +0x41b8, last +0x41bc
    std::vector<unsigned short> m_repulsiveLayers; // +0x41c4; first +0x41c8, last +0x41cc
};

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

class RHUnk005df860
{
public:
    void Unk005df860(const SBGeoPoint3D &first, const SBGeoPoint3D &second, const SBGeoPoint3D &third);
    void FUN_005df8b0();
    void FUN_005df900();
    void FUN_005df9a0();
    void FUN_005df9c0();
    void Unk005dfa00();
    char m_00[0x58];
};

class SBGeoBoundingBox2D
{
public:
    SBGeoBoundingBox2D();
    ~SBGeoBoundingBox2D() {}
    void Unk00607dc0(const SBGeoPoint2D &point);
    void FUN_00607e30(const class RHMalignitySegment &segment);
    bool FUN_00608400(const SBGeoPoint2D &) const;
    SBGeoPoint2D FUN_00608f40() const;
    int FUN_00609050(const SBGeoPoint2D &first, const SBGeoPoint2D &second);
    SBGeoBoundingBox2D &operator=(const SBGeoBoundingBox2D &other);
    SBGeoPoint2D m_first;
    SBGeoPoint2D m_second;
    char m_10[4];
};

class RHMalignitySegment
{
public:
    bool FUN_0060ad50(const SBGeoBoundingBox2D &box);
    undefined m_00[0x10];
};

class RHFastFindLine
{
public:
    RHFastFindLine();
    ~RHFastFindLine();
    void FUN_0051faf0(SBFile &, RHFastFindPointerArray &);
    float FUN_0051f450();
    float FUN_0051f470();
    float FUN_0051f490();
    float FUN_0051f4b0();
    undefined m_00[0x2c];
};

class RHMobileUnk006100e0 : public SBGeoPoint2D
{
public:
    RHMobileUnk006100e0(const RHMobileUnk006100e0 &);
    ~RHMobileUnk006100e0();
    undefined m_08[8];
};

class RHFastFindSegmentCalls
{
public:
    bool FUN_0060a990(const RHMalignitySegment &);
};

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
    char m_04[0x20];
    SBGeoBoundingBox2D m_bounds;
    SBGeoBoundingBox2D m_otherBounds;
    char m_4c[0x5c];
    RHUnk005df860 m_firstPlane;
    RHUnk005df860 m_secondPlane;
    char m_158[2];
    unsigned short m_layer;
    unsigned short m_sector;
    char m_15e[0x36];
    void *m_motionArea;
    char m_198[0xe];
    bool m_active;
    char m_1a7;
};

class RHUnk0057e4d0 : public RHFastFindSector
{
public:
    RHUnk0057e4d0();
    ~RHUnk0057e4d0();
    char m_3c[0xe0];
};

class RHElementActor;

// SIZE 0x94
class RHUnk0051a5e0
{
public:
    RHUnk0051a5e0();
    ~RHUnk0051a5e0();
    virtual bool FUN_0051abe0(bool, RHElementActor *, bool, bool, bool); // vtable+0x00
    virtual bool Serialize(SBFile &file); // vtable+0x04
    undefined m_04[8]; // +0x04
    RHFastFindSector *m_0c; // +0x0c
    RHFastFindSector *m_10; // +0x10
    unsigned short m_14; // +0x14
    short m_16; // +0x16
    SBGeoPoint2D m_18; // +0x18
    SBGeoPoint2D m_20; // +0x20
    undefined m_28[0x60]; // +0x28
    int m_88; // +0x88
    undefined m_8c[8]; // +0x8c
};

// VTABLE: GAME 0x006790a4
// SIZE 0xbc
class RHUnk0051aa00 : public RHUnk0051a5e0
{
public:
    RHUnk0051aa00();
    ~RHUnk0051aa00();
    virtual bool FUN_0051abe0(bool, RHElementActor *, bool, bool, bool); // vtable+0x00
    virtual bool Serialize(SBFile &file); // vtable+0x04
    virtual bool FUN_0051b870(bool, RHElementActor *, bool, bool, bool); // vtable+0x08
    virtual bool FUN_0057cd50(undefined4); // vtable+0x0c
    void Unk0051b2a0(SBFile &file, bool mode);
    SBGeoPoint2D m_94; // +0x94
    int m_9c; // +0x9c
    int m_a0; // +0xa0
    int m_a4; // +0xa4
    int m_a8; // +0xa8
    undefined m_ac[4]; // +0xac
    int m_b0; // +0xb0
    undefined m_b4[8]; // +0xb4
};

class RHScriptRecordWorld
{
public:
    void Unk004fc8f0(SBGeoPoint2D &first, SBGeoPoint2D &second, const SBGeoPoint2D *destination, unsigned short direction);
};

class RHSequenceElement;
class RHSeqNode
{
public:
    RHSeqNode *m_next;
    RHSeqNode *m_prev;
    RHSequenceElement *m_data;
};

class RHSeqList
{
public:
    RHSeqList(const char &allocator);
    static void CopyData(RHSequenceElement **destination, RHSequenceElement *const *source);
    void GoTo(int index);
    char m_00[4];
    RHSeqNode *m_head;
    int m_count;
    RHSeqNode *m_current;
    bool m_valid;
    char m_11[3];
    int m_index;
};

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
    void Unk004fe450(void **destination, unsigned int count, void *const &value);
    void Unk005008e0(void **first, void **last);
    unsigned int Size() { return first == 0 ? 0 : last - first; }
};

class RHFastFindGateArray : public RHScriptFXArray
{
public:
    unsigned int FUN_0059fbc0()
    {
        typedef unsigned (std::vector<unsigned long>::*Size)() const;
        Size size = &std::vector<unsigned long>::size;
        return (((const std::vector<unsigned long> *)this)->*size)();
    }
    void InsertLast(void *const &value, bool inlineCopy = true, bool externalSize = false, bool sourceFirst = false)
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
};

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

class RHUnkSectorPoints
{
public:
    unsigned int Unk0060ce80();
    SBGeoPoint2D &Unk0060cef0(unsigned int index);
};

class RHSectorScript
{
public:
    RHSectorScript();
    ~RHSectorScript();
    void InitializeFromMissionStream(SBFile &file);
    char m_00[0x30];
    unsigned long m_flags;
    char m_34[2];
    unsigned short m_layer;
    char m_38[0x80];
    bool m_active;
    char m_b9[0x3f];
};

class RHUnk0051e5e0
{
public:
    RHUnk0051e5e0();
    ~RHUnk0051e5e0();
    void FUN_0057ca80();
    int Unk0051e700(SBFile &file);
    void Unk0051e800();
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
    RHUnk0051e1e0();
    void FUN_0051f0f0();
    ~RHUnk0051e1e0();
    void Unk0051e230(SBFile &file, RHSeqList &sectors);
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

class RHUnk0051b6e0
{
public:
    RHUnk0051b6e0(RHUnk0051e1e0 *first, RHUnk0051e1e0 *second);
    ~RHUnk0051b6e0();
    char m_00[0x90];
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

class RHSector
{
public:
    void Unk0057cd60(SBFile &file, bool mode);
};

class RHUnk005fc3b0 : public SBGeoPoint2D
{
public:
    RHUnk005fc3b0();
    ~RHUnk005fc3b0() {}
    RHUnk005fc3b0 &FUN_005fc430(const SBGeoPoint2D &other);
    float Unk005fc6a0(float value);
};

// SIZE 0x14
class RHUnk005209d0
{
public:
    RHUnk005209d0(int type);
    virtual ~RHUnk005209d0(); // vtable+0x00
    undefined m_04[0x10]; // +0x04
};

// VTABLE: GAME 0x00678b54
// SIZE 0x40
class RHUnk00520ae0 : public RHUnk005209d0
{
public:
    RHUnk00520ae0();
    virtual ~RHUnk00520ae0(); // vtable+0x00
    RHUnk005fc3b0 m_14; // +0x14
    RHUnk005fc3b0 m_1c; // +0x1c
    undefined m_24[0x11]; // +0x24
    undefined m_35; // +0x35
    undefined m_36; // +0x36
    undefined m_37; // +0x37
    undefined m_38; // +0x38
    unsigned long m_id; // +0x3c
};

class RHUnk004ff7b0
{
public:
    void FUN_004ff7b0(unsigned int count, const float &value);
    char m_00[4];
    float *m_first;
};

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
