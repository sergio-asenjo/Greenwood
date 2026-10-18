#ifndef SB_NATIVE_FONT_BASE_H
#define SB_NATIVE_FONT_BASE_H

class SBNativeFontRenderContext;

class SBNativeFontBase
{
public:
    SBNativeFontBase();
    ~SBNativeFontBase();
    unsigned m_vptr;
    SBNativeFontRenderContext *m_context;
    unsigned char m_08[0x3c];
};

#endif
