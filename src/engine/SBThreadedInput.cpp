#include "SBThreadedInput.h"
#include <stdlib.h>
#include "RHDrawManager.h"
#include <new>
#include <memory>
#include <list>
#include <iterator>
#include "SBResourceManager.h"
#include "RHScriptListCore.h"

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
    unsigned long Unk005e4ed0(int, int, int, bool);
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

// GLOBAL: GAME 0x006c1260
RHUnk0046eb30 g_inputList;

#define g_inputHead (*(SBInputNode **)&g_inputList.head)
#define g_inputCount (*(unsigned long *)&g_inputList.count)
#define g_inputCurrent (*(SBInputNode **)&g_inputList.cursor)
#define g_inputChanged g_inputList.valid
#define g_inputIndex g_inputList.index

// GLOBAL: GAME 0x006c12c1
static bool g_inputAlternate;

// GLOBAL: GAME 0x006c1229
static bool g_inputRandomMotion;

struct SBInputMouseState
{
    short m_x;
    short m_y;
    short m_wheel;
    unsigned char m_left;
    unsigned char m_right;
    unsigned char m_middle;
};

// GLOBAL: GAME 0x006c12ac
bool g_mouseEnabled;

// GLOBAL: GAME 0x006c1300
SBInputPosition g_inputPosition;

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
SBInputPosition g_hotSpot;

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
    iterator InsertWithCount(iterator position, const SBThreadedInputElement &element);
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

struct RHUnk005c9010Iterator;
void FUN_005c9010(RHUnk005c9010Iterator &, int, std::bidirectional_iterator_tag);

static inline void AdvanceInput(int distance)
{
    for (; distance > 0; --distance)
        g_inputCurrent = g_inputCurrent->m_next;
    for (; distance < 0; ++distance)
        g_inputCurrent = g_inputCurrent->m_previous;
}

