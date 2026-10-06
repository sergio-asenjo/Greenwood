#include "RHFastFindGrid.h"

// GLOBAL: GAME 0x006c06f0
RHFastFindTacticalArray g_unk0x006c06f0;
// GLOBAL: GAME 0x006c0718
RHFastFindTacticalArray g_unk0x006c0718;

// deferred: unannotated pending reccmp #534
RHSeqList::RHSeqList(const char &allocator)
{
    m_00[0] = allocator;
    RHSeqNode *head = (RHSeqNode *)operator new(0xc);
    head->m_next = head;
    head->m_prev = head;
    m_head = head;
    m_count = 0;
}

// FUNCTION: GAME 0x004ebbd0
void RHFastFindGrid::InitializeLiftsFromProtoStream(SBFile &file)
{
    FUN_005e1d50(file, 0x20415a20, 2);
    unsigned short count;
    unsigned short sectorIndex;
    file.Access(&count, 2);
    for (unsigned short i = 0; i < count; ++i)
    {
        file.Access(&sectorIndex, 2);
        RHFastFindSector *sector = (RHFastFindSector *)m_sectors.m_first[sectorIndex];
        ((RHProfileFile &)file).FUN_005f5370(2, 1);
        if (!(sector->LiftFlag() & 1))
        {
            SBAssert(1, "P:\\Robin Hood\\RHfastfindgrid.cpp", 0xc22,
                // STRING: GAME 0x006afbd0
                "DA FALLEN MIR DIE OHREN AB : Illegal lift sector : %d !\n", sector->m_id);
        }
        sector->UnkSlot10(file, this);
    }
    FUN_005e20c0(file);
}

// FUNCTION: GAME 0x004ebc80
void RHFastFindGrid::InitializeBuildingsFromProtoStream(SBFile &file)
{
    FUN_005e1d50(file, 0x4641524d, 4);
    unsigned short count;
    file.Access(&count, 2);
    for (unsigned short i = 0; i < count; ++i)
    {
        bool isLift;
        file.Access(&isLift, 1);
        if (isLift)
        {
            void *lift = new RHUnk0057e4d0;
            ((RHUnk0057e4d0 *)lift)->UnkSlot10(file, this);
            fastfind_lifts.InsertLast(lift);
            FUN_004e8bd0(lift, m_layerCount - 1, true);
        }
        else
        {
            unsigned short gates;
            file.Access(&gates, 2);
            for (unsigned short j = 0; j < gates; ++j)
            {
                RHUnk0051aa00 *gate = new RHUnk0051aa00;
                gate->Unk0051b2a0(file, false);
                if (gate->m_88 != 0 && gate->m_88 != 3 && gate->m_88 != 7)
                    SBAssert(1, "P:\\Robin Hood\\RHfastfindgrid.cpp", 0xc9b,
                        // STRING: GAME 0x006afc0c
                        "VERBOTEN : Non-building & non-lift doors must be of type DEFAULT or GATE (%d,%d) !",
                        gate->m_94.m_x, gate->m_94.m_y);
                void *value = gate;
                fastfind_gateObjects.InsertLast(value);
            }
        }
    }
    FUN_005e20c0(file);
}

// FUNCTION: GAME 0x004eca10
void RHFastFindGrid::DeleteStaticRepulsivePoint(unsigned long id)
{
    RHFastFindRepulsive *point = m_repulsivePoints.begin();
    unsigned short *layer = m_repulsiveLayers.begin();
    for (; point != m_repulsivePoints.end(); ++point, ++layer)
    {
        if (point->m_id == id)
        {
            m_repulsivePoints.erase(point);
            m_repulsiveLayers.erase(layer);
            return;
        }
    }
    SBAssert(0, "P:\\Robin Hood\\RHfastfindgrid.cpp", 0xdcc,
        // STRING: GAME 0x006afc60
        "ACHTUNG : Trying to delete inexisting static repulsive point (ID : %d)", id);
}

