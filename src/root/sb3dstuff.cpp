#include "sb3dstuff.h"

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
