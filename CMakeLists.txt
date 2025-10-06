# CMakeLists.txt
cmake_minimum_required(VERSION 3.16)
project(V51GammaAlphaSc47 LANGUAGES CXX)

# Find Geant4 with UI and visualization components
find_package(Geant4 REQUIRED ui_all vis_all)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Convenience include (matches Geant4 examples: sets compile defs/include dirs)
include(${Geant4_USE_FILE})

file(GLOB sources CONFIGURE_DEPENDS src/*.cc)
file(GLOB headers CONFIGURE_DEPENDS include/*.hh)

add_executable(v51_gamma_alpha ${sources} ${headers})

# Public include dir so MSVC finds headers
target_include_directories(v51_gamma_alpha PRIVATE ${PROJECT_SOURCE_DIR}/include)

# Prefer MT if available
if(Geant4_multithreaded_FOUND)
  target_compile_definitions(v51_gamma_alpha PRIVATE G4MULTITHREADED)
endif()

# Warnings
if(MSVC)
  target_compile_options(v51_gamma_alpha PRIVATE /W3)
else()
  target_compile_options(v51_gamma_alpha PRIVATE -Wall -Wextra -Wno-unused-parameter)
endif()

# Link Geant4
target_link_libraries(v51_gamma_alpha PRIVATE ${Geant4_LIBRARIES})

# Copy macros next to the built executable for each config (Debug/Release)
add_custom_command(TARGET v51_gamma_alpha POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E make_directory "$<TARGET_FILE_DIR:v51_gamma_alpha>/macros"
  COMMAND ${CMAKE_COMMAND} -E copy_directory "${PROJECT_SOURCE_DIR}/macros" "$<TARGET_FILE_DIR:v51_gamma_alpha>/macros"
  VERBATIM)

# (Optional) Install targets and macros
install(TARGETS v51_gamma_alpha RUNTIME DESTINATION bin)
install(DIRECTORY macros DESTINATION share)