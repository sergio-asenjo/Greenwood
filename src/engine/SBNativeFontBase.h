#ifndef SB_NATIVE_FONT_BASE_H
#define SB_NATIVE_FONT_BASE_H

class SBNativeFontRenderContext;

class __declspec(novtable) SBNativeFontBase
{
public:
    SBNativeFontBase();
    ~SBNativeFontBase();
    void *FUN_0061e7e0(unsigned flags);
    virtual unsigned GetImplementationVersion() const = 0;
    SBNativeFontRenderContext *m_context;
    unsigned char m_08[0x3c];
};

#endif
