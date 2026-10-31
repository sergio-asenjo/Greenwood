#ifndef RHPATHFINDERCORE_H
#define RHPATHFINDERCORE_H

#include "Decomp.h"
#include <windows.h>
#include <memory>

class SBFile;
struct RHpathRequest;
struct RHPathRequestNode;
class RHUnkIter;
class RHPathWorkList;
class SBGeoPolyLine2DList;
class SBGeoPoint2D;
class SBGeoBoundingBox2D;
class RHElementActor;
class SBGeoVector2D;

// SIZE 0x18
class RHPathRequestList
{
public:
    RHPathRequestList(const std::allocator<void *> &value = std::allocator<void *>());
    ~RHPathRequestList();
    std::allocator<void *> allocator; // +0x00
    RHPathRequestNode *head; // +0x04
    int count; // +0x08
    RHPathRequestNode *cursor; // +0x0c
    char valid; // +0x10
    undefined padding[3]; // 0x11
    int index; // +0x14
    RHUnkIter FUN_0046eb80();
    RHUnkIter begin();
    RHUnkIter end();
    RHUnkIter insert(RHUnkIter position, RHpathRequest *const &request);
    void clear();
    RHpathRequest *&operator[](int wanted);
    void InsertInline(RHPathRequestNode *node, RHpathRequest *const &request);
    void GoTo(int wanted);
};

// SIZE 0x28
class RHPathFinder
{
public:
    RHPathFinder();
    void AddPathRequest(RHpathRequest *request);
    void FUN_00553760(RHElementActor *actor);
    void FUN_00553850(RHElementActor *actor);
    void FUN_005539a0(RHElementActor *actor);
    static bool FUN_00553a10(const SBGeoPoint2D &point, SBGeoPoint2D &node, unsigned char place, SBGeoVector2D &half, bool forward);
    static SBGeoPoint2D FUN_00553d20(SBGeoPoint2D &point, unsigned char place, SBGeoVector2D &vector);
    bool TurnOn();
    void GetPath(SBGeoPolyLine2DList &path);
    static unsigned char FUN_005568f0(unsigned char place, bool forward);
    static unsigned char FUN_00556920(unsigned char places);
    static float EstimateDistance(SBGeoPoint2D &first, SBGeoPoint2D &last);
    void FUN_00554750();
    void FUN_00556260();
    void FUN_005596d0(const SBGeoBoundingBox2D &bounds, float scale, unsigned short layer);
    void FUN_00559e00(const SBGeoBoundingBox2D &bounds, float scale, unsigned short layer);
    void FUN_005559b0(unsigned short graph, unsigned short node, unsigned short state, RHPathWorkList &list);
    void FUN_00556230(unsigned short graph, unsigned short sector, unsigned short state, RHPathWorkList &list);
    void FUN_00555a10(unsigned short graph, unsigned short node, unsigned state, RHPathWorkList &list);
    void FUN_00552d50(unsigned char speed);
    static unsigned short ConvertSector(unsigned short sector);
    bool Serialize(SBFile &file);
    void Emit(SBFile &file, RHpathRequest *request);

    int m_0; // +0x00
    DWORD m_4; // +0x04: thread id
    HANDLE m_8; // +0x08: thread handle
    int m_c; // +0x0c
    RHPathRequestList m_10; // +0x10, head +0x14, count +0x18
};

#endif
