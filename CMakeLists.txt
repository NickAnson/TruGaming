cmake_minimum_required(VERSION 3.10)
project(TruGaming)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS_DEBUG "-Os")
set(CMAKE_CXX_FLAGS_RELEASE "-Os")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/Executable/")
set(CMAKE_BINARY_DIR "${CMAKE_SOURCE_DIR}/Executable/")

if (CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(64BIT TRUE)
    set(ARCHITECTURE "x86-64")
else ()
    set(64BIT FALSE)
    set(ARCHITECTURE "x64")
endif ()

if (MSVC OR MSYS OR MINGW OR WIN32)
    #FOR NOW WINDOW USES DYNAMIC SFML LIBRARIES and bundles std libs together so sent file only contains exe and sfml dll
    set(CMAKE_CXX_STANDARD_LIBRARIES "-static-libgcc -static-libstdc++ -lwsock32 -lws2_32 ${CMAKE_CXX_STANDARD_LIBRARIES}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Bstatic,--whole-archive -Wl,--no-whole-archive")

    if (64BIT)
        set(SFML_STATIC_LIBRARIES FALSE)

        set(SFML_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/Dependencies/SFML/RELEASE/64Bit/OS_WINDOWS/include")
        set(SFML_LIBRARY_DIR "${CMAKE_SOURCE_DIR}/Dependencies/SFML/RELEASE/64Bit/OS_WINDOWS/lib")
        set(SFML_DIR "${CMAKE_SOURCE_DIR}/Dependencies/SFML/RELEASE/64Bit/OS_WINDOWS/lib/cmake/SFML/")

    else ()
        set(SFML_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/Dependencies/SFML/RELEASE/32Bit/OS_WINDOWS/include")
        set(SFML_LIBRARY_DIR "${CMAKE_SOURCE_DIR}/Dependencies/SFML/RELEASE/32Bit/OS_WINDOWS/lib")
        set(SFML_DIR "${CMAKE_SOURCE_DIR}/Dependencies/SFML/RELEASE/32Bit/OS_WINDOWS/lib/cmake/SFML/")
    endif ()
    find_package(SFML 2.5.1 REQUIRED COMPONENTS network system window graphics audio main)
elseif (APPLE AND NOT UNIX)
    message(FATAL_ERROR "Not supported on OSX at this time...")
elseif (UNIX)
    #FOR NOW LINUX USES DYNAMIC LIBRARIES as well
    if (64BIT)

        set(SFML_STATIC_LIBRARIES FALSE)

        set(SFML_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/Dependencies/SFML/RELEASE/64Bit/OS_LINUX/include")
        set(SFML_LIBRARY_DIR "${CMAKE_SOURCE_DIR}/Dependencies/SFML/RELEASE/64Bit/OS_LINUX/lib")
        set(SFML_DIR "${CMAKE_SOURCE_DIR}/Dependencies/SFML/RELEASE/64Bit/OS_LINUX/lib/cmake/SFML/")

        find_package(SFML 2.5.1 REQUIRED COMPONENTS network system window graphics audio)

    else ()
        message(FATAL_ERROR "Not supported on 32Bit Linux at this time...")

    endif ()
endif ()

add_executable(${PROJECT_NAME}
        ${CMAKE_SOURCE_DIR}/Source/Application.cpp
        ${CMAKE_SOURCE_DIR}/Source/Application.h
        ${CMAKE_SOURCE_DIR}/Source/TextureManager/Tilemap.h
        ${CMAKE_SOURCE_DIR}/Source/Movement/PlayerMovement.cpp
        ${CMAKE_SOURCE_DIR}/Source/Movement/PlayerMovement.h
        ${CMAKE_SOURCE_DIR}/Source/FileSystem/MapFileSystem.cpp
        ${CMAKE_SOURCE_DIR}/Source/FileSystem/MapFileSystem.h
        ${CMAKE_SOURCE_DIR}/Dependencies/Nlohmann/json.hpp Source/TextureManager/Tile.h)

target_include_directories(${PROJECT_NAME} PUBLIC ${SFML_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC sfml-graphics sfml-window sfml-system)

if (MSVC OR MSYS OR MINGW OR WIN32)
    set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "windows_${ARCHITECTURE}_TruGaming")
elseif (APPLE AND NOT UNIX AND 64BIT)
    set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "osx_${ARCHITECTURE}_TruGaming")
elseif (UNIX AND 64BIT)
    set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "linux_${ARCHITECTURE}_TruGaming")
endif ()
