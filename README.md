# Desperados Open Engine

A clean-room, cross-platform reimplementation of the runtime for *Desperados: Wanted Dead or Alive*.

## Status

Early foundation stage. The long-term goal is to replace the original executable while loading game data from a legally obtained local installation. This repository does not currently provide a playable game or claim compatibility with original missions.

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
- [Milestones](docs/roadmap/MILESTONES.md)

The first implementation component is a bounds-checked little-endian BinaryReader. Next priorities are filesystem access, read-only installation inventory and a resource catalog. Parsers will be independently implemented and tested with synthetic fixtures.

## Game data and legal notice

Users must provide their own legally obtained game installation. Do not upload or commit game executables, archives, maps, scripts, images, music, video, fonts, extracted assets or installation paths. The project license does not grant rights to the original game's content or trademarks. Interoperability and reverse-engineering rules vary by jurisdiction; consult qualified counsel for legal advice.
