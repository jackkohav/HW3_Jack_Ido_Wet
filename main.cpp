#include <iostream>
using std::cout;
using std::endl;

template<typename Iterator>
Iterator get(Iterator begin, Iterator end, int place){
    if(place <= 0) return end;
    int size = 0;
    for(Iterator m = begin; m != end; ++m){
        ++size;
    }
    if(size < place) return end;
    Iterator result;
    Iterator current_max = begin;
    for(Iterator k = begin; k != end; ++k){ // first, set result to the maximum
        if(*current_max < *k ) current_max = k;
    }
    result = current_max;
    for(Iterator l = begin; l != end; ++l){ // setting current_max to the first element that is less than result
        if(*l < *result){
            current_max = l;
            break;
        }
    }
    for(int j = 1; j < place; ++j){ // every iteration, result will be set to the largest element less than the previous result
        for(Iterator k = begin; k != end; ++k){
            if(*current_max < *k && *k < *result) current_max = k;
        }
        result = current_max;
        for(Iterator l = begin; l != end; ++l){ // setting current_max to the first element that is less than result
            if(*l < *result){
                current_max = l;
                break;
            }
        }
    }
    return result;
}
int main() {
    int array[10] ={1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int* index = get<int*>(array, array+10, 7);
    cout << *index << endl;
    return 0;
}