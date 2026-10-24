// RHSword.cpp — translation unit with __FILE__ evidence at 0x005c1ff0
// ("P:\Robin Hood\RHSword.cpp", symbols/functions-by-file.tsv).
//
// BINDING (0x005c1ff0):
//   - TU:        RHSword.cpp (embedded __FILE__ string 0x006b8bbc).
//   - Class:     RHSword (symbols/oracle-correlation.tsv: rhsword -> RHSword).
//   - Signature: RHSword::SerializePointer(SBFile&, RHSword*&). Signals:
//       * arg2 is a pointer-to-pointer (dereferenced and stored through);
//       * arg1 drives the file: byte +4 selects read/write, and
//         Access(void*, int) / GetError() are __thiscall on it;
//       * the read path does `new RHSword` (ctor 0x5c1b00, vtable 0x679e48
//         slot 0 = RHSword::Serialize 0x5c1fd0) then calls its virtual
//         Serialize(SBFile&) — exactly a RHSword*&.
//   - Corroboration: 0x00450370 in RHBow.cpp is byte-identical except for the
//     __FILE__/line/ctor, i.e. RHBow::SerializePointer(SBFile&, RHBow*&).
//
// NOTE: RHSword's ctor/dtor/serializer and the file/assert stubs are
// deliberately defined in a separate TU (RHSword_stubs.cpp). VC6 emits the
// `new`-cleanup C++ EH frame only while the destructor body is not visible at
// the call site; defining it here makes VC6 elide the frame.
//
// The `// STRING:` markers pin the literals to their original Game.exe
// addresses: the original is a fixed-base EXE, so its absolute string pointers
// carry no relocation records and reccmp cannot discover them by scanning.

#include "SBNullstr.h"
#include "RHSword.h"
#include "RHHumanWeaponCalls.h"
#include "RHProfileManager.h"

RHProfileManager *RHUnk00436500GetProfileManager();



// FUNCTION: GAME 0x005c1b60
char RHSword::FUN_005c1b60() const
{
    return *((const char *)m_unk4 + 0x16);
}

// FUNCTION: GAME 0x005c1d70
unsigned RHHumanWeaponCalls::FUN_005c1d70(int index)
{
    if (index < 10) {
        const RHHtHWeaponProfile *profile = *(const RHHtHWeaponProfile *const *)((const char *)this + 4);
        int kind = profile->m_1c[index].m_04;
        if (kind == 1 || (kind > 2 && kind <= 6))
            return profile->m_1c[index].m_08;
        return 2;
    }
    return 2;
}

// FUNCTION: GAME 0x005c1db0
unsigned short RHHumanWeaponCalls::FUN_005c1db0(int index)
{
    if (index < 10)
        return *(const unsigned short *)(*(const char *const *)((const char *)this + 4) + index * 32 + 0x28);
    return 0;
}

// FUNCTION: GAME 0x005c1e80
unsigned short RHHumanWeaponCalls::FUN_005c1e80(int index)
{
    if (index < 10)
        return *(const unsigned short *)(*(const char *const *)((const char *)this + 4) + index * 32 + 0x2c);
    return **(const unsigned short *const *)((const char *)this + 4);
}

// FUNCTION: GAME 0x005c1ea0
unsigned short RHHumanWeaponCalls::FUN_005c1ea0(int index)
{
    if (index < 10)
        return *(const unsigned short *)(*(const char *const *)((const char *)this + 4) + index * 32 + 0x2e);
    return (*(const unsigned short *const *)((const char *)this + 4))[2];
}

// FUNCTION: GAME 0x005c1ed0
float RHHumanWeaponCalls::FUN_005c1ed0(int index)
{
    if (index < 10) {
        double turns = *(const unsigned short *)(*(const char *const *)((const char *)this + 4) + index * 32 + 0x30) * 0.0027777777777777779;
        return turns * 6.2831854820251465;
    }
    return 0.0f;
}

// FUNCTION: GAME 0x005c1f10
float RHHumanWeaponCalls::FUN_005c1f10(int index)
{
    if (index < 10) {
        double turns = *(const unsigned short *)(*(const char *const *)((const char *)this + 4) + index * 32 + 0x32) * 0.0027777777777777779;
        return turns * 6.2831854820251465;
    }
    return 0.0f;
}

// FUNCTION: GAME 0x005c1f50
float RHHumanWeaponCalls::FUN_005c1f50(int index)
{
    if (index < 10) {
        double turns = *(const unsigned short *)(*(const char *const *)((const char *)this + 4) + index * 32 + 0x34) * 0.0027777777777777779;
        return turns * 6.2831854820251465;
    }
    return 0.0f;
}

// FUNCTION: GAME 0x005c1f90
unsigned short RHSword::FUN_005c1f90(int index) const
{
    if (index < 10)
        return *(const unsigned short *)((const char *)m_unk4 + index * 32 + 0x36);
    return 0;
}

// FUNCTION: GAME 0x005c1fb0
unsigned short RHSword::FUN_005c1fb0(int index) const
{
    if (index < 10)
        return *(const unsigned short *)((const char *)m_unk4 + index * 32 + 0x3a);
    return 1;
}

// FUNCTION: GAME 0x005c1fd0
bool RHSword::Serialize(SBFile &file)
{
    return RHUnk00436500GetProfileManager()->SerializeProfilePointer(file, *(const RHHtHWeaponProfile **)&m_unk4);
}

// FUNCTION: GAME 0x005c1ff0
bool RHSword::SerializePointer(SBFile &file, RHSword *&ptr)
{
    bool exists;

    if (!file.m_bLoading)
    {
        exists = (ptr != 0);
        if (file.Access(&exists, 1) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars
                                     ? err->m_chars
                                     // STRING: GAME 0x6773d0
                                     : "";
            SBAssert(0,
                     // STRING: GAME 0x6b8bbc
                     "P:\\Robin Hood\\RHSword.cpp",
                     365,
                     // STRING: GAME 0x6a7390
                     "Serialize failed reason is %s",
                     reason);
            return false;
        }
        if (exists)
            return ptr->Serialize(file);
        return true;
    }

    if (file.Access(&exists, 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHSword.cpp", 376, "Serialize failed reason is %s", reason);
        return false;
    }
    if (exists)
    {
        ptr = new RHSword;
        return ptr->Serialize(file);
    }
    return true;
}
