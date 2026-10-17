#include "SBNullstr.h"
extern "C" __declspec(dllimport) __declspec(noreturn) void __stdcall ExitThread(unsigned long);
#include "RHPathFinder.h"
#include "SBEvent.h"
#include "RHEngineWidenedCalls.h"
#include "RHActorDirectionCalls.h"
#include "RHMovementPathFinderCalls.h"
#include "SBGeoSegment2D.h"
#include <iterator>

struct RHUnk005c9010Iterator;
void FUN_005c9010(RHUnk005c9010Iterator &, int, std::bidirectional_iterator_tag);

inline void RHPathRequestList::GoTo(int wanted)
{
    int size = count;
    if (valid)
    {
        if (wanted <= (size + 1) / 2)
        {
            cursor = head->next;
            std::bidirectional_iterator_tag category;
            FUN_005c9010((RHUnk005c9010Iterator &)cursor, wanted, category);
        }
        else
        {
            cursor = head;
            std::bidirectional_iterator_tag category;
            FUN_005c9010((RHUnk005c9010Iterator &)cursor, wanted - size, category);
        }
        valid = false;
        index = wanted;
    }
    else
    {
        int previous = index;
        if (wanted != previous)
        {
            if (wanted < previous)
            {
                if (wanted < (previous + 1) / 2)
                {
                    cursor = (RHPathRequestNode *)begin().m_p;
                    std::bidirectional_iterator_tag category;
                    FUN_005c9010((RHUnk005c9010Iterator &)cursor, wanted, category);
                }
                else
                {
                    std::bidirectional_iterator_tag category;
                    FUN_005c9010((RHUnk005c9010Iterator &)cursor, wanted - previous, category);
                }
            }
            else if (wanted < (previous + size) / 2)
            {
                std::bidirectional_iterator_tag category;
                FUN_005c9010((RHUnk005c9010Iterator &)cursor, wanted - previous, category);
            }
            else
            {
                cursor = head;
                std::bidirectional_iterator_tag category;
                FUN_005c9010((RHUnk005c9010Iterator &)cursor, wanted - size, category);
            }
            index = wanted;
        }
    }
}

DECOMP_SIZE_ASSERT(SBGeoPoint2D, 0x08)
DECOMP_SIZE_ASSERT(SBGeoBoundingBox2D, 0x14)
DECOMP_SIZE_ASSERT(RHScriptNode, 0x0c)
DECOMP_SIZE_ASSERT(RHScriptIter, 0x04)
DECOMP_SIZE_ASSERT(RHUnk004b1520List, 0x18)
DECOMP_SIZE_ASSERT(RHpathRequest, 0x3c)
DECOMP_SIZE_ASSERT(RHPathRequestList, 0x18)
DECOMP_SIZE_ASSERT(RHPathFinder, 0x28)
DECOMP_SIZE_ASSERT(RHPathWorkList, 0x24)
DECOMP_SIZE_ASSERT(RHMalignityQueryList, 0x24)
DECOMP_SIZE_ASSERT(RHUnk005fc3b0, 0x08)
DECOMP_SIZE_ASSERT(RHPathSearchNode, 0x20)
DECOMP_SIZE_ASSERT(RHPathStateArray, 0x20)
DECOMP_SIZE_ASSERT(RHPathPointList, 0x28)

// GLOBAL: GAME 0x006c0d40
char g_pathStatus;
// GLOBAL: GAME 0x006c0d7c
RHPathSectorConversion *g_pathSectorFirst;
// GLOBAL: GAME 0x006c0d80
RHPathSectorConversion *g_pathSectorLast;
// GLOBAL: GAME 0x006c0d98
RHPathObstacleGrid *g_pathObstacleGrid;
// GLOBAL: GAME 0x006c0da4
char g_pathThreadDone;
// GLOBAL: GAME 0x006c0da8
RHpathRequest *g_currentPathRequest;
// GLOBAL: GAME 0x006c0cb4
RHPathGraphArray **g_pathGraphFirst;
// GLOBAL: GAME 0x006c0cb8
RHPathGraphArray **g_pathGraphLast;
// GLOBAL: GAME 0x006c0dcc
RHPathStateArray *g_pathStates;
// GLOBAL: GAME 0x006c0c78
RHPathPointList g_unk0x006c0c78;
struct RHSpriteGraphEntry;
extern RHSpriteGraphEntry *g_unk0x006c0cd4;
// GLOBAL: GAME 0x006c0d56
undefined2 g_unk0x006c0d56;
// GLOBAL: GAME 0x006c0d70
void *g_unk0x006c0d70;
// GLOBAL: GAME 0x006c0d9c
void *g_unk0x006c0d9c;
// GLOBAL: GAME 0x006c0da0
RHPathGraphArray *g_unk0x006c0da0;
// GLOBAL: GAME 0x006c0db0
RHPathSearchNode *g_unk0x006c0db0;
// GLOBAL: GAME 0x006c0db8
RHUnk005fc3b0 g_unk0x006c0db8;
// GLOBAL: GAME 0x006c0dc0
undefined2 g_unk0x006c0dc0;
// GLOBAL: GAME 0x006c0cf8
RHUnk004b1520List g_pathOpenNodes;

// GLOBAL: GAME 0x006c0ca0
float g_pathShortestDistance;

// STRING: GAME 0x006b15d0
const char g_pathWakeName[] = "Wake up";
// GLOBAL: GAME 0x006c0d48
SBEvent g_pathWakeEvent(g_pathWakeName);
// GLOBAL: GAME 0x006c0d58
CRITICAL_SECTION g_pathCriticalSection;

// deferred: unannotated pending reccmp #534.
RHScriptIter RHUnk004b1520List::FUN_00424410(RHScriptIter position, void *const &value)
{
    RHScriptNode *next = position.node;
    RHScriptNode *previous = next->previous;
    RHScriptNode *node = (RHScriptNode *)operator new(sizeof(RHScriptNode));
    node->next = next ? next : node;
    node->previous = previous ? previous : node;
    next->previous = node;
    node->previous->next = node;
    new (&node->data) void *(value);
    ++m_08;
    return RHScriptIter(node);
}

