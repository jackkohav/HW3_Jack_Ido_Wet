#include <iostream>
#include <string>
using std::string;
using std::exception;
#define NO_PRICE -1

// ---------------------------------------------
class NoPrice
{
};

// ---------------------------------------------
class Seat
{
    const int line_number
    int chair_number;
    int base_price;
public:
    Seat(int line, int chair, int base):
        line_number(line), chair_number(chair), base_price(base){}
    virtual int price() const = 0;
    virtual string location() const = 0;
};

// ---------------------------------------------
class GreenRoomSeat
{
    static const int
public:
    GreenRoomSeat(int line, int chair):
        Seat(line, chair, NO_PRICE){}
    int price() const override {
        throw NoPrice();
    }
    string location() const override {
        return "Green Room-> line: " + std::to_string(line_number) + ", chair: " +
           std::to_string(chair_number);
    }
};

// ---------------------------------------------
class MainHallSeat
{
};

// ---------------------------------------------
class SpecialSeat
{
};

// ---------------------------------------------
class GoldenCircleSeat
{
};

// ---------------------------------------------
class DisablePodiumSeat
{
};

// ---------------------------------------------
class RegularSeat
{
};

// ---------------------------------------------
class FrontRegularSeat
{
};

// ---------------------------------------------
class MiddleRegularSeat
{
};

// ---------------------------------------------
class RearRegularSeat
{
};

// ---------------------------------------------
