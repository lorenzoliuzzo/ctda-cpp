/**
 * @file    physics/quantities.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the definition of the SI 'base_quantity'.
 * @date    2023-09-11
 * @copyright Copyright (c) 2023
 */


#pragma once


namespace ctda {


    /// @brief This namespace contains the SI 'base_quantity'.
    namespace basis {
            
        using dimensionless      = base_quantity<0, 0, 0, 0, 0, 0, 0>; 
        using length             = base_quantity<1, 0, 0, 0, 0, 0, 0>;        
        using time               = base_quantity<0, 1, 0, 0, 0, 0, 0>;          
        using mass               = base_quantity<0, 0, 1, 0, 0, 0, 0>;          
        using temperature        = base_quantity<0, 0, 0, 1, 0, 0, 0>;    
        using elettric_current   = base_quantity<0, 0, 0, 0, 1, 0, 0>; 
        using substance_amount   = base_quantity<0, 0, 0, 0, 0, 1, 0>; 
        using luminous_intensity = base_quantity<0, 0, 0, 0, 0, 0, 1>; 


        using angle = math::divide_t<length, length>;                        ///< radian base_quantity
        using area = math::multiply_t<length, length>;                       ///< square_metre base_quantity
        using volume = math::multiply_t<length, area>;                       ///< cubic_metre base_quantity
        using velocity = math::divide_t<length, time>;                       ///< metre_per_second base_quantity
        using acceleration = math::divide_t<velocity, time>;                 ///< metre_per_second_squared base_quantity
        using angular_velocity = math::divide_t<angle, time>;                ///< radian_per_second base_quantity
        using angular_acceleration = math::divide_t<angular_velocity, time>; ///< radian_per_second2 base_quantity
        using momentum = math::multiply_t<mass, velocity>;                   ///< kilogram_metre_per_second base_quantity
        using impulse = math::multiply_t<momentum, time>;                    ///< kilogram_metre_per_second base_quantity
        using angular_momentum = math::multiply_t<momentum, length>;         ///< kilogram_metre_squared_per_second base_quantity
        using force = math::multiply_t<mass, acceleration>;                  ///< newton base_quantity
        using torque = math::multiply_t<force, length>;                      ///< newton_metre base_quantity
        using energy = math::multiply_t<force, length>;                      ///< joule base_quantity
        using action = math::multiply_t<energy, time>;                       ///< joule_second base_quantity
        using power = math::divide_t<energy, time>;                          ///< watt base_quantity
        using pressure = math::divide_t<force, area>;                        ///< pascal base_quantity
        using density = math::divide_t<mass, volume>;                        ///< kilogram_per_cubic_metre base_quantity
        using frequency = math::invert_t<time>;                              ///< hertz base_quantity
        
        
    } // namespace basis 


} // namespace ctda