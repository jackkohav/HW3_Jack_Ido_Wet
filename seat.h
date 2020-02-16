#include <iostream>
#include <string>
using std::string;
using std::exception;
#define NO_PRICE -1

// ---------------------------------------------
class NoPrice: public exception
{
};

// ---------------------------------------------
class Seat
{
protected:
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
class GreenRoomSeat: public Seat
{
public:
    GreenRoomSeat(int line, int chair):
        Seat(line, chair, NO_PRICE){}
    int price() const override {
        throw NoPrice();
    }
    string location() const override {
        return "Green Room-> line: " + std::to_string(line_number)
            + ", chair: " + std::to_string(chair_number);
    }
};

// ---------------------------------------------
class MainHallSeat: public Seat
{
protected:
    static const int addition_main_hall;
public:
    MainHallSeat(int line, int chair, int base):
        Seat(line, chair, base){}
};

// ---------------------------------------------
class SpecialSeat: public MainHallSeat
{
protected:
    static const int addition_special_seat;
public:
    SpecialSeat(int line, int chair, int base):
        MainHallSeat(line, chair, base){}
};

// ---------------------------------------------
class GoldenCircleSeat: public SpecialSeat
{
    static const int addition_golden_circle_seat;
public:
    GoldenCircleSeat(int line, int chair, int base):
        MainHallSeat(line, chair, base){}
    int price() const override{
        return base + addition_main_hall
            + addition_special_seat + addition_golden_circle_seat;
    }
    string location() const override{
        return "Golden Circle-> line: " + std::to_string(line_number)
               + ", chair: " + std::to_string(chair_number);
    }
};

// ---------------------------------------------
class DisablePodiumSeat
{
    static const int disable_podium_price;
public:
    GoldenCircleSeat(int line, int chair, int base):
            MainHallSeat(line, chair, base){}
    int price() const override{
        return disable_podium_price;
    }
    string location() const override{
        return "Disable Podium-> line: " + std::to_string(line_number)
               + ", chair: " + std::to_string(chair_number);
    }
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
