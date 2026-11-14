#ifndef SB_DRAW_MANAGER_H
#define SB_DRAW_MANAGER_H

#include <utility>
#include <string>
#include "SBDrawManagerCore.h"

class SBGeoVector2D;
class RHUnk00613e90;
class RHMobileUnk00607da0;

class SBDrawUnk005fc3b0Point
{
public:
    SBDrawUnk005fc3b0Point();
    ~SBDrawUnk005fc3b0Point();
    float m_x;
    float m_y;
};

struct SBDrawUnk005eec00Edge
{
    unsigned char m_00;
    char m_01[3];
    int m_04;
    unsigned long m_08;
    int m_0c;
    unsigned long m_10;
    int m_14;
    int m_18;
};

template<class T> class SBList;

#ifndef SBDRAW_MANAGER_OWNER_LAYOUT
class RHUnk005ef320
{
public:
    unsigned short Unk(int red, int green, int blue);
    bool FUN_005ef380(int value);
    bool FUN_005e3f40(const std::string &);
    bool FUN_005e3f70();
    bool FUN_005e5890(unsigned long, void **, unsigned long);
    void FUN_005e57e0(unsigned, SBGeoVector2D &);
    bool FUN_005e5bd0(unsigned long, void *);
    bool FUN_005e5d30(unsigned long);
    bool FUN_005ee640(SBList<SBGeoPoint2D> &, const SBGeoVector2D &);
    bool FUN_005eec00(unsigned long, unsigned long, void *, unsigned long,
        unsigned long, unsigned long, unsigned long, unsigned long);
    bool FUN_005e4810(unsigned short width, unsigned short height, unsigned short depth);
    bool FUN_005ed270(const RHMobileUnk00607da0 &bounds);
};
#endif

class SBDrawUnk005f0090Node
{
public:
    char m_pad0[0x0c];
    unsigned long m_key;
    void *m_object;
    unsigned short m_width;
    unsigned short m_height;
};

class SBDrawUnk005f0090
{
public:
    char m_pad0[4];
    SBDrawUnk005f0090Node *m_head;
    SBDrawUnk005f0090Node *FUN_005f0090(const unsigned long &);
    SBDrawUnk005f0090Node *FUN_005f01a0(const unsigned long &);
};

struct SBDrawUnk005efc10Iterator
{
    SBDrawUnk005f0090Node *m_node;
    SBDrawUnk005efc10Iterator() {}
    SBDrawUnk005efc10Iterator(SBDrawUnk005f0090Node *node) : m_node(node) {}
    bool operator==(const SBDrawUnk005efc10Iterator &other) const { return m_node == other.m_node; }
    bool operator!=(const SBDrawUnk005efc10Iterator &other) const { return m_node != other.m_node; }
    void FUN_005effc0();
    SBDrawUnk005efc10Iterator &operator++()
    {
        FUN_005effc0();
        return *this;
    }
    SBDrawUnk005efc10Iterator operator++(int)
    {
        SBDrawUnk005efc10Iterator previous = *this;
        FUN_005effc0();
        return previous;
    }
};

struct SBDrawUnk005e4f70Surface
{
    void *m_object;
    unsigned short m_width;
    unsigned short m_height;
    unsigned long m_color;
    unsigned long m_0c;
    bool m_locked;
    void *m_section;
};

typedef std::pair<const unsigned long, SBDrawUnk005e4f70Surface> SBDrawUnk005e4f70Pair;
typedef std::pair<SBDrawUnk005efc10Iterator, bool> SBDrawUnk005ef440Result;

struct SBDrawDecNode
{
    static SBDrawDecNode *&Left(SBDrawDecNode *node) { return node->m_00; }
    SBDrawDecNode *m_00;
    SBDrawDecNode *m_04;
    SBDrawDecNode *m_08;
    unsigned long m_0c;
    int m_10;
    int m_14;
    int m_18;
    int m_1c;
    int m_20;
    int m_24;
    int m_28;
};

struct SBDrawSurfaceEntry;

