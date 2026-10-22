#include "SBNullstr.h"
#include "VMCore.h"

VMUnk00634ab0Record::VMUnk00634ab0Record(const VMUnk00634ab0Record &other)
{
    ((std::string *)&m_name)->assign(*(const std::string *)&other.m_name, 0, std::string::npos);
    m_serializer = other.m_serializer;
}

bool VMUnk0063a250::FUN_0063a250(int, int) { return false; }
VMCore::VMCore(VMUnk0063a490 *, VMUnk0063a140 *) {}
