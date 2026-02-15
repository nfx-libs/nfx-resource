#==============================================================================
# nfx-resource - Library installation
#==============================================================================

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

# Install headers
install(DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# Install tool
install(TARGETS nfx-resourcegenerator-cli
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Configure and install CMake functions (with proper CLI path for installed packages)
configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/nfxResourceFunctions.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/nfxResourceFunctions.cmake
    @ONLY
)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/nfxResourceFunctions.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/nfx-resource
)

# Install library target
install(TARGETS nfx-resource
    EXPORT nfx-resource-targets
)

install(EXPORT nfx-resource-targets
    FILE nfx-resource-targets.cmake
    NAMESPACE nfx::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/nfx-resource
)

# Create config file
configure_package_config_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake/nfx-resource-config.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/nfx-resource-config.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/nfx-resource
)

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/nfx-resource-config-version.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/nfx-resource-config.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/nfx-resource-config-version.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/nfx-resource
)
