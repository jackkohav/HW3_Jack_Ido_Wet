#include <iostream>
#include <string>
#include "eurovision.h"
#include <array>

Participant::Participant(const string& state, const string& song, const int& timeLength,
                         const string& singer): State(state), Song(song),
        Time_Length(timeLength), Singer(singer), Is_Registered(false){}

string Participant::state() const{
    return State;
}

string Participant::song() const{
    return Song;
}

int Participant::timeLength() const{
    return Time_Length;
}

string Participant::singer() const{
    return Singer;
}

bool Participant::isRegistered() const{
    return Is_Registered;
}


Voter::Voter(string state, VoterType type): State(state), Type(type) {
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

void Participant::updateRegistered(bool is_registered){
    Is_Registered = is_registered;
}



std::ostream& operator<<(std::ostream& os, Participant& p){
    os << "[" << p.state() << "/" << p.song() << "/" << p.timeLength() << "/" << p.singer() << "]";
    return os;
}

string Voter::state() const{
    return State;
}

VoterType Voter::voterType() const {
    return Type;
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

Vote::Vote(const Voter& voter, const string& vote):
        voter(voter.state(), voter.voterType()), twelve_pts(""), ten_pts(""),
        eight_pts(""), seven_pts(""), six_pts(""), five_pts(""),
        four_pts(""), three_pts(""), two_pts(""), one_pts(""){
    if(voter.voterType() == Regular){
        one_pts = string(vote);
    }
    else{
        twelve_pts = string(vote);
    }
}

Vote::Vote(const Voter &voter, const string &vote1, const string &vote2,
           const string &vote3, const string &vote4, const string &vote5,
           const string &vote6, const string &vote7, const string &vote8,
           const string &vote9, const string &vote10):
           voter(voter.state(), voter.voterType()),  twelve_pts(vote1),
           ten_pts(vote2), eight_pts(vote3), seven_pts(vote4), six_pts(vote5),
           five_pts(vote6), four_pts(vote7), three_pts(vote8), two_pts(vote9),
           one_pts(vote10){}
