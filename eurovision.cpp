#include <iostream>
#include <string>
#include "eurovision.h"


Participant::Participant(string state, string song, int timeLength,
                         string singer): State(state), Song(song),
        Time_Length(timeLength), Singer(singer), Is_Registered(false){}

string Participant::state(){
    return State;
}

string Participant::song(){
    return Song;
}

int Participant::timeLength() {
    return Time_Length;
}
string Participant::singer(){
    return Singer;
}
bool Participant::isRegistered(){
    return Is_Registered;
}
std::ostream& operator<<(std::ostream& os, Participant& p){
    os << "[" << p.state() << "/" << p.song() << "/" << p.timeLength() << "/" << p.singer() << "]";
    return os;
}

template<typename Iterator>
Iterator get(Iterator begin, Iterator end, int i){
    
}