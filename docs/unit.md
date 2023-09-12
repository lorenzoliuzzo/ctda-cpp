---
title: Unit
layout: default
permalink: /unit
author_profile: true
nav_order: 2
---

# Unit
The `unit` struct represents a unit of measurement by combining a `base_quantity` with an `std::ratio` prefix:
```cpp
template <typename BASE_T, typename PREFIX_T = std::ratio<1>> 
    requires (is_base_v<BASE_T> && is_prefix_v<PREFIX_T>)  
struct unit {

    using base_t = BASE_T;      ///< base_quantity type
    using prefix_t = PREFIX_T;  ///< prefix type

    /// @brief Return a string representation of the unit
    static constexpr std::string to_string() noexcept {

        std::stringstream ss;
        auto factor = static_cast<double>(prefix_t::num) / static_cast<double>(prefix_t::den); 
        constexpr auto prefix = std::lower_bound(prefix_map.begin(), prefix_map.end(), factor,
            [](const auto& p, const auto& value) { return p.first < value; });
        
        if constexpr (prefix == prefix_map.end())
            ss << base_t::to_string();
        else
            ss << "[" << prefix->second << "]" << base_t::to_string();

        return ss.str();

    }

};
```

In the `units` namespace are defined the most common units of measure: 
```cpp
namespace units {

    using metre = unit<basis::length, std::ratio<1>>;    ///< metre unit
    inline static constexpr metre m;                    ///< m unit

    using kilometre = unit<basis::length, std::kilo>;    ///< kilometre unit
    inline static constexpr kilometre km;               ///< Km unit

    using decimetre = unit<basis::length, std::deci>;    ///< decimetre unit
    inline static constexpr decimetre dm;               ///< dm unit

    using centimetre = unit<basis::length, std::centi>;  ///< centimetre unit
    inline static constexpr centimetre cm;              ///< cm unit

    [...]

    using second = unit<basis::time, std::ratio<1>>;     ///< second unit
    inline static constexpr second s;                   ///< s unit

    using minute = unit<basis::time, std::ratio<60>>;    ///< minute unit
    inline static constexpr minute min;                 ///< min unit

    using hour = unit<basis::time, std::ratio<3600>>;    ///< hour unit
    inline static constexpr hour h;                     ///< h unit
    
    [...]

    using kilogram = unit<basis::mass>;                  ///< kilogram unit
    inline static constexpr kilogram kg;                ///< kg unit

    using gram = unit<basis::mass, std::milli>;          ///< gram unit
    inline static constexpr gram g;                     ///< g unit

    [...]


    using litre = cubic_decimetre;                      ///< litre unit
    inline static constexpr litre L;                    ///< L unit

    using joule = unit<basis::energy>;                   ///< Joule unit
    inline static constexpr joule J;                    ///< J unit

    using newton = unit<basis::force>;                   ///< Newton unit
    inline static constexpr newton N;                   ///< N unit

    using pascal = unit<basis::pressure>;                ///< Pascal unit
    inline static constexpr pascal Pa;                  ///< Pa unit

    [...]

}
```