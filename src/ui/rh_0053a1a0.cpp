#include "RHElementActor_calls.h"

class RHMenuPopupScroll
{
public:
    static void FUN_0053a0b0(int id);
};

// FUNCTION: GAME 0x0053a1a0
void FUN_0053a1a0(RHSequenceElement *element)
{
    RHMenuPopupScroll::FUN_0053a0b0(element->Unk00587160(0x14));
    element->FUN_00585970(0, 1);
}
