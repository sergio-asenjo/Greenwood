#include "SB.h"
#include <vector>

void RHSerializeName(SBFile &file, const char *name);

class RHShortBriefings
{
public:
    struct ShortBriefing
    {
        unsigned long m_0; // +0x00
        char m_4; // +0x04
        char m_pad5[3]; // +0x05
    };

    struct ShortBriefingVector
    {
        char m_allocator[4]; // +0x00
        ShortBriefing *m_first; // +0x04
        ShortBriefing *m_last; // +0x08
        ShortBriefing *m_end; // +0x0c

        ShortBriefing *begin() { return m_first; }
        ShortBriefing *end() { return m_last; }
        unsigned size() { return m_first == 0 ? 0 : m_last - m_first; }
    };

    ShortBriefingVector m_0; // +0x00
    ShortBriefingVector m_10; // +0x10

    bool Serialize(SBFile &file);
    static bool SerializeShortBriefing(SBFile &file, ShortBriefing &value);
    void Emit(SBFile &file);

    static bool SerializeContainer(SBFile &file, ShortBriefingVector &values,
                                   bool (*serialize)(SBFile &, ShortBriefing &))
    {
        if (!file.m_bLoading)
        {
            unsigned count = values.size();
            if (file.Access(&count, 4) < 0)
            {
                SBString *err = file.GetError();
                const char *reason = err->m_chars ? err->m_chars : "";
                SBAssert(0, "P:\\Robin Hood\\RHShortBriefings.cpp", 39, "Serialize failed reason is %s", reason);
                return false;
            }
            for (ShortBriefing *it = values.begin(); it != values.end(); ++it)
                if (!serialize(file, *it))
                    return false;
        }
        else
        {
            ShortBriefingVector &list = values;
            typedef std::vector<ShortBriefing> Vector;
            ShortBriefing *(Vector::*erase)(ShortBriefing *, ShortBriefing *) = &Vector::erase;
            (((Vector *)&list)->*erase)(list.begin(), list.end());
            unsigned count;
            if (file.Access(&count, 4) < 0)
            {
                SBString *err = file.GetError();
                const char *reason = err->m_chars ? err->m_chars : "";
                SBAssert(0, "P:\\Robin Hood\\RHShortBriefings.cpp", 60, "Serialize failed reason is %s", reason);
                return false;
            }
            while (count > 0)
            {
                ShortBriefing value;
                if (!serialize(file, value))
                    return false;
                void (Vector::*insert)(ShortBriefing *, unsigned, const ShortBriefing &) = &Vector::insert;
                (((Vector *)&list)->*insert)(list.end(), 1, value);
                --count;
            }
        }
        return true;
    }
};
