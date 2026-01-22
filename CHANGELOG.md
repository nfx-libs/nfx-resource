# Changelog

## [Unreleased]

### Added

- NIL

### Changed

- NIL

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
