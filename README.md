# nfx-resource

<!-- Project Info -->

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg?style=flat-square)](https://github.com/nfx-libs/nfx-resource/blob/main/LICENSE) [![GitHub release (latest by date)](https://img.shields.io/github/v/release/nfx-libs/nfx-resource?style=flat-square)](https://github.com/nfx-libs/nfx-resource/releases) [![GitHub tag (latest by date)](https://img.shields.io/github/tag/nfx-libs/nfx-resource?style=flat-square)](https://github.com/nfx-libs/nfx-resource/tags)<br/>

![C++20](https://img.shields.io/badge/C%2B%2B-20-blue?style=flat-square) ![CMake](https://img.shields.io/badge/CMake-3.20%2B-green.svg?style=flat-square) ![Cross Platform](https://img.shields.io/badge/Platform-Linux_Windows-lightgrey?style=flat-square)

<!-- CI/CD Status -->

[![Linux GCC](https://img.shields.io/github/actions/workflow/status/nfx-libs/nfx-resource/build-linux-gcc.yml?branch=main&label=Linux%20GCC&style=flat-square)](https://github.com/nfx-libs/nfx-resource/actions/workflows/build-linux-gcc.yml) [![Linux Clang](https://img.shields.io/github/actions/workflow/status/nfx-libs/nfx-resource/build-linux-clang.yml?branch=main&label=Linux%20Clang&style=flat-square)](https://github.com/nfx-libs/nfx-resource/actions/workflows/build-linux-clang.yml) [![Windows MinGW](https://img.shields.io/github/actions/workflow/status/nfx-libs/nfx-resource/build-windows-mingw.yml?branch=main&label=Windows%20MinGW&style=flat-square)](https://github.com/nfx-libs/nfx-resource/actions/workflows/build-windows-mingw.yml) [![Windows MSVC](https://img.shields.io/github/actions/workflow/status/nfx-libs/nfx-resource/build-windows-msvc.yml?branch=main&label=Windows%20MSVC&style=flat-square)](https://github.com/nfx-libs/nfx-resource/actions/workflows/build-windows-msvc.yml) [![CodeQL](https://img.shields.io/github/actions/workflow/status/nfx-libs/nfx-resource/codeql.yml?branch=main&label=CodeQL&style=flat-square)](https://github.com/nfx-libs/nfx-resource/actions/workflows/codeql.yml)

> A modern C++20 library for embedding binary resources (files) directly into C++ executables at compile-time

## Overview

nfx-resource is a lightweight C++20 library that enables compile-time embedding of binary files into your C++ executables. It provides a header-only interface library combined with a code generation tool that converts files into C++ byte arrays, allowing you to bundle configuration files, shaders, images, and other assets directly into your binary without external dependencies at runtime.

## Key Features

### 📦 Core Components

- **Resource**: Lightweight struct representing embedded binary data with name, data pointer, and size
- **nfx_embed_resources()**: CMake function for automatic code generation and resource embedding
- **Resource generator tool**: Command-line tool for converting files to C++ source code

### 🔒 Type-Safe Resource Access

- Compile-time resource embedding with zero runtime overhead
- `std::string_view` interface for text resources
- Direct byte array access for binary data
- Template-based `find()` for type-safe lookups
- Support for both C-style arrays and `std::vector` containers

### 🛤️ Flexible Integration

- **Header-only library**: Just include `<nfx/Resource.h>`
- **CMake integration**: Automatic code generation with `nfx_embed_resources()`
- **Manual usage**: Direct C++ array definitions without build tools
- **Namespace support**: Organize resources in nested C++ namespaces
- **Pattern matching**: Filter resources by glob patterns (e.g., `*.json`, `*.png`)

### 📊 Real-World Applications

- **Configuration files**: Embed JSON, YAML, TOML configs into executables
- **Shaders & Graphics**: Include GLSL, HLSL, SPIR-V shaders, textures, fonts
- **Web assets**: Bundle HTML, CSS, JavaScript for embedded servers
- **Game assets**: Embed level data, audio files, and localization resources
- **Test fixtures**: Include test data and sample files for unit tests

### ⚡ Performance Optimized

- Zero runtime file I/O - resources loaded at program startup
- Compile-time resource validation and embedding
- Minimal memory overhead - direct pointer access to data
- Efficient lookup with template-based find functions
- No heap allocations for resource metadata

### 🌍 Cross-Platform Support

- Linux, Windows
- GCC 14+, Clang 18+, MSVC 2022+
- CMake 3.20+ for build integration
- Consistent behavior across platforms

## Quick Start

### Requirements

- C++20 compatible compiler:
  - **GCC 14+** (14.2.0 tested)
  - **Clang 18+** (19.1.7 tested)
  - **MSVC 2022+** (19.44+ tested)
- CMake 3.20 or higher

### Using in Your Project

#### Option 1: Using FetchContent (Recommended)

```cmake
include(FetchContent)
FetchContent_Declare(
  nfx-resource
  GIT_REPOSITORY https://github.com/nfx-libs/nfx-resource.git
  GIT_TAG        main  # or use specific version tag like "1.0.0"
)
FetchContent_MakeAvailable(nfx-resource)

# Create your executable
add_executable(myapp main.cpp)

# Embed resources (automatically links nfx::resource)
nfx_embed_resources(
    TARGET myapp
    RESOURCE_DIR "${CMAKE_SOURCE_DIR}/resources"
    OUTPUT_DIR "${CMAKE_BINARY_DIR}/gen"
    NAMESPACE "myapp::resources"
    REGISTRY_NAME "resources"
    PATTERN "*.json" "*.png"
)
```

#### Option 2: As a Git Submodule

```bash
# Add as submodule
git submodule add https://github.com/nfx-libs/nfx-resource.git third-party/nfx-resource
```

```cmake
# In your CMakeLists.txt
add_subdirectory(third-party/nfx-resource)

add_executable(myapp main.cpp)

nfx_embed_resources(
    TARGET myapp
    RESOURCE_DIR "${CMAKE_SOURCE_DIR}/resources"
    OUTPUT_DIR "${CMAKE_BINARY_DIR}/gen"
    NAMESPACE "myapp::resources"
    REGISTRY_NAME "resources"
)
```

#### Option 3: Using find_package (After Installation)

```cmake
find_package(nfx-resource REQUIRED)

add_executable(myapp main.cpp)

nfx_embed_resources(
    TARGET myapp
    RESOURCE_DIR "${CMAKE_SOURCE_DIR}/resources"
    OUTPUT_DIR "${CMAKE_BINARY_DIR}/gen"
    NAMESPACE "myapp::resources"
    REGISTRY_NAME "resources"
)
```

## Usage Examples

### Basic Usage - CMake Integration

```cpp
#include <resources.h>  // Includes nfx::Resource automatically
#include <iostream>

int main() {
    // Find a specific resource by name
    auto* config = myapp::resources::find("config.json");
    
    if (config) {
        // Access as string view
        std::string_view json = config->str();
        std::cout << "Config: " << json << '\n';
        
        // Access as raw bytes
        const uint8_t* data = config->bytes();
        size_t size = config->size;
        
        // Check if empty
        if (!config->empty()) {
            std::cout << "Resource size: " << size << " bytes\n";
        }
    }
    
    return 0;
}
```

### Iterating All Resources

```cpp
#include <resources.h>  // Includes nfx::Resource automatically
#include <iostream>

int main() {
    // Iterate over all embedded resources
    for (const auto& resource : myapp::resources::all()) {
        std::cout << "Resource: " << resource.name 
                  << " (" << resource.size << " bytes)\n";
    }
    
    return 0;
}
```

### Using with Web Server

```cpp
#include <web_assets.h>  // Generated header with web::assets namespace

void serveStaticFile(const std::string& path) {
    auto* resource = web::assets::find(path);
    
    if (!resource) {
        sendNotFound();
        return;
    }
    
    // Serve the embedded resource
    std::string_view content = resource->str();
    
    // Determine MIME type from extension
    std::string mimeType = getMimeType(resource->name);
    
    sendResponse(200, mimeType, content);
}
```

### Shader Loading Example

```cpp
#include <shaders.h>  // Generated header with shaders namespace
#include <GL/gl.h>

GLuint loadShader(const std::string& name, GLenum shaderType) {
    auto* shader = shaders::find(name);
    if (!shader) {
        throw std::runtime_error("Shader not found: " + name);
    }
    
    GLuint id = glCreateShader(shaderType);
    
    const char* source = reinterpret_cast<const char*>(shader->data);
    GLint length = static_cast<GLint>(shader->size);
    
    glShaderSource(id, 1, &source, &length);
    glCompileShader(id);
    
    return id;
}

int main() {
    GLuint vertShader = loadShader("vertex.glsl", GL_VERTEX_SHADER);
    GLuint fragShader = loadShader("fragment.glsl", GL_FRAGMENT_SHADER);
    
    // Link shaders...
}
```

### Configuration File Example

```cpp
#include <app_config.h>  // Generated header with app::config namespace
#include <json/json.h>   // Your JSON library

struct AppConfig {
    std::string serverHost;
    int serverPort;
    bool debugMode;
};

AppConfig loadConfig() {
    auto* configRes = app::config::find("app_config.json");
    if (!configRes) {
        throw std::runtime_error("Configuration not found");
    }
    
    std::string_view jsonStr = configRes->str();
    
    // Parse JSON (example using hypothetical JSON library)
    Json::Value root = Json::parse(jsonStr);
    
    AppConfig config;
    config.serverHost = root["server"]["host"].asString();
    config.serverPort = root["server"]["port"].asInt();
    config.debugMode = root["debug"].asBool();
    
    return config;
}
```



## API Reference

### Resource Struct

```cpp
namespace nfx {
    struct Resource {
        std::string_view name;  // Resource filename
        const uint8_t* data;    // Pointer to embedded data
        size_t size;            // Size in bytes
        
        // Get resource as string view
        [[nodiscard]] constexpr std::string_view str() const noexcept;
        
        // Get resource as byte pointer
        [[nodiscard]] constexpr const uint8_t* bytes() const noexcept;
        
        // Check if resource is empty
        [[nodiscard]] constexpr bool empty() const noexcept;
    };
}
```

### find() Template Function

```cpp
namespace nfx {
    // Find a resource by name in any container
    template <typename ResourceArray>
    [[nodiscard]] inline const Resource* find(
        const ResourceArray& resources,
        std::string_view name
    ) noexcept;
}
```

### nfx_embed_resources() CMake Function

```cmake
nfx_embed_resources(
    TARGET <target>
    RESOURCE_DIR <resource_dir>
    OUTPUT_DIR <output_dir>
    NAMESPACE <namespace>
    REGISTRY_NAME <registry_name>
    [PATTERN pattern1 pattern2 ...]
    [RECURSE]
)
```

**Parameters:**
- `TARGET` - CMake target name (must exist before calling this function)
- `RESOURCE_DIR` - Absolute path to directory containing files to embed
- `OUTPUT_DIR` - Absolute path where generated `.cpp` and `.h` files will be written
- `NAMESPACE` - C++ namespace (supports nested namespaces like `my::app::resources`)
- `REGISTRY_NAME` - Name for generated files (creates `<name>.h` and `<name>.cpp`)
- `PATTERN` - Optional file glob patterns (default: `*` for all files)
- `RECURSE` - Optional flag to enable recursive subdirectory scanning

**Generated Functions:**

The CMake function generates two functions in your specified namespace:

```cpp
namespace your::namespace {
    // Get all embedded resources
    const std::vector<nfx::Resource>& all();
    
    // Find resource by name
    const nfx::Resource* find(std::string_view name);
}
```

**Example:**

```cmake
nfx_embed_resources(
    TARGET myapp
    RESOURCE_DIR "${CMAKE_SOURCE_DIR}/assets"
    OUTPUT_DIR "${CMAKE_BINARY_DIR}/generated"
    NAMESPACE "myapp::assets"
    REGISTRY_NAME "assets"
    PATTERN "*.json" "*.xml" "*.png"
)
```

This will:
1. Scan `${CMAKE_SOURCE_DIR}/assets` for files matching the patterns (current directory only)
2. Generate `assets.h` and `assets.cpp` in `${CMAKE_BINARY_DIR}/generated`
3. Create `myapp::assets::all()` and `myapp::assets::find()` functions
4. Add generated files to the `myapp` target
5. Include directory automatically added so you can `#include <assets.h>`

**Example with Recursive Scanning:**

```cmake
nfx_embed_resources(
    TARGET myapp
    RESOURCE_DIR "${CMAKE_SOURCE_DIR}/assets"
    OUTPUT_DIR "${CMAKE_BINARY_DIR}/generated"
    NAMESPACE "myapp::assets"
    REGISTRY_NAME "assets"
    PATTERN "*.json" "*.xml" "*.png"
    RECURSE  # Scan subdirectories recursively
)
```

With `RECURSE`, resources in subdirectories are named with their relative paths:
- `assets/config.json` → resource name: `"config.json"`
- `assets/shaders/vertex.glsl` → resource name: `"shaders/vertex.glsl"`
- `assets/textures/ui/icon.png` → resource name: `"textures/ui/icon.png"`

```cpp
// Find resources by their relative paths
auto* shader = myapp::assets::find("shaders/vertex.glsl");
auto* icon = myapp::assets::find("textures/ui/icon.png");
```

## Project Structure

```
nfx-resource/
├── cmake/                            # CMake modules and functions
├── include/nfx/                      # Public headers
└── src/                              # Resource generator
```

## Building the Library

```bash
# Clone the repository
git clone https://github.com/nfx-libs/nfx-resource.git
cd nfx-resource

# Create build directory
mkdir build && cd build

# Configure with CMake
cmake .. -DCMAKE_BUILD_TYPE=Release

# Build the tool
cmake --build . --config Release --parallel

# Install (optional)
sudo cmake --install .
```

## Installation

After building, you can install nfx-resource system-wide:

```bash
# Install to /usr/local (Linux)
sudo cmake --install build

# Install to custom prefix
cmake --install build --prefix /opt/nfx-resource
```

This installs:
- Headers to `include/nfx/`
- nfx-resourcegenerator-clitool to `bin/`
- CMake package config to `lib/cmake/nfx-resource/`

After installation, use with `find_package()`:

```cmake
find_package(nfx-resource REQUIRED)

add_executable(myapp main.cpp)

nfx_embed_resources(
    TARGET myapp
    RESOURCE_DIR "${CMAKE_SOURCE_DIR}/resources"
    OUTPUT_DIR "${CMAKE_BINARY_DIR}/gen"
    NAMESPACE "myapp::resources"
    REGISTRY_NAME "resources"
)
```

## Advanced Usage

### Resource Validation

```cpp
#include <resources.h>  // Generated header
#include <stdexcept>

const nfx::Resource& getResourceOrThrow(std::string_view name) {
    auto* res = resources::find(name);
    if (!res) {
        throw std::runtime_error(
            std::string("Resource not found: ") + std::string(name)
        );
    }
    return *res;
}
```

### Multiple Resource Directories

```cmake
# Embed resources from multiple directories with different namespaces
nfx_embed_resources(
    TARGET myapp
    RESOURCE_DIR "${CMAKE_SOURCE_DIR}/config"
    OUTPUT_DIR "${CMAKE_BINARY_DIR}/gen"
    NAMESPACE "myapp::config"
    REGISTRY_NAME "config"
    PATTERN "*.json" "*.xml"
)

nfx_embed_resources(
    TARGET myapp
    RESOURCE_DIR "${CMAKE_SOURCE_DIR}/shaders"
    OUTPUT_DIR "${CMAKE_BINARY_DIR}/gen"
    NAMESPACE "myapp::shaders"
    REGISTRY_NAME "shaders"
    PATTERN "*.glsl" "*.hlsl"
    RECURSE  # Include shaders from subdirectories
)
```

Then include the appropriate headers:
```cpp
#include <config.h>   // Includes nfx::Resource, provides myapp::config::find()
#include <shaders.h>  // Includes nfx::Resource, provides myapp::shaders::find()

// Access shader with subdirectory path
auto* vertShader = myapp::shaders::find("pbr/vertex.glsl");
```

### Custom Resource Registry

```cpp
#include <resources.h>  // Generated header
#include <unordered_map>
#include <string>

class ResourceManager {
public:
    ResourceManager(const std::vector<nfx::Resource>& resources) {
        for (const auto& res : resources) {
            cache_[std::string(res.name)] = &res;
        }
    }
    
    const nfx::Resource* find(std::string_view name) const {
        auto it = cache_.find(std::string(name));
        return it != cache_.end() ? it->second : nullptr;
    }
    
private:
    std::unordered_map<std::string, const nfx::Resource*> cache_;
};
```

## Roadmap

See [TODO.md](TODO.md) for upcoming features and project roadmap.

## Changelog

See the [CHANGELOG.md](CHANGELOG.md) for a detailed history of changes, new features, and bug fixes.

## License


This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---

_Updated on January 25, 2026_
