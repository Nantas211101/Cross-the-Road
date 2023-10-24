cmake_minimum_required(VERSION 3.21)
project(Cross_the_road LANGUAGES CXX)


include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

file(GLOB SRCS CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/src/*.cpp)

add_executable(Cross_the_road ${SRCS})
target_include_directories(Cross_the_road PRIVATE ./include)
target_link_libraries(Cross_the_road PRIVATE sfml-graphics sfml-window sfml-system)
target_compile_features(Cross_the_road PRIVATE cxx_std_17)
if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET Cross_the_road POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:Cross_the_road> $<TARGET_FILE_DIR:Cross_the_road> COMMAND_EXPAND_LISTS)
endif()

install(TARGETS Cross_the_road)