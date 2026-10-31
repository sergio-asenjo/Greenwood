// Anonymous cluster at 0x005f94cx (Hercules/MDA debug console).
// No __FILE__ or oracle evidence: class and method identity are unproven.

#include "SBNullstr.h"
#include <windows.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include "rh_005f7ff0.h"

int FUN_00579a20();

// Parked: the inlined string terminator store uses base length/index pointer SIB order natively.
// STUB: GAME 0x005f81d0
std::string FUN_005f81d0(long error)
{
    const char *text =
        // STRING: GAME 0x006bb170
        "Not a valid DX Errorcode!";
    switch (error)
    {
    case 0x80004001:
        text =
            // STRING: GAME 0x006bb15c
            "DxERR_UNSUPPORTED";
        break;
    case 0x8000000a:
        text =
            // STRING: GAME 0x006bb150
            "E_PENDING";
        break;
    case 0x80004002:
        text =
            // STRING: GAME 0x006bb13c
            "DxERR_NOINTERFACE";
        break;
    case 0x80040110:
        text =
            // STRING: GAME 0x006bb114
            "DSERR_NOAGGREGATION/DIERR_NOAGGREGATION";
        break;
    case 0x80004005:
        text =
            // STRING: GAME 0x006bb104
            "DxERR_GENERIC";
        break;
    case 0x80040154:
        text =
            // STRING: GAME 0x006bb0f0
            "DIERR_DEVICENOTREG";
        break;
    case 0x80040204:
        text =
            // STRING: GAME 0x006bb0dc
            "DIERR_HASEFFECTS";
        break;
    case 0x80040203:
        text =
            // STRING: GAME 0x006bb0c8
            "DIERR_NOTDOWNLOADED";
        break;
    case 0x80040202:
        text =
            // STRING: GAME 0x006bb0b8
            "DIERR_MOREDATA";
        break;
    case 0x80040201:
        text =
            // STRING: GAME 0x006bb0a4
            "DIERR_DEVICEFULL";
        break;
    case 0x800401f0:
        text =
            // STRING: GAME 0x006bb08c
            "DDERR_NOTINITIALIZED";
        break;
    case 0x80040205:
        text =
            // STRING: GAME 0x006bb070
            "DIERR_NOTEXCLUSIVEACQUIRED";
        break;
    case 0x80040207:
        text =
            // STRING: GAME 0x006bb05c
            "DIERR_NOTBUFFERED";
        break;
    case 0x80040206:
        text =
            // STRING: GAME 0x006bb044
            "DIERR_INCOMPLETEEFFECT";
        break;
    case 0x80040208:
        text =
            // STRING: GAME 0x006bb030
            "DIERR_EFFECTPLAYING";
        break;
    case 0x80070005:
        text =
            // STRING: GAME 0x006baff8
            "DIERR_HANDLEEXISTS/DIERR_OTHERAPPHASPRIO/DIERR_READONLY";
        break;
    case 0x80070002:
        text =
            // STRING: GAME 0x006bafd4
            "DIERR_NOTFOUND/DIERR_OBJECTNOTFOUND";
        break;
    case 0x8007000c:
        text =
            // STRING: GAME 0x006bafc0
            "DIERR_NOTACQUIRED";
        break;
    case 0x80070077:
        text =
            // STRING: GAME 0x006bafac
            "DIERR_BADDRIVERVER";
        break;
    case 0x80070057:
        text =
            // STRING: GAME 0x006baf98
            "DxERR_INVALIDPARAMS";
        break;
    case 0x8007001e:
        text =
            // STRING: GAME 0x006baf88
            "DIERR_INPUTLOST";
        break;
    case 0x80070015:
        text =
            // STRING: GAME 0x006baf70
            "DIERR_NOTINITIALIZED";
        break;
    case 0x8007000e:
        text =
            // STRING: GAME 0x006baf5c
            "DxERR_OUTOFMEMORY";
        break;
    case 0x800700aa:
        text =
            // STRING: GAME 0x006baf4c
            "DIERR_ACQUIRED";
        break;
    case 0x80070481:
        text =
            // STRING: GAME 0x006baf2c
            "DIERR_BETADIRECTINPUTVERSION";
        break;
    case 0x8007047e:
        text =
            // STRING: GAME 0x006baf10
            "DIERR_OLDDIRECTINPUTVERSION";
        break;
    case 0x800704df:
        text =
            // STRING: GAME 0x006baef4
            "DIERR_ALREADYINITIALIZED";
        break;
    case 0x8876000a:
        text =
            // STRING: GAME 0x006baed8
            "DDERR_CANNOTATTACHSURFACE";
        break;
    case 0x88760005:
        text =
            // STRING: GAME 0x006baebc
            "DDERR_ALREADYINITIALIZED";
        break;
    case 0x88760014:
        text =
            // STRING: GAME 0x006baea0
            "DDERR_CANNOTDETACHSURFACE";
        break;
    case 0x88760064:
        text =
            // STRING: GAME 0x006bae8c
            "DDERR_INVALIDCAPS";
        break;
    case 0x8876005f:
        text =
            // STRING: GAME 0x006bae70
            "DDERR_INCOMPATIBLEPRIMARY";
        break;
    case 0x8876005a:
        text =
            // STRING: GAME 0x006bae5c
            "DDERR_HEIGHTALIGN";
        break;
    case 0x88760037:
        text =
            // STRING: GAME 0x006bae4c
            "DDERR_EXCEPTION";
        break;
    case 0x88760028:
        text =
            // STRING: GAME 0x006bae34
            "DDERR_CURRENTLYNOTAVAIL";
        break;
    case 0x8876006e:
        text =
            // STRING: GAME 0x006bae1c
            "DDERR_INVALIDCLIPLIST";
        break;
    case 0x887600d7:
        text =
            // STRING: GAME 0x006bae08
            "DDERR_NOCOLORKEY";
        break;
    case 0x887600d4:
        text =
            // STRING: GAME 0x006badec
            "DDERR_NOCOOPERATIVELEVELSET";
        break;
    case 0x887600d2:
        text =
            // STRING: GAME 0x006badd8
            "DDERR_NOCOLORCONVHW";
        break;
    case 0x887600cd:
        text =
            // STRING: GAME 0x006badc4
            "DDERR_NOCLIPLIST";
        break;
    case 0x887600b4:
        text =
            // STRING: GAME 0x006badb4
            "DDERR_NOALPHAHW";
        break;
    case 0x887600aa:
        text =
            // STRING: GAME 0x006bada8
            "DDERR_NO3D";
        break;
    case 0x887600a0:
        text =
            // STRING: GAME 0x006bad90
            "DDERR_LOCKEDSURFACES";
        break;
    case 0x88760096:
        text =
            // STRING: GAME 0x006bad7c
            "DDERR_INVALIDRECT";
        break;
    case 0x88760091:
        text =
            // STRING: GAME 0x006bad60
            "DDERR_INVALIDPIXELFORMAT";
        break;
    case 0x88760082:
        text =
            // STRING: GAME 0x006bad4c
            "DDERR_INVALIDOBJECT";
        break;
    case 0x88760078:
        text =
            // STRING: GAME 0x006bad38
            "DDERR_INVALIDMODE";
        break;
    case 0x887600dc:
        text =
            // STRING: GAME 0x006bad24
            "DDERR_NOCOLORKEYHW";
        break;
    case 0x88760190:
        text =
            // STRING: GAME 0x006bad0c
            "DDERR_COLORKEYNOTSET";
        break;
    case 0x88760183:
        text =
            // STRING: GAME 0x006bacf8
            "DDERR_PALETTEBUSY";
        break;
    case 0x88760180:
        text =
            // STRING: GAME 0x006bacd4
            "DDERR_OVERLAYCOLORKEYONLYONEACTIVE";
        break;
    case 0x8876017e:
        text =
            // STRING: GAME 0x006bacbc
            "DDERR_OVERLAYCANTCLIP";
        break;
    case 0x8876017c:
        text =
            // STRING: GAME 0x006baca4
            "DDERR_OUTOFVIDEOMEMORY";
        break;
    case 0x88760168:
        text =
            // STRING: GAME 0x006bac94
            "DDERR_OUTOFCAPS";
        break;
    case 0x8876015e:
        text =
            // STRING: GAME 0x006bac80
            "DDERR_NOZOVERLAYHW";
        break;
    case 0x88760154:
        text =
            // STRING: GAME 0x006bac6c
            "DDERR_NOZBUFFERHW";
        break;
    case 0x8876014f:
        text =
            // STRING: GAME 0x006bac5c
            "DDERR_NOVSYNCHW";
        break;
    case 0x8876014a:
        text =
            // STRING: GAME 0x006bac48
            "DDERR_NOTEXTUREHW";
        break;
    case 0x88760140:
        text =
            // STRING: GAME 0x006bac34
            "DDERR_NOT8BITCOLOR";
        break;
    case 0x8876013d:
        text =
            // STRING: GAME 0x006bac1c
            "DDERR_NOT4BITCOLORINDEX";
        break;
    case 0x8876013c:
        text =
            // STRING: GAME 0x006bac08
            "DDERR_NOT4BITCOLOR";
        break;
    case 0x88760136:
        text =
            // STRING: GAME 0x006babf4
            "DDERR_NOSTRETCHHW";
        break;
    case 0x88760122:
        text =
            // STRING: GAME 0x006babe0
            "DDERR_NOROTATIONHW";
        break;
    case 0x88760118:
        text =
            // STRING: GAME 0x006babcc
            "DDERR_NORASTEROPHW";
        break;
    case 0x88760104:
        text =
            // STRING: GAME 0x006babb8
            "DDERR_NOOVERLAYHW";
        break;
    case 0x887600ff:
        text =
            // STRING: GAME 0x006baba8
            "DDERR_NOTFOUND";
        break;
    case 0x887600fa:
        text =
            // STRING: GAME 0x006bab94
            "DDERR_NOMIRRORHW";
        break;
    case 0x887600f0:
        text =
            // STRING: GAME 0x006bab88
            "DDERR_NOGDI";
        break;
    case 0x887600e6:
        text =
            // STRING: GAME 0x006bab78
            "DDERR_NOFLIPHW";
        break;
    case 0x887600e1:
        text =
            // STRING: GAME 0x006bab60
            "DDERR_NOEXCLUSIVEMODE";
        break;
    case 0x887600de:
        text =
            // STRING: GAME 0x006bab44
            "DDERR_NODIRECTDRAWSUPPORT";
        break;
    case 0x8876019a:
        text =
            // STRING: GAME 0x006bab24
            "DDERR_SURFACEALREADYATTACHED";
        break;
    case 0x88760239:
        text =
            // STRING: GAME 0x006bab14
            "DDERR_NOHWND";
        break;
    case 0x88760238:
        text =
            // STRING: GAME 0x006baafc
            "DDERR_NOCLIPPERATTACHED";
        break;
    case 0x88760237:
        text =
            // STRING: GAME 0x006baae0
            "DDERR_CLIPPERISUSINGHWND";
        break;
    case 0x88760236:
        text =
            // STRING: GAME 0x006baac8
            "DDERR_REGIONTOOSMALL";
        break;
    case 0x88760235:
        text =
            // STRING: GAME 0x006baab4
            "DDERR_NOEMULATION";
        break;
    case 0x88760234:
        text =
            // STRING: GAME 0x006baa90
            "DDERR_PRIMARYSURFACEALREADYEXISTS";
        break;
    case 0x88760233:
        text =
            // STRING: GAME 0x006baa78
            "DDERR_NODIRECTDRAWHW";
        break;
    case 0x88760232:
        text =
            // STRING: GAME 0x006baa58
            "DDERR_DIRECTDRAWALREADYCREATED";
        break;
    case 0x88760231:
        text =
            // STRING: GAME 0x006baa3c
            "DDERR_INVALIDDIRECTDRAWGUID";
        break;
    case 0x88760230:
        text =
            // STRING: GAME 0x006baa2c
            "DDERR_XALIGN";
        break;
    case 0x8876021c:
        text =
            // STRING: GAME 0x006baa14
            "DDERR_WASSTILLDRAWING";
        break;
    case 0x88760219:
        text =
            // STRING: GAME 0x006ba9f4
            "DDERR_VERTICALBLANKINPROGRESS";
        break;
    case 0x88760208:
        text =
            // STRING: GAME 0x006ba9dc
            "DDERR_UNSUPPORTEDMASK";
        break;
    case 0x887601fe:
        text =
            // STRING: GAME 0x006ba9c4
            "DDERR_UNSUPPORTEDFORMAT";
        break;
    case 0x887601ea:
        text =
            // STRING: GAME 0x006ba9b0
            "DDERR_TOOBIGWIDTH";
        break;
    case 0x887601e0:
        text =
            // STRING: GAME 0x006ba99c
            "DDERR_TOOBIGSIZE";
        break;
    case 0x887601d6:
        text =
            // STRING: GAME 0x006ba988
            "DDERR_TOOBIGHEIGHT";
        break;
    case 0x887601cc:
        text =
            // STRING: GAME 0x006ba96c
            "DDERR_SURFACENOTATTACHED";
        break;
    case 0x887601c2:
        text =
            // STRING: GAME 0x006ba958
            "DDERR_SURFACELOST";
        break;
    case 0x887601b8:
        text =
            // STRING: GAME 0x006ba940
            "DDERR_SURFACEISOBSCURED";
        break;
    case 0x887601b3:
        text =
            // STRING: GAME 0x006ba928
            "DDERR_CANTLOCKSURFACE";
        break;
    case 0x887601ae:
        text =
            // STRING: GAME 0x006ba914
            "DDERR_SURFACEBUSY";
        break;
    case 0x887601a4:
        text =
            // STRING: GAME 0x006ba8f4
            "DDERR_SURFACEALREADYDEPENDENT";
        break;
    case 0x8876023a:
        text =
            // STRING: GAME 0x006ba8dc
            "DDERR_HWNDSUBCLASSED";
        break;
    case 0x8876026c:
        text =
            // STRING: GAME 0x006ba8c4
            "DDERR_DCALREADYCREATED";
        break;
    case 0x88760259:
        text =
            // STRING: GAME 0x006ba8b4
            "DDERR_NOTLOADED";
        break;
    case 0x88760258:
        text =
            // STRING: GAME 0x006ba8a0
            "DDERR_NOOPTIMIZEHW";
        break;
    case 0x88760250:
        text =
            // STRING: GAME 0x006ba884
            "DDERR_INVALIDSURFACETYPE";
        break;
    case 0x8876024f:
        text =
            // STRING: GAME 0x006ba870
            "DDERR_NOMIPMAPHW";
        break;
    case 0x8876024e:
        text =
            // STRING: GAME 0x006ba858
            "DDERR_UNSUPPORTEDMODE";
        break;
    case 0x8876024d:
        text =
            // STRING: GAME 0x006ba844
            "DDERR_NOTPALETTIZED";
        break;
    case 0x8876024c:
        text =
            // STRING: GAME 0x006ba82c
            "DDERR_IMPLICITLYCREATED";
        break;
    case 0x8876024b:
        text =
            // STRING: GAME 0x006ba81c
            "DDERR_WRONGMODE";
        break;
    case 0x8876024a:
        text =
            // STRING: GAME 0x006ba810
            "DDERR_NODC";
        break;
    case 0x88760249:
        text =
            // STRING: GAME 0x006ba7fc
            "DDERR_CANTCREATEDC";
        break;
    case 0x88760248:
        text =
            // STRING: GAME 0x006ba7ec
            "DDERR_NOTLOCKED";
        break;
    case 0x88760247:
        text =
            // STRING: GAME 0x006ba7d8
            "DDERR_CANTDUPLICATE";
        break;
    case 0x88760246:
        text =
            // STRING: GAME 0x006ba7c4
            "DDERR_NOTFLIPPABLE";
        break;
    case 0x88760245:
        text =
            // STRING: GAME 0x006ba7a4
            "DDERR_EXCLUSIVEMODEALREADYSET";
        break;
    case 0x88760244:
        text =
            // STRING: GAME 0x006ba788
            "DDERR_NOTAOVERLAYSURFACE";
        break;
    case 0x88760243:
        text =
            // STRING: GAME 0x006ba770
            "DDERR_INVALIDPOSITION";
        break;
    case 0x88760242:
        text =
            // STRING: GAME 0x006ba75c
            "DDERR_NOOVERLAYDEST";
        break;
    case 0x88760241:
        text =
            // STRING: GAME 0x006ba744
            "DDERR_OVERLAYNOTVISIBLE";
        break;
    case 0x88760240:
        text =
            // STRING: GAME 0x006ba730
            "DDERR_NODDROPSHW";
        break;
    case 0x8876023f:
        text =
            // STRING: GAME 0x006ba720
            "DDERR_NOBLTHW";
        break;
    case 0x8876023e:
        text =
            // STRING: GAME 0x006ba708
            "DDERR_BLTFASTCANTCLIP";
        break;
    case 0x8876023d:
        text =
            // STRING: GAME 0x006ba6f4
            "DDERR_NOPALETTEHW";
        break;
    case 0x8876023c:
        text =
            // STRING: GAME 0x006ba6dc
            "DDERR_NOPALETTEATTACHED";
        break;
    case 0x8876023b:
        text =
            // STRING: GAME 0x006ba6c4
            "DDERR_HWNDALREADYSET";
        break;
    case 0x88760276:
        text =
            // STRING: GAME 0x006ba6ac
            "DDERR_NONONLOCALVIDMEM";
        break;
    case 0x887602b2:
        text =
            // STRING: GAME 0x006ba69c
            "DDERR_MOREDATA";
        break;
    case 0x887602a8:
        text =
            // STRING: GAME 0x006ba688
            "DDERR_NOTPAGELOCKED";
        break;
    case 0x88760294:
        text =
            // STRING: GAME 0x006ba670
            "DDERR_CANTPAGEUNLOCK";
        break;
    case 0x88760280:
        text =
            // STRING: GAME 0x006ba65c
            "DDERR_CANTPAGELOCK";
        break;
    case 0x887602b7:
        text =
            // STRING: GAME 0x006ba644
            "DDERR_VIDEONOTACTIVE";
        break;
    case 0x8877000a:
        text =
            // STRING: GAME 0x006ba630
            "DPERR_ACCESSDENIED";
        break;
    case 0x88770005:
        text =
            // STRING: GAME 0x006ba614
            "DPERR_ALREADYINITIALIZED";
        break;
    case 0x887602bb:
        text =
            // STRING: GAME 0x006ba5f4
            "DDERR_DEVICEDOESNTOWNSURFACE";
        break;
    case 0x88770014:
        text =
            // STRING: GAME 0x006ba5e0
            "DPERR_ACTIVEPLAYERS";
        break;
    case 0x88770078:
        text =
            // STRING: GAME 0x006ba5cc
            "DPERR_INVALIDFLAGS";
        break;
    case 0x8877005a:
        text =
            // STRING: GAME 0x006ba5bc
            "DPERR_EXCEPTION";
        break;
    case 0x88770050:
        text =
            // STRING: GAME 0x006ba5a0
            "DPERR_CAPSNOTAVAILABLEYET";
        break;
    case 0x88770046:
        text =
            // STRING: GAME 0x006ba588
            "DPERR_CANTCREATESESSION";
        break;
    case 0x8877003c:
        text =
            // STRING: GAME 0x006ba570
            "DPERR_CANTCREATEPLAYER";
        break;
    case 0x88770032:
        text =
            // STRING: GAME 0x006ba558
            "DPERR_CANTCREATEGROUP";
        break;
    case 0x88770028:
        text =
            // STRING: GAME 0x006ba544
            "DPERR_CANTADDPLAYER";
        break;
    case 0x8877001e:
        text =
            // STRING: GAME 0x006ba52c
            "DPERR_BUFFERTOOSMALL";
        break;
    case 0x88770082:
        text =
            // STRING: GAME 0x006ba518
            "DPERR_INVALIDOBJECT";
        break;
    case 0x88770140:
        text =
            // STRING: GAME 0x006ba504
            "DPERR_UNINITIALIZED";
        break;
    case 0x88770136:
        text =
            // STRING: GAME 0x006ba4f0
            "DPERR_SESSIONLOST";
        break;
    case 0x8877012c:
        text =
            // STRING: GAME 0x006ba4dc
            "DPERR_PLAYERLOST";
        break;
    case 0x88770118:
        text =
            // STRING: GAME 0x006ba4c8
            "DPERR_USERCANCEL";
        break;
    case 0x8877010e:
        text =
            // STRING: GAME 0x006ba4bc
            "DPERR_BUSY";
        break;
    case 0x887700fa:
        text =
            // STRING: GAME 0x006ba4a8
            "DPERR_UNAVAILABLE";
        break;
    case 0x887700f0:
        text =
            // STRING: GAME 0x006ba498
            "DPERR_TIMEOUT";
        break;
    case 0x887700e6:
        text =
            // STRING: GAME 0x006ba484
            "DPERR_SENDTOOBIG";
        break;
    case 0x887700dc:
        text =
            // STRING: GAME 0x006ba470
            "DPERR_NOSESSIONS";
        break;
    case 0x887700d2:
        text =
            // STRING: GAME 0x006ba460
            "DPERR_NOPLAYERS";
        break;
    case 0x887700c8:
        text =
            // STRING: GAME 0x006ba448
            "DPERR_NONAMESERVERFOUND";
        break;
    case 0x887700be:
        text =
            // STRING: GAME 0x006ba434
            "DPERR_NOMESSAGES";
        break;
    case 0x887700aa:
        text =
            // STRING: GAME 0x006ba420
            "DPERR_NOCONNECTION";
        break;
    case 0x887700a0:
        text =
            // STRING: GAME 0x006ba410
            "DPERR_NOCAPS";
        break;
    case 0x8877009b:
        text =
            // STRING: GAME 0x006ba3fc
            "DPERR_INVALIDGROUP";
        break;
    case 0x88770096:
        text =
            // STRING: GAME 0x006ba3e8
            "DPERR_INVALIDPLAYER";
        break;
    case 0x8877014a:
        text =
            // STRING: GAME 0x006ba3d4
            "DPERR_NONEWPLAYERS";
        break;
    case 0x8877015e:
        text =
            // STRING: GAME 0x006ba3c0
            "DPERR_CONNECTING";
        break;
    case 0x88770154:
        text =
            // STRING: GAME 0x006ba3a8
            "DPERR_INVALIDPASSWORD";
        break;
    case 0x887703e8:
        text =
            // STRING: GAME 0x006ba390
            "DPERR_BUFFERTOOLARGE";
        break;
    case 0x887703f2:
        text =
            // STRING: GAME 0x006ba378
            "DPERR_CANTCREATEPROCESS";
        break;
    case 0x887703fc:
        text =
            // STRING: GAME 0x006ba364
            "DPERR_APPNOTSTARTED";
        break;
    case 0x8877042e:
        text =
            // STRING: GAME 0x006ba350
            "DPERR_NOTLOBBIED";
        break;
    case 0x8877041a:
        text =
            // STRING: GAME 0x006ba334
            "DPERR_UNKNOWNAPPLICATION";
        break;
    case 0x88770406:
        text =
            // STRING: GAME 0x006ba31c
            "DPERR_INVALIDINTERFACE";
        break;
    case 0x887707d0:
        text =
            // STRING: GAME 0x006ba300
            "DPERR_AUTHENTICATIONFAILED";
        break;
    case 0x88770820:
        text =
            // STRING: GAME 0x006ba2ec
            "DPERR_LOGONDENIED";
        break;
    case 0x88770816:
        text =
            // STRING: GAME 0x006ba2d8
            "DPERR_NOTLOGGEDIN";
        break;
    case 0x8877080c:
        text =
            // STRING: GAME 0x006ba2c4
            "DPERR_CANTLOADCAPI";
        break;
    case 0x887707f8:
        text =
            // STRING: GAME 0x006ba2a4
            "DPERR_CANTLOADSECURITYPACKAGE";
        break;
    case 0x887707ee:
        text =
            // STRING: GAME 0x006ba290
            "DPERR_SIGNFAILED";
        break;
    case 0x887707e4:
        text =
            // STRING: GAME 0x006ba278
            "DPERR_ENCRYPTIONFAILED";
        break;
    case 0x887707da:
        text =
            // STRING: GAME 0x006ba264
            "DPERR_CANTLOADSSPI";
        break;
    case 0x8878000a:
        text =
            // STRING: GAME 0x006ba254
            "DSERR_ALLOCATED";
        break;
    case 0x887800a0:
        text =
            // STRING: GAME 0x006ba23c
            "DSERR_OTHERAPPHASPRIO";
        break;
    case 0x88780096:
        text =
            // STRING: GAME 0x006ba228
            "DSERR_BUFFERLOST";
        break;
    case 0x88780082:
        text =
            // STRING: GAME 0x006ba20c
            "DSERR_ALREADYINITIALIZED";
        break;
    case 0x88780078:
        text =
            // STRING: GAME 0x006ba1fc
            "DSERR_NODRIVER";
        break;
    case 0x88780064:
        text =
            // STRING: GAME 0x006ba1ec
            "DSERR_BADFORMAT";
        break;
    case 0x88780046:
        text =
            // STRING: GAME 0x006ba1d4
            "DSERR_PRIOLEVELNEEDED";
        break;
    case 0x88780032:
        text =
            // STRING: GAME 0x006ba1c0
            "DSERR_INVALIDCALL";
        break;
    case 0x8878001e:
        text =
            // STRING: GAME 0x006ba1a8
            "DSERR_CONTROLUNAVAIL";
        break;
    case 0x887800aa:
        text =
            // STRING: GAME 0x006ba194
            "DSERR_UNINITIALIZED";
        break;
    case 0x0000000c:
        text =
            // STRING: GAME 0x006ba178
            "DI_TRUNCATEDANDRESTARTED";
        break;
    case 0x00000008:
        text =
            // STRING: GAME 0x006ba168
            "DI_TRUNCATED";
        break;
    case 0x00000004:
        text =
            // STRING: GAME 0x006ba154
            "DI_EFFECTRESTARTED";
        break;
    case 0x00000003:
        text =
            // STRING: GAME 0x006ba140
            "DI_DOWNLOADSKIPPED";
        break;
    case 0x00000002:
        text =
            // STRING: GAME 0x006ba130
            "DI_POLLEDDEVICE";
        break;
    case 0x00000001:
        text =
            // STRING: GAME 0x006ba0f0
            "DI_BUFFEROVERFLOW/DI_NOEFFECT/DI_NOTATTACHED/DI_PROPNOEFFECT";
        break;
    case 0x00000000:
        text =
            // STRING: GAME 0x006ba0e8
            "Dx_OK";
        break;
    }
    return text;
}

