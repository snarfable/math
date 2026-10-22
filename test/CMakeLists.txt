add_executable(test46 test46.c mbuild-nsymm.c funcs.c)
target_link_libraries(test46 math m)
target_include_directories(test46 PUBLIC ${PROJECT_SOURCE_DIR})

include(FetchContent)

# --- GoogleTest -------------------------------------------------------------
# Prefer a system/config package when one is available (keeps native builds
# fast). Fall back to building from source, which is what the MinGW cross-build
# needs since no Windows GTest ships in the sysroot.
find_package(GTest QUIET)
if(NOT GTest_FOUND)
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        v1.14.0
    )
    FetchContent_MakeAvailable(googletest)
endif()

# --- BLAS / LAPACK ----------------------------------------------------------
# Same strategy: use the system LAPACK natively, otherwise cross-build the
# Netlib reference BLAS + LAPACK from source. This needs a Fortran compiler,
# which the MinGW toolchain supplies via gfortran-mingw-w64.
find_package(LAPACK QUIET)
if(NOT LAPACK_FOUND)
    # Reference LAPACK builds the reference BLAS itself; keep the extras and its
    # own (Fortran) test suite off. Set as normal variables so the reference
    # project's option() calls pick them up (CMP0077) without mutating the
    # parent project's cached BUILD_TESTING.
    set(CBLAS OFF)
    set(LAPACKE OFF)
    set(BUILD_TESTING OFF)
    FetchContent_Declare(
        lapack
        GIT_REPOSITORY https://github.com/Reference-LAPACK/lapack.git
        GIT_TAG        v3.12.0
    )
    FetchContent_MakeAvailable(lapack)
    # Reference LAPACK exports lowercase 'lapack'/'blas' targets; 'lapack'
    # already links 'blas'. Expose the same imported-target name module-mode
    # FindLAPACK would provide so the consumer below is source-compatible.
    if(NOT TARGET LAPACK::LAPACK)
        add_library(LAPACK::LAPACK ALIAS lapack)
    endif()
endif()

add_executable(mls_test mls_test.cpp)
target_link_libraries(mls_test PRIVATE GTest::gtest_main math LAPACK::LAPACK)
target_include_directories(mls_test PRIVATE ${PROJECT_SOURCE_DIR})

include(GoogleTest)
if(CMAKE_CROSSCOMPILING)
    # Can't run the Windows test binary on the build host, so defer test
    # enumeration to ctest time instead of running it during the build.
    gtest_discover_tests(mls_test DISCOVERY_MODE PRE_TEST)
else()
    gtest_discover_tests(mls_test)
endif()
