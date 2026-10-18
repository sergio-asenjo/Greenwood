#include <string.h>

typedef void BZFILE;

extern "C" int __stdcall BZ2_bzwrite(BZFILE *b, void *buf, int len);

class RHUnk005f7ff0
{
public:
    void FUN_005f7ff0(const char *str);
    BZFILE *m_0;
};

// FUNCTION: GAME 0x005f7ff0
void RHUnk005f7ff0::FUN_005f7ff0(const char *str)
{
    if (m_0 == 0 || str == 0)
        return;
    BZ2_bzwrite(m_0, (void *)str, strlen(str));
    // STRING: GAME 0x006b8f84
    BZ2_bzwrite(m_0, (void *)"\r\n", 2);
}
