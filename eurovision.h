#ifndef EUROVISION_H_
#define EUROVISION_H_

#include <iostream>

// it's allowed to define here any using statements, according to needs.
// do NOT define here : using namespace std;

//---------------------------------------------------

enum VoterType { All, Regular, Judge };
enum Phase { Registration, Contest, Voting };

//---------------------------------------------------
class String {
    int length;
    char* data;
    static char* allocate_and_copy(const char* data, int size);
    void verify_index(int index) const;
public:
    String(const char* str = ""); // String s1; or String s1 = "aa";
    String(const String& str); // String s2(s1);
    ~String();
    int size() const;
    String& operator=(const String&); // s1 = s2;
    String& operator+=(const String& str); // s1 += s2;
    const char& operator[](int index) const; // s[5] for const s
    char& operator[](int index); // s[5] for non-const s
    friend std::ostream& operator<<(std::ostream&, const String&); // cout << s1;
    friend bool operator==(const String&, const String&); // s1==s2
    friend bool operator<(const String&, const String&); // s1<s2
};

bool operator!=(const String& str1, const String& str2);
bool operator<=(const String& str1, const String& str2);
bool operator>(const String& str1, const String& str2);
bool operator>=(const String& str1, const String& str2);
String operator+(const String& str1, const String& str2);

class Participant
{
// relevant private members can be defined here, if necessary.
    bool _is_registered;
    String _state;
    String _song;
    int _time_length;
    String _singer;
public :
// need to define here possibly c'tr and d'tr and ONLY methods that
// are mentioned and demonstrated in the test example that has been published.
// NO OTHER METHODS SHOULD APPEAR HERE.
    Participant(const String& state, const String& song, const int& timeLength, const String& singer):
    _is_registered(false), _state(state), _song(song), _time_length(timeLength), _singer(singer){}
    Participant(Participant& p) = delete;
    ~Participant() = default;
    String state() const;
    String song() const;
    int timeLength() const;
    String singer() const;
    bool isRegistered() const;
    void update(const String& new_song, const int& new_time_length, const String& new_singer);
    void updateRegistered(bool is_registered);
    Participant& operator=(const Participant& p) = delete;
// NO friend is allowed here.

};
std::ostream& operator <<(std::ostream& os, const Participant& p);
//---------------------------------------------------


class Voter
{
// relevant private members can be defined here, if necessary.
    String _state;
    VoterType _type;
    int _number_of_votes;

public :
    explicit Voter(const String& state, const VoterType& type = Regular): _state(state), _type(type), _number_of_votes(0) {}
    ~Voter() = default;
    String state() const;
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
    String _points[10];
    Voter* _voter;
    Vote(Voter& voter, const String& vote);
    Vote(Voter& voter, const String& vote1, const String& vote2,
        const String& vote3 = String(""), const String& vote4 = String(""),
        const String& vote5 = String(""), const String& vote6 = String(""),
        const String& vote7 = String(""), const String& vote8 = String(""),
        const String& vote9 = String(""), const String& vote10 = String(""));
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
    explicit MainControl(int max_length = 180, int max_participants = 26, int max_votes = 5):
            _phase(Registration), _max_votes(max_votes), _number_of_votes(0), _max_time_length(max_length),
            _max_participants(max_participants), _number_of_participants(0),
            _participants(new const Participant*[max_participants]()),
            _regular_votes(new int[max_participants]()), _judge_votes(new int[max_participants]()){}
    ~MainControl();
    void setPhase(const Phase& phase);
    bool legalParticipant(const Participant& p) const;
    bool participate(const String& state_name) const;
    MainControl& operator+=(Participant& p);
    MainControl& operator-=(Participant& p);
    MainControl& operator+=(const Vote& v);
    class Iterator;
    Iterator begin() const;
    Iterator end() const;

    friend std::ostream& operator<<(std::ostream& os, const MainControl& mainControl);
};

class MainControl::Iterator{
    const MainControl* eurovision;
    int index;
    Iterator(const MainControl* eurovision, int index): eurovision(eurovision), index(index){}
    friend class MainControl;

public:
    Iterator(): eurovision(nullptr), index(0){}
    Iterator(const Iterator&) = default;
    Iterator& operator=(const Iterator&) = default;
    const Participant& operator*() const;
    Iterator& operator++();
    bool operator==(const Iterator& i) const;
    bool operator!=(const Iterator& i) const;
    bool operator<(const Iterator& i) const;
    Iterator& operator--() = delete;
};

// -----------------------------------------------------------

#endif
