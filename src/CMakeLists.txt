

set(SRC main.cpp
        Game.cpp
        GameStatePlay.cpp
        )

add_executable(OpenRR ${SRC})

target_include_directories(OpenRR PRIVATE ${OPENRR_INCLUDE_DIR} 
                                          ${OPENRR_INCLUDE_DIR}/CaveMap
                                          ${OPENRR_INCLUDE_DIR}/Common
                                          ${OPENRR_INCLUDE_DIR}/Menu
                                          ${OPENRR_INCLUDE_DIR}/Workers)


add_subdirectory(Common)
add_subdirectory(CaveMap)
add_subdirectory(Menu)
add_subdirectory(Workers)

target_link_libraries(OpenRR PRIVATE sfml-graphics sfml-window sfml-system)
target_link_libraries(OpenRR PRIVATE OpenRR-Common CaveMap Menu Workers)
