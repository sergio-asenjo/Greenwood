// RHMessenger.cpp — translation unit with __FILE__ evidence at 0x005472d0
// ("P:\Robin Hood\RHMessenger.cpp", symbols/functions-by-file.tsv).
//
// BINDING (0x005472d0 -> RHMessenger::Serialize(SBFile&)):
//   - TU:        rhmessenger.cpp (embedded __FILE__ string 0x006b118c).
//   - Class:     RHMessenger (symbols/oracle-correlation.tsv:
//                rhmessenger -> class RHMessenger, 25 methods).
//   - Signature: RHMessenger::Serialize(SBFile&) (symbols/mac-RH.txt:3082).
//   - Signals:
//       * the first act writes the tag "RHMessenger" (string 0x006b11ac) via
//         0x005e1b70 — the name matches the TU's class;
//       * a run of SBFile::Access checks at +0x1a/1 (line 873), +0x28/1 (876),
//         +0x2a/2 (877), +0xa2/2 (880), each with the "Serialize failed reason
//         is %s" idiom;
//       * a `file.m_version >= 0x11` gate: the read path Accesses +0x17/1 at
//         line 884, the below-version path stores 0 into the +0x17 byte;
//       * the file.m_bLoading gate (mov al,[esi+4]; test; je) then calls
//         0x00547560 on `this` in BOTH paths; on the loading path a
//         `file.m_version >= 0x2a` gate guards a final Access of a 1-byte
//         stack local at line 900;
//       * no loop and no `new`.
//
// BINDING (0x00547460 -> RHMessenger::SerializeLockUser(SBFile&)):
//   - TU:        rhmessenger.cpp (same embedded __FILE__ string 0x006b118c).
//   - Class:     RHMessenger; the Mac map's rhmessenger.cpp lists exactly two
//                methods, Serialize and SerializeLockUser
//                (symbols/mac-functions-by-file.tsv:128-129); Serialize is
//                already bound above, so the remaining __FILE__ function is
//                SerializeLockUser.
//   - Signals:   the body serialises the "lock user" flag at this+0x23; on the
//                loading path a fetched byte that differs from +0x23 dispatches
//                a lock/unlock action carrying the 0x1c/0x1d constant selected
//                by `byte == 0`; on the saving path it writes +0x23 directly.
//                Both Access failures use the "Serialize failed reason is %s"
//                idiom at lines 924 / 935.
//
// The `// STRING:` markers pin the literals to their original Game.exe
// addresses: the original is a fixed-base EXE, so its absolute string pointers
// carry no relocation records and reccmp cannot discover them by scanning.
// ("" 0x006773d0 and the format 0x006a7390 are annotated once, in
// src/RHSword.cpp; references here resolve to the same pooled entities.)

#include "SBNullstr.h"
#include "RHMessenger.h"
#include <algorithm>
#include <vector>
#include <math.h>

#define SBGEO_POINT2D_VIEW
class SBGeoVector2D;
class SBGeoPoint2D
{
public:
    SBGeoPoint2D();
    SBGeoPoint2D(const SBGeoPoint2D &other);
    ~SBGeoPoint2D();
    SBGeoVector2D Unk005fc110(const SBGeoPoint2D &other) const;
    float FUN_005fca90(const SBGeoPoint2D &other, float scale) const;
    SBGeoPoint2D &operator=(const SBGeoPoint2D &other);
    bool operator==(const SBGeoPoint2D &other) const;
    float m_x;
    float m_y;
};

template<class T> T &RHMessengerField(void *object, unsigned offset)
{
    return *(T *)((char *)object + offset);
}


// GLOBAL: GAME 0x006c0c4c
RHMessenger *g_unk0x006c0c4c = 0;

