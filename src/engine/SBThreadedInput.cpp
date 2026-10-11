#include "SBThreadedInput.h"
#include <stdlib.h>
#include "RHDrawManager.h"
#include <new>
#include <memory>
#include <list>
#include "SBResourceManager.h"

class RHUnk00613e90
{
public:
    RHUnk00613e90();
    ~RHUnk00613e90();
    unsigned char m_00[8];
    unsigned long m_pitch;
    unsigned short m_depth;
    unsigned char m_0e[2];
    unsigned short *m_data;
    unsigned char m_14[4];
};

class RHUnkFXDraw
{
public:
    bool Unk005e5a00(unsigned long, RHUnk00613e90 &, unsigned long);
    void Unk005e5ea0(RHUnk00613e90 &);
    unsigned short FUN_005e56c0(unsigned long);
    unsigned short FUN_005e5750(unsigned long);
    unsigned long Unk005e4ed0(int, int, int, int);
};

class RHMobileUnk00607da0
{
public:
    RHMobileUnk00607da0 &FUN_00607da0(const RHMobileUnk00607da0 &other);
};

class RHUnk005e6440
{
public:
    void Blit(unsigned long, SBGeoBoundingBox2D *, unsigned long, SBGeoBoundingBox2D *, unsigned long);
};

extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(void *);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(void *);
extern "C" __declspec(dllimport) unsigned long __stdcall SuspendThread(void *);
extern "C" __declspec(dllimport) int __stdcall TerminateThread(void *, unsigned long);
extern "C" __declspec(dllimport) int __stdcall CloseHandle(void *);
extern "C" __declspec(dllimport) void __stdcall DeleteCriticalSection(void *);
extern "C" __declspec(dllimport) void __stdcall InitializeCriticalSection(void *);
extern "C" __declspec(dllimport) void *__stdcall CreateThread(void *, unsigned long, unsigned long (__stdcall *)(void *), void *, unsigned long, unsigned long *);

// GLOBAL: GAME 0x006c1230
static unsigned long g_inputCriticalSection[6];

// GLOBAL: GAME 0x006c1268
static unsigned long g_inputCount;

// GLOBAL: GAME 0x006c12e0
static bool g_instantRefresh;

extern short g_lastXMove;

// GLOBAL: GAME 0x006c12c0
static bool g_validSaveBuffer;

// GLOBAL: GAME 0x006c1330
static void *g_mouseEvent;

// GLOBAL: GAME 0x006c1334
static void *g_keyboardEvent;

// GLOBAL: GAME 0x006c12b8
static RHUnkFXDraw *g_inputDrawManager;

struct SBThreadedInputElement
{
    bool m_keyboard;
    unsigned long m_offset;
    unsigned long m_data;
    unsigned long m_0c;
    unsigned long m_10;
};

struct SBInputNode
{
    SBInputNode *m_next;
    SBInputNode *m_previous;
    SBThreadedInputElement m_value;
};

// GLOBAL: GAME 0x006c1264
SBInputNode *g_inputHead;

// GLOBAL: GAME 0x006c1270
static bool g_inputChanged;

// GLOBAL: GAME 0x006c12ac
static bool g_mouseEnabled;

struct SBInputPosition
{
    float m_x;
    float m_y;
};

// GLOBAL: GAME 0x006c1300
static SBInputPosition g_inputPosition;

// GLOBAL: GAME 0x006c12e8
static SBGeoBoundingBox2D g_inputClipping;

// GLOBAL: GAME 0x006c1338
static SBResourceManager *g_inputResources;

extern unsigned short g_currentCursor;
extern unsigned short g_currentFrame;

// GLOBAL: GAME 0x006c1218
static unsigned long g_frameTime;

extern "C" __declspec(dllimport) unsigned long __stdcall GetTickCount();

// GLOBAL: GAME 0x006c1294
static bool g_selfIncrement;

// GLOBAL: GAME 0x006c1298
static SBInputPosition g_hotSpot;

// GLOBAL: GAME 0x006c12b0
static unsigned long g_renderingSurface;

// GLOBAL: GAME 0x006c125c
static unsigned long g_backgroundEven;

// GLOBAL: GAME 0x006c12fc
static unsigned long g_backgroundOdd;

