#ifndef RHCAMPAIGNRESETARRAY_H
#define RHCAMPAIGNRESETARRAY_H

#include <vector>
#include <algorithm>
#include <string>

template<class T>
class RHCampaignResetArray : public std::vector<T>
{
public:
    static void Reset(std::vector<T> &values)
    {
        T *next = std::copy(values.end(), values.end(), values.begin());
        void (std::vector<T>::*destroy)(T *, T *) = &RHCampaignResetArray<T>::_Destroy;
        (values.*destroy)(next, values.end());
        T *std::vector<T>::*last = &RHCampaignResetArray<T>::_Last;
        values.*last = next;
    }
};

template<>
inline void RHCampaignResetArray<std::wstring>::Reset(std::vector<std::wstring> &values)
{
    std::wstring *first = values.end();
    std::wstring *last = values.end();
    std::wstring *next = values.begin();
    for (; first != last; ++first, ++next)
    {
        std::wstring &(std::wstring::*assign)(const std::wstring &, unsigned, unsigned) = &std::wstring::assign;
        (next->*assign)(*first, 0, *(const volatile unsigned *)&std::wstring::npos);
    }
    void (std::vector<std::wstring>::*destroy)(std::wstring *, std::wstring *) = &RHCampaignResetArray<std::wstring>::_Destroy;
    (values.*destroy)(next, values.end());
    std::wstring *std::vector<std::wstring>::*end = &RHCampaignResetArray<std::wstring>::_Last;
    values.*end = next;
}

#endif
