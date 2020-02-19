#include <iostream>
#include <string>
#include "eurovision.h"

//----------------------------------------------MainControl class:---------------------------------------------------


MainControl::MainControl(int max_length, int max_participants, int max_votes):
        _max_votes(max_votes), _number_of_votes(0), _max_time_length(max_length),
        _max_participants(max_participants), _number_of_participants(0),
        _phase(Registration), _participants(new const Participant*[max_participants]()),
        _regular_votes(new int[max_participants]()), _judge_votes(new int[max_participants]()){}


MainControl::~MainControl() {
    delete[](_participants);
    delete[](_regular_votes);
    delete[](_judge_votes);
}

bool MainControl::legalParticipant(const Participant &p) const {
    return ( p.state() != "" && p.song() != "" && p.singer() != ""
            && p.timeLength() <= _max_time_length );
}

bool MainControl::participate(const string& state_name) const{
    for(int i = 0; i < _number_of_participants; ++i){
        if(_participants[i]->state() == state_name) return true;
    }
    return false;
}

void MainControl::setPhase(const Phase& phase) {
    if( (_phase == Registration && phase == Contest) ||
            (_phase == Contest && phase == Voting) ){
        _phase = phase;
    }
}

MainControl& MainControl::operator+=(Participant& p) {
    if(legalParticipant(p) && _number_of_participants < _max_participants
            && _phase == Registration && !participate(p.state())) {
        _participants[_number_of_participants++] = &p;
        p.updateRegistered(true);
    }
    return *this;
}

MainControl& MainControl::operator-=(Participant& p) {
    if(_phase != Registration || !p.isRegistered()) return *this;
    int participant_index = 0;
    for(int i = 0; i < _number_of_participants; ++i){
        if(_participants[i]->state() ==  p.state()){
            participant_index = i;
            break;
        }
    }
    for(int i = participant_index + 1; i < _number_of_participants; ++i){
        _participants[i - 1] = _participants[i];
    }
    _participants[--_number_of_participants] = NULL;
    p.updateRegistered(false);
    return *this;
}

MainControl& MainControl::operator+=(Vote v){
    if(_phase != Voting) return *this;
    if(v._voter->voterType() == Regular) {
        if(v._voter->timesOfVotes() >= _max_votes || v._voter->state() == v._points[9]) return *this;

        for(int i = 0; i < 9; ++i){
            if(v._points[i] != "") return *this;
        }

        for(int i = 0; i < _max_participants; ++i){
            if(_participants[i]->state() == v._points[9]){
                ++_regular_votes[i];
                break;
            }
        }
    } else {
        int points_for_places[10] = {12, 10, 8, 7, 6, 5, 4, 3, 2, 1};
        if(v._voter->timesOfVotes() >= 1) return *this;
        for(int i = 0; i < _number_of_participants; ++i) {
        }
        for(int i = 0; i < 10; ++i){
            if(v._points[i] == ""){
                return *this;
            }
            for(int j = 0; j < _max_participants; ++j){
                if(_participants[j]->state() == v._points[i] && v._points[i] != v._voter->state()){
                    _judge_votes[j] += (points_for_places[i]);
                    break;
                }
            }
        }
    }
    ++(*v._voter);
    return *this;
}

std::ostream& operator<<(std::ostream& os, const MainControl& mainControl){

    os << "{" << std::endl;
    if(mainControl._phase == Registration) os << "Registration";
    if(mainControl._phase == Contest) os << "Contest";
    if(mainControl._phase == Voting) os << "Voting";
    os << std::endl;
    string last_min = "";
    string current_min;
    int current_index;
    for(int i = 0; i < mainControl._number_of_participants; ++i){
        current_min = "";
        for(int j = 0; j < mainControl._number_of_participants; ++j){
            if(mainControl._participants[j]->state() < current_min || current_min == ""){
                if(mainControl._participants[j]->state() > last_min){
                    current_min = mainControl._participants[j]->state();
                    current_index = j;
                }
            }
        }
        if(mainControl._phase == Registration) {
            os << *(mainControl._participants[current_index]) << std::endl;
        }
        else if(mainControl._phase == Voting){
            os << mainControl._participants[current_index]->state() << " : Regular(" <<
               mainControl._regular_votes[current_index] << ") Judge(" <<
               mainControl._judge_votes[current_index] << ")" << std::endl;
        }
        last_min = current_min;
    }
    os << "}" << std::endl;
    return os;
}

