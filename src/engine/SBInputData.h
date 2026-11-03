#ifndef SB_INPUT_DATA_H
#define SB_INPUT_DATA_H

#include "SBInput.h"
#include "Decomp.h"

struct SBInputObjectFormat
{
    const SBInputDeviceGuid *guid;
    unsigned long offset;
    unsigned long type;
    unsigned long flags;
};

struct SBInputDataFormat
{
    unsigned long size;
    unsigned long objectSize;
    unsigned long flags;
    unsigned long dataSize;
    unsigned long objectCount;
    const SBInputObjectFormat *objects;
};

// GLOBAL: GAME 0x0067a6d8
const SBInputDeviceGuid g_inputPovGuid = {{0xa36d02f2, 0x11cfc9f3, 0x4544c7bf, 0x00005453}};
// GLOBAL: GAME 0x0067a6f8
const SBInputDeviceGuid g_inputSliderGuid = {{0xa36d02e4, 0x11cfc9f3, 0x4544c7bf, 0x00005453}};
// GLOBAL: GAME 0x0067a708
const SBInputDeviceGuid g_inputRzAxisGuid = {{0xa36d02e3, 0x11cfc9f3, 0x4544c7bf, 0x00005453}};
// GLOBAL: GAME 0x0067a718
const SBInputDeviceGuid g_inputRyAxisGuid = {{0xa36d02f5, 0x11cfc9f3, 0x4544c7bf, 0x00005453}};
// GLOBAL: GAME 0x0067a728
const SBInputDeviceGuid g_inputRxAxisGuid = {{0xa36d02f4, 0x11cfc9f3, 0x4544c7bf, 0x00005453}};
// GLOBAL: GAME 0x0067a738
const SBInputDeviceGuid g_inputZAxisGuid = {{0xa36d02e2, 0x11cfc9f3, 0x4544c7bf, 0x00005453}};
// GLOBAL: GAME 0x0067a748
const SBInputDeviceGuid g_inputYAxisGuid = {{0xa36d02e1, 0x11cfc9f3, 0x4544c7bf, 0x00005453}};
// GLOBAL: GAME 0x0067a758
const SBInputDeviceGuid g_inputXAxisGuid = {{0xa36d02e0, 0x11cfc9f3, 0x4544c7bf, 0x00005453}};

// GLOBAL: GAME 0x00650d80
const SBInputObjectFormat g_inputJoystickObjects[44] = {
    {&g_inputXAxisGuid, 0, 0x80ffff03, 0x100},
    {&g_inputYAxisGuid, 4, 0x80ffff03, 0x100},
    {&g_inputZAxisGuid, 8, 0x80ffff03, 0x100},
    {&g_inputRxAxisGuid, 12, 0x80ffff03, 0x100},
    {&g_inputRyAxisGuid, 16, 0x80ffff03, 0x100},
    {&g_inputRzAxisGuid, 20, 0x80ffff03, 0x100},
    {&g_inputSliderGuid, 24, 0x80ffff03, 0x100},
    {&g_inputSliderGuid, 28, 0x80ffff03, 0x100},
    {&g_inputPovGuid, 32, 0x80ffff10, 0},
    {&g_inputPovGuid, 36, 0x80ffff10, 0},
    {&g_inputPovGuid, 40, 0x80ffff10, 0},
    {&g_inputPovGuid, 44, 0x80ffff10, 0},
    {0, 48, 0x80ffff0c, 0},
    {0, 49, 0x80ffff0c, 0},
    {0, 50, 0x80ffff0c, 0},
    {0, 51, 0x80ffff0c, 0},
    {0, 52, 0x80ffff0c, 0},
    {0, 53, 0x80ffff0c, 0},
    {0, 54, 0x80ffff0c, 0},
    {0, 55, 0x80ffff0c, 0},
    {0, 56, 0x80ffff0c, 0},
    {0, 57, 0x80ffff0c, 0},
    {0, 58, 0x80ffff0c, 0},
    {0, 59, 0x80ffff0c, 0},
    {0, 60, 0x80ffff0c, 0},
    {0, 61, 0x80ffff0c, 0},
    {0, 62, 0x80ffff0c, 0},
    {0, 63, 0x80ffff0c, 0},
    {0, 64, 0x80ffff0c, 0},
    {0, 65, 0x80ffff0c, 0},
    {0, 66, 0x80ffff0c, 0},
    {0, 67, 0x80ffff0c, 0},
    {0, 68, 0x80ffff0c, 0},
    {0, 69, 0x80ffff0c, 0},
    {0, 70, 0x80ffff0c, 0},
    {0, 71, 0x80ffff0c, 0},
    {0, 72, 0x80ffff0c, 0},
    {0, 73, 0x80ffff0c, 0},
    {0, 74, 0x80ffff0c, 0},
    {0, 75, 0x80ffff0c, 0},
    {0, 76, 0x80ffff0c, 0},
    {0, 77, 0x80ffff0c, 0},
    {0, 78, 0x80ffff0c, 0},
    {0, 79, 0x80ffff0c, 0}
};

// GLOBAL: GAME 0x0067c5d8
const SBInputDataFormat g_inputJoystickFormat = {24, 16, 1, 80, 44, g_inputJoystickObjects};

DECOMP_SIZE_ASSERT(SBInputObjectFormat, 0x10)
DECOMP_SIZE_ASSERT(SBInputDataFormat, 0x18)
DECOMP_SIZE_ASSERT(g_inputJoystickObjects, 0x2c0)

#endif
