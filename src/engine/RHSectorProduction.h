#include "SB.h"
#include "Decomp.h"

// SIZE 0x08
class SBGeoPoint2D
{
public:
    float m_x; // 0x00
    float m_y; // 0x04
    SBGeoPoint2D();
    ~SBGeoPoint2D();
    SBGeoPoint2D(const SBGeoPoint2D &other);
    SBGeoPoint2D &operator=(const SBGeoPoint2D &other);
    bool Serialize(SBFile &file);
};

void RHSerializeName(SBFile &file, const char *name);

// SIZE 0x34
class RHSectorProduction
{
public:
    // SIZE 0x10
    struct Occupant
    {
        void *m_0; // +0x00
        SBGeoPoint2D m_point; // +0x04
        undefined2 m_c; // +0x0c
        undefined m_pad[2]; // +0x0e
        Occupant &operator=(const Occupant &other);
    };

    // SIZE 0x10
    struct Occupants
    {
        int m_grow; // +0x00
        Occupant *m_first; // +0x04
        Occupant *m_last; // +0x08
        Occupant *m_end; // +0x0c

        Occupant *begin() { return m_first; }
        Occupant *end() { return m_last; }
        unsigned size() { return m_first == 0 ? 0 : m_last - m_first; }
        void Destroy(Occupant *first, Occupant *last);
        void Insert(Occupant *where, unsigned count, const Occupant &value);
        void clear()
        {
            erase(begin(), end());
        }
        Occupant *erase(Occupant *first, Occupant *last)
        {
            Occupant *next = copy(last, end(), first);
            Destroy(next, end());
            m_last = next;
            return first;
        }
        static Occupant *copy(Occupant *next, Occupant *last, Occupant *first)
        {
            while (next != last)
            {
                *first = *next;
                ++first;
                ++next;
            }
            return first;
        }
        static Occupant *UninitializedCopy(const Occupant *first, const Occupant *last, Occupant *out);
        static void UninitializedFill(Occupant *first, unsigned count, const Occupant &value);
        static void Fill(Occupant *first, Occupant *last, const Occupant &value);
        static void DestroyElements(Occupant *first, Occupant *last);
        static Occupant *Allocate(int count);
    };

    int m_0; // +0x00
    unsigned short m_4; // +0x04
    undefined m_pad6[0x16]; // +0x06
    Occupants m_occupants; // +0x1c
    unsigned short m_2c; // +0x2c
    unsigned short m_2e; // +0x2e
    undefined m_30; // +0x30

    bool Serialize(SBFile &file);
    static bool SerializeOccupant(SBFile &file, Occupant &occupant);
    static bool FUN_005818c0(SBFile &file, Occupants &occupants,
                            bool (*serialize)(SBFile &, Occupant &));
    void Emit(SBFile &file);
};

bool FUN_00453da0(SBFile &file, void *&value);
void FUN_0045a850(RHSectorProduction::Occupant *out, const RHSectorProduction::Occupant &value);
