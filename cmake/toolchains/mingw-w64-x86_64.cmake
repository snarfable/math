set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_SYSTEM_PROCESSOR x86_64)

set(MINGW_TRIPLE "x86_64-w64-mingw32" CACHE STRING
    "Target triplet used to name the MinGW-w64 cross-compilers")
set(MINGW_SYSROOT "/usr/${MINGW_TRIPLE}" CACHE PATH
    "Root directory of the MinGW-w64 target libraries and headers")

set(CMAKE_C_COMPILER "${MINGW_TRIPLE}-gcc" CACHE STRING
    "MinGW-w64 C compiler")
set(CMAKE_CXX_COMPILER "${MINGW_TRIPLE}-g++" CACHE STRING
    "MinGW-w64 C++ compiler")
set(CMAKE_Fortran_COMPILER "${MINGW_TRIPLE}-gfortran" CACHE STRING
    "MinGW-w64 Fortran compiler")
set(CMAKE_RC_COMPILER "${MINGW_TRIPLE}-windres" CACHE STRING
    "MinGW-w64 resource compiler")

set(CMAKE_FIND_ROOT_PATH "${MINGW_SYSROOT}")
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)
