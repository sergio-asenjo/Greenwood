#ifndef SB_INPUT_SYSTEM_DATA_H
#define SB_INPUT_SYSTEM_DATA_H

#include "SBInputData.h"

extern const SBInputDeviceGuid g_inputKeyboardGuid;
extern const SBInputDeviceGuid g_inputMouseGuid;
extern const SBInputDeviceGuid g_inputKeyGuid;
extern const SBInputDeviceGuid g_inputDeviceInterfaceGuid;
extern const SBInputObjectFormat g_inputMouseObjects[7];
extern const SBInputObjectFormat g_inputBufferedMouseObjects[11];
extern const SBInputObjectFormat g_inputKeyboardObjects[256];
extern const SBInputDataFormat g_inputMouseFormat;
extern const SBInputDataFormat g_inputBufferedMouseFormat;
extern const SBInputDataFormat g_inputKeyboardFormat;

#endif
