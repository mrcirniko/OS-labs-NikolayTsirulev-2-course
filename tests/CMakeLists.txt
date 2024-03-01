include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        release-1.11.0
)

FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)


set(CMAKE_CXX_STANDARD 17)

#lab1
#[===[
add_executable(lab1_test lab1_test.cpp ../lab1/src/lab1.cpp ../lab1/include/lab1.hpp
        ../lab1/src/utils.cpp ../lab1/include/utils.hpp)

target_link_libraries(lab1_test PRIVATE GTest::GTest)
target_include_directories(lab1_test PRIVATE ../lab1/include)
]===]

#lab2

add_test(lab2_test lab2_test)

add_executable(lab2_test lab2_test.cpp ../lab2/src/lab2.cpp ../lab2/include/lab2.hpp)

target_link_libraries(lab2_test PRIVATE GTest::GTest)
target_include_directories(lab2_test PRIVATE ../lab2/include)

add_test(lab2_test lab2_test)

#lab3

add_test(lab3_test lab3_test)

add_executable(lab3_test lab3_test.cpp ../lab3/src/lab3.cpp ../lab3/include/lab3.hpp
        ../lab3/src/utils.cpp ../lab3/include/utils.hpp)

target_link_libraries(lab3_test PRIVATE GTest::GTest)
target_include_directories(lab3_test PRIVATE ../lab3/include)

add_test(lab3_test lab3_test)

#lab4

add_executable(lab4_test1 lab4_test1.cpp ../lab4/include/lib.hpp 
        ../lab4/src/lib1.cpp)
target_link_libraries(lab4_test1 PRIVATE GTest::GTest)
target_include_directories(lab4_test1 PRIVATE ../lab4/include)

add_test(lab4_test1 lab4_test1)

add_executable(lab4_test2 lab4_test2.cpp ../lab4/include/lib.hpp 
        ../lab4/src/lib2.cpp)
target_link_libraries(lab4_test2 PRIVATE GTest::GTest)
target_include_directories(lab4_test2 PRIVATE ../lab4/include)

add_test(lab4_test2 lab4_test2)

#cp

add_executable(cp_test cp_test.cpp)
target_include_directories(cp_test PRIVATE ${CMAKE_SOURCE_DIR}/cp/include)
target_include_directories(cp_test PRIVATE ${CMAKE_SOURCE_DIR}/cp/lib)
target_link_libraries(cp_test PRIVATE cp_lib GTest::GTest)

