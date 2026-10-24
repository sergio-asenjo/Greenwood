#ifndef SCTYPE_H
#define SCTYPE_H

#include <string>

class SCType
{
public:
    void GetTypeName(std::string &name) const;
    unsigned char m_type;
    unsigned char m_01[0x13];
    std::string m_name;
};

#endif
