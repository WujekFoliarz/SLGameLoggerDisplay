cmake_minimum_required (VERSION 3.18)
set(CMAKE_CXX_STANDARD 23)
project(SLGameLoggerDisplay)

file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/Source/*.cpp")

#add_library(${PROJECT_NAME} SHARED ${MY_SOURCES})
add_executable(${PROJECT_NAME} ${MY_SOURCES})

#target_precompile_headers(${PROJECT_NAME} PRIVATE src/pch.hpp)
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/src")

set(PRODUCTION_BUILD OFF)
if(PRODUCTION_BUILD)
    target_compile_definitions(${PROJECT_NAME} PUBLIC PRODUCTION_BUILD)
    target_compile_definitions(${PROJECT_NAME} PRIVATE RESOURCE_PATH="Resources/")
else()
    target_compile_definitions(${PROJECT_NAME} PRIVATE RESOURCE_PATH="${CMAKE_CURRENT_SOURCE_DIR}/Resources/")
endif()

# -- Libraries --
add_subdirectory("Thirdparty/raylib")
add_subdirectory("Thirdparty/json")
add_subdirectory("Thirdparty/imgui")
add_subdirectory("Thirdparty/rlImGui")
target_link_libraries(${PROJECT_NAME} PRIVATE raylib json imgui rlimgui)

# -- Extension --
# set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX ".asi")

# -- Strip debug symbols and statically link libgcc on mingw --
set(DEBUG_FILE "${PROJECT_NAME}.debug")

if(MINGW)
    set(DEBUG_FILE "${PROJECT_NAME}.pdb")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static -static-libgcc -static-libstdc++")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -static -static-libgcc -static-libstdc++")
endif()

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} --only-keep-debug $<TARGET_FILE:${PROJECT_NAME}> ${DEBUG_FILE}
    COMMAND ${CMAKE_OBJCOPY} --strip-all --strip-unneeded $<TARGET_FILE:${PROJECT_NAME}>
    COMMAND ${CMAKE_OBJCOPY} --add-gnu-debuglink=${DEBUG_FILE} $<TARGET_FILE:${PROJECT_NAME}>
)
