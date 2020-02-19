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
std::ostream& operator <<(std::ostream& os, const Participant& p);
//---------------------------------------------------


class Voter
{
// relevant private members can be defined here, if necessary.
    string _state;
    VoterType _type;
    int _number_of_votes;

public :
    explicit Voter(const string& state, const VoterType& type = Regular);
    ~Voter() = default;
    string state() const;
    int timesOfVotes() const;
    VoterType voterType() const;
    Voter& operator++();
// need to define here possibly c'tr and d'tr and ONLY methods that
// are mentioned and demonstrated in the test example that has been published.
// NO OTHER METHODS SHOULD APPEAR HERE.

// NO friend is allowed here.

};

std::ostream& operator<<(std::ostream& os, const Voter& v);

// -----------------------------------------------------------

struct Vote
{
    string _points[10];
    Voter* _voter;
    Vote(Voter& voter, const string& vote);
    Vote(Voter& voter, const string& vote1, const string& vote2,
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
    Phase _phase;
    int _max_votes;
    int _number_of_votes;
    int _max_time_length;
    int _max_participants;
    int _number_of_participants;
    const Participant** _participants;
    int* _regular_votes; //holds in the i'th place the amount of votes given from the audience to the i'th participant
    int* _judge_votes;   //holds in the i'th place the amount of votes given from the judges to the i'th participant


public :
// need to define here possibly c'tr and d'tr and ONLY methods that
// are mentioned and demonstrated in the test example that has been published.
// NO OTHER METHODS SHOULD APPEAR HERE.
// Also it's allowed here to define friend.
    explicit MainControl(int max_length = 180, int max_participants = 26, int max_votes = 5);
    ~MainControl();
    void setPhase(const Phase& phase);
    bool legalParticipant(const Participant& p) const;
    bool participate(const string& state_name) const;
    MainControl& operator+=(Participant& p);
    MainControl& operator-=(Participant& p);
    MainControl& operator+=(Vote v);

    friend std::ostream& operator<<(std::ostream& os, const MainControl& mainControl);

    class Iterator;
    Iterator begin() const;
    Iterator end() const;
};

class MainControl::Iterator{
    const MainControl* eurovision;
    int index;
    Iterator(const MainControl* eurovision, int index);
    friend class MainControl;

public:
    const Participant& operator*() const;
    Iterator& operator++();
    bool operator==(const Iterator& i) const;
    bool operator<(const Iterator& i) const;
    Iterator&operator--() = delete;
};

// -----------------------------------------------------------

#endif
