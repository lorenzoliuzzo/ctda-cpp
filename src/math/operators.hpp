/**
 * @file    math/operators.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   
 * @date    2023-06-24
 * 
 * @copyright Copyright (c) 2023
 */

#pragma once


namespace ctda {
    
    
    /// @brief Equal operator
    inline static constexpr auto operator==(const auto& x, const auto& y) noexcept { 

        return math::equal(x, y);
        
    }


    /// @brief Disqual operator
    inline static constexpr auto operator!=(auto x, auto y) noexcept { 

        return !math::equal(x, y);
        
    }


    /// @brief Greater than operator
    inline static constexpr auto operator>(const auto& x, const auto& y) noexcept { 

        return math::greater(x, y);
        
    }


    /// @brief Less than operator
    inline static constexpr auto operator<(const auto& x, const auto& y) noexcept { 

        return math::less(x, y);
        
    }


    /// @brief Greater than or equal operator
    inline static constexpr auto operator>=(const auto& x, const auto& y) noexcept { 

        return math::greater_equal(x, y);
        
    }


    /// @brief Less than or equal operator
    inline static constexpr auto operator<=(const auto& x, const auto& y) noexcept { 

        return math::less_equal(x, y);
        
    }


    /// @brief Negate operator 
    inline static constexpr auto operator-(auto x) noexcept { 
        
        return math::neg(x);
        
    }
    

    /// @brief Addition operator
    inline static constexpr auto operator+(auto x, auto y) noexcept { 

        return math::add(x, y);
        
    }


    /// @brief Subtraction operator
    inline static constexpr auto operator-(auto x, auto y) noexcept { 
        
        return math::sub(x, y);
        
    }


    /// @brief Multiplication operator
    inline static constexpr auto operator*(auto x, auto y) noexcept { 
        
        return math::mult(x, y);
        
    }


    /// @brief Division operator
    inline static constexpr auto operator/(auto x, auto y) noexcept { 

        return math::div(x, y);
        
    }


    /// @brief Increment operator
    inline static constexpr auto operator+=(auto& x, const auto& y) noexcept { 
        
        return x = math::add(x, y);
        
    }

    /// @brief Decrement operator
    inline static constexpr auto operator-=(auto& x, const auto& y) noexcept { 
        
        return x = math::sub(x, y);
        
    }

    /// @brief Scale operator
    template <typename T>
    inline static constexpr auto operator*=(auto& x, const T& y) noexcept { 

        return x = math::mult(x, y);
        
    }


    /// @brief Scale operator
    template <typename T>
    inline static constexpr auto operator/=(auto& x, const T& y) {

        return x = math::div(x, y);
        
    }


} // namespace scipp::math