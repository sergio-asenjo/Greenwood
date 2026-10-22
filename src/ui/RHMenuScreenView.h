#ifndef RHMENUSCREENVIEW_H
#define RHMENUSCREENVIEW_H

#include "Decomp.h"
#include "RHMenuScreenTimer.h"
#include <deque>
#include <vector>
#include <list>
#include <string>

class SBUILifetime
{
public:
    SBUILifetime();
    ~SBUILifetime();
    undefined m_00[0x17f8];
};

class SBUIUnkSurface
{
public:
    SBUIUnkSurface(unsigned long surface);
    ~SBUIUnkSurface();
    undefined m_00[0x20];
};

class SBThreadedInput;
class RHMenuWindow;
class RHMenuWindowUI;

struct RHMapScreenNode
{
    RHMapScreenNode *left;
    RHMapScreenNode *parent;
    RHMapScreenNode *right;
    undefined m_0c[0x14];
    int color;
};

struct RHMapScreenLess
{
};

struct RHMapScreenAlloc
{
};

class RHMapScreenTree
{
public:
    inline RHMapScreenTree(const RHMapScreenLess &comp, bool multi, const RHMapScreenAlloc &alloc);
    ~RHMapScreenTree();
    static inline RHMapScreenNode *Buynode(RHMapScreenNode *parent, int color);
    inline void Init();
    RHMapScreenAlloc m_alloc;
    RHMapScreenLess m_comp;
    undefined m_02[2];
    RHMapScreenNode *m_head;
    bool m_multi;
    undefined m_09[3];
    unsigned m_size;
};

class RHMenuScreenView
{
public:
    RHMenuScreenView(unsigned long flags, long background, bool colorize, bool pause, void *ui);
    RHMenuScreenView(unsigned long flags, long background, unsigned short color, void *ui);
    ~RHMenuScreenView();
    static void *FUN_0053b730(long background, unsigned short color);
    void FUN_0053c140(unsigned long flags);
    void FUN_0053be40(unsigned long value);
    void *FUN_0053be80(const std::string &name);
    void FUN_0053bb80(RHMenuWindow *window, bool display, bool modal);
    void FUN_0053b1f0(RHMenuWindow *window);
    void FUN_0053c390();
    void FUN_0053c650(RHMenuWindow *window, bool display);
    static void FUN_0053bbc0(RHMenuWindow *window);
    static void FUN_0053be60(RHMenuWindow *window);
    RHMenuWindowUI *FUN_0053bf30();
    void FUN_0053bf40(void *events);
    void FUN_0053c050();
    bool FUN_0053c320(void *widget);
    void FUN_0053c7f0(unsigned long surface);
    void FUN_0053c800();
    bool FUN_0053cd20();

    void *m_ui;
    unsigned long m_04;
    unsigned long m_08;
    void *m_background;
    SBUILifetime m_sbui;
    undefined m_1808[0x10c];
    unsigned long m_1914;
    SBThreadedInput *m_input;
    std::deque<std::vector<void *> > m_191c;
    SBUIUnkSurface m_surfaces;
    RHMapScreenTree m_196c;
    bool m_197c;
    std::list<RHMenuScreenTimer> m_1980;
    unsigned long m_198c;
};

typedef RHMenuScreenView RHMenuWindowScreen;

#endif
