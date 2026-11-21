#ifndef RHCONSOLEHELPARRAY_H
#define RHCONSOLEHELPARRAY_H

#include <vector>

struct RHConsoleHelpCommand;

class RHConsoleHelpArray : public std::vector<RHConsoleHelpCommand *>
{
public:
    RHConsoleHelpArray() : dirty(true) {}
    ~RHConsoleHelpArray() { clear(); }
    void insert(RHConsoleHelpCommand *const &value);
    RHConsoleHelpCommand **cursor;
    bool dirty;
    unsigned char m_15[0xb];
};

#endif
