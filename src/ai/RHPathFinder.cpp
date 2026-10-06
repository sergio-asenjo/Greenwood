#include "RHPathFinder.h"

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

// Parked: 83.78%, local/clear scheduling and annotated engine call.
// STUB: GAME 0x0055aa60
bool RHPathFinder::Serialize(SBFile &file)
{
    RHSerializeName(file,
                    // STRING: GAME 0x006b16b0
                    "RHPathFinder");
    unsigned short graphCount = g_pathGraphFirst == 0 ? 0 : g_pathGraphLast - g_pathGraphFirst;
    RHpathRequest *request; // The write path reloads the uninitialized +0x14 slot, distinct from current at +0x18.
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
    AddPathRequest(request);
    TurnOn();
    ConvertSector(0);
    Serialize(file);
}
