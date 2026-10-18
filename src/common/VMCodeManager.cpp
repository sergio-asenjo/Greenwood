#include "SBNullstr.h"
#include "VMCore.h"
#include <list>

// FUNCTION: GAME 0x0063a490
VMUnk0063a490Result *VMUnk0063a490::FUN_0063a490(void *value)
{
    const std::string &name = *(const std::string *)value;
    typedef std::list<VMUnk0063a490Result *> Classes;
    const Classes &classes = *(const Classes *)((const char *)this + 4);
    for (Classes::const_iterator node = classes.begin(); node != classes.end(); ++node) {
        VMUnk0063a490Result *result = *node;
        if (*(const std::string *)((const char *)result + 0x14) == name)
            return result;
    }
    return 0;
}

// FUNCTION: GAME 0x0063a510
void *VMUnk0063a490::FUN_0063a510(VMUnk0063a490Result *owner, void *value)
{
    const std::string &name = *(const std::string *)value;
    typedef std::list<void *> Functions;
    const Functions &functions = *(const Functions *)((const char *)owner + 0x34);
    for (Functions::const_iterator node = functions.begin(); node != functions.end(); ++node) {
        void *result = *node;
        if (*(const std::string *)((const char *)result + 4) == name)
            return result;
    }
    return 0;
}