// parked: best probe 61.16%.
// STUB: GAME 0x004ef340
void RHFastFindGrid::InitializeSightObstaclesFromProtoStream(SBFile &file)
{
    FUN_005e1d50(file, 0x574f4157, 3);
    RHUnk005a3450 *area = new RHUnk005a3450(4);
    {
        SBGeoPoint3D first(0.0f, 10.0f, 0.0f);
        SBGeoPoint3D second(10.0f, 0.0f, 0.0f);
        SBGeoPoint3D third(0.0f, 0.0f, 0.0f);
        area->FirstPlane().Unk005df860(third, second, first);
        area->FirstPlane().Unk005dfa00();
    }
    {
        SBGeoPoint3D first(0.0f, 10.0f, 0.0f);
        SBGeoPoint3D second(10.0f, 0.0f, 0.0f);
        SBGeoPoint3D third(0.0f, 0.0f, 0.0f);
        area->SecondPlane().Unk005df860(third, second, first);
        area->SecondPlane().Unk005dfa00();
    }
    area->Bounds().Unk00607dc0(SBGeoPoint2D(0.0f, 0.0f));
    area->Bounds().Unk00607dc0(SBGeoPoint2D(2000.0f, 2000.0f));
    area->OtherBounds() = area->Bounds();
    area->SetLayer(0);
    area->SetSector(0);
    area->m_flags |= 4;
    area->m_active = false;
    m_projectionAreas.InsertLast((void *const &)area);
    RHFastFindPointerArray &materials = *(RHFastFindPointerArray *)((char *)this + 0x4120);
    unsigned short materialCount;
    unsigned short materialIndex;
    file.Access(&materialCount, 2);
    for (unsigned short i = 0; i < materialCount; ++i)
    {
        file.Access(&materialIndex, 2);
        if (materialIndex >= materials.size())
            SBAssert(1, "P:\\Robin Hood\\RHfastfindgrid.cpp", 0x1406,
                // STRING: GAME 0x006afcdc
                "HALT ! STEHENBLEIBEN ! : Trying to associate non-existing material with default sight obstacle !");
        FUN_004e8bd0(materials.m_first[materialIndex], 0, true);
        FUN_004e99e0(materials.m_first[materialIndex], 0, true);
    }
    unsigned short obstacleCount;
    file.Access(&obstacleCount, 2);
    for (unsigned short j = 0; j < obstacleCount; ++j)
    {
        area = new RHUnk005a3450;
        area->Unk005a3810(file, materials);
        if (area->ProjectionFlag() & 1)
        {
            m_projectionAreas.InsertLast((void *const &)area);
            RHFastFindSightSector *sector = (RHFastFindSightSector *)m_sectors.m_first[area->m_sector];
            if ((sector->SectorFlag() & 1) && (sector->BaseFlag() & 1))
            {
                void *value = area;
                RHSeqNode *head = sector->m_head;
                RHSeqNode *previous = head->m_prev;
                RHSeqNode *node = (RHSeqNode *)operator new(0xc);
                node->m_next = head ? head : node;
                node->m_prev = previous ? previous : node;
                head->m_prev = node;
                node->m_prev->m_next = node;
                RHSeqList::CopyData(&node->m_data, (RHSequenceElement *const *)&value);
                ++sector->m_count;
                sector->m_changed = true;
            }
            else
                SBAssert(1, "P:\\Robin Hood\\RHfastfindgrid.cpp", 0x1420,
                    // STRING: GAME 0x006afca8
                    "Illegal sight obstacle/motion area association !\n");
            area->m_motionArea = area->Unk005a5780();
            FUN_004e8bd0(area->m_motionArea, 0, true);
        }
        FUN_004ef8e0(area, 0, true);
        (*(RHFastFindGateArray *)((char *)this + 0x4140)).InsertLast((void *const &)area, false, true);
    }
    FUN_005e20c0(file);
}

// deferred: unannotated pending reccmp #534
bool RHFastFindGrid::Unk004efbb0(SBFile &file, void **value)
{
    short index;
    if (!file.m_bLoading)
    {
        if (*value == 0)
        {
            index = -1;
            file.Access(&index, 2);
            return true;
        }
        index = m_patches.Find(*value);
        if (file.Access(&index, 2) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            // STRING: GAME 0x006afbac
            SBAssert(0, "P:\\Robin Hood\\RHfastfindgrid.cpp", 0x1498, "Serialize failed reason is %s", reason);
            return false;
        }
    }
    else
    {
        if (file.Access(&index, 2) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHfastfindgrid.cpp", 0x149f, "Serialize failed reason is %s", reason);
            return false;
        }
        if (index == -1)
        {
            *value = 0;
            return true;
        }
        *value = m_patches.m_first[index];
    }
    return true;
}

