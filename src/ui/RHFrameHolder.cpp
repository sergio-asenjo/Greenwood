#include "RHFrameHolder.h"

// STRING: GAME 0x006b0008
#define g_frameHolderFile "P:\\Robin Hood\\RHframeholder.cpp"
// STRING: GAME 0x006b0028
#define g_frameHolderIndexError "Unable to open the sprite index file"
// STRING: GAME 0x006b0050
#define g_frameHolderIndex "Data\\RobinHood.dic"
// STRING: GAME 0x006b0064
#define g_frameHolderBankError "No Sprite Bank Found !!"
// STRING: GAME 0x006b007c
#define g_frameHolderBank "Data\\RobinHood.bks"
// STRING: GAME 0x006b0090
#define g_frameHolderSurfaceError "Unable to retrieve surface from resource"

// parked (69.61%): STL pair construction and dictionary cleanup differ.
// STUB: GAME 0x00504040
bool RHFrameHolder::InitializeSpriteBank()
{
    std::map<unsigned short, unsigned short> dictionaries;
    if (!FUN_005f6400(g_frameHolderBank))
        SBAssert(1, g_frameHolderFile, 86, g_frameHolderBankError);
    int opened = m_bank.FUN_005f5d60(g_frameHolderBank, 1);
    if (opened == 0)
    {
        m_e8 = true;
        m_bank.FUN_005f5090(g_frameHolderBank, 1);
    }
    else
        m_e8 = false;
    RHUnk005f4fc0 index;
    if (index.FUN_005f5090(g_frameHolderIndex, 1) != 0)
    {
        SBAssert(1, g_frameHolderFile, 107, g_frameHolderIndexError);
        return false;
    }
    index.Access(&m_b4, 4);
    unsigned short count;
    index.Access(&count, 2);
    for (unsigned short i = 0; i < count; ++i)
    {
        unsigned short id;
        index.Access(&id, 2);
        unsigned short slot = FUN_005051a0(id, index);
        dictionaries[i] = slot;
    }
    dictionaries[0xffff] = 0xffff;
    unsigned long frames;
    index.Access(&frames, 4);
    m_frames.Resize(frames);
    for (unsigned long frame = 0; frame < frames; ++frame)
    {
        unsigned char bytes[14];
        index.Access(bytes, 14);
        RHFrameHolderRecord record;
        record.m_width = *(unsigned short *)bytes;
        record.m_height = *(unsigned short *)(bytes + 2);
        record.m_size = *(unsigned long *)(bytes + 8);
        record.m_data = opened + ((*(unsigned long *)(bytes + 4) >> 1) * 2);
        record.m_0c = 0;
        record.m_10 = true;
        record.m_12 = dictionaries[*(unsigned short *)(bytes + 12)];
        m_frames.m_first[frame] = record;
    }
    return true;
}

// parked (46.79%): container/frame scheduling remains unmatched.
// STUB: GAME 0x00505cd0
unsigned long RHFrameHolder::AddRowFromResource(SBResourceManager *resources, unsigned long row, unsigned short &count, SBArray<SBGeoVector2D> &vectors)
{
    vectors.RemoveAll();
    unsigned long first;
    unsigned long surface;
    long y;
    if (m_rows.Find(row) != m_rows.End())
    {
        count = resources->FUN_00600550(row);
        first = m_rows.Insert(RHFrameHolderRowMap::Value(row, 0)).first.m_node->m_value;
        for (unsigned long i = first; i < first + count; ++i)
        {
            long x;
            if (!resources->FUN_00600920(row, i - first, surface))
                SBAssert(1, g_frameHolderFile, 1208, g_frameHolderSurfaceError);
            unsigned long data = FUN_00505980(surface, m_frames[i].m_size, m_frames[i].m_width, m_frames[i].m_height, x, y);
            operator delete((void *)data);
            vectors.InsertLast(SBGeoVector2D((float)x, (float)y));
        }
    }
    else
    {
        first = m_frames.Size();
        count = resources->FUN_00600550(row);
        m_frames.Resize(first + count);
        for (long i = first; i < first + count; ++i)
        {
            if (!resources->FUN_00600920(row, i - first, surface))
                SBAssert(1, g_frameHolderFile, 1236, g_frameHolderSurfaceError);
            m_frames[i].m_10 = false;
            m_frames[i].m_data = FUN_00505980(surface, m_frames[i].m_size, m_frames[i].m_width, m_frames[i].m_height, i, y);
            m_frames[i].m_12 = 0xffff;
            FUN_00504b10(m_frames[i].m_data, m_frames[i].m_size, g_pEngine->FUN_004d2340(15));
            vectors.InsertLast(SBGeoVector2D((float)i, (float)y));
        }
        m_rows[row] = first;
    }
    return first;
}

void RHFrameHolder::Emit(SBResourceManager *resources, SBArray<SBGeoVector2D> &vectors)
{
    unsigned short count;
    InitializeSpriteBank();
    AddRowFromResource(resources, 0, count, vectors);
}
