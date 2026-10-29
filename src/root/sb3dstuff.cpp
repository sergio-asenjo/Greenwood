#include "SBNullstr.h"
#include "sb3dstuff.h"
#include "RHTripleVectorCalls.h"
#include "RHPlaneCalls.h"
#include <math.h>

extern float g_unk0x006785d8;

// FUNCTION: GAME 0x005df4c0
RHUnk00613e90::RHUnk00613e90(const RHUnk00613e90 &from, const RHUnk00613e90 &to)
{
    m_0 = to.m_0 - from.m_0;
    m_4 = to.m_4 - from.m_4;
    m_8 = to.m_8 - from.m_8;
}

// FUNCTION: GAME 0x005df510
bool RHUnk005df510::Serialize(SBFile &file)
{
    file.Access(&m_0, 4);
    file.Access(&m_4, 4);
    file.Access(&m_8, 4);
    return true;
}

// FUNCTION: GAME 0x005df5a0
RHUnk00613e90 RHUnk00613e90::FUN_005df5a0(const RHUnk00613e90 &other) const
{
    RHUnk00613e90 result(other.m_0 + m_0, other.m_4 + m_4, other.m_8 + m_8);
    return result;
}

// FUNCTION: GAME 0x005df5f0
float RHUnk00613e90::FUN_005df5f0(const RHUnk00613e90 &other) const
{
    return other.m_8 * m_8 + other.m_4 * m_4 + other.m_0 * m_0;
}

// FUNCTION: GAME 0x005df610
RHUnk00613e90 RHUnk00613e90::FUN_005df610(const RHUnk00613e90 &other) const
{
    unsigned char storage[sizeof(RHUnk00613e90)];
    return ((RHUnk00613e90 *)storage)->RHUnk00613e90::RHUnk00613e90(
        m_4 * other.m_8 - m_8 * other.m_4,
        m_8 * other.m_0 - other.m_8 * m_0,
        m_0 * other.m_4 - m_4 * other.m_0);
}

// FUNCTION: GAME 0x005df680
float RHUnk00613e90::FUN_005df680() const
{
    float x = (float)fabs(m_0);
    float y = (float)fabs(m_4);
    float z = (float)fabs(m_8);
    if (x > y)
        return x > z ? x : z;
    return y > z ? y : z;
}

// STUB: GAME 0x005df6e0
RHUnk00613e90 RHUnk00613e90::DistanceVectorToLine(const RHUnk00613e90 &first, const RHUnk00613e90 &second)
{
    RHUnk00613e90 direction;
    RHUnk00613e90 offset;
    direction = second.FUN_005df550(first);
    float scale = 1.0f / direction.Norm();
    direction.x *= scale;
    direction.y *= scale;
    direction.z *= scale;
    offset = FUN_005df550(first);
    RHUnk00613e90 projection = direction.Scaled(offset.FUN_005df5f0(direction));
    return offset.FUN_005df550(projection);
}

void EmitRHDistanceVectorToLine(RHUnk00613e90 *value)
{
    value->DistanceVectorToLine(*value, *value);
}

// FUNCTION: GAME 0x005df820
RHUnk005df860::RHUnk005df860()
{
    ((RHUnk00613e90 *)(m_00 + 0x00))->RHUnk00613e90::RHUnk00613e90();
    ((RHUnk00613e90 *)(m_00 + 0x0c))->RHUnk00613e90::RHUnk00613e90();
    ((RHUnk00613e90 *)(m_00 + 0x18))->RHUnk00613e90::RHUnk00613e90();
    ((RHUnk00613e90 *)(m_00 + 0x24))->RHUnk00613e90::RHUnk00613e90();
    ((RHUnk00613e90 *)(m_00 + 0x30))->RHUnk00613e90::RHUnk00613e90();
    ((RHUnk00613e90 *)(m_00 + 0x3c))->RHUnk00613e90::RHUnk00613e90();
}

// FUNCTION: GAME 0x005df8b0
void RHUnk005df860::FUN_005df8b0()
{
    RHUnk00613e90 *points = (RHUnk00613e90 *)this;
    points[3] = points[1].FUN_005df550(points[0]);
    points[4] = points[2].FUN_005df550(points[0]);
}

// FUNCTION: GAME 0x005df900
void RHUnk005df860::FUN_005df900()
{
    float *fields = (float *)this;
    float first = fields[10];
    float second = fields[13];
    float x = fields[15] = first * fields[14] - second * fields[11];
    float fourth = fields[9];
    float y = fields[16] = fields[12] * fields[11] - fourth * fields[14];
    float third = fields[13];
    float fifth = fields[12];
    float z = fields[17] = third * fields[9] - fifth * fields[10];
    float nz = *(volatile float *)(fields + 17);
    float ny = *(volatile float *)(fields + 16);
    float nx = *(volatile float *)(fields + 15);
    float length = (float)sqrt(nx * nx + ny * ny + nz * nz);
    fields[15] = x / length;
    fields[16] = y / length;
    fields[17] = z / length;
}

// FUNCTION: GAME 0x005df9a0
void RHUnk005df860::FUN_005df9a0()
{
    float *fields = (float *)this;
    fields[18] = -fields[15] * fields[0] - fields[16] * fields[1] - fields[17] * fields[2];
}

