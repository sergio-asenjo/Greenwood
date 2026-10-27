#ifndef SB_INPUT_KEYBOARD_STATE_H
#define SB_INPUT_KEYBOARD_STATE_H

class SBInputKeyboardState
{
public:
    unsigned char &operator[](unsigned short index) { return m_keys[index]; }
    unsigned char m_keys[0x100];
};

#endif