// GLOBAL: GAME 0x006c12a4
static unsigned long g_unk0x006c12a4;

// GLOBAL: GAME 0x006c130c
static unsigned long g_unk0x006c130c;

// GLOBAL: GAME 0x006c1318
static unsigned long g_unk0x006c1318;

// GLOBAL: GAME 0x006c1310
static unsigned long g_unk0x006c1310;

class RHUnk005ef320;
extern RHUnk005ef320 *g_unk0x6c11d0;

struct SBThreadedInputEvent
{
    unsigned long m_offset;
    unsigned long m_data;
    unsigned long m_08;
    unsigned long m_0c;
};

// GLOBAL: GAME 0x006c1204
static bool g_unk0x006c1204;

class SBInputListStorage : public std::list<SBThreadedInputElement>
{
public:
    static __forceinline _Nodeptr BuyNode(_Nodeptr next, _Nodeptr previous)
    {
        std::allocator<SBThreadedInputElement> allocator;
        _Nodeptr node = (_Nodeptr)allocator._Charalloc(sizeof(_Node));
        _Acc::_Next(node) = next != 0 ? next : node;
        _Acc::_Prev(node) = previous != 0 ? previous : node;
        return node;
    }
    static __forceinline iterator Position(SBInputNode *head)
    {
        return iterator((_Nodeptr)head);
    }
    static __forceinline iterator Insert(iterator position, const SBThreadedInputElement &element)
    {
        _Nodeptr node = position._Mynode();
        _Acc::_Prev(node) = BuyNode(node, _Acc::_Prev(node));
        node = _Acc::_Prev(node);
        _Acc::_Next(_Acc::_Prev(node)) = node;
        std::_Construct(&_Acc::_Value(node), element);
        return iterator(node);
    }
};

static inline void InsertInput(const SBThreadedInputElement &element)
{
    SBInputListStorage::Insert(SBInputListStorage::Position(g_inputHead), element);
    ++g_inputCount;
    g_inputChanged = true;
}

// FUNCTION: GAME 0x005f0c20
bool SBThreadedInput::FUN_005f0c20(bool keyboard, SBThreadedInputEvent &event)
{
    if (g_unk0x006c1204 == true)
        return true;
    if (keyboard == true && event.m_offset > 255)
        return false;
    SBThreadedInputElement element;
    element.m_keyboard = keyboard;
    element.m_offset = event.m_offset;
    element.m_data = event.m_data;
    element.m_0c = event.m_08;
    element.m_10 = event.m_0c;
    EnterCriticalSection(g_inputCriticalSection);
    InsertInput(element);
    LeaveCriticalSection(g_inputCriticalSection);
    return true;
}

// FUNCTION: GAME 0x005f0ce0
unsigned long FUN_005f0ce0()
{
    EnterCriticalSection(g_inputCriticalSection);
    unsigned long count = g_inputCount;
    LeaveCriticalSection(g_inputCriticalSection);
    return count;
}

// FUNCTION: GAME 0x005f0d10
unsigned long SBThreadedInput::GetNumberOfInputsUTS()
{
    return g_inputCount;
}

// FUNCTION: GAME 0x005f0fa0
bool SBThreadedInput::CleanUpInputs()
{
    EnterCriticalSection(g_inputCriticalSection);
    SBInputNode *end = *(SBInputNode *volatile *)&g_inputHead;
    SBInputNode *node = end->m_next;
    while (node != end) {
        SBInputNode *erased = node;
        node = node->m_next;
        erased->m_previous->m_next = erased->m_next;
        erased->m_next->m_previous = erased->m_previous;
        operator delete(erased);
        --g_inputCount;
    }
    g_inputChanged = true;
    LeaveCriticalSection(g_inputCriticalSection);
    return true;
}

// FUNCTION: GAME 0x005f13c0
void SBThreadedInput::Run()
{
    g_unk0x006c12a4 = g_inputDrawManager->Unk005e4ed0(55, 55, 0, 0);
    g_unk0x006c130c = g_inputDrawManager->Unk005e4ed0(55, 55, 0, 0);
    g_unk0x006c1318 = g_inputDrawManager->Unk005e4ed0(55, 55, 0, 0);
    g_unk0x006c1310 = g_inputDrawManager->Unk005e4ed0(110, 110, 0, 0);
    g_backgroundEven = g_inputDrawManager->Unk005e4ed0(55, 55, 0, 0);
    g_backgroundOdd = g_inputDrawManager->Unk005e4ed0(55, 55, 0, 0);
    InitializeCriticalSection(g_inputCriticalSection);
    m_thread = CreateThread(0, 0, (unsigned long (__stdcall *)(void *))0x005f09e0, 0, 0, &m_threadId);
    if (m_thread == 0) {
        m_running = false;
        return;
    }
    m_active = true;
    m_running = true;
}

