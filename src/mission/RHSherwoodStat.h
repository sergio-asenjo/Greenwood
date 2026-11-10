#ifndef RHSHERWOODSTAT_H
#define RHSHERWOODSTAT_H

#include <string>

class RHSectorProduction;

// VTABLE: GAME 0x00679bf0
class RHSherwoodStat
{
public:
    virtual std::wstring GetText() const;
    static std::wstring GetAmmoText(const RHSectorProduction *sector);
    static void GetProductionText(const RHSectorProduction *sector, std::wstring &text);
    static void GetScoreText(std::wstring &text);
    static void GetTrainHealText(const RHSectorProduction *sector, std::wstring &text);
};

#endif
