#include "SBNullstr.h"
#include "RHElement.h"

void RHSerializeName(SBFile &file, const char *name);

class RHElementFXMasked : public RHElement
{
public:
    bool Serialize(SBFile &file);
    char m_fc[4];
};

// FUNCTION: GAME 0x004aaf80
bool RHElementFXMasked::Serialize(SBFile &file)
{
    // STRING: GAME 0x006aeaf4
    RHSerializeName(file, "RHElementFXMasked");
    file.Access((char *)this + 0xfc, 4);
    return RHElement::Serialize(file);
}
