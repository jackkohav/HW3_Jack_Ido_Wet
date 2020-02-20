#include <iostream>
#include "eurovision.h"

void error(const char* str) {
    std::cerr << "Error: " << str << std::endl;
    exit(0);
}

int strcmp(const char* String1, const char* String2)
{
    for (int i = 0; ; i++)
    {
        if (String1[i] != String2[i])
        {
            return String1[i] < String2[i] ? -1 : 1;
        }

        if (String1[i] == '\0')
        {
            return 0;
        }
    }
}

int strlen(const char* str) {
    const char *s;
    for (s = str; *s; ++s)
        ;
    return (s - str);
}

char* strcpy(char *c, const char* s)
{
    int i = 0;
    for(i=0; i <= strlen(s); i++)
        c[i]=s[i];
    return c;
}

char* strcat(char * s1, const char * s2)
{
    int i=0;
    for(i=strlen(s2);i<strlen(s1);i++)
        s1[i]=s2[i];
    s1[++i]=0;
    return s1;
}

char* String::allocate_and_copy(const char* str, int size) {
    return strcpy(new char[size + 1], str);
}

String::String(const char* str) {
    length = strlen(str);
    data = allocate_and_copy(str, length);
}
String::String(const String& str) :
        length(str.size()),
        data(allocate_and_copy(str.data, str.length)) {
}
String::~String() {
    delete[] data;
}
int String::size() const {
    return length;
}

String& String::operator=(const String& str) {
    if (this == &str) {
        return *this;
    }
    delete[] data;
    data = allocate_and_copy(str.data, str.length);
    length = str.length;
    return *this;
}
String& String::operator+=(const String& str) {
    char* new_data = allocate_and_copy(data, this->length + str.length);
    strcat(new_data, str.data);
    delete[] data;
    length += str.length;
    data = new_data;
    return *this;
}
void String::verify_index(int index) const {
    if (index >= size() || index < 0) {
        error("Bad index");
    }
}
const char& String::operator[](int index) const {
    verify_index(index);
    return data[index];
}
char& String::operator[](int index) {
    verify_index(index);
    return data[index];
}
bool operator==(const String& str1, const String& str2) {
    return strcmp(str1.data, str2.data) == 0;
}
std::ostream& operator<<(std::ostream& os, const String& str) {
    os << str.data;
    return os;
}
bool operator<(const String& str1, const String& str2) {
    return strcmp(str1.data, str2.data) < 0;
}
bool operator!=(const String& str1, const String& str2) {
    return !(str1 == str2);
}
bool operator<=(const String& str1, const String& str2) {
    return (str1<str2 || str1==str2);
}
bool operator>(const String& str1, const String& str2) {
    return !(str1 <= str2);
}
bool operator>=(const String& str1, const String& str2) {
    return !(str1 < str2);
}
String operator+(const String& str1, const String& str2) {
    return String(str1) += str2;
}

//----------------------------------------------MainControl class:---------------------------------------------------

MainControl::~MainControl() {
    delete[](_participants);
    delete[](_regular_votes);
    delete[](_judge_votes);
}

bool MainControl::legalParticipant(const Participant &p) const {
    return ( p.state() != String("") && p.song() != String("")
        && p.singer() != String("") && p.timeLength() <= _max_time_length );
}

bool MainControl::participate(const String& state_name) const{
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
        int index = 0;
        for(; index < _number_of_participants; ++index){
            if(p.state() < (_participants[index])->state())
                break;
        }

        for(int i = _number_of_participants++; i > index; --i){
            _participants[i] = _participants[i-1];
        }
        _participants[index] = &p;
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
    _participants[--_number_of_participants] = nullptr;
    p.updateRegistered(false);
    return *this;
}

