# = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

if ( NOT DEFINED HEX_PLATFORM_DETECTED )

    if ( WIN32 OR WIN64 OR MINGW OR MING32 OR MINGW64 OR CYGWIN OR CYGWIN64 OR MSYS OR CMAKE_SYSTEM_NAME STREQUAL "Windows" )
        # Windows
        set( PLATFORM "windows" )
        set( HEX_WINDOWS ON )
        add_definitions( -DHEX_WINDOWS=1 )
    elseif ( ANDROID OR $CMAKE_SYSTEM_NAME STREQUAL "Android" )
        # Android
        set( PLATFORM "android" )
        set( HEX_ANDROID ON )
        add_definitions( -DHEX_ANDROID=1 )
    elseif ( APPLE OR CMAKE_SYSTEM_NAME STREQUAL "Darwin" )
        # Mac
        set( PLATFORM "mac" )
        set( HEX_MAC ON )
        add_definitions( -DHEX_MAC=1 )
    elseif ( LINUX OR UNIX OR CMAKE_SYSTEM_NAME STREQUAL "Linux" OR CMAKE_SYSTEM_NAME STREQUAL "FreeBSD" OR CMAKE_SYSTEM_NAME STREQUAL "CrayLinuxEnvironment" )
        # Linux
        set( PLATFORM "linux" )
        set( HEX_LINUX ON )
        add_definitions( -DHEX_LINUX=1 )
    elseif ( IOS )
        set( PLATFORM "ios" )
        set( HEX_IOS ON )
        add_definitions( -DHEX_IOS=1 )
    else ( WIN32 OR WIN64 OR MINGW OR MING32 OR MINGW64 OR CYGWIN OR CYGWIN64 OR MSYS OR CMAKE_SYSTEM_NAME STREQUAL "Windows" ) # WINDOWS
        message( FATAL_ERROR "hexEngine - failed to detect target-platform, configuration required" )
    endif ( WIN32 OR WIN64 OR MINGW OR MING32 OR MINGW64 OR CYGWIN OR CYGWIN64 OR MSYS OR CMAKE_SYSTEM_NAME STREQUAL "Windows" ) # WINDOWS

    message ( STATUS "hexEngine - platform is ${PLATFORM}" )

    set( HEX_PLATFORM_DETECTED ON )
    add_definitions( -DHEX_PLATFORM_DEFINED=1 )

endif ( NOT DEFINED HEX_PLATFORM_DETECTED )

if ( NOT DEFINED CPU_ARCHITECTURE_BIT )
    set( CPU_ARCHITECTURE_BIT "x64" )
    message( STATUS "hexEngine - CPU_ARCHITECTURE_BIT set to ${CPU_ARCHITECTURE_BIT} as default" )
else ( NOT DEFINED CPU_ARCHITECTURE_BIT )
    message( STATUS "hexEngine - CPU_ARCHITECTURE_BIT is ${CPU_ARCHITECTURE_BIT}" )
endif ( NOT DEFINED CPU_ARCHITECTURE_BIT )
add_definitions( -DCPU_ARCHITECTURE_BIT=${CPU_ARCHITECTURE_BIT} )

if ( NOT DEFINED CPU_ARCHITECTURE )
    set( CPU_ARCHITECTURE "amd" )
    message( STATUS "hexEngine - CPU_ARCHITECTURE set to ${CPU_ARCHITECTURE} as default" )
else ( NOT DEFINED CPU_ARCHITECTURE )
    message( STATUS "hexEngine - CPU_ARCHITECTURE is ${CPU_ARCHITECTURE}" )
endif ( NOT DEFINED CPU_ARCHITECTURE )
add_definitions( -DCPU_ARCHITECTURE=${CPU_ARCHITECTURE} )

# = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
