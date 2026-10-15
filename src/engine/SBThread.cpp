#include "SBThread.h"
#include "Decomp.h"

DECOMP_SIZE_ASSERT(SBThread, 0x10)

// FUNCTION: GAME 0x006252c0
SBThread::SBThread()
{
    m_running = false;
    m_active = false;
}

// SYNTHETIC: GAME 0x006252e0
// SBThread::`scalar deleting destructor'

// FUNCTION: GAME 0x00625300
SBThread::~SBThread()
{
    if (m_active == true)
        CloseHandle(m_thread);
}
