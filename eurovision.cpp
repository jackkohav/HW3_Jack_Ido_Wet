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
void Participant::update(string new_song, int new_time_length, string new_singer) {
    if(Is_Registered)
        return;
    if(new_song != "")
        Song = new_song;
    if(new_time_length != 0)
        Time_Length = new_time_length;
    if(new_singer != "")
        Singer = new_singer;
}
std::ostream& operator<<(std::ostream& os, Participant& p){
    os << "[" << p.state() << "/" << p.song() << "/" << p.timeLength() << "/" << p.singer() << "]";
    return os;
}