class SBDrawUnk005efc10
{
public:
    char m_00[4];
    SBDrawUnk005f0090Node *m_head;
    unsigned m_08;
    unsigned m_size;
    void FUN_005e3ed0();
    ~SBDrawUnk005efc10();
    SBDrawUnk005efc10Iterator FUN_005efa90(SBDrawUnk005efc10Iterator, SBDrawUnk005efc10Iterator);
    SBDrawUnk005efc10Iterator FUN_005ef570(SBDrawUnk005efc10Iterator);
    typedef SBDrawDecNode Node;
    static Node *&Left(Node *node) { return node->m_00; }
    static Node *&Parent(Node *node) { return node->m_04; }
    static Node *&Right(Node *node) { return node->m_08; }
    static int &Color(Node *node) { return node->m_28; }
    Node *&EraseLeftmost() { return *(Node **)m_head; }
    Node *&EraseRightmost() { return *(Node **)((char *)m_head + 8); }
    void FUN_005efc30(SBDrawUnk005f0090Node *);
    SBDrawUnk005f0090Node *&Root() { return *(SBDrawUnk005f0090Node **)((char *)m_head + 4); }
    SBDrawUnk005f0090Node *&Leftmost() { return *(SBDrawUnk005f0090Node **)m_head; }
    SBDrawUnk005f0090Node *&Rightmost() { return *(SBDrawUnk005f0090Node **)((char *)m_head + 8); }
    SBDrawUnk005efc10Iterator Begin() { return SBDrawUnk005efc10Iterator(Leftmost()); }
    SBDrawUnk005efc10Iterator End() { return SBDrawUnk005efc10Iterator(m_head); }
    SBDrawUnk005efc10Iterator FUN_005efc10(const unsigned long &);
    SBDrawUnk005efc10Iterator FUN_005efbc0(const unsigned long &);
    SBDrawUnk005efc10Iterator FUN_005f0070(const unsigned long &);
    SBDrawUnk005ef440Result FUN_005ef440(const SBDrawUnk005e4f70Pair &);
    SBDrawUnk005efc10Iterator FUN_005efcc0(SBDrawDecNode *, SBDrawDecNode *, const SBDrawSurfaceEntry &);
    SBDrawDecNode *&InsertRoot() { return ((SBDrawDecNode *)m_head)->m_04; }
    void Lrotate(SBDrawDecNode *);
    void Rrotate(SBDrawDecNode *);
};

class SBDrawUnk005e8450
{
public:
    bool FUN_005e7710(unsigned short *, unsigned short *, unsigned short *, unsigned,
        unsigned, unsigned, unsigned, unsigned);
    bool FUN_005e8110(unsigned short *, unsigned short *, unsigned short *, unsigned,
        unsigned, unsigned, unsigned, unsigned, unsigned short);
    bool FUN_005e7880(void *, void *, void *, int, int, int, int, int, unsigned short);
    bool FUN_005e78c0(unsigned short *, unsigned short *, unsigned short *, unsigned, unsigned, unsigned, unsigned, unsigned);
    bool FUN_005e7a30(unsigned short *, unsigned short *, unsigned short *, unsigned, unsigned, unsigned, unsigned, unsigned, unsigned short);
    bool FUN_005e7bc0(unsigned short *, unsigned short *, unsigned short *, unsigned, unsigned, unsigned, unsigned, unsigned);
    bool FUN_005e7de0(unsigned short *, unsigned short *, unsigned short *, unsigned, unsigned, unsigned, unsigned, unsigned);
    bool FUN_005e7fa0(unsigned short *, unsigned short *, unsigned short *, unsigned, unsigned, unsigned, unsigned, unsigned);
    bool FUN_005e82a0(unsigned short *, unsigned short *, unsigned short *, unsigned, unsigned, unsigned, unsigned, unsigned);
    bool FUN_005e7d30(void *, void *, void *, int, int, int, int, int, unsigned short);
    bool FUN_005e7d70(void *, void *, void *, int, int, int, int, int, unsigned short);
    bool FUN_005e7da0(void *, void *, void *, int, int, int, int, int, unsigned short);
    bool FUN_005e7f60(void *, void *, void *, int, int, int, int, int, unsigned short);
    bool FUN_005e8410(void *, void *, void *, int, int, int, int, int, unsigned short);
    bool FUN_005e8450(void *source, void *destination, void *alpha, int width,
        int height, int sourceStride, int destinationStride, int arg8, unsigned short arg9);
    bool FUN_005e84a0(void *, void *, void *, int, int, int, int, int, unsigned short);
    bool FUN_005e84e0(void *source, void *destination, void *alpha, unsigned short arg4,
        int width, int height, int sourceStride, int destinationStride,
        float stretchX, float stretchY);
    bool FUN_005e85b0(void *source, void *destination, void *alpha, unsigned short arg4,
        int width, int height, int sourceStride, int destinationStride,
        float stretchX, float stretchY);
    bool FUN_005e8670(void *source, void *destination, void *alpha, unsigned short arg4,
        int width, int height, int sourceStride, int destinationStride,
        float stretchX, float stretchY);
    bool FUN_005e8740(unsigned short *, unsigned short *, unsigned short *, unsigned,
        unsigned, unsigned, unsigned, float, float);
    bool FUN_005e8b10(unsigned short *, unsigned short *, unsigned short *, unsigned short,
        unsigned, unsigned, unsigned, unsigned, float, float);
    bool FUN_005e8f20(unsigned short *, unsigned short *, unsigned short *, unsigned,
        unsigned, unsigned, unsigned, float, float);
    bool FUN_005e93c0(unsigned short *, unsigned short *, unsigned short *, unsigned,
        unsigned, unsigned, unsigned, float, float);
    bool FUN_005e99f0(unsigned short *, unsigned short *, unsigned short *, unsigned,
        unsigned, unsigned, unsigned, float, float);
    bool FUN_005e9dc0(unsigned short *, unsigned short *, unsigned short *, unsigned short,
        unsigned, unsigned, unsigned, unsigned, float, float);
    bool FUN_005ea1d0(unsigned short *, unsigned short *, unsigned short *, unsigned,
        unsigned, unsigned, unsigned, float, float);
    bool FUN_005ea670(unsigned short *, unsigned short *, unsigned short *, unsigned,
        unsigned, unsigned, unsigned, float, float);
    bool FUN_005eb450(unsigned short *, unsigned short *, unsigned short, unsigned,
        unsigned, unsigned, unsigned, float, float);
    bool FUN_005eb800(unsigned short *, unsigned short *, unsigned short, unsigned,
        unsigned, unsigned, unsigned, float, float);
    bool FUN_005e92f0(void *source, void *destination, void *alpha, unsigned short arg4,
        int width, int height, int sourceStride, int destinationStride,
        float stretchX, float stretchY);
    bool FUN_005e9790(void *source, void *destination, void *alpha, unsigned short arg4,
        int width, int height, int sourceStride, int destinationStride,
        float stretchX, float stretchY);
    bool FUN_005e9860(void *source, void *destination, void *alpha, unsigned short arg4,
        int width, int height, int sourceStride, int destinationStride,
        float stretchX, float stretchY);
    bool FUN_005e9920(void *source, void *destination, void *alpha, unsigned short arg4,
        int width, int height, int sourceStride, int destinationStride,
        float stretchX, float stretchY);
    bool FUN_005ea5a0(void *source, void *destination, void *alpha, unsigned short arg4,
        int width, int height, int sourceStride, int destinationStride,
        float stretchX, float stretchY);
    bool FUN_005ec230(void *, void *, int, int, int, int, float, float, unsigned short, unsigned short);
    bool FUN_005ec320(void *, void *, int, int, int, int, float, float, unsigned short, unsigned short);
    bool FUN_005ec410(void *, void *, int, int, int, int, float, float, unsigned short, unsigned short);
    bool FUN_005ec500(void *, void *, int, int, int, int, float, float, unsigned short, unsigned short);
};

