/**
 * @file    ctda/core/quantity.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation of the 'quantity' struct.
 * @date    2023-09-11
 * @copyright Copyright (c) 2023
 */


#pragma once


namespace ctda {


    /// @brief This template meta-struct contains a physical quantity an union of a value and a 'unit'.
    /// @tparam The value stored in the quantity.
    /// @tparam The unit of the quantity.
    template <typename VALUE_T, typename UNIT_T = unit<dimensionless>>
        requires (is_unit_v<UNIT_T>)
    struct quantity {


        using base_t = UNIT_T::base_t; //< base of the quantity
        using unit_t = UNIT_T;         //< unit of the quantity
        using value_t = VALUE_T;       //< value type of the quantity


        value_t value;                 //< value stored in the quantity
        

        /// @brief Default constructor.
        constexpr quantity() noexcept : value{} {}
        
        /// @brief Constructor from a lhs value.
        /// @param value: The value_t object to be stored in the quantity.
        constexpr quantity(const value_t& value) noexcept : value{value} {}

        /// @brief Constructor from a rhs value.
        /// @param value: The value_t object to be stored in the quantity.
        constexpr quantity(value_t&& value) noexcept : value{std::move(value)} {}

        /// @brief Copy constructor.
        /// @param other: The quantity to be copied.
        constexpr quantity(const quantity& other) noexcept : value{other.value} {}

        /// @brief Move constructor.
        /// @param other: The quantity to be moved.
        constexpr quantity(quantity&& other) noexcept : value{std::move(other.value)} {}

        /// @brief Destructor.
        constexpr ~quantity() noexcept = default;


        /// @brief Copy assignment operator.
        /// @param other: The quantity to be copied.
        constexpr quantity& operator=(const quantity& other) noexcept = default;

        /// @brief Move assignment operator.
        /// @param other: The quantity to be moved.
        constexpr quantity& operator=(quantity&& other) noexcept = default;


        #if CTDA_QUANTITY_ACCESS_W_CURVY_BRACKETS
        
            /// @brief Access an element in the 'array-styled' quantity
            constexpr auto operator()(size_t i) noexcept -> decltype(auto) {

                auto val = this->value[i];
                return quantity<decltype(val), unit_t>(val);

            }

            /// @brief Access an element in the 'matrix-styled' quantity
            constexpr auto operator()(size_t i, size_t j) noexcept -> decltype(auto) {

                auto val = this->value[i][j];
                return quantity<decltype(val), unit_t>(val);

            }

            /// @brief Access an element in the 'tensor-styled' quantity
            constexpr auto operator()(size_t i, size_t j, size_t k) noexcept -> decltype(auto) {

                auto val = this->value[i][j][k];
                return quantity<decltype(val), unit_t>(val);
            }   

        #else

            /// @brief Access an element in the 'array-styled' quantity
            constexpr auto operator[](size_t i) noexcept {

                auto val = this->value[i];
                return quantity<decltype(val), unit_t>(val);

            }

        #endif


    }; // struct quantity


} // namespace ctda