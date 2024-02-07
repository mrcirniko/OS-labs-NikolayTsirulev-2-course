set(CMAKE_C_STANDARD 11)

add_executable(lab3
        main.cpp
        src/lab3.cpp
        include/utils.hpp src/utils.cpp)

target_include_directories(lab3 PRIVATE include)

add_executable(child
        src/child.cpp
        include/utils.hpp src/utils.cpp)

target_include_directories(child PRIVATE include)

add_dependencies(lab3 child)
