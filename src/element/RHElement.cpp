#include "RHElement.h"

// deferred: unannotated pending reccmp #534
bool RHElement::Serialize(SBFile &file)
{
    // STRING: GAME 0x006ae088
    RHSerializeName(file, "RHElement");
    if (!file.m_bLoading)
    {
        if (file.Access(&m_0c, 4) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            // STRING: GAME 0x006ae040
            SBAssert(0, "P:\\Robin Hood\\RHelement.cpp", 174, "Serialize failed reason is %s", reason);
            return false;
        }
    }
    else
    {
        int value;
        if (file.Access(&value, 4) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHelement.cpp", 179, "Serialize failed reason is %s", reason);
            return false;
        }
        if (value != m_0c)
        {
            SBAssert(0, "P:\\Robin Hood\\RHelement.cpp", 184,
                     // STRING: GAME 0x006ae05c
                     "STRENG VERBOTEN ! Creation order error !");
        }
    }
    if (file.Access(m_94, 10) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHelement.cpp", 188, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_a0, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHelement.cpp", 189, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_a4, 2) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHelement.cpp", 190, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_8c, 2) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHelement.cpp", 192, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_12, 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHelement.cpp", 195, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_71, 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHelement.cpp", 196, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_70, 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHelement.cpp", 197, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_10, 2) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHelement.cpp", 198, "Serialize failed reason is %s", reason);
        return false;
    }
    m_80.Serialize(file);
    m_74.Serialize(file);
    if (file.Access(&m_88, 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHelement.cpp", 204, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&m_8a, 2) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHelement.cpp", 205, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.m_bLoading && file.m_version < 4)
    {
        short value;
        if (file.Access(&value, 2) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHelement.cpp", 210, "Serialize failed reason is %s", reason);
            return false;
        }
    }
    if (file.Access(&m_08, 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHelement.cpp", 219, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.m_version >= 24)
    {
        if (file.Access(&m_a6, 1) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHelement.cpp", 223, "Serialize failed reason is %s", reason);
            return false;
        }
    }
    return m_50->FUN_005b5ed0(file);
}

// STUB: GAME 0x00462aa0
void RHElement::CrossElevationLine(RHElevationLine *line)
{
    if (line->m_20 == 0)
        line->m_22 = 64000;
    else
        line->m_22 = 4000;
    line->m_20 = 10;

    if (*(void **)((char *)m_50 + 0xec) == line->m_28)
    {
        ((RHBonusInfoBase *)((char *)m_50 + 4))->FUN_0055fa70(line->m_24);
        ((RHBonusInfoBase *)((char *)m_50 + 4))->FUN_0055f290();
        return;
    }
    if (*(void **)((char *)m_50 + 0xec) == line->m_24)
    {
        ((RHBonusInfoBase *)((char *)m_50 + 4))->FUN_0055fa70(line->m_28);
        ((RHBonusInfoBase *)((char *)m_50 + 4))->FUN_0055f290();
        return;
    }

    bool failed = true;
    {
        RHUnk0040f060 areas;
        SBAssert(0, "P:\\Robin Hood\\RHelement.cpp", 485,
                 // STRING: GAME 0x006ae150
                 "VERBOTEN : Illegal bond crossing : (%f,%f) - (%f,%f) !\n",
                 line->m_04, line->m_08, line->m_0c, line->m_10);
        const SBGeoPoint2D &point = *(SBGeoPoint2D *)((char *)m_50 + 0x24);
        RHElementGrid *grid = *(RHElementGrid **)((char *)this + 0x64);
        grid->FUN_004e89d0(&areas, point.CellY() * grid->m_3e98 + point.CellX(), 0x20);
        for (unsigned count = (unsigned short)areas.m_08, index = 0; count != 0; ++index, --count)
        {
            areas.GoTo(index);
            RHElementArea *area = areas.m_0c->data;
            if (*(unsigned short *)(area->m_58 + 0x15a) == *(unsigned short *)((char *)m_50 + 0xde)
                && area->m_3c.FUN_00608400(*(SBGeoPoint2D *)((char *)m_50 + 0x24))
                && (area ? &area->m_04 : 0)->FUN_0060c660(*(SBGeoPoint2D *)((char *)m_50 + 0x24)))
            {
                ((RHBonusInfoBase *)((char *)m_50 + 4))->FUN_0055fa70(area->m_58);
                failed = false;
            }
        }
    }

    if (!failed)
    {
        ((RHBonusInfoBase *)((char *)m_50 + 4))->FUN_0055f290();
        return;
    }
    if (*(unsigned *)((char *)m_50 + 0xc) & 1)
    {
        char allocator;
        RHElementAreaList areas(allocator);
        SBAssert(0, "P:\\Robin Hood\\RHelement.cpp", 510,
                 // STRING: GAME 0x006ae0f8
                 "STRENG VERBOTEN !: No projection area was found for this bond : (%f,%f) - (%f,%f) !\n",
                 line->m_04, line->m_08, line->m_0c, line->m_10);
        {
            SBGeoPoint2D point = ((SBGeoPoint2D *)((char *)m_50 + 0x24))->Unk005fc190(FUN_005fc4f0(2.0f, *(SBGeoPoint2D *)((char *)m_50 + 0x70)));
            RHElementGrid *grid = *(RHElementGrid **)((char *)this + 0x64);
            grid->FUN_004e89d0(&areas, point.CellY() * grid->m_3e98 + point.CellX(), 0x20);
            for (unsigned count = (unsigned short)areas.m_08, index = 0; count != 0; ++index, --count)
            {
                areas.GoTo(index);
                RHElementArea *area = areas.m_0c->data;
                if (*(unsigned short *)(area->m_58 + 0x15a) == *(unsigned short *)((char *)m_50 + 0xde)
                    && area->m_3c.FUN_00608400(point)
                    && (area ? &area->m_04 : 0)->FUN_0060c660(*(SBGeoPoint2D *)((char *)m_50 + 0x24)))
                {
                    ((RHBonusInfoBase *)((char *)m_50 + 4))->FUN_0055fa70(area->m_58);
                    failed = false;
                }
            }
        }
    }
    if (!failed)
        ((RHBonusInfoBase *)((char *)m_50 + 4))->FUN_0055f290();
    else
        SBAssert(0, "P:\\Robin Hood\\RHelement.cpp", 530,
                 // STRING: GAME 0x006ae094
                 "ABSOLUT VERBOTEN !: No projection area was found for this bond at second try : (%f,%f) - (%f,%f) !\n",
                 line->m_04, line->m_08, line->m_0c, line->m_10);
}

void RHElement::Emit(SBFile &file)
{
    Serialize(file);
    CrossElevationLine(0);
}
