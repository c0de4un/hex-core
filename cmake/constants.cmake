# = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# CMAKE
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

if ( NOT DEFINED HEX_CMAKE_VERSION )
    set( HEX_CMAKE_VERSION 3.22.1 )
endif ( NOT DEFINED HEX_CMAKE_VERSION )

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# PROJECT
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

set( HEX_CORE_PROJECT_NAME "hexEngine.Core" )
set( HEX_CORE_BINARY_NAME "hex_core" )
set( HEX_CORE_VERSION 0.1.0 )

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# C/C++
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

# C++ Version
if ( NOT DEFINED HEX_CXX_VERSION )
    set( HEX_CXX_VERSION 14 )
    message( STATUS "${HEX_CORE_PROJECT_NAME} - C++ version set to default. Use <HEX_CXX_VERSION> to change it" )
endif ( NOT DEFINED HEX_CXX_VERSION )
message( STATUS "${HEX_CORE_PROJECT_NAME} - C++ version is ${HEX_CXX_VERSION}" )

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# BUILD
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

# Build-Mode
if ( NOT DEFINED HEX_CORE_BUILD_MODE )
    set( HEX_CORE_BUILD_MODE "STATIC" )
    message( STATUS "${HEX_CORE_PROJECT_NAME} - build-mode set to default. Use <HEX_CORE_BUILD_MODE> to change it. Available types: STATIC, SHARED and EXPORT" )
endif ( NOT DEFINED HEX_CORE_BUILD_MODE )
message( STATUS "${HEX_CORE_PROJECT_NAME} - build-mode is ${HEX_CORE_BUILD_MODE}" )

# = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
