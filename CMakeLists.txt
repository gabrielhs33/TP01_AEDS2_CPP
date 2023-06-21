cmake_minimum_required(VERSION 3.23)
project(TP01_AEDS2_CPP)

set(CMAKE_CXX_STANDARD 14)

add_executable(TP01_AEDS2_CPP main.cpp entities/aluno/Aluno.cpp entities/aluno/Aluno.h entities/menu/Menu.cpp entities/menu/Menu.h entities/aluno/Professor.cpp entities/aluno/Professor.h entities/aluno/Gestor.cpp entities/aluno/Gestor.h)
