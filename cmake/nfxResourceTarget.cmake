#==============================================================================
# nfx-resource - CMake target
#==============================================================================

#----------------------------------------------
# Resource generator
#----------------------------------------------

add_executable(nfx-resourcegenerator-cli
    src/resourcefenerator-cli.cpp
)
set_target_properties(nfx-resourcegenerator-cli PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/bin"
)
add_executable(nfx::resourcegen ALIAS nfx-resourcegenerator-cli)

#----------------------------------------------
# Header-only library
#----------------------------------------------

add_library(nfx-resource INTERFACE)
add_library(nfx::resource ALIAS nfx-resource)

target_include_directories(nfx-resource
    INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

target_compile_features(nfx-resource INTERFACE cxx_std_20)
