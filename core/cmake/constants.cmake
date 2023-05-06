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

set( HEX_CORE_BINARY_NAME "hex" )
set( HEX_CORE_VERSION 0.1.0 )

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# C/C++
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

# C++ Version
if ( NOT DEFINED HEX_CXX_VERSION )
    set( HEX_CXX_VERSION 14 )
    message( STATUS "hexEngine - C++ version set to default. Use <HEX_CXX_VERSION> to change it" )
endif ( NOT DEFINED HEX_CXX_VERSION )
message( STATUS "hexEngine - C++ version is ${HEX_CXX_VERSION}" )

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# BUILD
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

# Build-Mode
if ( NOT DEFINED HEX_CORE_BUILD_MODE )
    set( HEX_CORE_BUILD_MODE "STATIC" )
    message( STATUS "hexEngine - build-mode set to default. Use <HEX_CORE_BUILD_MODE> to change it. Available types: STATIC, SHARED and EXPORT" )
endif ( NOT DEFINED HEX_CORE_BUILD_MODE )
message( STATUS "hexEngine - build-mode is ${HEX_CORE_BUILD_MODE}" )

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# DIRS
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

if ( NOT DEFINED HEX_SRC_ROOT_DIR )
    message( FATAL_ERROR "hexEngine - hexEngine root dir not set. Set it with <HEX_SRC_ROOT_DIR> (where core and other modules are located. Example: <src/engine>)" )
endif ( NOT DEFINED HEX_SRC_ROOT_DIR )

# = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
