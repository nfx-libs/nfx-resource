#==============================================================================
# nfx-resource - Top-level CMake configuration
#==============================================================================

#----------------------------------------------
# Project definition
#----------------------------------------------

cmake_minimum_required(VERSION 3.20)

project(nfx-resource
    VERSION 1.1.0
    DESCRIPTION "C++ Resource Embedding - Header-only interface library + code generation tool"
    HOMEPAGE_URL "https://github.com/nfx-libs/nfx-resource"
    LANGUAGES CXX
)

#----------------------------------------------
# Version configuration
#----------------------------------------------

set(NFX_RESOURCE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR} CACHE INTERNAL "nfx-resource major version")
set(NFX_RESOURCE_VERSION_MINOR ${PROJECT_VERSION_MINOR} CACHE INTERNAL "nfx-resource minor version")
set(NFX_RESOURCE_VERSION_PATCH ${PROJECT_VERSION_PATCH} CACHE INTERNAL "nfx-resource patch version")
set(NFX_RESOURCE_VERSION       ${PROJECT_VERSION}       CACHE INTERNAL "nfx-resource version")

#----------------------------------------------
# Project metadata
#----------------------------------------------

set(NFX_RESOURCE_LICENSE_FILE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")

#----------------------------------------------
# Build options
#----------------------------------------------

option(NFX_RESOURCE_INSTALL_PROJECT "Install project"                  OFF)
option(NFX_RESOURCE_PACKAGE_SOURCE  "Enable source package generation" OFF)

#----------------------------------------------
# CMake modules
#----------------------------------------------

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

#----------------------------------------------
# Main configuration
#----------------------------------------------

include(nfxResourceFunctions)
include(nfxResourceTarget)

#----------------------------------------------
# Installation and packaging
#----------------------------------------------

include(nfxResourceInstall)
include(nfxResourcePackaging)
