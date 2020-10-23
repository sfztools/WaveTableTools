cmake_minimum_required(VERSION "3.7")

project(WaveTableTools)

set(CMAKE_CXX_STANDARD 11)

option(WAVE_TABLE_TOOLS_ENABLE_UI "Enable UI" ON)

if(CMAKE_CXX_COMPILER_ID MATCHES "^(GNU|Clang|AppleClang)$")
  string(APPEND CMAKE_CXX_FLAGS " -Wall")
endif()

if(WIN32)
  add_compile_definitions("-D_USE_MATH_DEFINES=1")
endif()

add_subdirectory("thirdparty/kiss_fft" EXCLUDE_FROM_ALL)
add_subdirectory("thirdparty/span-lite" EXCLUDE_FROM_ALL)

#
find_package(PkgConfig REQUIRED)
pkg_check_modules(sndfile "sndfile" REQUIRED IMPORTED_TARGET)

#
include(GNUInstallDirs)

#
add_library(WLib STATIC
  "sources/Random.h"
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
#  target_compile_definitions(WLib PRIVATE "YYDEBUG=1")
#endif()
target_include_directories(WLib PUBLIC
  "sources")
target_link_libraries(WLib PRIVATE
  sfizz-kissfft)

#
add_executable(WCreate
  "sources/WCreate.cpp"
  "sources/utility/unicodefile.h"
  "sources/utility/unicodefile.c")
target_link_libraries(WCreate PRIVATE WLib)

#
add_executable(WMorph
  "sources/WMorph.cpp"
  "sources/utility/unicodefile.h"
  "sources/utility/unicodefile.c")
target_link_libraries(WMorph PRIVATE WLib PkgConfig::sndfile)

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
if(WAVE_TABLE_TOOLS_ENABLE_UI)
  find_package(SDL2 REQUIRED)
  set(OpenGL_GL_PREFERENCE "GLVND")
  find_package(OpenGL REQUIRED)
  if(WIN32)
  elseif(APPLE)
    find_library(APPKIT_FRAMEWORK "AppKit")
  else()
    pkg_check_modules(Gtk3 "gtk+-3.0" REQUIRED IMPORTED_TARGET)
  endif()

  #
  add_library(imgui STATIC
    "thirdparty/imgui/imgui.cpp"
    "thirdparty/imgui/imgui_draw.cpp"
    "thirdparty/imgui/imgui_widgets.cpp"
    "thirdparty/imgui/misc/cpp/imgui_stdlib.cpp")
  target_include_directories(imgui PUBLIC
    "thirdparty/imgui"
    "thirdparty/imgui/misc/cpp")

  #
  add_library(implot STATIC
    "thirdparty/implot/implot.cpp"
    "thirdparty/implot/implot_items.cpp")
  target_include_directories(implot PUBLIC "thirdparty/implot")
  target_link_libraries(implot PUBLIC imgui)

  #
  add_library(imgui-backend STATIC
    "thirdparty/imgui/backends/imgui_impl_sdl.cpp"
    "thirdparty/imgui/backends/imgui_impl_opengl2.cpp")
  target_include_directories(imgui-backend PUBLIC
    "thirdparty/imgui"
    "thirdparty/imgui/backends")
  if(TARGET SDL2::SDL2)
    target_link_libraries(imgui-backend PUBLIC SDL2::SDL2 OpenGL::OpenGL)
  else()
    target_include_directories(imgui-backend PUBLIC ${SDL2_INCLUDE_DIRS})
    target_link_libraries(imgui-backend PUBLIC ${SDL2_LIBRARIES})
  endif()

  #
  add_library(osdialog STATIC "thirdparty/osdialog/osdialog.c")
  target_include_directories(osdialog PUBLIC "thirdparty/osdialog")
  if(WIN32)
    target_sources(osdialog PRIVATE "thirdparty/osdialog/osdialog_win.c")
    target_link_libraries(osdialog PRIVATE "comdlg32")
  elseif(APPLE)
    target_sources(osdialog PRIVATE "thirdparty/osdialog/osdialog_mac.m")
    target_link_libraries(osdialog PRIVATE "${APPKIT_FRAMEWORK}")
  else()
    target_sources(osdialog PRIVATE "thirdparty/osdialog/osdialog_gtk3.c")
    target_link_libraries(osdialog PRIVATE PkgConfig::Gtk3)
  endif()

  #
  add_executable(WEdit WIN32
    "sources/interactive/WEdit.cpp"
    "sources/interactive/dsp/Wavetables.cpp"
    "sources/interactive/dsp/Wavetables.h"
    "sources/utility/unicodefile.h"
    "sources/utility/unicodefile.c")
  target_link_libraries(WEdit PRIVATE WLib implot imgui imgui-backend osdialog sfizz-kissfft nonstd::span-lite)
  if(NOT (WIN32 OR APPLE))
    target_link_libraries(WEdit PRIVATE PkgConfig::Gtk3)
  endif()
endif()

#
install(TARGETS WCreate WMorph RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}")
if(WAVE_TABLE_TOOLS_ENABLE_UI)
  install(TARGETS WEdit RUNTIME DESTINATION "${CMAKE_INSTALL_BINDIR}")
endif()
