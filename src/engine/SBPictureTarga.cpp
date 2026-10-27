// SBPictureTarga.cpp — TU (code 0x006150d0..0x006157f7). See SBPictureTarga.h for the binding evidence.

#include "SBNullstr.h"
#include "SBPictureTarga.h"
#include <string.h>

// FUNCTION: GAME 0x006150d0
SBPictureTarga::SBPictureTarga()
{
}

// FUNCTION: GAME 0x006150f0
void *SBPictureTarga::FUN_006150f0(unsigned flags)
{
    this->~SBPictureTarga();
    if (flags & 1)
        operator delete(this);
    return this;
}

// FUNCTION: GAME 0x00615110
SBPictureTarga::~SBPictureTarga()
{
}

// Parked: header byte/word loads and product registers allocate differently.
// STUB: GAME 0x00615120
const SBPictureInfo &SBPictureTarga::GetInfoFromFile(const std::string &name)
{
    RHUnk005f4fc0 file;
    if (file.FUN_005f5090(name, 1))
    {
        memset(&Info(), 0, sizeof(SBPictureInfo));
        return Info();
    }
    SBPictureTGAHeader header;
    SerializeHeader(file, header);
    file.FUN_005f5290();
    unsigned short depth = header.m_depth;
    unsigned short width = header.m_width;
    unsigned short height = header.m_height;
    Info().m_depth = depth;
    Info().m_width = width;
    Info().m_height = height;
    Info().m_size = (int)(depth * width * height) / 8;
    return Info();
}

// FUNCTION: GAME 0x00615220
bool SBPictureTarga::LoadFromFile(const std::string &name)
{
    RHUnk005f4fc0 file;
    if (file.FUN_005f5090(name, 1))
        return false;
    bool loaded = ((SBPictureTargaVirtuals *)this)->LoadFromStream(file);
    file.FUN_005f5290();
    return loaded;
}

// FUNCTION: GAME 0x006152d0
bool SBPictureTarga::LoadFromStream(SBFile &file)
{
    SBPictureTGAHeader header;
    SerializeHeader(file, header);
    m_20 = header.m_width;
    m_22 = header.m_height;
    if (m_1c)
    {
        operator delete(m_14);
        m_14 = 0;
    }
    switch (header.m_depth)
    {
    case 16:
    {
        m_04 = 2;
        m_24 = m_20 * 2;
        m_1c = m_22 * m_24;
        m_14 = new unsigned char[m_1c];
        for (unsigned short y = 0; y < header.m_height; ++y)
            file.Access((unsigned short *)m_14 + (header.m_height - y - 1) * header.m_width, header.m_width * 2);
        return true;
    }
    case 24:
        m_04 = 4;
        m_24 = m_20 * 3;
        m_1c = m_22 * m_24;
        m_14 = new unsigned char[m_1c];
        file.Access(m_14, m_1c);
        return true;
    case 8:
        m_24 = m_20;
        m_04 = 1;
        m_1c = m_22 * m_24;
        m_14 = new unsigned char[m_1c];
        file.Access(m_14, m_1c);
        return true;
    case 32:
        m_04 = 5;
        m_24 = m_20 * 2;
        m_1c = m_22 * m_24;
        m_14 = new unsigned char[m_1c];
        file.Access(m_14, m_1c);
        return true;
    }
    return false;
}

// FUNCTION: GAME 0x006154b0
bool SBPictureTarga::SaveToFile(const std::string &name)
{
    RHUnk005f4fc0 file;
    if (file.FUN_005f5090(name, 2))
        return false;
    bool saved = ((SBPictureTargaVirtuals *)this)->SaveToStream(file);
    file.FUN_005f5290();
    return saved;
}

// FUNCTION: GAME 0x00615560
bool SBPictureTarga::SaveToStream(SBFile &file)
{
    SBPictureTGAHeader header;
    switch (m_04)
    {
    case 4:
        header.m_depth = 24;
        header.SetColorMapped();
        break;
    case 3:
        FUN_006122b0(0);
    case 2:
        header.m_depth = 16;
        header.SetColorMapped();
        break;
    }
    header.m_idLength = 0;
    header.m_width = m_20;
    header.m_height = m_22;
    header.m_xOrigin = 0;
    header.m_yOrigin = 0;
    header.m_descriptor = 1;
    SerializeHeader(file, header);
    switch (header.m_depth)
    {
    case 16:
    {
        for (unsigned short y = 0; y < header.m_height; ++y)
            file.Access((unsigned short *)m_14 + (header.m_height - y - 1) * header.m_width, header.m_width * 2);
        break;
    }
    case 24:
    {
        for (unsigned short y = 0; y < header.m_height; ++y)
            file.Access(m_14 + (header.m_height - y - 1) * header.m_width * 3, header.m_width * 3);
        break;
    }
    case 8:
        file.Access(m_14, header.m_width * header.m_height);
        break;
    case 32:
        file.Access(m_14, header.m_width * header.m_height * 4);
        break;
    default:
        return false;
    }
    return true;
}

// FUNCTION: GAME 0x00615750
void SBPictureTarga::SerializeHeader(SBFile &file, SBPictureTGAHeader &header)
{
    file.Access(&header.m_idLength, 1);
    file.Access(&header.m_colorMapType, 1);
    file.Access(&header.m_imageType, 1);
    file.Access(&header.m_colorMapFirst, 2);
    file.Access(&header.m_colorMapLength, 2);
    file.Access(&header.m_colorMapDepth, 1);
    file.Access(&header.m_xOrigin, 2);
    file.Access(&header.m_yOrigin, 2);
    file.Access(&header.m_width, 2);
    file.Access(&header.m_height, 2);
    file.Access(&header.m_depth, 1);
    file.Access(&header.m_descriptor, 1);
}

void EmitSBPictureTarga(SBPictureTarga *picture)
{
    SBPictureTarga local;
    picture->FUN_006150f0(0);
    picture->GetInfoFromFile(std::string());
    picture->LoadFromFile(std::string());
    picture->SaveToFile(std::string());
    picture->LoadFromStream(*(SBFile *)0);
    picture->SaveToStream(*(SBFile *)0);
    picture->SerializeHeader(*(SBFile *)0, *(SBPictureTGAHeader *)0);
}