// Parked: 68.45%, list frame and cleanup scheduling.
// STUB: GAME 0x004f5750
bool RHPathObstacleGrid::FUN_004f5750(SBGeoBoundingBox2D &box, unsigned short sector)
{
    if (!(unsigned char)((RHUnk00608f10 *)&m_3e84)->FUN_00608f10(&box))
        return false;
    RHPathWorkList list;
    ((RHMalignityGridCalls *)this)->FUN_004ed070((RHMalignityQueryList &)list, sector, box, 2);
    bool result = list.count == 0;
    list.clear();
    return result;
}

// Parked: 34.49%, geometry temporaries and cleanup scheduling.
// STUB: GAME 0x004f5890
bool RHPathObstacleGrid::FUN_004f5890(SBGeoBoundingBox2D &box, unsigned short sector)
{
    RHMalignityQueryList list;
    if (!(unsigned char)((RHUnk00608f10 *)&m_3e84)->FUN_00608f10(&box))
    {
        float x;
        float y;
        if (box.last.x < g_unk0x00677488)
            x = -box.first.x;
        else if (m_3e84.last.x < box.first.x)
            x = -(box.last.x - m_3e84.last.x);
        else
            x = 0.0f;
        if (box.last.y < g_unk0x00677488)
            y = -box.first.y;
        else if (m_3e84.last.y < box.first.y)
            y = -(box.last.y - m_3e84.last.y);
        else
            y = 0.0f;
        ((RHMobileUnk006091b0 *)&box)->FUN_006091b0(SBGeoPoint2D(x, y));
    }
    unsigned short iteration = 0;
    do
    {
        ((RHMalignityGridCalls *)this)->FUN_004ed070(list, sector, box, 2);
        unsigned short count = (unsigned short)list.count;
        if (count == 0)
            return true;
        int index = 0;
        while (count != 0)
        {
            ((RHPathQueryCalls *)&list)->FUN_005c8e40(index);
            char *line = (char *)list.cursor->data;
            SBGeoPoint2D *origin = (SBGeoPoint2D *)(line + 4);
            SBGeoVector2D *normal = (SBGeoVector2D *)(line + 0x34);
            if (normal->FUN_005fc660(box.FUN_00608f40().Unk005fc110(*origin)) > g_unk0x00677488)
            {
                float distance = normal->FUN_005fc660(origin->Unk005fc110(box.first));
                if (distance > g_unk0x006787f8)
                    ((RHMobileUnk006091b0 *)&box)->FUN_006091b0(operator*(distance + g_unk0x0067749c, *(SBGeoVector2D *)normal));
                distance = normal->FUN_005fc660(origin->Unk005fc110(box.last));
                if (distance > g_unk0x006787f8)
                    ((RHMobileUnk006091b0 *)&box)->FUN_006091b0(operator*(distance + g_unk0x0067749c, *(SBGeoVector2D *)normal));
                distance = normal->FUN_005fc660(origin->Unk005fc110(SBGeoPoint2D(box.last.x, box.first.y)));
                if (distance > g_unk0x006787f8)
                    ((RHMobileUnk006091b0 *)&box)->FUN_006091b0(operator*(distance + g_unk0x0067749c, *(SBGeoVector2D *)normal));
                distance = normal->FUN_005fc660(origin->Unk005fc110(SBGeoPoint2D(box.first.x, box.last.y)));
                if (distance > g_unk0x006787f8)
                    ((RHMobileUnk006091b0 *)&box)->FUN_006091b0(operator*(distance + g_unk0x0067749c, *(SBGeoVector2D *)normal));
            }
            ++index;
            --count;
        }
        RHScriptNode *node = list.head->next;
        while (node != list.head)
        {
            RHScriptNode *current = node;
            node = node->next;
            current->previous->next = current->next;
            current->next->previous = current->previous;
            operator delete(current);
            --list.count;
        }
        list.valid = true;
        ++iteration;
    } while (iteration < 50);
    return false;
}

// FUNCTION: GAME 0x00552d50
void RHPathFinder::FUN_00552d50(unsigned char speed)
{
    switch (speed)
    {
    case 0:
        if (m_c != 0)
            SetThreadPriority(m_8, THREAD_PRIORITY_HIGHEST);
        break;
    case 1:
        if (m_c != 1 && m_c != 2)
            SetThreadPriority(m_8, THREAD_PRIORITY_NORMAL);
        break;
    case 2:
        if (m_c != 1 && m_c != 2)
            SetThreadPriority(m_8, THREAD_PRIORITY_NORMAL);
        break;
    case 3:
        if (m_c != 3)
            SetThreadPriority(m_8, THREAD_PRIORITY_LOWEST);
        break;
    }
    m_c = speed;
}