// FUNCTION: GAME 0x005f14c0
bool SBThreadedInput::SetCursor(unsigned short cursor, bool selfIncrement)
{
    EnterCriticalSection(g_inputCriticalSection);
    g_selfIncrement = selfIncrement;
    if (g_currentCursor != cursor) {
        g_currentCursor = cursor;
        g_currentFrame = 0;
        g_frameTime = GetTickCount();
        SBGeoVector2D hotSpot(g_inputResources->FUN_00600450(cursor));
        ((RHUnk005fc3b0 *)&g_hotSpot)->FUN_005fc430(hotSpot);
    }
    LeaveCriticalSection(g_inputCriticalSection);
    return true;
}

// FUNCTION: GAME 0x005f1580
bool SBThreadedInput::AttachToDisplay(unsigned long surface)
{
    g_inputDrawManager = (RHUnkFXDraw *)g_unk0x6c11d0;
    g_renderingSurface = surface;
    g_inputClipping.FUN_00609050(SBGeoPoint2D(0.0f, 0.0f),
        SBGeoPoint2D((float)g_inputDrawManager->FUN_005e56c0(0), (float)g_inputDrawManager->FUN_005e5750(0)));
    return true;
}

// FUNCTION: GAME 0x005f1650
void SBThreadedInput::ClearBackgroundStack()
{
    ((RHMobileUnk00607da0 *)((char *)this + 0x14))->FUN_00607da0((const RHMobileUnk00607da0 &)SBGeoBoundingBox2D());
    ((RHMobileUnk00607da0 *)((char *)this + 0x28))->FUN_00607da0((const RHMobileUnk00607da0 &)SBGeoBoundingBox2D());
}

// FUNCTION: GAME 0x005f19c0
void SBThreadedInput::PopMouseBackground(bool wait)
{
    unsigned long flags = wait == true ? 8 : 0;
    if ((*(unsigned long *)((char *)this + 0x10) - 1 & 1) == 0) {
        SBGeoBoundingBox2D &box = *(SBGeoBoundingBox2D *)((char *)this + 0x14);
        if (box.Unk00608f30() && box.m_max.m_x - box.m_min.m_x > g_unk0x00677488 &&
            box.m_max.m_y - box.m_min.m_y > g_unk0x00677488)
            ((RHUnk005e6440 *)g_inputDrawManager)->Blit(g_backgroundEven,
                (SBGeoBoundingBox2D *)((char *)this + 0x3c), 0, &box, flags);
    } else {
        SBGeoBoundingBox2D &box = *(SBGeoBoundingBox2D *)((char *)this + 0x28);
        if (box.Unk00608f30() && box.m_max.m_x - box.m_min.m_x > g_unk0x00677488 &&
            box.m_max.m_y - box.m_min.m_y > g_unk0x00677488)
            ((RHUnk005e6440 *)g_inputDrawManager)->Blit(g_backgroundOdd,
                (SBGeoBoundingBox2D *)((char *)this + 0x50), 0, &box, flags);
    }
}

// FUNCTION: GAME 0x005f2640
void SBThreadedInput::AccumulateColor16(unsigned short &red, unsigned short &green, unsigned short &blue, unsigned short color, unsigned short weight)
{
    red += (color >> 11) * weight;
    green += ((color >> 5) & 0x3e) * weight;
    blue += (color & 0x1f) * weight;
}

// FUNCTION: GAME 0x005f2680
void SBThreadedInput::AccumulateColor15(unsigned short &red, unsigned short &green, unsigned short &blue, unsigned short color, unsigned short weight)
{
    red += ((color >> 10) & 0x1f) * weight;
    green += ((color >> 5) & 0x1f) * weight;
    blue += (color & 0x1f) * weight;
}

