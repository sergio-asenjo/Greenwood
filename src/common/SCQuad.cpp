#include "SBNullstr.h"
#include "SCQuad.h"
#include "SBFile.h"
#include <string.h>

typedef int SCQuadArgSizeAssert[(sizeof(SCQuadArg) == 0xc) ? 1 : -1];
typedef int VMQuadSizeAssert[(sizeof(VMQuad) == 0xc) ? 1 : -1];

// GLOBAL: GAME 0x006c198c
FILE *g_unk0x006c198c;

// GLOBAL: GAME 0x006be404
char g_unk0x006be404[] = "+I\0-I\0*I\0/I\0+F\0-F\0*F\0/F\0"
    "\0\0\0\0"
    "<=I\0<I\0\0>=I\0>I\0\0!=I\0==I\0<=F\0<F\0\0>=F\0>F\0\0!=F\0==F";

#define SCQUAD_VALUE(argument) (((RHUnk0063a1d0 &)(argument)).FUN_0063a1d0())
#define SCQUAD_ARGUMENT(argument) ((argument).Serialize(file, writing, false))

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

// Parked: VC6 merges storage-write calls and duplicates the compact return tail.
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
            case 0:
                SCSerializeUnk00642a2f(
                    // STRING: GAME 0x006be4b8
                    "SCQuadArg::Serialize: SCQuadArg not defined.\n");
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

