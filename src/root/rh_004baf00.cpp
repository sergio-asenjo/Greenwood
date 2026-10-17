// Anonymous cluster at 0x004baf0x.
// No __FILE__ or oracle evidence: class and method identity are unproven.
// Case bodies and the jump-table order are exact from Game.exe.

// FUNCTION: GAME 0x004baf00
int FUN_004baf00(volatile int type)
{
    switch (type)
    {
    case 4:
        return 1;
    case 7:
        return 0x40;
    case 8:
        return 0x20;
    case 10:
        return 0x80;
    case 9:
        return 0x10;
    }
    return 0;
}

void EmitFUN_004baf00(int type)
{
    FUN_004baf00(type);
}
