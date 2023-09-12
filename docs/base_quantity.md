---
title: Base quantity
layout: default
permalink: /base_quantity
author_profile: true
nav_order: 1
---

# Base quantity
The `base_quantity` struct represents a physical quantity by storing the powers of the seven base quantities of the International System of Units ([SI](https://en.wikipedia.org/wiki/International_System_of_Units)) - `length`, `time`, `mass`, `temperature`, `electric_current`, `substance_amount`, and `luminous_intensity`, as template parameters:
```cpp
template <int LENGTH, int TIME, int MASS, int TEMPERATURE, 
          int ELETTRIC_CURRENT, int SUBSTANCE_AMOUNT, int LUMINOUS_INTENSITY>
struct base_quantity {

    static constexpr std::array<int, 7> powers = {LENGTH, TIME, MASS, TEMPERATURE, ELETTRIC_CURRENT, SUBSTANCE_AMOUNT, LUMINOUS_INTENSITY}; ///< array of the powers of the base quantities

    static constexpr std::array<std::string_view, 7> base_literals = {"m", "s", "kg", "K", "A", "mol", "cd"}; //< array of the literals of the base quantities

    /// @brief Returns the string representation of the base_quantity
    static constexpr std::string_view to_string() noexcept {

        std::stringstream ss;

        // Iterate over the base quantities and their powers
        meta::for_<7>([&](auto i) constexpr {

            if constexpr (powers[i] != 0) {

                if constexpr (powers[i] == 1) // Append the base quantity to the string builder
                    ss << base_literals[i]; 

                else // Append the base quantity and its power to the string builder
                    ss << base_literals[i] << '^' << powers[i]; 

            }
            
        });

        return ss.str();

    }

};
```

The powers of the base quantities can be accessed using the corresponding aliases.
It is possible to define custom base_quantities using the constuctor providing the powers, or just by combining existing types using the basic operations, defined inside the `scipp::math::op` namespace, such as multiplication, division, and exponentiation.
The base quantities are not meant to be used directly, but rather as template parameters for the unit and measurement structs.

The principal base quantities are defined in the `scipp::physics::base` namespace:
```cpp
namespace base {

    using length = base_quantity<1, 0, 0, 0, 0, 0, 0>;                      ///< metre base_quantity
    using time = base_quantity<0, 1, 0, 0, 0, 0, 0>;                        ///< second base_quantity                   
    using mass = base_quantity<0, 0, 1, 0, 0, 0, 0>;                        ///< kilogram base_quantity
    using temperature = base_quantity<0, 0, 0, 1, 0, 0, 0>;                 ///< kelvin base_quantity
    using electric_current = base_quantity<0, 0, 0, 0, 1, 0, 0>;            ///< ampere base_quantity
    using substance_amount = base_quantity<0, 0, 0, 0, 0, 1, 0>;            ///< mole base_quantity
    using luminous_intensity = base_quantity<0, 0, 0, 0, 0, 0, 1>;          ///< candela base_quantity

    using angle = math::op::divide_t<length, length>;                        ///< radian base_quantity
    using area = math::op::multiply_t<length, length>;                       ///< square_metre base_quantity
    using volume = math::op::multiply_t<length, area>;                       ///< cubic_metre base_quantity
    using velocity = math::op::divide_t<length, time>;                       ///< metre_per_second base_quantity
    using acceleration = math::op::divide_t<velocity, time>;                 ///< metre_per_second_squared base_quantity
    using angular_velocity = math::op::divide_t<angle, time>;                ///< radian_per_second base_quantity
    using angular_acceleration = math::op::divide_t<angular_velocity, time>; ///< radian_per_second2 base_quantity
    using momentum = math::op::multiply_t<mass, velocity>;                   ///< kilogram_metre_per_second base_quantity
    using impulse = math::op::multiply_t<momentum, time>;                    ///< kilogram_metre_per_second base_quantity
    using angular_momentum = math::op::multiply_t<momentum, length>;         ///< kilogram_metre_squared_per_second base_quantity
    using force = math::op::multiply_t<mass, acceleration>;                  ///< newton base_quantity
    using torque = math::op::multiply_t<force, length>;                      ///< newton_metre base_quantity
    using energy = math::op::multiply_t<force, length>;                      ///< joule base_quantity
    using action = math::op::multiply_t<energy, time>;                       ///< joule_second base_quantity
    using power = math::op::divide_t<energy, time>;                          ///< watt base_quantity
    using pressure = math::op::divide_t<force, area>;                        ///< pascal base_quantity
    using density = math::op::divide_t<mass, volume>;                        ///< kilogram_per_cubic_metre base_quantity
    using frequency = math::op::invert_t<time>;                              ///< hertz base_quantity

    [...]

}
```
