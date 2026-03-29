add_library(Menu STATIC
            ContextMenu.cpp
            Gui.cpp)     

target_include_directories(Menu PRIVATE ${OPENRR_INCLUDE_DIR}/Menu
                                        ${OPENRR_INCLUDE_DIR}/Common)