class RHUnk005f94c0
{
public:
    RHUnk005f94c0();
    void FUN_005f94f0();
    unsigned char m_0;
    unsigned char m_1[3];
    int m_4;
};

// FUNCTION: GAME 0x005f94c0
RHUnk005f94c0::RHUnk005f94c0()
{
    m_0 = ((int (*)(const char *))FUN_00579a20)(
              // STRING: GAME 0x006bb18c
              "enable_hercules") != 0;
    FUN_005f94f0();
}

// FUNCTION: GAME 0x005f94f0
void RHUnk005f94c0::FUN_005f94f0()
{
    if (m_0)
    {
        m_4 = 0;
        unsigned int *screen = (unsigned int *)0xb0000;
        for (int i = 0; i < 1000; ++i)
            screen[i] = 0x07000700;
    }
}

struct RHUnk005f94c0Cells
{
    unsigned short m_cells[9];
};

// GLOBAL: GAME 0x006c1418
bool g_unk0x006c1418;

// FUNCTION: GAME 0x005f9510
void SBSimpleUnk005f9510(void *console, const char *format, ...)
{
    char text[0xa00];
    va_list arguments;
    va_start(arguments, format);
    vsprintf(text, format, arguments);
    RHUnk005f94c0 *self = (RHUnk005f94c0 *)console;
    if (self->m_0)
    {
        if (!g_unk0x006c1418)
        {
            g_unk0x006c1418 = true;
            self->FUN_005f94f0();
        }
        if (strlen(text) / 80 + self->m_4 + 1 > 25)
        {
            RHUnk005f94c0Cells saved = *(RHUnk005f94c0Cells *)0xb0090;
            memmove((void *)0xb0000,
                (char *)0xb0000 + (strlen(text) / 80 + self->m_4 + 1 - 25) * 160,
                4000 - (strlen(text) / 80 + self->m_4 + 1 - 25) * 160);
            *(RHUnk005f94c0Cells *)0xb0090 = saved;
            self->m_4 = 24 - strlen(text) / 80;
        }
        unsigned short *line = (unsigned short *)(0xb0000 + self->m_4 * 160);
        memset(line, 0, (strlen(text) / 80 + 1) * 160);
        if (self->m_4 == 0)
        {
            for (int i = 71; i < 80; ++i)
                line[i] = 0x0700;
            *(char *)0xb0096 = ':';
        }
        for (int i = 0; text[i]; ++i)
            *line++ = text[i] + 0x700;
        self->m_4 += strlen(text) / 80 + 1;
    }
    strcat(text, "\n");
    g_unk0x006c1400.FUN_005f7ff0(text);
    OutputDebugStringA(text);
}

