#ifndef SBPICTUREUNKVIEW_H
#define SBPICTUREUNKVIEW_H

class SBPictureUnkView
{
public:
    SBPictureUnkView();
    ~SBPictureUnkView();
    char m_00[4];
    unsigned short m_width;
    unsigned short m_height;
    unsigned long m_pitch;
    unsigned short m_depth;
    char m_0e[2];
    unsigned short *m_data;
    char m_14[4];
};

#endif