MainControl& MainControl::operator+=(const Vote& v){
    if(_phase != Voting) return *this;
    if(v._voter->voterType() == Regular) {
        if(v._voter->timesOfVotes() >= _max_votes || v._voter->state() == v._points[9]) return *this;

        for(int i = 0; i < 9; ++i){
            if(v._points[i] != String("")) return *this;
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
            if(v._points[i] == String("")){
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
    for(int i = 0; i < mainControl._number_of_participants; ++i){
        if(mainControl._phase == Registration) {
            os << *(mainControl._participants[i]) << std::endl;
        }
        else if(mainControl._phase == Voting){
            os << mainControl._participants[i]->state() << " : Regular(" <<
               mainControl._regular_votes[i] << ") Judge(" <<
               mainControl._judge_votes[i] << ")" << std::endl;
        }
    }
    os << "}" << std::endl;
    return os;
}

//----------------------------------------------Participant class:---------------------------------------------------


String Participant::state() const{
    return _state;
}

String Participant::song() const{
    return _song;
}

int Participant::timeLength() const{
    return _time_length;
}

String Participant::singer() const{
    return _singer;
}

bool Participant::isRegistered() const{
    return _is_registered;
}

void Participant::update(const String& new_song, const int& new_time_length, const String& new_singer) {
    if(_is_registered)
        return;
    if(new_song != String(""))
        _song = new_song;
    if(new_time_length != 0)
        _time_length = new_time_length;
    if(new_singer != String(""))
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

String Voter::state() const{
    return _state;
}

int Voter::timesOfVotes() const {
    return _number_of_votes;
}

VoterType Voter::voterType() const {
    return _type;
}


Voter& Voter::operator++() {
    ++_number_of_votes;
    return *this;
}

//----------------------------------------------Vote struct:---------------------------------------------------------

Vote::Vote(Voter& voter, const String& vote){
    _voter = &voter;
    for(auto & _point : _points){
        _point = String("");
    }
    if(voter.voterType() == Regular){
        _points[9] = String(vote);
    }
    else{
        _points[0] = String(vote);
    }
}

Vote::Vote(Voter& voter, const String& vote1, const String& vote2,
           const String& vote3, const String& vote4, const String& vote5,
           const String& vote6, const String& vote7, const String& vote8,
           const String& vote9, const String& vote10) {
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
Iterator get(Iterator begin, Iterator end, int place){
    if(place <= 0) return end;
    int size = 0;
    for(Iterator m = begin; m != end; ++m){
        ++size;
    }
    if(size < place) return end;
    Iterator result = begin;
    Iterator current_max = begin;
    for(int j = 0; j < place; ++j){
        for(Iterator k = begin; k != end; ++k){
            if(*current_max < *k && *k < *result) current_max = k;
        }
        result = current_max;
        for(Iterator l = begin; l != end; ++l){
            if(*l < *result){
                current_max = l;
                break;
            }
        }
    }
    return result;
}


//----------------------------------------------part b.2:-----------------------------------------------------------

//----------------------------------------------MainControl class:--------------------------------------------------

MainControl::Iterator MainControl::begin() const {
    return MainControl::Iterator(this, 0);
}

MainControl::Iterator MainControl::end() const {
    return MainControl::Iterator(this, _number_of_participants);
}
//----------------------------------------------MainControl::Iterator class:----------------------------------------

const Participant& MainControl::Iterator::operator*() const {
    return *(eurovision->_participants[index]);
}

MainControl::Iterator& MainControl::Iterator::operator++() {
    index++;
    return *this;
}

bool MainControl::Iterator::operator==(const MainControl::Iterator &i) const {
    return eurovision == i.eurovision && index == i.index;
}

bool MainControl::Iterator::operator!=(const MainControl::Iterator &i) const {
    return !(*this == i);
}

bool MainControl::Iterator::operator<(const MainControl::Iterator &i) const {
    return eurovision == i.eurovision && index < i.index;
}

//----------------------------------------------part b.3:-----------------------------------------------------------

//----------------------------------------------MainControl class:--------------------------------------------------

struct StateAndPts{
    String state;
    int points;
    StateAndPts(): state(""), points(0){}
};

bool operator<(StateAndPts& participant1, StateAndPts& participant2){
    return participant1.points < participant2.points ||
        (participant1.points == participant2.points && participant1.state < participant2.state);
}

String MainControl::operator()(int place, VoterType type) const{
    StateAndPts* contenders = new StateAndPts[_number_of_participants];
    int* relevant_points = new int[_number_of_participants];
    for(int i = 0; i < _number_of_participants; ++i){
        switch(type){
            case Regular:
                relevant_points[i] = _regular_votes[i];
            case Judge:
                relevant_points[i] = _judge_votes[i];
            default:
                relevant_points[i] = _regular_votes[i] + _judge_votes[i];
        }
    }
    for(int i = 0; i < _number_of_participants; ++i){
        contenders[i].state = _participants[i]->state();
        contenders[i].points = relevant_points[i];
    }
    StateAndPts* winner = get <StateAndPts*> (contenders, contenders+_number_of_participants, place);
    return winner->state;
}