// FUNCTION: GAME 0x0063bbe0
int SCQuad::Serialize(FILE *file, bool writing, bool compact)
{
    int result = 0;
    int opcode;
    if (writing) {
        if (compact) {
            VMQuad quad;
            InitializeVMQuadWithSCQuad(*this, quad);
            result = SBFileUnk00643cd3(&quad.m_00, 1, 1, file);
            result += SBFileUnk00643cd3(&quad.m_04, 8, 1, file) * 8;
        } else {
            switch (m_00) {
            case 0:
                SCSerializeUnk00642a2f(
                    // STRING: GAME 0x006be728
                    "SCQuad::Flush(): Flush a Q_EMPTY(not initialized) instruction !");
                break;
            case 1:
                result = SCQuadUnk00644112(file,
                    // STRING: GAME 0x006be720
                    "\tNOP ");
                break;
            case 2:
                result = SCQuadUnk00644112(file,
                    // STRING: GAME 0x006be718
                    "\tPARAM ");
                result += SCQUAD_ARGUMENT(m_04);
                break;
            case 3:
                result = SCQuadUnk00644112(file,
                    // STRING: GAME 0x006be714
                    "\t");
                result += SCQUAD_ARGUMENT(m_04);
                result += SCQuadUnk00644112(file,
                    // STRING: GAME 0x006be700
                    ": slSizeOfVolatile ");
                result += SCQUAD_ARGUMENT(m_10);
                result += SCQuadUnk00644112(file,
                    // STRING: GAME 0x006be6e8
                    ", slSizeOfTemporary ");
                result += SCQUAD_ARGUMENT(m_1c);
                break;
            case 4: break;
            case 5: {
                result = SCQuadUnk00644112(file,
                        // STRING: GAME 0x006be6e0
                        "\tCALL ");
                if (((SCQuadUnkSymbol *)SCQUAD_VALUE(m_04))->m_3c >= 0) {
                    result += SCQUAD_ARGUMENT(m_04);
                } else {
                    char *name = *(char **)((char *)SCQUAD_VALUE(m_04) + 4);
                    if (!name) name = "";
                    SCQuadUnk00644112(g_unk0x006c198c,
                        // STRING: GAME 0x006be6c4
                        "SCQuad::Serialize:%s (%s)\n", SCQuadUnk0063c760(0xc), name);
                }
                break;
            }
            case 6:
                result = SCQuadUnk00644112(file,
                    // STRING: GAME 0x006be6b8
                    "\tRETURN ");
                break;
            case 7:
                result = SCQuadUnk00644112(file, "\tRETURN ");
                result += SCQUAD_ARGUMENT(m_04);
                break;
            case 8:
                result = SCQuadUnk00644112(file, "\t");
                result += SCQUAD_ARGUMENT(m_04);
                result += SCQuadUnk00644112(file,
                    // STRING: GAME 0x006be6a8
                    " := GETPARAM ");
                result += SCQUAD_ARGUMENT(m_10);
                break;
            case 9:
                result = SCQuadUnk00644112(file,
                    // STRING: GAME 0x006be69c
                    "\tSETPARAM ");
                result += SCQUAD_ARGUMENT(m_04);
                result += SCQuadUnk00644112(file,
                    // STRING: GAME 0x006be694
                    " := ");
                result += SCQUAD_ARGUMENT(m_10);
                break;
            case 10:
                result = SCQuadUnk00644112(file, "\t");
                result += SCQUAD_ARGUMENT(m_04);
                result += SCQuadUnk00644112(file,
                    // STRING: GAME 0x006be684
                    " := GETRETURN");
                break;
            case 0xb:
                result = SCQuadUnk00644112(file,
                    // STRING: GAME 0x006be674
                    "\tNATIVEPARAM ");
                result += SCQUAD_ARGUMENT(m_04);
                break;
            case 0xc: {
                result = SCQuadUnk00644112(file,
                    // STRING: GAME 0x006be664
                    "\tNATIVECALL ");
                if (((SCQuadUnkSymbol *)SCQUAD_VALUE(m_04))->m_3c >= 0) {
                    result += SCQUAD_ARGUMENT(m_04);
                } else {
                    char *name = *(char **)((char *)SCQUAD_VALUE(m_04) + 4);
                    if (!name) name = "";
                    SCQuadUnk00644112(g_unk0x006c198c, "SCQuad::Serialize:%s (%s)\n", SCQuadUnk0063c760(0xc), name);
                }
                break;
            }
            case 0xd:
                result = SCQuadUnk00644112(file, "\t");
                result += SCQUAD_ARGUMENT(m_04);
                result += SCQuadUnk00644112(file,
                    // STRING: GAME 0x006be64c
                    " := NATIVEGETRETURN ");
                break;
            case 0xe:
                result = SCQuadUnk00644112(file,
                    // STRING: GAME 0x006be644
                    "\tGOTO ");
                result += SCQUAD_ARGUMENT(m_04);
                break;
            case 0xf:
                result = SCQuadUnk00644112(file,
                    // STRING: GAME 0x006be63c
                    "\tIF ( ");
                result += SCQUAD_ARGUMENT(m_04);
                result += SCQuadUnk00644112(file,
                        // STRING: GAME 0x006be628
                        " != 0 ) THEN GOTO ");
                result += SCQUAD_ARGUMENT(m_10);
                break;
            case 0x10:
                result = SCQuadUnk00644112(file, "\tIF ( ");
                result += SCQUAD_ARGUMENT(m_04);
                result += SCQuadUnk00644112(file,
                        // STRING: GAME 0x006be614
                        " == 0 ) THEN GOTO ");
                result += SCQUAD_ARGUMENT(m_10);
                break;
            case 0x11:
                result = SCQuadUnk00644112(file, "\t");
                result += SCQUAD_ARGUMENT(m_04);
                result += SCQuadUnk00644112(file, " := ");
                result += SCQUAD_ARGUMENT(m_10);
                break;
            case 0x12: case 0x14:
                result = SCQuadUnk00644112(file, "\t");
                result += SCQUAD_ARGUMENT(m_04);
                result += SCQuadUnk00644112(file,
                    // STRING: GAME 0x006be60c
                    " :=F ");
                result += SCQUAD_ARGUMENT(m_10);
                break;
            case 0x13:
                result = SCQuadUnk00644112(file, "\t");
                result += SCQUAD_ARGUMENT(m_04);
                result += SCQuadUnk00644112(file,
                    // STRING: GAME 0x006be604
                    " :=I ");
                result += SCQUAD_ARGUMENT(m_10);
                break;
            case 0x15:
                result = SCQuadUnk00644112(file, "\t");
                result += SCQUAD_ARGUMENT(m_04);
                result += SCQuadUnk00644112(file,
                    // STRING: GAME 0x006be5fc
                    " :=I -");
                result += SCQUAD_ARGUMENT(m_10);
                break;
            case 0x16:
                result = SCQuadUnk00644112(file, "\t");
                result += SCQUAD_ARGUMENT(m_04);
                result += SCQuadUnk00644112(file,
                    // STRING: GAME 0x006be5f4
                    " :=F -");
                result += SCQUAD_ARGUMENT(m_10);
                break;
            case 0x17:
                result = SCQuadUnk00644112(file, "\t");
                result += SCQUAD_ARGUMENT(m_04);
                result += SCQuadUnk00644112(file,
                    // STRING: GAME 0x006be5e8
                    " := (INT) ");
                result += SCQUAD_ARGUMENT(m_10);
                break;
            case 0x18:
                result = SCQuadUnk00644112(file, "\t");
                result += SCQUAD_ARGUMENT(m_04);
                result += SCQuadUnk00644112(file,
                    // STRING: GAME 0x006be5d8
                    " := (FLOAT) ");
                result += SCQUAD_ARGUMENT(m_10);
                break;
            case 0x19: case 0x1a: case 0x1b: case 0x1c: case 0x1d: case 0x1e: case 0x1f:
                result = SCQuadUnk00644112(file, "\t");
                result += SCQUAD_ARGUMENT(m_04);
                result += SCQuadUnk00644112(file, " :=I ");
                result += SCQUAD_ARGUMENT(m_10);
                opcode = *(volatile int *)&m_00;
                result += SCQuadUnk00644112(file,
                    // STRING: GAME 0x006be5d0
                    " %s ", g_unk0x006be404 + (opcode * 3 - 0x4b));
                result += SCQUAD_ARGUMENT(m_1c);
                break;
            case 0x20: case 0x21: case 0x22: case 0x23:
                result = SCQuadUnk00644112(file, "\t");
                result += SCQUAD_ARGUMENT(m_04);
                result += SCQuadUnk00644112(file, " :=F ");
                result += SCQUAD_ARGUMENT(m_10);
                opcode = *(volatile int *)&m_00;
                result += SCQuadUnk00644112(file, " %s ", g_unk0x006be404 + (opcode * 3 - 0x4b));
                result += SCQUAD_ARGUMENT(m_1c);
                break;
            case 0x24: case 0x25: case 0x26: case 0x27: case 0x28: case 0x29:
                result = SCQuadUnk00644112(file, "\t");
                result += SCQUAD_ARGUMENT(m_04);
                result += SCQuadUnk00644112(file, " :=I ");
                result += SCQUAD_ARGUMENT(m_10);
                opcode = *(volatile int *)&m_00;
                result += SCQuadUnk00644112(file, " %s ", g_unk0x006be404 + (opcode * 4 - 0x74));
                result += SCQUAD_ARGUMENT(m_1c);
                break;
            case 0x2a: case 0x2b: case 0x2c: case 0x2d: case 0x2e: case 0x2f:
                result = SCQuadUnk00644112(file, "\t");
                result += SCQUAD_ARGUMENT(m_04);
                result += SCQuadUnk00644112(file, " :=F ");
                result += SCQUAD_ARGUMENT(m_10);
                opcode = *(volatile int *)&m_00;
                result += SCQuadUnk00644112(file, " %s ", g_unk0x006be404 + (opcode * 4 - 0x74));
                result += SCQUAD_ARGUMENT(m_1c);
                break;
            default:
                SCSerializeUnk00642a2f(
                    // STRING: GAME 0x006be5ac
                    "SCQuad::Serialize: Unknown SCQuad.\n");
            }
        }
    } else {
        SCSerializeUnk00642a2f(
            // STRING: GAME 0x006be580
            "SCQuad::Serialize: Not yet implemented !!!\n");
    }
    return result;
}

