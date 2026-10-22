<img src=".github/assets/greenwood-banner.png" alt="Greenwood, a matching decompilation of Robin Hood: The Legend of Sherwood" width="100%">

## Status

<img src=".github/assets/progress.svg" alt="Matching progress: 3,530 of 6,113 game functions decompiled" width="100%">

## About

Greenwood aims to fully decompile **Robin Hood: The Legend of Sherwood** (2002, Spellbound Entertainment), targeting **v1.1**. The goal is C++ source that compiles with **Microsoft Visual C++ 6.0 SP6** into byte-identical machine code, not a replacement engine or port.

## Credits

- [reccmp](https://github.com/isledecomp/reccmp) - compiled-function comparison and matching progress.
- [Ghidra](https://github.com/NationalSecurityAgency/ghidra) - disassembly and decompilation.
- [radare2](https://github.com/radareorg/radare2) - binary inspection and analysis.
- [Wine](https://www.winehq.org/) - running the original Windows compiler on Linux.
- [MSVC600](https://github.com/itsmattkc/MSVC600) - portable Visual C++ 6.0 toolchain.
- [objdiff](https://github.com/encounter/objdiff) - secondary compiled-code comparison.

## Third-party libraries

`Game.exe` statically links two open-source libraries. Both are vendored from upstream under `src/thirdparty/`, kept byte-for-byte with their licenses, and excluded from the progress above.

- [bzip2](https://sourceware.org/bzip2/) 1.0.1 (BSD-like) - `src/thirdparty/bzip2/`
- [zlib](https://zlib.net/) 1.1.3 (zlib license) - `src/thirdparty/zlib/`

The game also embeds a game-adapted MD5 derived from Mordechai T. Abzug's 1995 translation of the RSA Data Security MD5 algorithm. It is reconstructed, not vendored.
