#include <iostream>
#include <string>
#include "eurovision.h"
#include <array>

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
    if(i < 0) return end;
    int size = 0;
    for(Iterator m = begin; m != end; ++m){
        ++size;
    }
    if(size < i) return end;
    Iterator jth_max = begin;
    Iterator current_max = begin;
    for(int j  = 0; j < i; ++j){
        for(Iterator k = begin; k != end; ++k){
            if(*k > *current_max && *current_max < *jth_max) current_max = k;
        }
        jth_max = current_max;
        for(Iterator l = begin; l != end; ++l){
            if(*l < *jth_max){
                current_max = l;
                break;
            }
        }
    }
    return jth_max;
}