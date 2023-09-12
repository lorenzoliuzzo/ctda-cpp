cmake_minimum_required(VERSION 3.20)

project(ctda VERSION 0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-std=c++23 -O3 -g -pg --pedantic -Wall -Wextra")

set(CMAKE_PREFIX_PATH "/usr/local/")

find_package(GTest REQUIRED)
find_package(benchmark REQUIRED)

include_directories(include src)

add_library(${PROJECT_NAME} STATIC ${PROJECT_SOURCE_DIR}/include/ctda.hpp)
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

add_subdirectory(tests)

install(TARGETS ${PROJECT_NAME} DESTINATION lib)
install(
    FILES 
        ${PROJECT_SOURCE_DIR}/include/ctda.hpp 
        ${PROJECT_SOURCE_DIR}/src/traits.hpp
        ${PROJECT_SOURCE_DIR}/src/base.hpp
        ${PROJECT_SOURCE_DIR}/src/unit.hpp
        ${PROJECT_SOURCE_DIR}/src/units.hpp
        ${PROJECT_SOURCE_DIR}/src/quantity.hpp
        ${PROJECT_SOURCE_DIR}/src/io.hpp
        ${PROJECT_SOURCE_DIR}/src/math.hpp

    DESTINATION include/ctda
)

install(
    FILES
        ${PROJECT_SOURCE_DIR}/src/math/operators.hpp

    DESTINATION include/ctda/math
)

install(
    FILES
        ${PROJECT_SOURCE_DIR}/src/math/algebraic/add.hpp
        ${PROJECT_SOURCE_DIR}/src/math/algebraic/multiply.hpp
        ${PROJECT_SOURCE_DIR}/src/math/algebraic/negate.hpp
        ${PROJECT_SOURCE_DIR}/src/math/algebraic/invert.hpp 


    DESTINATION include/ctda/math/algebraic
)