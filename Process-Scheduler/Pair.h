#pragma once
#include<iostream>
using namespace std;
class Pair {
private:
    int first;
    int second;
public:
    Pair() {};

    Pair(int first, int second) {
        setfirst(first);
        setsecond(second);
    }
    void setfirst(int first) {
        this->first = first;
    }
    void setsecond(int second) {
        this->second = second;
    }
    int getfirst() {
        return first;
    }
    int getsecond() {
        return second;
    }
    void printPair() {
        cout << "(" << first << ", " << second << ")";
    }
    void printfirst() {
        cout << first;
    }
    void printsecond() {
        cout << second;
    }
};

