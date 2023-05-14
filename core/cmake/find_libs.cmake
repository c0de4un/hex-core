# = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# CORE
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

# GLM
if (NOT DEFINED GLM_INCLUDE_DIR)
    message(FATAL_ERROR "hexEngine - <GLM_INCLUDE_DIR> not defined")
endif (NOT DEFINED GLM_INCLUDE_DIR)
if ( NOT EXISTS "${GLM_INCLUDE_DIR}/vec3.hpp" )
    message( FATAL_ERROR "hexEngine - GLM not found at ${GLM_INCLUDE_DIR}" )
endif ( NOT EXISTS "${GLM_INCLUDE_DIR}/vec3.hpp" )

# = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
