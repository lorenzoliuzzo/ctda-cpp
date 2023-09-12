/**
 * @file    traits.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the ctda type traits.
 * @date    2023-08-12
 * @copyright Copyright (c) 2023
 */


#pragma once


namespace ctda {


    template <int LENGTH, int TIME, int MASS, int TEMPERATURE, int ELETTRIC_CURRENT, int SUBSTANCE_AMOUNT, int LUMINOUS_INTENSITY>
    struct base_quantity;

    /// @brief This template meta-struct checks if a type is a base.
    template <typename T>
    struct is_base : std::false_type {};

    template <int LENGTH, int TIME, int MASS, int TEMPERATURE, int ELETTRIC_CURRENT, int SUBSTANCE_AMOUNT, int LUMINOUS_INTENSITY>
    struct is_base<base_quantity<LENGTH, TIME, MASS, TEMPERATURE, ELETTRIC_CURRENT, SUBSTANCE_AMOUNT, LUMINOUS_INTENSITY>> : std::true_type {};
    
    template <typename T>
    inline constexpr bool is_base_v = is_base<T>::value;

    template <typename... Ts>
    inline constexpr bool are_base_v = std::conjunction_v<is_base<Ts>...>;

    /// @brief This template meta-struct checks if two base are the same.
    template <typename T1, typename T2>
        requires (are_base_v<T1, T2>)
    inline constexpr bool are_same_base_v = std::is_same_v<typename T1::powers, typename T2::powers>;


    /// @brief This template meta-struct checks if a type is a prefix.
    template <typename T>
    struct is_prefix : std::false_type {};

    template <intmax_t EXPONENT, intmax_t BASE_EXPONENT>
    struct is_prefix<std::ratio<EXPONENT, BASE_EXPONENT>> : std::true_type {};

    template <typename T>
    inline constexpr bool is_prefix_v = is_prefix<T>::value;

    template <typename... Ts>
    inline constexpr bool are_prefix_v = std::conjunction_v<is_prefix<Ts>...>;


    template <typename base_t, typename prefix_t>
        requires (is_base_v<base_t> && is_prefix_v<prefix_t>)
    struct unit;

    /// @brief This template meta-struct checks if a type is a unit.
    template <typename T>
    struct is_unit : std::false_type {};

    template <typename base_t, typename prefix_t>
    struct is_unit<unit<base_t, prefix_t>> : std::true_type {};

    template <typename T>
    inline constexpr bool is_unit_v = is_unit<T>::value;

    template <typename... Ts>
    inline constexpr bool are_unit_v = std::conjunction_v<is_unit<Ts>...>;

    template <typename FROM, typename TO>
        requires (are_unit_v<FROM, TO> && std::is_same_v<typename FROM::base_t, typename TO::base_t>)
    constexpr auto convertion_factor(const FROM&, const TO& ) {
        return FROM::factor / TO::factor;
    }


    template <typename value_t, typename unit_t>
        requires (is_unit_v<unit_t>)
    struct quantity;

    /// @brief This template meta-struct checks if a type is a quantity.
    template <typename T>
    struct is_quantity : std::false_type {};

    template <typename VALUE_T, typename UNIT_T>
    struct is_quantity<quantity<VALUE_T, UNIT_T>> : std::true_type {};

    template <typename T>
    inline constexpr bool is_quantity_v = is_quantity<T>::value;

    template <typename... Ts>
    inline constexpr bool are_quantity_v = std::conjunction_v<is_quantity<Ts>...>;


    template <typename T>
    struct is_complex : std::false_type {};

    template <typename T>
    struct is_complex<std::complex<T>> : std::true_type {};

    template <typename T>
    inline constexpr bool is_complex_v = is_complex<T>::value;

    template <typename... Ts>
    inline constexpr bool are_complex_v = std::conjunction_v<is_complex<Ts>...>;


} // namespace ctda