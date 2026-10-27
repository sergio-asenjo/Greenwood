#ifndef SCTYPE_H
#define SCTYPE_H

#include <string>
#include <stdio.h>
#include <list>

class SCFunctionArg;

class SCType
{
public:
    SCType() : m_type(0), m_01(0), m_04(-1) {}
    void GetTypeName(std::string &name) const;
    int Serialize(FILE *file, bool writing);
    unsigned char m_type;
    unsigned char m_01;
    int m_04;
    std::list<SCFunctionArg *> m_08;
    std::string m_name;
};

#endif
