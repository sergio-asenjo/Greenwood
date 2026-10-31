#ifndef RHFASTFINDGRIDCORE_H
#define RHFASTFINDGRIDCORE_H

#include "Decomp.h"
#include <vector>

class SBFile;
class SBGeoPoint2D;
class SBGeoBoundingBox2D;
class RHMalignitySegment;
class SBGeoPoint3D;
class RHFastFindRepulsive;
class RHUnkMaskObstacleTable;
struct RHFastFindLayer;

struct RHFastFindPointerArray
{
    int m_grow;
    void **m_first;
    void **m_last;
    void **m_end;
    void **m_search;
    bool m_changed;
    bool m_searching;
    int m_index;
    void *m_value;

    void Initialize(const char &allocator)
    {
        *(char *)&m_grow = allocator;
        m_first = 0;
        m_last = 0;
        m_end = 0;
        m_changed = true;
    }
    int size() const { return m_first == 0 ? 0 : m_last - m_first; }
    void **begin() const { return m_first; }
    void **end() const { return m_last; }
    void InsertLast(void *const &value);
    RHFastFindPointerArray &FUN_004ff0a0(const RHFastFindPointerArray &source);
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
    void InitializeMaskFromProtoStream(SBFile &file);
    void Convert2DTo3D(class RHUnk00613e90 &point, const SBGeoPoint2D &position, int type);
    bool IsReachableImpact(const class RHUnk00613e90 &from, const class RHUnk00613e90 &to, class RHUnk00613e90 &impact, void *&obstacle, int type);
    class RHUnk00613e90 PositionToPoint3D(struct RHUnk00571160Position &position);
    void FUN_004faf40(SBFile &file);
    void EmptyAllScriptSectors();
    void FUN_004fc660();
    bool FUN_004fc8f0(void *first, void *second, void *third, void *fourth);
    void *GetPatch(void *value);
    void FUN_004fb1d0(SBFile &file);
    void FUN_004fb230(SBFile &file);
    void FUN_004e8bd0(void *sector, unsigned short layer, bool mode);
    void FUN_004fad80(void *gate);
    void FUN_004ebfe0(void *point, unsigned short layer, bool mode);
    void FUN_004e99e0(void *sector, unsigned short layer, bool mode);
    void FUN_004e9d00(unsigned char enabled, unsigned short layer, void *sector);
    void FUN_004ed690(void *point, unsigned short layer, bool mode);
    void FUN_004ef8e0(class RHUnk005a3450 *area, unsigned short layer, bool mode);
    bool Unk004efbb0(SBFile &file, void **value);
    bool SerializeLinePointer(SBFile &file, void *&value);
    void Emit(SBFile &file, void *&value);

    char m_00[0x3e98];
    unsigned short m_width;
    unsigned short m_height;
    unsigned short m_layerCount;
    char m_3e9e[6];
    RHUnkMaskObstacleTable *m_3ea4;
    char m_3ea8[0x190];
    RHFastFindLayer *m_layers;
    struct RHFastFindCell *m_cells;
    RHFastFindPointerArray m_projectionAreas;
    RHFastFindPointerArray m_sectors;
    RHFastFindPointerArray m_gates;
    RHFastFindPointerArray m_patches;
    char m_40c0[0xf4];
    std::vector<RHFastFindRepulsive> m_repulsivePoints;
    std::vector<unsigned short> m_repulsiveLayers;
};

#endif
