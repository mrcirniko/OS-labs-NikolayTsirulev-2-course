#include "gtest/gtest.h"
#include "lib.hpp"

TEST(fourthLabTest, SortStaticTest1) {
    int array[] = {0, 1, 2, 3, 4, 5};
    int size = sizeof(array) / sizeof(int);
    int * result = Sort(array, size);
    for (int i = 0; i < size; ++i) {
        EXPECT_EQ(result[i], i);
    }
}

TEST(fourthLabTest, SortStaticTest2) {
    int array[] = {5, 4, 3, 2, 1, 0};
    int size = sizeof(array) / sizeof(int);
    int * result = Sort(array, size);
    for (int i = 0; i < size; ++i) {
        EXPECT_EQ(result[i], i);
    }
}

TEST(fourthLabTest, SortStaticTest3) {
    int array[] = {3, 5, 2, 1, 4, 0};
    int size = sizeof(array) / sizeof(int);
    int * result = Sort(array, size);
    for (int i = 0; i < size; ++i) {
        EXPECT_EQ(result[i], i);
    }
}

TEST(fourthLabTest, PrimeCountStaticTest1) {
    int result = PrimeCount(3, 15);
    EXPECT_EQ(result, 5);
}

TEST(fourthLabTest, PrimeCountStaticTest2) {
    int result = PrimeCount(5, 125);
    EXPECT_EQ(result, 28);
}

TEST(fourthLabTest, PrimeCountStaticTest3) {
    int result = PrimeCount(16, 1634);
    EXPECT_EQ(result, 252);
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}