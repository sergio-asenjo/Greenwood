#ifndef SBTHREADEDINPUT_H
#define SBTHREADEDINPUT_H

#include "Decomp.h"
#include "SBThread.h"
#ifndef SBGEO_BOUNDINGBOX2D_VIEW
#include "SBGeoBoundingBox2DCore.h"
#endif

class SBGeoBoundingBox2D;
class SBGeoVector2D;
class SBGeoPoint2D;
struct SBThreadedInputEvent;
struct SBInputMouseState;

class RHUnk00564020;

extern bool g_inputAlternate;
extern bool g_instantRefresh;
extern bool g_mouseEnabled;

enum SBButton
{
    SBButtonLeft,
    SBButtonRight,
    SBButtonMiddle
};

// VTABLE: GAME 0x0067a798
// SIZE 0x64
class SBThreadedInput : public SBThread
{
public:
    SBThreadedInput();
    virtual ~SBThreadedInput(); // vtable+0x00
    void FUN_005f1700();
    unsigned FUN_005104b0();
    static void AccumulateColor16(unsigned short &red, unsigned short &green, unsigned short &blue, unsigned short color, unsigned short weight);
    static void AccumulateColor15(unsigned short &red, unsigned short &green, unsigned short &blue, unsigned short color, unsigned short weight);
    static bool BlitBlur(unsigned long source, const SBGeoBoundingBox2D &sourceBox, unsigned long destination, const SBGeoBoundingBox2D &destinationBox, unsigned long flags, unsigned short *weights);
    static bool BlitBlind(unsigned long source, const SBGeoBoundingBox2D &sourceBox, unsigned long destination, const SBGeoBoundingBox2D &destinationBox, unsigned long flags);
    static bool BlitFilterX(unsigned long source, const SBGeoBoundingBox2D &sourceBox, unsigned long destination, const SBGeoBoundingBox2D &destinationBox, unsigned long flags, unsigned short *weights);
    static bool BlitFilterY(unsigned long source, const SBGeoBoundingBox2D &sourceBox, unsigned long destination, const SBGeoBoundingBox2D &destinationBox, unsigned long flags, unsigned short *weights);
    static bool BlitDouble(unsigned long source, const SBGeoBoundingBox2D &sourceBox, unsigned long destination, const SBGeoBoundingBox2D &destinationBox, unsigned long flags);
    static void ChangeShadowIntoPulse(unsigned long surface, const SBGeoBoundingBox2D &box, unsigned short level);
    static unsigned long GetNumberOfInputsUTS();
    static bool FUN_005f0d20(int index, SBInputMouseState &mouse, unsigned char *keyboard);
    static void FUN_005f1a90();
    bool CleanUpInputs();
    static unsigned short GetChar();
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
    static bool ReachPosition(const SBGeoPoint2D &position);
    static SBGeoVector2D GetSize();
    static unsigned short GetHeight();
    void Emit();

    static RHUnk00564020 mlistInput;
    static SBGeoPoint2D mpointPosition;
    static SBGeoVector2D mvectorHotSpot;
    static SBGeoVector2D mvectorDisplace;
    static SBGeoBoundingBox2D mboxClipping;
    static SBGeoBoundingBox2D mboxSaved;
    static SBGeoPoint2D mpointScreenPositionSaved;

private:
    unsigned long m_10; // 0x10
    SBGeoBoundingBox2D m_14; // 0x14
    SBGeoBoundingBox2D m_28; // 0x28
    SBGeoBoundingBox2D m_3c; // 0x3c
    SBGeoBoundingBox2D m_50; // 0x50
};

#define g_inputPosition SBThreadedInput::mpointPosition
#define g_hotSpot SBThreadedInput::mvectorHotSpot

unsigned long FUN_005f0ce0();

#endif
