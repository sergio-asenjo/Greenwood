#ifndef RHSOUNDCORE_H
#define RHSOUNDCORE_H

#include "RHSoundCacheCore.h"

class SBGeoPoint2D;
class RHSoundSource;
class RHSoundSourceManager;
struct RHSoundPendingNode;
struct RHSoundPendingData;
struct RHSoundSettings;

struct RHSoundChannelSettings
{
    float m_00;
    float m_04;
    float m_08;
    unsigned short m_0c;
    unsigned short m_0e;
    unsigned short m_10;
    unsigned short m_12;
    float m_14[3];
};

struct RHSoundGeometryView
{
    void FUN_005b33b0(RHSoundChannelSettings &settings);
    void FUN_005b3420(RHSoundChannelSettings &settings);
    unsigned short FUN_005b3500();
    unsigned short FUN_005b3490(bool);
    unsigned short FUN_005b34e0();
    bool FUN_005b2ff0(const RHSoundSettings &, bool, RHSoundChannelSettings &);
    undefined m_00[0x10];
    float m_10;
    undefined m_14[0xb4];
};

struct RHSoundChannel
{
    int m_00;
    void *m_04;
    RHSoundCacheEntry *m_08;
    void *m_0c;
};

struct RHSoundChannels
{
    undefined4 m_00;
    RHSoundChannel *m_04;
    RHSoundChannel *m_08;
    RHSoundChannel *m_0c;
    undefined m_10[4];
    bool m_14;
    undefined m_15[0x17];
    unsigned int Size() const { return m_04 ? m_08 - m_04 : 0; }
    RHSoundChannel *Begin() { return m_04; }
    RHSoundChannel *End() { return m_08; }
    void Destroy(RHSoundChannel *first, RHSoundChannel *last)
    {
        for (; first != last; ++first)
            ((std::allocator<RHSoundChannel> *)&m_00)->destroy(first);
    }
    RHSoundChannel *Remove(RHSoundChannel *first, RHSoundChannel *last)
    {
        RHSoundChannel *next = std::copy(last, m_08, first);
        Destroy(next, End());
        m_08 = next;
        return first;
    }
    void FUN_005aa920();
    void FUN_005aaa50(unsigned int, const RHSoundChannel &);
    int FUN_0045a490();
    RHSoundChannel *FUN_005aaca0(RHSoundChannel *, RHSoundChannel *, RHSoundChannel *);
    void FUN_005aacf0(RHSoundChannel *, unsigned int, const RHSoundChannel &);
};

class RHScriptSoundStateCalls
{
public:
    void FUN_005a7ef0(int state);
    void FUN_005a7fb0(int state);
};

class RHSound
{
public:
    bool FUN_005a6520(unsigned long &driver);
    void FUN_005a67b0(unsigned long &driver);
    bool InitializeSound(unsigned short driver, bool spatial, std::string &error);
    void *FUN_005a6f90();
    int FUN_005a72c0(const RHSoundSettings &sound, RHSoundChannelSettings &settings, unsigned int position);
    void FUN_005a7410(int channel, RHSoundChannelSettings &settings);
    bool InitializeSoundEngine(std::string &error);
    void Activate(const RHSoundCacheMissionProfile *profile, bool flag);
    void ApplySoundSettings();
    unsigned short FUN_005a8040();
    void FUN_005a8420(int channel);
    void FUN_005a8470(void *first, void *second);
    void FUN_005a8650(const SBGeoPoint2D &position, float zoom);
    void FUN_005a8700(void *position, void *zoom);
    void FUN_005ad400(void *data);
    void PlayJingle(int jingle);
    unsigned long OpenStream(const std::string &name, void *&stream, bool loop, unsigned long position);
    int FUN_005a9040(void *stream, void *callback, int channel);
    void FUN_005a90d0(void *&stream, int &channel);
    bool FUN_005a9170(unsigned long id);
    void FUN_005a9420();
    bool PlayDialog(std::string &name);
    bool Serialize(SBFile &file);
    void FUN_005a6fb0(int channel, int type, RHSoundCacheEntry *entry, void *value, void *value2, void *value3);
    RHSoundCacheEntry *FUN_005ae9f0(unsigned long id);
    RHSoundCacheEntry *FUN_005a7080(const RHSoundSettings &, bool);
    void FUN_005a7110(RHSoundSource *);
    bool FUN_005a9260(unsigned short, bool, unsigned long &, std::string &);
    void FUN_005ad570(void *);
    void FUN_005a79f0(bool);
    void FUN_005a74e0(unsigned long);
    bool FUN_005a71f0(RHSoundSource *);
    void FUN_005a7220(void *);
    void FUN_005a9380();
    void FUN_005a99b0();
    void FUN_005a99c0();
    bool IsDialogFinished();
    float GetDialogVolume();
    bool CloseDialog();
    void GetCacheStats(RHsampleCacheStats *, int &);
    void FUN_005a87f0(RHSoundSource *);
    void FUN_005a8810(void *);
    bool FUN_005a8880(RHSoundSource *);
    bool FUN_005a88a0(void *);
    bool FUN_005a8220(int, int, int, const SBGeoPoint2D &);
    bool FUN_005a8330(int, int, int, const SBGeoPoint2D &);
    void FUN_005aec10();
    void FUN_005a7660(bool);
    void FUN_005a8780();
    unsigned long FUN_005a93e0(RHSoundPendingData &);
    bool FUN_005a9400(const RHSoundSettings &);
    void Emit(SBFile &file, std::string &name, RHSoundChannelSettings &settings);

    RHSoundCache m_000;
    RHSoundGeometryView m_138;
    RHSoundSourceManager *m_200;
    void *m_204;
    unsigned short m_208;
    char m_20a;
    char m_20b;
    undefined m_20c[4];
    bool m_210;
    char m_211;
    char m_212;
    bool m_213;
    char m_214;
    undefined m_215[3];
    unsigned int m_218;
    RHSoundChannels m_21c;
    undefined m_248[4];
    RHSoundPendingNode *m_24c;
    unsigned int m_250;
    void *m_254;
    unsigned long m_258;
    int m_25c;
    void *m_260;
    int m_264;
    void *m_268;
    int m_26c;
    void *m_270;
    int m_274;
    char m_278;
    bool m_279;
    char m_27a;
    char m_27b;
    char m_27c;
    char m_27d;
    char m_27e;
    char m_27f;
    int m_280;
    unsigned short m_284;
    undefined m_286[2];
    unsigned long m_288;
    unsigned long m_28c;
    unsigned long m_290;
};

#endif
