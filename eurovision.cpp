#include <iostream>

int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}

Participant::Participant(string state, string song, int timeLength, string singer): state(state), song(song),
                                                        timeLength(timeLength), singer(singer), is_registered(false){
}
Participant::~Participant(){
    //the d'ors of string class are called.
}
Participant::

