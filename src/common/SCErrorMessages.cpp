// GLOBAL: GAME 0x006be894
const char *g_unk0x006be894[31] = {
    // STRING: GAME 0x006bee94
    "E01:Syntax error",
    // STRING: GAME 0x006bee74
    "E02:Variable already defined",
    // STRING: GAME 0x006bee54
    "E03:Function already defined",
    // STRING: GAME 0x006bee34
    "W04:Function already declared",
    // STRING: GAME 0x006bee18
    "E05:Event already defined",
    // STRING: GAME 0x006bedfc
    "W06:Event already declared",
    // STRING: GAME 0x006bede4
    "E07:Symbol not defined",
    // STRING: GAME 0x006bedcc
    "E08:Incompatibles types",
    // STRING: GAME 0x006beda8
    "E09:Type of expression not expected",
    // STRING: GAME 0x006bed84
    "E10:Instruction RETURN is required",
    // STRING: GAME 0x006bed64
    "E11:Wrong type for return value",
    // STRING: GAME 0x006bed38
    "W12:Instruction RETURN (value) is required",
    // STRING: GAME 0x006bed20
    "E13:Method not defined",
    // STRING: GAME 0x006bed08
    "E14:Method not declared",
    // STRING: GAME 0x006bece8
    "E15:Wrong number of parameters",
    // STRING: GAME 0x006becc4
    "E16:Type of one parameter is wrong",
    // STRING: GAME 0x006beca0
    "W17:Native type already declared",
    // STRING: GAME 0x006bec78
    "W18:Native function already declared",
    // STRING: GAME 0x006bec60
    "W19:Unknown native type",
    // STRING: GAME 0x006bec48
    "E20:Uncallable symbol",
    // STRING: GAME 0x006bec2c
    "E21:Symbol already defined",
    // STRING: GAME 0x006bec10
    "E22:Class already defined",
    // STRING: GAME 0x006bebf8
    "E23:String without end",
    // STRING: GAME 0x006beb98
    "W24:Visibility conflict between two variables(They have the same name, one of them is hidden.)",
    // STRING: GAME 0x006beb54
    "E25:Unable to recover from previous error(s); stopping compilation",
    // STRING: GAME 0x006beb28
    "E26:Declaration and definition dont match",
    // STRING: GAME 0x006beb08
    "E27:Symbol is not a variable.",
    // STRING: GAME 0x006beaf4
    "E28:Invalid break",
    // STRING: GAME 0x006beadc
    "E29:Invalid continue",
    // STRING: GAME 0x006beaac
    "E30:Case expression must be constant integer",
    // STRING: GAME 0x006bea84
    "E31:Switch expression must be integer"
};

// GLOBAL: GAME 0x006bea20
unsigned char g_unk0x006bea20[31] = {
    0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 1, 1, 0, 1, 0, 0, 2, 0, 0, 0, 0, 0, 0, 0
};

// GLOBAL: GAME 0x006c1994
int g_unk0x006c1994;

// FUNCTION: GAME 0x0063c760
const char *SCQuadUnk0063c760(int index)
{
    if (g_unk0x006c1994 >= g_unk0x006bea20[index])
        return g_unk0x006be894[index];
    return 0;
}
