#==============================================================================
# nfx-resource - Library packaging configuration (CPack)
#==============================================================================

#----------------------------------------------
# Packaging condition check
#----------------------------------------------

if(NOT NFX_RESOURCE_PACKAGE_SOURCE)
    return()
endif()

#----------------------------------------------
# CPack configuration
#----------------------------------------------

# --- Common settings ---
set(CPACK_PACKAGE_NAME                  ${PROJECT_NAME})
set(CPACK_PACKAGE_VENDOR                "nfx")
set(CPACK_PACKAGE_DIRECTORY             "${CMAKE_BINARY_DIR}/packages")
set(CPACK_PACKAGE_VERSION_MAJOR         ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR         ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH         ${PROJECT_VERSION_PATCH})
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY   "C++20 library for compile-time binary resource embedding")
set(CPACK_PACKAGE_HOMEPAGE_URL          ${CMAKE_PROJECT_HOMEPAGE_URL})
set(CPACK_RESOURCE_FILE_LICENSE         "${NFX_RESOURCE_LICENSE_FILE}")

# --- Source package settings ---
set(CPACK_SOURCE_PACKAGE_FILE_NAME      "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-Source")
set(CPACK_SOURCE_GENERATOR              "TGZ;ZIP")
set(CPACK_SOURCE_IGNORE_FILES           ".git/;.github/;.gitignore;build/;.deps/;Testing/;.vs/;.vscode/;.*~$")

#----------------------------------------------
# Include CPack
#----------------------------------------------

include(CPack)
