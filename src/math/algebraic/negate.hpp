/**
 * @file    math/algebraic/negate.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation of the negate struct.
 * @date    2023-08-12
 * 
 * @copyright Copyright (c) 2023
 */

#pragma once


namespace ctda {


    namespace math {


        /// @brief Negate specialization for numbers
        template <typename T>
            requires (std::is_arithmetic_v<T>)
        struct negate_impl<T> {

            using result_t = T;

            static constexpr result_t f(const T& x) noexcept {
                return -x;
            }                                             

        };


        /// @brief Negate specialization for std::array
        template <typename T, size_t N>
        struct negate_impl<std::array<T, N>> {

            using result_t = std::array<T, N>;

            static constexpr result_t f(const std::array<T, N>& arr) noexcept {

                result_t result{};
                for (size_t i = 0; i < N; ++i) 
                    result[i] = neg(arr[i]);
                return result;

            }                                             

        };


        /// @brief Negate specialization for quantities
        template <typename T>
            requires (is_quantity_v<T>)
        struct negate_impl<T> {

            using result_t = T;

            static constexpr result_t f(const T& x) noexcept {
                return neg(x.value);
            }

        };


    } // namespace math


} // namespace ctda