// Parked: 48.73%, frame/register scheduling.
// STUB: GAME 0x00552e00
void RHPathFinder::AddPathRequest(RHpathRequest *request)
{
    SBGeoBoundingBox2D box;
    box = ((RHPathActorInfo *)(*(char **)((char *)request->m_1c + 0x50) + 4))->FUN_00560450();
    if (!g_pathObstacleGrid->FUN_004f5750(box, request->m_0))
    {
        request->m_34 = 1;
        if (!g_pathObstacleGrid->FUN_004f5890(box, request->m_0))
        {
            ((RHUnk0046bcb0 *)request->m_1c)->Unk(8);
            ((RHScriptBatchCalls *)request->m_1c)->Unk00464630();
            SBGeoPoint2D *position = (SBGeoPoint2D *)(*(char **)((char *)request->m_1c + 0x50) + 0x24);
            SBAssert(0,
                     // STRING: GAME 0x006b15b0
                     "P:\\Robin Hood\\RHpathfinder.cpp", 468,
                     // STRING: GAME 0x006b15d8
                     "UNERH\xd6RT : Path request impossible, character cannot be extracted from its obstacle (%f,%f) !",
                     position->x, position->y);
            return;
        }
        request->m_8 = box.FUN_00608f40();
    }
    else
        request->m_34 = 0;
    RHPathRequestList &requests = m_10;
    int count = requests.count;
    if ((unsigned short)count < 2)
        requests.insert(requests.end(), request);
    else
    {
        unsigned short i = (unsigned short)(count - 1);
        for (; (short)i > 0; --i)
        {
            if (requests[(unsigned short)i]->m_2d <= request->m_2d)
            {
                unsigned next = (unsigned short)i + 1;
                if (next == requests.count)
                    requests.insert(requests.end(), request);
                else
                {
                    requests[next];
                    requests.InsertInline(requests.cursor, request);
                }
                break;
            }
        }
        if (i == 0)
        {
            if (g_pathStatus != 4 && g_pathStatus != 3)
                requests.InsertInline(requests.head->next, request);
            else
            {
                if (requests.count == 1)
                    requests.insert(requests.end(), request);
                else
                {
                    requests[1];
                    requests.insert(RHUnkIter(requests.cursor), request);
                }
                if (request->m_2d < m_c)
                    FUN_00552d50(request->m_2d);
            }
        }
    }
}

// Parked: cached-list advance lowering and actor/count register allocation differ.
// STUB: GAME 0x00553100
void RHMovementPathFinderCalls::FUN_00553100(void *actor)
{
    RHPathRequestList &requests = ((RHPathFinder *)this)->m_10;
    int count = requests.count;
    if ((unsigned short)count > 0)
    {
        if (requests.head->next->request->m_1c == actor)
            g_pathThreadDone = 1;
        for (unsigned short index = 1; index < (unsigned short)count; ++index)
        {
            RHpathRequest *request = requests[index];
            if (request->m_1c == actor)
            {
                delete request;
                requests.GoTo(index);
                RHPathRequestNode *node = requests.cursor;
                node->previous->next = node->next;
                node->next->previous = node->previous;
                operator delete(node);
                --requests.count;
                requests.valid = true;
                return;
            }
        }
    }
}

// FUNCTION: GAME 0x00553760
void RHPathFinder::FUN_00553760(RHElementActor *actor)
{
    int count = m_10.count;
    for (unsigned short index = 0; index < (unsigned short)count; ++index)
    {
        RHpathRequest *request = m_10[index];
        if (request->m_1c == actor)
        {
            switch (request->m_28)
            {
            case 6: case 16:
                request->m_28 = 10;
                request->m_24 = ((RHUnk00560410 *)(*(char **)((char *)actor + 0x50) + 4))->FUN_00560410(1);
                break;
            case 20:
                request->m_28 = 298;
                request->m_24 = ((RHUnk00560410 *)(*(char **)((char *)actor + 0x50) + 4))->FUN_00560410(5);
                break;
            case 21:
                request->m_28 = 299;
                request->m_24 = ((RHUnk00560410 *)(*(char **)((char *)actor + 0x50) + 4))->FUN_00560410(5);
                break;
            case 35:
                request->m_28 = 296;
                request->m_24 = ((RHUnk00560410 *)(*(char **)((char *)actor + 0x50) + 4))->FUN_00560410(4);
                break;
            case 38:
                request->m_28 = 297;
                request->m_24 = ((RHUnk00560410 *)(*(char **)((char *)actor + 0x50) + 4))->FUN_00560410(4);
                break;
            case 303:
                request->m_28 = 304;
                request->m_24 = ((RHUnk00560410 *)(*(char **)((char *)actor + 0x50) + 4))->FUN_00560410(1);
                break;
            case 305:
                request->m_28 = 10;
                request->m_24 = ((RHUnk00560410 *)(*(char **)((char *)actor + 0x50) + 4))->FUN_00560410(1);
                break;
            }
            return;
        }
    }
}

// Parked: cached-list cursor reset scheduling and receiver live ranges differ.
// STUB: GAME 0x00553850
void RHPathFinder::FUN_00553850(RHElementActor *actor)
{
    int count = m_10.count;
    for (unsigned short index = 0; index < (unsigned short)count; ++index)
    {
        m_10.GoTo(index);
        RHpathRequest *request = m_10.cursor->request;
        if (request->m_1c == actor)
        {
            if (request->m_28 == 16)
            {
                request->m_28 = 6;
                request->m_24 = ((RHUnk00560410 *)(*(char **)((char *)actor + 0x50) + 4))->FUN_00560410(1);
            }
            return;
        }
    }
}

// Parked: redundant command comparisons are eliminated by the rebuilt compiler.
// STUB: GAME 0x005539a0
void RHPathFinder::FUN_005539a0(RHElementActor *actor)
{
    int count = m_10.count;
    for (unsigned short index = 0; index < (unsigned short)count; ++index)
    {
        RHpathRequest *request = m_10[index];
        if (request->m_1c == actor)
        {
            if (request->m_28 == 6 || request->m_28 == 10)
                request->m_28 = 16;
            else
                request->m_28 = 16;
            request->m_24 = ((RHUnk00560410 *)(*(char **)((char *)actor + 0x50) + 4))->FUN_00560410(10);
            return;
        }
    }
}

