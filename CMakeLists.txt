cmake_minimum_required(VERSION 3.19)
project(uno)

set(CMAKE_CXX_STANDARD 20)

add_executable(uno src/main.cpp src/Card.cpp src/Card.h src/Deck.cpp src/Deck.h)