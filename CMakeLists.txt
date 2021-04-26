cmake_minimum_required(VERSION 3.10)
project(TruGaming)
set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_FLAGS_DEBUG "-O0")
set(CMAKE_CXX_FLAGS_DEBUG "-ggdb3")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/Executable/")
set(CMAKE_BINARY_DIR "${CMAKE_SOURCE_DIR}/Executable/")

add_compile_options(
        -Wall -Wno-error=maybe-uninitialized -pedantic --all-warnings -Wextra
)
if (CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(64BIT TRUE)
    set(ARCHITECTURE "x86-64")
else ()
    set(64BIT FALSE)
    set(ARCHITECTURE "x64")
endif ()

if (MSVC OR MSYS OR WIN32)

    #FOR NOW WINDOW USES DYNAMIC SFML LIBRARIES and bundles std libs together so sent file only contains exe and sfml dll
    if (64BIT)

        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static")
        set(CMAKE_CXX_STANDARD_LIBRARIES "-static-libgcc -static-libstdc++ -lpthread ${CMAKE_CXX_STANDARD_LIBRARIES}")

        set(SFML_STATIC_LIBRARIES FALSE)

        set(SFML_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/Dependencies/SFML/RELEASE/64Bit/OS_WINDOWS/include")
        set(SFML_LIBRARY_DIR "${CMAKE_SOURCE_DIR}/Dependencies/SFML/RELEASE/64Bit/OS_WINDOWS/lib")
        set(SFML_DIR "${CMAKE_SOURCE_DIR}/Dependencies/SFML/RELEASE/64Bit/OS_WINDOWS/lib/cmake/SFML/")

    else ()
        set(SFML_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/Dependencies/SFML/RELEASE/32Bit/OS_WINDOWS/include")
        set(SFML_LIBRARY_DIR "${CMAKE_SOURCE_DIR}/Dependencies/SFML/RELEASE/32Bit/OS_WINDOWS/lib")
        set(SFML_DIR "${CMAKE_SOURCE_DIR}/Dependencies/SFML/RELEASE/32Bit/OS_WINDOWS/lib/cmake/SFML/")
    endif ()

    find_package(SFML 2.5.1 REQUIRED COMPONENTS system window graphics audio network main)
elseif (APPLE AND NOT UNIX)
    message(FATAL_ERROR "Not supported on OSX at this time...")
elseif (UNIX)
    #FOR NOW LINUX USES DYNAMIC LIBRARIES as well
    set(CMAKE_C_FLAGS -m64)
    set(CMAKE_CXX_FLAGS -m64)

    set(SFML_STATIC_LIBRARIES FALSE)

    set(SFML_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/Dependencies/SFML/RELEASE/64Bit/OS_LINUX/include")
    set(SFML_LIBRARY_DIR "${CMAKE_SOURCE_DIR}/Dependencies/SFML/RELEASE/64Bit/OS_LINUX/lib")
    set(SFML_DIR "${CMAKE_SOURCE_DIR}/Dependencies/SFML/RELEASE/64Bit/OS_LINUX/lib/cmake/SFML/")

    find_package(SFML 2.5.1 REQUIRED COMPONENTS system window graphics audio network)

endif ()


add_executable(${PROJECT_NAME}
        ${CMAKE_SOURCE_DIR}/Source/GameManager/Entities/Tilemap.h
        ${CMAKE_SOURCE_DIR}/Source/Application.cpp
        ${CMAKE_SOURCE_DIR}/Source/Application.h
        ${CMAKE_SOURCE_DIR}/Source/GameManager/Entities/GameChunk.cpp
        ${CMAKE_SOURCE_DIR}/Source/GameManager/Entities/GameChunk.h
        ${CMAKE_SOURCE_DIR}/Dependencies/Nlohmann/json.hpp
        ${CMAKE_SOURCE_DIR}/Source/GameManager/Entities/Entity.h
        ${CMAKE_SOURCE_DIR}/Source/Constants/Singleton.h
        ${CMAKE_SOURCE_DIR}/Source/GameManager/GameText/GameText.cpp
        ${CMAKE_SOURCE_DIR}/Source/GameManager/GameText/GameText.h
        ${CMAKE_SOURCE_DIR}/Source/GameManager/MapEditor/MapUpdater.cpp
        ${CMAKE_SOURCE_DIR}/Source/GameManager/MapEditor/MapUpdater.h

        ${CMAKE_SOURCE_DIR}/Source/GameManager/Graphics/Animation.cpp
        ${CMAKE_SOURCE_DIR}/Source/GameManager/Graphics/Animation.h
        ${CMAKE_SOURCE_DIR}/Source/GameManager/Entities/Player.h

        ${CMAKE_SOURCE_DIR}/Dependencies/Kairos/Kairos.hpp
        ${CMAKE_SOURCE_DIR}/Dependencies/Kairos/Kairos/all.hpp

        ${CMAKE_SOURCE_DIR}/Dependencies/Kairos/Kairos/BasicClock.cpp
        ${CMAKE_SOURCE_DIR}/Dependencies/Kairos/Kairos/Continuum.cpp
        ${CMAKE_SOURCE_DIR}/Dependencies/Kairos/Kairos/Duration.cpp
        ${CMAKE_SOURCE_DIR}/Dependencies/Kairos/Kairos/FpsLite.cpp
        ${CMAKE_SOURCE_DIR}/Dependencies/Kairos/Kairos/Stopwatch.cpp
        ${CMAKE_SOURCE_DIR}/Dependencies/Kairos/Kairos/Timer.cpp
        ${CMAKE_SOURCE_DIR}/Dependencies/Kairos/Kairos/Timestep.cpp
        ${CMAKE_SOURCE_DIR}/Dependencies/Kairos/Kairos/TimestepLite.cpp

        ${CMAKE_SOURCE_DIR}/Dependencies/Kairos/Kairos/BasicClock.hpp
        ${CMAKE_SOURCE_DIR}/Dependencies/Kairos/Kairos/Continuum.hpp
        ${CMAKE_SOURCE_DIR}/Dependencies/Kairos/Kairos/Duration.hpp
        ${CMAKE_SOURCE_DIR}/Dependencies/Kairos/Kairos/FpsLite.hpp
        ${CMAKE_SOURCE_DIR}/Dependencies/Kairos/Kairos/Stopwatch.hpp
        ${CMAKE_SOURCE_DIR}/Dependencies/Kairos/Kairos/Timer.hpp
        ${CMAKE_SOURCE_DIR}/Dependencies/Kairos/Kairos/Timestep.hpp
        ${CMAKE_SOURCE_DIR}/Dependencies/Kairos/Kairos/TimestepLite.hpp
        ${CMAKE_SOURCE_DIR}/Source/GameManager/Views/View.h
        ${CMAKE_SOURCE_DIR}/Source/GameManager/Views/TitleScreen.cpp
        ${CMAKE_SOURCE_DIR}/Source/GameManager/Views/TitleScreen.h
        ${CMAKE_SOURCE_DIR}/Source/GameManager/States/State.h
        Source/GameManager/Views/WorldView.cpp
        Source/GameManager/Views/WorldView.h
        Source/Audio/Audio.h)

target_include_directories(${PROJECT_NAME} PUBLIC ${SFML_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} PUBLIC sfml-graphics sfml-window sfml-system sfml-main sfml-audio)

if (MSVC OR MSYS OR MINGW OR WIN32)
    set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "windows_${ARCHITECTURE}_TruGaming")
elseif (APPLE AND NOT UNIX AND 64BIT)
    set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "osx_${ARCHITECTURE}_TruGaming")
elseif (UNIX AND 64BIT)
    set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME "linux_${ARCHITECTURE}_TruGaming")
endif ()