// FUNCTION: GAME 0x005f4200
bool SBThreadedInput::BlitDouble(unsigned long source, const SBGeoBoundingBox2D &sourceBox, unsigned long destination, const SBGeoBoundingBox2D &destinationBox, unsigned long flags)
{
    RHUnk00613e90 destinationView;
    RHUnk00613e90 sourceView;
    if (!g_inputDrawManager->Unk005e5a00(source, sourceView, 0))
        return false;
    if (!g_inputDrawManager->Unk005e5a00(destination, destinationView, 0)) {
        g_inputDrawManager->Unk005e5ea0(sourceView);
        return false;
    }
    unsigned long sourcePitch = sourceView.m_pitch >> 1;
    float sourceX = sourceBox.m_min.m_x;
    float sourceY = sourceBox.m_min.m_y;
    unsigned short *sourceRow = sourceView.m_data + (int)sourceX + (int)sourceY * sourcePitch;
    unsigned long destinationPitch = destinationView.m_pitch >> 1;
    float destinationX = destinationBox.m_min.m_x;
    float destinationY = destinationBox.m_min.m_y;
    unsigned long *destinationRow = (unsigned long *)(destinationView.m_data + (int)destinationX + (int)destinationY * destinationPitch);
    unsigned short width = (unsigned short)(destinationBox.m_max.m_x - destinationBox.m_min.m_x);
    width >>= 1;
    unsigned short height = (unsigned short)(destinationBox.m_max.m_y - destinationBox.m_min.m_y);
    height >>= 1;
    if (height > 0) {
        unsigned long rows = height;
        do {
            unsigned short *sourceStart = sourceRow;
            unsigned long *destinationStart = destinationRow;
            if (width > 0) {
                unsigned long columns = width;
                do {
                    unsigned long color = *sourceRow++;
                    color |= color << 16;
                    *destinationRow++ = color;
                    *(unsigned long *)((char *)(destinationRow - 1) + destinationPitch * 2) = color;
                } while (--columns != 0);
            }
            sourceRow = sourceStart + sourcePitch;
            destinationRow = destinationStart + destinationPitch;
        } while (--rows != 0);
    }
    g_inputDrawManager->Unk005e5ea0(sourceView);
    g_inputDrawManager->Unk005e5ea0(destinationView);
    return true;
}

// FUNCTION: GAME 0x005f43d0
void SBThreadedInput::ChangeShadowIntoPulse(unsigned long surface, const SBGeoBoundingBox2D &box, unsigned short level)
{
    RHUnk00613e90 view;
    if (!g_inputDrawManager->Unk005e5a00(surface, view, 0))
        return;
    unsigned long pitch = view.m_pitch >> 1;
    float x = box.m_min.m_x;
    float y = box.m_min.m_y;
    unsigned short *row = view.m_data + (unsigned short)x + (unsigned short)y * pitch;
    unsigned short width = (unsigned short)(box.m_max.m_x - box.m_min.m_x);
    unsigned short height = (unsigned short)(box.m_max.m_y - box.m_min.m_y);
    int bounded;
    if (level > 0) {
        bounded = level;
        if (bounded > 100)
            bounded = 100;
    } else {
        bounded = 0;
    }
    level = bounded;
    unsigned short color;
    if (view.m_depth == 16)
        color = (((level * 60 / 100 & 0x3f) | ((level * 31 / 100) << 6)) << 5) | (level * 19 / 100 & 0x1f);
    else
        color = ((((level * 31 / 100 & 0x1f) << 5) | (level * 30 / 100 & 0x1f)) << 5) | (level * 23 / 100 & 0x1f);
    if (height > 0) {
        unsigned long rows = height;
        do {
            if (width > 0) {
                unsigned short *pixel = row;
                unsigned long columns = width;
                do {
                    if (*pixel == 0x1f)
                        *pixel = color;
                    ++pixel;
                } while (--columns != 0);
            }
            row += pitch;
        } while (--rows != 0);
    }
    g_inputDrawManager->Unk005e5ea0(view);
}

struct SBInputMouseState
{
    short m_x;
    short m_y;
    short m_wheel;
    unsigned char m_left;
    unsigned char m_right;
    unsigned char m_middle;
};

// GLOBAL: GAME 0x006c1208
static SBInputMouseState g_oldMouse;

