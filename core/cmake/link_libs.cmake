# = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# CORE
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

# GLM
if (NOT DEFINED GLM_INCLUDE_DIR)
    message(FATAL_ERROR "hexEngine - <GLM_INCLUDE_DIR> not defined")
endif (NOT DEFINED GLM_INCLUDE_DIR)
if ( NOT EXISTS "${GLM_INCLUDE_DIR}/glm/vec3.hpp" )
    message( FATAL_ERROR "hexEngine - GLM not found at ${GLM_INCLUDE_DIR}" )
endif ( NOT EXISTS "${GLM_INCLUDE_DIR}/glm/vec3.hpp" )
target_include_directories( hex PRIVATE ${GLM_INCLUDE_DIR} )

# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
# MODULES
# - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

# Dependencies defined by Modules
foreach( HEX_MODULE_NAME ${HEX_MODULES_LIST} )
    include( "${HEX_SRC_ROOT_DIR}/${HEX_MODULE_NAME}/link_libs.cmake" )
endforeach()

# = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
