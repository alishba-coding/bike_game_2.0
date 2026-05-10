cmake_minimum_required(VERSION 3.10)
project(MotorcycleGame)

# 1. Force C++20 Standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 2. Tell CMake where your local SFML 3.0 lives
set(SFML_DIR "${CMAKE_CURRENT_SOURCE_DIR}/dependencies/sfml/lib/cmake/SFML")

# 3. Find SFML 3.0 (Note the version change here)
find_package(SFML 3.0 COMPONENTS graphics window system REQUIRED)

# 4. Create the executable 
# IMPORTANT: Add your other .cpp files here as you create them!
add_executable(MotorcycleGame main.cpp)

# 5. Link the libraries
target_link_libraries(MotorcycleGame sfml-graphics sfml-window sfml-system)