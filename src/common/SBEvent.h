#ifndef SBEVENT_H
#define SBEVENT_H

#include <string>
#include <windows.h>

// VTABLE: GAME 0x0067ae30
// SIZE 0x08
class SBEvent
{
public:
    SBEvent(const std::string &name);
    virtual ~SBEvent(); // vtable+0x00
    bool WaitForEvent(long timeout);
    bool TriggerEvent();

    HANDLE m_event; // 0x04
};

#endif
