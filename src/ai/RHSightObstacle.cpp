#include "RHSightObstacle.h"

// STUB: GAME 0x005a41e0
bool RHSightObstacle::Serialize(SBFile &file)
{
    SBGeoPoint2D point;
    int count = m_4c.m_count;
    RHUnkSightVertex vertex;
    if (!file.m_bLoading)
    {
        RHUnkSightVertexList &vertices = m_4c;
        for (unsigned short i = 0; i < (unsigned short)count; ++i)
        {
            vertices.GoTo(i);
            vertex = vertices.m_current.node->data;
            point = m_7c.Unk0060cef0(i);
            if (file.Access(&vertex.m_00, 4) < 0)
            {
                SBString *err = file.GetError();
                const char *reason = err->m_chars ? err->m_chars : "";
                // STRING: GAME 0x006b7848
                SBAssert(0, "P:\\Robin Hood\\RHsightobstacle.cpp", 538, "Serialize failed reason is %s", reason);
                return false;
            }
            if (file.Access(&vertex.m_04, 4) < 0)
            {
                SBString *err = file.GetError();
                const char *reason = err->m_chars ? err->m_chars : "";
                SBAssert(0, "P:\\Robin Hood\\RHsightobstacle.cpp", 539, "Serialize failed reason is %s", reason);
                return false;
            }
            if (file.Access(&vertex.m_08, 4) < 0)
            {
                SBString *err = file.GetError();
                const char *reason = err->m_chars ? err->m_chars : "";
                SBAssert(0, "P:\\Robin Hood\\RHsightobstacle.cpp", 540, "Serialize failed reason is %s", reason);
                return false;
            }
            if (file.Access(&vertex.m_0c, 4) < 0)
            {
                SBString *err = file.GetError();
                const char *reason = err->m_chars ? err->m_chars : "";
                SBAssert(0, "P:\\Robin Hood\\RHsightobstacle.cpp", 541, "Serialize failed reason is %s", reason);
                return false;
            }
            point.Serialize(file);
        }
    }
    else
    {
        for (unsigned short i = 0; i < (unsigned short)count; ++i)
        {
            if (file.Access(&vertex.m_00, 4) < 0)
            {
                SBString *err = file.GetError();
                const char *reason = err->m_chars ? err->m_chars : "";
                SBAssert(0, "P:\\Robin Hood\\RHsightobstacle.cpp", 550, "Serialize failed reason is %s", reason);
                return false;
            }
            if (file.Access(&vertex.m_04, 4) < 0)
            {
                SBString *err = file.GetError();
                const char *reason = err->m_chars ? err->m_chars : "";
                SBAssert(0, "P:\\Robin Hood\\RHsightobstacle.cpp", 551, "Serialize failed reason is %s", reason);
                return false;
            }
            if (file.Access(&vertex.m_08, 4) < 0)
            {
                SBString *err = file.GetError();
                const char *reason = err->m_chars ? err->m_chars : "";
                SBAssert(0, "P:\\Robin Hood\\RHsightobstacle.cpp", 552, "Serialize failed reason is %s", reason);
                return false;
            }
            if (file.Access(&vertex.m_0c, 4) < 0)
            {
                SBString *err = file.GetError();
                const char *reason = err->m_chars ? err->m_chars : "";
                SBAssert(0, "P:\\Robin Hood\\RHsightobstacle.cpp", 553, "Serialize failed reason is %s", reason);
                return false;
            }
            point.Serialize(file);
            m_4c.At(i, std::bidirectional_iterator_tag()) = vertex;
            m_7c.Unk0060ced0(point, i);
        }
    }
    m_a8.FUN_005dfb00(file);
    m_100.FUN_005dfb00(file);
    m_0c.FUN_005dfd00(file);
    m_24.FUN_00607c70(file);
    m_38.FUN_00607c70(file);
    if (file.Access(&m_158, 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHsightobstacle.cpp", 569, "Serialize failed reason is %s", reason);
        return false;
    }
    return true;
}

void RHSightObstacle::Emit(SBFile &file) { Serialize(file); }
