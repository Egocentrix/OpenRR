add_library(Workers STATIC
            Worker.cpp)     

target_include_directories(Workers PRIVATE ${OPENRR_INCLUDE_DIR}/Workers
                                           ${OPENRR_INCLUDE_DIR}/Common)