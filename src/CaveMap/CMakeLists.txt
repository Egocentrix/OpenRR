add_library(CaveMap STATIC
            CaveMap.cpp
            CaveMapLogic.cpp
            MapRenderer.cpp
            Tile.cpp)

target_include_directories(CaveMap PRIVATE ${OPENRR_INCLUDE_DIR}/CaveMap
                                           ${OPENRR_INCLUDE_DIR}/Common)