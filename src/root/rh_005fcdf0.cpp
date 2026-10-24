// GLOBAL: GAME 0x0067a838
double g_unk0x0067a838;

// GLOBAL: GAME 0x00677da0
double g_unk0x00677da0;


// FUNCTION: GAME 0x005fcdf0
double FUN_005fcdf0(unsigned short value)
{
    double scaled = (double)(unsigned char)value * g_unk0x0067a838;
    return scaled * 6.2831854820251465 + g_unk0x00677da0;
}
