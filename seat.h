#include <iostream>
#include <string>
using std::string;
using std::exception;
#define NO_PRICE -1

// ---------------------------------------------
class NoPrice: public exception
{
public:
    virtual char const *what() const noexcept override();
};

// ---------------------------------------------
class Seat
{
protected:
    const int line
    const int chair;
    const int base_price;
public:
    Seat(const int& line, const int& chair, const int& base_price):
        line(line), chair(chair), base_price(base_price){}
    virtual int price() const = 0;
    virtual string location() const = 0;
};

// ---------------------------------------------
class GreenRoomSeat: public Seat
{
public:
    GreenRoomSeat(const int& line, const int& chair):
        Seat(line, chair, NO_PRICE){}
    int price() const override {
        throw NoPrice();
    }
    string location() const override {
        return "Green Room-> line: " + std::to_string(line)
            + ", chair: " + std::to_string(chair);
    }
};

// ---------------------------------------------
class MainHallSeat: public Seat
{
protected:
    static int addition_main_hall;
public:
    MainHallSeat(const int& line, cosnt int& chair, const int& base_price):
        Seat(line, chair, base_price){}
};

// ---------------------------------------------
class SpecialSeat: public MainHallSeat
{
protected:
    static int addition_special_seat;
public:
    SpecialSeat(const int& line, const int& chair, const int& base_price):
        MainHallSeat(line, chair, base_price){}
};

// ---------------------------------------------
class GoldenCircleSeat: public SpecialSeat
{
    static int addition_golden_circle_seat;
public:
    GoldenCircleSeat(const int& line, const int& chair, const int& base_price):
        MainHallSeat(line, chair, base_price){}
    int price() const override{
        return base_price + addition_main_hall
            + addition_special_seat + addition_golden_circle_seat;
    }
    string location() const override{
        return "Golden Circle-> line: " + std::to_string(line)
               + ", chair: " + std::to_string(chair);
    }
};

// ---------------------------------------------
class DisablePodiumSeat: public SpecialSeat
{
    static int disable_podium_price;
public:
    GoldenCircleSeat(const int& line, const int& chair, const int& base_price):
            MainHallSeat(line, chair, base_price){}
    int price() const override{
        return disable_podium_price;
    }
    string location() const override{
        return "Disable Podium-> line: " + std::to_string(line)
               + ", chair: " + std::to_string(chair);
    }
};

// ---------------------------------------------
class RegularSeat: public Seat
{
protected:
    static int addition_regular_seat;
    const char area;
public:
    RegularSeat(const char& area const int& line, const int& chair, const int& base_price):
        Seat(line, chair, base_price), area(area){}
};

// ---------------------------------------------
class FrontRegularSeat: public RegularSeat
{
    static int addition_front;
public:
    FrontRegularSeat(const char& area const int& line, const int& chair, const int& base):
        RegularSeat(area, line, chair, base){}
    int price() const override{
        return base_price + addition_regular_seat + addition_front;
    }
    string location() const override {
        return "Front-> area: " + area + ", line: " + std::to_string(line)
               + ", chair: " + std::to_string(chair);
    }
};

// ---------------------------------------------
class MiddleRegularSeat: public RegularSeat
{
    static int addition_middle;
public:
    FrontRegularSeat(const char& area const int& line, const int& chair, const int& base):
            RegularSeat(area, line, chair, base){}
    int price() const override{
        return base_price + addition_regular_seat + addition_middle;
    }
    string location() const override {
        return "Middle-> area: " + area + ", line: " + std::to_string(line)
               + ", chair: " + std::to_string(chair);
    }
};

// ---------------------------------------------
class RearRegularSeat
{
public:
    FrontRegularSeat(const char& area const int& line, const int& chair, const int& base):
            RegularSeat(area, line, chair, base){}
    int price() const override{
        return base_price;
    }
    string location() const override {
        return "Rear-> area: " + area + ", line: " + std::to_string(line)
               + ", chair: " + std::to_string(chair);
    }
};

// ---------------------------------------------
