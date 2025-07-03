cmake_minimum_required(VERSION 3.10)

project(VyLib LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE Debug)


# Prevent building in the source directory
if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
    message(FATAL_ERROR "In-source builds not allowed.\n")
endif()


# Executable Directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(VYLIB_BASE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(VYLIB_VENDOR_DIR ${CMAKE_CURRENT_SOURCE_DIR}/vendor)
set(VYLIB_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

include(cmake/CommonDefs.cmake)


set(VYLIB_COMPILER_FLAGS /W0)


set(VYLIB_SOURCES

    include/VyLib.h

    include/VyLib/Prerequisites.h

    # Algorthms
    include/VyLib/Algorithms/Hash.h

    # Assert
    include/VyLib/Assert/Assert.h

    # Common
    include/VyLib/Common/Common.h

    # Containers
    include/VyLib/Containers/Array.h
    include/VyLib/Containers/Bitmask.h
    include/VyLib/Containers/Deque.h
    include/VyLib/Containers/List.h
    include/VyLib/Containers/Map.h
    include/VyLib/Containers/Queue.h
    include/VyLib/Containers/Set.h
    include/VyLib/Containers/Span.h
    include/VyLib/Containers/Stack.h
    include/VyLib/Containers/Vector.h

    # IO
    include/VyLib/IO/Streams.cpp
    include/VyLib/IO/Streams.h

    # Strings
    include/VyLib/Strings/String.cpp
    include/VyLib/Strings/String.h

    # Log
    include/VyLib/Log/Log.cpp
    include/VyLib/Log/Log.h

    # Math
    include/VyLib/Math/Math.h

    # Memory
    include/VyLib/Memory/Ptrs.h

    # Serialization
    include/VyLib/Serialization/Endianness.h

    # Types
    include/VyLib/Types/CoreTypes.h
    include/VyLib/Types/StringTypes.h

    # Utils
    include/VyLib/Utils/ClassUtils.h
)

add_library(${PROJECT_NAME} ${VYLIB_SOURCES})
add_library(Vy::Lib ALIAS ${PROJECT_NAME})



add_subdirectory(vendor/glm)
add_subdirectory(vendor/fmt)
add_subdirectory(vendor/json)
add_subdirectory(vendor/spdlog)
add_subdirectory(vendor/magic_enum)


set(VYLIB_INCLUDE
    # ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${VYLIB_VENDOR_DIR}/json/include
    ${VYLIB_VENDOR_DIR}/magic_enum/include
    ${VYLIB_VENDOR_DIR}/spdlog/include
    ${VYLIB_VENDOR_DIR}/fmt/include
    ${VYLIB_VENDOR_DIR}/glm
)

set(VENDOR_LIBS
    glm
    fmt
    spdlog
    nlohmann_json::nlohmann_json
    magic_enum::magic_enum
)

target_include_directories(${PROJECT_NAME} PUBLIC ${VYLIB_INCLUDE_DIR} ${VYLIB_INCLUDE})
target_link_libraries(${PROJECT_NAME} PUBLIC ${VENDOR_LIBS})

target_compile_options(${PROJECT_NAME} PUBLIC ${VYLIB_COMPILER_FLAGS})

# message(STATUS "==========================================================================================")
# message(STATUS "CMake Configuration:")
# message(STATUS "- CMake Version:          ${CMAKE_VERSION}")
# message(STATUS "- CMake Generator:        ${CMAKE_GENERATOR}")
# message(STATUS "- CMake Build Type:       ${CMAKE_BUILD_TYPE}")
# message(STATUS "- CMake Source Directory: ${CMAKE_SOURCE_DIR}")
# message(STATUS "- CMake Binary Directory: ${CMAKE_BINARY_DIR}")
# message(STATUS "- C++ Compiler:           ${CMAKE_CXX_COMPILER}")
# message(STATUS "==========================================================================================")