// parked: best probe 71.97%.
// STUB: GAME 0x004f9490
bool RHFastFindGrid::Serialize(SBFile &file)
{
    RHSerializeName(file,
        // STRING: GAME 0x006afd40
        "RHFastFindGrid");
    if (file.m_bLoading)
    {
        for (unsigned short i = 0; i <= m_layerCount - 1; ++i)
        {
            RHFastFindLayer &layer = m_layers[i];
            RHUnk0054f870 **paths = layer.m_paths;
            for (short j = layer.m_pathCount - 1; j >= 0; --j)
                paths[j]->Unk00550220();
        }
    }
    for (unsigned short i = 0; i <= m_layerCount - 1; ++i)
    {
        unsigned short count = m_layers[i].m_pathCount;
        RHUnk0054f870 **paths = m_layers[i].m_paths;
        for (unsigned short j = 0; j < count; ++j)
            if (!paths[j]->Unk0054f870(file))
                return false;
    }
    unsigned short gateCount = m_gates.size();
    for (unsigned short gateIndex = 0; gateIndex < gateCount; ++gateIndex)
        if (!((RHFastFindSerializableGate *)m_gates.m_first[gateIndex])->UnkSlot4(file))
            return false;
    RHFastFindPointerArray &scripts = *(RHFastFindPointerArray *)((char *)this + 0x40e0);
    unsigned short scriptCount = scripts.size();
    for (unsigned short scriptIndex = 0; scriptIndex < scriptCount; ++scriptIndex)
    {
        void *data = scripts.m_first[scriptIndex];
        if (*(int *)((char *)data + 4) == 2)
        {
            RHFastFindSerializableSector *sector = data ? (RHFastFindSerializableSector *)((char *)data - 0xb8) : 0;
            if (!sector->UnkSlotc(file))
                return false;
        }
    }
    unsigned short sectorCount = m_sectors.size();
    for (unsigned short sectorIndex = 0; sectorIndex < sectorCount; ++sectorIndex)
    {
        RHFastFindSerializableSector *sector = (RHFastFindSerializableSector *)m_sectors.m_first[sectorIndex];
        if (sector)
        {
            if (sector->Flag12() & 1)
            {
                if (!sector->UnkSlotc(file))
                    return false;
            }
            else if (sector->Flag13() & 1)
            {
                if (!sector->UnkSlotc(file))
                    return false;
            }
            else if (sector->Flag9() & 1)
            {
                if (!sector->UnkSlotc(file))
                    return false;
            }
        }
    }
    if (file.m_bLoading && file.m_version < 4)
    {
        bool legacyFlag;
        unsigned short count;
        if (file.Access(&legacyFlag, 1) < 0)
        {
            SBString *error = file.GetError();
            SBAssert(0, "P:\\Robin Hood\\RHfastfindgrid.cpp", 0x2307, "Serialize failed reason is %s", error->m_chars ? error->m_chars : "");
            return false;
        }
        if (file.Access(&count, 2) < 0)
        {
            SBString *error = file.GetError();
            SBAssert(0, "P:\\Robin Hood\\RHfastfindgrid.cpp", 0x2309, "Serialize failed reason is %s", error->m_chars ? error->m_chars : "");
            return false;
        }
        for (unsigned short i = 0; i < count; ++i)
        {
            float legacyValue;
            if (file.Access(&legacyValue, 4) < 0)
            {
                SBString *error = file.GetError();
                SBAssert(0, "P:\\Robin Hood\\RHfastfindgrid.cpp", 0x230c, "Serialize failed reason is %s", error->m_chars ? error->m_chars : "");
                return false;
            }
            if (file.Access(&legacyValue, 4) < 0)
            {
                SBString *error = file.GetError();
                SBAssert(0, "P:\\Robin Hood\\RHfastfindgrid.cpp", 0x230d, "Serialize failed reason is %s", error->m_chars ? error->m_chars : "");
                return false;
            }
        }
    }
    RHUnk004b2190Member point;
    unsigned int pointCount;
    unsigned short layerIndex;
    if (file.m_bLoading)
    {
        m_repulsivePoints.erase(m_repulsivePoints.begin(), m_repulsivePoints.end());
        m_repulsiveLayers.erase(m_repulsiveLayers.begin(), m_repulsiveLayers.end());
        if (file.Access(&pointCount, 4) < 0)
        {
            SBString *error = file.GetError();
            SBAssert(0, "P:\\Robin Hood\\RHfastfindgrid.cpp", 0x234a, "Serialize failed reason is %s", error->m_chars ? error->m_chars : "");
            return false;
        }
        for (unsigned int i = 0; i < pointCount; ++i)
        {
            point.Serialize(file);
            if (file.Access(&layerIndex, 2) < 0)
            {
                SBString *error = file.GetError();
                SBAssert(0, "P:\\Robin Hood\\RHfastfindgrid.cpp", 0x234e, "Serialize failed reason is %s", error->m_chars ? error->m_chars : "");
                return false;
            }
            ((SBArray<RHUnk004b2190Member> *)&m_repulsivePoints)->Insert((RHUnk004b2190Member *)m_repulsivePoints.end(), 1, point);
            ((SBArray<unsigned short> *)&m_repulsiveLayers)->Insert(m_repulsiveLayers.end(), 1, layerIndex);
        }
    }
    else
    {
        pointCount = m_repulsivePoints.size();
        if (file.Access(&pointCount, 4) < 0)
        {
            SBString *error = file.GetError();
            SBAssert(0, "P:\\Robin Hood\\RHfastfindgrid.cpp", 0x2358, "Serialize failed reason is %s", error->m_chars ? error->m_chars : "");
            return false;
        }
        for (unsigned int i = 0; i < pointCount; ++i)
        {
            ((RHUnk004b2190Member *)&m_repulsivePoints[i])->Serialize(file);
            layerIndex = m_repulsiveLayers[i];
            if (file.Access(&layerIndex, 2) < 0)
            {
                SBString *error = file.GetError();
                SBAssert(0, "P:\\Robin Hood\\RHfastfindgrid.cpp", 0x235e, "Serialize failed reason is %s", error->m_chars ? error->m_chars : "");
                return false;
            }
        }
    }
    return true;
}

