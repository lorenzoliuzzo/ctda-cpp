/**
 * @file    ctda/core/unit.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation of the 'unit' struct.
 * @date    2023-09-11
 * @copyright Copyright (c) 2023
 */


#pragma once


namespace ctda {


    /// @brief  Struct unit is an union of a 'base_quantity' and an 'std::ratio' prefix
    /// @tparam BASE_TYPE: base_quantity
    /// @tparam PREFIX_TYPE: std::ratio
    template <typename BASE_T, typename PREFIX_T = std::ratio<1>> 
        requires (is_base_v<BASE_T> && is_prefix_v<PREFIX_T>)
    struct unit {

        using base_t = BASE_T;

        using prefix_t = PREFIX_T;


        static constexpr long double factor = static_cast<double>(prefix_t::num) / static_cast<double>(prefix_t::den);

    }; // struct unit


} // namespace ctda