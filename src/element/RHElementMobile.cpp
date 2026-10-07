#include "RHElementMobile.h"

// GLOBAL: GAME 0x006c0960
bool g_mobileAssertDoubleBond = false;

// Parked: x87 ordering and register/store scheduling remain non-exact.
// STUB: GAME 0x004ac350
bool RHElementMobile::ExecuteMacroCommand()
{
    unsigned char command = *m_190++;
    switch (command)
    {
    case 128:
    {
        m_1ec = *(unsigned short *)m_190;
        m_190 += 2;
        unsigned short count = Size();
        for (unsigned short i = 0; i < count; ++i)
        {
            RHMobileElement *element = i[m_b0];
            element->m_50->FUN_005b76e0(m_1ec, 0);
            ((RHUnk005bd5b0 *)element->m_50)->Unk(false);
        }
        m_194 -= 3;
        return true;
    }
    case 129:
    {
        float speed = *(float *)m_190;
        m_19c = speed;
        m_194 -= 5;
        m_190 += 4;
        ((RHUnk004af1d0 *)this)->Unk(speed != g_unk0x00677488);
        return true;
    }
    case 130:
    {
        SBGeoPoint2D position;
        SBGeoPoint2D destination;
        m_1a0 = *(float *)m_190;
        if (m_1a0 == g_unk0x00677488)
            m_1a0 = 0.1f;
        m_190 += 4;
        unsigned short waypoint = *(unsigned short *)m_190;
        m_190 += 2;
        if (waypoint >= m_188->Size())
            SBAssert(1,
                // STRING: GAME 0x006aeb08
                "P:\\Robin Hood\\RHelementmobile.cpp", 741,
                // STRING: GAME 0x006aebb8
                "VERBOTEN : Mobile element waypoint command referencing non-existing waypoint (%d) !", waypoint);
        RHMobileElement *element = m_188->m_4->m_4[waypoint];
        destination.m_x = element->m_64;
        destination.m_y = element->m_66;
        position = m_50->m_24;
        float distance = ((RHUnk005fc3b0 *)&destination.Unk005fc110(position))->Unk005fc6a0(1.0f);
        m_194 -= 7;
        m_1a4 = (m_19c + m_1a0) * (m_1a0 - m_19c) * g_unk0x006775d8 / distance;
        return true;
    }
    case 131:
    {
        m_198 = *(unsigned short *)m_190;
        m_190 += 2;
        unsigned short count = Size();
        for (unsigned short i = 0; i < count; ++i)
            i[m_b0]->m_fc = 1000000.0f;
        m_194 -= 3;
        return false;
    }
    case 132:
        SBAssert(0, "P:\\Robin Hood\\RHelementmobile.cpp", 780,
            // STRING: GAME 0x006aeb64
            "WARNUNG : \"Flip extremities\" command of moving elements was declared deprecated !");
        return true;
    case 133:
    {
        unsigned value = *(unsigned short *)m_190;
        m_190 += 2;
        FUN_004af0f0(value);
        m_194 -= 3;
        return true;
    }
    case 134:
    {
        unsigned short value = *(unsigned short *)m_190;
        m_190 += 2;
        ((RHUnk004af060 *)this)->Unk(value);
        m_194 -= 3;
        return true;
    }
    default:
        SBAssert(0, "P:\\Robin Hood\\RHelementmobile.cpp", 835,
            // STRING: GAME 0x006aeb2c
            "VERBOTEN : Unknown mobile element waypoint command !");
        return false;
    }
}

// Parked: mission-stream body has not been reconstructed.
// STUB: GAME 0x004ad5f0
void RHElementMobile::InitializeFromMissionStream(SBFile &file)
{
    (void)file;
}

// Parked: serialization body has not been reconstructed.
// STUB: GAME 0x004ae470
bool RHElementMobile::Serialize(SBFile &file)
{
    (void)file;
    return false;
}

