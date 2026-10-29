#include "SB.h"
#include "RHGameWidgetLifetime.h"
#include <vector>

void RHSerializeName(SBFile &file, const char *name);
class RHMenuWindow;
class SBGeoBoundingBox2D;

class RHShortBriefingsWidgetBase
{
public:
    RHShortBriefingsWidgetBase();
    ~RHShortBriefingsWidgetBase();
    unsigned m_vptr;
    char m_04[0x7c];
};

class RHShortBriefingsRenderer
{
public:
    RHShortBriefingsRenderer();
    ~RHShortBriefingsRenderer();
    char m_00[0x4c];
};

typedef RHGameLifetime00515f00 RHShortBriefingsText;

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
        ShortBriefingVector(const std::allocator<ShortBriefing> &allocator = std::allocator<ShortBriefing>())
            : m_allocator(allocator), m_first(0), m_last(0), m_end(0) {}
        ~ShortBriefingVector()
        {
            typedef std::vector<ShortBriefing> Vector;
            ((Vector *)this)->~Vector();
        }
        std::allocator<ShortBriefing> m_allocator; // +0x00
        ShortBriefing *m_first; // +0x04
        ShortBriefing *m_last; // +0x08
        ShortBriefing *m_end; // +0x0c

        ShortBriefing *begin() { return m_first; }
        ShortBriefing *end() { return m_last; }
        unsigned size() { return m_first == 0 ? 0 : m_last - m_first; }
    };

    ShortBriefingVector m_0; // +0x00
    ShortBriefingVector m_10; // +0x10
    ShortBriefingVector m_20; // +0x20
    RHShortBriefingsText m_30; // +0x30
    void *m_fc; // +0xfc

    RHShortBriefings(bool load);
    ~RHShortBriefings();
    void AddShortBriefing(unsigned long id, bool first);

    bool Serialize(SBFile &file);
    bool HasShortBriefing(unsigned long id) const;
    unsigned GetShortBriefingNumber(bool first) const;
    std::basic_string<unsigned short> GetShortBriefingText(const ShortBriefing &value) const;
    void CreateWidgets(RHMenuWindow *window, const SBGeoBoundingBox2D &box);
    void DestroyWidgets();
    void DoneShortBriefing(unsigned long id);
    void FUN_005a28c0(RHMenuWindow *window, SBGeoBoundingBox2D &box, bool mode);
    void FUN_005a2630(RHMenuWindow *window, SBGeoBoundingBox2D &box);
    static bool IsSearchedShortBriefing(const ShortBriefing &value);
    static unsigned long ulCurID;
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
