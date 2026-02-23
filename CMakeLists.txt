cmake_minimum_required(VERSION 4.1)
project(ttu_currency_exchange_c_)

set(CMAKE_CXX_STANDARD 14)

add_executable(ttu_currency_exchange_c_
        main.cpp
        management.cpp
        convert_currency.cpp
        conversion_rate.cpp
        conversion_rate.h
        convert_currency.h
        management.h
        client_user.cpp
        client_user.h
)