// Parked: cached-index lowering saves an extra register and schedules global loads differently.
// STUB: GAME 0x005f0d20
bool SBThreadedInput::FUN_005f0d20(int index, SBInputMouseState &mouse, unsigned char *keyboard)
{
    if (g_inputChanged)
    {
        int distance;
        if (index <= ((int)g_inputCount + 1) / 2)
        {
            g_inputCurrent = g_inputHead->m_next;
            distance = index;
        }
        else
        {
            g_inputCurrent = g_inputHead;
            distance = index - g_inputCount;
        }
        std::bidirectional_iterator_tag category;
        FUN_005c9010((RHUnk005c9010Iterator &)g_inputCurrent, distance, category);
        g_inputChanged = false;
        g_inputIndex = index;
    }
    else if (index != g_inputIndex)
    {
        if (index < g_inputIndex)
        {
            int distance;
            if (index < (g_inputIndex + 1) / 2)
            {
                g_inputCurrent = g_inputHead->m_next;
                distance = index;
            }
            else
                distance = index - g_inputIndex;
            std::bidirectional_iterator_tag category;
            FUN_005c9010((RHUnk005c9010Iterator &)g_inputCurrent, distance, category);
        }
        else if (index < (g_inputIndex + (int)g_inputCount) / 2)
            AdvanceInput(index - g_inputIndex);
        else
        {
            g_inputCurrent = g_inputHead;
            AdvanceInput(index - g_inputCount);
        }
        g_inputIndex = index;
    }
    SBThreadedInputElement element = g_inputCurrent->m_value;
    if (element.m_keyboard)
        keyboard[element.m_offset] = element.m_data;
    else if (g_inputAlternate)
    {
        if (element.m_offset == 0)
            g_lastXMove += (short)element.m_data;
        else if (element.m_offset == 4)
            g_lastXMove -= (short)element.m_data;
    }
    else
    {
        switch (element.m_offset)
        {
        case 0: mouse.m_x = (short)element.m_data; break;
        case 4: mouse.m_y = (short)element.m_data; break;
        case 8: mouse.m_wheel = (short)element.m_data; break;
        case 12: mouse.m_left = (element.m_data >> 7) & 1; break;
        case 13: mouse.m_right = (element.m_data >> 7) & 1; break;
        case 14: mouse.m_middle = (element.m_data >> 7) & 1; break;
        }
    }
    return true;
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

#include "ToolboxMouseState.h"

static inline void RemoveFirstInput()
{
    SBInputNode *node = g_inputHead->m_next;
    node->m_previous->m_next = node->m_next;
    node->m_next->m_previous = node->m_previous;
    operator delete(node);
    --g_inputCount;
    g_inputChanged = true;
}

#include "SBInput.h"

int FUN_005fb030(unsigned scanCode, unsigned short *output, int capacity, int mode);

// STUB: GAME 0x005f1000
unsigned short SBThreadedInput::GetChar()
{
    for (;;)
    {
        while (FUN_005f0ce0() == 0)
            SBInputUnk005fb730::mpInput->FUN_005fbfc0();
        EnterCriticalSection(g_inputCriticalSection);
        SBInputNode *node = g_inputHead->m_next;
        SBInputNode *next = node->m_next;
        SBThreadedInputElement element = node->m_value;
        node->m_previous->m_next = next;
        node->m_next->m_previous = node->m_previous;
        operator delete(node);
        --g_inputCount;
        g_inputChanged = true;
        LeaveCriticalSection(g_inputCriticalSection);
        if (element.m_keyboard != true || element.m_data != 0)
            continue;
        unsigned short characters[2];
        if (FUN_005fb030(element.m_offset, characters, 2, 1) > 0)
        {
            unsigned short character = *(unsigned char *)characters;
            if (character != 0)
                return character;
        }
        else
        {
            switch (element.m_offset)
            {
            case 200: return 0x101;
            case 208: return 0x102;
            case 205: return 0x104;
            case 203: return 0x103;
            case 211: return 0x105;
            case 210: return 0x108;
            }
        }
    }
}

// Parked: queue-consumer helper layering and conditional register saves differ from the original.
// STUB: GAME 0x005f1150
bool FUN_005f1150(ToolboxMouseState &mouse, unsigned char *keyboard)
{
    EnterCriticalSection(g_inputCriticalSection);
    if (g_inputCount == 0)
    {
        LeaveCriticalSection(g_inputCriticalSection);
        return false;
    }
    SBThreadedInputElement element = g_inputHead->m_next->m_value;
    RemoveFirstInput();
    LeaveCriticalSection(g_inputCriticalSection);
    if (element.m_keyboard == true)
    {
        if (element.m_offset <= 255)
            keyboard[element.m_offset] = element.m_data;
        return true;
    }
    switch (element.m_offset)
    {
    case 0:
        if (g_inputAlternate)
            return true;
        mouse.m_x = (short)element.m_data;
        EnterCriticalSection(g_inputCriticalSection);
        if ((int)g_inputCount > 0)
        {
            element = g_inputHead->m_next->m_value;
            if (element.m_keyboard == false && element.m_offset == 4)
            {
                mouse.m_y = (short)element.m_data;
                RemoveFirstInput();
            }
        }
        LeaveCriticalSection(g_inputCriticalSection);
        return true;
    case 4:
        if (g_inputAlternate)
            return true;
        mouse.m_y = (short)element.m_data;
        EnterCriticalSection(g_inputCriticalSection);
        if ((int)g_inputCount > 0)
        {
            element = g_inputHead->m_next->m_value;
            if (element.m_keyboard == false && element.m_offset == 0)
            {
                mouse.m_x = (short)element.m_data;
                RemoveFirstInput();
            }
        }
        LeaveCriticalSection(g_inputCriticalSection);
        return true;
    case 8:
        if (!g_inputAlternate)
            mouse.m_flags = (unsigned short)element.m_data;
        return true;
    case 12:
        ((unsigned char *)&mouse.m_buttons)[0] = (element.m_data >> 7) & 1;
        return true;
    case 13:
        ((unsigned char *)&mouse.m_buttons)[1] = (element.m_data >> 7) & 1;
        return true;
    case 14:
        ((unsigned char *)&mouse.m_extra)[0] = (element.m_data >> 7) & 1;
    }
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

// FUNCTION: GAME 0x005f1490
bool FUN_005f1490(const SBGeoPoint2D &first, const SBGeoPoint2D &second)
{
    ((SBGeoPoint2D *)&g_inputPosition)->SBGeoPoint2D::operator=(first);
    ((RHUnk005fc3b0 *)&g_hotSpot)->FUN_005fc430(second);
    return true;
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
        SBGeoVector2D hotSpot((const SBGeoVector2D &)g_inputResources->FUN_00600450(cursor));
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
        if (box.Unk00608f30() && box.m_max.m_x - box.m_min.m_x > 0.0f &&
            box.m_max.m_y - box.m_min.m_y > 0.0f)
            ((RHUnk005e6440 *)g_inputDrawManager)->Blit(g_backgroundEven,
                (SBGeoBoundingBox2D *)((char *)this + 0x3c), 0, &box, flags);
    } else {
        SBGeoBoundingBox2D &box = *(SBGeoBoundingBox2D *)((char *)this + 0x28);
        if (box.Unk00608f30() && box.m_max.m_x - box.m_min.m_x > 0.0f &&
            box.m_max.m_y - box.m_min.m_y > 0.0f)
            ((RHUnk005e6440 *)g_inputDrawManager)->Blit(g_backgroundOdd,
                (SBGeoBoundingBox2D *)((char *)this + 0x50), 0, &box, flags);
    }
}

// Parked: first insertion copy and argument/store scheduling differ after two shapes.
// STUB: GAME 0x005f1a90
void SBThreadedInput::FUN_005f1a90()
{
    EnterCriticalSection(g_inputCriticalSection);
    if (g_inputRandomMotion == true)
    {
        int dx = rand() * 2 / RAND_MAX;
        if (rand() % 2 == 0)
            dx = -dx;
        if (dx)
        {
            SBThreadedInputElement element;
            element.m_keyboard = false;
            element.m_offset = 0;
            element.m_data = dx;
            InsertInput(element);
            ((SBGeoPoint2D *)&g_inputPosition)->FUN_005fc1e0(SBGeoVector2D((float)dx, 0.0f));
        }
        int dy = rand() * 2 / RAND_MAX;
        if (rand() % 2 == 0)
            dy = -dy;
        if (dy)
        {
            SBThreadedInputElement element;
            element.m_keyboard = false;
            element.m_offset = 4;
            element.m_data = dy;
            InsertInput(element);
            ((SBGeoPoint2D *)&g_inputPosition)->FUN_005fc1e0(SBGeoVector2D(0.0f, (float)dy));
        }
        CalculatePosition();
    }
    LeaveCriticalSection(g_inputCriticalSection);
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
        g_inputPosition.m_x = g_inputClipping.m_max.m_x - 1.0f;
    if ((double)g_inputPosition.m_y < g_inputClipping.m_min.m_y) {
        float y = g_inputClipping.m_min.m_y;
        g_inputPosition.m_y = y;
    }
    if ((double)g_inputPosition.m_y >= g_inputClipping.m_max.m_y)
        g_inputPosition.m_y = g_inputClipping.m_max.m_y - 1.0f;
    return true;
}

// Parked: direct import calls retain the carried delay and GetTickCount register swap.
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

// FUNCTION: GAME 0x005f4950
bool SBThreadedInput::ReachPosition(const SBGeoPoint2D &position)
{
    if (!g_inputClipping.FUN_00608400(position))
        return false;
    EnterCriticalSection(g_inputCriticalSection);
    SBThreadedInputElement element;
    element.m_keyboard = false;
    element.m_offset = 0;
    element.m_data = (short)(position.m_x - g_inputPosition.m_x);
    float x = position.m_x;
    g_inputPosition.m_x = x;
    typedef SBInputListStorage::iterator (SBInputListStorage::*Insert)(SBInputListStorage::iterator, const SBThreadedInputElement &);
    Insert insert = &SBInputListStorage::InsertWithCount;
    (((SBInputListStorage *)&g_inputList)->*insert)(SBInputListStorage::Position(g_inputHead), element);
    g_inputChanged = true;
    element.m_keyboard = false;
    element.m_offset = 4;
    element.m_data = (short)(position.m_y - g_inputPosition.m_y);
    float y = position.m_y;
    g_inputPosition.m_y = y;
    InsertInput(element);
    LeaveCriticalSection(g_inputCriticalSection);
    return true;
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

class RHUnk005f4c90List
{
public:
    RHUnk005f4c90List *m_next;
    RHUnk005f4c90List *m_prev;
    char m_08[0x14];
};

class RHUnk005f4c90
{
public:
    RHUnk005f4c90();
    char m_0;
    char m_1[3];
    RHUnk005f4c90List *m_4;
    int m_8;
    char m_c[4];
    bool m_10;
};

// FUNCTION: GAME 0x005f4c90
RHUnk005f4c90::RHUnk005f4c90()
{
    char value;
    m_0 = value;
    RHUnk005f4c90List *list = new RHUnk005f4c90List;
    list->m_next = list;
    list->m_prev = list;
    m_4 = list;
    m_8 = 0;
    m_10 = 1;
}

// FUNCTION: GAME 0x005f4cc0
SBInputListStorage::iterator SBInputListStorage::InsertWithCount(iterator position, const SBThreadedInputElement &element)
{
    iterator result = Insert(position, element);
    ++_Size;
    return result;
}

void SBThreadedInput::Emit()
{
    ReachPosition(*(SBGeoPoint2D *)&g_inputPosition);
    unsigned short red = 0;
    unsigned short green = 0;
    unsigned short blue = 0;
    FUN_005f0ce0();
    FUN_005f0d20(0, *(SBInputMouseState *)this, (unsigned char *)this);
    FUN_005f1a90();
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
