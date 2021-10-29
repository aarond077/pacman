cmake_minimum_required(VERSION 3.10)
project(pacman)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_PREFIX_PATH "C:\\Qt\\5.14.2\\msvc2017")

find_package(Qt5Core REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Quick REQUIRED)

add_executable(pacman main.cpp simulation.cpp simulation.h tile.cpp tile.h ConsoleWindow.cpp ConsoleWindow.h enemy.cpp enemy.h pacman.cpp pacman.h position.cpp position.h console_timer.cpp console_timer.h)

target_link_libraries(pacman Qt5::Core)
target_link_libraries(pacman Qt5::Widgets)
target_link_libraries(pacman Qt5::Quick)
