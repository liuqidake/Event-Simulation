cmake_minimum_required(VERSION 3.13)
project(EventSimulations)

set(CMAKE_CXX_STANDARD 14)

add_executable(EventSimulations main.cpp BankSimulator.cpp BankSimulator.h EventSimulation.cpp EventSimulation.h Customer.h SupermarketSimulator.cpp SupermarketSimulator.h)