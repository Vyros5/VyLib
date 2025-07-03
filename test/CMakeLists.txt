

set(VYTEST_FILES
    EntryPoint.cpp
)


set(APP_NAME VyTest)
add_executable(${APP_NAME} ${VYTEST_FILES})
target_include_directories(${APP_NAME} PUBLIC ${VYLIB_INCLUDE})
target_link_libraries(${APP_NAME} PUBLIC VyLib)