// FUNCTION: GAME 0x00545ed0
void *RHMessenger::FUN_00545ed0(unsigned flags)
{
    this->~RHMessenger();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x00546050
RHMessenger *RHUnk00546050()
{
    if (!g_unk0x006c0c4c)
        g_unk0x006c0c4c = new RHMessenger;
    return g_unk0x006c0c4c;
}

// FUNCTION: GAME 0x00547080
void RHMessenger::Subscribe(RHReceiverInterface *receiver)
{
    std::vector<RHReceiverInterface *> &receivers = RHMessengerField<std::vector<RHReceiverInterface *> >(this, 4);
    receivers.push_back(receiver);
}

// FUNCTION: GAME 0x00547230
void RHMessenger::Unsubscribe(RHReceiverInterface *receiver)
{
    std::vector<RHReceiverInterface *> &receivers = RHMessengerField<std::vector<RHReceiverInterface *> >(this, 4);
    std::vector<RHReceiverInterface *>::iterator position = receivers.begin();
    RHReceiverInterface **last;
    memcpy(&last, (char *)this + 0x0c, sizeof(last));
    for (; position != last; ++position)
    {
        if (*position == receiver)
        {
            receivers.erase(position);
            return;
        }
    }
}

// FUNCTION: GAME 0x00547280
void RHMessenger::FUN_00547280()
{
    SBGeoPoint2D &previous = RHMessengerField<SBGeoPoint2D>(this, 0x8c);
    SBGeoPoint2D &position = RHMessengerField<SBGeoPoint2D>(this, 0x84);
    if (position == previous)
    {
        int count = RHMessengerField<int>(this, 0x9c);
        RHMessengerField<bool>(this, 0x24) = false;
        RHMessengerField<int>(this, 0x9c) = count + 1;
    }
    else
    {
        RHMessengerField<int>(this, 0x9c) = 0;
        previous = position;
        RHMessengerField<bool>(this, 0x24) = false;
    }
}

// FUNCTION: GAME 0x005472d0
bool RHMessenger::Serialize(SBFile &file)
{
    // STRING: GAME 0x6b11ac
    RHSerializeName(file, "RHMessenger");

    if (file.Access(&m_unk1a, 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0,
                 // STRING: GAME 0x6b118c
                 "P:\\Robin Hood\\RHMessenger.cpp",
                 873,
                 "Serialize failed reason is %s",
                 reason);
        return false;
    }

    if (file.Access(&m_unk28, 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHMessenger.cpp", 876, "Serialize failed reason is %s", reason);
        return false;
    }

    if (file.Access(&m_unk2a, 2) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHMessenger.cpp", 877, "Serialize failed reason is %s", reason);
        return false;
    }

    if (file.Access(&m_unka2, 2) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHMessenger.cpp", 880, "Serialize failed reason is %s", reason);
        return false;
    }

    if (file.m_version >= 0x11)
    {
        if (file.Access(&m_unk17, 1) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHMessenger.cpp", 884, "Serialize failed reason is %s", reason);
            return false;
        }
    }
    else
    {
        m_unk17 = 0;
    }

    if (file.m_bLoading)
    {
        Reset();

        if (file.m_version < 0x2a)
        {
            char scratch;
            if (file.Access(&scratch, 1) < 0)
            {
                SBString *err = file.GetError();
                const char *reason = err->m_chars ? err->m_chars : "";
                SBAssert(0, "P:\\Robin Hood\\RHMessenger.cpp", 900, "Serialize failed reason is %s", reason);
                return false;
            }
        }
    }
    else
    {
        Reset();
    }

    return true;
}

// FUNCTION: GAME 0x00547460
bool RHMessenger::SerializeLockUser(SBFile &file)
{
    if (file.m_bLoading)
    {
        char loaded;
        if (file.Access(&loaded, 1) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0,
                     // The __FILE__ literal 0x006b118c is annotated once, in
                     // RHMessenger::Serialize above; this reference resolves to
                     // the same pooled entity. ("" 0x006773d0 and the format
                     // 0x006a7390 are owned by src/RHSword.cpp.)
                     "P:\\Robin Hood\\RHMessenger.cpp",
                     924,
                     "Serialize failed reason is %s",
                     reason);
            return false;
        }

        if (loaded != m_unk23)
        {
            RHUnk005460c0(RHUnk5490f0(loaded == 0 ? 0x1d : 0x1c));
        }
    }
    else
    {
        if (file.Access(&m_unk23, 1) < 0)
        {
            SBString *err = file.GetError();
            const char *reason = err->m_chars ? err->m_chars : "";
            SBAssert(0, "P:\\Robin Hood\\RHMessenger.cpp", 935, "Serialize failed reason is %s", reason);
            return false;
        }
    }

    return true;
}

struct RHScriptNode
{
    RHScriptNode *next;
    RHScriptNode *prev;
};

struct RHScriptIter
{
    RHScriptNode *node;
    RHScriptIter(RHScriptNode *value) : node(value) {}
};

class RHUnk0046eb30
{
public:
    RHScriptIter erase(RHScriptIter position);
};

#include "SBGeoPolyLine2DList.h"

struct SBInputPosition;
extern SBInputPosition g_inputPosition;

struct RHMessengerFlags
{
    char m_00[0x14]; // 0x00
    bool m_14;       // 0x14
    bool m_15;       // 0x15
    bool m_16;       // 0x16
    char m_17[2];    // 0x17
    bool m_19;       // 0x19
    char m_1a;       // 0x1a
    bool m_1b;       // 0x1b
    bool m_1c;       // 0x1c
    bool m_1d;       // 0x1d
    char m_1e;       // 0x1e
    bool m_1f;       // 0x1f
    char m_20[4];    // 0x20
    bool m_24;       // 0x24
};

// FUNCTION: GAME 0x00547560
void RHMessenger::Reset()
{
    RHMessengerFlags &flags = *(RHMessengerFlags *)this;
    flags.m_14 = false;
    flags.m_15 = false;
    flags.m_16 = false;
    flags.m_19 = false;
    flags.m_1b = false;
    flags.m_1c = flags.m_1d;
    flags.m_1d = false;
    flags.m_1f = false;
    flags.m_24 = false;
    RHMessengerField<SBGeoPolyLine2DList>(this, 0x5c).FUN_00610ac0();
    RHScriptNode *head = RHMessengerField<RHScriptNode *>(this, 0x30);
    RHScriptNode *node = head->next;
    while (node != head)
    {
        RHScriptNode *current = node;
        node = node->next;
        ((RHUnk0046eb30 *)((char *)this + 0x2c))->erase(RHScriptIter(current));
    }
    RHMessengerField<bool>(this, 0x3c) = true;
    RHMessengerField<SBGeoPoint2D>(this, 0x84) = *(const SBGeoPoint2D *)&g_inputPosition;
    RHMessengerField<SBGeoPoint2D>(this, 0x8c) = *(const SBGeoPoint2D *)&g_inputPosition;
    RHMessengerField<int>(this, 0x94) = 0;
    RHMessengerField<int>(this, 0x98) = 0;
    RHMessengerField<int>(this, 0x9c) = 0;
    RHMessengerField<bool>(this, 0xa0) = false;
    RHMessengerField<bool>(this, 0xaa) = false;
}

class SBGeoVector2D : public SBGeoPoint2D
{
public:
    SBGeoVector2D operator-() const;
    SBGeoVector2D();
    SBGeoVector2D &operator=(const SBGeoVector2D &other);
    SBGeoVector2D(const SBGeoVector2D &other);
};

class RHUnk005fc3b0 : public SBGeoVector2D
{
public:
    RHUnk005fc3b0() {}
    RHUnk005fc3b0 &FUN_005fc430(const SBGeoPoint2D &other)
    {
        return (RHUnk005fc3b0 &)SBGeoVector2D::operator=((const SBGeoVector2D &)other);
    }
    float Unk005fc6a0(float value);
};

inline float RHMessengerLength(const SBGeoPoint2D &vector)
{
    return ((RHUnk005fc3b0 *)&vector)->Unk005fc6a0(1.0f);
}



// FUNCTION: GAME 0x00547f00
int RHMessenger::CheckThrustHI(const SBGeoPoint2D &a, const SBGeoPoint2D &b, const SBGeoPoint2D &c,
    const SBGeoPoint2D &d, unsigned long e, unsigned long f, unsigned long g, unsigned long h)
{
    SBGeoVector2D first = d.Unk005fc110(b);
    SBGeoVector2D second = d.Unk005fc110(c);
    if (fabs(first.FUN_005fca90(second, 1.0f)) < 1.5707963705062866)
    {
        if ((e <= g && g <= f && f <= h) || (g <= f && f <= h && h <= e) || (f <= h && h <= e && e <= g)
            || (h <= e && e <= g && g <= f))
            return 9;
        return 10;
    }
    return 0;
}

// FUNCTION: GAME 0x00548050
int RHMessenger::CheckThrustFG(const SBGeoPoint2D &a, const SBGeoPoint2D &b, const SBGeoPoint2D &c, float x, float y)
{
    float length = RHMessengerLength(c.Unk005fc110(b));
    if (x / length > 0.3f)
    {
        if (y / length <= 0.3f)
            return 7;
    }
    else if (y / length > 0.3f)
        return 8;
    return 0;
}







// FUNCTION: GAME 0x00548120
int RHMessenger::CheckThrustDE(const SBGeoPoint2D &a, const SBGeoVector2D &b, const SBGeoPoint2D &c,
    const SBGeoPoint2D &d)
{
    SBGeoVector2D first = d.Unk005fc110(c);
    RHUnk005fc3b0 direction;
    direction.FUN_005fc430(-b);
    float angle = direction.FUN_005fca90(first, 1.0f);
    if (angle > 0.785398185f && angle < 2.35619450f)
        return 6;
    if (angle < (-0.785398185f) && angle > (-2.35619450f))
        return 5;
    return 0;
}

// FUNCTION: GAME 0x00548280
int RHMessenger::CheckThrustAB(const SBGeoPoint2D &a, const SBGeoVector2D &b, const SBGeoPoint2D &c,
    const SBGeoPoint2D &d)
{
    SBGeoVector2D first = c.Unk005fc110(d);
    RHUnk005fc3b0 direction;
    direction.FUN_005fc430(-b);
    double angle = fabs(direction.FUN_005fca90(first, 1.0f));
    if (angle < 0.7853981852531433)
        return 3;
    if (angle > 2.35619455575943)
        return 2;
    return 0;
}

// FUNCTION: GAME 0x005483b0
int RHMessenger::CheckThrustC(unsigned long a, unsigned long b, unsigned long c, unsigned long d)
{
    unsigned long values[4];
    unsigned short index = 0;
    unsigned long minimum = 0xffffffff;
    unsigned long maximum = 0;
    bool ascending = a < b;
    values[0] = a;
    values[1] = b;
    values[2] = c;
    values[3] = d;
    for (unsigned short i = 0; i < 4; ++i)
    {
        if (ascending)
        {
            if (values[i] < minimum)
            {
                index = i;
                minimum = values[i];
            }
        }
        else if (values[i] > maximum)
        {
            index = i;
            maximum = values[i];
        }
    }
    for (unsigned short j = index; j < index + 3; ++j)
    {
        unsigned long current = values[j % 4];
        unsigned long next = values[(j + 1) % 4];
        if (current > next && ascending)
            return 0;
        if (current < next && !ascending)
            return 0;
    }
    return 4;
}

#include "RHPlayerProfileAccess.h"
#include "SBDrawViewport.h"

extern unsigned char g_unk0x006c0e48[];
class RHUnk005ef320;
extern RHUnk005ef320 *g_unk0x6c11d0;

inline float RHMessengerHeight(char *config)
{
    return *(float *)(config + 8);
}

inline unsigned short RHMessengerBlend(unsigned short source, unsigned short destination, unsigned short strength,
    int redMask, int greenMask)
{
    unsigned short red = source & redMask;
    unsigned short green = source & greenMask;
    unsigned short blue = source & 0x1f;
    unsigned short targetRed = (((destination & redMask) * strength) >> 5) & redMask;
    unsigned short targetGreen = (((destination & greenMask) * strength) >> 5) & greenMask;
    unsigned short targetBlue = (((destination & 0x1f) * strength) >> 5) & 0x1f;
    unsigned long resultRed = targetRed + (unsigned long)red;
    if (resultRed >= (unsigned long)redMask)
        resultRed = redMask;
    unsigned long resultGreen = targetGreen + (unsigned long)green;
    if (resultGreen >= (unsigned long)greenMask)
        resultGreen = greenMask;
    unsigned long resultBlue = targetBlue + (unsigned long)blue;
    if (resultBlue >= 0x1f)
        resultBlue = 0x1f;
    return (unsigned short)(resultBlue | resultGreen | resultRed);
}

// STUB: GAME 0x00548480
void RHMessenger::DrawMouseTrailPattern(const SBGeoPoint2D &point, unsigned short strength, SBDrawViewport &viewport)
{
    char *config = ((RHUnk0055dbb0 *)g_unk0x006c0e48)->FUN_0055dbb0() + 0x50;
    short count = (short)(RHMessengerField<unsigned short>(this, 0x58) <
        RHMessengerHeight(config) - (unsigned short)point.m_y ?
        RHMessengerField<unsigned short>(this, 0x58) :
        RHMessengerHeight(((RHUnk0055dbb0 *)g_unk0x006c0e48)->FUN_0055dbb0() + 0x50) - (unsigned short)point.m_y);
    unsigned short level = strength * 32 / 100;
    if (!level)
        return;
    if (level > 32)
        level = 32;
    unsigned short *pattern = RHMessengerField<unsigned short *>(this, 0x50) +
        (level - 1) * RHMessengerField<unsigned short>(this, 0x58);
    unsigned long pitch = viewport.m_pitch >> 1;
    unsigned short *pixel = viewport.m_pixels + (unsigned short)point.m_y * pitch + (unsigned short)point.m_x;
    if (RHMessengerField<unsigned short>(g_unk0x6c11d0, 0x10c) == 16)
    {
        if (count <= 0)
            return;
        int remaining = count;
        int i = 0;
        do
        {
            unsigned short source = pattern[i];
            int blend = (32 - (unsigned short)((RHMessengerField<unsigned short *>(this, 0x54)[i] * level) >> 5)) * 2;
            if (blend > 32)
                blend = 32;
            *pixel = RHMessengerBlend(source, *pixel, (unsigned short)blend, 0xf800, 0x7e0);
            pixel += pitch;
            ++i;
        } while (--remaining);
    }
    else
    {
        if (count <= 0)
            return;
        int remaining = count;
        int i = 0;
        do
        {
            unsigned short source = pattern[i];
            int blend = (32 - (unsigned short)((RHMessengerField<unsigned short *>(this, 0x54)[i] * level) >> 5)) * 2;
            if (blend > 32)
                blend = 32;
            *pixel = RHMessengerBlend(source, *pixel, (unsigned short)blend, 0x7c00, 0x3e0);
            pixel += pitch;
            ++i;
        } while (--remaining);
    }
}

// Force emission: a non-inline member function defined here is emitted into the
// object; this out-of-line call keeps RHMessenger::Serialize and
// RHMessenger::SerializeLockUser in the build.
void RHMessenger::Emit(SBFile &file)
{
    Subscribe(0);
    Unsubscribe(0);
    FUN_00547280();
    Serialize(file);
    SerializeLockUser(file);
}

#include "RHMouseMessage.h"

#include "RHActorMessage.h"


// FUNCTION: GAME 0x00549030
RHMessage::RHMessage(int type, int value) : m_type(type), m_value(value)
{
}

// FUNCTION: GAME 0x00549050
void *RHMessage::FUN_00549050(unsigned flags)
{
    this->~RHMessage();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x00549070
RHMessage::RHMessage(int type) : m_type(type), m_value(0)
{
}

// FUNCTION: GAME 0x00549090
RHMessage::~RHMessage()
{
}

// FUNCTION: GAME 0x005490a0
RHUnk5490f0::RHUnk5490f0(int command, int value) : RHMessage(0, value)
{
    m_unk0c = command;
}

// FUNCTION: GAME 0x005490d0
void *RHUnk5490f0::FUN_005490d0(unsigned flags)
{
    this->~RHUnk5490f0();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x005490f0
RHUnk5490f0::RHUnk5490f0(int value) : RHMessage(0)
{
    m_unk0c = value;
}

// FUNCTION: GAME 0x00549120
RHUnk00549120::RHUnk00549120(int value, const SBGeoPoint2D &point) : RHMessage(1), m_0c(value), m_10(point)
{
}

// FUNCTION: GAME 0x00549180
void *RHUnk00549120::FUN_00549180(unsigned flags)
{
    this->~RHUnk00549120();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x005491a0
RHUnk00549120::RHUnk00549120(int value, const SBGeoPoint2D &point, int extra)
    : RHMessage(1, extra), m_0c(value), m_10(point)
{
}

// FUNCTION: GAME 0x00549200
RHUnk00549120::~RHUnk00549120()
{
}

// FUNCTION: GAME 0x00549250
RHUnk00549250::RHUnk00549250(int command, void *actor) : RHMessage(2), m_0c(command), m_10(actor)
{
}

// FUNCTION: GAME 0x00549280
void *RHUnk00549250::FUN_00549280(unsigned flags)
{
    this->~RHUnk00549250();
    if (flags & 1)
        operator delete(this);
    return this;
}