// parked: default-branch cleanup split.
// STUB: GAME 0x004fa8e0
void RHFastFindGrid::InitializeTacticalInfosFromMissionStream(SBFile &file)
{
    FUN_005e1d50(file, 0x4849524e, 2);
    RHFastFindClearTactical(g_unk0x006c06f0);
    RHFastFindClearTactical(g_unk0x006c0718);
    unsigned short count;
    file.Access(&count, 2);
    for (unsigned short i = 0; i < count; ++i)
    {
        switch (FUN_005e1d00(file))
        {
        case 0x42555348:
            FUN_004faf40(file);
            break;
        case 0x484f4c45:
            FUN_004fb1d0(file);
            break;
        case 0x4e4c4950:
            FUN_004fb230(file);
            break;
        case 0x504f5720:
            InitializeReinforcementPointsFromMissionStream(file);
            break;
        default:
            char chunk[5];
            *(unsigned long *)chunk = FUN_005e1d00(file);
            chunk[4] = 0;
            FUN_005e2300(file);
            SBAssert(0, "P:\\Robin Hood\\RHfastfindgrid.cpp", 0x265f,
                // STRING: GAME 0x006afd50
                "ACHTUNG : Unimplemented or unknown chunk %s, skipped", chunk);
            break;
        }
    }
    FUN_005e20c0(file);
}

