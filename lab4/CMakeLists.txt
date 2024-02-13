set(CMAKE_CXX_STANDARD 17)

add_library(lib1 SHARED src/lib1.cpp)
add_library(lib2 SHARED src/lib2.cpp)

target_include_directories(lib1 PUBLIC include)
target_include_directories(lib2 PUBLIC include)

add_executable(static_main static_main.cpp)
target_link_libraries(static_main PRIVATE lib1)

add_executable(dynamic_main dynamic_main.cpp include/utils.hpp src/utils.cpp)
target_link_libraries(dynamic_main dl)
target_include_directories(dynamic_main PRIVATE include)