// Parked: entry load/scheduling and case-register allocation differ; budget exhausted.
// STUB: GAME 0x0063c360
void SCQuad::InitializeVMQuadWithSCQuad(SCQuad &source, VMQuad &quad)
{
    unsigned *operands = &quad.m_04;
    quad.m_00 = *(volatile unsigned *)&source.m_00;
    memset(operands, 0, 8);
    switch (m_00) {
    case 0:
        SCSerializeUnk00642a2f(
            // STRING: GAME 0x006be800
            "SCQuad::Serialize(): Serialize a Q_EMPTY(not initialized) instruction !");
        break;
    case 1: case 4: case 6: break;
    case 2: case 7: case 10: case 0xb: case 0xd:
        InitializeVMQuadSymbolWithSCQuadArg(*(unsigned short *)operands, source.m_04);
        break;
    case 3:
        *(unsigned short *)operands = SCQUAD_VALUE(source.m_10);
        *(unsigned short *)((char *)&quad + 6) = SCQUAD_VALUE(source.m_1c);
        break;
    case 5: {
        SCQuadArg &argument = source.m_04;
        if (((SCQuadUnkSymbol *)SCQUAD_VALUE(argument))->m_3c >= 0) {
            *operands = ((SCQuadUnkSymbol *)SCQUAD_VALUE(argument))->m_3c;
        } else {
            char *name = *(char **)((char *)SCQUAD_VALUE(argument) + 4);
            if (!name) name = "";
            SCQuadUnk00644112(g_unk0x006c198c,
                    // STRING: GAME 0x006be7d4
                    "InitializeVMQuadWithSCQuad(Q_CALL):%s (%s)\n", SCQuadUnk0063c760(0xc), name);
        }
        break;
    }
    case 0xc: {
        SCQuadArg &argument = source.m_04;
        if (((SCQuadUnkSymbol *)SCQUAD_VALUE(argument))->m_3c >= 0) {
            *operands = ((SCQuadUnkSymbol *)SCQUAD_VALUE(argument))->m_3c;
        } else {
            char *name = *(char **)((char *)SCQUAD_VALUE(argument) + 4);
            if (!name) name = "";
            SCQuadUnk00644112(g_unk0x006c198c,
                    // STRING: GAME 0x006be7a0
                    "InitializeVMQuadWithSCQuad(Q_NATIVECALL):%s (%s)\n", SCQuadUnk0063c760(0xc), name);
        }
        break;
    }
    case 9:
        quad.m_08 = SCQUAD_VALUE(source.m_04);
        InitializeVMQuadSymbolWithSCQuadArg(*(unsigned short *)operands, source.m_10);
        break;
    case 0xe:
        *operands = SCQUAD_VALUE(source.m_04);
        break;
    case 0xf: case 0x10:
        InitializeVMQuadSymbolWithSCQuadArg(*(unsigned short *)operands, source.m_04);
        quad.m_08 = SCQUAD_VALUE(source.m_10);
        break;
    case 8: case 0x13:
        InitializeVMQuadSymbolWithSCQuadArg(*(unsigned short *)operands, source.m_04);
        quad.m_08 = SCQUAD_VALUE(source.m_10);
        break;
    case 0x14: {
        SCQuadArg &argument = source.m_04;
        InitializeVMQuadSymbolWithSCQuadArg(*(unsigned short *)operands, argument);
        quad.m_float08 = source.m_10.GetFloat();
        break;
    }
    case 0x11: case 0x12: case 0x15: case 0x16: case 0x17: case 0x18:
        InitializeVMQuadSymbolWithSCQuadArg(*(unsigned short *)operands, source.m_04);
        InitializeVMQuadSymbolWithSCQuadArg(*(unsigned short *)((char *)&quad + 6), source.m_10);
        break;
    case 0x19: case 0x1a: case 0x1b: case 0x1c: case 0x1d: case 0x1e: case 0x1f:
    case 0x20: case 0x21: case 0x22: case 0x23: case 0x24: case 0x25: case 0x26:
    case 0x27: case 0x28: case 0x29: case 0x2a: case 0x2b: case 0x2c: case 0x2d: case 0x2e: case 0x2f:
        InitializeVMQuadSymbolWithSCQuadArg(*(unsigned short *)operands, source.m_04);
        InitializeVMQuadSymbolWithSCQuadArg(*(unsigned short *)((char *)&quad + 6), source.m_10);
        InitializeVMQuadSymbolWithSCQuadArg(*(unsigned short *)&quad.m_08, source.m_1c);
        break;
    default:
        SCSerializeUnk00642a2f(
            // STRING: GAME 0x006be768
            "SCQuad::InitializeVMQuadWithSCQuad: Unknown SCQuad.\n");
    }
}

// FUNCTION: GAME 0x0063c5e0
void SCQuad::InitializeVMQuadSymbolWithSCQuadArg(unsigned short &value, SCQuadArg &argument)
{
    RHUnk0063a1d0 &source = (RHUnk0063a1d0 &)argument;
    int offset = ((SCQuadUnkSymbol *)source.FUN_0063a1d0())->m_3c;
    value = offset;
    if (((SCQuadUnkSymbol *)source.FUN_0063a1d0())->m_38 == 2) {
    } else if (((SCQuadUnkSymbol *)source.FUN_0063a1d0())->m_38 == 3) {
        value |= 0x4000;
    } else {
        unsigned char storage = ((SCQuadUnkSymbol *)source.FUN_0063a1d0())->m_38;
        if (storage == 4)
            goto sharedSymbolStorage;
        if (storage == 5) {
sharedSymbolStorage:
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
}

void EmitSCQuad(SCQuad *quad, SCQuadArg *argument, unsigned short &value)
{
    quad->Serialize(0, false, false);
    VMQuad vm;
    quad->InitializeVMQuadWithSCQuad(*quad, vm);
    quad->InitializeVMQuadSymbolWithSCQuadArg(value, *argument);
}
