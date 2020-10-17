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
include(GNUInstallDirs)

#
add_executable(WCreate
  "sources/WCreate.cpp"
  "sources/Random.h"
  "sources/Random.cpp"
  "sources/Wavetable.h"
  "sources/Wavetable.cpp"
  "sources/WaveFormula.h"
  "sources/WaveFormula.cpp"
  "sources/series/SeriesExpr.h"
  "sources/series/SeriesExpr.cpp"
  "sources/series/SeriesExprGrammar.tab.cpp"
  "sources/series/SeriesExprGrammar.tab.h"
  "sources/series/SeriesExprGrammar.yy.cpp"
  "sources/series/SeriesExprGrammar.yy.h"
  "sources/series/SeriesExprGrammarExtra.h"
  "sources/utility/Locale.h")
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
    OUTPUT "${PROJECT_SOURCE_DIR}/sources/series/SeriesExprGrammar.tab.cpp"
    COMMAND "${BISON_PROGRAM}" "--output=SeriesExprGrammar.tab.cpp" "--defines=SeriesExprGrammar.tab.h" "SeriesExprGrammar.y"
    DEPENDS "${PROJECT_SOURCE_DIR}/sources/series/SeriesExprGrammar.y"
    BYPRODUCTS "${PROJECT_SOURCE_DIR}/sources/series/SeriesExprGrammar.tab.h"
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/sources/series")
  add_custom_command(
    OUTPUT "${PROJECT_SOURCE_DIR}/sources/series/SeriesExprGrammar.yy.cpp"
    COMMAND "${FLEX_PROGRAM}" "--outfile=SeriesExprGrammar.yy.cpp" "--header-file=SeriesExprGrammar.yy.h" "SeriesExprGrammar.l"
    DEPENDS "${PROJECT_SOURCE_DIR}/sources/series/SeriesExprGrammar.l"
    BYPRODUCTS "${PROJECT_SOURCE_DIR}/sources/series/SeriesExprGrammar.yy.h"
    WORKING_DIRECTORY "${PROJECT_SOURCE_DIR}/sources/series")
endif()

#
install(TARGETS WCreate WMorph RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}")
