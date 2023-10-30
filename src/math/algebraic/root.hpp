/**
 * @file    math/algebraic/root.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation of the root struct.
 * @date    2023-10-30
 * 
 * @copyright Copyright (c) 2023
 */

#pragma once


namespace ctda {


    namespace math {



        /// @brief Return the power of a base_quantity
        template <int POWER, typename BASE_T>
            requires (is_base_v<BASE_T>)
        struct root_impl<POWER, BASE_T> {

            using result_t = base_quantity<BASE_T::powers[0] / POWER, 
                                           BASE_T::powers[1] / POWER,
                                           BASE_T::powers[2] / POWER,
                                           BASE_T::powers[3] / POWER,
                                           BASE_T::powers[4] / POWER,
                                           BASE_T::powers[5] / POWER,
                                           BASE_T::powers[6] / POWER>;

            inline static constexpr result_t f(const BASE_T&) noexcept {

                return {};

            }                                             
            
        };


        /// @brief Return the power of a prefix
        template <int POWER, typename PREFIX_T>
            requires (is_prefix_v<PREFIX_T>)
        struct root_impl<POWER, PREFIX_T> {
            
            using result_t = std::ratio<static_cast<size_t>(std::pow(PREFIX_T::num, inv(POWER))), 
                                        static_cast<size_t>(std::pow(PREFIX_T::den, inv(POWER)))>;

            inline static constexpr result_t f(const PREFIX_T&) noexcept {

                return {};

            }       

        };


        /// @brief Return the power of an unit
        template <int POWER, typename UNIT_T>
            requires (is_unit_v<UNIT_T>)
        struct root_impl<POWER, UNIT_T> {
            
            using result_t = unit<root_t<POWER, typename UNIT_T::base_t>, 
                                  root_t<POWER, typename UNIT_T::prefix_t>>;

            inline static constexpr result_t f(const UNIT_T&) noexcept {

                return {};

            }       

        };


        /// @brief Return the power of a number
        template <int POWER, typename T>
            requires (std::is_arithmetic_v<T>)
        struct root_impl<POWER, T> {
            
            using result_t = T;

            inline static constexpr result_t f(const T& x) noexcept {

                return std::pow(x, inv(POWER));

            }       

        };


        /// @brief Return the power of an array
        template <int POWER, typename T, size_t N>
        struct root_impl<POWER, std::array<T, N>> {
            
            using result_t = std::array<root_t<POWER, T>, N>;

            static constexpr result_t f(const std::array<T, N>& x) noexcept {

                result_t result{};
                for (size_t i = 0; i < N; ++i) 
                    result[i] = root<POWER>(x[i]);
                return result;

            }       

        };


        /// @brief Return the power of a vector
        template <int POWER, typename T>
        struct root_impl<POWER, std::vector<T>> {
            
            using result_t = std::vector<root_t<POWER, T>>;

            static constexpr result_t f(const std::vector<T>& x) noexcept {

                result_t result(x.size());
                for (size_t i = 0; i < x.size(); ++i) 
                    result[i] = root<POWER>(x[i]);
                return result;

            }       

        };


        /// @brief Return the power of a quantity
        template <int POWER, typename T>
            requires (is_quantity_v<T>)
        struct root_impl<POWER, T> {
            
            using result_t = quantity<root_t<POWER, typename T::value_t>, 
                                      root_t<POWER, typename T::unit_t>>;

            inline static constexpr result_t f(const T& x) noexcept {

                return root<POWER>(x.value);

            }       

        };



        // /// @brief power a umeasurement
        // template <int POWER, typename UMEAS_TYPE>
        //     requires (physics::is_umeasurement_v<UMEAS_TYPE>)
        // struct root_impl<POWER, UMEAS_TYPE> {

        //     using result_t = physics::umeasurement<root_t<POWER, typename UMEAS_TYPE::base_t>>;                                             

        //     static constexpr result_t f(const UMEAS_TYPE& x) noexcept {

        //         return {std::pow(x.value, POWER), x.uncertainty * POWER};

        //     }       

        // };


        // /// @brief power a complex number
        // template <int POWER, typename T>
        //     requires (math::is_complex_v<T>)
        // struct root_impl<POWER, T> {

        //     using result_t = complex<root_t<POWER, typename T::value_t>>;

        //     static constexpr result_t f(const T& x) noexcept {

        //         return polar(op::root<POWER>(op::abs(x)), op::atan(x.imag, x.real) / POWER);

        //     }

        // };


        // /// @brief power a dual number
        // template <int POWER, typename T>
        //     requires (math::is_dual_v<T>)
        // struct root_impl<POWER, T> {

        //     using result_t = dual<root_t<POWER, T>>;

        //     static constexpr result_t f(const T& x) noexcept {

        //         return polar(op::root<POWER>(op::abs(x)), op::atan(x.imag, x.real) / POWER);
        
        //     }

        // };


        // /// @brief power a vector
        // template <int POWER, typename VECTOR_TYPE>
        //     requires (geometry::is_vector_v<VECTOR_TYPE>)
        // struct root_impl<POWER, VECTOR_TYPE> {

        //     using result_t = geometry::vector<root_t<POWER, typename VECTOR_TYPE::value_t>, VECTOR_TYPE::dim, VECTOR_TYPE::flag>; 

        //     static constexpr result_t f(const VECTOR_TYPE& x) {

        //         result_t x_pow;
        //         std::transform(std::execution::par, x.data.begin(), x.data.end(), x_pow.data.begin(), [](const auto& x_i) { return op::pow<POWER>(x_i); });
        //         return x_pow;

        //     }
        
        // };


        // template <int N, typename T>
        // struct root_impl<N, calculus::expr_ptr<T>> {

        //     using result_t = calculus::expr_ptr<op::root_t<N, T>>;

        //     static constexpr result_t f(const calculus::expr_ptr<T>& x) {

        //         return std::make_shared<calculus::root_expr<N, T>>(op::root<N>(x->val), x);

        //     }

        // };


        // template <int N, typename T>
        // struct root_impl<N, calculus::variable<T>> {

        //     using result_t = calculus::expr_ptr<op::root_t<N, T>>;

        //     static constexpr result_t f(const calculus::variable<T>& x) {

        //         return op::root<N>(x.expr); 

        //     }

        // };


    } // namespace functions


} // namespace scipp::math