// Parked: branch-local zero loads are hoisted and return cleanup tails are reordered.
// STUB: GAME 0x00553a10
bool RHPathFinder::FUN_00553a10(const SBGeoPoint2D &point, SBGeoPoint2D &node, unsigned char place, SBGeoVector2D &half, bool forward)
{
    RHUnk005fc3b0 first;
    RHUnk005fc3b0 second;
    RHUnk005fc3b0 vector;
    vector.FUN_005fc430(point.Unk005fc110(FUN_00553d20(node, place, half)));
    if (forward)
    {
        float zero = g_unk0x00677488;
        switch (place)
        {
        case 1:
            first.y = zero;
            second.x = zero;
            first.x = -1.0f;
            second.y = 1.0f;
            break;
        case 2:
            first.x = zero;
            second.y = zero;
            first.y = -1.0f;
            second.x = -1.0f;
            break;
        case 8:
            first.x = zero;
            second.y = zero;
            first.y = 1.0f;
            second.x = 1.0f;
            break;
        case 4:
            first.y = zero;
            second.x = zero;
            first.x = 1.0f;
            second.y = -1.0f;
            break;
        }
        if (first.FUN_005fc680(vector, 1.0f) >= g_unk0x00677488 ||
            second.FUN_005fc680(vector, 1.0f) < g_unk0x00677488)
            return false;
    }
    else
    {
        float zero = g_unk0x00677488;
        switch (place)
        {
        case 1:
            first.y = zero;
            second.x = zero;
            first.x = 1.0f;
            second.y = -1.0f;
            break;
        case 2:
            first.x = zero;
            second.y = zero;
            first.y = 1.0f;
            second.x = 1.0f;
            break;
        case 8:
            first.x = zero;
            second.y = zero;
            first.y = -1.0f;
            second.x = -1.0f;
            break;
        case 4:
            first.y = zero;
            second.x = zero;
            first.x = -1.0f;
            second.y = 1.0f;
            break;
        }
        if (first.FUN_005fc680(vector, 1.0f) > g_unk0x00677488 ||
            second.FUN_005fc680(vector, 1.0f) <= g_unk0x00677488)
            return false;
    }
    return true;
}

// FUNCTION: GAME 0x00553d20
SBGeoPoint2D RHPathFinder::FUN_00553d20(SBGeoPoint2D &point, unsigned char place, SBGeoVector2D &vector)
{
    SBGeoPoint2D result;
    switch (place)
    {
    case 1:
        result = point.FUN_005fc200(vector);
        break;
    case 2:
        result.x = point.x + vector.x;
        result.y = point.y - vector.y;
        break;
    case 8:
        result.x = point.x - vector.x;
        result.y = point.y + vector.y;
        break;
    case 4:
        result = point.Unk005fc190(vector);
        break;
    }
    return result;
}

// Parked: cached-list reset lowering, iterator temporary slot and count-register allocation differ.
// STUB: GAME 0x00554360
void FUN_00554360(RHPathSearchNode *node)
{
    float distance = *(float *)((char *)node + 0x14);
    unsigned short count = g_pathOpenNodes.m_08;
    if (count == 0)
    {
        RHScriptNode *next = g_pathOpenNodes.m_04->next;
        next->previous = ((RHUnk0046eb30 *)&g_pathOpenNodes)->Unk0059f720(next, next->previous);
        RHScriptNode *created = next->previous;
        created->previous->next = created;
        RHSeqList::CopyData((RHSequenceElement **)&created->data, (RHSequenceElement *const *)&node);
        ++g_pathOpenNodes.m_08;
        g_pathOpenNodes.m_10 = true;
    }
    else
    {
        unsigned short index = 0;
        ((RHTitbitList *)&g_pathOpenNodes)->At(0);
        while (distance > *(float *)((char *)g_pathOpenNodes.m_0c.node->data + 0x14))
        {
            ++index;
            if (index >= count)
                break;
            ((RHTitbitList *)&g_pathOpenNodes)->At(index);
            if (g_pathOpenNodes.m_0c.node->data == node)
                return;
        }
        if ((unsigned)index == g_pathOpenNodes.m_08)
        {
            RHScriptNode *next = g_pathOpenNodes.m_04;
            next->previous = ((RHUnk0046eb30 *)&g_pathOpenNodes)->Unk0059f720(next, next->previous);
            RHScriptNode *created = next->previous;
            created->previous->next = created;
            RHSeqList::CopyData((RHSequenceElement **)&created->data, (RHSequenceElement *const *)&node);
            ++g_pathOpenNodes.m_08;
            g_pathOpenNodes.m_10 = true;
        }
        else
        {
            ((RHPathRequestList *)&g_pathOpenNodes)->GoTo(index);
            g_pathOpenNodes.FUN_00424410(g_pathOpenNodes.m_0c, (void *const &)node);
            g_pathOpenNodes.m_10 = true;
        }
    }
}

// FUNCTION: GAME 0x00554560
void RHPathFinder::GetPath(RHPathPointList &path)
{
    path.FUN_00610ac0();
    unsigned short count = (unsigned short)(unsigned)((RHUnk0053bf20 *)&g_unk0x006c0c78)->FUN_0053bf20();
    if (count > 0)
    {
        int index = 0;
        unsigned remaining = count;
        do
        {
            path.FUN_00610a60(g_unk0x006c0c78.FUN_00610cb0(index));
            ++index;
        } while (--remaining);
    }
    g_pathStatus = 1;
}

// FUNCTION: GAME 0x005545c0
void __stdcall FUN_005545c0(void *)
{
    while (g_pathStatus)
    {
        switch (*(unsigned *)&g_pathStatus & 0xff)
        {
        case 3:
            if (!g_pathWakeEvent.WaitForEvent(INFINITE))
                SBAssert(0, "P:\\Robin Hood\\RHpathfinder.cpp", 0x651,
                    // STRING: GAME 0x006b1638
                    "Pathfinder error : WaitForEvent failed");
            break;
        case 2:
            EnterCriticalSection(&g_pathCriticalSection);
            g_pathStatus = 4;
            LeaveCriticalSection(&g_pathCriticalSection);
            FUN_005547c0(g_currentPathRequest->m_0, g_currentPathRequest->m_4,
                g_currentPathRequest->m_24, g_currentPathRequest->m_8,
                g_currentPathRequest->m_10);
            EnterCriticalSection(&g_pathCriticalSection);
            if (g_pathStatus)
            {
                g_pathStatus = 3;
                LeaveCriticalSection(&g_pathCriticalSection);
                if (!g_pathWakeEvent.WaitForEvent(INFINITE))
                    SBAssert(0, "P:\\Robin Hood\\RHpathfinder.cpp", 0x643,
                        "Pathfinder error : WaitForEvent failed");
            }
            else
                LeaveCriticalSection(&g_pathCriticalSection);
            break;
        case 1:
            if (!g_pathWakeEvent.WaitForEvent(INFINITE))
                SBAssert(0, "P:\\Robin Hood\\RHpathfinder.cpp", 0x65a,
                    "Pathfinder error : WaitForEvent failed");
            break;
        }
    }
    ExitThread(0);
}

