#include "SBNullstr.h"
#include "RHShortBriefings.h"

class RHShortBriefingVectorEmission : public std::vector<RHShortBriefings::ShortBriefing>
{
public:
    static void Emit()
    {
        typedef RHShortBriefings::ShortBriefing Value;
        void (std::vector<Value>::*volatile fill)(Value *, unsigned, const Value &) = &RHShortBriefingVectorEmission::_Ufill;
        Value *(std::vector<Value>::*volatile copy)(const Value *, const Value *, Value *) = &RHShortBriefingVectorEmission::_Ucopy;
        Value *(__cdecl *volatile assign)(Value *, Value *, Value *) = &std::copy;
    }
};

// TEMPLATE: GAME 0x0054c320
// ?insert@?$vector@UShortBriefing@RHShortBriefings@@V?$allocator@UShortBriefing@RHShortBriefings@@@std@@@std@@QAEXPAUShortBriefing@RHShortBriefings@@IABU34@@Z

// TEMPLATE: GAME 0x0054c570
// ?_Ufill@?$vector@UShortBriefing@RHShortBriefings@@V?$allocator@UShortBriefing@RHShortBriefings@@@std@@@std@@IAEXPAUShortBriefing@RHShortBriefings@@IABU34@@Z

// TEMPLATE: GAME 0x0054c5a0
// ?copy@std@@YAPAUShortBriefing@RHShortBriefings@@PAU23@00@Z

// FUNCTION: GAME 0x005a3030
bool RHShortBriefings::Serialize(SBFile &file)
{
    // STRING: GAME 0x006b7834
    RHSerializeName(file, "RHShortBriefings");
    SerializeContainer(file, m_0, SerializeShortBriefing);
    SerializeContainer(file, m_10, SerializeShortBriefing);
    return true;
}

// FUNCTION: GAME 0x005a32a0
bool RHShortBriefings::SerializeShortBriefing(SBFile &file, ShortBriefing &value)
{
    if (file.Access(&value.m_0, 4) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        // STRING: GAME 0x006b77a8
        SBAssert(0, "P:\\Robin Hood\\RHShortBriefings.cpp", 399, "Serialize failed reason is %s", reason);
        return false;
    }
    if (file.Access(&value.m_4, 1) < 0)
    {
        SBString *err = file.GetError();
        const char *reason = err->m_chars ? err->m_chars : "";
        SBAssert(0, "P:\\Robin Hood\\RHShortBriefings.cpp", 400, "Serialize failed reason is %s", reason);
        return false;
    }
    return true;
}

void RHShortBriefings::Emit(SBFile &file)
{
    RHShortBriefingVectorEmission::Emit();
    Serialize(file);
    ShortBriefing value;
    SerializeShortBriefing(file, value);
}

// TEMPLATE: GAME 0x005a3320
// ?_Ucopy@?$vector@UShortBriefing@RHShortBriefings@@V?$allocator@UShortBriefing@RHShortBriefings@@@std@@@std@@IAEPAUShortBriefing@RHShortBriefings@@PBU34@0PAU34@@Z

// TEMPLATE: GAME 0x005a3360
// ?erase@?$vector@UShortBriefing@RHShortBriefings@@V?$allocator@UShortBriefing@RHShortBriefings@@@std@@@std@@QAEPAUShortBriefing@RHShortBriefings@@PAU34@0@Z
