#include "SCQuad.h"
#include "SBFile.h"

// FUNCTION: GAME 0x0063b9a0
unsigned char SCQuadArg::GetType()
{
    return m_00;
}

// FUNCTION: GAME 0x0063b9b0
float SCQuadArg::GetFloat()
{
    return m_04;
}

// FUNCTION: GAME 0x0063b9c0
signed char SCQuadArg::GetReference()
{
    return m_08;
}

// STUB: GAME 0x0063b9d0
int SCQuadArg::Serialize(FILE *file, bool writing, bool compact)
{
    int result = 0;
    if (writing) {
        if (!compact) {
            RHUnk0063a1d0 &source = (RHUnk0063a1d0 &)*this;
            if (GetType() == 1 && ((SCQuadUnkSymbol *)source.FUN_0063a1d0())->m_3c >= 0 &&
                ((SCQuadUnkSymbol *)source.FUN_0063a1d0())->m_40 != 1) {
                if (((SCQuadUnkSymbol *)source.FUN_0063a1d0())->m_38 == 2) {
                    result = SBFileUnk00643cd3(
                        // STRING: GAME 0x006be57c
                        "G", 1, 1, file);
                } else if (((SCQuadUnkSymbol *)source.FUN_0063a1d0())->m_38 == 3) {
                    result = SBFileUnk00643cd3(
                        // STRING: GAME 0x006be578
                        "H", 1, 1, file);
                } else {
                    unsigned char storage = ((SCQuadUnkSymbol *)source.FUN_0063a1d0())->m_38;
                    if (storage == 4 || storage == 5) {
                        result = SBFileUnk00643cd3(
                            // STRING: GAME 0x006be574
                            "S", 1, 1, file);
                    } else if (((SCQuadUnkSymbol *)source.FUN_0063a1d0())->m_38 == 6) {
                        result = SBFileUnk00643cd3(
                            // STRING: GAME 0x006be570
                            "T", 1, 1, file);
                    } else {
                        SCSerializeUnk00642a2f(
                            // STRING: GAME 0x006be53c
                            "SCQuadArg::Serialize: Unknown storage for symbol.\n");
                    }
                }
                switch (GetReference()) {
                case -1:
                    result += SCQuadUnk00644112(file,
                        // STRING: GAME 0x006be4f0
                        "*@");
                    break;
                case 0:
                    result += SCQuadUnk00644112(file,
                        // STRING: GAME 0x006be4f4
                        "@");
                    break;
                case 1:
                    result += SCQuadUnk00644112(file,
                        // STRING: GAME 0x006be4f8
                        "&@");
                    break;
                default:
                    SCSerializeUnk00642a2f(
                        // STRING: GAME 0x006be4fc
                        "SCQuadArg::Serialize: Case not expected (for GetReference())\n");
                    break;
                }
            }
            switch (GetType()) {
            case 0:
                SCSerializeUnk00642a2f(
                    // STRING: GAME 0x006be4b8
                    "SCQuadArg::Serialize: SCQuadArg not defined.\n");
                break;
            case 1: {
                char *name = *(char **)((char *)source.FUN_0063a1d0() + 4);
                if (!name)
                    name = "";
                result += SCQuadUnk00644112(file,
                    // STRING: GAME 0x006be4ec
                    "%s", name);
                break;
            }
            case 2:
                result += SCQuadUnk00644112(file,
                    // STRING: GAME 0x006ae03c
                    "%d", (int)source.FUN_0063a1d0());
                break;
            case 3:
                result += SCQuadUnk00644112(file,
                    // STRING: GAME 0x006be4e8
                    "%f", GetFloat());
                break;
            default:
                SCSerializeUnk00642a2f(
                    // STRING: GAME 0x006be480
                    "SCQuadArg::Serialize: Case not expected (for GetType()\n");
                break;
            }
        }
    } else {
        SCSerializeUnk00642a2f(
            // STRING: GAME 0x006be450
            "SCQuadArg::Serialize: not yet implemented !!!\n");
    }
    return result;
}

void EmitSCQuadArg(SCQuadArg *argument)
{
    argument->GetType();
    argument->GetFloat();
    argument->GetReference();
    argument->Serialize(0, false, false);
}

// STUB: GAME 0x0063c5e0
void SCQuad::InitializeVMQuadSymbolWithSCQuadArg(unsigned short &value, SCQuadArg &argument)
{
    RHUnk0063a1d0 &source = (RHUnk0063a1d0 &)argument;
    int offset = ((SCQuadUnkSymbol *)source.FUN_0063a1d0())->m_3c;
    value = offset;
    if (((SCQuadUnkSymbol *)source.FUN_0063a1d0())->m_38 == 2)
        return;
    if (((SCQuadUnkSymbol *)source.FUN_0063a1d0())->m_38 == 3) {
        value |= 0x4000;
        return;
    }
    unsigned char storage = ((SCQuadUnkSymbol *)source.FUN_0063a1d0())->m_38;
    if (storage == 4 || storage == 5) {
        value |= 0x8000;
        return;
    }
    if (((SCQuadUnkSymbol *)source.FUN_0063a1d0())->m_38 == 6) {
        value |= 0xc000;
    } else {
        SCSerializeUnk00642a2f(
            // STRING: GAME 0x006be848
            "SCQuad::InitializeVMQuadSymbolWithSCQuadArg: Unknown storage for symbol.\n");
    }
}

void EmitSCQuad(SCQuad *quad, SCQuadArg *argument, unsigned short &value)
{
    quad->InitializeVMQuadSymbolWithSCQuadArg(value, *argument);
}
