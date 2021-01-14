cmake_minimum_required(VERSION 3.10)
project(TruGaming)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_LIBRARIES "-static-libgcc -static-libstdc++ -lwsock32 -lws2_32 ${CMAKE_CXX_STANDARD_LIBRARIES}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive")

set(CMAKE_CXX_FLAGS_DEBUG "-Os")
set(CMAKE_CXX_FLAGS_RELEASE "-Os")

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/Executable/")
set (CMAKE_BINARY_DIR  "${CMAKE_SOURCE_DIR}/Executable/")

if (CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(64BIT TRUE)
    set(ARCHITECTURE "x86-64")
endif()

if(MSVC OR MSYS OR MINGW OR WIN32)
    if (64BIT)
        set(SFML_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/Dependencies/SFML/RELEASE/64Bit/include")
        set(SFML_LIBRARY_DIR "${CMAKE_SOURCE_DIR}/Dependencies/SFML/RELEASE/64Bit/lib")
        set(SFML_DIR "${CMAKE_SOURCE_DIR}/Dependencies/SFML/RELEASE/64Bit/lib/cmake/SFML/")
    else()
        set(SFML_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/Dependencies/SFML/RELEASE/32Bit/include")
        set(SFML_LIBRARY_DIR "${CMAKE_SOURCE_DIR}/Dependencies/SFML/RELEASE/32Bit/lib")
        set(SFML_DIR "${CMAKE_SOURCE_DIR}/Dependencies/SFML/RELEASE/32Bit/lib/cmake/SFML/")
    endif()

elseif(APPLE AND NOT UNIX)
    message( FATAL_ERROR "Not supported on OSX at this time..." )
    set(APPLE TRUE)
elseif(UNIX)
    message( FATAL_ERROR "Not supported on UNIX at this time..." )
endif()

set(SFML_STATIC_LIBRARIES TRUE)

find_package(SFML 2.5.1 REQUIRED COMPONENTS network system window graphics audio main)



add_executable(${PROJECT_NAME}
        ${CMAKE_SOURCE_DIR}/Source/Application.cpp
        ${CMAKE_SOURCE_DIR}/Source/Application.h
        ${CMAKE_SOURCE_DIR}/Source/TextureManager/Tilemap.h
        ${CMAKE_SOURCE_DIR}/Source/Movement/PlayerMovement.cpp
        ${CMAKE_SOURCE_DIR}/Source/Movement/PlayerMovement.h
        ${CMAKE_SOURCE_DIR}/Source/FileSystem/MapFileSystem.cpp
        ${CMAKE_SOURCE_DIR}/Source/FileSystem/MapFileSystem.h
        ${CMAKE_SOURCE_DIR}/Dependencies/Nlohmann/json.hpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${SFML_INCLUDE_DIR})
target_link_libraries (${PROJECT_NAME} PUBLIC sfml-graphics sfml-window sfml-system sfml-main)

if(64BIT AND MSVC OR MSYS OR MINGW OR WIN32)
    set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "windows_x86-64_TruGaming")
endif()
