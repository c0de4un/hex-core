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

# = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =
