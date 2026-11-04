# Development milestones

## M0 — Foundation (in progress)
- [x] C++20 core target and CMake build.
- [x] Bounds-checked little-endian BinaryReader.
- [x] Unit test target and cross-platform CI workflow.
- [ ] SDL3 application build verified on Windows, Linux and macOS.

## M1 — Installation and resource inventory
- [ ] User-configurable installation path.
- [ ] Read-only installation discovery and validation.
- [ ] File inventory with relative paths, sizes and hashes.
- [ ] No asset extraction into the repository.

## M2 — Compatibility foundation
- [ ] Format research records and synthetic fixtures.
- [ ] Parser result/error model.
- [ ] First independently implemented read-only format parser.
- [ ] Fuzzing and malformed-input tests.

## M3 — Diagnostic viewer
- [ ] Resource inspection CLI.
- [ ] Basic image/texture diagnostics where format support permits.
- [ ] Isometric coordinate and camera prototype.

## M4 — Playable vertical slice
- [ ] World representation and collision queries.
- [ ] Entity movement and animation.
- [ ] Input, selection and basic interaction.

## M5 — Runtime compatibility
- [ ] AI, scripting, mission flow, audio and save/load.
- [ ] Compatibility tests against legally obtained local game data.

## M6 — Modern release
- [ ] Windows, Linux and macOS packaging.
- [ ] Optional modern display/input/accessibility improvements.
- [ ] Documented compatibility matrix.

A complete replacement runtime is a multi-stage project. No compatibility claim
is made before tests demonstrate it.
