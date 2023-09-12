/**
 * @file    ctda/ctda.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the import of all the headers of the library. 
 * @date    2023-09-11
 * 
 * @copyright Copyright (c) 2023
 */


#pragma once

#include <array>
#include <complex>
#include <cmath>    
#include <ratio>
#include <string_view>
#include <string>
#include <vector>


#define CTDA_QUANTITY_ACCESS_W_CURVY_BRACKETS 1


#include "traits.hpp"

#include "core/base_quantity.hpp"
#include "basis.hpp"

#include "core/unit.hpp"
#include "units.hpp" 

#include "core/quantity.hpp"

#include "io.hpp"

#include "math/operations.hpp"
#include "math/operators.hpp"
#include "math/algebraic/add.hpp"
#include "math/algebraic/multiply.hpp"
#include "math/algebraic/negate.hpp"
#include "math/algebraic/invert.hpp"
#include "math/algebraic/power.hpp"