// Parked: list cleanup, registers, and local scheduling remain non-exact.
// STUB: GAME 0x004af540
void RHElementMobile::CheckForLineCrossing()
{
    RHUnk0040f060 lines;
    if (!m_50->m_24.FUN_005fc0e0(m_50->m_40))
        return;
    ((RHMobileGrid *)*(void **)((char *)this + 0x64))->FUN_004ed370(&lines, m_50->m_de, RHMobileSegment(m_50->m_40, m_50->m_24), 12);
    unsigned short count = (unsigned short)lines.count;
    if (count)
    {
        for (unsigned short i = 0; i < count; ++i)
        {
            lines.GoTo(i);
            RHElevationLine *line = lines.cursor->data;
            unsigned flags = line->m_14;
            if ((flags >> 2) & 1)
            {
                SBGeoPoint2D first(line->m_4);
                SBGeoPoint2D second(line->m_c);
                for (unsigned short j = i + 1; j < count; ++j)
                {
                    lines.GoTo(j);
                    RHElevationLine *other = lines.cursor->data;
                    if (other->m_14 == flags &&
                        ((first == other->m_4 && second == other->m_c) ||
                         (second == other->m_4 && first == other->m_c)))
                    {
                        if (!g_mobileAssertDoubleBond)
                            g_mobileAssertDoubleBond = true;
                        SBAssert(0, "P:\\Robin Hood\\RHelementmobile.cpp", 1916,
                            // STRING: GAME 0x006ae298
                            "Double bond : (%f,%f) - (%f,%f) !\n", other->m_4.m_x, other->m_4.m_y, other->m_c.m_x, other->m_c.m_y);
                        lines.GoTo(j);
                        ((RHUnk0046eb30 *)&lines)->erase(RHScriptIter(lines.cursor));
                        --j;
                        --count;
                        lines.dirty = true;
                    }
                }
            }
        }
        for (unsigned short index = 0; index < count; ++index)
        {
            RHUnk005fc3b0 movement;
            lines.GoTo(index);
            SBGeoPoint2D &first = lines.cursor->data->m_4;
            movement.FUN_005fc430(m_50->m_40.Unk005fc110(first));
            if (((RHUnk005fc3b0 *)&((RHUnk0042fde0 *)&first)->FUN_0042fde0())->FUN_005fc680(movement, 1.0f) == g_unk0x00677488)
            {
                lines.GoTo(index);
                ((RHUnk0046eb30 *)&lines)->erase(RHScriptIter(lines.cursor));
                --index;
                --count;
                lines.dirty = true;
            }
        }
        if (count == 1)
        {
            ((RHElement *)this)->CrossElevationLine(lines.head->next->data);
            ((RHMobilePosition *)((char *)m_50 + 4))->FUN_0055fc20(false);
            FUN_004af170(m_50->m_ec);
        }
        else
        {
            void *area = m_50->m_ec;
            for (unsigned short index = 0; index < (int)count - 1; ++index)
            {
                for (unsigned short j = index; j < count; ++j)
                {
                    lines.GoTo(j);
                    RHElevationLine *line = lines.cursor->data;
                    if (line->m_28 == area)
                    {
                        area = line->m_24;
                        lines.GoTo(index);
                        RHElevationLine *&destination = lines.cursor->data;
                        lines.GoTo(j);
                        RHElevationLine *value = lines.cursor->data;
                        lines.cursor->data = destination;
                        lines.GoTo(index);
                        lines.cursor->data = value;
                        break;
                    }
                    if (line->m_24 == area)
                    {
                        area = line->m_28;
                        lines.GoTo(index);
                        RHElevationLine *&destination = lines.cursor->data;
                        lines.GoTo(j);
                        RHElevationLine *value = lines.cursor->data;
                        lines.cursor->data = destination;
                        lines.GoTo(index);
                        lines.cursor->data = value;
                        break;
                    }
                }
            }
        }
    }
}

void RHElementMobile::Emit(SBFile &file)
{
    ExecuteMacroCommand();
    InitializeFromMissionStream(file);
    Serialize(file);
    CheckForLineCrossing();
}
