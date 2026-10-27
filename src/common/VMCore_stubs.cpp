#include "SBNullstr.h"
#include "VMCore.h"

VMUnk00634ab0Record::VMUnk00634ab0Record(const VMUnk00634ab0Record &other)
{
    ((std::string *)&m_name)->assign(*(const std::string *)&other.m_name, 0, std::string::npos);
    m_serializer = other.m_serializer;
}