struct SBDrawUnk005e5ec0Surface
{
    void **m_vtable;
};

#include "SBDrawUnk005e5ec0.h"

void FUN_006220ec(void *, void *, int, int, int, int, unsigned, unsigned);
void FUN_00622028(void *, void *, int, int, int, int, unsigned, unsigned);
void FUN_006222bc(void *, void *, int, int, int, int, unsigned, unsigned);
void FUN_00622550(void *, void *, int, int, int, int, unsigned, unsigned);
void FUN_00623598(void *, void *, int, int, int, int, unsigned, unsigned);
void FUN_006221e4(void *, void *, int, int, int, int, unsigned, unsigned);
void FUN_00622380(void *, void *, int, int, int, int, unsigned, unsigned);
void FUN_00622478(void *, void *, int, int, int, int, unsigned, unsigned);
void FUN_0062261c(void *, void *, int, int, int, int, unsigned, unsigned);
void FUN_00622720(void *, void *, int, int, int, int, unsigned, unsigned);
void FUN_00623668(void *, void *, int, int, int, int, unsigned, unsigned);
void FUN_0062376c(void *, void *, int, int, int, int, unsigned, unsigned);

void FUN_00622800(void *, void *, void *, int, int, int, int, int);
void FUN_00622924(void *, void *, void *, int, int, int, int, int);
void FUN_00622a7c(void *, void *, void *, int, int, int, int, int);
void FUN_00622bc0(void *, void *, void *, int, int, int, int, int);
void FUN_00622ca0(void *, void *, void *, int, int, int, int, int);
void FUN_00622db4(void *, void *, void *, int, int, int, int, int);
void FUN_00622eb4(void *, void *, void *, int, int, int, int, int);
void FUN_00622fd4(void *, void *, void *, int, int, int, int, int);
void FUN_00623128(void *, void *, void *, int, int, int, int, int);
void FUN_00623268(void *, void *, int, int, int, int);
void FUN_00623360(void *, void *, int, int, int, int);
void FUN_0062348c(void *, void *, int, int, int, int);
void FUN_00623850(void *, void *, void *, int, int, int, int, int);
void FUN_00623978(void *, void *, void *, int, int, int, int, int);
void FUN_00623ad4(void *, void *, void *, int, int, int, int, int);
void FUN_00623c1c(void *, void *, void *, int, int, int, int, int);
void FUN_00623cfc(void *, void *, void *, int, int, int, int, int);
void FUN_00623e10(void *, void *, void *, int, int, int, int, int);
void FUN_00623f10(void *, void *, void *, int, int, int, int, int);
void FUN_00624030(void *, void *, void *, int, int, int, int, int);
void FUN_00624184(void *, void *, void *, int, int, int, int, int);
void FUN_006242c4(void *, void *, int, int, int, int);
void FUN_006243c0(void *, void *, int, int, int, int);
void FUN_006244ec(void *, void *, int, int, int, int);

