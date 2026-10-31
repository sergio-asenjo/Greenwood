#ifndef RHMALIGNITYACTORCALLS_H
#define RHMALIGNITYACTORCALLS_H

class RHUnk00613e90;
class SBGeoVector2D;
struct RHMalignityPosition;

class RHMalignityActorCalls
{
public:
    virtual void V00() = 0;
    virtual void V04() = 0;
    virtual void V08() = 0;
    virtual void V0c() = 0;
    virtual void V10() = 0;
    virtual void V14() = 0;
    virtual void V18() = 0;
    virtual void V1c() = 0;
    virtual void V20() = 0;
    virtual void V24() = 0;
    virtual void V28() = 0;
    virtual void V2c() = 0;
    virtual void V30(RHUnk00613e90 &point) = 0;
    virtual void V34() = 0;
    virtual void V38() = 0;
    virtual void V3c() = 0;
    virtual void V40() = 0;
    virtual void V44() = 0;
    virtual bool V48() = 0; // vtable+0x48
    virtual void V4c() = 0;
    virtual void V50() = 0;
    virtual void V54() = 0;
    virtual void V58() = 0;
    virtual void V5c(void *element) = 0;
    virtual void V60() = 0;
    virtual void V64() = 0;
    virtual void V68() = 0;
    virtual void V6c() = 0;
    virtual void V70() = 0;
    virtual void V74() = 0;
    virtual void V78() = 0;
    virtual void V7c() = 0;
    virtual void V80() = 0;
    virtual void V84() = 0;
    virtual void V88() = 0;
    virtual void V8c() = 0;
    virtual void V90() = 0;
    virtual void V94() = 0;
    virtual void V98() = 0;
    virtual void V9c() = 0;
    virtual void Va0() = 0;
    virtual void Va4() = 0;
    virtual void Va8() = 0;
    virtual void Vac() = 0;
    virtual void Vb0() = 0;
    virtual void Vb4() = 0;
    virtual void Vb8() = 0;
    virtual void Vbc() = 0;
    virtual void Vc0() = 0;
    virtual void Vc4() = 0;
    virtual void Vc8() = 0;
    virtual unsigned Vcc() = 0; // vtable+0xcc
    virtual void Vd0() = 0;
    virtual void Vd4(unsigned short value, bool first, bool second) = 0; // vtable+0xd4
    virtual void Vd8() = 0;
    virtual void Vdc() = 0;
    virtual void Ve0() = 0;
    virtual void Ve4() = 0;
    virtual void Ve8() = 0;
    virtual void Vec(int value, int mode) = 0; // vtable+0xec
    virtual bool Vf0() = 0; // vtable+0xf0
    virtual bool Vf4() = 0; // vtable+0xf4
    virtual bool Vf8() = 0; // vtable+0xf8
    virtual void Vfc() = 0;
    virtual void V100() = 0;
    virtual void V104() = 0;
    virtual void V108() = 0;
    virtual void V10c() = 0;
    virtual void V110() = 0;
    virtual void V114() = 0;
    virtual void V118() = 0;
    virtual bool V11c() = 0; // vtable+0x11c
    virtual void V120() = 0;
    virtual unsigned short V124() = 0;
    virtual void V128() = 0;
    virtual void V12c() = 0;
    virtual int V130() = 0; // vtable+0x130
    virtual void V134() = 0;
    virtual void V138() = 0;
    virtual void V13c() = 0;
    virtual void V140() = 0;
    virtual void V144() = 0;
    virtual void V148() = 0;
    virtual void V14c() = 0;
    virtual void V150() = 0;
    virtual void V154(void *value) = 0; // vtable+0x154
    virtual void V158() = 0;
    virtual void V15c() = 0;
    virtual void V160() = 0;
    virtual void V164() = 0;
    virtual bool V168() = 0; // vtable+0x168
    bool FUN_0048a260(const RHUnk00613e90 &point);
    float FUN_0048db80(void *position, void *actor);
    void FUN_0048e420(void *actor);
    void FUN_0048e580();
    void FUN_0048e5b0(unsigned operation, unsigned short value, unsigned unused);
    unsigned short FUN_0048e5f0(unsigned operation);
    unsigned short FUN_0048e610();
    void FUN_0048e620(unsigned short value);
    void FUN_0048e630(unsigned operation, unsigned short value);
    void FUN_0048e650(unsigned operation, unsigned short value);
    bool FUN_0048e670(void *actor);
    SBGeoVector2D FUN_004135b0();
    void FUN_0048e870(void *actor);
    void FUN_0048ebe0();
    void FUN_0048c700(void *actor, unsigned mode);
    unsigned char FUN_0048ca20(void *actor, unsigned mode);
    void FUN_0048cb90(void *actor);
    void FUN_0048d050();
    unsigned char FUN_0048c8e0(void *actor, unsigned mode);
    bool FUN_0048a130(void *actor);
    bool FUN_0048a350(void *actor);
    void *FUN_0048ee90(unsigned short index);
};

#endif
