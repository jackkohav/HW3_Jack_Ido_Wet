#include <iostream>


Participant::Participant(string state, string song, int timeLength, string singer): state(state), song(song),
                                                        timeLength(timeLength), singer(singer), is_registered(false){
}
string Participant::state(){
    return state;
}
string Participant::song(){
    return song;
}
int Participant::timeLength() {
    return timeLength;
}
string Participant::singer(){
    return singer;
}
bool Participant::is_registered(){
    return is_registered;
}
std::ostream& Participant::operator<<(std::ostream& os, Participant& p){
    os << "[" << p.state << "/" << p.song << "/" << p.timeLength << "/" << p.singer << "]";
    return os;
}
Participant::~Participant(){
    //the d'ors of string class are called.
}
