#include "SBNullstr.h"
#include "SBEvent.h"

void FUN_005f8030(int, const char *, int, const char *, ...);

typedef int SBEventSizeAssert[sizeof(SBEvent) == 8 ? 1 : -1];

// FUNCTION: GAME 0x0061e4f0
SBEvent::SBEvent(const std::string &name)
{
    m_event = CreateEventA(0, FALSE, FALSE, name.c_str());
    if (!m_event) {
        FUN_005f8030(0,
            // STRING: GAME 0x006bb814
            "P:\\Robin Hood\\SBLibNG\\SBEvent.cpp", 0x18,
            // STRING: GAME 0x006bb838
            "Unable to create windows event");
    }
}

// SYNTHETIC: GAME 0x0061e540
// SBEvent::`scalar deleting destructor'

// FUNCTION: GAME 0x0061e560
SBEvent::~SBEvent()
{
    if (m_event)
        CloseHandle(m_event);
}

// FUNCTION: GAME 0x0061e580
bool SBEvent::WaitForEvent(long timeout)
{
    if (!m_event)
        return false;
    if (WaitForSingleObject(m_event, timeout) == WAIT_TIMEOUT)
        return false;
    return true;
}

// FUNCTION: GAME 0x0061e5b0
bool SBEvent::TriggerEvent()
{
    if (m_event)
        return SetEvent(m_event) > 0;
    return false;
}

void EmitSBEvent(SBEvent *event, const std::string &name)
{
    new SBEvent(name);
    event->WaitForEvent(0);
    event->TriggerEvent();
}
