#pragma once
#include<iostream>
using namespace std;
class Pair {
private:
    int first;
    int second;
public:
    Pair() { first = -1; second = -1; };

    Pair(int f, int s) {
        setfirst(f);
        setsecond(s);
    }
    void setfirst(int f) {
        first = f;
    }
    void setsecond(int sec) {
        second = sec;
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

