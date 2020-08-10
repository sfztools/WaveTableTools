cmake_minimum_required(VERSION "3.7")

project(WaveTableTools)

if(CMAKE_CXX_COMPILER_ID MATCHES "^(GNU|Clang|AppleClang)$")
  string(APPEND CMAKE_CXX_FLAGS " -Wall")
endif()

add_subdirectory("thirdparty/kiss_fft" EXCLUDE_FROM_ALL)

#
find_package(PkgConfig REQUIRED)
pkg_check_modules(sndfile "sndfile" REQUIRED IMPORTED_TARGET)

#
add_executable(WCreate
  "sources/WCreate.cpp"
  "sources/Expr.h"
  "sources/Expr.cpp"
  "sources/Random.h"
  "sources/Random.cpp"
  "sources/Wavetable.h"
  "sources/Wavetable.cpp"
  "sources/ExprGrammar.tab.cpp"
  "sources/ExprGrammar.tab.h"
  "sources/ExprGrammar.yy.cpp"
  "sources/ExprGrammar.yy.h")
#if(TRUE)
#  target_compile_definitions(WCreate PRIVATE
#    "YYDEBUG=1")
#endif()
target_include_directories(WCreate PRIVATE
  "sources")
target_link_libraries(WCreate PRIVATE
  sfizz-kissfft)

#
add_executable(WMorph
  "sources/WMorph.cpp"
  "sources/Wavetable.h"
  "sources/Wavetable.cpp")
target_include_directories(WMorph PRIVATE
  "sources")
target_link_libraries(WMorph PRIVATE
  PkgConfig::sndfile)

#
find_program(FLEX_PROGRAM "flex")
find_program(BISON_PROGRAM "bison")
if(FLEX_PROGRAM AND BISON_PROGRAM)
  add_custom_command(
    OUTPUT "${PROJECT_SOURCE_DIR}/sources/ExprGrammar.tab.cpp"
    COMMAND "${BISON_PROGRAM}" "--output=ExprGrammar.tab.cpp" "--defines=ExprGrammar.tab.h" "ExprGrammar.y"
    DEPENDS "${PROJECT_SOURCE_DIR}/sources/ExprGrammar.y"
    BYPRODUCTS "${PROJECT_SOURCE_DIR}/sources/ExprGrammar.tab.h"
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/sources")
  add_custom_command(
    OUTPUT "${PROJECT_SOURCE_DIR}/sources/ExprGrammar.yy.cpp"
    COMMAND "${FLEX_PROGRAM}" "--outfile=ExprGrammar.yy.cpp" "--header-file=ExprGrammar.yy.h" "ExprGrammar.l"
    DEPENDS "${PROJECT_SOURCE_DIR}/sources/ExprGrammar.l"
    BYPRODUCTS "${PROJECT_SOURCE_DIR}/sources/ExprGrammar.yy.h"
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/sources")
endif()
