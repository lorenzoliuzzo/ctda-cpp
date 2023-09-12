---
title: Home
layout: home
permalink: /
nav_order: 0
---

# Compile Time Dimensional Analysis in C++
Dimensional analysis plays a crucial role in scientific computations by ensuring that mathematical expressions and equations are consistent in terms of units and dimensions. The library incorporates a compile-time structure for dimensional analysis, allowing users to define and manipulate physical quantities with their associated units.

# Usage

The library provides a `quantity` class template that can be used to define physical quantities with their associated units. The `quantity` class template is defined as follows:
```cpp
template <typename value_t, typename unit_t>
class quantity;
```
The `value_t` template parameter is used to define the type of the value of the quantity, while the `unit_t` template parameter is used to define the type of the unit of the quantity. The `unit_t` template parameter must be a type that satisfies the `unit` concept. 

The `unit` struct represents a unit of measurement by combining a base_quantity with an std::ratio prefix:
```cpp
template <typename base_t, typename prefix_t = std::ratio<1>>
class unit {

    static constexpr auto factor = static_cast<double>(prefix_t::num) / static_cast<double>(prefix_t::den); ///< conversion factor of the unit
}
```
The `base_t` template parameter is used to define the type of the base unit of the unit, while the `prefix_t` template parameter is used to define the type of the prefix of the unit.
In the units namespace are defined the most common units of measure.

The `base_quantity` struct represents a physical quantity by storing the powers of the seven base quantities of the International System of Units (SI) - length, time, mass, temperature, electric_current, substance_amount, and luminous_intensity, as template parameters:
```cpp
template <int LENGTH, int TIME, int MASS, int TEMPERATURE, int ELETTRIC_CURRENT, int SUBSTANCE_AMOUNT, int LUMINOUS_INTENSITY>
struct base_quantity {

    static constexpr std::array<int, 7> powers = {LENGTH, TIME, MASS, TEMPERATURE, ELETTRIC_CURRENT, SUBSTANCE_AMOUNT, LUMINOUS_INTENSITY}; ///< array of the powers of the base quantities

};
```


# How to install
You can clone the repository using this command:
```bash
git clone https://github.com/lorenzoliuzzo/ctda.git 
```

You can easily use the library by including the header file in your code: 
```cpp
#include "ctda.hpp"

using namespace ctda;
```

If you want to use the library in your project, you can add the following line to your `CMakeLists.txt` file:
```cmake
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/path/to/ctda)
```

If you would want to run the tests and the examples, you can use the following commands from the root directory of the repository:
```bash
bash build.sh
```

After that, you can run the tests and the examples using the following commands:
```bash
./build/tests/some_test
./build/examples/some_example
```

# Contributing
If you want to contribute to the project, you can open a [pull requests](https://github.com/lorenzoliuzzo/ctda/pulls) or use the [issue tracker](https://github.com/lorenzoliuzzo/ctda/issues/) to suggest any code implementations or report bugs. 
Any contributions are welcome! 

## License
The code is released under the terms of the [GNU General Public License v3.0](https://www.gnu.org/licenses/gpl-3.0.html), see the [LICENSE](https://github.com/lorenzoliuzzo/ctda/blob/master/LICENSE).
