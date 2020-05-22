set(SRC main.cpp
        CaveMap.cpp
        Game.cpp
        GameStatePlay.cpp
        TextureManager.cpp
        Tile.cpp)

add_executable(OpenRR ${SRC})

include_directories(${CMAKE_SOURCE_DIR}/include)

target_link_libraries(OpenRR sfml-graphics sfml-window sfml-system)