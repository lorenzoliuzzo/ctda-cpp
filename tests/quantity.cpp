/**
 * @file    tests/quantity.cpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains a test for the 'quantity' struct.
 * @date    2023-09-11
 * @copyright Copyright (c) 2023
 */


#include <gtest/gtest.h>

#include "ctda.hpp"

using namespace ctda;
using namespace units;
using namespace basis;


class QuantityTest : public testing::Test {
protected:
    using cm = unit<basis::length, std::ratio<1, 100>>;
    using s = units::second;
};


TEST_F(QuantityTest, QuantityConstruction) {

    constexpr auto a = quantity<double, cm>(1.0);
    constexpr auto b = quantity<int, s>(109);
    constexpr auto c = quantity<std::array<double, 3>, cm>({1.0, 2.0, 3.0});
    auto d = quantity<std::array<std::array<double, 3>, 3>, s>({
        {{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}}
    });

    std::cout << std::to_string(a) << std::endl;
    std::cout << std::to_string(b) << std::endl;
    std::cout << std::to_string(c) << std::endl;
    std::cout << std::to_string(d) << std::endl;

    size_t i = 0, j = 0;
    auto x = d(i, j);
    std::cout << std::to_string(x) << std::endl;
    std::cout << std::to_string(x) << std::endl;

    ASSERT_EQ(a.value, 1.0);
    ASSERT_EQ(b.value, 109);
    ASSERT_EQ(c.value, (std::array<double, 3>{1.0, 2.0, 3.0}));
    ASSERT_EQ(d.value[0], (std::array<double, 3>{1.0, 2.0, 3.0}));
    ASSERT_EQ(d.value[1], (std::array<double, 3>{4.0, 5.0, 6.0}));
    ASSERT_EQ(d.value[2], (std::array<double, 3>{7.0, 8.0, 9.0}));
    ASSERT_EQ(d.value[0][0], 1.0);
    // ASSERT_EQ((d(0, 0)), 1.0);
    // ASSERT_EQ(d(0), (quantity<std::array<double, 3>, cm>({1.0, 2.0, 3.0})));

}


int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}