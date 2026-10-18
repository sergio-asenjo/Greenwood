extern float g_unk0x00677488;

class RHUnk005fc780
{
public:
    float FUN_005fc780(float divisor);

    float m_0; // 0x00
    float m_4; // 0x04
};

// FUNCTION: GAME 0x005fc780
float RHUnk005fc780::FUN_005fc780(float divisor)
{
    float b = m_4 / divisor;
    if (m_0 > g_unk0x00677488)
    {
        if (b > g_unk0x00677488)
            return m_0 + b;
        return m_0 - b;
    }
    if (b > g_unk0x00677488)
        return b - m_0;
    return -m_0 - b;
}

void EmitRHUnk005fc780(RHUnk005fc780 *self)
{
    float (RHUnk005fc780::*f)(float) = &RHUnk005fc780::FUN_005fc780;
    (self->*f)(1.0f);
}
