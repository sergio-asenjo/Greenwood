extern float g_unk0x00677f7c;
extern float g_unk0x00677484;

extern "C" int rand();

// FUNCTION: GAME 0x0048f950
int FUN_0048f950()
{
    return (int)((rand() * 125) * g_unk0x00677f7c + g_unk0x00677484);
}

void EmitFUN_0048f950()
{
    FUN_0048f950();
}
