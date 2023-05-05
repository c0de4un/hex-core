# = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# EXPORT
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

if ( NOT DEFINED HEX_EXPORT_HEADERS )
    message( FATAL_ERROR "${CMAKE_PROJECT_NAME} - HEX_EXPORT_HEADERS is not defined. Its required to support sharing sources between scoped modules" )
endif ( NOT DEFINED HEX_EXPORT_HEADERS )

if ( NOT DEFINED HEX_EXPORT_SOURCES )
    message( FATAL_ERROR "${CMAKE_PROJECT_NAME} - HEX_EXPORT_SOURCES is not defined. Its required to support sharing sources between scoped modules" )
endif ( NOT DEFINED HEX_EXPORT_SOURCES )

# = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