// FUNCTION: GAME 0x005546e0
bool RHPathFinder::TurnOn()
{
    if (m_10.count == 0)
        g_pathStatus = 1;
    else
    {
        g_pathStatus = 2;
        RHPathRequestNode *node = *(RHPathRequestNode *volatile *)&m_10.head;
        node = node->next;
        g_currentPathRequest = node->request;
    }
    g_pathThreadDone = 0;
    m_8 = CreateThread(0, 0, (LPTHREAD_START_ROUTINE)0x005545c0, 0, 0, &m_4);
    if (!m_8)
    {
        SBAssert(0,
                 "P:\\Robin Hood\\RHpathfinder.cpp", 1676,
                 // STRING: GAME 0x006b1660
                 "Pathfinder error : Cannot create thread.");
        return false;
    }
    return true;
}

// Parked: the wake-event branch reloads the thread handle in ECX rather than EAX.
// STUB: GAME 0x00554750
void RHPathFinder::FUN_00554750()
{
    EnterCriticalSection(&g_pathCriticalSection);
    if (g_pathStatus != 1 && g_pathStatus != 3)
    {
        g_pathStatus = 0;
        LeaveCriticalSection(&g_pathCriticalSection);
        g_pathThreadDone = 1;
        WaitForSingleObject(m_8, INFINITE);
    }
    else
    {
        g_pathStatus = 0;
        LeaveCriticalSection(&g_pathCriticalSection);
        g_pathWakeEvent.TriggerEvent();
        WaitForSingleObject(m_8, INFINITE);
    }
}

// Parked: 66.54%, receiver scheduling, return cleanup and annotated callees.
// STUB: GAME 0x005547c0
bool FUN_005547c0(unsigned short graph, unsigned short sector, unsigned short direction, const SBGeoPoint2D &first, const SBGeoPoint2D &last)
{
    SBGeoPoint2D previous;
    SBGeoPoint2D middle;
    SBGeoPoint2D current;
    RHUnk005fc3b0 vector;
    g_unk0x006c0dc0 = graph;
    unsigned short converted = RHPathFinder::ConvertSector(sector);
    g_unk0x006c0d9c = g_pathGraphFirst[graph]->first[converted];
    g_unk0x006c0d70 = ((RHPathGraphArray *)g_unk0x006c0da0->first[graph])->first[converted];
    g_unk0x006c0d56 = direction;
    g_unk0x006c0db8.FUN_005fc430(((SBGeoPoint2D *)g_unk0x006c0cd4)[direction]);
    FUN_005557c0();
    g_unk0x006c0c78.FUN_00610ac0();
    if (!FUN_00558210(last))
        return false;
    if (g_currentPathRequest->m_34 && FUN_00557e70(first, last) && FUN_00556990(first, last))
        g_unk0x006c0c78.FUN_00610a60(last);
    else
    {
        FUN_00553e60(first, last);
        RHPathSearchNode *node = FUN_00556490(last);
        g_unk0x006c0db0 = node;
        if (!node)
            return false;
        g_unk0x006c0c78.FUN_00610a00(last);
        unsigned char value = node->m_1c;
        RHPathSearchNode *link = node->m_18;
        while (link)
        {
            value = FUN_00554b80(link, value, g_unk0x006c0c78);
            node = link->m_04;
            link = node->m_18;
        }
        FUN_005553d0(node, node->m_1d, value, g_unk0x006c0c78);
        g_unk0x006c0c78.FUN_00610a00(first);
        unsigned short count = (unsigned short)(unsigned)((RHUnk0053bf20 *)&g_unk0x006c0c78)->FUN_0053bf20();
        if (count > 3)
        {
            previous = g_unk0x006c0c78.FUN_00610cb0(0);
            middle = g_unk0x006c0c78.FUN_00610cb0(1);
            for (unsigned short index = 2; index < count; ++index)
            {
                current = g_unk0x006c0c78.FUN_00610cb0(index);
                vector.FUN_005fc430(operator*(0.00005f, (const SBGeoVector2D &)current.Unk005fc110(previous)));
                if (FUN_00556990(previous.Unk005fc190(vector), current.FUN_005fc200(vector)))
                {
                    g_unk0x006c0c78.FUN_00610b50(index - 1);
                    --count;
                    --index;
                }
                else
                    previous = middle;
                middle = current;
            }
        }
    }
    return true;
}

