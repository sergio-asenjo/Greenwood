#ifndef RHSECTORSCRIPT_H
#define RHSECTORSCRIPT_H

class SBFile;
class RHElementActor;

class RHUnkSectorScriptRef
{
public:
    int Unk004089f0(RHElementActor *actor);
    int Unk00408af0(RHElementActor *actor);
    int Unk00408900();
    void *m_0;
};

class RHSectorScript
{
public:
    bool FUN_0057ff00(RHElementActor *actor);
    void Enter(RHElementActor *actor);
    void Leave(RHElementActor *actor);
    void InitializeFromMissionStream(SBFile &file);
    bool Serialize(SBFile &file);
    void Emit(RHElementActor *actor);
    void Emit(SBFile &file);

    char m_pad0[0x36];
    unsigned short m_36;
    char m_pad38[0x80];
    char m_b8;
    char m_padb9[7];
    char *m_c0;
    RHUnkSectorScriptRef m_c4;
    unsigned short m_c8;
    char m_padca[2];
    unsigned m_cc[9];
    char m_padf0[4];
    int m_f4;
};

#endif
