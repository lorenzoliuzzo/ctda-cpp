/**
 * @file    ctda/core/base_quantity.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation of the base_quantity struct.
 * @date    2023-09-11
 * @copyright Copyright (c) 2023
 */


#pragma once


namespace ctda {
    

    /// @brief This template meta-structure contains the dimensional information for a physical quantity.
    template <int LENGTH, int TIME, int MASS, int TEMPERATURE, int ELETTRIC_CURRENT, int SUBSTANCE_AMOUNT, int LUMINOUS_INTENSITY> 
    struct base_quantity {

        /// powers of the base_quantity
        static constexpr std::array<int, 7> powers = {LENGTH, TIME, MASS, TEMPERATURE, ELETTRIC_CURRENT, SUBSTANCE_AMOUNT, LUMINOUS_INTENSITY};
        
    }; // struct base_quantity


    /// @brief Literals of the SI base quantities
    static constexpr std::array<std::string_view, 7> base_unit_literals = {"m", "s", "kg", "K", "A", "mol", "cd"};                               


} // namespace ctda