// Parked: docking-search local packing, layer-load width and branch scheduling differ.
// STUB: GAME 0x005553d0
void FUN_005553d0(RHPathSearchNode *node, unsigned char first, unsigned char last, RHPathPointList &list)
{
    if (!last)
        return;
    unsigned char common = first & last;
    if (common && RHPathFinder::FUN_00556920(common) == 1)
    {
        list.FUN_00610a00(RHPathFinder::FUN_00553d20(*(SBGeoPoint2D *)node, common, (SBGeoVector2D &)g_unk0x006c0db8));
        return;
    }
    if (RHPathFinder::FUN_00556920(last) == 1)
    {
        bool forwardOpen = true;
        bool backwardOpen = true;
        bool found = false;
        bool forward;
        unsigned char clockwise = last;
        unsigned char counterclockwise = last;
        while (!found)
        {
            if (forwardOpen)
            {
                clockwise = RHPathFinder::FUN_005568f0(clockwise, true);
                if (!(clockwise & (*(unsigned char **)((char *)node + 0x80))[g_unk0x006c0d56]))
                    forwardOpen = false;
                else if (first & clockwise)
                {
                    found = true;
                    forward = true;
                    first = clockwise;
                }
            }
            if (backwardOpen)
            {
                counterclockwise = RHPathFinder::FUN_005568f0(counterclockwise, false);
                if (!(counterclockwise & (*(unsigned char **)((char *)node + 0x80))[g_unk0x006c0d56]))
                    backwardOpen = false;
                else if (first & counterclockwise)
                {
                    forward = false;
                    first = counterclockwise;
                    break;
                }
            }
        }
        unsigned char place = last;
        while (place != first)
        {
            list.FUN_00610a00(RHPathFinder::FUN_00553d20(*(SBGeoPoint2D *)node, place, (SBGeoVector2D &)g_unk0x006c0db8));
            place = RHPathFinder::FUN_005568f0(place, forward);
        }
        list.FUN_00610a00(RHPathFinder::FUN_00553d20(*(SBGeoPoint2D *)node, place, (SBGeoVector2D &)g_unk0x006c0db8));
        return;
    }
    unsigned char count = RHPathFinder::FUN_00556920(last);
    unsigned char place = 1;
    unsigned char shortest = 5;
    bool forward;
    unsigned char destination;
    unsigned char source;
    while (count != 0)
    {
        bool forwardOpen = true;
        bool backwardOpen = true;
        bool found = false;
        while (!(last & place))
            place <<= 1;
        unsigned char forwardDistance = 0;
        unsigned char backwardDistance = 0;
        unsigned char clockwise = place;
        unsigned char counterclockwise = place;
        while (!found)
        {
            if (forwardOpen)
            {
                clockwise = RHPathFinder::FUN_005568f0(clockwise, true);
                if (!(clockwise & (*(unsigned char **)((char *)node + 0x80))[g_unk0x006c0d56]))
                    forwardOpen = false;
                else if (first & clockwise)
                {
                    found = true;
                    if (forwardDistance < shortest)
                    {
                        shortest = forwardDistance;
                        forward = true;
                        destination = clockwise;
                        source = place;
                    }
                }
                else
                    ++forwardDistance;
            }
            if (backwardOpen)
            {
                counterclockwise = RHPathFinder::FUN_005568f0(counterclockwise, false);
                if (!(counterclockwise & (*(unsigned char **)((char *)node + 0x80))[g_unk0x006c0d56]))
                    backwardOpen = false;
                else if (first & counterclockwise)
                {
                    if (backwardDistance < shortest)
                    {
                        shortest = backwardDistance;
                        forward = false;
                        destination = counterclockwise;
                        source = place;
                    }
                    break;
                }
                else
                    ++backwardDistance;
            }
        }
        place <<= 1;
        --count;
    }
    unsigned char current = source;
    while (current != destination)
    {
        list.FUN_00610a00(RHPathFinder::FUN_00553d20(*(SBGeoPoint2D *)node, current, (SBGeoVector2D &)g_unk0x006c0db8));
        current = RHPathFinder::FUN_005568f0(current, forward);
    }
    list.FUN_00610a00(RHPathFinder::FUN_00553d20(*(SBGeoPoint2D *)node, current, (SBGeoVector2D &)g_unk0x006c0db8));
}

// Parked: cached-node iterator temporaries, null-count tail and reset-store scheduling differ.
// STUB: GAME 0x005557c0
void FUN_005557c0()
{
    g_unk0x006c0db0 = 0;
    RHScriptNode *last = g_pathOpenNodes.m_04;
    RHSectorActorIter current((RHSectorActorNode *)last->next);
    while (current.m_p != (RHSectorActorNode *)last)
        ((RHUnk0046eb30 *)&g_pathOpenNodes)->erase(RHScriptIter((RHScriptNode *)(current++).m_p));
    g_pathOpenNodes.m_10 = true;
    g_pathShortestDistance = 20000000000.0f;
    RHPathGraphArray *area = (RHPathGraphArray *)g_unk0x006c0d9c;
    unsigned short count = area->size();
    if (count > 0)
    {
        unsigned graph = 0;
        unsigned remainingGraphs = count;
        do
        {
            RHPathRequestList &nodes = *(RHPathRequestList *)((RHPathGraphArray *)g_unk0x006c0d9c)->first[graph];
            unsigned short nodeCount = nodes.count;
            if (nodeCount > 0)
            {
                int index = 0;
                unsigned remainingNodes = nodeCount;
                do
                {
                    nodes.GoTo(index);
                    char *node = (char *)nodes.cursor->request;
                    node[8] = 0;
                    *(float *)(node + 0x0c) = 10000000000.0f;
                    *(float *)(node + 0x10) = 10000000000.0f;
                    *(float *)(node + 0x14) = 20000000000.0f;
                    *(void **)(node + 0x18) = 0;
                    ++index;
                } while (--remainingNodes);
            }
            ++graph;
        } while (--remainingGraphs);
    }
}

// FUNCTION: GAME 0x005559b0
void RHPathFinder::FUN_005559b0(unsigned short graph, unsigned short node, unsigned short state, RHPathWorkList &list)
{
    unsigned value = g_pathStates[graph].first[node];
    unsigned mask = 1 << ((unsigned)state << 1);
    if (value & mask)
        value += mask;
    else
        value -= mask;
    FUN_00555a10(graph, node, value, list);
}

// FUNCTION: GAME 0x00556230
void RHPathFinder::FUN_00556230(unsigned short graph, unsigned short sector, unsigned short state, RHPathWorkList &list)
{
    FUN_005559b0(graph, ConvertSector(sector), state, list);
}

