add_library(CaveMap STATIC
            Camera.cpp            
            CaveMap.cpp
            CaveMapLoader.cpp
            CaveMapLogic.cpp
            MapCommands.cpp
            MapRenderer.cpp
            PathFinder.cpp
            Tile.cpp)

target_include_directories(CaveMap PRIVATE ${OPENRR_INCLUDE_DIR}/CaveMap
                                           ${OPENRR_INCLUDE_DIR}/Common)