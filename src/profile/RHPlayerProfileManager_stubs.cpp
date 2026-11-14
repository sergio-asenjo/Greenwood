#include "SBNullstr.h"
#include "RHPlayerProfileManager.h"

template<> __declspec(selectany) const std::string::size_type std::string::npos = unsigned(-1);

// TEMPLATE: GAME 0x0056db40
// ?find@?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@QBEIPBDII@Z
unsigned EmitRHProfileStringFind(const std::string &text, const char *value, unsigned first, unsigned count)
{
    unsigned (std::string::*find)(const char *, unsigned, unsigned) const = &std::string::find;
    return (text.*find)(value, first, count);
}
