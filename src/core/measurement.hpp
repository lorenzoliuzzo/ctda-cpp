/**
 * @file    ctda/core/measurement.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation of the 'measurement' struct.
 * @date    2023-10-30
 * @copyright Copyright (c) 2023
 */


#pragma once


namespace ctda {


    template <typename QUANTITY_T>
        requires (is_quantity_v<QUANTITY_T>)
    struct measurement {

        using value_t = QUANTITY_T::value_t;
        
        using quantity_t = QUANTITY_T;

        using measurement_t = measurement<quantity_t>;


        constexpr measurement(const value_t& val) noexcept : val{val}, unc{} {}
        
        constexpr measurement(const value_t& val, const value_t& unc) noexcept : val{val}, unc{unc} {}


        constexpr measurement(const quantity_t& val) noexcept : val{val.value}, unc{} {}
        
        constexpr measurement(const quantity_t& val, const quantity_t& unc) noexcept : val{val.value}, unc{unc.value} {}


        constexpr quantity_t value() const noexcept {
            return this->val; 
        }

        constexpr quantity_t uncertainty() const noexcept {
            return this->unc; 
        }

        value_t val, unc;


    }; // struct measurement


}