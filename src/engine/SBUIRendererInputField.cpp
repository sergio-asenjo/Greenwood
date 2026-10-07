#include "SBUIRendererInputField.h"
#include "SBUIRenderer.h"

// STUB: GAME 0x00621430
void SBUIInputFieldUnk00621440::FUN_00621430(unsigned int value)
{
    ((SBUIUnk0060d530 *)this)->FUN_0060d530(value);
}

// FUNCTION: GAME 0x00621440
void SBUIInputFieldUnk00621440::FUN_00621440(SBUIInputFieldUnkResource *resource)
{
    m_6c = resource;
    if (m_64)
        m_64->v2(1);
    m_64 = m_6c->m_14;
    m_68 = m_6c->m_18;
}

void SBUIInputFieldEmit(SBUIInputFieldUnk00621440 *renderer)
{
    renderer->FUN_00621430(0);
    renderer->FUN_00621440(0);
}
