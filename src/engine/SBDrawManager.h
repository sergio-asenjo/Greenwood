#ifndef SB_DRAW_MANAGER_H
#define SB_DRAW_MANAGER_H

class SBGeoVector2D;
class RHUnk00613e90;

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
    bool FUN_005e3f70();
    void FUN_005e57e0(unsigned, SBGeoVector2D &);
    bool FUN_005e5bd0(unsigned long, void *);
    bool FUN_005ee640(void *, SBDrawUnk005fc3b0Point &);
    bool FUN_005eec00(unsigned long, unsigned long, void *, unsigned long,
        unsigned long, unsigned long, unsigned long, unsigned long);
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
};

struct SBDrawUnk005efc10Iterator
{
    SBDrawUnk005f0090Node *m_node;
    SBDrawUnk005efc10Iterator(SBDrawUnk005f0090Node *node) : m_node(node) {}
};

class SBDrawUnk005efc10
{
public:
    char m_00[4];
    SBDrawUnk005f0090Node *m_head;
    SBDrawUnk005efc10Iterator FUN_005efc10(const unsigned long &);
};

class SBDrawUnk005e8450
{
public:
    bool FUN_005e7880(void *, void *, void *, int, int, int, int, int, int);
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
