/**
 * @file    math/operations/algebraic/root.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-06-12
 * 
 * @copyright Copyright (c) 2023
 */



namespace scipp::math {


    namespace op {


        /// @brief power a physics::base_quantity
        template <int POWER, typename BASE_TYPE>
            requires (physics::is_base_v<BASE_TYPE>)
        struct root_impl<POWER, BASE_TYPE> {

            using result_t = physics::base_quantity<BASE_TYPE::length / POWER, 
                                                    BASE_TYPE::time / POWER,
                                                    BASE_TYPE::mass / POWER,
                                                    BASE_TYPE::temperature / POWER,
                                                    BASE_TYPE::elettric_current / POWER,
                                                    BASE_TYPE::substance_amount / POWER,
                                                    BASE_TYPE::luminous_intensity / POWER>;

            static constexpr result_t f(const BASE_TYPE&) noexcept {

                return {};

            }                                             
            
        };


        /// @brief power a prefix
        template <int POWER, typename PREFIX_TYPE>
            requires (physics::is_prefix_v<PREFIX_TYPE>)
        struct root_impl<POWER, PREFIX_TYPE> {
            
            using result_t = std::ratio<static_cast<int>(std::pow(PREFIX_TYPE::num, 1.0 / POWER)), 
                                        static_cast<int>(std::pow(PREFIX_TYPE::den, 1.0 / POWER))>; 


            static constexpr result_t f(const PREFIX_TYPE&) noexcept {

                return {};

            }       

        };


        /// @brief power an unit of measurement
        template <int POWER, typename UNIT_TYPE>
            requires (physics::is_unit_v<UNIT_TYPE>)
        struct root_impl<POWER, UNIT_TYPE> {

            using result_t = physics::unit<root_t<POWER, typename UNIT_TYPE::base_t>, root_t<POWER, typename UNIT_TYPE::prefix_t>>;                                             

            static constexpr result_t f(const UNIT_TYPE&) noexcept {

                return {};

            }    

        };


        /// @brief power a number
        template <int POWER, typename T>
            requires is_number_v<T>
        struct root_impl<POWER, T> {

            using result_t = T;

            static constexpr result_t f(const T& x) noexcept {

                return std::pow(x, 1.0 / POWER);

            }       

        };


        /// @brief power a measurement
        template <int POWER, typename MEAS_TYPE>
            requires physics::is_measurement_v<MEAS_TYPE>
        struct root_impl<POWER, MEAS_TYPE> {

            using result_t = physics::measurement<root_t<POWER, typename MEAS_TYPE::base_t>, typename MEAS_TYPE::value_t>;                                             

            static constexpr result_t f(const MEAS_TYPE& x) noexcept {

                return std::pow(x.value, 1.0 / POWER);

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


        /// @brief power a vector
        template <int POWER, typename VECTOR_TYPE>
            requires (geometry::is_vector_v<VECTOR_TYPE>)
        struct root_impl<POWER, VECTOR_TYPE> {

            using result_t = geometry::vector<root_t<POWER, typename VECTOR_TYPE::value_t>, VECTOR_TYPE::dim, VECTOR_TYPE::flag>; 

            static constexpr result_t f(const VECTOR_TYPE& x) {

                result_t x_pow;
                std::transform(std::execution::par, x.data.begin(), x.data.end(), x_pow.data.begin(), [](const auto& x_i) { return op::pow<POWER>(x_i); });
                return x_pow;

            }
        
        };


        template <int N, typename T>
        struct root_impl<N, calculus::expr_ptr<T>> {

            using result_t = calculus::expr_ptr<op::root_t<N, T>>;

            static constexpr result_t f(const calculus::expr_ptr<T>& x) {

                return std::make_shared<calculus::root_expr<N, T>>(op::root<N>(x->val), x);

            }

        };


        template <int N, typename T>
        struct root_impl<N, calculus::variable<T>> {

            using result_t = calculus::expr_ptr<op::root_t<N, T>>;

            static constexpr result_t f(const calculus::variable<T>& x) {

                return op::root<N>(x.expr); 

            }

        };


    } // namespace functions


} // namespace scipp::math