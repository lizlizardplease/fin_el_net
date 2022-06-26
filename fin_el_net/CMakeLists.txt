cmake_minimum_required(VERSION 3.19)
project(fin_el_net)
set(CMAKE_CXX_STANDARD 20)

add_executable(fin_el_net main.cpp MeshLoader.h MeshLoader.cpp Structures.h Structures.cpp Exceptions.h AneuMeshLoader.cpp AneuMeshLoader.h NeuMeshLoader.h NeuMeshLoader.cpp Hash.h)



