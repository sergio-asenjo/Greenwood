#ifndef RHPLAYERPROFILEMANAGERSTORAGE_H
#define RHPLAYERPROFILEMANAGERSTORAGE_H

class RHPlayerProfileManager;

class RHPlayerProfileManagerStorage
{
public:
    static RHPlayerProfileManager mInstance;
};

#define g_unk0x006c0e48 ((unsigned char *)&RHPlayerProfileManagerStorage::mInstance)

#endif
