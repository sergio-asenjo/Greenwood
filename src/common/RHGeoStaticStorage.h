#ifndef RHGEOSTATICSTORAGE_H
#define RHGEOSTATICSTORAGE_H

class SBGeoVector2D;

class RHFastFindGridStaticStorage
{
public:
    static SBGeoVector2D mvGridsetDiagonal;
};

class RHInfoPopupStaticStorage
{
public:
    static SBGeoVector2D vPositionOffset;
};

#define g_unk0x006c0aa8 (&RHFastFindGridStaticStorage::mvGridsetDiagonal)
#define g_unk0x006c0bb0 (&RHInfoPopupStaticStorage::vPositionOffset)

#endif
