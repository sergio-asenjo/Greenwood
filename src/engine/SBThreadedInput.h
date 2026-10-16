#ifndef SBTHREADEDINPUT_H
#define SBTHREADEDINPUT_H

#include "Decomp.h"

class SBGeoBoundingBox2D;
class SBGeoVector2D;
struct SBThreadedInputEvent;
struct SBInputMouseState;

struct SBInputPosition
{
    float m_x;
    float m_y;
};

extern SBInputPosition g_inputPosition;
extern SBInputPosition g_hotSpot;

enum SBButton
{
    SBButtonLeft,
    SBButtonRight,
    SBButtonMiddle
};

class SBThreadedInput
{
public:
    static void AccumulateColor16(unsigned short &red, unsigned short &green, unsigned short &blue, unsigned short color, unsigned short weight);
    static void AccumulateColor15(unsigned short &red, unsigned short &green, unsigned short &blue, unsigned short color, unsigned short weight);
    static bool BlitDouble(unsigned long source, const SBGeoBoundingBox2D &sourceBox, unsigned long destination, const SBGeoBoundingBox2D &destinationBox, unsigned long flags);
    static void ChangeShadowIntoPulse(unsigned long surface, const SBGeoBoundingBox2D &box, unsigned short level);
    static unsigned long GetNumberOfInputsUTS();
    bool CleanUpInputs();
    static bool FUN_005f0c20(bool keyboard, SBThreadedInputEvent &event);
    static void PushButton(SBButton button);
    static void ReleaseButton(SBButton button);
    static bool CalculatePosition();
    static bool CalculateFrame();
    void Run();
    void SetMouseEnabled(bool enabled);
    static void SetTheClippingBox(SBGeoBoundingBox2D box);
    void ClearBackgroundStack();
    static bool SetCursor(unsigned short cursor, bool selfIncrement);
    static bool AttachToDisplay(unsigned long surface);
    static void InputLoop(const SBInputMouseState &mouse);
    void PopMouseBackground(bool wait);
    static int GetDirection();
    bool Suspend();
    bool Destroy();
    static void SetInstantRefreshMode(bool enabled);
    static SBGeoVector2D GetSize();
    static unsigned short GetHeight();
    void Emit();

private:
    undefined m_opaque00[4];
    unsigned long m_threadId; // 0x04
    void *m_thread; // 0x08
    bool m_running; // 0x0c
    bool m_active; // 0x0d
    undefined m_opaque0e[0x56];
};

unsigned long FUN_005f0ce0();

#endif
