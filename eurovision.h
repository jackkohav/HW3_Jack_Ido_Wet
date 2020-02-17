#ifndef EUROVISION_H_
#define EUROVISION_H_

#include <iostream>
#include <string>
using std::string;
// it's allowed to define here any using statements, according to needs.
// do NOT define here : using namespace std;

//---------------------------------------------------

enum VoterType { All, Regular, Judge };
enum Phase { Registration, Contest, Voting };

//---------------------------------------------------
class Participant
{
// relevant private members can be defined here, if necessary.
    bool _is_registered;
    string _state;
    string _song;
    int _time_length;
    string _singer;
public :
// need to define here possibly c'tr and d'tr and ONLY methods that
// are mentioned and demonstrated in the test example that has been published.
// NO OTHER METHODS SHOULD APPEAR HERE.
    Participant(const string& state, const string& song, const int& timeLength, const string& singer);
    Participant(const Participant& p) = delete;
    ~Participant() = default;
    string state() const;
    string song() const;
    int timeLength() const;
    string singer() const;
    bool isRegistered() const;
    void update(const string& new_song, const int& new_time_length, const string& new_singer);
    void updateRegistered(bool is_registered);
    Participant& operator=(const Participant& p) = delete;
// NO friend is allowed here.

};
std::ostream& operator <<(std::ostream& os, Participant& p);
//---------------------------------------------------


class Voter
{
// relevant private members can be defined here, if necessary.
    string _state;
    VoterType _type;

public :
    explicit Voter(const string& state, const VoterType& type = Regular);
    ~Voter() = default;
    string state() const;
    VoterType voterType() const;
// need to define here possibly c'tr and d'tr and ONLY methods that
// are mentioned and demonstrated in the test example that has been published.
// NO OTHER METHODS SHOULD APPEAR HERE.

// NO friend is allowed here.

};

std::ostream& operator<<(std::ostream& os, const Voter& v){
    os << "<" << v.state() << "/" << v.voterType() << ">";
    return os;
}

// -----------------------------------------------------------

struct Vote
{
    string twelve_pts;
    string ten_pts;
    string eight_pts;
    string seven_pts;
    string six_pts;
    string five_pts;
    string four_pts;
    string three_pts;
    string two_pts;
    string one_pts;
    Voter voter;
    Vote(const Voter& voter, const string& vote);
    Vote(const Voter& voter, const string& vote1, const string& vote2,
        const string& vote3 = string(""), const string& vote4 = string(""),
        const string& vote5 = string(""), const string& vote6 = string(""),
        const string& vote7 = string(""), const string& vote8 = string(""),
        const string& vote9 = string(""), const string& vote10 = string(""));
    ~Vote() = default;
// ALL is public here.
// need to define ONLY data members and c'tr and d'tr.
// NO NEED to define anything else.

};

// -----------------------------------------------------------


class MainControl
{
// relevant private members can be defined here, if necessary.

public :

// need to define here possibly c'tr and d'tr and ONLY methods that
// are mentioned and demonstrated in the test example that has been published.
// NO OTHER METHODS SHOULD APPEAR HERE.

// Also it's allowed here to define friend.

};

// -----------------------------------------------------------

#endif
