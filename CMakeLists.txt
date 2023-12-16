cmake_minimum_required(VERSION 3.26)
project(ant_colony)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5.1 COMPONENTS graphics window system REQUIRED)

add_executable(ant_colony app/main.cpp
        app/src/simulateur/simulateur.cpp
        app/src/gui/gui.cpp
        app/src/simulateur/colonie/colonie.cpp
        app/src/simulateur/fourmi/fourmi.cpp
        app/src/simulateur/carte/carte.cpp
        app/src/simulateur/colonie/colonie.cpp
        app/include/simulateur/colonie/colonie.h
        app/include/simulateur/fourmi/fourmi_anarchiste.h
        app/include/simulateur/fourmi/fourmi_soldat.h
        app/include/simulateur/fourmi/fourmi_eclaireur.h
        app/include/simulateur/fourmi/fourmi_ouvriere.h
        app/include/simulateur/fourmi/fourmi_reine.h
        app/src/simulateur/fourmi/fourmi_soldat.cpp
        app/src/simulateur/fourmi/fourmi_reine.cpp
        app/src/simulateur/fourmi/fourmi_ouvriere.cpp
        app/src/simulateur/fourmi/fourmi_anarchiste.cpp
        app/src/simulateur/fourmi/fourmi_eclaireur.cpp
        app/src/simulateur/carte/case.cpp
        app/include/simulateur/carte/case.h
)

include_directories(app/include/simulateur)
include_directories(app/include/simulateur/carte)
include_directories(app/include/simulateur/colonie)
include_directories(app/include/simulateur/fourmi)
include_directories(app/include/gui)

target_include_directories(ant_colony PUBLIC app/include)
target_link_libraries(ant_colony sfml-graphics sfml-window sfml-system)
