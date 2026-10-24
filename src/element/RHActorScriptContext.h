#ifndef RHACTORSCRIPTCONTEXT_H
#define RHACTORSCRIPTCONTEXT_H

class RHUnkSectorScript;

class RHActorScriptContext
{
public:
    int FUN_004030a0();
    int ActionChange(int action, int previous);
    int FilterAIEvent(void *event, int value);
    void FUN_004033b0(int message, int argument1, int argument2);
    RHUnkSectorScript *m_0;
};

#endif
