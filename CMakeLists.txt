cmake_minimum_required(VERSION 3.5.0)
project(TaxiBookingSystem VERSION 0.1.0 LANGUAGES C CXX)
set (CMAKE_CXX_STANDARD 11)

add_executable(TaxiBookingApp TaxiBookingApp.cpp Booking.cpp User.cpp
    Booking.h Driver.h Functions.h Passenger.h Questions.h User.h Vehicle.h
)

