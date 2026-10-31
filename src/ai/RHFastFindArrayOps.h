#ifndef RHFASTFINDARRAYOPS_H
#define RHFASTFINDARRAYOPS_H

#include <vector>

class RHScriptFXArray
{
public:
    int grow;
    void **first;
    void **last;
    void **end;
    void **cursor;
    bool dirty;
    void **Unk004fe420(void **first, void **last, void **destination);
    void Unk004fe450(void **destination, unsigned int count, void *const &value);
    void Unk005008e0(void **first, void **last);
    unsigned int Size() { return first == 0 ? 0 : last - first; }
};

class RHFastFindGateArray : public RHScriptFXArray
{
public:
    unsigned int FUN_0059fbc0()
    {
        typedef unsigned (std::vector<unsigned long>::*Size)() const;
        Size size = &std::vector<unsigned long>::size;
        return (((const std::vector<unsigned long> *)this)->*size)();
    }
    void InsertLast(void *const &value, bool inlineCopy = true, bool externalSize = false, bool sourceFirst = false);
};

#endif
