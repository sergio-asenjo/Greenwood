#include "RHConsole.h"

// FUNCTION: GAME 0x0045ad00
RHConsole::RHConsole()
{
    m_8a = 1;
    m_historyIndex = 0;
    m_position = 0;
    m_completionDirty = true;
    m_completionIndex = 0;
    m_04[0] = 0;
    m_close = 0;
    for (unsigned i = 0; i < 10; ++i)
        m_history[i][0] = 0;

    // STRING: GAME 0x006ac8cc
    FUN_0045b620("AI", &RHConsole::FUN_0045e620,
        // STRING: GAME 0x006ac8d0
        "Display AI information.");
    // STRING: GAME 0x006ac8a8
    FUN_0045b620("ALARM", &RHConsole::FUN_0045eb40,
        // STRING: GAME 0x006ac8b0
        "Reinforcement arriving...");
    // STRING: GAME 0x006ac85c
    FUN_0045b620("AMOR", &RHConsole::FUN_0045ee70,
        // STRING: GAME 0x006ac864
        "Increase the number of available arrows for all the selected PCs.");
    // STRING: GAME 0x006ac834
    FUN_0045b620("AMULETS", &RHConsole::FUN_0045eaa0,
        // STRING: GAME 0x006ac83c
        "Add amulets to the campaign.");
    // STRING: GAME 0x006ac820
    FUN_0045b620("ASSERTFALSE", &RHConsole::CheatAssertFalse,
        // STRING: GAME 0x006ac82c
        "Ok !");
    // STRING: GAME 0x006ac7f4
    FUN_0045b620("BABYLON", &RHConsole::FUN_0045e6a0,
        // STRING: GAME 0x006ac7fc
        "Display all NPC remarks on screen.");
    // STRING: GAME 0x006ac7cc
    FUN_0045b620("BIG BROTHER", &RHConsole::FUN_0045e530,
        // STRING: GAME 0x006ac7d8
        "Display some actor infos.");
    // STRING: GAME 0x006ac7ac
    FUN_0045b620("BUD SPENCER", &RHConsole::FUN_0045e2e0,
        // STRING: GAME 0x006ac7b8
        "Stun all oponents.");
    // STRING: GAME 0x006ac790
    FUN_0045b620("CALL", &RHConsole::FUN_0045f590,
        // STRING: GAME 0x006ac798
        "Call a PC's method");
    // STRING: GAME 0x006ac770
    FUN_0045b620("COMA", &RHConsole::FUN_0045e8d0,
        // STRING: GAME 0x006ac778
        "Put a PC in the coma");
    // STRING: GAME 0x006ac748
    FUN_0045b620("COMPANIES", &RHConsole::CheatCompanyNrDisplay,
        // STRING: GAME 0x006ac754
        "Display the company numbers");
    // STRING: GAME 0x006ac714
    FUN_0045b620("DIES IRAE", &RHConsole::FUN_0045db20,
        // STRING: GAME 0x006ac720
        "Divine intervention against enemies.");
    // STRING: GAME 0x006ac6f0
    FUN_0045b620("EINSTEIN", &RHConsole::FUN_0045e290,
        // STRING: GAME 0x006ac6fc
        "Show all 3D-obstacles !");
    // STRING: GAME 0x006ac67c
    FUN_0045b620("ELEVATION", &RHConsole::FUN_0045cc60,
        // STRING: GAME 0x006ac688
        "Display bonds (yellow, red when crossed), character elevation (blue) and character movement (white).");
    // STRING: GAME 0x006ac650
    FUN_0045b620("EULER", &RHConsole::FUN_0045e450,
        // STRING: GAME 0x006ac658
        "Show the graph of the pathfinder.");
    // STRING: GAME 0x006ac640
    FUN_0045b620("EZB", &RHConsole::FUN_0045f0c0,
        // STRING: GAME 0x006ac644
        "Gives money");
    // STRING: GAME 0x006ac624
    FUN_0045b620("FPS", &RHConsole::FUN_0045e670,
        // STRING: GAME 0x006ac628
        "Display the FPS rate");
    // STRING: GAME 0x006ac5f4
    FUN_0045b620("FORGET", &RHConsole::FUN_0045f4e0,
        // STRING: GAME 0x006ac5fc
        "Check the current state of the memory");
    // STRING: GAME 0x006ac5c4
    FUN_0045b620("FREEZE", &RHConsole::FUN_0045dc80,
        // STRING: GAME 0x006ac5cc
        "Freeze / unfrost all NPCs in the level.");
    // STRING: GAME 0x006ac58c
    FUN_0045b620("FULLHOUSE", &RHConsole::FUN_0045f050,
        // STRING: GAME 0x006ac598
        "Give all PCs ammunition for all actions.");
    // STRING: GAME 0x006ac550
    FUN_0045b620("GOLDENEYE", &RHConsole::FUN_0045cc20,
        // STRING: GAME 0x006ac55c
        "Make all PCs invisible for other characters.");
    FUN_0045b620("HADES", &RHConsole::FUN_0045e7e0,
        // STRING: GAME 0x006ac53c
        "Kill selected NPC");
    // STRING: GAME 0x006ac518
    FUN_0045b620("HELP", &RHConsole::FUN_0045ccb0,
        // STRING: GAME 0x006ac520
        "Display this help.");
    // STRING: GAME 0x006ac4ec
    FUN_0045b620("HIGHLANDER", &RHConsole::FUN_0045d840,
        // STRING: GAME 0x006ac4f8
        "All PCs become invulnerable.");
    // STRING: GAME 0x006ac4b8
    FUN_0045b620("HIGHLANDER2", &RHConsole::FUN_0045d8b0,
        // STRING: GAME 0x006ac4c4
        "All adversaries become invulnerable.");
    // STRING: GAME 0x006ac488
    FUN_0045b620("HONOLULU", &RHConsole::FUN_0045d920,
        // STRING: GAME 0x006ac494
        "Beam the selected NPC to Honolulu");
    // STRING: GAME 0x006ac460
    FUN_0045b620("KOLKOZ", &RHConsole::FUN_004600b0,
        // STRING: GAME 0x006ac468
        "Add a new peasant to the gang.");
    // STRING: GAME 0x006ac420
    FUN_0045b620("LAST MAN STANDING", &RHConsole::FUN_0045da50,
        // STRING: GAME 0x006ac434
        "Beam all but the selected NPC to Honolulu");
    // STRING: GAME 0x006ac3ec
    FUN_0045b620("LEVEL TEXT", &RHConsole::FUN_00460140,
        // STRING: GAME 0x006ac3f8
        "Display all texts for the current level");
    // STRING: GAME 0x006ac3cc
    FUN_0045b620("LOOSE", &RHConsole::FUN_0045d5c0,
        // STRING: GAME 0x006ac3d4
        "Loose this mission !");
    // STRING: GAME 0x006ac3a0
    FUN_0045b620("MISTER SANDMAN", &RHConsole::FUN_0045dd90,
        // STRING: GAME 0x006ac3b0
        "The PCs make a little nap.");
    FUN_0045b620("MORPHEUS", &RHConsole::FUN_0045e6f0,
        // STRING: GAME 0x006ac388
        "Knock out selected NPC");
    // STRING: GAME 0x006ac350
    FUN_0045b620("MOTION", &RHConsole::FUN_0045e4b0,
        // STRING: GAME 0x006ac358
        "Show all motion obstacles & doors.");
    // STRING: GAME 0x006ac31c
    FUN_0045b620("NOISE", &RHConsole::FUN_0045db80,
        // STRING: GAME 0x006ac324
        "Display ranges of walk noise of the PCs.");
    // STRING: GAME 0x006ac2f4
    FUN_0045b620("NUKE", &RHConsole::FUN_0045d650,
        // STRING: GAME 0x006ac2fc
        "Kill all opponent in the level.");
    // STRING: GAME 0x006ac2b8
    FUN_0045b620("PAMELA ANDERSON", &RHConsole::FUN_0045dce0,
        // STRING: GAME 0x006ac2c8
        "Make the soldiers stupid in close combat.");
    // STRING: GAME 0x006ac28c
    FUN_0045b620("PROJECTION", &RHConsole::FUN_0045e400,
        // STRING: GAME 0x006ac298
        "Show all 3D-projection areas.");
    // STRING: GAME 0x006ac26c
    FUN_0045b620("RAILROAD", &RHConsole::FUN_0045e240,
        // STRING: GAME 0x006ac278
        "Display railroads.");
    // STRING: GAME 0x006ac244
    FUN_0045b620("ROTER ALARM", &RHConsole::FUN_0045dd40,
        // STRING: GAME 0x006ac250
        "Alert all NPCs in the level");
    // STRING: GAME 0x006ac210
    FUN_0045b620("SAN PETRUS", &RHConsole::FUN_0045eb50,
        // STRING: GAME 0x006ac21c
        "Make all selected PC go to paradise.");
    FUN_0045b620("SHADOW", &RHConsole::FUN_0045d780,
        // STRING: GAME 0x006ac1ec
        "Display the free shadow polygon.");
    // STRING: GAME 0x006ac1b8
    FUN_0045b620("SPHERE", &RHConsole::FUN_0045f310,
        // STRING: GAME 0x006ac1c0
        "Display the shadow polygon sphere.");
    // STRING: GAME 0x006ac168
    FUN_0045b620("STATUS FRAMECACHE", &RHConsole::FUN_0045df30,
        // STRING: GAME 0x006ac17c
        "Get information about the current sprite caching system.");
    // STRING: GAME 0x006ac12c
    FUN_0045b620("STATUS HARDWARE", &RHConsole::FUN_0045df30,
        // STRING: GAME 0x006ac13c
        "Get information about the hardware used.");
    // STRING: GAME 0x006ac0f4
    FUN_0045b620("STATUS SHADOW", &RHConsole::FUN_0045df30,
        // STRING: GAME 0x006ac104
        "Get Information about the sprite cache.");
    // STRING: GAME 0x006ac0c0
    FUN_0045b620("STATUS PC", &RHConsole::FUN_0045f500,
        // STRING: GAME 0x006ac0cc
        "Display the current status of all PC");
    // STRING: GAME 0x006ac0a0
    FUN_0045b620("UBIQUITY", &RHConsole::FUN_004600e0,
        // STRING: GAME 0x006ac0ac
        "Unblip all actors.");
    // STRING: GAME 0x006ac05c
    FUN_0045b620("WAKEUP", &RHConsole::FUN_0045d7d0,
        // STRING: GAME 0x006ac064
        "When the currently selected NPC is sleeping, he wakes up.");
    // STRING: GAME 0x006ac008
    FUN_0045b620("WASP MASTER", &RHConsole::FUN_0045ec90,
        // STRING: GAME 0x006ac014
        "Increases the number of available wasp nets for all the selected PCs.");
    // STRING: GAME 0x006abff0
    FUN_0045b620("WIN", &RHConsole::FUN_0045cda0,
        // STRING: GAME 0x006abff4
        "Win this mission !");
    // STRING: GAME 0x006abfd8
    FUN_0045b620("WAPPEN", &RHConsole::FUN_0045f2a0,
        // STRING: GAME 0x006abfe0
        "Give blazons");
    // STRING: GAME 0x006abfc0
    FUN_0045b620("LUKAS", &RHConsole::FUN_0045f330,
        // STRING: GAME 0x006abfc8
        "Knock out a PC.");
    // STRING: GAME 0x006abf98
    FUN_0045b620("ANIM", &RHConsole::FUN_00460350,
        // STRING: GAME 0x006abfa0
        "Show all animation polylines.");
    // STRING: GAME 0x006abf68
    FUN_0045b620("SARKOZY", &RHConsole::FUN_00460370,
        // STRING: GAME 0x006abf70
        "Securization of all memory allocation !");
    // STRING: GAME 0x006abf40
    FUN_0045b620("SEEKANDDESTROY", &RHConsole::FUN_0045d5f0,
        // STRING: GAME 0x006abf50
        "Display all seek points");
    // STRING: GAME 0x006abf18
    FUN_0045b620("REPORT", &RHConsole::FUN_004603b0,
        // STRING: GAME 0x006abf20
        "Complete campaign state report");
    // STRING: GAME 0x006abefc
    FUN_0045b620("LIGHT", &RHConsole::FUN_004603e0,
        // STRING: GAME 0x006abf04
        "Display light zones");
    // STRING: GAME 0x006abee0
    FUN_0045b620("PCSIGHT", &RHConsole::FUN_00460410,
        // STRING: GAME 0x006abee8
        "Enable PC view cone");
    // STRING: GAME 0x006abea8
    FUN_0045b620("CAMPAIGN", &RHConsole::FUN_00460460,
        // STRING: GAME 0x006abeb4
        "Load campaign values (CAMPAIGN FILENAME)");
    // STRING: GAME 0x006abe84
    FUN_0045b620("I AM THE WINNER", &RHConsole::FUN_0045d580,
        // STRING: GAME 0x006abe94
        "Win the campaign !");
    // STRING: GAME 0x006abe60
    FUN_0045b620("CESTLAZONE", &RHConsole::FUN_0045dc20,
        // STRING: GAME 0x006abe6c
        "Display script zones.");
    // STRING: GAME 0x006abe28
    FUN_0045b620("OPTIMIZE", &RHConsole::FUN_0045de60,
        // STRING: GAME 0x006abe34
        "Try to optimize the custom memory manager.");
    // STRING: GAME 0x006abdf8
    FUN_0045b620("CHROMA", &RHConsole::FUN_00460620,
        // STRING: GAME 0x006abe00
        "Change the color of one PC on the fly.");
    // STRING: GAME 0x006abdec
    FUN_0045b900("GOODLUCK", &RHConsole::FUN_0045eaa0, "");
    FUN_0045b900("EINSTEIN", &RHConsole::FUN_0045e290, "");
    // STRING: GAME 0x006abde4
    FUN_0045b900("CASH", &RHConsole::FUN_0045f0c0, "");
    // STRING: GAME 0x006abdd8
    FUN_0045b900("IMMUNITY", &RHConsole::FUN_0045d840, "");
    // STRING: GAME 0x006abdcc
    FUN_0045b900("MERRYMAN", &RHConsole::FUN_004600b0, "");
    // STRING: GAME 0x006abdc8
    FUN_0045b900("PAM", &RHConsole::FUN_0045dce0, "");
    // STRING: GAME 0x006abdc0
    FUN_0045b900("UNBLIP", &RHConsole::FUN_004600e0, "");
    // STRING: GAME 0x006abdb8
    FUN_0045b900("WINNER", &RHConsole::FUN_0045cda0, "");
    // STRING: GAME 0x006abdb0
    FUN_0045b900("BINGO", &RHConsole::FUN_0045f050, "");
    m_5b6 = 1;
}

int FUN_0064324d(const char *, const char *, ...)
{
    return 0;
}
