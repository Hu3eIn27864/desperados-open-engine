# Subsystem observations from executable string metadata

**Status:** preliminary research notes  
**Evidence:** user-generated ASCII string extraction from a locally owned copy of the original Windows executable  
**Scope:** names, diagnostics, and subsystem labels only; no original executable, DLL, asset, script, or raw string dump is included.

## Method and limitations

The observations below were derived from printable strings extracted from the executable and grouped by topic. Reported offsets are file offsets from that local extraction, not runtime addresses or verified function locations.

String metadata is useful for forming hypotheses about architecture and interfaces. It does **not** establish execution order, data layout, call graphs, algorithms, or exact runtime semantics. Names may be internal terminology, debug labels, or error-message wording. These notes intentionally summarize the evidence rather than republish a bulk string dump.

## World and level data

The executable contains distinct loader/status labels for several world-related data categories, including:

- background and background patches;
- materials and motion information;
- sectors and masks;
- buildings and lifts;
- waypoint paths;
- sight information;
- sound-source data;
- script-related data;
- dialogues, mobile elements, bond information, and tactical data.

Diagnostics also refer to doors, building/sector validity, actor transitions into and out of script sectors, and waypoint visibility or obstacle intersections.

**Working hypothesis:** level data is represented as multiple related subsystems rather than one undifferentiated map blob. The names suggest spatial, visual, navigation, interaction, and script-linked data categories. Their exact serialization formats and dependencies remain unknown.

## Navigation and spatial queries

The extracted labels and diagnostics refer to:

- waypoints and waypoint paths;
- patrol-path assignment for NPCs;
- visibility checks between path locations;
- obstacle proximity and path/obstacle intersection checks;
- sectors and motion areas;
- doors and building entry.

**Working hypothesis:** navigation uses waypoint/path structures and interacts with collision or obstacle data. Separate checks for ordinary actors and riders suggest movement profiles may affect path validation. This is not yet proof of the pathfinding algorithm or its data representation.

## NPC artificial intelligence

The executable exposes a large vocabulary of AI state/substate labels. The observed families include default/idling, watching, seeking, attacking, fleeing, menacing, surrendering, and looking-for-help behavior. Individual labels describe more specific activities such as taking cover, reloading, reacting to noises, investigating bodies, or following tactical paths.

It also names attitude categories corresponding to friendly, nervous, hostile, suspicious, and neutral behavior. Diagnostics distinguish NPCs from playable characters, civilists, animals, and other actor types, and mention configurable view cones, alert state, patrol paths, posts, and AI locking.

**Working hypothesis:** the AI is organized as a hierarchical or otherwise multi-level state model with actor-type constraints and event-driven transitions. The labels alone do not reveal the state graph, priorities, timing, perception formulas, or transition rules.

## Scripting and sequences

The executable contains named gameplay events (for example, hearing, seeing, reaching a point, timers, and actor-condition changes), as well as diagnostics associated with sequence construction and playback.

Other metadata explicitly references a script compiler, a virtual-machine implementation, bytecode loading, script files, and serialization. Script-facing diagnostics cover actor/location validation and commands for movement, animation, speech, firing, doors, AI control, and character-specific abilities.

**Working hypothesis:** mission logic is mediated by a script system with a bytecode-consuming virtual machine. A sequence subsystem appears to coordinate multi-step actor actions such as movement, turning, animation, speech, and combat actions. The precise bytecode format, instruction set, VM semantics, and sequence representation have not been established.

## Implications for the open implementation

These observations support the following implementation boundaries:

1. Keep world-data parsing separated into independently testable parsers and validated engine-owned structures.
2. Model spatial concepts explicitly: sectors, waypoints, paths, obstacles, buildings, doors, and motion areas.
3. Keep actor classification separate from AI state and attitude.
4. Represent AI states and substates as typed data in the new engine; do not treat extracted labels as a complete behavioral specification.
5. Keep mission scripting behind a dedicated runtime interface. Do not design a bytecode parser until the format has been independently characterized.
6. Represent sequences as a separate gameplay/runtime concept rather than mixing them into rendering or low-level file parsing.

## Next research questions

- Which files in a clean installation correspond to each named world-data category?
- Are the categories stored in one container, multiple containers, or level-specific files?
- What coordinate system and units are used by waypoints, sectors, and actor positions?
- How are waypoint paths connected to sectors, obstacles, doors, and building transitions?
- Which AI state transitions are autonomous, and which are triggered by mission events?
- What is the boundary between script bytecode, script-visible commands, and sequence execution?
- Which metadata can be confirmed using controlled in-game observations without publishing original content?

## Clean-room and publication policy

This document contains independently written summaries of technical observations. It does not include executable code, decompiler output, raw disassembly, bulk extracted strings, original game resources, or proprietary scripts. Future format specifications should distinguish measured facts from hypotheses and should use synthetic fixtures for parser tests.

Reverse-engineering and interoperability rules depend on jurisdiction and circumstances. This document is a technical research note, not a legal conclusion or a claim that every form of reverse engineering or publication is permitted.
