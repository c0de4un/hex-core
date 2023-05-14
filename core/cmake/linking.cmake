# = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# MODULES
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

# Flags for Clang
target_compile_options( hex PUBLIC -fexceptions )

# Link with hexEngine.Core
target_include_directories( hex PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/core/public" )

# Link with hexEngine.Patfrom
target_include_directories( hex PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/${PLATFORM}/public" )

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# LIBRARIES
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

# GLM
if (NOT DEFINED GLM_INCLUDE_DIR)
    message(FATAL_ERROR "hexEngine - <GLM_INCLUDE_DIR> not defined")
endif (NOT DEFINED GLM_INCLUDE_DIR)
if ( NOT EXISTS "${GLM_INCLUDE_DIR}/vec3.hpp" )
    message( FATAL_ERROR "hexEngine - GLM not found at ${GLM_INCLUDE_DIR}" )
endif ( NOT EXISTS "${GLM_INCLUDE_DIR}/vec3.hpp" )
target_include_directories( hex PRIVATE "${GLM_INCLUDE_DIR}" )

# = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
