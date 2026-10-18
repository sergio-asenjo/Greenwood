// Anonymous function at 0x004646c0.

class RHUnk004646c0Dispatch
{
public:
    virtual void v0() = 0;
    virtual void v1() = 0;
    virtual void v2() = 0;
    virtual void v3(int first, int second) = 0;
};

class RHUnk004646c0
{
public:
    void FUN_004646c0();
    char m_00[0x130];
    RHUnk004646c0Dispatch *m_130;
    char m_134[0x15];
    char m_149;
};

// FUNCTION: GAME 0x004646c0
void RHUnk004646c0::FUN_004646c0()
{
    m_149 = 1;
    if (m_130)
        m_130->v3(6, 1);
}
