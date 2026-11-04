# Architecture overview

The engine uses one-way layers. Binary game data must not leak into gameplay:
parsers produce validated, engine-owned structures.

## Planned layers
1. **Application** — startup, configuration, command-line handling and shutdown.
2. **Platform** — SDL3 window, input, timing and platform integration.
3. **Core** — errors, logging, binary reading, filesystem abstractions and IDs.
4. **Resources** — install discovery, file providers, archives, resource catalog and caches.
5. **Compatibility** — read-only parsers for supported original data formats.
6. **Runtime** — world, geometry, navigation, entities, animation, AI, scripts, gameplay, UI, audio and savegames.
7. **Presentation** — renderer, camera, scaling and accessibility.

## Dependency rules
- Core has no dependency on SDL3 or game-specific formats.
- Compatibility may depend on Core and Resources, never on gameplay.
- Runtime consumes validated models, not raw byte offsets.
- Platform APIs stay behind narrow interfaces.
- Parsing is bounds-checked and rejects malformed or unreasonable input sizes.

## Initial sequence
BinaryReader -> filesystem provider -> installation inventory -> resource catalog
-> format parsers -> diagnostic asset inspector -> isometric viewer -> playable slice.
