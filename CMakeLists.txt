cmake_minimum_required(VERSION 3.16)
project(CMakeSFMLProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

file(GLOB SRCS CONFIGURE_DEPENDS 
    ${CMAKE_SOURCE_DIR}/src/*.cpp
    ${CMAKE_SOURCE_DIR}/src/GUI/*.cpp
    ${CMAKE_SOURCE_DIR}/src/States/*.cpp
    ${CMAKE_SOURCE_DIR}/src/World/*.cpp
    ${CMAKE_SOURCE_DIR}/src/World/Level/*.cpp
    ${CMAKE_SOURCE_DIR}/src/Audio/*.cpp
    ${CMAKE_SOURCE_DIR}/src/Player/*.cpp
)

add_executable(game ${SRCS})
target_link_libraries(game PRIVATE sfml-graphics sfml-window sfml-system sfml-audio)
target_compile_features(game PRIVATE cxx_std_17)
target_include_directories(game PRIVATE 
    ${CMAKE_SOURCE_DIR}/include/
    ${CMAKE_SOURCE_DIR}/include/States/
    ${CMAKE_SOURCE_DIR}/include/GUI/
    ${CMAKE_SOURCE_DIR}/include/Identifiers/
    ${CMAKE_SOURCE_DIR}/template/
    ${CMAKE_SOURCE_DIR}/include/World/
    ${CMAKE_SOURCE_DIR}/include/World/Level/
    ${CMAKE_SOURCE_DIR}/include/Audio/
    ${CMAKE_SOURCE_DIR}/include/Player/
)

if(WIN32)
    add_custom_command(
        TARGET game
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:game>
        VERBATIM)
endif()

install(TARGETS game)