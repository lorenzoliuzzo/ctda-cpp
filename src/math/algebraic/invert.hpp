/**
 * @file    math/algebraic/invert.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation of the invert struct.
 * @date    2023-08-12
 * 
 * @copyright Copyright (c) 2023
 */

#pragma once


namespace ctda {


    namespace math {


        /// @brief Invert specialization for base_quantities
        template <typename T>
            requires (is_base_v<T>)
        struct invert_impl<T> {

            using result_t = base_quantity<-T::powers[0],
                                           -T::powers[1],
                                           -T::powers[2],
                                           -T::powers[3],
                                           -T::powers[4],
                                           -T::powers[5],
                                           -T::powers[6]>;

            static constexpr result_t f(const T&) noexcept {
                return {};
            }                                             

        };


        /// @brief Invert specialization for prefixes 
        template <typename T>
            requires (is_prefix_v<T>)
        struct invert_impl<T> {
            
            using result_t = std::ratio<T::den, T::num>;

            static constexpr result_t f(const T&) noexcept {
                return {};
            }                                             
            
        };
     

        /// @brief Invert specialization for units
        template <typename T>
            requires (is_unit_v<T>)
        struct invert_impl<T> { 
            
            using result_t = unit<invert_t<typename T::base_t>, 
                                  invert_t<typename T::prefix_t>>;

            static constexpr result_t f(const T&) noexcept {
                return {};
            }       

        };


        /// @brief Invert specialization for numbers
        template <typename T>
            requires (std::is_arithmetic_v<T>)
        struct invert_impl<T> {

            using result_t = decltype(1.0 / std::declval<T>());

            static constexpr result_t f(const T& x) noexcept {
                return 1.0 / x;
            }                                             

        };


        /// @brief Invert specialization for std::array
        template <typename T, size_t N>
        struct invert_impl<std::array<T, N>> {

            using result_t = std::array<invert_t<T>, N>;

            static constexpr result_t f(const std::array<T, N>& arr) noexcept {

                result_t result{};
                for (size_t i = 0; i < N; ++i) 
                    result[i] = inv(arr[i]);
                return result;

            }                                             

        };


        /// @brief Invert specialization for quantities
        template <typename T>
            requires (is_quantity_v<T>)
        struct invert_impl<T> {

            using result_t = quantity<invert_t<typename T::value_t>, 
                                      invert_t<typename T::unit_t>>;

            static constexpr result_t f(const T& x) noexcept {
                return inv(x.value);
            }

        };


    } // namespace math


} // namespace ctda
