cmake_minimum_required(VERSION 3.26)
project(ant_colony_clion)

set(CMAKE_CXX_STANDARD 11)

find_package(SFML 2.5.1 COMPONENTS graphics window system REQUIRED)

add_executable(ant_colony_clion app/main.cpp
        app/src/simulateur/colonie.cpp
        app/include/colonie.h
        app/src/gui/gui.cpp
        app/include/gui.h
        app/src/simulateur/fourmi/fourmi.cpp
        app/include/fourmi.h
        app/include/constantes.h
)

target_link_libraries(ant_colony_clion sfml-graphics sfml-window sfml-system)
