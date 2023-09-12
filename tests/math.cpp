/**
 * @file    tests/ops.cpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains a test for the type operations of the library.
 * @date    2023-08-13
 * 
 * @copyright Copyright (c) 2023
 */


#include <gtest/gtest.h>

#include "ctda.hpp"

using namespace ctda;
using namespace units;


class QuantityTest : public ::testing::Test {
protected:
    using cm = unit<basis::length, std::ratio<1, 100>>;
    using s = units::second;
};


TEST_F(QuantityTest, QuantityArithmeticOperations) {
    // Addition
    auto a = quantity<double, cm>(1.0);
    auto b = quantity<double, cm>(2.0);
    auto c = quantity<double, cm>(3.0);
    auto result_add = a + b + c;
    ASSERT_EQ(result_add.value, 6.0);

    // Subtraction
    auto x = quantity<int, cm>(10);
    auto y = quantity<int, cm>(7);
    auto result_sub = x - y;
    ASSERT_EQ(result_sub.value, 3);

    // Multiplication
    auto p = quantity<float, cm>(2.5f);
    auto q = quantity<float, cm>(4.0f);
    auto result_mul = p * q;
    ASSERT_FLOAT_EQ(result_mul.value, 10.0f);

    // Division
    auto u = quantity<long double, cm>(12.0L);
    auto v = quantity<long double, cm>(3.0L);
    auto result_div = u / v;
    ASSERT_EQ(result_div.value, 4.0L);

    // Array Addition
    auto a_array = quantity<std::array<int, 3>, cm>({1, 2, 3});
    auto b_array = quantity<std::array<int, 3>, cm>({4, 5, 6});
    auto result_array_add = a_array + b_array;
    ASSERT_EQ(result_array_add.value[0], 5);
    ASSERT_EQ(result_array_add.value[1], 7);
    ASSERT_EQ(result_array_add.value[2], 9);

    // Matrix Subtraction
    auto a_matrix = quantity<std::array<std::array<int, 3>, 3>, cm>({
        {{9, 8, 7}, {6, 5, 4}, {3, 2, 1}}
    });
    auto b_matrix = quantity<std::array<std::array<int, 3>, 3>, cm>({
        {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}
    });
    auto result_matrix_sub = a_matrix - b_matrix;
    ASSERT_EQ(result_matrix_sub.value[0][0], 8);
    ASSERT_EQ(result_matrix_sub.value[1][1], 0);
    ASSERT_EQ(result_matrix_sub.value[2][2], -8);


    // Complex Addition
    auto a_complex = quantity<std::complex<double>, cm>({1., 2.});
    auto b_complex = quantity<std::complex<int>, cm>({3, 4});
    auto result_complex_add = a_complex + b_complex;
    ASSERT_DOUBLE_EQ(result_complex_add.value.real(), 4.0);
    ASSERT_DOUBLE_EQ(result_complex_add.value.imag(), 6.0);
    

    // Complex Multiplication
    auto result_complex_mul = a_complex * b_complex;
    ASSERT_DOUBLE_EQ(result_complex_mul.value.real(), -5.0);
    ASSERT_DOUBLE_EQ(result_complex_mul.value.imag(), 10.0);

}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}