// STUB: GAME 0x004faaa0
    void RHFastFindGrid::InitializeReinforcementPointsFromMissionStream(SBFile &file)
{
    FUN_005e1d50(file, 0x504f5720, 2);
    unsigned short count;
    file.Access(&count, 2);
    for (unsigned short i = 0; i < count; ++i)
    {
        short x;
        short y;
        int directionValue;
        int nextDirection;
        unsigned short layer;
        unsigned short sectorIndex;
        short direction;
        file.Access(&x, 2);
        file.Access(&y, 2);
        file.Access(&directionValue, 4);
        file.Access(&nextDirection, 4);
        file.Access(&layer, 2);
        file.Access(&sectorIndex, 2);
        file.Access(&direction, 2);
        RHFastFindSector *sector;
        if (sectorIndex == 0xffff)
            sector = fastfind_defaultSector;
        else
            sector = (RHFastFindSector *)m_sectors.m_first[sectorIndex];
        if (!(sector->SectorFlag() & 1) || !(sector->BaseFlag() & 1))
            SBAssert(1, "P:\\Robin Hood\\RHfastfindgrid.cpp", 0x268e,
                // STRING: GAME 0x006afd88
                "DA LACHEN DIE H\334HNER ! Reinforcemenent point lies in invalid sector !");
        SBGeoPoint2D destination((float)x, (float)y);
        SBGeoPoint2D first;
        SBGeoPoint2D second;
        ((RHScriptRecordWorld *)this)->Unk004fc8f0(second, first, &destination, (unsigned short)directionValue);
        RHUnk0051aa00 *gate = new RHUnk0051aa00;
        gate->m_88 = 8;
        gate->m_9c = 6;
        gate->m_a0 = 6;
        gate->m_a4 = 6;
        gate->m_a8 = 6;
        gate->m_b0 = 0;
        gate->m_14 = m_layerCount;
        gate->m_0c = fastfind_defaultSector;
        gate->m_18.Set((short)first.m_x, (short)first.m_y);
        gate->m_94.Set((short)second.m_x, (short)second.m_y);
        gate->m_10 = sector;
        gate->m_16 = direction;
        gate->m_20.Set(x, y);
        FUN_004fad80(gate);
    }
    FUN_005e20c0(file);
}

// STUB: GAME 0x004fb510
void RHFastFindGrid::InitializeJumpStuffFromProtoStream(SBFile &file)
{
    char allocator;
    RHUnk004e5270 sectors(allocator);
    FUN_005e1d50(file, 0x50505050, 4);
    unsigned short sectorCount;
    file.Access(&sectorCount, 2);
    for (unsigned short i = 0; i < sectorCount; ++i)
    {
        void *sector = new RHUnk0051e5e0;
        ((RHUnk0051e5e0 *)sector)->Unk0051e700(file);
        sectors.InsertLast(sector);
    }
    unsigned short jumpCount;
    file.Access(&jumpCount, 2);
    for (unsigned short j = 0; j < jumpCount; ++j)
    {
        RHUnk0051e1e0 *first = new RHUnk0051e1e0;
        first->Unk0051e230(file, sectors);
        RHUnk0051e1e0 *second = new RHUnk0051e1e0;
        second->Unk0051e230(file, sectors);
        first->m_other = second;
        second->m_other = first;
        bool mode;
        file.Access(&mode, 1);
        first->m_mode = mode;
        second->m_mode = mode;
        first->m_layer = second->m_sector->m_layer;
        first->m_owner = second->m_sector->m_98;
        void *value = first;
        ((RHUnk004e5270 *)((char *)first->m_owner + 0xc8))->InsertLast(value);
        second->m_layer = first->m_sector->m_layer;
        second->m_owner = first->m_sector->m_98;
        value = second;
        ((RHUnk004e5270 *)((char *)second->m_owner + 0xc8))->InsertLast(value);
        FUN_004ed690(first, first->m_layer, true);
        FUN_004ed690(second, second->m_layer, true);
        RHUnk0051b6e0 *gate = new RHUnk0051b6e0(first, second);
        value = gate;
        m_gates.InsertLast(value);
        first->m_gate = gate;
        second->m_gate = gate;
    }
    for (unsigned short k = 0; k < sectorCount; ++k)
    {
        sectors.GoTo(k);
        RHUnk0051e5e0 *sector = (RHUnk0051e5e0 *)sectors.m_current->m_data;
        sector->Unk0051e800();
        FUN_004e8bd0(sector, sector->m_layer, true);
        if (sector->m_lines.size() == 0)
            SBAssert(1, "P:\\Robin Hood\\RHfastfindgrid.cpp", 0x27da,
                // STRING: GAME 0x006afdd0
                "AUF WIEDERSEHEN : Jump-zone (%f,%f) has no jump-line !",
                ((RHUnkSectorPoints *)((char *)sector + 4))->Unk0060cef0(0).m_x,
                ((RHUnkSectorPoints *)((char *)sector + 4))->Unk0060cef0(0).m_y);
    }
    FUN_005e20c0(file);
}