// Parked: 43.31%, list frame/cursor scheduling; unannotated for rule 28.
void RHPathFinder::FUN_00556260()
{
    RHPathWorkList list;
    unsigned short graphs = g_pathGraphFirst ? g_pathGraphLast - g_pathGraphFirst : 0;
    for (unsigned short graph = 0; graph < graphs; ++graph)
    {
        unsigned short count = g_pathGraphFirst[graph]->size();
        for (unsigned short node = 0; node < count; ++node)
            FUN_00555a10(graph, node, g_pathStates[graph].first[node], list);
    }
    list.clear();
}

// Parked: graph-count null tail, register allocation and state-offset induction differ.
// STUB: GAME 0x005563f0
void RHEngineWidenedCalls::FUN_005563f0(unsigned value)
{
    unsigned short graphs = g_pathGraphFirst ? g_pathGraphLast - g_pathGraphFirst : 0;
    if (graphs > 0)
    {
        unsigned graph = 0;
        unsigned remainingGraphs = graphs;
        do
        {
            unsigned short nodes = g_pathGraphFirst[graph]->size();
            if (nodes > 0)
            {
                unsigned node = 0;
                unsigned remainingNodes = nodes;
                do
                {
                    g_pathStates[graph].first[node] = value;
                    ++node;
                } while (--remainingNodes);
            }
            ++graph;
        } while (--remainingGraphs);
    }
}

// FUNCTION: GAME 0x005568f0
unsigned char RHPathFinder::FUN_005568f0(unsigned char place, bool forward)
{
    if (forward)
    {
        if (place == 8)
            return 1;
        return (unsigned)place << 1;
    }
    if (place == 1)
        return 8;
    return (unsigned)place >> 1;
}

// FUNCTION: GAME 0x00556920
unsigned char RHPathFinder::FUN_00556920(unsigned char places)
{
    switch (places)
    {
    case 0:
        return 0;
    case 1: case 2: case 4: case 8:
        return 1;
    case 3: case 5: case 6: case 9: case 10: case 12:
        return 2;
    case 7: case 11: case 13: case 14:
        return 3;
    case 15:
        return 4;
    }
    return 0;
}

inline void RHPathSetVector(RHUnk005fc3b0 &vector, float x, float y)
{
    vector.x = x;
    vector.y = y;
}

struct RHPathMotionSegments
{
    undefined padding[0x2c];
    SBGeoSegment2D *first;
    SBGeoSegment2D *last;
    unsigned size() const
    {
        if (!first)
            return 0;
        return last - first;
    }
    SBGeoSegment2D &operator[](unsigned index)
    {
        SBGeoSegment2D *begin = first;
        return begin[index];
    }
};

// FUNCTION: GAME 0x00557e70
bool FUN_00557e70(const SBGeoPoint2D &first, const SBGeoPoint2D &last)
{
    SBGeoSegment2D segment(SBGeoPoint2D(0.0f, 0.0f), SBGeoPoint2D(0.0f, 0.0f));
    segment.First() = first;
    segment.Second() = last;
    unsigned short count = ((RHPathMotionSegments *)g_unk0x006c0d70)->size();
    for (unsigned short index = 0; index < count; ++index)
        if (segment.IsIntersecting((*(RHPathMotionSegments *)g_unk0x006c0d70)[index]))
            return false;
    return true;
}

// FUNCTION: GAME 0x00557f90
bool FUN_00557f90(const SBGeoPoint2D &point, const void *node)
{
    RHUnk005fc3b0 vector;
    const SBGeoPoint2D &origin = *(const SBGeoPoint2D *)node;
    const RHUnk005fc3b0 &first = *(const RHUnk005fc3b0 *)((const char *)node + 0x6c);
    RHPathSetVector(vector, point.x - g_unk0x006c0db8.x - origin.x, point.y - g_unk0x006c0db8.y - origin.y);
    if (first.FUN_005fc680(vector, 1.0f) > g_unk0x00677488 ||
        ((const RHUnk005fc3b0 *)((const char *)node + 0x74))->FUN_005fc680(vector, 1.0f) > g_unk0x00677488 ||
        (RHPathSetVector(vector, point.x + g_unk0x006c0db8.x - origin.x, point.y - g_unk0x006c0db8.y - origin.y),
            first.FUN_005fc680(vector, 1.0f) > g_unk0x00677488) ||
        ((const RHUnk005fc3b0 *)((const char *)node + 0x74))->FUN_005fc680(vector, 1.0f) > g_unk0x00677488 ||
        (RHPathSetVector(vector, point.x + g_unk0x006c0db8.x - origin.x, point.y + g_unk0x006c0db8.y - origin.y),
            first.FUN_005fc680(vector, 1.0f) > g_unk0x00677488) ||
        ((const RHUnk005fc3b0 *)((const char *)node + 0x74))->FUN_005fc680(vector, 1.0f) > g_unk0x00677488 ||
        (RHPathSetVector(vector, point.x - g_unk0x006c0db8.x - origin.x, point.y + g_unk0x006c0db8.y - origin.y),
            first.FUN_005fc680(vector, 1.0f) > g_unk0x00677488) ||
        ((const RHUnk005fc3b0 *)((const char *)node + 0x74))->FUN_005fc680(vector, 1.0f) > g_unk0x00677488)
        return true;
    return false;
}

// FUNCTION: GAME 0x005581a0
float RHPathFinder::EstimateDistance(SBGeoPoint2D &first, SBGeoPoint2D &last)
{
    return ((RHUnk005fc3b0 *)&last.Unk005fc110(first))->Unk005fc6a0(1.0f);
}

