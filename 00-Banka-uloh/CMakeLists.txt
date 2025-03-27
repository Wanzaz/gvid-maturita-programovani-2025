cmake_minimum_required(VERSION 3.5)

project(00-Banka-uloh LANGUAGES C)

add_executable(00-Banka-uloh main.c)

include(GNUInstallDirs)
install(TARGETS 00-Banka-uloh
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
