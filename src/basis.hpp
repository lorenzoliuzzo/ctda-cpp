/**
 * @file    physics/basis.hpp
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

    } // namespace basis


} // namespace ctda