/**
 * @file    physics/units.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the definition of SI and derived 'unit'
 * @todo    Add the SI derived quantities and units.
 * @date    2023-09-11
 * @copyright Copyright (c) 2023
 */


#pragma once


namespace ctda {


    namespace units {


        using dimensionless = unit<basis::dimensionless>;
        using meter         = unit<basis::length>;
        using second        = unit<basis::time>;
        using kilogram      = unit<basis::mass>;
        using ampere        = unit<basis::elettric_current>;
        using kelvin        = unit<basis::temperature>;
        using mole          = unit<basis::substance_amount>;
        using candela       = unit<basis::luminous_intensity>;
        using radian        = unit<basis::dimensionless>;
        using steradian     = unit<basis::dimensionless>;

        // inline static constexpr auto newton = kilogram * meter / (second * second);
        // inline static constexpr auto joule = newton * meter;
        // inline static constexpr auto watt = joule / second;
        // inline static constexpr auto pascal = newton / (meter * meter);
        // inline static constexpr auto hertz = 1 / second;
        // inline static constexpr auto coulomb = ampere * second;
        // inline static constexpr auto volt = watt / ampere;
        // inline static constexpr auto ohm = volt / ampere;
        // inline static constexpr auto farad = coulomb / volt;
        // inline static constexpr auto weber = volt * second;
        // inline static constexpr auto tesla = weber / (meter * meter);
        // inline static constexpr auto henry = weber / ampere;
        // inline static constexpr auto siemens = 1 / ohm;
        // inline static constexpr auto lux = candela / (meter * meter);
        // inline static constexpr auto becquerel = 1 / second;
        // inline static constexpr auto gray = joule / kilogram;
        // inline static constexpr auto sievert = joule / kilogram;
        // inline static constexpr auto katal = mole / second;


    } // namespace units


} // namespace ctda