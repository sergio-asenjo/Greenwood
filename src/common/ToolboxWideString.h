#ifndef TOOLBOXWIDESTRING_H
#define TOOLBOXWIDESTRING_H

#include <string>

namespace Toolbox
{
    std::wstring Convert(const std::string &text);
    std::wstring TrimWideString(const std::wstring &text);
}

#endif
