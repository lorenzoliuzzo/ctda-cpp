/**
 * @file    math/algebraic/add.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation of the add struct.
 * @date    2023-08-12
 * 
 * @copyright Copyright (c) 2023
 */

#pragma once


namespace ctda {


    namespace math {


        /// @brief Add specialization for numbers
        template <typename T1, typename T2>
            requires (std::is_arithmetic_v<T1> && std::is_arithmetic_v<T2>)
        struct add_impl<T1, T2> {

            using result_t = decltype(std::declval<T1>() + std::declval<T2>());

            static constexpr result_t f(const T1& a, const T2& b) noexcept {
                return a + b;
            }                                             

        };


        /// @brief Add specialization for complex numbers
        template <typename T1, typename T2>
        struct add_impl<std::complex<T1>, std::complex<T2>> {

            using result_t = std::complex<decltype(std::declval<T1>() + std::declval<T2>())>;

            static constexpr result_t f(const std::complex<T1>& a, const std::complex<T2>& b) noexcept {
                return {a.real() + b.real(), a.imag() + b.imag()};
            }                                             

        };        


        /// @brief Add specialization for array
        template <typename T1, typename T2, size_t N>
        struct add_impl<std::array<T1, N>, std::array<T2, N>> {

            using result_t = std::array<std::common_type_t<T1, T2>, N>;

            static constexpr result_t f(const std::array<T1, N>& a, const std::array<T2, N>& b) noexcept {
                
                result_t result{};
                for (size_t i = 0; i < N; ++i) 
                    result[i] = a[i] + b[i];
                return result;

            }                                             

        };


        template <typename T1, typename T2>
        struct add_impl<std::vector<T1>, std::vector<T2>> {

            using result_t = std::vector<std::common_type_t<T1, T2>>;

            static constexpr result_t f(const std::vector<T1>& a, const std::vector<T2>& b) {
                
                if (a.size() != b.size())
                    throw std::runtime_error("Cannot add vectors of different sizes");

                result_t result(a.size());
                for (size_t i = 0; i < a.size(); ++i) 
                    result[i] = a[i] + b[i];
                return result;

            }                                             

        };
        

        /// @brief Add specialization for numbers and arrays
        template <typename T1, typename T2, size_t N>
            requires (std::is_arithmetic_v<T1>)
        struct add_impl<T1, std::array<T2, N>> {

            using result_t = std::array<add_t<T1, T2>, N>;

            static constexpr result_t f(const T1& a, const std::array<T2, N>& b) noexcept {
                
                result_t result{};
                for (size_t i = 0; i < N; ++i) 
                    result[i] = a + b[i];
                return result;

            }                                             

        };

        template <typename T1, size_t N, typename T2>
            requires (std::is_arithmetic_v<T2>)
        struct add_impl<std::array<T1, N>, T2> {

            using result_t = std::array<add_t<T1, T2>, N>;

            static constexpr result_t f(const std::array<T1, N>& a, const T2& b) noexcept {
                
                result_t result{};
                for (size_t i = 0; i < N; ++i) 
                    result[i] = a[i] + b;
                return result;

            }                                             

        };


        /// @brief Add specialization for quantities
        /// @tparam T1
        /// @tparam T2
        template <typename T1, typename T2>
            requires (are_quantity_v<T1, T2> && std::is_same_v<typename T1::base_t, typename T2::base_t>)
        struct add_impl<T1, T2> {

            using result_t = quantity<add_t<typename T1::value_t, typename T2::value_t>, 
                                      typename T1::unit_t>;

            static constexpr result_t f(const T1& x, const T2& y) noexcept {

                if constexpr (std::is_same_v<typename T1::unit_t, typename T2::unit_t>) 
                    return x.value + y.value;
                else
                    return x.value + y.value * conversion_factor(typename T1::unit_t{}, typename T2::unit_t{});

            }

        };


        /// @brief Add specialization for quantities and numbers, complex numbers, arrays
        template <typename T1, typename T2>
            requires (is_quantity_v<T1> && std::is_same_v<typename T1::base_t, basis::dimensionless>)
                && (std::is_arithmetic_v<T2> || is_complex_v<T2> || std::is_array_v<T2>)
        struct add_impl<T1, T2> {

            using result_t = quantity<add_t<typename T1::value_t, T2>, typename T1::unit_t>;

            static constexpr result_t f(const T1& x, const T2& y) noexcept {
                return x.value + y;
            }
            
        };

        template <typename T1, typename T2>
            requires (std::is_arithmetic_v<T2> || is_complex_v<T2> || std::is_array_v<T2>)
                && (is_quantity_v<T2> && std::is_same_v<typename T2::base_t, basis::dimensionless>)
        struct add_impl<T1, T2> {

            using result_t = quantity<add_t<T1, typename T2::value_t>, typename T2::unit_t>;

            static constexpr result_t f(const T1& x, const T2& y) noexcept {
                return x + y.value;
            }
            
        };


    } // namespace math


} // namespace ctda