// GLOBAL: GAME 0x006c1220
static SBInputPosition g_mouseDisplace;

// GLOBAL: GAME 0x006c1324
static unsigned short g_buttonState;

// GLOBAL: GAME 0x006c1214
static unsigned short g_leftCount;

// GLOBAL: GAME 0x006c1248
static unsigned short g_leftDefault;

// GLOBAL: GAME 0x006c1258
static unsigned short g_rightCount;

// GLOBAL: GAME 0x006c12b4
static unsigned short g_rightDefault;

// GLOBAL: GAME 0x006c131e
static unsigned short g_middleCount;

// GLOBAL: GAME 0x006c131c
static unsigned short g_middleDefault;

// Parked: VC6 carries the pressed constant in ecx instead of eax.
// STUB: GAME 0x005f45d0
void SBThreadedInput::InputLoop(const SBInputMouseState &mouse)
{
    float x = mouse.m_x;
    float y = mouse.m_y;
    g_mouseDisplace.m_x = x;
    g_mouseDisplace.m_y = y;
    ((SBGeoPoint2D *)&g_inputPosition)->FUN_005fc1e0(*(SBGeoPoint2D *)&g_mouseDisplace);
    CalculatePosition();
    g_buttonState = 0;
    if (!mouse.m_left && g_oldMouse.m_left == true) {
        if (g_leftCount == 0) {
            g_buttonState = 1;
            g_leftCount = g_leftDefault;
        } else {
            g_buttonState = 8;
        }
    }
    if (mouse.m_left == true && !g_oldMouse.m_left)
        g_buttonState |= 64;
    if (!mouse.m_right && g_oldMouse.m_right == true) {
        if (g_rightCount == 0) {
            g_buttonState |= 2;
            g_rightCount = g_rightDefault;
        } else {
            g_buttonState |= 16;
        }
    }
    if (mouse.m_right == true && !g_oldMouse.m_right)
        g_buttonState |= 128;
    if (!mouse.m_middle && g_oldMouse.m_middle == true) {
        if (g_middleCount == 0) {
            g_buttonState |= 4;
            g_middleCount = g_middleDefault;
        } else {
            g_buttonState |= 32;
        }
    }
    if (mouse.m_middle == true && !g_oldMouse.m_middle)
        g_buttonState |= 256;
}

// FUNCTION: GAME 0x005f4700
bool SBThreadedInput::CalculatePosition()
{
    if (g_inputPosition.m_x < g_inputClipping.m_min.m_x)
        g_inputPosition.m_x = g_inputClipping.m_min.m_x;
    if (g_inputClipping.m_max.m_x <= g_inputPosition.m_x)
        g_inputPosition.m_x = g_inputClipping.m_max.m_x - g_unk0x0067749c;
    if ((double)g_inputPosition.m_y < g_inputClipping.m_min.m_y) {
        float y = g_inputClipping.m_min.m_y;
        g_inputPosition.m_y = y;
    }
    if ((double)g_inputPosition.m_y >= g_inputClipping.m_max.m_y)
        g_inputPosition.m_y = g_inputClipping.m_max.m_y - g_unk0x0067749c;
    return true;
}

// Parked: VC6 swaps the carried delay and GetTickCount registers.
// STUB: GAME 0x005f4790
bool SBThreadedInput::CalculateFrame()
{
    unsigned short duration = g_inputResources->FUN_00600390(g_currentCursor);
    unsigned long (__stdcall *tick)() = GetTickCount;
    unsigned long delay = duration * 25;
    if (tick() - g_frameTime > delay) {
        g_frameTime = tick();
        ++g_currentFrame;
        if (g_currentFrame >= g_inputResources->FUN_00600550(g_currentCursor))
            g_currentFrame = 0;
    }
    return true;
}

// FUNCTION: GAME 0x005f4810
int SBThreadedInput::GetDirection()
{
    if (abs(g_lastXMove) > 20) {
        if (g_lastXMove > 0) {
            g_lastXMove = 0;
            return 0;
        }
        g_lastXMove = 0;
        return 1;
    }
    return 2;
}

// FUNCTION: GAME 0x005f4840
bool SBThreadedInput::Suspend()
{
    SuspendThread(m_thread);
    return true;
}

