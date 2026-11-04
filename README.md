# Desperados Open Engine

A clean-room, cross-platform reimplementation of the runtime for *Desperados: Wanted Dead or Alive*.

## Project status

**Early foundation and research stage.** The long-term goal is to replace the original executable while loading game data from a legally obtained local installation. This repository does not currently provide a playable game and does not claim compatibility with original missions.

The project has a working C++20/CMake foundation, a bounds-checked binary reader, unit tests and cross-platform core CI. Initial architecture and clean-room documentation are in place. High-level research notes have also been recorded for world data, navigation, NPC AI, scripting, audio and savegames.

The original executable has been examined locally to identify broad subsystem boundaries and implementation clues. This is research, not a completed reimplementation: resource parsers, rendering, world simulation, AI and gameplay are still largely unimplemented.

### Current implementation status

| Area | Status |
|---|---|
| C++20 / CMake foundation | Implemented |
| BinaryReader and core unit tests | Implemented |
| Core CI on Windows, Linux and macOS | Implemented |
| SDL3 desktop shell | Minimal shell; full platform verification remains |
| Architecture and clean-room process | Documented |
| Initial technical research notes | Documented |
| Installation detection and resource inventory | Not implemented |
| Game resource parsers | Not implemented |
| Isometric renderer and world representation | Not implemented |
| NPC AI, scripting and gameplay | Not implemented |
| Audio and save/load compatibility | Not implemented |

## Roadmap

The detailed checklist lives in [Development milestones](docs/roadmap/MILESTONES.md). The high-level sequence is:

| Milestone | Goal | Main deliverable |
|---|---|---|
| **M0 — Foundation** | Build and test infrastructure | C++20 core, BinaryReader, CI and minimal SDL3 shell |
| **M1 — Installation and resource inventory** | Discover a user-supplied installation safely | Configurable path, validation and read-only file inventory with sizes and hashes |
| **M2 — Compatibility foundation** | Understand and parse selected resource formats | Parser result/error model, independently implemented parsers, synthetic fixtures and malformed-input tests |
| **M3 — Diagnostic viewer** | Inspect supported resources and establish the visual coordinate system | Resource inspection CLI, texture diagnostics and an isometric camera prototype |
| **M4 — Playable vertical slice** | Make a small part of the runtime interactive | World representation, collision queries, entity movement, animation, selection and basic interaction |
| **M5 — Runtime compatibility** | Implement the systems needed for broader mission support | AI, scripting, mission flow, audio, save/load and compatibility tests |
| **M6 — Modern release** | Package and document a usable cross-platform runtime | Windows, Linux and macOS packaging, compatibility matrix and optional modern usability improvements |

### Immediate development plan

The next practical steps are deliberately focused on turning research into working software:

1. **Resource manager and installation inventory:** accept a user-configured installation directory, validate it read-only, and list relative paths, file sizes and hashes.
2. **First resource container/parser:** investigate a selected format and implement an independent parser, initially tested against synthetic fixtures and malformed inputs.
3. **SDL3 rendering prototype:** establish an isometric coordinate system, camera and basic diagnostic drawing.
4. **Connect data to presentation:** display a supported resource in the prototype when its format is sufficiently understood.

These are development targets, not promised delivery dates. Original game data must remain local and must never be committed to this repository.

## Estimated project duration

The following are **rough planning estimates for one developer working consistently**, not deadlines or guarantees. Actual calendar time depends heavily on weekly availability, prior experience, the complexity of undocumented formats and the level of compatibility expected.

| Target | Indicative effort |
|---|---:|
| Technical prototype: window, build pipeline and file inventory | 2–6 weeks |
| First real resources parsed and displayed | 2–4 months |
| First walkable isometric scene | 4–8 months |
| First playable mission slice with movement and interaction | 8–15 months |
| Broader gameplay systems | 1.5–3 years |
| Extensive compatibility with the original game | 3–5+ years |

Part-time development can take substantially longer—potentially two to three times these calendar estimates. Unknown formats or complex mission scripting may also extend the schedule. A complete replacement runtime is a multi-year project; compatibility claims will only be made when supported by tests.

## Principles

- Independent clean-room implementation; no copied or adapted third-party engine code.
- Original game executables and assets are not distributed here.
- C++20, SDL3 and CMake 3.25+.
- Target platforms: Windows, Linux and macOS.
- No map or mission editor is planned.
- Apache-2.0 applies only to original project code and documentation.

## Build the core tests

Requirements: CMake 3.25+, a C++20 compiler and (optionally) Ninja.

```sh
cmake -S . -B build -DDOE_BUILD_GAME=OFF -DDOE_BUILD_TESTS=ON
cmake --build build --config Debug
ctest --test-dir build -C Debug --output-on-failure
```

The core test target does not require SDL3.

## Build the desktop shell

Install SDL3 with its CMake package configuration available, then configure:

```sh
cmake -S . -B build-desktop -DDOE_BUILD_GAME=ON -DDOE_BUILD_TESTS=ON
cmake --build build-desktop --config Debug
```

The desktop target currently provides only a minimal SDL3 window/event loop.

## Architecture and development

- [Architecture overview](docs/architecture/overview.md)
- [Clean-room process](docs/clean-room/PROCESS.md)
- [Detailed development milestones](docs/roadmap/MILESTONES.md)
- [Subsystem string observations](docs/research/subsystem-string-observations.md)
- [Audio and savegame observations](docs/research/audio-and-savegame-observations.md)

The first implementation component is a bounds-checked little-endian BinaryReader. Parsers will produce validated, engine-owned structures; gameplay code should not depend on binary offsets. Parsers are to be independently implemented and tested with synthetic fixtures.

## Game data and legal notice

Users must provide their own legally obtained game installation. Do not upload or commit game executables, archives, maps, scripts, images, music, video, fonts, extracted assets or installation paths. The project license does not grant rights to the original game's content or trademarks. Interoperability and reverse-engineering rules vary by jurisdiction; consult qualified counsel for legal advice.
