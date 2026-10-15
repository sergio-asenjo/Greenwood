#ifndef RHWIDGETPORTRAITCLASS_H
#define RHWIDGETPORTRAITCLASS_H

#include "SB.h"

class SBGeoPoint2D;
class SBGeoBoundingBox2D;

// SIZE 0x04
class RHUnk005d92c0Sub
{
public:
    virtual void v00(); // vtable+0x00
    virtual void v01(); // vtable+0x04
    virtual void v02(); // vtable+0x08
    virtual void v03(); // vtable+0x0c
    virtual void v04(); // vtable+0x10
    virtual void v05(); // vtable+0x14
    virtual void v06(); // vtable+0x18
    virtual void v07(); // vtable+0x1c
    virtual void v08(const SBGeoPoint2D &point); // vtable+0x20
    virtual void v09(); // vtable+0x24
    virtual bool v10(long value); // vtable+0x28
    virtual void v11(); // vtable+0x2c
    virtual void v12(); // vtable+0x30
    virtual void v13(); // vtable+0x34
    virtual void v14(RHUnk005d92c0Sub *widget); // vtable+0x38
    virtual void v15(RHUnk005d92c0Sub *widget); // vtable+0x3c
    virtual void v16(); // vtable+0x40
    virtual void v17(); // vtable+0x44
    virtual void v18(); // vtable+0x48
    virtual void v19(); // vtable+0x4c
    virtual void *v20(); // vtable+0x50
    virtual void v21(int value); // vtable+0x54
    void DisableQuick(char *slot)
    {
        *(int *)(slot + 0xa50) = -1;
        *(char *)(slot + 0xa55) = 0;
        v21(0);
    }
};

// SIZE 0x104
struct RHUnk005d92c0Elem
{
    int m_00;      // [0x00]
    char m_04;     // [0x04]
    char m_05;     // [0x05]
    undefined m_pad0[0x4e - 0x06]; // 0x06
    char m_4e;     // [0x4e]
    char m_4f;     // [0x4f]
    char m_50;     // [0x50]
    char m_51;     // [0x51]
    undefined m_pad1[0x104 - 0x52]; // 0x52
};

// SIZE 0xe58
class RHWidgetPortrait
{
public:
    bool Serialize(SBFile &file);
    void Emit(SBFile &file);

    bool FUN_005d75c0(int first, int second, int third);
    bool FUN_005d7730(int value);
    bool FUN_005d7810(unsigned int index, void *value);
    bool FUN_005d7930(int value);
    bool FUN_005d7a30(int value);
    bool FUN_005d7b30(int value);
    bool FUN_005d7c40(int index, void *value, int mode);
    bool FUN_005d7ea0();
    bool FUN_005d8430();
    void FUN_005d8ed0(int value, int height);
    void FUN_005d9070();
    bool FUN_005d9090(unsigned int index);
    bool FUN_005d90c0(unsigned int index);
    void FUN_005d9160();
    void FUN_005d9180();
    SBGeoBoundingBox2D FUN_005d9210() const;

    bool Method005d6690();
    bool Method005d67e0();
    bool Method005d73d0();
    bool Method005d7530();
    void FUN_005d9c30();
    void FUN_005da1f0();
    void FUN_005d9920();
    bool FUN_005d9a20(int action);
    void FUN_005d9bc0();
    bool FUN_005d9eb0(int action);
    std::wstring GetPCName() const;

private:
    undefined m_pad0[0x16c]; // 0x00
    float m_16c;           // [0x16c]
    float m_170;           // [0x170]
    undefined m_pad1[0x7bc - 0x174]; // 0x174
    RHUnk005d92c0Sub m_7bc; // [0x7bc]
    char m_7c0;            // [0x7c0]
    undefined m_pad2[0xa50 - 0x7c1]; // 0x7c1
    RHUnk005d92c0Elem m_arr[3]; // [0xa50]
    undefined m_pad3[0xe50 - (0xa50 + 3 * 0x104)]; // 0xd5c
    char m_e50[6];         // [0xe50]
};

#endif