// FUNCTION: GAME 0x005df9c0
void RHUnk005df860::FUN_005df9c0()
{
    float *fields = (float *)this;
    float factor = g_unk0x006785d8 / fields[17];
    fields[19] = (float)(factor * fields[15]);
    fields[20] = (float)(factor * fields[16]);
    fields[21] = (float)(factor * fields[18]);
}

// FUNCTION: GAME 0x005dfa20
void RHUnk005df860::FUN_005dfa20(const RHUnk00613e90 &offset)
{
    float *fields = (float *)this;
    fields[0] = offset.m_0 + fields[0];
    float y0 = fields[1];
    fields[1] = y0 + offset.m_4;
    float z0 = fields[2];
    fields[2] = z0 + offset.m_8;
    float x1 = fields[3];
    fields[3] = x1 + offset.m_0;
    float y1 = fields[4];
    fields[4] = y1 + offset.m_4;
    float z1 = fields[5];
    fields[5] = z1 + offset.m_8;
    float x2 = fields[6];
    fields[6] = x2 + offset.m_0;
    float y2 = fields[7];
    fields[7] = y2 + offset.m_4;
    float z2 = fields[8];
    fields[8] = z2 + offset.m_8;
    fields[18] = -fields[15] * fields[0] - fields[16] * fields[1] - fields[17] * fields[2];
    fields[21] = -(fields[18] / fields[17]);
}

// FUNCTION: GAME 0x005dfaa0
void RHUnk005df860::FUN_005dfaa0(const SBGeoPoint2D &offset)
{
    const float *value = (const float *)&offset;
    float *fields = (float *)this;
    fields[0] = value[0] + fields[0];
    float y0 = fields[1];
    fields[1] = y0 + value[1];
    float x1 = fields[3];
    fields[3] = x1 + value[0];
    float y1 = value[1];
    fields[4] = y1 + fields[4];
    float x2 = fields[6];
    fields[6] = x2 + value[0];
    float y2 = value[1];
    fields[7] = y2 + fields[7];
    fields[18] = -fields[15] * fields[0] - fields[16] * fields[1] - fields[2] * fields[17];
    fields[21] = -(fields[18] / fields[17]);
}

// FUNCTION: GAME 0x005dfb00
bool RHUnk005dfb00::FUN_005dfb00(SBFile &file)
{
    m_0c.Serialize(file);
    m_18.Serialize(file);
    m_3c.Serialize(file);
    m_00.Serialize(file);
    m_24.Serialize(file);
    m_30.Serialize(file);

    if (file.Access(&m_4c, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        // STRING: GAME 0x006b8f48
        SBAssert(0, "P:\\Robin Hood\\sb3dstuff.cpp", 299, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_50, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\sb3dstuff.cpp", 300, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_54, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\sb3dstuff.cpp", 301, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_48, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\sb3dstuff.cpp", 302, "Serialize failed reason is %s", reason);
        return false;
    }
    return true;
}

// FUNCTION: GAME 0x005dfc20
RHUnk005dfd00::RHUnk005dfd00()
{
    m_00 = 0x7149f2ca;
    m_04 = 0xf149f2ca;
    m_08 = 0x7149f2ca;
    m_0c = 0xf149f2ca;
    m_10 = 0x7149f2ca;
    m_14 = 0xf149f2ca;
}

// FUNCTION: GAME 0x005dfc80
void RHUnk005dfd00::FUN_005dfc80(RHUnk00613e90 point)
{
    float x = point.x;
    float y = point.y;
    float z = point.z;
    float *fields = (float *)this;
    if (fields[0] > x)
        fields[0] = x;
    if (fields[1] < x)
        fields[1] = x;
    if (fields[2] > y)
        fields[2] = y;
    if (fields[3] < y)
        fields[3] = y;
    if (fields[4] > z)
        fields[4] = z;
    if (fields[5] < z)
        fields[5] = z;
}

// FUNCTION: GAME 0x005dfd00
bool RHUnk005dfd00::FUN_005dfd00(SBFile &file)
{
    if (file.Access(&m_00, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\sb3dstuff.cpp", 387, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_04, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\sb3dstuff.cpp", 388, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_08, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\sb3dstuff.cpp", 389, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_0c, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\sb3dstuff.cpp", 390, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_10, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\sb3dstuff.cpp", 391, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_14, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\sb3dstuff.cpp", 392, "Serialize failed reason is %s", reason);
        return false;
    }
    return true;
}

void RHUnk005dfb00::Emit(SBFile &file) { FUN_005dfb00(file); }
void RHUnk005dfd00::Emit(SBFile &file) { FUN_005dfd00(file); }

float EmitSB3DGeometry(RHUnk00613e90 &vector, RHUnk005df860 &plane)
{
    RHUnk005df860 initializedPlane;
    RHUnk005dfd00 bounds;
    bounds.FUN_005dfc80(RHUnk00613e90(0.0f, 0.0f, 0.0f));
    RHUnk00613e90 difference(vector, vector);
    vector.FUN_005df5a0(vector);
    vector.FUN_005df5f0(vector);
    vector.FUN_005df610(vector);
    plane.FUN_005df8b0();
    plane.FUN_005df900();
    plane.FUN_005df9a0();
    plane.FUN_005df9c0();
    plane.FUN_005dfa20(vector);
    plane.FUN_005dfaa0(*(const SBGeoPoint2D *)&vector);
    return vector.FUN_005df680();
}
