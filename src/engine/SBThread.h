#ifndef SBTHREAD_H
#define SBTHREAD_H

#include <windows.h>

// VTABLE: GAME 0x0067ae74
// SIZE 0x10
class SBThread
{
public:
    SBThread();
    virtual ~SBThread(); // vtable+0x00

    unsigned long m_threadId; // 0x04
    HANDLE m_thread; // 0x08
    bool m_running; // 0x0c
    bool m_active; // 0x0d
};

#endif
