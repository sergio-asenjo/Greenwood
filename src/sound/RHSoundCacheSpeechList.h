#ifndef RHSOUNDCACHESPEECHLIST_H
#define RHSOUNDCACHESPEECHLIST_H

#include "RHSoundCache.h"

struct RHSoundCacheSpeechList : RHSoundCacheList
{
    void GoToSpeech(int wanted)
    {
        int count = m_08;
        if (m_10)
        {
            if (wanted <= (count + 1) / 2)
            {
                std::bidirectional_iterator_tag category;
                FUN_005c9010((RHUnk005c9010Iterator &)(m_0c = FUN_0046eb80()), wanted, category);
            }
            else
            {
                std::bidirectional_iterator_tag category;
                FUN_005c9010((RHUnk005c9010Iterator &)(m_0c = end()), wanted - count, category);
            }
            m_10 = false;
            m_14 = wanted;
        }
        else
        {
            int previous = m_14;
            if (wanted != previous)
            {
                if (wanted < previous)
                {
                    if (wanted < (previous + 1) / 2)
                    {
                        std::bidirectional_iterator_tag category;
                        FUN_005c9010((RHUnk005c9010Iterator &)(m_0c = FUN_0046eb80()), wanted, category);
                    }
                    else
                    {
                        std::bidirectional_iterator_tag category;
                        FUN_005c9010((RHUnk005c9010Iterator &)m_0c, wanted - previous, category);
                    }
                }
                else if (wanted < (previous + count) / 2)
                {
                    std::bidirectional_iterator_tag category;
                    FUN_005c9010((RHUnk005c9010Iterator &)m_0c, wanted - previous, category);
                }
                else
                {
                    m_0c = end();
                    std::bidirectional_iterator_tag category;
                    FUN_005c9010((RHUnk005c9010Iterator &)m_0c, wanted - count, category);
                }
                m_14 = wanted;
            }
        }
    }
    unsigned long &SpeechAt(int wanted)
    {
        GoToSpeech(wanted);
        return *m_0c;
    }
};

#endif
