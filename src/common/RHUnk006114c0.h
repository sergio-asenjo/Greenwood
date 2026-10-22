#ifndef RHUNK006114C0_H
#define RHUNK006114C0_H

#include "Decomp.h"
#include <string>

class SBFile;
class SBGeoPoint2D;
class SBGeoVector2D;
class RHUnkFXDraw;

// SIZE 0x38
class __declspec(novtable) RHUnk006114c0
{
public:
    RHUnk006114c0();
    void *FUN_00611540(unsigned flags);
    virtual ~RHUnk006114c0(); // vtable+0x00
    virtual void Unk04(); // vtable+0x04
    virtual void Unk08(); // vtable+0x08
    virtual void Unk0c(); // vtable+0x0c
    virtual void Unk10(); // vtable+0x10
    virtual void Unk14(); // vtable+0x14
    virtual bool FUN_006118b0(const std::string &name); // vtable+0x18
    virtual bool Unk1c(SBFile &file); // vtable+0x1c
    virtual bool Unk20(RHUnkFXDraw *, unsigned long); // vtable+0x20
    virtual void *FUN_006114e0(); // vtable+0x24
    virtual unsigned int FUN_006114f0(); // vtable+0x28
    virtual unsigned short FUN_00611500(); // vtable+0x2c
    virtual unsigned short FUN_00611510(); // vtable+0x30
    virtual unsigned short FUN_00611520(); // vtable+0x34
    virtual int FUN_00611530(); // vtable+0x38
    bool Unk00611710(SBFile &);
    bool Unk00613530(RHUnkFXDraw *, unsigned long);
    bool Unk00611e10(unsigned long, unsigned long);
    RHUnk006114c0 *Unk00612ad0(const SBGeoPoint2D &, const SBGeoVector2D &);
    void FUN_00611aa0(SBFile &, void *);
    bool FUN_006134a0(void *configuration);
    bool FUN_00611960(SBFile &file);
    unsigned short UnkField20() const { return m_width; }
    unsigned short UnkField22() const { return m_height; }
    undefined m_04[0x1c]; // 0x04
    unsigned short m_width; // 0x20
    unsigned short m_height; // 0x22
    undefined m_24[0x14]; // 0x24
};

#endif
