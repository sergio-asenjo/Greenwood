extern "C" int rand(void);

namespace VMCoreCustomDependencies
{
    void FUN_00577090(int, int) {}
    int FUN_00579bd0(int) { return 0; }
    int FUN_00579c90(int) { return 0; }
    int FUN_00579d00(int) { return 0; }
    int FUN_00579d70(int) { return 0; }
    void FUN_005714a0(int) {}
    bool FUN_005714b0(bool) { return false; }
    bool FUN_00572a20(int) { return false; }
    bool FUN_00575350(int) { return false; }
    bool FUN_00573d10(int, int, int, int) { return false; }
    bool Call006390a0(int) { return false; }
    // FUNCTION: GAME 0x00577cf0
    bool FUN_00577cf0(int object, int value)
    {
        if (!value)
            return (*(unsigned *)((char *)*(void **)((char *)*(void **)((char *)object + 0x50) + 0xe0) + 0x30) >> 13) & 1;
        return *(void **)((char *)*(void **)((char *)object + 0x50) + 0xe0) == (void *)value;
    }
    void FUN_00578830(bool) {}
    bool FUN_00578690(int, int, int) { return false; }
    bool FUN_00570e30(int) { return false; }
    bool FUN_00570e50(int) { return false; }
    void Call00578c50(int) {}
    // FUNCTION: GAME 0x00578680
    int FUN_00578680(int count) { return rand() % count; }
    int FUN_005791f0(int) { return 0; }
    void FUN_00579000(int, int) {}
    void FUN_005786f0(int, int, bool) {}
    void FUN_005799d0(int, int, int) {}
    void FUN_00579a00(int, int) {}
    int FUN_0057a950(int) { return 0; }
    void FUN_0057ae60(int) {}
    void FUN_00577df0(bool) {}
    void FUN_0057ae40(int) {}
    bool FUN_00571e30(int) { return false; }
    void FUN_0057b2b0(int, int, int) {}
    bool FUN_0057b3d0(int) { return false; }
    void FUN_0057bff0(int) {}
}
