// Anonymous cluster at 0x0056de50.
// No __FILE__ or oracle evidence: class and method identity are unproven.
// Member offsets are exact from Game.exe.

#include "RHMotionAreaList.h"
#include "Decomp.h"

class RHUnk0056de50
{
public:
    RHUnk0056de50();
    ~RHUnk0056de50();
    int m_0;
    int m_4;
    int m_8;
    short m_c;
    short m_e;
    int m_10;
    RHMotionAreaList<void *> m_14;
    int m_38;
    char m_3c;
    char m_3d[3];
};

DECOMP_SIZE_ASSERT(RHUnk0056de50, 0x40)

// FUNCTION: GAME 0x0056de50
RHUnk0056de50::RHUnk0056de50()
{
    m_10 = 0;
    m_0 = 0;
    m_4 = 0;
    m_8 = 0;
    m_c = 0;
    m_38 = 0;
    m_3c = 0;
}

// FUNCTION: GAME 0x0056de90
RHUnk0056de50::~RHUnk0056de50()
{
}
