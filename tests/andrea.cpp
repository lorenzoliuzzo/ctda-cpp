#include "ctda.hpp"
#include <iostream>

using namespace ctda;
using namespace units;

int main(){

    using metre = base_quantity<1,0,0,0,0,0,0>;
    using millimetre = unit<metre, std::milli>;
    using centiseconds = unit<basis::time, std::centi>;
    auto mm = millimetre{};
    auto cs = centiseconds{};

    auto l1 = quantity<std::array<double,2>,millimetre>({1.0,2.0});
    auto t1 = quantity<double,centiseconds>(2.0);
    // std::cout << std::to_string(mm) << std::endl;
    // std::cout << std::to_string(cs) << std::endl;

    // std::cout << std::to_string(cs/mm) << std::endl;
    // std::cout << std::to_string(l1) << std::endl;
    // std::cout << std::to_string(l1/t1) << std::endl;
    // std::cout << std::to_string(math::inv(l1/t1)) << std::endl;


    auto m_matrix = quantity<std::array<std::array<double,2>,2>, millimetre>({{{1.0,2.0},{3.0,4.0}}});


    std::cout << '\n' << std::to_string(m_matrix.value) << '\n'; 
    std::cout << std::to_string(m_matrix) << "\n\n";

    std::cout << std::to_string(m_matrix.value[0]) << '\n'; 
    std::cout << std::to_string(m_matrix(0)) << '\n';
    
    std::cout << std::to_string(l1) << '\n'; 
    std::cout << std::to_string(math::sq(l1)) << '\n'; 

    std::cout << std::to_string(l1(0)) << '\n'; 
    std::cout << std::to_string(math::sq(l1(0))) << '\n'; 
    
    std::cout << std::to_string(m_matrix) << '\n';    
    std::cout << std::to_string(math::sq(m_matrix)) << '\n';    
    std::cout << std::to_string(math::cb(m_matrix)) << '\n';    

    


//     std::cout << sizeof(mm) << std::endl;
//     std::cout << sizeof(metre{}) << std::endl;
//     std::cout << sizeof(t1) << std::endl;
//     std::cout << sizeof(l1) << std::endl;
    

//     auto v1 = quantity<std::vector<double>,millimetre>({1.0,2.0,1.0});
//     auto v2 = quantity<std::vector<double>,millimetre>({2.0,4.0,3.0});
   
//    std::cout << std::to_string(v1+v2) << std::endl;
    
    return 0;
}