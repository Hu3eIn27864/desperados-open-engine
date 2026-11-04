# Preliminary audio and savegame observations

## Scope and provenance

This note summarizes high-level observations from strings and imported API names reported by a local inspection of the user's own installed game executable. It is an independently written research summary, not a transcription of the executable. No original executable, DLL, game asset, raw string dump, disassembly, or extracted resource is included.

These observations are evidence of names, diagnostics, and imported interfaces present in the inspected build. They do not establish complete runtime behavior, binary formats, or compatibility requirements.

## Audio subsystem

The inspected executable references FMOD APIs and DirectSound, including initialization, driver/output selection, stream playback, sample loading, channel control, and spatial-audio listener/source operations. This supports the conclusion that the original game used a dedicated audio subsystem with a middleware-backed playback layer.

Additional diagnostic and source-name clues indicate several responsibilities:

- Sound-source management and caching are represented by distinct components.
- Spatial audio includes listener attributes, distance scaling, roll-off, and 3D source attributes.
- Music playback uses streams and appears to distinguish quiet, alert, and combat music pools.
- Sound data is organized into banks or grouped resources, with ID lookup and version-validation paths.
- Menu sounds and in-game sounds/music have distinguishable loading paths.
- Bink video playback is integrated with audio-related APIs, although the exact synchronization behavior is not established by these clues.

The names of referenced resource files are not specifications. Their internal layouts, compression, sample encoding, identifiers, and version rules remain unknown and must be investigated separately using controlled experiments and synthetic test fixtures.

## Savegame subsystem

The inspected executable contains source-name and diagnostic clues for custom savegame handling, dynamic savegame handling, and a savegame manager. Other clues indicate:

- Numbered save slots and dedicated quick-save/quick-load paths.
- Validation of savegame files.
- Version numbers and a compatibility path for older savegames.
- Extraction of a thumbnail from a savegame.

This suggests that saving/loading should be modeled as a dedicated subsystem rather than as an incidental serialization function. A clean implementation should use an engine-owned, explicitly versioned format, with clear separation between container metadata, world state, and optional preview data. Any compatibility reader should be developed only after the original format is understood sufficiently and tested against legally obtained local examples; synthetic fixtures should be used for parser development.

## Architectural implications for this project

1. Keep audio backend integration behind an engine-owned audio interface. Gameplay should request semantic events or sound cues rather than call FMOD-style APIs directly.
2. Represent sound sources, listeners, music state, and resource-bank lookup as separate concepts.
3. Treat spatial audio as a runtime service that consumes world positions and listener state; do not couple it to the renderer.
4. Implement savegame serialization independently from resource-file parsing and gameplay logic.
5. Make savegame versions explicit and test migrations with synthetic fixtures.
6. Do not infer exact file formats, IDs, or state transitions from strings or import names alone.

## Confidence and open questions

**High confidence:** the inspected executable references FMOD/DirectSound functionality, spatial-audio operations, sound-bank handling, distinct music paths, and dedicated savegame components.

**Moderate confidence:** music has separate quiet/alert/combat pools; sound-source management and caching are distinct responsibilities; savegames include version handling and thumbnail extraction.

**Unknown:** the exact audio resource and bank formats, sound ID namespace, mixing rules, music transition logic, savegame container layout, serialized object graph, thumbnail encoding, and backward-compatibility guarantees.

All future format research should record reproducible observations without publishing original resources, bulk extracted strings, binary dumps, or decompiler output.
