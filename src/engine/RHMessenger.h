// RHMessenger — declarations for RHMessenger.cpp (decompiled TU).
//
// BINDINGS:
//   0x005472d0 -> RHMessenger::Serialize(SBFile&)
//   0x00547460 -> RHMessenger::SerializeLockUser(SBFile&)   (both __FILE__)
//
// Member layout is derived from the target instructions of
// RHMessenger::Serialize (0x005472d0) and RHMessenger::SerializeLockUser
// (0x00547460): this at +0x17 (byte), +0x1a (byte), +0x23 (byte, the "lock
// user" flag), +0x28 (byte), +0x2a (short), +0xa2 (short) and the nested Reset
// callee's fields at +0x14..+0xaa. Only the bytes the matched functions touch
// are laid out; everything else is opaque padding.

#include "SB.h"
#include "RHMessage.h"

// A 0x10-byte value object constructed on a stack temporary and passed by
// reference to RHMessenger::SerializeLockUser's action callee. Layout derived
// from the target: ctor 0x005490f0 (vtable at +0, clears +0x4/+0x8 via base
// ctor 0x00549070, stores its int argument at +0xc), dtor 0x00549110. Identity
// deliberately unproven: no Windows-side __FILE__/tag/string names the type, so
// it stays named by address (docs/05-naming.md). Defined once in
// RHMessenger_stubs.cpp.
// SIZE 0x10
// VTABLE: GAME 0x00679b64
class RHUnk5490f0 : public RHMessage
{
public:
    RHUnk5490f0(int value);
    RHUnk5490f0(int command, int value);
    ~RHUnk5490f0();
    void *FUN_005490d0(unsigned flags);
    int m_unk0c; // 0x0c
};

class RHReceiverInterface;
class SBGeoPoint2D;
class SBGeoVector2D;

class RHMessenger
{
public:
    RHMessenger();
    ~RHMessenger();
    void *FUN_00545ed0(unsigned flags);
    virtual bool Serialize(SBFile &file);

    // Target 0x00547460 (__FILE__ rhmessenger.cpp). On the loading path it
    // reads the "lock user" byte into a local, and when the read value differs
    // from the current flag at +0x23 dispatches a lock/unlock (0x1c/0x1d)
    // action; on the saving path it writes the flag at +0x23. Ends in a plain
    // `ret 4` (__thiscall(this, SBFile&)). PROVISIONAL progress confirmed by
    // the Mac map (symbols/mac-functions-by-file.tsv:129, rhmessenger.cpp ->
    // SerializeLockUser) plus the +0x23 lock-user flag its body serialises.
    bool SerializeLockUser(SBFile &file);

    // Target 0x005460c0 (__thiscall(this, RHUnk5490f0&), ends `ret 4`). A real
    // RHMessenger method: it reads this[+0x23]/+0x20/+0x26/+0xa2/+0xa8, the
    // same flag block Serialize/SerializeLockUser touch, and dispatches on the
    // argument's field at +0xc. No Windows-side __FILE__/tag/string names it, so
    // it stays named by address. Defined once in RHMessenger_stubs.cpp.
    void RHUnk005460c0(RHUnk5490f0 &message);

    // Target 0x00547560 — __thiscall(this), no extra args (ends in a plain
    // `ret`, not `ret N`). PROVISIONAL identity: it clears a run of byte/word
    // flags across [0x14, 0xaa] and resets two embedded containers; it is
    // called from both the loading and saving paths of Serialize. It is a real
    // RHMessenger method (it touches `this` directly), but no Windows-side
    // __FILE__/tag/string binds a name to it. The Mac oracle's RHMessenger
    // method set (symbols/mac-RH.txt:3066-3085) contains RHMessenger::Reset()
    // as a plausible match, but a cross-binary signature match is not accepted
    // as evidence (docs/05-naming.md). Defined once in RHMessenger_stubs.cpp.
    void Reset();

    void Emit(SBFile &file);
    void Subscribe(RHReceiverInterface *receiver);
    void Unsubscribe(RHReceiverInterface *receiver);
    void FUN_00547280();
    int CheckThrustHI(const SBGeoPoint2D &a, const SBGeoPoint2D &b, const SBGeoPoint2D &c, const SBGeoPoint2D &d,
        unsigned long e, unsigned long f, unsigned long g, unsigned long h);
    int CheckThrustFG(const SBGeoPoint2D &a, const SBGeoPoint2D &b, const SBGeoPoint2D &c, float x, float y);
    int CheckThrustDE(const SBGeoPoint2D &a, const SBGeoVector2D &b, const SBGeoPoint2D &c, const SBGeoPoint2D &d);
    int CheckThrustAB(const SBGeoPoint2D &a, const SBGeoVector2D &b, const SBGeoPoint2D &c, const SBGeoPoint2D &d);
    int CheckThrustC(unsigned long a, unsigned long b, unsigned long c, unsigned long d);

private:
    char m_unk00[0x2e];   // [0x00, 0x2e): vptr + opaque; the 4-byte tail at
                          // [0x2a, 0x2e) is the short field below, reached
                          // through byte-address arithmetic. A short member at
                          // +0x2a would make VC6 insert 4 bytes of padding at
                          // +0x17..+0x1a (aligning the short), shifting every
                          // later offset; the original packs +0x1a/1, +0x28/1
                          // and +0x2a/2 with no gap, so the short is carved out
                          // of an opaque byte run instead.
    char m_unk2e[0x7a];
};

// The fields RHMessenger::Serialize (and SerializeLockUser) touch. Offset
// aliases on a byte array do not disturb the layout: reading/writing through
// them emits byte/word accesses at the exact original offsets while VC6 keeps
// the array alignment at 1.
#define m_unk17  (*(char *)((char *)this + 0x17))
#define m_unk1a  (*(char *)((char *)this + 0x1a))
#define m_unk23  (*(char *)((char *)this + 0x23))
#define m_unk28  (*(char *)((char *)this + 0x28))
#define m_unk2a  (*(short *)((char *)this + 0x2a))
#define m_unka2  (*(short *)((char *)this + 0xa2))

// Serialises a type-name tag into the stream; target 0x005e1b70. Defined once
// in RHElementObject_stubs.cpp; declared here so the call resolves.
void RHSerializeName(SBFile &file, const char *name);
