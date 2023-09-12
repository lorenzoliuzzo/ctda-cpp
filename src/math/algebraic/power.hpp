/**
 * @file    math/algebraic/power.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation of the power struct.
 * @date    2023-08-12
 * 
 * @copyright Copyright (c) 2023
 */

#pragma once


namespace ctda {


    namespace math {


        /// @brief Return the power of a base_quantity
        template <int POWER, typename BASE_T>
            requires (is_base_v<BASE_T>)
        struct power_impl<POWER, BASE_T> {

            using result_t = base_quantity<BASE_T::powers[0] * POWER, 
                                           BASE_T::powers[1] * POWER,
                                           BASE_T::powers[2] * POWER,
                                           BASE_T::powers[3] * POWER,
                                           BASE_T::powers[4] * POWER,
                                           BASE_T::powers[5] * POWER,
                                           BASE_T::powers[6] * POWER>;

            inline static constexpr result_t f(const BASE_T&) noexcept {

                return {};

            }                                             
            
        };


        /// @brief Return the power of a prefix
        template <int POWER, typename PREFIX_T>
            requires (is_prefix_v<PREFIX_T>)
        struct power_impl<POWER, PREFIX_T> {
            
            using result_t = std::ratio<static_cast<size_t>(std::pow(PREFIX_T::num, POWER)), 
                                        static_cast<size_t>(std::pow(PREFIX_T::den, POWER))>;

            inline static constexpr result_t f(const PREFIX_T&) noexcept {

                return {};

            }       

        };


        /// @brief Return the power of an unit
        template <int POWER, typename UNIT_T>
            requires (is_unit_v<UNIT_T>)
        struct power_impl<POWER, UNIT_T> {
            
            using result_t = unit<power_t<POWER, typename UNIT_T::base_t>, 
                                  power_t<POWER, typename UNIT_T::prefix_t>>;

            inline static constexpr result_t f(const UNIT_T&) noexcept {

                return {};

            }       

        };


        /// @brief Return the power of a number
        template <int POWER, typename T>
            requires (std::is_arithmetic_v<T>)
        struct power_impl<POWER, T> {
            
            using result_t = T;

            inline static constexpr result_t f(const T& x) noexcept {

                return std::pow(x, POWER);

            }       

        };


        /// @brief Return the power of an array
        template <int POWER, typename T, size_t N>
        struct power_impl<POWER, std::array<T, N>> {
            
            using result_t = std::array<power_t<POWER, T>, N>;

            static constexpr result_t f(const std::array<T, N>& x) noexcept {

                result_t result{};
                for (size_t i = 0; i < N; ++i) 
                    result[i] = pow<POWER>(x[i]);
                return result;

            }       

        };


        /// @brief Return the power of a vector
        template <int POWER, typename T>
        struct power_impl<POWER, std::vector<T>> {
            
            using result_t = std::vector<power_t<POWER, T>>;

            static constexpr result_t f(const std::vector<T>& x) noexcept {

                result_t result(x.size());
                for (size_t i = 0; i < x.size(); ++i) 
                    result[i] = pow<POWER>(x[i]);
                return result;

            }       

        };


        /// @brief Return the power of a quantity
        template <int POWER, typename T>
            requires (is_quantity_v<T>)
        struct power_impl<POWER, T> {
            
            using result_t = quantity<power_t<POWER, typename T::value_t>, 
                                      power_t<POWER, typename T::unit_t>>;

            inline static constexpr result_t f(const T& x) noexcept {

                return pow<POWER>(x.value);

            }       

        };


    } // namespace math


} // namespace ctda