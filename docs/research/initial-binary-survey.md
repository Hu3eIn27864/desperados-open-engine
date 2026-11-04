# Initial binary survey (user-provided observations)

**Status:** preliminary, static metadata only  
**Date recorded:** 2026-11-04  
**Environment:** Termux on Android; GNU binutils and Info-ZIP  
**Scope:** observations reported from a locally owned game installation. No original executable, DLL, asset, disassembly dump, or decompiler output is included in this repository.

## Clean-room handling

This document records independently written factual observations and tool results. It does not reproduce machine code, decompiler pseudocode, executable resources, or other game content. Original files remain on the user's device. Future implementation work must be based on separately written specifications and tests, not copied or adapted original code.

## Container observation: `Game.pac`

The user reported the following results:

- `file Game.pac`: identified as ZIP archive data, made by ZIP version 2.5, extract version 2.0, Deflate compression.
- `unzip -t Game.pac`: all three entries tested successfully; no compressed-data errors reported.
- `unzip -l Game.pac`: three entries:

| Entry | Uncompressed size | Timestamp |
|---|---:|---|
| `binkw32.dll` | 285,696 bytes | 2000-09-11 07:46 |
| `fmod.dll` | 116,224 bytes | 2001-01-09 23:08 |
| `game.exe` | 2,707,456 bytes | 2001-06-12 12:18 |

The archive's reported SHA-256 is:

```text
908b7ac00d18f97735d2752a3946db31d1b7bc49d1739a65ba8ee44e1cfe7c67
```

This is evidence for this particular archive only. It does not establish that every `.pac` file used by the game is ZIP-compatible. Additional samples and structural tests are required before specifying a general PAC reader.

## Executable observation: `game.exe`

The user reported:

- `file game.exe`: PE32 executable for Windows (GUI), Intel i386, four sections.
- `objdump -f game.exe`: COFF-i386; architecture `i386`; reported start address `0x002217be`.

Section table reported by `objdump -h`:

| Section | Size | VMA | Reported type |
|---|---:|---:|---|
| `.text` | `0x00251769` | `0x00401000` | TEXT |
| `.rdata` | `0x00028488` | `0x00653000` | DATA |
| `.data` | `0x00017000` | `0x0067c000` | DATA |
| `.rsrc` | `0x00001f90` | `0x00697000` | DATA |

Imported DLL names reported by `objdump -p`:

- `KERNEL32.dll`
- `USER32.dll`
- `ADVAPI32.dll`
- `ole32.dll`
- `OLEAUT32.dll`
- `binkw32.dll`
- `DSOUND.dll`
- `fmod.dll`
- `AVIFIL32.dll`
- `GDI32.dll`
- `DDRAW.dll`
- `DINPUT.dll`
- `WINMM.dll`

The reported Bink import names include `BinkNextFrame`, `BinkCopyToBuffer`, `BinkOpen`, `BinkDoFrame`, `BinkSetSoundSystem`, `BinkOpenDirectSound`, `BinkGetError`, `BinkClose`, and `BinkWait`. These imports indicate a Bink integration; they do not by themselves establish the full video playback path or how the game invokes it.

The presence of `fmod.dll` and `DSOUND.dll` among imports is evidence of audio-related dependencies, but the exact division of responsibilities still needs investigation.

## Interpretation and confidence

- **High confidence:** the inspected `game.exe` is a 32-bit x86 Windows PE executable, based on the reported `file` and `objdump` output.
- **High confidence:** this particular `Game.pac` archive is readable by Info-ZIP and contains the three listed entries.
- **Medium confidence:** the imported libraries indicate dependencies on legacy Windows graphics, input, sound, video, and system APIs. Import presence alone does not prove which code paths are used at runtime.
- **Not yet established:** whether all game data uses ZIP containers, whether other archives use extensions or custom headers, the engine's internal subsystem boundaries, or any gameplay algorithms.

## Next reproducible analysis steps

Run locally and share only the resulting factual summaries, not full disassembly dumps:

```sh
cd ~/desperados-analysis/extracted_game
objdump -p game.exe
objdump -h game.exe
strings -a -n 6 -t x game.exe > ../game_strings_ascii.txt
strings -a -el -n 5 -t x game.exe > ../game_strings_utf16le.txt
objdump -t game.exe | head -100
```

The first 100 lines of the earlier `strings -a` output mostly contained instruction-like byte sequences and section labels. That is not evidence of meaningful game strings; the offset-tagged ASCII and UTF-16LE passes should be reviewed and filtered before drawing conclusions.

For the next stage, document candidate file signatures and archive layouts using synthetic test data. Do not add original game files, extracted DLLs, asset data, raw disassembly, or wholesale decompiler output to this repository.
