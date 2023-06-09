# = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

if ( NOT DEFINED HEX_BUILD_TYPES )
    if ( ${CMAKE_BUILD_TYPE} STREQUAL "Debug" )
        message ( STATUS "hexEngine - DEBUG-Mode enabled" )

        set ( HEX_BUILD_TYPE "debug" )
        set ( HEX_DEBUG ON )
        add_definitions ( -DHEX_DEBUG=1 )
    else ( ${CMAKE_BUILD_TYPE} STREQUAL "Debug" )
        message ( STATUS "hexEngine - DEBUG-Mode disabled" )

        set ( HEX_BUILD_TYPE "release" )
        set ( HEX_DEBUG OFF )
        #add_definitions ( -DHEX_DEBUG=0 )
    endif ( ${CMAKE_BUILD_TYPE} STREQUAL "Debug" )

    if ( NOT DEFINED HEX_LOGGING AND HEX_DEBUG )
        set(HEX_LOGGING ON)
        add_definitions ( -DHEX_LOGGING=1 )
    endif ( NOT DEFINED HEX_LOGGING AND HEX_DEBUG )

    if ( NOT HEX_MEMORY_DEBUG )
        message( "hexEngine - Memory-Management debugging is disabled. Set <HEX_MEMORY_DEBUG> to enable it" )
    else ( NOT HEX_MEMORY_DEBUG )
        message( "hexEngine - Memory-Management debugging is enabled" )
        add_definitions( -DHEX_MEMORY_DEBUG=1 )
    endif ( NOT HEX_MEMORY_DEBUG )

    set( NOT DEFINED HEX_BUILD_TYPES TRUE )
endif ( NOT DEFINED HEX_BUILD_TYPES )

# = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
