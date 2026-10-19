// RHGroundMark.cpp — translation unit with __FILE__ evidence at 0x0051c380
// ("P:\Robin Hood\RHgroundmark.cpp", symbols/functions-by-file.tsv).
//
// BINDING (0x0051c380 -> RHGroundMark::Serialize(SBFile&)):
//   - TU:        rhgroundmark.cpp (embedded __FILE__ string 0x006b0638).
//   - Class:     RHGroundMark (symbols/oracle-correlation.tsv: rhgroundmark ->
//                class RHGroundMark, 11 methods).
//   - Method:    RHGroundMark::Serialize(SBFile&) — the only serializer in the
//                TU (symbols/mac-functions-by-file.tsv: 0x0013946c Serialize).
//   - Signals:
//       * the first act writes the tag "RHGroundMark" (string 0x006b0658) via
//         0x005e1b70;
//       * a write path (file.m_bLoading == 0) that walks the SBList at this+0x14
//         and serialises each RHGroundInfo (an 8-byte SBGeoPoint2D plus two
//         unsigned shorts) — copy via 0x005fc090 (SBGeoPoint2D::operator=) and
//         the two Access calls;
//       * a read path that clears the list via 0x0051c7c0, reads a count, then
//         loops serialising each element and linking a new node through the
//         inlined list insert: operator new 0x006428b5 (size 0x14) plus the
//         RHGroundInfo copy ctor 0x00606040 (calls SBGeoPoint2D copy ctor
//         0x005fc040);
//       * the EH frame (handler 0x00663439) around the RHGroundInfo local at
//         [esp+0x20] (point ctor 0x005fc030 / dtor 0x005fc080).
//     This matches the Mac oracle's structure (SBList::GoTo on the write path,
//     std::list/__clear + insert on the read path).
//
// STATUS: BLOCKED — not a byte match (binding is solid; logic reproduced).
// The residual is the stack-frame / EH layout, the same family as
// RHTitbits::Serialize:
//   * target frame:  `sub esp, 0x1c`; locals at [esp+0x10] (count),
//     [esp+0x14], [esp+0x18], [esp+0x1c] and the 12-byte RHGroundInfo at
//     [esp+0x20]; EH state dword at [esp+0x34].
//   * VC6 at this source shape emits `sub esp, 0x14`: it elides two of the
//     three 4-byte slots before the element local, so every [esp+N] shifts by 8.
//     Isolate-probes (two out-of-line object locals, by-value insert result,
//     explicit iterator temporaries, `this` in a local reference) all reproduce
//     a 0x14 frame; the target's extra 8 bytes are VC6 EH bookkeeping for the
//     inlined list insert that this compiler does not materialise from any
//     tested source shape.
//   * Register residual (a consequence of the frame): target keeps `this` in
//     `esi` and the write-loop counter in `ebp`; we get `this` in `ebp` and the
//     counter in `ebx`.
// Kept as STUB so reccmp does not count it; the reconstruction is for reference.

#include "RHGroundMark.h"

// STUB: GAME 0x0051c380
bool RHGroundMark::Serialize(SBFile &file)
{
    RHGroundInfo info;
    RHGroundInfoIter clearOut;

    // STRING: GAME 0x6b0658
    RHSerializeName(file, "RHGroundMark");

    if (!file.m_bLoading)
    {
        unsigned long count = m_list.m_count;
        if (file.Access(&count, 4) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0,
                     // STRING: GAME 0x6b0638
                     "P:\\Robin Hood\\RHgroundmark.cpp",
                     197,
                     "Serialize failed reason is %s",
                     reason);
            return false;
        }
        for (unsigned int i = 0; i < count; i++)
        {
            m_list.GoTo(i);
            info = *(RHGroundInfo *)((char *)m_list.m_cur + 8);
            if (file.Access(&info.m_a, 2) < 0)
            {
                SBString *err = file.GetError();
                const char *reason = err->m_chars ? err->m_chars : "";
                SBAssert(0, "P:\\Robin Hood\\RHgroundmark.cpp", 202, "Serialize failed reason is %s", reason);
                return false;
            }
            if (file.Access(&info.m_b, 2) < 0)
            {
                SBString *err = file.GetError();
                const char *reason = err->m_chars ? err->m_chars : "";
                SBAssert(0, "P:\\Robin Hood\\RHgroundmark.cpp", 203, "Serialize failed reason is %s", reason);
                return false;
            }
            info.m_point.Serialize(file);
        }
    }
    else
    {
        m_list.Clear(&clearOut, m_list.m_head->m_next, m_list.m_head);
        m_list.m_valid = 1;
        unsigned long count;
        if (file.Access(&count, 4) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHgroundmark.cpp", 211, "Serialize failed reason is %s", reason);
            return false;
        }
        for (unsigned int i = 0; i < count; i++)
        {
            if (file.Access(&info.m_a, 2) < 0)
            {
                SBString *err = file.GetError();
                const char *reason = err->m_chars ? err->m_chars : "";
                SBAssert(0, "P:\\Robin Hood\\RHgroundmark.cpp", 214, "Serialize failed reason is %s", reason);
                return false;
            }
            if (file.Access(&info.m_b, 2) < 0)
            {
                SBString *err = file.GetError();
                const char *reason = err->m_chars ? err->m_chars : "";
                SBAssert(0, "P:\\Robin Hood\\RHgroundmark.cpp", 215, "Serialize failed reason is %s", reason);
                return false;
            }
            info.m_point.Serialize(file);
            m_list.insert(m_list.end(), info);
            m_list.m_valid = 1;
        }
    }
    return true;
}

// FUNCTION: GAME 0x0051c720
void RHGroundInfoList::Dispose()
{
    RHGroundInfoNode *last = m_head;
    RHGroundInfoNode *current = last->m_next;
    while (current != last)
    {
        RHGroundInfoNode *node = current;
        current = current->m_next;
        node->m_prev->m_next = node->m_next;
        node->m_next->m_prev = node->m_prev;
        node->m_data.~RHGroundInfo();
        ::operator delete(node);
        --m_count;
    }
    ::operator delete(m_head);
    m_head = 0;
    m_count = 0;
}

// FUNCTION: GAME 0x0051c780
RHGroundInfoIter RHGroundInfoList::Erase(RHGroundInfoIter position)
{
    RHGroundInfoNode *node = (RHGroundInfoNode *)(position++).m_p;
    node->m_prev->m_next = node->m_next;
    node->m_next->m_prev = node->m_prev;
    node->m_data.~RHGroundInfo();
    ::operator delete(node);
    --m_count;
    return position;
}

// FUNCTION: GAME 0x0051c7c0
void *RHGroundInfoList::Clear(void *out, RHGroundInfoNode *first, RHGroundInfoNode *last)
{
    while (first != last)
    {
        RHGroundInfoNode *node = first;
        first = first->m_next;
        node->m_prev->m_next = node->m_next;
        node->m_next->m_prev = node->m_prev;
        node->m_data.~RHGroundInfo();
        ::operator delete(node);
        --m_count;
    }
    *(RHGroundInfoNode **)out = first;
    return out;
}

void RHGroundMark::Emit(SBFile &file)
{
    Serialize(file);
    m_list.Dispose();
    m_list.Erase(m_list.end());
    m_list.Clear(0, 0, 0);
}