// STUB: GAME 0x004fb8e0
void RHFastFindGrid::InitializeScriptStuffFromMissionStream(SBFile &file)
{
    FUN_005e1d50(file, 0x47554c50, 2);
    unsigned short count;
    file.Access(&count, 2);
    for (unsigned short i = 0; i < count; ++i)
    {
        RHUnk00522470 *point = new RHUnk00522470;
        point->Unk005224d0(file);
        FUN_004ebfe0(point, point->m_layer, true);
        void *value = point ? (char *)point + 0x14 : 0;
        (*(RHFastFindPointerArray *)((char *)this + 0x40e0)).InsertLast(value);
    }
    file.Access(&count, 2);
    for (unsigned short j = 0; j < count; ++j)
    {
        RHSectorScript *sector = new RHSectorScript;
        sector->InitializeFromMissionStream(file);
        if (!sector->m_active)
            sector->m_flags &= ~0x80;
        if (((RHUnkSectorPoints *)((char *)sector + 4))->Unk0060ce80() >= 3)
        {
            FUN_004e8bd0(sector, sector->m_layer, true);
            FUN_004e99e0(sector, sector->m_layer, true);
        }
        else
            SBAssert(0, "P:\\Robin Hood\\RHfastfindgrid.cpp", 0x284d,
                // STRING: GAME 0x006afe08
                "ACHTUNG : Script sector with less than 3 points !");
        void *value = sector ? (char *)sector + 0xb8 : 0;
        (*(RHFastFindGateArray *)((char *)this + 0x40e0)).InsertLast(value, false);
    }
    FUN_005e20c0(file);
}

// deferred: unannotated pending reccmp #534
bool RHUnkPathGeometry::Unk004fbec0(SBFile &file, void *&value)
{
    RHFastFindGrid &grid = *(RHFastFindGrid *)this;
    unsigned short index;
    if (!file.m_bLoading)
    {
        if (value == 0)
            index = 0xffff;
        else
        {
            index = *(unsigned short *)((char *)value + 0x38);
            if (index >= grid.m_sectors.size())
            {
                SBAssert(1, "P:\\Robin Hood\\RHfastfindgrid.cpp", 0x2928,
                    // STRING: GAME 0x006afe3c
                    "VERBOTEN : Serializing unknown sector.");
            }
        }
        if (file.Access(&index, 2) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHfastfindgrid.cpp", 0x292c, "Serialize failed reason is %s", reason);
            return false;
        }
    }
    else
    {
        if (file.Access(&index, 2) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHfastfindgrid.cpp", 0x2930, "Serialize failed reason is %s", reason);
            return false;
        }
        if (index != 0xffff)
        {
            if (index >= grid.m_sectors.size())
                SBAssert(1, "P:\\Robin Hood\\RHfastfindgrid.cpp", 0x2936, "VERBOTEN : Serializing unknown sector.");
            value = grid.m_sectors.m_first[index];
            return true;
        }
        value = 0;
    }
    return true;
}

// deferred: unannotated pending reccmp #534
bool RHUnkPathGeometry::Unk004fc030(SBFile &file, void *&value)
{
    RHFastFindGrid &grid = *(RHFastFindGrid *)this;
    short index;
    if (!file.m_bLoading)
    {
        if (value == 0)
            index = -1;
        else
            index = grid.m_gates.Find(value);
        if (file.Access(&index, 2) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHfastfindgrid.cpp", 0x2953, "Serialize failed reason is %s", reason);
            return false;
        }
    }
    else
    {
        if (file.Access(&index, 2) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHfastfindgrid.cpp", 0x2957, "Serialize failed reason is %s", reason);
            return false;
        }
        if (index == -1)
        {
            value = 0;
            return true;
        }
        value = grid.m_gates.m_first[index];
    }
    return true;
}

