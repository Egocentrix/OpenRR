add_library(OpenRR-Common STATIC
            Helpers.cpp 
            TextureManager.cpp)       

target_include_directories(OpenRR-Common PRIVATE ${OPENRR_INCLUDE_DIR}/Common)