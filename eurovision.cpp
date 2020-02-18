#include <iostream>
#include <string>
#include "eurovision.h"

//----------------------------------------------MainControl class:---------------------------------------------------


MainControl::MainControl(int max_length, int max_participants, int max_votes):
        _max_votes(max_votes), _number_of_votes(0), _max_time_length(max_length),
        _max_participants(max_participants), _number_of_participants(0),
        _phase(Registration), _participants(new const Participant*[max_participants]()),
        _regular_votes(new const int[max_participants]()), _judge_votes(new const int[max_participants]()){}


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
}

MainControl& MainControl::operator+=(Vote& v){

}

std::ostream& operator<<(std::ostream& os, const MainControl& mainControl){
    os << "{" << std::endl << "Voting" << std::endl;
    for(int i = 0; i < mainControl._number_of_participants; ++i){
        os << mainControl._participants[i]->state() << " : Regular(" <<
        mainControl._regular_votes[i] << ") Judge(" << mainControl._judge_votes[i] << ")" << std::endl;
    }
    os << "}";
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

//----------------------------------------------Voter class:---------------------------------------------------------

std::ostream& operator<<(std::ostream& os, Participant& p){
    os << "[" << p.state() << "/" << p.song() << "/" << p.timeLength() << "/" << p.singer() << "]";
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

Vote::Vote(const Voter& voter, const string& vote1, const string& vote2,
           const string& vote3, const string& vote4, const string& vote5,
           const string& vote6, const string& vote7, const string& vote8,
           const string& vote9, const string& vote10):
           voter(voter.state(), voter.voterType()),  twelve_pts(vote1),
           ten_pts(vote2), eight_pts(vote3), seven_pts(vote4), six_pts(vote5),
           five_pts(vote6), four_pts(vote7), three_pts(vote8), two_pts(vote9),
           one_pts(vote10){}

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