cmake_minimum_required(VERSION 3.16.3)
project(ArcanaWorld2D)
set(CMAKE_CXX_STANDARD 14)

#[[set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")]]
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/Library)

include_directories(
        Library/SDL2/include
        Library/SDL2_image/include
        Library/SDL2_ttf/include
)

link_directories(
        Library/SDL2/lib/x64
        Library/SDL2_image/lib/x64
        Library/SDL2_ttf/lib/x64
)

set(TARGET_LIBS
        SDL2main
        SDL2
        SDL2_image
        SDL2_ttf
        )

set(APP App.cpp)

file(GLOB WINDOW Window/*.cpp)

set(CONFIG Utility/Config.cpp)

file(GLOB BASES Utility/Base/*.cpp Utility/Base/Screen.h)

file(GLOB MANAGERS Manager/*.cpp)

file(GLOB SURFACE Surface/*.cpp Surface/Screens/*.cpp Surface/Entities/*.cpp Surface/Maps/*.cpp)

set(EXECUTABLE_CONNECTOR
        ${APP}
        ${WINDOW}
        ${CONFIG}
        ${BASES}
        ${MANAGERS}
        ${SURFACE}
        )

add_executable(${PROJECT_NAME} main.cpp ${EXECUTABLE_CONNECTOR})
target_link_libraries(${PROJECT_NAME} ${TARGET_LIBS})