//----------------------------------------------Participant class:---------------------------------------------------

Participant::Participant(const string& state, const string& song, const int& timeLength,
                         const string& singer): _state(state), _song(song),
        _time_length(timeLength), _singer(singer), _is_registered(false){}

string Participant::state() const{
    return _state;
}

string Participant::song() const{
    return _song;
}

int Participant::timeLength() const{
    return _time_length;
}

string Participant::singer() const{
    return _singer;
}

bool Participant::isRegistered() const{
    return _is_registered;
}

void Participant::update(const string& new_song, const int& new_time_length, const string& new_singer) {
    if(_is_registered)
        return;
    if(new_song != "")
        _song = new_song;
    if(new_time_length != 0)
        _time_length = new_time_length;
    if(new_singer != "")
        _singer = new_singer;
}

void Participant::updateRegistered(bool is_registered){
    _is_registered = is_registered;
}

std::ostream& operator<<(std::ostream& os, const Participant& p){
    os << "[" << p.state() << "/" << p.song() << "/" << p.timeLength() << "/" << p.singer() << "]";
    return os;
}

//----------------------------------------------Voter class:---------------------------------------------------------


std::ostream& operator<<(std::ostream& os, const Voter& v){
    os << "<" << v.state() << "/";
    if(v.voterType() == Regular) os << "Regular>";
    if(v.voterType() == Judge) os << "Judge>";
    return os;
}

string Voter::state() const{
    return _state;
}

int Voter::timesOfVotes() const {
    return _number_of_votes;
}

VoterType Voter::voterType() const {
    return _type;
}

Voter::Voter(const string& state, const VoterType& type): _state(state), _type(type), _number_of_votes(0) {
}

Voter& Voter::operator++() {
    ++_number_of_votes;
    return *this;
}

//----------------------------------------------Vote struct:---------------------------------------------------------

Vote::Vote(Voter& voter, const string& vote){
    _voter = &voter;
    for(int i = 0; i < 10; ++i){
        _points[i] = string("");
    }
    if(voter.voterType() == Regular){
        _points[9] = string(vote);
    }
    else{
        _points[0] = string(vote);
    }
}

Vote::Vote(Voter& voter, const string& vote1, const string& vote2,
           const string& vote3, const string& vote4, const string& vote5,
           const string& vote6, const string& vote7, const string& vote8,
           const string& vote9, const string& vote10) {
    _voter = &voter;
    _points[0] = vote1;
    _points[1] = vote2;
    _points[2] = vote3;
    _points[3] = vote4;
    _points[4] = vote5;
    _points[5] = vote6;
    _points[6] = vote7;
    _points[7] = vote8;
    _points[8] = vote9;
    _points[9] = vote10;
}


//----------------------------------------------part b.1:-----------------------------------------------------------

template<typename Iterator>
Iterator get(Iterator begin, Iterator end, int i){
    if(i < 0) return end;
    int size = 0;
    for(Iterator m = begin; m != end; ++m){
        ++size;
    }
    if(size < i) return end;
    Iterator jth_to_max = begin;
    Iterator current_max = begin;
    for(int j  = 0; j < i; ++j){
        for(Iterator k = begin; k != end; ++k){
            if(*k > *current_max && *current_max < *jth_to_max) current_max = k;
        }
        jth_to_max = current_max;
        for(Iterator l = begin; l != end; ++l){
            if(*l < *jth_to_max){
                current_max = l;
                break;
            }
        }
    }
    return jth_to_max;
}