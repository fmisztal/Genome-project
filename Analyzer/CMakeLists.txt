cmake_minimum_required(VERSION 3.5)

project(Analyzer LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(Analyzer main.cpp lista.cpp kolejka.cpp drzewo.cpp)
