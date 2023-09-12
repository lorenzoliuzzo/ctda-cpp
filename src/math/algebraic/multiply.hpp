/**
 * @file    math/algebraic/multiply.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation of the multiply struct.
 * @date    2023-08-12
 * 
 * @copyright Copyright (c) 2023
 */

#pragma once


namespace ctda {


    namespace math {


        /// @brief Multiply specialization for base_quantities
        template <typename T1, typename T2>
            requires (are_base_v<T1, T2>)
        struct multiply_impl<T1, T2> {

            using result_t = base_quantity<T1::powers[0] + T2::powers[0],
                                           T1::powers[1] + T2::powers[1],
                                           T1::powers[2] + T2::powers[2],
                                           T1::powers[3] + T2::powers[3],
                                           T1::powers[4] + T2::powers[4],
                                           T1::powers[5] + T2::powers[5],
                                           T1::powers[6] + T2::powers[6]>;

            static constexpr result_t f(const T1&, const T2&) noexcept {
                return {};
            }                                             

        };



        /// @brief Multiply specialization for prefixes 
        template <typename T1, typename T2>
            requires (are_prefix_v<T1, T2>)
        struct multiply_impl<T1, T2> {
            
            using result_t = std::ratio_multiply<T1, T2>;

            static constexpr result_t f(const T1&, const T2&) noexcept {
                return {};
            }                                             
            
        };


        /// @brief Multiply specialization for prefix and unit
        template <typename T1, typename T2>
        requires (is_prefix_v<T1> && is_unit_v<T2>)
        struct multiply_impl<T1, T2> {
            
            using result_t = unit<typename T2::base_t, multiply_t<T1, typename T2::prefix_t>>;

            static constexpr result_t f(const T1&, const T2&) noexcept {
                return {};
            }
            
        };
        

        /// @brief Multiply specialization for units
        template <typename T1, typename T2>
            requires (are_unit_v<T1, T2>)
        struct multiply_impl<T1, T2> { 
            
            using result_t = unit<multiply_t<typename T1::base_t, typename T2::base_t>, 
                                  multiply_t<typename T1::prefix_t, typename T2::prefix_t>>;

            static constexpr result_t f(const T1&, const T2&) noexcept {
                return {};
            }       

        };


        /// @brief Multiply specialization for numbers
        template <typename T1, typename T2>
            requires (std::is_arithmetic_v<T1> && std::is_arithmetic_v<T2>)
        struct multiply_impl<T1, T2> {

            using result_t = std::common_type_t<T1, T2>;

            static constexpr result_t f(const T1& a, const T2& b) noexcept {
                return a * b;
            }                                             

        };


        /// @brief Multiply specialization for complex numbers
        template <typename T1, typename T2>
        struct multiply_impl<std::complex<T1>, std::complex<T2>> {

            using result_t = std::complex<std::common_type_t<T1, T2>>;

            static constexpr result_t f(const std::complex<T1>& a, const std::complex<T2>& b) noexcept {
                return {a.real() * b.real() - a.imag() * b.imag(), 
                        a.real() * b.imag() + a.imag() * b.real()};
            }                                             
            
        }; 
        

        /// @brief Multiply specialization for numbers and arrays
        template <typename T1, typename T2, size_t N>
            requires (std::is_arithmetic_v<T1> || is_complex_v<T1>)
        struct multiply_impl<T1, std::array<T2, N>> {

            using result_t = std::array<multiply_t<T1, T2>, N>;

            static constexpr result_t f(const T1& a, const std::array<T2, N>& b) noexcept {
                
                result_t result{};
                for (size_t i = 0; i < N; ++i) 
                    result[i] = a * b[i];
                return result;

            }                                             

        };

        template <typename T1, size_t N, typename T2>
            requires (std::is_arithmetic_v<T2> || is_complex_v<T2>)
        struct multiply_impl<std::array<T1, N>, T2> {

            using result_t = std::array<multiply_t<T1, T2>, N>;

            static constexpr result_t f(const std::array<T1, N>& a, const T2& b) noexcept {
                
                result_t result{};
                for (size_t i = 0; i < N; ++i) 
                    result[i] = a[i] * b;
                return result;

            }                                             

        };


        /// @brief Multiply specialization for quantities
        template <typename T1, typename T2>
            requires (are_quantity_v<T1, T2>)
        struct multiply_impl<T1, T2> {

            using result_t = quantity<multiply_t<typename T1::value_t, typename T2::value_t>, 
                                      multiply_t<typename T1::unit_t, typename T2::unit_t>>;

            static constexpr result_t f(const T1& x, const T2& y) noexcept {
                return x.value * y.value;
            }

        };


        /// @brief Multiply specialization for quantities and numbers
        template <typename T1, typename T2>
            requires (is_quantity_v<T1> && (std::is_arithmetic_v<T2> || is_complex_v<T2>))
        struct multiply_impl<T1, T2> {

            using result_t = quantity<multiply_t<typename T1::value_t, T2>, typename T1::unit_t>;

            static constexpr result_t f(const T1& x, const T2& y) noexcept {
                return x.value * y;
            }
            
        };

        template <typename T1, typename T2>
            requires ((std::is_arithmetic_v<T1> || is_complex_v<T1>) && is_quantity_v<T2>)
        struct multiply_impl<T1, T2> {

            using result_t = quantity<multiply_t<T1, typename T2::value_t>, typename T2::unit_t>;

            static constexpr result_t f(const T1& x, const T2& y) noexcept {
                return x * y.value;
            }
            
        };


        /// @brief Multiply specialization for quantity and array
        template <typename T1, typename T2, size_t N>
            requires (is_quantity_v<T1> && std::is_arithmetic_v<typename T1::value_t> && std::is_arithmetic_v<T2>)
        struct multiply_impl<T1, std::array<T2, N>> {

            using result_t = quantity<std::array<multiply_t<typename T1::value_t, T2>, N>, typename T1::unit_t>;

            static constexpr result_t f(const T1& a, const std::array<T2, N>& b) noexcept {
                
                result_t result{};
                for (size_t i = 0; i < N; ++i) 
                    result.value[i] = a.value * b[i];
                return result;

            }                                             

        };     

        template <typename T1, size_t N, typename T2>
            requires (std::is_arithmetic_v<T1> && is_quantity_v<T2> && std::is_arithmetic_v<typename T2::value_t>)
        struct multiply_impl<std::array<T1, N>, T2> {

            using result_t = quantity<std::array<multiply_t<T1, typename T2::value_t>, N>, typename T2::unit_t>;

            static constexpr result_t f(const std::array<T1, N>& a, const T2& b) noexcept {
                
                result_t result{};
                for (size_t i = 0; i < N; ++i) 
                    result.value[i] = a[i] * b.value;
                return result;

            }                                             

        };        


    } // namespace math


} // namespace ctda