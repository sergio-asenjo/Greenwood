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

extern const SBInputDeviceGuid g_inputPovGuid;
extern const SBInputDeviceGuid g_inputSliderGuid;
extern const SBInputDeviceGuid g_inputRzAxisGuid;
extern const SBInputDeviceGuid g_inputRyAxisGuid;
extern const SBInputDeviceGuid g_inputRxAxisGuid;
extern const SBInputDeviceGuid g_inputZAxisGuid;
extern const SBInputDeviceGuid g_inputYAxisGuid;
extern const SBInputDeviceGuid g_inputXAxisGuid;
extern const SBInputObjectFormat g_inputJoystickObjects[44];
extern const SBInputDataFormat g_inputJoystickFormat;

DECOMP_SIZE_ASSERT(SBInputObjectFormat, 0x10)
DECOMP_SIZE_ASSERT(SBInputDataFormat, 0x18)
DECOMP_SIZE_ASSERT(g_inputJoystickObjects, 0x2c0)

#endif
