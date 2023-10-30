/**
 * @file    quantity.hpp
 * @author  Lorenzo Liuzzo (lorenzoliuzzo@outlook.com)
 * @brief   This file contains the implementation of the quantity struct.
 * @date    2023-08-23
 * @copyright Copyright (c) 2023
 */


#pragma once


namespace std {


    template <typename T>
    constexpr string to_string(const complex<T>& z) noexcept {
            
        stringstream ss;
        ss << '(' << z.real() << ", " << z.imag() << ')';
        return ss.str();

    }


    template <typename T, size_t N>
        requires (is_arithmetic_v<T>)
    constexpr string to_string(const array<T, N>& a) noexcept {

        stringstream ss;

        ss << '[';
        for (size_t i = 0; i < N; ++i) {
            ss << to_string(a[i]); 
            if (i != N - 1) 
               ss << ' ';
        }
        ss << ']';

        return ss.str();

    }


    template <typename T>
    constexpr string to_string(const vector<T>& a) noexcept {

        stringstream ss;
        const size_t N = a.size();

        ss << '[';
        for (size_t i = 0; i < N; ++i) {
            ss << to_string(a[i]);
            if (i != N - 1) 
               ss << ' ';
        }
        ss << ']';

        return ss.str();

    }


    template <typename T, size_t N, size_t M>
    constexpr string to_string(const array<array<T, N>, M>& a) noexcept {

        stringstream ss;

        ss << '[';

        for (size_t i = 0; i < M; ++i) {
            ss << to_string(a[i]);
            if (i != M - 1)
                ss << '\n';
        }

        ss << ']';

        return ss.str();

    }


    template <typename T>
        requires (ctda::is_base_v<T>)
    constexpr string to_string(const T&) noexcept{

        stringstream ss;

        // To track the first term to handle spacing
        bool first_term = true;  

        // Iterate over the base quantities and their powers
        for (int i = 0; i < 7; ++i) 

            if (T::powers[i] != 0) {
                if (!first_term) // Add a space between terms
                    ss << ' ';
                if (T::powers[i] != 1) // Add the power if not 1
                    ss << ctda::base_unit_literals[i] << '^' << T::powers[i]; 
                else 
                    ss << ctda::base_unit_literals[i]; 

                first_term = false;
            }

        return ss.str();    

    }        


    /// @brief The prefix map contains factor and char representation of the SI prefixes.
    inline static constexpr auto prefix_map = array<pair<int, char>, 20>(
        {
            {-24, 'y'}, //< yocto prefix
            {-21, 'z'}, //< zepto prefix
            {-18, 'a'}, //< atto prefix
            {-15, 'f'}, //< femto prefix
            {-12, 'p'}, //< pico prefix
            {-9,  'n'}, //< nano prefix
            {-6,  'u'}, //< micro prefix
            {-3,  'm'}, //< milli prefix
            {-2,  'c'}, //< centi prefix
            {-1,  'd'}, //< deci prefix
            {1,   'D'}, //< deca prefix
            {2,   'h'}, //< hecto prefix
            {3,   'k'}, //< kilo prefix
            {6,   'M'}, //< mega prefix
            {9,   'G'}, //< giga prefix
            {12,  'T'}, //< tera prefix
            {15,  'P'}, //< peta prefix
            {18,  'E'}, //< exa prefix
            {21,  'Z'}, //< zetta prefix
            {24,  'Y'} //< yotta prefix

        }
    ); 


    template <typename T>
        requires (ctda::is_unit_v<T>)
    constexpr string to_string(const T&) noexcept {

        stringstream ss;

        constexpr auto digits = static_cast<int>(log10(T::factor));

        if constexpr (digits < -24 || digits > 24) 
            throw runtime_error("Prefix out of range.");

        if constexpr (digits != 0) {

            constexpr auto prefix = lower_bound(
                prefix_map.begin(), prefix_map.end(), 
                digits,
                [](const auto& p, const auto& value) { 
                    return p.first < value; 
                }
            );
            
            ss << '(' << prefix->second << ')'; 
            
        }

        ss << to_string(typename T::base_t{});

        return ss.str();
        
    }


    /// @brief Get a string representation of the quantity.
    template <typename T>
        requires (ctda::is_quantity_v<T>)
    constexpr string to_string(const T& q) noexcept {

        return to_string(q.value) + ' ' + to_string(typename T::unit_t{});

    }


    /// @brief Get a string representation of the measurement.
    template <typename T>
        requires (ctda::is_measurement_v<T>)
    constexpr string to_string(const T& m) noexcept {

        return to_string(m.value()) + " +- " + to_string(m.uncertainty());

    }


} // namespace std


namespace ctda {

    template <typename T>
        requires (is_quantity_v<T> || is_measurement_v<T>)
    constexpr std::ostream& operator<<(std::ostream& os, T x) noexcept {

        return os << std::to_string(x);

    }

}