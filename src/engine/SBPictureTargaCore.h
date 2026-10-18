#ifndef SBPICTURETARGACORE_H
#define SBPICTURETARGACORE_H

#include "SBPicture.h"
#include <string>

class SBFile;
struct SBPictureInfo;
struct SBPictureTGAHeader;

class SBPictureTargaBase : public SBPicture
{
public:
    SBPictureTargaBase();
    ~SBPictureTargaBase();
};

class SBPictureTarga : public SBPictureTargaBase
{
public:
    SBPictureTarga();
    ~SBPictureTarga();
    void *FUN_006150f0(unsigned flags);
    const SBPictureInfo &GetInfoFromFile(const std::string &name);
    bool LoadFromFile(const std::string &name);
    bool LoadFromStream(SBFile &file);
    bool SaveToFile(const std::string &name);
    bool SaveToStream(SBFile &file);
    void SerializeHeader(SBFile &file, SBPictureTGAHeader &header);
    SBPictureInfo &Info() { return *(SBPictureInfo *)m_pad08; }
};

#endif