// FUNCTION: GAME 0x005f4850
bool SBThreadedInput::Destroy()
{
    TerminateThread(m_thread, 0);
    CloseHandle(g_mouseEvent);
    CloseHandle(g_keyboardEvent);
    DeleteCriticalSection(g_inputCriticalSection);
    return true;
}

// FUNCTION: GAME 0x005f4890
void SBThreadedInput::SetTheClippingBox(SBGeoBoundingBox2D box)
{
    ((RHMobileUnk00607da0 *)&g_inputClipping)->FUN_00607da0((const RHMobileUnk00607da0 &)box);
    CalculatePosition();
}

// FUNCTION: GAME 0x005f4900
void SBThreadedInput::SetMouseEnabled(bool enabled)
{
    if (enabled == true && !g_mouseEnabled) {
        g_validSaveBuffer = false;
        CleanUpInputs();
    }
    g_mouseEnabled = enabled;
}

// FUNCTION: GAME 0x005f4930
void SBThreadedInput::SetInstantRefreshMode(bool enabled)
{
    if (enabled == true && !g_instantRefresh)
        g_validSaveBuffer = false;
    g_instantRefresh = enabled;
}

// FUNCTION: GAME 0x005f4a60
void SBThreadedInput::PushButton(SBButton button)
{
    SBThreadedInputElement element;
    element.m_keyboard = false;
    switch (button) {
    case SBButtonLeft: element.m_offset = 12; break;
    case SBButtonRight: element.m_offset = 13; break;
    case SBButtonMiddle: element.m_offset = 14; break;
    }
    element.m_data = 128;
    EnterCriticalSection(g_inputCriticalSection);
    InsertInput(element);
    LeaveCriticalSection(g_inputCriticalSection);
}

// FUNCTION: GAME 0x005f4b10
void SBThreadedInput::ReleaseButton(SBButton button)
{
    SBThreadedInputElement element;
    element.m_keyboard = false;
    switch (button) {
    case SBButtonLeft: element.m_offset = 12; break;
    case SBButtonRight: element.m_offset = 13; break;
    case SBButtonMiddle: element.m_offset = 14; break;
    }
    element.m_data = 0;
    EnterCriticalSection(g_inputCriticalSection);
    InsertInput(element);
    LeaveCriticalSection(g_inputCriticalSection);
}

// FUNCTION: GAME 0x005f4bc0
SBGeoVector2D SBThreadedInput::GetSize()
{
    unsigned long surface;
    g_inputResources->FUN_00600920(g_currentCursor, g_currentFrame, surface);
    return SBGeoVector2D((float)g_inputDrawManager->FUN_005e56c0(surface),
        (float)g_inputDrawManager->FUN_005e5750(surface));
}

// FUNCTION: GAME 0x005f4c50
unsigned short SBThreadedInput::GetHeight()
{
    unsigned long surface;
    g_inputResources->FUN_00600920(g_currentCursor, g_currentFrame, surface);
    return g_inputDrawManager->FUN_005e5750(surface);
}

void SBThreadedInput::Emit()
{
    unsigned short red = 0;
    unsigned short green = 0;
    unsigned short blue = 0;
    FUN_005f0ce0();
    GetNumberOfInputsUTS();
    FUN_005f0c20(false, *(SBThreadedInputEvent *)this);
    PushButton(SBButtonLeft);
    ReleaseButton(SBButtonLeft);
    CleanUpInputs();
    Run();
    CalculatePosition();
    CalculateFrame();
    SetMouseEnabled(true);
    SetTheClippingBox(*(SBGeoBoundingBox2D *)this);
    ClearBackgroundStack();
    SetCursor(0, false);
    AttachToDisplay(0);
    InputLoop(*(SBInputMouseState *)this);
    PopMouseBackground(false);
    AccumulateColor16(red, green, blue, red, green);
    AccumulateColor15(red, green, blue, red, green);
    BlitDouble(red, *(SBGeoBoundingBox2D *)this, green, *(SBGeoBoundingBox2D *)this, 0);
    ChangeShadowIntoPulse(red, *(SBGeoBoundingBox2D *)this, green);
    GetDirection();
    Suspend();
    Destroy();
    SetInstantRefreshMode(true);
    GetSize();
    GetHeight();
}
