cmake_minimum_required(VERSION 3.10.2)
project(kitty-dash)

# C++ standardı
set(CMAKE_CXX_STANDARD 17)

# Kaynak dosyalarımızı derlemeye dahil et
add_executable(kitty-dash 
    main.cpp
)