class RHUnk005f9760
{
public:
    bool FUN_005f97f0(FILE *file, unsigned long start, unsigned long kind, unsigned long end,
        int flags, HANDLE process, const char *name, const void *context);
    unsigned long m_0;
    unsigned long m_4;
};

// GLOBAL: GAME 0x006c13b8
unsigned long g_unk0x006c13b8;

// GLOBAL: GAME 0x006c13d0
unsigned long g_unk0x006c13d0[6];

// GLOBAL: GAME 0x006c1408
unsigned long g_unk0x006c1408;

// FUNCTION: GAME 0x005f97f0
bool RHUnk005f9760::FUN_005f97f0(FILE *file, unsigned long start, unsigned long kind, unsigned long end,
    int flags, HANDLE process, const char *name, const void *context)
{
    if (context)
        memcpy(g_unk0x006c13d0, context, sizeof(g_unk0x006c13d0));
    else
        memset(g_unk0x006c13d0, 0, sizeof(g_unk0x006c13d0));
    unsigned long base = start;
    g_unk0x006c13b8 = kind;
    if (end)
        m_0 = end;
    if (name)
        g_unk0x006c1408 = strlen(name);
    unsigned long size = m_0 - base;
    if (fwrite(&base, 4, 1, file) < 1)
        return false;
    if (fwrite(&g_unk0x006c13b8, 4, 1, file) < 1)
        return false;
    if (fwrite(&size, 4, 1, file) < 1)
        return false;
    if (fwrite(&flags, 4, 1, file) < 1)
        return false;
    if (fwrite(g_unk0x006c13d0, 4, 6, file) < 1)
        return false;
    if (fwrite(&g_unk0x006c1408, 4, 1, file) < 1)
        return false;
    if (g_unk0x006c1408 && fwrite(name, g_unk0x006c1408 + 1, 1, file) < 1)
        return false;
    if (process)
    {
        void *buffer = operator new(size);
        ReadProcessMemory(process, (const void *)base, buffer, size, 0);
        if (fwrite(buffer, 1, size, file) < size)
            return false;
        operator delete(buffer);
    }
    else if (fwrite((const void *)base, 1, size, file) < size)
        return false;
    return true;
}

void EmitRHUnk005f9760(RHUnk005f9760 *dump)
{
    dump->FUN_005f97f0(0, 0, 0, 0, 0, 0, 0, 0);
}
