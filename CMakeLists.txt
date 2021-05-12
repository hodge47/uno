cmake_minimum_required(VERSION 3.12)
project(uno)

set(CMAKE_CXX_STANDARD 20)

add_executable(uno src/main.cpp src/Card.cpp src/Card.h src/Deck.cpp src/Deck.h src/Player.cpp src/Player.h src/GameManager.cpp src/GameManager.h)