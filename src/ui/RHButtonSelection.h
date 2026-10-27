#ifndef RHBUTTONSELECTION_H
#define RHBUTTONSELECTION_H

class RHUnk0052d2c0
{
public:
    // FUNCTION: GAME 0x0052d2c0
    void SetEnable(bool enable)
    {
        if (enable == true)
        {
            if (!m_enabled)
            {
                int old = m_unk7c;
                m_enabled = true;
                if (old == 5) m_unk7c = 8;
                if (m_unk7c == 6) m_unk7c = 9;
            }
        }
        else if (enable == false)
        {
            if (m_enabled == true)
            {
                int old = m_unk7c;
                m_enabled = false;
                m_unk4c = 0;
                if (old == 8) m_unk7c = 5;
                if (m_unk7c == 9) m_unk7c = 6;
            }
        }
    }

    char m_pad0[0x4c];
    int m_unk4c;
    char m_pad1[0x2c];
    int m_unk7c;
    char m_pad2[0x58];
    bool m_enabled;
};

#endif
