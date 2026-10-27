#include "SBNullstr.h"
#include "SCType.h"
#include "SBFile.h"

int SCSerializeUnk00642a2f(const char *, ...) throw();

void EmitSCType(const SCType *type, std::string &name)
{
    type->GetTypeName(name);
}

void EmitSCTypeSerialize(SCType *type)
{
    type->Serialize(0, false);
}

// FUNCTION: GAME 0x00639c10
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

// FUNCTION: GAME 0x00639f80
int SCType::Serialize(FILE *file, bool writing)
{
    int result;
    if (writing) {
        unsigned char type = m_type;
        unsigned char length = m_name.size();
        result = SBFileUnk00643cd3(&type, 1, 1, file);
        result += SBFileUnk00643cd3(&length, 1, 1, file);
        result += SBFileUnk00643cd3(m_name.c_str(), length, 1, file);
    } else {
        unsigned char length;
        char name[32];
        result = SBFileUnk00643e0c(&m_type, 1, 1, file);
        result += SBFileUnk00643e0c(&length, 1, 1, file);
        result += SBFileUnk00643e0c(name, length, 1, file);
        name[length] = 0;
        m_name = name;
    }
    return result;
}
