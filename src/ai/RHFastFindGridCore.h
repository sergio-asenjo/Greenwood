#ifndef RHFASTFINDGRIDCORE_H
#define RHFASTFINDGRIDCORE_H

#include "Decomp.h"
#include <vector>

class SBFile;
class SBGeoPoint2D;
class SBGeoBoundingBox2D;
class SBGeoSegment2D;
class RHUnk00613e90;
class RHUnk00520ae0;
class RHUnk004fd7f0;
class RHUnk004fda20;
class RHSector;
struct RHFastFindLayer;

#include "RHFastFindPointerArray.h"
#include "RHTransientPointerList.h"

class RHFastFindGrid
{
public:
    virtual ~RHFastFindGrid();
    void Finalize();
    void FUN_004e8ae0(class RHFastFindUniqueList &output, unsigned short layer, const SBGeoBoundingBox2D &box, unsigned long mask);
    bool FUN_004e9570(const SBGeoPoint2D &point, unsigned short layer);
    void FUN_004ec240(class RHFastFindUniqueList &, unsigned short, const SBGeoBoundingBox2D &, unsigned long);
    void FUN_004ec450(class RHFastFindUniqueList &, unsigned long, unsigned long);
    void FUN_004ec560(class RHFastFindUniqueList &, unsigned short, const SBGeoBoundingBox2D &, unsigned long);
    void FUN_004ec700(class RHFastFindUniqueList &, unsigned short, const SBGeoSegment2D &, unsigned long);
    bool FUN_004ecb50(class RHFastFindUniqueList &, unsigned short, const SBGeoBoundingBox2D &, unsigned long);
    bool FUN_004ecc60(class RHFastFindUniqueList &, class RHFastFindUniqueList &, class RHFastFindUniqueList &, unsigned short, const SBGeoBoundingBox2D &);
    void FUN_004ecf60(class RHFastFindUniqueList &, unsigned long, unsigned long);
    void FUN_004ed070(class RHFastFindUniqueList &, unsigned short, const SBGeoBoundingBox2D &, unsigned long);
    void FUN_004ed370(class RHFastFindUniqueList &, unsigned short, const SBGeoSegment2D &, unsigned long);
    void FUN_004ed9b0(SBFile &);
    void FUN_004eda80(void *value, unsigned short layer, bool mode);
    void FUN_004edcf0(class RHFastFindUniqueList &output, unsigned long cell, unsigned long mask);
    void FUN_004ede00(class RHFastFindUniqueList &output, unsigned short layer, const SBGeoBoundingBox2D &box, void *point);
    void FUN_004ee120(class RHFastFindUniqueList &output, unsigned short layer, const SBGeoBoundingBox2D &box, void *point, undefined4 mode);
    void FUN_004ee470(class RHFastFindUniqueList &output, unsigned short layer, const SBGeoBoundingBox2D &box);
    void FUN_004ee770(RHTransientPointerList<void> &output, unsigned long cell, unsigned long mask);
    void FUN_004ee880(class RHFastFindUniqueList &output, unsigned short layer, const SBGeoBoundingBox2D &box, unsigned long mask);
    void FUN_004eea50(class RHFastFindUniqueList &output, unsigned short layer, const SBGeoSegment2D &segment, unsigned long mask);
    void FUN_004eec20(class RHFastFindUniqueList &output, unsigned short layer, const SBGeoBoundingBox2D &box, unsigned long mask);
    void FUN_004eef30(class RHFastFindUniqueList &output, unsigned short layer, const SBGeoSegment2D &segment, unsigned long mask);
    void FUN_004efd10(void *patch, unsigned short layer, bool mode);
    bool FUN_004efe40(const RHUnk00613e90 &first, const RHUnk00613e90 &second, float &slope, float &intercept);
    bool FUN_004eff80(const RHUnk00613e90 &first, const RHUnk00613e90 &second, unsigned long mask);
    bool FUN_004f0230(const RHUnk00613e90 &first, const RHUnk00613e90 &second, class RHFastFindUniqueList &found, char mode, char bypassCache);
    bool FUN_004f3130(const RHUnk00613e90 &point, float height, RHUnk00613e90 &result, void *&blocker, unsigned long mask);
    bool FUN_004f2d10(const RHUnk00613e90 &point, float height, RHUnk00613e90 &result, void *&blocker, unsigned long mask);
    bool FindAutorizedPositionStraight(SBGeoBoundingBox2D &box, const SBGeoPoint2D &point, unsigned short layer);
    bool Unk004f9170(const SBGeoPoint2D &a, const SBGeoPoint2D &b, unsigned short layer, void *radius);
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
    void ComputeBorderPoint(SBGeoPoint2D *border, SBGeoPoint2D *outside,
                            const SBGeoPoint2D *position, unsigned direction);
    void *GetPatch(void *value);
    void FUN_004fb1d0(SBFile &file);
    void FUN_004fb230(SBFile &file);
    void FUN_004e8bd0(void *sector, unsigned short layer, bool mode);
    void FUN_004fad80(void *gate);
    void FUN_004ebfe0(void *point, unsigned short layer, bool mode);
    void FUN_004e99e0(void *sector, unsigned short layer, bool mode);
    void FUN_004e9d00(unsigned char enabled, unsigned short layer, void *sector);
    void CreateStaticRepulsivePoints(RHSector &sector, unsigned short layer, bool mode);
    void FUN_004ed690(void *point, unsigned short layer, bool mode);
    void FUN_004ef8e0(void *area, unsigned short layer, bool mode);
    bool Unk004efbb0(SBFile &file, void **value);
    bool SerializeLinePointer(SBFile &file, void *&value);
    void Emit(SBFile &file, void *&value);

    // VTABLE: GAME 0x00678b4c
    undefined m_04[0x3e94];
    unsigned short m_width;
    unsigned short m_height;
    unsigned short m_layerCount;
    char m_3e9e[6];
    RHUnk004fd7f0 *m_3ea4;
    RHUnk004fd7f0 *m_layerRecordEnd;
    char m_3eac[8];
    bool m_layerRecordsChanged;
    char m_3eb5[0xcb];
    RHUnk004fda20 *m_cellRecords;
    RHUnk004fda20 *m_cellRecordEnd;
    char m_3f88[8];
    bool m_cellRecordsChanged;
    char m_3f91[0xa7];
    RHFastFindLayer *m_layers;
    struct RHFastFindCell *m_cells;
    RHFastFindPointerArray m_projectionAreas;
    RHFastFindPointerArray m_sectors;
    RHFastFindPointerArray m_gates;
    RHFastFindPointerArray m_patches;
    char m_40c0[0x60];
    RHFastFindPointerArray m_4120;
    char m_4140[0x44];
    void *m_4184;
    char m_4188[0x2c];
    std::vector<RHUnk00520ae0> m_repulsivePoints;
    std::vector<unsigned short> m_repulsiveLayers;
};

#endif
