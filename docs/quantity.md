---
title: Quantity
layout: default
permalink: /quantity
author_profile: true
nav_order: 3
---

# Measurement
Most of the time we write code to solve a problem that has a physical meaning, we assume that the code that we write is physically correct, but often we do make mistakes or, simply, we do not fully understand the problem we are trying to solve yet.

## A simple example 
Consider this basic example, where we want to do something physically meaningful, like calculating the force upon an object.
Suppose an apple fell from a tree and hit your head so hard that you can not remember Newton's second law of motion. You decide to calculate the force using whatever physical quantity presents itself to you. You measure the length of the tree and the mass of the apple and use them to calculate the force in this way:
```cpp
double calculate_force(double mass, double length) {

  return mass + length;

}

int main() {

  // This code will compile because it's not wrong to add any generic numbers
  double length{2.5};
  double mass{3.0};
  double force = calculate_force(length, mass);

  return 0;   
}
```

The code compiles, but it would give you a wrong anwser, because of the wrong physics law you choose to invent to calculate the force. 
This is due to the fact that the compiler does not know the physical meaning of the code, it only knows the type of the variables, which is not enough to understand the physical meaning of the code.
To find these types of error, if we are lucky enough to notice some weird numerical results, we need to read the code and understand the physical meaning of the code, which is not always easy. As long as the compiler can not distinguish between numbers used to represents different physical quantities, it does not help us in any way and we are left with a mad search through the code.
The solution is to use a type that encodes the physical meaning of the variable as well as its value type. The scipp library comes in handy here.

The `measurement` struct represents a physical measurement as a value with a dimensional-aware template meta-structure. 
Using the measurement struct, it is possible to perform dimensional analysis at compile-time without loss of precision and overhead. Basically, writing physical accurate code is now possible and easy!
```cpp
template <typename BASE_T, typename VALUE_TYPE = double>
    requires (is_base_v<BASE_TYPE> && math::is_number_v<VALUE_TYPE>)
struct measurement {

    using base_t = BASE_TYPE;   ///< The base of the measurement
    using value_t = VALUE_TYPE; ///< The type of the value of the measurement

    value_t value;              ///< The value of the measurement


    static constexpr measurement zero{value_t{}};   ///< The zero measurement

    static constexpr measurement one{value_t{1.0}}; ///< The one measurement


    /// @brief Default constructor
    constexpr measurement() noexcept : value{value_t{}} {}

    /// @brief Construct a measurement from a scalar value
    constexpr measurement(const value_t& val) noexcept : value{val} {}

    /// @brief Construct a measurement from a scalar value
    constexpr measurement(value_t&& val) noexcept : value{std::move(val)} {}

    /// @brief Construct a measurement from a scalar value and an unit
    /// @note The unit must be of the same base of the measurement 
    /// @note The value is immediatly converted to the base unit
    template <typename UNIT_TYPE> 
        requires (is_unit_v<UNIT_TYPE> && is_same_base_v<base_t, typename UNIT_TYPE::base_t>)
    constexpr measurement(value_t&& val, const UNIT_TYPE&) noexcept {

        using prefix_t = typename UNIT_TYPE::prefix_t;
        constexpr auto factor = static_cast<double>(prefix_t::num) / static_cast<double>(prefix_t::den);
        this->value = std::forward<value_t>(val * factor);
        
    }

    /// @brief Implicitly convert the measurement to a scalar value if it is a scalar base measurement
    constexpr operator value_t() const requires is_scalar_base_v<base_t> { 
        
        return this->value; 

    }

    /// @brief Extract the value of this measurement converted to a specific unit
    /// @note The unit must be of the same base of the measurement
    template <typename T>
    constexpr auto value_as(const unit<base_t, T>&) const noexcept {

        return this->value / static_cast<double>(T::num) * static_cast<double>(T::den);

    }   


    /// @brief Print a measurement to an output stream
    friend constexpr std::ostream& operator<<(std::ostream& os, const measurement& other) noexcept { 
        
        os << other.value; 
        if constexpr (!is_scalar_base_v<base_t>) 
            os << ' ' << base_t::to_string();
        return os;
        
    }

};
```

The value type is defaulted to double, but it can be changed to any type that supports the basic arithmetic operations. 
Operations between measurements with different units are allowed and they respect the dimensional analysis rules, i.e. we cannot sum two measurements with different base units, but we can multiply them to product something with a different physical meaning.
For example, we can write the previous code in this way:

```cpp
int main() {
  measurement<basis::length, double> length{1.0};
  measurement<basis::mass, double> mass{60.0};
  measurement<basis::force, double> force{length * mass};
}
```

This code will not compile yet because it contains incorrect physical operations, but at least the physical error in the code is now clear to the compiler, which will give us an error message that will help us understand the problem:
```cpp
error: conversion from ‘measurement<base_quantity<[...],0,[...],[...],[...],[...],[...]>,[...]>’ to non-scalar type ‘measurement<base_quantity<[...],-2,[...],[...],[...],[...],[...]>,[...]>’ requested here:
    measurement<basis::force, double> force = length * mass;
```

We are indeed trying to assign a value obtained from the multiplication of a length and a mass, which does not correspond to the physical meaning of the force, to a variable of type `measurement<basis::force, double>`.

Remembering Newton second law, we can rewrite the previous code in the correct way:
```cpp
int main() {
  measurement<basis::acceleration, double> a{1.0};
  measurement<basis::mass, double> m{60.0};
  measurement<basis::force, double> F = m * a;
}
```

Maybe you are thinking that this is all very nice, but that it is not worth the effort to write code in this way, because it is too complicated, but simply this is not true. In fact, the code is not more complicated, it is just different.
Please note that this is all done at compile time, so we don't have to run the code and maybe, if we are lucky, find a little suspicius numerical result that will make us think that something is wrong in the code and then manually debug it to find the error.
The compiler will tell us exactly where the error is and what the error is, so we can fix it immediately and return to code.
Another advantage of using the measurement struct is that we can do not bother about conversions between units, instead we can just write our physical code in a natural way, as we would do on paper.