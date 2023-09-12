add_executable(
  quantity
  quantity.cpp
)

add_executable(
  andrea
  andrea.cpp
)
target_link_libraries(
  quantity
  GTest::gtest_main
)

add_executable(
  math
  math.cpp
)

target_link_libraries(
  math
  GTest::gtest_main
)


include(GoogleTest)
gtest_discover_tests(quantity ops)

