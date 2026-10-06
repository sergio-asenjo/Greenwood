#include "RHPath.h"

// FUNCTION: GAME 0x00550690
bool RHPath::TestIfPathIsFine(RHElementActor *actor)
{
    SBGeoPoint2D current;
    SBGeoPoint2D previous;
    bool fine = true;
    RHWaypoint *last = (*m_4)[0];
    unsigned short count = m_4 == 0 ? 0 : m_4->size();
    for (unsigned short i = 1; i < count; ++i)
    {
        RHWaypoint *waypoint = (*m_4)[i];
        if (waypoint->m_6c == last->m_6c && waypoint->m_68 == last->m_68)
        {
            ((RHUnkPathPointSet *)&current)->Set(waypoint->m_64, waypoint->m_66);
            ((RHUnkPathPointSet *)&previous)->Set(last->m_64, last->m_66);
            if (!((RHUnkPathGeometry *)g_unk0x6c0a9c)->Unk004f9260(previous, current, waypoint->m_6c))
            {
                SBAssert(0,
                         // STRING: GAME 0x006b143c
                         "P:\\Robin Hood\\RHpath.cpp", 267,
                         // STRING: GAME 0x006b14f0
                         "Path intersects obstacle between waypoints (%u, %u) and (%u, %u).",
                         (unsigned short)previous.m_x, (unsigned short)previous.m_y,
                         (unsigned short)current.m_x, (unsigned short)current.m_y);
                ((RHUnkPathEngine *)g_pEngine)->Unk004dab90(m_4, i - 1);
                fine = false;
            }
            else if (!((RHUnkPathGeometry *)g_unk0x6c0a9c)->Unk004f9170(previous, current, waypoint->m_6c,
                         ((RHUnkPathActorView *)actor)->UnkRadius()))
            {
                ((RHUnkPathEngine *)g_pEngine)->Unk004dab90(m_4, i - 1);
                if (actor->m_4 == 0x103 &&
                    ((RHUnkPathGeometry *)g_unk0x6c0a9c)->Unk004f9170(previous, current, waypoint->m_6c,
                        ((RHUnkPathEngineView *)g_pEngine)->Actor().UnkRadius()))
                {
                    SBAssert(0, "P:\\Robin Hood\\RHpath.cpp", 277,
                             // STRING: GAME 0x006b149c
                             "Path too near to obstacle (for a rider) between waypoints (%u, %u) and (%u, %u).",
                             (unsigned short)previous.m_x, (unsigned short)previous.m_y,
                             (unsigned short)current.m_x, (unsigned short)current.m_y);
                }
                else
                {
                    SBAssert(0, "P:\\Robin Hood\\RHpath.cpp", 281,
                             // STRING: GAME 0x006b1458
                             "Path too near to obstacle between waypoints (%u, %u) and (%u, %u).",
                             (unsigned short)previous.m_x, (unsigned short)previous.m_y,
                             (unsigned short)current.m_x, (unsigned short)current.m_y);
                }
                fine = false;
            }
        }
        last = waypoint;
    }
    return fine;
}

#define RH_PATH_ACCESS(value, bytes, line) \
    if (file.Access(&(value), bytes) < 0) \
    { \
        SBString *err = file.GetError(); \
        const char *reason = err->m_chars ? err->m_chars : ""; \
        SBAssert(0, "P:\\Robin Hood\\RHpath.cpp", line, "Serialize failed reason is %s", reason); \
        return false; \
    }

// FUNCTION: GAME 0x00550990
bool RHPath::SerializeStatus(SBFile &file)
{
    unsigned int count;
    unsigned short index;
    RHPathHistory value;
    // STRING: GAME 0x006b1534
    RHSerializeName(file, "RHPath::SerializeStatus");
    RH_PATH_ACCESS(m_0, 1, 319);
    RH_PATH_ACCESS(m_1, 1, 320);
    RH_PATH_ACCESS(m_2, 1, 321);
    if (file.m_bLoading)
    {
        RH_PATH_ACCESS(m_8, 2, 325);
        if (m_8 == 0xffff)
            m_4 = 0;
        else
            m_4 = g_unk0x6c0b9c->m_8[m_8];
        RH_PATH_ACCESS(count, 2, 337);
        RHPathHistoryList &list = m_c;
        list.clear();
        for (index = 0; index < (unsigned short)count; ++index)
        {
            RH_PATH_ACCESS(value.m_0, 4, 341);
            RH_PATH_ACCESS(value.m_4, 4, 342);
            ((RHUnkPathGeometry *)g_unk0x6c0a9c)->Unk004fbec0(file, value.m_8);
            RH_PATH_ACCESS(value.m_c, 2, 344);
            RH_PATH_ACCESS(value.m_10, 1, 345);
            RH_PATH_ACCESS(value.m_12, 2, 346);
            list.insert(list.end(), value);
            list.m_valid = 1;
        }
    }
    else
    {
        index = m_4 == 0 ? 0xffff : m_8;
        RH_PATH_ACCESS(index, 2, 362);
        count = m_c.m_count;
        RH_PATH_ACCESS(count, 2, 366);
        for (index = 0; index < (unsigned short)count; ++index)
        {
            value = m_c[index];
            RH_PATH_ACCESS(value.m_0, 4, 371);
            RH_PATH_ACCESS(value.m_4, 4, 372);
            ((RHUnkPathGeometry *)g_unk0x6c0a9c)->Unk004fbec0(file, value.m_8);
            RH_PATH_ACCESS(value.m_c, 2, 374);
            RH_PATH_ACCESS(value.m_10, 1, 375);
            RH_PATH_ACCESS(value.m_12, 2, 376);
        }
    }
    return true;
}

// FUNCTION: GAME 0x00551bb0
unsigned int RHWaypoint::LoadDataFromFile(SBFile &file)
{
    file.Access(&m_64, 2);
    file.Access(&m_66, 2);
    ((RHUnkPathGeometry *)g_unk0x6c0a9c)->Unk004fbec0(file, m_68);
    file.Access(&m_6c, 2);
    file.Access(&m_6e, 1);
    file.Access(&m_70, 2);
    unsigned int size = 11;
    if (m_70 > 0)
    {
        if (m_6e)
        {
            m_78 = new char[m_70 + 1];
            file.Access(m_78, m_70);
            m_78[m_70] = 0;
            size += m_70;
            if (g_unk0x6c0691)
            {
                if (!((RHUnkSectorScript *)this)->Unk00639a30(m_78))
                    SBAssert(1, "P:\\Robin Hood\\RHpath.cpp", 819,
                             // STRING: GAME 0x006b154c
                             "Structural error in RHD, a Waypoint has got a script reference that does not exist !");
                m_60.m_0 = this;
                m_60.Unk00408660();
            }
        }
        else
        {
            m_74 = new char[m_70];
            file.Access(m_74, m_70);
            size += m_70;
        }
    }
    return size;
}

void RHPath::Emit(SBFile &file, RHElementActor *actor)
{
    TestIfPathIsFine(actor);
    SerializeStatus(file);
}

void RHWaypoint::Emit(SBFile &file)
{
    LoadDataFromFile(file);
}
