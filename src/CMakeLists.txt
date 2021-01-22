set(SRC main.cpp
        CaveMap.cpp
        Game.cpp
        GameStatePlay.cpp
        Helpers.cpp
        TextureManager.cpp
        Tile.cpp)

add_executable(OpenRR ${SRC})

target_include_directories(OpenRR PRIVATE ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(OpenRR PRIVATE sfml-graphics sfml-window sfml-system)