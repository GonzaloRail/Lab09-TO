cmake_minimum_required(VERSION 3.16)

project(ER1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ER1 main.cpp
    foomanager.h foomanager.cpp)

include(GNUInstallDirs)
install(TARGETS ER1
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
