find_package(Catch2 3 REQUIRED)

# These tests can use the Catch2-provided main
add_executable(tests
               CaveMapTests.cpp
               CommonTests.cpp
)

target_include_directories(tests PRIVATE ${OPENRR_INCLUDE_DIR} 
                                         ${OPENRR_INCLUDE_DIR}/CaveMap
                                         ${OPENRR_INCLUDE_DIR}/Common
                                         ${OPENRR_INCLUDE_DIR}/Menu)

target_link_libraries(tests PRIVATE Catch2::Catch2WithMain sfml-graphics)
target_link_libraries(tests PRIVATE CaveMap OpenRR-Common)
