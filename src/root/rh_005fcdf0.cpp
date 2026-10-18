// GLOBAL: GAME 0x0067a838
double g_unk0x0067a838;

// GLOBAL: GAME 0x00677da0
double g_unk0x00677da0;

extern double g_swordFullTurn;

// FUNCTION: GAME 0x005fcdf0
double FUN_005fcdf0(unsigned char value)
{
    double scaled = (double)value * g_unk0x0067a838;
    return scaled * g_swordFullTurn + g_unk0x00677da0;
}
