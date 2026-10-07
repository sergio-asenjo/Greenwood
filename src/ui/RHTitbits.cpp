#include "RHTitbits.h"

// Parked: list/file register allocation and cursor scheduling remain different.
// STUB: GAME 0x005c3a60
bool RHTitbits::Serialize(SBFile &file)
{
    unsigned int count;
    unsigned int i;
    RHTitbit elem;

    // STRING: GAME 0x6b8bfc
    RHSerializeName(file, "RHTitbits");

    if (file.Access(&m_ac, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0,
                 // STRING: GAME 0x6b8bd8
                 "P:\\Robin Hood\\RHtitbit.cpp",
                 621,
                 "Serialize failed reason is %s",
                 reason);
        return false;
    }

    if (!file.m_bLoading)
    {
        count = m_list.m_count;
        if (file.Access(&count, 4) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHtitbit.cpp", 626, "Serialize failed reason is %s", reason);
            return false;
        }
    }
    else
    {
        RHTitbitList &list = m_list;
        typedef RHTitbitIterator (RHTitbitList::*Erase)(RHTitbitIterator, RHTitbitIterator);
        (list.*(Erase)&RHTitbitList::Clear)(RHTitbitIterator(list.m_head->m_next), RHTitbitIterator(list.m_head));
        list.m_valid = 1;
        if (file.Access(&count, 4) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHtitbit.cpp", 631, "Serialize failed reason is %s", reason);
            return false;
        }
        list.Resize(count);
        m_a4 = 0xf;
        m_a8 = 10.0f;
    }

    RHTitbitNode *node;
    for (i = 0; i < count; i++)
    {
        if (!file.m_bLoading)
        {
            RHTitbitList &list = m_list;
            list.At(i);
            node = list.m_cur;
            elem = node->m_data;
        }

        if (file.Access(&elem.m_00, 4) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHtitbit.cpp", 647, "Serialize failed reason is %s", reason);
            return false;
        }
        if (file.Access(&elem.m_0a, 2) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHtitbit.cpp", 648, "Serialize failed reason is %s", reason);
            return false;
        }
        if (file.Access(&elem.m_08, 2) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHtitbit.cpp", 649, "Serialize failed reason is %s", reason);
            return false;
        }
        if (file.Access(&elem.m_06, 2) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHtitbit.cpp", 650, "Serialize failed reason is %s", reason);
            return false;
        }
        if (file.Access(&elem.m_04, 2) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHtitbit.cpp", 651, "Serialize failed reason is %s", reason);
            return false;
        }
        if (file.Access(&elem.m_24, 4) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHtitbit.cpp", 652, "Serialize failed reason is %s", reason);
            return false;
        }
        if (file.Access(&elem.m_24, 4) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHtitbit.cpp", 653, "Serialize failed reason is %s", reason);
            return false;
        }
        if (file.Access(&elem.m_u14.m_14s, 2) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHtitbit.cpp", 654, "Serialize failed reason is %s", reason);
            return false;
        }
        if (file.Access(&elem.m_28, 1) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHtitbit.cpp", 655, "Serialize failed reason is %s", reason);
            return false;
        }
        if (file.Access(&elem.m_2c, 4) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHtitbit.cpp", 656, "Serialize failed reason is %s", reason);
            return false;
        }

        g_pEngine->SerializeNestedA(file, &elem.m_0c);
        g_pEngine->SerializeNestedB(file, &elem.m_10);
        ((RHUnk005df510 *)((char *)&elem + 0x1c))->Serialize(file);

        if (file.m_bLoading)
        {
            m_list.Seek(i);
            m_list.m_cur->m_data = elem;
        }
    }

    return true;
}

void RHTitbits::Emit(SBFile &file)
{
    Serialize(file);
}
