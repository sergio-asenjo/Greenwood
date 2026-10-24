
extern "C" int rand();

// FUNCTION: GAME 0x0048f950
int FUN_0048f950()
{
    return (int)((rand() * 125) * 0.00003051850944757461548f + 50.0f);
}

void EmitFUN_0048f950()
{
    FUN_0048f950();
}
