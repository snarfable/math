cmake_minimum_required(VERSION 4.0.0)
project(math VERSION 0.1.0)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

include(CTest)
enable_testing()

enable_language(Fortran)
set(FC gfortran)

set(GROMACS_VERSION "2018")
set(CMAKE_Fortran_SOURCE_FILE_EXTENSIONS f90)

option(HAVE_DOUBLE ON)

add_library(mathext linalg.f90 runge.f90 anint.f90)
add_library(math lagrange.c quadrature.c nurbs.c legendre.c mls.c cgrad.c mqrbf.c points.c nuclei.c sparse.c punity.c pbc.c anint.f90 combinadic.c parse.c trees.c symtab.c cfgread.c
    killmeplease.cpp)
add_executable(killmeplease killmeplease.cpp)
target_link_libraries(math gromacs mathext)
target_include_directories(math PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
target_include_directories(mathext PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

configure_file(${PROJECT_SOURCE_DIR}/math_config.h.in ${PROJECT_SOURCE_DIR}/math_config.h)

add_subdirectory(test)

add_library(math::math ALIAS math)
add_library(math::mathext ALIAS mathext)

install(TARGETS math mathext
    EXPORT mathTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
file(GLOB math_public_headers CONFIGURE_DEPENDS "${PROJECT_SOURCE_DIR}/*.h")
install(FILES ${math_public_headers}
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
set(math_cmake_install_dir "${CMAKE_INSTALL_LIBDIR}/cmake/math")
configure_package_config_file(
    "${PROJECT_SOURCE_DIR}/cmake/mathConfig.cmake.in"
    "${PROJECT_BINARY_DIR}/mathConfig.cmake"
    INSTALL_DESTINATION "${math_cmake_install_dir}"
)
write_basic_package_version_file(
    "${PROJECT_BINARY_DIR}/mathConfigVersion.cmake"
    VERSION "${PROJECT_VERSION}"
    COMPATIBILITY SameMajorVersion
)
install(EXPORT mathTargets
    FILE mathTargets.cmake
    NAMESPACE math::
    DESTINATION "${math_cmake_install_dir}"
)
install(FILES
    "${PROJECT_BINARY_DIR}/mathConfig.cmake"
    "${PROJECT_BINARY_DIR}/mathConfigVersion.cmake"
    DESTINATION "${math_cmake_install_dir}"
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
