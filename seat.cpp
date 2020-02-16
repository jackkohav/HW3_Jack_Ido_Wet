#include <iostream>
#include <string>
using std::string;
using std::exception;

#include "seat.h"

char const* NoPrice::what() const noexcept {
    return "Not For Sale !";
}

int MainHallSeat::addition_main_hall = 100;

int SpecialSeat::addition_special_seat = 300;

int GoldenCircleSeat::addition_golden_circle_seat = 1000;

int DisablePodiumSeat::disable_podium_price = 200;

int FrontRegularSeat::addition_front = 500;

int MiddleRegularSeat::addition_middle = 250;