# Changelog

## [Unreleased]

### Added

- `RECURSE` option for `nfx_embed_resources()` to enable recursive subdirectory scanning
- Automatic relative path preservation for resources in subdirectories when `RECURSE` is enabled
- Optional 4th parameter for resource generator CLI to specify custom resource names

### Changed

- Resource naming: with `RECURSE`, resources now use relative paths (e.g., `"shaders/vertex.glsl"`) instead of just filenames
- Pattern handling: `RECURSE` mode uses `**` glob patterns to properly match files in subdirectories

### Deprecated

- NIL

### Removed

- NIL

### Fixed

- NIL

### Security

- NIL

## [1.0.0] - 2026-01-22

### Added

- Header-only C++20 library for compile-time binary resource embedding
- `nfx::Resource` struct with `str()`, `bytes()`, and `empty()` methods for type-safe resource access
- CMake function `nfx_embed_resources()` for automated resource generation and integration
- Resource code generator tool for converting files to C++ source code
- Template-based `nfx::find()` helper for resource lookup
- Automatic generation of resource registry headers with `all()` and `find()` functions
- Support for multiple resource directories with unique namespaces via `REGISTRY_NAME` parameter
- Pattern-based file filtering (glob patterns)
- Cross-platform support (Linux, Windows)
- Zero runtime overhead with direct memory access to embedded data
