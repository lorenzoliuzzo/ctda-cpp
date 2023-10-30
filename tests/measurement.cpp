/**
 * @file    tests/measurement.cpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains a test for the 'measurement' struct.
 * @date    2023-10-30
 * @copyright Copyright (c) 2023
 */


#include "ctda.hpp"
#include <iostream>

using namespace ctda;


int main() {

    quantity<double, units::meter> q(1);
    std::cout << q << '\n';

    measurement<decltype(q)> m(q.value, 0.1);

    std::cout << m << '\n';


    static_assert(are_same_quantity_v<decltype(q), decltype(q)>);
    static_assert(are_same_quantity_v<decltype(q), decltype(q), decltype(q)>);

    auto x = q + q; 
    std::cout << x << '\n';

    auto y = m + m; 
    std::cout << y.value() << '\n';
    std::cout << y.uncertainty() << '\n';

    std::cout << sizeof(x) << '\n';
    std::cout << sizeof(y) << '\n';

    std::cout << std::to_string(basis::momentum{}) << '\n';
    
    return 0; 

}