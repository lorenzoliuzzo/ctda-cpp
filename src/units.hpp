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

        // using newton = kilogram * meter / (second * second);
        // using joule = newton * meter;
        // using watt = joule / second;
        // using pascal = newton / (meter * meter);
        // using hertz = 1 / second;
        // using coulomb = ampere * second;
        // using volt = watt / ampere;
        // using ohm = volt / ampere;
        // using farad = coulomb / volt;
        // using weber = volt * second;
        // using tesla = weber / (meter * meter);
        // using henry = weber / ampere;
        // using siemens = 1 / ohm;
        // using lux = candela / (meter * meter);
        // using becquerel = 1 / second;
        // using gray = joule / kilogram;
        // using sievert = joule / kilogram;
        // using katal = mole / second;


    } // namespace units


} // namespace ctda