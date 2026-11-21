#ifndef RHPATCHCLASS_H
#define RHPATCHCLASS_H

#include <list>
#include "RHMotionAreaList.h"
#ifndef SBGEO_POINT2D_VIEW
#include "SBGeoPoint2D.h"
#endif
#include "SBResourceManager.h"

class SBFile;
class RHElementActor;
class RHPatchVirtualCalls;
class RHUnk0057d3f0;

class RHPatchActorList
{
public:
    ~RHPatchActorList()
    {
        typedef std::list<RHElementActor *> Actors;
        void (Actors::*clear)() = &Actors::clear;
        (list.*clear)();
    }
    std::list<RHElementActor *> list;
    std::list<RHElementActor *>::iterator current;
    char valid;
    char padding11[3];
    int index;
    char searchValid;
    char padding19[3];
    int searchIndex;
    RHElementActor *searchValue;

    int Find(RHElementActor *actor)
    {
        int count = list.size();
        searchValue = actor;
        searchValid = 1;
        void *head = *(void **)((char *)&list + 4);
        void *first = *(void *volatile *)head;
        *(void **)&current = first;
        int wanted = 0;
        for (; wanted < count; ++wanted, current++)
            if (*current == searchValue)
                break;
        if (wanted < count)
        {
            searchIndex = wanted;
            valid = 0;
            index = wanted;
        }
        else
        {
            valid = 1;
            searchIndex = -1;
        }
        return searchIndex;
    }
};

class RHUnk0054f870
{
public:
    bool Unk0054f870(SBFile &file);
};

class RHPatch
{
public:
    ~RHPatch();
    bool Serialize(SBFile &file) { return ((RHUnk0054f870 *)this)->Unk0054f870(file); }
    void Enter(RHElementActor *actor);
    void Leave(RHElementActor *actor);
    void FUN_0054fc40(bool open);
    void FUN_0054fe10();
    void FUN_0054fe50(bool open, bool mode);
    void FUN_00550070(bool mode);
    void FUN_00550150();
    void FUN_00550220();
    void Emit(SBFile &file, RHElementActor *actor);

    char m_0;
    char m_1;
    char m_2;
    char m_3;
    char m_4;
    char m_5;
    char m_6;
    char m_7;
    char m_8;
    char m_9;
    char m_a;
    char m_b;
    char m_c;
    char m_d;
    char paddinge[2];
    unsigned long m_10;
    unsigned short m_14;
    unsigned short m_16;
    RHPatchVirtualCalls *m_18;
    RHMotionAreaList<void *> m_1c;
    RHMotionAreaList<void *> m_40;
    RHMotionAreaList<void *> m_64;
    RHMotionAreaList<void *> m_88;
    RHMotionAreaList<void *> m_ac;
    RHMotionAreaList<void *> m_d0;
    RHMotionAreaList<void *> m_f4;
    RHMotionAreaList<void *> m_118;
    unsigned short m_13c;
    unsigned short m_13e;
    SBGeoPoint2D m_140;
    RHUnk0057d3f0 *m_148;
    RHUnk0057d3f0 *m_14c;
    RHUnk0057d3f0 *m_150;
    RHUnk0057d3f0 *m_154;
    SBResourceSurfaceArray m_158;
    RHPatchActorList m_178;
    char m_19c;
};

#endif
