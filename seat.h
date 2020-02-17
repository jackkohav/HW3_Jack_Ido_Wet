#include <iostream>
#include <string>
using std::string;
using std::exception;

#define NO_PRICE (-1)

// ---------------------------------------------
class NoPrice: public exception
{
public:
    char const *what() const noexcept override{
        return "Not For Sale !";
    }
};

// ---------------------------------------------
class Seat
{
protected:
    const int line;
    const int chair;
    const int base_price;
public:
    Seat(const int& line, const int& chair, const int& base_price):
        line(line), chair(chair), base_price(base_price){}
    virtual ~Seat() = default;
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
        return string("Green Room-> line: ") + std::to_string(line)
            + string(", chair: ") + std::to_string(chair);
    }
};

// ---------------------------------------------
class MainHallSeat: public Seat
{
protected:
    static int addition_main_hall;
public:
    MainHallSeat(const int& line, const int& chair, const int& base_price):
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
protected:
    static int addition_golden_circle_seat;
public:
    GoldenCircleSeat(const int& line, const int& chair, const int& base_price):
        SpecialSeat(line, chair, base_price){}
    int price() const override{
        return base_price + addition_main_hall
            + addition_special_seat + addition_golden_circle_seat;
    }
    string location() const override{
        return string("Golden Circle-> line: ") + std::to_string(line)
               + string(", chair: ") + std::to_string(chair);
    }
};

// ---------------------------------------------
class DisablePodiumSeat: public SpecialSeat
{
    static int disable_podium_price;
public:
    DisablePodiumSeat(const int& line, const int& chair, const int& base_price = NO_PRICE):
            SpecialSeat(line, chair, base_price){}
    int price() const override{
        return disable_podium_price;
    }
    string location() const override{
        return string("Disable Podium-> line: ") + std::to_string(line)
               + string(", chair: ") + std::to_string(chair);
    }
};

// ---------------------------------------------
class RegularSeat: public MainHallSeat
{
protected:
    const char area;
public:
    RegularSeat(const char& area, const int& line, const int& chair, const int& base_price):
        MainHallSeat(line, chair, base_price), area(area){}
};

// ---------------------------------------------
class FrontRegularSeat: public RegularSeat
{
    static int addition_front;
public:
    FrontRegularSeat(const char& area, const int& line, const int& chair, const int& base):
        RegularSeat(area, line, chair, base){}
    int price() const override{
        return base_price + addition_main_hall + addition_front;
    }
    string location() const override {
        return string("Front-> area: ") + area + string(", line: ") + std::to_string(line)
               + string(", chair: ") + std::to_string(chair);
    }
};

// ---------------------------------------------
class MiddleRegularSeat: public RegularSeat
{
    static int addition_middle;
public:
    MiddleRegularSeat(const char& area, const int& line, const int& chair, const int& base_price):
            RegularSeat(area, line, chair, base_price){}
    int price() const override{
        return base_price + addition_middle;
    }
    string location() const override {
        return string("Middle-> area: ") + area + string(", line: ") + std::to_string(line)
               + string(", chair: ") + std::to_string(chair);
    }
};

// ---------------------------------------------
class RearRegularSeat: public RegularSeat
{
public:
    RearRegularSeat(const char& area, const int& line, const int& chair, const int& base_price):
            RegularSeat(area, line, chair, base_price){}
    int price() const override{
        return base_price;
    }
    string location() const override {
        return string("Rear-> area: ") + area + string(", line: ") + std::to_string(line)
               + string(", chair: ") + std::to_string(chair);
    }
};

// ---------------------------------------------
