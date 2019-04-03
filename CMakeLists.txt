cmake_minimum_required(VERSION 3.13)
project(EventSimulations)

set(CMAKE_CXX_STANDARD 14)

add_executable(EventSimulator main.cpp BankSimulator.cpp BankSimulator.h EventSimulator.cpp EventSimulator.h Customer.h SupermarketSimulator.cpp SupermarketSimulator.h)