// FUNCTION: GAME 0x00559660
unsigned short RHPathFinder::ConvertSector(unsigned short sector)
{
    unsigned short size = g_pathSectorFirst == 0 ? 0 : g_pathSectorLast - g_pathSectorFirst;
    for (unsigned short i = 0; i < size; ++i)
        if (g_pathSectorFirst[i].source == sector)
            return g_pathSectorFirst[i].destination;
    SBAssert(0, "P:\\Robin Hood\\RHpathfinder.cpp", 5049,
             // STRING: GAME 0x006b168c
             "ConvertSector failed (sector %d)", sector);
    return 0;
}

#define PATH_ACCESS(pointer, size, line) \
    if (file.Access(pointer, size) < 0) \
    { \
        SBString *err = file.GetError(); \
        SBAssert(0, "P:\\Robin Hood\\RHpathfinder.cpp", line, \
                 "Serialize failed reason is %s", err->m_chars ? err->m_chars : ""); \
        return false; \
    }

#define PATH_REQUEST_FIELDS(request, line) \
    PATH_ACCESS(&(request)->m_28, 4, line) \
    PATH_ACCESS(&(request)->m_2c, 1, line + 1) \
    PATH_ACCESS(&(request)->m_34, 1, line + 2) \
    PATH_ACCESS(&(request)->m_30, 4, line + 3) \
    PATH_ACCESS(&(request)->m_2d, 1, line + 4) \
    PATH_ACCESS(&(request)->m_4, 2, line + 5) \
    PATH_ACCESS(&(request)->m_24, 2, line + 6) \
    PATH_ACCESS(&(request)->m_0, 2, line + 7) \
    PATH_ACCESS(&(request)->m_2, 2, line + 8) \
    (request)->m_10.Serialize(file); \
    (request)->m_8.Serialize(file); \
    g_pEngine->FUN_004c3af0(file, (request)->m_1c); \
    g_pEngine->SerializeElementPointer(file, (request)->m_20); \
    ((RHPathSequenceSerializer *)g_unk0x6c1040)->FUN_0058b7c0(file, (request)->m_18);

// Parked: counted begin callee corrected; iterator-result/local scheduling and engine-call residuals remain.
// STUB: GAME 0x0055aa60
bool RHPathFinder::Serialize(SBFile &file)
{
    RHSerializeName(file,
                    // STRING: GAME 0x006b16b0
                    "RHPathFinder");
    unsigned short graphCount = g_pathGraphFirst == 0 ? 0 : g_pathGraphLast - g_pathGraphFirst;
    RHpathRequest *request;
    if (file.m_bLoading)
    {
        FUN_00554750();
        PATH_ACCESS(&g_pathThreadDone, 1, 5485)
        RHPathRequestList &requests = m_10;
        requests.clear();
        unsigned short count;
        PATH_ACCESS(&count, 2, 5490)
        for (unsigned short i = 0; i < count; ++i)
        {
            request = new RHpathRequest;
            PATH_REQUEST_FIELDS(request, 5495)
            requests.insert(requests.end(), request);
        }
        for (unsigned short graph = 0; graph < graphCount; ++graph)
        {
            unsigned short size = g_pathGraphFirst[graph]->size();
            for (unsigned short node = 0; node < size; ++node)
            {
                unsigned value;
                PATH_ACCESS(&value, 4, 5523)
                g_pathStates[graph].first[node] = value;
            }
        }
        FUN_00556260();
        TurnOn();
    }
    else
    {
        unsigned short count = m_10.count;
        unsigned short i = 0;
        if (g_pathThreadDone)
        {
            i = 1;
            --count;
        }
        bool done = false;
        PATH_ACCESS(&done, 1, 5544)
        PATH_ACCESS(&count, 2, 5546)
        for (; i < m_10.count; ++i)
        {
            RHpathRequest *current = m_10[i];
            PATH_ACCESS(&current->m_28, 4, 5552)
            PATH_ACCESS(&request->m_2c, 1, 5553)
            PATH_ACCESS(&request->m_34, 1, 5554)
            PATH_ACCESS(&request->m_30, 4, 5555)
            PATH_ACCESS(&request->m_2d, 1, 5556)
            PATH_ACCESS(&request->m_4, 2, 5557)
            PATH_ACCESS(&request->m_24, 2, 5558)
            PATH_ACCESS(&request->m_0, 2, 5559)
            PATH_ACCESS(&request->m_2, 2, 5560)
            request->m_10.Serialize(file);
            request->m_8.Serialize(file);
            g_pEngine->FUN_004c3af0(file, request->m_1c);
            g_pEngine->SerializeElementPointer(file, request->m_20);
            ((RHPathSequenceSerializer *)g_unk0x6c1040)->FUN_0058b7c0(file, request->m_18);
        }
        for (unsigned short graph = 0; graph < graphCount; ++graph)
        {
            unsigned short size = g_pathGraphFirst[graph]->size();
            for (unsigned short node = 0; node < size; ++node)
            {
                unsigned value = g_pathStates[graph].first[node];
                PATH_ACCESS(&value, 4, 5579)
            }
        }
    }
    return true;
}

#undef PATH_REQUEST_FIELDS
#undef PATH_ACCESS

void RHPathFinder::Emit(SBFile &file, RHpathRequest *request)
{
    FUN_00553760((RHElementActor *)request->m_1c);
    FUN_00553850((RHElementActor *)request->m_1c);
    FUN_005539a0((RHElementActor *)request->m_1c);
    FUN_00553a10(request->m_8, request->m_10, 1, (SBGeoVector2D &)request->m_10, true);
    FUN_00553d20(request->m_8, 1, (SBGeoVector2D &)request->m_10);
    FUN_00554360((RHPathSearchNode *)request);
    GetPath(g_unk0x006c0c78);
    FUN_005568f0(1, false);
    FUN_00556920(1);
    EstimateDistance(request->m_8, request->m_10);
    FUN_00557f90(request->m_8, request);
    AddPathRequest(request);
    TurnOn();
    ConvertSector(0);
    Serialize(file);
}
