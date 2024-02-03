#include <gtest/gtest.h>

#include "lab2.hpp"

TEST(secondLabTests, ONE) {
    std::vector<std::vector<int>> matrix = { 
        { 1, 0, 0},
        { 0, 1, 0},
        { 0, 0, 1}
    };
    size_t threadQuantity = 1;
    ASSERT_EQ(calculateDeterminant(threadQuantity, matrix), 1);
}

TEST(secondLabTests, TWO) {
    std::vector<std::vector<int>> matrix = { 
            { 3, 6, 2, 9, 2 }, 
            { 5, 8, 3, 5, 2 }, 
            { 5, 4, 8, 10, 3 }, 
            { 1, 4, 7, 5, 5 }, 
            { 6, 9, 3, 1, 4 }
    };
    size_t threadQuantity = 1;
    ASSERT_EQ(calculateDeterminant(threadQuantity, matrix), 2717);
}

TEST(secondLabTests, THREE) {
    std::vector<std::vector<int>> matrix = { 
            { 3, 6, 2, 9, 2 }, 
            { 5, 8, 3, 5, 2 }, 
            { 5, 4, 8, 10, 3 }, 
            { 1, 4, 7, 5, 5 }, 
            { 6, 9, 3, 1, 4 }
    };
    size_t threadQuantity = 10;
    ASSERT_EQ(calculateDeterminant(threadQuantity, matrix), 2717);
}

TEST(secondLabTests, FOUR) {
    std::vector<std::vector<int>> matrix = { 
            { 2, 5, 6, 10, 3, 1, 5, 3, 1, 5, }, 
            { 3, 5, 7, 10, 4, 5, 3, 7, 10, 8, }, 
            { 7, 5, 8, 3, 7, 1, 8, 3, 1, 7, }, 
            { 10, 2, 4, 5, 4, 6, 5, 8, 8, 6, }, 
            { 3, 2, 10, 9, 3, 5, 5, 8, 4, 6, }, 
            { 5, 10, 10, 2, 2, 8, 4, 1, 2, 4, }, 
            { 9, 1, 8, 2, 5, 1, 7, 10, 10, 6, }, 
            { 7, 2, 9, 8, 2, 2, 3, 8, 9, 6, }, 
            { 3, 3, 7, 5, 6, 10, 2, 9, 10, 4, }, 
            { 3, 10, 6, 10, 2, 1, 2, 10, 2, 1, }
    };
    size_t threadQuantity = 1;
    ASSERT_EQ(calculateDeterminant(threadQuantity, matrix), 294535103);
}

TEST(secondLabTests, FIVE) {
    std::vector<std::vector<int>> matrix = { 
            { 2, 5, 6, 10, 3, 1, 5, 3, 1, 5, }, 
            { 3, 5, 7, 10, 4, 5, 3, 7, 10, 8, }, 
            { 7, 5, 8, 3, 7, 1, 8, 3, 1, 7, }, 
            { 10, 2, 4, 5, 4, 6, 5, 8, 8, 6, }, 
            { 3, 2, 10, 9, 3, 5, 5, 8, 4, 6, }, 
            { 5, 10, 10, 2, 2, 8, 4, 1, 2, 4, }, 
            { 9, 1, 8, 2, 5, 1, 7, 10, 10, 6, }, 
            { 7, 2, 9, 8, 2, 2, 3, 8, 9, 6, }, 
            { 3, 3, 7, 5, 6, 10, 2, 9, 10, 4, }, 
            { 3, 10, 6, 10, 2, 1, 2, 10, 2, 1, }
    };
    size_t threadQuantity = 10;
    ASSERT_EQ(calculateDeterminant(threadQuantity, matrix), 294535103);
}

TEST(secondLabTests, SIX) {
    std::vector<std::vector<int>> matrix = { 
            { 2, 5, 6, 10, 3, 1, 5, 3, 1, 5, }, 
            { 3, 5, 7, 10, 4, 5, 3, 7, 10, 8, }, 
            { 7, 5, 8, 3, 7, 1, 8, 3, 1, 7, }, 
            { 10, 2, 4, 5, 4, 6, 5, 8, 8, 6, }, 
            { 3, 2, 10, 9, 3, 5, 5, 8, 4, 6, }, 
            { 5, 10, 10, 2, 2, 8, 4, 1, 2, 4, }, 
            { 9, 1, 8, 2, 5, 1, 7, 10, 10, 6, }, 
            { 7, 2, 9, 8, 2, 2, 3, 8, 9, 6, }, 
            { 3, 3, 7, 5, 6, 10, 2, 9, 10, 4, }, 
            { 3, 10, 6, 10, 2, 1, 2, 10, 2, 1, }
    };
    size_t threadQuantity = 350;
    ASSERT_EQ(calculateDeterminant(threadQuantity, matrix), 294535103);
}

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}