// deferred: unannotated pending reccmp #534
bool RHUnkPathGeometry::Unk004fc180(SBFile &file, void *&value)
{
    RHFastFindGrid &grid = *(RHFastFindGrid *)this;
    short index;
    if (!file.m_bLoading)
    {
        if (value == 0)
            index = -1;
        else
            index = grid.m_projectionAreas.Find(value);
        if (file.Access(&index, 2) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHfastfindgrid.cpp", 0x2976, "Serialize failed reason is %s", reason);
            return false;
        }
    }
    else
    {
        if (file.Access(&index, 2) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHfastfindgrid.cpp", 0x297a, "Serialize failed reason is %s", reason);
            return false;
        }
        if (index == -1)
        {
            value = 0;
            return true;
        }
        value = grid.m_projectionAreas.m_first[index];
    }
    return true;
}

// deferred: unannotated pending reccmp #534
bool RHUnkPathGeometry::Unk004fc2d0(SBFile &file, void *&value)
{
    RHFastFindGrid &grid = *(RHFastFindGrid *)this;
    short index;
    if (!file.m_bLoading)
    {
        if (value == 0)
            index = -1;
        else
            index = *(short *)((char *)value + 4) - 1;
        if (file.Access(&index, 2) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHfastfindgrid.cpp", 0x2998, "Serialize failed reason is %s", reason);
            return false;
        }
    }
    else
    {
        if (file.Access(&index, 2) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHfastfindgrid.cpp", 0x299c, "Serialize failed reason is %s", reason);
            return false;
        }
        if (index == -1)
        {
            value = 0;
            return true;
        }
        value = grid.m_layers->m_obstacles[index];
    }
    return true;
}

// FUNCTION: GAME 0x004fc3b0
bool RHFastFindGrid::SerializeLinePointer(SBFile &file, void *&value)
{
    unsigned short layerIndex;
    short lineIndex;
    if (!file.m_bLoading)
    {
        if (value == 0)
        {
            lineIndex = -1;
            layerIndex = 0xffff;
        }
        else
        {
            bool found = false;
            for (unsigned short i = 0; i < m_layerCount; ++i)
            {
                unsigned short lineCount = m_layers[i].m_lineCount;
                for (unsigned short j = 0; j < lineCount; ++j)
                {
                    found = m_layers[i].m_lines[j] == value;
                    if (found)
                    {
                        layerIndex = i;
                        lineIndex = j;
                        break;
                    }
                }
                if (found)
                    break;
            }
        }
        if (file.Access(&layerIndex, 2) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHfastfindgrid.cpp", 0x29da, "Serialize failed reason is %s", reason);
            return false;
        }
        if (file.Access(&lineIndex, 2) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHfastfindgrid.cpp", 0x29db, "Serialize failed reason is %s", reason);
            return false;
        }
    }
    else
    {
        if (file.Access(&layerIndex, 2) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHfastfindgrid.cpp", 0x29df, "Serialize failed reason is %s", reason);
            return false;
        }
        if (file.Access(&lineIndex, 2) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHfastfindgrid.cpp", 0x29e0, "Serialize failed reason is %s", reason);
            return false;
        }
        if (lineIndex == -1)
        {
            value = 0;
            return true;
        }
        value = m_layers[layerIndex].m_lines[lineIndex];
    }
    return true;
}

// deferred: unannotated pending reccmp #534
void **RHScriptFXArray::Unk004fe420(void **first, void **last, void **destination)
{
    for (; first != last; ++first, ++destination)
        if (destination)
            *destination = *first;
    return destination;
}

// deferred: unannotated pending reccmp #534
unsigned int RHFastFindGateArray::FUN_0059fbc0()
{
    return Size();
}

void RHFastFindGrid::Emit(SBFile &file, void *&value)
{
    InitializeLiftsFromProtoStream(file);
    InitializeBuildingsFromProtoStream(file);
    InitializeSightObstaclesFromProtoStream(file);
    Serialize(file);
    DeleteStaticRepulsivePoint(0);
    InitializeTacticalInfosFromMissionStream(file);
    InitializeJumpStuffFromProtoStream(file);
    InitializeScriptStuffFromMissionStream(file);
    SerializeLinePointer(file, value);
}
