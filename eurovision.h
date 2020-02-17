#ifndef EUROVISION_H_
#define EUROVISION_H_

#include <iostream>

// it's allowed to define here any using statements, according to needs.
// do NOT define here : using namespace std;

//---------------------------------------------------

enum VoterType { All, Regular, Judge };
enum Phase { Registration, Contest, Voting };

//---------------------------------------------------
typedef char* string;
class Participant
{
// relevant private members can be defined here, if necessary.
    bool Is_Registered;
    string State;
    string Song;
    int Time_Length;
    string Singer;
public :
// need to define here possibly c'tr and d'tr and ONLY methods that
// are mentioned and demonstrated in the test example that has been published.
// NO OTHER METHODS SHOULD APPEAR HERE.
    Participant(string state, string song, int timeLength, string singer);
    Participant(const Participant& p) = delete;
    ~Participant();
    string state();
    string song();
    int timeLength();
    string singer();
    bool isRegistered();
    void update(string new_song, int new_time_length, string new_singer);
    Participant& operator=(const Participant& p) = delete;
// NO friend is allowed here.

};
std::ostream& operator <<(std::ostream os, Participant& p);
//---------------------------------------------------


class Voter
{
// relevant private members can be defined here, if necessary.

public :

// need to define here possibly c'tr and d'tr and ONLY methods that
// are mentioned and demonstrated in the test example that has been published.
// NO OTHER METHODS SHOULD APPEAR HERE.

// NO friend is allowed here.

};


// -----------------------------------------------------------

struct Vote
{

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
