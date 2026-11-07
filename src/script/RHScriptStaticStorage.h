#ifndef RHSCRIPTSTATICSTORAGE_H
#define RHSCRIPTSTATICSTORAGE_H

template<class C> class SBResourceTextArray;
class RHFastFindRangeArray;
class RHUnk00564020;

class RHScriptStaticStorage
{
public:
    static SBResourceTextArray<char> marrayString;
    static RHFastFindRangeArray marrayElementsScript;
    static RHUnk00564020 mlistUnk6c0fe8;
    static RHUnk00564020 mlistUnk6c0f50;
    static RHUnk00564020 mlistLocationStorage;
    static RHUnk00564020 mlistUnk6c0f80;
};

#endif
