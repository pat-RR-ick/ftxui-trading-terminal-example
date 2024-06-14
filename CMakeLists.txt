cmake_minimum_required(VERSION 3.11)

# Fetch dependencies
include(FetchContent)
set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)

# Fetch fmt library
FetchContent_Declare(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
  GIT_TAG 9.1.0  # Replace with a stable tag or commit hash
)
FetchContent_MakeAvailable(fmt)

# Fetch ftxui library
FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
  GIT_TAG main  # Consider using a stable tag or commit hash if available
)
FetchContent_MakeAvailable(ftxui)

# Project setup
project(home_screen LANGUAGES CXX VERSION 1.0.0)

# Add executable
add_executable(home_screen
  src/main.cpp
  src/htop_component.cpp
  src/bar_chart_component.cpp
  src/flags_component.cpp 
  src/order_book_component.cpp 
  src/data_utils.hpp 
)

# Include directories
target_include_directories(home_screen PRIVATE ${ftxui_SOURCE_DIR}/include ${fmt_SOURCE_DIR}/include)

# Link libraries
target_link_libraries(home_screen
  PRIVATE ftxui::screen
  PRIVATE ftxui::dom
  PRIVATE ftxui::component
  PRIVATE fmt::fmt
)

# Print messages for debugging
message(STATUS "ftxui_SOURCE_DIR: ${ftxui_SOURCE_DIR}")
message(STATUS "fmt_SOURCE_DIR: ${fmt_SOURCE_DIR}")
