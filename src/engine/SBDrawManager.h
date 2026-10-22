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
    char m_01[7];
    unsigned long m_08;
    char m_0c[4];
    unsigned long m_10;
    int m_14;
    int m_18;
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
    bool FUN_005ee640(void *, SBDrawUnk005fc3b0Point &);
    bool FUN_005eec00(unsigned long, unsigned long, void *, unsigned long,
        unsigned long, unsigned long, unsigned long, unsigned long);
    void FUN_005e4810(int width, int height, int depth);
    bool FUN_005ed270(const RHMobileUnk00607da0 &bounds);
};

class SBDrawUnk005f0090Node
{
public:
    char m_pad0[0x0c];
    unsigned long m_key;
    char m_pad10[4];
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
    bool FUN_005e7880(void *, void *, void *, int, int, int, int, int, int);
    bool FUN_005e78c0(unsigned short *, unsigned short *, unsigned short *, unsigned, unsigned, unsigned, unsigned, unsigned);
    bool FUN_005e7a30(unsigned short *, unsigned short *, unsigned short *, unsigned, unsigned, unsigned, unsigned, unsigned, unsigned short);
    bool FUN_005e7bc0(unsigned short *, unsigned short *, unsigned short *, unsigned, unsigned, unsigned, unsigned, unsigned);
    bool FUN_005e7de0(unsigned short *, unsigned short *, unsigned short *, unsigned, unsigned, unsigned, unsigned, unsigned);
    bool FUN_005e7fa0(unsigned short *, unsigned short *, unsigned short *, unsigned, unsigned, unsigned, unsigned, unsigned);
    bool FUN_005e82a0(unsigned short *, unsigned short *, unsigned short *, unsigned, unsigned, unsigned, unsigned, unsigned);
    bool FUN_005e7d30(void *, void *, void *, int, int, int, int, int, int);
    bool FUN_005e7d70(void *, void *, void *, int, int, int, int, int, int);
    bool FUN_005e7da0(void *, void *, void *, int, int, int, int, int, int);
    bool FUN_005e7f60(void *, void *, void *, int, int, int, int, int, int);
    bool FUN_005e8410(void *, void *, void *, int, int, int, int, int, int);
    bool FUN_005e8450(void *source, void *destination, void *alpha, int width,
        int height, int sourceStride, int destinationStride, int arg8, int arg9);
    bool FUN_005e84a0(void *, void *, void *, int, int, int, int, int, int);
    bool FUN_005e84e0(void *source, void *destination, void *alpha, int arg4,
        int width, int height, int sourceStride, int destinationStride,
        float stretchX, float stretchY);
    bool FUN_005e85b0(void *source, void *destination, void *alpha, int arg4,
        int width, int height, int sourceStride, int destinationStride,
        float stretchX, float stretchY);
    bool FUN_005e8670(void *source, void *destination, void *alpha, int arg4,
        int width, int height, int sourceStride, int destinationStride,
        float stretchX, float stretchY);
    bool FUN_005e8740(unsigned short *, unsigned short *, unsigned short *, unsigned,
        unsigned, unsigned, unsigned, float, float);
    bool FUN_005e8b10(unsigned short *, unsigned short *, unsigned short *, unsigned,
        unsigned, unsigned, unsigned, unsigned, float, float);
    bool FUN_005e8f20(unsigned short *, unsigned short *, unsigned short *, unsigned,
        unsigned, unsigned, unsigned, float, float);
    bool FUN_005e93c0(unsigned short *, unsigned short *, unsigned short *, unsigned,
        unsigned, unsigned, unsigned, float, float);
    bool FUN_005e99f0(unsigned short *, unsigned short *, unsigned short *, unsigned,
        unsigned, unsigned, unsigned, float, float);
    bool FUN_005e9dc0(unsigned short *, unsigned short *, unsigned short *, unsigned,
        unsigned, unsigned, unsigned, unsigned, float, float);
    bool FUN_005ea1d0(unsigned short *, unsigned short *, unsigned short *, unsigned,
        unsigned, unsigned, unsigned, float, float);
    bool FUN_005ea670(unsigned short *, unsigned short *, unsigned short *, unsigned,
        unsigned, unsigned, unsigned, float, float);
    bool FUN_005eb450(unsigned short *, unsigned short *, unsigned, unsigned,
        unsigned, unsigned, unsigned, float, float);
    bool FUN_005eb800(unsigned short *, unsigned short *, unsigned, unsigned,
        unsigned, unsigned, unsigned, float, float);
    bool FUN_005e92f0(void *source, void *destination, void *alpha, int arg4,
        int width, int height, int sourceStride, int destinationStride,
        float stretchX, float stretchY);
    bool FUN_005e9790(void *source, void *destination, void *alpha, int arg4,
        int width, int height, int sourceStride, int destinationStride,
        float stretchX, float stretchY);
    bool FUN_005e9860(void *source, void *destination, void *alpha, int arg4,
        int width, int height, int sourceStride, int destinationStride,
        float stretchX, float stretchY);
    bool FUN_005e9920(void *source, void *destination, void *alpha, int arg4,
        int width, int height, int sourceStride, int destinationStride,
        float stretchX, float stretchY);
    bool FUN_005ea5a0(void *source, void *destination, void *alpha, int arg4,
        int width, int height, int sourceStride, int destinationStride,
        float stretchX, float stretchY);
    bool FUN_005ec230(void *, void *, int, int, int, int, float, float, unsigned, unsigned);
    bool FUN_005ec320(void *, void *, int, int, int, int, float, float, unsigned, unsigned);
    bool FUN_005ec410(void *, void *, int, int, int, int, float, float, unsigned, unsigned);
    bool FUN_005ec500(void *, void *, int, int, int, int, float, float, unsigned, unsigned);
};

struct SBDrawUnk005e5ec0Surface
{
    void **m_vtable;
};

class SBDrawUnk005e5ec0
{
public:
    char m_00[0x10c];
    unsigned short m_10c;
    bool FUN_005e5ec0(unsigned long, unsigned long);
    unsigned short FUN_005e5f60(unsigned long);
};

void FUN_006220ec(void *, void *, int, int, int, int, unsigned, unsigned);
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

#endif
