# = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# MODULES
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

if ( NOT DEFINED HEX_MODULES_LIST )
    message( FATAL_ERROR "${PROJECT_NAME} - modules not listed. List them in <HEX_MODULES_LIST>. Example: <windows;gl;net>" )
else ( NOT DEFINED HEX_MODULES_LIST )
    message( STATUS "${PROJECT_NAME} - enabled modules: ${HEX_MODULES_LIST}" )
endif ( NOT DEFINED HEX_MODULES_LIST )

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# EXPORT
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

if ( NOT DEFINED HEX_EXPORT_HEADERS )
    message( FATAL_ERROR "${PROJECT_NAME} - HEX_EXPORT_HEADERS is not defined. Its required to support sharing sources between scoped modules" )
endif ( NOT DEFINED HEX_EXPORT_HEADERS )

if ( NOT DEFINED HEX_EXPORT_SOURCES )
    message( FATAL_ERROR "${PROJECT_NAME} - HEX_EXPORT_SOURCES is not defined. Its required to support sharing sources between scoped modules" )
endif ( NOT DEFINED HEX_EXPORT_SOURCES )

# = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
