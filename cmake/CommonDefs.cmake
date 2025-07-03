

#--------------------------------------------------------------------
# Platform
#--------------------------------------------------------------------

if (WIN32)
    add_compile_definitions(VY_PLATFORM_WINDOWS=1)
endif()
if(APPLE)
    add_compile_definitions(VY_PLATFORM_APPLE=1)
endif()
if(UNIX AND NOT APPLE)
    add_compile_definitions(VY_PLATFORM_UNIX=1)
endif()
if(NOT WIN32 AND NOT APPLE AND NOT UNIX)
    add_compile_definitions(VY_PLATFORM_UNKNOWN=1)
endif()


#--------------------------------------------------------------------
# Compiler
#--------------------------------------------------------------------
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_definitions(VY_COMPILER_CLANG=1)
elseif (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    add_compile_definitions(VY_COMPILER_GNU=1)
elseif (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    add_compile_definitions(VY_COMPILER_MSVC=1)
elseif (CMAKE_CXX_COMPILER_ID MATCHES "Intel")
    add_compile_definitions(VY_COMPILER_INTEL=1)
else()
    add_compile_definitions(VY_COMPILER_OTHER=1)
endif()