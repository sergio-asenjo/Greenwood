#ifndef SBINPUTMOUSESTATE_H
#define SBINPUTMOUSESTATE_H

struct SBInputMouseState
{
    short m_x;
    short m_y;
    short m_wheel;
    unsigned char m_left;
    unsigned char m_right;
    unsigned char m_middle;
};

#endif
