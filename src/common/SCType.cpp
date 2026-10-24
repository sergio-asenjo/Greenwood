#include "SBNullstr.h"
#include "SCType.h"

int SCSerializeUnk00642a2f(const char *, ...);

void EmitSCType(const SCType *type, std::string &name)
{
    type->GetTypeName(name);
}

// STUB: GAME 0x00639c10
void SCType::GetTypeName(std::string &name) const
{
    unsigned char type = m_type;
    switch (type)
    {
    case 4:
        // STRING: GAME 0x006be288
        name = std::string("void");
        return;
    case 1:
        // STRING: GAME 0x006be280
        name = std::string("bool");
        return;
    case 2:
        // STRING: GAME 0x006be27c
        name = std::string("int");
        return;
    case 3:
        // STRING: GAME 0x006be274
        name = std::string("float");
        return;
    case 7:
        name = m_name;
        return;
    case 0:
    case 5:
    case 6:
    case 8:
        // STRING: GAME 0x006be268
        name = std::string("NotExpected");
    default:
        SCSerializeUnk00642a2f(
            // STRING: GAME 0x006be23c
            "SCType::GetTypeName: Case not expected.\n");
    }
}
