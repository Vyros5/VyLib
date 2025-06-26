cmake_minimum_required(VERSION 3.25)
project(Vendor CXX C)

include(FetchContent)

set(YAMLCPP_TAG     2f86d13775d119edbb69af52e5f566fd65c6953b)


FetchContent_Declare(
  yaml-cpp
  GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
  GIT_TAG        ${YAMLCPP_TAG}
)
FetchContent_MakeAvailable(yaml-cpp)


add_subdirectory(json)
add_subdirectory(magic_enum)