#ifdef SBDRAW_MANAGER_OWNER_LAYOUT
#include <list>
#include <string>
#include <new>
#include "RHCivilianProfile.h"
#include "SBGeoBoundingBox2DCore.h"

struct SBDrawTreeNode;
extern SBDrawTreeNode *g_unk0x006c11dc;
extern unsigned g_unk0x006c11d8;

inline SBDrawUnk005efc10::~SBDrawUnk005efc10()
{
    SBDrawUnk005efc10Iterator first(Leftmost());
    SBDrawUnk005efc10Iterator last(m_head);
    FUN_005efa90(first, last);
    operator delete(m_head);
    m_head = 0;
    m_size = 0;
    {
        std::_Lockit lock;
        if (--g_unk0x006c11d8 == 0) {
            operator delete(g_unk0x006c11dc);
            g_unk0x006c11dc = 0;
        }
    }
}

class SBDrawDriverList
{
public:
    ~SBDrawDriverList()
    {
        typedef std::list<std::string>::iterator (std::list<std::string>::*Erase)(
            std::list<std::string>::iterator, std::list<std::string>::iterator);
        Erase erase = &std::list<std::string>::erase;
        (m_list.*erase)(m_list.begin(), m_list.end());
    }
    void Add(const std::string &name)
    {
        m_list.push_back(name);
        m_dirty = true;
    }
    std::list<std::string> m_list;
    std::list<std::string>::iterator m_current;
    bool m_dirty;
    char m_pad11[0x0f];
    RHProfileText m_text;
};

class RHUnk005ef320
{
public:
    unsigned short Unk(int red, int green, int blue);
    bool FUN_005ef380(int value);
    bool FUN_005e3f40(const std::string &);
    bool FUN_005e3f70();
    bool FUN_005e5890(unsigned long, void **, unsigned long);
    void FUN_005e57e0(unsigned, SBGeoVector2D &);
    bool FUN_005e5bd0(unsigned long, void *);
    bool FUN_005e5d30(unsigned long);
    bool FUN_005ee640(SBList<SBGeoPoint2D> &, const SBGeoVector2D &);
    bool FUN_005eec00(unsigned long, unsigned long, void *, unsigned long,
        unsigned long, unsigned long, unsigned long, unsigned long);
    bool FUN_005e4810(unsigned short width, unsigned short height, unsigned short depth);
    bool FUN_005ed270(const RHMobileUnk00607da0 &bounds);
    ~RHUnk005ef320();

    char m_section[0x18];
    SBDrawDriverList m_driverList;
    int m_48;
    int m_4c;
    unsigned long m_50;
    SBDrawUnk005efc10 m_surfaces;
    std::list<unsigned long> m_released;
    unsigned long m_70;
    unsigned long m_74;
    unsigned long m_consoleSurface;
    unsigned char m_7c;
    char m_pad7d[0x03];
    unsigned char m_fullscreen;
    unsigned char m_81;
    char m_pad82[0x02];
    SBDrawUnk005e5ec0Surface *m_84;
    SBDrawUnk005e5ec0Surface *m_88;
    SBDrawUnk005e5ec0Surface *m_8c;
    char m_90[0x6c];
    void *m_instance;
    void *m_window;
    char m_104[0x08];
    unsigned short m_depth;
    unsigned short m_width;
    unsigned short m_height;
    unsigned char m_112;
    unsigned char m_113;
    unsigned char m_114;
    unsigned char m_115;
    char m_pad116[0x02];
    SBGeoBoundingBox2D m_bounds;
    char m_12c[0x04];
    unsigned long m_130;
    SBDrawUnk005eec00Edge *m_134;
    unsigned long m_138;
    unsigned long *m_13c;
    unsigned long m_140;
    unsigned long m_144;
    unsigned long m_148;
    unsigned long m_14c;
};
#endif

#endif
