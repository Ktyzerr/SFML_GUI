cmake_minimum_required(VERSION 3.25)
project("SFML_GUI_PROJECT" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(SFML 3.0 COMPONENTS Graphics Window System REQUIRED)

add_subdirectory(SFML_GUI)
add_subdirectory(examples)