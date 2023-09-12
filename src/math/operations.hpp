/**
 * @file    math/operations.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation of the operations among ctda types.
 * @date    2023-08-12
 * @copyright Copyright (c) 2023
 */


#pragma once


namespace ctda {


    namespace math {


        template <typename T1, typename T2>
        struct equal_impl;

        template <typename T1, typename T2>
        inline static constexpr bool equal(const T1& x, const T2& y) noexcept {
            
            return equal_impl<T1, T2>::f(x, y); 

        }


        template <typename T1, typename T2>
        struct greater_impl;

        template <typename T1, typename T2>
        inline static constexpr bool greater(const T1& x, const T2& y) noexcept {
            
            return greater_impl<T1, T2>::f(x, y); 

        }


        template <typename T1, typename T2>
        struct less_impl;

        template <typename T1, typename T2>
        inline static constexpr bool less(const T1& x, const T2& y) noexcept {
            
            return less_impl<T1, T2>::f(x, y); 

        }


        template <typename T1, typename T2>
        struct greater_equal_impl;

        template <typename T1, typename T2>
        inline static constexpr bool greater_equal(const T1& x, const T2& y) noexcept {
            
            return greater_equal_impl<T1, T2>::f(x, y); 

        }


        template <typename T1, typename T2>
        struct less_equal_impl;

        template <typename T1, typename T2>
        inline static constexpr bool less_equal(const T1& x, const T2& y) noexcept {
            
            return less_equal_impl<T1, T2>::f(x, y); 

        }


        template <typename T>
        struct negate_impl; 

        template <typename T>
        inline static constexpr auto neg(const T& x) noexcept {
            
            return negate_impl<T>::f(x); 

        }


        template <typename T1, typename T2>
        struct add_impl;

        template <typename T1, typename T2>
        using add_t = typename add_impl<T1, T2>::result_t;

        template <typename T1, typename T2>
        inline static constexpr auto add(const T1& x, const T2& y) noexcept {
            
            return add_impl<T1, T2>::f(x, y); 

        }
        

        template <typename T1, typename T2>
        inline static constexpr auto sub(const T1& x, const T2& y) noexcept {
            
            return add(x, neg(y)); 

        }


        template <typename T1, typename T2>
        struct multiply_impl;       

        template <typename T1, typename T2>
        using multiply_t = typename multiply_impl<T1, T2>::result_t;
    
        template <typename T1, typename T2>
        inline static constexpr auto mult(const T1& x, const T2& y) noexcept {
            
            return multiply_impl<T1, T2>::f(x, y); 

        }


        template <typename T>
        struct invert_impl;       

        template <typename T>
        using invert_t = typename invert_impl<T>::result_t;

        template <typename T>
        inline static constexpr auto inv(const T& x) {
            
            return invert_impl<T>::f(x);

        }


        template <typename T1, typename T2>
        using divide_t = multiply_t<T1, invert_t<T2>>;
    
        template <typename T1, typename T2>
        inline static constexpr auto div(const T1& x, const T2& y) noexcept {
            
            return mult(x, inv(y));

        }


        template <int POWER, typename T>
        struct power_impl; 

        template <int POWER, typename T>
        using power_t = typename power_impl<POWER, T>::result_t;

        template <int POWER, typename T>
        inline static constexpr auto pow(const T& x) noexcept {
            
            return power_impl<POWER, T>::f(x); 

        }


        template <typename T>
        using square_t = power_t<2, T>;

        inline static constexpr auto sq(const auto& x) noexcept {
            
            return pow<2>(x); 

        }

        template <typename T>
        using cube_t = power_t<3, T>;

        inline static constexpr auto cb(const auto& x) noexcept {
            
            return pow<3>(x); 

        }


        // template <typename POWER, typename T>
        // using root_t = power_t<POWER, invert_t<T>>;

        // template <typename POWER, typename T>
        // inline static constexpr auto root(const T& x) {
            
        //     return power_impl<inv(POWER), T>::f(x);

        // }

        // inline static constexpr auto sqrt(const auto& x) {
            
        //     return pow<0.5>(x); 

        // }

        // inline static constexpr auto cbrt(const auto& x) {
            
        //     return pow<1. / 3.>(x); 

        // }


    
    } // namespace math


} // namespace ctda