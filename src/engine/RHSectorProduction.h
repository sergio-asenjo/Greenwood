#include "SB.h"
#include "Decomp.h"
#include <vector>

// SIZE 0x08
class SBGeoVector2D;

#ifndef SBGEO_POINT2D_VIEW
#define SBGEO_POINT2D_VIEW
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
    SBGeoVector2D Unk005fc110(const SBGeoPoint2D &other) const;
    SBGeoPoint2D Unk005fc190(const SBGeoPoint2D &other) const;
    SBGeoPoint2D FUN_005fc200(const SBGeoPoint2D &other) const;
    float FUN_005fc700(float scale) const;
};
#endif

void RHSerializeName(SBFile &file, const char *name);

class RHElementActorPC;
class RHMission;

// SIZE 0x34
class RHSectorProduction
{
public:
    // SIZE 0x10
    struct Occupant
    {
        void *m_0; // +0x00
        SBGeoPoint2D m_point; // +0x04
        unsigned short m_c; // +0x0c
        Occupant &operator=(const Occupant &other);
    };

    // SIZE 0x10
    class Occupants : public std::vector<Occupant>
    {
    public:
        Occupant *begin() { return _First; }
        Occupant *end() { return _Last; }
        unsigned size() { return _First == 0 ? 0 : _Last - _First; }
        void Destroy(Occupant *first, Occupant *last);
        void Insert(Occupant *where, unsigned count, const Occupant &value);
        void clear()
        {
            erase(begin(), end());
        }
        void ClearAll()
        {
            Occupant *(*copy)(Occupant *, Occupant *, Occupant *) = std::copy;
            Occupant *next = copy(end(), end(), begin());
            Destroy(next, end());
            _Last = next;
        }
        Occupant *erase(Occupant *first, Occupant *last)
        {
            Occupant *next = copy(last, end(), first);
            Destroy(next, end());
            _Last = next;
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

    // SIZE 0x10
    struct Point
    {
        SBGeoPoint2D m_point; // +0x00
        unsigned short m_8; // +0x08
        unsigned short m_a; // +0x0a
        unsigned short m_c; // +0x0c
    };
    typedef std::vector<Point> Points;

    int m_0; // +0x00
    unsigned short m_4; // +0x04
    int m_8; // +0x08
    Points m_points; // +0x0c
    Occupants m_occupants; // +0x1c
    unsigned short m_2c; // +0x2c
    unsigned short m_2e; // +0x2e
    char m_30; // +0x30

    RHSectorProduction(int type);
    RHSectorProduction(const RHSectorProduction &value);
    // FUNCTION: GAME 0x00456960
    ~RHSectorProduction() {}
    RHSectorProduction &operator=(const RHSectorProduction &value);

    bool Serialize(SBFile &file);
    static bool SerializeOccupant(SBFile &file, Occupant &occupant);
    static bool FUN_005818c0(SBFile &file, Occupants &occupants,
                            bool (*serialize)(SBFile &, Occupant &));
    static int FUN_00580350(int type);
    int FUN_005803c0();
    unsigned int FUN_00580500();
    unsigned int FUN_005806b0() const;
    void FUN_00580430();
    void FUN_00580520();
    void FUN_005804e0();
    RHElementActorPC *FUN_005806c0() const;
    bool FUN_00580940(const RHElementActorPC *pc) const;
    char FUN_00580960() const;
    void FUN_00580b70();
    void FUN_00580d20(const RHMission *mission);
    void FUN_00580dc0();
    void FUN_00580e80();
    void FUN_00581020(const RHMission *mission);
    void FUN_005810c0(const RHMission *mission);
    void FUN_00581180(const RHMission *mission);
    void Emit(SBFile &file);
};

bool FUN_00453da0(SBFile &file, void *&value);
