add_executable(test46 test46.c mbuild-nsymm.c funcs.c)
target_link_libraries(test46 math m)
target_include_directories(test46 PUBLIC ${PROJECT_SOURCE_DIR})

find_package(GTest REQUIRED)
find_package(LAPACK REQUIRED)

add_executable(mls_test mls_test.cpp)
target_link_libraries(mls_test PRIVATE GTest::gtest_main math LAPACK::LAPACK)
target_include_directories(mls_test PRIVATE ${PROJECT_SOURCE_DIR})

include(GoogleTest)
gtest_discover_tests(mls_test)
