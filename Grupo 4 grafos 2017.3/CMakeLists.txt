cmake_minimum_required(VERSION 3.8)
project(Grupo_4_grafos_2017_3)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        Headers/Aresta.h
        Headers/Grafo.h
        Headers/No.h
        Source/Aresta.cpp
        Source/Grafo.cpp
        Source/No.cpp
        Main.cpp
        teste.txt)

add_executable(Grupo_4_grafos_2017_3 ${SOURCE_FILES})